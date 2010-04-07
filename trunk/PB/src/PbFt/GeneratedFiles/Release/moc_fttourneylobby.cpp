/****************************************************************************
** Meta object code from reading C++ file 'fttourneylobby.h'
**
** Created: Fri 2. Apr 21:30:32 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fttourneylobby.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fttourneylobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTourneyLobby[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      29,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   15,   15,   15, 0x0a,
      58,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTTourneyLobby[] = {
    "FTTourneyLobby\0\0observeSig()\0"
    "observeClicked()\0doObserve()\0"
    "tourneyLobbyClosing(FTWidgetHook*)\0"
};

const QMetaObject FTTourneyLobby::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTTourneyLobby,
      qt_meta_data_FTTourneyLobby, 0 }
};

const QMetaObject *FTTourneyLobby::metaObject() const
{
    return &staticMetaObject;
}

void *FTTourneyLobby::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTourneyLobby))
        return static_cast<void*>(const_cast< FTTourneyLobby*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTTourneyLobby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: observeSig(); break;
        case 1: observeClicked(); break;
        case 2: doObserve(); break;
        case 3: tourneyLobbyClosing((*reinterpret_cast< FTWidgetHook*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FTTourneyLobby::observeSig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FTTourneyLobby::observeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
