#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
