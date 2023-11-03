#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QTableWidget>
#include <QtSql>
#include <QDataWidgetMapper>

#include "ui_mainwindow.h"
#include "callform.h"
#include "nameform.h"
#include "searchform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DBman;


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  void closeEvent(QCloseEvent *close_trigger);
  QSqlRelationalTableModel *model = nullptr;
  QString last_db;
  QString clean_title;
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  CallForm *callform=new CallForm();
  NameForm *nameform=new NameForm();
  SearchForm *searchform=new SearchForm();

  virtual void  keyPressEvent(QKeyEvent *event);
  QGroupBox *horizontalGroupBox;
  int CallIdx = 0;
  int NameIdx = 0;
  QDataWidgetMapper *mapper;

  QMenuBar *appMenuBar;

  QAction *openAction;
  QAction *createAction;
  QAction *quitAction;
  QAction *searchAction;
  QAction *searchNameAction;
  QAction *searchCallAction;

  /** file submenu options */
  QAction *editAction;


  /** Toolbar actions */
  QAction *newAction;
  QAction *deleateAction;
  QAction *nextAction;
  QAction *previousAction;

  QPushButton *newButton;
  QPushButton *deleteButton;
  QPushButton *nextButton;
  QPushButton *previousButton;
  QPushButton *updateButton;

  /** Create the main UI actions. */
  void createActions();

  /** Create the menu bar and sub-menus. */
  void createMenuBar();

  /** Create the toolbars */
  void createToolBars();

  void loadSettings();
  void saveSettings();
  void optionChanged();

  void saveChanges();
  void createView();
  void showError(const QSqlError &err);

private slots:

  void on_CallEdit_textEdited(const QString &arg1);
  void on_NameEdit_textEdited();
  void on_FreqEdit_textEdited();
  void on_CityEdit_textEdited();
  void on_CountyEdit_textEdited();
  void on_RemarksEdit_textEdited();
  void setChanges();

  /** for retrieving data from editforms to mainform */
  void receiveCall(int);
  void receiveName(int);
  void receiveSearch(int);

public slots:
  /** Show open file dialog */
  void openClicked();
  void createClicked();
  void searchClicked();
  void searchNameClicked();
  void searchCallClicked();

  /** exit this app */
  void quitClicked();
  void shutdownClicked();

  void newClicked();
  void deleteClicked();
  void updateClicked();
  void updateButtons(int row);

};
#endif
