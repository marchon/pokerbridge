/****************************************************************************
** Meta object code from reading C++ file 'pbremotetable.h'
**
** Created: Mon 22. Mar 21:15:17 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbremotetable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbremotetable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBRemoteTable[] = {

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

static const char qt_meta_stringdata_PBRemoteTable[] = {
    "PBRemoteTable\0"
};

const QMetaObject PBRemoteTable::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteTable,
      qt_meta_data_PBRemoteTable, 0 }
};

const QMetaObject *PBRemoteTable::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteTable))
        return static_cast<void*>(const_cast< PBRemoteTable*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PBRemoteTables[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x05,
      62,   53,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PBRemoteTables[] = {
    "PBRemoteTables\0\0table\0"
    "tableCreatedEvent(QVariantMap)\0tableUrl\0"
    "tableOpenedEvent(QString)\0"
};

const QMetaObject PBRemoteTables::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteTables,
      qt_meta_data_PBRemoteTables, 0 }
};

const QMetaObject *PBRemoteTables::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteTables::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteTables))
        return static_cast<void*>(const_cast< PBRemoteTables*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteTables::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tableCreatedEvent((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 1: tableOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PBRemoteTables::tableCreatedEvent(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PBRemoteTables::tableOpenedEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
