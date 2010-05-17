/****************************************************************************
** Meta object code from reading C++ file 'pbremotelobby.h'
**
** Created: Tue 23. Mar 18:05:00 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbremotelobby.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbremotelobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBRemoteLobbyAdaptor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      26,   22,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBRemoteLobbyAdaptor[] = {
    "PBRemoteLobbyAdaptor\0\0msg\0pong(QVariantMap)\0"
};

const QMetaObject PBRemoteLobbyAdaptor::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteLobbyAdaptor,
      qt_meta_data_PBRemoteLobbyAdaptor, 0 }
};

const QMetaObject *PBRemoteLobbyAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteLobbyAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteLobbyAdaptor))
        return static_cast<void*>(const_cast< PBRemoteLobbyAdaptor*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteLobbyAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pong((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_PBRemoteLobbyProxy[] = {

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

static const char qt_meta_stringdata_PBRemoteLobbyProxy[] = {
    "PBRemoteLobbyProxy\0"
};

const QMetaObject PBRemoteLobbyProxy::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteLobbyProxy,
      qt_meta_data_PBRemoteLobbyProxy, 0 }
};

const QMetaObject *PBRemoteLobbyProxy::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteLobbyProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteLobbyProxy))
        return static_cast<void*>(const_cast< PBRemoteLobbyProxy*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteLobbyProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
