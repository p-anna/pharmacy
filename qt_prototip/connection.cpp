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

    setQuerry("../Pharmacy/select.sql");
    execSelectQuerry1();
    printTable();
}


void Connection::addTableRow(std::vector<std::string> row)
{
    _table.push_back(row);
}

std::vector<std::string> Connection::tableRow(int i) const
{
    return _table[i];
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

std::vector<std::vector<std::string> > Connection::table() const
{
    return _table;
}


void Connection::addPurchase(std::vector<std::string> row)
{
//    std::cout << row[0] << " " << _purchaseAmmount[row[0]] << std::endl;
    if(_purchaseAmmount[row[0]] == 0)
    {
        _purchase.push_back(row);
        _purchaseAmmount[row[0]] = std::stoi(row[3]);
    }
    else
    {
        unsigned i=0;
        while(i < _purchase.size())
        {
            if(_purchase[i][0] == row[0])
                break;

            ++i;
        }
        _purchaseAmmount[row[0]] += std::stoi(row[3]);
        _purchase[i][3] = std::to_string(_purchaseAmmount[row[0]]);
        _purchase[i][4] = std::to_string(std::stod(_purchase[i][4])+std::stod(row[4]));
    }
}

std::vector<std::string> Connection::purchaseRow(int row) const
{
    return _purchase[row];
}

void Connection::deletePurchaseRow(int row)
{
    _purchaseAmmount[_purchase[row][0]] = 0;
    _purchase[row] = _purchase.back();
    _purchase.pop_back();
}


std::vector<std::vector<std::string> > Connection::purchase() const
{
    return _purchase;
}

void Connection::clearPurchase()
{
    _purchase.clear();
    _purchaseAmmount.clear();
}

int Connection::purchaseAmmount(std::string id)
{
    return _purchaseAmmount[id];
}

unsigned Connection::billId() const
{
    return _billId;
}

void Connection::setBillId(const unsigned &billId)
{
    _billId = billId;
}


void Connection::setQuerry(std::string path)
{
    std::ifstream in(path);
    std::string l;
    std::getline(in, l);
    _querry = QSqlQuery(l.c_str());
}

void Connection::setQuerry(const QSqlQuery q)
{
    _querry = q;
}

void Connection::execSelectQuerry1()
{
    _table.clear();
    while(_querry.next())
    {
        std::vector<std::string> row;
        for(unsigned i=0; i<5; i++)
        {
            row.push_back(_querry.value(i).toString().toStdString());
        }
        addTableRow(row);
    }
    _querry.finish();
}

void Connection::execSelectQuerry2()
{
    _querry.next();
    if(!_querry.value(0).isNull())
        _billId = std::stoul(_querry.value(0).toString().toStdString());
    else
        _billId = 0;

    _querry.finish();
}

void Connection::execQuerry()
{
    _querry.exec();
    _querry.finish();
}
