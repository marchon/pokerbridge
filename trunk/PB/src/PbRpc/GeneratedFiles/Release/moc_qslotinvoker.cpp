/****************************************************************************
** Meta object code from reading C++ file 'qslotinvoker.h'
**
** Created: Thu 11. Mar 14:41:55 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\qslotinvoker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qslotinvoker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSlotInvoker[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      28,   23,   14,   13, 0x0a,
      52,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSlotInvoker[] = {
    "QSlotInvoker\0\0QVariant\0args\0"
    "invoke(QList<QVariant>)\0receiverDestroyed()\0"
};

const QMetaObject QSlotInvoker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSlotInvoker,
      qt_meta_data_QSlotInvoker, 0 }
};

const QMetaObject *QSlotInvoker::metaObject() const
{
    return &staticMetaObject;
}

void *QSlotInvoker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSlotInvoker))
        return static_cast<void*>(const_cast< QSlotInvoker*>(this));
    return QObject::qt_metacast(_clname);
}

int QSlotInvoker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QVariant _r = invoke((*reinterpret_cast< const QList<QVariant>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 1: receiverDestroyed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
