#include "customfasttablewidget.h"

CustomFastTableWidget::CustomFastTableWidget(QWidget *parent) :
    QAbstractScrollArea(parent),
    mMouseEvent(QEvent::MouseMove, QPoint(0, 0), Qt::NoButton, Qt::NoButton, Qt::NoModifier)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    mCurrentRow=-1;
    mCurrentColumn=-1;

    mMousePressed=false;
    mCtrlPressed=false;
    mShiftPressed=false;
    mMouseLocation=InMiddleWorld;
    mMouseLocationForShift=InMiddleWorld;
    mLastX=-1;
    mLastY=-1;
    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseResizeLineX=-1;
    mMouseResizeLineY=-1;
    mMouseResizeCell=-1;

    mStyle=StyleSimple;

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

    setMouseTracking(true);

    horizontalScrollBar()->setSingleStep(100);
    verticalScrollBar()->setSingleStep(100);

    mMouseHoldTimer.setInterval(5);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged(int)));

    connect(&mMouseHoldTimer, SIGNAL(timeout()), this, SLOT(mouseHoldTick()));

    FASTTABLE_END_PROFILE;
}

CustomFastTableWidget::~CustomFastTableWidget()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    clear();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::keyPressEvent(QKeyEvent *event)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    if (event->key()==Qt::Key_Up)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (mCurrentRow>0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, mCurrentRow-1);
                }
                else
                {
                    setCurrentCell(mCurrentRow-1, mCurrentColumn);

                    initShiftSelection();
                }
            }
        }

        scrollToCurrentCell();
    }
    else
    if (event->key()==Qt::Key_Down)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (mCurrentRow<mRowCount-1)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, mCurrentRow+1);
                }
                else
                {
                    setCurrentCell(mCurrentRow+1, mCurrentColumn);

                    initShiftSelection();
                }
            }
        }

        scrollToCurrentCell();
    }
    else
    if (event->key()==Qt::Key_Left)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (mCurrentColumn>0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn-1, mCurrentRow);
                }
                else
                {
                    setCurrentCell(mCurrentRow, mCurrentColumn-1);

                    initShiftSelection();
                }
            }
        }

        scrollToCurrentCell();
    }
    else
    if (event->key()==Qt::Key_Right)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (mCurrentColumn<mColumnCount-1)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn+1, mCurrentRow);
                }
                else
                {
                    setCurrentCell(mCurrentRow, mCurrentColumn+1);

                    initShiftSelection();
                }
            }
        }

        scrollToCurrentCell();
    }
    else
    if (event->key()==Qt::Key_PageUp)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (mCurrentRow>0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    if (mCurrentRow>10)
                    {
                        selectRangeForHandlers(mCurrentColumn, mCurrentRow-10);
                    }
                    else
                    {
                        selectRangeForHandlers(mCurrentColumn, 0);
                    }
                }
                else
                {
                    if (mCurrentRow>10)
                    {
                        setCurrentCell(mCurrentRow-10, mCurrentColumn);
                    }
                    else
                    {
                        setCurrentCell(0, mCurrentColumn);
                    }

                    initShiftSelection();
                }
            }
        }

        scrollToCurrentCell();
    }
    else
    if (event->key()==Qt::Key_PageDown)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (mCurrentRow<mRowCount-1)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    if (mCurrentRow<mRowCount-10)
                    {
                        selectRangeForHandlers(mCurrentColumn, mCurrentRow+10);
                    }
                    else
                    {
                        selectRangeForHandlers(mCurrentColumn, mRowCount-1);
                    }
                }
                else
                {
                    if (mCurrentRow<mRowCount-10)
                    {
                        setCurrentCell(mCurrentRow+10, mCurrentColumn);
                    }
                    else
                    {
                        setCurrentCell(mRowCount-1, mCurrentColumn);
                    }

                    initShiftSelection();
                }
            }
        }

        scrollToCurrentCell();
    }
    else
    if (event->key()==Qt::Key_Home)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(0, 0);

            initShiftSelection();
        }
        else
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                initShiftSelectionForKeyboard();

                selectRangeForHandlers(mCurrentColumn, 0);
            }
            else
            {
                setCurrentCell(0, mCurrentColumn);

                initShiftSelection();
            }
        }

        scrollToTop();
    }
    else
    if (event->key()==Qt::Key_End)
    {
        if (mCurrentRow<0 || mCurrentColumn<0)
        {
            setCurrentCell(mRowCount-1, 0);

            initShiftSelection();
        }
        else
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                initShiftSelectionForKeyboard();

                selectRangeForHandlers(mCurrentColumn, mRowCount-1);
            }
            else
            {
                setCurrentCell(mRowCount-1, mCurrentColumn);

                initShiftSelection();
            }
        }

        scrollToBottom();
    }
    else
    if (event==QKeySequence::SelectAll)
    {
        selectAll();
    }
    else
    if (event==QKeySequence::Copy)
    {
        if (mCurSelection.length()>0)
        {
            QRect aCopyRect=selectedRanges().at(0);
            QString toClipboard="";

            for (int i=aCopyRect.top(); i<=aCopyRect.bottom(); i++)
            {
                if (toClipboard!="")
                {
                    toClipboard.append("\n");
                }

                QString aRow="";

                for (int j=aCopyRect.left(); j<=aCopyRect.right(); j++)
                {
                    if (aRow!="")
                    {
                        aRow.append("\t");
                    }

                    aRow.append(mData.at(i).at(j));
                }

                toClipboard.append(aRow);
            }

            QApplication::clipboard()->setText(toClipboard);
        }
    }
    else
    {
        QAbstractScrollArea::keyPressEvent(event);
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::mousePressEvent(QMouseEvent *event)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    int x=event->x();
    int y=event->y();

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    QPoint pos;

    pos=cellAt(x, y);

    if (pos!=QPoint(-1, -1))
    {
        mMousePressed=true;
        mMouseLocation=InCell;
        mCtrlPressed=event->modifiers() & Qt::ControlModifier;
        mShiftPressed=event->modifiers() & Qt::ShiftModifier;

        if (mShiftPressed && event->button()==Qt::LeftButton)
        {
            if (mMouseLocationForShift!=mMouseLocation)
            {
                mMouseLocationForShift=mMouseLocation;
                unselectAll();
                mMouseSelectedCells.clear();

                if (mMouseXForShift>=0 && mMouseYForShift>=0)
                {
                    setCurrentCell(mMouseYForShift, mMouseXForShift);
                }
            }

            if (mMouseXForShift<0 || mMouseYForShift<0)
            {
                if (mCurrentColumn<0 || mCurrentRow<0)
                {
                    setCurrentCell(0, 0);
                }

                initShiftSelection();
            }

            mLastX=mMouseXForShift;
            mLastY=mMouseYForShift;

            fillShiftSelection();

            selectRangeForHandlers(pos.x(), pos.y());
        }
        else
        {
            mLastX=pos.x();
            mLastY=pos.y();

            if (event->button()==Qt::LeftButton)
            {
                mMouseSelectedCells.clear();

                mMouseXForShift=mLastX;
                mMouseYForShift=mLastY;

                mMouseLocationForShift=mMouseLocation;

                if (mCtrlPressed)
                {
                    setCurrentCell(mLastY, mLastX, true);

                    FASTTABLE_ASSERT(mLastY>=0 && mLastY<mSelectedCells.length());
                    FASTTABLE_ASSERT(mLastX>=0 && mLastX<mSelectedCells.at(mLastY).length());

                    setCellSelected(mLastY, mLastX, !mSelectedCells.at(mLastY).at(mLastX));
                }
                else
                {
                    setCurrentCell(mLastY, mLastX);
                }

                QList<bool> aRow;
                aRow.append(mSelectedCells.at(mLastY).at(mLastX));

                mMouseSelectedCells.append(aRow);
            }
            else
            {
                if (!mSelectedCells.at(mLastY).at(mLastX))
                {
                    mMouseSelectedCells.clear();

                    mMouseXForShift=mLastX;
                    mMouseYForShift=mLastY;

                    mMouseLocationForShift=mMouseLocation;

                    setCurrentCell(mLastY, mLastX);
                }
            }
        }
    }
    else
    {
        pos=horizontalHeader_CellAt(x, y);

        if (pos!=QPoint(-1, -1))
        {
            mMousePressed=true;
            mMouseLocation=InHorizontalHeaderCell;
            mLastX=pos.x();
            mLastY=pos.y();
            mCtrlPressed=event->modifiers() & Qt::ControlModifier;
            mShiftPressed=event->modifiers() & Qt::ShiftModifier;

            if (
                !mCtrlPressed
                &&
                !mShiftPressed
                &&
                (
                 x<offsetX+mOffsetX.at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                 ||
                 x>offsetX+mOffsetX.at(mLastX)+mColumnWidths.at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                )
               )
            {
                mMouseResizeCell=mVerticalHeader_ColumnCount+mLastX;

                if (x<offsetX+mOffsetX.at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                {
                    mMouseResizeCell--;

                    if (mLastX==0)
                    {
                        mMouseResizeLineX=mVerticalHeader_TotalWidth;
                    }
                    else
                    {
                        mMouseResizeLineX=mOffsetX.at(mLastX-1)+mColumnWidths.at(mLastX-1);
                    }
                }
                else
                {
                    mMouseResizeLineX=mOffsetX.at(mLastX)+mColumnWidths.at(mLastX);
                }

                viewport()->update();
            }
            else
            if (
                !mCtrlPressed
                &&
                !mShiftPressed
                &&
                (
                 (
                  mLastY>0
                  &&
                  y<mHorizontalHeader_OffsetY.at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                 )
                 ||
                 y>mHorizontalHeader_OffsetY.at(mLastY)+mHorizontalHeader_RowHeights.at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                )
               )
            {
                mMouseResizeCell=mLastY;

                if (y<mHorizontalHeader_OffsetY.at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                {
                    mMouseResizeCell--;
                }

                mMouseResizeLineY=mHorizontalHeader_OffsetY.at(mMouseResizeCell)+mHorizontalHeader_RowHeights.at(mMouseResizeCell);

                viewport()->update();
            }
            else
            {
                if (mShiftPressed && event->button()==Qt::LeftButton)
                {
                    if (mMouseLocationForShift!=mMouseLocation)
                    {
                        mMouseLocationForShift=mMouseLocation;
                        unselectAll();
                        mMouseSelectedCells.clear();
                    }

                    if (mMouseXForShift<0 || mMouseYForShift<0)
                    {
                        if (mCurrentColumn<0 || mCurrentRow<0)
                        {
                            setCurrentCell(0, 0);
                        }

                        initShiftSelection();
                    }

                    mLastX=mMouseXForShift;
                    mLastY=mMouseYForShift;

                    if (mMouseSelectedCells.length()==0)
                    {
                        int minX=qMin(mCurrentColumn, mLastX);
                        int maxX=qMax(mCurrentColumn, mLastX);

                        for (int i=0; i<mRowCount; i++)
                        {
                            QList<bool> aRow;

                            for (int j=minX; j<=maxX; j++)
                            {
                                aRow.append(j==mLastX || mSelectedCells.at(i).at(j));
                            }

                            mMouseSelectedCells.append(aRow);
                        }
                    }

                    horizontalHeader_SelectRangeForHandlers(pos.x());
                }
                else
                {
                    mMouseSelectedCells.clear();

                    mMouseXForShift=mLastX;
                    mMouseYForShift=mLastY;

                    mMouseLocationForShift=mMouseLocation;

                    if (mCtrlPressed && event->button()==Qt::LeftButton)
                    {
                        setCurrentCell(mRowCount-1, mLastX, true);

                        FASTTABLE_ASSERT(mSelectedCells.length()>0);
                        FASTTABLE_ASSERT(mLastX>=0 && mLastX<mSelectedCells.at(0).length());

                        if (mSelectedCells.at(0).at(mLastX))
                        {
                            unselectColumn(mLastX);
                        }
                        else
                        {
                            selectColumn(mLastX);
                        }
                    }
                    else
                    {
                        setCurrentCell(mRowCount-1, mLastX);
                        selectColumn(mLastX);
                    }

                    for (int i=0; i<mRowCount; i++)
                    {
                        QList<bool> aRow;
                        aRow.append(mSelectedCells.at(i).at(mLastX));

                        mMouseSelectedCells.append(aRow);
                    }

                    viewport()->update();
                }
            }
        }
        else
        {
            pos=verticalHeader_CellAt(x, y);

            if (pos!=QPoint(-1, -1))
            {
                mMousePressed=true;
                mMouseLocation=InVerticalHeaderCell;
                mLastX=pos.x();
                mLastY=pos.y();
                mCtrlPressed=event->modifiers() & Qt::ControlModifier;
                mShiftPressed=event->modifiers() & Qt::ShiftModifier;

                if (
                    !mCtrlPressed
                    &&
                    !mShiftPressed
                    &&
                    (
                     (
                      mLastX>0 && x<mVerticalHeader_OffsetX.at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                     )
                     ||
                     x>mVerticalHeader_OffsetX.at(mLastX)+mVerticalHeader_ColumnWidths.at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    )
                   )
                {
                    mMouseResizeCell=mLastX;

                    if (x<mVerticalHeader_OffsetX.at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                    {
                        mMouseResizeCell--;
                    }

                    mMouseResizeLineX=mVerticalHeader_OffsetX.at(mMouseResizeCell)+mVerticalHeader_ColumnWidths.at(mMouseResizeCell);

                    viewport()->update();
                }
                else
                if (
                    !mCtrlPressed
                    &&
                    !mShiftPressed
                    &&
                    (
                     y<offsetY+mOffsetY.at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                     ||
                     y>offsetY+mOffsetY.at(mLastY)+mRowHeights.at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    )
                   )
                {
                    mMouseResizeCell=mHorizontalHeader_RowCount+mLastY;

                    if (y<offsetY+mOffsetY.at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                    {
                        mMouseResizeCell--;

                        if (mLastY==0)
                        {
                            mMouseResizeLineY=mHorizontalHeader_TotalHeight;
                        }
                        else
                        {
                            mMouseResizeLineY=mOffsetY.at(mLastY-1)+mRowHeights.at(mLastY-1);
                        }
                    }
                    else
                    {
                        mMouseResizeLineY=mOffsetY.at(mLastY)+mRowHeights.at(mLastY);
                    }

                    viewport()->update();
                }
                else
                {
                    if (mShiftPressed && event->button()==Qt::LeftButton)
                    {
                        if (mMouseLocationForShift!=mMouseLocation)
                        {
                            mMouseLocationForShift=mMouseLocation;
                            unselectAll();
                            mMouseSelectedCells.clear();
                        }

                        if (mMouseXForShift<0 || mMouseYForShift<0)
                        {
                            if (mCurrentColumn<0 || mCurrentRow<0)
                            {
                                setCurrentCell(0, 0);
                            }

                            initShiftSelection();
                        }

                        mLastX=mMouseXForShift;
                        mLastY=mMouseYForShift;

                        if (mMouseSelectedCells.length()==0)
                        {
                            int minY=qMin(mCurrentRow, mLastY);
                            int maxY=qMax(mCurrentRow, mLastY);

                            for (int i=minY; i<=maxY; i++)
                            {
                                QList<bool> aRow;

                                for (int j=0; j<mColumnCount; j++)
                                {
                                    aRow.append(i==mLastY || mSelectedCells.at(i).at(j));
                                }

                                mMouseSelectedCells.append(aRow);
                            }
                        }

                        verticalHeader_SelectRangeForHandlers(pos.y());
                    }
                    else
                    {
                        mMouseSelectedCells.clear();

                        mMouseXForShift=mLastX;
                        mMouseYForShift=mLastY;

                        mMouseLocationForShift=mMouseLocation;

                        if (mCtrlPressed && event->button()==Qt::LeftButton)
                        {
                            setCurrentCell(mLastY, mColumnCount-1, true);

                            FASTTABLE_ASSERT(mLastY>=0 && mLastY<mSelectedCells.length());
                            FASTTABLE_ASSERT(mSelectedCells.at(mLastY).length()>0);

                            if (mSelectedCells.at(mLastY).at(0))
                            {
                                unselectRow(mLastY);
                            }
                            else
                            {
                                selectRow(mLastY);
                            }
                        }
                        else
                        {
                            setCurrentCell(mLastY, mColumnCount-1);
                            selectRow(mLastY);
                        }

                        QList<bool> aRow;

                        for (int i=0; i<mColumnCount; i++)
                        {
                            aRow.append(mSelectedCells.at(mLastY).at(i));
                        }

                        mMouseSelectedCells.append(aRow);

                        viewport()->update();
                    }
                }
            }
            else
            if (atTopLeftCorner(x, y))
            {
                mMousePressed=true;
                mMouseLocation=InTopLeftCorner;
                mLastX=0;
                mLastY=0;
                mCtrlPressed=event->modifiers() & Qt::ControlModifier;
                mShiftPressed=event->modifiers() & Qt::ShiftModifier;

                if (
                    !mCtrlPressed
                    &&
                    !mShiftPressed
                    &&
                    x>mVerticalHeader_TotalWidth-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                   )
                {
                    mMouseResizeCell=mVerticalHeader_ColumnCount-1;
                    mMouseResizeLineX=mVerticalHeader_TotalWidth;

                    viewport()->update();
                }
                else
                if (
                    !mCtrlPressed
                    &&
                    !mShiftPressed
                    &&
                    y>mHorizontalHeader_TotalHeight-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                   )
                {
                    mMouseResizeCell=mHorizontalHeader_RowCount-1;
                    mMouseResizeLineY=mHorizontalHeader_TotalHeight;

                    viewport()->update();
                }
                else
                {
                    viewport()->update();
                }
            }
        }
    }

    QAbstractScrollArea::mousePressEvent(event);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::mouseMoveEvent(QMouseEvent *event)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    int x=event->x();
    int y=event->y();

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    if (mMousePressed && event->buttons() & Qt::LeftButton)
    {
        QSize areaSize=viewport()->size();

        bool needHold=false;

        if (x<10 && mMouseResizeCell<0)
        {
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()-FASTTABLE_MOUSE_HOLD_SCROLL_SPEED);
            needHold=true;
        }
        else
        if (x>areaSize.width()-10 && mMouseResizeCell<0)
        {
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()+FASTTABLE_MOUSE_HOLD_SCROLL_SPEED);
            needHold=true;
        }

        if (y<10 && mMouseResizeCell<0)
        {
            verticalScrollBar()->setValue(verticalScrollBar()->value()-FASTTABLE_MOUSE_HOLD_SCROLL_SPEED);
            needHold=true;
        }
        else
        if (y>areaSize.height()-10 && mMouseResizeCell<0)
        {
            verticalScrollBar()->setValue(verticalScrollBar()->value()+FASTTABLE_MOUSE_HOLD_SCROLL_SPEED);
            needHold=true;
        }

        mMouseHoldTimer.stop();

        if (needHold)
        {
            mMouseHoldTimer.start();
            mMouseEvent=*event;
        }

        if (mMouseLocation==InCell)
        {
            int resX=mCurrentColumn;
            int resY=mCurrentRow;

            while (resX>0 && x<offsetX+mOffsetX.at(resX) && (mColumnWidths.at(resX)<=0 || x<offsetX+mOffsetX.at(resX)+mColumnWidths.at(resX)))
            {
                resX--;
            }

            while (resX<mColumnCount-1 && x>offsetX+mOffsetX.at(resX) && (mColumnWidths.at(resX)<=0 || x>offsetX+mOffsetX.at(resX)+mColumnWidths.at(resX)))
            {
                resX++;
            }

            while (resY>0 && y<offsetY+mOffsetY.at(resY) && (mRowHeights.at(resY)<=0 || y<offsetY+mOffsetY.at(resY)+mRowHeights.at(resY)))
            {
                resY--;
            }

            while (resY<mRowCount-1 && y>offsetY+mOffsetY.at(resY) && (mRowHeights.at(resY)<=0 || y>offsetY+mOffsetY.at(resY)+mRowHeights.at(resY)))
            {
                resY++;
            }

            if (resX!=mCurrentColumn || resY!=mCurrentRow)
            {
                selectRangeForHandlers(resX, resY);
            }
        }
        else
        {
            if (mMouseResizeLineX>=0)
            {
                mMouseResizeLineX=-offsetX+x;

                int newWidth;

                if (mMouseResizeCell>=mVerticalHeader_ColumnCount)
                {
                    newWidth=mMouseResizeLineX-mOffsetX.at(mMouseResizeCell-mVerticalHeader_ColumnCount);
                }
                else
                {
                    newWidth=offsetX+mMouseResizeLineX-mVerticalHeader_OffsetX.at(mMouseResizeCell);
                }

                if (newWidth<FASTTABLE_MOUSE_RESIZE_MINIMUM_WIDTH)
                {
                    mMouseResizeLineX-=newWidth-FASTTABLE_MOUSE_RESIZE_MINIMUM_WIDTH;
                    newWidth=FASTTABLE_MOUSE_RESIZE_MINIMUM_WIDTH;
                }
                else
                if (newWidth>32767)
                {
                    mMouseResizeLineX-=newWidth-32767;
                    newWidth=32767;
                }

                if (mMouseResizeCell>=mVerticalHeader_ColumnCount)
                {
                    setColumnWidth(mMouseResizeCell-mVerticalHeader_ColumnCount, newWidth);
                }
                else
                {
                    verticalHeader_SetColumnWidth(mMouseResizeCell, newWidth);
                }

                viewport()->update();
            }
            else
            if (mMouseResizeLineY>=0)
            {
                mMouseResizeLineY=-offsetY+y;

                int newHeight;

                if (mMouseResizeCell>=mHorizontalHeader_RowCount)
                {
                    newHeight=mMouseResizeLineY-mOffsetY.at(mMouseResizeCell-mHorizontalHeader_RowCount);
                }
                else
                {
                    newHeight=offsetY+mMouseResizeLineY-mHorizontalHeader_OffsetY.at(mMouseResizeCell);
                }

                if (newHeight<FASTTABLE_MOUSE_RESIZE_MINIMUM_HEIGHT)
                {
                    mMouseResizeLineY-=newHeight-FASTTABLE_MOUSE_RESIZE_MINIMUM_HEIGHT;
                    newHeight=FASTTABLE_MOUSE_RESIZE_MINIMUM_HEIGHT;
                }
                else
                if (newHeight>32767)
                {
                    mMouseResizeLineY-=newHeight-32767;
                    newHeight=32767;
                }

                if (mMouseResizeCell>=mHorizontalHeader_RowCount)
                {
                    setRowHeight(mMouseResizeCell-mHorizontalHeader_RowCount, newHeight);
                }
                else
                {
                    horizontalHeader_SetRowHeight(mMouseResizeCell, newHeight);
                }

                viewport()->update();
            }
            else
            {
                if (mMouseLocation==InHorizontalHeaderCell)
                {
                    int resX=mCurrentColumn;

                    while (resX>0 && x<offsetX+mOffsetX.at(resX) && (mColumnWidths.at(resX)<=0 || x<offsetX+mOffsetX.at(resX)+mColumnWidths.at(resX)))
                    {
                        resX--;
                    }

                    while (resX<mColumnCount-1 && x>offsetX+mOffsetX.at(resX) && (mColumnWidths.at(resX)<=0 || x>offsetX+mOffsetX.at(resX)+mColumnWidths.at(resX)))
                    {
                        resX++;
                    }

                    if (resX!=mCurrentColumn)
                    {
                        horizontalHeader_SelectRangeForHandlers(resX);
                    }
                }
                else
                if (mMouseLocation==InVerticalHeaderCell)
                {
                    int resY=mCurrentRow;

                    while (resY>0 && y<offsetY+mOffsetY.at(resY) && (mRowHeights.at(resY)<=0 || y<offsetY+mOffsetY.at(resY)+mRowHeights.at(resY)))
                    {
                        resY--;
                    }

                    while (resY<mRowCount-1 && y>offsetY+mOffsetY.at(resY) && (mRowHeights.at(resY)<=0 || y>offsetY+mOffsetY.at(resY)+mRowHeights.at(resY)))
                    {
                        resY++;
                    }

                    if (resY!=mCurrentRow)
                    {
                        verticalHeader_SelectRangeForHandlers(resY);
                    }
                }
            }
        }
    }
    else
    {
        if (event->buttons()==Qt::NoButton)
        {
            QPoint pos;

            pos=horizontalHeader_CellAt(x, y);

            if (pos!=QPoint(-1, -1))
            {
                if (mMouseLocation!=InHorizontalHeaderCell || mLastX!=pos.x() || mLastY!=pos.y())
                {
                    mMouseLocation=InHorizontalHeaderCell;
                    mLastX=pos.x();
                    mLastY=pos.y();

                    viewport()->update();
                }

                if (
                    x<offsetX+mOffsetX.at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    ||
                    x>offsetX+mOffsetX.at(mLastX)+mColumnWidths.at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                   )
                {
                    setCursor(Qt::SplitHCursor);
                }
                else
                if (
                    (
                     mLastY>0 && y<mHorizontalHeader_OffsetY.at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    )
                    ||
                    y>mHorizontalHeader_OffsetY.at(mLastY)+mHorizontalHeader_RowHeights.at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                   )
                {
                    setCursor(Qt::SplitVCursor);
                }
                else
                {
                    setCursor(Qt::ArrowCursor);
                }
            }
            else
            {
                pos=verticalHeader_CellAt(x, y);

                if (pos!=QPoint(-1, -1))
                {
                    if (mMouseLocation!=InVerticalHeaderCell || mLastX!=pos.x() || mLastY!=pos.y())
                    {
                        mMouseLocation=InVerticalHeaderCell;
                        mLastX=pos.x();
                        mLastY=pos.y();

                        viewport()->update();
                    }

                    if (
                        (
                         mLastX>0 && x<mVerticalHeader_OffsetX.at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                        )
                        ||
                        x>mVerticalHeader_OffsetX.at(mLastX)+mVerticalHeader_ColumnWidths.at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                       )
                    {
                        setCursor(Qt::SplitHCursor);
                    }
                    else
                    if (
                        y<offsetY+mOffsetY.at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                        ||
                        y>offsetY+mOffsetY.at(mLastY)+mRowHeights.at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                       )
                    {
                        setCursor(Qt::SplitVCursor);
                    }
                    else
                    {
                        setCursor(Qt::ArrowCursor);
                    }
                }
                else
                if (atTopLeftCorner(x, y))
                {
                    if (mMouseLocation!=InTopLeftCorner)
                    {
                        mMouseLocation=InTopLeftCorner;
                        mLastX=0;
                        mLastY=0;

                        viewport()->update();
                    }

                    if (x>mVerticalHeader_TotalWidth-FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                    {
                        setCursor(Qt::SplitHCursor);
                    }
                    else
                    if (y>mHorizontalHeader_TotalHeight-FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                    {
                        setCursor(Qt::SplitVCursor);
                    }
                    else
                    {
                        setCursor(Qt::ArrowCursor);
                    }
                }
                else
                {
                    mMouseLocation=InMiddleWorld;

                    if (mLastX>=0 || mLastY>=0)
                    {
                        mLastX=-1;
                        mLastY=-1;

                        viewport()->update();

                        setCursor(Qt::ArrowCursor);
                    }
                }
            }
        }
    }

    QAbstractScrollArea::mouseMoveEvent(event);

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::mouseHoldTick()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mouseMoveEvent(&mMouseEvent);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::initShiftSelectionForKeyboard()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mMouseXForShift<0 || mMouseYForShift<0)
    {
        mMouseXForShift=mCurrentColumn;
        mMouseYForShift=mCurrentRow;
    }

    mLastX=mMouseXForShift;
    mLastY=mMouseYForShift;

    fillShiftSelection();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::initShiftSelection()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mMouseSelectedCells.clear();
    mMouseXForShift=mCurrentColumn;
    mMouseYForShift=mCurrentRow;

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::fillShiftSelection()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mMouseSelectedCells.length()==0)
    {
        int minX=qMin(mCurrentColumn, mLastX);
        int minY=qMin(mCurrentRow, mLastY);
        int maxX=qMax(mCurrentColumn, mLastX);
        int maxY=qMax(mCurrentRow, mLastY);

        for (int i=minY; i<=maxY; i++)
        {
            QList<bool> aRow;

            for (int j=minX; j<=maxX; j++)
            {
                aRow.append(false);
            }

            mMouseSelectedCells.append(aRow);
        }

        mMouseSelectedCells[mMouseYForShift-minY][mMouseXForShift-minX]=mSelectedCells.at(mMouseYForShift).at(mMouseXForShift);
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::selectRangeForHandlers(int resX, int resY)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    int minX=qMin(resX, mLastX);
    int minY=qMin(resY, mLastY);
    int maxX=qMax(resX, mLastX);
    int maxY=qMax(resY, mLastY);

    int lastMinX=qMin(mCurrentColumn, mLastX);
    int lastMinY=qMin(mCurrentRow, mLastY);
    int lastMaxX=qMax(mCurrentColumn, mLastX);
    int lastMaxY=qMax(mCurrentRow, mLastY);

    FASTTABLE_ASSERT(lastMaxY-lastMinY+1==mMouseSelectedCells.length());

    for (int i=lastMinY; i<=lastMaxY; i++)
    {
        FASTTABLE_ASSERT(lastMaxX-lastMinX+1==mMouseSelectedCells.at(i-lastMinY).length());

        for (int j=lastMinX; j<=lastMaxX; j++)
        {
            setCellSelected(i, j, mMouseSelectedCells.at(i-lastMinY).at(j-lastMinX));
        }
    }

    while (mMouseSelectedCells.length()>maxY-minY+1)
    {
        mMouseSelectedCells.removeLast();
    }

    while (mMouseSelectedCells.length()<maxY-minY+1)
    {
        mMouseSelectedCells.append(QList<bool>());
    }

    setCurrentCell(resY, resX, true);

    bool aSelected=mSelectedCells.at(mLastY).at(mLastX);

    for (int i=minY; i<=maxY; i++)
    {
        while (mMouseSelectedCells.at(i-minY).length()>maxX-minX+1)
        {
            mMouseSelectedCells[i-minY].removeLast();
        }

        while (mMouseSelectedCells.at(i-minY).length()<maxX-minX+1)
        {
            mMouseSelectedCells[i-minY].append(false);
        }

        for (int j=minX; j<=maxX; j++)
        {
            mMouseSelectedCells[i-minY][j-minX]=mSelectedCells.at(i).at(j);

            setCellSelected(i, j, aSelected);
        }
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_SelectRangeForHandlers(int resX)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    int minX=qMin(resX, mLastX);
    int maxX=qMax(resX, mLastX);

    int lastMinX=qMin(mCurrentColumn, mLastX);
    int lastMaxX=qMax(mCurrentColumn, mLastX);

    FASTTABLE_ASSERT(mMouseSelectedCells.length()==mRowCount);

    for (int i=0; i<mRowCount; i++)
    {
        FASTTABLE_ASSERT(lastMaxX-lastMinX+1==mMouseSelectedCells.at(i).length());

        for (int j=lastMinX; j<=lastMaxX; j++)
        {
            setCellSelected(i, j, mMouseSelectedCells.at(i).at(j-lastMinX));
        }
    }

    setCurrentCell(mRowCount-1, resX, true);

    bool aSelected=mSelectedCells.at(0).at(mLastX);

    for (int i=0; i<mRowCount; i++)
    {
        while (mMouseSelectedCells.at(i).length()>maxX-minX+1)
        {
            mMouseSelectedCells[i].removeLast();
        }

        while (mMouseSelectedCells.at(i).length()<maxX-minX+1)
        {
            mMouseSelectedCells[i].append(false);
        }

        for (int j=minX; j<=maxX; j++)
        {
            mMouseSelectedCells[i][j-minX]=mSelectedCells.at(i).at(j);

            setCellSelected(i, j, aSelected);
        }
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_SelectRangeForHandlers(int resY)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    int minY=qMin(resY, mLastY);
    int maxY=qMax(resY, mLastY);

    int lastMinY=qMin(mCurrentRow, mLastY);
    int lastMaxY=qMax(mCurrentRow, mLastY);

    FASTTABLE_ASSERT(lastMaxY-lastMinY+1==mMouseSelectedCells.length());

    for (int i=lastMinY; i<=lastMaxY; i++)
    {
        FASTTABLE_ASSERT(mMouseSelectedCells.at(i-lastMinY).length()==mColumnCount);

        for (int j=0; j<mColumnCount; j++)
        {
            setCellSelected(i, j, mMouseSelectedCells.at(i-lastMinY).at(j));
        }
    }

    while (mMouseSelectedCells.length()>maxY-minY+1)
    {
        mMouseSelectedCells.removeLast();
    }

    while (mMouseSelectedCells.length()<maxY-minY+1)
    {
        mMouseSelectedCells.append(QList<bool>());
    }

    setCurrentCell(resY, mColumnCount-1, true);

    bool aSelected=mSelectedCells.at(mLastY).at(0);

    for (int i=minY; i<=maxY; i++)
    {
        while (mMouseSelectedCells.at(i-minY).length()<mColumnCount)
        {
            mMouseSelectedCells[i-minY].append(false);
        }

        for (int j=0; j<mColumnCount; j++)
        {
            mMouseSelectedCells[i-minY][j]=mSelectedCells.at(i).at(j);

            setCellSelected(i, j, aSelected);
        }
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mMouseLocation==InTopLeftCorner)
    {
        if (atTopLeftCorner(event->x(), event->y()))
        {
            if (mSelectedCells.at(0).at(0))
            {
                unselectAll();
            }
            else
            {
                selectAll();
            }
        }
    }

    if (mMouseResizeCell>=0)
    {
        mMouseResizeCell=-1;
        mMouseResizeLineX=-1;
        mMouseResizeLineY=-1;

        viewport()->update();

        setCursor(Qt::ArrowCursor);
    }
    else
    if (mMouseLocation!=InCell && mMouseLocation!=InMiddleWorld)
    {
        viewport()->update();
    }

    if (mMouseLocation==InCell && mMouseXForShift==mCurrentColumn && mMouseYForShift==mCurrentRow)
    {
        scrollToCurrentCell();
    }

    mMousePressed=false;
    mCtrlPressed=false;
    mShiftPressed=false;
    mMouseLocation=InMiddleWorld;
    mLastX=-1;
    mLastY=-1;

    mMouseHoldTimer.stop();

    mouseMoveEvent(event);
    QAbstractScrollArea::mouseReleaseEvent(event);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::leaveEvent(QEvent *event)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (!mMousePressed)
    {
        if (mMouseLocation!=InCell && mMouseLocation!=InMiddleWorld)
        {
            viewport()->update();
        }

        mMouseLocation=InMiddleWorld;
        mLastX=-1;
        mLastY=-1;
        setCursor(Qt::ArrowCursor);
    }

    QAbstractScrollArea::leaveEvent(event);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::resizeEvent(QResizeEvent *event)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    updateBarsRanges();
    updateVisibleRange();

    QAbstractScrollArea::resizeEvent(event);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::paintEvent(QPaintEvent *event)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

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
                if (mColumnWidths.at(j)>0 && mRowHeights.at(i)>0)
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
                if (mColumnWidths.at(j)>0 && mHorizontalHeader_RowHeights.at(i)>0)
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
                if (mVerticalHeader_ColumnWidths.at(j)>0 && mRowHeights.at(i)>0)
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

    if (mMouseResizeLineX>=0)
    {
        painter.setPen(QPen(QColor(0, 0, 0)));
        painter.drawLine(offsetX+mMouseResizeLineX, 0, offsetX+mMouseResizeLineX, mTotalHeight);
    }

    if (mMouseResizeLineY>=0)
    {
        painter.setPen(QPen(QColor(0, 0, 0)));
        painter.drawLine(0, offsetY+mMouseResizeLineY, mTotalWidth, offsetY+mMouseResizeLineY);
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    bool    aHeaderPressed;
    QColor  *aGridColor;
    QBrush  *aBackgroundBrush;
    QColor  *aBorderColor;
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

            aHeaderPressed=false;

            if (row==mCurrentRow && column==mCurrentColumn)
            {
                aBorderColor=&mCellBorderColor;
            }
            else
            {
                aBorderColor=0;
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

            if (mMouseLocation==InHorizontalHeaderCell)
            {
                if (mMousePressed)
                {
                    int minX=qMin(mCurrentColumn, mLastX);
                    int maxX=qMax(mCurrentColumn, mLastX);

                    if (
                        mHorizontalHeader_SelectedColumns.at(column)==mRowCount
                        ||
                        (
                         mMouseResizeCell<0
                         &&
                         column>=minX
                         &&
                         column<=maxX
                        )
                       )
                    {
                        aHeaderPressed=true;
                        aBorderColor=&mHorizontalHeader_CellBorderColor;
                    }
                    else
                    {
                        aHeaderPressed=false;
                        aBorderColor=0;
                    }
                }
                else
                {
                    aHeaderPressed=false;

                    if (row==mLastY && column==mLastX)
                    {
                        aBorderColor=&mHorizontalHeader_CellBorderColor;
                    }
                    else
                    {
                        if (mHorizontalHeader_SelectedColumns.at(column)==mRowCount)
                        {
                            aHeaderPressed=true;
                            aBorderColor=&mHorizontalHeader_CellBorderColor;
                        }
                        else
                        {
                            aBorderColor=0;
                        }
                    }
                }
            }
            else
            {
                if (mHorizontalHeader_SelectedColumns.at(column)==mRowCount)
                {
                    aHeaderPressed=true;
                    aBorderColor=&mHorizontalHeader_CellBorderColor;
                }
                else
                {
                    aHeaderPressed=false;
                    aBorderColor=0;
                }
            }

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

            if (mMouseLocation==InVerticalHeaderCell)
            {
                if (mMousePressed)
                {
                    int minY=qMin(mCurrentRow, mLastY);
                    int maxY=qMax(mCurrentRow, mLastY);

                    if (
                        mVerticalHeader_SelectedRows.at(row)==mColumnCount
                        ||
                        (
                         mMouseResizeCell<0
                         &&
                         row>=minY
                         &&
                         row<=maxY
                        )
                       )
                    {
                        aHeaderPressed=true;
                        aBorderColor=&mVerticalHeader_CellBorderColor;
                    }
                    else
                    {
                        aHeaderPressed=false;
                        aBorderColor=0;
                    }
                }
                else
                {
                    aHeaderPressed=false;

                    if (row==mLastY && column==mLastX)
                    {
                        aBorderColor=&mVerticalHeader_CellBorderColor;
                    }
                    else
                    {
                        if (mVerticalHeader_SelectedRows.at(row)==mColumnCount)
                        {
                            aHeaderPressed=true;
                            aBorderColor=&mVerticalHeader_CellBorderColor;
                        }
                        else
                        {
                            aBorderColor=0;
                        }
                    }
                }
            }
            else
            {
                if (mVerticalHeader_SelectedRows.at(row)==mColumnCount)
                {
                    aHeaderPressed=true;
                    aBorderColor=&mVerticalHeader_CellBorderColor;
                }
                else
                {
                    aHeaderPressed=false;
                    aBorderColor=0;
                }
            }

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

            if (mMouseLocation==InTopLeftCorner)
            {
                if (mMouseResizeCell<0)
                {
                    aHeaderPressed=mMousePressed;
                    aBorderColor=&mHorizontalHeader_CellBorderColor;
                }
                else
                {
                    aHeaderPressed=false;
                    aBorderColor=0;
                }
            }
            else
            {
                aHeaderPressed=false;
                aBorderColor=0;
            }

            aTextColor=0;
            aText=0;
            aFont=0;
            textFlags=0;
        }
        break;
        default:
        {
            aHeaderPressed=false;
            aGridColor=0;
            aBackgroundBrush=0;
            aBorderColor=0;
            aTextColor=0;
            aText=0;
            aFont=0;
            textFlags=0;
        }
        break;
    }

    paintCell(painter, x ,y, width, height, drawComponent, aHeaderPressed, aGridColor, aBackgroundBrush, aBorderColor, aTextColor, aText, aFont, textFlags);

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const DrawComponent drawComponent, bool headerPressed, QColor *aGridColor,
                                      QBrush *aBackgroundBrush, QColor *aBorderColor, QColor *aTextColor, QString *aText, QFont *aFont, int aTextFlags)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    if (drawComponent==DrawCell)
    {
        headerPressed=false;
        (*mDrawCellFunction)(painter, x, y, width, height, headerPressed, aGridColor, aBackgroundBrush, aBorderColor);
    }
    else
    {
        (*mDrawHeaderCellFunction)(painter, x, y, width, height, headerPressed, aGridColor, aBackgroundBrush, aBorderColor);
    }

    if (width>8 && height>8 && aText)
    {
        painter.setPen(QPen(*aTextColor));
        painter.setFont(*aFont);
        painter.drawText(x+4, y+4, width-8, height-8, aTextFlags, *aText);
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

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

    if (aBorderColor && width>2 && height>2)
    {
        QPen aPen(*aBorderColor);

        QVector<qreal> aDashes;
        aDashes.append(1);
        aDashes.append(1);
        aPen.setDashPattern(aDashes);

        painter.setPen(aPen);
        painter.drawRect(x+1, y+1, width-2, height-2);
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintCellDefault(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    painter.fillRect(x, y, width, height, *aBackgroundBrush);

    painter.setPen(QPen(*aGridColor));
    painter.drawRect(x, y, width, height);

    if (aBorderColor && width>2 && height>2)
    {
        QPen aPen(*aBorderColor);

        QVector<qreal> aDashes;
        aDashes.append(1);
        aDashes.append(1);
        aPen.setDashPattern(aDashes);

        painter.setPen(aPen);
        painter.drawRect(x+1, y+1, width-2, height-2);
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    QColor backColorDown=aBorderColor ? *aBorderColor : aBackgroundBrush->color();

    int r;
    int g;
    int b;

    if (headerPressed)
    {
        r=backColorDown.red()-40;
        g=backColorDown.green()-40;
        b=backColorDown.blue()-40;

        if (r<0)
        {
            r=0;
        }

        if (g<0)
        {
            g=0;
        }

        if (b<0)
        {
            b=0;
        }

        backColorDown.setRgb(r, g, b);
    }

    r=backColorDown.red()+20;
    g=backColorDown.green()+20;
    b=backColorDown.blue()+20;

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

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellWinXP(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    if (headerPressed)
    {
        QColor backColor=aBackgroundBrush->color();

        int r=backColor.red()-15;
        int g=backColor.green()-10;
        int b=backColor.blue()-5;

        if (r<0)
        {
            r=0;
        }

        if (g<0)
        {
            g=0;
        }

        if (b<0)
        {
            b=0;
        }

        backColor.setRgb(r, g, b);

        r=aGridColor->red()-40;
        g=aGridColor->green()-40;
        b=aGridColor->blue()-30;

        if (r<0)
        {
            r=0;
        }

        if (g<0)
        {
            g=0;
        }

        if (b<0)
        {
            b=0;
        }

        QColor gridColor(r, g, b);

        painter.fillRect(x+3, y+3, width-3, height-3, backColor);

        painter.setPen(QPen(gridColor));
        painter.drawRect(x, y, width, height);

        painter.setPen(QPen(QColor(backColor.red()+(gridColor.red()-backColor.red())*2/3, backColor.green()+(gridColor.green()-backColor.green())*2/3, backColor.blue()+(gridColor.blue()-backColor.blue())*2/3)));
        painter.drawLine(x+1, y+height-1, x+1, y+1);
        painter.drawLine(x+1, y+1, x+width-1, y+1);

        painter.setPen(QPen(QColor(backColor.red()+(gridColor.red()-backColor.red())/3, backColor.green()+(gridColor.green()-backColor.green())/3, backColor.blue()+(gridColor.blue()-backColor.blue())/3)));
        painter.drawLine(x+2, y+height-1, x+2, y+2);
        painter.drawLine(x+2, y+2, x+width-1, y+2);
    }
    else
    {
        QColor backColor=aBackgroundBrush->color();

        if (aBorderColor)
        {
            int r=backColor.red()+20;
            int g=backColor.green()+20;
            int b=backColor.blue()+20;

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

            backColor.setRgb(r, g, b);
        }

        painter.fillRect(x+1, y+1, width, height-3, backColor);

        painter.setPen(QPen(QColor(255, 255, 255)));
        painter.drawLine(x+width, y+4, x+width, y+height-4);
        painter.drawLine(x, y+4, x, y+height-4);

        painter.setPen(QPen(*aGridColor));
        painter.drawLine(x+width-1, y+4, x+width-1, y+height-4);

        if (y==0)
        {
            painter.drawLine(x, y, x+width, y);
        }

        if (aBorderColor)
        {
            int r=aBorderColor->red()+5;
            int g=aBorderColor->green()+20;
            int b=aBorderColor->blue()+60;

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

            backColor.setRgb(r, g, b);

            painter.setPen(QPen(*aBorderColor));
            painter.drawLine(x, y+height-2, x+width, y+height-2);
            painter.drawLine(x, y+height, x+width, y+height);

            painter.setPen(QPen(backColor));
            painter.drawLine(x, y+height-1, x+width, y+height-1);
        }
        else
        {
            painter.drawLine(x, y+height, x+width, y+height);
            painter.setPen(QPen(QColor(backColor.red()+(aGridColor->red()-backColor.red())*2/3, backColor.green()+(aGridColor->green()-backColor.green())*2/3, backColor.blue()+(aGridColor->blue()-backColor.blue())*2/3)));
            painter.drawLine(x, y+height-1, x+width, y+height-1);
            painter.setPen(QPen(QColor(backColor.red()+(aGridColor->red()-backColor.red())/3, backColor.green()+(aGridColor->green()-backColor.green())/3, backColor.blue()+(aGridColor->blue()-backColor.blue())/3)));
            painter.drawLine(x, y+height-2, x+width, y+height-2);
        }
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellWin7(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    QColor backColorDown;

    int r;
    int g;
    int b;

    if (aBorderColor)
    {
        if (headerPressed)
        {
            r=aBorderColor->red()+30;
            g=aBorderColor->green()+20;
            b=aBorderColor->blue()+20;
        }
        else
        {
            r=aBorderColor->red()+80;
            g=aBorderColor->green()+50;
            b=aBorderColor->blue()+20;
        }

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

        backColorDown.setRgb(r, g, b);
    }
    else
    {
        backColorDown=aBackgroundBrush->color();
    }

    r=backColorDown.red()+15;
    g=backColorDown.green()+15;
    b=backColorDown.blue()+15;

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

    painter.fillRect(x+2, y+1, width-3, height/2-1, backColorUp);
    painter.fillRect(x+2, y+height/2, width-3, height-height/2, backColorDown);

    if (aBorderColor)
    {
        if (headerPressed)
        {
            r=aBorderColor->red()-30;
            g=aBorderColor->green()-40;
            b=aBorderColor->blue()-50;

            if (r<0)
            {
                r=0;
            }

            if (g<0)
            {
                g=0;
            }

            if (b<0)
            {
                b=0;
            }

            painter.setPen(QPen(QColor(r, g, b)));
        }
        else
        {
            painter.setPen(QPen(*aBorderColor));
        }
    }
    else
    {
        painter.setPen(QPen(*aGridColor));
    }

    if (y==0 || aBorderColor)
    {
        painter.drawLine(x, y, x+width, y);
    }

    if (x==0 || aBorderColor)
    {
        painter.drawLine(x, y, x, y+height);
    }

    painter.drawLine(x+width, y, x+width, y+height);
    painter.drawLine(x, y+height, x+width, y+height);

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintHeaderCellDefault(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    QColor backColor=aBorderColor? *aBorderColor : aBackgroundBrush->color();

    if (headerPressed)
    {
        int r=backColor.red()-40;
        int g=backColor.green()-40;
        int b=backColor.blue()-40;

        if (r<0)
        {
            r=0;
        }

        if (g<0)
        {
            g=0;
        }

        if (b<0)
        {
            b=0;
        }

        backColor.setRgb(r, g, b);
    }

    painter.fillRect(x, y, width, height, backColor);

    painter.setPen(QPen(*aGridColor));
    painter.drawRect(x, y, width, height);

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::scrollBarValueChanged(int value)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    updateVisibleRange();

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::updateBarsRanges()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::updateVisibleRange()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

            while (mVerticalHeader_VisibleRight<mVerticalHeader_ColumnCount-1 && mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)<maxX && (mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<=0 || mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<maxX))
            {
                mVerticalHeader_VisibleRight++;
            }

            while (mVerticalHeader_VisibleRight>0 && mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)>maxX && (mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<=0 || mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)>maxX))
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

            while (mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowCount-1 && mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)<maxY && (mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<=0 || mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<maxY))
            {
                mHorizontalHeader_VisibleBottom++;
            }

            while (mHorizontalHeader_VisibleBottom>0 && mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)>maxY && (mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<=0 || mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)>maxY))
            {
                mHorizontalHeader_VisibleBottom--;
            }
        }

        if (
            mHorizontalHeader_VisibleBottom<0
            ||
            (
             mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<=0 ?
                (mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)<maxY)
                :
                (mHorizontalHeader_OffsetY.at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights.at(mHorizontalHeader_VisibleBottom)<maxY)
            )
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

            while (mVisibleTop<mRowCount-1 && mOffsetY.at(mVisibleTop)<minY && (mRowHeights.at(mVisibleTop)<=0 || mOffsetY.at(mVisibleTop)+mRowHeights.at(mVisibleTop)<minY))
            {
                mVisibleTop++;
            }

            while (mVisibleTop>0 && mOffsetY.at(mVisibleTop)>minY && (mRowHeights.at(mVisibleTop)<=0 || mOffsetY.at(mVisibleTop)+mRowHeights.at(mVisibleTop)>minY))
            {
                mVisibleTop--;
            }

            while (mVisibleBottom<mRowCount-1 && mOffsetY.at(mVisibleBottom)<maxY && (mRowHeights.at(mVisibleBottom)<=0 || mOffsetY.at(mVisibleBottom)+mRowHeights.at(mVisibleBottom)<maxY))
            {
                mVisibleBottom++;
            }

            while (mVisibleBottom>0 && mOffsetY.at(mVisibleBottom)>maxY && (mRowHeights.at(mVisibleBottom)<=0 || mOffsetY.at(mVisibleBottom)+mRowHeights.at(mVisibleBottom)>maxY))
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
            (
             mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<=0?
                (mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)<maxX)
                :
                (mVerticalHeader_OffsetX.at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths.at(mVerticalHeader_VisibleRight)<maxX)
            )
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

            while (mVisibleLeft<mColumnCount-1 && mOffsetX.at(mVisibleLeft)<minX && (mColumnWidths.at(mVisibleLeft)<=0 || mOffsetX.at(mVisibleLeft)+mColumnWidths.at(mVisibleLeft)<minX))
            {
                mVisibleLeft++;
            }

            while (mVisibleLeft>0 && mOffsetX.at(mVisibleLeft)>minX && (mColumnWidths.at(mVisibleLeft)<=0 || mOffsetX.at(mVisibleLeft)+mColumnWidths.at(mVisibleLeft)>minX))
            {
                mVisibleLeft--;
            }

            while (mVisibleRight<mColumnCount-1 && mOffsetX.at(mVisibleRight)<maxX && (mColumnWidths.at(mVisibleRight)<=0 || mOffsetX.at(mVisibleRight)+mColumnWidths.at(mVisibleRight)<maxX))
            {
                mVisibleRight++;
            }

            while (mVisibleRight>0 && mOffsetX.at(mVisibleRight)>maxX && (mColumnWidths.at(mVisibleRight)<=0 || mOffsetX.at(mVisibleRight)+mColumnWidths.at(mVisibleRight)>maxX))
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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::clear()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    mCurrentRow=-1;
    mCurrentColumn=-1;

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

    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseResizeLineX=-1;
    mMouseResizeLineY=-1;
    mMouseResizeCell=-1;

    mMouseSelectedCells.clear();

    updateBarsRanges();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::selectRow(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, true);
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::unselectRow(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);

    for (int i=0; i<mColumnCount; ++i)
    {
        setCellSelected(row, i, false);
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::selectColumn(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, true);
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::unselectColumn(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);

    for (int i=0; i<mRowCount; ++i)
    {
        setCellSelected(i, column, false);
    }

    FASTTABLE_END_PROFILE;
}

CustomFastTableWidget::Style CustomFastTableWidget::style()
{
    FASTTABLE_DEBUG;
    return mStyle;
}

void CustomFastTableWidget::setStyle(Style style, bool keepColors)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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
                    mCellBorderColor.setRgb(180, 180, 180);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(220, 220, 220));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(200, 200, 200);
                    mHorizontalHeader_CellBorderColor.setRgb(240, 240, 240);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(220, 220, 220));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(200, 200, 200);
                    mVerticalHeader_CellBorderColor.setRgb(240, 240, 240);

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
                    mCellBorderColor.setRgb(141, 140, 139);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(234, 233, 231));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(210, 207, 204);
                    mHorizontalHeader_CellBorderColor.setRgb(249, 248, 248);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(233, 232, 231));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(190, 186, 182);
                    mVerticalHeader_CellBorderColor.setRgb(249, 248, 248);

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
                    mCellBorderColor.setRgb(206, 149, 58);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(235, 234, 219));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(199, 197, 178);
                    mHorizontalHeader_CellBorderColor.setRgb(249, 177, 25);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(235, 234, 219));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(199, 197, 178);
                    mVerticalHeader_CellBorderColor.setRgb(249, 177, 25);

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
                    mCellBorderColor.setRgb(206, 149, 58);

                    mHorizontalHeader_DefaultBackgroundBrush.setColor(QColor(241, 242, 244));
                    mHorizontalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mHorizontalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mHorizontalHeader_GridColor.setRgb(213, 213, 213);
                    mHorizontalHeader_CellBorderColor.setRgb(105, 187, 227);

                    mVerticalHeader_DefaultBackgroundBrush.setColor(QColor(241, 242, 244));
                    mVerticalHeader_DefaultBackgroundBrush.setStyle(Qt::SolidPattern);
                    mVerticalHeader_DefaultForegroundColor.setRgb(0, 0, 0);
                    mVerticalHeader_GridColor.setRgb(213, 213, 213);
                    mVerticalHeader_CellBorderColor.setRgb(105, 187, 227);

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
                mDrawHeaderCellFunction=&paintHeaderCellDefault;
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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

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

        mVerticalHeader_SelectedRows[i]=mColumnCount;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns.length());

        mHorizontalHeader_SelectedColumns[i]=mRowCount;
    }

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::unselectAll()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

        mVerticalHeader_SelectedRows[i]=0;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns.length());

        mHorizontalHeader_SelectedColumns[i]=0;
    }

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::addRow()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    insertRow(mRowCount);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::insertRow(int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    mOffsetY.insert(row, row==0? mHorizontalHeader_TotalHeight : (mRowHeights.at(row-1)<=0? mOffsetY.at(row-1) : (mOffsetY.at(row-1)+mRowHeights.at(row-1))));
    mRowHeights.insert(row, mDefaultHeight);

    for (int i=row+1; i<mRowCount; ++i)
    {
        mOffsetY[i]+=mDefaultHeight;
    }

    mData.insert(row, aNewRow);
    mVerticalHeader_Data.insert(row, aNewRow);
    mSelectedCells.insert(row, aNewRowbool);
    mVerticalHeader_SelectedRows.insert(row, 0);

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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::deleteRow(int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);
    FASTTABLE_ASSERT(row>=0 && row<mOffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<mRowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<mData.length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells.length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows.length());

    int diff=mRowHeights.at(row);

    if (diff>0)
    {
        mTotalHeight-=diff;

        FASTTABLE_ASSERT(mTotalHeight>=0);

        for (int i=row+1; i<mRowCount; ++i)
        {
            mOffsetY[i]-=diff;

            FASTTABLE_ASSERT(mOffsetY.at(i)>=0);
        }
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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::addColumn()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    insertColumn(mColumnCount);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::insertColumn(int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<=mColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<=mOffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<=mColumnWidths.length());
    FASTTABLE_ASSERT(column>=0 && column<=mHorizontalHeader_SelectedColumns.length());

    mColumnCount++;

    mTotalWidth+=mDefaultWidth;

    mOffsetX.insert(column, column==0? mVerticalHeader_TotalWidth : (mColumnWidths.at(column-1)<=0? mOffsetX.at(column-1) : (mOffsetX.at(column-1)+mColumnWidths.at(column-1))));
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

    mHorizontalHeader_SelectedColumns.insert(column, 0);

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::deleteColumn(int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<mOffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths.length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns.length());

    int diff=mColumnWidths.at(column);

    if (diff>0)
    {
        mTotalWidth-=diff;

        FASTTABLE_ASSERT(mTotalWidth>=0);

        for (int i=column+1; i<mColumnCount; ++i)
        {
            mOffsetX[i]-=diff;

            FASTTABLE_ASSERT(mOffsetX.at(i)>=0);
        }
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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_AddRow()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    horizontalHeader_InsertRow(mHorizontalHeader_RowCount);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_InsertRow(int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_RowCount);
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_OffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_RowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_Data.length());

    mHorizontalHeader_RowCount++;

    QStringList aNewRow;

    mHorizontalHeader_TotalHeight+=mDefaultHeight;
    mTotalHeight+=mDefaultHeight;

    mHorizontalHeader_OffsetY.insert(row, row==0? 0 : (mHorizontalHeader_RowHeights.at(row-1)<=0? mHorizontalHeader_OffsetY.at(row-1) : (mHorizontalHeader_OffsetY.at(row-1)+mHorizontalHeader_RowHeights.at(row-1))));
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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_DeleteRow(int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_RowCount);
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_OffsetY.length());
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_RowHeights.length());
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data.length());

    int diff=mHorizontalHeader_RowHeights.at(row);

    if (diff>0)
    {
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
    }

    mHorizontalHeader_OffsetY.removeAt(row);
    mHorizontalHeader_RowHeights.removeAt(row);
    mHorizontalHeader_Data.removeAt(row);

    mHorizontalHeader_RowCount--;

    updateBarsRanges();
    updateVisibleRange();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_AddColumn()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    verticalHeader_InsertColumn(mVerticalHeader_ColumnCount);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_InsertColumn(int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_ColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_OffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_ColumnWidths.length());

    mVerticalHeader_ColumnCount++;

    mVerticalHeader_TotalWidth+=mDefaultWidth;
    mTotalWidth+=mDefaultWidth;

    mVerticalHeader_OffsetX.insert(column, column==0? 0 : (mVerticalHeader_ColumnWidths.at(column-1)<=0? mVerticalHeader_OffsetX.at(column-1) : (mVerticalHeader_OffsetX.at(column-1)+mVerticalHeader_ColumnWidths.at(column-1))));
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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_DeleteColumn(int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_OffsetX.length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnWidths.length());

    int diff=mVerticalHeader_ColumnWidths.at(column);

    if (diff>0)
    {
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

    FASTTABLE_END_PROFILE;
}

