#if QT_VERSION < 0x060000
  #include <QDesktopWidget>
#else
  #include <QScreen>
#endif

#include "nameform.h"
#include "ui_NameForm.h"
#include "dbman.h"
#include "mainwindow.h"

NameForm::NameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NameForm)
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

NameForm::~NameForm()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------
void NameForm::SetSignals()
{
  /** button signals */
  connect(ui->Name_Button, &QPushButton::released, this, &NameForm::Name_Button_clicked);
  connect(ui->Cancel_Button, &QPushButton::released, this, &NameForm::Cancel_Button_clicked);
}

//-------------------------------------------------------------------------------------------
void NameForm::Name_Button_clicked()
{
  QString line="%"+ui->lineEdit->text()+"%";

  QStringList recordList=DBman::Select_Name(line);
qDebug()<<recordList;

  int rec=recordList.count();
  if(rec<1)
  {
// no records found
  }

  if(rec==1) // found only one record, return it
  {
    QStringList recList=recordList[0].split(",");
    int recno=recList[0].toInt();
qDebug() <<"recno "<< recno;
qDebug() <<"call "<< recList[1];
qDebug() <<"name "<< recList[2];
    emit sendData(recList[2],recno);// send line to MainWindow
    close();
  }

  if(rec>1)
  {
// found more than one, pop up list
  }

//  emit sendData(line);// send line to MainWindow
//  close();
}

//-------------------------------------------------------------------------------------------
void NameForm::Cancel_Button_clicked()
{
  close();
}

