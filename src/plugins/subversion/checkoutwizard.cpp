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

#include "checkoutwizard.h"
#include "checkoutwizardpage.h"
#include "subversionplugin.h"

#include <coreplugin/iversioncontrol.h>
#include <vcsbase/checkoutjobs.h>
#include <vcsbase/vcsbaseconstants.h>
#include <vcsbase/vcsconfigurationpage.h>
#include <utils/qtcassert.h>

#include <QIcon>

namespace Subversion {
namespace Internal {

CheckoutWizard::CheckoutWizard(QObject *parent) :
        VcsBase::BaseCheckoutWizard(parent)
{
    setId(QLatin1String(VcsBase::Constants::VCS_ID_SUBVERSION));
}

QIcon CheckoutWizard::icon() const
{
    return QIcon(QLatin1String(":/subversion/images/subversion.png"));
}

QString CheckoutWizard::description() const
{
    return tr("Checks out a Subversion repository and tries to load the contained project.");
}

QString CheckoutWizard::displayName() const
{
    return tr("Subversion Checkout");
}

QList<QWizardPage*> CheckoutWizard::createParameterPages(const QString &path)
{
    QList<QWizardPage*> rc;
    const Core::IVersionControl *vc = SubversionPlugin::instance()->versionControl();
    if (!vc->isConfigured())
        rc.append(new VcsBase::VcsConfigurationPage(vc));
    CheckoutWizardPage *cwp = new CheckoutWizardPage;
    cwp->setPath(path);
    rc.append(cwp);
    return rc;
}

QSharedPointer<VcsBase::AbstractCheckoutJob> CheckoutWizard::createJob(const QList<QWizardPage*> &parameterPages,
                                                                    QString *checkoutPath)
{
    // Collect parameters for the checkout command.
    const CheckoutWizardPage *cwp = qobject_cast<const CheckoutWizardPage *>(parameterPages.front());
    QTC_ASSERT(cwp, return QSharedPointer<VcsBase::AbstractCheckoutJob>())
    const SubversionSettings settings = SubversionPlugin::instance()->settings();
    const QString binary = settings.svnCommand;
    const QString directory = cwp->directory();
    QStringList args;
    args << QLatin1String("checkout") << cwp->repository() << directory;
    const QString workingDirectory = cwp->path();
    *checkoutPath = workingDirectory + QLatin1Char('/') + directory;
    const QStringList completeArgs = settings.hasAuthentication() ?
                                     SubversionPlugin::addAuthenticationOptions(args, settings.user, settings.password) :
                                     args;
    VcsBase::ProcessCheckoutJob *job = new VcsBase::ProcessCheckoutJob;
    job->addStep(binary, completeArgs, workingDirectory);
    return QSharedPointer<VcsBase::AbstractCheckoutJob>(job);
}

} // namespace Internal
} // namespace Subversion