int CustomFastTableWidget::rowCount()
{
    FASTTABLE_DEBUG;
    return mRowCount;
}

void CustomFastTableWidget::setRowCount(int count)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

int CustomFastTableWidget::columnCount()
{
    FASTTABLE_DEBUG;
    return mColumnCount;
}

void CustomFastTableWidget::setColumnCount(int count)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

qint16 CustomFastTableWidget::horizontalHeader_RowCount()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_RowCount;
}

void CustomFastTableWidget::horizontalHeader_SetRowCount(qint16 count)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

qint16 CustomFastTableWidget::verticalHeader_ColumnCount()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_ColumnCount;
}

void CustomFastTableWidget::verticalHeader_SetColumnCount(qint16 count)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::setSizes(int aRowCount, int aColumnCount, qint16 aHorizontalHeaderRowCount, qint16 aVerticalHeaderColumnCount)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

QBrush CustomFastTableWidget::defaultBackgroundBrush()
{
    FASTTABLE_DEBUG;
    return mDefaultBackgroundBrush;
}

void CustomFastTableWidget::setDefaultBackgroundBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mDefaultBackgroundBrush=brush;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::defaultForegroundColor()
{
    FASTTABLE_DEBUG;
    return mDefaultForegroundColor;
}

void CustomFastTableWidget::setDefaultForegroundColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mDefaultForegroundColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::gridColor()
{
    FASTTABLE_DEBUG;
    return mGridColor;
}

