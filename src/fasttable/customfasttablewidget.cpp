#include "customfasttablewidget.h"

CustomFastTableWidget::CustomFastTableWidget(QWidget *parent) :
    QAbstractScrollArea(parent)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mRowCount=0;
    mColumnCount=0;
    mHorizontalHeader_RowCount=0;
    mVerticalHeader_ColumnCount=0;

    mDefaultWidth=100;
    mDefaultHeight=30;
    mTotalWidth=0;
    mTotalHeight=0;
    mVerticalHeader_TotalWidth=0;
    mHorizontalHeader_TotalHeight=0;

    mVisibleLeft=-1;
    mVisibleRight=-1;
    mVisibleTop=-1;
    mVisibleBottom=-1;

    mHorizontalHeader_VisibleBottom=-1;

    mVerticalHeader_VisibleRight=-1;

#ifdef Q_OS_LINUX
    setStyle(StyleLinux);
#endif
#ifdef Q_OS_WIN
    switch (QSysInfo::windowsVersion())
    {
        case QSysInfo::WV_XP:
        {
            setStyle(StyleWinXP);
        }
        break;
        case QSysInfo::WV_WINDOWS7:
        {
            setStyle(StyleWin7);
        }
        break;
        default:
        {
            setStyle(StyleWinXP);
        }
        break;
    }
#endif

    horizontalScrollBar()->setSingleStep(100);
    verticalScrollBar()->setSingleStep(100);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollBarValueChanged(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(verticalScrollBarValueChanged(int)));

    END_PROFILE;
}

CustomFastTableWidget::~CustomFastTableWidget()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    clear();

    END_PROFILE;
}

void CustomFastTableWidget::mousePressEvent(QMouseEvent *event)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    QAbstractScrollArea::mousePressEvent(event);

    END_PROFILE;
}

void CustomFastTableWidget::resizeEvent(QResizeEvent *event)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    updateBarsRanges();
    updateVisibleRange();

    QAbstractScrollArea::resizeEvent(event);

    END_PROFILE;
}

