#ifndef PUBLICTABLEWIDGET_H
#define PUBLICTABLEWIDGET_H

#include "src/fasttable/fasttablewidget.h"

class PublicFastTable : public FastTableWidget
{
public:
    int getRowCount();
    int getColumnCount();

    quint16 getDefaultHeight();
    quint16 getDefaultWidth();
    int getTotalHeight();
    int getTotalWidth();

    QBrush getDefaultBackgroundBrush();
    QColor getDefaultForegroundColor();
    QColor getGridColor();
    QBrush getSelectionBrush();

    int getVisibleLeft();
    int getVisibleRight();
    int getVisibleTop();
    int getVisibleBottom();

    QList< QStringList >     *getData();
    QList< quint16 >         *getRowHeights();
    QList< quint16 >         *getColumnWidths();
    QList< int >             *getOffsetX();
    QList< int >             *getOffsetY();
    QList< QList<bool> >     *getSelectedCells();
    QList< QPoint >          *getCurSelection();
    QList< QList<QBrush *> > *getBackgroundBrushes();
    QList< QList<QColor *> > *getForegroundColors();
    QList< QList<QFont *> >  *getCellFonts();
    QList< QList<int> >      *getCellTextFlags();
    QList< QList<quint16> >  *getCellMergeX();
    QList< QList<quint16> >  *getCellMergeY();
    QList< QList<int> >      *getCellMergeParentRow();
    QList< QList<int> >      *getCellMergeParentColumn();
};

class PublicCustomFastTable : public FastTableWidget
{
public:
    int getRowCount();
    int getColumnCount();

    quint16 getDefaultHeight();
    quint16 getDefaultWidth();
    int getTotalHeight();
    int getTotalWidth();

    QBrush getDefaultBackgroundBrush();
    QColor getDefaultForegroundColor();
    QColor getGridColor();
    QBrush getSelectionBrush();

    int getVisibleLeft();
    int getVisibleRight();
    int getVisibleTop();
    int getVisibleBottom();

    QList< QStringList >     *getData();
    QList< quint16 >         *getRowHeights();
    QList< quint16 >         *getColumnWidths();
    QList< int >             *getOffsetX();
    QList< int >             *getOffsetY();
    QList< QList<bool> >     *getSelectedCells();
    QList< QPoint >          *getCurSelection();
};

#endif // PUBLICTABLEWIDGET_H
