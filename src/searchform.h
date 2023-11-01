#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>


namespace Ui
{
  class SearchForm;
}

class SearchForm : public QWidget
{
  Q_OBJECT

public:
  explicit SearchForm(QWidget *parent =0);
  ~SearchForm();

private:
  Ui::SearchForm *ui;
  void SetSignals();

private slots:
  void Call_Button_clicked();
  void Name_Button_clicked();
  void Cancel_Button_clicked();

signals:
  void sendData(QString,QString);

};


#endif
