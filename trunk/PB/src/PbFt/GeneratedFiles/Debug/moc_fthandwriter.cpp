/****************************************************************************
** Meta object code from reading C++ file 'fthandwriter.h'
**
** Created: Mon 29. Mar 21:29:44 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fthandwriter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fthandwriter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTHandWriter[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      25,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTHandWriter[] = {
    "FTHandWriter\0\0s,handInfo\0"
    "onHandHistory(QString,PBHandInfo*)\0"
};

const QMetaObject FTHandWriter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FTHandWriter,
      qt_meta_data_FTHandWriter, 0 }
};

const QMetaObject *FTHandWriter::metaObject() const
{
    return &staticMetaObject;
}

void *FTHandWriter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTHandWriter))
        return static_cast<void*>(const_cast< FTHandWriter*>(this));
    return QObject::qt_metacast(_clname);
}

int FTHandWriter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onHandHistory((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< PBHandInfo*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
