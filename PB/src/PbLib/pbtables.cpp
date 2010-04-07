#include "stdafx.h"
#include "pbtables.h"
#include "pbtable.h"

PBTables::PBTables(QObject *parent) : QObject(parent)
{
}

PBTable *PBTables::table(const QString &tableId)
{
	return qFindChild<PBTable*>(this, tableId);
}

int PBTables::tableCount()
{
	return qFindChildren<PBTable*>(this).size();
}

PBTable *PBTables::newTable(const QString &tableId)
{
	PBTable *tbl = new PBTable(this);
	tbl->setTableId(tableId);
	qLog(Debug)<<"created table "<<tableId;
	emit newTableEvent(tbl);
	return tbl;
}


QString PBTable::tableId()
{
	return objectName();
}

void PBTable::setTableId(QString tableId)
{
	setObjectName(tableId);
}

