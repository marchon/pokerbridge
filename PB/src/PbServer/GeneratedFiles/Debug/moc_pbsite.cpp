/****************************************************************************
** Meta object code from reading C++ file 'pbsite.h'
**
** Created: Fri 19. Mar 20:56:53 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbsite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbsite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBSiteTourneys[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      41,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBSiteTourneys[] = {
    "PBSiteTourneys\0\0lobbyId,siteId,tourneyId\0"
    "tourneyInfoEvent(QString,QString,QString)\0"
    "onTourneyInfoEvent(QString,QString,QString)\0"
};

const QMetaObject PBSiteTourneys::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBSiteTourneys,
      qt_meta_data_PBSiteTourneys, 0 }
};

const QMetaObject *PBSiteTourneys::metaObject() const
{
    return &staticMetaObject;
}

void *PBSiteTourneys::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBSiteTourneys))
        return static_cast<void*>(const_cast< PBSiteTourneys*>(this));
    return QObject::qt_metacast(_clname);
}

int PBSiteTourneys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tourneyInfoEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: onTourneyInfoEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PBSiteTourneys::tourneyInfoEvent(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_PBSite[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,    8,    7,    7, 0x0a,
      40,    8,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PBSite[] = {
    "PBSite\0\0ch\0onChannelOpened(RpcChannel*)\0"
    "onChannelClosed(RpcChannel*)\0"
};

const QMetaObject PBSite::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBSite,
      qt_meta_data_PBSite, 0 }
};

const QMetaObject *PBSite::metaObject() const
{
    return &staticMetaObject;
}

void *PBSite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBSite))
        return static_cast<void*>(const_cast< PBSite*>(this));
    return QObject::qt_metacast(_clname);
}

int PBSite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onChannelOpened((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        case 1: onChannelClosed((*reinterpret_cast< RpcChannel*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
