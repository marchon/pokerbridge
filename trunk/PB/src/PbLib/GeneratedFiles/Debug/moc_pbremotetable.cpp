/****************************************************************************
** Meta object code from reading C++ file 'pbremotetable.h'
**
** Created: Tue 23. Mar 17:47:36 2010
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
static const uint qt_meta_data_PBRemoteTableAdaptor[] = {

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

static const char qt_meta_stringdata_PBRemoteTableAdaptor[] = {
    "PBRemoteTableAdaptor\0"
};

const QMetaObject PBRemoteTableAdaptor::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteTableAdaptor,
      qt_meta_data_PBRemoteTableAdaptor, 0 }
};

const QMetaObject *PBRemoteTableAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteTableAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteTableAdaptor))
        return static_cast<void*>(const_cast< PBRemoteTableAdaptor*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteTableAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PBRemoteTablesAdaptor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x05,
      69,   60,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      95,   23,   22,   22, 0x09,
     127,  123,   22,   22, 0x09,
     160,   60,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PBRemoteTablesAdaptor[] = {
    "PBRemoteTablesAdaptor\0\0table\0"
    "tableCreatedEvent(QVariantMap)\0tableUrl\0"
    "tableOpenedEvent(QString)\0"
    "l_onNewTableEvent(PBTable*)\0msg\0"
    "onTableCreatedEvent(QVariantMap)\0"
    "onTableOpenedEvent(QString)\0"
};

const QMetaObject PBRemoteTablesAdaptor::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteTablesAdaptor,
      qt_meta_data_PBRemoteTablesAdaptor, 0 }
};

const QMetaObject *PBRemoteTablesAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteTablesAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteTablesAdaptor))
        return static_cast<void*>(const_cast< PBRemoteTablesAdaptor*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteTablesAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tableCreatedEvent((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 1: tableOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: l_onNewTableEvent((*reinterpret_cast< PBTable*(*)>(_a[1]))); break;
        case 3: onTableCreatedEvent((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 4: onTableOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PBRemoteTablesAdaptor::tableCreatedEvent(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PBRemoteTablesAdaptor::tableOpenedEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
