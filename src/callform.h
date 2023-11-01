#ifndef CALLFORM_H
#define CALLFORM_H

#include <QWidget>


namespace Ui
{
  class CallForm;
}

class CallForm : public QWidget
{
  Q_OBJECT

public:
  explicit CallForm(QWidget *parent =0);
  ~CallForm();

private:
  Ui::CallForm *ui;
  void SetSignals();

private slots:
  void Call_Button_clicked();
  void Cancel_Button_clicked();

signals:
  void sendData(QString);
};


#endif
