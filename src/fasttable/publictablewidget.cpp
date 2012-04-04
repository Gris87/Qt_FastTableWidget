#include "publictablewidget.h"

int PublicFastTable::getRowCount()
{
    return mRowCount;
}

int PublicFastTable::getColumnCount()
{
    return mColumnCount;
}

quint16 PublicFastTable::getDefaultHeight()
{
    return mDefaultHeight;
}

quint16 PublicFastTable::getDefaultWidth()
{
    return mDefaultWidth;
}

int     PublicFastTable::getTotalHeight()
{
    return mTotalHeight;
}

int     PublicFastTable::getTotalWidth()
{
    return mTotalWidth;
}

QBrush PublicFastTable::getDefaultBackgroundBrush()
{
    return mDefaultBackgroundBrush;
}

QColor PublicFastTable::getDefaultForegroundColor()
{
    return mDefaultForegroundColor;
}

QColor PublicFastTable::getGridColor()
{
    return mGridColor;
}

QBrush PublicFastTable::getSelectionBrush()
{
    return mSelectionBrush;
}

QList< QStringList >      *PublicFastTable::getData()
{
    return &mData;
}

QList< quint16 >          *PublicFastTable::getRowHeights()
{
    return &mRowHeights;
}

QList< quint16 >          *PublicFastTable::getColumnWidths()
{
    return &mColumnWidths;
}

QList< int >              *PublicFastTable::getOffsetX()
{
    return &mOffsetX;
}

QList< int >              *PublicFastTable::getOffsetY()
{
    return &mOffsetY;
}

QList< QList<bool> >      *PublicFastTable::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPoint >           *PublicFastTable::getCurSelection()
{
    return &mCurSelection;
}

QList< QList<QBrush *> >  *PublicFastTable::getBackgroundBrushes()
{
    return &mBackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::getForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::getCellFonts()
{
    return &mCellFonts;
}

QList< QList<int> >       *PublicFastTable::getCellTextFlags()
{
    return &mCellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::getCellMergeX()
{
    return &mCellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::getCellMergeY()
{
    return &mCellMergeY;
}

QList< QList<int> >       *PublicFastTable::getCellMergeParentRow()
{
    return &mCellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::getCellMergeParentColumn()
{
    return &mCellMergeParentColumn;
}

// ==============================================================================================================

int PublicCustomFastTable::getRowCount()
{
    return mRowCount;
}

int PublicCustomFastTable::getColumnCount()
{
    return mColumnCount;
}

quint16 PublicCustomFastTable::getDefaultHeight()
{
    return mDefaultHeight;
}

quint16 PublicCustomFastTable::getDefaultWidth()
{
    return mDefaultWidth;
}

int     PublicCustomFastTable::getTotalHeight()
{
    return mTotalHeight;
}

int     PublicCustomFastTable::getTotalWidth()
{
    return mTotalWidth;
}

QBrush PublicCustomFastTable::getDefaultBackgroundBrush()
{
    return mDefaultBackgroundBrush;
}

QColor PublicCustomFastTable::getDefaultForegroundColor()
{
    return mDefaultForegroundColor;
}

QColor PublicCustomFastTable::getGridColor()
{
    return mGridColor;
}

QBrush PublicCustomFastTable::getSelectionBrush()
{
    return mSelectionBrush;
}

QList< QStringList >      *PublicCustomFastTable::getData()
{
    return &mData;
}

QList< quint16 >          *PublicCustomFastTable::getRowHeights()
{
    return &mRowHeights;
}

QList< quint16 >          *PublicCustomFastTable::getColumnWidths()
{
    return &mColumnWidths;
}

QList< int >              *PublicCustomFastTable::getOffsetX()
{
    return &mOffsetX;
}

QList< int >              *PublicCustomFastTable::getOffsetY()
{
    return &mOffsetY;
}

QList< QList<bool> >      *PublicCustomFastTable::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPoint >           *PublicCustomFastTable::getCurSelection()
{
    return &mCurSelection;
}
