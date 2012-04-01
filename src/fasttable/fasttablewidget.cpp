#include "fasttablewidget.h"

FastTableWidget::FastTableWidget(QWidget *parent) :
    QAbstractScrollArea(parent)
{
    START_PROFILE

    mRowCount=0;
    mColumnCount=0;

    mDefaultHeight=30;
    mDefaultWidth=100;
    mTotalHeight=0;
    mTotalWidth=0;

    mDefaultBackgroundBrush.setColor(QColor(255, 255, 255));
    mDefaultForegroundColor.setRgb(0, 0, 0);
    mGridColor.setRgb(0, 0, 0);
    mSelectionBrush.setColor(QColor(0, 0, 255));

    mVisibleLeft=-1;
    mVisibleRight=-1;
    mVisibleTop=-1;
    mVisibleBottom=-1;

    mStartSelection=false;

    horizontalScrollBar()->setSingleStep(100);
    verticalScrollBar()->setSingleStep(100);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollBarValueChanged(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(verticalScrollBarValueChanged(int)));

    END_PROFILE("FastTableWidget::FastTableWidget(QWidget *parent)")
}

FastTableWidget::~FastTableWidget()
{
    START_PROFILE

    clearTable();

    END_PROFILE("FastTableWidget::~FastTableWidget()")
}

void FastTableWidget::clearTable()
{
    START_PROFILE

    resetBackgroundBrushes();
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
    mBackgroundBrushes.clear();
    mForegroundColors.clear();
    mCellFonts.clear();
    mCellTextFlags.clear();
    mSelectedCells.clear();
    mCurSelection.clear();

    mStartSelection=false;

    END_PROFILE("void FastTableWidget::clearTable()")
}

void FastTableWidget::resetBackgroundBrushes()
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::resetBackgroundBrushes()")
}

void FastTableWidget::resetForegroundColors()
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::resetForegroundColors()")
}

void FastTableWidget::resetFonts()
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::resetFonts()")
}

void FastTableWidget::resetTextFlags()
{
    START_PROFILE

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            mCellTextFlags[i][j]=Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;
        }
    }

    END_PROFILE("void FastTableWidget::resetTextFlags()")
}

void FastTableWidget::resetBackgroundBrush(const int row, const int column)
{
    START_PROFILE

    if (mBackgroundBrushes.at(row).at(column))
    {
        delete mBackgroundBrushes.at(row).at(column);
        mBackgroundBrushes[row][column]=0;
    }

    END_PROFILE("void FastTableWidget::resetBackgroundBrush(const int row, const int column)")
}

void FastTableWidget::resetForegroundColor(const int row, const int column)
{
    START_PROFILE

    if (mForegroundColors.at(row).at(column))
    {
        delete mForegroundColors.at(row).at(column);
        mForegroundColors[row][column]=0;
    }

    END_PROFILE("void FastTableWidget::resetForegroundColor(const int row, const int column)")
}

void FastTableWidget::resetFont(const int row, const int column)
{
    START_PROFILE

    if (mCellFonts.at(row).at(column))
    {
        delete mCellFonts.at(row).at(column);
        mCellFonts[row][column]=0;
    }

    END_PROFILE("void FastTableWidget::resetFont(const int row, const int column)")
}

void FastTableWidget::resetTextFlag(const int row, const int column)
{
    START_PROFILE

    mCellTextFlags[row][column]=Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap;

    END_PROFILE("void FastTableWidget::resetTextFlag(const int row, const int column)")
}

void FastTableWidget::selectRow(const int row)
{
    START_PROFILE

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, true);
    }

    END_PROFILE("void FastTableWidget::selectRow(const int row)")
}

void FastTableWidget::unselectRow(const int row)
{
    START_PROFILE

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, false);
    }

    END_PROFILE("void FastTableWidget::unselectRow(const int row)")
}

void FastTableWidget::selectColumn(const int column)
{
    START_PROFILE

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, true);
    }

    END_PROFILE("void FastTableWidget::selectColumn(const int column)")
}

void FastTableWidget::unselectColumn(const int column)
{
    START_PROFILE

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, false);
    }

    END_PROFILE("void FastTableWidget::unselectColumn(const int column)")
}

void FastTableWidget::selectAll()
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::selectAll()")
}

void FastTableWidget::unselectAll()
{
    START_PROFILE

    for (int i=0; i<mCurSelection.length(); ++i)
    {
        mSelectedCells[mCurSelection.at(i).y()][mCurSelection.at(i).x()]=false;
    }

    mCurSelection.clear();

    END_PROFILE("void FastTableWidget::unselectAll()")
}

void FastTableWidget::mousePressEvent(QMouseEvent *event)
{
    START_PROFILE

    QAbstractScrollArea::mousePressEvent(event);

    END_PROFILE("void FastTableWidget::mousePressEvent(QMouseEvent *event)")
}

