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
    void buttonPrint_clicked();
    void tableWidgetDatabase_cellDoubleClicked(int row, int column);
    void tableWidgetPurchase_cellDoubleClicked(int row, int column);
    void lineEditSearch_textChanged(const QString &pattern);


private:
    void refreshDatabaseTable();
    void refreshPurchaseTable();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