void CustomFastTableWidget::paintEvent(QPaintEvent *event)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    QPainter painter(viewport());

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    if (mVisibleLeft>=0 && mVisibleTop>=0)
    {
        FASTTABLE_ASSERT(mVisibleBottom<mOffsetY.length());
        FASTTABLE_ASSERT(mVisibleBottom<mRowHeights.length());
        FASTTABLE_ASSERT(mVisibleRight<mOffsetX.length());
        FASTTABLE_ASSERT(mVisibleRight<mColumnWidths.length());

        for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
        {
            for (int j=mVisibleLeft; j<=mVisibleRight; ++j)
            {
                if (mColumnWidths.at(j)>=0 && mRowHeights.at(i)>=0)
                {
                    paintCell(painter, offsetX+mOffsetX.at(j), offsetY+mOffsetY.at(i), mColumnWidths.at(j), mRowHeights.at(i), i, j, DrawCell);
                }
            }
        }
    }

    if (mHorizontalHeader_VisibleBottom>=0 && mVisibleLeft>=0)
    {
        FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_OffsetY.length());
        FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowHeights.length());
        FASTTABLE_ASSERT(mVisibleRight<mOffsetX.length());
        FASTTABLE_ASSERT(mVisibleRight<mColumnWidths.length());

        for (int i=0; i<=mHorizontalHeader_VisibleBottom; ++i)
        {
            for (int j=mVisibleLeft; j<=mVisibleRight; ++j)
            {
                if (mColumnWidths.at(j)>=0 && mHorizontalHeader_RowHeights.at(i)>=0)
                {
                    paintCell(painter, offsetX+mOffsetX.at(j), mHorizontalHeader_OffsetY.at(i), mColumnWidths.at(j), mHorizontalHeader_RowHeights.at(i), i, j, DrawHorizontalHeaderCell);
                }
            }
        }
    }

    if (mVerticalHeader_VisibleRight>=0 && mVisibleTop>=0)
    {
        FASTTABLE_ASSERT(mVisibleBottom<mOffsetY.length());
        FASTTABLE_ASSERT(mVisibleBottom<mRowHeights.length());
        FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_OffsetX.length());
        FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_ColumnWidths.length());

        for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
        {
            for (int j=0; j<=mVerticalHeader_VisibleRight; ++j)
            {
                if (mVerticalHeader_ColumnWidths.at(j)>=0 && mRowHeights.at(i)>=0)
                {
                    paintCell(painter, mVerticalHeader_OffsetX.at(j), offsetY+mOffsetY.at(i), mVerticalHeader_ColumnWidths.at(j), mRowHeights.at(i), i, j, DrawVerticalHeaderCell);
                }
            }
        }
    }

    if (mVerticalHeader_VisibleRight>=0 && mHorizontalHeader_VisibleBottom>=0 && mVerticalHeader_TotalWidth>0 && mHorizontalHeader_TotalHeight>0)
    {
        paintCell(painter, 0, 0, mVerticalHeader_TotalWidth, mHorizontalHeader_TotalHeight, -1, -1, DrawTopLeftCorner);
    }

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    QColor  *aGridColor;
    QBrush  *aBackgroundBrush;
    QColor  *aTextColor;
    QString *aText;
    QString aVerticalText;
    QFont   *aFont;
    QFont   aTextFont;
    int     textFlags;

    switch (drawComponent)
    {
        case DrawCell:
        {
            FASTTABLE_ASSERT(row>=0 && row<mSelectedCells.length());
            FASTTABLE_ASSERT(column>=0 && column<mSelectedCells.at(row).length());
            FASTTABLE_ASSERT(row>=0 && row<mData.length());
            FASTTABLE_ASSERT(column>=0 && column<mData.at(row).length());

            aGridColor=&mGridColor;

            if (mSelectedCells.at(row).at(column))
            {
                aBackgroundBrush=&mSelectionBrush;
                aTextColor=&mSelectionTextColor;
            }
            else
            {
                aBackgroundBrush=&mDefaultBackgroundBrush;
                aTextColor=&mDefaultForegroundColor;
            }

            aText=&mData[row][column];

            aTextFont=font();
            aFont=&aTextFont;

            textFlags=FASTTABLE_DEFAULT_TEXT_FLAG;
        }
        break;
        case DrawHorizontalHeaderCell:
        {
            FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data.length());
            FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(row).length());
            FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns.length());

            aGridColor=&mHorizontalHeader_GridColor;
            aBackgroundBrush=&mHorizontalHeader_DefaultBackgroundBrush;
            aTextColor=&mHorizontalHeader_DefaultForegroundColor;
            aText=&mHorizontalHeader_Data[row][column];

            aTextFont=font();
            aFont=&aTextFont;

            if (mHorizontalHeader_SelectedColumns.at(column))
            {
                aBackgroundBrush=&mHorizontalHeader_DefaultBackgroundBrush;

                aFont->setPointSize(aFont->pointSize()+1);
                aFont->setBold(true);
            }

            textFlags=FASTTABLE_HEADER_DEFAULT_TEXT_FLAG;
        }
        break;
        case DrawVerticalHeaderCell:
        {
            FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
            FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data.at(row).length());
            FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows.length());

            aGridColor=&mVerticalHeader_GridColor;
            aBackgroundBrush=&mVerticalHeader_DefaultBackgroundBrush;
            aTextColor=&mVerticalHeader_DefaultForegroundColor;
            aText=&mVerticalHeader_Data[row][column];

            if (*aText=="")
            {
                aVerticalText=QString::number(row+1);
                aText=&aVerticalText;
            }

            aTextFont=font();
            aFont=&aTextFont;

            if (mVerticalHeader_SelectedRows.at(row))
            {
                aFont->setPointSize(aFont->pointSize()+1);
                aFont->setBold(true);
            }

            textFlags=FASTTABLE_DEFAULT_TEXT_FLAG;
        }
        break;
        case DrawTopLeftCorner:
        {
            aGridColor=&mHorizontalHeader_GridColor;
            aBackgroundBrush=&mHorizontalHeader_DefaultBackgroundBrush;
            aTextColor=0;
            aText=0;
            aFont=0;
            textFlags=0;
        }
        break;
        default:
        {
            aGridColor=0;
            aBackgroundBrush=0;
            aTextColor=0;
            aText=0;
            aFont=0;
            textFlags=0;
        }
        break;
    }

    paintCell(painter, x ,y, width, height, row, column, drawComponent, aGridColor, aBackgroundBrush, aTextColor, aText, aFont, textFlags);

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent,
                                      QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aTextColor, QString *aText, QFont *aFont, int aTextFlags)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    if (drawComponent==DrawCell || height<=8)
    {
        (*mDrawCellFunction)(painter, x, y, width, height, row, column, aGridColor, aBackgroundBrush);
    }
    else
    {
        (*mDrawHeaderCellFunction)(painter, x, y, width, height, row, column, aGridColor, aBackgroundBrush);
    }

    if (width>8 && height>8 && aText)
    {
        painter.setPen(QPen(*aTextColor));
        painter.setFont(*aFont);
        painter.drawText(x+4, y+4, width-8, height-8, aTextFlags, *aText);
    }

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, QColor *aGridColor, QBrush *aBackgroundBrush)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    QColor backColorDown=aBackgroundBrush->color();

    int r=backColorDown.red()+10;
    int g=backColorDown.green()+10;
    int b=backColorDown.blue()+10;

    if (r>255)
    {
        r=255;
    }

    if (g>255)
    {
        g=255;
    }

    if (b>255)
    {
        b=255;
    }

    QColor backColorUp(r, g, b);

    QLinearGradient aGradient(x, y, x, y+height);
    aGradient.setColorAt(0, backColorUp);
    aGradient.setColorAt(1, backColorDown);

    QBrush aBrush(aGradient);

    painter.fillRect(x, y, width, height, aBrush);

    painter.setPen(QPen(*aGridColor));
    painter.drawRect(x, y, width, height);

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintCellDefault(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, QColor *aGridColor, QBrush *aBackgroundBrush)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    painter.fillRect(x, y, width, height, *aBackgroundBrush);

    painter.setPen(QPen(*aGridColor));
    painter.drawRect(x, y, width, height);

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, QColor *aGridColor, QBrush *aBackgroundBrush)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    QColor backColorDown=aBackgroundBrush->color();

    int r=backColorDown.red()+20;
    int g=backColorDown.green()+20;
    int b=backColorDown.blue()+20;

    if (r>255)
    {
        r=255;
    }

    if (g>255)
    {
        g=255;
    }

    if (b>255)
    {
        b=255;
    }

    QColor backColorUp(r, g, b);

    QLinearGradient aGradient(x, y, x, y+height);
    aGradient.setColorAt(0, backColorUp);
    aGradient.setColorAt(1, backColorDown);

    QBrush aBrush(aGradient);

    painter.fillRect(x, y, width, height, aBrush);

    painter.setPen(QPen(*aGridColor));
    painter.drawRect(x, y, width, height);

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellWinXP(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, QColor *aGridColor, QBrush *aBackgroundBrush)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    painter.fillRect(x+1, y+1, width, height-3, *aBackgroundBrush);

    painter.setPen(QPen(QColor(255, 255, 255)));
    painter.drawLine(x+width, y+4, x+width, y+height-4);
    painter.drawLine(x, y+4, x, y+height-4);

    painter.setPen(QPen(*aGridColor));
    painter.drawLine(x+width-1, y+4, x+width-1, y+height-4);
    painter.drawLine(x, y+height, x+width, y+height);
    painter.drawLine(x, y, x+width, y);

    QColor backColor=aBackgroundBrush->color();

    painter.setPen(QPen(QColor(backColor.red()+(aGridColor->red()-backColor.red())*2/3, backColor.green()+(aGridColor->green()-backColor.green())*2/3, backColor.blue()+(aGridColor->blue()-backColor.blue())*2/3)));
    painter.drawLine(x, y+height-1, x+width, y+height-1);
    painter.setPen(QPen(QColor(backColor.red()+(aGridColor->red()-backColor.red())/3, backColor.green()+(aGridColor->green()-backColor.green())/3, backColor.blue()+(aGridColor->blue()-backColor.blue())/3)));
    painter.drawLine(x, y+height-2, x+width, y+height-2);

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellWin7(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, QColor *aGridColor, QBrush *aBackgroundBrush)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    QColor backColorDown=aBackgroundBrush->color();

    int r=backColorDown.red()+15;
    int g=backColorDown.green()+15;
    int b=backColorDown.blue()+15;

    if (r>255)
    {
        r=255;
    }

    if (g>255)
    {
        g=255;
    }

    if (b>255)
    {
        b=255;
    }

    QColor backColorUp(r, g, b);

    painter.setPen(QPen(backColorUp));
    painter.drawLine(x+1, y, x+1, y+height);
    painter.drawLine(x+width-1, y, x+width-1, y+height);

    painter.fillRect(x+2, y, width-3, height/2, backColorUp);
    painter.fillRect(x+2, y+height/2, width-3, height-height/2, backColorDown);

    painter.setPen(QPen(*aGridColor));
    painter.drawRect(x, y, width, height);

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::horizontalScrollBarValueChanged(int value)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    updateVisibleRange();

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::verticalScrollBarValueChanged(int value)
{
    FASTTABLE_FREQUENT_DEBUG;
    START_FREQUENT_PROFILE;

    updateVisibleRange();

    END_FREQUENT_PROFILE;
}

void CustomFastTableWidget::updateBarsRanges()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (mTotalWidth<=0 || mTotalHeight<=0)
    {
        horizontalScrollBar()->setRange(0, 0);
        verticalScrollBar()->setRange(0, 0);
    }
    else
    {
        QSize areaSize=viewport()->size();

        horizontalScrollBar()->setPageStep(areaSize.width()-mVerticalHeader_TotalWidth);
        verticalScrollBar()->setPageStep(areaSize.height()-mHorizontalHeader_TotalHeight);

        horizontalScrollBar()->setRange(0, mTotalWidth  - areaSize.width()  + 1);
        verticalScrollBar()->setRange(0,   mTotalHeight - areaSize.height() + 1);
    }

    END_PROFILE;
}

