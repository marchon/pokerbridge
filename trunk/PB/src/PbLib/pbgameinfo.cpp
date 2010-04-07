#include "stdafx.h"
#include "pbgameinfo.h"
#include "rmsg.h"
#include "json.h"
PBGameInfo::PBGameInfo(QObject *parent) : QObject(parent)
{
	_tablesObserved = -1;
	_tablesMax = -1;

	_needTableOpened = _needTourneyOpened = _needTableJoined = -1;
	_gameComplete = -1;
	_tableOpened = _tourneyOpened = -1;
}

QString PBGameInfo::gameId()
{
	return siteId()+"-"+tableId()+"-"+tourneyTableId();
}

void PBGameInfo::setGameId(const QString &id)
{
	
}

QString PBGameInfo::tableId()
{
	return _tableId;
}

void PBGameInfo::setTableId(const QString &id)
{
	_tableId = id;
	setObjectName(gameId());
}

QString PBGameInfo::tourneyTableId()
{
	return _tourneyTableId;
}

void PBGameInfo::setTourneyTableId(const QString &id)
{
	_tourneyTableId = id;
	setObjectName(gameId());
}

int PBGameInfo::canOpen()
{
	return _canOpen;
}

void PBGameInfo::setCanOpen(int co)
{
	_canOpen = co;
}

QString PBGameInfo::siteId()
{
	return _siteId;
}

void PBGameInfo::setSiteId(const QString &id)
{
	_siteId = id;
	setObjectName(gameId());
}

int PBGameInfo::canJoin()
{
	return _canJoin;
}

void PBGameInfo::setCanJoin(int value)
{
	_canJoin = value;
}

QString PBGameInfo::gameFamily()
{
	return _gameFamily;
}

void PBGameInfo::setGameFamily(const QString &id)
{
	_gameFamily =id;
}

double PBGameInfo::smallBlind()
{
	return _smallBlind;
}

void PBGameInfo::setSmallBlind(double v)
{
	_smallBlind = v;
}

double PBGameInfo::bigBlind()
{
	return _bigBlind;
}

void PBGameInfo::setBigBlind(double v)
{
	_bigBlind = v;
}

int PBGameInfo::maxSeats()
{
	return _maxSeats;
}
void PBGameInfo::setMaxSeats(int v)
{
	_maxSeats = v;
}

QString PBGameInfo::driver()
{
	return _driver;
}

void PBGameInfo::setDriver(QString driver)
{
	_driver = driver;
}
int PBGameInfo::gameComplete()
{
	return _gameComplete;
}

void PBGameInfo::setGameComplete(int gc)
{
	_gameComplete = gc;
}

int PBGameInfo::tableOpened()
{
	return _tableOpened;
}
void PBGameInfo::setTableOpened(int to)
{
	_tableOpened = to;
}

int PBGameInfo::tourneyOpened()
{
	return _tourneyOpened;
}

void PBGameInfo::setTourneyOpened(int to)
{
	_tourneyOpened = to;
}



////////////

PBSiteGameInfo::PBSiteGameInfo(QObject *parent): PBGameInfo(parent)
{
	_lastUpdateTime = QTime::currentTime(); 
}

QString PBSiteGameInfo::ownerId()
{
	return _owner ? _owner->objectName(): "?"; 
}


QTime PBSiteGameInfo::lastUpdateTime()
{
	return _lastUpdateTime;
}

void PBSiteGameInfo::setLastUpdateTime(QTime t)
{
	_lastUpdateTime = t;
}
	
PBLobbyDriver *PBSiteGameInfo::owner()
{
	return _owner;
}

void PBSiteGameInfo::setOwner(PBLobbyDriver *drv)
{
	_owner=drv;
}

void PBSiteGameInfo::updateInfo(PBGameInfo *src)
{
	setBigBlind(src->bigBlind());
	setSmallBlind(src->smallBlind());
	setGameComplete(src->gameComplete());
}

void PBSiteGameInfo::updateState(PBGameInfo *src)
{
	setTableOpened(src->tableOpened());
	setTourneyOpened(src->tourneyOpened());
	setCanJoin(src->canJoin());
	setCanOpen(src->canOpen());
	setTablesMax(src->tablesMax());
	setOpenedTablesCount(src->openedTablesCount());

}

int PBSiteGameInfo::needTableOpened()
{
	return _needTableOpened;
}

void PBSiteGameInfo::setNeedTableOpened(int to)
{
	_needTableOpened = to;
}

int PBSiteGameInfo::needTourneyOpened()
{
	return _needTourneyOpened;
}

void PBSiteGameInfo::setNeedTourneyOpened(int to)
{
	_needTourneyOpened = to;
}

int PBSiteGameInfo::needTableJoined()
{
	return _needTableJoined;
}

void PBSiteGameInfo::setNeedTableJoined(int tj)
{
	_needTableJoined = tj;
}

