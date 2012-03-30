#ifndef FASTTABLETEST_H
#define FASTTABLETEST_H

#include "fasttablewidget.h"

class FastTableTest : public FastTableWidget
{
    Q_OBJECT
public:
    explicit FastTableTest(QWidget *parent = 0);

    int getRowCount();
    int getColumnCount();

    quint16 getDefaultHeight();
    quint16 getDefaultWidth();
    int     getTotalHeight();
    int     getTotalWidth();

    QColor getDefaultBackgroundColor();
    QColor getDefaultForegroundColor();
    QColor getGridColor();
    QColor getSelectionColor();

    QList< QStringList >      *getData();
    QList< quint16 >          *getRowHeights();
    QList< quint16 >          *getColumnWidths();
    QList< int >              *getOffsetX();
    QList< int >              *getOffsetY();
    QList< QList<bool> >      *getSelectedCells();
    QList< QPoint >           *getCurSelection();
    QList< QList<QColor *> >  *getBackgroundColors();
    QList< QList<QColor *> >  *getForegroundColors();
    QList< QList<QFont *> >   *getCellFonts();
    QList< QList<int> >       *getCellTextFlags();

    bool getStartSelection();
};

#endif // FASTTABLETEST_H