void CustomFastTableWidget::updateVisibleRange()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (mRowCount==0 || mColumnCount==0)
    {
        mVisibleLeft=-1;
        mVisibleRight=-1;
        mVisibleTop=-1;
        mVisibleBottom=-1;
        mVerticalHeader_VisibleRight=-1;
        mHorizontalHeader_VisibleBottom=-1;
    }
    else
    {
        QSize areaSize=viewport()->size();

        int minX=horizontalScrollBar()->value();
        int minY=verticalScrollBar()->value();
        int maxX=minX+areaSize.width();
        int maxY=minY+areaSize.height();

        if (mVerticalHeader_ColumnCount==0)
        {
            mVerticalHeader_VisibleRight=-1;
        }
        else
        {
            if (mVerticalHeader_VisibleRight<0)
            {
                mVerticalHeader_VisibleRight=0;
            }
            else
            if (mVerticalHeader_VisibleRight>=mVerticalHeader_ColumnCount)
            {
                mVerticalHeader_VisibleRight=mVerticalHeader_ColumnCount-1;
            }

            FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_OffsetX.length());
            FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_ColumnWidths.length());

            while (mVerticalHeader_VisibleRight<mVerticalHeader_ColumnCount-1 && mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)<maxX && mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<maxX)
            {
                mVerticalHeader_VisibleRight++;
            }

            while (mVerticalHeader_VisibleRight>0 && mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)>maxX && mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)>maxX)
            {
                mVerticalHeader_VisibleRight--;
            }
        }


        if (mHorizontalHeader_RowCount==0)
        {
            mHorizontalHeader_VisibleBottom=-1;
        }
        else
        {
            if (mHorizontalHeader_VisibleBottom<0)
            {
                mHorizontalHeader_VisibleBottom=0;
            }
            else
            if (mHorizontalHeader_VisibleBottom>=mHorizontalHeader_RowCount)
            {
                mHorizontalHeader_VisibleBottom=mHorizontalHeader_RowCount-1;
            }

            FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_OffsetY.length());
            FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowHeights.length());

            while (mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowCount-1 && mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)<maxY && mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<maxY)
            {
                mHorizontalHeader_VisibleBottom++;
            }

            while (mHorizontalHeader_VisibleBottom>0 && mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)>maxY && mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)>maxY)
            {
                mHorizontalHeader_VisibleBottom--;
            }
        }

        if (
            mHorizontalHeader_VisibleBottom<0
            ||
            mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<maxY
           )
        {
            if (
                mVisibleTop<0
                ||
                mVisibleBottom<0
               )
            {
                mVisibleTop=0;
                mVisibleBottom=0;
            }
            else
            {
                if (mVisibleTop>=mRowCount)
                {
                    mVisibleTop=mRowCount-1;
                }
                if (mVisibleBottom>=mRowCount)
                {
                    mVisibleBottom=mRowCount-1;
                }
            }

            minY+=mHorizontalHeader_TotalHeight;

            FASTTABLE_ASSERT(mVisibleTop<mOffsetY.length());
            FASTTABLE_ASSERT(mVisibleTop<mRowHeights.length());
            FASTTABLE_ASSERT(mVisibleBottom<mOffsetY.length());
            FASTTABLE_ASSERT(mVisibleBottom<mRowHeights.length());

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
        else
        {
            mVisibleTop=-1;
            mVisibleBottom=-1;
        }

        if (
            mVerticalHeader_VisibleRight<0
            ||
            mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<maxX
           )
        {
            if (
                mVisibleLeft<0
                ||
                mVisibleRight<0
               )
            {
                mVisibleLeft=0;
                mVisibleRight=0;
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
            }

            minX+=mVerticalHeader_TotalWidth;

            FASTTABLE_ASSERT(mVisibleLeft<mOffsetX.length());
            FASTTABLE_ASSERT(mVisibleLeft<mColumnWidths.length());
            FASTTABLE_ASSERT(mVisibleRight<mOffsetX.length());
            FASTTABLE_ASSERT(mVisibleRight<mColumnWidths.length());

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
        }
        else
        {
            mVisibleLeft=-1;
            mVisibleRight=-1;
        }
    }

    END_PROFILE;
}

void CustomFastTableWidget::clear()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mRowCount=0;
    mColumnCount=0;
    mHorizontalHeader_RowCount=0;
    mVerticalHeader_ColumnCount=0;

    mTotalWidth=0;
    mTotalHeight=0;
    mVerticalHeader_TotalWidth=0;
    mHorizontalHeader_TotalHeight=0;

    mVisibleLeft=-1;
    mVisibleRight=-1;
    mVisibleTop=-1;
    mVisibleBottom=-1;

    mHorizontalHeader_VisibleBottom=-1;

    mVerticalHeader_VisibleRight=-1;

    mData.clear();
    mRowHeights.clear();
    mColumnWidths.clear();
    mOffsetX.clear();
    mOffsetY.clear();

    mHorizontalHeader_Data.clear();
    mHorizontalHeader_RowHeights.clear();
    mHorizontalHeader_OffsetY.clear();

    mVerticalHeader_Data.clear();
    mVerticalHeader_ColumnWidths.clear();
    mVerticalHeader_OffsetX.clear();

    mSelectedCells.clear();
    mCurSelection.clear();
    mHorizontalHeader_SelectedColumns.clear();
    mVerticalHeader_SelectedRows.clear();

    updateBarsRanges();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::selectRow(const int row)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, true);
    }

    END_PROFILE;
}

void CustomFastTableWidget::unselectRow(const int row)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, false);
    }

    END_PROFILE;
}

void CustomFastTableWidget::selectColumn(const int column)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, true);
    }

    END_PROFILE;
}

void CustomFastTableWidget::unselectColumn(const int column)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, false);
    }

    END_PROFILE;
}

CustomFastTableWidget::Style CustomFastTableWidget::style()
{
    FASTTABLE_DEBUG;
    return mStyle;
}

