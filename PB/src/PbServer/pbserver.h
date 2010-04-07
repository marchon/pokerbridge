#pragma once
class RMessageQueue;


class PBLauncher;
class PBLobbyDriver;
class PBServer : public QObject
{
	Q_OBJECT
public:
	PBServer(QObject *parent=0);
	QSettings *settings();
	
	void checkDeads();
	int assignIndex(PBLobbyDriver *drv);

public slots:
	void queueOpened(RMessageQueue *queue);

protected:
	int _agentsCount;
	QSettings *_settings;
	PBLauncher *_launcher;
};


