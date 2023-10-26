#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>

class DbManager
{
public:
  DbManager(const QString& path );
  ~DbManager();

  bool isOpen() const;
  bool createTable();
  bool createMusicListTable(const QString &tableName);
  bool createSettingsTable(const QString &tableName);
  bool insertMusic(const QString tableName, const QString &name, const QString &path, const int &lenghtAsSecond, QString lenghtToShow);
  bool removePerson(const QString& name);
  bool personExists(const QString& name) const;
  void printAllPersons() const;
  bool removeAllPersons();
  bool changeSetting(  QString columnName, QString value );
  int getSetting(QString whichOne);
  bool updateMusic(const int &musicId,const QString &name, const QString &path, const int &lenghtAsSecond, QString lenghtToShow);
  bool updateMusicDuration(const int &musicId , const int &lenghtAsSecond , QString lenghtToShow );
  bool removeMusic(const int &musicId);
  bool changeShuffleMode(int value );
  bool deleteAllList();
  QString tableNamesMusicList;// = "tblMusicList";
  QString tableNamesSettings;// = "tblSettings";

  typedef struct
  {
    QString id;// = "id";
    QString current_index;// = "current_index";
    QString selected_index;// = "selected_index";
    QString repeatSingle;// = "repeatSingle";
    QString repeatAll;// = "repeatAll";
    QString shuffle;// = "shuffle";
    QString volume;// = "volume";
  } table_settings ;

  typedef struct
  {
      QString id;// = "id";
    QString name;// = "name";
    QString path;// = "path";
    QString lenghtAsSecond;// = "lenghtAsSecond";
    QString lenghtToShow;// = "lenghtToShow";
    } table_music;

  struct tablesAndColumns
  {
    table_settings _tableSettings;
    table_music _tableMusic;
  };

  const tablesAndColumns *allTables;

private:
    QSqlDatabase m_db;

};

#endif // DBMANAGER_H
