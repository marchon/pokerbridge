#include "stdafx.h"
#include "fthandhistory.h"
#include "fthooks.h"
#include "pbhandinfo.h"

Q_GLOBAL_STATIC(FTHandHistory, qFTHandHistory);

FTHandHistory* FTHandHistory::instance(){ return qFTHandHistory(); }


FTHandHistory::FTHandHistory(QObject *parent) : QObject(parent)
{
}

void FTHandHistory::onStringAppend(const QString &self, const QString &s)
{
	//qLog(Debug)<<"FTHandHistory::onStringAppend";
	if(self.indexOf(QString::fromAscii("SUMMARY"))!=-1)
	{
		QString filtered = self;
		filtered.remove(QChar::fromAscii(0x1d));
		PBHandInfo hi;
		hi.setGameFamily("unknown");
		bool ok = parseHandInfo(filtered, &hi);
		emit handHistoryEvent(filtered, &hi);
	}
}

bool FTHandHistory::parseHandInfo(const QString &history, PBHandInfo *result)
{
	//Full Tilt Poker Game #17342876342: Table Recline (6 max) - $0.50/$1 - No Limit Hold'em - 21:09:25 ET - 2010/01/04 (partial) 
	QRegExp re("Full Tilt Poker Game \\#(\\d+)\\: Table ([^-]+)-([^-]+)-([^-]+)-([^-]+)-([^-]+)[ ]+(.*)",Qt::CaseInsensitive, QRegExp::RegExp);
	if(re.indexIn(history)!=-1)
	{
		result->setHandId(re.cap(1));
		result->setTableId(re.cap(2));
		
		QString sblinds = re.cap(3);
		
		sblinds = sblinds.remove("$");
		QStringList blinds = sblinds.split("/");
		
		double bb = 0, sb = 0;
		if(blinds.size()>0)
			sb = blinds[0].toDouble();
		if(blinds.size()>1)
			bb = blinds[1].toDouble();

		result->setBigBlind(bb);
		result->setSmallBlind(sb);
		result->setGameFamily(re.cap(4));
		return true;
	}
	return false;
}