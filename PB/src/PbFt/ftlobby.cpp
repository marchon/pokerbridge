#include "stdafx.h"
#include "fttable.h"
#include "ftlobby.h"
#include "fthooks.h"
#include "fttables.h"
#include "fthandhistory.h"
#include "fthandwriter.h"
#include "ftlist.h"
#include "fttourneys.h"
#include "ftpanel.h"
#include "mdump.h"
#include "ftmainthread.h"
#include "fttasks.h"
#include "QtGui/qtablewidget.h"

void FTLobbyHooks::installHooks()
{
	QAbstractItemViewHooks::rowsInserted = onRowsInserted;
	QWidgetHooks::mouseButtonPressEvent = onMouseButtonPress;
	QWidgetHooks::setVisible = onWidgetSetVisible;
	QWidgetHooks::show = onWidgetShow;
	QWidgetHooks::closeEvent = onClose;
	QStringHooks::append = onStringAppend;
	QStringHooks::indexOf = onStringIndexOf;
	QWidgetHooks::paintDone = onPaint;
	QWidgetHooks::destroyEvent = onDestroy;
	QWidgetHooks::drawTextItem = onDrawTextItem;
}

void FTLobbyHooks::uninstallHooks()
{
	QAbstractItemViewHooks::rowsInserted = 0;
	QWidgetHooks::mouseButtonPressEvent = 0;
	QWidgetHooks::setVisible = 0;
	QWidgetHooks::show = 0;
	QWidgetHooks::closeEvent = 0;
	QStringHooks::append = 0;
	QStringHooks::indexOf = 0;
	QWidgetHooks::paintDone = 0;
	QWidgetHooks::destroyEvent= 0;
}

#define LOG_HOOK(t) qLog(Info)<<QThread::currentThread()<<":"<<t;

// entries from the hooks
void FTLobbyHooks::onRowsInserted(QAbstractItemView *view, int start, int end)
{
	//LOG_HOOK("onRowsInserted");
	if(	FTLobby::instance())
		FTLobby::instance()->onRowsInserted(view, start, end);
}

void FTLobbyHooks::onClose(QWidget *w, QEvent *e)
{
//	LOG_HOOK("onClose");
	if(FTLobby::instance())
		FTLobby::instance()->onClose(w,e);
}

void FTLobbyHooks::onDestroy(QWidget *w, QEvent *e)
{
	//LOG_HOOK("onDestroy");
	if(FTLobby::instance())
		FTLobby::instance()->onDestroy(w,e);
}

void FTLobbyHooks::onMouseButtonPress(QWidget *w, QEvent *e)
{
	//CRASH
	//*(char*)0x1234567=0;
	LOG_HOOK("MM"<<QTUtil::widgetInfo(w)<<" "<<e);
	while(w!=0)
	{
		QMouseEvent *me = static_cast<QMouseEvent*>(e);
		w=static_cast<QWidget*>(w->parent());
		if(w)
			qLog(Info)<<"MM "<<me->x()<<":"<<me->y()<<"->"+QTUtil::widgetInfo(w);
	}

}

void FTLobbyHooks::onWidgetShow(QWidget *w)
{
//	LOG_HOOK("onWidgetShow "<<QTUtil::widgetInfo(w));
	if(!FTPanel::instance())
		{
			//qLog(Debug)<<"Need Panel="<<PB_OPTION_IS_TRUE("Debug/Panel", false);
			if(PB_OPTION_IS_TRUE("Debug/Panel", false))
			{
				// placed here to guarantee GUI thread
				FTPanel::createInstance();
			}
		}

	if(FTLobby::instance())
		FTLobby::instance()->onWidgetShow(w);
}

void FTLobbyHooks::onWidgetSetVisible(QWidget *w, bool isVisible)
{
//	LOG_HOOK("onWidgetSetVisible"<<QTUtil::widgetInfo(w)<<","<<isVisible);
	if(FTLobby::instance())
		FTLobby::instance()->onWidgetSetVisible(w, isVisible);
}

void FTLobbyHooks::onStringIndexOf(const QString &s)
{
	//LOG_HOOK("onStringIndexOf");
	if(FTLobby::instance())
		FTLobby::instance()->onStringIndexOf(s);
}

void FTLobbyHooks::onStringAppend(const QString &self, const QString &s)
{
	//LOG_HOOK("onStringAppend");
	if(FTLobby::instance())
		FTLobby::instance()->onStringAppend(self, s);
}

void FTLobbyHooks::onPaint(QWidget *w)
{
	if(0==FTLobby::instance())
		FTLobby::create(w);
//	LOG_HOOK("onPaint");
	if(FTLobby::instance())
		FTLobby::instance()->onPaint(w);
//	return true;
}

