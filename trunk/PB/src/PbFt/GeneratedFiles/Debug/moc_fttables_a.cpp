/****************************************************************************
** Meta object code from reading C++ file 'fttables_a.h'
**
** Created: Thu 25. Mar 16:20:35 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fttables_a.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fttables_a.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTablesAdaptor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      26,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   52,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTTablesAdaptor[] = {
    "FTTablesAdaptor\0\0tableUrl\0"
    "tableOpenedEvent(QString)\0tableId\0"
    "onTableOpenedEvent(QString)\0"
};

const QMetaObject FTTablesAdaptor::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_FTTablesAdaptor,
      qt_meta_data_FTTablesAdaptor, 0 }
};

const QMetaObject *FTTablesAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *FTTablesAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTablesAdaptor))
        return static_cast<void*>(const_cast< FTTablesAdaptor*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int FTTablesAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tableOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: onTableOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FTTablesAdaptor::tableOpenedEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
