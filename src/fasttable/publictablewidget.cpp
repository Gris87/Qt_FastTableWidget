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

QList< QList<QBrush *> >  *PublicFastTable::getHorizontalHeaderBackgroundBrushes()
{
    return &mBackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::getHorizontalHeaderForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::getHorizontalHeaderCellFonts()
{
    return &mCellFonts;
}

QList< QList<int> >       *PublicFastTable::getHorizontalHeaderCellTextFlags()
{
    return &mCellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::getHorizontalHeaderCellMergeX()
{
    return &mCellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::getHorizontalHeaderCellMergeY()
{
    return &mCellMergeY;
}

QList< QList<int> >       *PublicFastTable::getHorizontalHeaderCellMergeParentRow()
{
    return &mCellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::getHorizontalHeaderCellMergeParentColumn()
{
    return &mCellMergeParentColumn;
}

QList< QList<QBrush *> >  *PublicFastTable::getVerticalHeaderBackgroundBrushes()
{
    return &mBackgroundBrushes;
}

QList< QList<QColor *> >  *PublicFastTable::getVerticalHeaderForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *PublicFastTable::getVerticalHeaderCellFonts()
{
    return &mCellFonts;
}

QList< QList<int> >       *PublicFastTable::getVerticalHeaderCellTextFlags()
{
    return &mCellTextFlags;
}

QList< QList<quint16> >   *PublicFastTable::getVerticalHeaderCellMergeX()
{
    return &mCellMergeX;
}

QList< QList<quint16> >   *PublicFastTable::getVerticalHeaderCellMergeY()
{
    return &mCellMergeY;
}

QList< QList<int> >       *PublicFastTable::getVerticalHeaderCellMergeParentRow()
{
    return &mCellMergeParentRow;
}

QList< QList<int> >       *PublicFastTable::getVerticalHeaderCellMergeParentColumn()
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

qint16 PublicCustomFastTable::getHorizontalHeaderRowCount()
{
    return mHorizontalHeaderRowCount;
}

qint16 PublicCustomFastTable::getVerticalHeaderColumnCount()
{
    return mVerticalHeaderColumnCount;
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

QBrush PublicCustomFastTable::getHorizontalHeaderDefaultBackgroundBrush()
{
    return mHorizontalHeaderDefaultBackgroundBrush;
}

QColor PublicCustomFastTable::getHorizontalHeaderDefaultForegroundColor()
{
    return mHorizontalHeaderDefaultForegroundColor;
}

QColor PublicCustomFastTable::getHorizontalHeaderGridColor()
{
    return mHorizontalHeaderGridColor;
}

QBrush PublicCustomFastTable::getVerticalHeaderDefaultBackgroundBrush()
{
    return mVerticalHeaderDefaultBackgroundBrush;
}

QColor PublicCustomFastTable::getVerticalHeaderDefaultForegroundColor()
{
    return mVerticalHeaderDefaultForegroundColor;
}

QColor PublicCustomFastTable::getVerticalHeaderGridColor()
{
    return mVerticalHeaderGridColor;
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

int PublicCustomFastTable::getVerticalHeaderTotalWidth()
{
    return mVerticalHeaderTotalWidth;
}

int PublicCustomFastTable::getHorizontalHeaderTotalHeight()
{
    return mHorizontalHeaderTotalHeight;
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

int PublicCustomFastTable::getHorizontalHeaderVisibleLeft()
{
    return mHorizontalHeaderVisibleLeft;
}

int PublicCustomFastTable::getHorizontalHeaderVisibleRight()
{
    return mHorizontalHeaderVisibleRight;
}

int PublicCustomFastTable::getHorizontalHeaderVisibleTop()
{
    return mHorizontalHeaderVisibleTop;
}

int PublicCustomFastTable::getHorizontalHeaderVisibleBottom()
{
    return mHorizontalHeaderVisibleBottom;
}

int PublicCustomFastTable::getVerticalHeaderVisibleLeft()
{
    return mVerticalHeaderVisibleLeft;
}

int PublicCustomFastTable::getVerticalHeaderVisibleRight()
{
    return mVerticalHeaderVisibleRight;
}

int PublicCustomFastTable::getVerticalHeaderVisibleTop()
{
    return mVerticalHeaderVisibleTop;
}

int PublicCustomFastTable::getVerticalHeaderVisibleBottom()
{
    return mVerticalHeaderVisibleBottom;
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

QList< QStringList > *PublicCustomFastTable::getHorizontalHeaderData()
{
    return &mHorizontalHeaderData;
}

QList< quint16 >     *PublicCustomFastTable::getHorizontalHeaderRowHeights()
{
    return &mHorizontalHeaderRowHeights;
}

QList< quint16 >     *PublicCustomFastTable::getHorizontalHeaderColumnWidths()
{
    return &mHorizontalHeaderColumnWidths;
}

QList< int >         *PublicCustomFastTable::getHorizontalHeaderOffsetX()
{
    return &mHorizontalHeaderOffsetX;
}

QList< int >         *PublicCustomFastTable::getHorizontalHeaderOffsetY()
{
    return &mHorizontalHeaderOffsetY;
}

QList< QStringList > *PublicCustomFastTable::getVerticalHeaderData()
{
    return &mVerticalHeaderData;
}

QList< quint16 >     *PublicCustomFastTable::getVerticalHeaderRowHeights()
{
    return &mVerticalHeaderRowHeights;
}

QList< quint16 >     *PublicCustomFastTable::getVerticalHeaderColumnWidths()
{
    return &mVerticalHeaderColumnWidths;
}

QList< int >         *PublicCustomFastTable::getVerticalHeaderOffsetX()
{
    return &mVerticalHeaderOffsetX;
}

QList< int >         *PublicCustomFastTable::getVerticalHeaderOffsetY()
{
    return &mVerticalHeaderOffsetY;
}

QList< QList<bool> > *PublicCustomFastTable::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPoint >      *PublicCustomFastTable::getCurSelection()
{
    return &mCurSelection;
}

QList< bool >        *PublicCustomFastTable::getHorizontalHeaderSelectedColumns()
{
    return &mHorizontalHeaderSelectedColumns;
}

QList< bool >        *PublicCustomFastTable::getVerticalHeaderSelectedRows()
{
    return &mVerticalHeaderSelectedRows;
}
