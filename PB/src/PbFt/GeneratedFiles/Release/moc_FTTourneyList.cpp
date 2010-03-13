/****************************************************************************
** Meta object code from reading C++ file 'FTTourneyList.h'
**
** Created: Thu 11. Mar 14:42:03 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\FTTourneyList.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FTTourneyList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTourneyList[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTTourneyList[] = {
    "FTTourneyList\0\0tourneysUpdated()\0"
    "onListUpdated()\0"
};

const QMetaObject FTTourneyList::staticMetaObject = {
    { &FTList::staticMetaObject, qt_meta_stringdata_FTTourneyList,
      qt_meta_data_FTTourneyList, 0 }
};

const QMetaObject *FTTourneyList::metaObject() const
{
    return &staticMetaObject;
}

void *FTTourneyList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTourneyList))
        return static_cast<void*>(const_cast< FTTourneyList*>(this));
    return FTList::qt_metacast(_clname);
}

int FTTourneyList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTList::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tourneysUpdated(); break;
        case 1: onListUpdated(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FTTourneyList::tourneysUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