void FTLobbyHooks::onDrawTextItem(QWidget *widget, const QPointF &p, const QTextItem &ti)
{
//	LOG_HOOK("onDrawTextItem");
	if(FTLobby::instance())
		FTLobby::instance()->onDrawTextItem(widget, p, ti);
}




//Q_GLOBAL_STATIC(FTLobby, qFTLobby);
FTLobby * volatile  _instance = 0;
//FTLobby globalLobby;
bool inInstance = false;
QMutex instanceMutex;

QWaitCondition FTLobby::lobbyCreated;

FTLobby* FTLobby::instance()
{ 
	return _instance;
	
}

void FTLobby::create(QWidget *w)
{
	if(0==_instance)
	{
		QWidget *lobbyWidget = QTUtil::parentWithClass(w,"CMainWindow");
		if(0!=lobbyWidget && lobbyWidget->isVisible())
		{
//			FTLobby::rpcConnect();
			_instance = new FTLobby();
		}
	}
}

FTLobby::FTLobby() : FTWidgetHook(0,0)
{
	static char logName[_MAX_PATH];
	sprintf(logName,"pbft-%d.log",GetCurrentProcessId());

	QPBLog::install();
	QPBLog::logToFile(logName);
	qLog(Debug)<<"LOG STARTED";
	QPBLog::flushLogFile();

	static char dumpName[_MAX_PATH];
	sprintf(dumpName,"pbft-%d",GetCurrentProcessId());
	MiniDumper::Install(dumpName);
//#define TEST_EX
#ifdef TEST_EX
	static int n=0;
	static int j;
	j=1/n;
	*(char*)n=0;
#endif 

	setObjectName(QString("FT-%1").arg(GetCurrentProcessId()));

	qLog(Debug)<<"FTLobby::FTLobby, thread "<<QThread::currentThread();
	_loginDone = false;
	_filterIndex = -1;
	_initialized = false;
	_waitFilterUpdate = 0;
	
	init();
}

void FTLobby::init()
{
	if(_initialized)
		return;
	
	RTcpMessageQueue *mq = new RTcpMessageQueue(this);
	mq->connectToHost("localhost",777);
	//mq->waitConnected();

	
	QString	settingsFilePath = QDir::currentPath()+QDir().separator()+"PBFT.INI";

	_settings = new QSettings(settingsFilePath, QSettings::IniFormat);

	_tables = new FTTables(0, this); 

	_handHistory = FTHandHistory::instance();
	_handWriter = new FTHandWriter(this);
	_handWriter->setHistoryDir(settings()->value("Grabber/outputDir",".").toString());
	_handWriter->subscribe(_handHistory);

	_lists = new FTLists(0, this);

	_tourneys = new FTTourneys(0, this);
	_tourneys->setTables(_tables);
 
	_tasks = new FTTasks(this);
	connect(this, SIGNAL(widgetClosing(FTWidgetHook*)), 
		_tasks, SLOT(stop()));

	connect(_lists, SIGNAL(paintDoneEvent(FTList*)), this, SLOT(onPaintDoneEvent(FTList*)));

	//qLog(Debug)<<"lobby created"; 
	_initialized = true;

	lobbyCreated.wakeAll();
}


void FTLobby::onWidget(QWidget *w)
{
	FTWidgetHook::onWidget(w);
	if(widget()==0)
	{
		// catch main window
		QWidget *mainWidget = QTUtil::parentWithClass(w, "CMainWindow");
		if(mainWidget)
		{
			setWidget(mainWidget);
			//qLog(Info)<<"Main window cought";
			emit widgetHooked(this);
		}
	}
	//if(w==widget())
	//{
	//qLog(Info)<<"exploring children of "<<w->metaObject()->className();
	if(!qstrcmp(w->metaObject()->className(),"CConnectDlg"))
		onWidgetChilds(w, true);	
	//}

	if(PB_OPTION_IS_TRUE("Modules/AutoLogin", false))
		autoLogin(w);

	if(PB_OPTION_IS_TRUE("Modules/SetFilter", false))
		clickFilter();
}

