#ifndef PICKERFORM_H
#define PICKERFORM_H

#include <QWidget>


namespace Ui
{
  class PickerForm;
}

class PickerForm : public QWidget
{
  Q_OBJECT

public:
  explicit PickerForm(QStringList recordList,QWidget *parent =0);
  ~PickerForm();
private:
  Ui::PickerForm *ui;
  void SetSignals();
  void grokList(QStringList);

private slots:
//  void Name_Button_clicked();
  void Cancel_Button_clicked();

signals:
//  void sendData(QString,int);

};


#endif
