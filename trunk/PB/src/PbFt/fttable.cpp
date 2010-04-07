#include "stdafx.h"
#include "fttable.h"
#include "ftpanel.h"
#include "fthooks.h"
#include "ftlobby.h"
#include "fttables.h"

#include "pbtable.h"
#include "pbseatedplayer.h"
#include "pbseats.h"



void FTDlg::onWidget(QWidget *w)
{
	QAbstractButton *btn = qobject_cast<QAbstractButton*>(w);

	QString clazz = w->metaObject()->className();
	QLineEdit *edit = qobject_cast<QLineEdit*>(w);
	QLabel *label = qobject_cast<QLabel*>(w);
	if(0!=label)
	{
		question = label->text();
	}else
	if(0!=edit)
	{
		textEdit = edit;
	}else if(0!=btn)
	{
		if(hookFor(w)==0)
			if(btn->text()=="OK" || btn->text()=="Yes")
			{
				okBtn = new FTButton(btn, this);
			}else if(btn->text()=="Cancel" || btn->text()=="No")
				cancelBtn = new FTButton(btn, this);
	}
}

void FTDlg::setValue(QString value)
{
	if(0!=textEdit)
		textEdit->setText(value);
}

void FTDlg::onWidgetSetVisible(QWidget *w, bool visible)
{
	FTWidgetHook::onWidgetSetVisible(w,visible);
	onWidgetChilds(w, true);
	if(w==widget() && visible)
	if(0!=okBtn)
	{
		int ans = onDialog();
		if(1==ans)
		{
			if(okBtn)
				okBtn->press();
		}else if(2==ans)
		{
			if(cancelBtn)
				cancelBtn->press();
		}
	}
}

int FTDlg::onDialog()
{
	emit dialogEvent(question);
	return answer;
}

FTActionButton::FTActionButton()
{
	_button = 0;
	_prefix = "?";
}

void FTActionButton::setPrefix(QString prefix)
{
	_prefix = prefix;
}

double FTActionButton::amount()
{
	return _amount;
}

void FTActionButton::setAmount(double amount)
{
	_amount = amount;
}

void FTActionButton::setButton(FTButton *button)
{
	_button = button;
}

void FTActionButton::press()
{
	_button->press();
}

bool FTActionButton::visibleTo(FTWidgetHook *wh)
{
	return _button && _button->visibleTo(wh);
}

bool FTActionButton::enabled()
{
	return 0!=_button && _enabled;
}

void FTActionButton::setEnabled(bool isEnabled)
{
	_enabled = isEnabled;
}


bool FTActionButton::attach(FTButton *button)
{
	QString text = button->text();
	
	setAmount(-1);
	if(!text.startsWith(_prefix))
		return false;
	
	setButton(button);


	return true;
}

bool FTActionButton::parse()
{
	setEnabled(false);

	if(0==_button)
		return false;

	QString text = _button->text();
	int s = _prefix.length();
	while(s<text.length() && !text[s].isDigit())
		s++;
	QString amountStr = text.mid(s);
	amountStr.remove(QRegExp("[\\,\\$]"));
	if(!amountStr.isEmpty())
	{
		bool ok;
		setAmount(amountStr.toDouble(&ok));
		if(!ok)
			qLog(Error)<<"failed to parse amount from button ["+text+"]";
	}
	setEnabled(true);
	return true;
}







FTTable::FTTable(QWidget *widget, QObject *parent)
	: FTWidgetHook(widget, parent)
{
	_seats = new PBSeats( this );

	checkBtn.setPrefix("CHECK");	actions.append(&checkBtn);
	foldBtn.setPrefix("FOLD");	actions.append(&foldBtn);
	callBtn.setPrefix("CALL");	actions.append(&callBtn);
	betBtn.setPrefix("BET");	actions.append(&betBtn);
	raiseBtn.setPrefix("RAISE");	actions.append(&raiseBtn);
	sitoutBtn.setPrefix("SIT");	actions.append(&sitoutBtn);
	waitBBBtn.setPrefix("WAIT");	actions.append(&waitBBBtn);
	postBtn.setPrefix("POST");	actions.append(&postBtn);


	joinBtn.setPrefix("JOIN");	// join wating list
	sitinBtn.setPrefix("DEAL");	// deal me in
	
	//new RpcAdaptor(this);
	new RMessageAdaptor(this);
	
	_tourneyComplete = false;

//	startTimer(2000);
}

