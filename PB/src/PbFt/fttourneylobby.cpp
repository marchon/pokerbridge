#include "stdafx.h"
#include "fttourneylobby.h"
#include "ftbutton.h"
#include "fttourneys.h"
#include "fthooks.h"
#include "fttables.h"
#include "pbtourney.h"
#include "fttable.h"
#include "ftlobby.h"

FTTourneyLobby::FTTourneyLobby(QWidget *widget, QObject *parent) : FTWidgetHook(widget, parent)
{
	// upon creating, it takes some time for lobby elements to be found and parsed
	// it includes: status determining, observe/register buttons catching
	// after all these elements are found, "ready()" is set to true and widgetFound() raised
	_ready = false;
	_timeAlive=0;
	_observeBtn = 0;
	_observeAsked = false;
	_openedTime = QTime::currentTime();

	_status = "Unknown";
	hasPainted = false;
	//connect(this, SIGNAL(observeSig()), this, SLOT(doObserve()));

	connect(this, SIGNAL(widgetClosing(FTWidgetHook*)), this, SLOT(tourneyLobbyClosing(FTWidgetHook*)));

	new RMessageAdaptor(this);
	_timerId = startTimer(1000);
}

FTTourneyLobby::~FTTourneyLobby()
{
	qLog(Debug)<<"~FTTourneyLobby "<<tourneyId();
	killTimer(_timerId);
}

QString FTTourneyLobby::tourneyId()
{
	return objectName();
}

void FTTourneyLobby::setTourneyId(const QString &tourneyId)
{
	setObjectName(tourneyId);
}
//registernow_btn
///[:run_observe_table_btn]QPushButton/QAbstractButton"Observe
void FTTourneyLobby::onWidget(QWidget *w)
{
	FTWidgetHook::onWidget(w);
	if(w==widget())
		onWidgetChilds(w, true);
	if(0==_observeBtn)
	{
		_observeBtn = FTButton::fromWidget(w,this, "","","run_observe_table_btn");
		if(_observeBtn)
		{
			bool ena=_observeBtn->button()->isEnabled();

			qLog(Info)<<"tourlobby "<<tourneyId()<<" observe found:"<<w<<" ena="<<ena<< " "<<QTUtil::widgetInfo(w); 

		}
	}
}

bool FTTourneyLobby::canObserve()
{
	return _observeBtn && _observeBtn->visibleTo(this);
}


void FTTourneyLobby::observe()
{
/*	if(table()!=0)
	{
		qLog(Debug)<<"FTTourneyLobby::observe - table is already opened";
		return;
	}
	if(!canObserve())
	{
		qLog(Debug)<<"observe::can not observe";
	}
*/	_observeAsked = true;
	qLog(Info)<<"FTTourneyLobby::observe asked";
//	doObserve();
}

class QAccessButton : public QAbstractButton
{
public:
	void emitClicked(){emit clicked();}
	void emitReleased(){emit clicked();}
};

void FTTourneyLobby::doObserve()
{
	if(!isAlive())
	{
		qLog(Info)<<"FTTourneyLobby::observe is Closing "<<tourneyId();
		return;
	}
	if(!_ready)
	{
		qLog(Info)<<"FTTourneyLobby::observe is not ready "<<tourneyId();
	}
	if(0==_observeBtn || !_observeBtn->visibleTo(this))
	{
		qLog(Info)<<" FTTourneyLobby::observe: no observe button "<<tourneyId();
		return;
	}
	//widget()->activateWindow();
	_observeBtn->press();
	//((QAccessButton*)_observeBtn->button())->emitClicked();
	
	qLog(Info)<<"tourney "<<tourneyId()<<" observe click";
}


void FTTourneyLobby::onWidgetSetVisible(QWidget *w, bool isVisible)
{
	FTWidgetHook::onWidgetSetVisible(w, isVisible);
	
	if(w==widget())
	{
		onWidgetChilds(w, true);
		//FTWidgetHook::deferWidgetFound();
	}
}

FTTourneys *FTTourneyLobby::tourneys()
{
	return qobject_cast<FTTourneys*>(parent());

}

void FTTourneyLobby::emitWidgetFound()
{
	if(_ready)
	{
		qLog(Debug)<<"already created "<<tourneyId();
		return;
	}
	_ready = true;
	qLog(Info)<<"Tourney Lobby created ["+tourneyId()+"] "<<_openedTime.elapsed();
	_openedTime = QTime::currentTime();
	tourneys()->tourneyLobbyOpened(this);
	if(_status!="Unknown")
		tourneys()->sendTourneyInfo(tourneyId());
}


void FTTourneyLobby::tourneyLobbyClosing(FTWidgetHook *wh)
{
	tourneys()->sendTourneyInfo(tourneyId());
	tourneys()->tourneyLobbyClosed(this);
}

void FTTourneyLobby::onPaint(QWidget *w)
{
	FTWidgetHook::onPaint(w);

	// all this to emit ToruneyLobbyOpened after observeBtn was found
	if(!hasPainted && 0!=_observeBtn && _observeBtn->widget()==w && !_observeBtn->text().isEmpty())
	{
		hasPainted=true;

	//	emitWidgetFound();
	}
}

void FTTourneyLobby::onDrawTextItem(QWidget *w, const QPointF &p, const QTextItem &ti)
{
	const char *statusText[] = {"Running", "Completed", "Seating", "Registering" };
	//int statuses[]={PBTourneyStatus::Running, PBTourneyStatus::Completed, PBTourneyStatus::Seating };

	QRegExp valueRx("top_r_line_(\\d)_value");
	if(valueRx.indexIn(w->objectName())>-1)
	{
		//int status = PBTourneyStatus::Unknown;
		QString status = _status;
		for(int i=0;i<sizeof(statusText)/sizeof(statusText[0]); i++)
		{
			if(ti.text()==statusText[i])
				//status=statuses[i];
			{
//				qLog(Debug)<<" draw "<<ti.text()<<" in "<<tourneyId();
				status=statusText[i];
			}
		}
		if(_status != status)
		{
			qLog(Debug)<<QTime::currentTime()<<" Tourney "<<this<<":"<<tourneyId()<<" Status Changes To "<<status<< " From "<<_status<<" ("<<w->objectName()<<") alive="<<_timeAlive;
			qLog(Debug)<<QTUtil::widgetInfo(w);
			_status = (PBTourneyStatus)status;

			tourneys()->tourneyStatusChanged(this);
		}
	}
}

FTTable *FTTourneyLobby::table()
{
	FTTables *tables = tourneys()->tables();
	if(tables)
	{
		FTTable *table = tables->tourneyTable(tourneyId());
		return table;
	}
	return 0;
}

void FTTourneyLobby::timerEvent(QTimerEvent *e)
{
	if(!isAlive())
		return;
	_timeAlive++;
	if(!_ready)
	{
		if(_status=="Unknown")
			return;
		if(objectName().isEmpty())
			return;
		emitWidgetFound();
		_ready=true;
	}else{
	}
	if(_observeAsked)
		if(table())
		{
			FTTourneys *tourneys = qobject_cast<FTTourneys*>(parent());
			Q_ASSERT(tourneys!=0);

			_observeAsked = false;
			qLog(Debug)<<"table for tourney "<<tourneyId()<<" is opened. observe done";
			//sendTourneyInfo();
		}else{
			doObserve();
		}
}

bool FTTourneyLobby::ready()
{
	return _ready;
}

PBTourneyStatus FTTourneyLobby::status()
{
	return _status;
}