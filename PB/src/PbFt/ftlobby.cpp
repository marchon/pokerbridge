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
		w=static_cast<QWidget*>(w->parent());
		if(w)
			qLog(Info)<<"MM ->"+QTUtil::widgetInfo(w);
	}

}

void FTLobbyHooks::onWidgetShow(QWidget *w)
{
//	LOG_HOOK("onWidgetShow "<<QTUtil::widgetInfo(w));
	if(FTLobby::instance())
	{
		FTLobby::instance()->onWidgetShow(w);
	
		if(!FTPanel::instance())
		{
			if(PB_OPTION_IS_TRUE("Debug/Panel", false))
			{
				// placed here to guarantee GUI thread
				FTPanel::createInstance();
			}
		}
	}
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
	if(inInstance)
		return 0;
	inInstance=true;
	instanceMutex.lock(); 
	if(_instance)
	{ 
		instanceMutex.unlock(); 
		inInstance=false;
		return _instance;  
	} 
	qLog(Debug)<<"crea";
	_instance=new FTLobby();
	instanceMutex.unlock(); 
	inInstance=false;
	return _instance; 
}//return qFTLobby(); }

/*FTLobby* FTLobby::instance()
{
	if(_instance)
		return _instance;
	FTLobby *instance = new FTLobby();
	instance->init();
	_instance = instance;
}
*/
FTLobby::FTLobby() : FTWidgetHook(0,0)
{
	qLog(Debug)<<"FTLobby::FTLobby";
	_loginDone = false;

	_initialized = false;
	init();
}

void FTLobby::init()
{
	if(_initialized)
		return;
	


	QString settingsFilePath = QDir::currentPath()+QDir().separator()+"PBFT.INI";
	_settings = new QSettings(settingsFilePath, QSettings::IniFormat);

	_tables = new FTTables(0, this); 

	_handHistory = FTHandHistory::instance();
	_handWriter = new FTHandWriter(this);
	_handWriter->setHistoryDir(settings()->value("History/outputDir",".").toString());
	_handWriter->subscribe(_handHistory);

	_lists = new FTLists(0, this);

	_tourneys = new FTTourneys(0, this);
 
	_tasks = new FTTasks(this);
	connect(this, SIGNAL(widgetClosing(FTWidgetHook*)), 
		_tasks, SLOT(stop()));

	qLog(Debug)<<"lobby created"; 
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
			qLog(Info)<<"Main window cought";
			emit widgetHooked(this);
		}
	}
	//if(w==widget())
	//{
	//qLog(Info)<<"exploring children of "<<w->metaObject()->className();
	if(!qstrcmp(w->metaObject()->className(),"CConnectDlg"))
		onWidgetChilds(w, true);	
	//}

	if(!_loginDone)
	{
		if(!_loginBtn)
			_loginBtn = FTButton::fromWidget(w,this, "","","btn_login");
		if(_loginBtn && _loginBtn->button() && _loginBtn->button()->isEnabled() && widget() && _loginBtn->visibleTo(this))
		{
			qLog(Info)<<"Clicking login";
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
	qLog(Debug)<<"~FTLobby";
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
	if(PB_OPTION_IS_TRUE("Modules/TableOpener",true))
		tasks()->tableOpener()->start();
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