bool FTTable::parseTitle()
{
	if(!widget())
		return false;

	QString title = widget()->windowTitle();
	QStringList parts = title.split(" - ");

	if(parts.size()<3)
		return false;

	
	QString gameType = parts[2];

	QString first = parts[0];
	
	QRegExp tourneyRe("\\((\\d+)\\)\\, Table (\\d+)");
	int tourneyIdx = tourneyRe.indexIn(first);
	if(tourneyIdx>-1)
	{
		QString tourneyType = first.left(tourneyIdx);
		_tourneyId = tourneyRe.cap(1);
		_tableNo = tourneyRe.cap(2);
		QString blinds = parts[1];
		setTableId(parts[0]);

		//qLog(Info)<<"tourney "<<tableId()<<" id="<<tourneyId()<<" blinds="<<blinds;
	}
	return true;
}

FTTable::~FTTable(	)
{
	qLog(Debug)<<"~FTTable "<<tableId();
}

QString FTTable::tableId()
{
	return objectName();
}

void FTTable::setTableId(QString tableId)
{
	setObjectName(tableId);
}

QString FTTable::handId()
{
	return _handId;
}

void FTTable::setHandId(QString handId)
{
	_handId = handId;
}

/// input events
void FTTable::onNewChatLine(const QString &input)
{
	QString player;
	double amount;

	QString allin;
	QString handValue;
	QString flopCards,heroHoleCards,turnCard,riverCard;

#define PCH(act) parseChat(input, player, act, ", and is ", amount, allin)
	
	if(PCH(" posts the big blind of "))
		_postBigBlind(player, amount);
	else	
	if(PCH(" posts the small blind of "))
		_postSmallBlind(player, amount);
	else
	if(PCH(" posts a dead small blind of "))
		_postDeadBlind(player, amount*3);
	else
	if(PCH(" posts "))
		_postDeadBlind(player, amount);
	else
	if(PCH(" calls "))
		_call(player, amount);
	else	
	if(PCH(" raises to "))
		_raise(player, amount);
	else
	if(PCH(" checks"))
		_check(player);
	else
	if(PCH(" folds"))
		_fold(player);
	else
	if(PCH(" bets "))
		_bet(player,amount);
	else
	if(parseChat(input, player, " wins the pot ", " with ", amount, handValue))
		_winMainPot(player, amount);
	else
	if(parseChat(input, player, " wins the main pot ", " with ", amount, handValue))
		_winMainPot(player, amount);
	else
	if(parseChat(input, player, " wins the side pot ", " with ", amount, handValue))
		_winSidePot(player, amount);
	else
	if(parseChat(input, player, " ties for the pot ", " with ", amount, handValue))
		_tieMainPot(player, amount);// shows 
	else
	if(parseCards(input, player, " shows [", "]", heroHoleCards, handValue))
		_showCards(player, heroHoleCards);
	else
	if(parseCards(input, player, " shows ", " shows ", heroHoleCards, handValue))
		_showHand(player, handValue);
	else
	if(parseCards(input,player, " have been dealt ", "", heroHoleCards, handValue))
		_holeCards(heroHoleCards);
	else
	if(parseCards(input,player, "The river is ","", riverCard, handValue))
		_riverCard(riverCard);
	else
	if(parseCards(input,player, "The turn is ","", turnCard, handValue))
		_turnCard(turnCard);
	else
	if(parseCards(input,player, "The flop is ","",flopCards, handValue))
		_flopCards(flopCards);
	else
		qLog(Error)<<"chat unparsed: "<<input;
//	if(0!=hudView)
//		hudView->repaint();
}

