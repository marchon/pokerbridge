/****************************************************************************
** Meta object code from reading C++ file 'rtcpmessagequeue.h'
**
** Created: Fri 2. Apr 21:30:12 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rtcpmessagequeue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtcpmessagequeue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTcpMessageQueue[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      30,   17,   17,   17, 0x0a,
      42,   17,   17,   17, 0x0a,
      61,   57,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RTcpMessageQueue[] = {
    "RTcpMessageQueue\0\0readyRead()\0connected()\0"
    "disconnected()\0msg\0messageReceived(QVariantMap)\0"
};

const QMetaObject RTcpMessageQueue::staticMetaObject = {
    { &RMessageQueue::staticMetaObject, qt_meta_stringdata_RTcpMessageQueue,
      qt_meta_data_RTcpMessageQueue, 0 }
};

const QMetaObject *RTcpMessageQueue::metaObject() const
{
    return &staticMetaObject;
}

void *RTcpMessageQueue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTcpMessageQueue))
        return static_cast<void*>(const_cast< RTcpMessageQueue*>(this));
    return RMessageQueue::qt_metacast(_clname);
}

int RTcpMessageQueue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RMessageQueue::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyRead(); break;
        case 1: connected(); break;
        case 2: disconnected(); break;
        case 3: messageReceived((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
