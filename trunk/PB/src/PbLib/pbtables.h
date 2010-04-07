#pragma once


class PB_EXPORT PBTables : public QObject
{
	Q_OBJECT
public:
	PBTables(QObject *parent = 0);

	PBTable *table(const QString &tableId);
	int tableCount();
	PBTable *newTable(const QString &tableId);	
signals:
	void newTableEvent(PBTable *tbl);
};

