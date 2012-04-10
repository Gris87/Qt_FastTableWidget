#ifndef PUBLICTABLEWIDGET_H
#define PUBLICTABLEWIDGET_H

#include "src/fasttable/fasttablewidget.h"

class PublicFastTable : public FastTableWidget
{
public:
    QList< QList<QBrush *> > *getBackgroundBrushes();
    QList< QList<QColor *> > *getForegroundColors();
    QList< QList<QFont *> >  *getCellFonts();
    QList< QList<int> >      *getCellTextFlags();
    QList< QList<quint16> >  *getCellMergeX();
    QList< QList<quint16> >  *getCellMergeY();
    QList< QList<int> >      *getCellMergeParentRow();
    QList< QList<int> >      *getCellMergeParentColumn();

    QList< QList<QBrush *> > *getHorizontalHeaderBackgroundBrushes();
    QList< QList<QColor *> > *getHorizontalHeaderForegroundColors();
    QList< QList<QFont *> >  *getHorizontalHeaderCellFonts();
    QList< QList<int> >      *getHorizontalHeaderCellTextFlags();
    QList< QList<quint16> >  *getHorizontalHeaderCellMergeX();
    QList< QList<quint16> >  *getHorizontalHeaderCellMergeY();
    QList< QList<int> >      *getHorizontalHeaderCellMergeParentRow();
    QList< QList<int> >      *getHorizontalHeaderCellMergeParentColumn();

    QList< QList<QBrush *> > *getVerticalHeaderBackgroundBrushes();
    QList< QList<QColor *> > *getVerticalHeaderForegroundColors();
    QList< QList<QFont *> >  *getVerticalHeaderCellFonts();
    QList< QList<int> >      *getVerticalHeaderCellTextFlags();
    QList< QList<quint16> >  *getVerticalHeaderCellMergeX();
    QList< QList<quint16> >  *getVerticalHeaderCellMergeY();
    QList< QList<int> >      *getVerticalHeaderCellMergeParentRow();
    QList< QList<int> >      *getVerticalHeaderCellMergeParentColumn();
};

class PublicCustomFastTable : public CustomFastTableWidget
{
public:
    int getRowCount();
    int getColumnCount();
    qint16 getHorizontalHeaderRowCount();
    qint16 getVerticalHeaderColumnCount();

    QBrush getDefaultBackgroundBrush();
    QColor getDefaultForegroundColor();
    QColor getGridColor();

    QBrush getHorizontalHeaderDefaultBackgroundBrush();
    QColor getHorizontalHeaderDefaultForegroundColor();
    QColor getHorizontalHeaderGridColor();

    QBrush getVerticalHeaderDefaultBackgroundBrush();
    QColor getVerticalHeaderDefaultForegroundColor();
    QColor getVerticalHeaderGridColor();

    QBrush getSelectionBrush();

    quint16 getDefaultWidth();
    quint16 getDefaultHeight();
    int getTotalWidth();
    int getTotalHeight();
    int getVerticalHeaderTotalWidth();
    int getHorizontalHeaderTotalHeight();

    int getVisibleLeft();
    int getVisibleRight();
    int getVisibleTop();
    int getVisibleBottom();

    int getHorizontalHeaderVisibleLeft();
    int getHorizontalHeaderVisibleRight();
    int getHorizontalHeaderVisibleTop();
    int getHorizontalHeaderVisibleBottom();

    int getVerticalHeaderVisibleLeft();
    int getVerticalHeaderVisibleRight();
    int getVerticalHeaderVisibleTop();
    int getVerticalHeaderVisibleBottom();

    QList< QStringList > *getData();
    QList< quint16 >     *getRowHeights();
    QList< quint16 >     *getColumnWidths();
    QList< int >         *getOffsetX();
    QList< int >         *getOffsetY();

    QList< QStringList > *getHorizontalHeaderData();
    QList< quint16 >     *getHorizontalHeaderRowHeights();
    QList< quint16 >     *getHorizontalHeaderColumnWidths();
    QList< int >         *getHorizontalHeaderOffsetX();
    QList< int >         *getHorizontalHeaderOffsetY();

    QList< QStringList > *getVerticalHeaderData();
    QList< quint16 >     *getVerticalHeaderRowHeights();
    QList< quint16 >     *getVerticalHeaderColumnWidths();
    QList< int >         *getVerticalHeaderOffsetX();
    QList< int >         *getVerticalHeaderOffsetY();

    QList< QList<bool> > *getSelectedCells();
    QList< QPoint >      *getCurSelection();
    QList< bool >        *getHorizontalHeaderSelectedColumns();
    QList< bool >        *getVerticalHeaderSelectedRows();
};

#endif // PUBLICTABLEWIDGET_H
