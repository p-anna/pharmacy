#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <iostream>
#include <math.h>
#include <QInputDialog>
#include <QTableWidget>

Connection c;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonPrint, SIGNAL(clicked()), this, SLOT(buttonPrint_clicked()));
    connect(ui->tableWidgetDatabase, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(tableWidgetDatabase_cellDoubleClicked(int,int)));
    connect(ui->tableWidgetPurchase, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(tableWidgetPurchase_cellDoubleClicked(int,int)));
    connect(ui->lineEditSearch, SIGNAL(textChanged(QString)),
            this, SLOT(lineEditSearch_textChanged(QString)));

    ui->tableWidgetDatabase->setAlternatingRowColors(true);
    ui->tableWidgetDatabase->verticalHeader()->setHidden(true);
    ui->tableWidgetDatabase->setShowGrid(true);
    ui->tableWidgetDatabase->setSortingEnabled(true);

    ui->tableWidgetPurchase->setAlternatingRowColors(true);
    ui->tableWidgetPurchase->verticalHeader()->setHidden(true);
    ui->tableWidgetPurchase->setShowGrid(true);
    ui->tableWidgetPurchase->setSortingEnabled(true);

    ui->lineEditTotalAmount->setText("0.00");
    ui->lineEditTotalAmount->setEnabled(false);

    //ui->tableWidget_2->sortItems();

    c = Connection("QMYSQL", "localhost", "mydb", "root", "");
    c.setQuerry("../PharmacyGUI/select.sql");
    c.execSelectQuerry();
    c.printTable();

    //OSVEZAVA TABELU PRE NEGO STO JE NAPRAVI
    refreshDatabaseTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPrint_clicked()
{
    if(c.purchase().size() != 0)
    {
        QSqlQuery q1;
        QSqlQuery q2;

        q1.prepare("insert into RACUN values (0, 2, ?, current_date, \"kes\")");
        q1.bindValue(0, ui->lineEditTotalAmount->text());
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
        ui->lineEditTotalAmount->setText("0.00");

        c.setQuerry("../PharmacyGUI/select.sql");
        c.execQuerry();
        refreshDatabaseTable();
    }
}

void MainWindow::tableWidgetDatabase_cellDoubleClicked(int row, int column)
{
    std::vector<std::string> r = c.tableRow(row);
    if(r[4] != std::to_string(0))
    {
        int n = QInputDialog::getInt(this, "Unesite kolicinu", "Kolicina");
        if(n>0 && n+c.purchaseAmmount(r[0])<=std::stoi(r[4]))
        {
            c.addPurchase({r[0], r[1], r[2], std::to_string(n), std::to_string(std::stod(r[3])*n)});
            refreshPurchaseTable();
            ui->lineEditTotalAmount->setText(std::to_string(std::stod(ui->lineEditTotalAmount->text().toStdString())+std::stod(r[3])*n).c_str());
        }
    }
}

void MainWindow::tableWidgetPurchase_cellDoubleClicked(int row, int column)
{
    std::vector<std::string> r = c.purchaseRow(row);
    ui->lineEditTotalAmount->setText(std::to_string(std::stod(ui->lineEditTotalAmount->text().toStdString())-std::stod(r[4])).c_str());
    c.deletePurchaseRow(row);
    refreshPurchaseTable();
}

void MainWindow::lineEditSearch_textChanged(const QString &pattern)
{
    if(pattern != "")
    {
        QString s = "select P.id_proizvoda, P.naziv, coalesce(D.naziv, \"-\") as naziv, PR.cena, sum(coalesce(M.kolicina, 0)) as kolicina ";
        s.append("from PROIZVOD P join PREPARAT PR on PR.id_proizvoda=P.id_proizvoda left outer join DOBAVLJAC D on D.id_dobavljaca = P.id_dobavljaca left outer join MAGACIN M on M.id_proizvoda=P.id_proizvoda ");
        s.append("where P.naziv like \"%" + pattern + "%\" or D.naziv like \"%" + pattern + "%\" ");
        s.append("group by P.id_proizvoda, P.naziv, P.id_dobavljaca;");

        QSqlQuery q = QSqlQuery(s);
        c.setQuerry(q);
    }
    else
        c.setQuerry("../PharmacyGUI/select.sql");

    c.execSelectQuerry();
    refreshDatabaseTable();
}


