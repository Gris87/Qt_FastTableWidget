#include "fasttablewidget.h"

FastTableWidget::FastTableWidget(QWidget *parent) :
    CustomFastTableWidget(parent)
{
    START_PROFILE;
    END_PROFILE("FastTableWidget::FastTableWidget(QWidget *parent)");
}

FastTableWidget::~FastTableWidget()
{
    START_PROFILE;
    END_PROFILE("FastTableWidget::~FastTableWidget()");
}

void FastTableWidget::paintEvent(QPaintEvent *event)
{
    START_FREQUENT_PROFILE;

    QPainter painter(viewport());

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    if (mVisibleTop<0 || mVisibleLeft<0)
    {
        return;
    }

    for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
    {
        for (int j=mVisibleLeft; j<=mVisibleRight; ++j)
        {
            if (mCellMergeParentRow.at(i).at(j)>=0 && mCellMergeParentColumn.at(i).at(j)>=0)
            {
                int spanX=mCellMergeX.at(i).at(j);
                int spanY=mCellMergeY.at(i).at(j);

                if (spanX>1 || spanY>1)
                {
                    int aWidth=0;
                    int aHeight=0;

                    for (int g=0; g<spanX; g++)
                    {
                        aWidth+=mColumnWidths.at(j+g);
                    }

                    for (int g=0; g<spanY; g++)
                    {
                        aHeight+=mRowHeights.at(i+g);
                    }

                    paintCell(painter, offsetX+mOffsetX.at(j), offsetY+mOffsetY.at(i), aWidth, aHeight, i, j, DrawCell);
                }
            }
            else
            {
                paintCell(painter, offsetX+mOffsetX.at(j), offsetY+mOffsetY.at(i), mColumnWidths.at(j), mRowHeights.at(i), i, j, DrawCell);
            }
        }
    }

    END_FREQUENT_PROFILE("void FastTableWidget::paintEvent(QPaintEvent *event)");
}

void FastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent)
{
    START_FREQUENT_PROFILE;

    QBrush *aBackgroundBrush;

    if (mSelectedCells.at(row).at(column))
    {
        aBackgroundBrush=&mSelectionBrush;
    }
    else
    {
        aBackgroundBrush=mBackgroundBrushes.at(row).at(column);

        if (aBackgroundBrush==0)
        {
            aBackgroundBrush=&mDefaultBackgroundBrush;
        }
    }

    QColor *aForegroundColor;

    aForegroundColor=mForegroundColors.at(row).at(column);

    if (aForegroundColor==0)
    {
        aForegroundColor=&mDefaultForegroundColor;
    }

    QFont *aFont=mCellFonts.at(row).at(column);

    if (aFont)
    {
        painter.setFont(*aFont);
    }
    else
    {
        painter.setFont(font());
    }

    painter.setPen(QPen(mGridColor));

    painter.fillRect(x, y, width, height, *aBackgroundBrush);
    painter.drawRect(x, y, width, height);

    painter.setPen(QPen(*aForegroundColor));
    painter.drawText(x+4, y+4, width-8, height-8, mCellTextFlags.at(row).at(column), mData.at(row).at(column));

    END_FREQUENT_PROFILE("void FastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int row, const int column)");
}

