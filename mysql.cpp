#include "mysql.h"

Mysql::Mysql()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("foreign_trade_company");
    db.setUserName("root");
    db.setPassword("mo42516571");
}
