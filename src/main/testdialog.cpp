#include "testdialog.h"
#include "ui_testdialog.h"

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mFastTableWidget=new FastTableTest(this);
    ui->fastTableLayout->addWidget(mFastTableWidget);

    mData             = mFastTableWidget->getData();
    mRowHeights       = mFastTableWidget->getRowHeights();
    mColumnWidths     = mFastTableWidget->getColumnWidths();
    mSelectedCells    = mFastTableWidget->getSelectedCells();
    mCurSelection     = mFastTableWidget->getCurSelection();
    mBackgroundColors = mFastTableWidget->getBackgroundColors();
    mForegroundColors = mFastTableWidget->getForegroundColors();
    mCellFonts        = mFastTableWidget->getCellFonts();

    bool success;

    ui->progressBar->setMaximum(ui->testGridLayout->count() >> 1);
    ui->progressBar->setValue(0);

    // ----------------------------------------------------------------
    // TEST 1: Initial state
    // ----------------------------------------------------------------

    success =            mCurSelection->length()==0;
    success = success && mFastTableWidget->getTotalHeight()==0;
    success = success && mFastTableWidget->getTotalWidth()==0;

    testCompleted(success, ui->initialResLabel);
    ui->progressBar->setValue(ui->progressBar->value()+1);

    // ----------------------------------------------------------------
    // TEST 2: setRowCount(50)
    // ----------------------------------------------------------------

    mFastTableWidget->setRowCount(50);

    success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
    success = success && mFastTableWidget->getTotalWidth()==0;
    success = success && checkForSizes(50, 0);

    testCompleted(success, ui->setRow50ResLabel);
    ui->progressBar->setValue(ui->progressBar->value()+1);

    // ----------------------------------------------------------------
    // TEST 3: setColumnCount(20)
    // ----------------------------------------------------------------

    mFastTableWidget->setColumnCount(20);

    success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
    success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth()*20;
    success = success && checkForSizes(50, 20);

    testCompleted(success, ui->setCol20ResLabel);
    ui->progressBar->setValue(ui->progressBar->value()+1);

    // ----------------------------------------------------------------
    // TEST 4: setColumnCount(1)
    // ----------------------------------------------------------------

    mFastTableWidget->setColumnCount(1);

    success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*50;
    success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth();
    success = success && checkForSizes(50, 1);

    testCompleted(success, ui->setCol1ResLabel);
    ui->progressBar->setValue(ui->progressBar->value()+1);

    // ----------------------------------------------------------------
    // TEST 5: setRowCount(2)
    // ----------------------------------------------------------------

    mFastTableWidget->setRowCount(2);

    success =            mFastTableWidget->getTotalHeight()==mFastTableWidget->getDefaultHeight()*2;
    success = success && mFastTableWidget->getTotalWidth()==mFastTableWidget->getDefaultWidth();
    success = success && checkForSizes(2, 1);

    testCompleted(success, ui->setRow2ResLabel);
    ui->progressBar->setValue(ui->progressBar->value()+1);

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
    success = success && mSelectedCells->length()==rows;
    success = success && mBackgroundColors->length()==rows;
    success = success && mForegroundColors->length()==rows;
    success = success && mCellFonts->length()==rows;

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
