#ifndef FTLIST_H
#define FTLIST_H

#include "ftwidgethook.h"

class FTList;
class FTLists:public FTWidgetHook
{
	Q_OBJECT
public:
	FTLists(QWidget *widget, QObject *parent=0);
	
	virtual void onRowsInserted(QAbstractItemView *view, int start, int end);
	virtual void onWidgetSetVisible(QWidget *w, bool isVisible);

	FTList *list(QString id);
public:
	void listUpdated(FTList *list);
	void paintDone(FTList *list){ emit paintDoneEvent(list); }
signals:
	void listUpdatedEvent(FTList *list);
	void paintDoneEvent(FTList *list);
private:
	QHash<QString, FTList*> _lists;
};



class FTList:public FTWidgetHook
{
	Q_OBJECT
public:
	FTList(QWidget *widget, QObject *parent=0);
	

	void onRowsInserted(QAbstractItemView *view, int start, int end);

	void onDrawTextItem(QWidget *widget, const QPointF &p, const QTextItem &ti);
	void onPaint(QWidget *w);

	int rowCount();
	QString value(int row, int col);
	int indexOfColumn(QString column);
	int indexOfRow(QString value);
	static void dump(QAbstractItemModel *model, int start, int end);

	void dblClick(int row, int col);
	void click(int row, int col, float subX=0.3, float subY=0.3);

	void setPainterMode(bool painterMode);

	QAbstractItemView *view();
	QAbstractItemModel *model();

	int paintedCount(){ return _items.count();}
signals:
	void listUpdatedEvent();
protected:
	bool _painterMode;
	bool _paintDone;
	QMap<int, QString> _items;
};
#endif FTLIST_H