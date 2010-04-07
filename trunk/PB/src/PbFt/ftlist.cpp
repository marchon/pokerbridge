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
	QAbstractItemModel *model = view->model();
	//qLog(Debug)<<"rowsInserted("<<start<<","<<end<<")"<<QTUtil::widgetInfo(view)<<", model "<<model->metaObject()->className()<<":"<<model->objectName();
	//FTList::dump(model,start, end);

	if(0==alist)
	{
		QString modelClass = model->metaObject()->className();
		
		//qLog(Info)<<"LIST-WIDGET "<<QTUtil::widgetInfo(view)<<" MODEL: "<<modelClass;

		if(start==0)
		{
			if(ftSngLobbyModel==modelClass)
			{
				alist = new FTTourneyList(view, this);
				alist->setObjectName(modelClass);
			}
		}

		if(view->objectName()=="list_1")
		{
			alist = new FTList(view, this);
			alist->setObjectName("filter1");
			alist->setPainterMode(true);

		}else if(view->objectName()=="list_2")
		{
			alist = new FTList(view, this);
			alist->setObjectName("filter2");
			alist->setPainterMode(true);
		}else if(view->objectName()=="list_3")
		{
			alist = new FTList(view, this);
			alist->setObjectName("filter3");
			alist->setPainterMode(true);
		}else if(view->objectName()=="list_4")
		{
			alist = new FTList(view, this);
			alist->setObjectName("filter4");
			alist->setPainterMode(true);
		}else if(view->objectName()=="list_5")
		{
			alist = new FTList(view, this);
			alist->setObjectName("filter5");
			alist->setPainterMode(true);
		}


		//qLog(Debug)<<"rowsInserted("<<start<<","<<end<<")"<<QTUtil::widgetInfo(view)<<", model "<<model->metaObject()->className()<<":"<<model->objectName();
	}


	if(alist)
		alist->onRowsInserted(view, start, end);
	
	
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
	_painterMode = false;
	_paintDone = false;
}



void FTList::onRowsInserted(QAbstractItemView *view, int start, int end)
{
	_items.clear();

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


void FTList::dump(QAbstractItemModel *model, int start, int end)
{
	if(!model)
		return;

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
			qLog(Debug)<<i<<":"<<s;
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
	QString v = model()->data(model()->index(row, col)).toString();
	if(!v.isEmpty())
		return v;
	if(_painterMode)
		if(row>=0 && row<_items.size())
			return _items.values()[row];
	return "";
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

int FTList::indexOfRow(QString v)
{
	QAbstractItemModel *amodel = model();
	for(int j=0;j<amodel->rowCount();j++)
	{
		QString row = value(j,0);
		if(row==v)
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

}

void FTList::click(int row, int col, float subX, float subY)
{
	QModelIndex index = model()->index(row,col);

	QRect rc = view()->visualRect(index);
	QPoint pt(rc.x()+rc.width()*subX,rc.y()+rc.height()*subY);
	
	//qLog(Info)<<"click "<<objectName()<<" "<<pt.x()<<":"<<pt.y();

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

}

void FTList::onDrawTextItem(QWidget *w, const QPointF &p, const QTextItem &ti)
{
	FTWidgetHook::onDrawTextItem(w, p, ti);
	
	if(widget() && (widget()->isAncestorOf(w)))
	{
		if(_paintDone)
		{
			_paintDone=false;
			_items.clear();
			//qLog(Debug)<<"ITEMSCLEAR "<<QTUtil::widgetInfo(w);
		}
		//qLog(Debug)<<"DT: "<<p<<":"<<ti.text()<<QTUtil::widgetInfo(w);
		if(_painterMode)
			_items[p.y()] = ti.text();
	}
}

void FTList::setPainterMode(bool pm)
{
	_painterMode = pm;
}

void FTList::onPaint(QWidget *w)
{
	FTWidgetHook::onPaint(w);
	if(widget() && (widget()->isAncestorOf(w)))
	{
		//qLog(Debug)<<"PAINTDONE "<<QTUtil::widgetInfo(w);
		FTLists *lists = qobject_cast<FTLists*>(parent());
		if(0!=lists)
			lists->paintDone(this);
		_paintDone = true;
	}
}