void FTLobby::autoLogin(QWidget *w)
{
	if(!_loginDone)
	{
		QString loginButtonName = PB_OPTION_STR("AutoLogin/Button", "btn_login"); //btn_observe
		if(!_loginBtn)
			_loginBtn = FTButton::fromWidget(w,this, "","",loginButtonName);
		if(_loginBtn && _loginBtn->button() && _loginBtn->button()->isEnabled() && widget() && _loginBtn->visibleTo(this))
		{
			qLog(Info)<<"Clicking login button:"<<loginButtonName;
			_loginBtn->press();
			_loginDone = true;
			onLoggedIn();
		}
	}
	if(!_cancelConnectionBtn)
		_cancelConnectionBtn = FTButton::fromWidget(w,this,"","","cancelButton");
	if(!_connectionStatusLbl)
		_connectionStatusLbl = FTLabel::fromWidget(w, this, "","QLabel","statusLabel");

	if(_cancelConnectionBtn && _cancelConnectionBtn->widget() 
		&& _connectionStatusLbl && _connectionStatusLbl->widget())
	{
		qLog(Info)<<"Connecting FT. Status is: "<<_connectionStatusLbl->text();
		if(_connectionStatusLbl->text().indexOf("Unable")>-1)
		{
			qLog(Info)<<"Clicking Connection/Cancel";
			_cancelConnectionBtn->press();
		}
	}
	
}

extern FTMainThread mainThread;

FTLobby::~FTLobby()
{
	MiniDumper::Uninstall();
	//qLog(Debug)<<"~FTLobby";
	FTLobbyHooks::uninstallHooks();
	mainThread.exit(2);
	_instance = 0;
	//FTPanel::destroyInstance();
}

/*void FTLobby::destroy()
{
	delete instance();
}
*/
QSettings *FTLobby::settings()
{
	return _settings;
}

FTTasks *FTLobby::tasks()
{
	return _tasks;
}


void FTLobby::onLoggedIn()
{
	configUpdate();
}

QString FTLobby::grabMode()
{
	return PB_OPTION_STR("Grabber/Mode","");
}

void FTLobby::configUpdate()
{
	QString oldGrabMode = grabMode();

	if(tasks()->tourneyOpener())
		tasks()->tourneyOpener()->stop();

	QString profile = PB_OPTION_STR("Grabber/Profile","");
	gameFilter(profile);

	if(PB_OPTION_IS_TRUE("Modules/Grabber",true))
	{
		
		if(grabMode()=="Tourney")
			tasks()->tourneyOpener()->start();
	}
}

void FTLobby::onStringAppend(const QString &self, const QString &s)
{
	if(_handHistory)
		_handHistory->onStringAppend(self, s);
}

void FTLobby::onStringIndexOf(const QString &s)
{
	_tables->onStringIndexOf(s);
}

FTTables *FTLobby::tables()
{
	return _tables;
}

FTLists *FTLobby::lists()
{
	return _lists;
}

FTTourneys *FTLobby::tourneys()
{
	return _tourneys;
}

void FTLobby::onConfig(RMessage *msg)
{
	qLog(Debug)<<"onConfig";	
	Q_FOREACH(QString key, msg->args().keys())
	{
		if(!key.startsWith("r-"))
		{
			settings()->setValue(key, msg->args()[key]);
			configUpdate();
			qLog(Debug)<<"onConfig: "<<key<<msg->args()[key];
		}
	}

	qLog(Debug)<<"SI="<<PB_OPTION_INT("Grabber/SplitIndex",0)<<" SF="<<PB_OPTION_INT("Grabber/SplitFactor",1);
}


void FTLobby::gameFilter(QString filter)
{
	if(!PB_OPTION_IS_TRUE("Modules/SetFilter", false))
		return;

	_filters = filter.split("/");
	if(_filters.size()<3)
	{
		qLog(Debug)<<"Filter should be a/b/c/d/e !"<<filter;
		return;
	}
	qLog(Info)<<"FILTER: "<<filter;

	_filterIndex = 1;
	_filterClickTime = QTime::currentTime();
	
	clickFilter();
}

void FTLobby::onPaintDoneEvent(FTList *list)
{

}

void FTLobby::clickFilter()
{
	if(_filterIndex>_filters.size())
	{
		//qLog(Info)<<"Filter set done";
		_filterIndex=-1;
	}
	if(_filterIndex<1)
		return;
	if(_filterClickTime.elapsed()>15000 && _filterIndex>-1)
	{
		qLog(Info)<<"Failed to catch filter "<<_filters[_filterIndex-1]<<" after 15 secs in list_"<<_filterIndex;
		FTList *failedlist = lists()->list(QString("filter%1").arg(_filterIndex));
		if(failedlist)
		{
			for(int i=0;i<failedlist->paintedCount();i++)
				qLog(Debug)<<failedlist->value(i,0);
		}
		_filterIndex=-1;
		return;
	}
	FTList *f1 = lists()->list(QString("filter%1").arg(_filterIndex));
	if(!f1)
		return;
	int row = f1->indexOfRow(_filters[_filterIndex-1]);
	if(row<0)
	{
	}
	else
	{
		_filterIndex++;
		f1->click(row,0, 0.5,0.5);

		qLog(Debug)<<f1->objectName()<<": clicked "<<row;
	}
}

void FTLobby::onListUpdatedEvent(FTList *list)
{
}