void CustomFastTableWidget::setStyle(Style style, bool keepColors)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (mStyle!=style)
    {
        mStyle=style;

        if (!keepColors)
        {
            switch (mStyle)
            {
                case StyleSimple:
                {
                    mDefaultBackgroundBrush.setColor(QColor(255, 255, 255));
                    mDefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mDefaultForegroundColor.setRgb(0, 0, 0);
                    mGridColor.setRgb(200, 200, 200);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(220, 220, 220));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(200, 200, 200);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(220, 220, 220));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(200, 200, 200);

                    mSelectionBrush.setColor(QColor(49, 106, 197));
                    mSelectionBrush.setStyle(Qt::SolidPattern);
                    mSelectionTextColor.setRgb(255, 255, 255);
                }
                break;
                case StyleLinux:
                {
                    mDefaultBackgroundBrush.setColor(QColor(255, 255, 255));
                    mDefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mDefaultForegroundColor.setRgb(0, 0, 0);
                    mGridColor.setRgb(202, 201, 200);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(234, 233, 231));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(210, 207, 204);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(233, 232, 231));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(190, 186, 182);

                    mSelectionBrush.setColor(QColor(235, 110, 60));
                    mSelectionBrush.setStyle(Qt::SolidPattern);
                    mSelectionTextColor.setRgb(255, 255, 255);
                }
                break;
                case StyleWinXP:
                {
                    mDefaultBackgroundBrush.setColor(QColor(255, 255, 255));
                    mDefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mDefaultForegroundColor.setRgb(0, 0, 0);
                    mGridColor.setRgb(192, 192, 192);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(235, 234, 219));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(199, 197, 178);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(235, 234, 219));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(199, 197, 178);

                    mSelectionBrush.setColor(QColor(49, 106, 197));
                    mSelectionBrush.setStyle(Qt::SolidPattern);
                    mSelectionTextColor.setRgb(255, 255, 255);
                }
                break;
                case StyleWin7:
                {
                    mDefaultBackgroundBrush.setColor(QColor(255, 255, 255));
                    mDefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mDefaultForegroundColor.setRgb(0, 0, 0);
                    mGridColor.setRgb(216, 216, 216);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(241, 242, 244));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(213, 213, 213);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(241, 242, 244));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(213, 213, 213);

                    mSelectionBrush.setColor(QColor(51, 153, 255));
                    mSelectionBrush.setStyle(Qt::SolidPattern);
                    mSelectionTextColor.setRgb(255, 255, 255);
                }
                break;
            }
        }

        switch (mStyle)
        {
            case StyleSimple:
            {
                mDrawCellFunction=&paintCellDefault;
                mDrawHeaderCellFunction=&paintCellDefault;
            }
            break;
            case StyleLinux:
            {
                mDrawCellFunction=&paintCellLinux;
                mDrawHeaderCellFunction=&paintHeaderCellLinux;
            }
            break;
            case StyleWinXP:
            {
                mDrawCellFunction=&paintCellDefault;
                mDrawHeaderCellFunction=&paintHeaderCellWinXP;
            }
            break;
            case StyleWin7:
            {
                mDrawCellFunction=&paintCellDefault;
                mDrawHeaderCellFunction=&paintHeaderCellWin7;
            }
            break;
        }

        viewport()->update();
    }

    END_PROFILE;
}

void CustomFastTableWidget::setDrawCellFunction(DrawFunction aDrawCellFunction)
{
    mDrawCellFunction=aDrawCellFunction;
    viewport()->update();
}

void CustomFastTableWidget::setDrawHeaderCellFunction(DrawFunction aDrawHeaderCellFunction)
{
    mDrawHeaderCellFunction=aDrawHeaderCellFunction;
    viewport()->update();
}

void CustomFastTableWidget::selectAll()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mCurSelection.clear();

    QPoint aCellPos;

    for (int i=0; i<mRowCount; ++i)
    {
        for (int j=0; j<mColumnCount; ++j)
        {
            FASTTABLE_ASSERT(i<mSelectedCells.length());
            FASTTABLE_ASSERT(j<mSelectedCells.at(i).length());

            aCellPos.setX(j);
            aCellPos.setY(i);

            mCurSelection.append(aCellPos);

            mSelectedCells[i][j]=true;
        }
    }

    for (int i=0; i<mRowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mVerticalHeader_SelectedRows.length());

        mVerticalHeader_SelectedRows[i]=true;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns.length());

        mHorizontalHeader_SelectedColumns[i]=true;
    }

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::unselectAll()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    for (int i=0; i<mCurSelection.length(); ++i)
    {
        FASTTABLE_ASSERT(mCurSelection.at(i).y()<mSelectedCells.length());
        FASTTABLE_ASSERT(mCurSelection.at(i).x()<mSelectedCells.at(mCurSelection.at(i).y()).length());

        mSelectedCells[mCurSelection.at(i).y()][mCurSelection.at(i).x()]=false;
    }

    mCurSelection.clear();

    for (int i=0; i<mRowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mVerticalHeader_SelectedRows.length());

        mVerticalHeader_SelectedRows[i]=false;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns.length());

        mHorizontalHeader_SelectedColumns[i]=false;
    }

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::addRow()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    insertRow(mRowCount);

    END_PROFILE;
}

void CustomFastTableWidget::insertRow(int row)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<=mRowCount);
    FASTTABLE_ASSERT(row>=0 && row<=mOffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<=mRowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<=mData.length());
    FASTTABLE_ASSERT(row>=0 && row<=mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(row>=0 && row<=mSelectedCells.length());
    FASTTABLE_ASSERT(row>=0 && row<=mVerticalHeader_SelectedRows.length());

    mRowCount++;

    QStringList aNewRow;
    QList<bool> aNewRowbool;

    mTotalHeight+=mDefaultHeight;

    mOffsetY.insert(row, row==0? mHorizontalHeader_TotalHeight : (mOffsetY.at(row-1)+mRowHeights.at(row-1)));
    mRowHeights.insert(row, mDefaultHeight);

    for (int i=row+1; i<mRowCount; ++i)
    {
        mOffsetY[i]+=mDefaultHeight;
    }

    mData.insert(row, aNewRow);
    mVerticalHeader_Data.insert(row, aNewRow);
    mSelectedCells.insert(row, aNewRowbool);
    mVerticalHeader_SelectedRows.insert(row, false);

    for (int i=0; i<mVerticalHeader_ColumnCount; ++i)
    {
        mVerticalHeader_Data[row].append("");
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        mData[row].append("");
        mSelectedCells[row].append(false);
    }

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::deleteRow(int row)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);
    FASTTABLE_ASSERT(row>=0 && row<mOffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<mRowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<mData.length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells.length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows.length());

    int diff=mRowHeights.at(row);

    mTotalHeight-=diff;

    FASTTABLE_ASSERT(mTotalHeight>=0);

    for (int i=row+1; i<mRowCount; ++i)
    {
        mOffsetY[i]-=diff;

        FASTTABLE_ASSERT(mOffsetY.at(i)>=0);
    }

    mOffsetY.removeAt(row);
    mRowHeights.removeAt(row);

    mData.removeAt(row);
    mVerticalHeader_Data.removeAt(row);

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mSelectedCells.at(row).length());

        if (mSelectedCells.at(row).at(i))
        {
            for (int j=0; j<mCurSelection.length(); ++j)
            {
                if (mCurSelection.at(j).y()==row && mCurSelection.at(j).x()==i)
                {
                    mCurSelection.removeAt(j);
                    break;
                }
            }
        }
    }

    mSelectedCells.removeAt(row);
    mVerticalHeader_SelectedRows.removeAt(row);

    mRowCount--;

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::addColumn()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    insertColumn(mColumnCount);

    END_PROFILE;
}

