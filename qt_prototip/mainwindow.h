#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

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

    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_tableWidget_2_cellDoubleClicked(int row, int column);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    void refreshDataBaseTable();
    void refreshPurchaseTable();

    Ui::MainWindow *ui;
    QMainWindow *_w;
};

#endif // MAINWINDOW_H
/*
QWidget *cWidget;
QFrame *cFrame;
QWidget *lWidget;
QVBoxLayout *vLayout;
QSpinBox *sBox;
QPushButton *pButton;

cWidget = new QWidget(_w);
cWidget->setObjectName("cWidget");
cFrame = new QFrame(cWidget);
cFrame->setObjectName("cFrame");
cFrame->setGeometry(0, 0, 295, 245);

lWidget = new QWidget(cFrame);
lWidget->setObjectName("lWidget");
lWidget->setGeometry(0, 0, 290, 240);
vLayout = new QVBoxLayout(lWidget);
vLayout->setObjectName("vLayout");
vLayout->setSpacing(1);

sBox = new QSpinBox(lWidget);
sBox->setObjectName("sBox");
vLayout->addWidget(sBox);

pButton = new QPushButton(lWidget);
pButton->setObjectName("pButton");
vLayout->addWidget(pButton);

cWidget->show();
*/
