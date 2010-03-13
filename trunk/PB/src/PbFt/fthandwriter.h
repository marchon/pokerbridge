#ifndef FTHANDWRITER_H
#define FTHANDWRITER_H

class FTHandHistory;
class PBHandInfo;
class FTHandWriter : public QObject
{
	Q_OBJECT;
public:
	FTHandWriter(QObject *parent = 0);

	void subscribe(QObject *history);

	QString historyDir();
	void setHistoryDir(QString dir);

public slots:
	void onHandHistory(const QString &s, PBHandInfo *handInfo);
protected:
	QString _historyDir;
};
#endif