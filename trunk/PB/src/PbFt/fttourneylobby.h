#pragma once
#include "ftwidgethook.h"

class FTTourneys;

class FTTourneyLobby : public FTWidgetHook
{
	Q_OBJECT
public:
	FTTourneyLobby(QWidget *widget, QObject *parent=0);

	QString tourneyId();
	void setTourneyId(const QString &tourneyId);
	
	virtual void onWidget(QWidget *w);
	virtual void onWidgetSetVisible(QWidget *w, bool isVisible);
	
	virtual void emitWidgetFound();
	void observe();

	FTTourneys *tourneys();
	
	void onPaint(QWidget *w);

signals:
	void observeSig();
	void observeClicked();
public slots:
	void doObserve();

protected:
	FTButton *_observeBtn;
	bool hasPainted;
};