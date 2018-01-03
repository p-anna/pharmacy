#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <vector>

class Connection
{
public:
    Connection(std::string driver, QString host, QString dbName, QString user, QString pass);
    void setQuerry(std::string path);
    void addRow(std::vector<std::string> row);
    std::vector<std::vector<std::string> > table() const;
    void printTable() const;

    void execSelectQuerry();
    void execQuerry();


private:
    QSqlDatabase _db;
    QSqlQuery _querry;
    std::vector<std::vector<std::string> > _table;
};

#endif // CONNECTION_H

