/****************************************************************************
** Meta object code from reading C++ file 'rmessage.h'
**
** Created: Wed 31. Mar 17:35:42 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "..\..\rmessage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rmessage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RMessage[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   12, // enums/sets
       0,    0, // constructors

 // enums: name, flags, count, data
       9, 0x1,    4,   20,
      23, 0x1,    4,   28,

 // enum data: key, value
      29, uint(RMessage::NotifyChildren),
      44, uint(RMessage::NotifyParents),
      58, uint(RMessage::Done),
      63, uint(RMessage::SingleQueue),
      29, uint(RMessage::NotifyChildren),
      44, uint(RMessage::NotifyParents),
      58, uint(RMessage::Done),
      63, uint(RMessage::SingleQueue),

       0        // eod
};

static const char qt_meta_stringdata_RMessage[] = {
    "RMessage\0RMessageFlags\0Flags\0"
    "NotifyChildren\0NotifyParents\0Done\0"
    "SingleQueue\0"
};

const QMetaObject RMessage::staticMetaObject = {
    { 0, qt_meta_stringdata_RMessage,
      qt_meta_data_RMessage, 0 }
};
QT_END_MOC_NAMESPACE
