#include "customfasttablewidget.h"

CustomFastTableWidget::CustomFastTableWidget(QWidget *parent) :
    QAbstractScrollArea(parent),
    mMouseEvent(QEvent::MouseMove, QPoint(0, 0), Qt::NoButton, Qt::NoButton, Qt::NoModifier)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    init(true);

    FASTTABLE_END_PROFILE;
}

CustomFastTableWidget::CustomFastTableWidget(const bool aUseInternalData, QWidget *parent) :
    QAbstractScrollArea(parent),
    mMouseEvent(QEvent::MouseMove, QPoint(0, 0), Qt::NoButton, Qt::NoButton, Qt::NoModifier)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    init(aUseInternalData);

    FASTTABLE_END_PROFILE;
}

CustomFastTableWidget::~CustomFastTableWidget()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    clear();
    deleteLists();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::init(const bool aUseInternalData)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mUseInternalData=aUseInternalData;

    createLists();

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

    mAlternatingRowColors=false;
    mHorizontalHeaderStretchLastSection=false;
    mVerticalHeaderStretchLastSection=false;

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

    mMouseHoldTimer.setInterval(5);
    connect(&mMouseHoldTimer, SIGNAL(timeout()), this, SLOT(mouseHoldTick()));

    mEditable=true;
    mEditCellRow=-1;
    mEditCellColumn=-1;
    mEditor=0;

    setMouseTracking(true);

    horizontalScrollBar()->setSingleStep(100);
    verticalScrollBar()->setSingleStep(100);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged(int)));

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::createLists()
{
    if (mUseInternalData)
    {
        mData                         = new QList< QStringList >();
    }
    else
    {
        mData                         = 0;
    }

    mRowHeights                       = new QList< qint16 >();
    mColumnWidths                     = new QList< qint16 >();
    mOffsetX                          = new QList< int >();
    mOffsetY                          = new QList< int >();

    mHorizontalHeader_Data            = new QList< QStringList >();
    mHorizontalHeader_RowHeights      = new QList< qint16 >();
    mHorizontalHeader_OffsetY         = new QList< int >();

    mVerticalHeader_Data              = new QList< QStringList >();
    mVerticalHeader_ColumnWidths      = new QList< qint16 >();
    mVerticalHeader_OffsetX           = new QList< int >();

    mSelectedCells                    = new QList< QList<bool> >();
    mCurSelection                     = new QList< QPoint >();
    mHorizontalHeader_SelectedColumns = new QList< int >();
    mVerticalHeader_SelectedRows      = new QList< int >();

    mMouseSelectedCells               = new QList< QList<bool> >();
}

void CustomFastTableWidget::deleteLists()
{
    if (mData)
    {
        delete mData;
    }

    delete mRowHeights;
    delete mColumnWidths;
    delete mOffsetX;
    delete mOffsetY;

    delete mHorizontalHeader_Data;
    delete mHorizontalHeader_RowHeights;
    delete mHorizontalHeader_OffsetY;

    delete mVerticalHeader_Data;
    delete mVerticalHeader_ColumnWidths;
    delete mVerticalHeader_OffsetX;

    delete mSelectedCells;
    delete mCurSelection;
    delete mHorizontalHeader_SelectedColumns;
    delete mVerticalHeader_SelectedRows;

    delete mMouseSelectedCells;
}

bool CustomFastTableWidget::updatesEnabled() const
{
    return viewport()->updatesEnabled();
}