bool FTTable::parseShowdownCards(const QString& input, QString &player, QString&cards, QString &value)
{
	QString showsStr = " shows [";
	int si0 = input.indexOf(showsStr);
	if(si0>=0)
	{
		player = input.mid(0,si0);
		int si1 = input.indexOf("] ");
		if(si1>=si0)
		{
			cards = input.mid(si0+showsStr.length(),si1-showsStr.length()-si0);
			value = input.mid(si1+2);
			return true;
		}
	}

	// "mucked" varsion
	if(input.lastIndexOf("Seat ")<0)
		return false;

	showsStr=" showed [";
	int si = input.lastIndexOf(showsStr);
	if(si<0)
	{
		showsStr = " mucked [";
		si = input.lastIndexOf(showsStr);
	}
	if(si<0)
		return false;
	QString suffStr = "]";
	int hi = input.indexOf(suffStr, showsStr.length()+si);
	if(hi<0)
		return false;
	cards = input.mid(si+showsStr.length(), hi-si-showsStr.length());
	int xi = input.indexOf(" (small blind) ");
	if(xi>-1)
		si=xi;
	xi = input.indexOf(" (button) ");
	if(xi>-1)
		si=xi;
	xi = input.indexOf(" (big blind) ");
	if(xi>-1)
		si=xi;
	int ai = input.lastIndexOf(": ");
	player = input.mid(ai+2,si-ai-2);	
	value = input.mid(hi+suffStr.length());
//	pbLog("PHS ["<<player<<"]["<<cards<<"]["<<value<<"]"<<input);
	return true;
}

void FTTable::onHandHistory(const QString &history, PBHandInfo *info)
{
	QMap<QString, QString> playerCardsMap;

	QStringList lines = history.split("\n");
	for(int i=0;i<lines.size();i++)
	{
		QString player="";
		QString handValue;
		QString cards;
		if(parseShowdownCards(lines[i],player,cards,handValue))
			playerCardsMap[player] = cards;
	}

	for(QMap<QString,QString>::iterator i = playerCardsMap.begin(); i!=playerCardsMap.end(); i++)
		showCardsEvent(i.key(), i.value());
}

bool FTTable::parseCards(const QString &input, QString &player, const QString preCards, const QString preValue, QString &cards, QString &value)
{
	//Dealer: You have been dealt [Qs 9c]
	player="";
	cards="";
	int pi = input.lastIndexOf(preCards);
	if(pi<0)
		return false;

	int si = input.indexOf(preValue,preValue.length());
	if(si<0)
		si=input.length();
	else
		value=input.mid(si+preValue.length());

	cards = input.mid(pi+preCards.length(),si-preCards.length()-pi);
	cards.remove(QRegExp("[\\[\\]]"));
	
	player = input.mid(0,pi);

//	pbLog("CRD ["<<player<<"] ["<<cards<<"] ["<<value<<"]"<<" CRD("<<preCards<<":"<<preValue<<"):"<<input);

	return true;
}

//Dealer: monsterjpier1 posts the big blind of 10
bool FTTable::parseChat(const QString &input, QString &player, const QString &action, const QString &preSuffix, double &amount, QString &suffix)
{
	player = "";
	amount = 0;
	suffix = "";

	int ai = input.lastIndexOf(action);
	if(-1==ai)
		return false;

	player = input.mid(0,ai);
	int li = -1;
	if(preSuffix.length()>0)
	{
		li = input.indexOf(preSuffix, ai+action.length());
		if(-1==li)
			li=input.indexOf(")");
		if(-1!=li)
		{
			suffix = input.mid(li+preSuffix.length());
		}else li = input.length();
	}
	
	QString amountStr = input.mid(ai+action.length(),li-ai-action.length());
	amountStr.remove(QRegExp("[$,\\(\\)]"));
	if(amountStr.length()>0)
	{
		bool ok = false;
		amount = amountStr.toDouble(&ok);
		if(!ok)
		{
			qLog(Error)<<"Failed to parse amount ["<<amountStr<<"]";
		}
	}

	//pbLog("PCH ["<<player<<"] ["<<amount<<"] ["<<suffix<<"]"<<" PCH("<<action<<"):"<<input);
	return true;
}





void FTTable::onHandEnd(const QString&)
{

	qLog(DebugHand)<<"seats on table ["<<tableId()<<"] with button at "<<seats()->buttonSeat();
	int seatNo=1;
/*	for(FTSeatsList::iterator p = seats.begin();p!=seats.end();p++,seatNo++)
		if(*p!=NULL)
			pbDbg(seatNo<<":"<<(*p)->getSeat()<<":"<<(*p)->getPlayerId()<<"("<<(*p)->getStake()<<")")
		else
			pbDbg(seatNo<<":free");
	
	seats.clear();
*/	
	
	seats()->reset(); // TODO why? ANSWER: next hand will be with wrong players else

	setHandId("");

	qLog(DebugHand)<<"seats cleared on table=["<<tableId()<<"]";
}

