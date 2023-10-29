#ifndef DBMAN_H
#define DBMAN_H

#include <QtSql>

//class dbman
//{
//public:
//  static bool ok;

//  static int initDB();
//  static int initDB(QString dbName);
//  static void update(int recno);

//};

QSqlError initDB(QString dbName);

void addRec(QSqlQuery &rec,const QString &call,const QString &freq,const QString &name,
            const QString &city,const QString &county,const QString &remarks);

const auto HAMS_SQL = QLatin1String(R"(create table hams(id integer primary key, Call varchar,  Freq varchar,Name varchar, City varchar,County varchar,Remarks varchar))");


const auto INSERT_HAMS_SQL = QLatin1String(R"(insert into hams(Call,Freq,Name,City,County,Remarks) values(?, ?, ?, ?, ?,?))");


#endif

