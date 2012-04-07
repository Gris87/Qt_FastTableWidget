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

    mData                  = (((PublicCustomFastTable*)mFastTable)->getData());
    mRowHeights            = (((PublicCustomFastTable*)mFastTable)->getRowHeights());
    mColumnWidths          = (((PublicCustomFastTable*)mFastTable)->getColumnWidths());
    mOffsetX               = (((PublicCustomFastTable*)mFastTable)->getOffsetX());
    mOffsetY               = (((PublicCustomFastTable*)mFastTable)->getOffsetY());
    mSelectedCells         = (((PublicCustomFastTable*)mFastTable)->getSelectedCells());
    mCurSelection          = (((PublicCustomFastTable*)mFastTable)->getCurSelection());

    if (mFastTable->inherits("FastTableWidget"))
    {
        mBackgroundBrushes     = (((PublicFastTable*)mFastTable)->getBackgroundBrushes());
        mForegroundColors      = (((PublicFastTable*)mFastTable)->getForegroundColors());
        mCellFonts             = (((PublicFastTable*)mFastTable)->getCellFonts());
        mCellTextFlags         = (((PublicFastTable*)mFastTable)->getCellTextFlags());
        mCellMergeX            = (((PublicFastTable*)mFastTable)->getCellMergeX());
        mCellMergeY            = (((PublicFastTable*)mFastTable)->getCellMergeY());
        mCellMergeParentRow    = (((PublicFastTable*)mFastTable)->getCellMergeParentRow());
        mCellMergeParentColumn = (((PublicFastTable*)mFastTable)->getCellMergeParentColumn());
    }
    else
    {
        mBackgroundBrushes     = 0;
        mForegroundColors      = 0;
        mCellFonts             = 0;
        mCellTextFlags         = 0;
        mCellMergeX            = 0;
        mCellMergeY            = 0;
        mCellMergeParentRow    = 0;
        mCellMergeParentColumn = 0;
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
        success =            mCurSelection->length()==0;
        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==0;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==0;
        success = success && ((PublicFastTable*)mFastTable)->getRowCount()==0;
        success = success && ((PublicFastTable*)mFastTable)->getColumnCount()==0;
        success = success && checkForSizes(0, 0);

        testCompleted(success, ui->initialResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 2: setRowCount(50)";
    // ----------------------------------------------------------------
    {
        mFastTable->setRowCount(50);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==0;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 0);

        testCompleted(success, ui->setRow50ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 3: setColumnCount(20)";
    // ----------------------------------------------------------------
    {
        mFastTable->setColumnCount(20);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==((PublicFastTable*)mFastTable)->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==((PublicFastTable*)mFastTable)->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setCol20ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 4: setColumnCount(1)";
    // ----------------------------------------------------------------
    {
        mFastTable->setColumnCount(1);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==((PublicFastTable*)mFastTable)->getDefaultWidth();
        success = success && mOffsetX->at(0)==0;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 1);

        testCompleted(success, ui->setCol1ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 5: setRowCount(2)";
    // ----------------------------------------------------------------
    {
        mFastTable->setRowCount(2);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*2;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==((PublicFastTable*)mFastTable)->getDefaultWidth();
        success = success && mOffsetX->at(0)==0;
        success = success && mOffsetY->at(1)==((PublicFastTable*)mFastTable)->getDefaultHeight();
        success = success && checkForSizes(2, 1);

        testCompleted(success, ui->setRow2ResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 6: clearTable()";
    // ----------------------------------------------------------------
    {
        mFastTable->clearTable();

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==0;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==0;
        success = success && checkForSizes(0, 0);

        testCompleted(success, ui->clearTableResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 7: setRowCount(50)";
    // ----------------------------------------------------------------
    {
        mFastTable->setRowCount(50);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==0;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 0);

        testCompleted(success, ui->setRow50ResLabel2);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 8: setColumnCount(20)";
    // ----------------------------------------------------------------
    {
        mFastTable->setColumnCount(20);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==((PublicFastTable*)mFastTable)->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==((PublicFastTable*)mFastTable)->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setCol20ResLabel2);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 9: setDefaultBackgroundBrush";
    // ----------------------------------------------------------------
    {
        QBrush aDefaultBackgroundBrush=((PublicFastTable*)mFastTable)->getDefaultBackgroundBrush();
        QBrush aNewDefaultBackgroundBrush=QBrush(QColor(1, 2, 3));

        mFastTable->setDefaultBackgroundBrush(aNewDefaultBackgroundBrush);

        success =            ((PublicFastTable*)mFastTable)->getDefaultBackgroundBrush()==aNewDefaultBackgroundBrush;

        mFastTable->setDefaultBackgroundBrush(aDefaultBackgroundBrush);

        success = success && ((PublicFastTable*)mFastTable)->getDefaultBackgroundBrush()==aDefaultBackgroundBrush;

        testCompleted(success, ui->setDefBackgroundResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 10: setDefaultForegroundColor";
    // ----------------------------------------------------------------
    {
        QColor aDefaultForegroundColor=((PublicFastTable*)mFastTable)->getDefaultForegroundColor();
        QColor aNewDefaultForegroundColor=QColor(1, 2, 3);

        mFastTable->setDefaultForegroundColor(aNewDefaultForegroundColor);

        success =            ((PublicFastTable*)mFastTable)->getDefaultForegroundColor()==aNewDefaultForegroundColor;

        mFastTable->setDefaultForegroundColor(aDefaultForegroundColor);

        success = success && ((PublicFastTable*)mFastTable)->getDefaultForegroundColor()==aDefaultForegroundColor;

        testCompleted(success, ui->setDefForegroundResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 11: setGridColor";
    // ----------------------------------------------------------------
    {
        QColor aGridColor=((PublicFastTable*)mFastTable)->getGridColor();
        QColor aNewGridColor=QColor(1, 2, 3);

        mFastTable->setGridColor(aNewGridColor);

        success =            ((PublicFastTable*)mFastTable)->getGridColor()==aNewGridColor;

        mFastTable->setGridColor(aGridColor);

        success = success && ((PublicFastTable*)mFastTable)->getGridColor()==aGridColor;

        testCompleted(success, ui->setGridColorResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 12: setSelectionBrush";
    // ----------------------------------------------------------------
    {
        QBrush aSelectionBrush=((PublicFastTable*)mFastTable)->getSelectionBrush();
        QBrush aNewSelectionBrush=QBrush(QColor(1, 2, 3));

        mFastTable->setSelectionBrush(aNewSelectionBrush);

        success =            ((PublicFastTable*)mFastTable)->getSelectionBrush()==aNewSelectionBrush;

        mFastTable->setSelectionBrush(aSelectionBrush);

        success = success && ((PublicFastTable*)mFastTable)->getSelectionBrush()==aSelectionBrush;

        testCompleted(success, ui->setSelectionColorResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 13: setDefaultHeight";
    // ----------------------------------------------------------------
    {
        quint16 aDefaultHeight=((PublicFastTable*)mFastTable)->getDefaultHeight();
        quint16 aNewDefaultHeight=10;

        mFastTable->setDefaultHeight(aNewDefaultHeight);
        mFastTable->setRowCount(51);

        success =            ((PublicFastTable*)mFastTable)->getDefaultHeight()==aNewDefaultHeight;
        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==aDefaultHeight*50+aNewDefaultHeight;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==((PublicFastTable*)mFastTable)->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==((PublicFastTable*)mFastTable)->getDefaultWidth()*19;
        success = success && mOffsetY->at(50)==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && checkForSizes(51, 20);

        mFastTable->setDefaultHeight(aDefaultHeight);
        mFastTable->setRowCount(50);

        success =            ((PublicFastTable*)mFastTable)->getDefaultHeight()==aDefaultHeight;
        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==aDefaultHeight*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==((PublicFastTable*)mFastTable)->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==((PublicFastTable*)mFastTable)->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setDefHeightResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 14: setDefaultWidth";
    // ----------------------------------------------------------------
    {
        quint16 aDefaultWidth=((PublicFastTable*)mFastTable)->getDefaultWidth();
        quint16 aNewDefaultWidth=10;

        mFastTable->setDefaultWidth(aNewDefaultWidth);
        mFastTable->setColumnCount(21);

        success =            ((PublicFastTable*)mFastTable)->getDefaultWidth()==aNewDefaultWidth;
        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==aDefaultWidth*20+aNewDefaultWidth;
        success = success && mOffsetX->at(19)==((PublicFastTable*)mFastTable)->getDefaultWidth()*19;
        success = success && mOffsetY->at(50)==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && checkForSizes(50, 21);

        mFastTable->setDefaultWidth(aDefaultWidth);
        mFastTable->setColumnCount(20);

        success =            ((PublicFastTable*)mFastTable)->getDefaultWidth()==aDefaultWidth;
        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==((PublicFastTable*)mFastTable)->getDefaultHeight()*50;
        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==aDefaultWidth*20;
        success = success && mOffsetX->at(19)==((PublicFastTable*)mFastTable)->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==((PublicFastTable*)mFastTable)->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setDefWidthResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 15: setRowHeight";
    // ----------------------------------------------------------------
    {
        int     aTotalHeight=((PublicFastTable*)mFastTable)->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(30);

        mFastTable->setRowHeight(30, aRowHeight+100);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==aTotalHeight+100;

        mFastTable->setRowHeight(30, aRowHeight);

        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==aTotalHeight;

        testCompleted(success, ui->setRowHeightResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 16: setColumnWidth";
    // ----------------------------------------------------------------
    {
        int     aTotalWidth=((PublicFastTable*)mFastTable)->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(10);

        mFastTable->setColumnWidth(10, aColumnWidth+100);

        success =            ((PublicFastTable*)mFastTable)->getTotalWidth()==aTotalWidth+100;

        mFastTable->setColumnWidth(10, aColumnWidth);

        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==aTotalWidth;

        testCompleted(success, ui->setColumnWidthResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 17: totalHeight";
    // ----------------------------------------------------------------
    {
        int     aTotalHeight=((PublicFastTable*)mFastTable)->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(49);

        mFastTable->setRowHeight(49, aRowHeight+100);
        mFastTable->setRowCount(51);

        success =            ((PublicFastTable*)mFastTable)->getTotalHeight()==aTotalHeight+((PublicFastTable*)mFastTable)->getDefaultHeight()+100;
        success = success && mOffsetY->at(50)==aTotalHeight+100;

        mFastTable->setRowHeight(49, aRowHeight);
        mFastTable->setRowCount(50);

        success = success && ((PublicFastTable*)mFastTable)->getTotalHeight()==aTotalHeight;

        testCompleted(success, ui->totalHeightResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 18: totalWidth";
    // ----------------------------------------------------------------
    {
        int     aTotalWidth=((PublicFastTable*)mFastTable)->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(19);

        mFastTable->setColumnWidth(19, aColumnWidth+100);
        mFastTable->setColumnCount(21);

        success =            ((PublicFastTable*)mFastTable)->getTotalWidth()==aTotalWidth+((PublicFastTable*)mFastTable)->getDefaultWidth()+100;
        success = success && mOffsetX->at(20)==aTotalWidth+100;

        mFastTable->setColumnWidth(19, aColumnWidth);
        mFastTable->setColumnCount(20);

        success = success && ((PublicFastTable*)mFastTable)->getTotalWidth()==aTotalWidth;

        testCompleted(success, ui->totalWidthResLabel);
    }
    // ----------------------------------------------------------------
    qDebug()<<"TEST 19: setText";
    // ----------------------------------------------------------------
    {
        for (int i=0; i<mFastTable->rowCount(); ++i)
        {
            for (int j=0; j<mFastTable->columnCount(); ++j)
            {
                mFastTable->setText(i, j, QString::number(i*mFastTable->columnCount()+j));
            }
        }

        success=true;

        for (int i=0; i<((PublicFastTable*)mFastTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)mFastTable)->getColumnCount(); ++j)
            {
                if (
                    mData->at(i).at(j)!=QString::number(i*((PublicFastTable*)mFastTable)->getColumnCount()+j)
                    ||
                    mFastTable->text(i, j)!=QString::number(i*((PublicFastTable*)mFastTable)->getColumnCount()+j)
                   )
                {
                    success=false;
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
        mFastTable->selectAll();

        success=true;

        for (int i=0; i<((PublicFastTable*)mFastTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)mFastTable)->getColumnCount(); ++j)
            {
                if (!mSelectedCells->at(i).at(j))
                {
                    success=false;
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        mFastTable->setCellSelected(10, 5, false);

        success = success && !mSelectedCells->at(10).at(5);

        mFastTable->unselectAll();

        if (success)
        {
            for (int i=0; i<((PublicFastTable*)mFastTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicFastTable*)mFastTable)->getColumnCount(); ++j)
                {
                    if (mSelectedCells->at(i).at(j))
                    {
                        success=false;
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
        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QBrush aNewBackgroundBrush(QColor(1, 2, 3));

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setBackgroundBrush(i, j, aNewBackgroundBrush);
            }
        }

        success=true;

        for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
            {
                if (
                    mBackgroundBrushes->at(i).at(j)==0
                    ||
                    *mBackgroundBrushes->at(i).at(j)!=aNewBackgroundBrush
                    ||
                    aTable->backgroundBrush(i, j)!=aNewBackgroundBrush
                   )
                {
                    success=false;
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetBackgroundBrush(10, 5);

        success = success && mBackgroundBrushes->at(10).at(5)==0;

        aTable->resetBackgroundBrushes();

        if (success)
        {
            for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
                {
                    if (mBackgroundBrushes->at(i).at(j)!=0)
                    {
                        success=false;
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
        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QColor aNewForegroundColor(3, 2, 1);

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setForegroundColor(i, j, aNewForegroundColor);
            }
        }

        success=true;

        for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
            {
                if (
                    mForegroundColors->at(i).at(j)==0
                    ||
                    *mForegroundColors->at(i).at(j)!=aNewForegroundColor
                    ||
                    aTable->foregroundColor(i, j)!=aNewForegroundColor
                   )
                {
                    success=false;
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetForegroundColor(10, 5);

        success = success && mForegroundColors->at(10).at(5)==0;

        aTable->resetForegroundColors();

        if (success)
        {
            for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
                {
                    if (mForegroundColors->at(i).at(j)!=0)
                    {
                        success=false;
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
        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        QFont aNewCellFont("Arial", 12, 1, true);

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setCellFont(i, j, aNewCellFont);
            }
        }

        success=true;

        for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
            {
                if (
                    mCellFonts->at(i).at(j)==0
                    ||
                    *mCellFonts->at(i).at(j)!=aNewCellFont
                    ||
                    aTable->cellFont(i, j)!=aNewCellFont
                   )
                {
                    success=false;
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetFont(10, 5);

        success = success && mCellFonts->at(10).at(5)==0;

        aTable->resetFonts();

        if (success)
        {
            for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
                {
                    if (mCellFonts->at(i).at(j)!=0)
                    {
                        success=false;
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
        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        int aNewFlag=Qt::AlignRight | Qt::AlignTop;

        for (int i=0; i<aTable->rowCount(); ++i)
        {
            for (int j=0; j<aTable->columnCount(); ++j)
            {
                aTable->setCellTextFlags(i, j, aNewFlag);
            }
        }

        success=true;

        for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
            {
                if (
                    mCellTextFlags->at(i).at(j)!=aNewFlag
                    ||
                    aTable->cellTextFlags(i, j)!=aNewFlag
                   )
                {
                    success=false;
                    break;
                }
            }

            if (!success)
            {
                break;
            }
        }

        aTable->resetTextFlag(10, 5);

        success = success && aTable->cellTextFlags(10, 5)==(Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap);

        aTable->resetTextFlags();

        if (success)
        {
            for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
            {
                for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
                {
                    if (aTable->cellTextFlags(i, j)!=(Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap))
                    {
                        success=false;
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
        FastTableWidget* aTable=(FastTableWidget*)mFastTable;

        success=true;

        aTable->setSpan(1, 2, 2, 3);

        for (int i=1; i<=2; i++)
        {
            for (int j=2; j<=4; j++)
            {
                success = success && mCellMergeParentRow->at(i).at(j)==1;
                success = success && mCellMergeParentColumn->at(i).at(j)==2;
                success = success && aTable->spanParent(i, j)==QPoint(2, 1);
            }
        }

        success = success && mCellMergeX->at(1).at(2)==3;
        success = success && mCellMergeY->at(1).at(2)==2;

        aTable->setSpan(0, 3, 2, 1);

        for (int i=1; i<=2; i++)
        {
            for (int j=2; j<=4; j++)
            {
                if (i!=1 && j!=3)
                {
                    success = success && mCellMergeParentRow->at(i).at(j)==-1;
                    success = success && mCellMergeParentColumn->at(i).at(j)==-1;
                    success = success && aTable->spanParent(i, j)==QPoint(-1, -1);
                }
            }
        }

        success = success && mCellMergeX->at(1).at(2)==1;
        success = success && mCellMergeY->at(1).at(2)==1;

        for (int i=0; i<=1; i++)
        {
            success = success && mCellMergeParentRow->at(i).at(3)==0;
            success = success && mCellMergeParentColumn->at(i).at(3)==3;
            success = success && aTable->spanParent(i, 3)==QPoint(3, 0);
        }

        success = success && mCellMergeX->at(0).at(3)==1;
        success = success && mCellMergeY->at(0).at(3)==2;

        aTable->clearSpans();

        for (int i=0; i<((PublicFastTable*)aTable)->getRowCount(); ++i)
        {
            for (int j=0; j<((PublicFastTable*)aTable)->getColumnCount(); ++j)
            {
                if (
                    aTable->rowSpan(i, j)!=1
                    ||
                    aTable->columnSpan(i, j)!=1
                    ||
                    aTable->spanParent(i, j)!=QPoint(-1, -1)
                    ||
                    mCellMergeX->at(i).at(j)!=1
                    ||
                    mCellMergeY->at(i).at(j)!=1
                    ||
                    mCellMergeParentRow->at(i).at(j)!=-1
                    ||
                    mCellMergeParentColumn->at(i).at(j)!=-1
                   )
                {
                    success=false;
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

    success = success && ((PublicFastTable*)mFastTable)->getRowCount()==rows;
    success = success && ((PublicFastTable*)mFastTable)->getColumnCount()==columns;
    success = success && (mData==0                  || mData->length()==rows);
    success = success && (mRowHeights==0            || mRowHeights->length()==rows);
    success = success && (mColumnWidths==0          || mColumnWidths->length()==columns);
    success = success && (mOffsetX==0               || mOffsetX->length()==columns);
    success = success && (mOffsetY==0               || mOffsetY->length()==rows);
    success = success && (mSelectedCells==0         || mSelectedCells->length()==rows);
    success = success && (mBackgroundBrushes==0     || mBackgroundBrushes->length()==rows);
    success = success && (mForegroundColors==0      || mForegroundColors->length()==rows);
    success = success && (mCellFonts==0             || mCellFonts->length()==rows);
    success = success && (mCellTextFlags==0         || mCellTextFlags->length()==rows);
    success = success && (mCellMergeX==0            || mCellMergeX->length()==rows);
    success = success && (mCellMergeY==0            || mCellMergeY->length()==rows);
    success = success && (mCellMergeParentRow==0    || mCellMergeParentRow->length()==rows);
    success = success && (mCellMergeParentColumn==0 || mCellMergeParentColumn->length()==rows);

    if (success && mData)
    {
        for (int i=0; i<mData->length(); ++i)
        {
            if (mData->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mSelectedCells)
    {
        for (int i=0; i<mSelectedCells->length(); ++i)
        {
            if (mSelectedCells->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mBackgroundBrushes)
    {
        for (int i=0; i<mBackgroundBrushes->length(); ++i)
        {
            if (mBackgroundBrushes->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mForegroundColors)
    {
        for (int i=0; i<mForegroundColors->length(); ++i)
        {
            if (mForegroundColors->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mCellFonts)
    {
        for (int i=0; i<mCellFonts->length(); ++i)
        {
            if (mCellFonts->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mCellTextFlags)
    {
        for (int i=0; i<mCellTextFlags->length(); ++i)
        {
            if (mCellTextFlags->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mCellMergeX)
    {
        for (int i=0; i<mCellMergeX->length(); ++i)
        {
            if (mCellMergeX->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mCellMergeY)
    {
        for (int i=0; i<mCellMergeY->length(); ++i)
        {
            if (mCellMergeY->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mCellMergeParentRow)
    {
        for (int i=0; i<mCellMergeParentRow->length(); ++i)
        {
            if (mCellMergeParentRow->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success && mCellMergeParentColumn)
    {
        for (int i=0; i<mCellMergeParentColumn->length(); ++i)
        {
            if (mCellMergeParentColumn->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

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