void MainWindow::refreshDatabaseTable()
{
    int width = ui->tableWidgetDatabase->width();

    std::vector<std::vector<std::string> > tab = c.table();
    ui->tableWidgetDatabase->clear();
    ui->tableWidgetDatabase->setRowCount(tab.size()+1);
    ui->tableWidgetDatabase->setColumnCount(4);

//    ui->tableWidgetDatabase->setStyleSheet("color: rgb(0,0,0);");
    for(auto i=0; i<ui->tableWidgetDatabase->rowCount(); i++)
        for(auto j=0; j<4; j++)
        {
            if(i != ui->tableWidgetDatabase->rowCount()-1)
                ui->tableWidgetDatabase->setItem(i, j, new QTableWidgetItem(tab[i][j+1].c_str()));
            else
                ui->tableWidgetDatabase->setItem(i, j, new QTableWidgetItem(""));
            ui->tableWidgetDatabase->item(i, j)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }

    ui->tableWidgetDatabase->horizontalHeader()->setFont(QFont("Cantarell", 10, 100, false));
//    ui->tableWidgetDatabase->horizontalHeader()->setStyleSheet("color: rgb(92,7,134);");
    ui->tableWidgetDatabase->setHorizontalHeaderItem(0, new QTableWidgetItem("PROIZVOD"));
    ui->tableWidgetDatabase->setHorizontalHeaderItem(1, new QTableWidgetItem("DOBAVLJAC"));
    ui->tableWidgetDatabase->setHorizontalHeaderItem(2, new QTableWidgetItem("CENA"));
    ui->tableWidgetDatabase->setHorizontalHeaderItem(3, new QTableWidgetItem("KOLICINA"));
    ui->tableWidgetDatabase->setColumnWidth(0, std::floor(width/4));
    ui->tableWidgetDatabase->setColumnWidth(1, std::floor(width/4));
    ui->tableWidgetDatabase->setColumnWidth(2, std::floor(width/4));
    ui->tableWidgetDatabase->setColumnWidth(3, std::floor(width/4)-1);
}

void MainWindow::refreshPurchaseTable()
{
    std::vector<std::vector<std::string> > purchase = c.purchase();

    QPalette palette = ui->tableWidgetPurchase->palette();
    QFont hfont = ui->tableWidgetDatabase->horizontalHeader()->font();
//    QFont tfont = ui->tableWidget->font();

    int width = ui->tableWidgetPurchase->width();

    ui->tableWidgetPurchase->clear();
    ui->tableWidgetPurchase->setRowCount(purchase.size());
    ui->tableWidgetPurchase->setColumnCount(4);
    //ui->tableWidgetPurchase->setPalette(palette);
    //ui->tableWidgetPurchase->setFrameShape(ui->tableWidgetDatabase->frameShape());
    //ui->tableWidgetPurchase->setFrameShadow(ui->tableWidgetDatabase->frameShadow());
    //ui->tableWidgetPurchase->horizontalHeader()->setFont(hfont);

    ui->tableWidgetPurchase->setHorizontalHeaderItem(0, new QTableWidgetItem("PROIZVOD"));
    ui->tableWidgetPurchase->setHorizontalHeaderItem(1, new QTableWidgetItem("DOBAVLJAC"));
    ui->tableWidgetPurchase->setHorizontalHeaderItem(2, new QTableWidgetItem("KOLICINA"));
    ui->tableWidgetPurchase->setHorizontalHeaderItem(3, new QTableWidgetItem("IZNOS"));
    ui->tableWidgetPurchase->setColumnWidth(0, std::floor(width/4));
    ui->tableWidgetPurchase->setColumnWidth(1, std::floor(width/4));
    ui->tableWidgetPurchase->setColumnWidth(2, std::floor(width/4));
    ui->tableWidgetPurchase->setColumnWidth(3, std::floor(width/4)-1);

    //ui->tableWidget_2->setStyleSheet("color: rgb(0, 0, 0);");
    for(unsigned i=0; i<purchase.size(); i++)
        for(unsigned j=0; j<4; j++)
        {
            ui->tableWidgetPurchase->setItem(i, j, new QTableWidgetItem(purchase[i][j+1].c_str()));
            ui->tableWidgetPurchase->item(i, j)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
}
