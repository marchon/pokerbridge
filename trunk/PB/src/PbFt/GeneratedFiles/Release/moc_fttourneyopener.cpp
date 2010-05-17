/****************************************************************************
** Meta object code from reading C++ file 'fttourneyopener.h'
**
** Created: Thu 8. Apr 19:38:00 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fttourneyopener.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fttourneyopener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTourneyOpener[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x09,
      44,   17,   16,   16, 0x09,
      73,   70,   16,   16, 0x09,
     121,  111,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTTourneyOpener[] = {
    "FTTourneyOpener\0\0msg\0onOpenTable(RMessage*)\0"
    "onCloseTourney(RMessage*)\0tl\0"
    "onTourneyLobbyOpened(FTTourneyLobby*)\0"
    "tourneyId\0onTourneyLobbyClosed(QString)\0"
};

const QMetaObject FTTourneyOpener::staticMetaObject = {
    { &FTListClicker::staticMetaObject, qt_meta_stringdata_FTTourneyOpener,
      qt_meta_data_FTTourneyOpener, 0 }
};

const QMetaObject *FTTourneyOpener::metaObject() const
{
    return &staticMetaObject;
}

void *FTTourneyOpener::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTourneyOpener))
        return static_cast<void*>(const_cast< FTTourneyOpener*>(this));
    return FTListClicker::qt_metacast(_clname);
}

int FTTourneyOpener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTListClicker::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onOpenTable((*reinterpret_cast< RMessage*(*)>(_a[1]))); break;
        case 1: onCloseTourney((*reinterpret_cast< RMessage*(*)>(_a[1]))); break;
        case 2: onTourneyLobbyOpened((*reinterpret_cast< FTTourneyLobby*(*)>(_a[1]))); break;
        case 3: onTourneyLobbyClosed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
