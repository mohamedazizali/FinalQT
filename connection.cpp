#include "connection.h"

Connection::Connection()
{}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Aziz");
    db.setUserName("Aziz");
    db.setPassword("aziz");

    if (db.open())
        return true;
    return false;
}
void Connection::closeconnection(){db.close();}