void CustomFastTableWidget::setGridColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mGridColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::cellBorderColor()
{
    FASTTABLE_DEBUG;
    return mCellBorderColor;
}

void CustomFastTableWidget::setCellBorderColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mCellBorderColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QBrush CustomFastTableWidget::horizontalHeader_DefaultBackgroundBrush()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_DefaultBackgroundBrush;
}

void CustomFastTableWidget::horizontalHeader_SetDefaultBackgroundBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mHorizontalHeader_DefaultBackgroundBrush=brush;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::horizontalHeader_DefaultForegroundColor()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_DefaultForegroundColor;
}

void CustomFastTableWidget::horizontalHeader_SetDefaultForegroundColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mHorizontalHeader_DefaultForegroundColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::horizontalHeader_GridColor()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_GridColor;
}

void CustomFastTableWidget::horizontalHeader_SetGridColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mHorizontalHeader_GridColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::horizontalHeader_CellBorderColor()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeader_CellBorderColor;
}

void CustomFastTableWidget::horizontalHeader_SetCellBorderColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mHorizontalHeader_CellBorderColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QBrush CustomFastTableWidget::verticalHeader_DefaultBackgroundBrush()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_DefaultBackgroundBrush;
}

void CustomFastTableWidget::verticalHeader_SetDefaultBackgroundBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mVerticalHeader_DefaultBackgroundBrush=brush;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::verticalHeader_DefaultForegroundColor()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_DefaultForegroundColor;
}

