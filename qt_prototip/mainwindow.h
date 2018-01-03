#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void buttonHome_clicked();
    void buttonReceipts_clicked();
    void buttonBuySell_clicked();
    void buttonHelp_clicked();
    void buttonExit_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
