#include "fasttabletest.h"

FastTableTest::FastTableTest(QWidget *parent) :
    FastTableWidget(parent)
{
}

int FastTableTest::getRowCount()
{
    return mRowCount;
}

int FastTableTest::getColumnCount()
{
    return mColumnCount;
}

quint16 FastTableTest::getDefaultHeight()
{
    return mDefaultHeight;
}

quint16 FastTableTest::getDefaultWidth()
{
    return mDefaultWidth;
}

int     FastTableTest::getTotalHeight()
{
    return mTotalHeight;
}

int     FastTableTest::getTotalWidth()
{
    return mTotalWidth;
}

QBrush FastTableTest::getDefaultBackgroundBrush()
{
    return mDefaultBackgroundBrush;
}

QColor FastTableTest::getDefaultForegroundColor()
{
    return mDefaultForegroundColor;
}

QColor FastTableTest::getGridColor()
{
    return mGridColor;
}

QBrush FastTableTest::getSelectionBrush()
{
    return mSelectionBrush;
}

QList< QStringList >      *FastTableTest::getData()
{
    return &mData;
}

QList< quint16 >          *FastTableTest::getRowHeights()
{
    return &mRowHeights;
}

QList< quint16 >          *FastTableTest::getColumnWidths()
{
    return &mColumnWidths;
}

QList< int >              *FastTableTest::getOffsetX()
{
    return &mOffsetX;
}

QList< int >              *FastTableTest::getOffsetY()
{
    return &mOffsetY;
}

QList< QList<bool> >      *FastTableTest::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPoint >           *FastTableTest::getCurSelection()
{
    return &mCurSelection;
}

QList< QList<QBrush *> >  *FastTableTest::getBackgroundBrushes()
{
    return &mBackgroundBrushes;
}

QList< QList<QColor *> >  *FastTableTest::getForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *FastTableTest::getCellFonts()
{
    return &mCellFonts;
}

QList< QList<int> >       *FastTableTest::getCellTextFlags()
{
    return &mCellTextFlags;
}

QList< QList<quint16> >       *FastTableTest::getCellMergeX()
{
    return &mCellMergeX;
}

QList< QList<quint16> >       *FastTableTest::getCellMergeY()
{
    return &mCellMergeY;
}

QList< QList<int> >       *FastTableTest::getCellMergeParentRow()
{
    return &mCellMergeParentRow;
}

QList< QList<int> >       *FastTableTest::getCellMergeParentColumn()
{
    return &mCellMergeParentColumn;
}

bool FastTableTest::getStartSelection()
{
    return mStartSelection;
}
