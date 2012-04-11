#ifndef TESTFRAME_H
#define TESTFRAME_H

#include <QWidget>
#include "ui_testframe.h"

#include <QSplitter>
#include "qdebug.h"

#include "src/fasttable/customfasttablewidget.h"
#include "src/fasttable/publictablewidget.h"

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
    QList< quint16 >         *mRowHeights;
    QList< quint16 >         *mColumnWidths;
    QList< int >             *mOffsetX;
    QList< int >             *mOffsetY;

    QList< QStringList >     *mHorizontalHeader_Data;
    QList< quint16 >         *mHorizontalHeader_RowHeights;
    QList< int >             *mHorizontalHeader_OffsetY;

    QList< QStringList >     *mVerticalHeader_Data;
    QList< quint16 >         *mVerticalHeader_ColumnWidths;
    QList< int >             *mVerticalHeader_OffsetX;

    QList< QList<bool> >     *mSelectedCells;
    QList< QPoint >          *mCurSelection;
    QList< bool >            *mHorizontalHeader_SelectedColumns;
    QList< bool >            *mVerticalHeader_SelectedRows;

    QList< QList<QBrush *> > *mBackgroundBrushes;
    QList< QList<QColor *> > *mForegroundColors;
    QList< QList<QFont *> >  *mCellFonts;
    QList< QList<int> >      *mCellTextFlags;
    QList< QList<quint16> >  *mCellMergeX;
    QList< QList<quint16> >  *mCellMergeY;
    QList< QList<int> >      *mCellMergeParentRow;
    QList< QList<int> >      *mCellMergeParentColumn;

    QList< QList<QBrush *> > *mHorizontalHeader_BackgroundBrushes;
    QList< QList<QColor *> > *mHorizontalHeader_ForegroundColors;
    QList< QList<QFont *> >  *mHorizontalHeader_CellFonts;
    QList< QList<int> >      *mHorizontalHeader_CellTextFlags;
    QList< QList<quint16> >  *mHorizontalHeader_CellMergeX;
    QList< QList<quint16> >  *mHorizontalHeader_CellMergeY;
    QList< QList<int> >      *mHorizontalHeader_CellMergeParentRow;
    QList< QList<int> >      *mHorizontalHeader_CellMergeParentColumn;

    QList< QList<QBrush *> > *mVerticalHeader_BackgroundBrushes;
    QList< QList<QColor *> > *mVerticalHeader_ForegroundColors;
    QList< QList<QFont *> >  *mVerticalHeader_CellFonts;
    QList< QList<int> >      *mVerticalHeader_CellTextFlags;
    QList< QList<quint16> >  *mVerticalHeader_CellMergeX;
    QList< QList<quint16> >  *mVerticalHeader_CellMergeY;
    QList< QList<int> >      *mVerticalHeader_CellMergeParentRow;
    QList< QList<int> >      *mVerticalHeader_CellMergeParentColumn;

    //---------------------------------------------------------------------------

    Ui::TestFrame         *ui;
    CustomFastTableWidget *mFastTable;
    QSplitter             *mDividerSplitter;

    explicit TestFrame(CustomFastTableWidget* aFastTable, QWidget *parent = 0);
    ~TestFrame();

    void startTest();

    bool checkForSizes(int rows, int columns, int headerRows, int headerColumns);

    inline void testCompleted(bool success, QLabel *aLabel);
    inline void testSuccess(QLabel *aLabel);
    inline void testFail(QLabel *aLabel);
    inline void testNotSupported(QLabel *aLabel);

signals:
    void testFinished();
};

#endif // TESTFRAME_H
