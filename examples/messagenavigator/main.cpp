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

#include "messagenavigator.h"
#include <qtopiaapplication.h>

// Comment out this line to use a manual main() function.
// Ensure you also remove CONFIG+=qtopia_main from qbuild.pro if you do this.
#define USE_THE_MAIN_MACROS



#ifdef USE_THE_MAIN_MACROS

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, MessageNavigator)
QTOPIA_MAIN

#else

#ifdef SINGLE_EXEC
QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, MessageNavigator)
#define MAIN_FUNC main_MessageNavigator
#else
#define MAIN_FUNC main
#endif

// This is the storage for the SXE key that uniquely identified this applicaiton.
// make will fail without this!
QSXE_APP_KEY

int MAIN_FUNC( int argc, char **argv )
{
    // This is required to load the SXE key into memory
    QSXE_SET_APP_KEY(argv[0]);

    QtopiaApplication a( argc, argv );

    // Set the preferred document system connection type
    QTOPIA_SET_DOCUMENT_SYSTEM_CONNECTION();

    MessageNavigator *mw = new MessageNavigator();
    a.setMainWidget(mw);
    if ( mw->metaObject()->indexOfSlot("setDocument(QString)") != -1 ) {
        a.showMainDocumentWidget();
    } else {
        a.showMainWidget();
    }
    int rv = a.exec();
    delete mw;
    return rv;
}

#endif

