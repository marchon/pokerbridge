#include "stdafx.h"
#include "qpblog.h"

QSet<QtMsgHandler> QPBLog::handlers;
QMutex QPBLog::lock;
QtMsgHandler QPBLog::old = 0;
QFile QPBLog::logFile;
QTextStream QPBLog::stream;

static void aBetterMessageHandler(QtMsgType type, const char *msg)
{
#ifdef Q_OS_WIN32
    // Output for DebugView
    QString fstr(msg);
    OutputDebugString((fstr + "\r\n").utf16());
#endif
    fprintf(stdout, "%s\r\n", msg);
    fflush(stdout);

    if ( type == QtFatalMsg )
        abort();
}
 

void QPBLog::addHandler(QtMsgHandler handler)
{
	lock.lock();
	handlers.insert(handler);
	lock.unlock();
}

void QPBLog::removeHandler(QtMsgHandler handler)
{
	lock.lock();
	handlers.remove(handler);
	lock.unlock();
}

void QPBLog::handler(QtMsgType type, const char *msg)
{
	for(QSet<QtMsgHandler>::ConstIterator it = handlers.begin(); it!= handlers.end(); it++)
	{
		QtMsgHandler h = (*it);
		h(type, msg);
	}
}

void QPBLog::logToFile(const QString &path, QIODevice::OpenMode mode)
{
	logFile.setFileName(path);
	if(!logFile.open(mode))
		qWarning()<<"QPBLog: failed to open file \""<<path<<"\","<<logFile.errorString();
	else
	{
		addHandler(fileLogHandler);
		stream.setDevice(&logFile);
	}
}

void QPBLog::install()
{
	old = qInstallMsgHandler(handler);
	if(0!=old)
		addHandler(old);
	else
		addHandler(aBetterMessageHandler);
}

void QPBLog::uninstall()
{
	qInstallMsgHandler(old);
}

void QPBLog::flushLogFile()
{
	logFile.flush();
}

void QPBLog::fileLogHandler(QtMsgType type, const char *msg)
{
	Q_ASSERT(logFile.isOpen());
	Q_ASSERT(logFile.isWritable());
	uint len = qstrlen(msg);
	logFile.write(msg, len);
	logFile.write("\r\n",2);
}
 
