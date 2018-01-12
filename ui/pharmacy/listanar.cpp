#include "listanar.h"
#include "ui_listanar.h"

listaNar::listaNar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listaNar)
{
    ui->setupUi(this);
}

listaNar::~listaNar()
{
    delete ui;
}
