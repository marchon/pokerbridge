/****************************************************************************
** Meta object code from reading C++ file 'pbtourney.h'
**
** Created: Fri 2. Apr 21:30:24 2010
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
       0,    0, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      30,   14, 0x0009510b,
      51,   44, 0x06095103,
      57,   44, 0x06095103,
      70,   62, 0x0a095103,

 // enums: name, flags, count, data

 // enum data: key, value

       0        // eod
};

static const char qt_meta_stringdata_PBTourneyInfo[] = {
    "PBTourneyInfo\0PBTourneyStatus\0"
    "tourneyStatus\0double\0buyIn\0rake\0QString\0"
    "tourneyId\0"
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
        case 0: *reinterpret_cast< PBTourneyStatus*>(_v) = tourneyStatus(); break;
        case 1: *reinterpret_cast< double*>(_v) = buyIn(); break;
        case 2: *reinterpret_cast< double*>(_v) = rake(); break;
        case 3: *reinterpret_cast< QString*>(_v) = tourneyId(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTourneyStatus(*reinterpret_cast< PBTourneyStatus*>(_v)); break;
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
static const uint qt_meta_data_PBTourney[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   12, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      26,   10, 0x0009510b,
      48,   40, 0x0a095103,
      58,   40, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_PBTourney[] = {
    "PBTourney\0PBTourneyStatus\0tourneyStatus\0"
    "QString\0tourneyId\0siteId\0"
};

const QMetaObject PBTourney::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBTourney,
      qt_meta_data_PBTourney, 0 }
};

const QMetaObject *PBTourney::metaObject() const
{
    return &staticMetaObject;
}

void *PBTourney::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBTourney))
        return static_cast<void*>(const_cast< PBTourney*>(this));
    return QObject::qt_metacast(_clname);
}

int PBTourney::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< PBTourneyStatus*>(_v) = tourneyStatus(); break;
        case 1: *reinterpret_cast< QString*>(_v) = tourneyId(); break;
        case 2: *reinterpret_cast< QString*>(_v) = siteId(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTourneyStatus(*reinterpret_cast< PBTourneyStatus*>(_v)); break;
        case 1: setTourneyId(*reinterpret_cast< QString*>(_v)); break;
        case 2: setSiteId(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
static const uint qt_meta_data_PBTourneys[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      44,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PBTourneys[] = {
    "PBTourneys\0\0trn\0newTourneyEvent(PBTourney*)\0"
    "tourneyUpdatedEvent(PBTourney*)\0"
};

const QMetaObject PBTourneys::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBTourneys,
      qt_meta_data_PBTourneys, 0 }
};

const QMetaObject *PBTourneys::metaObject() const
{
    return &staticMetaObject;
}

void *PBTourneys::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBTourneys))
        return static_cast<void*>(const_cast< PBTourneys*>(this));
    return QObject::qt_metacast(_clname);
}

int PBTourneys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newTourneyEvent((*reinterpret_cast< PBTourney*(*)>(_a[1]))); break;
        case 1: tourneyUpdatedEvent((*reinterpret_cast< PBTourney*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PBTourneys::newTourneyEvent(PBTourney * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PBTourneys::tourneyUpdatedEvent(PBTourney * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
