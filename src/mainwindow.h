#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QTableWidget>
#include <QtSql>
#include <QDataWidgetMapper>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//class SearchForm;
//class CallForm;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  void closeEvent(QCloseEvent *close_trigger);
  QSqlRelationalTableModel *model = nullptr;

  ~MainWindow();

private:
  Ui::MainWindow *ui;
  virtual void  keyPressEvent(QKeyEvent *event);
  QGroupBox *horizontalGroupBox;
//  QSqlRelationalTableModel *model = nullptr;
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
  QAction *saveAction;


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

//  QPushButton *searchButton;

  /** Create the main UI actions. */
  void createActions();

  /** Create the menu bar and sub-menus. */
  void createMenuBar();

  /** Create the toolbars */
  void createToolBars();

  void createView();
  void showError(const QSqlError &err);

private slots:

  void on_CallEdit_textEdited(const QString &arg1);
  void on_NameEdit_textEdited(const QString &arg1);
  void on_FreqEdit_textEdited(const QString &arg1);
  void on_CityEdit_textEdited(const QString &arg1);
  void on_CountyEdit_textEdited(const QString &arg1);
  void on_RemarksEdit_textEdited(const QString &arg1);
  void setChanges();


public slots:
  /** Show open file dialog */
  void openClicked();
  void createClicked();
  void saveClicked();
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
