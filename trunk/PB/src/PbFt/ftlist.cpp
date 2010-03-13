#include "stdafx.h"
#include "ftlist.h"
#include "fthooks.h"
#include "ftpanel.h"
#include "fttourneylist.h"

FTLists::FTLists(QWidget *widget, QObject *parent) : FTWidgetHook(widget, parent)
{

}

FTList *FTLists::list(QString id)
{
	FTList *list = qobject_cast<FTList*>(hookFor(id));
	return list;
}

void FTLists::listUpdated(FTList *list)
{
	emit listUpdatedEvent(list);
}

void FTLists::onRowsInserted(QAbstractItemView *view, int start, int end)
{
	FTList *alist = qobject_cast<FTList*>(hookFor(view));
	if(0==alist)
	{
		//qLog(Debug)<<"LIST-WIDGET "<<QTUtil::widgetInfo(view);

		QAbstractItemModel *model = view->model();
		QString modelClass = model->metaObject()->className();

		if(start==0)
		{
			if(ftSngLobbyModel==modelClass)
			{
				alist = new FTTourneyList(view, this);
				alist->setObjectName(modelClass);
			}
		}
	}


	if(alist)
		alist->onRowsInserted(view, start, end);

	//qLog(Debug)<<"rowsInserted("<<start<<","<<end<<")"<<QTUtil::widgetInfo(view)<<", model "<<model->metaObject()->className()<<":"<<model->objectName();
}

void FTLists::onWidgetSetVisible(QWidget *w, bool isVisible)
{
	FTWidgetHook::onWidgetSetVisible(w, isVisible);
	
	QAbstractItemView *view = qobject_cast<QAbstractItemView*>(w);
	if(0!=view)
	{
		if(view->model()->metaObject()->className()==ftSngLobbyModel)
		{
			qLog(Debug)<<"List "<<ftSngLobbyModel<<" shows";
		}
	}
}

//CBrowseSitAndGoLobbyProxyModel

FTList::FTList(QWidget *widget, QObject *parent) : FTWidgetHook(widget, parent)
{ 
	_maxItems = 10;	
	connect(this, SIGNAL(clickSig(FTListClicker*)), this, SLOT(doClick(FTListClicker*))/*, Qt::QueuedConnection*/);
}



void FTList::onRowsInserted(QAbstractItemView *view, int start, int end)
{
	QAbstractItemModel *model = view->model();
//	qLog(Debug)<<QTUtil::objectInfo(model);
	
	/*
	QAbstractProxyModel *proxyModel = qobject_cast<QAbstractProxyModel*>(model);
	while(0!=proxyModel)
	{
		model = proxyModel->sourceModel();
		qLog(Debug)<<" is proxy for "<<QTUtil::objectInfo(model);
		proxyModel = qobject_cast<QAbstractProxyModel*>(model);
	}
	*/

//	trace(model, start, end);

	emit listUpdatedEvent();
	FTLists *lists = qobject_cast<FTLists*>(parent());
	if(0!=lists)
		lists->listUpdated(this);
}


void FTList::trace(QAbstractItemModel *model, int start, int end)
{
	QString s = "Header:";
	for(int j=0;j<model->columnCount();j++)
	{
		QString hdrItem = model->headerData(j,Qt::Orientation::Horizontal, Qt::DisplayRole).toString();
		s+=" "+hdrItem;
	}

	qLog(Debug)<<s;
	//for(int role = Qt::DisplayRole;role<=50;role++)
	{
		//qLog(Debug)<<"role"<<role;
		for(int i=start;i<=end;i++)
		{
			s="";
			for(int j=0;j<model->columnCount();j++)
			{
				QVariant v ;
				v= model->data(model->index(i,j), Qt::DisplayRole);
				s+=v.toString();
				s+=" ";
		
			}
			qLog(Debug)<<s;
		}
	}
}

int FTList::rowCount()
{
	QAbstractItemModel *amodel = model();
	if(!amodel)
	{
		qLog(Debug)<<"ERROR: FTList::rowCount model=0";
		return 0;
	}
	return model()->rowCount();
}

QString FTList::value(int row, int col)
{
	return model()->data(model()->index(row, col)).toString();
}

int FTList::indexOfColumn(QString column)
{
	QAbstractItemModel *amodel = model();
	for(int j=0;j<amodel->columnCount();j++)
	{
		QString header = amodel->headerData(j,Qt::Orientation::Horizontal, Qt::DisplayRole).toString();
		if(header==column)
			return j;
	}
	return -1;
}


class QAccessItemView : public QAbstractItemView
{
public:
	void doubleClicked(const QModelIndex &index)
	{
		emit QAbstractItemView::doubleClicked(index);
	}
};

void FTList::click(FTListClicker *filter, int maxItems)
{
	_maxItems = maxItems;
	emit clickSig(filter);
}

QAbstractItemView *FTList::view()
{
	QAbstractItemView *view = qobject_cast<QAbstractItemView*>(widget());
	Q_ASSERT(view);
	return view;
}

QAbstractItemModel *FTList::model()
{
	QAbstractItemModel *amodel = view()->model();
	Q_ASSERT(amodel);
	return amodel;
}

int FTList::doClick(FTListClicker *filter)
{
	QAbstractItemModel *amodel = model();
	QAbstractItemView *aview = view();
	
	filter->click(this);
	return 0;	
}
static int n=0;
void FTList::dblClick(int row, int col)
{
	QModelIndex index = model()->index(row,col);

	QRect rc = view()->visualRect(index);
	QPoint pt(rc.x()+rc.width()/3,rc.y()+rc.height()/2);
	
	QWidget *widget = (QWidget*) view();
	widget = widget->childAt(10,10);

	QEvent *e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseMove,
			pt,widget->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QApplication::postEvent(widget, e);


	e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseButtonPress,
			pt,widget->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QApplication::postEvent(widget, e);

	e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseButtonRelease,
			pt,widget->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QApplication::postEvent(widget, e);

	e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseButtonDblClick,
			pt,widget->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QApplication::postEvent(widget, e);




//	QEvent *e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseButtonDblClick,
//			pt,widget()->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
//	QCoreApplication::postEvent(widget(), e);
}



void FTDefaultListClicker::add(QString column, QString value)
{
	_filters[column].append(value);
}

void FTDefaultListClicker::click(FTList *list)
{
	int totalClicked = 0;
	int filteredRow = 0;
	for(int row=0; row<list->rowCount(); row++)
	{
		if(filter(list, row))
		{
			if(_index<0 || _index==filteredRow)
				list->dblClick(row,0);
			filteredRow++;
		}
	}
}
bool FTDefaultListClicker::filter(FTList *list, int row)
{
	bool include = false;
	bool exclude = false;
	Q_FOREACH(QString scol, _filters.keys())
	{
		QList<QString> &filts = _filters[scol];
		int col = list->indexOfColumn(scol);
		if(col>=0)
		{
			if(filts.indexOf(list->value(row, col))>=0)
				include=true;
			else 
				exclude=true;
		}
	}
	if(!(include && !exclude))
		return false;
	return true;
}
