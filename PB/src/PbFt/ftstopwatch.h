#pragma once

class FTStopWatch : public QObject
{
	Q_OBJECT;
public:
	FTStopWatch(QObject *parent = 0);

public slots:
	void onTimer();
protected:
	QString stopWatchPath;
};