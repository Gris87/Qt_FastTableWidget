#ifndef TESTFRAME_H
#define TESTFRAME_H

#include <QWidget>
#include "ui_testframe.h"

#include <QSplitter>
#include <QLabel>

#include "../fasttable/customfasttablewidget.h"

#define TEST_STEP(condition) if (success)\
                             {\
                                 success = success && condition;\
                                 \
                                 if (!success)\
                                 {\
                                     qWarning()<<"Error at: "#condition;\
                                 }\
                             }

#define CHECK_COLUMN_COUNT(list) if (success && list)\
                                 {\
                                     for (int i=0; i<list->length(); ++i)\
                                     {\
                                         TEST_STEP(list->at(i).length()==columns)\
                                         \
                                         if (!success)\
                                         {\
                                             break;\
                                         }\
                                     }\
                                 }

#define CHECK_VERTICAL_COLUMN_COUNT(list) if (success && list)\
                                          {\
                                              for (int i=0; i<list->length(); ++i)\
                                              {\
                                                  TEST_STEP(list->at(i).length()==headerColumns)\
                                                  \
                                                  if (!success)\
                                                  {\
                                                      break;\
                                                  }\
                                              }\
                                          }

namespace Ui {
    class TestFrame;
}

class TestFrame : public QWidget
{
    Q_OBJECT

public:
    QList< QStringList >     *mData;
    QList< qint16 >          *mRowHeights;
    QList< qint16 >          *mColumnWidths;
    QList< int >             *mOffsetX;
    QList< int >             *mOffsetY;

    QList< QStringList >     *mHorizontalHeader_Data;
    QList< qint16 >          *mHorizontalHeader_RowHeights;
    QList< int >             *mHorizontalHeader_OffsetY;

    QList< QStringList >     *mVerticalHeader_Data;
    QList< qint16 >          *mVerticalHeader_ColumnWidths;
    QList< int >             *mVerticalHeader_OffsetX;

    QList< QList<bool> >     *mSelectedCells;
    QList< QPoint >          *mCurSelection;
    QList< int >             *mHorizontalHeader_SelectedColumns;
    QList< int >             *mVerticalHeader_SelectedRows;

    QList< QList<QBrush *> > *mBackgroundBrushes;
    QList< QList<QColor *> > *mForegroundColors;
    QList< QList<QFont *> >  *mCellFonts;
    QList< QList<int> >      *mCellTextFlags;
    QList< QList<quint16> >  *mCellMergeX;
    QList< QList<quint16> >  *mCellMergeY;
    QList< QList<int> >      *mCellMergeParentRow;
    QList< QList<int> >      *mCellMergeParentColumn;
    QList< QRect >           *mMerges;

    QList< QList<QBrush *> > *mHorizontalHeader_BackgroundBrushes;
    QList< QList<QColor *> > *mHorizontalHeader_ForegroundColors;
    QList< QList<QFont *> >  *mHorizontalHeader_CellFonts;
    QList< QList<int> >      *mHorizontalHeader_CellTextFlags;
    QList< QList<quint16> >  *mHorizontalHeader_CellMergeX;
    QList< QList<quint16> >  *mHorizontalHeader_CellMergeY;
    QList< QList<int> >      *mHorizontalHeader_CellMergeParentRow;
    QList< QList<int> >      *mHorizontalHeader_CellMergeParentColumn;
    QList< QRect >           *mHorizontalHeader_Merges;

    QList< QList<QBrush *> > *mVerticalHeader_BackgroundBrushes;
    QList< QList<QColor *> > *mVerticalHeader_ForegroundColors;
    QList< QList<QFont *> >  *mVerticalHeader_CellFonts;
    QList< QList<int> >      *mVerticalHeader_CellTextFlags;
    QList< QList<quint16> >  *mVerticalHeader_CellMergeX;
    QList< QList<quint16> >  *mVerticalHeader_CellMergeY;
    QList< QList<int> >      *mVerticalHeader_CellMergeParentRow;
    QList< QList<int> >      *mVerticalHeader_CellMergeParentColumn;
    QList< QRect >           *mVerticalHeader_Merges;

    //---------------------------------------------------------------------------

    Ui::TestFrame         *ui;
    CustomFastTableWidget *mFastTable;
    QSplitter             *mDividerSplitter;

    explicit TestFrame(CustomFastTableWidget* aFastTable, QWidget *parent = 0);
    ~TestFrame();

    void startTest();

    bool checkForSizes(int rows, int columns, int headerRows, int headerColumns);

    inline void addTestLabel(QString aTestName);
    QLabel* getLabel(QString aTestName);

    inline void testCompleted(bool success, QString aTestName);
    inline void testSuccess(QString aTestName);
    inline void testFail(QString aTestName);
    inline void testNotSupported(QString aTestName);

signals:
    void testFinished();
};

#endif // TESTFRAME_H
