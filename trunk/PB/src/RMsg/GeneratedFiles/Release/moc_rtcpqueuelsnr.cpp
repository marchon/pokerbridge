/****************************************************************************
** Meta object code from reading C++ file 'rtcpqueuelsnr.h'
**
** Created: Fri 2. Apr 21:30:11 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rtcpqueuelsnr.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtcpqueuelsnr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTcpQueueListener[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   18,   18,   18, 0x09,
      65,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RTcpQueueListener[] = {
    "RTcpQueueListener\0\0q\0queueOpened(RMessageQueue*)\0"
    "newConnection()\0_queueOpened()\0"
};

const QMetaObject RTcpQueueListener::staticMetaObject = {
    { &RMessageQueue::staticMetaObject, qt_meta_stringdata_RTcpQueueListener,
      qt_meta_data_RTcpQueueListener, 0 }
};

const QMetaObject *RTcpQueueListener::metaObject() const
{
    return &staticMetaObject;
}

void *RTcpQueueListener::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTcpQueueListener))
        return static_cast<void*>(const_cast< RTcpQueueListener*>(this));
    return RMessageQueue::qt_metacast(_clname);
}

int RTcpQueueListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RMessageQueue::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: queueOpened((*reinterpret_cast< RMessageQueue*(*)>(_a[1]))); break;
        case 1: newConnection(); break;
        case 2: _queueOpened(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RTcpQueueListener::queueOpened(RMessageQueue * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
