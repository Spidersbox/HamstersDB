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

private slots:

signals:

};


#endif
