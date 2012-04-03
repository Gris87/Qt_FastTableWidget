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

    QBrush getDefaultBackgroundBrush();
    QColor getDefaultForegroundColor();
    QColor getGridColor();
    QBrush getSelectionBrush();

    QList< QStringList >      *getData();
    QList< quint16 >          *getRowHeights();
    QList< quint16 >          *getColumnWidths();
    QList< int >              *getOffsetX();
    QList< int >              *getOffsetY();
    QList< QList<bool> >      *getSelectedCells();
    QList< QPoint >           *getCurSelection();
    QList< QList<QBrush *> >  *getBackgroundBrushes();
    QList< QList<QColor *> >  *getForegroundColors();
    QList< QList<QFont *> >   *getCellFonts();
    QList< QList<int> >       *getCellTextFlags();
    QList< QList<quint16> >   *getCellMergeX();
    QList< QList<quint16> >   *getCellMergeY();
    QList< QList<int> >       *getCellMergeParentRow();
    QList< QList<int> >       *getCellMergeParentColumn();

    bool getStartSelection();
};

#endif // FASTTABLETEST_H
