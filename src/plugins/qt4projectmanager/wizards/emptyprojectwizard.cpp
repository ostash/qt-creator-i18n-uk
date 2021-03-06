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

#include "emptyprojectwizard.h"

#include "emptyprojectwizarddialog.h"

#include <projectexplorer/projectexplorerconstants.h>

#include <QIcon>

namespace Qt4ProjectManager {
namespace Internal {

EmptyProjectWizard::EmptyProjectWizard()
  : QtWizard(QLatin1String("U.Qt4Empty"),
             QLatin1String(ProjectExplorer::Constants::QT_PROJECT_WIZARD_CATEGORY),
             QLatin1String(ProjectExplorer::Constants::QT_PROJECT_WIZARD_CATEGORY_DISPLAY),
             tr("Empty Qt Project"),
             tr("Creates a qmake-based project without any files. This allows you to create "
                "an application without any default classes."),
             QIcon(QLatin1String(":/wizards/images/gui.png")))
{
}

Core::FeatureSet EmptyProjectWizard::requiredFeatures() const
{
    return Core::FeatureSet();
}

QWizard *EmptyProjectWizard::createWizardDialog(QWidget *parent,
                                                const Core::WizardDialogParameters &wizardDialogParameters) const
{
    EmptyProjectWizardDialog *dialog = new EmptyProjectWizardDialog(displayName(), icon(), parent, wizardDialogParameters);
    dialog->setProjectName(EmptyProjectWizardDialog::uniqueProjectName(wizardDialogParameters.defaultPath()));
    return dialog;
}

Core::GeneratedFiles
        EmptyProjectWizard::generateFiles(const QWizard *w,
                                        QString * /*errorMessage*/) const
{
    const EmptyProjectWizardDialog *wizard = qobject_cast< const EmptyProjectWizardDialog *>(w);
    const QtProjectParameters params = wizard->parameters();
    const QString projectPath = params.projectPath();
    const QString profileName = Core::BaseFileWizard::buildFileName(projectPath, params.fileName, profileSuffix());

    Core::GeneratedFile profile(profileName);
    profile.setAttributes(Core::GeneratedFile::OpenProjectAttribute | Core::GeneratedFile::OpenEditorAttribute);
    return Core::GeneratedFiles() << profile;
}

} // namespace Internal
} // namespace Qt4ProjectManager
