/****************************************************************************
** Meta object code from reading C++ file 'rmessagequeue.h'
**
** Created: Mon 29. Mar 21:29:18 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rmessagequeue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rmessagequeue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RMessageQueue[] = {

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
      24,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_RMessageQueue[] = {
    "RMessageQueue\0\0opened()\0closed()\0"
};

const QMetaObject RMessageQueue::staticMetaObject = {
    { &RMessageAdaptor::staticMetaObject, qt_meta_stringdata_RMessageQueue,
      qt_meta_data_RMessageQueue, 0 }
};

const QMetaObject *RMessageQueue::metaObject() const
{
    return &staticMetaObject;
}

void *RMessageQueue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RMessageQueue))
        return static_cast<void*>(const_cast< RMessageQueue*>(this));
    return RMessageAdaptor::qt_metacast(_clname);
}

int RMessageQueue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RMessageAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: opened(); break;
        case 1: closed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void RMessageQueue::opened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RMessageQueue::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
