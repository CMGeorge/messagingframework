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


#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QToolButton>
#include <QGridLayout>
#include <QResizeEvent>
#include <qtmailnamespace.h>

#define DEFINE_STATUS_MONITOR_INSTANCE
#include "statusmonitor.h"

class ServiceActionStatusWidget : public QWidget
{
    Q_OBJECT

public:
    ServiceActionStatusWidget(QMailServiceAction* service, const QString& description, QWidget* parent = 0);
    QSize sizeHint() const;

private slots:
    void progressChanged(uint value, uint total);

private:
    void init();

private:
    QMailServiceAction* m_serviceAction;
    QLabel* m_descriptionLabel;
    QProgressBar* m_progressBar;
    QToolButton* m_cancelButton;
    QString m_description;
};


ServiceActionStatusWidget::ServiceActionStatusWidget(QMailServiceAction* action, const QString& description = QString(), QWidget* parent)
:
QWidget(parent),
m_serviceAction(action),
m_description(description)
{
    init();
    connect(m_serviceAction,SIGNAL(destroyed(QObject*)),this,SLOT(deleteLater()));
}

QSize ServiceActionStatusWidget::sizeHint() const
{
    return QSize(300,60);
}

void ServiceActionStatusWidget::progressChanged(uint value, uint total)
{
    m_progressBar->setRange(0,total);
    m_progressBar->setValue(value);
}

void ServiceActionStatusWidget::init()
{
    QGridLayout* gl = new QGridLayout(this);
    gl->setSpacing(2);

    m_descriptionLabel = new QLabel(m_description,this);
    gl->addWidget(m_descriptionLabel,0,0,1,2);

    m_progressBar = new QProgressBar(this);
    gl->addWidget(m_progressBar,1,0,1,1);

    m_cancelButton = new QToolButton(this);
    m_cancelButton->setIcon(Qtmail::icon("cancel"));
    gl->addWidget(m_cancelButton,1,1,1,1);

    connect(m_serviceAction,SIGNAL(progressChanged(uint,uint)),
            this, SLOT(progressChanged(uint,uint)));

    connect(m_cancelButton,SIGNAL(clicked(bool)),m_serviceAction,SLOT(cancelOperation()));
}


ServiceActionStatusItem::ServiceActionStatusItem(QMailServiceAction* serviceAction, const QString& description)
:
StatusItem(),
m_serviceAction(serviceAction),
m_description(description)
{
    setParent(serviceAction);
    connect(m_serviceAction, SIGNAL(activityChanged(QMailServiceAction::Activity)),
            this,SLOT(serviceActivityChanged(QMailServiceAction::Activity)));
    connect(m_serviceAction, SIGNAL(statusChanged(const QMailServiceAction::Status)),
            this,SLOT(serviceStatusChanged(const QMailServiceAction::Status)));
    connect(m_serviceAction, SIGNAL(progressChanged(uint,uint)),
            this,SIGNAL(progressChanged(uint,uint)));
}

QWidget* ServiceActionStatusItem::widget()
{
    ServiceActionStatusWidget* asw = new ServiceActionStatusWidget(m_serviceAction,m_description);
    return asw;
}

QPair<uint,uint> ServiceActionStatusItem::progress() const
{
    return m_serviceAction->progress();
}

QString ServiceActionStatusItem::status() const
{
    return m_serviceAction->status().text;
}

void ServiceActionStatusItem::serviceActivityChanged(QMailServiceAction::Activity a)
{
    if(a == QMailServiceAction::Successful || a == QMailServiceAction::Failed)
        emit finished();
}

void ServiceActionStatusItem::serviceStatusChanged(const QMailServiceAction::Status& s)
{
    emit statusChanged(s.text);
}

Q_GLOBAL_STATIC(StatusMonitor,StatusMonitorInstance);

StatusMonitor* StatusMonitor::instance()
{
    return StatusMonitorInstance();
}

void StatusMonitor::add(StatusItem* newItem)
{
    if(!newItem || m_statusItems.contains(newItem))
    {
        qWarning() << "Status item already exists.";
        return;
    }

    m_statusItems.append(newItem);
    connect(newItem,SIGNAL(finished()),this,SLOT(statusItemFinished()));
    connect(newItem,SIGNAL(progressChanged(uint,uint)),
        this,SLOT(statusItemProgressChanged()));
    connect(newItem,SIGNAL(statusChanged(QString)),this,SIGNAL(statusChanged(QString)));
    connect(newItem,SIGNAL(destroyed(QObject*)),this,SLOT(statusItemDestroyed(QObject*)));
    emit added(newItem);
}

int StatusMonitor::itemCount() const
{
    return m_statusItems.count();
}

StatusMonitor::StatusMonitor()
:
QObject()
{
}

void StatusMonitor::updateProgress()
{
    uint total = 0;
    uint totalValue = 0;

    foreach(StatusItem* item, m_statusItems)
    {
        total += item->progress().second;
        totalValue += item->progress().first;
    }
    emit progressChanged(totalValue,total);
}


void StatusMonitor::statusItemFinished()
{
    //remove the sender from the list
    StatusItem* item = qobject_cast<StatusItem*>(sender());
    m_statusItems.removeAll(item);
    disconnect(item);
    emit removed(item);
    item->deleteLater();
}

void StatusMonitor::statusItemProgressChanged()
{
    updateProgress();
}

void StatusMonitor::statusItemDestroyed(QObject* s)
{
    StatusItem* ss = qobject_cast<StatusItem*>(s);
    if(ss)
    {
        m_statusItems.removeAll(ss);
        disconnect(ss);
        emit removed(ss);
    }
}

#include <statusmonitor.moc>
