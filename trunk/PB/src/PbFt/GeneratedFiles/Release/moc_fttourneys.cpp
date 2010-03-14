/****************************************************************************
** Meta object code from reading C++ file 'fttourneys.h'
**
** Created: Sun 14. Mar 04:04:27 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fttourneys.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fttourneys.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTourneys[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x05,
      59,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FTTourneys[] = {
    "FTTourneys\0\0lobby\0"
    "tourneyLobbyOpenedEvent(FTTourneyLobby*)\0"
    "tourneyLobbyObserveClickedEvent(FTTourneyLobby*)\0"
};

const QMetaObject FTTourneys::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTTourneys,
      qt_meta_data_FTTourneys, 0 }
};

const QMetaObject *FTTourneys::metaObject() const
{
    return &staticMetaObject;
}

void *FTTourneys::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTourneys))
        return static_cast<void*>(const_cast< FTTourneys*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTTourneys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tourneyLobbyOpenedEvent((*reinterpret_cast< FTTourneyLobby*(*)>(_a[1]))); break;
        case 1: tourneyLobbyObserveClickedEvent((*reinterpret_cast< FTTourneyLobby*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FTTourneys::tourneyLobbyOpenedEvent(FTTourneyLobby * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FTTourneys::tourneyLobbyObserveClickedEvent(FTTourneyLobby * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
