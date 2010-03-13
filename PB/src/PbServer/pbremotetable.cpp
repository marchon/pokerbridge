#include "stdafx.h"
#include "pbremotetable.h"
#include "pbtables.h"

PBRemoteTables::PBRemoteTables(QObject *parent)
{

}

PBTables *PBRemoteTables::tables()
{
	return qobject_cast<PBTables*>(parent());
}


void PBRemoteTables::onTableOpened(QString tableId)
{
	tables()->newTable(tableId);
}