void CustomFastTableWidget::insertColumn(int column)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<=mColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<=mOffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<=mColumnWidths.length());
    FASTTABLE_ASSERT(column>=0 && column<=mHorizontalHeader_SelectedColumns.length());

    mColumnCount++;

    mTotalWidth+=mDefaultWidth;

    mOffsetX.insert(column, column==0? mVerticalHeader_TotalWidth : (mOffsetX.at(column-1)+mColumnWidths.at(column-1)));
    mColumnWidths.insert(column, mDefaultWidth);

    for (int i=column+1; i<mColumnCount; ++i)
    {
        mOffsetX[i]+=mDefaultWidth;
    }

    for (int i=0; i<mHorizontalHeader_Data.length(); ++i)
    {
        FASTTABLE_ASSERT(column<=mHorizontalHeader_Data.at(i).length());

        mHorizontalHeader_Data[i].insert(column, "");
    }

    for (int i=0; i<mData.length(); ++i)
    {
        FASTTABLE_ASSERT(column<=mData.at(i).length());
        FASTTABLE_ASSERT(column<=mSelectedCells.at(i).length());

        mData[i].insert(column, "");
        mSelectedCells[i].insert(column, false);
    }

    mHorizontalHeader_SelectedColumns.insert(column, false);

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::deleteColumn(int column)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<mOffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths.length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns.length());

    int diff=mColumnWidths.at(column);

    mTotalWidth-=diff;

    FASTTABLE_ASSERT(mTotalWidth>=0);

    for (int i=column+1; i<mColumnCount; ++i)
    {
        mOffsetX[i]-=diff;

        FASTTABLE_ASSERT(mOffsetX.at(i)>=0);

    }

    mOffsetX.removeAt(column);
    mColumnWidths.removeAt(column);

    for (int i=0; i<mHorizontalHeader_Data.length(); ++i)
    {
        FASTTABLE_ASSERT(column<mHorizontalHeader_Data.at(i).length());

        mHorizontalHeader_Data[i].removeAt(column);
    }

    for (int i=0; i<mData.length(); ++i)
    {
        FASTTABLE_ASSERT(column<mData.at(i).length());
        FASTTABLE_ASSERT(column<mSelectedCells.at(i).length());

        mData[i].removeAt(column);

        if (mSelectedCells.at(i).at(column))
        {
            for (int j=0; j<mCurSelection.length(); ++j)
            {
                if (mCurSelection.at(j).y()==i && mCurSelection.at(j).x()==column)
                {
                    mCurSelection.removeAt(j);
                    break;
                }
            }
        }

        mSelectedCells[i].removeAt(column);
    }

    mHorizontalHeader_SelectedColumns.removeAt(column);

    mColumnCount--;

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_AddRow()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    horizontalHeader_InsertRow(mHorizontalHeader_RowCount);

    END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_InsertRow(int row)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_RowCount);
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_OffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_RowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_Data.length());

    mHorizontalHeader_RowCount++;

    QStringList aNewRow;

    mHorizontalHeader_TotalHeight+=mDefaultHeight;
    mTotalHeight+=mDefaultHeight;

    mHorizontalHeader_OffsetY.insert(row, row==0? 0 : (mHorizontalHeader_OffsetY.at(row-1)+mHorizontalHeader_RowHeights.at(row-1)));
    mHorizontalHeader_RowHeights.insert(row, mDefaultHeight);

    for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
    {
        mHorizontalHeader_OffsetY[i]+=mDefaultHeight;
    }

    for (int i=0; i<mRowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetY.length());

        mOffsetY[i]+=mDefaultHeight;
    }

    mHorizontalHeader_Data.insert(row, aNewRow);

    for (int i=0; i<mColumnCount; ++i)
    {
        mHorizontalHeader_Data[row].append("");
    }

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_DeleteRow(int row)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_RowCount);
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_OffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_RowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data.length());

    int diff=mHorizontalHeader_RowHeights.at(row);

    mHorizontalHeader_TotalHeight-=diff;
    mTotalHeight-=diff;

    FASTTABLE_ASSERT(mHorizontalHeader_TotalHeight>=0);
    FASTTABLE_ASSERT(mTotalHeight>=0);

    for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
    {
        mHorizontalHeader_OffsetY[i]-=diff;

        FASTTABLE_ASSERT(mHorizontalHeader_OffsetY.at(i)>=0);
    }

    for (int i=0; i<mRowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetY.length());

        mOffsetY[i]-=diff;

        FASTTABLE_ASSERT(mOffsetY.at(i)>=0);
    }

    mHorizontalHeader_OffsetY.removeAt(row);
    mHorizontalHeader_RowHeights.removeAt(row);
    mHorizontalHeader_Data.removeAt(row);

    mHorizontalHeader_RowCount--;

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_AddColumn()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    verticalHeader_InsertColumn(mVerticalHeader_ColumnCount);

    END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_InsertColumn(int column)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_ColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_OffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_ColumnWidths.length());

    mVerticalHeader_ColumnCount++;

    mVerticalHeader_TotalWidth+=mDefaultWidth;
    mTotalWidth+=mDefaultWidth;

    mVerticalHeader_OffsetX.insert(column, column==0? 0 : (mVerticalHeader_OffsetX.at(column-1)+mVerticalHeader_ColumnWidths.at(column-1)));
    mVerticalHeader_ColumnWidths.insert(column, mDefaultWidth);

    for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
    {
        mVerticalHeader_OffsetX[i]+=mDefaultWidth;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetX.length());

        mOffsetX[i]+=mDefaultWidth;
    }

    for (int i=0; i<mVerticalHeader_Data.length(); ++i)
    {
        FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_Data.at(i).length());

        mVerticalHeader_Data[i].insert(column, "");
    }

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_DeleteColumn(int column)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_OffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnWidths.length());

    int diff=mVerticalHeader_ColumnWidths.at(column);

    mVerticalHeader_TotalWidth-=diff;
    mTotalWidth-=diff;

    FASTTABLE_ASSERT(mVerticalHeader_TotalWidth>=0);
    FASTTABLE_ASSERT(mTotalWidth>=0);

    for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
    {
        mVerticalHeader_OffsetX[i]-=diff;

        FASTTABLE_ASSERT(mVerticalHeader_OffsetX.at(i)>=0);
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetX.length());

        mOffsetX[i]-=diff;

        FASTTABLE_ASSERT(mOffsetX.at(i)>=0);
    }

    mVerticalHeader_OffsetX.removeAt(column);
    mVerticalHeader_ColumnWidths.removeAt(column);

    for (int i=0; i<mVerticalHeader_Data.length(); ++i)
    {
        FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data.at(i).length());

        mVerticalHeader_Data[i].removeAt(column);
    }

    mVerticalHeader_ColumnCount--;

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    END_PROFILE;
}

int CustomFastTableWidget::rowCount()
{
    FASTTABLE_DEBUG;
    return mRowCount;
}

