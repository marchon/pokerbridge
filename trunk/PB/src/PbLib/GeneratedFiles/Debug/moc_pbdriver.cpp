/****************************************************************************
** Meta object code from reading C++ file 'pbdriver.h'
**
** Created: Thu 1. Apr 18:03:11 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbdriver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBLobbyDriverProfile[] = {

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

static const char qt_meta_stringdata_PBLobbyDriverProfile[] = {
    "PBLobbyDriverProfile\0"
};

const QMetaObject PBLobbyDriverProfile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBLobbyDriverProfile,
      qt_meta_data_PBLobbyDriverProfile, 0 }
};

const QMetaObject *PBLobbyDriverProfile::metaObject() const
{
    return &staticMetaObject;
}

void *PBLobbyDriverProfile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBLobbyDriverProfile))
        return static_cast<void*>(const_cast< PBLobbyDriverProfile*>(this));
    return QObject::qt_metacast(_clname);
}

int PBLobbyDriverProfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PBLobbyDriver[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBLobbyDriver[] = {
    "PBLobbyDriver\0\0onDisconnected()\0"
};

const QMetaObject PBLobbyDriver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBLobbyDriver,
      qt_meta_data_PBLobbyDriver, 0 }
};

const QMetaObject *PBLobbyDriver::metaObject() const
{
    return &staticMetaObject;
}

void *PBLobbyDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBLobbyDriver))
        return static_cast<void*>(const_cast< PBLobbyDriver*>(this));
    return QObject::qt_metacast(_clname);
}

int PBLobbyDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onDisconnected(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
