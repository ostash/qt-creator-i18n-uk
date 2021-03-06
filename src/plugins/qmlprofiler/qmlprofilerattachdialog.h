/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef QMLPROFILERATTACHDIALOG_H
#define QMLPROFILERATTACHDIALOG_H

#include <QDialog>

namespace QmlProfiler {
namespace Internal {

namespace Ui {
    class QmlProfilerAttachDialog;
}

class QmlProfilerAttachDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QmlProfilerAttachDialog(QWidget *parent = 0);
    ~QmlProfilerAttachDialog();

    QString address() const;
    uint port() const;
    QString sysroot() const;

    void setAddress(const QString &address);
    void setPort(uint port);
    void setSysroot(const QString &sysroot);

private:
    Ui::QmlProfilerAttachDialog *ui;
};

} // namespace Internal
} // namespace QmlProfiler

#endif // QMLPROFILERATTACHDIALOG_H
