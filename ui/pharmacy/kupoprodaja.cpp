#include "kupoprodaja.h"
#include "ui_kupoprodaja.h"

kupoprodaja::kupoprodaja(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::kupoprodaja)
{
    ui->setupUi(this);

}

kupoprodaja::~kupoprodaja()
{
    delete ui;
}
