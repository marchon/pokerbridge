#include "stdafx.h"
#include "fttourneylobby.h"
#include "ftbutton.h"
#include "fttourneys.h"
#include "fthooks.h"

FTTourneyLobby::FTTourneyLobby(QWidget *widget, QObject *parent) : FTWidgetHook(widget, parent)
{
	_observeBtn = 0;
	hasPainted = false;
	connect(this, SIGNAL(observeSig()), this, SLOT(doObserve()));
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

void FTTourneyLobby::observe()
{
	qLog(Info)<<"tourlobby::observe";
	emit observeSig();
}

class QAccessButton : public QAbstractButton
{
public:
	void emitClicked(){emit clicked();}
	void emitReleased(){emit clicked();}
};

void FTTourneyLobby::doObserve()
{
	if(0==_observeBtn)
	{
		qLog(Info)<<" FTTourneyLobby::observe: no observe button";
		return;
	}
	//widget()->activateWindow();
	_observeBtn->press();
	//((QAccessButton*)_observeBtn->button())->emitClicked();
	
	qLog(Info)<<"tourney "<<tourneyId()<<" observe click";
	FTTourneys *tourneys = qobject_cast<FTTourneys*>(parent());
	Q_ASSERT(tourneys!=0);
	tourneys->observeClicked(this);
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
	qLog(Info)<<"Tourney Lobby created ["+tourneyId()+"]";
	tourneys()->tourneyLobbyOpened(this);
}

void FTTourneyLobby::onPaint(QWidget *w)
{
	FTWidgetHook::onPaint(w);

	// all this to emit ToruneyLobbyOpened after observeBtn was found
	if(!hasPainted && 0!=_observeBtn && _observeBtn->widget()==w && !_observeBtn->text().isEmpty())
	{
		hasPainted=true;
		emitWidgetFound();
	}
}