void CustomFastTableWidget::setUpdatesEnabled(bool enable)
{
    viewport()->setUpdatesEnabled(enable);
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
            int aNextRow=mCurrentRow-1;

            while (aNextRow>=0 && !rowVisible(aNextRow))
            {
                --aNextRow;
            }

            if (aNextRow>=0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, aNextRow);
                }
                else
                {
                    setCurrentCell(aNextRow, mCurrentColumn);

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
            int aNextRow=mCurrentRow+1;

            while (aNextRow<mRowCount && !rowVisible(aNextRow))
            {
                ++aNextRow;
            }

            if (aNextRow<mRowCount)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, aNextRow);
                }
                else
                {
                    setCurrentCell(aNextRow, mCurrentColumn);

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
            int aNextColumn=mCurrentColumn-1;

            while (aNextColumn>=0 && !columnVisible(aNextColumn))
            {
                --aNextColumn;
            }

            if (aNextColumn>=0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(aNextColumn, mCurrentRow);
                }
                else
                {
                    setCurrentCell(mCurrentRow, aNextColumn);

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
            int aNextColumn=mCurrentColumn+1;

            while (aNextColumn<mColumnCount && !columnVisible(aNextColumn))
            {
                ++aNextColumn;
            }

            if (aNextColumn<mColumnCount)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(aNextColumn, mCurrentRow);
                }
                else
                {
                    setCurrentCell(mCurrentRow, aNextColumn);

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
            int aNextRow=mCurrentRow;
            int aGoodRow;
            int aCount=0;

            for (int i=0; i<10; ++i)
            {
                do
                {
                    --aNextRow;
                } while (aNextRow>=0 && !rowVisible(aNextRow));

                if (aNextRow>=0)
                {
                    aGoodRow=aNextRow;
                    ++aCount;
                }
                else
                {
                    break;
                }
            }

            if (aCount>0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, aGoodRow);
                }
                else
                {
                    setCurrentCell(aGoodRow, mCurrentColumn);

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
            int aNextRow=mCurrentRow;
            int aGoodRow;
            int aCount=0;

            for (int i=0; i<10; ++i)
            {
                do
                {
                    ++aNextRow;
                } while (aNextRow<mRowCount && !rowVisible(aNextRow));

                if (aNextRow<mRowCount)
                {
                    aGoodRow=aNextRow;
                    ++aCount;
                }
                else
                {
                    break;
                }
            }

            if (aCount>0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, aGoodRow);
                }
                else
                {
                    setCurrentCell(aGoodRow, mCurrentColumn);

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
            int aNextRow=0;

            while (aNextRow<mRowCount && !rowVisible(aNextRow))
            {
                ++aNextRow;
            }

            if (aNextRow<mRowCount)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, aNextRow);
                }
                else
                {
                    setCurrentCell(aNextRow, mCurrentColumn);

                    initShiftSelection();
                }
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
            int aNextRow=mRowCount-1;

            while (aNextRow>=0 && !rowVisible(aNextRow))
            {
                --aNextRow;
            }

            if (aNextRow>=0)
            {
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    initShiftSelectionForKeyboard();

                    selectRangeForHandlers(mCurrentColumn, aNextRow);
                }
                else
                {
                    setCurrentCell(aNextRow, mCurrentColumn);

                    initShiftSelection();
                }
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
        QList<QRect> aRanges=selectedRanges();

        if (aRanges.length()>0)
        {
            QRect aCopyRect=aRanges.at(0);
            QString toClipboard="";

            for (int i=aCopyRect.top(); i<=aCopyRect.bottom(); i++)
            {
                if (!rowVisible(i))
                {
                    continue;
                }

                if (toClipboard!="")
                {
                    toClipboard.append("\n");
                }

                QString aRow="";

                for (int j=aCopyRect.left(); j<=aCopyRect.right(); j++)
                {
                    if (!columnVisible(j))
                    {
                        continue;
                    }

                    if (aRow!="")
                    {
                        aRow.append("\t");
                    }

                    aRow.append(text(i, j));
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

bool CustomFastTableWidget::focusNextPrevChild(bool next)
{
    if (mCurrentRow<0 || mCurrentColumn<0)
    {
        setCurrentCell(0, 0);

        initShiftSelection();
    }
    else
    {
        if (next)
        {
            if (mCurrentColumn<mColumnCount-1)
            {
                setCurrentCell(mCurrentRow, mCurrentColumn+1);
            }
            else
            {
                if (mCurrentRow<mRowCount-1)
                {
                    setCurrentCell(mCurrentRow+1, 0);
                }
                else
                {
                    setCurrentCell(0, 0);
                }
            }
        }
        else
        {
            if (mCurrentColumn>0)
            {
                setCurrentCell(mCurrentRow, mCurrentColumn-1);
            }
            else
            {
                if (mCurrentRow>0)
                {
                    setCurrentCell(mCurrentRow-1, mColumnCount-1);
                }
                else
                {
                    setCurrentCell(mRowCount-1, mColumnCount-1);
                }
            }
        }

        initShiftSelection();
    }

    scrollToCurrentCell();

    return true;
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
                mMouseSelectedCells->clear();

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

            emit cellClicked(pos.x(), pos.y());
        }
        else
        {
            mLastX=pos.x();
            mLastY=pos.y();

            if (event->button()==Qt::LeftButton)
            {
                mMouseSelectedCells->clear();

                mMouseXForShift=mLastX;
                mMouseYForShift=mLastY;

                mMouseLocationForShift=mMouseLocation;

                if (mCtrlPressed)
                {
                    setCurrentCell(mLastY, mLastX, true);

                    FASTTABLE_ASSERT(mLastY>=0 && mLastY<mSelectedCells->length());
                    FASTTABLE_ASSERT(mLastX>=0 && mLastX<mSelectedCells->at(mLastY).length());

                    setCellSelected(mLastY, mLastX, !mSelectedCells->at(mLastY).at(mLastX));
                }
                else
                {
                    setCurrentCell(mLastY, mLastX);
                }

                QList<bool> aRow;
                aRow.append(mSelectedCells->at(mLastY).at(mLastX));

                mMouseSelectedCells->append(aRow);
            }
            else
            {
                if (!mSelectedCells->at(mLastY).at(mLastX))
                {
                    mMouseSelectedCells->clear();

                    mMouseXForShift=mLastX;
                    mMouseYForShift=mLastY;

                    mMouseLocationForShift=mMouseLocation;

                    setCurrentCell(mLastY, mLastX);
                }
            }

            if (event->button()==Qt::LeftButton)
            {
                emit cellClicked(pos.y(), pos.x());
            }
            else
            if (event->button()==Qt::RightButton)
            {
                emit cellRightClicked(pos.y(), pos.x());
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
                event->button()==Qt::LeftButton
                &&
                (
                 x<offsetX+mOffsetX->at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                 ||
                 x>offsetX+mOffsetX->at(mLastX)+mColumnWidths->at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                )
               )
            {
                mMouseResizeCell=mVerticalHeader_ColumnCount+mLastX;

                if (x<offsetX+mOffsetX->at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                {
                    int aLastX=mLastX;

                    while (aLastX>0 && !columnVisible(aLastX-1))
                    {
                        --aLastX;
                    }

                    mMouseResizeCell=mVerticalHeader_ColumnCount+aLastX-1;

                    if (aLastX==0)
                    {
                        mMouseResizeLineX=mVerticalHeader_TotalWidth;
                    }
                    else
                    {
                        mMouseResizeLineX=mOffsetX->at(aLastX-1)+mColumnWidths->at(aLastX-1);
                    }
                }
                else
                {
                    mMouseResizeLineX=mOffsetX->at(mLastX)+mColumnWidths->at(mLastX);
                }

                viewport()->update();
            }
            else
            if (
                !mCtrlPressed
                &&
                !mShiftPressed
                &&
                event->button()==Qt::LeftButton
                &&
                (
                 (
                  mLastY>0
                  &&
                  y<mHorizontalHeader_OffsetY->at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                 )
                 ||
                 y>mHorizontalHeader_OffsetY->at(mLastY)+mHorizontalHeader_RowHeights->at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                )
               )
            {
                mMouseResizeCell=mLastY;

                if (y<mHorizontalHeader_OffsetY->at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                {
                    --mMouseResizeCell;

                    while (mMouseResizeCell>=0 && mHorizontalHeader_RowHeights->at(mMouseResizeCell)<=0)
                    {
                        --mMouseResizeCell;
                    }
                }

                if (mMouseResizeCell>=0)
                {
                    mMouseResizeLineY=mHorizontalHeader_OffsetY->at(mMouseResizeCell)+mHorizontalHeader_RowHeights->at(mMouseResizeCell);

                    viewport()->update();
                }
                else
                {
                    mMousePressed=false;
                    mCtrlPressed=false;
                    mShiftPressed=false;
                    mMouseLocation=InMiddleWorld;
                    mLastX=-1;
                    mLastY=-1;
                }
            }
            else
            {
                if (mShiftPressed && event->button()==Qt::LeftButton)
                {
                    if (mMouseLocationForShift!=mMouseLocation)
                    {
                        mMouseLocationForShift=mMouseLocation;
                        unselectAll();
                        mMouseSelectedCells->clear();
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

                    if (mMouseSelectedCells->length()==0)
                    {
                        int minX=qMin(mCurrentColumn, mLastX);
                        int maxX=qMax(mCurrentColumn, mLastX);

                        for (int i=0; i<mRowCount; i++)
                        {
                            QList<bool> aRow;

                            for (int j=minX; j<=maxX; j++)
                            {
                                aRow.append(j==mLastX || mSelectedCells->at(i).at(j));
                            }

                            mMouseSelectedCells->append(aRow);
                        }
                    }

                    horizontalHeader_SelectRangeForHandlers(pos.x());
                }
                else
                {
                    mMouseSelectedCells->clear();

                    mMouseXForShift=mLastX;
                    mMouseYForShift=mLastY;

                    mMouseLocationForShift=mMouseLocation;

                    if (mCtrlPressed && event->button()==Qt::LeftButton)
                    {
                        setCurrentCell(mRowCount-1, mLastX, true);

                        FASTTABLE_ASSERT(mSelectedCells->length()>0);
                        FASTTABLE_ASSERT(mLastX>=0 && mLastX<mSelectedCells->at(0).length());

                        if (mSelectedCells->at(0).at(mLastX))
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
                        aRow.append(mSelectedCells->at(i).at(mLastX));

                        mMouseSelectedCells->append(aRow);
                    }

                    viewport()->update();

                    if (event->button()==Qt::LeftButton)
                    {
                        emit horizontalHeader_CellClicked(pos.y(), pos.x());
                    }
                    else
                    if (event->button()==Qt::RightButton)
                    {
                        emit horizontalHeader_CellRightClicked(pos.y(), pos.x());
                    }
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
                    event->button()==Qt::LeftButton
                    &&
                    (
                     (
                      mLastX>0 && x<mVerticalHeader_OffsetX->at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                     )
                     ||
                     x>mVerticalHeader_OffsetX->at(mLastX)+mVerticalHeader_ColumnWidths->at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    )
                   )
                {
                    mMouseResizeCell=mLastX;

                    if (x<mVerticalHeader_OffsetX->at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                    {
                        --mMouseResizeCell;

                        while (mMouseResizeCell>=0 && mVerticalHeader_ColumnWidths->at(mMouseResizeCell)<=0)
                        {
                            --mMouseResizeCell;
                        }
                    }

                    if (mMouseResizeCell>=0)
                    {
                        mMouseResizeLineX=mVerticalHeader_OffsetX->at(mMouseResizeCell)+mVerticalHeader_ColumnWidths->at(mMouseResizeCell);

                        viewport()->update();
                    }
                    else
                    {
                        mMousePressed=false;
                        mCtrlPressed=false;
                        mShiftPressed=false;
                        mMouseLocation=InMiddleWorld;
                        mLastX=-1;
                        mLastY=-1;
                    }
                }
                else
                if (
                    !mCtrlPressed
                    &&
                    !mShiftPressed
                    &&
                    event->button()==Qt::LeftButton
                    &&
                    (
                     y<offsetY+mOffsetY->at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                     ||
                     y>offsetY+mOffsetY->at(mLastY)+mRowHeights->at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    )
                   )
                {
                    mMouseResizeCell=mHorizontalHeader_RowCount+mLastY;

                    if (y<offsetY+mOffsetY->at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD)
                    {
                        int aLastY=mLastY;

                        while (aLastY>0 && !rowVisible(aLastY-1))
                        {
                            --aLastY;
                        }

                        mMouseResizeCell=mHorizontalHeader_RowCount+aLastY-1;

                        if (aLastY==0)
                        {
                            mMouseResizeLineY=mHorizontalHeader_TotalHeight;
                        }
                        else
                        {
                            mMouseResizeLineY=mOffsetY->at(aLastY-1)+mRowHeights->at(aLastY-1);
                        }
                    }
                    else
                    {
                        mMouseResizeLineY=mOffsetY->at(mLastY)+mRowHeights->at(mLastY);
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
                            mMouseSelectedCells->clear();
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

                        if (mMouseSelectedCells->length()==0)
                        {
                            int minY=qMin(mCurrentRow, mLastY);
                            int maxY=qMax(mCurrentRow, mLastY);

                            for (int i=minY; i<=maxY; i++)
                            {
                                QList<bool> aRow;

                                for (int j=0; j<mColumnCount; j++)
                                {
                                    aRow.append(i==mLastY || mSelectedCells->at(i).at(j));
                                }

                                mMouseSelectedCells->append(aRow);
                            }
                        }

                        verticalHeader_SelectRangeForHandlers(pos.y());
                    }
                    else
                    {
                        mMouseSelectedCells->clear();

                        mMouseXForShift=mLastX;
                        mMouseYForShift=mLastY;

                        mMouseLocationForShift=mMouseLocation;

                        if (mCtrlPressed && event->button()==Qt::LeftButton)
                        {
                            setCurrentCell(mLastY, mColumnCount-1, true);

                            FASTTABLE_ASSERT(mLastY>=0 && mLastY<mSelectedCells->length());
                            FASTTABLE_ASSERT(mSelectedCells->at(mLastY).length()>0);

                            if (mSelectedCells->at(mLastY).at(0))
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
                            aRow.append(mSelectedCells->at(mLastY).at(i));
                        }

                        mMouseSelectedCells->append(aRow);

                        viewport()->update();

                        if (event->button()==Qt::LeftButton)
                        {
                            emit verticalHeader_CellClicked(pos.y(), pos.x());
                        }
                        else
                        if (event->button()==Qt::RightButton)
                        {
                            emit verticalHeader_CellRightClicked(pos.y(), pos.x());
                        }
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
                    event->button()==Qt::LeftButton
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
                    event->button()==Qt::LeftButton
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

                    if (event->button()==Qt::LeftButton)
                    {
                        emit topLeftCornerClicked();
                    }
                    else
                    if (event->button()==Qt::RightButton)
                    {
                        emit topLeftCornerRightClicked();
                    }
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

            if (event!=&mMouseEvent)
            {
                mMouseEvent=*event;
            }
        }

        if (mMouseLocation==InCell)
        {
            int resX=mCurrentColumn;
            int resY=mCurrentRow;

            while (resX>0 && x<offsetX+mOffsetX->at(resX) && (mColumnWidths->at(resX)<=0 || x<offsetX+mOffsetX->at(resX)+mColumnWidths->at(resX)))
            {
                resX--;
            }

            while (resX<mColumnCount-1 && x>offsetX+mOffsetX->at(resX) && (mColumnWidths->at(resX)<=0 || x>offsetX+mOffsetX->at(resX)+mColumnWidths->at(resX)))
            {
                resX++;
            }

            while (resY>0 && y<offsetY+mOffsetY->at(resY) && (mRowHeights->at(resY)<=0 || y<offsetY+mOffsetY->at(resY)+mRowHeights->at(resY)))
            {
                resY--;
            }

            while (resY<mRowCount-1 && y>offsetY+mOffsetY->at(resY) && (mRowHeights->at(resY)<=0 || y>offsetY+mOffsetY->at(resY)+mRowHeights->at(resY)))
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
                    newWidth=mMouseResizeLineX-mOffsetX->at(mMouseResizeCell-mVerticalHeader_ColumnCount);
                }
                else
                {
                    newWidth=offsetX+mMouseResizeLineX-mVerticalHeader_OffsetX->at(mMouseResizeCell);
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
                    newHeight=mMouseResizeLineY-mOffsetY->at(mMouseResizeCell-mHorizontalHeader_RowCount);
                }
                else
                {
                    newHeight=offsetY+mMouseResizeLineY-mHorizontalHeader_OffsetY->at(mMouseResizeCell);
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

                    while (resX>0 && x<offsetX+mOffsetX->at(resX) && (mColumnWidths->at(resX)<=0 || x<offsetX+mOffsetX->at(resX)+mColumnWidths->at(resX)))
                    {
                        resX--;
                    }

                    while (resX<mColumnCount-1 && x>offsetX+mOffsetX->at(resX) && (mColumnWidths->at(resX)<=0 || x>offsetX+mOffsetX->at(resX)+mColumnWidths->at(resX)))
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

                    while (resY>0 && y<offsetY+mOffsetY->at(resY) && (mRowHeights->at(resY)<=0 || y<offsetY+mOffsetY->at(resY)+mRowHeights->at(resY)))
                    {
                        resY--;
                    }

                    while (resY<mRowCount-1 && y>offsetY+mOffsetY->at(resY) && (mRowHeights->at(resY)<=0 || y>offsetY+mOffsetY->at(resY)+mRowHeights->at(resY)))
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
                    x<offsetX+mOffsetX->at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    ||
                    x>offsetX+mOffsetX->at(mLastX)+mColumnWidths->at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                   )
                {
                    setCursor(Qt::SplitHCursor);
                }
                else
                if (
                    (
                     mLastY>0 && y<mHorizontalHeader_OffsetY->at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                    )
                    ||
                    y>mHorizontalHeader_OffsetY->at(mLastY)+mHorizontalHeader_RowHeights->at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
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
                         mLastX>0 && x<mVerticalHeader_OffsetX->at(mLastX)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                        )
                        ||
                        x>mVerticalHeader_OffsetX->at(mLastX)+mVerticalHeader_ColumnWidths->at(mLastX)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
                       )
                    {
                        setCursor(Qt::SplitHCursor);
                    }
                    else
                    if (
                        y<offsetY+mOffsetY->at(mLastY)+FASTTABLE_MOUSE_RESIZE_THRESHOLD
                        ||
                        y>offsetY+mOffsetY->at(mLastY)+mRowHeights->at(mLastY)-FASTTABLE_MOUSE_RESIZE_THRESHOLD
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

    mMouseSelectedCells->clear();
    mMouseXForShift=mCurrentColumn;
    mMouseYForShift=mCurrentRow;

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::fillShiftSelection()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mMouseSelectedCells->length()==0)
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

            mMouseSelectedCells->append(aRow);
        }

        (*mMouseSelectedCells)[mMouseYForShift-minY][mMouseXForShift-minX]=mSelectedCells->at(mMouseYForShift).at(mMouseXForShift);
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

    // Do not process mouse selection if selection was changed programmatically during mouse button holding
    {
        if (lastMaxY-lastMinY+1!=mMouseSelectedCells->length())
        {
            return;
        }

        for (int i=lastMinY; i<=lastMaxY; i++)
        {
            if (lastMaxX-lastMinX+1!=mMouseSelectedCells->at(i-lastMinY).length())
            {
                return;
            }
        }
    }

    for (int i=lastMinY; i<=lastMaxY; i++)
    {
        for (int j=lastMinX; j<=lastMaxX; j++)
        {
            setCellSelected(i, j, mMouseSelectedCells->at(i-lastMinY).at(j-lastMinX));
        }
    }

    while (mMouseSelectedCells->length()>maxY-minY+1)
    {
        mMouseSelectedCells->removeLast();
    }

    while (mMouseSelectedCells->length()<maxY-minY+1)
    {
        mMouseSelectedCells->append(QList<bool>());
    }

    setCurrentCell(resY, resX, true);

    bool aSelected=mSelectedCells->at(mLastY).at(mLastX);

    for (int i=minY; i<=maxY; i++)
    {
        while (mMouseSelectedCells->at(i-minY).length()>maxX-minX+1)
        {
            (*mMouseSelectedCells)[i-minY].removeLast();
        }

        while (mMouseSelectedCells->at(i-minY).length()<maxX-minX+1)
        {
            (*mMouseSelectedCells)[i-minY].append(false);
        }

        for (int j=minX; j<=maxX; j++)
        {
            (*mMouseSelectedCells)[i-minY][j-minX]=mSelectedCells->at(i).at(j);

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

    FASTTABLE_ASSERT(mMouseSelectedCells->length()==mRowCount);

    for (int i=0; i<mRowCount; i++)
    {
        FASTTABLE_ASSERT(lastMaxX-lastMinX+1==mMouseSelectedCells->at(i).length());

        for (int j=lastMinX; j<=lastMaxX; j++)
        {
            setCellSelected(i, j, mMouseSelectedCells->at(i).at(j-lastMinX));
        }
    }

    setCurrentCell(mRowCount-1, resX, true);

    bool aSelected=mSelectedCells->at(0).at(mLastX);

    for (int i=0; i<mRowCount; i++)
    {
        while (mMouseSelectedCells->at(i).length()>maxX-minX+1)
        {
            (*mMouseSelectedCells)[i].removeLast();
        }

        while (mMouseSelectedCells->at(i).length()<maxX-minX+1)
        {
            (*mMouseSelectedCells)[i].append(false);
        }

        for (int j=minX; j<=maxX; j++)
        {
            (*mMouseSelectedCells)[i][j-minX]=mSelectedCells->at(i).at(j);

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

    FASTTABLE_ASSERT(lastMaxY-lastMinY+1==mMouseSelectedCells->length());

    for (int i=lastMinY; i<=lastMaxY; i++)
    {
        FASTTABLE_ASSERT(mMouseSelectedCells->at(i-lastMinY).length()==mColumnCount);

        for (int j=0; j<mColumnCount; j++)
        {
            setCellSelected(i, j, mMouseSelectedCells->at(i-lastMinY).at(j));
        }
    }

    while (mMouseSelectedCells->length()>maxY-minY+1)
    {
        mMouseSelectedCells->removeLast();
    }

    while (mMouseSelectedCells->length()<maxY-minY+1)
    {
        mMouseSelectedCells->append(QList<bool>());
    }

    setCurrentCell(resY, mColumnCount-1, true);

    bool aSelected=mSelectedCells->at(mLastY).at(0);

    for (int i=minY; i<=maxY; i++)
    {
        while (mMouseSelectedCells->at(i-minY).length()<mColumnCount)
        {
            (*mMouseSelectedCells)[i-minY].append(false);
        }

        for (int j=0; j<mColumnCount; j++)
        {
            (*mMouseSelectedCells)[i-minY][j]=mSelectedCells->at(i).at(j);

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
            if (mSelectedCells->at(0).at(0))
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

void CustomFastTableWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (event->button()==Qt::LeftButton)
    {
        int x=event->x();
        int y=event->y();

        QPoint pos;

        pos=cellAt(x, y);

        if (pos!=QPoint(-1, -1))
        {
            emit cellDoubleClicked(pos.y(), pos.x());
        }
        else
        {
            pos=horizontalHeader_CellAt(x, y);

            if (pos!=QPoint(-1, -1))
            {
                emit horizontalHeader_CellDoubleClicked(pos.y(), pos.x());
            }
            else
            {
                pos=verticalHeader_CellAt(x, y);

                if (pos!=QPoint(-1, -1))
                {
                    emit verticalHeader_CellDoubleClicked(pos.y(), pos.x());
                }
                else
                if (atTopLeftCorner(x, y))
                {
                    emit topLeftCornerDoubleClicked();
                }
            }
        }
    }

    QAbstractScrollArea::mouseDoubleClickEvent(event);

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

    updateSizes();
    QAbstractScrollArea::resizeEvent(event);

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::paintEvent(QPaintEvent * /*event*/)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    QPainter painter(viewport());

    painter.fillRect(0, 0, viewport()->width(), viewport()->height(), palette().color(QPalette::Window));

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    if (mVisibleLeft>=0 && mVisibleTop>=0)
    {
        FASTTABLE_ASSERT(mVisibleBottom<mOffsetY->length());
        FASTTABLE_ASSERT(mVisibleBottom<mRowHeights->length());
        FASTTABLE_ASSERT(mVisibleRight<mOffsetX->length());
        FASTTABLE_ASSERT(mVisibleRight<mColumnWidths->length());

        for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
        {
            for (int j=mVisibleLeft; j<=mVisibleRight; ++j)
            {
                if (mColumnWidths->at(j)>0 && mRowHeights->at(i)>0)
                {
                    paintCell(painter, offsetX+mOffsetX->at(j), offsetY+mOffsetY->at(i), mColumnWidths->at(j), mRowHeights->at(i), i, j, DrawCell);
                }
            }
        }
    }

    if (mHorizontalHeader_VisibleBottom>=0 && mVisibleLeft>=0)
    {
        FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_OffsetY->length());
        FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowHeights->length());
        FASTTABLE_ASSERT(mVisibleRight<mOffsetX->length());
        FASTTABLE_ASSERT(mVisibleRight<mColumnWidths->length());

        for (int i=0; i<=mHorizontalHeader_VisibleBottom; ++i)
        {
            for (int j=mVisibleLeft; j<=mVisibleRight; ++j)
            {
                if (mColumnWidths->at(j)>0 && mHorizontalHeader_RowHeights->at(i)>0)
                {
                    paintCell(painter, offsetX+mOffsetX->at(j), mHorizontalHeader_OffsetY->at(i), mColumnWidths->at(j), mHorizontalHeader_RowHeights->at(i), i, j, DrawHorizontalHeaderCell);
                }
            }
        }
    }

    if (mVerticalHeader_VisibleRight>=0 && mVisibleTop>=0)
    {
        FASTTABLE_ASSERT(mVisibleBottom<mOffsetY->length());
        FASTTABLE_ASSERT(mVisibleBottom<mRowHeights->length());
        FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_OffsetX->length());
        FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_ColumnWidths->length());

        for (int i=mVisibleTop; i<=mVisibleBottom; ++i)
        {
            for (int j=0; j<=mVerticalHeader_VisibleRight; ++j)
            {
                if (mVerticalHeader_ColumnWidths->at(j)>0 && mRowHeights->at(i)>0)
                {
                    paintCell(painter, mVerticalHeader_OffsetX->at(j), offsetY+mOffsetY->at(i), mVerticalHeader_ColumnWidths->at(j), mRowHeights->at(i), i, j, DrawVerticalHeaderCell);
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
    QBrush  aTextBackgroundBrush;
    QColor  *aBorderColor;
    QColor  *aTextColor;
    QColor  aForegroundColor;
    QString *aText;
    QString aTextString;
    QFont   *aFont;
    QFont   aTextFont;
    int     textFlags;

    QPalette aPalette=palette();

    switch (drawComponent)
    {
        case DrawCell:
        {
            FASTTABLE_ASSERT(row>=0 && row<mSelectedCells->length());
            FASTTABLE_ASSERT(column>=0 && column<mSelectedCells->at(row).length());

            aGridColor=&mGridColor;

            if (mSelectedCells->at(row).at(column))
            {
                aTextBackgroundBrush=aPalette.highlight();
                aForegroundColor=aPalette.color(QPalette::HighlightedText);
            }
            else
            {
                if (mUseInternalData && mAlternatingRowColors && (row & 1))
                {
                    aTextBackgroundBrush=aPalette.alternateBase();
                }
                else
                {
                    aTextBackgroundBrush=backgroundBrush(row, column);
                }

                aForegroundColor=foregroundColor(row, column);
            }

            aBackgroundBrush=&aTextBackgroundBrush;
            aTextColor=&aForegroundColor;



            aHeaderPressed=false;

            if (row==mCurrentRow && column==mCurrentColumn)
            {
                aBorderColor=&mCellBorderColor;
            }
            else
            {
                aBorderColor=0;
            }

            aTextString=text(row, column);
            aText=&aTextString;

            aTextFont=cellFont(row, column);
            aFont=&aTextFont;

            textFlags=cellTextFlags(row, column);
        }
        break;
        case DrawHorizontalHeaderCell:
        {
            FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data->length());
            FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data->at(row).length());
            FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns->length());

            aGridColor=&mHorizontalHeader_GridColor;
            aBackgroundBrush=&mHorizontalHeader_DefaultBackgroundBrush;

            if (mMouseLocation==InHorizontalHeaderCell)
            {
                if (mMousePressed)
                {
                    int minX=qMin(mCurrentColumn, mLastX);
                    int maxX=qMax(mCurrentColumn, mLastX);

                    if (
                        mHorizontalHeader_SelectedColumns->at(column)==mRowCount
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
                        if (mHorizontalHeader_SelectedColumns->at(column)==mRowCount)
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
                if (mHorizontalHeader_SelectedColumns->at(column)==mRowCount)
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
            aText=&(*mHorizontalHeader_Data)[row][column];

            aTextFont=font();
            aFont=&aTextFont;

            if (mHorizontalHeader_SelectedColumns->at(column))
            {
                aFont->setPointSize(aFont->pointSize()+1);
                aFont->setBold(true);
            }

            textFlags=FASTTABLE_HEADER_DEFAULT_TEXT_FLAG;
        }
        break;
        case DrawVerticalHeaderCell:
        {
            FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data->length());
            FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data->at(row).length());
            FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows->length());

            aGridColor=&mVerticalHeader_GridColor;
            aBackgroundBrush=&mVerticalHeader_DefaultBackgroundBrush;

            if (mMouseLocation==InVerticalHeaderCell)
            {
                if (mMousePressed)
                {
                    int minY=qMin(mCurrentRow, mLastY);
                    int maxY=qMax(mCurrentRow, mLastY);

                    if (
                        mVerticalHeader_SelectedRows->at(row)==mColumnCount
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
                        if (mVerticalHeader_SelectedRows->at(row)==mColumnCount)
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
                if (mVerticalHeader_SelectedRows->at(row)==mColumnCount)
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
            aText=&(*mVerticalHeader_Data)[row][column];

            if (*aText=="")
            {
                aTextString=QString::number(row+1);
                aText=&aTextString;
            }

            aTextFont=font();
            aFont=&aTextFont;

            if (mVerticalHeader_SelectedRows->at(row))
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

    if (width>FASTTABLE_TEXT_MARGIN*2 && height>FASTTABLE_TEXT_MARGIN*2 && aText)
    {
        painter.setPen(QPen(*aTextColor));
        painter.setFont(*aFont);
        painter.drawText(x+FASTTABLE_TEXT_MARGIN, y+FASTTABLE_TEXT_MARGIN, width-FASTTABLE_TEXT_MARGIN*2, height-FASTTABLE_TEXT_MARGIN*2, aTextFlags, *aText);
    }

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::paintCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const bool /*headerPressed*/, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
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

void CustomFastTableWidget::paintCellDefault(QPainter &painter, const int x, const int y, const int width, const int height, const bool /*headerPressed*/, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor)
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

void CustomFastTableWidget::scrollBarValueChanged(int /*value*/)
{
    FASTTABLE_FREQUENT_DEBUG;
    FASTTABLE_FREQUENT_START_PROFILE;

    updateVisibleRange();

    FASTTABLE_FREQUENT_END_PROFILE;
}

void CustomFastTableWidget::updateSizes()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mHorizontalHeaderStretchLastSection && mColumnCount>0)
    {
        int aTotalWidth=0;

        for (int i=0; i<mVerticalHeader_ColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mVerticalHeader_ColumnWidths->length());

            if (mVerticalHeader_ColumnWidths->at(i)>0)
            {
                aTotalWidth+=mVerticalHeader_ColumnWidths->at(i);
            }
        }

        for (int i=0; i<mColumnCount-1; ++i)
        {
            FASTTABLE_ASSERT(i<mColumnWidths->length());

            if (mColumnWidths->at(i)>0)
            {
                aTotalWidth+=mColumnWidths->at(i);
            }
        }

        int aColumnWidth=viewport()->width()-aTotalWidth-1;

        if (aColumnWidth<FASTTABLE_MOUSE_RESIZE_MINIMUM_WIDTH)
        {
            aColumnWidth=FASTTABLE_MOUSE_RESIZE_MINIMUM_WIDTH;
        }

        setColumnWidth(mColumnCount-1, aColumnWidth);
    }

    if (mVerticalHeaderStretchLastSection && mRowCount>0)
    {
        int aTotalHeight=0;

        for (int i=0; i<mHorizontalHeader_RowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mHorizontalHeader_RowHeights->length());

            if (mHorizontalHeader_RowHeights->at(i)>0)
            {
                aTotalHeight+=mHorizontalHeader_RowHeights->at(i);
            }
        }

        for (int i=0; i<mRowCount-1; ++i)
        {
            FASTTABLE_ASSERT(i<mRowHeights->length());

            if (mRowHeights->at(i)>0)
            {
                aTotalHeight+=mRowHeights->at(i);
            }
        }

        int aRowHeight=viewport()->height()-aTotalHeight-1;

        if (aRowHeight<FASTTABLE_MOUSE_RESIZE_MINIMUM_HEIGHT)
        {
            aRowHeight=FASTTABLE_MOUSE_RESIZE_MINIMUM_HEIGHT;
        }

        setRowHeight(mRowCount-1, aRowHeight);
    }

    updateBarsRanges();
    updateVisibleRange();

    FASTTABLE_END_PROFILE;
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

            FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_OffsetX->length());
            FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_ColumnWidths->length());

            while (mVerticalHeader_VisibleRight<mVerticalHeader_ColumnCount-1 && mVerticalHeader_OffsetX->at(mVerticalHeader_VisibleRight)<maxX && (mVerticalHeader_ColumnWidths->at(mVerticalHeader_VisibleRight)<=0 || mVerticalHeader_OffsetX->at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths->at(mVerticalHeader_VisibleRight)<maxX))
            {
                mVerticalHeader_VisibleRight++;
            }

            while (mVerticalHeader_VisibleRight>0 && mVerticalHeader_OffsetX->at(mVerticalHeader_VisibleRight)>maxX && (mVerticalHeader_ColumnWidths->at(mVerticalHeader_VisibleRight)<=0 || mVerticalHeader_OffsetX->at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths->at(mVerticalHeader_VisibleRight)>maxX))
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

            FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_OffsetY->length());
            FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowHeights->length());

            while (mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowCount-1 && mHorizontalHeader_OffsetY->at(mHorizontalHeader_VisibleBottom)<maxY && (mHorizontalHeader_RowHeights->at(mHorizontalHeader_VisibleBottom)<=0 || mHorizontalHeader_OffsetY->at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights->at(mHorizontalHeader_VisibleBottom)<maxY))
            {
                mHorizontalHeader_VisibleBottom++;
            }

            while (mHorizontalHeader_VisibleBottom>0 && mHorizontalHeader_OffsetY->at(mHorizontalHeader_VisibleBottom)>maxY && (mHorizontalHeader_RowHeights->at(mHorizontalHeader_VisibleBottom)<=0 || mHorizontalHeader_OffsetY->at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights->at(mHorizontalHeader_VisibleBottom)>maxY))
            {
                mHorizontalHeader_VisibleBottom--;
            }
        }

        if (
            mHorizontalHeader_VisibleBottom<0
            ||
            (
             mHorizontalHeader_RowHeights->at(mHorizontalHeader_VisibleBottom)<=0 ?
                (mHorizontalHeader_OffsetY->at(mHorizontalHeader_VisibleBottom)<maxY)
                :
                (mHorizontalHeader_OffsetY->at(mHorizontalHeader_VisibleBottom)+mHorizontalHeader_RowHeights->at(mHorizontalHeader_VisibleBottom)<maxY)
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

            FASTTABLE_ASSERT(mVisibleTop<mOffsetY->length());
            FASTTABLE_ASSERT(mVisibleTop<mRowHeights->length());
            FASTTABLE_ASSERT(mVisibleBottom<mOffsetY->length());
            FASTTABLE_ASSERT(mVisibleBottom<mRowHeights->length());

            while (mVisibleTop<mRowCount-1 && mOffsetY->at(mVisibleTop)<minY && (mRowHeights->at(mVisibleTop)<=0 || mOffsetY->at(mVisibleTop)+mRowHeights->at(mVisibleTop)<minY))
            {
                mVisibleTop++;
            }

            while (mVisibleTop>0 && mOffsetY->at(mVisibleTop)>minY && (mRowHeights->at(mVisibleTop)<=0 || mOffsetY->at(mVisibleTop)+mRowHeights->at(mVisibleTop)>minY))
            {
                mVisibleTop--;
            }

            while (mVisibleBottom<mRowCount-1 && mOffsetY->at(mVisibleBottom)<maxY && (mRowHeights->at(mVisibleBottom)<=0 || mOffsetY->at(mVisibleBottom)+mRowHeights->at(mVisibleBottom)<maxY))
            {
                mVisibleBottom++;
            }

            while (mVisibleBottom>0 && mOffsetY->at(mVisibleBottom)>maxY && (mRowHeights->at(mVisibleBottom)<=0 || mOffsetY->at(mVisibleBottom)+mRowHeights->at(mVisibleBottom)>maxY))
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
             mVerticalHeader_ColumnWidths->at(mVerticalHeader_VisibleRight)<=0?
                (mVerticalHeader_OffsetX->at(mVerticalHeader_VisibleRight)<maxX)
                :
                (mVerticalHeader_OffsetX->at(mVerticalHeader_VisibleRight)+mVerticalHeader_ColumnWidths->at(mVerticalHeader_VisibleRight)<maxX)
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

            FASTTABLE_ASSERT(mVisibleLeft<mOffsetX->length());
            FASTTABLE_ASSERT(mVisibleLeft<mColumnWidths->length());
            FASTTABLE_ASSERT(mVisibleRight<mOffsetX->length());
            FASTTABLE_ASSERT(mVisibleRight<mColumnWidths->length());

            while (mVisibleLeft<mColumnCount-1 && mOffsetX->at(mVisibleLeft)<minX && (mColumnWidths->at(mVisibleLeft)<=0 || mOffsetX->at(mVisibleLeft)+mColumnWidths->at(mVisibleLeft)<minX))
            {
                mVisibleLeft++;
            }

            while (mVisibleLeft>0 && mOffsetX->at(mVisibleLeft)>minX && (mColumnWidths->at(mVisibleLeft)<=0 || mOffsetX->at(mVisibleLeft)+mColumnWidths->at(mVisibleLeft)>minX))
            {
                mVisibleLeft--;
            }

            while (mVisibleRight<mColumnCount-1 && mOffsetX->at(mVisibleRight)<maxX && (mColumnWidths->at(mVisibleRight)<=0 || mOffsetX->at(mVisibleRight)+mColumnWidths->at(mVisibleRight)<maxX))
            {
                mVisibleRight++;
            }

            while (mVisibleRight>0 && mOffsetX->at(mVisibleRight)>maxX && (mColumnWidths->at(mVisibleRight)<=0 || mOffsetX->at(mVisibleRight)+mColumnWidths->at(mVisibleRight)>maxX))
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

    int aOldCurrentRow=mCurrentRow;
    int aOldCurrentColumn=mCurrentColumn;

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

    // If you don't use internal data, you may reimplement this function in your class
    if (mData)
    {
        mData->clear();
    }

    mRowHeights->clear();
    mColumnWidths->clear();
    mOffsetX->clear();
    mOffsetY->clear();

    mHorizontalHeader_Data->clear();
    mHorizontalHeader_RowHeights->clear();
    mHorizontalHeader_OffsetY->clear();

    mVerticalHeader_Data->clear();
    mVerticalHeader_ColumnWidths->clear();
    mVerticalHeader_OffsetX->clear();

    mSelectedCells->clear();
    mCurSelection->clear();
    mHorizontalHeader_SelectedColumns->clear();
    mVerticalHeader_SelectedRows->clear();

    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseResizeLineX=-1;
    mMouseResizeLineY=-1;
    mMouseResizeCell=-1;

    mMouseSelectedCells->clear();

    mEditCellRow=-1;
    mEditCellColumn=-1;
    mEditor=0;        // TODO: FastTable: Remove editor

    updateBarsRanges();

    viewport()->update();

    emit selectionChanged();

    if (aOldCurrentRow!=mCurrentRow || aOldCurrentColumn!=mCurrentColumn)
    {
        emit currentCellChanged(aOldCurrentRow, aOldCurrentColumn, mCurrentRow, mCurrentColumn);
        emit cellChanged(mCurrentRow, mCurrentColumn);
    }

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

void CustomFastTableWidget::searchNext(const QString &pattern, const QTableWidget::SelectionBehavior behaviour, const int column)
{
    FASTTABLE_ASSERT(behaviour==QTableWidget::SelectItems || behaviour==QTableWidget::SelectRows);

    if (mRowCount<=0 || mColumnCount<=0)
    {
        return;
    }

    if (behaviour==QTableWidget::SelectItems)
    {
        int aCurRow=mCurrentRow;
        int aCurColumn=mCurrentColumn;

        if (aCurRow<0)
        {
            aCurRow=0;
        }

        if (aCurColumn<0)
        {
            aCurColumn=0;
        }

        int aInitRow=aCurRow;
        int aInitColumn=aCurColumn;

        while (true)
        {
            ++aCurColumn;

            if (aCurColumn>=mColumnCount)
            {
                aCurColumn=0;
                ++aCurRow;

                if (aCurRow>=mRowCount)
                {
                    aCurRow=0;
                }
            }

            if (aCurRow==aInitRow && aCurColumn==aInitColumn)
            {
                break;
            }

            if (
                rowVisible(aCurRow)
                &&
                columnVisible(aCurColumn)
                &&
                (
                 column<0
                 ||
                 aCurColumn==column
                )
                &&
                text(aCurRow, aCurColumn).contains(pattern, Qt::CaseInsensitive)
               )
            {
                break;
            }
        }

        setCurrentCell(aCurRow, aCurColumn);
        scrollToCurrentCell();
    }
    else
    {
        int aCurRow=mCurrentRow;

        if (aCurRow<0)
        {
            aCurRow=0;
        }

        int aInitPos=aCurRow;

        while (true)
        {
            ++aCurRow;

            if (aCurRow>=mRowCount)
            {
                aCurRow=0;
            }

            if (aCurRow==aInitPos)
            {
                break;
            }

            if (!rowVisible(aCurRow))
            {
                continue;
            }

            if (column<0)
            {
                bool good=false;

                for (int i=0; i<mColumnCount; ++i)
                {
                    if (text(aCurRow, i).contains(pattern, Qt::CaseInsensitive))
                    {
                        good=true;
                        break;
                    }
                }

                if (good)
                {
                    break;
                }
            }
            else
            {
                if (text(aCurRow, column).contains(pattern, Qt::CaseInsensitive))
                {
                    break;
                }
            }
        }

        setCurrentCell(aCurRow, 0);
        scrollToCurrentCell();
        selectRow(aCurRow);
    }
}

void CustomFastTableWidget::searchPrevious(const QString &pattern, const QTableWidget::SelectionBehavior behaviour, const int column)
{
    FASTTABLE_ASSERT(behaviour==QTableWidget::SelectItems || behaviour==QTableWidget::SelectRows);

    if (mRowCount<=0 || mColumnCount<=0)
    {
        return;
    }

    if (behaviour==QTableWidget::SelectItems)
    {
        int aCurRow=mCurrentRow;
        int aCurColumn=mCurrentColumn;

        if (aCurRow<0)
        {
            aCurRow=0;
        }

        if (aCurColumn<0)
        {
            aCurColumn=0;
        }

        int aInitRow=aCurRow;
        int aInitColumn=aCurColumn;

        while (true)
        {
            --aCurColumn;

            if (aCurColumn<0)
            {
                aCurColumn=mColumnCount-1;
                --aCurRow;

                if (aCurRow<0)
                {
                    aCurRow=mRowCount-1;
                }
            }

            if (aCurRow==aInitRow && aCurColumn==aInitColumn)
            {
                break;
            }

            if (
                rowVisible(aCurRow)
                &&
                columnVisible(aCurColumn)
                &&
                (
                 column<0
                 ||
                 aCurColumn==column
                )
                &&
                text(aCurRow, aCurColumn).contains(pattern, Qt::CaseInsensitive)
               )
            {
                break;
            }
        }

        setCurrentCell(aCurRow, aCurColumn);
        scrollToCurrentCell();
    }
    else
    {
        int aCurRow=mCurrentRow;

        if (aCurRow<0)
        {
            aCurRow=0;
        }

        int aInitPos=aCurRow;

        while (true)
        {
            --aCurRow;

            if (aCurRow<0)
            {
                aCurRow=mRowCount-1;
            }

            if (aCurRow==aInitPos)
            {
                break;
            }

            if (!rowVisible(aCurRow))
            {
                continue;
            }

            if (column<0)
            {
                bool good=false;

                for (int i=0; i<mColumnCount; ++i)
                {
                    if (text(aCurRow, i).contains(pattern, Qt::CaseInsensitive))
                    {
                        good=true;
                        break;
                    }
                }

                if (good)
                {
                    break;
                }
            }
            else
            {
                if (text(aCurRow, column).contains(pattern, Qt::CaseInsensitive))
                {
                    break;
                }
            }
        }

        setCurrentCell(aCurRow, 0);
        scrollToCurrentCell();
        selectRow(aCurRow);
    }
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
            QPalette aPallete=palette();

            switch (mStyle)
            {
                case StyleSimple:
                {
                    aPallete.setColor(QPalette::Active,   QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Disabled, QPalette::Base, QColor(240, 240, 240));

                    aPallete.setColor(QPalette::AlternateBase, QColor(246, 246, 246));

                    aPallete.setColor(QPalette::Active,   QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Inactive, QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Disabled, QPalette::Text, QColor(120, 120, 120));

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

                    aPallete.setColor(QPalette::Active,   QPalette::Highlight, QColor(49,  106, 197));
                    aPallete.setColor(QPalette::Inactive, QPalette::Highlight, QColor(240, 240, 240));
                    aPallete.setColor(QPalette::Disabled, QPalette::Highlight, QColor(49,  106, 197));

                    aPallete.setColor(QPalette::Active,   QPalette::HighlightedText, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor(0, 0, 0));
                    aPallete.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(255, 255, 255));
                }
                break;
                case StyleLinux:
                {
                    aPallete.setColor(QPalette::Active,   QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Disabled, QPalette::Base, QColor(240, 240, 240));

                    aPallete.setColor(QPalette::AlternateBase, QColor(246, 246, 246));

                    aPallete.setColor(QPalette::Active,   QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Inactive, QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Disabled, QPalette::Text, QColor(120, 120, 120));

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

                    aPallete.setColor(QPalette::Active,   QPalette::Highlight, QColor(235, 110, 60));
                    aPallete.setColor(QPalette::Inactive, QPalette::Highlight, QColor(240, 240, 240));
                    aPallete.setColor(QPalette::Disabled, QPalette::Highlight, QColor(235, 110, 60));

                    aPallete.setColor(QPalette::Active,   QPalette::HighlightedText, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor(0, 0, 0));
                    aPallete.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(255, 255, 255));
                }
                break;
                case StyleWinXP:
                {
                    aPallete.setColor(QPalette::Active,   QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Disabled, QPalette::Base, QColor(240, 240, 240));

                    aPallete.setColor(QPalette::AlternateBase, QColor(246, 246, 246));

                    aPallete.setColor(QPalette::Active,   QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Inactive, QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Disabled, QPalette::Text, QColor(120, 120, 120));

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

                    aPallete.setColor(QPalette::Active,   QPalette::Highlight, QColor(49, 106, 197));
                    aPallete.setColor(QPalette::Inactive, QPalette::Highlight, QColor(240, 240, 240));
                    aPallete.setColor(QPalette::Disabled, QPalette::Highlight, QColor(49, 106, 197));

                    aPallete.setColor(QPalette::Active,   QPalette::HighlightedText, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor(0, 0, 0));
                    aPallete.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(255, 255, 255));
                }
                break;
                case StyleWin7:
                {
                    aPallete.setColor(QPalette::Active,   QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::Base, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Disabled, QPalette::Base, QColor(240, 240, 240));

                    aPallete.setColor(QPalette::AlternateBase, QColor(246, 246, 246));

                    aPallete.setColor(QPalette::Active,   QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Inactive, QPalette::Text, QColor(0,   0,   0));
                    aPallete.setColor(QPalette::Disabled, QPalette::Text, QColor(120, 120, 120));

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

                    aPallete.setColor(QPalette::Active,   QPalette::Highlight, QColor(51, 153, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::Highlight, QColor(240, 240, 240));
                    aPallete.setColor(QPalette::Disabled, QPalette::Highlight, QColor(51, 153, 255));

                    aPallete.setColor(QPalette::Active,   QPalette::HighlightedText, QColor(255, 255, 255));
                    aPallete.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor(0, 0, 0));
                    aPallete.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(255, 255, 255));
                }
                break;
            }

            setPalette(aPallete);
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

    bool allSelected=true;

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns->length());

        if (mHorizontalHeader_SelectedColumns->at(i)!=mRowCount)
        {
            allSelected=false;
            break;
        }
    }

    if (!allSelected)
    {
        QPoint aCellPos;

        for (int i=0; i<mRowCount; ++i)
        {
            for (int j=0; j<mColumnCount; ++j)
            {
                FASTTABLE_ASSERT(i<mSelectedCells->length());
                FASTTABLE_ASSERT(j<mSelectedCells->at(i).length());

                if (!mSelectedCells->at(i).at(j))
                {
                    aCellPos.setX(j);
                    aCellPos.setY(i);

                    mCurSelection->append(aCellPos);

                    (*mSelectedCells)[i][j]=true;
                }
            }
        }

        for (int i=0; i<mRowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mVerticalHeader_SelectedRows->length());

            (*mVerticalHeader_SelectedRows)[i]=mColumnCount;
        }

        for (int i=0; i<mColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns->length());

            (*mHorizontalHeader_SelectedColumns)[i]=mRowCount;
        }

        viewport()->update();

        emit selectionChanged();
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::unselectAll()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    if (mCurSelection->length()>0)
    {
        for (int i=0; i<mCurSelection->length(); ++i)
        {
            FASTTABLE_ASSERT(mCurSelection->at(i).y()<mSelectedCells->length());
            FASTTABLE_ASSERT(mCurSelection->at(i).x()<mSelectedCells->at(mCurSelection->at(i).y()).length());

            (*mSelectedCells)[mCurSelection->at(i).y()][mCurSelection->at(i).x()]=false;
        }

        mCurSelection->clear();

        for (int i=0; i<mRowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mVerticalHeader_SelectedRows->length());

            (*mVerticalHeader_SelectedRows)[i]=0;
        }

        for (int i=0; i<mColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mHorizontalHeader_SelectedColumns->length());

            (*mHorizontalHeader_SelectedColumns)[i]=0;
        }

        viewport()->update();

        emit selectionChanged();
    }

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
    FASTTABLE_ASSERT(row>=0 && row<=mOffsetY->length());
    FASTTABLE_ASSERT(row>=0 && row<=mRowHeights->length());
    FASTTABLE_ASSERT(mData==0 || (row>=0 && row<=mData->length()));
    FASTTABLE_ASSERT(row>=0 && row<=mVerticalHeader_Data->length());
    FASTTABLE_ASSERT(row>=0 && row<=mSelectedCells->length());
    FASTTABLE_ASSERT(row>=0 && row<=mVerticalHeader_SelectedRows->length());

    mRowCount++;

    QStringList aNewRow;
    QList<bool> aNewRowbool;

    mTotalHeight+=mDefaultHeight;

    mOffsetY->insert(row, row==0? mHorizontalHeader_TotalHeight : (mRowHeights->at(row-1)<=0? mOffsetY->at(row-1) : (mOffsetY->at(row-1)+mRowHeights->at(row-1))));
    mRowHeights->insert(row, mDefaultHeight);

    for (int i=row+1; i<mRowCount; ++i)
    {
        (*mOffsetY)[i]+=mDefaultHeight;
    }

    if (mData)
    {
        mData->insert(row, aNewRow);
    }

    mVerticalHeader_Data->insert(row, aNewRow);
    mSelectedCells->insert(row, aNewRowbool);
    mVerticalHeader_SelectedRows->insert(row, 0);

    for (int i=0; i<mVerticalHeader_ColumnCount; ++i)
    {
        (*mVerticalHeader_Data)[row].append("");
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        if (mData)
        {
            (*mData)[row].append("");
        }

        (*mSelectedCells)[row].append(false);
    }

    for (int i=0; i<mCurSelection->length(); ++i)
    {
        if (mCurSelection->at(i).y()>=row)
        {
            (*mCurSelection)[i].setY(mCurSelection->at(i).y()+1);
        }
    }

    if (mCurrentRow>=row)
    {
        mCurrentRow++;
    }

    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseLocationForShift=InMiddleWorld;
    mMouseSelectedCells->clear();

    updateSizes();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::removeRow(int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mRowCount);
    FASTTABLE_ASSERT(row>=0 && row<mOffsetY->length());
    FASTTABLE_ASSERT(row>=0 && row<mRowHeights->length());
    FASTTABLE_ASSERT(mData==0 || (row>=0 && row<mData->length()));
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data->length());
    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells->length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows->length());

    int diff=mRowHeights->at(row);

    if (diff>0)
    {
        mTotalHeight-=diff;

        FASTTABLE_ASSERT(mTotalHeight>=0);

        for (int i=row+1; i<mRowCount; ++i)
        {
            (*mOffsetY)[i]-=diff;

            FASTTABLE_ASSERT(mOffsetY->at(i)>=0);
        }
    }

    mOffsetY->removeAt(row);
    mRowHeights->removeAt(row);

    if (mData)
    {
        mData->removeAt(row);
    }

    mVerticalHeader_Data->removeAt(row);

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mSelectedCells->at(row).length());

        if (mSelectedCells->at(row).at(i))
        {
            (*mHorizontalHeader_SelectedColumns)[i]--;
        }
    }

    mSelectedCells->removeAt(row);
    mVerticalHeader_SelectedRows->removeAt(row);

    for (int i=0; i<mCurSelection->length(); ++i)
    {
        if (mCurSelection->at(i).y()>row)
        {
            (*mCurSelection)[i].setY(mCurSelection->at(i).y()-1);
        }
        else
        if (mCurSelection->at(i).y()==row)
        {
            mCurSelection->removeAt(i);
            --i;
        }
    }

    if (mCurrentRow>row || mCurrentRow>mRowCount-2)
    {
        mCurrentRow--;
    }

    if (mCurrentRow>=0 && mCurrentColumn>=0)
    {
        setCellSelected(mCurrentRow, mCurrentColumn, true);
    }

    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseLocationForShift=InMiddleWorld;
    mMouseSelectedCells->clear();

    mRowCount--;

    updateSizes();

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
    FASTTABLE_ASSERT(column>=0 && column<=mOffsetX->length());
    FASTTABLE_ASSERT(column>=0 && column<=mColumnWidths->length());
    FASTTABLE_ASSERT(column>=0 && column<=mHorizontalHeader_SelectedColumns->length());

    mColumnCount++;

    mTotalWidth+=mDefaultWidth;

    mOffsetX->insert(column, column==0? mVerticalHeader_TotalWidth : (mColumnWidths->at(column-1)<=0? mOffsetX->at(column-1) : (mOffsetX->at(column-1)+mColumnWidths->at(column-1))));
    mColumnWidths->insert(column, mDefaultWidth);

    for (int i=column+1; i<mColumnCount; ++i)
    {
        (*mOffsetX)[i]+=mDefaultWidth;
    }

    for (int i=0; i<mHorizontalHeader_Data->length(); ++i)
    {
        FASTTABLE_ASSERT(column<=mHorizontalHeader_Data->at(i).length());

        (*mHorizontalHeader_Data)[i].insert(column, "");
    }

    for (int i=0; i<mSelectedCells->length(); ++i)
    {
        FASTTABLE_ASSERT(mData==0 || column<=mData->at(i).length());
        FASTTABLE_ASSERT(column<=mSelectedCells->at(i).length());

        if (mData)
        {
            (*mData)[i].insert(column, "");
        }

        (*mSelectedCells)[i].insert(column, false);
    }

    mHorizontalHeader_SelectedColumns->insert(column, 0);

    for (int i=0; i<mCurSelection->length(); ++i)
    {
        if (mCurSelection->at(i).x()>=column)
        {
            (*mCurSelection)[i].setX(mCurSelection->at(i).x()+1);
        }
    }

    if (mCurrentColumn>=column)
    {
        mCurrentColumn++;
    }

    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseLocationForShift=InMiddleWorld;
    mMouseSelectedCells->clear();

    updateSizes();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::removeColumn(int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<mOffsetX->length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths->length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns->length());

    int diff=mColumnWidths->at(column);

    if (diff>0)
    {
        mTotalWidth-=diff;

        FASTTABLE_ASSERT(mTotalWidth>=0);

        for (int i=column+1; i<mColumnCount; ++i)
        {
            (*mOffsetX)[i]-=diff;

            FASTTABLE_ASSERT(mOffsetX->at(i)>=0);
        }
    }

    mOffsetX->removeAt(column);
    mColumnWidths->removeAt(column);

    for (int i=0; i<mHorizontalHeader_Data->length(); ++i)
    {
        FASTTABLE_ASSERT(column<mHorizontalHeader_Data->at(i).length());

        (*mHorizontalHeader_Data)[i].removeAt(column);
    }

    for (int i=0; i<mSelectedCells->length(); ++i)
    {
        FASTTABLE_ASSERT(mData==0 || column<mData->at(i).length());
        FASTTABLE_ASSERT(column<mSelectedCells->at(i).length());

        if (mData)
        {
            (*mData)[i].removeAt(column);
        }

        if (mSelectedCells->at(i).at(column))
        {
            (*mVerticalHeader_SelectedRows)[i]--;
        }

        (*mSelectedCells)[i].removeAt(column);
    }

    mHorizontalHeader_SelectedColumns->removeAt(column);

    for (int i=0; i<mCurSelection->length(); ++i)
    {
        if (mCurSelection->at(i).x()>column)
        {
            (*mCurSelection)[i].setX(mCurSelection->at(i).x()-1);
        }
        else
        if (mCurSelection->at(i).x()==column)
        {
            mCurSelection->removeAt(i);
            --i;
        }
    }

    if (mCurrentColumn>column || mCurrentColumn>mColumnCount-2)
    {
        mCurrentColumn--;
    }

    if (mCurrentRow>=0 && mCurrentColumn>=0)
    {
        setCellSelected(mCurrentRow, mCurrentColumn, true);
    }

    mMouseXForShift=-1;
    mMouseYForShift=-1;
    mMouseLocationForShift=InMiddleWorld;
    mMouseSelectedCells->clear();

    mColumnCount--;

    updateSizes();

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
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_OffsetY->length());
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_RowHeights->length());
    FASTTABLE_ASSERT(row>=0 && row<=mHorizontalHeader_Data->length());

    mHorizontalHeader_RowCount++;

    QStringList aNewRow;

    mHorizontalHeader_TotalHeight+=mDefaultHeight;
    mTotalHeight+=mDefaultHeight;

    mHorizontalHeader_OffsetY->insert(row, row==0? 0 : (mHorizontalHeader_RowHeights->at(row-1)<=0? mHorizontalHeader_OffsetY->at(row-1) : (mHorizontalHeader_OffsetY->at(row-1)+mHorizontalHeader_RowHeights->at(row-1))));
    mHorizontalHeader_RowHeights->insert(row, mDefaultHeight);

    for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
    {
        (*mHorizontalHeader_OffsetY)[i]+=mDefaultHeight;
    }

    for (int i=0; i<mRowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetY->length());

        (*mOffsetY)[i]+=mDefaultHeight;
    }

    mHorizontalHeader_Data->insert(row, aNewRow);

    for (int i=0; i<mColumnCount; ++i)
    {
        (*mHorizontalHeader_Data)[row].append("");
    }

    updateSizes();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_RemoveRow(int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_RowCount);
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_OffsetY->length());
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_RowHeights->length());
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data->length());

    int diff=mHorizontalHeader_RowHeights->at(row);

    if (diff>0)
    {
        mHorizontalHeader_TotalHeight-=diff;
        mTotalHeight-=diff;

        FASTTABLE_ASSERT(mHorizontalHeader_TotalHeight>=0);
        FASTTABLE_ASSERT(mTotalHeight>=0);

        for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
        {
            (*mHorizontalHeader_OffsetY)[i]-=diff;

            FASTTABLE_ASSERT(mHorizontalHeader_OffsetY->at(i)>=0);
        }

        for (int i=0; i<mRowCount; ++i)
        {
            FASTTABLE_ASSERT(i<mOffsetY->length());

            (*mOffsetY)[i]-=diff;

            FASTTABLE_ASSERT(mOffsetY->at(i)>=0);
        }
    }

    mHorizontalHeader_OffsetY->removeAt(row);
    mHorizontalHeader_RowHeights->removeAt(row);
    mHorizontalHeader_Data->removeAt(row);

    mHorizontalHeader_RowCount--;

    updateSizes();

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
    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_OffsetX->length());
    FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_ColumnWidths->length());

    mVerticalHeader_ColumnCount++;

    mVerticalHeader_TotalWidth+=mDefaultWidth;
    mTotalWidth+=mDefaultWidth;

    mVerticalHeader_OffsetX->insert(column, column==0? 0 : (mVerticalHeader_ColumnWidths->at(column-1)<=0? mVerticalHeader_OffsetX->at(column-1) : (mVerticalHeader_OffsetX->at(column-1)+mVerticalHeader_ColumnWidths->at(column-1))));
    mVerticalHeader_ColumnWidths->insert(column, mDefaultWidth);

    for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
    {
        (*mVerticalHeader_OffsetX)[i]+=mDefaultWidth;
    }

    for (int i=0; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetX->length());

        (*mOffsetX)[i]+=mDefaultWidth;
    }

    for (int i=0; i<mVerticalHeader_Data->length(); ++i)
    {
        FASTTABLE_ASSERT(column>=0 && column<=mVerticalHeader_Data->at(i).length());

        (*mVerticalHeader_Data)[i].insert(column, "");
    }

    updateSizes();

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_RemoveColumn(int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnCount);
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_OffsetX->length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnWidths->length());

    int diff=mVerticalHeader_ColumnWidths->at(column);

    if (diff>0)
    {
        mVerticalHeader_TotalWidth-=diff;
        mTotalWidth-=diff;

        FASTTABLE_ASSERT(mVerticalHeader_TotalWidth>=0);
        FASTTABLE_ASSERT(mTotalWidth>=0);

        for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
        {
            (*mVerticalHeader_OffsetX)[i]-=diff;

            FASTTABLE_ASSERT(mVerticalHeader_OffsetX->at(i)>=0);
        }

        for (int i=0; i<mColumnCount; ++i)
        {
            FASTTABLE_ASSERT(i<mOffsetX->length());

            (*mOffsetX)[i]-=diff;

            FASTTABLE_ASSERT(mOffsetX->at(i)>=0);
        }
    }

    mVerticalHeader_OffsetX->removeAt(column);
    mVerticalHeader_ColumnWidths->removeAt(column);

    for (int i=0; i<mVerticalHeader_Data->length(); ++i)
    {
        FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data->at(i).length());

        (*mVerticalHeader_Data)[i].removeAt(column);
    }

    mVerticalHeader_ColumnCount--;

    updateSizes();

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
            removeRow(mRowCount-1);
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
            removeColumn(mColumnCount-1);
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
            horizontalHeader_RemoveRow(mHorizontalHeader_RowCount-1);
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
            verticalHeader_RemoveColumn(mVerticalHeader_ColumnCount-1);
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

