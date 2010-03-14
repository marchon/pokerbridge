/****************************************************************************
** Meta object code from reading C++ file 'rpclistener.h'
**
** Created: Sun 14. Mar 04:04:14 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rpclistener.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rpclistener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RpcListener[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   12,   12,   12, 0x08,
      81,   77,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RpcListener[] = {
    "RpcListener\0\0msg,ch\0"
    "incomingMessage(QVariantMap,RpcChannel*)\0"
    "newConnection()\0msg\0connNewMessage(QVariantMap)\0"
};

const QMetaObject RpcListener::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RpcListener,
      qt_meta_data_RpcListener, 0 }
};

const QMetaObject *RpcListener::metaObject() const
{
    return &staticMetaObject;
}

void *RpcListener::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RpcListener))
        return static_cast<void*>(const_cast< RpcListener*>(this));
    return QObject::qt_metacast(_clname);
}

int RpcListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: incomingMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< RpcChannel*(*)>(_a[2]))); break;
        case 1: newConnection(); break;
        case 2: connNewMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RpcListener::incomingMessage(QVariantMap _t1, RpcChannel * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
