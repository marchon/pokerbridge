#ifndef FTHISTORY_H
#define FTHISTORY_H

class PBHandInfo;
class FTHandHistory : public QObject
{
	Q_OBJECT
public:
	FTHandHistory(QObject *parent=0);

	static FTHandHistory *instance();
	bool parseHandInfo(const QString &history, PBHandInfo *result);
public slots:
	void onStringAppend(const QString &self, const QString &s);

signals:
	void handHistoryEvent(const QString &s, PBHandInfo *info);
};
#endif