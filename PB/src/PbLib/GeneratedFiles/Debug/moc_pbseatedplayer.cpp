/****************************************************************************
** Meta object code from reading C++ file 'pbseatedplayer.h'
**
** Created: Sat 13. Mar 18:21:54 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbseatedplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbseatedplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBSeatedPlayer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       5,   22, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      23,   16,   15,   15, 0x05,
      46,   16,   15,   15, 0x05,

 // properties: name, type, flags
      74,   70, 0x02095103,
      87,   79, 0x0a095103,
     103,   96, 0x06095103,
     114,  109, 0x01095103,
     125,   79, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_PBSeatedPlayer[] = {
    "PBSeatedPlayer\0\0player\0sitIn(PBSeatedPlayer*)\0"
    "sitOut(PBSeatedPlayer*)\0int\0seat\0"
    "QString\0playerId\0double\0stake\0bool\0"
    "sittingOut\0holeCards\0"
};

const QMetaObject PBSeatedPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBSeatedPlayer,
      qt_meta_data_PBSeatedPlayer, 0 }
};

const QMetaObject *PBSeatedPlayer::metaObject() const
{
    return &staticMetaObject;
}

void *PBSeatedPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBSeatedPlayer))
        return static_cast<void*>(const_cast< PBSeatedPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int PBSeatedPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sitIn((*reinterpret_cast< PBSeatedPlayer*(*)>(_a[1]))); break;
        case 1: sitOut((*reinterpret_cast< PBSeatedPlayer*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = seat(); break;
        case 1: *reinterpret_cast< QString*>(_v) = playerId(); break;
        case 2: *reinterpret_cast< double*>(_v) = stake(); break;
        case 3: *reinterpret_cast< bool*>(_v) = sittingOut(); break;
        case 4: *reinterpret_cast< QString*>(_v) = holeCards(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSeat(*reinterpret_cast< int*>(_v)); break;
        case 1: setPlayerId(*reinterpret_cast< QString*>(_v)); break;
        case 2: setStake(*reinterpret_cast< double*>(_v)); break;
        case 3: setSittingOut(*reinterpret_cast< bool*>(_v)); break;
        case 4: setHoleCards(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PBSeatedPlayer::sitIn(PBSeatedPlayer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PBSeatedPlayer::sitOut(PBSeatedPlayer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