void FTTable::buttonSeat(int pos)
{
	if(seats()->buttonSeat()==-1)
	{
		seats()->setButtonSeat(pos);
		
		emit buttonSeatEvent(seats()->buttonSeat());
		emit handStartEvent(handId());
	}
}

/* FT hides info about players in the chat. This info is taken from QString. 
Code assumes seat info follows right after first line in chat, which is "Dealer: Hand #xxxx */



void FTTable::setPlayerAtSeat(int seat, QString playerId, double stake, bool isSitOut)
{
	if(seats()->seatsCount()<seat+1)
		seats()->setSeatsCount(seat+1);
	PBSeatedPlayer *player = seats()->join(seat, playerId, stake, isSitOut); 
}


void FTTable::_postSmallBlind(QString playerId, double amount)
{
	// set button if didn't do so
	int seat = seats()->seatOf(playerId);
	seats()->setButtonSeat(seats()->prevSeat(seat));

	emit postSmallBlindEvent(playerId, amount);
}

void FTTable::_postBigBlind(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" posts big blind "<<amount;
	emit postBigBlindEvent(player, amount);
}

void FTTable::_postDeadBlind(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" posts dead blind "<<amount;
	emit postDeadBlindEvent(player, amount);
}

void FTTable::_check(QString player)
{
	qLog(Info)<<handId()<<": "+player<<" checks";
	emit checkEvent(player);
}

void FTTable::_call(QString player, double amountToCall)
{
	qLog(Info)<<handId()<<": "+player<<" calls "<<amountToCall;
	emit callEvent(player, amountToCall);
}

void FTTable::_raise(QString player, double raiseTo)
{
	qLog(Info)<<handId()<<": "+player<<" raises to "<<raiseTo;
	emit raiseEvent(player, raiseTo);
}

void FTTable::_fold(QString player)
{
	qLog(Info)<<handId()<<": "+player<<" folds";
	emit foldEvent(player);
}

void FTTable::_bet(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" bets "<<amount;
	emit betEvent(player, amount);
}

void FTTable::_winMainPot(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" wins main pot "<<amount;
	emit winMainPotEvent(player, amount);
}

void FTTable::_tieMainPot(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" ties main pot "<<amount;
	emit tieMainPotEvent(player, amount);
}

void FTTable::_winSidePot(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" wins side pot "<<amount;
	emit winSidePotEvent(player, amount);
}

void FTTable::_tieSidePot(QString player, double amount)
{
	qLog(Info)<<handId()<<": "+player<<" ties side pot "<<amount;
	emit tieSidePotEvent(player, amount);
}

void FTTable::_sitOut(QString player)
{
	qLog(Info)<<handId()<<": "+player<<" sits out";
	emit sitOutEvent(player);
}

void FTTable::_sitIn(QString player)
{
	qLog(Info)<<handId()<<": "+player<<" sits in";
	emit sitInEvent(player);
}

void FTTable::_join(QString player)
{
	qLog(Info)<<handId()<<": "+player<<" joins";
	emit joinEvent(player);
}

void FTTable::leave(QString player)
{
	qLog(Info)<<handId()<<": "+player<<" leaves";
	emit joinEvent(player);
}

void FTTable::_flopCards(QString cards)
{
	qLog(Info)<<handId()<<": flop "<<cards;
	emit flopCardsEvent(cards);
}

void FTTable::_turnCard(QString card)
{
	qLog(Info)<<handId()<<": turn "<<card;
	emit turnCardEvent(card);
}

void FTTable::_riverCard(QString card)
{
	qLog(Info)<<handId()<<": river "<<card;
	emit riverCardEvent(card);
}

void FTTable::_holeCards(QString cards)
{
	qLog(Info)<<handId()<<": hero cards "<<cards;
	emit holeCardsEvent(cards);
}

void FTTable::_showCards(QString player, QString cards)
{
	qLog(Info)<<handId()<<": "<<player<<" shows "<<cards;
	emit showCardsEvent(player,cards);
}

void FTTable::_showHand(QString player, QString handValue)
{
	qLog(Info)<<handId()<<": "<<player<<" hand "<<handValue;
	emit showHandEvent(player,handValue);
}

