/****************************************************************************
** Meta object code from reading C++ file 'pbremotetable.h'
**
** Created: Sat 13. Mar 18:21:59 2010
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
    { &QObject::staticMetaObject, qt_meta_stringdata_PBRemoteTable,
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
    return QObject::qt_metacast(_clname);
}

int PBRemoteTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PBRemoteTables[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBRemoteTables[] = {
    "PBRemoteTables\0\0tableId\0onTableOpened(QString)\0"
};

const QMetaObject PBRemoteTables::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBRemoteTables,
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
    return QObject::qt_metacast(_clname);
}

int PBRemoteTables::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onTableOpened((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_PBRemoteLobby[] = {

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

static const char qt_meta_stringdata_PBRemoteLobby[] = {
    "PBRemoteLobby\0"
};

const QMetaObject PBRemoteLobby::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteLobby,
      qt_meta_data_PBRemoteLobby, 0 }
};

const QMetaObject *PBRemoteLobby::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteLobby::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteLobby))
        return static_cast<void*>(const_cast< PBRemoteLobby*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteLobby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PBRemoteLobbies[] = {

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

static const char qt_meta_stringdata_PBRemoteLobbies[] = {
    "PBRemoteLobbies\0"
};

const QMetaObject PBRemoteLobbies::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteLobbies,
      qt_meta_data_PBRemoteLobbies, 0 }
};

const QMetaObject *PBRemoteLobbies::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteLobbies::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteLobbies))
        return static_cast<void*>(const_cast< PBRemoteLobbies*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteLobbies::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
