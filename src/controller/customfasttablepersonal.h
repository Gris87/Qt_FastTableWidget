#ifndef CUSTOMFASTTABLEPERSONAL_H
#define CUSTOMFASTTABLEPERSONAL_H

#include "../fasttable/customfasttablewidget.h"

class CustomFastTablePersonal : public CustomFastTableWidget
{
    Q_OBJECT
public:
    explicit CustomFastTablePersonal(QWidget *parent = 0);

    QString text(const int row, const int column);
    QBrush backgroundBrush(const int row, const int column);
    QColor foregroundColor(const int row, const int column);
    QFont cellFont(const int row, const int column);
    int cellTextFlags(const int row, const int column);
};

#endif // CUSTOMFASTTABLEPERSONAL_H