bool CustomFastTableWidget::alternatingRowColors()
{
    FASTTABLE_DEBUG;
    return mAlternatingRowColors;
}

void CustomFastTableWidget::setAlternatingRowColors(bool enable)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mAlternatingRowColors=enable;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

bool CustomFastTableWidget::horizontalHeader_StretchLastSection()
{
    FASTTABLE_DEBUG;
    return mHorizontalHeaderStretchLastSection;
}

void CustomFastTableWidget::horizontalHeader_SetStretchLastSection(bool enable)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mHorizontalHeaderStretchLastSection=enable;

    if (mHorizontalHeaderStretchLastSection)
    {
        updateSizes();
    }

    FASTTABLE_END_PROFILE;
}

bool CustomFastTableWidget::verticalHeader_StretchLastSection()
{
    FASTTABLE_DEBUG;
    return mVerticalHeaderStretchLastSection;
}

void CustomFastTableWidget::verticalHeader_SetStretchLastSection(bool enable)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    mVerticalHeaderStretchLastSection=enable;

    if (mVerticalHeaderStretchLastSection)
    {
        updateSizes();
    }

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
    FASTTABLE_ASSERT(column<mColumnWidths->length());

    if (mColumnWidths->at(column)<0)
    {
        return -mColumnWidths->at(column);
    }
    else
    {
        return mColumnWidths->at(column);
    }
}

