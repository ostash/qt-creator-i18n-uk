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

#ifndef VCSPLUGIN_H
#define VCSPLUGIN_H

#include <extensionsystem/iplugin.h>

#include <QObject>

QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

namespace VcsBase {
namespace Internal {

class CommonVcsSettings;
class CommonOptionsPage;
class CoreListener;

class VcsPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

public:
    VcsPlugin();
    ~VcsPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);

    void extensionsInitialized();

    static VcsPlugin *instance();

    CoreListener *coreListener() const;

    CommonVcsSettings settings() const;

    // Model of user nick names used for the submit
    // editor. Stored centrally here to achieve delayed
    // initialization and updating on settings change.
    QStandardItemModel *nickNameModel();

signals:
    void settingsChanged(const VcsBase::Internal::CommonVcsSettings &s);

private slots:
    void slotSettingsChanged();

private:
    void populateNickNameModel();

    static VcsPlugin *m_instance;
    CommonOptionsPage *m_settingsPage;
    QStandardItemModel *m_nickNameModel;
    CoreListener *m_coreListener;
};

} // namespace Internal
} // namespace VcsBase

#endif // VCSPLUGIN_H