void CustomFastTableWidget::setRowCount(int count)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mRowCount!=count)
    {
        bool wasAllowUpdates=updatesEnabled();

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(false);
        }

        while (mRowCount<count)
        {
            addRow();
        }

        while (mRowCount>count)
        {
            deleteRow(mRowCount-1);
        }

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(true);
        }
    }

    END_PROFILE;
}

int CustomFastTableWidget::columnCount()
{
    FASTTABLE_DEBUG;
    return mColumnCount;
}

void CustomFastTableWidget::setColumnCount(int count)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mColumnCount!=count)
    {
        bool wasAllowUpdates=updatesEnabled();

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(false);
        }

        while (mColumnCount<count)
        {
            addColumn();
        }

        while (mColumnCount>count)
        {
            deleteColumn(mColumnCount-1);
        }

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(true);
        }
    }

    END_PROFILE;
}

qint16 CustomFastTableWidget::horizontalHeader_RowCount()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_RowCount;
}

void CustomFastTableWidget::horizontalHeader_SetRowCount(qint16 count)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mHorizontalHeader_RowCount!=count)
    {
        bool wasAllowUpdates=updatesEnabled();

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(false);
        }

        while (mHorizontalHeader_RowCount<count)
        {
            horizontalHeader_AddRow();
        }

        while (mHorizontalHeader_RowCount>count)
        {
            horizontalHeader_DeleteRow(mHorizontalHeader_RowCount-1);
        }

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(true);
        }
    }

    END_PROFILE;
}

qint16 CustomFastTableWidget::verticalHeader_ColumnCount()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_ColumnCount;
}

void CustomFastTableWidget::verticalHeader_SetColumnCount(qint16 count)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mVerticalHeader_ColumnCount!=count)
    {
        bool wasAllowUpdates=updatesEnabled();

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(false);
        }

        while (mVerticalHeader_ColumnCount<count)
        {
            verticalHeader_AddColumn();
        }

        while (mVerticalHeader_ColumnCount>count)
        {
            verticalHeader_DeleteColumn(mVerticalHeader_ColumnCount-1);
        }

        if (wasAllowUpdates)
        {
            setUpdatesEnabled(true);
        }
    }

    END_PROFILE;
}

void CustomFastTableWidget::setSizes(int aRowCount, int aColumnCount, qint16 aHorizontalHeaderRowCount, qint16 aVerticalHeaderColumnCount)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    bool wasAllowUpdates=updatesEnabled();

    if (wasAllowUpdates)
    {
        setUpdatesEnabled(false);
    }

    setRowCount(aRowCount);
    setColumnCount(aColumnCount);
    horizontalHeader_SetRowCount(aHorizontalHeaderRowCount);
    verticalHeader_SetColumnCount(aVerticalHeaderColumnCount);

    if (wasAllowUpdates)
    {
        setUpdatesEnabled(true);
    }

    END_PROFILE;
}

QBrush CustomFastTableWidget::defaultBackgroundBrush()
{
    FASTTABLE_DEBUG;
    return mDefaultBackgroundBrush;
}

void CustomFastTableWidget::setDefaultBackgroundBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mDefaultBackgroundBrush=brush;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::defaultForegroundColor()
{
    FASTTABLE_DEBUG;
    return mDefaultForegroundColor;
}

void CustomFastTableWidget::setDefaultForegroundColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mDefaultForegroundColor=color;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::gridColor()
{
    FASTTABLE_DEBUG;
    return mGridColor;
}

void CustomFastTableWidget::setGridColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mGridColor=color;

    viewport()->update();

    END_PROFILE;
}

QBrush CustomFastTableWidget::horizontalHeader_DefaultBackgroundBrush()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_DefaultBackgroundBrush;
}

void CustomFastTableWidget::horizontalHeader_SetDefaultBackgroundBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mHorizontalHeader_DefaultBackgroundBrush=brush;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::horizontalHeader_DefaultForegroundColor()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_DefaultForegroundColor;
}

void CustomFastTableWidget::horizontalHeader_SetDefaultForegroundColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mHorizontalHeader_DefaultForegroundColor=color;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::horizontalHeader_GridColor()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_GridColor;
}

void CustomFastTableWidget::horizontalHeader_SetGridColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mHorizontalHeader_GridColor=color;

    viewport()->update();

    END_PROFILE;
}

QBrush CustomFastTableWidget::verticalHeader_DefaultBackgroundBrush()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_DefaultBackgroundBrush;
}

void CustomFastTableWidget::verticalHeader_SetDefaultBackgroundBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mVerticalHeader_DefaultBackgroundBrush=brush;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::verticalHeader_DefaultForegroundColor()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_DefaultForegroundColor;
}

void CustomFastTableWidget::verticalHeader_SetDefaultForegroundColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mVerticalHeader_DefaultForegroundColor=color;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::verticalHeader_GridColor()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_GridColor;
}

void CustomFastTableWidget::verticalHeader_SetGridColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mVerticalHeader_GridColor=color;

    viewport()->update();

    END_PROFILE;
}

QBrush CustomFastTableWidget::selectionBrush()
{
    FASTTABLE_DEBUG;
    return mSelectionBrush;
}

void CustomFastTableWidget::setSelectionBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mSelectionBrush=brush;

    viewport()->update();

    END_PROFILE;
}

QColor CustomFastTableWidget::selectionTextColor()
{
    FASTTABLE_DEBUG;
    return mSelectionTextColor;
}

void CustomFastTableWidget::setSelectionTextColor(QColor color)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    mSelectionTextColor=color;

    viewport()->update();

    END_PROFILE;
}

quint16 CustomFastTableWidget::defaultWidth()
{
    FASTTABLE_DEBUG;
    return mDefaultWidth;
}

void CustomFastTableWidget::setDefaultWidth(quint16 width)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (width<=0)
    {
        width=1;
    }
    else
    if (width>32767)
    {
        FASTTABLE_LOG_DEBUG("Default width is too big: "+QString::number(width)+". The maximum width is 32767");
        width=32767;
    }

    mDefaultWidth=width;

    END_PROFILE;
}

quint16 CustomFastTableWidget::defaultHeight()
{
    FASTTABLE_DEBUG;
    return mDefaultHeight;
}

void CustomFastTableWidget::setDefaultHeight(quint16 height)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    if (height<=0)
    {
        height=1;
    }
    else
    if (height>32767)
    {
        FASTTABLE_LOG_DEBUG("Default height is too big: "+QString::number(height)+". The maximum height is 32767");
        height=32767;
    }

    mDefaultHeight=height;

    END_PROFILE;
}

quint16 CustomFastTableWidget::columnWidth(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column<mColumnWidths.length());

    if (mColumnWidths.at(column)<0)
    {
        return -mColumnWidths.at(column);
    }
    else
    {
        return mColumnWidths.at(column);
    }
}

