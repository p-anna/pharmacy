#include "db_delegate.h"

#include <QtWidgets>

db_delegate::db_delegate(QObject *parent)
    : QSqlRelationalDelegate(parent)
{
}

void db_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    opt.rect.adjust(0, 0, -1, -1); // since we draw the grid ourselves
    QSqlRelationalDelegate::paint(painter, opt, index);

    QPen pen = painter->pen();
    painter->setPen(option.palette.color(QPalette::Mid));
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
    painter->setPen(pen);
}
