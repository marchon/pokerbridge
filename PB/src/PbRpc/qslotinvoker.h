/****************************************************************************
**
** This file is part of the Qt Extended Opensource Package.
**
** Copyright (C) 2009 Trolltech ASA.
**
** Contact: Qt Extended Information (info@qtextended.org)
**
** This file may be used under the terms of the GNU General Public License
** version 2.0 as published by the Free Software Foundation and appearing
** in the file LICENSE.GPL included in the packaging of this file.
**
** Please review the following information to ensure GNU General Public
** Licensing requirements will be met:
**     http://www.fsf.org/licensing/licenses/info/GPLv2.html.
**
**
****************************************************************************/

#ifndef QSLOTINVOKER_H
#define QSLOTINVOKER_H

#include "pbglobal.h"
#define QTOPIABASE_EXPORT PB_EXPORT

//#include <qobject.h>
//#include <qvariant.h>
//#include <qlist.h>
//#include <qtopiaglobal.h>

class QSlotInvokerPrivate;

class QTOPIABASE_EXPORT QSlotInvoker : public QObject
{
    Q_OBJECT
public:
    QSlotInvoker( QObject *receiver, const QByteArray& member,
                  QObject *parent=0 );
    ~QSlotInvoker();

    bool memberPresent() const;
    bool canInvoke( int numArgs ) const;
    QObject *receiver() const;
    QByteArray member() const;
    int *parameterTypes() const;
    int parameterTypesCount() const;

public slots:
    QVariant invoke( const QList<QVariant>& args );

private slots:
    void receiverDestroyed();

private:
    QSlotInvokerPrivate *d;
};

#endif
