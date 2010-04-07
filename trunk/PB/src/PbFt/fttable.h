#ifndef FTTABLE_H
#define FTTABLE_H

#pragma once

#include "ftwidgethook.h"
#include "ftbutton.h"
#include "pbseats.h"
#include "pbgameoptions.h"

class FTPlayer 
{
};



class QHUDWidget;
class PBHandInfo;
class FTTables;
class PBTable;
class FTDlg : public FTWidgetHook
{
	Q_OBJECT;
public:
	enum {
		OK = 1,
		Yes = 1,
		Cancel = 2,
		No = 2
	};

	FTDlg(QWidget *w, QObject *parent, int ans = 1) : FTWidgetHook(w, parent){ setAnswer(ans); }

	virtual void onWidgetSetVisible(QWidget *w, bool visible);
	virtual void onWidget(QWidget *w);
	virtual int onDialog();

	void setAnswer(int ananswer){ answer = ananswer; }
	void setValue(QString value);
signals:
	void dialogEvent(QString question);
protected:
	QPointer<FTButton> okBtn;
	QPointer<FTButton> cancelBtn;
	QPointer<QLineEdit> textEdit;
	QString question;
	bool answerOk;
	int answer;
};

class FTActionButton
{
public:
	FTActionButton();
	
	void setPrefix(QString prefix);

	double amount();
	void setAmount(double amount);
	void setButton(FTButton *button);
	FTButton *button(){return _button;}
	bool parse();
	bool attach(FTButton *button);
	bool visibleTo(FTWidgetHook *wh);
	void press();
	bool enabled();
	void setEnabled(bool enabled);
	QString prefix(){return _prefix;}
protected:
	FTButton *_button;
	double _amount;
	bool _enabled;
	QString _prefix;
};

class FTTable : public FTWidgetHook
{
	Q_OBJECT
public:
	FTTable(QWidget *widget, QObject *parent);
	~FTTable();

public:
	void onNewChatLine(const QString &line);
	void onWidget(QWidget *w);
	void onWidgetSetVisible(QWidget *w, bool visible);
	bool onShowActionPanel(const QString &panelClazz, const QString &buttonName, QWidget *w, bool visible, FTActionButton &btn);
	void onDrawTextItem(QWidget *widget, const QPointF &p, const QTextItem &ti);

	void onPaint(QWidget *widget);

	virtual void _widgetClosing();
public:
	bool parseActionButton(const QString &text, const QString &prefix, double &amount);
	void setActionButton(const QString &id, QWidget *w, double amount);
	bool parseTitle();
public:
	void onHandStart(const QString &handId);
	void onHandEnd(const QString &handId);
	void onHandHistory(const QString &history, PBHandInfo *handInfo);
	
	void onButton(FTButton *button);
public slots:
	void onMsgBox(QString question);
protected:
	bool parseChat(const QString &input, QString &player, const QString &preAmount, const QString &preSuffix, double &amount, QString &suffx);
	bool parseCards(const QString &input, QString &player, const QString preCards, const QString preValue, QString &cards, QString &value);
	bool parseShowdownCards(const QString& input, QString &player, QString&cards, QString &value);
	bool parseButtons();
	void detachButtons();
	void logActiveButtons();

	// called from FTTables to fix some missed in chat issues
public:
	void setPlayerAtSeat(int seat, QString player, double stake, bool isSitout);
	void buttonSeat(int pos);
	
	FTTables *tables();

	void _postSmallBlind(QString player, double amount);
	void _postBigBlind(QString player, double amount);
	void _postDeadBlind(QString player, double amount);
	void _check(QString player);
	void _call(QString player, double amountToCall);
	void _raise(QString player, double raiseTo);
	void _fold(QString player);
	void _bet(QString player, double amount);
	void _winMainPot(QString player, double amount);
	void _tieMainPot(QString player, double amount);
	void _winSidePot(QString player, double amount);
	void _tieSidePot(QString player, double amount);
	void _sitOut(QString player);
	void _sitIn(QString player);
	void _join(QString player);
	void leave(QString player);

	void _flopCards(QString cards);
	void _turnCard(QString card);
	void _riverCard(QString card);
	void _holeCards(QString cards);

	void _showCards(QString player, QString cards);
	void _showHand(QString player, QString handValue);

	virtual void timerEvent(QTimerEvent *e);
protected slots:
	void getChips_Dialog(QString question);

signals:
	void postSmallBlindEvent(QString player, double amount);
	void postBigBlindEvent(QString player, double amount);
	void postDeadBlindEvent(QString player, double amount);
	void checkEvent(QString player);
	void callEvent(QString player, double amountToCall);
	void raiseEvent(QString player, double raiseTo);
	void foldEvent(QString player);
	void betEvent(QString player, double amount);
	void winMainPotEvent(QString player, double amount);
	void tieMainPotEvent(QString player, double amount);
	void winSidePotEvent(QString player, double amount);
	void tieSidePotEvent(QString player, double amount);
	void sitOutEvent(QString player);
	void sitInEvent(QString player);
	void joinEvent(QString player);
	void leaveEvent(QString player);

	void flopCardsEvent(QString cards);
	void turnCardEvent(QString card);
	void riverCardEvent(QString card);
	void holeCardsEvent(QString cards);

	void showCardsEvent(QString player, QString cards);
	void showHandEvent(QString player, QString handValue);
	void handStartEvent(QString handId);
	void buttonSeatEvent(int seat);

public:
	void checkCall();
	void betRaise(double amount);
	void fold();
	void sitout();
	void sitin();
	void postBB();
	void waitBB();
	void join();

public:
	QString tableId();
	void setTableId(QString tableId);
	
	//QString tableStatus();
	bool tourneyComplete(){ return _tourneyComplete; }
	
	QString handId();
	void setHandId(QString handId);

	QString tourneyId(){return _tourneyId;}
	QString tableNo(){return _tableNo;}
	bool isTourney(){return !_tourneyId.isEmpty(); }

	QPointer<PBSeats > seats(){ return _seats; }
public:
	QString _handId;
	QString heroId;
	double actionAmount;
	bool _tourneyComplete;
public:
	PBSeats *_seats;
	PBTable *_table;

	QList<FTActionButton*> actions;
	QString _tourneyId;
	QString _tableNo;
	QString _tourneyStatus;
	PBGameOptions _gameOpts;

	FTActionButton checkBtn;
	FTActionButton raiseBtn;
	FTActionButton callBtn;
	FTActionButton betBtn;
	FTActionButton foldBtn;
	
	FTActionButton postBtn;
	FTActionButton sitoutBtn;
	FTActionButton sitinBtn;
	FTActionButton waitBBBtn;
	FTActionButton joinBtn;
};

#endif