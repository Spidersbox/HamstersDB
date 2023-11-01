#include <QApplication>
#include <QSqlTableModel>
#include <QMenuBar>
#include <QIcon>
#include <QStyle>
#include <QTableView>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QKeyEvent>

#include <stdlib.h>
#include <QtSql>
#include <QDataWidgetMapper>

//#include <QtGui/QApplication>  //qt4
#include <QApplication>  //qt5
#if QT_VERSION < 0x060000
  #include <QDesktopWidget>
#else
  #include <QScreen>
#endif

#include <QMessageBox> // for debuging
#include <QDebug>

#include "mainwindow.h"
#include "dbman.h"
#include "searchform.h"
#include "callform.h"
#include "nameform.h"

#include "ui_mainwindow.h"
//#include "ui_SearchForm.h"
//#include "ui_NameForm.h"
//#include "ui_CallForm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  resize(840, 450);
  setWindowTitle(tr("Hamsters DB"));

  QIcon icon(":/images/favicon"); 
  setWindowIcon(icon);

  /** center form on screen */
#if QT_VERSION < 0x060000
  QApplication::setAttribute(Qt::AA_DontUseNativeDialogs);//remove GtkDialog mapped without ...
  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();
  move(center.x() - width() * 0.5, center.y() - height() * 0.5);
#else
  QCoreApplication::setAttribute(Qt::AA_DontUseNativeDialogs);//remove GtkDialog warning
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect  screenGeometry = screen->geometry();
  int height = screenGeometry.height()/2;
  int width = screenGeometry.width()/2;
  move(width-400,height-225);
#endif
   
#ifndef Q_OS_MAC
    qApp->setWindowIcon(QIcon(":/images/favicon"));
    setWindowIcon(QIcon(":/images/favicon"));
#else
    setUnifiedTitleAndToolBarOnMac(true);
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

  /** Create the toolbars */
  createToolBars();

  /** Create actions for the toolbar, menu bar and tray/dock icon */
  createActions();

  /** Create application menu bar */
  createMenuBar();
  /** menubar on form instead */
  menuBar()->setNativeMenuBar(false);


}

//--------------------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *close_trigger)
{
  close_trigger=close_trigger; //make unused param warning go away
  shutdownClicked();
}

//--------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete ui;
}

//--------------------------------------------------------------------------------------
void MainWindow::on_CallEdit_textEdited(const QString &arg1)
{
  ui->CallEdit->setText(arg1.toUpper());
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_NameEdit_textEdited(const QString &arg1)
{
//  ui->CallEdit->setText(arg1.toUpper());
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_FreqEdit_textEdited(const QString &arg1)
{
//  ui->CallEdit->setText(arg1.toUpper());
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_CityEdit_textEdited(const QString &arg1)
{
//  ui->CallEdit->setText(arg1.toUpper());
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_CountyEdit_textEdited(const QString &arg1)
{
//  ui->CallEdit->setText(arg1.toUpper());
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_RemarksEdit_textEdited(const QString &arg1)
{
//  ui->CallEdit->setText(arg1.toUpper());
  setChanges();
}

//-----------------------------------------------------------------------------------------
void MainWindow::setChanges()
{
  updateButton->setEnabled(true);
}

//-----------------------------------------------------------------------------------------
void MainWindow::createMenuBar()
{

#ifdef Q_OS_MAC
  // Create a decoupled menu bar on Mac
  // which stays even if the window is closed
  appMenuBar = new QMenuBar();
#else
  // Get the main window's menu bar on other platforms
  appMenuBar = menuBar();
#endif

  // Configure the menus
  QMenu *file = appMenuBar->addMenu(tr("&File"));
  file->addAction(openAction);
  file->addAction(createAction);
  file->addAction(saveAction);
  file->addAction(quitAction);

  QMenu *search = appMenuBar->addMenu(tr("&Search"));
  search->addAction(searchNameAction);
  search->addAction(searchCallAction);

}

//-----------------------------------------------------------------------------------------
void MainWindow::createToolBars()
{
  newButton = new QPushButton(this);
  newButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_new); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_new_hover);}");
  newButton->setToolTip(tr("Add a new blank record"));
  newButton->setEnabled(true);

  deleteButton = new QPushButton(this);
  deleteButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_delete); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_delete_hover);}");
  deleteButton->setToolTip(tr("Delete this record"));
  deleteButton->setEnabled(true);

  nextButton = new QPushButton(this);
  nextButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_next); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_next_hover);}" ":disabled{background-color:#a9a9a9;}");
  nextButton->setToolTip(tr("go to next record"));
  nextButton->setEnabled(true);

  previousButton = new QPushButton(this);
  previousButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_previous);width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_previous_hover);}" ":disabled{background-color:#a9a9a9;}");
  previousButton->setToolTip(tr("go to previous record"));
  previousButton->setEnabled(true);

  updateButton = new QPushButton(this);
  updateButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_update);width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_update_hover);}" ":disabled{background-color:#a9a9a9;}");
  updateButton->setToolTip(tr("save changes to disk"));
  updateButton->setEnabled(false);

  horizontalGroupBox = new QGroupBox;
  QHBoxLayout *navLayout = new QHBoxLayout;

  navLayout->addWidget(newButton);
  navLayout->addWidget(deleteButton);
  navLayout->addWidget(previousButton);
  navLayout->addWidget(nextButton);
  navLayout->addWidget(updateButton);
  navLayout->setContentsMargins(0,0,0,0);

  horizontalGroupBox->setLayout(navLayout);
  ui->verticalLayout->addWidget(horizontalGroupBox,0, Qt::AlignCenter);
}

