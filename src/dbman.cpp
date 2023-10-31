#include <QtCore/QCoreApplication>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>  // db.lastError error reporting
#include <QtSql>
#include <QMessageBox> // for debuging
#include <QDebug>
#include "dbman.h"
#include "mainwindow.h"

static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

//-----------------------------------------------------------------------------------------
QSqlError initDB(QString dbName)
{
    db.setDatabaseName(dbName);

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("hams", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery rec;
    if (!rec.exec(HAMS_SQL))
        return rec.lastError();


    if (!rec.prepare(INSERT_HAMS_SQL))
        return rec.lastError();

    addRec(rec, "KKLKQ","145.19","Walt","Republic","Ferry"," it's me :)");
    addRec(rec, "WA7EC","145.19","Sam Jenkins","Republic","Ferry","");

    return QSqlError();
}

//-----------------------------------------------------------------------------------------
QSqlError insert()
{
  QSqlQuery rec;
  if (db.isOpen())
  {
    if (!rec.prepare(INSERT_HAMS_SQL))
      return rec.lastError();

    addRec(rec, "","","","","","");
  }
  return rec.lastError();
}

//-----------------------------------------------------------------------------------------
QSqlError removeRow(QSqlRelationalTableModel *tempmodel,int row,int count)
{
  QSqlQuery rec;
  if (db.isOpen())
  {
    bool rtn=tempmodel->removeRows(row,count);
  }
  return rec.lastError();
}

//-----------------------------------------------------------------------------------------
void open(QString DBname)
{
  if (db.isOpen())
    db.close();

  db.setDatabaseName(DBname);
  if (!db.open())
  {
    QMessageBox::critical(0,"Cannot open database","Unable to establish a database connection", QMessageBox::Cancel);
        return;
  }

}

//-----------------------------------------------------------------------------------------
void closeDB()
{
if (db.isOpen())
    db.close();
}

//-----------------------------------------------------------------------------------------
void addRec(QSqlQuery &rec,const QString &call,const QString &freq,const QString &name,
            const QString &city,const QString &county,const QString &remarks)
{
  rec.addBindValue(call);
  rec.addBindValue(freq);
  rec.addBindValue(name);
  rec.addBindValue(city);
  rec.addBindValue(county);
  rec.addBindValue(remarks);
  rec.exec();
}

