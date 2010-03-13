#pragma once

class FTButton;
class FTWidgetHook: public QObject
{
	Q_OBJECT
public:
	FTWidgetHook(QWidget *widget, QObject *parent = 0);
	virtual ~FTWidgetHook();
	QWidget *widget();
	void setWidget(QWidget *widget);
	bool visible();
	bool visibleTo(FTWidgetHook *wh);

	void click(QPoint pt);

	virtual FTWidgetHook* hookFor(QWidget *w);
	virtual FTWidgetHook* hookFor(QString name);

	void onWidgetChilds(QWidget *w, bool recurse=false);
	
	bool isAlive(){ return !_closing; }

	virtual void onWidget(QWidget *w);		// widget was found
	virtual void onWidgetShow(QWidget *w);	
	virtual void onWidgetSetVisible(QWidget *w, bool isVisible); // widget changed visibility
	virtual void onStringIndexOf(const QString &s);	// string was hooked
	virtual void onStringAppend(const QString &self, const QString &s);	// string was hooked
	virtual void onMouseButtonPress(QWidget *w, QEvent* e);
	virtual void onPaint(QWidget *w);
	virtual void onDrawTextItem(QWidget *widget, const QPointF &p, const QTextItem &ti);
	virtual void onRowsInserted(QAbstractItemView *view, int start, int end);	// rows inserted into the table
	virtual void onClose(QWidget *w, QEvent *e);
	virtual void onDestroy(QWidget *w, QEvent *e);
	//void deferWidgetFound();
public slots:
	void immediateClose();
	void close();
	//virtual void emitWidgetFound();
signals:
	void closeSig();
	void widgetDestroying(FTWidgetHook *wh);
	void widgetClosing(FTWidgetHook *wh);
	void widgetHooked(FTWidgetHook *wh);
private:
	QPointer<QWidget> _widget;
	bool _visible;
	QTimer *timer;
	bool _closing;
};