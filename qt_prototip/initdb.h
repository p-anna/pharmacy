#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

// veoma ogranicen isecak iz baze
// U TABELI SIROVINA FALI CENA (u modelu baze tj.; ovde je ubacena)?

void add_proizvod(QSqlQuery &q, const QVariant &id, const QString &naziv)
{
    q.addBindValue(id);
    q.addBindValue(naziv);
    q.exec();
    //title year authorID genreID rating
}

QVariant add_preparat(QSqlQuery &q, const int id, const double cena, const QString &bar_kod, const int na_recept)
{
    q.addBindValue(id);
    q.addBindValue(cena);
    q.addBindValue(bar_kod);
    q.addBindValue(na_recept);
    q.exec();
    return q.lastInsertId();
}

QVariant add_sirovina(QSqlQuery &q, const int id, const double cena, const QString &tip_sirovine)
{
    q.addBindValue(id);
    q.addBindValue(cena);
    q.addBindValue(tip_sirovine);
    q.exec();
    return q.lastInsertId();
}

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("proizvod", Qt::CaseInsensitive)
        && tables.contains("preparat", Qt::CaseInsensitive)
        && tables.contains("sirovina", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(QLatin1String("create table proizvod(id integer primary key, naziv varchar not null)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table preparat(id integer primary key, cena double, bar_kod varchar, na_recept integer)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table sirovina(id integer primary key, cena double, tip_sirovine varchar)")))
        return q.lastError();

    if (!q.prepare(QLatin1String("insert into preparat(id, cena, bar_kod, na_recept) values(?, ?, ?, ?)")))
        return q.lastError();
    QVariant brufen_id = add_preparat(q, 1, 10, "xxx", 0);
    QVariant aspirin_id = add_preparat(q, 2, 100, "yyy", 0);
    QVariant bensedin_id = add_preparat(q, 3, 1000, "zzz", 0);

    if (!q.prepare(QLatin1String("insert into sirovina(id, cena, tip_sirovine) values(?, ?, ?)")))
        return q.lastError();
    QVariant sirovina1_id = add_sirovina(q, 4, 20, QLatin1String("Prva vrsta"));
    QVariant sirovina2_id = add_sirovina(q, 5, 200, QLatin1String("Druga vrsta"));

    if (!q.prepare(QLatin1String("insert into proizvod(id, naziv) values(?, ?)")))
        return q.lastError();
    add_proizvod(q, brufen_id, QLatin1String("Brufen"));
    add_proizvod(q, aspirin_id, QLatin1String("Aspirin"));
    add_proizvod(q, bensedin_id, QLatin1String("Bensedin"));
    add_proizvod(q, sirovina1_id, QLatin1String("Sirovina1"));
    add_proizvod(q, sirovina2_id, QLatin1String("Sirovina2"));
    return QSqlError();
}

#endif
