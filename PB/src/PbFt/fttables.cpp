#include "stdafx.h"
#include "fttables.h"
#include "fthooks.h"
#include "pbseats.h"
#include "ftlobby.h"
#include "fttable.h"
#include "fthandhistory.h"
#include "pbhandinfo.h"
#include "ftpanel.h"
#include "fttables.h"
#include "fttourneys.h"

FTTables::FTTables(QWidget *w, QObject *parent) :FTWidgetHook(w, parent)
{
	connect(FTHandHistory::instance(), SIGNAL(handHistoryEvent(const QString &,PBHandInfo*)),
		this, SLOT(onHandHistory(const QString &,PBHandInfo*)), Qt::DirectConnection);
	
	connect(lobby(), SIGNAL(tooManyWindows()), this, SLOT(onTooManyWindows()));

	_windowsLimit = 10000;

	new RMessageAdaptor(this);
}


void FTTables::onTooManyWindows()
{
	_windowsLimit = tableCount();
}

int FTTables::tableCountLimit()
{
	return _windowsLimit;
}

void FTTables::onRowsInserted(QAbstractItemView *view, int start, int end)
{
	QString title;
		
	if(0!=qstrcmp(view->metaObject()->className(),"CChatView"))
		return;

	QWidget *parentWTitle = QTUtil::getParentTitle(view, title);	
		
	FTTableId tableId;
	if(0==parentWTitle)
		qLog(DebugHand)<<"no parent with title";
	else if(!parseTableId(title, tableId))
	{
		if(title!="Last Hand History")
			qLog(DebugHand)<<"failed to parse tableId from "<<title;
	}
	else {
		QAbstractItemModel *model = view->model();
		QVariant d = model->data(model->index(model->rowCount()-1,0));
		newChatLine(tableId, d.toString());
	}
}

void FTTables::newChatLine(FTTableId tableId, const QString &line)
{
	//qLog(Debug)<<"[" <<line << "] at table=[" << tableId << "]";

	//FTTable* table = lobby()->table(tableId);
	
	QString dealerStr = "Dealer: ";

	if(!line.startsWith(dealerStr))
		return;

	QString input = line.mid(dealerStr.length());

	QRegExp re("Hand \\#(\\d+)");
	if(re.indexIn(input)!=-1)
	{
		QString chatNextHand = re.cap(1);

		nextHandTable = tableId;
		
		if(chatNextHand!=nextHand)
			qLog(DebugHand)<<"cachedNextHand=["<<nextHand<<"] isn't equal to chat's nextHand=["<<chatNextHand<<"]";

		assignHandToTable(chatNextHand, tableId);
	
		return;
	}
	
	FTTable *atable = getTable(tableId);
	if(atable)
		atable->onNewChatLine(input);
}

void FTTables::onStringIndexOf(const QString &s)
{
	QRegExp handRe("Dealer: Hand #(\\d+)");
	QRegExp seatRe("Dealer: Seat (\\d+): (.+) \\(([\\d\\.]+)\\)"); // Dealer: Seat 1: kenmacg (947)
	QRegExp buRe("Dealer: The button is in seat #(\\d+)");

	if(s.indexOf(QString::fromAscii("folds"))>-1)
	{
		qLog(Debug)<<"INDEXOF "<<s;
	}

	QString filt = s;
	filt.remove(QRegExp("[$,]"));

	if(nextHandTable.isEmpty())
		return;

	FTTable *atable = getTable(nextHandTable); // AT1

	if(handRe.indexIn(filt)!=-1)
	{
		nextHand = handRe.cap(1); // cache nextHand Id
		nextHandTable="";	// will be filled in Chat.NewLine
		qLog(DebugHand)<<"hand "<<nextHand<<" cached";
	}else if(atable==0)
	{
		if(!nextHand.isEmpty())
			qLog(DebugHand)<<"...............--->ignored, table ["<<nextHandTable<<"] not found for nextHand=["<<nextHand<<"]";
	}else if(seatRe.indexIn(filt)!=-1)
	{
		// we assume that nextHandTable will be filled upon this time (in OnNewChatLine)
		QString seatStr = seatRe.cap(1);
		QString playerStr = seatRe.cap(2);
		QString stakeStr = seatRe.cap(3);

		qLog(DebugHand)<<nextHand+": Seat ["<<seatStr<<"] ["<<playerStr<<"] ["<<stakeStr<<"] assigned to table "<<nextHandTable;
		bool isSitOut = filt.indexOf("sitting out")>=0;
		atable->setPlayerAtSeat(seatStr.toInt() - 1, playerStr, stakeStr.toDouble(), isSitOut);
		
	}else if(buRe.indexIn(filt)!=-1)
	{
//		 doesn't work since button is determined only after blinds were posted...
		
		int butSeat = buRe.cap(1).toInt()-1;
		qLog(DebugHand)<<nextHand+": Button at seat #"<<(butSeat+1)<<" at table "<<nextHandTable;

		atable->buttonSeat(butSeat);
		
	}
}

void FTTables::assignHandToTable(QString chatNextHand, QString tableId)
{
	// assign table to hand
	FTTable *atable = getTable(tableId);
	if(!atable)
	{
		qLog(Debug)<<"assignHandToTable "<<tableId<<" no table";
		return;
	}
	atable->setHandId(chatNextHand);
	handsOnTables[chatNextHand] = tableId; // update hand->table mapping

	qLog(DebugHand) << "hand ["<<chatNextHand<<"] binded to table ["<<tableId<<"]";
}

FTLobby *FTTables::lobby()
{
	return qobject_cast<FTLobby*>(parent());
}

