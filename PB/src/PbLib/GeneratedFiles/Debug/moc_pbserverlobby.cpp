/****************************************************************************
** Meta object code from reading C++ file 'pbserverlobby.h'
**
** Created: Tue 23. Mar 18:34:23 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbserverlobby.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbserverlobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBServerLobbyAdaptor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      34,   22,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBServerLobbyAdaptor[] = {
    "PBServerLobbyAdaptor\0\0remoteLobby\0"
    "remoteLobbyConnect(QString)\0"
};

const QMetaObject PBServerLobbyAdaptor::staticMetaObject = {
    { &PBRemoteLobbyAdaptor::staticMetaObject, qt_meta_stringdata_PBServerLobbyAdaptor,
      qt_meta_data_PBServerLobbyAdaptor, 0 }
};

const QMetaObject *PBServerLobbyAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *PBServerLobbyAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBServerLobbyAdaptor))
        return static_cast<void*>(const_cast< PBServerLobbyAdaptor*>(this));
    return PBRemoteLobbyAdaptor::qt_metacast(_clname);
}

int PBServerLobbyAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PBRemoteLobbyAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: remoteLobbyConnect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
