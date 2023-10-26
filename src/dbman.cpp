#include <QtCore/QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>  // db.lastError error reporting
#include <QtSql>
#include "dbman.h"

QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

int dbman::initDB()
{
  bool ok=0;
  // Initialize the database:
  //  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setDatabaseName("CHAT");
  db.setUserName("chat");
  db.setPassword("chat1");
  ok=db.open();
  if(!ok)
  {
    qDebug() << db.lastError();
    qFatal( "Failed to connect." );
    return ok;
  }
  qDebug() << "Database is connected.";
  QSqlQuery qry;

  qry.prepare("SET SESSION wait_timeout = 345600");
  if(!qry.exec())
    qDebug() << qry.lastError();

  qry.prepare("SET SESSION interactive_timeout = 345600");
  if(!qry.exec())
    qDebug() << qry.lastError();

  qry.prepare( "SHOW VARIABLES LIKE '%timeout%'");
  if(!qry.exec())
    qDebug() << qry.lastError();
  else
  {
    QString user, message;
    QSqlRecord data = qry.record();
    for( int r=0; qry.next(); r++ )
    {
      user=qry.value(0).toString();
      message=qry.value(1).toString();
qDebug() <<user << ":" << message;
db.close();
//    client->write(QString("Server: "+ user + ":" + message + "\n").toUtf8());
    }
//    qDebug() << data;
  }
  return ok;
}
