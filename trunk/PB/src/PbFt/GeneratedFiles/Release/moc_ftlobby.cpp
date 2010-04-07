/****************************************************************************
** Meta object code from reading C++ file 'ftlobby.h'
**
** Created: Fri 2. Apr 21:30:32 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\ftlobby.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftlobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTLobby[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   26,    8,    8, 0x0a,
      55,   50,    8,    8, 0x0a,
      83,   50,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTLobby[] = {
    "FTLobby\0\0tooManyWindows()\0msg\0"
    "onConfig(RMessage*)\0list\0"
    "onListUpdatedEvent(FTList*)\0"
    "onPaintDoneEvent(FTList*)\0"
};

const QMetaObject FTLobby::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTLobby,
      qt_meta_data_FTLobby, 0 }
};

const QMetaObject *FTLobby::metaObject() const
{
    return &staticMetaObject;
}

void *FTLobby::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTLobby))
        return static_cast<void*>(const_cast< FTLobby*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTLobby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tooManyWindows(); break;
        case 1: onConfig((*reinterpret_cast< RMessage*(*)>(_a[1]))); break;
        case 2: onListUpdatedEvent((*reinterpret_cast< FTList*(*)>(_a[1]))); break;
        case 3: onPaintDoneEvent((*reinterpret_cast< FTList*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FTLobby::tooManyWindows()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