void FastTableWidget::updateVisibleRange()
{
    START_PROFILE;

    if (mRowCount==0 || mColumnCount==0)
    {
        mVisibleLeft=-1;
        mVisibleRight=-1;
        mVisibleTop=-1;
        mVisibleBottom=-1;
    }
    else
    {
        if (
            mVisibleLeft<0
            ||
            mVisibleRight<0
            ||
            mVisibleTop<0
            ||
            mVisibleBottom<0
           )
        {
            mVisibleLeft=0;
            mVisibleRight=0;
            mVisibleTop=0;
            mVisibleBottom=0;
        }
        else
        {
            if (mVisibleLeft>=mColumnCount)
            {
                mVisibleLeft=mColumnCount-1;
            }
            if (mVisibleRight>=mColumnCount)
            {
                mVisibleRight=mColumnCount-1;
            }
            if (mVisibleTop>=mRowCount)
            {
                mVisibleTop=mRowCount-1;
            }
            if (mVisibleBottom>=mRowCount)
            {
                mVisibleBottom=mRowCount-1;
            }
        }

        int minX=horizontalScrollBar()->value();
        int minY=verticalScrollBar()->value();
        int maxX=minX+viewport()->width();
        int maxY=minY+viewport()->height();

        while (mVisibleLeft<mColumnCount-1 && mOffsetX.at(mVisibleLeft)<minX && mOffsetX.at(mVisibleLeft)+mColumnWidths.at(mVisibleLeft)<minX)
        {
            mVisibleLeft++;
        }

        while (mVisibleLeft>0 && mOffsetX.at(mVisibleLeft)>minX && mOffsetX.at(mVisibleLeft)+mColumnWidths.at(mVisibleLeft)>minX)
        {
            mVisibleLeft--;
        }

        while (mVisibleRight<mColumnCount-1 && mOffsetX.at(mVisibleRight)<maxX && mOffsetX.at(mVisibleRight)+mColumnWidths.at(mVisibleRight)<maxX)
        {
            mVisibleRight++;
        }

        while (mVisibleRight>0 && mOffsetX.at(mVisibleRight)>maxX && mOffsetX.at(mVisibleRight)+mColumnWidths.at(mVisibleRight)>maxX)
        {
            mVisibleRight--;
        }

        while (mVisibleTop<mRowCount-1 && mOffsetY.at(mVisibleTop)<minY && mOffsetY.at(mVisibleTop)+mRowHeights.at(mVisibleTop)<minY)
        {
            mVisibleTop++;
        }

        while (mVisibleTop>0 && mOffsetY.at(mVisibleTop)>minY && mOffsetY.at(mVisibleTop)+mRowHeights.at(mVisibleTop)>minY)
        {
            mVisibleTop--;
        }

        while (mVisibleBottom<mRowCount-1 && mOffsetY.at(mVisibleBottom)<maxY && mOffsetY.at(mVisibleBottom)+mRowHeights.at(mVisibleBottom)<maxY)
        {
            mVisibleBottom++;
        }

        while (mVisibleBottom>0 && mOffsetY.at(mVisibleBottom)>maxY && mOffsetY.at(mVisibleBottom)+mRowHeights.at(mVisibleBottom)>maxY)
        {
            mVisibleBottom--;
        }

        int originalLeft=mVisibleLeft;
        int originalTop=mVisibleTop;

        for (int i=0; i<mRowCount; i++)
        {

            int parentColumn=mCellMergeParentColumn.at(i).at(originalLeft);

            if (parentColumn>=0 &&parentColumn<mVisibleLeft)
            {
                mVisibleLeft=parentColumn;
            }
        }

        for (int i=0; i<mColumnCount; i++)
        {
            int parentRow=mCellMergeParentRow.at(originalTop).at(i);

            if (parentRow>=0 && parentRow<mVisibleTop)
            {
                mVisibleTop=parentRow;
            }
        }
    }

    END_PROFILE("void FastTableWidget::updateVisibleRange()");
}

void FastTableWidget::clearTable()
{
    START_PROFILE;

    resetBackgroundBrushes();
    resetForegroundColors();
    resetFonts();

    mBackgroundBrushes.clear();
    mForegroundColors.clear();
    mCellFonts.clear();
    mCellTextFlags.clear();
    mCellMergeX.clear();
    mCellMergeY.clear();
    mCellMergeParentRow.clear();
    mCellMergeParentColumn.clear();

    CustomFastTableWidget::clearTable();

    END_PROFILE("void FastTableWidget::clearTable()");
}

void FastTableWidget::resetBackgroundBrushes()
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            if (mBackgroundBrushes.at(i).at(j))
            {
                delete mBackgroundBrushes.at(i).at(j);
                mBackgroundBrushes[i][j]=0;
            }
        }
    }

    END_PROFILE("void FastTableWidget::resetBackgroundBrushes()");
}

