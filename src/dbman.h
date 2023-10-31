#ifndef DBMAN_H
#define DBMAN_H

#include <QtSql>


QSqlError initDB(QString dbName);
QSqlError insert();

void addRec(QSqlQuery &rec,const QString &call,const QString &freq,const QString &name,
            const QString &city,const QString &county,const QString &remarks);

const auto HAMS_SQL = QLatin1String(R"(create table hams(id integer primary key, Call varchar,  Freq varchar,Name varchar, City varchar,County varchar,Remarks varchar))");


const auto INSERT_HAMS_SQL = QLatin1String(R"(insert into hams(Call,Freq,Name,City,County,Remarks) values(?, ?, ?, ?, ?,?))");

void open(QString DBname);
void closeDB();
#endif

