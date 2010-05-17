/****************************************************************************
** Meta object code from reading C++ file 'ftlistclicker.h'
**
** Created: Wed 7. Apr 21:07:10 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\ftlistclicker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftlistclicker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTListClicker[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTListClicker[] = {
    "FTListClicker\0\0list\0onListUpdated(FTList*)\0"
};

const QMetaObject FTListClicker::staticMetaObject = {
    { &FTTask::staticMetaObject, qt_meta_stringdata_FTListClicker,
      qt_meta_data_FTListClicker, 0 }
};

const QMetaObject *FTListClicker::metaObject() const
{
    return &staticMetaObject;
}

void *FTListClicker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTListClicker))
        return static_cast<void*>(const_cast< FTListClicker*>(this));
    return FTTask::qt_metacast(_clname);
}

int FTListClicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onListUpdated((*reinterpret_cast< FTList*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
