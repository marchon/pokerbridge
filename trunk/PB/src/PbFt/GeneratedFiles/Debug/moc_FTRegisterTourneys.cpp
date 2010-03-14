/****************************************************************************
** Meta object code from reading C++ file 'FTRegisterTourneys.h'
**
** Created: Sat 13. Mar 19:40:54 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\FTRegisterTourneys.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FTRegisterTourneys.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTRegisterTourneys[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x09,
      30,   19,   19,   19, 0x09,
      49,   19,   19,   19, 0x09,
      75,   69,   19,   19, 0x09,
     118,  113,   19,   19, 0x09,
     141,   69,   19,   19, 0x09,
     195,  187,   19,   19, 0x09,
     221,  218,   19,   19, 0x09,
     251,  218,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTRegisterTourneys[] = {
    "FTRegisterTourneys\0\0execute()\0"
    "onTooManyWindows()\0onTourneysUpdated()\0"
    "lobby\0onTourneyLobbyOpened(FTTourneyLobby*)\0"
    "list\0onListUpdated(FTList*)\0"
    "onTourneyLobbyObserveClicked(FTTourneyLobby*)\0"
    "tableId\0onTableOpened(QString)\0wh\0"
    "onLobbyClosing(FTWidgetHook*)\0"
    "onLobbyHooked(FTWidgetHook*)\0"
};

const QMetaObject FTRegisterTourneys::staticMetaObject = {
    { &FTTask::staticMetaObject, qt_meta_stringdata_FTRegisterTourneys,
      qt_meta_data_FTRegisterTourneys, 0 }
};

const QMetaObject *FTRegisterTourneys::metaObject() const
{
    return &staticMetaObject;
}

void *FTRegisterTourneys::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTRegisterTourneys))
        return static_cast<void*>(const_cast< FTRegisterTourneys*>(this));
    return FTTask::qt_metacast(_clname);
}

int FTRegisterTourneys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: execute(); break;
        case 1: onTooManyWindows(); break;
        case 2: onTourneysUpdated(); break;
        case 3: onTourneyLobbyOpened((*reinterpret_cast< FTTourneyLobby*(*)>(_a[1]))); break;
        case 4: onListUpdated((*reinterpret_cast< FTList*(*)>(_a[1]))); break;
        case 5: onTourneyLobbyObserveClicked((*reinterpret_cast< FTTourneyLobby*(*)>(_a[1]))); break;
        case 6: onTableOpened((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: onLobbyClosing((*reinterpret_cast< FTWidgetHook*(*)>(_a[1]))); break;
        case 8: onLobbyHooked((*reinterpret_cast< FTWidgetHook*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
