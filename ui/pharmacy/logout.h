#ifndef LOGOUT_H
#define LOGOUT_H

#include <QDialog>

namespace Ui {
class Logout;
}

class Logout : public QDialog
{
    Q_OBJECT

public:
    explicit Logout(QWidget *parent = 0);
    ~Logout();

private:
    Ui::Logout *ui;
};

#endif // LOGOUT_H
