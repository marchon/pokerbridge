#pragma once
class RMessageQueue;


class PBLauncher;
class PBLobbyDriver;
class PBLobbyDriverProfile;

class PBServer : public QObject
{
	Q_OBJECT
public:
	PBServer(QObject *parent=0);
	QSettings *settings();
	
	void checkDeads();
	int assignIndex(PBLobbyDriver *drv);

	PBLobbyDriverProfile *profile();
	int driversCount();
	static PBServer *instance();
public slots:
	void queueOpened(RMessageQueue *queue);
signals:
	void driverTimeout(PBLobbyDriver *drv);
protected:
	static PBServer *_instance;
	int _agentsCount;
	QSettings *_settings;
	PBLauncher *_launcher;
	friend class PBLobbyDriver;
};


