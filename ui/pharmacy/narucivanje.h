#ifndef NARUCIVANJE_H
#define NARUCIVANJE_H

#include <QDialog>
#include<QGroupBox>

namespace Ui {
class narucivanje;
}

class narucivanje : public QDialog
{
    Q_OBJECT

public:
    explicit narucivanje(QWidget *parent = 0);
    ~narucivanje();

private:
    Ui::narucivanje *ui;
};

#endif // NARUCIVANJE_H
