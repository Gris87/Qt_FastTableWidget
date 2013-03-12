#include "customfasttablepersonal.h"

CustomFastTablePersonal::CustomFastTablePersonal(QWidget *parent) :
    CustomFastTableWidget(false, parent)
{
}

QString CustomFastTablePersonal::text(const int row, const int column)
{
    return QString::number(row)+"+"+QString::number(column)+"="+QString::number(row+column);
}

QBrush CustomFastTablePersonal::backgroundBrush(const int row, const int /*column*/)
{
    return QBrush(QColor((quint8)(row << 6), (quint8)(row >> 2), (quint8)(row >> 10)));
}

QColor CustomFastTablePersonal::foregroundColor(const int row, const int column)
{
    quint8 aPart=row*8+column;
    return QColor(255-aPart, 255-aPart, 255-aPart);
}

QFont CustomFastTablePersonal::cellFont(const int /*row*/, const int /*column*/)
{
    return QFont("Arial", 12, QFont::Bold);
}

int CustomFastTablePersonal::cellTextFlags(const int /*row*/, const int /*column*/)
{
    return Qt::AlignRight | Qt::AlignVCenter;
}
