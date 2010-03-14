/****************************************************************************
** Meta object code from reading C++ file 'ftlist.h'
**
** Created: Sun 14. Mar 04:04:28 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\ftlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTLists[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,    9,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FTLists[] = {
    "FTLists\0\0list\0listUpdatedEvent(FTList*)\0"
};

const QMetaObject FTLists::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTLists,
      qt_meta_data_FTLists, 0 }
};

const QMetaObject *FTLists::metaObject() const
{
    return &staticMetaObject;
}

void *FTLists::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTLists))
        return static_cast<void*>(const_cast< FTLists*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTLists::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: listUpdatedEvent((*reinterpret_cast< FTList*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void FTLists::listUpdatedEvent(FTList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_FTList[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      34,   27,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   27,   59,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTList[] = {
    "FTList\0\0listUpdatedEvent()\0filter\0"
    "clickSig(FTListClicker*)\0int\0"
    "doClick(FTListClicker*)\0"
};

const QMetaObject FTList::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTList,
      qt_meta_data_FTList, 0 }
};

const QMetaObject *FTList::metaObject() const
{
    return &staticMetaObject;
}

void *FTList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTList))
        return static_cast<void*>(const_cast< FTList*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: listUpdatedEvent(); break;
        case 1: clickSig((*reinterpret_cast< FTListClicker*(*)>(_a[1]))); break;
        case 2: { int _r = doClick((*reinterpret_cast< FTListClicker*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FTList::listUpdatedEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FTList::clickSig(FTListClicker * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