void FastTableWidget::resetForegroundColors()
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            if (mForegroundColors.at(i).at(j))
            {
                delete mForegroundColors.at(i).at(j);
                mForegroundColors[i][j]=0;
            }
        }
    }

    END_PROFILE("void FastTableWidget::resetForegroundColors()");
}

void FastTableWidget::resetFonts()
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            if (mCellFonts.at(i).at(j))
            {
                delete mCellFonts.at(i).at(j);
                mCellFonts[i][j]=0;
            }
        }
    }

    END_PROFILE("void FastTableWidget::resetFonts()");
}

void FastTableWidget::resetTextFlags()
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            mCellTextFlags[i][j]=Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;
        }
    }

    END_PROFILE("void FastTableWidget::resetTextFlags()");
}

void FastTableWidget::resetBackgroundBrush(const int row, const int column)
{
    START_PROFILE;

    if (mBackgroundBrushes.at(row).at(column))
    {
        delete mBackgroundBrushes.at(row).at(column);
        mBackgroundBrushes[row][column]=0;
    }

    END_PROFILE("void FastTableWidget::resetBackgroundBrush(const int row, const int column)");
}

void FastTableWidget::resetForegroundColor(const int row, const int column)
{
    START_PROFILE;

    if (mForegroundColors.at(row).at(column))
    {
        delete mForegroundColors.at(row).at(column);
        mForegroundColors[row][column]=0;
    }

    END_PROFILE("void FastTableWidget::resetForegroundColor(const int row, const int column)");
}

void FastTableWidget::resetFont(const int row, const int column)
{
    START_PROFILE;

    if (mCellFonts.at(row).at(column))
    {
        delete mCellFonts.at(row).at(column);
        mCellFonts[row][column]=0;
    }

    END_PROFILE("void FastTableWidget::resetFont(const int row, const int column)");
}

void FastTableWidget::resetTextFlag(const int row, const int column)
{
    START_PROFILE;

    mCellTextFlags[row][column]=Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;

    END_PROFILE("void FastTableWidget::resetTextFlag(const int row, const int column)");
}

void FastTableWidget::insertRow(int row)
{
    START_PROFILE;

    CustomFastTableWidget::insertRow(row);

    QList<QBrush *> aNewRowBrush;
    QList<QColor *> aNewRowColor;
    QList<QFont *> aNewRowFont;
    QList<int> aNewRowint;
    QList<quint16> aNewRowqint16;

    mBackgroundBrushes.insert(row, aNewRowBrush);
    mForegroundColors.insert(row, aNewRowColor);
    mCellFonts.insert(row, aNewRowFont);
    mCellTextFlags.insert(row, aNewRowint);
    mCellMergeX.insert(row, aNewRowqint16);
    mCellMergeY.insert(row, aNewRowqint16);
    mCellMergeParentRow.insert(row, aNewRowint);
    mCellMergeParentColumn.insert(row, aNewRowint);

    for (int i=0; i<mColumnCount; ++i)
    {
        mBackgroundBrushes[row].append(0);
        mForegroundColors[row].append(0);
        mCellFonts[row].append(0);
        mCellTextFlags[row].append(Qt::AlignTop | Qt::AlignVCenter | Qt::TextWordWrap);
        mCellMergeX[row].append(1);
        mCellMergeY[row].append(1);
        mCellMergeParentRow[row].append(-1);
        mCellMergeParentColumn[row].append(-1);
    }

    END_PROFILE("void FastTableWidget::insertRow(int row)");
}

void FastTableWidget::deleteRow(int row)
{
    START_PROFILE;

    for (int i=0; i<mColumnCount; ++i)
    {
        if (mBackgroundBrushes.at(row).at(i))
        {
            delete mBackgroundBrushes.at(row).at(i);
        }

        if (mForegroundColors.at(row).at(i))
        {
            delete mForegroundColors.at(row).at(i);
        }

        if (mCellFonts.at(row).at(i))
        {
            delete mCellFonts.at(row).at(i);
        }
    }

    mBackgroundBrushes.removeAt(row);
    mForegroundColors.removeAt(row);
    mCellFonts.removeAt(row);
    mCellTextFlags.removeAt(row);
    mCellMergeX.removeAt(row);
    mCellMergeY.removeAt(row);
    mCellMergeParentRow.removeAt(row);
    mCellMergeParentColumn.removeAt(row);

    CustomFastTableWidget::deleteRow(row);

    END_PROFILE("void FastTableWidget::deleteRow(int row)");
}

