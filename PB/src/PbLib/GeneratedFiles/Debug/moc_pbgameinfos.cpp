/****************************************************************************
** Meta object code from reading C++ file 'pbgameinfos.h'
**
** Created: Fri 2. Apr 19:43:14 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbgameinfos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbgameinfos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBGameInfos[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   13,   12,   12, 0x0a,
      43,   13,   39,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBGameInfos[] = {
    "PBGameInfos\0\0msg\0onGameInfo(RMessage*)\0"
    "int\0priGameInfo(RMessage*)\0"
};

const QMetaObject PBGameInfos::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBGameInfos,
      qt_meta_data_PBGameInfos, 0 }
};

const QMetaObject *PBGameInfos::metaObject() const
{
    return &staticMetaObject;
}

void *PBGameInfos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBGameInfos))
        return static_cast<void*>(const_cast< PBGameInfos*>(this));
    return QObject::qt_metacast(_clname);
}

int PBGameInfos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onGameInfo((*reinterpret_cast< RMessage*(*)>(_a[1]))); break;
        case 1: { int _r = priGameInfo((*reinterpret_cast< RMessage*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
