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

#include "gitsubmiteditor.h"
#include "gitsubmiteditorwidget.h"
#include "gitconstants.h"
#include "commitdata.h"

#include <utils/qtcassert.h>
#include <vcsbase/submitfilemodel.h>

#include <QDebug>
#include <QStringList>
#include <QTextCodec>

namespace Git {
namespace Internal {

/* The problem with git is that no diff can be obtained to for a random
 * multiselection of staged/unstaged files; it requires the --cached
 * option for staged files. So, we sort apart the diff file lists
 * according to a type flag we add to the model. */

GitSubmitEditor::GitSubmitEditor(const VcsBase::VcsBaseSubmitEditorParameters *parameters, QWidget *parent) :
    VcsBaseSubmitEditor(parameters, new GitSubmitEditorWidget(parent)),
    m_model(0)
{
    connect(this, SIGNAL(diffSelectedFiles(QStringList)), this, SLOT(slotDiffSelected(QStringList)));
}

GitSubmitEditorWidget *GitSubmitEditor::submitEditorWidget()
{
    return static_cast<GitSubmitEditorWidget *>(widget());
}

void GitSubmitEditor::setCommitData(const CommitData &d)
{
    submitEditorWidget()->setPanelData(d.panelData);
    submitEditorWidget()->setPanelInfo(d.panelInfo);

    m_commitEncoding = d.commitEncoding;

    m_model = new VcsBase::SubmitFileModel(this);
    if (!d.files.isEmpty()) {
        for (QList<CommitData::StateFilePair>::const_iterator it = d.files.constBegin();
             it != d.files.constEnd(); ++it) {
            const CommitData::FileState state = it->first;
            const QString file = it->second;
            m_model->addFile(file, CommitData::stateDisplayName(state), state & CommitData::StagedFile,
                             QVariant(static_cast<int>(state)));
        }
    }
    setFileModel(m_model, d.panelInfo.repository);
}

void GitSubmitEditor::slotDiffSelected(const QStringList &files)
{
    // Sort it apart into staged/unstaged files
    QStringList unstagedFiles;
    QStringList stagedFiles;
    const int fileColumn = fileNameColumn();
    const int rowCount = m_model->rowCount();
    for (int r = 0; r < rowCount; r++) {
        const QString fileName = m_model->item(r, fileColumn)->text();
        if (files.contains(fileName)) {
            const CommitData::FileState state = static_cast<CommitData::FileState>(m_model->extraData(r).toInt());
            if (state & CommitData::StagedFile)
                stagedFiles.push_back(fileName);
            else if (state != CommitData::UntrackedFile)
                unstagedFiles.push_back(fileName);
        }
    }
    if (!unstagedFiles.empty() || !stagedFiles.empty())
        emit diff(unstagedFiles, stagedFiles);
}

GitSubmitEditorPanelData GitSubmitEditor::panelData() const
{
    return const_cast<GitSubmitEditor*>(this)->submitEditorWidget()->panelData();
}

QByteArray GitSubmitEditor::fileContents() const
{
    const QString& text = const_cast<GitSubmitEditor*>(this)->submitEditorWidget()->descriptionText();

    if (!m_commitEncoding.isEmpty()) {
        // Do the encoding convert, When use user-defined encoding
        // e.g. git config --global i18n.commitencoding utf-8
        QTextCodec *codec = QTextCodec::codecForName(m_commitEncoding.toLocal8Bit());
        if (codec)
            return codec->fromUnicode(text);
    }

    // Using utf-8 as the default encoding
    return text.toUtf8();
}

} // namespace Internal
} // namespace Git
