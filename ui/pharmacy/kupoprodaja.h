#ifndef KUPOPRODAJA_H
#define KUPOPRODAJA_H

#include <QMainWindow>


namespace Ui {
class kupoprodaja;
}

class kupoprodaja : public QMainWindow
{
    Q_OBJECT

public:
    explicit kupoprodaja(QWidget *parent = 0);
    ~kupoprodaja();

private:
    Ui::kupoprodaja *ui;
};

#endif // KUPOPRODAJA_H
