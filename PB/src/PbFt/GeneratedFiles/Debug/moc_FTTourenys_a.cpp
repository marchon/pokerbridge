/****************************************************************************
** Meta object code from reading C++ file 'FTTourenys_a.h'
**
** Created: Wed 17. Mar 14:32:51 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\FTTourenys_a.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FTTourenys_a.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTourneysAdaptor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      23,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   48,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTTourneysAdaptor[] = {
    "FTTourneysAdaptor\0\0msg\0tourneyInfo(QVariantMap)\0"
    "tourneyId\0tourneyLobbyOpenedEvent(QString)\0"
};

const QMetaObject FTTourneysAdaptor::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_FTTourneysAdaptor,
      qt_meta_data_FTTourneysAdaptor, 0 }
};

const QMetaObject *FTTourneysAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *FTTourneysAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTourneysAdaptor))
        return static_cast<void*>(const_cast< FTTourneysAdaptor*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int FTTourneysAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tourneyInfo((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 1: tourneyLobbyOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FTTourneysAdaptor::tourneyInfo(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
