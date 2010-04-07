#pragma once
#include "ftwidgethook.h"
#include "pbtourney.h"

class FTTourneys;



class FTTourneyLobby : public FTWidgetHook
{
	Q_OBJECT
public:
	FTTourneyLobby(QWidget *widget, QObject *parent=0);
	~FTTourneyLobby();

	QString tourneyId();
	void setTourneyId(const QString &tourneyId);
	PBTourneyStatus status();

	virtual void onWidget(QWidget *w);
	virtual void onWidgetSetVisible(QWidget *w, bool isVisible);
	
	virtual void emitWidgetFound();
	
	
	void observe();

	virtual void timerEvent(QTimerEvent *ev);

	FTTourneys *tourneys();
	FTTable *table();

	bool ready();

	void onPaint(QWidget *w);
	void onDrawTextItem(QWidget *w, const QPointF &p, const QTextItem &ti);

	bool canObserve();
	QTime openedTime(){ return _openedTime; } 

signals:
	void observeSig();
	void observeClicked();

public slots:	// Commands

public slots:
	void doObserve();
	void tourneyLobbyClosing(FTWidgetHook*);
protected:
	QPointer<FTButton> _observeBtn;
	PBTourneyStatus _status;
	bool _ready;
	QTime _openedTime;
	bool _observeAsked;
	int _timeAlive;
	int _timerId;
	bool hasPainted;
};