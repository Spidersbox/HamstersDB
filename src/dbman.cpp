#include <QtCore/QCoreApplication>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>  // db.lastError error reporting
#include <QtSql>
#include <QMessageBox> // for debuging
#include <QDebug>

#include "dbman.h"
#include "mainwindow.h"
#include "nameform.h"

static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

class DBman;


//-----------------------------------------------------------------------------------------
QSqlError DBman::initDB(QString dbName)
{
  db.setDatabaseName(dbName);

  if(!db.open())
    return db.lastError();

  QStringList tables = db.tables();
  if(tables.contains("hams", Qt::CaseInsensitive))
    return QSqlError();

  QSqlQuery query;
  if(!query.exec(Create_HAMS_Table))
    return query.lastError();

  if(!query.prepare(Insert_HAMS))
    return query.lastError();

  addRec(query, "KK7LKQ","145.19","Walt","Republic","Ferry"," it's me :)");
  addRec(query, "WA7EC","145.19","Sam Jenkins","Republic","Ferry","");

  return QSqlError();
}

//-----------------------------------------------------------------------------------------
QSqlError DBman::insert()
{
  QSqlQuery rec;
  if (db.isOpen())
  {
    if (!rec.prepare(Insert_HAMS))
      return rec.lastError();

    addRec(rec, "","","","","","");
  }
  return rec.lastError();
}

//-----------------------------------------------------------------------------------------
QSqlError DBman::removeRow(QSqlRelationalTableModel *tempmodel,int row,int count)
{
  QSqlQuery rec;
  if (db.isOpen())
  {
    bool rtn=tempmodel->removeRows(row,count);
  }
  return rec.lastError();
}

//-----------------------------------------------------------------------------------------
void DBman::open(QString DBname)
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
void DBman::closeDB()
{
if (db.isOpen())
    db.close();
}

//-----------------------------------------------------------------------------------------
void DBman::addRec(QSqlQuery &rec,const QString &call,const QString &freq,const QString &name,
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

//-----------------------------------------------------------------------------------------
QStringList DBman::Select_Name(QString name)
{
  QSqlQuery query;
  QStringList recordList;
  int recno=0;
  if (db.isOpen())
  {
    query.prepare("SELECT * FROM hams WHERE Name like ?");
    query.addBindValue(name);
    if(query.exec())
    {
      while(query.next())
      {
        QSqlRecord record = query.record();
        for(int i=0; i<record.count(); ++i)
        {
//          qDebug()<<"fieldname"<<record.fieldName(i);
          if(record.fieldName(i)=="Name")
          {
            QString temp=query.value(i-3).toString()+","; // -3 id
            temp +=query.value(i-2).toString()+",";       // -2 call
            temp +=query.value(i).toString()+",";         // 
            temp +=query.value(i+1).toString()+",";       // +1 city
            temp +=query.value(i+2).toString();           // +4 county
            recordList.append(temp);
//            qDebug()<<"value"<<query.value(i).toString();
          }
        }
        recno++;
      }
    return recordList;
    }
    else QMessageBox::critical(0,"HamstersDB","query error :"+query.lastError().text(), QMessageBox::Cancel);
  } else QMessageBox::critical(0,"HamstersDB","Database is not open", QMessageBox::Cancel);
  return recordList;
}
