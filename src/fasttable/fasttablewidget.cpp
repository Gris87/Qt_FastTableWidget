#include "fasttablewidget.h"

FastTableWidget::FastTableWidget(QWidget *parent) :
    QAbstractScrollArea(parent)
{
    mRowCount=0;
    mColumnCount=0;

    mDefaultHeight=30;
    mDefaultWidth=100;
    mTotalHeight=0;
    mTotalWidth=0;

    mDefaultBackgroundColor.setRgb(255, 255, 255);
    mDefaultForegroundColor.setRgb(0, 0, 0);
    mGridColor.setRgb(0, 0, 0);
    mSelectionColor.setRgb(0, 0, 255);

    mVisibleLeft=-1;
    mVisibleRight=-1;
    mVisibleTop=-1;
    mVisibleBottom=-1;

    mStartSelection=false;

    horizontalScrollBar()->setSingleStep(100);
    verticalScrollBar()->setSingleStep(100);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollBarValueChanged(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(verticalScrollBarValueChanged(int)));
}

FastTableWidget::~FastTableWidget()
{
    clearTable();
}

void FastTableWidget::clearTable()
{
    resetBackgroundColors();
    resetForegroundColors();
    resetFonts();

    mRowCount=0;
    mColumnCount=0;

    mTotalHeight=0;
    mTotalWidth=0;

    mVisibleLeft=-1;
    mVisibleRight=-1;
    mVisibleTop=-1;
    mVisibleBottom=-1;

    mRowHeights.clear();
    mColumnWidths.clear();
    mOffsetX.clear();
    mOffsetY.clear();
    mData.clear();
    mBackgroundColors.clear();
    mBackgroundColors.clear();
    mCellFonts.clear();
    mCellTextFlags.clear();
    mSelectedCells.clear();
    mCurSelection.clear();

    mStartSelection=false;
}

void FastTableWidget::resetBackgroundColors()
{
    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            if (mBackgroundColors.at(i).at(j))
            {
                delete mBackgroundColors.at(i).at(j);
                mBackgroundColors[i][j]=0;
            }
        }
    }
}

void FastTableWidget::resetForegroundColors()
{
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
}

void FastTableWidget::resetFonts()
{
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
}

void FastTableWidget::resetTextFlags()
{
    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            mCellTextFlags[i][j]=Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;
        }
    }
}

void FastTableWidget::resetBackgroundColor(const int row, const int column)
{
    if (mBackgroundColors.at(row).at(column))
    {
        delete mBackgroundColors.at(row).at(column);
        mBackgroundColors[row][column]=0;
    }
}

void FastTableWidget::resetForegroundColor(const int row, const int column)
{
    if (mForegroundColors.at(row).at(column))
    {
        delete mForegroundColors.at(row).at(column);
        mForegroundColors[row][column]=0;
    }
}

void FastTableWidget::resetFont(const int row, const int column)
{
    if (mCellFonts.at(row).at(column))
    {
        delete mCellFonts.at(row).at(column);
        mCellFonts[row][column]=0;
    }
}

void FastTableWidget::resetTextFlag(const int row, const int column)
{
    mCellTextFlags[row][column]=Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;
}

void FastTableWidget::selectRow(const int row)
{
    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, true);
    }
}

void FastTableWidget::unselectRow(const int row)
{
    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, false);
    }
}

void FastTableWidget::selectColumn(const int column)
{
    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, true);
    }
}

void FastTableWidget::unselectColumn(const int column)
{
    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, false);
    }
}

void FastTableWidget::selectAll()
{
    mCurSelection.clear();

    QPoint aCellPos;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            aCellPos.setX(j);
            aCellPos.setY(i);

            mCurSelection.append(aCellPos);

            mSelectedCells[i][j]=true;
        }
    }
}

void FastTableWidget::unselectAll()
{
    for (int i=0; i<mCurSelection.length(); ++i)
    {
        mSelectedCells[mCurSelection.at(i).y()][mCurSelection.at(i).x()]=false;
    }

    mCurSelection.clear();
}

void FastTableWidget::mousePressEvent(QMouseEvent *event)
{
    QAbstractScrollArea::mousePressEvent(event);
}

