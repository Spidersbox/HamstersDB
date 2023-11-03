#ifndef DBMAN_H
#define DBMAN_H

#include <QStringList>
#include <QtSql>

class DBman;


class DBman
{

public:
  DBman (QObject *_parent);
  ~DBman();
static void closeDB();
static QSqlError insert();
static QSqlError initDB(QString dbName);
static void open(QString DBname);
static QStringList Select_Name(QString name);
static QStringList Select_Call(QString name);

static QSqlError removeRow(QSqlRelationalTableModel *tempmodel,int row, int count);

static constexpr auto Create_HAMS_Table = QLatin1String(R"(create table hams(id integer primary key, Call varchar,  Freq varchar,Name varchar, City varchar,County varchar,Remarks varchar))");

static void addRec(QSqlQuery &rec,const QString &call,const QString &freq,const QString &name,
            const QString &city,const QString &county,const QString &remarks);

static constexpr auto Insert_HAMS = QLatin1String(R"(insert into hams(Call,Freq,Name,City,County,Remarks) values(?, ?, ?, ?, ?,?))");


private:


private slots:

signals:

};

#endif

