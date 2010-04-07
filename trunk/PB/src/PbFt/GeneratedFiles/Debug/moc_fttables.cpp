/****************************************************************************
** Meta object code from reading C++ file 'fttables.h'
**
** Created: Thu 1. Apr 17:12:25 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fttables.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fttables.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTTables[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      18,   10,    9,    9, 0x05,
      52,   44,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,   78,    9,    9, 0x0a,
     138,  136,    9,    9, 0x0a,
     174,  163,    9,    9, 0x0a,
     216,  209,    9,    9, 0x0a,
     234,  209,    9,    9, 0x0a,
     253,    9,    9,    9, 0x0a,
     272,   44,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTTables[] = {
    "FTTables\0\0history\0handHistoryEvent(QString)\0"
    "tableId\0tableOpenedEvent(QString)\0"
    "view,start,end\0"
    "onRowsInserted(QAbstractItemView*,int,int)\0"
    "s\0onStringIndexOf(QString)\0histStr,hi\0"
    "onHandHistory(QString,PBHandInfo*)\0"
    "widget\0onPaint(QWidget*)\0onWidget(QWidget*)\0"
    "onTooManyWindows()\0emitTableOpened(QString)\0"
};

const QMetaObject FTTables::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTTables,
      qt_meta_data_FTTables, 0 }
};

const QMetaObject *FTTables::metaObject() const
{
    return &staticMetaObject;
}

void *FTTables::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTables))
        return static_cast<void*>(const_cast< FTTables*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTTables::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: handHistoryEvent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: tableOpenedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: onRowsInserted((*reinterpret_cast< QAbstractItemView*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: onStringIndexOf((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: onHandHistory((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< PBHandInfo*(*)>(_a[2]))); break;
        case 5: onPaint((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 6: onWidget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 7: onTooManyWindows(); break;
        case 8: emitTableOpened((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FTTables::handHistoryEvent(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FTTables::tableOpenedEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
