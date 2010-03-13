#ifndef FTTABLES_H
#define FTTABLES_H

#include "ftwidgethook.h"

class FTTables : public FTWidgetHook
{
	Q_OBJECT
public:
	FTTables(QWidget *w, QObject *parent=0);

public:
	// returns table or lazy creates one
	FTTable *table(const FTTableId &tableId);
	FTTable *getTable(const FTTableId &tableId);
	int tableCount();
	QList<FTTable*> tables();
	FTTable *tourneyTable(QString tourneyId);
public slots:
	void onRowsInserted(QAbstractItemView *view, int start, int end);
	//void onWidgetSetVisible(QWidget *widget, bool isVisible);
	//void onDrawTextItem(QWidget *widget, const QPointF &p, const QTextItem &ti);
	void onStringIndexOf(const QString &s);
	void onHandHistory(const QString &histStr, PBHandInfo *hi);
	void onPaint(QWidget *widget);
	void onWidget(QWidget *widget);
signals:
	void handHistoryEvent(const QString &history);
	void tableOpenedEvent(QString tableId);
protected:
	FTLobby *lobby();
	bool parseTableId(const QString &windowTitle, QString &tableId);
	void newChatLine(FTTableId tableId, const QString &line);
	void assignHandToTable(QString chatNextHand, QString tableId);

protected:
	FTTable *tableFromChild(QWidget *widget);
	QWidget *parentTableWidget(QWidget *w);

protected:
	QString nextHand;
	QString nextHandTable;

	QHash<QString, QString> handsOnTables;

	// tableId(string) -> table
	//QHash<QString, FTTable*> _tables;
};

#endif