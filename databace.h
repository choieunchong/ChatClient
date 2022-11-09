#ifndef DATABACE_H
#define DATABACE_H

#include <QSqlDatabase>
#include <QString>
class Databace : public QSqlDatabase
{

public:
    Databace();
    QSqlDatabase set_database_info(QString sql, QString ip, int port, QString dbname, QString username, QString passwoed);

private:
    QSqlDatabase database;

};

#endif // DATABACE_H
