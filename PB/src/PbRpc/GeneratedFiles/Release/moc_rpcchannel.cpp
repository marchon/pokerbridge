/****************************************************************************
** Meta object code from reading C++ file 'rpcchannel.h'
**
** Created: Sun 14. Mar 04:04:14 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rpcchannel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rpcchannel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RpcChannel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      24,   11,   11,   11, 0x0a,
      40,   36,   11,   11, 0x0a,
      65,   36,   11,   11, 0x0a,
      89,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RpcChannel[] = {
    "RpcChannel\0\0readyRead()\0connected()\0"
    "msg\0sendMessage(QVariantMap)\0"
    "newMessage(QVariantMap)\0socketDisconnected()\0"
};

const QMetaObject RpcChannel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RpcChannel,
      qt_meta_data_RpcChannel, 0 }
};

const QMetaObject *RpcChannel::metaObject() const
{
    return &staticMetaObject;
}

void *RpcChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RpcChannel))
        return static_cast<void*>(const_cast< RpcChannel*>(this));
    return QObject::qt_metacast(_clname);
}

int RpcChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyRead(); break;
        case 1: connected(); break;
        case 2: sendMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: newMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 4: socketDisconnected(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
