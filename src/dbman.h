#ifndef DBMAN_H
#define DBMAN_H

#include <QStringList>
#include <QtSql>

static auto Create_HAMS_Table = QLatin1String(R"(create table hams(id integer primary key, Call varchar, Freq varchar, Name varchar, City varchar, County varchar, Country varchar, Remarks varchar))");
static auto Insert_HAMS = QLatin1String(R"(insert into hams(Call, Freq, Name, City, County, Country, Remarks) values(?, ?, ?, ?, ?,?,?))");

class DBman;

bool isOpen();

class DBman
{

public:
  DBman (QObject *_parent);
  ~DBman();
static bool isOpen();
static void closeDB();
static QSqlError insert();
static QSqlError initDB(QString dbName);
static void open(QString DBname);
static QStringList Select_Name(QString name);
static QStringList Select_Call(QString name);

static QSqlError removeRow(QSqlRelationalTableModel *tempmodel,int row, int count);

static void addRec(QSqlQuery &rec,const QString &call,const QString &freq,const QString &name,
            const QString &city,const QString &county,const QString &country,const QString &remarks);

private:


private slots:

signals:

};

#endif