void FastTableWidget::insertColumn(int column)
{
    START_PROFILE;

    CustomFastTableWidget::insertColumn(column);

    for (int i=0; i<mData.length(); ++i)
    {
        mBackgroundBrushes[i].insert(column, 0);
        mForegroundColors[i].insert(column, 0);
        mCellFonts[i].insert(column, 0);
        mCellTextFlags[i].insert(column, Qt::AlignTop | Qt::AlignVCenter | Qt::TextWordWrap);
        mCellMergeX[i].insert(column, 1);
        mCellMergeY[i].insert(column, 1);
        mCellMergeParentRow[i].insert(column, -1);
        mCellMergeParentColumn[i].insert(column, -1);
    }

    END_PROFILE("void FastTableWidget::insertColumn(int column)");
}

void FastTableWidget::deleteColumn(int column)
{
    START_PROFILE;

    for (int i=0; i<mData.length(); ++i)
    {
        if (mBackgroundBrushes.at(i).at(column))
        {
            delete mBackgroundBrushes.at(i).at(column);
        }

        if (mForegroundColors.at(i).at(column))
        {
            delete mForegroundColors.at(i).at(column);
        }

        if (mCellFonts.at(i).at(column))
        {
            delete mCellFonts.at(i).at(column);
        }

        mBackgroundBrushes[i].removeAt(column);
        mForegroundColors[i].removeAt(column);
        mCellFonts[i].removeAt(column);
        mCellTextFlags[i].removeAt(column);
        mCellMergeX[i].removeAt(column);
        mCellMergeY[i].removeAt(column);
        mCellMergeParentRow[i].removeAt(column);
        mCellMergeParentColumn[i].removeAt(column);
    }

    CustomFastTableWidget::deleteColumn(column);

    END_PROFILE("void FastTableWidget::deleteColumn(int column)");
}

QBrush FastTableWidget::backgroundBrush(const int row, const int column)
{
    START_PROFILE;

    QBrush *aBrush=mBackgroundBrushes.at(row).at(column);

    if (aBrush==0)
    {
        aBrush=&mDefaultBackgroundBrush;
    }

    END_PROFILE("QBrush FastTableWidget::backgroundBrush(const int row, const int column)");

    return *aBrush;
}

void FastTableWidget::setBackgroundBrush(const int row, const int column, const QBrush brush)
{
    START_PROFILE;

    if (mBackgroundBrushes.at(row).at(column))
    {
        *mBackgroundBrushes[row][column]=brush;
    }
    else
    {
        mBackgroundBrushes[row][column]=new QBrush(brush);
    }

    END_PROFILE("void FastTableWidget::setBackgroundBrush(const int row, const int column, const QBrush brush)");
}

QColor FastTableWidget::foregroundColor(const int row, const int column)
{
    START_PROFILE;

    QColor *aColor=mForegroundColors.at(row).at(column);

    if (aColor==0)
    {
        aColor=&mDefaultForegroundColor;
    }

    END_PROFILE("QColor FastTableWidget::foregroundColor(const int row, const int column)");

    return *aColor;
}

void FastTableWidget::setForegroundColor(const int row, const int column, const QColor color)
{
    START_PROFILE;

    if (mForegroundColors.at(row).at(column))
    {
        *mForegroundColors[row][column]=color;
    }
    else
    {
        mForegroundColors[row][column]=new QColor(color);
    }

    END_PROFILE("void FastTableWidget::setForegroundColor(const int row, const int column, const QColor color)");
}

