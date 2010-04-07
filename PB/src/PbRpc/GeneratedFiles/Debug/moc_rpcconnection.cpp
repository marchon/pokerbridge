/****************************************************************************
** Meta object code from reading C++ file 'rpcconnection.h'
**
** Created: Thu 25. Mar 16:20:20 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rpcconnection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rpcconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RpcConnection[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      46,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_RpcConnection[] = {
    "RpcConnection\0\0chan\0disconnected(RpcChannel*)\0"
    "connected(RpcChannel*)\0"
};

const QMetaObject RpcConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RpcConnection,
      qt_meta_data_RpcConnection, 0 }
};

const QMetaObject *RpcConnection::metaObject() const
{
    return &staticMetaObject;
}

void *RpcConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RpcConnection))
        return static_cast<void*>(const_cast< RpcConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int RpcConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: disconnected((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 1: connected((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void RpcConnection::disconnected(RpcChannel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RpcConnection::connected(RpcChannel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
