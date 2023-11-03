#if QT_VERSION < 0x060000
  #include <QDesktopWidget>
#else
  #include <QScreen>
#endif
#include <QTableWidget>

#include "nameform.h"
#include "ui_PickerForm.h"
#include "dbman.h"
#include "pickerform.h"


PickerForm::PickerForm(QStringList recordList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PickerForm)
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

  SetSignals();
  grokList(recordList);
}

PickerForm::~PickerForm()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------
void PickerForm::SetSignals()
{
  // button signals
//  connect(ui->Name_Button, &QPushButton::released, this, &NameForm::Name_Button_clicked);
  connect(ui->cancel_Button, &QPushButton::released, this, &PickerForm::Cancel_Button_clicked);
}


//-------------------------------------------------------------------------------------------
void PickerForm::grokList(QStringList recordList)
{
  int rec=recordList.count();
  int currentRow;
  for(int t=0;t<rec;t++)
  {
    QStringList recList=recordList[t].split(",");
    int recno=recList[0].toInt();

qDebug() <<"recno "<< recno << recList[1]<< recList[2]<< recList[3];

    currentRow = PickerForm::ui->tableWidget->rowCount();  
    ui->tableWidget->setRowCount(currentRow + 1);
 
    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(recList[0]));
    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(recList[1]));
    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(recList[2]));
    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(recList[3]));

  }

}

/*
//-------------------------------------------------------------------------------------------
void NameForm::Name_Button_clicked()
{
  QString line="%"+ui->lineEdit->text()+"%";

  QStringList recordList=DBman::Select_Name(line);
qDebug()<<recordList;

  int rec=recordList.count();
  if(rec<1) // no records found
  {
qDebug() <<"rec "<< rec;

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

*/
//-------------------------------------------------------------------------------------------
void PickerForm::Cancel_Button_clicked()
{
  close();
}

