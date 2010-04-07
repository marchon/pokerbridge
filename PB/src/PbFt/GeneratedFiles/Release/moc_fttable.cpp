/****************************************************************************
** Meta object code from reading C++ file 'fttable.h'
**
** Created: Fri 2. Apr 21:30:32 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\fttable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fttable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTDlg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,    7,    6,    6, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FTDlg[] = {
    "FTDlg\0\0question\0dialogEvent(QString)\0"
};

const QMetaObject FTDlg::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTDlg,
      qt_meta_data_FTDlg, 0 }
};

const QMetaObject *FTDlg::metaObject() const
{
    return &staticMetaObject;
}

void *FTDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTDlg))
        return static_cast<void*>(const_cast< FTDlg*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dialogEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void FTDlg::dialogEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_FTTable[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      23,    9,    8,    8, 0x05,
      59,    9,    8,    8, 0x05,
      93,    9,    8,    8, 0x05,
     135,  128,    8,    8, 0x05,
     175,  155,    8,    8, 0x05,
     216,  201,    8,    8, 0x05,
     243,  128,    8,    8, 0x05,
     262,    9,    8,    8, 0x05,
     287,    9,    8,    8, 0x05,
     319,    9,    8,    8, 0x05,
     351,    9,    8,    8, 0x05,
     383,    9,    8,    8, 0x05,
     415,  128,    8,    8, 0x05,
     436,  128,    8,    8, 0x05,
     456,  128,    8,    8, 0x05,
     475,  128,    8,    8, 0x05,
     501,  495,    8,    8, 0x05,
     530,  525,    8,    8, 0x05,
     553,  525,    8,    8, 0x05,
     577,  495,    8,    8, 0x05,
     614,  601,    8,    8, 0x05,
     663,  646,    8,    8, 0x05,
     701,  694,    8,    8, 0x05,
     730,  725,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     760,  751,    8,    8, 0x0a,
     778,  751,    8,    8, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FTTable[] = {
    "FTTable\0\0player,amount\0"
    "postSmallBlindEvent(QString,double)\0"
    "postBigBlindEvent(QString,double)\0"
    "postDeadBlindEvent(QString,double)\0"
    "player\0checkEvent(QString)\0"
    "player,amountToCall\0callEvent(QString,double)\0"
    "player,raiseTo\0raiseEvent(QString,double)\0"
    "foldEvent(QString)\0betEvent(QString,double)\0"
    "winMainPotEvent(QString,double)\0"
    "tieMainPotEvent(QString,double)\0"
    "winSidePotEvent(QString,double)\0"
    "tieSidePotEvent(QString,double)\0"
    "sitOutEvent(QString)\0sitInEvent(QString)\0"
    "joinEvent(QString)\0leaveEvent(QString)\0"
    "cards\0flopCardsEvent(QString)\0card\0"
    "turnCardEvent(QString)\0riverCardEvent(QString)\0"
    "holeCardsEvent(QString)\0player,cards\0"
    "showCardsEvent(QString,QString)\0"
    "player,handValue\0showHandEvent(QString,QString)\0"
    "handId\0handStartEvent(QString)\0seat\0"
    "buttonSeatEvent(int)\0question\0"
    "onMsgBox(QString)\0getChips_Dialog(QString)\0"
};

const QMetaObject FTTable::staticMetaObject = {
    { &FTWidgetHook::staticMetaObject, qt_meta_stringdata_FTTable,
      qt_meta_data_FTTable, 0 }
};

const QMetaObject *FTTable::metaObject() const
{
    return &staticMetaObject;
}

void *FTTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTTable))
        return static_cast<void*>(const_cast< FTTable*>(this));
    return FTWidgetHook::qt_metacast(_clname);
}

int FTTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FTWidgetHook::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: postSmallBlindEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: postBigBlindEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: postDeadBlindEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: checkEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: callEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: raiseEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: foldEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: betEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: winMainPotEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: tieMainPotEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: winSidePotEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 11: tieSidePotEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: sitOutEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: sitInEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: joinEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: leaveEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: flopCardsEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: turnCardEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: riverCardEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: holeCardsEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: showCardsEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 21: showHandEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 22: handStartEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: buttonSeatEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: onMsgBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: getChips_Dialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void FTTable::postSmallBlindEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FTTable::postBigBlindEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FTTable::postDeadBlindEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FTTable::checkEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FTTable::callEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FTTable::raiseEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FTTable::foldEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FTTable::betEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FTTable::winMainPotEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void FTTable::tieMainPotEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void FTTable::winSidePotEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void FTTable::tieSidePotEvent(QString _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void FTTable::sitOutEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void FTTable::sitInEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void FTTable::joinEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void FTTable::leaveEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void FTTable::flopCardsEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void FTTable::turnCardEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void FTTable::riverCardEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void FTTable::holeCardsEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void FTTable::showCardsEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void FTTable::showHandEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void FTTable::handStartEvent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void FTTable::buttonSeatEvent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}
QT_END_MOC_NAMESPACE