void CustomFastTableWidget::setColumnWidth(const int column, quint16 width, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column<mColumnWidths->length());

    if (width>32767)
    {
        FASTTABLE_LOG_DEBUG("Width for column #"+QString::number(column)+" is too big: "+QString::number(width)+". The maximum width is 32767");
        width=32767;
    }

    if (mColumnWidths->at(column)<0)
    {
        (*mColumnWidths)[column]=-width;
    }
    else
    if (mColumnWidths->at(column)!=width)
    {
        int aDiff=width-mColumnWidths->at(column);

        (*mColumnWidths)[column]=width;

        mTotalWidth+=aDiff;

        FASTTABLE_ASSERT(mTotalWidth>=0);

        // If you don't use forceUpdate you need to use updateOffsetsX later
        if (forceUpdate)
        {
            for (int i=column+1; i<mColumnCount; ++i)
            {
                FASTTABLE_ASSERT(i<mOffsetX->length());

                (*mOffsetX)[i]+=aDiff;

                FASTTABLE_ASSERT(mOffsetX->at(i)>=0);
            }

            updateSizes();

            viewport()->update();
        }
    }

    FASTTABLE_END_PROFILE;
}

quint16 CustomFastTableWidget::rowHeight(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mRowHeights->length());

    if (mRowHeights->at(row)<0)
    {
        return -mRowHeights->at(row);
    }
    else
    {
        return mRowHeights->at(row);
    }
}

