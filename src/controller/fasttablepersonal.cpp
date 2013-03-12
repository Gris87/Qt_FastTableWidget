#include "fasttablepersonal.h"

FastTablePersonal::FastTablePersonal(QWidget *parent) :
    FastTableWidget(false, parent)
{
}

QString FastTablePersonal::text(const int row, const int column)
{
    return QString::number(row)+"+"+QString::number(column)+"="+QString::number(row+column);
}

QBrush FastTablePersonal::backgroundBrush(const int row, const int /*column*/)
{
    return QBrush(QColor((quint8)(row << 6), (quint8)(row >> 2), (quint8)(row >> 10)));
}

QColor FastTablePersonal::foregroundColor(const int row, const int column)
{
    quint8 aPart=row*8+column;
    return QColor(255-aPart, 255-aPart, 255-aPart);
}

QFont FastTablePersonal::cellFont(const int /*row*/, const int /*column*/)
{
    return QFont("Arial", 12, QFont::Bold);
}

int FastTablePersonal::cellTextFlags(const int /*row*/, const int /*column*/)
{
    return Qt::AlignRight | Qt::AlignVCenter;
}
