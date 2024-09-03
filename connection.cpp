#include "connection.h"

Connection::Connection()
{}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("final_bd");
    db.setUserName("final");
    db.setPassword("final");

    if (db.open())
        return true;
    return false;
}
void Connection::closeconnection(){db.close();}
