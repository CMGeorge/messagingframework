/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Messaging Framework.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtmailnamespace.h"
#include <qmaillog.h>
#include <QMap>

typedef QMap<QString,QIcon> IconMap;

static QIcon loadIcon(const QString& themeIdentifier, const QString& resourceFallback)
{
#if ((QT_VERSION < QT_VERSION_CHECK(4, 6, 0)) || !defined(Q_OS_LINUX))
    Q_UNUSED(themeIdentifier);
    return QIcon(resourceFallback);
#else
    return QIcon::fromTheme(themeIdentifier,QIcon(resourceFallback));
#endif
}

static IconMap init()
{
    IconMap m;
    m.insert("clear",loadIcon("edit-clear",":icon/erase"));
    m.insert("attachment",loadIcon("mail-attachment",":icon/attach"));
    m.insert("add",loadIcon("list-add",":icon/add"));
    m.insert("remove",loadIcon("list-remove",":icon/erase"));
    m.insert("reset", loadIcon("document-revert", ":icon/reset"));
    m.insert("close",loadIcon("window-close",":icon/close"));
    m.insert("uparrow",loadIcon("up",":icon/up"));
    m.insert("downarrow",loadIcon("down",":icon/down"));
    m.insert("sendandreceive",loadIcon("mail-send-receive",":icon/sync"));
    m.insert("cancel",loadIcon("process-stop",":icon/cancel"));
    m.insert("settings",loadIcon("package_settings",":icon/settings"));
    m.insert("compose",loadIcon("mail-message-new",":icon/new"));
    m.insert("search",loadIcon("search",":icon/find"));
    m.insert("reply",loadIcon("mail-reply-sender",":icon/reply"));
    m.insert("replyall",loadIcon("mail-reply-all",":icon/replyall"));
    m.insert("forward",loadIcon("mail-forward",":icon/forward"));
    m.insert("deletemail",loadIcon("edit-delete-mail",":icon/trash"));
    m.insert("folder",loadIcon("folder",":icon/folder"));
    m.insert("folderremote",loadIcon("folder-remote",":icon/folder-remote"));
    m.insert("inboxfolder",loadIcon("inboxfolder",":icon/inbox"));
    m.insert("trashfolder",loadIcon("emptytrash",":icon/trash"));
    m.insert("junkfolder",loadIcon("mail-mark-junk",":icon/folder"));
    m.insert("sentfolder",loadIcon("mail-send",":icon/sent"));
    m.insert("accountfolder",loadIcon("accountfolder",":icon/account"));
    m.insert("outboxfolder",loadIcon("outboxfolder",":icon/outbox"));
    m.insert("draftfolder",loadIcon("emblem-draft",":icon/drafts"));
    m.insert("workoffline",loadIcon("network-offline",":icon/connect_no"));
    m.insert("quit",loadIcon("exit",":icon/quit"));
    return m;
}

QIcon Qtmail::icon(const QString& name)
{
    static IconMap icons(init());
    QIcon result = icons[name];

    if(result.isNull())
        qWarning() << name << " icon not found.";

    return icons[name];
}
