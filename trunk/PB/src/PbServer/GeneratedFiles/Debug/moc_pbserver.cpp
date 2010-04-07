/****************************************************************************
** Meta object code from reading C++ file 'pbserver.h'
**
** Created: Mon 29. Mar 17:08:49 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBServer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBServer[] = {
    "PBServer\0\0queue\0queueOpened(RMessageQueue*)\0"
};

const QMetaObject PBServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBServer,
      qt_meta_data_PBServer, 0 }
};

const QMetaObject *PBServer::metaObject() const
{
    return &staticMetaObject;
}

void *PBServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBServer))
        return static_cast<void*>(const_cast< PBServer*>(this));
    return QObject::qt_metacast(_clname);
}

int PBServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: queueOpened((*reinterpret_cast< RMessageQueue*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
