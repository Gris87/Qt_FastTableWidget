#include "customfasttablewidget.h"

CustomFastTableWidget::CustomFastTableWidget(QWidget *parent) :
    QAbstractScrollArea(parent)
{
    START_PROFILE;

    mRowCount=0;
    mColumnCount=0;
    mHorizontalHeader_RowCount=0;
    mVerticalHeader_ColumnCount=0;

    mDefaultBackgroundBrush.setColor(QColor(255, 255, 255));
    mDefaultForegroundColor.setRgb(0, 0, 0);
    mGridColor.setRgb(0, 0, 0);

    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(180, 180, 180));
    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
    mHorizontalHeader_GridColor.setRgb(0, 0, 0);

    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(180, 180, 180));
    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
    mVerticalHeader_GridColor.setRgb(0, 0, 0);

    mSelectionBrush.setColor(QColor(0, 0, 255));

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

    horizontalScrollBar()->setSingleStep(100);
    verticalScrollBar()->setSingleStep(100);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollBarValueChanged(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(verticalScrollBarValueChanged(int)));

    END_PROFILE("CustomFastTableWidget::CustomFastTableWidget(QWidget *parent)");
}

CustomFastTableWidget::~CustomFastTableWidget()
{
    START_PROFILE;

    clearTable();

    END_PROFILE("CustomFastTableWidget::~CustomFastTableWidget()");
}

void CustomFastTableWidget::mousePressEvent(QMouseEvent *event)
{
    START_PROFILE;

    QAbstractScrollArea::mousePressEvent(event);

    END_PROFILE("void CustomFastTableWidget::mousePressEvent(QMouseEvent *event)");
}

void CustomFastTableWidget::resizeEvent(QResizeEvent *event)
{
    START_PROFILE;

    updateBarsRanges();
    updateVisibleRange();

    QAbstractScrollArea::resizeEvent(event);

    END_PROFILE("void CustomFastTableWidget::resizeEvent(QResizeEvent *event)");
}

void CustomFastTableWidget::paintEvent(QPaintEvent *event)
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
            paintCell(painter, offsetX+mOffsetX.at(j), offsetY+mOffsetY.at(i), mColumnWidths.at(j), mRowHeights.at(i), i, j, DrawCell);
        }
    }

    END_FREQUENT_PROFILE("void CustomFastTableWidget::paintEvent(QPaintEvent *event)");
}

void CustomFastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent)
{
    START_FREQUENT_PROFILE;

    QColor  *aGridColor;
    QBrush  *aBackgroundBrush;
    QColor  *aTextColor;
    QString *aText;

    switch (drawComponent)
    {
        case DrawCell:
        {
            aGridColor=&mGridColor;
            aBackgroundBrush=&mDefaultBackgroundBrush;
            aTextColor=&mDefaultForegroundColor;
            aText=&mData[row][column];
        }
        break;
        case DrawHorizontalHeaderCell:
        {
            aGridColor=&mHorizontalHeader_GridColor;
            aBackgroundBrush=&mHorizontalHeader_DefaultBackgroundBrush;
            aTextColor=&mHorizontalHeader_DefaultForegroundColor;
            aText=&mHorizontalHeader_Data[row][column];
        }
        break;
        case DrawVerticalHeaderCell:
        {
            aGridColor=&mVerticalHeader_GridColor;
            aBackgroundBrush=&mVerticalHeader_DefaultBackgroundBrush;
            aTextColor=&mVerticalHeader_DefaultForegroundColor;
            aText=&mVerticalHeader_Data[row][column];
        }
        break;
        case DrawTopLeftCorner:
        {
            aGridColor=&mHorizontalHeader_GridColor;
            aBackgroundBrush=&mHorizontalHeader_DefaultBackgroundBrush;
            aTextColor=0;
            aText=0;
        }
        break;
        default:
        {
            aGridColor=0;
            aBackgroundBrush=0;
            aTextColor=0;
            aText=0;
        }
        break;
    }

    painter.setPen(QPen(*aGridColor));
    painter.setFont(font());

    painter.fillRect(x, y, width, height, *aBackgroundBrush);
    painter.drawRect(x, y, width, height);

    if (aText)
    {
        painter.setPen(QPen(*aTextColor));
        painter.drawText(x+4, y+4, width-8, height-8, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, *aText);
    }

    END_FREQUENT_PROFILE("void CustomFastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int row, const int column)");
}