void FastTableWidget::resizeEvent(QResizeEvent *event)
{
    updateBarsRanges();
    updateVisibleRange();

    QAbstractScrollArea::resizeEvent(event);
}

void FastTableWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
    {
        for (int j=mVisibleLeft; j<=mVisibleRight; ++j)
        {
            paintCell(painter, offsetX+mOffsetX.at(j), offsetY+mOffsetY.at(i), i, j);
        }
    }
}

void FastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int row, const int column)
{
    QColor *aBackgroundColor;

    if (mSelectedCells.at(row).at(column))
    {
        aBackgroundColor=&mSelectionColor;
    }
    else
    {
        aBackgroundColor=mBackgroundColors.at(row).at(column);

        if (aBackgroundColor==0)
        {
            aBackgroundColor=&mDefaultBackgroundColor;
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

    painter.fillRect(x, y, mColumnWidths.at(column), mRowHeights.at(row), *aBackgroundColor);
    painter.drawRect(x, y, mColumnWidths.at(column), mRowHeights.at(row));

    painter.setPen(QPen(*aForegroundColor));
    painter.drawText(x+4, y+4, mColumnWidths.at(column)-8, mRowHeights.at(row)-8, mCellTextFlags.at(row).at(column), mData.at(row).at(column));
}

void FastTableWidget::horizontalScrollBarValueChanged(int value)
{
    updateVisibleRange();
}

void FastTableWidget::verticalScrollBarValueChanged(int value)
{
    updateVisibleRange();
}

void FastTableWidget::updateBarsRanges()
{
    QSize areaSize = viewport()->size();

    horizontalScrollBar()->setPageStep(mTotalWidth);
    verticalScrollBar()->setPageStep(mTotalHeight);

    horizontalScrollBar()->setRange(0, mTotalWidth - areaSize.width());
    verticalScrollBar()->setRange(0, mTotalHeight - areaSize.height());
}

void FastTableWidget::updateVisibleRange()
{
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
            mVisibleLeft==-1
            ||
            mVisibleRight==-1
            ||
            mVisibleTop==-1
            ||
            mVisibleBottom==-1
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
    }
}

int FastTableWidget::rowCount()
{
    return mRowCount;
}

void FastTableWidget::setRowCount(int count)
{
    if (count<0)
    {
        count=0;
    }

    if (mRowCount!=count)
    {
        while (mRowCount<count)
        {
            QStringList aNewRow;
            QList<QColor *> aNewRowColor;
            QList<QFont *> aNewRowFont;
            QList<bool> aNewRowbool;
            QList<int> aNewRowint;

            mTotalHeight+=mDefaultHeight;

            mData.append(aNewRow);
            mRowHeights.append(mDefaultHeight);
            mOffsetY.append(mRowCount==0? 0 : (mOffsetY.at(mRowCount-1)+mRowHeights.at(mRowCount-1)));
            mBackgroundColors.append(aNewRowColor);
            mForegroundColors.append(aNewRowColor);
            mCellFonts.append(aNewRowFont);
            mCellTextFlags.append(aNewRowint);
            mSelectedCells.append(aNewRowbool);

            for (int i=0; i<mColumnCount; ++i)
            {
                mData[mRowCount].append("");
                mBackgroundColors[mRowCount].append(0);
                mForegroundColors[mRowCount].append(0);
                mCellFonts[mRowCount].append(0);
                mCellTextFlags[mRowCount].append(Qt::AlignTop | Qt::AlignVCenter | Qt::TextWordWrap);
                mSelectedCells[mRowCount].append(false);
            }

            mRowCount++;
        }

        while (mRowCount>count)
        {
            mRowCount--;

            mTotalHeight-=mRowHeights.at(mRowCount);

            for (int i=0; i<mColumnCount; ++i)
            {
                if (mBackgroundColors.at(mRowCount).at(i))
                {
                    delete mBackgroundColors.at(mRowCount).at(i);
                }

                if (mForegroundColors.at(mRowCount).at(i))
                {
                    delete mForegroundColors.at(mRowCount).at(i);
                }

                if (mCellFonts.at(mRowCount).at(i))
                {
                    delete mCellFonts.at(mRowCount).at(i);
                }
            }

            mData.removeLast();
            mRowHeights.removeLast();
            mOffsetY.removeLast();
            mBackgroundColors.removeLast();
            mForegroundColors.removeLast();
            mCellFonts.removeLast();
            mCellTextFlags.removeLast();

            for (int i=0; i<mColumnCount; ++i)
            {
                if (mSelectedCells.last().at(i))
                {
                    for (int j=0; j<mCurSelection.length(); ++j)
                    {
                        if (mCurSelection.at(j).y()==mRowCount && mCurSelection.at(j).x()==i)
                        {
                            mCurSelection.removeAt(j);
                            break;
                        }
                    }
                }
            }

            mSelectedCells.removeLast();
        }

        updateBarsRanges();
        updateVisibleRange();
    }
}

int FastTableWidget::columnCount()
{
    return mColumnCount;
}

void FastTableWidget::setColumnCount(int count)
{
    if (count<0)
    {
        count=0;
    }

    if (mColumnCount!=count)
    {
        if (mColumnCount<count)
        {
            for (int i=mColumnCount; i<count; ++i)
            {
                mColumnWidths.append(mDefaultWidth);
                mTotalWidth+=mDefaultWidth;

                mOffsetX.append(i==0? 0 : (mOffsetX.at(i-1)+mColumnWidths.at(i-1)));
            }

            for (int i=0; i<mData.length(); ++i)
            {
                for (int j=mColumnCount; j<count; ++j)
                {
                    mData[i].append("");
                    mBackgroundColors[i].append(0);
                    mForegroundColors[i].append(0);
                    mCellFonts[i].append(0);
                    mCellTextFlags[i].append(Qt::AlignTop | Qt::AlignVCenter | Qt::TextWordWrap);
                    mSelectedCells[i].append(false);
                }
            }
        }
        else
        {
            for (int i=mColumnCount-1; i>=count; --i)
            {
                mTotalWidth-=mColumnWidths.at(i);
                mColumnWidths.removeLast();
                mOffsetX.removeLast();
            }

            for (int i=0; i<mData.length(); ++i)
            {
                for (int j=mColumnCount-1; j>=count; --j)
                {
                    if (mBackgroundColors.at(i).at(j))
                    {
                        delete mBackgroundColors.at(i).at(j);
                    }

                    if (mForegroundColors.at(i).at(j))
                    {
                        delete mForegroundColors.at(i).at(j);
                    }

                    if (mCellFonts.at(i).at(j))
                    {
                        delete mCellFonts.at(i).at(j);
                    }

                    mData[i].removeLast();
                    mBackgroundColors[i].removeLast();
                    mForegroundColors[i].removeLast();
                    mCellFonts[i].removeLast();
                    mCellTextFlags[i].removeLast();

                    if (mSelectedCells.at(i).last())
                    {
                        for (int k=0; k<mCurSelection.length(); ++k)
                        {
                            if (mCurSelection.at(k).y()==i && mCurSelection.at(k).x()==j)
                            {
                                mCurSelection.removeAt(k);
                                break;
                            }
                        }
                    }

                    mSelectedCells[i].removeLast();
                }
            }
        }

        mColumnCount=count;

        updateBarsRanges();
        updateVisibleRange();
    }
}

QColor FastTableWidget::defaultBackgroundColor()
{
    return mDefaultBackgroundColor;
}

void FastTableWidget::setDefaultBackgroundColor(QColor color)
{
    mDefaultBackgroundColor=color;
}

QColor FastTableWidget::defaultForegroundColor()
{
    return mDefaultForegroundColor;
}

void FastTableWidget::setDefaultForegroundColor(QColor color)
{
    mDefaultForegroundColor=color;
}

QColor FastTableWidget::gridColor()
{
    return mGridColor;
}

void FastTableWidget::setGridColor(QColor color)
{
    mGridColor=color;
}

QColor FastTableWidget::selectionColor()
{
    return mSelectionColor;
}

void FastTableWidget::setSelectionColor(QColor color)
{
    mSelectionColor=color;
}

quint16 FastTableWidget::defaultHeight()
{
    return mDefaultHeight;
}

void FastTableWidget::setDefaultHeight(quint16 height)
{
    mDefaultHeight=height;
}

quint16 FastTableWidget::defaultWidth()
{
    return mDefaultWidth;
}

void FastTableWidget::setDefaultWidth(quint16 width)
{
    mDefaultWidth=width;
}

int FastTableWidget::totalHeight()
{
    return mTotalHeight;
}

int FastTableWidget::totalWidth()
{
    return mTotalWidth;
}

QRect FastTableWidget::visibleRange()
{
    QRect aRect;
    aRect.setCoords(mVisibleLeft, mVisibleTop, mVisibleRight, mVisibleBottom);
    return aRect;
}

QString FastTableWidget::text(const int row, const int column)
{
    return mData.at(row).at(column);
}

void FastTableWidget::setText(const int row, const int column, const QString text)
{
    mData[row][column]=text;
}

quint16 FastTableWidget::rowHeight(const int row)
{
    return mRowHeights.at(row);
}

void FastTableWidget::setRowHeight(const int row, const quint16 height)
{
    if (mRowHeights.at(row)!=height)
    {
        int aDiff=height-mRowHeights.at(row);

        mTotalHeight+=aDiff;
        mRowHeights[row]=height;

        for (int i=row+1; i<mRowCount; ++i)
        {
            mOffsetY[i]=mOffsetY.at(i)+aDiff;
        }

        updateBarsRanges();
        updateVisibleRange();
    }
}

quint16 FastTableWidget::columnWidth(const int column)
{
    return mColumnWidths.at(column);
}

void FastTableWidget::setColumnWidth(const int column, const quint16 width)
{
    if (mColumnWidths.at(column)!=width)
    {
        int aDiff=width-mColumnWidths.at(column);

        mTotalWidth+=aDiff;
        mColumnWidths[column]=width;

        for (int i=column+1; i<mColumnCount; ++i)
        {
            mOffsetX[i]=mOffsetX.at(i)+aDiff;
        }

        updateBarsRanges();
        updateVisibleRange();
    }
}

QColor FastTableWidget::backgroundColor(const int row, const int column)
{
    if (mBackgroundColors.at(row).at(column))
    {
        return *mBackgroundColors.at(row).at(column);
    }

    return mDefaultBackgroundColor;
}

void FastTableWidget::setBackgroundColor(const int row, const int column, const QColor color)
{
    if (mBackgroundColors.at(row).at(column))
    {
        *mBackgroundColors[row][column]=color;
    }
    else
    {
        mBackgroundColors[row][column]=new QColor(color);
    }
}

QColor FastTableWidget::foregroundColor(const int row, const int column)
{
    if (mForegroundColors.at(row).at(column))
    {
        return *mForegroundColors.at(row).at(column);
    }

    return mDefaultForegroundColor;
}

void FastTableWidget::setForegroundColor(const int row, const int column, const QColor color)
{
    if (mForegroundColors.at(row).at(column))
    {
        *mForegroundColors[row][column]=color;
    }
    else
    {
        mForegroundColors[row][column]=new QColor(color);
    }
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
    if (mCellFonts.at(row).at(column))
    {
        *mCellFonts[row][column]=font;
    }
    else
    {
        mCellFonts[row][column]=new QFont(font);
    }
}

int FastTableWidget::cellTextFlags(const int row, const int column)
{
    return mCellTextFlags.at(row).at(column);
}

void FastTableWidget::setCellTextFlags(const int row, const int column, const int flags)
{
    mCellTextFlags[row][column]=flags;
}

bool FastTableWidget::cellSelected(const int row, const int column)
{
    return mSelectedCells.at(row).at(column);
}

void FastTableWidget::setCellSelected(const int row, const int column, const bool selected)
{
    if (mSelectedCells.at(row).at(column)!=selected)
    {
        mSelectedCells[row][column]=selected;

        if (selected)
        {
            mCurSelection.append(QPoint(column, row));
        }
        else
        {
            for (int i=0; i<mCurSelection.length(); ++i)
            {
                if (mCurSelection.at(i).y()==row && mCurSelection.at(i).x()==column)
                {
                    mCurSelection.removeAt(i);
                    break;
                }
            }
        }
    }
}
