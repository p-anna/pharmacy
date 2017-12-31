#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <ui_main_window.h>
#include <QtWidgets>

class main_window : public QMainWindow
{
  Q_OBJECT

public:
  explicit main_window();

private:
  void showError(const QSqlError &err);
  Ui::main_window ui;
  QSqlRelationalTableModel *model;
  int id_idx; //indeks kolone u kojoj se cuva ID
};

#endif // MAIN_WINDOW_H
