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

#ifndef SELECTCOMPOSERWIDGET_H
#define SELECTCOMPOSERWIDGET_H

#include <QPair>
#include <qmailmessage.h>
#include <QString>
#include <QWidget>

class SelectListWidget;

QT_BEGIN_NAMESPACE

class QListWidget;
class QListWidgetItem;

QT_END_NAMESPACE;

class SelectComposerWidget : public QWidget
{
    Q_OBJECT

public:
    SelectComposerWidget( QWidget* parent );

    void setSelected(const QString& selected, QMailMessage::MessageType type);

    QString singularKey() const;

    QList<QMailMessage::MessageType> availableTypes() const;

    QPair<QString, QMailMessage::MessageType> currentSelection() const;

signals:
    void selected(const QPair<QString, QMailMessage::MessageType> &);
    void cancel();

protected slots:
    void accept(QListWidgetItem* item);
    void refresh();

protected:
    void keyPressEvent(QKeyEvent *e);
    void init();

private:
    SelectListWidget* m_listWidget;
};

#endif