void FTTable::onWidget(QWidget *w)
{
	//if(onShowActionPanel("CDealMeInReadyBtnPanel", "DEAL", w, w->isVisible(), sitinBtn))
	//	;
	//else if(onShowActionPanel("CWaitingListButtonPanel", "JOIN", w, w->isVisible(), sitinBtn))
	//	;

	QString clazz = w->metaObject()->className();
	QString name = w->objectName();

	QAbstractButton *btn = qobject_cast<QAbstractButton*>(w);
	if(btn)
	{
		if(clazz=="CMultiLineBtn") // or CMultiLineCheckbox
		{
			FTButton *hookButton = qobject_cast<FTButton*>(hookFor(btn));
			if(0==hookButton)
			{
				{
					hookButton =  new FTButton(btn, this);
				}
			}
			onButton(hookButton);
		}
	}
	
	if(clazz=="CGetChipsDlg")
	{
		FTDlg *getChipsDlg = new FTDlg(w, this);
		connect(getChipsDlg, SIGNAL(dialogEvent(QString)), this, SLOT(getChips_Dialog(QString)));
	}

	if(clazz=="CMessageBox")
	{
		FTDlg *msgBox = new FTDlg(w, this);
		connect(msgBox, SIGNAL(dialogEvent(QString)), this, SLOT(onMsgBox(QString)));
	}

	if(w==widget() && !w->windowTitle().isEmpty())
		parseTitle();

	FTWidgetHook::onWidget(w);
}

void FTTable::getChips_Dialog(QString question)
{
	FTDlg *dlg = qobject_cast<FTDlg*>(sender());
	Q_ASSERT(dlg);
	dlg->setAnswer(FTDlg::Yes);
	dlg->setValue("150");
}

void FTTable::onMsgBox(QString question)
{
	FTDlg *dlg = qobject_cast<FTDlg*>(sender());
	Q_ASSERT(dlg);

	if(question.indexOf("Auto Post Blinds")>-1)
		dlg->setAnswer(1);
	if(question.indexOf("windows")>-1)
	{
		FTLobby::instance()->emitTooManyWindows();
	}
}

void FTTable::onButton(FTButton *button)
{
	Q_FOREACH(FTActionButton* ab, actions)
	{
		ab->attach(button);
	}
	joinBtn.attach(button);
	sitinBtn.attach(button);
}

bool FTTable::parseButtons()
{
	Q_FOREACH(FTActionButton* ab, actions)
	{
		ab->parse();
	}
	return true;
}

void FTTable::detachButtons()
{
	Q_FOREACH(FTActionButton* ab, actions)
	{
		ab->setButton(0);
		ab->setEnabled(false);
	}
	qLog(DebugHand)<<"detached buttons";
}

FTTables *FTTable::tables()
{
	return static_cast<FTTables*>(parent());
}

void FTTable::onDrawTextItem(QWidget *w, const QPointF &p, const QTextItem &ti)
{

	if(widget() && widget()->isAncestorOf(w) && ti.text().indexOf("is over")>-1)
	{
		_tourneyComplete = true;
		tables()->tourneyIsOver(this);
	}

/*	if(0==hudView)
		return;

	for(int i=0; i<table()->getSeatsCount(); i++)
	{
		PBSeatedPlayer *player = table()->playerAt(i);
		if(0!=player && player->getPlayerId() == text)
		{
			hudView->setLocation(player->getPlayerId(), pt);
		}
	}
*/
}

void FTTable::_widgetClosing()
{
	FTWidgetHook::_widgetClosing();
	tables()->sendTableInfo(this);
}

