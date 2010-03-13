#include "stdafx.h"
#include "fthooks.h"
#include "ftwidgethook.h"
#include "ftbutton.h"

FTWidgetHook::FTWidgetHook(QWidget *widget, QObject *parent /*= 0*/)
	:QObject(parent)
{
	_widget = widget;
	connect(this, SIGNAL(closeSig()), this, SLOT(immediateClose())/*, Qt::QueuedConnection*/);
	timer = 0;
	_closing = false;
}

FTWidgetHook::~FTWidgetHook()
{

}

QWidget *FTWidgetHook::widget()
{
	return _widget;
}

void FTWidgetHook::setWidget(QWidget *widget)
{
	_widget = widget;
	_visible = widget->isVisible();
}

FTWidgetHook* FTWidgetHook::hookFor(QWidget *w)
{
	Q_FOREACH(QObject*obj, children())
	{
		FTWidgetHook *hook = qobject_cast<FTWidgetHook*>(obj);
		if(0!=hook && hook->widget()==w)
			return hook;
	}
	return 0;
}

FTWidgetHook* FTWidgetHook::hookFor(QString name)
{
	Q_FOREACH(QObject*obj, children())
	{
		FTWidgetHook *hook = qobject_cast<FTWidgetHook*>(obj);
		if(0!=hook && hook->objectName().indexOf(name)>-1)
			return hook;
	}
	return 0;
}


#define WIDGET_FORWARD(method) 	Q_FOREACH(QObject *child, children()){\
		FTWidgetHook* wh = qobject_cast<FTWidgetHook*>(child);\
		if(0!=wh && (wh->widget()==w \
			|| 0==wh->widget() || 0==widget() || wh->widget()->isAncestorOf(w)))\
			wh->method;\
		}

#define FORWARD(method) Q_FOREACH(QObject *child, children()){\
		FTWidgetHook* wh = qobject_cast<FTWidgetHook*>(child);\
		if(0!=wh)\
			wh->method;\
		}

void FTWidgetHook::onWidgetShow(QWidget *w)
{
	onWidget(w);
	WIDGET_FORWARD(onWidgetShow(w));
}

void FTWidgetHook::onWidget(QWidget *w)
{
	// create children here
}

void FTWidgetHook::onWidgetSetVisible(QWidget *w, bool isVisible)
{
	onWidget(w);
	WIDGET_FORWARD(onWidgetSetVisible(w,isVisible));
}

void FTWidgetHook::onWidgetChilds(QWidget *w, bool recurse)
{
	Q_ASSERT(w);
	for(int i=0;i<w->children().count();i++)
	{
		QWidget *child = static_cast<QWidget*>(w->children().at(i));
		onWidget(child);
		if(recurse)
			onWidgetChilds(child);
	}
}

void FTWidgetHook::immediateClose()
{
	Q_ASSERT(widget());
	//QTimer::singleShot(1000, widget(), SLOT(close()));
	widget()->close();
}

void FTWidgetHook::close()
{
	emit closeSig();
}

void FTWidgetHook::onStringIndexOf(const QString &s)
{
	FORWARD(onStringIndexOf(s));
}

void FTWidgetHook::onStringAppend(const QString &self, const QString &s)
{
	FORWARD(onStringAppend(self,s));
}

void FTWidgetHook::onMouseButtonPress(QWidget *w, QEvent* e)
{
	onWidget(w);
	WIDGET_FORWARD(onMouseButtonPress(w,e));
}

void FTWidgetHook::onPaint(QWidget *w)
{
	onWidget(w);
	WIDGET_FORWARD(onPaint(w));
}

void FTWidgetHook::onClose(QWidget *w, QEvent *e)
{
	WIDGET_FORWARD(onClose(w,e));
	if(w==widget())
	{
		_closing = true;
		qLog(Info)<<"WidgetClose "<<metaObject()->className()<<"["<<objectName()<<"], widget="<<w;
		emit widgetClosing(this);
		deleteLater();
	}
}
void FTWidgetHook::onDestroy(QWidget *w, QEvent *e)
{
	WIDGET_FORWARD(onDestroy(w,e));
	if(w==widget())
	{
		_closing = true;
		qLog(Info)<<"WidgetDestroy "<<metaObject()->className()<<"["<<objectName()<<"], widget="<<w;
		emit widgetDestroying(this);
		deleteLater();
	}
}

void FTWidgetHook::onDrawTextItem(QWidget *w, const QPointF &p, const QTextItem &ti)
{
	onWidget(w);
	WIDGET_FORWARD(onDrawTextItem(w,p,ti));
}

void FTWidgetHook::onRowsInserted(QAbstractItemView *w, int start, int end)
{
	onWidget(w);
	WIDGET_FORWARD(onRowsInserted(w,start,end));
}

bool FTWidgetHook::visible()
{
	return widget()->isVisible();
}

bool FTWidgetHook::visibleTo(FTWidgetHook *wh)
{
	return widget()->isVisibleTo(wh->widget());
}

void FTWidgetHook::click(QPoint pt)
{
	Q_ASSERT(widget()!=0);

	//pt.setX(3);pt.setY(3);

	QEvent *e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseMove,
			pt,widget()->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QCoreApplication::postEvent(widget(), e);


	e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseButtonPress,
			pt,widget()->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QCoreApplication::postEvent(widget(), e);

	e = QMouseEvent::createExtendedMouseEvent(QEvent::MouseButtonRelease,
			pt,widget()->mapToGlobal(pt), Qt::LeftButton,Qt::LeftButton,0);
	QCoreApplication::postEvent(widget(), e);

	qLog(Debug)<<" posted click to "<<QTUtil::widgetInfo(widget())<<" at "<<pt;

}
/*
void FTWidgetHook::deferWidgetFound()
{
	QTimer::singleShot(500, this, SLOT(emitWidgetFound()));
}

void FTWidgetHook::emitWidgetFound()
{

}*/