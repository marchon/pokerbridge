#pragma once


class FTTask : public QObject
{
	Q_OBJECT

public:
	FTTask(QObject *parent = 0) : QObject(parent){ }
	virtual void start(){ }
	virtual void stop(){}
	virtual bool isRunning(){ return false; }
};

class FTTasks : public QObject
{
	Q_OBJECT
public:
	FTTasks(QObject *parent=0);

	FTTask *tableOpener();
public slots:
	void stop();
};