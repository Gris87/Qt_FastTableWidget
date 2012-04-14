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

    while (ui->testGridLayout->count()>0)
    {
        delete ui->testGridLayout->itemAt(0)->widget();
    }

    addTestLabel("Initial state");
    addTestLabel("setRowCount(50)");
    addTestLabel("setColumnCount(20)");
    addTestLabel("setRowCount(2)");
    addTestLabel("setColumnCount(1)");
    addTestLabel("clear()");
    addTestLabel("setRowCount(50)_2");
    addTestLabel("setColumnCount(20)_2");
    addTestLabel("horizontalHeader_SetRowCount(2)");
    addTestLabel("verticalHeader_SetColumnCount(1)");
    addTestLabel("setRowCount(2)_2");
    addTestLabel("setColumnCount(1)_2");
    addTestLabel("horizontalHeader_SetRowCount(50)");
    addTestLabel("verticalHeader_SetColumnCount(20)");
    addTestLabel("clear()_2");
    addTestLabel("setRowCount(50)_3");
    addTestLabel("setColumnCount(20)_3");
    addTestLabel("horizontalHeader_SetRowCount(2)_2");
    addTestLabel("verticalHeader_SetColumnCount(1)_2");
    addTestLabel("setDefaultBackgroundBrush");
    addTestLabel("setDefaultForegroundColor");
    addTestLabel("setGridColor");
    addTestLabel("horizontalHeader_SetDefaultBackgroundBrush");
    addTestLabel("horizontalHeader_SetDefaultForegroundColor");
    addTestLabel("horizontalHeader_SetGridColor");
    addTestLabel("verticalHeader_SetDefaultBackgroundBrush");
    addTestLabel("verticalHeader_SetDefaultForegroundColor");
    addTestLabel("verticalHeader_SetGridColor");
    addTestLabel("setSelectionBrush");
    addTestLabel("setSelectionTextColor");
    addTestLabel("setDefaultWidth");
    addTestLabel("setDefaultHeight");
    addTestLabel("setColumnWidth");
    addTestLabel("setRowHeight");
    addTestLabel("verticalHeader_SetColumnWidth");
    addTestLabel("horizontalHeader_SetRowHeight");
    addTestLabel("setText");
    addTestLabel("horizontalHeader_SetText");
    addTestLabel("verticalHeader_SetText");
    addTestLabel("setCellSelected");
    addTestLabel("setBackgroundBrush");
    addTestLabel("horizontalHeader_SetBackgroundBrush");
    addTestLabel("verticalHeader_SetBackgroundBrush");
    addTestLabel("setForegroundColor");
    addTestLabel("horizontalHeader_SetForegroundColor");
    addTestLabel("verticalHeader_SetForegroundColor");
    addTestLabel("setCellFont");
    addTestLabel("horizontalHeader_SetCellFont");
    addTestLabel("verticalHeader_SetCellFont");
    addTestLabel("setCellTextFlags");
    addTestLabel("horizontalHeader_SetCellTextFlags");
    addTestLabel("verticalHeader_SetCellTextFlags");
    addTestLabel("setSpan");
    addTestLabel("horizontalHeader_SetSpan");
    addTestLabel("verticalHeader_SetSpan");

    //-------------------------------------------------------------------------------------------------------------

    mData                                   = (((PublicCustomFastTable*)mFastTable)->getData());
    mRowHeights                             = (((PublicCustomFastTable*)mFastTable)->getRowHeights());
    mColumnWidths                           = (((PublicCustomFastTable*)mFastTable)->getColumnWidths());
    mOffsetX                                = (((PublicCustomFastTable*)mFastTable)->getOffsetX());
    mOffsetY                                = (((PublicCustomFastTable*)mFastTable)->getOffsetY());

    mHorizontalHeader_Data                  = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetData());
    mHorizontalHeader_RowHeights            = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetRowHeights());
    mHorizontalHeader_OffsetY               = (((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetOffsetY());

    mVerticalHeader_Data                    = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetData());
    mVerticalHeader_ColumnWidths            = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetColumnWidths());
    mVerticalHeader_OffsetX                 = (((PublicCustomFastTable*)mFastTable)->verticalHeader_GetOffsetX());

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

        TEST_STEP(mCurSelection->length()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==0);
        TEST_STEP(checkForSizes(0, 0, 0, 0));

        testCompleted(success, "Initial state");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 2: setRowCount(50)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(50, 0, 0, 0));

        testCompleted(success, "setRowCount(50)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 3: setColumnCount(20)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(50, 20, 0, 0));

        testCompleted(success, "setColumnCount(20)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 4: setRowCount(2)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(2, 20, 0, 0));

        testCompleted(success, "setRowCount(2)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 5: setColumnCount(1)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(1);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(mOffsetX->at(0)==0);
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(2, 1, 0, 0));

        testCompleted(success, "setColumnCount(1)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 6: clear()";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->clear();

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==0);
        TEST_STEP(checkForSizes(0, 0, 0, 0));

        testCompleted(success, "clear()");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 7: setRowCount(50)_2";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(50, 0, 0, 0));

        testCompleted(success, "setRowCount(50)_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 8: setColumnCount(20)_2";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(50, 20, 0, 0));

        testCompleted(success, "setColumnCount(20)_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 9: horizontalHeader_SetRowCount(2)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->horizontalHeader_SetRowCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 20, 2, 0));

        testCompleted(success, "horizontalHeader_SetRowCount(2)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 10: verticalHeader_SetColumnCount(1)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->verticalHeader_SetColumnCount(1);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(20+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(19+1));
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 20, 2, 1));

        testCompleted(success, "verticalHeader_SetColumnCount(1)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 11: setRowCount(2)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(20+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(2+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(19+1));
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(1+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(2, 20, 2, 1));

        testCompleted(success, "setRowCount(2)_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 12: setColumnCount(1)_2";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(1);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(1+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(2+2));
        TEST_STEP(mOffsetX->at(0)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(1+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(2, 1, 2, 1));

        testCompleted(success, "setColumnCount(1)_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 13: horizontalHeader_SetRowCount(50)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->horizontalHeader_SetRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(1+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(2+50));
        TEST_STEP(mOffsetX->at(0)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(1+50));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(2, 1, 50, 1));

        testCompleted(success, "horizontalHeader_SetRowCount(50)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 14: verticalHeader_SetColumnCount(20)";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->verticalHeader_SetColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(1+20));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(2+50));
        TEST_STEP(mOffsetX->at(0)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(mOffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(1+50));
        TEST_STEP(mVerticalHeader_OffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mHorizontalHeader_OffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(2, 1, 50, 20));

        testCompleted(success, "verticalHeader_SetColumnCount(20)");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 15: clear()_2";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->clear();

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==0);
        TEST_STEP(checkForSizes(0, 0, 0, 0));

        testCompleted(success, "clear()_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 16: setRowCount(50)_3";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(50, 0, 0, 0));

        testCompleted(success, "setRowCount(50)_3");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 17: setColumnCount(20)_3";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*50);
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*49);
        TEST_STEP(checkForSizes(50, 20, 0, 0));

        testCompleted(success, "setColumnCount(20)_3");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 18: horizontalHeader_SetRowCount(2)_2";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->horizontalHeader_SetRowCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==0);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*20);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*19);
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 20, 2, 0));

        testCompleted(success, "horizontalHeader_SetRowCount(2)_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 19: verticalHeader_SetColumnCount(1)_2";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->verticalHeader_SetColumnCount(1);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(20+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(19+1));
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 20, 2, 1));

        testCompleted(success, "verticalHeader_SetColumnCount(1)_2");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 20: setDefaultBackgroundBrush";
    // ----------------------------------------------------------------
    {
        success=true;

        QBrush aOldBrush=((PublicCustomFastTable*)mFastTable)->getDefaultBackgroundBrush();
        QBrush aNewBrush=QBrush(QColor(1, 2, 3));

        mFastTable->setDefaultBackgroundBrush(aNewBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultBackgroundBrush()==aNewBrush);

        mFastTable->setDefaultBackgroundBrush(aOldBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultBackgroundBrush()==aOldBrush);

        testCompleted(success, "setDefaultBackgroundBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 21: setDefaultForegroundColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->getDefaultForegroundColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->setDefaultForegroundColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultForegroundColor()==aNewColor);

        mFastTable->setDefaultForegroundColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultForegroundColor()==aOldColor);

        testCompleted(success, "setDefaultForegroundColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 22: setGridColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->getGridColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->setGridColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getGridColor()==aNewColor);

        mFastTable->setGridColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getGridColor()==aOldColor);

        testCompleted(success, "setGridColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 23: horizontalHeader_SetDefaultBackgroundBrush";
    // ----------------------------------------------------------------
    {
        success=true;

        QBrush aOldBrush=((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetDefaultBackgroundBrush();
        QBrush aNewBrush=QBrush(QColor(1, 2, 3));

        mFastTable->horizontalHeader_SetDefaultBackgroundBrush(aNewBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetDefaultBackgroundBrush()==aNewBrush);

        mFastTable->horizontalHeader_SetDefaultBackgroundBrush(aOldBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetDefaultBackgroundBrush()==aOldBrush);

        testCompleted(success, "horizontalHeader_SetDefaultBackgroundBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 24: horizontalHeader_SetDefaultForegroundColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetDefaultForegroundColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->horizontalHeader_SetDefaultForegroundColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetDefaultForegroundColor()==aNewColor);

        mFastTable->horizontalHeader_SetDefaultForegroundColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetDefaultForegroundColor()==aOldColor);

        testCompleted(success, "horizontalHeader_SetDefaultForegroundColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 25: horizontalHeader_SetGridColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetGridColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->horizontalHeader_SetGridColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetGridColor()==aNewColor);

        mFastTable->horizontalHeader_SetGridColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetGridColor()==aOldColor);

        testCompleted(success, "horizontalHeader_SetGridColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 26: verticalHeader_SetDefaultBackgroundBrush";
    // ----------------------------------------------------------------
    {
        success=true;

        QBrush aOldBrush=((PublicCustomFastTable*)mFastTable)->verticalHeader_GetDefaultBackgroundBrush();
        QBrush aNewBrush=QBrush(QColor(1, 2, 3));

        mFastTable->verticalHeader_SetDefaultBackgroundBrush(aNewBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetDefaultBackgroundBrush()==aNewBrush);

        mFastTable->verticalHeader_SetDefaultBackgroundBrush(aOldBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetDefaultBackgroundBrush()==aOldBrush);

        testCompleted(success, "verticalHeader_SetDefaultBackgroundBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 27: verticalHeader_SetDefaultForegroundColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->verticalHeader_GetDefaultForegroundColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->verticalHeader_SetDefaultForegroundColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetDefaultForegroundColor()==aNewColor);

        mFastTable->verticalHeader_SetDefaultForegroundColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetDefaultForegroundColor()==aOldColor);

        testCompleted(success, "verticalHeader_SetDefaultForegroundColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 28: verticalHeader_SetGridColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->verticalHeader_GetGridColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->verticalHeader_SetGridColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetGridColor()==aNewColor);

        mFastTable->verticalHeader_SetGridColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetGridColor()==aOldColor);

        testCompleted(success, "verticalHeader_SetGridColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 29: setSelectionBrush";
    // ----------------------------------------------------------------
    {
        success=true;

        QBrush aOldBrush=((PublicCustomFastTable*)mFastTable)->getSelectionBrush();
        QBrush aNewBrush=QBrush(QColor(1, 2, 3));

        mFastTable->setSelectionBrush(aNewBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getSelectionBrush()==aNewBrush);

        mFastTable->setSelectionBrush(aOldBrush);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getSelectionBrush()==aOldBrush);

        testCompleted(success, "setSelectionBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 30: setSelectionTextColor";
    // ----------------------------------------------------------------
    {
        success=true;

        QColor aOldColor=((PublicCustomFastTable*)mFastTable)->getSelectionTextColor();
        QColor aNewColor=QColor(1, 2, 3);

        mFastTable->setSelectionTextColor(aNewColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getSelectionTextColor()==aNewColor);

        mFastTable->setSelectionTextColor(aOldColor);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getSelectionTextColor()==aOldColor);

        testCompleted(success, "setSelectionTextColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 31: setDefaultWidth";
    // ----------------------------------------------------------------
    {
        success=true;

        quint16 aDefaultWidth=((PublicCustomFastTable*)mFastTable)->getDefaultWidth();
        quint16 aNewDefaultWidth=aDefaultWidth+10;

        mFastTable->setDefaultWidth(aNewDefaultWidth);
        mFastTable->setColumnCount(21);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultWidth()==aNewDefaultWidth);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==aDefaultWidth);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aDefaultWidth*(20+1)+aNewDefaultWidth);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(20)==aDefaultWidth*(20+1));
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 21, 2, 1));

        mFastTable->setDefaultWidth(aDefaultWidth);
        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultWidth()==aDefaultWidth);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(20+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(19+1));
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 20, 2, 1));

        testCompleted(success, "setDefaultWidth");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 32: setDefaultHeight";
    // ----------------------------------------------------------------
    {
        success=true;

        quint16 aDefaultHeight=((PublicCustomFastTable*)mFastTable)->getDefaultHeight();
        quint16 aNewDefaultHeight=aDefaultHeight+10;

        mFastTable->setDefaultHeight(aNewDefaultHeight);
        mFastTable->setRowCount(51);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultHeight()==aNewDefaultHeight);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==aDefaultHeight*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(20+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aDefaultHeight*(50+2)+aNewDefaultHeight);
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(19+1));
        TEST_STEP(mOffsetY->at(50)==aDefaultHeight*(50+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==aDefaultHeight);
        TEST_STEP(checkForSizes(51, 20, 2, 1));

        mFastTable->setDefaultHeight(aDefaultHeight);
        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getDefaultHeight()==aDefaultHeight);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth());
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*2);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(20+1));
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(50+2));
        TEST_STEP(mOffsetX->at(19)==((PublicCustomFastTable*)mFastTable)->getDefaultWidth()*(19+1));
        TEST_STEP(mOffsetY->at(49)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight()*(49+2));
        TEST_STEP(mVerticalHeader_OffsetX->at(0)==0);
        TEST_STEP(mHorizontalHeader_OffsetY->at(1)==((PublicCustomFastTable*)mFastTable)->getDefaultHeight());
        TEST_STEP(checkForSizes(50, 20, 2, 1));

        testCompleted(success, "setDefaultHeight");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 33: setColumnWidth";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aTotalWidth=((PublicCustomFastTable*)mFastTable)->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(19);

        mFastTable->setColumnWidth(19, aColumnWidth+100);
        mFastTable->setColumnCount(21);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth+((PublicCustomFastTable*)mFastTable)->getDefaultWidth()+100);
        TEST_STEP(mOffsetX->at(20)==aTotalWidth+100);

        mFastTable->setColumnWidth(19, aColumnWidth);
        mFastTable->setColumnCount(20);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth);


        testCompleted(success, "setColumnWidth");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 34: setRowHeight";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aTotalHeight=((PublicCustomFastTable*)mFastTable)->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(49);

        mFastTable->setRowHeight(49, aRowHeight+100);
        mFastTable->setRowCount(51);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight+((PublicCustomFastTable*)mFastTable)->getDefaultHeight()+100);
        TEST_STEP(mOffsetY->at(50)==aTotalHeight+100);

        mFastTable->setRowHeight(49, aRowHeight);
        mFastTable->setRowCount(50);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight);


        testCompleted(success, "setRowHeight");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 35: verticalHeader_SetColumnWidth";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aVerticalTotalWidth=((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth();
        int     aTotalWidth=((PublicCustomFastTable*)mFastTable)->getTotalWidth();
        quint16 aColumnWidth=mVerticalHeader_ColumnWidths->at(0);

        mFastTable->verticalHeader_SetColumnWidth(0, aColumnWidth+100);
        mFastTable->verticalHeader_SetColumnCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==aVerticalTotalWidth+((PublicCustomFastTable*)mFastTable)->getDefaultWidth()+100);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth+((PublicCustomFastTable*)mFastTable)->getDefaultWidth()+100);
        TEST_STEP(mVerticalHeader_OffsetX->at(1)==aColumnWidth+100);
        TEST_STEP(mOffsetX->at(19)==aTotalWidth+100);

        mFastTable->verticalHeader_SetColumnWidth(0, aColumnWidth);
        mFastTable->verticalHeader_SetColumnCount(1);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetTotalWidth()==aVerticalTotalWidth);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalWidth()==aTotalWidth);

        testCompleted(success, "verticalHeader_SetColumnWidth");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 36: horizontalHeader_SetRowHeight";
    // ----------------------------------------------------------------
    {
        success=true;

        int     aHorizontalTotalHeight=((PublicCustomFastTable*)mFastTable)->horizontalHeader_TotalHeight();
        int     aTotalHeight=((PublicCustomFastTable*)mFastTable)->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(1);

        mFastTable->horizontalHeader_SetRowHeight(1, aRowHeight+100);
        mFastTable->horizontalHeader_SetRowCount(3);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_TotalHeight()==aHorizontalTotalHeight+((PublicCustomFastTable*)mFastTable)->getDefaultHeight()+100);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight+((PublicCustomFastTable*)mFastTable)->getDefaultHeight()+100);
        TEST_STEP(mHorizontalHeader_OffsetY->at(2)==aRowHeight+((PublicCustomFastTable*)mFastTable)->getDefaultHeight()+100);
        TEST_STEP(mOffsetY->at(49)==aTotalHeight+100);

        mFastTable->horizontalHeader_SetRowHeight(1, aRowHeight);
        mFastTable->horizontalHeader_SetRowCount(2);

        TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_TotalHeight()==aHorizontalTotalHeight);
        TEST_STEP(((PublicCustomFastTable*)mFastTable)->getTotalHeight()==aTotalHeight);

        testCompleted(success, "horizontalHeader_SetRowHeight");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 37: horizontalHeader_SetText";
    // ----------------------------------------------------------------
    {
        success=true;

        for (int i=0; i<mFastTable->horizontalHeader_RowCount(); ++i)
        {
            for (int j=0; j<mFastTable->columnCount(); ++j)
            {
                mFastTable->horizontalHeader_SetText(i, j, "A"+QString::number(i*mFastTable->columnCount()+j));
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mHorizontalHeader_Data->at(i).at(j)=="A"+QString::number(i*((PublicCustomFastTable*)mFastTable)->getColumnCount()+j));
                TEST_STEP(mFastTable->horizontalHeader_Text(i, j)=="A"+QString::number(i*((PublicCustomFastTable*)mFastTable)->getColumnCount()+j));

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

        testCompleted(success, "horizontalHeader_SetText");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 38: verticalHeader_SetText";
    // ----------------------------------------------------------------
    {
        success=true;

        for (int i=0; i<mFastTable->rowCount(); ++i)
        {
            mFastTable->verticalHeader_SetText(i, 0, "B"+QString::number(i));
        }

        for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
        {
            TEST_STEP(mVerticalHeader_Data->at(i).at(0)=="B"+QString::number(i));
            TEST_STEP(mFastTable->verticalHeader_Text(i, 0)=="B"+QString::number(i));

            if (!success)
            {
                break;
            }
        }

        for (int i=0; i<mFastTable->rowCount(); ++i)
        {
            mFastTable->verticalHeader_SetText(i, 0, "");
        }

        for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
        {
            TEST_STEP(mVerticalHeader_Data->at(i).at(0)=="");
            TEST_STEP(mFastTable->verticalHeader_Text(i, 0)=="");

            if (!success)
            {
                break;
            }
        }

        testCompleted(success, "verticalHeader_SetText");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 39: setText";
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
                TEST_STEP(mData->at(i).at(j)==QString::number(i*((PublicCustomFastTable*)mFastTable)->getColumnCount()+j));
                TEST_STEP(mFastTable->text(i, j)==QString::number(i*((PublicCustomFastTable*)mFastTable)->getColumnCount()+j));

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

        testCompleted(success, "setText");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 40: setCellSelected";
    // ----------------------------------------------------------------
    {
        success=true;

        mFastTable->selectAll();

        for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mSelectedCells->at(i).at(j));

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

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
            {
                TEST_STEP(mVerticalHeader_SelectedRows->at(i));

                if (!success)
                {
                    break;
                }
            }
        }

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++i)
            {
                TEST_STEP(mHorizontalHeader_SelectedColumns->at(i));

                if (!success)
                {
                    break;
                }
            }
        }

        TEST_STEP(mCurSelection->length()==50*20);

        mFastTable->setCellSelected(10, 5, false);

        TEST_STEP(!mSelectedCells->at(10).at(5));
        TEST_STEP(mCurSelection->length()==50*20-1);

        mFastTable->unselectRow(10);

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++i)
            {
                TEST_STEP(!mSelectedCells->at(10).at(i));

                if (!success)
                {
                    break;
                }
            }
        }

        TEST_STEP(!mVerticalHeader_SelectedRows->at(10));
        TEST_STEP(mCurSelection->length()==49*20);

        mFastTable->unselectColumn(5);

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
            {
                TEST_STEP(!mSelectedCells->at(i).at(5));

                if (!success)
                {
                    break;
                }
            }
        }

        TEST_STEP(!mHorizontalHeader_SelectedColumns->at(5));
        TEST_STEP(mCurSelection->length()==49*19);

        mFastTable->unselectAll();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(!mSelectedCells->at(i).at(j));

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

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getRowCount(); ++i)
            {
                TEST_STEP(!mVerticalHeader_SelectedRows->at(i));

                if (!success)
                {
                    break;
                }
            }
        }

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)mFastTable)->getColumnCount(); ++i)
            {
                TEST_STEP(!mHorizontalHeader_SelectedColumns->at(i));

                if (!success)
                {
                    break;
                }
            }
        }

        TEST_STEP(mCurSelection->length()==0);

        testCompleted(success, "setCellSelected");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 41: setBackgroundBrush";
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
                TEST_STEP(mBackgroundBrushes->at(i).at(j) && *mBackgroundBrushes->at(i).at(j)==aNewBackgroundBrush);
                TEST_STEP(aTable->backgroundBrush(i, j)==aNewBackgroundBrush);

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

        TEST_STEP(mBackgroundBrushes->at(10).at(5)==0);

        aTable->resetBackgroundBrushes();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mBackgroundBrushes->at(i).at(j)==0);

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

        testCompleted(success, "setBackgroundBrush");
    }
    else
    {
        testNotSupported("setBackgroundBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 42: horizontalHeader_SetBackgroundBrush";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QBrush aNewBackgroundBrush(QColor(1, 2, 3));

        for (int i=0; i<aTable->horizontalHeader_RowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->horizontalHeader_SetBackgroundBrush(i, j, aNewBackgroundBrush);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mHorizontalHeader_BackgroundBrushes->at(i).at(j) && *mHorizontalHeader_BackgroundBrushes->at(i).at(j)==aNewBackgroundBrush);
                TEST_STEP(aTable->horizontalHeader_BackgroundBrush(i, j)==aNewBackgroundBrush);

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

        aTable->horizontalHeader_ResetBackgroundBrush(1, 0);

        TEST_STEP(mHorizontalHeader_BackgroundBrushes->at(1).at(0)==0);

        aTable->horizontalHeader_ResetBackgroundBrushes();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mHorizontalHeader_BackgroundBrushes->at(i).at(j)==0);

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

        testCompleted(success, "horizontalHeader_SetBackgroundBrush");
    }
    else
    {
        testNotSupported("horizontalHeader_SetBackgroundBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 43: verticalHeader_SetBackgroundBrush";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QBrush aNewBackgroundBrush(QColor(1, 2, 3));

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->verticalHeader_ColumnCount(); ++j)
            {
                aTable->verticalHeader_SetBackgroundBrush(i, j, aNewBackgroundBrush);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
            {
                TEST_STEP(mVerticalHeader_BackgroundBrushes->at(i).at(j) && *mVerticalHeader_BackgroundBrushes->at(i).at(j)==aNewBackgroundBrush);
                TEST_STEP(aTable->verticalHeader_BackgroundBrush(i, j)==aNewBackgroundBrush);

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

        aTable->verticalHeader_ResetBackgroundBrush(1, 0);

        TEST_STEP(mVerticalHeader_BackgroundBrushes->at(1).at(0)==0);

        aTable->verticalHeader_ResetBackgroundBrushes();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
                {
                    TEST_STEP(mVerticalHeader_BackgroundBrushes->at(i).at(j)==0);

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

        testCompleted(success, "verticalHeader_SetBackgroundBrush");
    }
    else
    {
        testNotSupported("verticalHeader_SetBackgroundBrush");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 44: setForegroundColor";
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
                TEST_STEP(mForegroundColors->at(i).at(j) && *mForegroundColors->at(i).at(j)==aNewForegroundColor);
                TEST_STEP(aTable->foregroundColor(i, j)==aNewForegroundColor);

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

        TEST_STEP(mForegroundColors->at(10).at(5)==0);

        aTable->resetForegroundColors();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mForegroundColors->at(i).at(j)==0);

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

        testCompleted(success, "setForegroundColor");
    }
    else
    {
        testNotSupported("setForegroundColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 45: horizontalHeader_SetForegroundColor";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QColor aNewForegroundColor(3, 2, 1);

        for (int i=0; i<aTable->horizontalHeader_RowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->horizontalHeader_SetForegroundColor(i, j, aNewForegroundColor);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mHorizontalHeader_ForegroundColors->at(i).at(j) && *mHorizontalHeader_ForegroundColors->at(i).at(j)==aNewForegroundColor);
                TEST_STEP(aTable->horizontalHeader_ForegroundColor(i, j)==aNewForegroundColor);

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

        aTable->horizontalHeader_ResetForegroundColor(1, 0);

        TEST_STEP(mHorizontalHeader_ForegroundColors->at(1).at(0)==0);

        aTable->horizontalHeader_ResetForegroundColors();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mHorizontalHeader_ForegroundColors->at(i).at(j)==0);

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

        testCompleted(success, "horizontalHeader_SetForegroundColor");
    }
    else
    {
        testNotSupported("horizontalHeader_SetForegroundColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 46: verticalHeader_SetForegroundColor";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QColor aNewForegroundColor(3, 2, 1);

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->verticalHeader_ColumnCount(); ++j)
            {
                aTable->verticalHeader_SetForegroundColor(i, j, aNewForegroundColor);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
            {
                TEST_STEP(mVerticalHeader_ForegroundColors->at(i).at(j) && *mVerticalHeader_ForegroundColors->at(i).at(j)==aNewForegroundColor);
                TEST_STEP(aTable->verticalHeader_ForegroundColor(i, j)==aNewForegroundColor);

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

        aTable->verticalHeader_ResetForegroundColor(1, 0);

        TEST_STEP(mVerticalHeader_ForegroundColors->at(1).at(0)==0);

        aTable->verticalHeader_ResetForegroundColors();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
                {
                    TEST_STEP(mVerticalHeader_ForegroundColors->at(i).at(j)==0);

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

        testCompleted(success, "verticalHeader_SetForegroundColor");
    }
    else
    {
        testNotSupported("verticalHeader_SetForegroundColor");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 47: setCellFont";
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
                TEST_STEP(mCellFonts->at(i).at(j) && *mCellFonts->at(i).at(j)==aNewCellFont);
                TEST_STEP(aTable->cellFont(i, j)==aNewCellFont);

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

        TEST_STEP(mCellFonts->at(10).at(5)==0);

        aTable->resetFonts();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mCellFonts->at(i).at(j)==0);

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

        testCompleted(success, "setCellFont");
    }
    else
    {
        testNotSupported("setCellFont");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 48: horizontalHeader_SetCellFont";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QFont aNewCellFont("Arial", 12, 1, true);

        for (int i=0; i<aTable->horizontalHeader_RowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->horizontalHeader_SetCellFont(i, j, aNewCellFont);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mHorizontalHeader_CellFonts->at(i).at(j) && *mHorizontalHeader_CellFonts->at(i).at(j)==aNewCellFont);
                TEST_STEP(aTable->horizontalHeader_CellFont(i, j)==aNewCellFont);

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

        aTable->horizontalHeader_ResetFont(1, 0);

        TEST_STEP(mHorizontalHeader_CellFonts->at(1).at(0)==0);

        aTable->horizontalHeader_ResetFonts();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mHorizontalHeader_CellFonts->at(i).at(j)==0);

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

        testCompleted(success, "horizontalHeader_SetCellFont");
    }
    else
    {
        testNotSupported("horizontalHeader_SetCellFont");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 49: verticalHeader_SetCellFont";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QFont aNewCellFont("Arial", 12, 1, true);

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->verticalHeader_ColumnCount(); ++j)
            {
                aTable->verticalHeader_SetCellFont(i, j, aNewCellFont);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
            {
                TEST_STEP(mVerticalHeader_CellFonts->at(i).at(j) && *mVerticalHeader_CellFonts->at(i).at(j)==aNewCellFont);
                TEST_STEP(aTable->verticalHeader_CellFont(i, j)==aNewCellFont);

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

        aTable->verticalHeader_ResetFont(1, 0);

        TEST_STEP(mVerticalHeader_CellFonts->at(1).at(0)==0);

        aTable->verticalHeader_ResetFonts();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
                {
                    TEST_STEP(mVerticalHeader_CellFonts->at(i).at(j)==0);

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

        testCompleted(success, "verticalHeader_SetCellFont");
    }
    else
    {
        testNotSupported("verticalHeader_SetCellFont");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 50: setCellTextFlags";
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
                TEST_STEP(mCellTextFlags->at(i).at(j)==aNewFlag);
                TEST_STEP(aTable->cellTextFlags(i, j)==aNewFlag);

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

        aTable->resetCellTextFlag(10, 5);

        TEST_STEP(aTable->cellTextFlags(10, 5)==(FASTTABLE_DEFAULT_TEXT_FLAG));

        aTable->resetCellTextFlags();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mCellTextFlags->at(i).at(j)==(FASTTABLE_DEFAULT_TEXT_FLAG));
                    TEST_STEP(aTable->cellTextFlags(i, j)==(FASTTABLE_DEFAULT_TEXT_FLAG));

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

        testCompleted(success, "setCellTextFlags");
    }
    else
    {
        testNotSupported("setCellTextFlags");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 51: horizontalHeader_SetCellTextFlags";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        int aNewFlag=Qt::AlignRight | Qt::AlignTop;

        for (int i=0; i<aTable->horizontalHeader_RowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->horizontalHeader_SetCellTextFlags(i, j, aNewFlag);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(mHorizontalHeader_CellTextFlags->at(i).at(j)==aNewFlag);
                TEST_STEP(aTable->horizontalHeader_CellTextFlags(i, j)==aNewFlag);

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

        aTable->horizontalHeader_ResetCellTextFlag(1, 0);

        TEST_STEP(aTable->horizontalHeader_CellTextFlags(1, 0)==(FASTTABLE_HEADER_DEFAULT_TEXT_FLAG));

        aTable->horizontalHeader_ResetCellTextFlags();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
                {
                    TEST_STEP(mHorizontalHeader_CellTextFlags->at(i).at(j)==(FASTTABLE_HEADER_DEFAULT_TEXT_FLAG));
                    TEST_STEP(aTable->horizontalHeader_CellTextFlags(i, j)==(FASTTABLE_HEADER_DEFAULT_TEXT_FLAG));

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

        testCompleted(success, "horizontalHeader_SetCellTextFlags");
    }
    else
    {
        testNotSupported("horizontalHeader_SetCellTextFlags");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 52: verticalHeader_SetCellTextFlags";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        int aNewFlag=Qt::AlignRight | Qt::AlignTop;

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->verticalHeader_ColumnCount(); ++j)
            {
                aTable->verticalHeader_SetCellTextFlags(i, j, aNewFlag);
            }
        }

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
            {
                TEST_STEP(mVerticalHeader_CellTextFlags->at(i).at(j)==aNewFlag);
                TEST_STEP(aTable->verticalHeader_CellTextFlags(i, j)==aNewFlag);

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

        aTable->verticalHeader_ResetCellTextFlag(1, 0);

        TEST_STEP(aTable->verticalHeader_CellTextFlags(1, 0)==(FASTTABLE_DEFAULT_TEXT_FLAG));

        aTable->verticalHeader_ResetCellTextFlags();

        if (success)
        {
            for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
                {
                    TEST_STEP(mVerticalHeader_CellTextFlags->at(i).at(j)==(FASTTABLE_DEFAULT_TEXT_FLAG));
                    TEST_STEP(aTable->verticalHeader_CellTextFlags(i, j)==(FASTTABLE_DEFAULT_TEXT_FLAG));

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

        testCompleted(success, "verticalHeader_SetCellTextFlags");
    }
    else
    {
        testNotSupported("verticalHeader_SetCellTextFlags");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 53: setSpan";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        aTable->setSpan(1, 2, 2, 3);

        for (int i=1; i<=2; ++i)
        {
            for (int j=2; j<=4; ++j)
            {
                TEST_STEP(mCellMergeParentRow->at(i).at(j)==1);
                TEST_STEP(mCellMergeParentColumn->at(i).at(j)==2);
                TEST_STEP(aTable->spanParent(i, j)==QPoint(2, 1));
            }
        }

        TEST_STEP(mCellMergeX->at(1).at(2)==3);
        TEST_STEP(mCellMergeY->at(1).at(2)==2);

        aTable->setSpan(0, 3, 2, 1);

        for (int i=1; i<=2; ++i)
        {
            for (int j=2; j<=4; ++j)
            {
                if (i!=1 || j!=3)
                {
                    TEST_STEP(mCellMergeParentRow->at(i).at(j)==-1);
                    TEST_STEP(mCellMergeParentColumn->at(i).at(j)==-1);
                    TEST_STEP(aTable->spanParent(i, j)==QPoint(-1, -1));
                }
            }
        }

        TEST_STEP(mCellMergeX->at(1).at(2)==1);
        TEST_STEP(mCellMergeY->at(1).at(2)==1);

        for (int i=0; i<=1; ++i)
        {
            TEST_STEP(mCellMergeParentRow->at(i).at(3)==0);
            TEST_STEP(mCellMergeParentColumn->at(i).at(3)==3);
            TEST_STEP(aTable->spanParent(i, 3)==QPoint(3, 0));
        }

        TEST_STEP(mCellMergeX->at(0).at(3)==1);
        TEST_STEP(mCellMergeY->at(0).at(3)==2);

        aTable->clearSpans();

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(aTable->rowSpan(i, j)==1);
                TEST_STEP(aTable->columnSpan(i, j)==1);
                TEST_STEP(aTable->spanParent(i, j)==QPoint(-1, -1));
                TEST_STEP(mCellMergeX->at(i).at(j)==1);
                TEST_STEP(mCellMergeY->at(i).at(j)==1);
                TEST_STEP(mCellMergeParentRow->at(i).at(j)==-1);
                TEST_STEP(mCellMergeParentColumn->at(i).at(j)==-1);

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

        testCompleted(success, "setSpan");
    }
    else
    {
        testNotSupported("setSpan");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 54: horizontalHeader_SetSpan";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        aTable->horizontalHeader_SetSpan(0, 2, 2, 3);

        for (int i=0; i<=1; ++i)
        {
            for (int j=2; j<=4; ++j)
            {
                TEST_STEP(mHorizontalHeader_CellMergeParentRow->at(i).at(j)==0);
                TEST_STEP(mHorizontalHeader_CellMergeParentColumn->at(i).at(j)==2);
                TEST_STEP(aTable->horizontalHeader_SpanParent(i, j)==QPoint(2, 0));
            }
        }

        TEST_STEP(mHorizontalHeader_CellMergeX->at(0).at(2)==3);
        TEST_STEP(mHorizontalHeader_CellMergeY->at(0).at(2)==2);

        aTable->horizontalHeader_SetSpan(0, 1, 1, 2);

        for (int i=0; i<=1; ++i)
        {
            for (int j=2; j<=4; ++j)
            {
                if (i!=0 || j!=2)
                {
                    TEST_STEP(mHorizontalHeader_CellMergeParentRow->at(i).at(j)==-1);
                    TEST_STEP(mHorizontalHeader_CellMergeParentColumn->at(i).at(j)==-1);
                    TEST_STEP(aTable->horizontalHeader_SpanParent(i, j)==QPoint(-1, -1));
                }
            }
        }

        TEST_STEP(mHorizontalHeader_CellMergeX->at(0).at(2)==1);
        TEST_STEP(mHorizontalHeader_CellMergeY->at(0).at(2)==1);

        for (int i=1; i<=2; ++i)
        {
            TEST_STEP(mHorizontalHeader_CellMergeParentRow->at(0).at(i)==0);
            TEST_STEP(mHorizontalHeader_CellMergeParentColumn->at(0).at(i)==1);
            TEST_STEP(aTable->horizontalHeader_SpanParent(0, i)==QPoint(1, 0));
        }

        TEST_STEP(mHorizontalHeader_CellMergeX->at(0).at(1)==2);
        TEST_STEP(mHorizontalHeader_CellMergeY->at(0).at(1)==1);

        aTable->horizontalHeader_ClearSpans();

        for (int i=0; i<((PublicCustomFastTable*)aTable)->horizontalHeader_GetRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->getColumnCount(); ++j)
            {
                TEST_STEP(aTable->horizontalHeader_RowSpan(i, j)==1);
                TEST_STEP(aTable->horizontalHeader_ColumnSpan(i, j)==1);
                TEST_STEP(aTable->horizontalHeader_SpanParent(i, j)==QPoint(-1, -1));
                TEST_STEP(mHorizontalHeader_CellMergeX->at(i).at(j)==1);
                TEST_STEP(mHorizontalHeader_CellMergeY->at(i).at(j)==1);
                TEST_STEP(mHorizontalHeader_CellMergeParentRow->at(i).at(j)==-1);
                TEST_STEP(mHorizontalHeader_CellMergeParentColumn->at(i).at(j)==-1);

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

        testCompleted(success, "horizontalHeader_SetSpan");
    }
    else
    {
        testNotSupported("horizontalHeader_SetSpan");
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 55: verticalHeader_SetSpan";
    // ----------------------------------------------------------------
    if (mFastTable->inherits("FastTableWidget"))
    {
        success=true;

        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        aTable->verticalHeader_SetSpan(2, 0, 3, 1);

        for (int i=2; i<=4; ++i)
        {
            TEST_STEP(mVerticalHeader_CellMergeParentRow->at(i).at(0)==2);
            TEST_STEP(mVerticalHeader_CellMergeParentColumn->at(i).at(0)==0);
            TEST_STEP(aTable->verticalHeader_SpanParent(i, 0)==QPoint(0, 2));
        }

        TEST_STEP(mVerticalHeader_CellMergeX->at(2).at(0)==1);
        TEST_STEP(mVerticalHeader_CellMergeY->at(2).at(0)==3);

        aTable->verticalHeader_SetSpan(3, 0, 2, 1);

        TEST_STEP(mVerticalHeader_CellMergeParentRow->at(2).at(0)==-1);
        TEST_STEP(mVerticalHeader_CellMergeParentColumn->at(2).at(0)==-1);
        TEST_STEP(aTable->verticalHeader_SpanParent(2, 0)==QPoint(-1, -1));
        TEST_STEP(mVerticalHeader_CellMergeX->at(2).at(0)==1);
        TEST_STEP(mVerticalHeader_CellMergeY->at(2).at(0)==1);

        for (int i=3; i<=4; ++i)
        {
            TEST_STEP(mVerticalHeader_CellMergeParentRow->at(i).at(0)==3);
            TEST_STEP(mVerticalHeader_CellMergeParentColumn->at(i).at(0)==0);
            TEST_STEP(aTable->verticalHeader_SpanParent(i, 0)==QPoint(0, 3));
        }

        TEST_STEP(mVerticalHeader_CellMergeX->at(3).at(0)==1);
        TEST_STEP(mVerticalHeader_CellMergeY->at(3).at(0)==2);

        aTable->verticalHeader_ClearSpans();

        for (int i=0; i<((PublicCustomFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicCustomFastTable*)aTable)->verticalHeader_GetColumnCount(); ++j)
            {
                TEST_STEP(aTable->verticalHeader_RowSpan(i, j)==1);
                TEST_STEP(aTable->verticalHeader_ColumnSpan(i, j)==1);
                TEST_STEP(aTable->verticalHeader_SpanParent(i, j)==QPoint(-1, -1));
                TEST_STEP(mVerticalHeader_CellMergeX->at(i).at(j)==1);
                TEST_STEP(mVerticalHeader_CellMergeY->at(i).at(j)==1);
                TEST_STEP(mVerticalHeader_CellMergeParentRow->at(i).at(j)==-1);
                TEST_STEP(mVerticalHeader_CellMergeParentColumn->at(i).at(j)==-1);

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

        testCompleted(success, "verticalHeader_SetSpan");
    }
    else
    {
        testNotSupported("verticalHeader_SetSpan");
    }
}

bool TestFrame::checkForSizes(int rows, int columns, int headerRows, int headerColumns)
{
    bool success=true;

    TEST_STEP(((PublicCustomFastTable*)mFastTable)->getRowCount()==rows);
    TEST_STEP(((PublicCustomFastTable*)mFastTable)->getColumnCount()==columns);
    TEST_STEP(((PublicCustomFastTable*)mFastTable)->horizontalHeader_GetRowCount()==headerRows);
    TEST_STEP(((PublicCustomFastTable*)mFastTable)->verticalHeader_GetColumnCount()==headerColumns);

    TEST_STEP((mData==0                                   || mData->length()==rows));
    TEST_STEP((mRowHeights==0                             || mRowHeights->length()==rows));
    TEST_STEP((mColumnWidths==0                           || mColumnWidths->length()==columns));
    TEST_STEP((mOffsetX==0                                || mOffsetX->length()==columns));
    TEST_STEP((mOffsetY==0                                || mOffsetY->length()==rows));

    TEST_STEP((mHorizontalHeader_Data==0                  || mHorizontalHeader_Data->length()==headerRows                  || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_RowHeights==0            || mHorizontalHeader_RowHeights->length()==headerRows            || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_OffsetY==0               || mHorizontalHeader_OffsetY->length()==headerRows               || rows<=0 || columns<=0));

    TEST_STEP((mVerticalHeader_Data==0                    || mVerticalHeader_Data->length()==rows                          || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_ColumnWidths==0            || mVerticalHeader_ColumnWidths->length()==headerColumns         || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_OffsetX==0                 || mVerticalHeader_OffsetX->length()==headerColumns              || rows<=0 || columns<=0));

    TEST_STEP((mSelectedCells==0                          || mSelectedCells->length()==rows));
    TEST_STEP((mHorizontalHeader_SelectedColumns==0       || mHorizontalHeader_SelectedColumns->length()==columns));
    TEST_STEP((mVerticalHeader_SelectedRows==0            || mVerticalHeader_SelectedRows->length()==rows));

    TEST_STEP((mBackgroundBrushes==0                      || mBackgroundBrushes->length()==rows));
    TEST_STEP((mForegroundColors==0                       || mForegroundColors->length()==rows));
    TEST_STEP((mCellFonts==0                              || mCellFonts->length()==rows));
    TEST_STEP((mCellTextFlags==0                          || mCellTextFlags->length()==rows));
    TEST_STEP((mCellMergeX==0                             || mCellMergeX->length()==rows));
    TEST_STEP((mCellMergeY==0                             || mCellMergeY->length()==rows));
    TEST_STEP((mCellMergeParentRow==0                     || mCellMergeParentRow->length()==rows));
    TEST_STEP((mCellMergeParentColumn==0                  || mCellMergeParentColumn->length()==rows));

    TEST_STEP((mHorizontalHeader_BackgroundBrushes==0     || mHorizontalHeader_BackgroundBrushes->length()==headerRows     || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_ForegroundColors==0      || mHorizontalHeader_ForegroundColors->length()==headerRows      || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_CellFonts==0             || mHorizontalHeader_CellFonts->length()==headerRows             || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_CellTextFlags==0         || mHorizontalHeader_CellTextFlags->length()==headerRows         || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_CellMergeX==0            || mHorizontalHeader_CellMergeX->length()==headerRows            || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_CellMergeY==0            || mHorizontalHeader_CellMergeY->length()==headerRows            || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_CellMergeParentRow==0    || mHorizontalHeader_CellMergeParentRow->length()==headerRows    || rows<=0 || columns<=0));
    TEST_STEP((mHorizontalHeader_CellMergeParentColumn==0 || mHorizontalHeader_CellMergeParentColumn->length()==headerRows || rows<=0 || columns<=0));

    TEST_STEP((mVerticalHeader_BackgroundBrushes==0       || mVerticalHeader_BackgroundBrushes->length()==rows             || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_ForegroundColors==0        || mVerticalHeader_ForegroundColors->length()==rows              || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_CellFonts==0               || mVerticalHeader_CellFonts->length()==rows                     || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_CellTextFlags==0           || mVerticalHeader_CellTextFlags->length()==rows                 || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_CellMergeX==0              || mVerticalHeader_CellMergeX->length()==rows                    || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_CellMergeY==0              || mVerticalHeader_CellMergeY->length()==rows                    || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_CellMergeParentRow==0      || mVerticalHeader_CellMergeParentRow->length()==rows            || rows<=0 || columns<=0));
    TEST_STEP((mVerticalHeader_CellMergeParentColumn==0   || mVerticalHeader_CellMergeParentColumn->length()==rows         || rows<=0 || columns<=0));


    CHECK_COLUMN_COUNT(mData);
    CHECK_COLUMN_COUNT(mHorizontalHeader_Data);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_Data);

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

    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_BackgroundBrushes);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_ForegroundColors);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_CellFonts);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_CellTextFlags);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_CellMergeX);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_CellMergeY);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_CellMergeParentRow);
    CHECK_VERTICAL_COLUMN_COUNT(mVerticalHeader_CellMergeParentColumn);

    return success;
}

void TestFrame::addTestLabel(QString aTestName)
{
    int aCount=ui->testGridLayout->count()/3;
    int row=aCount%25;
    int column=aCount/25*3;

    QLabel *aLabel;

    //------

    aLabel=new QLabel(QString::number(aCount+1), this);

    ui->testGridLayout->addWidget(aLabel, row, column);

    //------

    aLabel=new QLabel(aTestName, this);

    aLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    ui->testGridLayout->addWidget(aLabel, row, column+1);

    //------

    aLabel=new QLabel("IN PROGRESS", this);

    QFont aFont=aLabel->font();
    aFont.setBold(true);
    aLabel->setFont(aFont);

    QPalette aPalette=aLabel->palette();
    aPalette.setColor(QPalette::WindowText, QColor(0, 0, 255));
    aLabel->setPalette(aPalette);

    ui->testGridLayout->addWidget(aLabel, row, column+2);
}

QLabel* TestFrame::getLabel(QString aTestName)
{
    for (int i=1; i<ui->testGridLayout->count(); i+=3)
    {
        if (((QLabel*)ui->testGridLayout->itemAt(i)->widget())->text()==aTestName)
        {
            return (QLabel*)ui->testGridLayout->itemAt(i+1)->widget();
        }
    }

    return 0;
}

void TestFrame::testCompleted(bool success, QString aTestName)
{
    if (success)
    {
        testSuccess(aTestName);
    }
    else
    {
        testFail(aTestName);
    }
}

void TestFrame::testSuccess(QString aTestName)
{
    QLabel *aLabel=getLabel(aTestName);

    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(0, 128, 0));

    aLabel->setText("SUCCESS");
    aLabel->setPalette(aPalette);

    emit testFinished();
}

void TestFrame::testFail(QString aTestName)
{
    QLabel *aLabel=getLabel(aTestName);

    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(128, 0, 0));

    aLabel->setText("FAIL");
    aLabel->setPalette(aPalette);

    qWarning()<<"FAIL";

    emit testFinished();
}

void TestFrame::testNotSupported(QString aTestName)
{
    QLabel *aLabel=getLabel(aTestName);

    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(0, 128, 128));

    aLabel->setText("NOT SUPPORTED");
    aLabel->setPalette(aPalette);

    emit testFinished();
}
