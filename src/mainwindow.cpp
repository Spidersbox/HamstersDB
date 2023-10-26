#include <QApplication>
#include <QSqlTableModel>
#include <QMenuBar>
#include <QIcon>
#include <QStyle>
#include <QTableView>
#include <QFileDialog>
#include <QFile>

#include <stdlib.h>

//#include <QtGui/QApplication>  //qt4
#include <QApplication>  //qt5
#if QT_VERSION < 0x060000
  #include <QDesktopWidget>
#else
  #include <QScreen>
#endif

#include <QMessageBox> // for debuging
#include <QDebug>

#include "connection.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  resize(800, 450);
  setWindowTitle(tr("Hamsters DB"));

  QIcon icon(":/images/favicon"); 
  setWindowIcon(icon);

  /** center form on screen */
#if QT_VERSION < 0x060000
  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();
  move(center.x() - width() * 0.5, center.y() - height() * 0.5);
#else
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





/*
  if (!createConnection())
    return "cound not connect";
*/

//  QSqlTableModel model;

//  initializeModel(&model);

//  QTableView *view1 = createView(&model, QObject::tr("Table Model (View 1)"));
//  QTableView *view2 = createView(&model, QObject::tr("Table Model (View 2)"));

//  view1->show();
//  view2->move(view1->x() + view1->width() + 20, view1->y());
//  view2->show();

}

//--------------------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *close_trigger)
{
  shutdownClicked();
}

//--------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------------------------------
void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
  ui->lineEdit->setText(arg1.toUpper());
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
  file->addAction(saveAction);
  file->addAction(quitAction);

//  QMenu *search = appMenuBar->addMenu(tr("&F3"));
////  QMenu *submenu=settings->addMenu("&Playlist");
//  search->addAction(searchAction);

}

//-----------------------------------------------------------------------------------------
void MainWindow::createToolBars()
{

  newButton = new QPushButton(this);
  newButton->setStyleSheet("*{border-image:url(:/images/bt_new); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_new_hover);}");
  newButton->setEnabled(true);

  deleteButton = new QPushButton(this);
  deleteButton->setStyleSheet("*{border-image:url(:/images/bt_delete); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_delete_hover);}");
  deleteButton->setEnabled(true);

  nextButton = new QPushButton(this);
  nextButton->setStyleSheet("*{border-image:url(:/images/bt_next); width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_next_hover);}");
  nextButton->setEnabled(true);

  previousButton = new QPushButton(this);
  previousButton->setStyleSheet("*{border-image:url(:/images/bt_previous);width:32px; height:32px;}" ":hover{ border-image: url(:/images/bt_previous_hover);}");
  previousButton->setEnabled(true);


  horizontalGroupBox = new QGroupBox;
  QHBoxLayout *navLayout = new QHBoxLayout;

  navLayout->addWidget(newButton);
  navLayout->addWidget(deleteButton);
  navLayout->addWidget(nextButton);
  navLayout->addWidget(previousButton);
  navLayout->setContentsMargins(0,0,0,0);

  horizontalGroupBox->setLayout(navLayout);
  horizontalGroupBox->setContentsMargins(0,0,0,0);

  ui->statusBar->addWidget(horizontalGroupBox);
}

//-----------------------------------------------------------------------------------------
void MainWindow::createActions()
{

  // main menu actions
  openAction = new QAction(QIcon(":/images/bt_open"), tr("&Open database file"), this);
  openAction->setToolTip(tr("Open a database file"));
  saveAction = new QAction(QIcon(":/images/bt_save"), tr("&Save database to a file"), this);
  saveAction->setToolTip(tr("save the database"));
  quitAction = new QAction(QIcon(":/images/bt_close"), tr("E&xit"), this);
  quitAction->setToolTip(tr("Quit application"));


  // main menu signals
  connect(openAction, SIGNAL(triggered()), this, SLOT(openClicked()));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(saveClicked()));
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quitClicked()));

  // table nav toolbar signals
  connect(newButton, SIGNAL(clicked()), this, SLOT(newClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
  connect(nextButton, SIGNAL(clicked()), this, SLOT(nextClicked()));
  connect(previousButton, SIGNAL(clicked()), this, SLOT(previousClicked()));

}


//-----------------------------------------------------------------------------------------
/** Show open file dialog */
void MainWindow::openClicked()
{
  QString filename=QFileDialog::getOpenFileName(
              this,
              "Open database",
              "/",
              "SQL DB files (*.sql)");

  QFile file(filename);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
/*
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    playlist.clear();
    ui->listWidget->clear();
    ui->listWidget2->clear();
    QTextStream textStream(&file);
    while (!textStream.atEnd())
    {
      QString line=textStream.readLine();
      playlist<<line;
      ui->listWidget->addItem(line);
    }
*/
    file.close();
    QApplication::restoreOverrideCursor();
//    stopClicked();
//    loadPlayer();
  }
  else
  {
    QString mess="Could not open file: "+filename;
    QMessageBox::warning(this,"Random Player",mess);
  }
}

//-----------------------------------------------------------------------------------------
// menu-new
void MainWindow::newClicked()
{
  QMessageBox::warning(this,"warning","New was clicked");
}

//-----------------------------------------------------------------------------------------
// menu-save
void MainWindow::saveClicked()
{
  QMessageBox::warning(this,"warning","save was clicked");
}

//-----------------------------------------------------------------------------------------
// menu-search
void MainWindow::searchClicked()
{
  QMessageBox::warning(this,"warning","search was clicked");
}

//-----------------------------------------------------------------------------------------
/** delete button */
void MainWindow::deleteClicked()
{
  QMessageBox::warning(this,"warning","delete was clicked");
}

//-----------------------------------------------------------------------------------------
/** next button */
void MainWindow::nextClicked()
{
  QMessageBox::warning(this,"warning","Next was clicked");
}

//-----------------------------------------------------------------------------------------
void MainWindow::previousClicked()
{/** previous button */
  QMessageBox::warning(this,"warning","previous was clicked");
//  player->stop();
//  player->play();
}

//-----------------------------------------------------------------------------------------
/** exit this app */
void MainWindow::quitClicked()
{
  QMessageBox::warning(this,"warning","quit was clicked");
  qApp->quit();
}

//-----------------------------------------------------------------------------------------
/** exit this app */
void MainWindow::shutdownClicked()
{
  QMessageBox::warning(this,"warning","App shut down detected");
  qApp->quit();
}


//--------------------------------------------------------------------------------------
void MainWindow::initializeTable()
{
//  ui->tableView->setTable("person");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select();

//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));

//  ui->setTable("person");

//  MainWindow->setEditStrategy(QSqlTableModel::OnManualSubmit);
//  MainWindow->select();

//  MainWindow->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//  MainWindow->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
//  MainWindow->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

//--------------------------------------------------------------------------------------
QTableView *createView(QSqlTableModel *model, const QString &title = "")
{
//    QTableView *view = new QTableView;
//  ui->tableView->setModel(model);
//  ui->tableView->setWindowTitle(title);
//    return view;
}

