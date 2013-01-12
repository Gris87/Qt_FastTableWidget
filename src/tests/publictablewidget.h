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
    QList< QRect >           *getMerges();

    QList< QList<QBrush *> > *horizontalHeader_GetBackgroundBrushes();
    QList< QList<QColor *> > *horizontalHeader_GetForegroundColors();
    QList< QList<QFont *> >  *horizontalHeader_GetCellFonts();
    QList< QList<int> >      *horizontalHeader_GetCellTextFlags();
    QList< QList<quint16> >  *horizontalHeader_GetCellMergeX();
    QList< QList<quint16> >  *horizontalHeader_GetCellMergeY();
    QList< QList<int> >      *horizontalHeader_GetCellMergeParentRow();
    QList< QList<int> >      *horizontalHeader_GetCellMergeParentColumn();
    QList< QRect >           *horizontalHeader_GetMerges();

    QList< QList<QBrush *> > *verticalHeader_GetBackgroundBrushes();
    QList< QList<QColor *> > *verticalHeader_GetForegroundColors();
    QList< QList<QFont *> >  *verticalHeader_GetCellFonts();
    QList< QList<int> >      *verticalHeader_GetCellTextFlags();
    QList< QList<quint16> >  *verticalHeader_GetCellMergeX();
    QList< QList<quint16> >  *verticalHeader_GetCellMergeY();
    QList< QList<int> >      *verticalHeader_GetCellMergeParentRow();
    QList< QList<int> >      *verticalHeader_GetCellMergeParentColumn();
    QList< QRect >           *verticalHeader_GetMerges();
};

class PublicCustomFastTable : public CustomFastTableWidget
{
public:
    QColor getGridColor();
    QColor getCellBorderColor();

    QBrush horizontalHeader_GetDefaultBackgroundBrush();
    QColor horizontalHeader_GetDefaultForegroundColor();
    QColor horizontalHeader_GetGridColor();
    QColor horizontalHeader_GetCellBorderColor();

    QBrush verticalHeader_GetDefaultBackgroundBrush();
    QColor verticalHeader_GetDefaultForegroundColor();
    QColor verticalHeader_GetGridColor();
    QColor verticalHeader_GetCellBorderColor();

    int getRowCount();
    int getColumnCount();
    qint16 horizontalHeader_GetRowCount();
    qint16 verticalHeader_GetColumnCount();

    quint16 getDefaultWidth();
    quint16 getDefaultHeight();
    int getTotalWidth();
    int getTotalHeight();
    int verticalHeader_GetTotalWidth();
    int horizontalHeader_GetTotalHeight();

    int getVisibleLeft();
    int getVisibleRight();
    int getVisibleTop();
    int getVisibleBottom();

    int horizontalHeader_GetVisibleBottom();

    int verticalHeader_GetVisibleRight();

    QList< QStringList > *getData();
    QList< qint16 >      *getRowHeights();
    QList< qint16 >      *getColumnWidths();
    QList< int >         *getOffsetX();
    QList< int >         *getOffsetY();

    QList< QStringList > *horizontalHeader_GetData();
    QList< qint16 >      *horizontalHeader_GetRowHeights();
    QList< int >         *horizontalHeader_GetOffsetY();

    QList< QStringList > *verticalHeader_GetData();
    QList< qint16 >      *verticalHeader_GetColumnWidths();
    QList< int >         *verticalHeader_GetOffsetX();

    QList< QList<bool> > *getSelectedCells();
    QList< QPoint >      *getCurSelection();
    QList< int >         *horizontalHeader_GetSelectedColumns();
    QList< int >         *verticalHeader_GetSelectedRows();

    int getCurrentRow();
    int getCurrentColumn();

    int getLastX();
    int getLastY();
    int getMouseXForShift();
    int getMouseYForShift();
    int getMouseResizeLineX();
    int getMouseResizeLineY();
    int getMouseResizeCell();

    bool getMousePressed();
    bool getCtrlPressed();
    bool getShiftPressed();

    MouseLocation getMouseLocation();
    MouseLocation getMouseLocationForShift();

    QList< QList<bool> > *getMouseSelectedCells();
};

#endif // PUBLICTABLEWIDGET_H
