#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QWidgetItem>
#include <QInputDialog>

Connection c;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonReceipts,SIGNAL(clicked()),
            this, SLOT(buttonReceipts_clicked()));
    connect(ui->buttonHome,SIGNAL(clicked()),
            this, SLOT(buttonHome_clicked()));
    connect(ui->buttonBuySell,SIGNAL(clicked()),
            this, SLOT(buttonBuySell_clicked()));
    connect(ui->buttonHelp,SIGNAL(clicked()),
            this, SLOT(buttonHelp_clicked()));
    connect(ui->buttonExit,SIGNAL(clicked()),
            this, SLOT(buttonExit_clicked()));

    c = Connection("QMYSQL", "localhost", "mydb", "root", "");
    c.setQuerry("../PharmacyGUI/select.sql");
    c.execSelectQuerry();
    c.printTable();

    refreshDataBaseTable();

    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->verticalHeader()->setHidden(true);
    ui->tableWidget_2->setShowGrid(true);
    ui->tableWidget_2->setSortingEnabled(true);

    ui->lineEdit_7->setText("0.00");
    ui->lineEdit_7->setEnabled(false);

    refreshPurchaseTable();

    //ui->tableWidget_2->sortItems();
    //ui->tableWidget_2->cellDoubleClicked();
    //ui->tableWidget_2->itemDoubleClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::buttonHome_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::buttonReceipts_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::buttonBuySell_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::buttonHelp_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::buttonExit_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}



void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    std::vector<std::string> r = c.tableRow(row);
    if(r[4] != std::to_string(0))
    {
        int n = QInputDialog::getInt(this, "Unesite kolicinu", "Kolicina");
        if(n>0 && n+c.purchaseAmmount(r[0])<=std::stoi(r[4]))
        {
            c.addPurchase({r[0], r[1], r[2], std::to_string(n), std::to_string(std::stod(r[3])*n)});
            refreshPurchaseTable();
            ui->lineEdit_7->setText(std::to_string(std::stod(ui->lineEdit_7->text().toStdString())+std::stod(r[3])*n).c_str());
        }
    }
}

void MainWindow::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    std::vector<std::string> r = c.purchaseRow(row);
    ui->lineEdit_7->setText(std::to_string(std::stod(ui->lineEdit_7->text().toStdString())-std::stod(r[4])).c_str());
    c.deletePurchaseRow(row);
    refreshPurchaseTable();
}

void MainWindow::refreshDataBaseTable()
{
    std::vector<std::vector<std::string> > tab = c.table();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(tab.size()+1);
    ui->tableWidget->setColumnCount(4);

    ui->tableWidget->setStyleSheet("color: rgb(0,0,0);");
    for(auto i=0; i<ui->tableWidget->rowCount(); i++)
        for(auto j=0; j<4; j++)
        {
            if(i != ui->tableWidget->rowCount()-1)
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(tab[i][j+1].c_str()));
            else
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }

    ui->tableWidget->horizontalHeader()->setFont(QFont("Cantarell", 10, 100, false));
    ui->tableWidget->horizontalHeader()->setStyleSheet("color: rgb(92,7,134);");
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("PROIZVOD"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("DOBAVLJAC"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("CENA"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("KOLICINA"));
}

void MainWindow::refreshPurchaseTable()
{
    std::vector<std::vector<std::string> > purchase = c.purchase();

    QPalette palette = ui->tableWidget_2->palette();
    QFont hfont = ui->tableWidget->horizontalHeader()->font();
    QFont tfont = ui->tableWidget->font();

    int width = ui->tableWidget_2->width();

    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(purchase.size());
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setPalette(palette);
    ui->tableWidget_2->setFrameShape(ui->tableWidget->frameShape());
    ui->tableWidget_2->setFrameShadow(ui->tableWidget->frameShadow());
    ui->tableWidget_2->horizontalHeader()->setFont(hfont);

    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("PROIZVOD"));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("DOBAVLJAC"));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("KOLICINA"));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("IZNOS"));
    ui->tableWidget_2->setColumnWidth(0, std::floor(width/4));
    ui->tableWidget_2->setColumnWidth(1, std::floor(width/4));
    ui->tableWidget_2->setColumnWidth(2, std::floor(width/4));
    ui->tableWidget_2->setColumnWidth(3, std::floor(width/4)-1);

    //ui->tableWidget_2->setStyleSheet("color: rgb(0, 0, 0);");
    for(unsigned i=0; i<purchase.size(); i++)
        for(unsigned j=0; j<4; j++)
        {
            ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(purchase[i][j+1].c_str()));
            ui->tableWidget_2->item(i, j)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    if(arg1 != "")
    {
        QString s = "select P.id_proizvoda, P.naziv, coalesce(D.naziv, \"-\") as naziv, PR.cena, sum(coalesce(M.kolicina, 0)) as kolicina ";
        s.append("from PROIZVOD P join PREPARAT PR on PR.id_proizvoda=P.id_proizvoda left outer join DOBAVLJAC D on D.id_dobavljaca = P.id_dobavljaca left outer join MAGACIN M on M.id_proizvoda=P.id_proizvoda ");
        s.append("where P.naziv like \"%" + arg1 + "%\" or D.naziv like \"%" + arg1 + "%\" ");
        s.append("group by P.id_proizvoda, P.naziv, P.id_dobavljaca;");

        QSqlQuery q = QSqlQuery(s);
        c.setQuerry(q);
    }
    else
        c.setQuerry("../PharmacyGUI/select.sql");

    c.execSelectQuerry();
    refreshDataBaseTable();
}

void MainWindow::on_pushButton_clicked()
{
    if(c.purchase().size() != 0)
    {
        QSqlQuery q1;
        QSqlQuery q2;

        q1.prepare("insert into RACUN values (0, 2, ?, current_date, \"kes\")");
        q1.bindValue(0, ui->lineEdit_7->text());
        c.setQuerry(q1);
        c.execQuerry();


        std::vector<std::vector<std::string> > pur = c.purchase();
        for(unsigned i=0; i<pur.size(); i++)
        {
            q2.clear();
            q2.prepare("insert into KUPOVINA values (0, ?, NULL, ?, NULL)");
            q2.bindValue(0, pur[i][0].c_str());
            q2.bindValue(1, pur[i][3].c_str());

            c.setQuerry(q2);
            c.execQuerry();
        }

        c.clearPurchase();
        refreshPurchaseTable();
        ui->lineEdit_7->setText("0.00");


        c.setQuerry("../PharmacyGUI/select.sql");
        c.execQuerry();
        refreshDataBaseTable();
    }
}
