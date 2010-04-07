/****************************************************************************
** Meta object code from reading C++ file 'pbseats.h'
**
** Created: Fri 2. Apr 21:30:26 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbseats.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbseats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBSeats[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   12, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      12,    8, 0x02095103,
      23,    8, 0x02095001,

       0        // eod
};

static const char qt_meta_stringdata_PBSeats[] = {
    "PBSeats\0int\0buttonSeat\0seatsCount\0"
};

const QMetaObject PBSeats::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBSeats,
      qt_meta_data_PBSeats, 0 }
};

const QMetaObject *PBSeats::metaObject() const
{
    return &staticMetaObject;
}

void *PBSeats::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBSeats))
        return static_cast<void*>(const_cast< PBSeats*>(this));
    return QObject::qt_metacast(_clname);
}

int PBSeats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = buttonSeat(); break;
        case 1: *reinterpret_cast< int*>(_v) = seatsCount(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setButtonSeat(*reinterpret_cast< int*>(_v)); break;
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