void CustomFastTableWidget::verticalHeader_SetDefaultForegroundColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mVerticalHeader_DefaultForegroundColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::verticalHeader_GridColor()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_GridColor;
}

void CustomFastTableWidget::verticalHeader_SetGridColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mVerticalHeader_GridColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::verticalHeader_CellBorderColor()
{
    FASTTABLE_DEBUG;
    return mVerticalHeader_CellBorderColor;
}

void CustomFastTableWidget::verticalHeader_SetCellBorderColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mVerticalHeader_CellBorderColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QBrush CustomFastTableWidget::selectionBrush()
{
    FASTTABLE_DEBUG;
    return mSelectionBrush;
}

void CustomFastTableWidget::setSelectionBrush(QBrush brush)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mSelectionBrush=brush;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QColor CustomFastTableWidget::selectionTextColor()
{
    FASTTABLE_DEBUG;
    return mSelectionTextColor;
}

void CustomFastTableWidget::setSelectionTextColor(QColor color)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mSelectionTextColor=color;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

quint16 CustomFastTableWidget::defaultWidth()
{
    FASTTABLE_DEBUG;
    return mDefaultWidth;
}

void CustomFastTableWidget::setDefaultWidth(quint16 width)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
}

quint16 CustomFastTableWidget::defaultHeight()
{
    FASTTABLE_DEBUG;
    return mDefaultHeight;
}

