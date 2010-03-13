/****************************************************************************
** Meta object code from reading C++ file 'rpcconnection.h'
**
** Created: Sat 13. Mar 18:21:51 2010
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
       9,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   15,   14,   14, 0x05,
      66,   63,   14,   14, 0x05,
      93,   63,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     120,   14,   14,   14, 0x09,
     139,   15,   14,   14, 0x0a,
     180,  176,   14,   14, 0x2a,
     205,   63,   14,   14, 0x0a,
     229,  176,   14,   14, 0x0a,
     265,   63,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RpcConnection[] = {
    "RpcConnection\0\0map,ch\0"
    "incomingMessage(QVariantMap,RpcChannel*)\0"
    "ch\0channelOpened(RpcChannel*)\0"
    "channelClosed(RpcChannel*)\0"
    "unregisterSender()\0"
    "sendMessage(QVariantMap,RpcChannel*)\0"
    "map\0sendMessage(QVariantMap)\0"
    "newChannel(RpcChannel*)\0"
    "channelIncomingMessage(QVariantMap)\0"
    "channelDisconnected(RpcChannel*)\0"
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
        case 0: incomingMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< RpcChannel*(*)>(_a[2]))); break;
        case 1: channelOpened((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 2: channelClosed((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 3: unregisterSender(); break;
        case 4: sendMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< RpcChannel*(*)>(_a[2]))); break;
        case 5: sendMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: newChannel((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 7: channelIncomingMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 8: channelDisconnected((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void RpcConnection::incomingMessage(QVariantMap _t1, RpcChannel * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RpcConnection::channelOpened(RpcChannel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RpcConnection::channelClosed(RpcChannel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
