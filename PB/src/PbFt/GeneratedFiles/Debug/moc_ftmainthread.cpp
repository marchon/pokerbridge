/****************************************************************************
** Meta object code from reading C++ file 'ftmainthread.h'
**
** Created: Mon 29. Mar 21:29:44 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\ftmainthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftmainthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTMainThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_FTMainThread[] = {
    "FTMainThread\0"
};

const QMetaObject FTMainThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FTMainThread,
      qt_meta_data_FTMainThread, 0 }
};

const QMetaObject *FTMainThread::metaObject() const
{
    return &staticMetaObject;
}

void *FTMainThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTMainThread))
        return static_cast<void*>(const_cast< FTMainThread*>(this));
    return QThread::qt_metacast(_clname);
}

int FTMainThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