void CustomFastTableWidget::setColumnWidth(const int column, quint16 width)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column<mColumnWidths.length());

    if (width>32767)
    {
        FASTTABLE_LOG_DEBUG("Width for column #"+QString::number(column)+" is too big: "+QString::number(width)+". The maximum width is 32767");
        width=32767;
    }

    if (mColumnWidths.at(column)<0)
    {
        mColumnWidths[column]=-width;
    }
    else
    if (mColumnWidths.at(column)!=width)
    {
        int aDiff=width-mColumnWidths.at(column);

        mColumnWidths[column]=width;

        mTotalWidth+=aDiff;

        FASTTABLE_ASSERT(mTotalWidth>=0);

        for (int i=column+1; i<mColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mOffsetX.length());

            mOffsetX[i]+=aDiff;

            FASTTABLE_ASSERT(mOffsetX.at(i)>=0);
        }

        updateBarsRanges();
        updateVisibleRange();

        viewport()->update();
    }

    END_PROFILE;
}

quint16 CustomFastTableWidget::rowHeight(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mRowHeights.length());

    if (mRowHeights.at(row)<0)
    {
        return -mRowHeights.at(row);
    }
    else
    {
        return mRowHeights.at(row);
    }
}

void CustomFastTableWidget::setRowHeight(const int row, quint16 height)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row<mRowHeights.length());

    if (height>32767)
    {
        FASTTABLE_LOG_DEBUG("Height for row #"+QString::number(row)+" is too big: "+QString::number(height)+". The maximum height is 32767");
        height=32767;
    }

    if (mRowHeights.at(row)<0)
    {
        mRowHeights[row]=-height;
    }
    else
    if (mRowHeights.at(row)!=height)
    {
        int aDiff=height-mRowHeights.at(row);

        mRowHeights[row]=height;

        mTotalHeight+=aDiff;

        FASTTABLE_ASSERT(mTotalHeight>=0);

        for (int i=row+1; i<mRowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mOffsetY.length());

            mOffsetY[i]+=aDiff;

            FASTTABLE_ASSERT(mOffsetY.at(i)>=0);
        }

        updateBarsRanges();
        updateVisibleRange();

        viewport()->update();
    }

    END_PROFILE;
}

quint16 CustomFastTableWidget::verticalHeader_ColumnWidth(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths.length());

    if (mVerticalHeader_ColumnWidths.at(column)<0)
    {
        return -mVerticalHeader_ColumnWidths.at(column);
    }
    else
    {
        return mVerticalHeader_ColumnWidths.at(column);
    }
}

void CustomFastTableWidget::verticalHeader_SetColumnWidth(const int column, quint16 width)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths.length());

    if (width>32767)
    {
        FASTTABLE_LOG_DEBUG("Width for column #"+QString::number(column)+" in vertical header is too big: "+QString::number(width)+". The maximum width is 32767");
        width=32767;
    }

    if (mVerticalHeader_ColumnWidths.at(column)<0)
    {
        mVerticalHeader_ColumnWidths[column]=-width;
    }
    else
    if (mVerticalHeader_ColumnWidths.at(column)!=width)
    {
        int aDiff=width-mVerticalHeader_ColumnWidths.at(column);

        mVerticalHeader_ColumnWidths[column]=width;

        mVerticalHeader_TotalWidth+=aDiff;
        mTotalWidth+=aDiff;

        FASTTABLE_ASSERT(mVerticalHeader_TotalWidth>=0);
        FASTTABLE_ASSERT(mTotalWidth>=0);

        for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mVerticalHeader_OffsetX.length());

            mVerticalHeader_OffsetX[i]+=aDiff;

            FASTTABLE_ASSERT(mVerticalHeader_OffsetX.at(i)>=0);
        }

        for (int i=0; i<mColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mOffsetX.length());

            mOffsetX[i]+=aDiff;

            FASTTABLE_ASSERT(mOffsetX.at(i)>=0);
        }

        updateBarsRanges();
        updateVisibleRange();

        viewport()->update();
    }

    END_PROFILE;
}

quint16 CustomFastTableWidget::horizontalHeader_RowHeight(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights.length());

    if (mHorizontalHeader_RowHeights.at(row)<0)
    {
        return -mHorizontalHeader_RowHeights.at(row);
    }
    else
    {
        return mHorizontalHeader_RowHeights.at(row);
    }
}

void CustomFastTableWidget::horizontalHeader_SetRowHeight(const int row, quint16 height)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights.length());

    if (height>32767)
    {
        FASTTABLE_LOG_DEBUG("Height for row #"+QString::number(row)+" in horizontal header is too big: "+QString::number(height)+". The maximum height is 32767");
        height=32767;
    }

    if (mHorizontalHeader_RowHeights.at(row)<0)
    {
        mHorizontalHeader_RowHeights[row]=-height;
    }
    else
    if (mHorizontalHeader_RowHeights.at(row)!=height)
    {
        int aDiff=height-mHorizontalHeader_RowHeights.at(row);

        mHorizontalHeader_RowHeights[row]=height;

        mHorizontalHeader_TotalHeight+=aDiff;
        mTotalHeight+=aDiff;

        FASTTABLE_ASSERT(mHorizontalHeader_TotalHeight>=0);
        FASTTABLE_ASSERT(mTotalHeight>=0);

        for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mHorizontalHeader_OffsetY.length());

            mHorizontalHeader_OffsetY[i]+=aDiff;

            FASTTABLE_ASSERT(mHorizontalHeader_OffsetY.at(i)>=0);
        }

        for (int i=0; i<mRowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mOffsetY.length());

            mOffsetY[i]+=aDiff;

            FASTTABLE_ASSERT(mOffsetY.at(i)>=0);
        }

        updateBarsRanges();
        updateVisibleRange();

        viewport()->update();
    }

    END_PROFILE;
}

int CustomFastTableWidget::totalWidth()
{
    FASTTABLE_DEBUG;
    return mTotalWidth;
}

int CustomFastTableWidget::totalHeight()
{
    FASTTABLE_DEBUG;
    return mTotalHeight;
}

int CustomFastTableWidget::verticalHeader_TotalWidth()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_TotalWidth;
}

int CustomFastTableWidget::horizontalHeader_TotalHeight()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_TotalHeight;
}

bool CustomFastTableWidget::columnVisible(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column<mColumnWidths.length());

    return mColumnWidths.at(column)>=0;
}

void CustomFastTableWidget::setColumnVisible(const int column, bool visible)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column<mColumnWidths.length());

    qint16 prevWidth=mColumnWidths.at(column);
    bool wasVisible=prevWidth>=0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            mColumnWidths[column]=0;

            if (prevWidth==0)
            {
                prevWidth=-10;
            }

            setColumnWidth(column, -prevWidth);
        }
        else
        {
            setColumnWidth(column, 0);
            mColumnWidths[column]=-prevWidth;
        }
    }

    END_PROFILE;
}

bool CustomFastTableWidget::rowVisible(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mRowHeights.length());

    return mRowHeights.at(row)>=0;
}