void CustomFastTableWidget::setDefaultHeight(quint16 height)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column<mColumnWidths.length());

    qint16 prevWidth=mColumnWidths.at(column);
    bool wasVisible=prevWidth>0;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row<mRowHeights.length());

    qint16 prevHeight=mRowHeights.at(row);
    bool wasVisible=prevHeight>0;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths.length());

    qint16 prevWidth=mVerticalHeader_ColumnWidths.at(column);
    bool wasVisible=prevWidth>0;

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

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights.length());

    qint16 prevHeight=mHorizontalHeader_RowHeights.at(row);
    bool wasVisible=prevHeight>0;

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

    FASTTABLE_END_PROFILE;
}

QRect CustomFastTableWidget::visibleRange()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QRect aRect;
    aRect.setCoords(mVisibleLeft, mVisibleTop, mVisibleRight, mVisibleBottom);

    FASTTABLE_END_PROFILE;

    return aRect;
}

QRect CustomFastTableWidget::horizontalHeader_VisibleRange()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QRect aRect;

    if (mHorizontalHeader_VisibleBottom>=0)
    {
        aRect.setCoords(mVisibleLeft, 0, mVisibleRight, mHorizontalHeader_VisibleBottom);
    }
    else
    {
        aRect.setCoords(-1, -1, -1, -1);
    }

    FASTTABLE_END_PROFILE;

    return aRect;
}

