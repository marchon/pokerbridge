/****************************************************************************
** Meta object code from reading C++ file 'pbremotetourneys.h'
**
** Created: Tue 23. Mar 19:56:58 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbremotetourneys.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbremotetourneys.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBRemoteTourneysAdaptor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      31,   25,   24,   24, 0x05,
      68,   64,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,   98,   24,   24, 0x09,
     138,   98,   24,   24, 0x09,
     174,   64,   24,   24, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PBRemoteTourneysAdaptor[] = {
    "PBRemoteTourneysAdaptor\0\0table\0"
    "tourneyCreatedEvent(QVariantMap)\0msg\0"
    "tourneyInfoEvent(QVariantMap)\0tourney\0"
    "l_onNewTourneyEvent(PBTourney*)\0"
    "l_onTourneyUpdatedEvent(PBTourney*)\0"
    "onTourneyInfoEvent(QVariantMap)\0"
};

const QMetaObject PBRemoteTourneysAdaptor::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteTourneysAdaptor,
      qt_meta_data_PBRemoteTourneysAdaptor, 0 }
};

const QMetaObject *PBRemoteTourneysAdaptor::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteTourneysAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteTourneysAdaptor))
        return static_cast<void*>(const_cast< PBRemoteTourneysAdaptor*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteTourneysAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tourneyCreatedEvent((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 1: tourneyInfoEvent((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 2: l_onNewTourneyEvent((*reinterpret_cast< PBTourney*(*)>(_a[1]))); break;
        case 3: l_onTourneyUpdatedEvent((*reinterpret_cast< PBTourney*(*)>(_a[1]))); break;
        case 4: onTourneyInfoEvent((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PBRemoteTourneysAdaptor::tourneyCreatedEvent(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PBRemoteTourneysAdaptor::tourneyInfoEvent(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_PBRemoteTourneysProxy[] = {

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

static const char qt_meta_stringdata_PBRemoteTourneysProxy[] = {
    "PBRemoteTourneysProxy\0"
};

const QMetaObject PBRemoteTourneysProxy::staticMetaObject = {
    { &RpcAdaptor::staticMetaObject, qt_meta_stringdata_PBRemoteTourneysProxy,
      qt_meta_data_PBRemoteTourneysProxy, 0 }
};

const QMetaObject *PBRemoteTourneysProxy::metaObject() const
{
    return &staticMetaObject;
}

void *PBRemoteTourneysProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBRemoteTourneysProxy))
        return static_cast<void*>(const_cast< PBRemoteTourneysProxy*>(this));
    return RpcAdaptor::qt_metacast(_clname);
}

int PBRemoteTourneysProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RpcAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