void FastTableWidget::resizeEvent(QResizeEvent *event)
{
    START_PROFILE

    updateBarsRanges();
    updateVisibleRange();

    QAbstractScrollArea::resizeEvent(event);

    END_PROFILE("void FastTableWidget::resizeEvent(QResizeEvent *event)")
}

void FastTableWidget::paintEvent(QPaintEvent *event)
{
    START_FREQUENT_PROFILE

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

    END_FREQUENT_PROFILE("void FastTableWidget::paintEvent(QPaintEvent *event)")
}

void FastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int row, const int column)
{
    START_FREQUENT_PROFILE

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

    painter.fillRect(x, y, mColumnWidths.at(column), mRowHeights.at(row), *aBackgroundBrush);
    painter.drawRect(x, y, mColumnWidths.at(column), mRowHeights.at(row));

    painter.setPen(QPen(*aForegroundColor));
    painter.drawText(x+4, y+4, mColumnWidths.at(column)-8, mRowHeights.at(row)-8, mCellTextFlags.at(row).at(column), mData.at(row).at(column));

    END_FREQUENT_PROFILE("void FastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int row, const int column)")
}

void FastTableWidget::horizontalScrollBarValueChanged(int value)
{
    START_PROFILE

    updateVisibleRange();

    END_PROFILE("void FastTableWidget::horizontalScrollBarValueChanged(int value)")
}

void FastTableWidget::verticalScrollBarValueChanged(int value)
{
    START_PROFILE

    updateVisibleRange();

    END_PROFILE("void FastTableWidget::verticalScrollBarValueChanged(int value)")
}

void FastTableWidget::updateBarsRanges()
{
    START_PROFILE

    QSize areaSize = viewport()->size();

    horizontalScrollBar()->setPageStep(mTotalWidth);
    verticalScrollBar()->setPageStep(mTotalHeight);

    horizontalScrollBar()->setRange(0, mTotalWidth - areaSize.width());
    verticalScrollBar()->setRange(0, mTotalHeight - areaSize.height());

    END_PROFILE("void FastTableWidget::updateBarsRanges()")
}

void FastTableWidget::updateVisibleRange()
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::updateVisibleRange()")
}

int FastTableWidget::rowCount()
{
    return mRowCount;
}

