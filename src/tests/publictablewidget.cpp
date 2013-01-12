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

QList< QRect >            *PublicFastTable::getMerges()
{
    return &mMerges;
}

QList< QList<QBrush *> >  *PublicFastTable::horizontalHeader_GetBackgroundBrushes()
{
    return &mHorizontalHeader_BackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::horizontalHeader_GetForegroundColors()
{
    return &mHorizontalHeader_ForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::horizontalHeader_GetCellFonts()
{
    return &mHorizontalHeader_CellFonts;
}

QList< QList<int> >       *PublicFastTable::horizontalHeader_GetCellTextFlags()
{
    return &mHorizontalHeader_CellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::horizontalHeader_GetCellMergeX()
{
    return &mHorizontalHeader_CellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::horizontalHeader_GetCellMergeY()
{
    return &mHorizontalHeader_CellMergeY;
}

QList< QList<int> >       *PublicFastTable::horizontalHeader_GetCellMergeParentRow()
{
    return &mHorizontalHeader_CellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::horizontalHeader_GetCellMergeParentColumn()
{
    return &mHorizontalHeader_CellMergeParentColumn;
}

QList< QRect >            *PublicFastTable::horizontalHeader_GetMerges()
{
    return &mHorizontalHeader_Merges;
}

QList< QList<QBrush *> >  *PublicFastTable::verticalHeader_GetBackgroundBrushes()
{
    return &mVerticalHeader_BackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::verticalHeader_GetForegroundColors()
{
    return &mVerticalHeader_ForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::verticalHeader_GetCellFonts()
{
    return &mVerticalHeader_CellFonts;
}

QList< QList<int> >       *PublicFastTable::verticalHeader_GetCellTextFlags()
{
    return &mVerticalHeader_CellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::verticalHeader_GetCellMergeX()
{
    return &mVerticalHeader_CellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::verticalHeader_GetCellMergeY()
{
    return &mVerticalHeader_CellMergeY;
}

QList< QList<int> >       *PublicFastTable::verticalHeader_GetCellMergeParentRow()
{
    return &mVerticalHeader_CellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::verticalHeader_GetCellMergeParentColumn()
{
    return &mVerticalHeader_CellMergeParentColumn;
}

QList< QRect >            *PublicFastTable::verticalHeader_GetMerges()
{
    return &mVerticalHeader_Merges;
}

// ==============================================================================================================

QColor PublicCustomFastTable::getGridColor()
{
    return mGridColor;
}

QColor PublicCustomFastTable::getCellBorderColor()
{
    return mCellBorderColor;
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

QColor PublicCustomFastTable::horizontalHeader_GetCellBorderColor()
{
    return mHorizontalHeader_CellBorderColor;
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

QColor PublicCustomFastTable::verticalHeader_GetCellBorderColor()
{
    return mVerticalHeader_CellBorderColor;
}

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

int PublicCustomFastTable::horizontalHeader_GetVisibleBottom()
{
    return mHorizontalHeader_VisibleBottom;
}

int PublicCustomFastTable::verticalHeader_GetVisibleRight()
{
    return mVerticalHeader_VisibleRight;
}

QList< QStringList > *PublicCustomFastTable::getData()
{
    return &mData;
}

QList< qint16 >      *PublicCustomFastTable::getRowHeights()
{
    return &mRowHeights;
}

QList< qint16 >      *PublicCustomFastTable::getColumnWidths()
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

QList< qint16 >      *PublicCustomFastTable::horizontalHeader_GetRowHeights()
{
    return &mHorizontalHeader_RowHeights;
}

QList< int >         *PublicCustomFastTable::horizontalHeader_GetOffsetY()
{
    return &mHorizontalHeader_OffsetY;
}

QList< QStringList > *PublicCustomFastTable::verticalHeader_GetData()
{
    return &mVerticalHeader_Data;
}

QList< qint16 >      *PublicCustomFastTable::verticalHeader_GetColumnWidths()
{
    return &mVerticalHeader_ColumnWidths;
}

QList< int >         *PublicCustomFastTable::verticalHeader_GetOffsetX()
{
    return &mVerticalHeader_OffsetX;
}

QList< QList<bool> > *PublicCustomFastTable::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPoint >      *PublicCustomFastTable::getCurSelection()
{
    return &mCurSelection;
}

QList< int >         *PublicCustomFastTable::horizontalHeader_GetSelectedColumns()
{
    return &mHorizontalHeader_SelectedColumns;
}

QList< int >         *PublicCustomFastTable::verticalHeader_GetSelectedRows()
{
    return &mVerticalHeader_SelectedRows;
}

int PublicCustomFastTable::getCurrentRow()
{
    return mCurrentRow;
}

int PublicCustomFastTable::getCurrentColumn()
{
    return mCurrentColumn;
}

int PublicCustomFastTable::getLastX()
{
    return mLastX;
}

int PublicCustomFastTable::getLastY()
{
    return mLastY;
}

int PublicCustomFastTable::getMouseXForShift()
{
    return mMouseXForShift;
}

int PublicCustomFastTable::getMouseYForShift()
{
    return mMouseYForShift;
}

int PublicCustomFastTable::getMouseResizeLineX()
{
    return mMouseResizeLineX;
}

int PublicCustomFastTable::getMouseResizeLineY()
{
    return mMouseResizeLineY;
}

int PublicCustomFastTable::getMouseResizeCell()
{
    return mMouseResizeCell;
}

bool PublicCustomFastTable::getMousePressed()
{
    return mMousePressed;
}

bool PublicCustomFastTable::getCtrlPressed()
{
    return mCtrlPressed;
}

bool PublicCustomFastTable::getShiftPressed()
{
    return mShiftPressed;
}

CustomFastTableWidget::MouseLocation PublicCustomFastTable::getMouseLocation()
{
    return mMouseLocation;
}

CustomFastTableWidget::MouseLocation PublicCustomFastTable::getMouseLocationForShift()
{
    return mMouseLocationForShift;
}

QList< QList<bool> > *PublicCustomFastTable::getMouseSelectedCells()
{
    return &mMouseSelectedCells;
}
