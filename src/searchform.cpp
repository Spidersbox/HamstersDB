#if QT_VERSION < 0x060000
  #include <QDesktopWidget>
#else
  #include <QScreen>
#endif

#include "searchform.h"
#include "ui_SearchForm.h"
#include "mainwindow.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
  ui->setupUi(this);

// center form on screen
#if QT_VERSION < 0x060000
  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();
  move(center.x() - width() * 0.5, center.y() - height() * 0.5);
#else
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect  screenGeometry = screen->geometry();
  int height = screenGeometry.height()/2;
  int width = screenGeometry.width()/2;
  move(width-324,height-250);
#endif

  // Create actions for the toolbar, menu bar and tray/dock icon
  SetSignals();

}

SearchForm::~SearchForm()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------
void SearchForm::SetSignals()
{
  /** button signals */
  connect(ui->Call_Button, &QPushButton::released, this, &SearchForm::Call_Button_clicked);
  connect(ui->Name_Button, &QPushButton::released, this, &SearchForm::Name_Button_clicked);
  connect(ui->Cancel_Button, &QPushButton::released, this, &SearchForm::Cancel_Button_clicked);
}

//-------------------------------------------------------------------------------------------
void SearchForm::Call_Button_clicked()
{
  QString line=ui->lineEdit->text();
  emit sendData(line,QString("Call"));// send line to MainWindow
  close();
}

//-------------------------------------------------------------------------------------------
void SearchForm::Name_Button_clicked()
{
  QString line=ui->lineEdit->text();
  emit sendData(line,QString("Name"));// send line to MainWindow
  close();
}

//-------------------------------------------------------------------------------------------
void SearchForm::Cancel_Button_clicked()
{
  close();
}

