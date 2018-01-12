#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    /************************* Slika na qlabel sa fixiranom velicinom *************************/
    QPixmap pm("/home/panna/pharmacy/question.png");

    int velicina = 12;

    ui->znakpitanja->setPixmap(pm.scaled(velicina,velicina,Qt::KeepAspectRatio));
    ui->znakpitanja2->setPixmap(pm.scaled(velicina,velicina,Qt::KeepAspectRatio));

    /******************************************************************************************/

}

Login::~Login()
{
    delete ui;
}
