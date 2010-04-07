/****************************************************************************
** Meta object code from reading C++ file 'ftpanel.h'
**
** Created: Fri 2. Apr 21:30:32 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\ftpanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTPanel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,    8,    8,    8, 0x0a,
      45,    8,    8,    8, 0x0a,
      66,    8,    8,    8, 0x0a,
      86,    8,    8,    8, 0x0a,
     104,    8,    8,    8, 0x0a,
     122,    8,    8,    8, 0x0a,
     139,    8,    8,    8, 0x0a,
     157,    8,    8,    8, 0x0a,
     174,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTPanel[] = {
    "FTPanel\0\0s\0writeLog(QString)\0"
    "onFoldClicked()\0onCheckCallClicked()\0"
    "onBetRaiseClicked()\0onPostBBClicked()\0"
    "onWaitBBClicked()\0onSitinClicked()\0"
    "onSitoutClicked()\0onCloseClicked()\0"
    "onJoinClicked()\0"
};

const QMetaObject FTPanel::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_FTPanel,
      qt_meta_data_FTPanel, 0 }
};

const QMetaObject *FTPanel::metaObject() const
{
    return &staticMetaObject;
}

void *FTPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTPanel))
        return static_cast<void*>(const_cast< FTPanel*>(this));
    return QFrame::qt_metacast(_clname);
}

int FTPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: writeLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: onFoldClicked(); break;
        case 2: onCheckCallClicked(); break;
        case 3: onBetRaiseClicked(); break;
        case 4: onPostBBClicked(); break;
        case 5: onWaitBBClicked(); break;
        case 6: onSitinClicked(); break;
        case 7: onSitoutClicked(); break;
        case 8: onCloseClicked(); break;
        case 9: onJoinClicked(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void FTPanel::writeLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
