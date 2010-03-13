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
signals:
	void listUpdatedEvent(FTList *list);
	
private:
	QHash<QString, FTList*> _lists;
};

class FTListClicker
{
public:
	virtual void click(FTList *list)=0;
};

class FTDefaultListClicker: public FTListClicker
{
public:
	FTDefaultListClicker(){_index=-1;}
	void add(QString column, QString value);
	bool filter(FTList *list, int row);
	void click(FTList *list);
	void load();
	void setIndex(int index){_index=index;}
	int index(){return _index;}
protected:
	QHash<QString,QList<QString>> _filters;
	int _index;
};



class FTList:public FTWidgetHook
{
	Q_OBJECT
public:
	FTList(QWidget *widget, QObject *parent=0);
	

	void onRowsInserted(QAbstractItemView *view, int start, int end);


	void click(FTListClicker *clicker, int maxItems = 10);

	int rowCount();
	QString value(int row, int col);
	int indexOfColumn(QString column);
	void trace(QAbstractItemModel *model, int start, int end);

	QAbstractItemView *view();
	QAbstractItemModel *model();

signals:
	void listUpdatedEvent();
	void clickSig(FTListClicker *filter);
protected slots:
	int doClick(FTListClicker *filter);
public:
	void dblClick(int row, int col);
	int _maxItems;
};
#endif FTLIST_H