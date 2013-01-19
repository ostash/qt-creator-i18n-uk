#include "gitorious/gitoriousclonewizard.h"
#include "mergetool.h"
#include "gerrit/gerritplugin.h"
    Git::Constants::C_GITSUBMITEDITOR,
    VcsBase::VcsBaseSubmitEditorParameters::DiffRows
    m_commandLocator = new Locator::CommandLocator("Git", prefix, prefix);
    /*  "Current File" menu */
    Core::ActionContainer *currentFileMenu = Core::ActionManager::createMenu(Core::Id("Git.CurrentFileMenu"));
    currentFileMenu->menu()->setTitle(tr("Current &File"));
    gitContainer->addMenu(currentFileMenu);
    ParameterActionCommandPair parameterActionCommand
            = createFileAction(currentFileMenu,
            = createFileAction(currentFileMenu,
    parameterActionCommand
                = createFileAction(currentFileMenu,
                                   tr("Blame Current File"), tr("Blame for \"%1\""),
                                   Core::Id("Git.Blame"),
                                   globalcontext, true, SLOT(blameFile()));
    parameterActionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+B") : tr("Alt+G,Alt+B")));

    currentFileMenu->addSeparator(globalcontext);
            = createFileAction(currentFileMenu,
            = createFileAction(currentFileMenu,
            = createFileAction(currentFileMenu,
            = createFileAction(currentFileMenu,
    /* \"Current File" menu */


    /*  "Current Project" menu */
    Core::ActionContainer *currentProjectMenu = Core::ActionManager::createMenu(Core::Id("Git.CurrentProjectMenu"));
    currentProjectMenu->menu()->setTitle(tr("Current &Project"));
    gitContainer->addMenu(currentProjectMenu);
            = createProjectAction(currentProjectMenu,
            = createProjectAction(currentProjectMenu,
                = createProjectAction(currentProjectMenu,
    /* \"Current Project" menu */
    /*  "Local Repository" menu */
    Core::ActionContainer *localRepositoryMenu = Core::ActionManager::createMenu(Core::Id("Git.LocalRepositoryMenu"));
    localRepositoryMenu->menu()->setTitle(tr("&Local Repository"));
    gitContainer->addMenu(localRepositoryMenu);

    createRepositoryAction(localRepositoryMenu,
    createRepositoryAction(localRepositoryMenu,
    createRepositoryAction(localRepositoryMenu,
                           tr("Clean..."), Core::Id("Git.CleanRepository"),
                           globalcontext, true, SLOT(cleanRepository()));

    createRepositoryAction(localRepositoryMenu,
    // --------------
    localRepositoryMenu->addSeparator(globalcontext);
    ActionCommandPair actionCommand = createRepositoryAction(localRepositoryMenu,
                                                             tr("Commit..."), Core::Id("Git.Commit"),
                                                             globalcontext, true, SLOT(startCommit()));
    actionCommand.second->setDefaultKeySequence(QKeySequence(Core::UseMacShortcuts ? tr("Meta+G,Meta+C") : tr("Alt+G,Alt+C")));
    createRepositoryAction(localRepositoryMenu,
                           tr("Amend Last Commit..."), Core::Id("Git.AmendCommit"),
                           globalcontext, true, SLOT(startAmendCommit()));
    // --------------
    localRepositoryMenu->addSeparator(globalcontext);
    createRepositoryAction(localRepositoryMenu,
                           tr("Reset..."), Core::Id("Git.Reset"),
                           globalcontext, false, SLOT(resetRepository()));
    createRepositoryAction(localRepositoryMenu,
                           tr("Revert Single Commit..."), Core::Id("Git.Revert"),
                           globalcontext, true, SLOT(startRevertCommit()));
    createRepositoryAction(localRepositoryMenu,
                           tr("Cherry-Pick Commit..."), Core::Id("Git.CherryPick"),
                           globalcontext, true, SLOT(startCherryPickCommit()));
    // --------------
    localRepositoryMenu->addSeparator(globalcontext);
    createRepositoryAction(localRepositoryMenu,
    localRepositoryMenu->addSeparator(globalcontext);
    // "Patch" menu
    patchMenu->menu()->setTitle(tr("&Patch"));
    localRepositoryMenu->addMenu(patchMenu);
    // "Stash" menu
    stashMenu->menu()->setTitle(tr("&Stash"));
    localRepositoryMenu->addMenu(stashMenu);
    actionCommand = createRepositoryAction(stashMenu,
                                           tr("Stash"), Core::Id("Git.Stash"),
                                           globalcontext, true, SLOT(stash()));

    /* \"Local Repository" menu */

    // --------------

    /*  "Remote Repository" menu */
    Core::ActionContainer *remoteRepositoryMenu = Core::ActionManager::createMenu(Core::Id("Git.RemoteRepositoryMenu"));
    remoteRepositoryMenu->menu()->setTitle(tr("&Remote Repository"));
    gitContainer->addMenu(remoteRepositoryMenu);

    createRepositoryAction(remoteRepositoryMenu,
                           tr("Fetch"), Core::Id("Git.Fetch"),
                           globalcontext, true, SLOT(fetch()));

    createRepositoryAction(remoteRepositoryMenu,
                           tr("Pull"), Core::Id("Git.Pull"),
                           globalcontext, true, SLOT(pull()));

    actionCommand = createRepositoryAction(remoteRepositoryMenu,
                                           tr("Push"), Core::Id("Git.Push"),
                                           globalcontext, true, SLOT(push()));

    // --------------
    remoteRepositoryMenu->addSeparator(globalcontext);

    // "Subversion" menu
    subversionMenu->menu()->setTitle(tr("&Subversion"));
    remoteRepositoryMenu->addMenu(subversionMenu);
    // --------------
    remoteRepositoryMenu->addSeparator(globalcontext);
    createRepositoryAction(remoteRepositoryMenu,
                           tr("Manage Remotes..."), Core::Id("Git.RemoteList"),
                           globalcontext, false, SLOT(remoteList()));
    /* \"Remote Repository" menu */
    // --------------
    /*  "Git Tools" menu */
    Core::ActionContainer *gitToolsMenu = Core::ActionManager::createMenu(Core::Id("Git.GitToolsMenu"));
    gitToolsMenu->menu()->setTitle(tr("Git &Tools"));
    gitContainer->addMenu(gitToolsMenu);
    createRepositoryAction(gitToolsMenu,
                           tr("Gitk"), Core::Id("Git.LaunchGitK"),
                           globalcontext, true, &GitClient::launchGitK);
    parameterActionCommand
            = createFileAction(gitToolsMenu,
                               tr("Gitk Current File"), tr("Gitk of \"%1\""),
                               Core::Id("Git.GitkFile"), globalcontext, true, SLOT(gitkForCurrentFile()));

    parameterActionCommand
            = createFileAction(gitToolsMenu,
                               tr("Gitk for folder of Current File"), tr("Gitk for folder of \"%1\""),
                               Core::Id("Git.GitkFolder"), globalcontext, true, SLOT(gitkForCurrentFolder()));

    // --------------
    gitToolsMenu->addSeparator(globalcontext);

    m_repositoryBrowserAction
            = createRepositoryAction(gitToolsMenu,
                                     tr("Repository Browser"), Core::Id("Git.LaunchRepositoryBrowser"),
                                     globalcontext, true, &GitClient::launchRepositoryBrowser).first;
    createRepositoryAction(gitToolsMenu,
                           tr("Merge Tool"), Core::Id("Git.MergeTool"),
                           globalcontext, true, SLOT(startMergeTool()));

    /* \"Git Tools" menu */

    // --------------
    m_showAction = new QAction(tr("Show..."), this);
    Core::Command *showCommitCommand = Core::ActionManager::registerAction(m_showAction, "Git.ShowCommit", globalcontext);
    connect(m_showAction, SIGNAL(triggered()), this, SLOT(showCommit()));
    gitContainer->addAction(showCommitCommand);

    m_createRepositoryAction = new QAction(tr("Create Repository..."), this);
    Core::Command *createRepositoryCommand = Core::ActionManager::registerAction(m_createRepositoryAction, "Git.CreateRepository", globalcontext);
    connect(m_createRepositoryAction, SIGNAL(triggered()), this, SLOT(createRepository()));
    gitContainer->addAction(createRepositoryCommand);

    /* "Gerrit" */
    return gp->initialize(remoteRepositoryMenu);
void GitPlugin::submitEditorMerge(const QStringList &unmerged)
{
    m_gitClient->merge(m_submitRepository, unmerged);
}

        switch (dialog.resetType()) {
        case HardReset:
            m_gitClient->hardReset(state.topLevel(), dialog.commit());
            break;
        case SoftReset:
            m_gitClient->softReset(state.topLevel(), dialog.commit());
            break;
        }
}


void GitPlugin::startRevertCommit()
{
    startRevertOrCherryPick(true);
}

void GitPlugin::startCherryPickCommit()
{
    startRevertOrCherryPick(false);
}

void GitPlugin::startRevertOrCherryPick(bool isRevert)
{
    const VcsBase::VcsBasePluginState state = currentState();

    QString stashKeyword = (isRevert ? QLatin1String("Revert") : QLatin1String("Cherry-pick"));

    GitClient::StashResult stashResult =
            m_gitClient->ensureStash(state.topLevel(), stashKeyword);
    switch (stashResult) {
    case GitClient::StashUnchanged:
    case GitClient::Stashed:
        break;
    default:
        return;
    }

    QString workingDirectory;
    if (state.hasFile())
        workingDirectory = state.currentFileDirectory();
    else if (state.hasTopLevel())
        workingDirectory = state.topLevel();
    else
        return;

    ChangeSelectionDialog changeSelectionDialog(workingDirectory);

    if (changeSelectionDialog.exec() != QDialog::Accepted)
        return;
    const QString change = changeSelectionDialog.change();
    if (change.isEmpty())
        return;

    bool success = (isRevert ? m_gitClient->revertCommit(workingDirectory, change) :
                               m_gitClient->cherryPickCommit(workingDirectory, change));

    if (success && (stashResult == GitClient::Stashed))
        m_gitClient->stashPop(workingDirectory);
void GitPlugin::gitkForCurrentFile()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);
    m_gitClient->launchGitK(state.currentFileTopLevel(), state.relativeCurrentFile());
}

void GitPlugin::gitkForCurrentFolder()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasFile(), return);

    /*
     *  entire lower part of the code can be easily replaced with one line:
     *
     *  m_gitClient->launchGitK(dir.currentFileDirectory(), QLatin1String("."));
     *
     *  However, there is a bug in gitk in version 1.7.9.5, and if you run above
     *  command, there will be no documents listed in lower right section.
     *
     *  This is why I use lower combination in order to avoid this problems in gitk.
     *
     *  Git version 1.7.10.4 does not have this issue, and it can easily use
     *  one line command mentioned above.
     *
     */
    QDir dir(state.currentFileDirectory());
    if (QFileInfo(dir,QLatin1String(".git")).exists() || dir.cd(QLatin1String(".git")))
        m_gitClient->launchGitK(state.currentFileDirectory());
    else {
        QString folderName = dir.absolutePath();
        dir.cdUp();
        folderName = folderName.remove(0, dir.absolutePath().length() + 1);
        m_gitClient->launchGitK(dir.absolutePath(), folderName);
    }
}

    submitEditor->setAmend(amend);
    connect(submitEditor, SIGNAL(merge(QStringList)), this, SLOT(submitEditorMerge(QStringList)));
    bool rebase = m_gitClient->settings()->boolValue(GitSettings::pullRebaseKey);

    if (!rebase) {
        bool isDetached;
        QString branchRebaseConfig = m_gitClient->synchronousRepositoryBranches(state.topLevel(), &isDetached).at(0);
        if (!isDetached) {
            branchRebaseConfig.prepend(QLatin1String("branch."));
            branchRebaseConfig.append(QLatin1String(".rebase"));
            rebase = (m_gitClient->readConfigValue(state.topLevel(), branchRebaseConfig) == QLatin1String("true"));
        }
    }
    GitClient::StashResult stashResult = m_gitClient->ensureStash(state.topLevel(), QLatin1String("Pull"));
        if (m_gitClient->synchronousPull(state.topLevel(), rebase) && (stashResult == GitClient::Stashed))
void GitPlugin::startMergeTool()
{
    const VcsBase::VcsBasePluginState state = currentState();
    QTC_ASSERT(state.hasTopLevel(), return);
    m_gitClient->merge(state.topLevel());
}

            if (v.canConvert<GitClientMemberFunc>())
                return qvariant_cast<GitClientMemberFunc>(v);
    switch (m_gitClient->ensureStash(workingDirectory, QLatin1String("Apply-Patch"))) {
        if (errorMessage.isEmpty())
        else
#ifdef WITH_TESTS
#include "giteditor.h"

#include <QTest>
#include <QTextBlock>
#include <QTextDocument>

Q_DECLARE_METATYPE(FileStates)

void GitPlugin::testStatusParsing_data()
{
    QTest::addColumn<FileStates>("first");
    QTest::addColumn<FileStates>("second");

    QTest::newRow(" M") << FileStates(ModifiedFile) << FileStates(UnknownFileState);
    QTest::newRow(" D") << FileStates(DeletedFile) << FileStates(UnknownFileState);
    QTest::newRow("M ") << (ModifiedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("MM") << (ModifiedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("MD") << (ModifiedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("A ") << (AddedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("AM") << (AddedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("AD") << (AddedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("D ") << (DeletedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("DM") << (DeletedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("R ") << (RenamedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("RM") << (RenamedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("RD") << (RenamedFile | StagedFile) << FileStates(DeletedFile);
    QTest::newRow("C ") << (CopiedFile | StagedFile) << FileStates(UnknownFileState);
    QTest::newRow("CM") << (CopiedFile | StagedFile) << FileStates(ModifiedFile);
    QTest::newRow("CD") << (CopiedFile | StagedFile) << FileStates(DeletedFile);

    // Merges
    QTest::newRow("DD") << (DeletedFile | UnmergedFile | UnmergedUs | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("AA") << (AddedFile | UnmergedFile | UnmergedUs | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("UU") << (ModifiedFile | UnmergedFile | UnmergedUs | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("AU") << (AddedFile | UnmergedFile | UnmergedUs) << FileStates(UnknownFileState);
    QTest::newRow("UD") << (DeletedFile | UnmergedFile | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("UA") << (AddedFile | UnmergedFile | UnmergedThem) << FileStates(UnknownFileState);
    QTest::newRow("DU") << (DeletedFile | UnmergedFile | UnmergedUs) << FileStates(UnknownFileState);
}

void GitPlugin::testStatusParsing()
{
    CommitData data;
    QFETCH(FileStates, first);
    QFETCH(FileStates, second);
    QString output = QLatin1String("## master...origin/master [ahead 1]\n");
    output += QString::fromLatin1(QTest::currentDataTag()) + QLatin1String(" main.cpp\n");
    data.parseFilesFromStatus(output);
    QCOMPARE(data.files.at(0).first, first);
    if (second == UnknownFileState)
        QCOMPARE(data.files.size(), 1);
    else
        QCOMPARE(data.files.at(1).first, second);
}

void GitPlugin::testDiffFileResolving_data()
{
    QTest::addColumn<QByteArray>("header");
    QTest::addColumn<QByteArray>("fileName");

    QTest::newRow("New") << QByteArray(
            "diff --git a/src/plugins/git/giteditor.cpp b/src/plugins/git/giteditor.cpp\n"
            "new file mode 100644\n"
            "index 0000000..40997ff\n"
            "--- /dev/null\n"
            "+++ b/src/plugins/git/giteditor.cpp\n"
            "@@ -0,0 +1,281 @@\n\n")
        << QByteArray("src/plugins/git/giteditor.cpp");
    QTest::newRow("Deleted") << QByteArray(
            "diff --git a/src/plugins/git/giteditor.cpp b/src/plugins/git/giteditor.cpp\n"
            "deleted file mode 100644\n"
            "index 40997ff..0000000\n"
            "--- a/src/plugins/git/giteditor.cpp\n"
            "+++ /dev/null\n"
            "@@ -1,281 +0,0 @@\n\n")
        << QByteArray("src/plugins/git/giteditor.cpp");
    QTest::newRow("Normal") << QByteArray(
            "diff --git a/src/plugins/git/giteditor.cpp b/src/plugins/git/giteditor.cpp\n"
            "index 69e0b52..8fc974d 100644\n"
            "--- a/src/plugins/git/giteditor.cpp\n"
            "+++ b/src/plugins/git/giteditor.cpp\n"
            "@@ -49,6 +49,8 @@\n\n")
        << QByteArray("src/plugins/git/giteditor.cpp");
}

void GitPlugin::testDiffFileResolving()
{
    GitEditor editor(editorParameters + 3, 0);
    VcsBase::VcsBaseEditorWidget::testDiffFileResolving(&editor);
}
#endif