void CustomFastTableWidget::horizontalScrollBarValueChanged(int value)
{
    START_FREQUENT_PROFILE;

    updateVisibleRange();

    END_FREQUENT_PROFILE("void CustomFastTableWidget::horizontalScrollBarValueChanged(int value)");
}

void CustomFastTableWidget::verticalScrollBarValueChanged(int value)
{
    START_FREQUENT_PROFILE;

    updateVisibleRange();

    END_FREQUENT_PROFILE("void CustomFastTableWidget::verticalScrollBarValueChanged(int value)");
}

void CustomFastTableWidget::updateBarsRanges()
{
    START_PROFILE;

    QSize areaSize = viewport()->size();

    horizontalScrollBar()->setPageStep(mTotalWidth);
    verticalScrollBar()->setPageStep(mTotalHeight);

    horizontalScrollBar()->setRange(0, mTotalWidth  - areaSize.width()  + 1);
    verticalScrollBar()->setRange(0,   mTotalHeight - areaSize.height() + 1);

    END_PROFILE("void CustomFastTableWidget::updateBarsRanges()");
}

void CustomFastTableWidget::updateVisibleRange()
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
    }

    END_PROFILE("void CustomFastTableWidget::updateVisibleRange()");
}

void CustomFastTableWidget::clearTable()
{
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

    END_PROFILE("void CustomFastTableWidget::clearTable()");
}

void CustomFastTableWidget::selectRow(const int row)
{
    START_PROFILE;

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, true);
    }

    END_PROFILE("void CustomFastTableWidget::selectRow(const int row)");
}

void CustomFastTableWidget::unselectRow(const int row)
{
    START_PROFILE;

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, false);
    }

    END_PROFILE("void CustomFastTableWidget::unselectRow(const int row)");
}

void CustomFastTableWidget::selectColumn(const int column)
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, true);
    }

    END_PROFILE("void CustomFastTableWidget::selectColumn(const int column)");
}

void CustomFastTableWidget::unselectColumn(const int column)
{
    START_PROFILE;

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, false);
    }

    END_PROFILE("void CustomFastTableWidget::unselectColumn(const int column)");
}

void CustomFastTableWidget::selectAll()
{
    START_PROFILE;

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

    for (int i=0; i<mRowCount; ++i)
    {
        mVerticalHeader_SelectedRows[i]=true;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        mHorizontalHeader_SelectedColumns[i]=true;
    }

    END_PROFILE("void CustomFastTableWidget::selectAll()");
}

void CustomFastTableWidget::unselectAll()
{
    START_PROFILE;

    for (int i=0; i<mCurSelection.length(); ++i)
    {
        mSelectedCells[mCurSelection.at(i).y()][mCurSelection.at(i).x()]=false;
    }

    mCurSelection.clear();

    for (int i=0; i<mRowCount; ++i)
    {
        mVerticalHeader_SelectedRows[i]=false;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        mHorizontalHeader_SelectedColumns[i]=false;
    }

    END_PROFILE("void CustomFastTableWidget::unselectAll()");
}

void CustomFastTableWidget::addRow()
{
    START_PROFILE;

    insertRow(mRowCount);

    END_PROFILE("void CustomFastTableWidget::addRow()");
}

void CustomFastTableWidget::insertRow(int row)
{
    START_PROFILE;

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

    END_PROFILE("void CustomFastTableWidget::insertRow(int row)");
}

void CustomFastTableWidget::deleteRow(int row)
{
    START_PROFILE;

    int diff=mRowHeights.at(row);

    mTotalHeight-=diff;

    for (int i=row+1; i<mRowCount; ++i)
    {
        mOffsetY[i]-=diff;
    }

    mOffsetY.removeAt(row);
    mRowHeights.removeAt(row);

    mData.removeAt(row);
    mVerticalHeader_Data.removeAt(row);

    for (int i=0; i<mColumnCount; ++i)
    {
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

    END_PROFILE("void CustomFastTableWidget::deleteRow(int row)");
}

void CustomFastTableWidget::addColumn()
{
    START_PROFILE;

    insertColumn(mColumnCount);

    END_PROFILE("void CustomFastTableWidget::addColumn()");
}

void CustomFastTableWidget::insertColumn(int column)
{
    START_PROFILE;

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
        mHorizontalHeader_Data[i].insert(column, "");
    }

    for (int i=0; i<mData.length(); ++i)
    {
        mData[i].insert(column, "");
        mSelectedCells[i].insert(column, false);
    }

    mHorizontalHeader_SelectedColumns.insert(column, false);

    END_PROFILE("void CustomFastTableWidget::insertColumn(int column)");
}

