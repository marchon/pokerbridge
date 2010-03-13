#include "stdafx.h"
#include "fthooks.h"
#include "easyhook.h"

#define NO_REENT_START(x) 		static bool inHook##x = false;\
		if(!inHook##x){\
			inHook##x=true;
#define NO_REENT_END(x)	inHook##x=false; }



HOOK_TRACE_INFO QStringHooks::h_QString_append = {0};
HOOK_TRACE_INFO QStringHooks::h_QString_indexOf = {0};

void (*QStringHooks::append)(const QString &self, const QString &value) = 0;
void (*QStringHooks::indexOf)(const QString &self) = 0;


class  QHookString : public QString
{
public:
	QString &append(const QString &s);
	int indexOf(QChar c, int from = 0, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
};


bool QStringHooks::install()
{
	if(!EasyHookCpp("QtCore4.dll", "?append@QString@@QAEAAV1@ABV1@@Z", QHookString::append, &h_QString_append))
		return false;

	if(!EasyHookCpp("QtCore4.dll", "?indexOf@QString@@QBEHVQChar@@HW4CaseSensitivity@Qt@@@Z", QHookString::indexOf, &h_QString_indexOf))
		return false;

	return true;
}

QString &QHookString::append(const QString &s)
{
	QString &res = QString::append(s);
	NO_REENT_START(append)
	if(QStringHooks::append)
		(*QStringHooks::append)(*this, s);
	NO_REENT_END(append)
	return res;
}

int QHookString::indexOf(QChar c, int from /*= 0*/, Qt::CaseSensitivity cs /*= Qt::CaseSensitive*/) const
{
	NO_REENT_START(indexOf)
		if(QStringHooks::indexOf)
			(*QStringHooks::indexOf)(*this);
	NO_REENT_END(indexOf)
	return QString::indexOf(c,from,cs);
}


HOOK_TRACE_INFO QAbstractItemViewHooks::h_QAbstractItemView_rowsInserted = {0};
void (*QAbstractItemViewHooks::rowsInserted)(QAbstractItemView *view, int start, int end) = 0;

class QHookAbstractItemView : QAbstractItemView
{
public:
	void _rowsInserted(const QModelIndex &parent, int start, int end);

};


bool QAbstractItemViewHooks::install()
{
	if(!EasyHookCpp("QtGui4.dll", "?rowsInserted@QAbstractItemView@@MAEXABVQModelIndex@@HH@Z", QHookAbstractItemView::_rowsInserted, &h_QAbstractItemView_rowsInserted))
		return false;
	return true;
}

void QHookAbstractItemView::_rowsInserted(const QModelIndex &parent, int start, int end)
{
	//FullTilt::instance()->onRowsInserted(this, start, end);
	QAbstractItemView::rowsInserted(parent, start, end);

	NO_REENT_START(rowsInserted)
	if(0!=QAbstractItemViewHooks::rowsInserted)
		(*QAbstractItemViewHooks::rowsInserted)(this, start, end);
	NO_REENT_END(rowsInserted)
}


/// QWidget
class QHookWidget : QWidget
{
public:
	void _show();
	void _hide();
	void _setVisible(bool visible);
};


void QHookWidget::_show()
{
	QWidget::show();
	

	//FTPanel::instance();
	NO_REENT_START(show)
	if(QWidgetHooks::show)
		(*QWidgetHooks::show)(this);
	NO_REENT_END(show)
}

void QHookWidget::_hide()
{
	QWidget::hide();
	
	NO_REENT_START(hide)
	if(0!=QWidgetHooks::hide)
		(*QWidgetHooks::hide)(this);
	NO_REENT_END(hide)
}



//?setVisible@QWidget@@UAEX_N@Z
void QHookWidget::_setVisible(bool visible)
{
	bool wasVisible = isVisible();

	QWidget::setVisible(visible);
	
	NO_REENT_START(setVisible)
	if(wasVisible!=visible)
	{
		if(0!=QWidgetHooks::setVisible)
			(*QWidgetHooks::setVisible)(this, visible);
	}
	NO_REENT_END(setVisible)
}


class QHookPainter : QPainter
{
public:
	void _end();
	void _drawTextItem(const QPointF &p, const QTextItem &ti);
};


void QHookPainter::_end()
{
	NO_REENT_START(end)
		if(device()->devType()==QInternal::Widget)
		{
			QWidget *w = static_cast<QWidget*>(device());
			
			if(0!=QWidgetHooks::paintDone)
				(*QWidgetHooks::paintDone)(w);
		}
	NO_REENT_END(end)
	QPainter::end();
}


void QHookPainter::_drawTextItem(const QPointF &p, const QTextItem &ti)
{
	QPainter::drawTextItem(p,ti);
	NO_REENT_START(drawTextItem)
	if(device()->devType()==QInternal::Widget)
	{
		QWidget *w = static_cast<QWidget*>(device());
		if(0!=QWidgetHooks::drawTextItem)
			(*QWidgetHooks::drawTextItem)(w, p, ti);
	}
	NO_REENT_END(drawTextItem)
}


HOOK_TRACE_INFO QWidgetHooks::h_QWidget_show = {0};
HOOK_TRACE_INFO QWidgetHooks::h_QWidget_hide = {0};
HOOK_TRACE_INFO QWidgetHooks::h_QWidget_setVisible = {0};
HOOK_TRACE_INFO QWidgetHooks::h_QPainter_end = {0};
HOOK_TRACE_INFO QWidgetHooks::h_QPainter_drawTextItem = {0};

void (*QWidgetHooks::show)(QWidget *widget) = 0;
void (*QWidgetHooks::hide)(QWidget *widget) = 0;
void (*QWidgetHooks::setVisible)(QWidget *widget, bool visible) = 0;
void (*QWidgetHooks::paintDone)(QWidget *widget) = 0;
void (*QWidgetHooks::drawTextItem)(QWidget *widget, const QPointF &p, const QTextItem &ti) = 0;
void (*QWidgetHooks::paintEvent)(QWidget *widget, QEvent *ev) = 0;
void (*QWidgetHooks::mouseButtonPressEvent)(QWidget *widget, QEvent *ev) = 0;
void (*QWidgetHooks::closeEvent)(QWidget *widget, QEvent *ev) = 0;
void (*QWidgetHooks::destroyEvent)(QWidget *widget, QEvent *ev) = 0;

QWidgetEventFilter* QWidgetHooks::filter = 0;

bool QWidgetHooks::install()
{
	if(!EasyHookCpp("QtGui4.dll", "?show@QWidget@@QAEXXZ", QHookWidget::_show, &h_QWidget_show))
		return false;
	if(!EasyHookCpp("QtGui4.dll", "?hide@QWidget@@QAEXXZ", QHookWidget::_hide, &h_QWidget_hide))
		return false;
	if(!EasyHookCpp("QtGui4.dll", "?setVisible@QWidget@@UAEX_N@Z", QHookWidget::_setVisible, &h_QWidget_setVisible))
		return false;
	
	if(!EasyHookCpp("QtGui4.dll", "?end@QPainter@@QAE_NXZ", QHookPainter::_end, &h_QPainter_end))
		return false;
	
	if(!EasyHookCpp("QtGui4.dll", "?drawTextItem@QPainter@@QAEXABVQPointF@@ABVQTextItem@@@Z", QHookPainter::_drawTextItem, &h_QPainter_drawTextItem))
		return false;
	
	//installFilter(); dies here if injection is done at app startup
	return true;
} 

bool QWidgetHooks::installFilter()
{
	if(filter)
		return false;
	QCoreApplication *app = QCoreApplication::instance();
	if(app)
	{
		qLog(Info)<<"installing filter";
		filter = new QWidgetEventFilter();
		filter->moveToThread(app->thread());
		app->installEventFilter(filter);
		qLog(Info)<<"event filter installed";
		return true;
	}
	return false;
}

bool QWidgetHooks::uninstall()
{
	if(filter){
		QCoreApplication *app = QCoreApplication::instance();
		app->removeEventFilter(filter);
		delete filter;
		filter = 0;
		qLog(Debug)<<"Event filter uninstalled";
	}
	return true; 
}

QWidgetEventFilter::QWidgetEventFilter(QObject *parent) : QObject(parent)
{
	last = 0;
}

bool QWidgetEventFilter::eventFilter(QObject *object, QEvent *event)
{
	//qLog(Debug)<<"event "<<event;
	
	if (event->type() == QEvent::Paint) {
		QWidget *w = qobject_cast<QWidget*>(object);
		if(w && w!=last)
		{
			if(QWidgetHooks::paintEvent)
				(*QWidgetHooks::paintEvent)(w, event);
			return false;
		}
           return false;
	}else if (event->type() == QEvent::MouseButtonPress) {
		QWidget *w = qobject_cast<QWidget*>(object);
		if(w && w!=last)
		{
			if(QWidgetHooks::mouseButtonPressEvent)
				(*QWidgetHooks::mouseButtonPressEvent)(w, event);
			last=w;
		}
        return false;
	}else if(event->type() == QEvent::Close){
		QWidget *w = qobject_cast<QWidget*>(object);
		if(QWidgetHooks::closeEvent)
			(*QWidgetHooks::closeEvent)(w,event);
	}else if(event->type() == QEvent::Destroy){
		QWidget *w = qobject_cast<QWidget*>(object);
		if(QWidgetHooks::destroyEvent)
			(*QWidgetHooks::destroyEvent)(w,event);
	}
    return false;
}



/// QTUtil


QWidget *QTUtil::getParentTitle(QWidget *w, QString &title)
{
	title = "";

	while(NULL!=w && w->windowTitle().length()==0)
		w=static_cast<QWidget*>(w->parent());

	if(w)
		title = w->windowTitle();
	return w;
}

QWidget *QTUtil::parentWithClass(QWidget *w, const QString &clazz)
{
	while(NULL!=w && strcmp(w->metaObject()->className(),clazz.toAscii().constData())!=0)
		w=static_cast<QWidget*>(w->parent());

	return w;
}



QString QTUtil::widgetInfo(QWidget *w)
{
	QAbstractButton *btn = qobject_cast<QAbstractButton*>(w);
	
	QString info = "["+w->windowTitle()+":"+w->objectName()+"]";
	info+=w->metaObject()->className();
	info+="/";
	info+=w->metaObject()->superClass()->className();
	info+=((btn!=0)?"\""+btn->text()+"\"":"");
	info+="("+QString().sprintf("%d:%d:%d:%d",w->x(),w->y(),w->width(),w->height())+")";
	if(w->parent()!=0)
		info+="===>"+widgetInfo((QWidget*)w->parent());
	return info;
}

QString QTUtil::objectInfo(QObject *w)
{
	return "["+w->objectName()+"]"+w->metaObject()->className()+"/"+w->metaObject()->superClass()->className();
}

QWidget *QTUtil::childButton(QWidget *w, const QString &title)
{
	for(int i=0;i<w->children().count();i++)
	{
		//pbDbg("child "+QTUtil::widgetInfo(static_cast<QWidget*>(w->children().at(i))));
		QAbstractButton *btn = qobject_cast<QAbstractButton*>(w->children().at(i));
		if(NULL!=btn)
			if(btn->text().indexOf(title)>-1)
				return btn;
	}
	return 0;
}