QFont FastTableWidget::cellFont(const int row, const int column)
{
    if (mCellFonts.at(row).at(column))
    {
        return *mCellFonts.at(row).at(column);
    }

    return this->font();
}

void FastTableWidget::setCellFont(const int row, const int column, const QFont font)
{
    START_PROFILE;

    if (mCellFonts.at(row).at(column))
    {
        *mCellFonts[row][column]=font;
    }
    else
    {
        mCellFonts[row][column]=new QFont(font);
    }

    END_PROFILE("void FastTableWidget::setCellFont(const int row, const int column, const QFont font)");
}

int FastTableWidget::cellTextFlags(const int row, const int column)
{
    return mCellTextFlags.at(row).at(column);
}

void FastTableWidget::setCellTextFlags(const int row, const int column, const int flags)
{
    START_PROFILE;

    mCellTextFlags[row][column]=flags;

    END_PROFILE("void FastTableWidget::setCellTextFlags(const int row, const int column, const int flags)");
}

void FastTableWidget::clearSpans()
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            mCellMergeX[i][j]=1;
            mCellMergeY[i][j]=1;
            mCellMergeParentRow[i][j]=-1;
            mCellMergeParentColumn[i][j]=-1;
        }
    }

    END_PROFILE("void FastTableWidget::clearSpans()");
}

void FastTableWidget::setSpan(const int row, const int column, quint16 rowSpan, quint16 columnSpan)
{
    START_PROFILE;

    if (row+rowSpan>mRowCount)
    {
        rowSpan=mRowCount-row;
    }

    if (column+columnSpan>mColumnCount)
    {
        columnSpan=mColumnCount-column;
    }

    if (rowSpan<1)
    {
        rowSpan=1;
    }

    if (columnSpan<1)
    {
        columnSpan=1;
    }

    int parentRow;
    int parentColumn;

    for (int i=0; i<rowSpan; i++)
    {
        for (int j=0; j<columnSpan; j++)
        {
            parentRow=mCellMergeParentRow.at(row+i).at(column+j);
            parentColumn=mCellMergeParentColumn.at(row+i).at(column+j);

            if (parentRow>=0 && parentColumn>=0)
            {
                int parentSpanX=mCellMergeX.at(parentRow).at(parentColumn);
                int parentSpanY=mCellMergeY.at(parentRow).at(parentColumn);

                for (int g=0; g<parentSpanY; g++)
                {
                    for (int h=0; h<parentSpanX; h++)
                    {
                        mCellMergeParentRow[parentRow+g][parentColumn+h]=-1;
                        mCellMergeParentColumn[parentRow+g][parentColumn+h]=-1;
                    }
                }

                mCellMergeX[parentRow][parentColumn]=1;
                mCellMergeY[parentRow][parentColumn]=1;
            }

            mCellMergeParentRow[row+i][column+j]=row;
            mCellMergeParentColumn[row+i][column+j]=column;
        }
    }

    mCellMergeX[row][column]=columnSpan;
    mCellMergeY[row][column]=rowSpan;

    if (rowSpan==1 && columnSpan==1)
    {
        mCellMergeParentRow[row][column]=-1;
        mCellMergeParentColumn[row][column]=-1;
    }

    END_PROFILE("void FastTableWidget::setSpan(const int row, const int column, quint16 rowSpan, quint16 columnSpan)");
}

quint16 FastTableWidget::rowSpan(const int row, const int column)
{
    START_PROFILE;

    return mCellMergeY.at(row).at(column);

    END_PROFILE("quint16 FastTableWidget::rowSpan(const int row, const int column)");
}

quint16 FastTableWidget::columnSpan(const int row, const int column)
{
    START_PROFILE;

    return mCellMergeX.at(row).at(column);

    END_PROFILE("quint16 FastTableWidget::columnSpan(const int row, const int column)");
}

QPoint FastTableWidget::spanParent(const int row, const int column)
{
    START_PROFILE;

    return QPoint(mCellMergeParentColumn.at(row).at(column), mCellMergeParentRow.at(row).at(column));

    END_PROFILE("QPoint FastTableWidget::spanParent(const int row, const int column)");
}
