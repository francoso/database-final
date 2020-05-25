#ifndef MYSQL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#define MYSQL_H

class Mysql
{
public:
    QSqlDatabase db;
    Mysql();
};

#endif // MYSQL_H