void CustomFastTableWidget::deleteColumn(int column)
{
    START_PROFILE;

    int diff=mColumnWidths.at(column);

    mTotalWidth-=diff;

    for (int i=column+1; i<mColumnCount; ++i)
    {
        mOffsetX[i]-=diff;
    }

    mOffsetX.removeAt(column);
    mColumnWidths.removeAt(column);

    for (int i=0; i<mHorizontalHeader_Data.length(); ++i)
    {
        mHorizontalHeader_Data[i].removeAt(column);
    }

    for (int i=0; i<mData.length(); ++i)
    {
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

    END_PROFILE("void CustomFastTableWidget::deleteColumn(int column)");
}

void CustomFastTableWidget::horizontalHeader_AddRow()
{
    START_PROFILE;

    horizontalHeader_InsertRow(mHorizontalHeader_RowCount);

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_AddRow()");
}

void CustomFastTableWidget::horizontalHeader_InsertRow(int row)
{
    START_PROFILE;

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
        mOffsetY[i]+=mDefaultHeight;
    }

    mHorizontalHeader_Data.insert(row, aNewRow);

    for (int i=0; i<mColumnCount; ++i)
    {
        mHorizontalHeader_Data[row].append("");
    }

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_InsertRow(int row)");
}

void CustomFastTableWidget::horizontalHeader_DeleteRow(int row)
{
    START_PROFILE;

    int diff=mHorizontalHeader_RowHeights.at(row);

    mHorizontalHeader_TotalHeight-=diff;
    mTotalHeight-=diff;

    for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
    {
        mHorizontalHeader_OffsetY[i]-=diff;
    }

    for (int i=0; i<mRowCount; ++i)
    {
        mOffsetY[i]-=diff;
    }

    mHorizontalHeader_OffsetY.removeAt(row);
    mHorizontalHeader_RowHeights.removeAt(row);
    mHorizontalHeader_Data.removeAt(row);

    mHorizontalHeader_RowCount--;

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_DeleteRow(int row)");
}

void CustomFastTableWidget::verticalHeader_AddColumn()
{
    START_PROFILE;

    verticalHeader_InsertColumn(mVerticalHeader_ColumnCount);

    END_PROFILE("void CustomFastTableWidget::verticalHeader_AddColumn()");
}

void CustomFastTableWidget::verticalHeader_InsertColumn(int column)
{
    START_PROFILE;

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
        mOffsetX[i]+=mDefaultWidth;
    }

    for (int i=0; i<mVerticalHeader_Data.length(); ++i)
    {
        mVerticalHeader_Data[i].insert(column, "");
    }

    END_PROFILE("void CustomFastTableWidget::verticalHeader_InsertColumn(int column)");
}

void CustomFastTableWidget::verticalHeader_DeleteColumn(int column)
{
    START_PROFILE;

    int diff=mVerticalHeader_ColumnWidths.at(column);

    mVerticalHeader_TotalWidth-=diff;
    mTotalWidth-=diff;

    for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
    {
        mVerticalHeader_OffsetX[i]-=diff;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        mOffsetX[i]-=diff;
    }

    mVerticalHeader_OffsetX.removeAt(column);
    mVerticalHeader_ColumnWidths.removeAt(column);

    for (int i=0; i<mVerticalHeader_Data.length(); ++i)
    {
        mVerticalHeader_Data[i].removeAt(column);
    }

    mVerticalHeader_ColumnCount--;

    END_PROFILE("void CustomFastTableWidget::verticalHeader_DeleteColumn(int column)");
}

int CustomFastTableWidget::rowCount()
{
    return mRowCount;
}

