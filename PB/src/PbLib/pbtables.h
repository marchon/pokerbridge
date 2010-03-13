#pragma once


class PB_EXPORT PBTables : public QObject
{
	Q_OBJECT
public:
	PBTable *table(const QString &tableId);
	int tableCount();
	PBTable *newTable(const QString &tableId);	
};