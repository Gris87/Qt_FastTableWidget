#include "testframe.h"

TestFrame::TestFrame(CustomFastTableWidget* aFastTable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestFrame)
{
    ui->setupUi(this);

    mFastTable=aFastTable;

    mDividerSplitter=new QSplitter(Qt::Vertical, this);

    ui->dividerLayout->removeWidget(ui->testsScrollArea);

    mDividerSplitter->addWidget(mFastTable);
    mDividerSplitter->addWidget(ui->testsScrollArea);

    ui->dividerLayout->addWidget(mDividerSplitter);

    mData                                   = (((PublicCustomFastTable*)mFastTable)->getData());
    mRowHeights                             = (((PublicCustomFastTable*)mFastTable)->getRowHeights());
    mColumnWidths                           = (((PublicCustomFastTable*)mFastTable)->getColumnWidths());
    mOffsetX                                = (((PublicCustomFastTable*)mFastTable)->getOffsetX());
    mOffsetY                                = (((PublicCustomFastTable*)mFastTable)->getOffsetY());

    mHorizontalHeader_Data                  = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetData());
    mHorizontalHeader_RowHeights            = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetRowHeights());
    mHorizontalHeader_ColumnWidths          = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetColumnWidths());
    mHorizontalHeader_OffsetX               = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetOffsetX());
    mHorizontalHeader_OffsetY               = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetOffsetY());

    mVerticalHeader_Data                    = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetData());
    mVerticalHeader_RowHeights              = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetRowHeights());
    mVerticalHeader_ColumnWidths            = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetColumnWidths());
    mVerticalHeader_OffsetX                 = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetOffsetX());
    mVerticalHeader_OffsetY                 = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetOffsetY());

    mSelectedCells                          = (((PublicCustomFastTable*)mFastTable)->getSelectedCells());
    mCurSelection                           = (((PublicCustomFastTable*)mFastTable)->getCurSelection());
    mHorizontalHeader_SelectedColumns       = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetSelectedColumns());
    mVerticalHeader_SelectedRows            = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetSelectedRows());

    if (mFastTable->inherits("FastTableWidget"))
    {
        mBackgroundBrushes                      = (((PublicFastTable*)mFastTable)->getBackgroundBrushes());
        mForegroundColors                       = (((PublicFastTable*)mFastTable)->getForegroundColors());
        mCellFonts                              = (((PublicFastTable*)mFastTable)->getCellFonts());
        mCellTextFlags                          = (((PublicFastTable*)mFastTable)->getCellTextFlags());
        mCellMergeX                             = (((PublicFastTable*)mFastTable)->getCellMergeX());
        mCellMergeY                             = (((PublicFastTable*)mFastTable)->getCellMergeY());
        mCellMergeParentRow                     = (((PublicFastTable*)mFastTable)->getCellMergeParentRow());
        mCellMergeParentColumn                  = (((PublicFastTable*)mFastTable)->getCellMergeParentColumn());

        mHorizontalHeader_BackgroundBrushes     = (((PublicFastTable*)mFastTable)->horizontalHeader_GetBackgroundBrushes());
        mHorizontalHeader_ForegroundColors      = (((PublicFastTable*)mFastTable)->horizontalHeader_GetForegroundColors());
        mHorizontalHeader_CellFonts             = (((PublicFastTable*)mFastTable)->horizontalHeader_GetCellFonts());
        mHorizontalHeader_CellTextFlags         = (((PublicFastTable*)mFastTable)->horizontalHeader_GetCellTextFlags());
        mHorizontalHeader_CellMergeX            = (((PublicFastTable*)mFastTable)->horizontalHeader_GetCellMergeX());
        mHorizontalHeader_CellMergeY            = (((PublicFastTable*)mFastTable)->horizontalHeader_GetCellMergeY());
        mHorizontalHeader_CellMergeParentRow    = (((PublicFastTable*)mFastTable)->horizontalHeader_GetCellMergeParentRow());
        mHorizontalHeader_CellMergeParentColumn = (((PublicFastTable*)mFastTable)->horizontalHeader_GetCellMergeParentColumn());

        mVerticalHeader_BackgroundBrushes       = (((PublicFastTable*)mFastTable)->verticalHeader_GetBackgroundBrushes());
        mVerticalHeader_ForegroundColors        = (((PublicFastTable*)mFastTable)->verticalHeader_GetForegroundColors());
        mVerticalHeader_CellFonts               = (((PublicFastTable*)mFastTable)->verticalHeader_GetCellFonts());
        mVerticalHeader_CellTextFlags           = (((PublicFastTable*)mFastTable)->verticalHeader_GetCellTextFlags());
        mVerticalHeader_CellMergeX              = (((PublicFastTable*)mFastTable)->verticalHeader_GetCellMergeX());
        mVerticalHeader_CellMergeY              = (((PublicFastTable*)mFastTable)->verticalHeader_GetCellMergeY());
        mVerticalHeader_CellMergeParentRow      = (((PublicFastTable*)mFastTable)->verticalHeader_GetCellMergeParentRow());
        mVerticalHeader_CellMergeParentColumn   = (((PublicFastTable*)mFastTable)->verticalHeader_GetCellMergeParentColumn());
    }
    else
    {
        mBackgroundBrushes                      = 0;
        mForegroundColors                       = 0;
        mCellFonts                              = 0;
        mCellTextFlags                          = 0;
        mCellMergeX                             = 0;
        mCellMergeY                             = 0;
        mCellMergeParentRow                     = 0;
        mCellMergeParentColumn                  = 0;

        mHorizontalHeader_BackgroundBrushes     = 0;
        mHorizontalHeader_ForegroundColors      = 0;
        mHorizontalHeader_CellFonts             = 0;
        mHorizontalHeader_CellTextFlags         = 0;
        mHorizontalHeader_CellMergeX            = 0;
        mHorizontalHeader_CellMergeY            = 0;
        mHorizontalHeader_CellMergeParentRow    = 0;
        mHorizontalHeader_CellMergeParentColumn = 0;

        mVerticalHeader_BackgroundBrushes       = 0;
        mVerticalHeader_ForegroundColors        = 0;
        mVerticalHeader_CellFonts               = 0;
        mVerticalHeader_CellTextFlags           = 0;
        mVerticalHeader_CellMergeX              = 0;
        mVerticalHeader_CellMergeY              = 0;
        mVerticalHeader_CellMergeParentRow      = 0;
        mVerticalHeader_CellMergeParentColumn   = 0;
    }
}

