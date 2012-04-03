#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>

#include <QLabel>
#include <QFont>
#include <QSplitter>

#include "qdebug.h"

#include "src/fasttable/fasttabletest.h"

namespace Ui {
    class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = 0);
    ~TestDialog();

    QSplitter     *mDividerSplitter;
    FastTableTest *mFastTableWidget;

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

    bool checkForSizes(int rows, int columns);

    inline void testCompleted(bool success, QLabel *aLabel);
    inline void testSuccess(QLabel *aLabel);
    inline void testFail(QLabel *aLabel);

private:
    Ui::TestDialog *ui;
};

#endif // TESTDIALOG_H