void CustomFastTableWidget::setRowVisible(const int row, bool visible)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row<mRowHeights.length());

    qint16 prevHeight=mRowHeights.at(row);
    bool wasVisible=prevHeight>=0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            mRowHeights[row]=0;

            if (prevHeight==0)
            {
                prevHeight=-10;
            }

            setRowHeight(row, -prevHeight);
        }
        else
        {
            setRowHeight(row, 0);
            mRowHeights[row]=-prevHeight;
        }
    }

    END_PROFILE;
}

bool CustomFastTableWidget::verticalHeader_ColumnVisible(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths.length());

    return mVerticalHeader_ColumnWidths.at(column)>=0;
}

void CustomFastTableWidget::verticalHeader_SetColumnVisible(const int column, bool visible)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths.length());

    qint16 prevWidth=mVerticalHeader_ColumnWidths.at(column);
    bool wasVisible=prevWidth>=0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            mVerticalHeader_ColumnWidths[column]=0;

            if (prevWidth==0)
            {
                prevWidth=-10;
            }

            verticalHeader_SetColumnWidth(column, -prevWidth);
        }
        else
        {
            verticalHeader_SetColumnWidth(column, 0);
            mVerticalHeader_ColumnWidths[column]=-prevWidth;
        }
    }

    END_PROFILE;
}

bool CustomFastTableWidget::horizontalHeader_RowVisible(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights.length());

    return mHorizontalHeader_RowHeights.at(row)>=0;
}

void CustomFastTableWidget::horizontalHeader_SetRowVisible(const int row, bool visible)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights.length());

    qint16 prevHeight=mHorizontalHeader_RowHeights.at(row);
    bool wasVisible=prevHeight>=0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            mHorizontalHeader_RowHeights[row]=0;

            if (prevHeight==0)
            {
                prevHeight=-10;
            }

            horizontalHeader_SetRowHeight(row, -prevHeight);
        }
        else
        {
            horizontalHeader_SetRowHeight(row, 0);
            mHorizontalHeader_RowHeights[row]=-prevHeight;
        }
    }

    END_PROFILE;
}

QRect CustomFastTableWidget::visibleRange()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    QRect aRect;
    aRect.setCoords(mVisibleLeft, mVisibleTop, mVisibleRight, mVisibleBottom);

    END_PROFILE;

    return aRect;
}

QRect CustomFastTableWidget::horizontalHeader_VisibleRange()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    QRect aRect;

    if (mHorizontalHeader_VisibleBottom>=0)
    {
        aRect.setCoords(mVisibleLeft, 0, mVisibleRight, mHorizontalHeader_VisibleBottom);
    }
    else
    {
        aRect.setCoords(-1, -1, -1, -1);
    }

    END_PROFILE;

    return aRect;
}

QRect CustomFastTableWidget::verticalHeader_VisibleRange()
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    QRect aRect;

    if (mVerticalHeader_VisibleRight>=0)
    {
        aRect.setCoords(0, mVisibleTop, mVerticalHeader_VisibleRight, mVisibleBottom);
    }
    else
    {
        aRect.setCoords(-1, -1, -1, -1);
    }

    END_PROFILE;

    return aRect;
}

QString CustomFastTableWidget::text(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mData.length());
    FASTTABLE_ASSERT(column>=0 && column<mData.at(row).length());

    return mData.at(row).at(column);
}

void CustomFastTableWidget::setText(const int row, const int column, const QString text)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mData.length());
    FASTTABLE_ASSERT(column>=0 && column<mData.at(row).length());

    mData[row][column]=text;

    viewport()->update();

    END_PROFILE;
}

QString CustomFastTableWidget::horizontalHeader_Text(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data.length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(row).length());

    return mHorizontalHeader_Data.at(row).at(column);
}

QString CustomFastTableWidget::horizontalHeader_Text(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(mHorizontalHeader_Data.length()>0);
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(0).length());

    return mHorizontalHeader_Data.at(0).at(column);
}

void CustomFastTableWidget::horizontalHeader_SetText(const int row, const int column, const QString text)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data.length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(row).length());

    mHorizontalHeader_Data[row][column]=text;

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_SetText(const int column, const QString text)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    for (int i=0; i<mHorizontalHeader_RowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_Data.length());
        FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(i).length());

        mHorizontalHeader_Data[i][column]=text;
    }

    viewport()->update();

    END_PROFILE;
}

QString CustomFastTableWidget::verticalHeader_Text(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data.at(row).length());

    return mVerticalHeader_Data.at(row).at(column);
}

QString CustomFastTableWidget::verticalHeader_Text(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(mVerticalHeader_Data.at(row).length()>0);

    return mVerticalHeader_Data.at(row).at(0);
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const int column, const QString text)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data.at(row).length());

    mVerticalHeader_Data[row][column]=text;

    viewport()->update();

    END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const QString text)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());

    for (int i=0; i<mVerticalHeader_ColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mVerticalHeader_Data.at(row).length());

        mVerticalHeader_Data[row][i]=text;
    }

    viewport()->update();

    END_PROFILE;
}

bool CustomFastTableWidget::cellSelected(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells.length());
    FASTTABLE_ASSERT(column>=0 && column<mSelectedCells.at(row).length());

    return mSelectedCells.at(row).at(column);
}

void CustomFastTableWidget::setCellSelected(const int row, const int column, const bool selected)
{
    FASTTABLE_DEBUG;
    START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells.length());
    FASTTABLE_ASSERT(column>=0 && column<mSelectedCells.at(row).length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows.length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns.length());

    if (mSelectedCells.at(row).at(column)!=selected)
    {
        mSelectedCells[row][column]=selected;

        if (selected)
        {
            mCurSelection.append(QPoint(column, row));

            mVerticalHeader_SelectedRows[row]=true;
            mHorizontalHeader_SelectedColumns[column]=true;
        }
        else
        {
            bool rowFound=false;
            bool columnFound=false;

            for (int i=0; i<mCurSelection.length(); ++i)
            {
                if (mCurSelection.at(i).y()==row)
                {
                    if (mCurSelection.at(i).x()==column)
                    {
                        mCurSelection.removeAt(i);
                        --i;

                        continue;
                    }

                    rowFound=true;
                }
                else
                {
                    if (mCurSelection.at(i).x()==column)
                    {
                        columnFound=true;
                    }
                }
            }

            mVerticalHeader_SelectedRows[row]=rowFound;
            mHorizontalHeader_SelectedColumns[column]=columnFound;
        }

        viewport()->update();
    }

    END_PROFILE;
}

QList<QPoint> CustomFastTableWidget::currentSelection()
{
    FASTTABLE_DEBUG;
    return mCurSelection;
}

bool CustomFastTableWidget::horizontalHeader_ColumnSelected(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns.length());

    return mHorizontalHeader_SelectedColumns.at(column);
}

bool CustomFastTableWidget::verticalHeader_RowSelected(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows.length());

    return mVerticalHeader_SelectedRows.at(row);
}
