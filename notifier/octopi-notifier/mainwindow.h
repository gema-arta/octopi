#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../src/unixcommand.h"

#include <QProcess>
#include <QString>
#include <QMainWindow>
#include <QSystemTrayIcon>

class QIcon;
class QMenu;
class QAction;
class QFileSystemWatcher;
class PacmanHelperClient;

#ifdef KSTATUS
  class KStatusNotifierItem;
#endif

enum ExecOpt { ectn_NORMAL_EXEC_OPT, ectn_SYSUPGRADE_EXEC_OPT, ectn_SYSUPGRADE_NOCONFIRM_EXEC_OPT };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

  explicit MainWindow(QWidget *parent = 0);
    
private slots:

  void pacmanHelperTimerTimeout();
  void afterPacmanHelperSyncDatabase();
  void execSystemTrayActivated(QSystemTrayIcon::ActivationReason);
  void refreshAppIcon();
  void runOctopi(ExecOpt execOptions = ectn_SYSUPGRADE_EXEC_OPT);
  void runOctopiSysUpgrade();

  inline void startOctopi() { runOctopi(ectn_NORMAL_EXEC_OPT); }

  void aboutOctopiNotifier();
  void hideOctopi();
  void exitNotifier();
  void doSystemUpgrade();
  void doSystemUpgradeFinished(int, QProcess::ExitStatus);
  void toggleEnableInterface(bool state);

private:

  int m_numberOfOutdatedPackages;
  int m_numberOfOutdatedAURPackages;
  bool m_systemUpgradeDialog;
  CommandExecuting m_commandExecuting;
  UnixCommand *m_unixCommand;

  QAction *m_actionOctopi;
  QAction *m_actionSystemUpgrade;
  QAction *m_actionAbout;
  QAction *m_actionExit;
  QIcon m_icon;
  QStringList *m_outdatedPackageList;
  QStringList *m_outdatedAURPackageList;
  QTimer *m_pacmanHelperTimer;

#ifdef KSTATUS
  KStatusNotifierItem * m_systemTrayIcon;
#else
  QSystemTrayIcon *m_systemTrayIcon;
#endif

  QMenu *m_systemTrayIconMenu;
  QFileSystemWatcher *m_pacmanDatabaseSystemWatcher;
  PacmanHelperClient *m_pacmanHelperClient;

  bool _isSUAvailable();
  void initSystemTrayIcon();
  void sendNotification(const QString &msg);
};

#endif // MAINWINDOW_H
