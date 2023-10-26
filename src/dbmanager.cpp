#include "dbmanager.h"
#include <QDebug>

DbManager::DbManager(const QString &path)
{
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);

  allTables = new tablesAndColumns();

  if (!m_db.open())
  {
    qDebug() << "Error: connection with database fail";
  }
  else
  {
    qDebug() << "Database: connection ok";
  }
}

DbManager::~DbManager()
{
  if (m_db.isOpen())
  {
    m_db.close();
  }
}

bool DbManager::isOpen() const
{
  return m_db.isOpen();
}

bool DbManager::createTable()
{
  bool success = false;
  return success;
}

bool DbManager::createMusicListTable(const QString &tableName)
{
  bool success = true;

  QSqlQuery query;
  query.prepare("CREATE TABLE " + tableName + "("
    + allTables->_tableMusic.id       + " INTEGER PRIMARY KEY AUTOINCREMENT, "
    + allTables->_tableMusic.name     + " TEXT, "
    + allTables->_tableMusic.path     + " TEXT,"
    + allTables->_tableMusic.lenghtAsSecond   + " INTEGER "
    + allTables->_tableMusic.lenghtToShow + " TEXT );");
  if (!query.exec())
  {
    qDebug() << "müzik listesi tablosu zaten oluşturulmuş durumda gardaşım ";
    success = false;
  }
  return success;
}

bool DbManager::createSettingsTable(const QString &tableName)
{
  bool success = true;

  QSqlQuery query;
  query.prepare("CREATE TABLE " + tableName +
    "(" + allTables->_tableSettings.id + " INTEGER PRIMARY KEY, "
    + allTables->_tableSettings.current_index  + " INTEGER, "
    + allTables->_tableSettings.repeatSingle + " INTEGER, "
    + allTables->_tableSettings.repeatAll + " INTEGER, "
    + allTables->_tableSettings.shuffle + " INTEGER, "
    + allTables->_tableSettings.volume + " INTEGER);");
  if (!query.exec())
  {
    qDebug() << "Ayarlar tablosu zaten oluşturulmuş durumda.";
    success = false;
  }

  if(success == true)
  {
    QSqlQuery queryValues;
    queryValues.prepare("INSERT INTO " + tableName +
      "(" + allTables->_tableSettings.id + ", "
      + allTables->_tableSettings.current_index + ", "
      + allTables->_tableSettings.repeatSingle + ", "
      + allTables->_tableSettings.repeatAll + ", "
      + allTables->_tableSettings.shuffle + ", "
      + allTables->_tableSettings.volume
      + ") VALUES(1,0,0,0,0,50);");
    if (!queryValues.exec())
    {
      qDebug() << "Ayarlar Tablosunun değerleri eklenemedi.";
      success = false;
    }
  }
  return success;
}

bool DbManager::changeSetting(QString columnName, QString value )
{
  bool success = false;

  if(columnName != "" && value != "")
  {
    QSqlQuery queryAdd;
    queryAdd.prepare("UPDATE " + tableNamesSettings + " SET " + columnName + "=:value where id=1");
      queryAdd.bindValue(":value", value);
    if(queryAdd.exec())
    {
      success = true;
    }
    else
    {
      qDebug() << "ayar değiştirilemedi: " << queryAdd.lastError();
    }
  }
  return success;
}

bool DbManager::changeShuffleMode(int value )
{
  bool success = false;

  if( value > -1)
  {
    QSqlQuery queryAdd;
    queryAdd.prepare("UPDATE " + tableNamesSettings + " SET shuffle=" + QString::number(value) + " where id=1");
    qDebug() << "UPDATE " + tableNamesSettings + " SET shuffle=" + QString::number(value) + " where id=1";
    if(queryAdd.exec())
    {
      success = true;
    }
    else
    {
      qDebug() << "ayar değiştirilemedi: " << queryAdd.lastError();
    }
  }
  return success;
}

bool DbManager::insertMusic(const QString tableName,const QString &name, const QString &path, const int &lenghtAsSecond, QString lenghtToShow)
{
  bool success = false;

  if (!name.isEmpty())
  {
    QSqlQuery queryAdd;
      queryAdd.prepare("INSERT INTO " + tableName + " (name,path,lenghtAsSecond,lenghtToShow) VALUES (:name,:path,:lenghtAsSecond,:lenghtToShow)");
      queryAdd.bindValue(":name", name);
      queryAdd.bindValue(":path", path);
      queryAdd.bindValue(":lenghtAsSecond", lenghtAsSecond);
      queryAdd.bindValue(":lenghtToShow", lenghtToShow);
    if(queryAdd.exec())
    {
      success = true;
    }
    else
    {
      qDebug() << "müzik eklenemedi: " << queryAdd.lastError();
    }
  }
  else
  {
    qDebug() << "Ekleme yapılamsı için veri gerekmektedir.";
  }
  return success;
}

bool DbManager::removeMusic(const int &musicId)
{
  bool success = false;

  if (musicId > -1)
  {
    QSqlQuery queryDelete;
    queryDelete.prepare("DELETE FROM " + tableNamesMusicList + " WHERE id=" + QString::number(musicId) );
    success = queryDelete.exec();

    if(!success)
    {
      qDebug() << "MusicSilindi: " << queryDelete.lastError();
    }
  }
  else
  {
    qDebug() << "MusicSilinemedi";
  }
  return success;
}

bool DbManager::personExists(const QString& name) const
{
  bool exists = false;

  QSqlQuery checkQuery;
  checkQuery.prepare("SELECT name FROM people WHERE name = (:name)");
  checkQuery.bindValue(":name", name);
  if (checkQuery.exec())
  {
    if (checkQuery.next())
    {
      exists = true;
    }
  }
  else
  {
    qDebug() << "person exists failed: " << checkQuery.lastError();
  }
  return exists;
}

