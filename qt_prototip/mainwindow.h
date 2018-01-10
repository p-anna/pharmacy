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
    void buttonDatabase_clicked();
    void buttonPurchase_clicked();
    void buttonOrder_clicked();
    void buttonHelp_clicked();
    void buttonExit_clicked();
    void buttonPrint_clicked();
    void tableWidgetDatabase_cellDoubleClicked(int row, int column);
    void tableWidgetPurchase_cellDoubleClicked(int row, int column);
    void lineEditSearch_textChanged(const QString &pattern);


private:
    void resizeEvent(QResizeEvent *event);
    void refreshDatabaseTable();
    void refreshPurchaseTable();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
