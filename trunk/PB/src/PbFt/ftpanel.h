#pragma once

class FTTable;

class FTPanel : public QFrame
{
	Q_OBJECT
public:
	FTPanel();
	~FTPanel();
	// logging
	static void msgHandler(QtMsgType type, const char *msg);

	// table control
	void connectTables(FTTables *tables);
	void setAmount(double amount);
	double amount();

	static FTPanel* instance();
	static void createInstance();
	static void destroyInstance();

	void updateTableCombo();
	FTTable *table();
signals:
	void writeLog(QString s);

protected:
	static FTPanel* _instance;
	QTextEdit *textEdit;
	QPushButton *checkCallBtn;
	QPushButton *betRaiseBtn;
	QPushButton *foldBtn;
	QLineEdit *amountEdit;
	QPushButton *postBtn;
	QPushButton *waitBtn;
	QPushButton *sitoutBtn;
	QPushButton *sitinBtn;
	QPushButton *joinBtn;
	QPushButton *closeBtn;
	QComboBox *tableCombo;
	FTTables *_tables;

public slots:
	void onFoldClicked(); 
	void onCheckCallClicked();
	void onBetRaiseClicked();
	void onPostBBClicked();
	void onWaitBBClicked();
	void onSitinClicked();
	void onSitoutClicked();
	void onCloseClicked();
	void onJoinClicked();
};

