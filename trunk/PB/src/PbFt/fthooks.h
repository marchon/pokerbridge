#ifndef FTHOOKS_H
#define FTHOOKS_H


class PB_EXPORT QStringHooks : public QObject
{
public:
	static bool install();
	
	static QStringHooks *instance();

	static void (*append)(const QString &self, const QString &value);
	static void (*indexOf)(const QString &self);

public:
	static HOOK_TRACE_INFO h_QString_append;
	static HOOK_TRACE_INFO h_QString_indexOf;
	friend class QHookString;
};

class QWidgetEventFilter : public QObject
{
	Q_OBJECT;
public:
	QWidgetEventFilter(QObject *parent=0);
	bool eventFilter(QObject *object, QEvent *event);
protected:
	QWidget *last;
};

class PB_EXPORT QWidgetHooks 
{
public:
	static void (*show)(QWidget *widget);
	static void (*hide)(QWidget *widget);
	static void (*setVisible)(QWidget *widget, bool visible);
	static void (*paintDone)(QWidget *widget);
	static void (*drawTextItem)(QWidget *widget, const QPointF &p, const QTextItem &ti);
	static void (*paintEvent)(QWidget *widget, QEvent *ev);
	static void (*mouseButtonPressEvent)(QWidget *widget, QEvent *ev);
	static void (*closeEvent)(QWidget *widget, QEvent *ev);
	static void (*destroyEvent)(QWidget *widget, QEvent *ev);
public:
	static bool install();
	static bool installFilter();
	static bool uninstall();
public:
	static HOOK_TRACE_INFO h_QPainter_end;
	static HOOK_TRACE_INFO h_QPainter_drawTextItem;

	static HOOK_TRACE_INFO h_QWidget_show;
	static HOOK_TRACE_INFO h_QWidget_hide;
	static HOOK_TRACE_INFO h_QWidget_setVisible;
protected:
	static QWidgetEventFilter *filter;

	friend class QHookWidget;
	friend class QHookPainter;
};


class PB_EXPORT QAbstractItemViewHooks
{
public:
	static void (*rowsInserted)(QAbstractItemView *view, int start, int end);
	static bool install();
public:
	static HOOK_TRACE_INFO h_QAbstractItemView_rowsInserted;

	friend class QHookAbstractItemView;
};


// QTUtil
class PB_EXPORT QTUtil
{
public:
	static QWidget *getParentTitle(QWidget *w, QString &title);
	static QString widgetInfo(QWidget *w);
	static QString objectInfo(QObject *w);
	static QWidget *parentWithClass(QWidget *w, const QString &clazz);
	static QWidget *childButton(QWidget *w, const QString &title);
};

#endif