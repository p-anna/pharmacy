#include "connection.h"
#include <iostream>
#include <fstream>
#include <QVariant>
#include <QSqlDriver>

Connection::Connection(){}

Connection::Connection(std::string driver, QString host, QString dbName, QString user, QString pass = "")
{
    _db = QSqlDatabase::addDatabase(driver.c_str());
    _db.setHostName(QString(host));
    _db.setDatabaseName(dbName);
    _db.setUserName(user);
    _db.setPassword(pass);

    if(!_db.open())
    {
        std::cout << "Connection Failed!" << std::endl;
        std::exit(-1);
    }
}

void Connection::setQuerry(std::string path)
{
    std::ifstream in(path);
    std::string l;
    std::getline(in, l);
    _querry = QSqlQuery(l.c_str());
}

void Connection::addTableRow(std::vector<std::string> row)
{
    _table.push_back(row);
}

std::vector<std::string> Connection::tableRow(int i) const
{
    return _table[i];
}

void Connection::addPurchaseRow(std::vector<std::string> row)
{
    _purchase.push_back(row);
}

std::vector<std::string> Connection::purchaseRow(int row) const
{
    return _purchase[row];
}

void Connection::deletePurchaseRow(int row)
{
    _purchase[row] = _purchase.back();
    _purchase.pop_back();
}

void Connection::printTable() const
{
    for(unsigned i=0; i<_table.size(); i++)
    {
        for(unsigned j=0; j<_table[i].size(); j++)
            std::cout << _table[i][j] << " ";

        std::cout << std::endl;
    }
}

void Connection::execSelectQuerry()
{
    while(_querry.next())
    {
        std::vector<std::string> row;
        for(unsigned i=1; i<5; i++)
        {
            row.push_back(_querry.value(i).toString().toStdString());
        }
        addTableRow(row);
    }
}

void Connection::execQuerry()
{
    _querry.exec();
}

std::vector<std::vector<std::string> > Connection::table() const
{
    return _table;
}

std::vector<std::vector<std::string> > Connection::purchase() const
{
    return _purchase;
}

