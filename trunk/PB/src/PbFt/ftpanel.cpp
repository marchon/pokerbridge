#include "stdafx.h"
#include "qpblog.h"
#include "ftpanel.h"
#include "fttables.h"
#include "fttable.h"

FTPanel *FTPanel::_instance = NULL;

FTPanel::FTPanel() : QFrame(NULL, 0)
{

   resize(300,200);
   
   textEdit = new QTextEdit( this );

   foldBtn = new QPushButton("F", this);
   connect(foldBtn, SIGNAL(clicked()), this, SLOT(onFoldClicked()));
   checkCallBtn = new QPushButton("X/C", this);
   connect(checkCallBtn, SIGNAL(clicked()), this, SLOT(onCheckCallClicked()));
   betRaiseBtn = new QPushButton("B/R", this);
   connect(betRaiseBtn, SIGNAL(clicked()), this, SLOT(onBetRaiseClicked()));
   amountEdit = new QLineEdit("0",this);
   sitinBtn = new QPushButton("deal", this);
	connect(sitinBtn, SIGNAL(clicked()), this, SLOT(onSitinClicked()));
   sitoutBtn = new QPushButton("sito", this);
   connect(sitoutBtn, SIGNAL(clicked()), this, SLOT(onSitoutClicked()));
   postBtn = new QPushButton("post", this);
   connect(postBtn, SIGNAL(clicked()), this, SLOT(onPostBBClicked()));
   waitBtn = new QPushButton("wait", this);
   connect(waitBtn, SIGNAL(clicked()), this, SLOT(onWaitBBClicked()));
	joinBtn = new QPushButton("join", this);
	connect(joinBtn, SIGNAL(clicked()), this, SLOT(onJoinClicked()));
   closeBtn = new QPushButton("close", this);
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(onCloseClicked()));

   tableCombo = new QComboBox(this);
   
   _tables = 0;

   updateTableCombo();

   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(textEdit);
   
   QHBoxLayout *hLayout = new QHBoxLayout;
   hLayout->addWidget(foldBtn);
   hLayout->addWidget(checkCallBtn);
   hLayout->addWidget(betRaiseBtn);
   hLayout->addWidget(amountEdit);
   layout->addLayout(hLayout);

   QHBoxLayout *h2layout = new QHBoxLayout;
   h2layout->addWidget(postBtn);
   h2layout->addWidget(waitBtn);
   h2layout->addWidget(sitinBtn);
   h2layout->addWidget(sitoutBtn);
   layout->addLayout(h2layout);

   QHBoxLayout *h3layout = new QHBoxLayout;
   h3layout->addWidget(tableCombo);
   h3layout->addWidget(joinBtn);
   h3layout->addWidget(closeBtn);
   layout->addLayout(h3layout);

   setLayout(layout);

   connect(this, SIGNAL(writeLog(QString)),textEdit, SLOT(append(QString)), Qt::QueuedConnection);

   textEdit->setVisible(true);
   show();
}

FTPanel::~FTPanel()
{
}

void FTPanel::updateTableCombo()
{
	tableCombo->clear();
	if(_tables)
	{
		QList<FTTable*> tables = _tables->tables();
		Q_FOREACH(FTTable* tbl, tables)
		{
			tableCombo->addItem(tbl->tableId());
		}
	}
}

void FTPanel::onFoldClicked()
{
	if(table())
		table()->fold();
}


void FTPanel::onCheckCallClicked()
{
	if(table())
		table()->checkCall();
}

void FTPanel::onBetRaiseClicked()
{
	if(table())
		table()->betRaise(amount());
}

void FTPanel::onPostBBClicked()
{
	if(table())
		table()->postBB();
}

void FTPanel::onWaitBBClicked()
{
	if(table())
		table()->waitBB();
}

void FTPanel::onJoinClicked()
{
	if(table())
		table()->join();
}

void FTPanel::onSitoutClicked()
{
	if(table())
		table()->sitout();
}

void FTPanel::onSitinClicked()
{
	if(table())
		table()->sitin();
}

void FTPanel::onCloseClicked()
{
	if(table())
		table()->close();
}

void FTPanel::createInstance()
{
	if(NULL==_instance)
	{
		_instance=new FTPanel();
		qLog(Debug)<<"created FTPanel";
	}
}

void FTPanel::destroyInstance()
{
	FTPanel *instance = _instance;
	if(0!=instance)
	{
		_instance=0;
		delete instance;
		qLog(Debug)<<"destroyed FTPanel";
	}
}

FTPanel* FTPanel::instance()
{
	return _instance;
}

void FTPanel::msgHandler(QtMsgType type, const char *msg)
{
	if(_instance)
		if(type==QtMsgType::QtWarningMsg)
			emit _instance->writeLog(msg);
}

void FTPanel::connectTables(FTTables *tbl)
{
	_tables=tbl;
}

FTTable *FTPanel::table()
{
	QString tableId = tableCombo->currentText();
	return _tables->getTable(tableId);

}

void FTPanel::setAmount(double amount)
{
	amountEdit->setText(QString().sprintf("%f",amount));
}

double FTPanel::amount()
{
	double value=1;
	value = amountEdit->text().toDouble();
	return value;
}

