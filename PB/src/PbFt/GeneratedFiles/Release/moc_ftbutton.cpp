/****************************************************************************
** Meta object code from reading C++ file 'ftbutton.h'
**
** Created: Sun 14. Mar 04:04:28 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\ftbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_FTButton[] = {
    "FTButton\0"
};

const QMetaObject FTButton::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTButton,
      qt_meta_data_FTButton, 0 }
};

const QMetaObject *FTButton::metaObject() const
{
    return &staticMetaObject;
}

void *FTButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTButton))
        return static_cast<void*>(const_cast< FTButton*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FTLabel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_FTLabel[] = {
    "FTLabel\0"
};

const QMetaObject FTLabel::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTLabel,
      qt_meta_data_FTLabel, 0 }
};

const QMetaObject *FTLabel::metaObject() const
{
    return &staticMetaObject;
}

void *FTLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTLabel))
        return static_cast<void*>(const_cast< FTLabel*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