QRect CustomFastTableWidget::verticalHeader_VisibleRange()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QRect aRect;

    if (mVerticalHeader_VisibleRight>=0)
    {
        aRect.setCoords(0, mVisibleTop, mVerticalHeader_VisibleRight, mVisibleBottom);
    }
    else
    {
        aRect.setCoords(-1, -1, -1, -1);
    }

    FASTTABLE_END_PROFILE;

    return aRect;
}

QRect CustomFastTableWidget::cellRectangle(const int row, const int column)
{
    FASTTABLE_DEBUG;

    FASTTABLE_ASSERT(column>=0 && column<mOffsetX.length());
    FASTTABLE_ASSERT(row>=0    && row<mOffsetY.length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths.length());
    FASTTABLE_ASSERT(row>=0    && row<mRowHeights.length());

    return QRect(mOffsetX.at(column), mOffsetY.at(row), mColumnWidths.at(column), mRowHeights.at(row));
}

QRect CustomFastTableWidget::horizontalHeader_CellRectangle(const int row, const int column)
{
    FASTTABLE_DEBUG;

    FASTTABLE_ASSERT(column>=0 && column<mOffsetX.length());
    FASTTABLE_ASSERT(row>=0    && row<mHorizontalHeader_OffsetY.length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths.length());
    FASTTABLE_ASSERT(row>=0    && row<mHorizontalHeader_RowHeights.length());

    return QRect(mOffsetX.at(column), mHorizontalHeader_OffsetY.at(row), mColumnWidths.at(column), mHorizontalHeader_RowHeights.at(row));
}

