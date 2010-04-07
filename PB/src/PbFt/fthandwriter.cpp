#include "stdafx.h"
#include "fthandwriter.h"
#include "fthandhistory.h"
#include "pbhandinfo.h"

FTHandWriter::FTHandWriter(QObject *parent): QObject(parent)
{
}

void FTHandWriter::subscribe(QObject *history)
{
	connect(history,SIGNAL(handHistoryEvent(const QString&,PBHandInfo*)),
		this, SLOT(onHandHistory(const QString&,PBHandInfo*)), Qt::DirectConnection);
}

QString FTHandWriter::historyDir()
{
	return _historyDir;
}

void FTHandWriter::setHistoryDir(QString dir)
{
	_historyDir = dir;
}

void FTHandWriter::onHandHistory(const QString &s, PBHandInfo *hi)
{
	QString fileName = historyDir();

	qLog(DebugHand)<<"onHandHistory "<<fileName;

	if(!fileName.isEmpty())
	{
		QDir().mkpath(fileName);
		fileName.append(QDir().separator());
	}
	fileName.append(QDate::currentDate().toString("yyyyMMdd"));
	fileName.append("-");
	QString gtype = hi->gameFamily();
	gtype.replace(QRegExp("[\\\\\\/]"),"-");
	fileName.append(gtype);
	fileName.append(".txt");
	QFile file(fileName+".txt");
	if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		qLog(Error)<<"Error opening history file "<< fileName;
		return;
	}

	QTextStream ts(&file);
 
	ts << s << endl;

	ts.flush();
	file.close();

	qLog(Error)<<"HAND "+hi->handId()+" written: "+fileName;

//	hemStats->update();
}

