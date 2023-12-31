#ifndef NAMEFORM_H
#define NAMEFORM_H

#include <QWidget>
#include "pickerform.h"

namespace Ui
{
  class NameForm;
}

class NameForm : public QWidget
{
  Q_OBJECT

public:
  explicit NameForm(QWidget *parent =0);
  ~NameForm();

private:
  Ui::NameForm *ui;
  void SetSignals();

private slots:
  void Name_Button_clicked();
  void Cancel_Button_clicked();
  void receiveNameRec(int);

signals:
  void sendData(int); //receive from mainwindow
};


#endif
