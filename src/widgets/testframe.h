#ifndef TESTFRAME_H
#define TESTFRAME_H

#include <QWidget>
#include "ui_testframe.h"

#include <QSplitter>
#include "qdebug.h"

#include "src/fasttable/fasttablewidget.h"
#include "src/fasttable/publictablewidget.h"

namespace Ui {
    class TestFrame;
}

class TestFrame : public QWidget
{
    Q_OBJECT

public:
    Ui::TestFrame   *ui;
    FastTableWidget *mFastTable;
    QSplitter       *mDividerSplitter;

    QList< QStringList >      *mData;
    QList< quint16 >          *mRowHeights;
    QList< quint16 >          *mColumnWidths;
    QList< int >              *mOffsetX;
    QList< int >              *mOffsetY;
    QList< QList<bool> >      *mSelectedCells;
    QList< QPoint >           *mCurSelection;
    QList< QList<QBrush *> >  *mBackgroundBrushes;
    QList< QList<QColor *> >  *mForegroundColors;
    QList< QList<QFont *> >   *mCellFonts;
    QList< QList<int> >       *mCellTextFlags;
    QList< QList<quint16> >   *mCellMergeX;
    QList< QList<quint16> >   *mCellMergeY;
    QList< QList<int> >       *mCellMergeParentRow;
    QList< QList<int> >       *mCellMergeParentColumn;

    explicit TestFrame(FastTableWidget* aFastTable, QWidget *parent = 0);
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
