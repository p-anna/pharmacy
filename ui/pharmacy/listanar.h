#ifndef LISTANAR_H
#define LISTANAR_H

#include <QDialog>

namespace Ui {
class listaNar;
}

class listaNar : public QDialog
{
    Q_OBJECT

public:
    explicit listaNar(QWidget *parent = 0);
    ~listaNar();

private:
    Ui::listaNar *ui;
};

#endif // LISTANAR_H
