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

    QList< QStringList >     *mHorizontalHeaderData;
    QList< quint16 >         *mHorizontalHeaderRowHeights;
    QList< quint16 >         *mHorizontalHeaderColumnWidths;
    QList< int >             *mHorizontalHeaderOffsetX;
    QList< int >             *mHorizontalHeaderOffsetY;

    QList< QStringList >     *mVerticalHeaderData;
    QList< quint16 >         *mVerticalHeaderRowHeights;
    QList< quint16 >         *mVerticalHeaderColumnWidths;
    QList< int >             *mVerticalHeaderOffsetX;
    QList< int >             *mVerticalHeaderOffsetY;

    QList< QList<bool> >     *mSelectedCells;
    QList< QPoint >          *mCurSelection;
    QList< bool >            *mHorizontalHeaderSelectedColumns;
    QList< bool >            *mVerticalHeaderSelectedRows;

    QList< QList<QBrush *> > *mBackgroundBrushes;
    QList< QList<QColor *> > *mForegroundColors;
    QList< QList<QFont *> >  *mCellFonts;
    QList< QList<int> >      *mCellTextFlags;
    QList< QList<quint16> >  *mCellMergeX;
    QList< QList<quint16> >  *mCellMergeY;
    QList< QList<int> >      *mCellMergeParentRow;
    QList< QList<int> >      *mCellMergeParentColumn;

    QList< QList<QBrush *> > *mHorizontalHeaderBackgroundBrushes;
    QList< QList<QColor *> > *mHorizontalHeaderForegroundColors;
    QList< QList<QFont *> >  *mHorizontalHeaderCellFonts;
    QList< QList<int> >      *mHorizontalHeaderCellTextFlags;
    QList< QList<quint16> >  *mHorizontalHeaderCellMergeX;
    QList< QList<quint16> >  *mHorizontalHeaderCellMergeY;
    QList< QList<int> >      *mHorizontalHeaderCellMergeParentRow;
    QList< QList<int> >      *mHorizontalHeaderCellMergeParentColumn;

    QList< QList<QBrush *> > *mVerticalHeaderBackgroundBrushes;
    QList< QList<QColor *> > *mVerticalHeaderForegroundColors;
    QList< QList<QFont *> >  *mVerticalHeaderCellFonts;
    QList< QList<int> >      *mVerticalHeaderCellTextFlags;
    QList< QList<quint16> >  *mVerticalHeaderCellMergeX;
    QList< QList<quint16> >  *mVerticalHeaderCellMergeY;
    QList< QList<int> >      *mVerticalHeaderCellMergeParentRow;
    QList< QList<int> >      *mVerticalHeaderCellMergeParentColumn;

    //---------------------------------------------------------------------------

    Ui::TestFrame         *ui;
    CustomFastTableWidget *mFastTable;
    QSplitter             *mDividerSplitter;

    explicit TestFrame(CustomFastTableWidget* aFastTable, QWidget *parent = 0);
    ~TestFrame();

    void startTest();

    bool checkForSizes(int rows, int columns);

    inline void testCompleted(bool success, QLabel *aLabel);
    inline void testSuccess(QLabel *aLabel);
    inline void testFail(QLabel *aLabel);
    inline void testNotSupported(QLabel *aLabel);

signals:
    void testFinished();
};

#endif // TESTFRAME_H
