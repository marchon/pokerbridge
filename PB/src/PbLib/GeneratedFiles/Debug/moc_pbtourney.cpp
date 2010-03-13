/****************************************************************************
** Meta object code from reading C++ file 'pbtourney.h'
**
** Created: Sat 13. Mar 18:21:54 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbtourney.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbtourney.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBTourneyInfo[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   12, // properties
       1,   24, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      28,   14, 0x0009510b,
      49,   42, 0x06095103,
      55,   42, 0x06095103,
      68,   60, 0x0a095103,

 // enums: name, flags, count, data
      14, 0x0,    3,   28,

 // enum data: key, value
      78, uint(PBTourneyInfo::Registering),
      90, uint(PBTourneyInfo::Running),
      98, uint(PBTourneyInfo::Completed),

       0        // eod
};

static const char qt_meta_stringdata_PBTourneyInfo[] = {
    "PBTourneyInfo\0TourneyStatus\0tourneyStatus\0"
    "double\0buyIn\0rake\0QString\0tourneyId\0"
    "Registering\0Running\0Completed\0"
};

const QMetaObject PBTourneyInfo::staticMetaObject = {
    { &PBGameInfo::staticMetaObject, qt_meta_stringdata_PBTourneyInfo,
      qt_meta_data_PBTourneyInfo, 0 }
};

const QMetaObject *PBTourneyInfo::metaObject() const
{
    return &staticMetaObject;
}

void *PBTourneyInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBTourneyInfo))
        return static_cast<void*>(const_cast< PBTourneyInfo*>(this));
    return PBGameInfo::qt_metacast(_clname);
}

int PBTourneyInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PBGameInfo::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< TourneyStatus*>(_v) = tourneyStatus(); break;
        case 1: *reinterpret_cast< double*>(_v) = buyIn(); break;
        case 2: *reinterpret_cast< double*>(_v) = rake(); break;
        case 3: *reinterpret_cast< QString*>(_v) = tourneyId(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTourneyStatus(*reinterpret_cast< TourneyStatus*>(_v)); break;
        case 1: setBuyIn(*reinterpret_cast< double*>(_v)); break;
        case 2: setRake(*reinterpret_cast< double*>(_v)); break;
        case 3: setTourneyId(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