void CustomFastTableWidget::setRowHeight(const int row, quint16 height, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row<mRowHeights->length());

    if (height>32767)
    {
        FASTTABLE_LOG_DEBUG("Height for row #"+QString::number(row)+" is too big: "+QString::number(height)+". The maximum height is 32767");
        height=32767;
    }

    if (mRowHeights->at(row)<0)
    {
        (*mRowHeights)[row]=-height;
    }
    else
    if (mRowHeights->at(row)!=height)
    {
        int aDiff=height-mRowHeights->at(row);

        (*mRowHeights)[row]=height;

        mTotalHeight+=aDiff;

        FASTTABLE_ASSERT(mTotalHeight>=0);

        // If you don't use forceUpdate you need to use updateOffsetsY later
        if (forceUpdate)
        {
            for (int i=row+1; i<mRowCount; ++i)
            {
                FASTTABLE_ASSERT(i<mOffsetY->length());

                (*mOffsetY)[i]+=aDiff;

                FASTTABLE_ASSERT(mOffsetY->at(i)>=0);
            }

            updateSizes();

            viewport()->update();
        }
    }

    FASTTABLE_END_PROFILE;
}

quint16 CustomFastTableWidget::verticalHeader_ColumnWidth(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths->length());

    if (mVerticalHeader_ColumnWidths->at(column)<0)
    {
        return -mVerticalHeader_ColumnWidths->at(column);
    }
    else
    {
        return mVerticalHeader_ColumnWidths->at(column);
    }
}

