#include "testdialog.h"
#include "ui_testdialog.h"

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mFastTableWidget=new FastTableTest(this);

    mDividerSplitter=new QSplitter(Qt::Vertical, this);

    ui->dividerLayout->removeWidget(ui->testsScrollArea);

    mDividerSplitter->addWidget(mFastTableWidget);
    mDividerSplitter->addWidget(ui->testsScrollArea);

    ui->dividerLayout->addWidget(mDividerSplitter);

    // --------------------------------------------------------

    mData             = mFastTableWidget->getData();
    mRowHeights       = mFastTableWidget->getRowHeights();
    mColumnWidths     = mFastTableWidget->getColumnWidths();
    mOffsetX          = mFastTableWidget->getOffsetX();
    mOffsetY          = mFastTableWidget->getOffsetY();
    mSelectedCells    = mFastTableWidget->getSelectedCells();
    mCurSelection     = mFastTableWidget->getCurSelection();
    mBackgroundColors = mFastTableWidget->getBackgroundColors();
    mForegroundColors = mFastTableWidget->getForegroundColors();
    mCellFonts        = mFastTableWidget->getCellFonts();
    mCellTextFlags    = mFastTableWidget->getCellTextFlags();

    // --------------------------------------------------------

    bool success;

    ui->progressBar->setMaximum(ui->testGridLayout->count() >> 1);
    ui->progressBar->setValue(0);

    // ----------------------------------------------------------------
    // TEST 1: Initial state
    // ----------------------------------------------------------------
    {
        success =            mCurSelection->length()==0;
        success = success && mFastTableWidget->getTotalHeight()==0;
        success = success && mFastTableWidget->getTotalWidth()==0;
        success = success && mFastTableWidget->getRowCount()==0;
        success = success && mFastTableWidget->getColumnCount()==0;
        success = success && !mFastTableWidget->getStartSelection();
        success = success && checkForSizes(0, 0);

        testCompleted(success, ui->initialResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 2: setRowCount(50)
    // ----------------------------------------------------------------
    {
        mFastTableWidget->setRowCount(50);

        success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==0;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 0);

        testCompleted(success, ui->setRow50ResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 3: setColumnCount(20)
    // ----------------------------------------------------------------
    {
        mFastTableWidget->setColumnCount(20);

        success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==mFastTableWidget->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setCol20ResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 4: setColumnCount(1)
    // ----------------------------------------------------------------
    {
        mFastTableWidget->setColumnCount(1);

        success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth();
        success = success && mOffsetX->at(0)==0;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 1);

        testCompleted(success, ui->setCol1ResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 5: setRowCount(2)
    // ----------------------------------------------------------------
    {
        mFastTableWidget->setRowCount(2);

        success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*2;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth();
        success = success && mOffsetX->at(0)==0;
        success = success && mOffsetY->at(1)==mFastTableWidget->getDefaultHeight();
        success = success && checkForSizes(2, 1);

        testCompleted(success, ui->setRow2ResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 6: setRowCount(50)
    // ----------------------------------------------------------------
    {
        mFastTableWidget->setRowCount(50);

        success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth();
        success = success && mOffsetX->at(0)==0;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 1);

        testCompleted(success, ui->setRow50ResLabel2);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 7: setColumnCount(20)
    // ----------------------------------------------------------------
    {
        mFastTableWidget->setColumnCount(20);

        success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==mFastTableWidget->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setCol20ResLabel2);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 8: setDefaultBackgroundColor
    // ----------------------------------------------------------------
    {
        QColor aDefaultBackgroundColor=mFastTableWidget->getDefaultBackgroundColor();
        QColor aNewDefaultBackgroundColor=QColor(255-aDefaultBackgroundColor.red(), 255-aDefaultBackgroundColor.green(), 255-aDefaultBackgroundColor.blue());

        mFastTableWidget->setDefaultBackgroundColor(aNewDefaultBackgroundColor);

        success =            mFastTableWidget->getDefaultBackgroundColor()==aNewDefaultBackgroundColor;

        mFastTableWidget->setDefaultBackgroundColor(aDefaultBackgroundColor);

        success = success && mFastTableWidget->getDefaultBackgroundColor()==aDefaultBackgroundColor;

        testCompleted(success, ui->setDefBackgroundResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 9: setDefaultForegroundColor
    // ----------------------------------------------------------------
    {
        QColor aDefaultForegroundColor=mFastTableWidget->getDefaultForegroundColor();
        QColor aNewDefaultForegroundColor=QColor(255-aDefaultForegroundColor.red(), 255-aDefaultForegroundColor.green(), 255-aDefaultForegroundColor.blue());

        mFastTableWidget->setDefaultForegroundColor(aNewDefaultForegroundColor);

        success =            mFastTableWidget->getDefaultForegroundColor()==aNewDefaultForegroundColor;

        mFastTableWidget->setDefaultForegroundColor(aDefaultForegroundColor);

        success = success && mFastTableWidget->getDefaultForegroundColor()==aDefaultForegroundColor;

        testCompleted(success, ui->setDefForegroundResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 10: setGridColor
    // ----------------------------------------------------------------
    {
        QColor aGridColor=mFastTableWidget->getGridColor();
        QColor aNewGridColor=QColor(255-aGridColor.red(), 255-aGridColor.green(), 255-aGridColor.blue());

        mFastTableWidget->setGridColor(aNewGridColor);

        success =            mFastTableWidget->getGridColor()==aNewGridColor;

        mFastTableWidget->setGridColor(aGridColor);

        success = success && mFastTableWidget->getGridColor()==aGridColor;

        testCompleted(success, ui->setGridColorResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 11: setSelectionColor
    // ----------------------------------------------------------------
    {
        QColor aSelectionColor=mFastTableWidget->getSelectionColor();
        QColor aNewSelectionColor=QColor(255-aSelectionColor.red(), 255-aSelectionColor.green(), 255-aSelectionColor.blue());

        mFastTableWidget->setSelectionColor(aNewSelectionColor);

        success =            mFastTableWidget->getSelectionColor()==aNewSelectionColor;

        mFastTableWidget->setSelectionColor(aSelectionColor);

        success = success && mFastTableWidget->getSelectionColor()==aSelectionColor;

        testCompleted(success, ui->setSelectionColorResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 12: setDefaultHeight
    // ----------------------------------------------------------------
    {
        quint16 aDefaultHeight=mFastTableWidget->getDefaultHeight();
        quint16 aNewDefaultHeight=10;

        mFastTableWidget->setDefaultHeight(aNewDefaultHeight);
        mFastTableWidget->setRowCount(51);

        success =            mFastTableWidget->getDefaultHeight()==aNewDefaultHeight;
        success = success && mFastTableWidget->getTotalHeight()==aDefaultHeight*50+aNewDefaultHeight;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==mFastTableWidget->getDefaultWidth()*19;
        success = success && mOffsetY->at(50)==mFastTableWidget->getDefaultHeight()*50;
        success = success && checkForSizes(51, 20);

        mFastTableWidget->setDefaultHeight(aDefaultHeight);
        mFastTableWidget->setRowCount(50);

        success =            mFastTableWidget->getDefaultHeight()==aDefaultHeight;
        success = success && mFastTableWidget->getTotalHeight()==aDefaultHeight*50;
        success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth()*20;
        success = success && mOffsetX->at(19)==mFastTableWidget->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setDefHeightResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 13: setDefaultWidth
    // ----------------------------------------------------------------
    {
        quint16 aDefaultWidth=mFastTableWidget->getDefaultWidth();
        quint16 aNewDefaultWidth=10;

        mFastTableWidget->setDefaultWidth(aNewDefaultWidth);
        mFastTableWidget->setColumnCount(21);

        success =            mFastTableWidget->getDefaultWidth()==aNewDefaultWidth;
        success = success && mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==aDefaultWidth*20+aNewDefaultWidth;
        success = success && mOffsetX->at(19)==mFastTableWidget->getDefaultWidth()*19;
        success = success && mOffsetY->at(50)==mFastTableWidget->getDefaultHeight()*50;
        success = success && checkForSizes(50, 21);

        mFastTableWidget->setDefaultWidth(aDefaultWidth);
        mFastTableWidget->setColumnCount(20);

        success =            mFastTableWidget->getDefaultWidth()==aDefaultWidth;
        success = success && mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
        success = success && mFastTableWidget->getTotalWidth()==aDefaultWidth*20;
        success = success && mOffsetX->at(19)==mFastTableWidget->getDefaultWidth()*19;
        success = success && mOffsetY->at(49)==mFastTableWidget->getDefaultHeight()*49;
        success = success && checkForSizes(50, 20);

        testCompleted(success, ui->setDefWidthResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 14: totalHeight
    // ----------------------------------------------------------------
    {
        int     aTotalHeight=mFastTableWidget->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(49);

        mFastTableWidget->setRowHeight(49, aRowHeight+100);
        mFastTableWidget->setRowCount(51);

        success =            mFastTableWidget->getTotalHeight()==aTotalHeight+mFastTableWidget->getDefaultHeight()+100;
        success = success && mOffsetY->at(50)==aTotalHeight+100;

        mFastTableWidget->setRowHeight(49, aRowHeight);
        mFastTableWidget->setRowCount(50);

        success = success && mFastTableWidget->getTotalHeight()==aTotalHeight;

        testCompleted(success, ui->totalHeightResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 15: totalWidth
    // ----------------------------------------------------------------
    {
        int     aTotalWidth=mFastTableWidget->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(19);

        mFastTableWidget->setColumnWidth(19, aColumnWidth+100);
        mFastTableWidget->setColumnCount(21);

        success =            mFastTableWidget->getTotalWidth()==aTotalWidth+mFastTableWidget->getDefaultWidth()+100;
        success = success && mOffsetX->at(20)==aTotalWidth+100;

        mFastTableWidget->setColumnWidth(19, aColumnWidth);
        mFastTableWidget->setColumnCount(20);

        success = success && mFastTableWidget->getTotalWidth()==aTotalWidth;

        testCompleted(success, ui->totalWidthResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 16: setText
    // ----------------------------------------------------------------
    {
        for (int i=0; i<mFastTableWidget->rowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->columnCount(); ++j)
            {
                mFastTableWidget->setText(i, j, QString::number(i*mFastTableWidget->columnCount()+j));
            }
        }

        success=true;

        for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
            {
                if (
                    mData->at(i).at(j)!=QString::number(i*mFastTableWidget->getColumnCount()+j)
                    ||
                    mFastTableWidget->text(i, j)!=QString::number(i*mFastTableWidget->getColumnCount()+j)
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
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 17: setBackgroundColor
    // ----------------------------------------------------------------
    {
        QColor aNewBackgroundColor(1, 2, 3);

        for (int i=0; i<mFastTableWidget->rowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->columnCount(); ++j)
            {
                mFastTableWidget->setBackgroundColor(i, j, aNewBackgroundColor);
            }
        }

        success=true;

        for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
            {
                if (
                    mBackgroundColors->at(i).at(j)==0
                    ||
                    *mBackgroundColors->at(i).at(j)!=aNewBackgroundColor
                    ||
                    mFastTableWidget->backgroundColor(i, j)!=aNewBackgroundColor
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

        mFastTableWidget->resetBackgroundColor(10, 5);

        success = success && mBackgroundColors->at(10).at(5)==0;

        mFastTableWidget->resetBackgroundColors();

        if (success)
        {
            for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
            {
                for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
                {
                    if (mBackgroundColors->at(i).at(j)!=0)
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
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 18: setForegroundColor
    // ----------------------------------------------------------------
    {
        QColor aNewForegroundColor(3, 2, 1);

        for (int i=0; i<mFastTableWidget->rowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->columnCount(); ++j)
            {
                mFastTableWidget->setForegroundColor(i, j, aNewForegroundColor);
            }
        }

        success=true;

        for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
            {
                if (
                    mForegroundColors->at(i).at(j)==0
                    ||
                    *mForegroundColors->at(i).at(j)!=aNewForegroundColor
                    ||
                    mFastTableWidget->foregroundColor(i, j)!=aNewForegroundColor
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

        mFastTableWidget->resetForegroundColor(10, 5);

        success = success && mForegroundColors->at(10).at(5)==0;

        mFastTableWidget->resetForegroundColors();

        if (success)
        {
            for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
            {
                for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
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
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 19: setCellFont
    // ----------------------------------------------------------------
    {
        QFont aNewCellFont("Arial", 12, 1, true);

        for (int i=0; i<mFastTableWidget->rowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->columnCount(); ++j)
            {
                mFastTableWidget->setCellFont(i, j, aNewCellFont);
            }
        }

        success=true;

        for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
            {
                if (
                    mCellFonts->at(i).at(j)==0
                    ||
                    *mCellFonts->at(i).at(j)!=aNewCellFont
                    ||
                    mFastTableWidget->cellFont(i, j)!=aNewCellFont
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

        mFastTableWidget->resetFont(10, 5);

        success = success && mCellFonts->at(10).at(5)==0;

        mFastTableWidget->resetFonts();

        if (success)
        {
            for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
            {
                for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
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
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 20: setTextFlags
    // ----------------------------------------------------------------
    {
        int aNewFlag=Qt::AlignRight | Qt::AlignTop;

        for (int i=0; i<mFastTableWidget->rowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->columnCount(); ++j)
            {
                mFastTableWidget->setCellTextFlags(i, j, aNewFlag);
            }
        }

        success=true;

        for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
            {
                if (
                    mCellTextFlags->at(i).at(j)!=aNewFlag
                    ||
                    mFastTableWidget->cellTextFlags(i, j)!=aNewFlag
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

        mFastTableWidget->resetTextFlag(10, 5);

        success = success && mFastTableWidget->cellTextFlags(10, 5)==(Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap);

        mFastTableWidget->resetTextFlags();

        if (success)
        {
            for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
            {
                for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
                {
                    if (mFastTableWidget->cellTextFlags(i, j)!=(Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap))
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
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 21: setCellSelected
    // ----------------------------------------------------------------
    {
        mFastTableWidget->selectAll();

        success=true;

        for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
        {
            for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
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

        mFastTableWidget->setCellSelected(10, 5, false);

        success = success && !mSelectedCells->at(10).at(5);

        mFastTableWidget->unselectAll();

        if (success)
        {
            for (int i=0; i<mFastTableWidget->getRowCount(); ++i)
            {
                for (int j=0; j<mFastTableWidget->getColumnCount(); ++j)
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
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 22: setRowHeight
    // ----------------------------------------------------------------
    {
        int     aTotalHeight=mFastTableWidget->getTotalHeight();
        quint16 aRowHeight=mRowHeights->at(30);

        mFastTableWidget->setRowHeight(30, aRowHeight+100);

        success =            mFastTableWidget->getTotalHeight()==aTotalHeight+100;

        mFastTableWidget->setRowHeight(30, aRowHeight);

        success = success && mFastTableWidget->getTotalHeight()==aTotalHeight;

        testCompleted(success, ui->setRowHeightResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------
    // TEST 23: setColumnWidth
    // ----------------------------------------------------------------
    {
        int     aTotalWidth=mFastTableWidget->getTotalWidth();
        quint16 aColumnWidth=mColumnWidths->at(10);

        mFastTableWidget->setColumnWidth(10, aColumnWidth+100);

        success =            mFastTableWidget->getTotalWidth()==aTotalWidth+100;

        mFastTableWidget->setColumnWidth(10, aColumnWidth);

        success = success && mFastTableWidget->getTotalWidth()==aTotalWidth;

        testCompleted(success, ui->setColumnWidthResLabel);
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    // ----------------------------------------------------------------

    ui->progressBar->setValue(0);
}

TestDialog::~TestDialog()
{
    delete ui;
}

bool TestDialog::checkForSizes(int rows, int columns)
{
    bool success;

    success =            mFastTableWidget->getRowCount()==rows;
    success = success && mFastTableWidget->getColumnCount()==columns;
    success = success && mData->length()==rows;
    success = success && mRowHeights->length()==rows;
    success = success && mColumnWidths->length()==columns;
    success = success && mOffsetX->length()==columns;
    success = success && mOffsetY->length()==rows;
    success = success && mSelectedCells->length()==rows;
    success = success && mBackgroundColors->length()==rows;
    success = success && mForegroundColors->length()==rows;
    success = success && mCellFonts->length()==rows;
    success = success && mCellTextFlags->length()==rows;

    if (success)
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

    if (success)
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

    if (success)
    {
        for (int i=0; i<mBackgroundColors->length(); ++i)
        {
            if (mBackgroundColors->at(i).length()!=columns)
            {
                success=false;
                break;
            }
        }
    }

    if (success)
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

    if (success)
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

    if (success)
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

    return success;
}

void TestDialog::testCompleted(bool success, QLabel *aLabel)
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

void TestDialog::testSuccess(QLabel *aLabel)
{
    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(0, 128, 0));

    aLabel->setText("SUCCESS");
    aLabel->setPalette(aPalette);
}

void TestDialog::testFail(QLabel *aLabel)
{
    QPalette aPalette;

    aPalette.setColor(QPalette::WindowText, QColor(128, 0, 0));

    aLabel->setText("FAIL");
    aLabel->setPalette(aPalette);
}
