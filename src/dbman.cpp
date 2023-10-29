#include <QtCore/QCoreApplication>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>  // db.lastError error reporting
#include <QtSql>
#include <QMessageBox> // for debuging
#include <QDebug>
#include "dbman.h"

//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");



//-----------------------------------------------------------------------------------------
QSqlError initDB(QString dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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
//    addBook(q, QLatin1String("Going Postal"), 2004, pratchettId, fantasy, 3);

    return QSqlError();
}

//-----------------------------------------------------------------------------------------
void update(int recno)
{
  bool ok=db.open();
  if(ok)  // is db open?
  {
    qDebug() << "dbman::update: database is open, rec # is "<<QString(recno);
  }
  else
  {
    qDebug() << "dbAdd: database is not open";
  }
}

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