QRect CustomFastTableWidget::verticalHeader_CellRectangle(const int row, const int column)
{
    FASTTABLE_DEBUG;

    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_OffsetX.length());
    FASTTABLE_ASSERT(row>=0    && row<mOffsetY.length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnWidths.length());
    FASTTABLE_ASSERT(row>=0    && row<mRowHeights.length());

    return QRect(mVerticalHeader_OffsetX.at(column), mOffsetY.at(row), mVerticalHeader_ColumnWidths.at(column), mRowHeights.at(row));
}

void CustomFastTableWidget::scrollToTop()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    verticalScrollBar()->setValue(0);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::scrollToBottom()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    verticalScrollBar()->setValue(verticalScrollBar()->maximum());

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::scrollToCell(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (row<0 || column<0)
    {
        horizontalScrollBar()->setValue(0);
        verticalScrollBar()->setValue(0);
    }
    else
    {
        QSize areaSize=viewport()->size();
        QRect aCellRect=cellRectangle(row, column);

        if (aCellRect.left()-mVerticalHeader_TotalWidth<horizontalScrollBar()->value())
        {
            horizontalScrollBar()->setValue(aCellRect.left()-mVerticalHeader_TotalWidth);
        }
        else
        if (aCellRect.right()>horizontalScrollBar()->value()+areaSize.width())
        {
            horizontalScrollBar()->setValue(aCellRect.right()-areaSize.width());
        }

        if (aCellRect.top()-mHorizontalHeader_TotalHeight<verticalScrollBar()->value())
        {
            verticalScrollBar()->setValue(aCellRect.top()-mHorizontalHeader_TotalHeight);
        }
        else
        if (aCellRect.bottom()>verticalScrollBar()->value()+areaSize.height())
        {
            verticalScrollBar()->setValue(aCellRect.bottom()-areaSize.height());
        }
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::scrollToCurrentCell()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    scrollToCell(mCurrentRow, mCurrentColumn);

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mData.length());
    FASTTABLE_ASSERT(column>=0 && column<mData.at(row).length());

    mData[row][column]=text;

    viewport()->update();

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data.length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(row).length());

    mHorizontalHeader_Data[row][column]=text;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_SetText(const int column, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    for (int i=0; i<mHorizontalHeader_RowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_Data.length());
        FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data.at(i).length());

        mHorizontalHeader_Data[i][column]=text;
    }

    viewport()->update();

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data.at(row).length());

    mVerticalHeader_Data[row][column]=text;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data.length());

    for (int i=0; i<mVerticalHeader_ColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mVerticalHeader_Data.at(row).length());

        mVerticalHeader_Data[row][i]=text;
    }

    viewport()->update();

    FASTTABLE_END_PROFILE;
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
    FASTTABLE_START_PROFILE;

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

            mVerticalHeader_SelectedRows[row]++;
            mHorizontalHeader_SelectedColumns[column]++;
        }
        else
        {
            for (int i=0; i<mCurSelection.length(); ++i)
            {
                if (mCurSelection.at(i).y()==row)
                {
                    if (mCurSelection.at(i).x()==column)
                    {
                        mCurSelection.removeAt(i);
                        break;
                    }
                }
            }

            mVerticalHeader_SelectedRows[row]--;
            mHorizontalHeader_SelectedColumns[column]--;
        }

        viewport()->update();
    }

    FASTTABLE_END_PROFILE;
}