void CustomFastTableWidget::verticalHeader_SetColumnWidth(const int column, quint16 width, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths->length());

    if (width>32767)
    {
        FASTTABLE_LOG_DEBUG("Width for column #"+QString::number(column)+" in vertical header is too big: "+QString::number(width)+". The maximum width is 32767");
        width=32767;
    }

    if (mVerticalHeader_ColumnWidths->at(column)<0)
    {
        (*mVerticalHeader_ColumnWidths)[column]=-width;
    }
    else
    if (mVerticalHeader_ColumnWidths->at(column)!=width)
    {
        int aDiff=width-mVerticalHeader_ColumnWidths->at(column);

        (*mVerticalHeader_ColumnWidths)[column]=width;

        mVerticalHeader_TotalWidth+=aDiff;
        mTotalWidth+=aDiff;

        FASTTABLE_ASSERT(mVerticalHeader_TotalWidth>=0);
        FASTTABLE_ASSERT(mTotalWidth>=0);

        // If you don't use forceUpdate you need to use verticalHeader_UpdateOffsetsX later
        if (forceUpdate)
        {
            for (int i=column+1; i<mVerticalHeader_ColumnCount; ++i)
            {
                FASTTABLE_ASSERT(i<mVerticalHeader_OffsetX->length());

                (*mVerticalHeader_OffsetX)[i]+=aDiff;

                FASTTABLE_ASSERT(mVerticalHeader_OffsetX->at(i)>=0);
            }

            for (int i=0; i<mColumnCount; ++i)
            {
                FASTTABLE_ASSERT(i<mOffsetX->length());

                (*mOffsetX)[i]+=aDiff;

                FASTTABLE_ASSERT(mOffsetX->at(i)>=0);
            }

            updateSizes();

            viewport()->update();
        }
    }

    FASTTABLE_END_PROFILE;
}

