#ifndef APOTEKA_H
#define APOTEKA_H

#include <QMainWindow>
#include"login.h"
#include"logout.h"
#include"kupoprodaja.h"
#include"narucivanje.h"
#include"listanar.h"

namespace Ui {
class Apoteka;
}

class Apoteka : public QMainWindow
{
    Q_OBJECT

public:
    explicit Apoteka(QWidget *parent = 0);
    ~Apoteka();

private slots:
    void on_actionLogin_triggered();

    void on_actionLogin_2_triggered();

    void on_actionLogout_triggered();

    void on_actionKupovina_triggered();

    void on_actionRobe_triggered();

    void on_actionLista_triggered();

private:
    Ui::Apoteka *ui;
};

#endif // APOTEKA_H
