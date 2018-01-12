#include "apoteka.h"
#include "ui_apoteka.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>

Apoteka::Apoteka(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Apoteka)
{

    ui->setupUi(this);

}

Apoteka::~Apoteka()
{
    delete ui;
}

void Apoteka::on_actionLogin_triggered()
{
    Login login;
    login.setModal(true);
    login.exec();
}

void Apoteka::on_actionLogin_2_triggered()
{
    Login login;
    login.setModal(true);
    login.exec();
}

void Apoteka::on_actionLogout_triggered()
{
    Logout logout;
    logout.setModal(true);
    logout.exec();
}

void Apoteka::on_actionKupovina_triggered()
{
    kupoprodaja *k = new kupoprodaja();
    k->show();

}

void Apoteka::on_actionRobe_triggered()
{
    narucivanje n;
    n.setModal(true);
    n.exec();
}

void Apoteka::on_actionLista_triggered()
{
    listaNar n;
    n.setModal(true);
    n.exec();
}
