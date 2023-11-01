#ifndef NAMEFORM_H
#define NAMEFORM_H

#include <QWidget>


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

private slots:

signals:

};


#endif