//-----------------------------------------------------------------------------------------
void MainWindow::createActions()
{

  // main menu actions
  openAction = new QAction(QIcon(":/images/bt_open"), tr("&Open database file"), this);
  openAction->setToolTip(tr("Open a database file"));
  createAction = new QAction(QIcon(":/images/bt_create"), tr("&Create new database file"), this);
  createAction->setToolTip(tr("Create a new database file"));
  saveAction = new QAction(QIcon(":/images/bt_save"), tr("&Save database to a file"), this);
  saveAction->setToolTip(tr("save the database"));

  quitAction = new QAction(QIcon(":/images/bt_close"), tr("E&xit"), this);
  quitAction->setToolTip(tr("Quit application"));

  searchNameAction = new QAction(QIcon(":/images/bt_search_name"), tr("by Name"), this);
  searchNameAction->setToolTip(tr("search by name"));
  searchCallAction = new QAction(QIcon(":/images/bt_search_call"), tr("by Call"), this);
  searchCallAction->setToolTip(tr("search by callsign"));

  // main menu signals
  connect(openAction, SIGNAL(triggered()), this, SLOT(openClicked()));
  connect(createAction, SIGNAL(triggered()), this, SLOT(createClicked()));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(saveClicked()));
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quitClicked()));
  connect(searchNameAction, SIGNAL(triggered()), this, SLOT(searchNameClicked()));
  connect(searchCallAction, SIGNAL(triggered()), this, SLOT(searchCallClicked()));

  // table nav toolbar signals
  connect(newButton, SIGNAL(clicked()), this, SLOT(newClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
  connect(updateButton, SIGNAL(clicked()), this, SLOT(updateClicked()));

}


//-----------------------------------------------------------------------------------------
/** Show open file dialog */
void MainWindow::openClicked()
{
  QString filename=QFileDialog::getOpenFileName(this,"Open database",qApp->applicationDirPath(),
                                                "SQL DB files (*.sql)");
  open(filename);
  createView();
}

//-----------------------------------------------------------------------------------------
// menu-create new db
void MainWindow::createClicked()
{
  QString default_path=qApp->applicationDirPath()+"/HAMS.sql";

  // check to see if default db exists
  if(!QFileInfo::exists(default_path))
  {
    // default db does not exist - create it
    QSqlError err = initDB(default_path);
    if (err.type() != QSqlError::NoError)
    {
      showError(err);
      return;
    }
    createView();
  }
  else
  {
    QString filename=QFileDialog::getSaveFileName(
              this,"Create database",qApp->applicationDirPath(),
              "SQL DB files (*.sql)");

    QFileInfo Finfo(filename);
    QString ext = Finfo.suffix();
    if(ext !="sql")
      filename+=".sql";

    // check if file exists
    if(!QFileInfo::exists(filename))
    {
      // default db does not exist - create it
      QSqlError err = initDB(filename);
      if (err.type() != QSqlError::NoError)
      {
        showError(err);
        return;
      }
      createView();
    }
  }
}
//-----------------------------------------------------------------------------------------
// nav-new
void MainWindow::newClicked()
{
  QSqlError err =  insert();
  if (err.type() != QSqlError::NoError)
  {
    showError(err);
    return;
  }
  saveClicked();
  mapper->toLast();

  int cnt=mapper->currentIndex();
  QModelIndex index = ui->DBTable->model()->index(cnt, 0);
  ui->DBTable->setCurrentIndex(index);
}

//-----------------------------------------------------------------------------------------
// nav-delete
void MainWindow::deleteClicked()
{
  int cnt=mapper->currentIndex();
  QModelIndex index = ui->DBTable->model()->index(cnt-1, 0);

  QSqlError err =  removeRow(model,cnt,1);
  if (err.type() != QSqlError::NoError)
  {
    showError(err);
    return;
  }
  saveClicked();
  ui->DBTable->setCurrentIndex(index);
}

//-----------------------------------------------------------------------------------------
// nav-update
void MainWindow::updateClicked()
{
  int cnt=mapper->currentIndex();
  QModelIndex index = ui->DBTable->model()->index(cnt, 0);
  saveClicked();
  updateButton->setEnabled(false);
  ui->DBTable->setCurrentIndex(index);
}

//-----------------------------------------------------------------------------------------
// menu-save
void MainWindow::saveClicked()
{
  model->database().transaction();
  if (model->submitAll())
  {
    model->database().commit();
  }
  else
  {
    model->database().rollback();
    QMessageBox::warning(this, tr("HamstersDB"),tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
  }
}

//-----------------------------------------------------------------------------------------
// menu-search
void MainWindow::searchClicked()
{
//  QMessageBox::warning(this,"warning","search was clicked");
//  SearchForm *searchform = new SearchForm();
  /** for retrieving data from editform to mainform */
  connect(searchform, SIGNAL(sendData(QString,QString)), this, SLOT(receiveSearch(QString,QString)));
  searchform->show();
}

//-----------------------------------------------------------------------------------------
// menu-search-Name
void MainWindow::searchNameClicked()
{
  /** for retrieving data from editform to mainform */
  connect(nameform, SIGNAL(sendData(QString)), this, SLOT(receiveName(QString)));
  nameform->show();
}

//-----------------------------------------------------------------------------------------
// menu-search-Call
void MainWindow::searchCallClicked()
{
//  QMessageBox::warning(this,"warning","search-Call was clicked");
//   *callform = new CallForm();
  /** for retrieving data from editform to mainform */
  connect(callform, SIGNAL(sendData(QString)), this, SLOT(receiveCall(QString)));
  callform->show();
}

//-----------------------------------------------------------------------------------------
/** recieves Call sign from search form */
void MainWindow::receiveCall(QString line)
{

  QMessageBox::warning(this,"warning","receiveCall got "+line);

  disconnect(callform, SIGNAL(sendData(QString)), this, SLOT(receiveCall(QString)));
}

//-----------------------------------------------------------------------------------------
/** recieves Name from search form */
void MainWindow::receiveName(QString line)
{

  QMessageBox::warning(this,"warning","receiveName got "+line);

  disconnect(nameform, SIGNAL(sendData(QString)), this, SLOT(receiveName(QString)));
}

//-----------------------------------------------------------------------------------------
/** recieves Name or Callsign from search form */
void MainWindow::receiveSearch(QString line,QString type)
{

  QMessageBox::warning(this,"warning","receiveSearch got "+line+" and "+type);

  disconnect(searchform, SIGNAL(sendData(QString,QString)), this, SLOT(receiveSearch(QString,QString)));
}

//-----------------------------------------------------------------------------------------
// update Buttons
void MainWindow::updateButtons(int row)
{
  previousButton->setEnabled(row > 0);
  nextButton->setEnabled(row < model->rowCount() - 1);
}

//-----------------------------------------------------------------------------------------
/** exit this app */
void MainWindow::quitClicked()
{
  closeDB();
  qApp->quit();
}

//-----------------------------------------------------------------------------------------
/** exit this app */
void MainWindow::shutdownClicked()
{
  closeDB();
  qApp->quit();
}

//--------------------------------------------------------------------------------------
void MainWindow::createView()
{
  model = new QSqlRelationalTableModel(ui->DBTable);
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  model->setTable("hams");

  // Remember the indexes of the columns:
  CallIdx = model->fieldIndex("Call");
  NameIdx = model->fieldIndex("Name");

  model->setHeaderData(CallIdx, Qt::Horizontal, tr("Call Sign"));
  model->setHeaderData(NameIdx, Qt::Horizontal, tr("Name"));
  model->setHeaderData(model->fieldIndex("Freq"),Qt::Horizontal, tr("CH/Freq"));
  model->setHeaderData(model->fieldIndex("City"), Qt::Horizontal, tr("City"));
  model->setHeaderData(model->fieldIndex("County"),Qt::Horizontal, tr("County"));
  model->setHeaderData(model->fieldIndex("Remarks"),Qt::Horizontal, tr("Remarks"));


// Populate the model:
  if (!model->select())
  {
    showError(model->lastError());
    return;
  }
  ui->DBTable->setModel(model);

  mapper = new QDataWidgetMapper(this);
  mapper->setModel(model);
  mapper->setItemDelegate(new QSqlRelationalDelegate(this));
  mapper->addMapping(ui->CallEdit, model->fieldIndex("Call"));
  mapper->addMapping(ui->FreqEdit, model->fieldIndex("Freq"));
  mapper->addMapping(ui->NameEdit, model->fieldIndex("Name"));
  mapper->addMapping(ui->CityEdit, model->fieldIndex("City"));
  mapper->addMapping(ui->CountyEdit, model->fieldIndex("County"));
  mapper->addMapping(ui->RemarksEdit, model->fieldIndex("Remarks"));

  connect(previousButton, &QAbstractButton::clicked, mapper, &QDataWidgetMapper::toPrevious);
  connect(nextButton, &QAbstractButton::clicked, mapper, &QDataWidgetMapper::toNext);
  connect(mapper, &QDataWidgetMapper::currentIndexChanged, this,&MainWindow::updateButtons);

//  mapper->addMapping(typeComboBox, typeIndex);

  connect(ui->DBTable->selectionModel(),&QItemSelectionModel::currentRowChanged,
            mapper,&QDataWidgetMapper::setCurrentModelIndex);
  ui->DBTable->setCurrentIndex(model->index(0, 0));
  ui->DBTable->selectRow(0);

  ui->DBTable->setColumnWidth(0,0);//id
  ui->DBTable->setColumnWidth(1,80);//call sign
  ui->DBTable->setColumnWidth(2,80);//ch/freq
  ui->DBTable->setColumnWidth(3,100);//name
  ui->DBTable->setColumnWidth(4,100);//city
  ui->DBTable->setColumnWidth(5,100);//county
  ui->DBTable->setColumnWidth(6,550);//remarks
}

//--------------------------------------------------------------------------------------
void MainWindow::keyPressEvent ( QKeyEvent * event ) 
{
  switch(event->key())
  {
    case Qt::Key_F3:
      searchClicked();  //we want to handle this
      break;
    default:
      QWidget::keyPressEvent(event);  //let others handle this
  }
}

//--------------------------------------------------------------------------------------
void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

