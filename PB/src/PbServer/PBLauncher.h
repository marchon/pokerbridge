#pragma once
class PBLauncher : public QObject
{
	Q_OBJECT
public:
	PBLauncher(QObject *parent = 0);

	void start();

	void setPath(QString path);

	virtual void timerEvent(QTimerEvent *e);

	void kill(long pid);
	
	void setMaxCount(int mc);
protected:
	int _timerId;
	int _maxCount;
	QString _processName;
	QString _dirName;
	QString _dllPath;
};