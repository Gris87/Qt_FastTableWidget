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

QColor FastTableTest::getDefaultBackgroundColor()
{
    return mDefaultBackgroundColor;
}

QColor FastTableTest::getDefaultForegroundColor()
{
    return mDefaultForegroundColor;
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

QList< QList<bool> >      *FastTableTest::getSelectedCells()
{
    return &mSelectedCells;
}

QList< QPair<int, int> >  *FastTableTest::getCurSelection()
{
    return &mCurSelection;
}

QList< QList<QColor *> >  *FastTableTest::getBackgroundColors()
{
    return &mBackgroundColors;
}

QList< QList<QColor *> >  *FastTableTest::getForegroundColors()
{
    return &mForegroundColors;
}

QList< QList<QFont *> >   *FastTableTest::getCellFonts()
{
    return &mCellFonts;
}

bool FastTableTest::getStartSelection()
{
    return mStartSelection;
}