void FTTables::onHandHistory(const QString &histStr, PBHandInfo *hi)
{
	if(0==hi)
		qLog(DebugHand)<<"FTTables::onHandHistory: no handInfo, error!";
	else
	{
		QString handId = hi->handId();
		QString tableId = hi->tableId();

		qLog(DebugHand)<<"onHandHistory(Hand=["<<handId<<"], Table=["<<tableId<<"]";

		QHash<QString,QString>::iterator i = handsOnTables.find(handId);
		if(i!=handsOnTables.end())
		{
			QString cachedTableId = i.value();
			handsOnTables.erase(i);

			qLog(DebugHand)<<"removed Hand ["<<handId<<"]->"<<cachedTableId<<" from handTableMap";

			FTTable *t = getTable(cachedTableId);
			if(t==0)
			{
				qLog(Error)<<"failed to finish hand "<<handId<<", cached table ["<<cachedTableId<<"]"<<" not found in tableMap";
			}else
			{
				t->onHandHistory(histStr, hi);		
				t->onHandEnd(handId);
			}
		}else{
			qLog(DebugHand)<<"history ignored (dup?) for hand "<<handId<<" table "<<tableId;
		}
	}
	// notify all
	emit handHistoryEvent(histStr);
}

void FTTables::tourneyIsOver(FTTable *tbl)
{
	tbl->immediateClose();
}

bool FTTables::parseTableId(const QString &windowTitle, QString &tableId)
{
	if(windowTitle.indexOf("Hold'em")<0)
		return false;

	tableId = windowTitle;
	tableId = tableId.remove("Chat: ");

	QStringList parts = tableId.split(" - ");

	QRegExp loginRe("Logged In As (.+)");
	QString login = "";
	if(loginRe.indexIn(parts.last())!=-1)
	{
		login = loginRe.cap(1);
		parts.removeLast();
	}
	
	tableId =  parts[0]; //parts.join(" - ").trimmed();
	return true;
}



FTTable *FTTables::getTable(const FTTableId &tableId)
{
	FTWidgetHook *h = hookFor(tableId);
	FTTable *table = qobject_cast<FTTable*>(h);
	
	Q_ASSERT(!(h && !table));
	return table;
}

FTTable *FTTables::table(const FTTableId &tableId)
{
	FTTable *table = getTable(tableId);
	
	if(0==table)
	{
		table = new FTTable(0, this);
		table->setTableId(tableId);
		qLog(Info)<<"Table created ["+tableId+"], "+QString().sprintf(" %d total",tableCount());

		if(FTPanel::instance())
		{
			FTPanel::instance()->connectTables(this);
			FTPanel::instance()->updateTableCombo();
		}

	}

	return table;
}

int FTTables::tableCount()
{
	int count = 0;
	Q_FOREACH(QObject *tbl, children())
	{
		if(qobject_cast<FTTable*>(tbl)!=0)
			count++;
	}
	return count;
}

QList<FTTable*> FTTables::tables()
{
	QList<FTTable*> list;
	Q_FOREACH(QObject *obj, children())
	{
		FTTable *tbl = qobject_cast<FTTable*>(obj);
		if(tbl!=0)
			list.append(tbl);
	}
	return list;
}

QWidget *FTTables::parentTableWidget(QWidget *w)
{
	QWidget *ptw = QTUtil::parentWithClass(w, "CTableViewGamePlay");
	if(0==ptw)
		ptw= QTUtil::parentWithClass(w, "CTableViewSpeed");
	
	return ptw;
}

FTTable *FTTables::tableFromChild(QWidget *widget)
{
	QString title;
	QString tableId;

	QWidget *tableWidget = parentTableWidget(widget);
	if(tableWidget)
	{
		title = tableWidget->windowTitle();
		if(!parseTableId(title, tableId))
			;//pbErr("failed to parse tableId for widget "+QTUtil::widgetInfo(widget)+" --"+title)
		else{
			FTTable *tbl = table(tableId);
			if(0==tbl->widget())
			{
				tbl->setWidget(tableWidget);
				tbl->onWidget(tableWidget);
				// here caption should be parsed
				emit tableOpenedEvent(tableId);
				qLog(DebugHand) << "table ["<<tableId<<"] assigned widget "<<tableWidget;

				sendTableInfo(tbl);
			}
		}
	}
	return 0;
}

FTTable *FTTables::tourneyTable(QString tourneyId)
{
	Q_FOREACH(QObject *obj, children())
	{
		FTTable *tbl = qobject_cast<FTTable*>(obj);
		if(0!=tbl)
		{
			if(tbl->isTourney() && tbl->tourneyId()==tourneyId)
				return tbl;
		}
	}
	return 0;
}

QList<FTTable*> FTTables::tourneyTables()
{
	QList<FTTable*> result;
	Q_FOREACH(QObject *obj, children())
	{
		FTTable *tbl = qobject_cast<FTTable*>(obj);
		if(0!=tbl)
		{
			if(tbl->isTourney())
				result.append(tbl);
		}
	}
	return result;
}

void FTTables::onPaint(QWidget *widget)
{
	// find drawing widget of table. Is unnamed
	QWidget *tableWidget = parentTableWidget(widget); 
	if(tableWidget!=0 &&widget->height()>0.95*tableWidget->height())
	{
		FTTable *table = tableFromChild(widget);
		if(0!=table)
		{
			table->onPaint(widget);
		}

	}
}

void FTTables::onWidget(QWidget *widget)
{
	// this will create table if needed
	FTTable *table = tableFromChild(widget);
	if(0!=table)
		table->onWidget(widget);
}

void FTTables::sendTableInfo(FTTable *tbl)
{
	if(tbl->isTourney())
		lobby()->tourneys()->sendTourneyInfo(tbl->tourneyId());
}