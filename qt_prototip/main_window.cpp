#include "main_window.h"
#include "db_delegate.h"
#include "initdb.h"

#include <QtSql>

main_window::main_window()
{
    ui.setupUi(this);

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, "Unable to load database", "SQLITE driver required");

    // init baze na osnovu initdb.h
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // kreiramo data model
    model = new QSqlRelationalTableModel(ui.db_table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("proizvod");

    // ovde zapamtimo indekse foreign key-eva
    id_idx = model->fieldIndex("id");

    // vezujemo kolonu, koja je foreign key za drugu tabelu
    // ne mozemo postaviti veze na vise tabela ovde, nazalost, ovo treba izmeniti svakako.
    //model->setRelation(id_idx, QSqlRelation("sirovina", "id", "id")); -- zato se sirovine nece videti u prikazu
    model->setRelation(id_idx, QSqlRelation("preparat", "id", "cena"));  // ne znam zasto se u tabeli ne ispisuje cena

    // caption-i u tabeli, iznad kolona
    model->setHeaderData(model->fieldIndex("naziv"), Qt::Horizontal, tr("NAZIV"));
    model->setHeaderData(id_idx, Qt::Horizontal, tr("CENA"));

    // select da pokupimo podatke
    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    // postavimo model
    ui.db_table->setModel(model);
    ui.db_table->setItemDelegate(new db_delegate(ui.db_table));
    ui.db_table->setSelectionMode(QAbstractItemView::SingleSelection);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new db_delegate(this));

    ui.db_table->setCurrentIndex(model->index(0, 0));
}

void main_window::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}
