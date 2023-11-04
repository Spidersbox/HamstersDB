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
#include <QSettings>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QSize>

//#include <QtGui/QApplication>  //qt4
#include <QApplication>  //qt5
#if QT_VERSION < 0x060000
  #include <QDesktopWidget>
#else
  #include <QScreen>
#endif
#include <stdlib.h>

#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "dbman.h"
#include "searchform.h"
#include "callform.h"
#include "nameform.h"

#include "ui_mainwindow.h"

class DBman;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setWindowTitle("Hamsters DB");

  // load settings from ini file
  loadSettings();


  QIcon icon(":/images/favicon"); 
  setWindowIcon(icon);

   
#ifndef Q_OS_MAC
    qApp->setWindowIcon(QIcon(":/images/favicon"));
    setWindowIcon(QIcon(":/images/favicon"));
#else
    setUnifiedTitleAndToolBarOnMac(true);
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

  // Create the toolbars
  createToolBars();

  // Create actions for the toolbar, menu bar and tray/dock icon
  createActions();

  // Create application menu bar
  createMenuBar();

  // menubar on form instead
  menuBar()->setNativeMenuBar(false);

  if(last_db.length() >1)
  {
    if(QFileInfo::exists(last_db))
    {
      DBman::open(last_db);
      clean_title="Hamsters DB "+last_db;
      setWindowTitle(clean_title);
      createView();
    }
    else
    {
      createClicked();
    }
  }

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
void MainWindow::on_NameEdit_textEdited()
{
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_FreqEdit_textEdited()
{
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_CityEdit_textEdited()
{
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_CountyEdit_textEdited()
{
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_CountryEdit_textEdited()
{
  setChanges();
}

//--------------------------------------------------------------------------------------
void MainWindow::on_RemarksEdit_textEdited()
{
  setChanges();
}

//-----------------------------------------------------------------------------------------
void MainWindow::setChanges()
{
  updateButton->setEnabled(true);
  setWindowTitle(clean_title+" not saved");
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
  QMenu *file = appMenuBar->addMenu("&File");
  file->addAction(openAction);
  file->addAction(createAction);
  file->addAction(quitAction);

  QMenu *search = appMenuBar->addMenu("&Search");
  search->addAction(searchNameAction);
  search->addAction(searchCallAction);

}

//-----------------------------------------------------------------------------------------
void MainWindow::createToolBars()
{
  newButton = new QPushButton(this);
  newButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_new); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_new_hover);}");
  newButton->setToolTip("Add a new blank record");
  newButton->setEnabled(true);

  deleteButton = new QPushButton(this);
  deleteButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_delete); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_delete_hover);}");
  deleteButton->setToolTip("Delete this record");
  deleteButton->setEnabled(true);

  nextButton = new QPushButton(this);
  nextButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_next); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_next_hover);}" ":disabled{background-color:#a9a9a9;}");
  nextButton->setToolTip("go to next record");
  nextButton->setEnabled(true);

  previousButton = new QPushButton(this);
  previousButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_previous);width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_previous_hover);}" ":disabled{background-color:#a9a9a9;}");
  previousButton->setToolTip("go to previous record");
  previousButton->setEnabled(true);

  updateButton = new QPushButton(this);
  updateButton->setStyleSheet("QPushButton{border-image:url(:/images/bt_update);width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_update_hover);}" ":disabled{background-color:#a9a9a9;}");
  updateButton->setToolTip("save changes to disk");
  updateButton->setEnabled(false);

  widget = new QWidget;
  QHBoxLayout *navLayout = new QHBoxLayout;

  navLayout->addWidget(newButton);
  navLayout->addWidget(deleteButton);
  navLayout->addWidget(previousButton);
  navLayout->addWidget(nextButton);
  navLayout->addWidget(updateButton);
  navLayout->setContentsMargins(0,0,0,0);

  widget->setLayout(navLayout);
  widget->setContentsMargins(0,0,0,0);
  ui->verticalLayout->addWidget(widget,0, Qt::AlignCenter);
  ui->verticalLayout->setContentsMargins(0,0,0,0);
}

