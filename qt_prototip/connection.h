#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <vector>
#include <map>

class Connection
{
public:
    Connection();
    Connection(std::string driver, QString host, QString dbName, QString user, QString pass);

    void setQuerry(std::string path);
    void setQuerry(const QSqlQuery q);
    void execSelectQuerry1();
    void execSelectQuerry2();
    void execQuerry();

    void addTableRow(std::vector<std::string> row);
    std::vector<std::string> tableRow(int i) const;
    std::vector<std::vector<std::string> > table() const;
    void printTable() const;

    void addPurchase(std::vector<std::string> row);
    std::vector<std::string> purchaseRow(int row) const;
    void deletePurchaseRow(int row);
    std::vector<std::vector<std::string> > purchase() const;
    void clearPurchase();

    int purchaseAmmount(std::string id);
    unsigned billId() const;
    void setBillId(const unsigned &billId);

private:
    QSqlDatabase _db;
    QSqlQuery _querry;
    std::vector<std::vector<std::string> > _table;
    std::vector<std::vector<std::string> > _purchase;
    std::map<std::string, int> _purchaseAmmount;
    unsigned _billId;
};

#endif // CONNECTION_H

