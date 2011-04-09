/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Messaging Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <ctype.h>
#include <QObject>
#include <QTest>
#include "qmailnamespace.h"

using namespace QMail;

class tst_QMailnamespace : public QObject
{
    Q_OBJECT

public:
    tst_QMailnamespace() {}
    virtual ~tst_QMailnamespace() {}

private slots:
    void test_qmailnamespace();
};

QTEST_MAIN(tst_QMailnamespace)

#include "tst_qmailnamespace.moc"

void tst_QMailnamespace::test_qmailnamespace()
{
    QString file("locktestfile");
    int id = fileLock(file);
    QVERIFY(id != -1);
    QVERIFY(fileUnlock(id));

    QCOMPARE(sslCertsPath(), QString("/etc/ssl/certs/"));

    messageServerPath();
    messageSettingsPath();

    QStringList types = extensionsForMimeType("audio/mpeg");
    QVERIFY(types.count() != 0);
    QCOMPARE(extensionsForMimeType("audio/pcmu").count(), 0);

    QMail::usleep(1000);

    //QCOMPARE(lastSystemErrorMessage(), QString("Success"));
}
