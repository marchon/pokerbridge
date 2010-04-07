#ifndef QXLOG_H
#define QXLOG_H

class PB_EXPORT QPBLog
{

public:
	static void addHandler(QtMsgHandler handler);
	static void removeHandler(QtMsgHandler handler);
	
	static void install();
	static void uninstall();

	static void logToFile(const QString &path, QIODevice::OpenMode mode = QIODevice::WriteOnly|QIODevice::Unbuffered);
	static void flushLogFile();
	static QTextStream &ts(const char*cat){ return stream;}
private:
	static void fileLogHandler(QtMsgType type, const char *msg);
	static void handler(QtMsgType type, const char *msg);
private:
	static QSet<QtMsgHandler> handlers;
	static QMutex lock;
	static QtMsgHandler old;
	static QFile logFile;
	static QTextStream stream;
};

inline QDebug qLogInfo(){ return qWarning(); }
inline QDebug qLogError(){ return qWarning(); }
inline QDebug qLogDebug(){ return qDebug(); }
inline QDebug qLog(){return qDebug(); }
inline QDebug qLogDebugNet(){ return qDebug(); }
inline QNoDebug qLogDebugHand(){ return QNoDebug();}
#define qLog(cat) qLog##cat()<<"["<<#cat<<"]"

class QPBDumpFile : public QTextStream
{
public:
	QPBDumpFile(QString name, int flags=QIODevice::WriteOnly|QIODevice::Append){
		QString path=name+QString("%1").arg(GetCurrentProcessId());
		file.setFileName(path);
		file.open((QIODevice::OpenMode)flags);
		setDevice(&file);
	}
	~QPBDumpFile()
	{
		flush();
		file.close();
	}
private:
	QFile file;
};
#endif