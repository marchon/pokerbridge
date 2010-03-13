/****************************************************************************
** Meta object code from reading C++ file 'pbtable.h'
**
** Created: Thu 11. Mar 14:41:56 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbtable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbtable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBTable[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   12, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      17,    8, 0x0009510b,
      33,   24, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_PBTable[] = {
    "PBTable\0PBHandId\0handId\0PBSeats*\0seats\0"
};

const QMetaObject PBTable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBTable,
      qt_meta_data_PBTable, 0 }
};

const QMetaObject *PBTable::metaObject() const
{
    return &staticMetaObject;
}

void *PBTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBTable))
        return static_cast<void*>(const_cast< PBTable*>(this));
    return QObject::qt_metacast(_clname);
}

int PBTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< PBHandId*>(_v) = handId(); break;
        case 1: *reinterpret_cast< PBSeats**>(_v) = seats(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setHandId(*reinterpret_cast< PBHandId*>(_v)); break;
        case 1: setSeats(*reinterpret_cast< PBSeats**>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
