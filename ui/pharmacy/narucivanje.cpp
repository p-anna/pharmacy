#include "narucivanje.h"
#include "ui_narucivanje.h"

narucivanje::narucivanje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::narucivanje)
{
    ui->setupUi(this);
   }

narucivanje::~narucivanje()
{
    delete ui;
}
