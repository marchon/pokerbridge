/****************************************************************************
** Meta object code from reading C++ file 'pbsite.h'
**
** Created: Tue 23. Mar 14:39:32 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbsite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbsite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBSite[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,    8,    7,    7, 0x0a,
      40,    8,    7,    7, 0x0a,
      73,   69,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBSite[] = {
    "PBSite\0\0ch\0onChannelOpened(RpcChannel*)\0"
    "onChannelClosed(RpcChannel*)\0url\0"
    "onRemoteLobbyConnect(RpcUrl&)\0"
};

const QMetaObject PBSite::staticMetaObject = {
    { &PBRemoteLobby::staticMetaObject, qt_meta_stringdata_PBSite,
      qt_meta_data_PBSite, 0 }
};

const QMetaObject *PBSite::metaObject() const
{
    return &staticMetaObject;
}

void *PBSite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBSite))
        return static_cast<void*>(const_cast< PBSite*>(this));
    return PBRemoteLobby::qt_metacast(_clname);
}

int PBSite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PBRemoteLobby::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onChannelOpened((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 1: onChannelClosed((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 2: onRemoteLobbyConnect((*reinterpret_cast< RpcUrl(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