void FastTableWidget::setRowCount(int count)
{
    START_PROFILE

    if (count<0)
    {
        count=0;
    }

    if (mRowCount!=count)
    {
        while (mRowCount<count)
        {
            QStringList aNewRow;
            QList<QBrush *> aNewRowBrush;
            QList<QColor *> aNewRowColor;
            QList<QFont *> aNewRowFont;
            QList<bool> aNewRowbool;
            QList<int> aNewRowint;

            mTotalHeight+=mDefaultHeight;

            mData.append(aNewRow);
            mRowHeights.append(mDefaultHeight);
            mOffsetY.append(mRowCount==0? 0 : (mOffsetY.at(mRowCount-1)+mRowHeights.at(mRowCount-1)));
            mBackgroundBrushes.append(aNewRowBrush);
            mForegroundColors.append(aNewRowColor);
            mCellFonts.append(aNewRowFont);
            mCellTextFlags.append(aNewRowint);
            mSelectedCells.append(aNewRowbool);

            for (int i=0; i<mColumnCount; ++i)
            {
                mData[mRowCount].append("");
                mBackgroundBrushes[mRowCount].append(0);
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
                if (mBackgroundBrushes.at(mRowCount).at(i))
                {
                    delete mBackgroundBrushes.at(mRowCount).at(i);
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
            mBackgroundBrushes.removeLast();
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

    END_PROFILE("void FastTableWidget::setRowCount(int count)")
}

int FastTableWidget::columnCount()
{
    return mColumnCount;
}

void FastTableWidget::setColumnCount(int count)
{
    START_PROFILE

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
                    mBackgroundBrushes[i].append(0);
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
                    if (mBackgroundBrushes.at(i).at(j))
                    {
                        delete mBackgroundBrushes.at(i).at(j);
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
                    mBackgroundBrushes[i].removeLast();
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

    END_PROFILE("void FastTableWidget::setColumnCount(int count)")
}

QBrush FastTableWidget::defaultBackgroundBrush()
{
    return mDefaultBackgroundBrush;
}

void FastTableWidget::setDefaultBackgroundBrush(QBrush brush)
{
    START_PROFILE

    mDefaultBackgroundBrush=brush;

    END_PROFILE("void FastTableWidget::setDefaultBackgroundBrush(QBrush brush)")
}

QColor FastTableWidget::defaultForegroundColor()
{
    return mDefaultForegroundColor;
}

void FastTableWidget::setDefaultForegroundColor(QColor color)
{
    START_PROFILE

    mDefaultForegroundColor=color;

    END_PROFILE("void FastTableWidget::setDefaultForegroundColor(QColor color)")
}

QColor FastTableWidget::gridColor()
{
    return mGridColor;
}

void FastTableWidget::setGridColor(QColor color)
{
    START_PROFILE

    mGridColor=color;

    END_PROFILE("void FastTableWidget::setGridColor(QColor color)")
}

QBrush FastTableWidget::selectionBrush()
{
    return mSelectionBrush;
}

void FastTableWidget::setSelectionBrush(QBrush brush)
{
    START_PROFILE

    mSelectionBrush=brush;

    END_PROFILE("void FastTableWidget::setSelectionBrush(QBrush brush)")
}

quint16 FastTableWidget::defaultHeight()
{
    return mDefaultHeight;
}

void FastTableWidget::setDefaultHeight(quint16 height)
{
    START_PROFILE

    mDefaultHeight=height;

    END_PROFILE("void FastTableWidget::setDefaultHeight(quint16 height)")
}

quint16 FastTableWidget::defaultWidth()
{
    return mDefaultWidth;
}

void FastTableWidget::setDefaultWidth(quint16 width)
{
    START_PROFILE

    mDefaultWidth=width;

    END_PROFILE("void FastTableWidget::setDefaultWidth(quint16 width)")
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
    START_PROFILE

    QRect aRect;
    aRect.setCoords(mVisibleLeft, mVisibleTop, mVisibleRight, mVisibleBottom);

    END_PROFILE("QRect FastTableWidget::visibleRange()")

    return aRect;
}

QString FastTableWidget::text(const int row, const int column)
{
    return mData.at(row).at(column);
}

void FastTableWidget::setText(const int row, const int column, const QString text)
{
    START_FREQUENT_PROFILE

    mData[row][column]=text;

    END_FREQUENT_PROFILE("void FastTableWidget::setText(const int row, const int column, const QString text)")
}

quint16 FastTableWidget::rowHeight(const int row)
{
    return mRowHeights.at(row);
}

void FastTableWidget::setRowHeight(const int row, const quint16 height)
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::setRowHeight(const int row, const quint16 height)")
}

quint16 FastTableWidget::columnWidth(const int column)
{
    return mColumnWidths.at(column);
}

void FastTableWidget::setColumnWidth(const int column, const quint16 width)
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::setColumnWidth(const int column, const quint16 width)")
}

QBrush FastTableWidget::backgroundBrush(const int row, const int column)
{
    START_PROFILE

    QBrush *aBrush=mBackgroundBrushes.at(row).at(column);

    if (aBrush==0)
    {
        aBrush=&mDefaultBackgroundBrush;
    }

    END_PROFILE("QBrush FastTableWidget::backgroundBrush(const int row, const int column)")

    return *aBrush;
}

void FastTableWidget::setBackgroundBrush(const int row, const int column, const QBrush brush)
{
    START_PROFILE

    if (mBackgroundBrushes.at(row).at(column))
    {
        *mBackgroundBrushes[row][column]=brush;
    }
    else
    {
        mBackgroundBrushes[row][column]=new QBrush(brush);
    }

    END_PROFILE("void FastTableWidget::setBackgroundBrush(const int row, const int column, const QBrush brush)")
}

QColor FastTableWidget::foregroundColor(const int row, const int column)
{
    START_PROFILE

    QColor *aColor=mForegroundColors.at(row).at(column);

    if (aColor==0)
    {
        aColor=&mDefaultForegroundColor;
    }

    END_PROFILE("QColor FastTableWidget::foregroundColor(const int row, const int column)")

    return *aColor;
}

void FastTableWidget::setForegroundColor(const int row, const int column, const QColor color)
{
    START_PROFILE

    if (mForegroundColors.at(row).at(column))
    {
        *mForegroundColors[row][column]=color;
    }
    else
    {
        mForegroundColors[row][column]=new QColor(color);
    }

    END_PROFILE("void FastTableWidget::setForegroundColor(const int row, const int column, const QColor color)")
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
    START_PROFILE

    if (mCellFonts.at(row).at(column))
    {
        *mCellFonts[row][column]=font;
    }
    else
    {
        mCellFonts[row][column]=new QFont(font);
    }

    END_PROFILE("void FastTableWidget::setCellFont(const int row, const int column, const QFont font)")
}

int FastTableWidget::cellTextFlags(const int row, const int column)
{
    return mCellTextFlags.at(row).at(column);
}

void FastTableWidget::setCellTextFlags(const int row, const int column, const int flags)
{
    START_PROFILE

    mCellTextFlags[row][column]=flags;

    END_PROFILE("void FastTableWidget::setCellTextFlags(const int row, const int column, const int flags)")
}

bool FastTableWidget::cellSelected(const int row, const int column)
{
    return mSelectedCells.at(row).at(column);
}

void FastTableWidget::setCellSelected(const int row, const int column, const bool selected)
{
    START_PROFILE

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

    END_PROFILE("void FastTableWidget::setCellSelected(const int row, const int column, const bool selected)")
}
