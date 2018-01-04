#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <vector>

class Connection
{
public:
    Connection();
    Connection(std::string driver, QString host, QString dbName, QString user, QString pass);

    void setQuerry(std::string path);
    void addTableRow(std::vector<std::string> row);
    std::vector<std::string> tableRow(int i) const;
    std::vector<std::vector<std::string> > table() const;
    void printTable() const;

    void addPurchaseRow(std::vector<std::string> row);
    std::vector<std::string> purchaseRow(int row) const;
    void deletePurchaseRow(int row);
    std::vector<std::vector<std::string> > purchase() const;

    void execSelectQuerry();
    void execQuerry();


private:
    QSqlDatabase _db;
    QSqlQuery _querry;
    std::vector<std::vector<std::string> > _table;
    std::vector<std::vector<std::string> > _purchase;
};

#endif // CONNECTION_H

