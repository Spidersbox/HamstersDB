#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
  ui->lineEdit->setText(arg1.toUpper());
}

void MainWindow::on_comboBox_editTextChanged(const QString &arg1)
{

}
