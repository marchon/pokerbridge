/****************************************************************************
** Meta object code from reading C++ file 'fthandhistory.h'
**
** Created: Sat 13. Mar 18:22:00 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fthandhistory.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fthandhistory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTHandHistory[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   60,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTHandHistory[] = {
    "FTHandHistory\0\0s,info\0"
    "handHistoryEvent(QString,PBHandInfo*)\0"
    "self,s\0onStringAppend(QString,QString)\0"
};

const QMetaObject FTHandHistory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FTHandHistory,
      qt_meta_data_FTHandHistory, 0 }
};

const QMetaObject *FTHandHistory::metaObject() const
{
    return &staticMetaObject;
}

void *FTHandHistory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTHandHistory))
        return static_cast<void*>(const_cast< FTHandHistory*>(this));
    return QObject::qt_metacast(_clname);
}

int FTHandHistory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: handHistoryEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< PBHandInfo*(*)>(_a[2]))); break;
        case 1: onStringAppend((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FTHandHistory::handHistoryEvent(const QString & _t1, PBHandInfo * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
