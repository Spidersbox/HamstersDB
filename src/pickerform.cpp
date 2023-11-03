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
  connect(ui->ok_Button, &QPushButton::released, this, &PickerForm::Ok_Button_clicked);
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

    currentRow = PickerForm::ui->tableWidget->rowCount();  
    ui->tableWidget->setRowCount(currentRow + 1);
 
    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(recList[0]));
    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(recList[1]));
    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(recList[2]));
    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(recList[3]));
  }
}

//-------------------------------------------------------------------------------------------
void PickerForm::Ok_Button_clicked()
{
  int selected=ui->tableWidget->currentRow();
  QString a=ui->tableWidget->item(selected,0)->text();
  bool err;
  int recno = a.toInt(&err);
  if (!err)
  {
    qDebug() << "PickerForm: a toInt error";
  }

  emit sendDataPicker(recno);// send line back to caller
  close();
}

//-------------------------------------------------------------------------------------------
void PickerForm::Cancel_Button_clicked()
{
  close();
}

