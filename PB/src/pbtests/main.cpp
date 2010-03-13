
#include <QtCore>
#include <qthread.h>
#include <qthread_p.h>
#include "testthread.h"
/*
void startQtThread(void *arg)
{
    QThread *thr = reinterpret_cast<QThread *>(arg);
    QThreadData *data = QThreadData::get2(thr);

    qt_create_tls();
    TlsSetValue(qt_current_thread_data_tls_index, data);

    QThread::setTerminationEnabled(false);

    data->quitNow = false;
    // ### TODO: allow the user to create a custom event dispatcher
    createEventDispatcher(data);

#if !defined(QT_NO_DEBUG) && defined(Q_CC_MSVC) && !defined(Q_OS_WINCE)
    // sets the name of the current thread.
    QByteArray objectName = thr->objectName().toLocal8Bit();
    qt_set_thread_name((HANDLE)-1,
                       objectName.isEmpty() ?
                       thr->metaObject()->className() : objectName.constData());
#endif

    emit thr->started();
    QThread::setTerminationEnabled(true);
    thr->run();

    finish(arg);
    return 0;
}

void finishQtThread(void *arg, bool lockAnyway)
{
    QThread *thr = reinterpret_cast<QThread *>(arg);
    QThreadPrivate *d = thr->d_func();

    if (lockAnyway)
        d->mutex.lock();
    d->priority = QThread::InheritPriority;
    d->running = false;
    d->finished = true;
    if (d->terminated)
        emit thr->terminated();
    d->terminated = false;
    emit thr->finished();

    if (d->data->eventDispatcher) {
        d->data->eventDispatcher->closingDown();
        QAbstractEventDispatcher *eventDispatcher = d->data->eventDispatcher;
        d->data->eventDispatcher = 0;
        delete eventDispatcher;
    }

    QThreadStorageData::finish(reinterpret_cast<void **>(&d->data->tls));

    if (!d->waiters) {
        CloseHandle(d->handle);
        d->handle = 0;
    }

    d->id = 0;

    if (lockAnyway)
        d->mutex.unlock();
}


int main(int argc, char *argv[])
{
	MyThread thr;
	QThreadPrivate::start(&thr);

	QCoreApplication a(argc, argv);
//	QThread *thr = QThread::currentThread();
	
	QTimer timer;
	timer.setInterval(1000);
	timer.start();

	return 0;//return a.exec();
}
*/
void main()
{
}