/****************************************************************************
** Meta object code from reading C++ file 'pbgameinfo.h'
**
** Created: Fri 2. Apr 17:19:13 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\pbgameinfo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pbgameinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PBGameInfo[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      16,   12, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // properties: name, type, flags
      19,   11, 0x0a095103,
      26,   11, 0x0a095103,
      34,   11, 0x0a095103,
      49,   11, 0x0a095103,
      60,   56, 0x02095103,
      68,   11, 0x0a095103,
      86,   79, 0x06095103,
      97,   79, 0x06095103,
     106,   56, 0x02095103,
     115,   11, 0x0a095103,
     122,   56, 0x02095103,
     130,   56, 0x02095103,
     148,   56, 0x02095103,
     158,   56, 0x02095103,
     170,   56, 0x02095103,
     184,   56, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_PBGameInfo[] = {
    "PBGameInfo\0QString\0gameId\0tableId\0"
    "tourneyTableId\0siteId\0int\0canJoin\0"
    "gameFamily\0double\0smallBlind\0bigBlind\0"
    "maxSeats\0driver\0canOpen\0openedTablesCount\0"
    "tablesMax\0tableOpened\0tourneyOpened\0"
    "gameComplete\0"
};

const QMetaObject PBGameInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PBGameInfo,
      qt_meta_data_PBGameInfo, 0 }
};

const QMetaObject *PBGameInfo::metaObject() const
{
    return &staticMetaObject;
}

void *PBGameInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBGameInfo))
        return static_cast<void*>(const_cast< PBGameInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int PBGameInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = gameId(); break;
        case 1: *reinterpret_cast< QString*>(_v) = tableId(); break;
        case 2: *reinterpret_cast< QString*>(_v) = tourneyTableId(); break;
        case 3: *reinterpret_cast< QString*>(_v) = siteId(); break;
        case 4: *reinterpret_cast< int*>(_v) = canJoin(); break;
        case 5: *reinterpret_cast< QString*>(_v) = gameFamily(); break;
        case 6: *reinterpret_cast< double*>(_v) = smallBlind(); break;
        case 7: *reinterpret_cast< double*>(_v) = bigBlind(); break;
        case 8: *reinterpret_cast< int*>(_v) = maxSeats(); break;
        case 9: *reinterpret_cast< QString*>(_v) = driver(); break;
        case 10: *reinterpret_cast< int*>(_v) = canOpen(); break;
        case 11: *reinterpret_cast< int*>(_v) = openedTablesCount(); break;
        case 12: *reinterpret_cast< int*>(_v) = tablesMax(); break;
        case 13: *reinterpret_cast< int*>(_v) = tableOpened(); break;
        case 14: *reinterpret_cast< int*>(_v) = tourneyOpened(); break;
        case 15: *reinterpret_cast< int*>(_v) = gameComplete(); break;
        }
        _id -= 16;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setGameId(*reinterpret_cast< QString*>(_v)); break;
        case 1: setTableId(*reinterpret_cast< QString*>(_v)); break;
        case 2: setTourneyTableId(*reinterpret_cast< QString*>(_v)); break;
        case 3: setSiteId(*reinterpret_cast< QString*>(_v)); break;
        case 4: setCanJoin(*reinterpret_cast< int*>(_v)); break;
        case 5: setGameFamily(*reinterpret_cast< QString*>(_v)); break;
        case 6: setSmallBlind(*reinterpret_cast< double*>(_v)); break;
        case 7: setBigBlind(*reinterpret_cast< double*>(_v)); break;
        case 8: setMaxSeats(*reinterpret_cast< int*>(_v)); break;
        case 9: setDriver(*reinterpret_cast< QString*>(_v)); break;
        case 10: setCanOpen(*reinterpret_cast< int*>(_v)); break;
        case 11: setOpenedTablesCount(*reinterpret_cast< int*>(_v)); break;
        case 12: setTablesMax(*reinterpret_cast< int*>(_v)); break;
        case 13: setTableOpened(*reinterpret_cast< int*>(_v)); break;
        case 14: setTourneyOpened(*reinterpret_cast< int*>(_v)); break;
        case 15: setGameComplete(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 16;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 16;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
static const uint qt_meta_data_PBSiteGameInfo[] = {

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

static const char qt_meta_stringdata_PBSiteGameInfo[] = {
    "PBSiteGameInfo\0"
};

const QMetaObject PBSiteGameInfo::staticMetaObject = {
    { &PBGameInfo::staticMetaObject, qt_meta_stringdata_PBSiteGameInfo,
      qt_meta_data_PBSiteGameInfo, 0 }
};

const QMetaObject *PBSiteGameInfo::metaObject() const
{
    return &staticMetaObject;
}

void *PBSiteGameInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PBSiteGameInfo))
        return static_cast<void*>(const_cast< PBSiteGameInfo*>(this));
    return PBGameInfo::qt_metacast(_clname);
}

int PBSiteGameInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PBGameInfo::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