TestFrame::~TestFrame()
{
    delete ui;
}

void TestFrame::startTest()
{
    bool success;

    // ----------------------------------------------------------------
    qDebug()<<"TEST 1: Initial state";
    // ----------------------------------------------------------------
    {
        success=true;

        TEST_STEP(mCurSelection->length()==0)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==0)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getRowCount()==0)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getColumnCount()==0)
        TEST_STEP(checkForSizes(0, 0))

        testCompleted(success, ui->initialResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 2: setRowCount(50)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 0))

        testCompleted(success, ui->setRow50ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 3: setColumnCount(20)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20)
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 20))

        testCompleted(success, ui->setCol20ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 4: setColumnCount(1)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(1);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth())
        TEST_STEP(mOffsetX->at(0)==0)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 1))

        testCompleted(success, ui->setCol1ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 5: setRowCount(2)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth())
        TEST_STEP(mOffsetX->at(0)==0)
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight())
        TEST_STEP(checkForSizes(2, 1))

        testCompleted(success, ui->setRow2ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 6: clearTable()";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->clearTable();

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==0)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0)
        TEST_STEP(checkForSizes(0, 0))

        testCompleted(success, ui->clearTableResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 7: setRowCount(50)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 0))

        testCompleted(success, ui->setRow50ResLabel2);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 8: setColumnCount(20)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20)
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 20))

        testCompleted(success, ui->setCol20ResLabel2);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 9: setDefaultBackgroundBrush";
    // ----------------------------------------------------------------
    {
        success=true;

        QBrush aDefaultBackgroundBrush=((PublicCustomFastTable*)mFastTable)->getDefaultBackgroundBrush();
        QBrush aNewDefaultBackgroundBrush=QBrush(QColor(1, 2, 3));

        mFastTable->setDefaultBackgroundBrush(aNewDefaultBackgroundBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultBackgroundBrush()==aNewDefaultBackgroundBrush)

        mFastTable->setDefaultBackgroundBrush(aDefaultBackgroundBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultBackgroundBrush()==aDefaultBackgroundBrush)

        testCompleted(success, ui->setDefBackgroundResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 10: setDefaultForegroundColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aDefaultForegroundColor=((PublicCustomFastTable*)mFastTable)->getDefaultForegroundColor();
        QColor aNewDefaultForegroundColor=QColor(1, 2, 3);

        mFastTable->setDefaultForegroundColor(aNewDefaultForegroundColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultForegroundColor()==aNewDefaultForegroundColor)

        mFastTable->setDefaultForegroundColor(aDefaultForegroundColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultForegroundColor()==aDefaultForegroundColor)

        testCompleted(success, ui->setDefForegroundResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 11: setGridColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aGridColor=((PublicCustomFastTable*)mFastTable)->getGridColor();
        QColor aNewGridColor=QColor(1, 2, 3);

        mFastTable->setGridColor(aNewGridColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getGridColor()==aNewGridColor)

        mFastTable->setGridColor(aGridColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getGridColor()==aGridColor)

        testCompleted(success, ui->setGridColorResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 12: setSelectionBrush";
    // ----------------------------------------------------------------
    {
        success=true;

        QBrush aSelectionBrush=((PublicCustomFastTable*)mFastTable)->getSelectionBrush();
        QBrush aNewSelectionBrush=QBrush(QColor(1, 2, 3));

        mFastTable->setSelectionBrush(aNewSelectionBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getSelectionBrush()==aNewSelectionBrush)

        mFastTable->setSelectionBrush(aSelectionBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getSelectionBrush()==aSelectionBrush)

        testCompleted(success, ui->setSelectionColorResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 13: setDefaultHeight";
    // ----------------------------------------------------------------
    {
        success=true;

        quint16 aDefaultHeight=((PublicCustomFastTable*)mFastTable)->getDefaultHeight();
        quint16 aNewDefaultHeight=10;

        mFastTable->setDefaultHeight(aNewDefaultHeight);
        mFastTable->setRowCount(51);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultHeight()==aNewDefaultHeight)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aDefaultHeight*50+aNewDefaultHeight)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20)
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19)
        TEST_STEP(mOffsetY->at(50)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(checkForSizes(51, 20))

        mFastTable->setDefaultHeight(aDefaultHeight);
        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultHeight()==aDefaultHeight)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aDefaultHeight*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20)
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 20))

        testCompleted(success, ui->setDefHeightResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 14: setDefaultWidth";
    // ----------------------------------------------------------------
    {
        success=true;

        quint16 aDefaultWidth=((PublicCustomFastTable*)mFastTable)->getDefaultWidth();
        quint16 aNewDefaultWidth=10;

        mFastTable->setDefaultWidth(aNewDefaultWidth);
        mFastTable->setColumnCount(21);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultWidth()==aNewDefaultWidth)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aDefaultWidth*20+aNewDefaultWidth)
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19)
        TEST_STEP(mOffsetY->at(50)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(checkForSizes(50, 21))

        mFastTable->setDefaultWidth(aDefaultWidth);
        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultWidth()==aDefaultWidth)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50)
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aDefaultWidth*20)
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19)
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49)
        TEST_STEP(checkForSizes(50, 20))

        testCompleted(success, ui->setDefWidthResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 15: setRowHeight";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aTotalHeight=((PublicCustomFastTable*)mFastTable)->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(30);

        mFastTable->setRowHeight(30, aRowHeight+100);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight+100)

        mFastTable->setRowHeight(30, aRowHeight);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight)

        testCompleted(success, ui->setRowHeightResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 16: setColumnWidth";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aTotalWidth=((PublicCustomFastTable*)mFastTable)->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(10);

        mFastTable->setColumnWidth(10, aColumnWidth+100);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth+100)

        mFastTable->setColumnWidth(10, aColumnWidth);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth)

        testCompleted(success, ui->setColumnWidthResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 17: totalHeight";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aTotalHeight=((PublicCustomFastTable*)mFastTable)->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(49);

        mFastTable->setRowHeight(49, aRowHeight+100);
        mFastTable->setRowCount(51);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight+((PublicCustomFastTable*)mFastTable)->getDefaultHeight()+100)
        TEST_STEP(mOffsetY->at(50)==aTotalHeight+100)

        mFastTable->setRowHeight(49, aRowHeight);
        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight)

        testCompleted(success, ui->totalHeightResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 18: totalWidth";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aTotalWidth=((PublicCustomFastTable*)mFastTable)->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(19);

        mFastTable->setColumnWidth(19, aColumnWidth+100);
        mFastTable->setColumnCount(21);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth+((PublicCustomFastTable*)mFastTable)->getDefaultWidth()+100)
        TEST_STEP(mOffsetX->at(20)==aTotalWidth+100)

        mFastTable->setColumnWidth(19, aColumnWidth);
        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth)

        testCompleted(success, ui->totalWidthResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 19: setText";
    // ----------------------------------------------------------------
    {
        success=true;

        for (int i=0; i<mFastTable->rowCount(); ++i)
        {
            for (int j=0; j<mFastTable->columnCount(); ++j)
            {
                mFastTable->setText(i, j, QString::number(i*mFastTable->columnCount()+j));
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mData->at(i).at(j)==QString::number(i*((PublicCustomFastTable*)mFastTable)->getColumnCount()+j))
                TEST_STEP(mFastTable->text(i, j)==QString::number(i*((PublicCustomFastTable*)mFastTable)->getColumnCount()+j))

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        testCompleted(success, ui->setTextResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 20: setCellSelected";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->selectAll();

        for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mSelectedCells->at(i).at(j))

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        mFastTable->setCellSelected(10, 5, false);

        TEST_STEP(!mSelectedCells->at(10).at(5))

        mFastTable->unselectAll();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(!mSelectedCells->at(i).at(j))

                    if (!success)
                    {
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }
            }
        }

        testCompleted(success, ui->setCellSelectedResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 21: setBackgroundBrush";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QBrush aNewBackgroundBrush(QColor(1, 2, 3));

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setBackgroundBrush(i, j, aNewBackgroundBrush);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mBackgroundBrushes->at(i).at(j) && *mBackgroundBrushes->at(i).at(j)==aNewBackgroundBrush)
                TEST_STEP(aTable->backgroundBrush(i, j)==aNewBackgroundBrush)

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetBackgroundBrush(10, 5);

        TEST_STEP(mBackgroundBrushes->at(10).at(5)==0)

        aTable->resetBackgroundBrushes();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mBackgroundBrushes->at(i).at(j)==0)

                    if (!success)
                    {
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }
            }
        }

        testCompleted(success, ui->setBackgroundResLabel);
    }
    else
    {
        testNotSupported(ui->setBackgroundResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 22: setForegroundColor";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QColor aNewForegroundColor(3, 2, 1);

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setForegroundColor(i, j, aNewForegroundColor);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mForegroundColors->at(i).at(j) && *mForegroundColors->at(i).at(j)==aNewForegroundColor)
                TEST_STEP(aTable->foregroundColor(i, j)==aNewForegroundColor)

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetForegroundColor(10, 5);

        TEST_STEP(mForegroundColors->at(10).at(5)==0)

        aTable->resetForegroundColors();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mForegroundColors->at(i).at(j)==0)

                    if (!success)
                    {
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }
            }
        }

        testCompleted(success, ui->setForegroundResLabel);
    }
    else
    {
        testNotSupported(ui->setForegroundResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 23: setCellFont";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QFont aNewCellFont("Arial", 12, 1, true);

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setCellFont(i, j, aNewCellFont);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mCellFonts->at(i).at(j) && *mCellFonts->at(i).at(j)==aNewCellFont)
                TEST_STEP(aTable->cellFont(i, j)==aNewCellFont)

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetFont(10, 5);

        TEST_STEP(mCellFonts->at(10).at(5)==0)

        aTable->resetFonts();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mCellFonts->at(i).at(j)==0)

                    if (!success)
                    {
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }
            }
        }

        testCompleted(success, ui->setCellFontResLabel);
    }
    else
    {
        testNotSupported(ui->setCellFontResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 24: setTextFlags";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        int aNewFlag=Qt::AlignRight | Qt::AlignTop;

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setCellTextFlags(i, j, aNewFlag);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mCellTextFlags->at(i).at(j)==aNewFlag)
                TEST_STEP(aTable->cellTextFlags(i, j)==aNewFlag)

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetTextFlag(10, 5);

        TEST_STEP(aTable->cellTextFlags(10, 5)==(Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap))

        aTable->resetTextFlags();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(aTable->cellTextFlags(i, j)==(Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap))

                    if (!success)
                    {
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }
            }
        }

        testCompleted(success, ui->setCellTextFlagsResLabel);
    }
    else
    {
        testNotSupported(ui->setCellTextFlagsResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 25: setSpan";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        aTable->setSpan(1, 2, 2, 3);

        for (int i=1; i<=2; i++)
        {
            for (int j=2; j<=4; j++)
            {
                TEST_STEP(mCellMergeParentRow->at(i).at(j)==1)
                TEST_STEP(mCellMergeParentColumn->at(i).at(j)==2)
                TEST_STEP(aTable->spanParent(i, j)==QPoint(2, 1))
            }
        }

        TEST_STEP(mCellMergeX->at(1).at(2)==3)
        TEST_STEP(mCellMergeY->at(1).at(2)==2)

        aTable->setSpan(0, 3, 2, 1);

        for (int i=1; i<=2; i++)
        {
            for (int j=2; j<=4; j++)
            {
                if (i!=1 && j!=3)
                {
                    TEST_STEP(mCellMergeParentRow->at(i).at(j)==-1)
                    TEST_STEP(mCellMergeParentColumn->at(i).at(j)==-1)
                    TEST_STEP(aTable->spanParent(i, j)==QPoint(-1, -1))
                }
            }
        }

        TEST_STEP(mCellMergeX->at(1).at(2)==1)
        TEST_STEP(mCellMergeY->at(1).at(2)==1)

        for (int i=0; i<=1; i++)
        {
            TEST_STEP(mCellMergeParentRow->at(i).at(3)==0)
            TEST_STEP(mCellMergeParentColumn->at(i).at(3)==3)
            TEST_STEP(aTable->spanParent(i, 3)==QPoint(3, 0))
        }

        TEST_STEP(mCellMergeX->at(0).at(3)==1)
        TEST_STEP(mCellMergeY->at(0).at(3)==2)

        aTable->clearSpans();

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(aTable->rowSpan(i, j)==1)
                TEST_STEP(aTable->columnSpan(i, j)==1)
                TEST_STEP(aTable->spanParent(i, j)==QPoint(-1, -1))
                TEST_STEP(mCellMergeX->at(i).at(j)==1)
                TEST_STEP(mCellMergeY->at(i).at(j)==1)
                TEST_STEP(mCellMergeParentRow->at(i).at(j)==-1)
                TEST_STEP(mCellMergeParentColumn->at(i).at(j)==-1)

                if (!success)
                {
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        testCompleted(success, ui->setSpanResLabel);
    }
    else
    {
        testNotSupported(ui->setSpanResLabel);
    }
}

bool TestFrame::checkForSizes(int rows, int columns)
{
    bool success=true;

    TEST_STEP(((PublicCustomFastTable*)mFastTable)->getRowCount()==rows)
    TEST_STEP(((PublicCustomFastTable*)mFastTable)->getColumnCount()==columns)
    TEST_STEP((mData==0                  || mData->length()==rows))
    TEST_STEP((mRowHeights==0            || mRowHeights->length()==rows))
    TEST_STEP((mColumnWidths==0          || mColumnWidths->length()==columns))
    TEST_STEP((mOffsetX==0               || mOffsetX->length()==columns))
    TEST_STEP((mOffsetY==0               || mOffsetY->length()==rows))
    TEST_STEP((mSelectedCells==0         || mSelectedCells->length()==rows))
    TEST_STEP((mBackgroundBrushes==0     || mBackgroundBrushes->length()==rows))
    TEST_STEP((mForegroundColors==0      || mForegroundColors->length()==rows))
    TEST_STEP((mCellFonts==0             || mCellFonts->length()==rows))
    TEST_STEP((mCellTextFlags==0         || mCellTextFlags->length()==rows))
    TEST_STEP((mCellMergeX==0            || mCellMergeX->length()==rows))
    TEST_STEP((mCellMergeY==0            || mCellMergeY->length()==rows))
    TEST_STEP((mCellMergeParentRow==0    || mCellMergeParentRow->length()==rows))
    TEST_STEP((mCellMergeParentColumn==0 || mCellMergeParentColumn->length()==rows))

    CHECK_COLUMN_COUNT(mData);
    CHECK_COLUMN_COUNT(mHorizontalHeader_Data);
    CHECK_COLUMN_COUNT(mVerticalHeader_Data);
    CHECK_COLUMN_COUNT(mSelectedCells);
    CHECK_COLUMN_COUNT(mBackgroundBrushes);
    CHECK_COLUMN_COUNT(mForegroundColors);
    CHECK_COLUMN_COUNT(mCellFonts);
    CHECK_COLUMN_COUNT(mCellTextFlags);
    CHECK_COLUMN_COUNT(mCellMergeX);
    CHECK_COLUMN_COUNT(mCellMergeY);
    CHECK_COLUMN_COUNT(mCellMergeParentRow);
    CHECK_COLUMN_COUNT(mCellMergeParentColumn);
    CHECK_COLUMN_COUNT(mHorizontalHeader_BackgroundBrushes);
    CHECK_COLUMN_COUNT(mHorizontalHeader_ForegroundColors);
    CHECK_COLUMN_COUNT(mHorizontalHeader_CellFonts);
    CHECK_COLUMN_COUNT(mHorizontalHeader_CellTextFlags);
    CHECK_COLUMN_COUNT(mHorizontalHeader_CellMergeX);
    CHECK_COLUMN_COUNT(mHorizontalHeader_CellMergeY);
    CHECK_COLUMN_COUNT(mHorizontalHeader_CellMergeParentRow);
    CHECK_COLUMN_COUNT(mHorizontalHeader_CellMergeParentColumn);
    CHECK_COLUMN_COUNT(mVerticalHeader_BackgroundBrushes);
    CHECK_COLUMN_COUNT(mVerticalHeader_ForegroundColors);
    CHECK_COLUMN_COUNT(mVerticalHeader_CellFonts);
    CHECK_COLUMN_COUNT(mVerticalHeader_CellTextFlags);
    CHECK_COLUMN_COUNT(mVerticalHeader_CellMergeX);
    CHECK_COLUMN_COUNT(mVerticalHeader_CellMergeY);
    CHECK_COLUMN_COUNT(mVerticalHeader_CellMergeParentRow);
    CHECK_COLUMN_COUNT(mVerticalHeader_CellMergeParentColumn);

    return success;
}

void TestFrame::testCompleted(bool success, QLabel *aLabel)
{
    if (success)
    {
        testSuccess(aLabel);
    }
    else
    {
        testFail(aLabel);
    }
}

void TestFrame::testSuccess(QLabel *aLabel)
{
    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(0, 128, 0));

    aLabel->setText("SUCCESS");
    aLabel->setPalette(aPalette);

    emit testFinished();
}

void TestFrame::testFail(QLabel *aLabel)
{
    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(128, 0, 0));

    aLabel->setText("FAIL");
    aLabel->setPalette(aPalette);

    qWarning()<<"FAIL";

    emit testFinished();
}

void TestFrame::testNotSupported(QLabel *aLabel)
{
    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(0, 128, 128));

    aLabel->setText("NOT SUPPORTED");
    aLabel->setPalette(aPalette);

    emit testFinished();
}
