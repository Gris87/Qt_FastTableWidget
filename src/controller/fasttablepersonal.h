#ifndef FASTTABLEPERSONAL_H
#define FASTTABLEPERSONAL_H

#include "../fasttable/fasttablewidget.h"

class FastTablePersonal : public FastTableWidget
{
    Q_OBJECT
public:
    explicit FastTablePersonal(QWidget *parent = 0);

    QString text(const int row, const int column);
    QBrush backgroundBrush(const int row, const int column);
    QColor foregroundColor(const int row, const int column);
    QFont cellFont(const int row, const int column);
    int cellTextFlags(const int row, const int column);
};

#endif // FASTTABLEPERSONAL_H