quint16 CustomFastTableWidget::horizontalHeader_RowHeight(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights->length());

    if (mHorizontalHeader_RowHeights->at(row)<0)
    {
        return -mHorizontalHeader_RowHeights->at(row);
    }
    else
    {
        return mHorizontalHeader_RowHeights->at(row);
    }
}

void CustomFastTableWidget::horizontalHeader_SetRowHeight(const int row, quint16 height, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights->length());

    if (height>32767)
    {
        FASTTABLE_LOG_DEBUG("Height for row #"+QString::number(row)+" in horizontal header is too big: "+QString::number(height)+". The maximum height is 32767");
        height=32767;
    }

    if (mHorizontalHeader_RowHeights->at(row)<0)
    {
        (*mHorizontalHeader_RowHeights)[row]=-height;
    }
    else
    if (mHorizontalHeader_RowHeights->at(row)!=height)
    {
        int aDiff=height-mHorizontalHeader_RowHeights->at(row);

        (*mHorizontalHeader_RowHeights)[row]=height;

        mHorizontalHeader_TotalHeight+=aDiff;
        mTotalHeight+=aDiff;

        FASTTABLE_ASSERT(mHorizontalHeader_TotalHeight>=0);
        FASTTABLE_ASSERT(mTotalHeight>=0);

        // If you don't use forceUpdate you need to use horizontalHeader_UpdateOffsetsY later
        if (forceUpdate)
        {
            for (int i=row+1; i<mHorizontalHeader_RowCount; ++i)
            {
                FASTTABLE_ASSERT(i<mHorizontalHeader_OffsetY->length());

                (*mHorizontalHeader_OffsetY)[i]+=aDiff;

                FASTTABLE_ASSERT(mHorizontalHeader_OffsetY->at(i)>=0);
            }

            for (int i=0; i<mRowCount; ++i)
            {
                FASTTABLE_ASSERT(i<mOffsetY->length());

                (*mOffsetY)[i]+=aDiff;

                FASTTABLE_ASSERT(mOffsetY->at(i)>=0);
            }

            updateSizes();

            viewport()->update();
        }
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
    FASTTABLE_ASSERT(column<mColumnWidths->length());

    return mColumnWidths->at(column)>=0;
}

void CustomFastTableWidget::setColumnVisible(const int column, bool visible, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column<mColumnWidths->length());

    qint16 prevWidth=mColumnWidths->at(column);
    bool wasVisible=prevWidth>0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            (*mColumnWidths)[column]=0;

            if (prevWidth==0)
            {
                prevWidth=-10;
            }

            setColumnWidth(column, -prevWidth, forceUpdate);
        }
        else
        {
            setColumnWidth(column, 0, forceUpdate);
            (*mColumnWidths)[column]=-prevWidth;
        }
    }

    FASTTABLE_END_PROFILE;
}

bool CustomFastTableWidget::rowVisible(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mRowHeights->length());

    return mRowHeights->at(row)>0;
}

void CustomFastTableWidget::setRowVisible(const int row, bool visible, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row<mRowHeights->length());

    qint16 prevHeight=mRowHeights->at(row);
    bool wasVisible=prevHeight>0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            (*mRowHeights)[row]=0;

            if (prevHeight==0)
            {
                prevHeight=-10;
            }

            setRowHeight(row, -prevHeight, forceUpdate);
        }
        else
        {
            setRowHeight(row, 0, forceUpdate);
            (*mRowHeights)[row]=-prevHeight;
        }
    }

    FASTTABLE_END_PROFILE;
}

bool CustomFastTableWidget::verticalHeader_ColumnVisible(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths->length());

    return mVerticalHeader_ColumnWidths->at(column)>=0;
}

void CustomFastTableWidget::verticalHeader_SetColumnVisible(const int column, bool visible, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(column<mVerticalHeader_ColumnWidths->length());

    qint16 prevWidth=mVerticalHeader_ColumnWidths->at(column);
    bool wasVisible=prevWidth>0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            (*mVerticalHeader_ColumnWidths)[column]=0;

            if (prevWidth==0)
            {
                prevWidth=-10;
            }

            verticalHeader_SetColumnWidth(column, -prevWidth, forceUpdate);
        }
        else
        {
            verticalHeader_SetColumnWidth(column, 0, forceUpdate);
            (*mVerticalHeader_ColumnWidths)[column]=-prevWidth;
        }
    }

    FASTTABLE_END_PROFILE;
}

bool CustomFastTableWidget::horizontalHeader_RowVisible(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights->length());

    return mHorizontalHeader_RowHeights->at(row)>=0;
}

void CustomFastTableWidget::horizontalHeader_SetRowVisible(const int row, bool visible, bool forceUpdate)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row<mHorizontalHeader_RowHeights->length());

    qint16 prevHeight=mHorizontalHeader_RowHeights->at(row);
    bool wasVisible=prevHeight>0;

    if (wasVisible!=visible)
    {
        if (visible)
        {
            (*mHorizontalHeader_RowHeights)[row]=0;

            if (prevHeight==0)
            {
                prevHeight=-10;
            }

            horizontalHeader_SetRowHeight(row, -prevHeight, forceUpdate);
        }
        else
        {
            horizontalHeader_SetRowHeight(row, 0, forceUpdate);
            (*mHorizontalHeader_RowHeights)[row]=-prevHeight;
        }
    }

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::updateOffsetsX(const int fromIndex)
{
    int aCurOffset;

    if (fromIndex==0)
    {
        aCurOffset=mVerticalHeader_TotalWidth;
    }
    else
    {
        aCurOffset=mOffsetX->at(fromIndex);
    }

    for (int i=fromIndex; i<mColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetX->length());
        FASTTABLE_ASSERT(i<mColumnWidths->length());

        (*mOffsetX)[i]=aCurOffset;

        if (mColumnWidths->at(i)>0)
        {
            aCurOffset+=mColumnWidths->at(i);
        }

        FASTTABLE_ASSERT(mOffsetX->at(i)>=0);
    }

    updateSizes();

    viewport()->update();
}

void CustomFastTableWidget::updateOffsetsY(const int fromIndex)
{
    int aCurOffset;

    if (fromIndex==0)
    {
        aCurOffset=mHorizontalHeader_TotalHeight;
    }
    else
    {
        aCurOffset=mOffsetY->at(fromIndex);
    }

    for (int i=fromIndex; i<mRowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mOffsetY->length());
        FASTTABLE_ASSERT(i<mRowHeights->length());

        (*mOffsetY)[i]=aCurOffset;

        if (mRowHeights->at(i)>0)
        {
            aCurOffset+=mRowHeights->at(i);
        }

        FASTTABLE_ASSERT(mOffsetY->at(i)>=0);
    }

    updateSizes();

    viewport()->update();
}

void CustomFastTableWidget::verticalHeader_UpdateOffsetsX(const int fromIndex)
{
    int aCurOffset;

    if (fromIndex==0)
    {
        aCurOffset=0;
    }
    else
    {
        aCurOffset=mVerticalHeader_OffsetX->at(fromIndex);
    }

    for (int i=fromIndex; i<mVerticalHeader_ColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mVerticalHeader_OffsetX->length());
        FASTTABLE_ASSERT(i<mVerticalHeader_ColumnWidths->length());

        (*mVerticalHeader_OffsetX)[i]=aCurOffset;

        if (mVerticalHeader_ColumnWidths->at(i)>0)
        {
            aCurOffset+=mVerticalHeader_ColumnWidths->at(i);
        }

        FASTTABLE_ASSERT(mVerticalHeader_OffsetX->at(i)>=0);
    }

    updateOffsetsX();
}

void CustomFastTableWidget::horizontalHeader_UpdateOffsetsY(const int fromIndex)
{
    int aCurOffset;

    if (fromIndex==0)
    {
        aCurOffset=0;
    }
    else
    {
        aCurOffset=mHorizontalHeader_OffsetY->at(fromIndex);
    }

    for (int i=fromIndex; i<mHorizontalHeader_RowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_OffsetY->length());
        FASTTABLE_ASSERT(i<mHorizontalHeader_RowHeights->length());

        (*mHorizontalHeader_OffsetY)[i]=aCurOffset;

        if (mHorizontalHeader_RowHeights->at(i)>0)
        {
            aCurOffset+=mHorizontalHeader_RowHeights->at(i);
        }

        FASTTABLE_ASSERT(mHorizontalHeader_OffsetY->at(i)>=0);
    }

    updateOffsetsY();
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

    FASTTABLE_ASSERT(column>=0 && column<mOffsetX->length());
    FASTTABLE_ASSERT(row>=0    && row<mOffsetY->length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths->length());
    FASTTABLE_ASSERT(row>=0    && row<mRowHeights->length());

    return QRect(mOffsetX->at(column), mOffsetY->at(row), mColumnWidths->at(column), mRowHeights->at(row));
}

QRect CustomFastTableWidget::horizontalHeader_CellRectangle(const int row, const int column)
{
    FASTTABLE_DEBUG;

    FASTTABLE_ASSERT(column>=0 && column<mOffsetX->length());
    FASTTABLE_ASSERT(row>=0    && row<mHorizontalHeader_OffsetY->length());
    FASTTABLE_ASSERT(column>=0 && column<mColumnWidths->length());
    FASTTABLE_ASSERT(row>=0    && row<mHorizontalHeader_RowHeights->length());

    return QRect(mOffsetX->at(column), mHorizontalHeader_OffsetY->at(row), mColumnWidths->at(column), mHorizontalHeader_RowHeights->at(row));
}

QRect CustomFastTableWidget::verticalHeader_CellRectangle(const int row, const int column)
{
    FASTTABLE_DEBUG;

    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_OffsetX->length());
    FASTTABLE_ASSERT(row>=0    && row<mOffsetY->length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_ColumnWidths->length());
    FASTTABLE_ASSERT(row>=0    && row<mRowHeights->length());

    return QRect(mVerticalHeader_OffsetX->at(column), mOffsetY->at(row), mVerticalHeader_ColumnWidths->at(column), mRowHeights->at(row));
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

    // If you don't use internal data, you have to reimplement this function in your class
    FASTTABLE_ASSERT(mUseInternalData);
    FASTTABLE_ASSERT(row>=0 && row<mData->length());
    FASTTABLE_ASSERT(column>=0 && column<mData->at(row).length());

    return mData->at(row).at(column);
}

