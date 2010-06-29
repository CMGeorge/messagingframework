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

#include "imapauthenticator.h"

#include "imapprotocol.h"
#include "imapconfiguration.h"

#include <qmailauthenticator.h>
#include <qmailtransport.h>


bool ImapAuthenticator::useEncryption(const QMailAccountConfiguration::ServiceConfiguration &svcCfg, const QStringList &capabilities)
{
#ifdef QT_NO_OPENSSL
    return false;
#else
    ImapConfiguration imapCfg(svcCfg);
    bool useTLS(imapCfg.mailEncryption() == QMailTransport::Encrypt_TLS);

    if (!capabilities.contains("STARTTLS")) {
        if (useTLS) {
            qWarning() << "Server does not support TLS - continuing unencrypted";
        }
    } else {
        if (useTLS) {
            return true;
        }
    }

    return QMailAuthenticator::useEncryption(svcCfg, capabilities);
#endif
}

QByteArray ImapAuthenticator::getAuthentication(const QMailAccountConfiguration::ServiceConfiguration &svcCfg, const QStringList &capabilities)
{
    QByteArray result(QMailAuthenticator::getAuthentication(svcCfg, capabilities));
    if (!result.isEmpty())
        return QByteArray("AUTHENTICATE ") + result;

    // If not handled by the authenticator, fall back to login
    ImapConfiguration imapCfg(svcCfg);
    return QByteArray("LOGIN") + " " + ImapProtocol::quoteString(imapCfg.mailUserName().toAscii()) 
                               + " " + ImapProtocol::quoteString(imapCfg.mailPassword().toAscii());
}

QByteArray ImapAuthenticator::getResponse(const QMailAccountConfiguration::ServiceConfiguration &svcCfg, const QByteArray &challenge)
{
    return QMailAuthenticator::getResponse(svcCfg, challenge);
}

