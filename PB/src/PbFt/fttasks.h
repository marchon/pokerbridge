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
public:
	FTTasks(QObject *parent=0);
	void stop();
	FTTask *tableOpener();
};