//-----------------------------------------------------------------------------------------
void MainWindow::createActions()
{

  // main menu actions
  openAction = new QAction(QIcon(":/images/bt_open"),"&Open database file", this);
  openAction->setToolTip("Open a database file");
  createAction = new QAction(QIcon(":/images/bt_create"),"&Create new database file", this);
  createAction->setToolTip("Create a new database file");

  quitAction = new QAction(QIcon(":/images/bt_close"),"E&xit", this);
  quitAction->setToolTip("Quit application");

  searchNameAction = new QAction(QIcon(":/images/bt_search_name"),"by Name", this);
  searchNameAction->setToolTip("search by name");
  searchCallAction = new QAction(QIcon(":/images/bt_search_call"),"by Call", this);
  searchCallAction->setToolTip("search by callsign");

  // main menu signals
  connect(openAction, SIGNAL(triggered()), this, SLOT(openClicked()));
  connect(createAction, SIGNAL(triggered()), this, SLOT(createClicked()));
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quitClicked()));
  connect(searchNameAction, SIGNAL(triggered()), this, SLOT(searchNameClicked()));
  connect(searchCallAction, SIGNAL(triggered()), this, SLOT(searchCallClicked()));

  // table nav toolbar signals
  connect(newButton, SIGNAL(clicked()), this, SLOT(newClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
  connect(updateButton, SIGNAL(clicked()), this, SLOT(updateClicked()));

}


//-----------------------------------------------------------------------------------------
// Show open file dialog
void MainWindow::openClicked()
{
  QString filename=QFileDialog::getOpenFileName(this,"Open database",qApp->applicationDirPath(),
                                                "SQL DB files (*.db);;(*.sql)");
  last_db=filename;
  DBman::open(filename);
  clean_title="Hamsters DB "+filename;
  setWindowTitle(clean_title);
  createView();
}

//-----------------------------------------------------------------------------------------
// menu-create new db
void MainWindow::createClicked()
{
  QString default_path=qApp->applicationDirPath()+"/HAMS.db";

  // check to see if default db exists
  if(!QFileInfo::exists(default_path))
  {
    // default db does not exist - create it
    QSqlError err = DBman::initDB(default_path);
    if (err.type() != QSqlError::NoError)
    {
      showError(err);
      return;
    }
    clean_title="Hamsters DB "+default_path;
    setWindowTitle(clean_title);
    createView();
  }
  else
  {
    QString filename=QFileDialog::getSaveFileName(
              this,"Create database",qApp->applicationDirPath(),
              "SQL DB files (*.db)");

    QFileInfo Finfo(filename);
    QString ext = Finfo.suffix();
    if(ext !="db")
      filename+=".db";

    // check if file exists
    if(!QFileInfo::exists(filename))
    {
      // default db does not exist - create it
      QSqlError err = DBman::initDB(filename);
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
  QSqlError err =  DBman::insert();
  if (err.type() != QSqlError::NoError)
  {
    showError(err);
    return;
  }
  saveChanges();
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

  QSqlError err =  DBman::removeRow(model,cnt,1);
  if (err.type() != QSqlError::NoError)
  {
    showError(err);
    return;
  }
  saveChanges();
  ui->DBTable->setCurrentIndex(index);
}

//-----------------------------------------------------------------------------------------
// nav-update
void MainWindow::updateClicked()
{
  int cnt=mapper->currentIndex();
  QModelIndex index = ui->DBTable->model()->index(cnt, 0);
  saveChanges();
  updateButton->setEnabled(false);
  ui->DBTable->setCurrentIndex(index);
}

//-----------------------------------------------------------------------------------------
// save changes to disk
void MainWindow::saveChanges()
{
  model->database().transaction();
  if (model->submitAll())
  {
    model->database().commit();
    setWindowTitle(clean_title);
  }
  else
  {
    model->database().rollback();
    QMessageBox::warning(this,"HamstersDB","The database reported an error: "+model->lastError().text());
  }
}

//-----------------------------------------------------------------------------------------
// menu-search
void MainWindow::searchClicked()
{
  // for retrieving data from editform to mainform
  connect(searchform, SIGNAL(sendData(int)), this, SLOT(receiveSearch(int)));
  searchform->show();
}

//-----------------------------------------------------------------------------------------
// menu-search-Name
void MainWindow::searchNameClicked()
{
  // for retrieving data from editform to mainform
  connect(nameform, SIGNAL(sendData(int)), this, SLOT(receiveName(int)));
  nameform->show();
}

//-----------------------------------------------------------------------------------------
// menu-search-Call
void MainWindow::searchCallClicked()
{
  // for retrieving data from editform to mainform
  connect(callform, SIGNAL(sendData(int)), this, SLOT(receiveCall(int)));
  callform->show();
}

//-----------------------------------------------------------------------------------------
// recieves Call sign from search form
void MainWindow::receiveCall(int index)
{
  disconnect(callform, SIGNAL(sendData(int)), this, SLOT(receiveCall(int)));
  QModelIndex dbindex = ui->DBTable->model()->index(index-1, 0);
  ui->DBTable->setCurrentIndex(dbindex);
}

//-----------------------------------------------------------------------------------------
// recieves Name from search form
void MainWindow::receiveName(int index)
{
  disconnect(nameform, SIGNAL(sendData(int)), this, SLOT(receiveName(int)));
  QModelIndex dbindex = ui->DBTable->model()->index(index-1, 0);
  ui->DBTable->setCurrentIndex(dbindex);
}

//-----------------------------------------------------------------------------------------
// recieves Name or Callsign from search
void MainWindow::receiveSearch(int index)
{
  disconnect(searchform, SIGNAL(sendData(int)), this, SLOT(receiveSearch(int)));
  QModelIndex dbindex = ui->DBTable->model()->index(index-1, 0);
  ui->DBTable->setCurrentIndex(dbindex);
}

//-----------------------------------------------------------------------------------------
// update Buttons
void MainWindow::updateButtons(int row)
{
  previousButton->setEnabled(row > 0);
  nextButton->setEnabled(row < model->rowCount() - 1);
}

//-----------------------------------------------------------------------------------------
// exit this app
void MainWindow::quitClicked()
{
  DBman::closeDB();
  saveSettings();
  qApp->quit();
}

//-----------------------------------------------------------------------------------------
// exit this app
void MainWindow::shutdownClicked()
{
  DBman::closeDB();
  saveSettings();
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

  model->setHeaderData(CallIdx, Qt::Horizontal,"Call Sign");
  model->setHeaderData(NameIdx, Qt::Horizontal,"Name");
  model->setHeaderData(model->fieldIndex("Freq"),Qt::Horizontal,"CH/Freq");
  model->setHeaderData(model->fieldIndex("City"), Qt::Horizontal,"City");
  model->setHeaderData(model->fieldIndex("County"),Qt::Horizontal,"County");
  model->setHeaderData(model->fieldIndex("Country"),Qt::Horizontal,"Country");
  model->setHeaderData(model->fieldIndex("Remarks"),Qt::Horizontal,"Remarks");


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
  mapper->addMapping(ui->CountryEdit, model->fieldIndex("Country"));
  mapper->addMapping(ui->RemarksEdit, model->fieldIndex("Remarks"));

  connect(previousButton, &QAbstractButton::clicked, mapper, &QDataWidgetMapper::toPrevious);
  connect(nextButton, &QAbstractButton::clicked, mapper, &QDataWidgetMapper::toNext);
  connect(mapper, &QDataWidgetMapper::currentIndexChanged, this,&MainWindow::updateButtons);

  connect(ui->DBTable->selectionModel(),&QItemSelectionModel::currentRowChanged,
            mapper,&QDataWidgetMapper::setCurrentModelIndex);
  ui->DBTable->setCurrentIndex(model->index(0, 0));
  ui->DBTable->selectRow(0);

  ui->DBTable->setColumnWidth(0,0);//id
  ui->DBTable->setColumnWidth(1,70);//call sign
  ui->DBTable->setColumnWidth(2,70);//ch/freq
  ui->DBTable->setColumnWidth(3,100);//name
  ui->DBTable->setColumnWidth(4,100);//city
  ui->DBTable->setColumnWidth(5,100);//county
  ui->DBTable->setColumnWidth(6,100);//country
  ui->DBTable->setColumnWidth(7,550);//remarks
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
void MainWindow::optionChanged()
{
  saveSettings();
  loadSettings(); // to resize the window
}

//--------------------------------------------------------------------------------------
void MainWindow::saveSettings()
{
  QSettings settings("HamstersDB", "settings");
  settings.beginGroup("MainWindow");
  settings.setValue("size", size());
  settings.setValue("pos", pos());
  settings.endGroup();
  if(last_db.length() >1)
  {
    settings.setValue("last_openedDB",last_db);
  }
  else
  {
    settings.setValue("last_openedDB",qApp->applicationDirPath()+"/HAMS.db");
  }

}

//--------------------------------------------------------------------------------------
void MainWindow::loadSettings()
{
  //default center of screen
int x,y;
#if QT_VERSION < 0x060000
  QApplication::setAttribute(Qt::AA_DontUseNativeDialogs);//remove GtkDialog mapped without ...
  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();
  x=center.x() - width() * 0.5;
  y=center.y() - height() * 0.5;
#else
  QCoreApplication::setAttribute(Qt::AA_DontUseNativeDialogs);//remove GtkDialog warning
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect  screenGeometry = screen->geometry();
  x=screenGeometry.height()/2 -225;
  y=screenGeometry.width()/2 -400;
#endif

  QSettings settings("HamstersDB", "settings");
  settings.beginGroup("MainWindow");
  resize(settings.value("size", QSize(840,450)).toSize());
  move(settings.value("pos", QPoint(x,y)).toPoint());
  settings.endGroup();
  QString default_DB=qApp->applicationDirPath()+"/HAMS.db";
  last_db=settings.value("last_openedDB",default_DB).toString();
}

//--------------------------------------------------------------------------------------
void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