QList<QPoint> CustomFastTableWidget::selectedCells()
{
    FASTTABLE_DEBUG;
    return mCurSelection;
}

QList<QRect> CustomFastTableWidget::selectedRanges()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QList<QRect> res;

    for (int i=0; i<mRowCount; i++)
    {
        for (int j=0; j<mColumnCount; j++)
        {
            if (mSelectedCells.at(i).at(j))
            {
                bool good=true;

                for (int k=0; k<res.length(); k++)
                {
                    if (res.at(k).contains(j, i, false))
                    {
                        good=false;
                        break;
                    }
                }

                if (good)
                {
                    int width=1;

                    while (j+width<mColumnCount && mSelectedCells.at(i).at(j+width))
                    {
                        width++;
                    }

                    int height=1;

                    while (i+height<mRowCount)
                    {
                        for (int k=j; k<j+width; k++)
                        {
                            if (!mSelectedCells.at(i+height).at(k))
                            {
                                good=false;
                                break;
                            }
                        }

                        if (!good)
                        {
                            break;
                        }

                        height++;
                    }

                    res.append(QRect(j, i, width, height));
                }
            }
        }
    }

    FASTTABLE_END_PROFILE;
    return res;
}

QPoint CustomFastTableWidget::topLeftSelectedCell()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mCurSelection.length()==0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    for (int i=0; i<mRowCount; i++)
    {
        for (int j=0; j<mColumnCount; j++)
        {
            if (mSelectedCells.at(i).at(j))
            {
                FASTTABLE_END_PROFILE;
                return QPoint(j, i);
            }
        }
    }

    FASTTABLE_END_PROFILE;
    return QPoint(-1, -1);
}

bool CustomFastTableWidget::columnHasSelection(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns.length());

    return mHorizontalHeader_SelectedColumns.at(column)!=0;
}

bool CustomFastTableWidget::rowHasSelection(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows.length());

    return mVerticalHeader_SelectedRows.at(row)!=0;
}

QPoint CustomFastTableWidget::currentCell()
{
    FASTTABLE_DEBUG;
    return QPoint(mCurrentColumn, mCurrentRow);
}

void CustomFastTableWidget::setCurrentCell(int row, int column, const bool keepSelection)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (row<0 || column<0 || row>=mRowCount || column>=mColumnCount)
    {
        row=-1;
        column=-1;
    }

    if (
        mCurrentRow!=row
        ||
        mCurrentColumn!=column
        ||
        (
         !keepSelection
         &&
         (
          mCurSelection.length()>1
          ||
          (
           row>=0
           &&
           !mSelectedCells.at(row).at(column)
          )
         )
        )
       )
    {
        mCurrentRow=row;
        mCurrentColumn=column;

        if (!keepSelection)
        {
            unselectAll();

            if (row>=0)
            {
                setCellSelected(row, column, true);
            }
        }

        viewport()->update();
    }

    FASTTABLE_END_PROFILE;
}

int CustomFastTableWidget::currentRow()
{
    FASTTABLE_DEBUG;
    return mCurrentRow;
}

void CustomFastTableWidget::setCurrentRow(const int row, const bool keepSelection)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    setCurrentCell(row, mCurrentColumn, keepSelection)

    FASTTABLE_END_PROFILE;
}

int CustomFastTableWidget::currentColumn()
{
    FASTTABLE_DEBUG;
    return mCurrentColumn;
}

void CustomFastTableWidget::setCurrentColumn(const int column, const bool keepSelection)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    setCurrentCell(mCurrentRow, column, keepSelection)

    FASTTABLE_END_PROFILE;
}

QPoint CustomFastTableWidget::cellAt(const int x, const int y)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QSize areaSize=viewport()->size();

    if (x<mVerticalHeader_TotalWidth || y<mHorizontalHeader_TotalHeight || x>=areaSize.width() || y>=areaSize.height() || mVisibleLeft<0 || mVisibleTop<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    FASTTABLE_ASSERT(mVisibleBottom<mOffsetY.length());
    FASTTABLE_ASSERT(mVisibleBottom<mRowHeights.length());
    FASTTABLE_ASSERT(mVisibleRight<mOffsetX.length());
    FASTTABLE_ASSERT(mVisibleRight<mColumnWidths.length());

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    int resX=-1;

    for (int i=mVisibleLeft; i<=mVisibleRight; ++i)
    {
        if (x>=offsetX+mOffsetX.at(i) && (mColumnWidths.at(i)<=0 || x<offsetX+mOffsetX.at(i)+mColumnWidths.at(i)))
        {
            resX=i;
            break;
        }
    }

    if (resX<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }



    int resY=-1;

    for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
    {
        if (y>=offsetY+mOffsetY.at(i) && (mRowHeights.at(i)<=0 || y<offsetY+mOffsetY.at(i)+mRowHeights.at(i)))
        {
            resY=i;
            break;
        }
    }

    if (resY<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    FASTTABLE_END_PROFILE;
    return QPoint(resX, resY);
}

QPoint CustomFastTableWidget::horizontalHeader_CellAt(const int x, const int y)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QSize areaSize=viewport()->size();

    if (x<mVerticalHeader_TotalWidth || y<0 || x>=areaSize.width() || y>=mHorizontalHeader_TotalHeight || y>=areaSize.height() || mVisibleLeft<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_OffsetY.length());
    FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowHeights.length());
    FASTTABLE_ASSERT(mVisibleRight<mOffsetX.length());
    FASTTABLE_ASSERT(mVisibleRight<mColumnWidths.length());

    int offsetX=-horizontalScrollBar()->value();

    int resX=-1;

    for (int i=mVisibleLeft; i<=mVisibleRight; ++i)
    {
        if (x>=offsetX+mOffsetX.at(i) && (mColumnWidths.at(i)<=0 || x<offsetX+mOffsetX.at(i)+mColumnWidths.at(i)))
        {
            resX=i;
            break;
        }
    }

    if (resX<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }



    int resY=-1;

    for (int i=0; i<=mHorizontalHeader_VisibleBottom; ++i)
    {
        if (y>=mHorizontalHeader_OffsetY.at(i) && (mHorizontalHeader_RowHeights.at(i)<=0 || y<mHorizontalHeader_OffsetY.at(i)+mHorizontalHeader_RowHeights.at(i)))
        {
            resY=i;
            break;
        }
    }

    if (resY<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    FASTTABLE_END_PROFILE;
    return QPoint(resX, resY);
}

QPoint CustomFastTableWidget::verticalHeader_CellAt(const int x, const int y)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QSize areaSize=viewport()->size();

    if (x<0 || y<mHorizontalHeader_TotalHeight || x>=mVerticalHeader_TotalWidth || x>=areaSize.width() || y>=areaSize.height() || mVisibleTop<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    FASTTABLE_ASSERT(mVisibleBottom<mOffsetY.length());
    FASTTABLE_ASSERT(mVisibleBottom<mRowHeights.length());
    FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_OffsetX.length());
    FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_ColumnWidths.length());

    int offsetY=-verticalScrollBar()->value();

    int resX=-1;

    for (int i=0; i<=mVerticalHeader_VisibleRight; ++i)
    {
        if (x>=mVerticalHeader_OffsetX.at(i) && (mVerticalHeader_ColumnWidths.at(i)<=0 || x<mVerticalHeader_OffsetX.at(i)+mVerticalHeader_ColumnWidths.at(i)))
        {
            resX=i;
            break;
        }
    }

    if (resX<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }



    int resY=-1;

    for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
    {
        if (y>=offsetY+mOffsetY.at(i) && (mRowHeights.at(i)<=0 || y<offsetY+mOffsetY.at(i)+mRowHeights.at(i)))
        {
            resY=i;
            break;
        }
    }

    if (resY<0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    FASTTABLE_END_PROFILE;
    return QPoint(resX, resY);
}

bool CustomFastTableWidget::atTopLeftCorner(const int x, const int y)
{
    FASTTABLE_DEBUG;

    QSize areaSize=viewport()->size();

    return x>=0 && y>=0 && x<mVerticalHeader_TotalWidth && y<mHorizontalHeader_TotalHeight && x<areaSize.width() && y<areaSize.height();
}
