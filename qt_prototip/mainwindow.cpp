#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QWidgetItem>
#include "connection.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    Connection c = Connection("QMYSQL", "localhost", "mydb", "root", "");
    c.setQuerry("./select.sql");
    c.execSelectQuerry();
    c.printTable();

    std::vector<std::vector<std::string> > tab = c.table();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(tab.size()+1);
    ui->tableWidget->setColumnCount(4);

    ui->tableWidget->setStyleSheet("color: rgb(0,0,0);");
    for(auto i=0; i<ui->tableWidget->rowCount(); i++)
        for(auto j=0; j<4; j++)
        {
            if(i != ui->tableWidget->rowCount()-1)
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(tab[i][j].c_str()));
            else
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }

    ui->tableWidget->horizontalHeader()->setFont(QFont("Cantarell", 10, 100, false));
    ui->tableWidget->horizontalHeader()->setStyleSheet("color: rgb(92,7,134);");
    QPalette palette = ui->tableWidget->horizontalHeader()->palette();
    QFont font = ui->tableWidget->horizontalHeader()->font();
    //palette.setColor();
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("PROIZVOD"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("DOBAVLJAC"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("CENA"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("KOLICINA"));

//---------------------------------------------------------------------------------------------------------------------

    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(1);
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setPalette(palette);
    ui->tableWidget_2->setFrameShape(ui->tableWidget->frameShape());
    ui->tableWidget_2->setFrameShadow(ui->tableWidget->frameShadow());
    ui->tableWidget_2->horizontalHeader()->setFont(font);

    int width = ui->tableWidget_2->width();
    int height = ui->tableWidget_2->height();

    for(auto j=0; j<4; j++)
    {
        ui->tableWidget_2->setItem(0, j, new QTableWidgetItem(""));
        ui->tableWidget_2->item(0, j)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("PROIZVOD"));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("DOBAVLJAC"));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("KOLICINA"));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("IZNOS"));
    ui->tableWidget_2->setColumnWidth(0, std::floor(width/4));
    ui->tableWidget_2->setColumnWidth(1, std::floor(width/4));
    ui->tableWidget_2->setColumnWidth(2, std::floor(width/4));
    ui->tableWidget_2->setColumnWidth(3, std::floor(width/4)-1);
    ui->tableWidget_2->setRowHeight(0, height);

    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->verticalHeader()->setHidden(true);
    ui->tableWidget_2->setShowGrid(true);
    ui->tableWidget_2->setSortingEnabled(true);
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
