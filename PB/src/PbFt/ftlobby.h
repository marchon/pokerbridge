#pragma once

#include "ftdefs.h"
#include "ftwidgethook.h"

class FTHandHistory;
class FTHandWriter;
class FTLists;
class FTTourneys;
class FTLabel;
class FTTasks;

class FTLobbyHooks
{
public:
	static void onWidgetShow(QWidget *w);	
	static void onWidgetSetVisible(QWidget *w, bool isVisible); // widget changed visibility
	static void onMouseButtonPress(QWidget *w, QEvent* e);
	static void onPaint(QWidget *w);
	static void onDrawTextItem(QWidget *widget, const QPointF &p, const QTextItem &ti);
	static void onRowsInserted(QAbstractItemView *view, int start, int end);	// rows inserted into the table

	static void onStringIndexOf(const QString &s);	// string was hooked
	static void onStringAppend(const QString &self, const QString &s);	// string was hooked
	static void onClose(QWidget *w, QEvent *e);
	static void onDestroy(QWidget *w, QEvent *e);
	static void installHooks();
	static void uninstallHooks();
};



class FTLobby : public FTWidgetHook
{
	Q_OBJECT
public:
	FTLobby();
	~FTLobby();

	QSettings *settings();
	void init();

public:
	static FTLobby *instance();
	//static void destroy();
	FTTables *tables();
	FTLists *lists();
	FTTourneys *tourneys();
	FTTasks *tasks();

	void onLoggedIn();

	void onStringIndexOf(const QString &s);	// string was hooked
	void onStringAppend(const QString &self, const QString &s);	// string was hooked
	void onWidget(QWidget *w);
	
	void emitTooManyWindows(){ emit tooManyWindows(); }


signals:
	void tooManyWindows();
public:
	static QWaitCondition lobbyCreated;
	static QMutex mutex;
protected:
	QPointer<FTTables> _tables;
	QSettings *_settings;
	FTHandHistory *_handHistory;
	FTHandWriter *_handWriter;
	QPointer<FTLists> _lists;
	QPointer<FTTourneys> _tourneys;
	QPointer<FTTasks> _tasks;

	QPointer<FTButton> _loginBtn;
	QPointer<FTButton> _cancelConnectionBtn;
	QPointer<FTLabel> _connectionStatusLbl;
	bool _loginDone;

	
	bool _initialized;
};

#define PB_OPTION_IS_TRUE(opt,def) (FTLobby::instance()->settings()->value(opt,def)=="true")
#define PB_OPTION_INT(opt,def) (FTLobby::instance()->settings()->value(opt,def).toInt())