void CustomFastTableWidget::setRowCount(int count)
{
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mRowCount!=count)
    {
        while (mRowCount<count)
        {
            addRow();
        }

        while (mRowCount>count)
        {
            deleteRow(mRowCount-1);
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::setRowCount(int count)");
}

int CustomFastTableWidget::columnCount()
{
    return mColumnCount;
}

void CustomFastTableWidget::setColumnCount(int count)
{
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mColumnCount!=count)
    {
        while (mColumnCount<count)
        {
            addColumn();
        }

        while (mColumnCount>count)
        {
            deleteColumn(mColumnCount-1);
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::setColumnCount(int count)");
}

qint16 CustomFastTableWidget::horizontalHeader_RowCount()
{
    return mHorizontalHeader_RowCount;
}

void CustomFastTableWidget::horizontalHeader_SetRowCount(qint16 count)
{
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mHorizontalHeader_RowCount!=count)
    {
        while (mHorizontalHeader_RowCount<count)
        {
            horizontalHeader_AddRow();
        }

        while (mHorizontalHeader_RowCount>count)
        {
            horizontalHeader_DeleteRow(mHorizontalHeader_RowCount-1);
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetRowCount(int count)");
}

qint16 CustomFastTableWidget::verticalHeader_ColumnCount()
{
    return mVerticalHeader_ColumnCount;
}

void CustomFastTableWidget::verticalHeader_SetColumnCount(qint16 count)
{
    START_PROFILE;

    if (count<0)
    {
        count=0;
    }

    if (mVerticalHeader_ColumnCount!=count)
    {
        while (mVerticalHeader_ColumnCount<count)
        {
            verticalHeader_AddColumn();
        }

        while (mVerticalHeader_ColumnCount>count)
        {
            verticalHeader_DeleteColumn(mVerticalHeader_ColumnCount-1);
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::verticalHeader_SetColumnCount(int count)");
}

QBrush CustomFastTableWidget::defaultBackgroundBrush()
{
    return mDefaultBackgroundBrush;
}

void CustomFastTableWidget::setDefaultBackgroundBrush(QBrush brush)
{
    START_PROFILE;

    mDefaultBackgroundBrush=brush;

    END_PROFILE("void CustomFastTableWidget::setDefaultBackgroundBrush(QBrush brush)");
}

QColor CustomFastTableWidget::defaultForegroundColor()
{
    return mDefaultForegroundColor;
}

void CustomFastTableWidget::setDefaultForegroundColor(QColor color)
{
    START_PROFILE;

    mDefaultForegroundColor=color;

    END_PROFILE("void CustomFastTableWidget::setDefaultForegroundColor(QColor color)");
}

QColor CustomFastTableWidget::gridColor()
{
    return mGridColor;
}

void CustomFastTableWidget::setGridColor(QColor color)
{
    START_PROFILE;

    mGridColor=color;

    END_PROFILE("void CustomFastTableWidget::setGridColor(QColor color)");
}

QBrush CustomFastTableWidget::horizontalHeader_DefaultBackgroundBrush()
{
    return mHorizontalHeader_DefaultBackgroundBrush;
}

void CustomFastTableWidget::horizontalHeader_SetDefaultBackgroundBrush(QBrush brush)
{
    START_PROFILE;

    mHorizontalHeader_DefaultBackgroundBrush=brush;

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetDefaultBackgroundBrush(QBrush brush)");
}

QColor CustomFastTableWidget::horizontalHeader_DefaultForegroundColor()
{
    return mHorizontalHeader_DefaultForegroundColor;
}

void CustomFastTableWidget::horizontalHeader_SetDefaultForegroundColor(QColor color)
{
    START_PROFILE;

    mHorizontalHeader_DefaultForegroundColor=color;

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetDefaultForegroundColor(QColor color)");
}

QColor CustomFastTableWidget::horizontalHeader_GridColor()
{
    return mHorizontalHeader_GridColor;
}

void CustomFastTableWidget::horizontalHeader_SetGridColor(QColor color)
{
    START_PROFILE;

    mHorizontalHeader_GridColor=color;

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetGridColor(QColor color)");
}

QBrush CustomFastTableWidget::verticalHeader_DefaultBackgroundBrush()
{
    return mVerticalHeader_DefaultBackgroundBrush;
}

void CustomFastTableWidget::verticalHeader_SetDefaultBackgroundBrush(QBrush brush)
{
    START_PROFILE;

    mVerticalHeader_DefaultBackgroundBrush=brush;

    END_PROFILE("void CustomFastTableWidget::verticalHeader_SetDefaultBackgroundBrush(QBrush brush)");
}

QColor CustomFastTableWidget::verticalHeader_DefaultForegroundColor()
{
    return mVerticalHeader_DefaultForegroundColor;
}

void CustomFastTableWidget::verticalHeader_SetDefaultForegroundColor(QColor color)
{
    START_PROFILE;

    mVerticalHeader_DefaultForegroundColor=color;

    END_PROFILE("void CustomFastTableWidget::verticalHeader_SetDefaultForegroundColor(QColor color)");
}

QColor CustomFastTableWidget::verticalHeader_GridColor()
{
    return mVerticalHeader_GridColor;
}

void CustomFastTableWidget::verticalHeader_SetGridColor(QColor color)
{
    START_PROFILE;

    mVerticalHeader_GridColor=color;

    END_PROFILE("void CustomFastTableWidget::verticalHeader_SetGridColor(QColor color)");
}

QBrush CustomFastTableWidget::selectionBrush()
{
    return mSelectionBrush;
}

void CustomFastTableWidget::setSelectionBrush(QBrush brush)
{
    START_PROFILE;

    mSelectionBrush=brush;

    END_PROFILE("void CustomFastTableWidget::setSelectionBrush(QBrush brush)");
}

quint16 CustomFastTableWidget::defaultWidth()
{
    return mDefaultWidth;
}

void CustomFastTableWidget::setDefaultWidth(quint16 width)
{
    START_PROFILE;

    mDefaultWidth=width;

    END_PROFILE("void CustomFastTableWidget::setDefaultWidth(quint16 width)");
}

quint16 CustomFastTableWidget::defaultHeight()
{
    return mDefaultHeight;
}

void CustomFastTableWidget::setDefaultHeight(quint16 height)
{
    START_PROFILE;

    mDefaultHeight=height;

    END_PROFILE("void CustomFastTableWidget::setDefaultHeight(quint16 height)");
}

quint16 CustomFastTableWidget::columnWidth(const int column)
{
    return mColumnWidths.at(column);
}

void CustomFastTableWidget::setColumnWidth(const int column, const quint16 width)
{
    START_PROFILE;

    if (mColumnWidths.at(column)!=width)
    {
        int aDiff=width-mColumnWidths.at(column);

        mColumnWidths[column]=width;

        mTotalWidth+=aDiff;

        for (int i=column+1; i<mColumnCount; ++i)
        {
            mOffsetX[i]+=aDiff;
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::setColumnWidth(const int column, const quint16 width)");
}

quint16 CustomFastTableWidget::rowHeight(const int row)
{
    return mRowHeights.at(row);
}

void CustomFastTableWidget::setRowHeight(const int row, const quint16 height)
{
    START_PROFILE;

    if (mRowHeights.at(row)!=height)
    {
        int aDiff=height-mRowHeights.at(row);

        mRowHeights[row]=height;

        mTotalHeight+=aDiff;

        for (int i=row+1; i<mRowCount; ++i)
        {
            mOffsetY[i]+=aDiff;
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::setRowHeight(const int row, const quint16 height)");
}

quint16 CustomFastTableWidget::verticalHeader_ColumnWidth(const int column)
{
    return mVerticalHeader_ColumnWidths.at(column);
}

void CustomFastTableWidget::verticalHeader_SetColumnWidth(const int column, const quint16 width)
{
    START_PROFILE;

    if (mVerticalHeader_ColumnWidths.at(column)!=width)
    {
        int aDiff=width-mVerticalHeader_ColumnWidths.at(column);

        mVerticalHeader_ColumnWidths[column]=width;

        mVerticalHeader_TotalWidth+=aDiff;
        mTotalWidth+=aDiff;

        for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
        {
            mVerticalHeader_OffsetX[i]+=aDiff;
        }

        for (int i=0; i<mColumnCount; ++i)
        {
            mOffsetX[i]+=aDiff;
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::setColumnWidth(const int column, const quint16 width)");
}

quint16 CustomFastTableWidget::horizontalHeader_RowHeight(const int row)
{
    return mHorizontalHeader_RowHeights.at(row);
}

void CustomFastTableWidget::horizontalHeader_SetRowHeight(const int row, const quint16 height)
{
    START_PROFILE;

    if (mHorizontalHeader_RowHeights.at(row)!=height)
    {
        int aDiff=height-mHorizontalHeader_RowHeights.at(row);

        mHorizontalHeader_RowHeights[row]=height;

        mHorizontalHeader_TotalHeight+=aDiff;
        mTotalHeight+=aDiff;

        for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
        {
            mHorizontalHeader_OffsetY[i]+=aDiff;
        }

        for (int i=0; i<mRowCount; ++i)
        {
            mOffsetY[i]+=aDiff;
        }

        updateBarsRanges();
        updateVisibleRange();
    }

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetRowHeight(const int row, const quint16 height)");
}

int CustomFastTableWidget::totalWidth()
{
    return mTotalWidth;
}

int CustomFastTableWidget::totalHeight()
{
    return mTotalHeight;
}

int CustomFastTableWidget::verticalHeader_TotalWidth()
{
    return mVerticalHeader_TotalWidth;
}

int CustomFastTableWidget::horizontalHeader_TotalHeight()
{
    return mHorizontalHeader_TotalHeight;
}

QRect CustomFastTableWidget::visibleRange()
{
    START_PROFILE;

    QRect aRect;
    aRect.setCoords(mVisibleLeft, mVisibleTop, mVisibleRight, mVisibleBottom);

    END_PROFILE("QRect CustomFastTableWidget::visibleRange()");

    return aRect;
}

QRect CustomFastTableWidget::horizontalHeader_VisibleRange()
{
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

    END_PROFILE("QRect CustomFastTableWidget::horizontalHeader_VisibleRange()");

    return aRect;
}

QRect CustomFastTableWidget::verticalHeader_VisibleRange()
{
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

    END_PROFILE("QRect CustomFastTableWidget::verticalHeader_VisibleRange()");

    return aRect;
}

QString CustomFastTableWidget::text(const int row, const int column)
{
    return mData.at(row).at(column);
}

void CustomFastTableWidget::setText(const int row, const int column, const QString text)
{
    START_FREQUENT_PROFILE;

    mData[row][column]=text;

    END_FREQUENT_PROFILE("void CustomFastTableWidget::setText(const int row, const int column, const QString text)");
}

QString CustomFastTableWidget::horizontalHeader_Text(const int row, const int column)
{
    return mHorizontalHeader_Data.at(row).at(column);
}

QString CustomFastTableWidget::horizontalHeader_Text(const int column)
{
    return mHorizontalHeader_Data.at(0).at(column);
}

void CustomFastTableWidget::horizontalHeader_SetText(const int row, const int column, const QString text)
{
    START_PROFILE;

    mHorizontalHeader_Data[row][column]=text;

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetText(const int row, const int column, const QString text)");
}

void CustomFastTableWidget::horizontalHeader_SetText(const int column, const QString text)
{
    START_PROFILE;

    for (int i=0; i<mHorizontalHeader_RowCount; i++)
    {
        mHorizontalHeader_Data[i][column]=text;
    }

    END_PROFILE("void CustomFastTableWidget::horizontalHeader_SetText(const int column, const QString text)");
}

QString CustomFastTableWidget::verticalHeader_Text(const int row, const int column)
{
    return mVerticalHeader_Data.at(row).at(column);
}

QString CustomFastTableWidget::verticalHeader_Text(const int row)
{
    return mVerticalHeader_Data.at(row).at(0);
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const int column, const QString text)
{
    START_PROFILE;

    mVerticalHeader_Data[row][column]=text;

    END_PROFILE("void CustomFastTableWidget::verticalHeader_SetText(const int row, const int column, const QString text)");
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const QString text)
{
    START_PROFILE;

    for (int i=0; i<mVerticalHeader_ColumnCount; i++)
    {
        mVerticalHeader_Data[row][i]=text;
    }

    END_PROFILE("void CustomFastTableWidget::verticalHeader_SetText(const int row, const QString text)");
}

bool CustomFastTableWidget::cellSelected(const int row, const int column)
{
    return mSelectedCells.at(row).at(column);
}

void CustomFastTableWidget::setCellSelected(const int row, const int column, const bool selected)
{
    START_PROFILE;

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

    END_PROFILE("void CustomFastTableWidget::setCellSelected(const int row, const int column, const bool selected)");
}
