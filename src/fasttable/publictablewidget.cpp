#include "publictablewidget.h"

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

QList< QList<QBrush *> >  *PublicFastTable::horizontalHeader_GetBackgroundBrushes()
{
    return &mBackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::horizontalHeader_GetForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::horizontalHeader_GetCellFonts()
{
    return &mCellFonts;
}

QList< QList<int> >       *PublicFastTable::horizontalHeader_GetCellTextFlags()
{
    return &mCellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::horizontalHeader_GetCellMergeX()
{
    return &mCellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::horizontalHeader_GetCellMergeY()
{
    return &mCellMergeY;
}

QList< QList<int> >       *PublicFastTable::horizontalHeader_GetCellMergeParentRow()
{
    return &mCellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::horizontalHeader_GetCellMergeParentColumn()
{
    return &mCellMergeParentColumn;
}

QList< QList<QBrush *> >  *PublicFastTable::verticalHeader_GetBackgroundBrushes()
{
    return &mBackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::verticalHeader_GetForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::verticalHeader_GetCellFonts()
{
    return &mCellFonts;
}

QList< QList<int> >       *PublicFastTable::verticalHeader_GetCellTextFlags()
{
    return &mCellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::verticalHeader_GetCellMergeX()
{
    return &mCellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::verticalHeader_GetCellMergeY()
{
    return &mCellMergeY;
}

QList< QList<int> >       *PublicFastTable::verticalHeader_GetCellMergeParentRow()
{
    return &mCellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::verticalHeader_GetCellMergeParentColumn()
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

qint16 PublicCustomFastTable::horizontalHeader_GetRowCount()
{
    return mHorizontalHeader_RowCount;
}

qint16 PublicCustomFastTable::verticalHeader_GetColumnCount()
{
    return mVerticalHeader_ColumnCount;
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

QBrush PublicCustomFastTable::horizontalHeader_GetDefaultBackgroundBrush()
{
    return mHorizontalHeader_DefaultBackgroundBrush;
}

QColor PublicCustomFastTable::horizontalHeader_GetDefaultForegroundColor()
{
    return mHorizontalHeader_DefaultForegroundColor;
}

QColor PublicCustomFastTable::horizontalHeader_GetGridColor()
{
    return mHorizontalHeader_GridColor;
}

QBrush PublicCustomFastTable::verticalHeader_GetDefaultBackgroundBrush()
{
    return mVerticalHeader_DefaultBackgroundBrush;
}

QColor PublicCustomFastTable::verticalHeader_GetDefaultForegroundColor()
{
    return mVerticalHeader_DefaultForegroundColor;
}

QColor PublicCustomFastTable::verticalHeader_GetGridColor()
{
    return mVerticalHeader_GridColor;
}

QBrush PublicCustomFastTable::getSelectionBrush()
{
    return mSelectionBrush;
}

quint16 PublicCustomFastTable::getDefaultWidth()
{
    return mDefaultWidth;
}

quint16 PublicCustomFastTable::getDefaultHeight()
{
    return mDefaultHeight;
}

int PublicCustomFastTable::getTotalWidth()
{
    return mTotalWidth;
}

int PublicCustomFastTable::getTotalHeight()
{
    return mTotalHeight;
}

int PublicCustomFastTable::verticalHeader_GetTotalWidth()
{
    return mVerticalHeader_TotalWidth;
}

int PublicCustomFastTable::horizontalHeader_GetTotalHeight()
{
    return mHorizontalHeader_TotalHeight;
}

int PublicCustomFastTable::getVisibleLeft()
{
    return mVisibleLeft;
}

int PublicCustomFastTable::getVisibleRight()
{
    return mVisibleRight;
}

int PublicCustomFastTable::getVisibleTop()
{
    return mVisibleTop;
}

int PublicCustomFastTable::getVisibleBottom()
{
    return mVisibleBottom;
}

int PublicCustomFastTable::horizontalHeader_GetVisibleLeft()
{
    return mHorizontalHeader_VisibleLeft;
}

int PublicCustomFastTable::horizontalHeader_GetVisibleRight()
{
    return mHorizontalHeader_VisibleRight;
}

int PublicCustomFastTable::horizontalHeader_GetVisibleTop()
{
    return mHorizontalHeader_VisibleTop;
}

int PublicCustomFastTable::horizontalHeader_GetVisibleBottom()
{
    return mHorizontalHeader_VisibleBottom;
}

int PublicCustomFastTable::verticalHeader_GetVisibleLeft()
{
    return mVerticalHeader_VisibleLeft;
}

int PublicCustomFastTable::verticalHeader_GetVisibleRight()
{
    return mVerticalHeader_VisibleRight;
}

int PublicCustomFastTable::verticalHeader_GetVisibleTop()
{
    return mVerticalHeader_VisibleTop;
}

int PublicCustomFastTable::verticalHeader_GetVisibleBottom()
{
    return mVerticalHeader_VisibleBottom;
}

QList< QStringList > *PublicCustomFastTable::getData()
{
    return &mData;
}

QList< quint16 >     *PublicCustomFastTable::getRowHeights()
{
    return &mRowHeights;
}

QList< quint16 >     *PublicCustomFastTable::getColumnWidths()
{
    return &mColumnWidths;
}

QList< int >         *PublicCustomFastTable::getOffsetX()
{
    return &mOffsetX;
}

QList< int >         *PublicCustomFastTable::getOffsetY()
{
    return &mOffsetY;
}

QList< QStringList > *PublicCustomFastTable::horizontalHeader_GetData()
{
    return &mHorizontalHeader_Data;
}

QList< quint16 >     *PublicCustomFastTable::horizontalHeader_GetRowHeights()
{
    return &mHorizontalHeader_RowHeights;
}

QList< int >         *PublicCustomFastTable::horizontalHeader_GetOffsetX()
{
    return &mHorizontalHeader_OffsetX;
}

QList< int >         *PublicCustomFastTable::horizontalHeader_GetOffsetY()
{
    return &mHorizontalHeader_OffsetY;
}

QList< QStringList > *PublicCustomFastTable::verticalHeader_GetData()
{
    return &mVerticalHeader_Data;
}

QList< quint16 >     *PublicCustomFastTable::verticalHeader_GetColumnWidths()
{
    return &mVerticalHeader_ColumnWidths;
}

QList< int >         *PublicCustomFastTable::verticalHeader_GetOffsetX()
{
    return &mVerticalHeader_OffsetX;
}

QList< int >         *PublicCustomFastTable::verticalHeader_GetOffsetY()
{
    return &mVerticalHeader_OffsetY;
}

QList< QList<bool> > *PublicCustomFastTable::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPoint >      *PublicCustomFastTable::getCurSelection()
{
    return &mCurSelection;
}

QList< bool >        *PublicCustomFastTable::horizontalHeader_GetSelectedColumns()
{
    return &mHorizontalHeader_SelectedColumns;
}

QList< bool >        *PublicCustomFastTable::verticalHeader_GetSelectedRows()
{
    return &mVerticalHeader_SelectedRows;
}
