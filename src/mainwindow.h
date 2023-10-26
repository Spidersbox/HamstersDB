#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>

#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  void closeEvent(QCloseEvent *close_trigger);
  ~MainWindow();




//    bool saveToDisk(const QString &filename, QNetworkReply* reply);

private:
  Ui::MainWindow *ui;
  QGroupBox *horizontalGroupBox;

  QMenuBar *appMenuBar;
  QAction *openAction;
  QAction *quitAction;

  /** file submenu options */
  QAction *editAction;
  QAction *saveAction;

  QAction *searchAction;

  /** Toolbar actions */
  QAction *newAction;
  QAction *deleeteAction;
  QAction *nextAction;
  QAction *previousAction;

  QPushButton *newButton;
  QPushButton *deleteButton;
  QPushButton *nextButton;
  QPushButton *previousButton;

  QPushButton *searchButton;

  /** Create the main UI actions. */
  void createActions();
  /** Create the menu bar and sub-menus. */
  void createMenuBar();
  /** Create the toolbars */
  void createToolBars();

//    void download(const QUrl &downTo,QNetworkReply *reply);

private slots:

  void on_lineEdit_textEdited(const QString &arg1);
  void initializeTable();


//    void start();
//    void getlist();
//    void getListFinished(QNetworkReply* reply);
//    void downloadFinished(QNetworkReply *reply);
//    void updateProgress(qint64 read, qint64 total);
//    bool netHandleError(QNetworkReply* reply, QString urlDownload);
//    void networkTimeout();
//    static bool isHttpRedirect(QNetworkReply *reply);

public slots:
  /** Show open file dialog */
  void openClicked();
  void saveClicked();
  void searchClicked();

  /** exit this app */
  void quitClicked();
void shutdownClicked();

  void newClicked();
  void deleteClicked();
//  void stopClicked();
  void nextClicked();
  void previousClicked();

};
#endif
