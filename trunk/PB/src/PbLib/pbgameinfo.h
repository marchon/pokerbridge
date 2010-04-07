#pragma once

#include "PBRequest.h"
#include "pbdriver.h"

class RMessage;

// single table game
class PB_EXPORT PBGameInfo : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(QString gameId READ gameId WRITE setGameId)	// FT-bamboo, FT-123-1
	Q_PROPERTY(QString tableId READ tableId WRITE setTableId) // "bamboo" for table 'bamboo' or '123' for tourney 123
	Q_PROPERTY(QString tourneyTableId READ tourneyTableId WRITE setTourneyTableId) // 1 for MTT's 1st table
	Q_PROPERTY(QString siteId READ siteId WRITE setSiteId)	// FT, PS,...
	Q_PROPERTY(int canJoin READ canJoin WRITE setCanJoin) // Registering
	Q_PROPERTY(QString gameFamily READ  gameFamily WRITE setGameFamily)	// SNG, MTT, Cash
	Q_PROPERTY(double smallBlind READ smallBlind WRITE setSmallBlind)
	Q_PROPERTY(double bigBlind READ bigBlind WRITE setBigBlind)
	Q_PROPERTY(int maxSeats READ maxSeats WRITE setMaxSeats)
	Q_PROPERTY(QString driver READ driver() WRITE setDriver())
	Q_PROPERTY(int canOpen READ canOpen WRITE setCanOpen) 
	Q_PROPERTY(int openedTablesCount READ openedTablesCount WRITE setOpenedTablesCount) 
	Q_PROPERTY(int tablesMax READ tablesMax WRITE setTablesMax) 
	Q_PROPERTY(int tableOpened READ tableOpened WRITE setTableOpened)
	Q_PROPERTY(int tourneyOpened READ tourneyOpened WRITE setTourneyOpened)
	Q_PROPERTY(int gameComplete READ gameComplete WRITE setGameComplete)


	/*  observing			-- the game is observed by hero
		sittingout			-- the game is joined, currently sitting out
		waitinglist			-- the game is on waiting list
		playing				-- the game is playing
		askedaction			-- the game is playing, we need to tell action
	*/
public:

	PBGameInfo(QObject *parent=0);

	QString gameId();
	void setGameId(const QString &id);

	QString tableId();
	void setTableId(const QString &id);

	QString tourneyTableId();
	void setTourneyTableId(const QString &id);

	QString siteId();
	void setSiteId(const QString &id);

	int canJoin();
	void setCanJoin(int tr);

	int canOpen();
	void setCanOpen(int tr);

	int tableOpened();
	void setTableOpened(int to);

	int tourneyOpened();
	void setTourneyOpened(int to);

	int gameComplete();
	void setGameComplete(int gc);

	QString gameFamily();
	void setGameFamily(const QString &id);

	double smallBlind();
	void setSmallBlind(double v);

	double bigBlind();
	void setBigBlind(double v);

	int maxSeats();
	void setMaxSeats(int v);

	QString driver();
	void setDriver(QString driver);

	int openedTablesCount(){ return _tablesObserved; }
	void setOpenedTablesCount(int tablesObserved){_tablesObserved=tablesObserved;}

	int tablesMax(){ return _tablesMax; }
	void setTablesMax(int tablesMax){ _tablesMax = tablesMax; }


protected:
	int _maxSeats;
	double _smallBlind;
	double _bigBlind;
	QString _gameFamily;
	QString _siteId;
	QString _tourneyId;
	QString _tourneyTableId;
	QString _tableId;
	QString _gameId;
	QString _driver;
	int _tablesObserved;
	int _tablesMax;
	int _tableOpened;
	int _tourneyOpened;
	int _gameComplete;
	int _needTableOpened;
	int _needTourneyOpened;
	int _needTableJoined;
	int _canOpen;
	int _canJoin;

};


class PBLobbyDriver;
class PBSiteGameInfo : public PBGameInfo
{
	Q_OBJECT;
public:
	PBSiteGameInfo(QObject *parent);
	
	void updateInfo(PBGameInfo *src);
	void updateState(PBGameInfo *src);

	QTime lastUpdateTime();
	void setLastUpdateTime(QTime t);
	
	PBLobbyDriver *owner();
	void setOwner(PBLobbyDriver *drv);
	QString ownerId();

	int needTableOpened();
	void setNeedTableOpened(int to);

	int needTourneyOpened();
	void setNeedTourneyOpened(int to);

	int needTableJoined();
	void setNeedTableJoined(int tj);

protected:
	QTime _lastUpdateTime;
	QPointer<PBLobbyDriver> _owner;
};