void CustomFastTableWidget::setText(const int row, const int column, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    // If you don't use internal data, you may reimplement this function in your class
    FASTTABLE_ASSERT(mUseInternalData);
    FASTTABLE_ASSERT(row>=0 && row<mData->length());
    FASTTABLE_ASSERT(column>=0 && column<mData->at(row).length());

    (*mData)[row][column]=text;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QString CustomFastTableWidget::horizontalHeader_Text(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data->length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data->at(row).length());

    return mHorizontalHeader_Data->at(row).at(column);
}

QString CustomFastTableWidget::horizontalHeader_Text(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(mHorizontalHeader_Data->length()>0);
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data->at(0).length());

    return mHorizontalHeader_Data->at(0).at(column);
}

void CustomFastTableWidget::horizontalHeader_SetText(const int row, const int column, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mHorizontalHeader_Data->length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data->at(row).length());

    (*mHorizontalHeader_Data)[row][column]=text;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::horizontalHeader_SetText(const int column, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    for (int i=0; i<mHorizontalHeader_RowCount; ++i)
    {
        FASTTABLE_ASSERT(i<mHorizontalHeader_Data->length());
        FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_Data->at(i).length());

        (*mHorizontalHeader_Data)[i][column]=text;
    }

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QString CustomFastTableWidget::verticalHeader_Text(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data->length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data->at(row).length());

    return mVerticalHeader_Data->at(row).at(column);
}

QString CustomFastTableWidget::verticalHeader_Text(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data->length());
    FASTTABLE_ASSERT(mVerticalHeader_Data->at(row).length()>0);

    return mVerticalHeader_Data->at(row).at(0);
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const int column, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data->length());
    FASTTABLE_ASSERT(column>=0 && column<mVerticalHeader_Data->at(row).length());

    (*mVerticalHeader_Data)[row][column]=text;

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

void CustomFastTableWidget::verticalHeader_SetText(const int row, const QString text)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_Data->length());

    for (int i=0; i<mVerticalHeader_ColumnCount; ++i)
    {
        FASTTABLE_ASSERT(i<mVerticalHeader_Data->at(row).length());

        (*mVerticalHeader_Data)[row][i]=text;
    }

    viewport()->update();

    FASTTABLE_END_PROFILE;
}

QBrush CustomFastTableWidget::backgroundBrush(const int /*row*/, const int /*column*/)
{
    FASTTABLE_DEBUG;

    // If you don't use internal data, you may reimplement this function in your class
    return palette().base();
}

void CustomFastTableWidget::setBackgroundBrush(const int /*row*/, const int /*column*/, const QBrush /*brush*/)
{
    // Nothing
    // If you don't use internal data, you may reimplement this function in your class

    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(!mUseInternalData);
}

QColor CustomFastTableWidget::foregroundColor(const int /*row*/, const int /*column*/)
{
    FASTTABLE_DEBUG;

    // If you don't use internal data, you may reimplement this function in your class
    return palette().color(QPalette::Text);
}

void CustomFastTableWidget::setForegroundColor(const int /*row*/, const int /*column*/, const QColor /*color*/)
{
    // Nothing
    // If you don't use internal data, you may reimplement this function in your class

    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(!mUseInternalData);
}

QFont CustomFastTableWidget::cellFont(const int /*row*/, const int /*column*/)
{
    FASTTABLE_DEBUG;

    // If you don't use internal data, you may reimplement this function in your class
    return font();
}

void CustomFastTableWidget::setCellFont(const int /*row*/, const int /*column*/, const QFont /*font*/)
{
    // Nothing
    // If you don't use internal data, you may reimplement this function in your class

    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(!mUseInternalData);
}

int CustomFastTableWidget::cellTextFlags(const int /*row*/, const int /*column*/)
{
    FASTTABLE_DEBUG;

    // If you don't use internal data, you may reimplement this function in your class
    return FASTTABLE_DEFAULT_TEXT_FLAG;
}

void CustomFastTableWidget::setCellTextFlags(const int /*row*/, const int /*column*/, const int /*flags*/)
{
    // Nothing
    // If you don't use internal data, you may reimplement this function in your class

    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(!mUseInternalData);
}

bool CustomFastTableWidget::cellSelected(const int row, const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells->length());
    FASTTABLE_ASSERT(column>=0 && column<mSelectedCells->at(row).length());

    return mSelectedCells->at(row).at(column);
}

void CustomFastTableWidget::setCellSelected(const int row, const int column, const bool selected)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    FASTTABLE_ASSERT(row>=0 && row<mSelectedCells->length());
    FASTTABLE_ASSERT(column>=0 && column<mSelectedCells->at(row).length());
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows->length());
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns->length());

    if (mSelectedCells->at(row).at(column)!=selected)
    {
        (*mSelectedCells)[row][column]=selected;

        if (selected)
        {
            mCurSelection->append(QPoint(column, row));

            (*mVerticalHeader_SelectedRows)[row]++;
            (*mHorizontalHeader_SelectedColumns)[column]++;
        }
        else
        {
            for (int i=0; i<mCurSelection->length(); ++i)
            {
                if (mCurSelection->at(i).y()==row)
                {
                    if (mCurSelection->at(i).x()==column)
                    {
                        mCurSelection->removeAt(i);
                        break;
                    }
                }
            }

            (*mVerticalHeader_SelectedRows)[row]--;
            (*mHorizontalHeader_SelectedColumns)[column]--;
        }

        viewport()->update();

        emit selectionChanged();
    }

    FASTTABLE_END_PROFILE;
}

QList<QPoint> CustomFastTableWidget::selectedCells()
{
    FASTTABLE_DEBUG;
    return *mCurSelection;
}

QList<QRect> CustomFastTableWidget::selectedRanges()
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    QList<QRect> res;

    if (mCurSelection->length()==0)
    {
        FASTTABLE_END_PROFILE;
        return res;
    }

    for (int i=0; i<mRowCount; i++)
    {
        for (int j=0; j<mColumnCount; j++)
        {
            if (mSelectedCells->at(i).at(j))
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

                    while (j+width<mColumnCount && mSelectedCells->at(i).at(j+width))
                    {
                        width++;
                    }

                    int height=1;

                    while (i+height<mRowCount)
                    {
                        for (int k=j; k<j+width; k++)
                        {
                            if (!mSelectedCells->at(i+height).at(k))
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

    if (mCurSelection->length()==0)
    {
        FASTTABLE_END_PROFILE;
        return QPoint(-1, -1);
    }

    for (int i=0; i<mRowCount; i++)
    {
        for (int j=0; j<mColumnCount; j++)
        {
            if (mSelectedCells->at(i).at(j))
            {
                FASTTABLE_END_PROFILE;
                return QPoint(j, i);
            }
        }
    }

    FASTTABLE_END_PROFILE;
    return QPoint(-1, -1);
}

bool CustomFastTableWidget::rowHasSelection(const int row)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(row>=0 && row<mVerticalHeader_SelectedRows->length());

    return mVerticalHeader_SelectedRows->at(row)!=0;
}

bool CustomFastTableWidget::columnHasSelection(const int column)
{
    FASTTABLE_DEBUG;
    FASTTABLE_ASSERT(column>=0 && column<mHorizontalHeader_SelectedColumns->length());

    return mHorizontalHeader_SelectedColumns->at(column)!=0;
}

QPoint CustomFastTableWidget::currentCell()
{
    FASTTABLE_DEBUG;
    return QPoint(mCurrentColumn, mCurrentRow);
}

void CustomFastTableWidget::setCurrentCell(const int row, const int column, const bool keepSelection)
{
    FASTTABLE_DEBUG;
    FASTTABLE_START_PROFILE;

    int realRow=row;
    int realColumn=column;

    if (realRow>=0 && realRow<mRowCount && realColumn>=0 && realColumn<mColumnCount)
    {
        if (!rowVisible(realRow))
        {
            do
            {
                --realRow;
            } while (realRow>=0 && !rowVisible(realRow));

            if (realRow<0)
            {
                realRow=row;

                do
                {
                    ++realRow;
                } while (realRow<mRowCount && !rowVisible(realRow));
            }
        }

        if (realRow<mRowCount && !columnVisible(realColumn))
        {
            do
            {
                --realColumn;
            } while (realColumn>=0 && !columnVisible(realColumn));

            if (realColumn<0)
            {
                realColumn=column;

                do
                {
                    ++realColumn;
                } while (realColumn<mColumnCount && !columnVisible(realColumn));
            }
        }
    }

    if (realRow<0 || realColumn<0 || realRow>=mRowCount || realColumn>=mColumnCount)
    {
        realRow=-1;
        realColumn=-1;
    }

    if (
        mCurrentRow!=realRow
        ||
        mCurrentColumn!=realColumn
        ||
        (
         !keepSelection
         &&
         (
          mCurSelection->length()>1
          ||
          (
           realRow>=0
           &&
           !mSelectedCells->at(realRow).at(realColumn)
          )
         )
        )
       )
    {
        int aOldCurrentRow=mCurrentRow;
        int aOldCurrentColumn=mCurrentColumn;

        mCurrentRow=realRow;
        mCurrentColumn=realColumn;

        if (!keepSelection)
        {
            unselectAll();

            if (realRow>=0)
            {
                setCellSelected(realRow, realColumn, true);
            }
        }

        viewport()->update();

        emit currentCellChanged(aOldCurrentRow, aOldCurrentColumn, mCurrentRow, mCurrentColumn);
        emit cellChanged(mCurrentRow, mCurrentColumn);
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

    setCurrentCell(row, mCurrentColumn<0? 0 : mCurrentColumn, keepSelection)

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

    setCurrentCell(mCurrentRow<0? 0: mCurrentRow, column, keepSelection)

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

    FASTTABLE_ASSERT(mVisibleBottom<mOffsetY->length());
    FASTTABLE_ASSERT(mVisibleBottom<mRowHeights->length());
    FASTTABLE_ASSERT(mVisibleRight<mOffsetX->length());
    FASTTABLE_ASSERT(mVisibleRight<mColumnWidths->length());

    int offsetX=-horizontalScrollBar()->value();
    int offsetY=-verticalScrollBar()->value();

    int resX=-1;

    for (int i=mVisibleLeft; i<=mVisibleRight; ++i)
    {
        if (x>=offsetX+mOffsetX->at(i) && x<offsetX+mOffsetX->at(i)+mColumnWidths->at(i))
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
        if (y>=offsetY+mOffsetY->at(i) && y<offsetY+mOffsetY->at(i)+mRowHeights->at(i))
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

    FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_OffsetY->length());
    FASTTABLE_ASSERT(mHorizontalHeader_VisibleBottom<mHorizontalHeader_RowHeights->length());
    FASTTABLE_ASSERT(mVisibleRight<mOffsetX->length());
    FASTTABLE_ASSERT(mVisibleRight<mColumnWidths->length());

    int offsetX=-horizontalScrollBar()->value();

    int resX=-1;

    for (int i=mVisibleLeft; i<=mVisibleRight; ++i)
    {
        if (x>=offsetX+mOffsetX->at(i) && x<offsetX+mOffsetX->at(i)+mColumnWidths->at(i))
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
        if (y>=mHorizontalHeader_OffsetY->at(i) && y<mHorizontalHeader_OffsetY->at(i)+mHorizontalHeader_RowHeights->at(i))
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

    FASTTABLE_ASSERT(mVisibleBottom<mOffsetY->length());
    FASTTABLE_ASSERT(mVisibleBottom<mRowHeights->length());
    FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_OffsetX->length());
    FASTTABLE_ASSERT(mVerticalHeader_VisibleRight<mVerticalHeader_ColumnWidths->length());

    int offsetY=-verticalScrollBar()->value();

    int resX=-1;

    for (int i=0; i<=mVerticalHeader_VisibleRight; ++i)
    {
        if (x>=mVerticalHeader_OffsetX->at(i) && x<mVerticalHeader_OffsetX->at(i)+mVerticalHeader_ColumnWidths->at(i))
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
        if (y>=offsetY+mOffsetY->at(i) && y<offsetY+mOffsetY->at(i)+mRowHeights->at(i))
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

bool CustomFastTableWidget::isEditable() const
{
    return mEditable;
}

void CustomFastTableWidget::setEditable(const bool aEditable)
{
    mEditable=aEditable;
}
