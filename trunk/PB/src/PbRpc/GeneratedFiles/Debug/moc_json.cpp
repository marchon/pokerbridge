/****************************************************************************
** Meta object code from reading C++ file 'json.h'
**
** Created: Sat 13. Mar 18:21:51 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\json.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'json.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JsonReader[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_JsonReader[] = {
    "JsonReader\0\0msg\0parsed(QVariantMap)\0"
};

const QMetaObject JsonReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JsonReader,
      qt_meta_data_JsonReader, 0 }
};

const QMetaObject *JsonReader::metaObject() const
{
    return &staticMetaObject;
}

void *JsonReader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JsonReader))
        return static_cast<void*>(const_cast< JsonReader*>(this));
    return QObject::qt_metacast(_clname);
}

int JsonReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: parsed((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void JsonReader::parsed(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