void FTTable::onWidgetSetVisible(QWidget *w, bool visible)
{
	// updates hooks
	FTWidgetHook::onWidgetSetVisible(w, visible);


	if(w==widget())
		if(!visible)
		{
			qLog(Debug)<<"TableHide "<<w<<" t="<<tableId();
			_widgetClosing();
		}

	onWidgetChilds(w); //explore buttons

	QString clazz = w->metaObject()->className();
	QString name = w->objectName();

	if(clazz=="CBetActionsPanel")
	{
		detachButtons();
		onWidgetChilds(w); //explores buttons and attaches them - see onWidget/onButton
		if(visible)
		{
			qLog(Info)<<"Action request";
			
			parseButtons();	// updates text from attached buttons and enables commands

		
			double amount = -1;
			if(betBtn.enabled())
				amount = betBtn.amount();
			if(raiseBtn.enabled())
				amount = raiseBtn.amount();

			if(FTPanel::instance())
				FTPanel::instance()->setAmount(amount);


		}else{
			// upon hide of the panel buttons change their behaviour
			detachButtons();
			//FTPanel::instance()->disconnectTable(this);
		}
		logActiveButtons();
	}else if(clazz=="CDealMeInReadyBtnPanel")
	{
		onWidgetChilds(w);
		if(visible)
		{
			sitinBtn.parse();
//			qLog()<<"sitinBtn="<<QTUtil::widgetInfo(sitinBtn.button()->widget());
//			qLog()<<"me="<<QTUtil::widgetInfo(this->widget());

		}else{
			sitinBtn.setEnabled(false);
		}
		logActiveButtons();
	}else if(clazz=="CWaitingListButtonPanel")
	{
		onWidgetChilds(w);
		if(visible)
		{
			joinBtn.parse();
		}else{
			joinBtn.setEnabled(false);
		}
		logActiveButtons();
	}else if(clazz=="CGetChipsDlg")
	{
		onWidgetChilds(w);
	}
}

void FTTable::logActiveButtons()
{
	Q_FOREACH(FTActionButton *ab, actions)
	{
		if(ab->enabled())
			qLog(DebugHand)<<ab->prefix()<<" "<<ab->amount();
	}
	if(joinBtn.enabled())
		qLog(DebugHand)<<joinBtn.prefix();
	if(sitinBtn.enabled())
		qLog(DebugHand)<<sitinBtn.prefix();

}


void FTTable::checkCall()
{
	qLog(Info)<<handId()+": <CHECKCALL>";
	if(checkBtn.enabled())
	{
		qLog(Info)<<handId()+": check";
		checkBtn.press();
	}else if(callBtn.enabled())
	{
		qLog(Info)<<handId()+": call "+QString().sprintf("%f",callBtn.amount());
		callBtn.press();
	}else
		qLog(Info)<<(handId()+": no check or call button");
		
}

void FTTable::betRaise(double amount)
{
	qLog(Info)<<handId()+": <BETRAISE>";
	if(betBtn.enabled())
	{
		qLog(Info)<<handId()+": bet";
		betBtn.press();
	}else if(raiseBtn.enabled())
	{
		qLog(Info)<<handId()+": raise "+QString().sprintf("%f",raiseBtn.amount());
		raiseBtn.press();
	}else
		qLog(Info)<<handId()+": no bet or raise button";
		
}
void FTTable::fold()
{
	qLog(Info)<<handId()+": <FOLD>";

	if(foldBtn.enabled())
	{
		foldBtn.press();
	}else
		qLog(Info)<<handId()+":no fold button!";
}

void FTTable::sitout()
{
	qLog(Info)<<handId()+": <SITOUT>";
	if(sitoutBtn.enabled())
	{
		sitoutBtn.press();
	}else
		qLog(Info)<<handId()+":no sitout button!";
}

void FTTable::sitin()
{
	qLog(Info)<<(handId()+": <SITIN>");
	if(sitinBtn.enabled())
	{
		sitinBtn.press();
	}else
		qLog(Info)<<handId()+":no sitin button!";
}

void FTTable::join()
{
	qLog(Info)<<(handId()+": <JOIN>");
	if(joinBtn.enabled())
	{
		joinBtn.press();
	}else
		qLog(Info)<<handId()+":no JOIN button!";
}

void FTTable::postBB()
{
	qLog(Info)<<(handId()+": <POSTBB>");
	if(postBtn.enabled())
	{
		postBtn.press();
	}else
		qLog(Info)<<(handId()+":no post sb/bb button!");
}

void FTTable::waitBB()
{
	qLog(Info)<<(handId()+": <WAITBB>");
	if(waitBBBtn.enabled())
	{
		waitBBBtn.press();
	}else
		qLog(Info)<<(handId()+":no wait sb/bb button!");
}


void FTTable::onPaint(QWidget *widget)
{
}

void FTTable::timerEvent(QTimerEvent *e)
{
	//tables()->sendTableInfo(this);
}