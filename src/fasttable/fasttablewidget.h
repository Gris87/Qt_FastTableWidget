#ifndef FASTTABLEWIDGET_H
#define FASTTABLEWIDGET_H

#include "customfasttablewidget.h"

//------------------------------------------------------------------------------

class FastTableWidget : public CustomFastTableWidget
{
    Q_OBJECT

public:
    explicit FastTableWidget(QWidget *parent = 0);
    ~FastTableWidget();

    void clearTable();

    void resetBackgroundBrushes();
    void resetForegroundColors();
    void resetFonts();
    void resetCellTextFlags();

    void horizontalHeader_ResetBackgroundBrushes();
    void horizontalHeader_ResetForegroundColors();
    void horizontalHeader_ResetFonts();
    void horizontalHeader_ResetCellTextFlags();

    void verticalHeader_ResetBackgroundBrushes();
    void verticalHeader_ResetForegroundColors();
    void verticalHeader_ResetFonts();
    void verticalHeader_ResetCellTextFlags();

    void resetBackgroundBrush(const int row, const int column);
    void resetForegroundColor(const int row, const int column);
    void resetFont(const int row, const int column);
    void resetCellTextFlag(const int row, const int column);

    void horizontalHeader_ResetBackgroundBrush(const int row, const int column);
    void horizontalHeader_ResetForegroundColor(const int row, const int column);
    void horizontalHeader_ResetFont(const int row, const int column);
    void horizontalHeader_ResetCellTextFlag(const int row, const int column);

    void verticalHeader_ResetBackgroundBrush(const int row, const int column);
    void verticalHeader_ResetForegroundColor(const int row, const int column);
    void verticalHeader_ResetFont(const int row, const int column);
    void verticalHeader_ResetCellTextFlag(const int row, const int column);

    void insertRow(int row);
    void deleteRow(int row);

    void insertColumn(int column);
    void deleteColumn(int column);

    void horizontalHeader_InsertRow(int row);
    void horizontalHeader_DeleteRow(int row);

    void verticalHeader_InsertColumn(int column);
    void verticalHeader_DeleteColumn(int column);

    QBrush backgroundBrush(const int row, const int column);
    void setBackgroundBrush(const int row, const int column, const QBrush brush);

    QBrush horizontalHeader_BackgroundBrush(const int row, const int column);
    void horizontalHeader_SetBackgroundBrush(const int row, const int column, const QBrush brush);

    QBrush verticalHeader_BackgroundBrush(const int row, const int column);
    void verticalHeader_SetBackgroundBrush(const int row, const int column, const QBrush brush);

    QColor foregroundColor(const int row, const int column);
    void setForegroundColor(const int row, const int column, const QColor color);

    QColor horizontalHeader_ForegroundColor(const int row, const int column);
    void horizontalHeader_SetForegroundColor(const int row, const int column, const QColor color);

    QColor verticalHeader_ForegroundColor(const int row, const int column);
    void verticalHeader_SetForegroundColor(const int row, const int column, const QColor color);

    QFont cellFont(const int row, const int column);
    void setCellFont(const int row, const int column, const QFont font);

    QFont horizontalHeader_CellFont(const int row, const int column);
    void horizontalHeader_SetCellFont(const int row, const int column, const QFont font);

    QFont verticalHeader_CellFont(const int row, const int column);
    void verticalHeader_SetCellFont(const int row, const int column, const QFont font);

    int cellTextFlags(const int row, const int column);
    void setCellTextFlags(const int row, const int column, const int flags);

    int horizontalHeader_CellTextFlags(const int row, const int column);
    void horizontalHeader_SetCellTextFlags(const int row, const int column, const int flags);

    int verticalHeader_CellTextFlags(const int row, const int column);
    void verticalHeader_SetCellTextFlags(const int row, const int column, const int flags);

    void clearSpans();
    void setSpan(const int row, const int column, quint16 rowSpan, quint16 columnSpan);
    quint16 rowSpan(const int row, const int column);
    quint16 columnSpan(const int row, const int column);
    QPoint spanParent(const int row, const int column);

    void horizontalHeader_ClearSpans();
    void horizontalHeader_SetSpan(const int row, const int column, quint16 rowSpan, quint16 columnSpan);
    quint16 horizontalHeader_RowSpan(const int row, const int column);
    quint16 horizontalHeader_ColumnSpan(const int row, const int column);
    QPoint horizontalHeader_SpanParent(const int row, const int column);

    void verticalHeader_ClearSpans();
    void verticalHeader_SetSpan(const int row, const int column, quint16 rowSpan, quint16 columnSpan);
    quint16 verticalHeader_RowSpan(const int row, const int column);
    quint16 verticalHeader_ColumnSpan(const int row, const int column);
    QPoint verticalHeader_SpanParent(const int row, const int column);

protected:
    QList< QList<QBrush *> > mBackgroundBrushes;
    QList< QList<QColor *> > mForegroundColors;
    QList< QList<QFont *> >  mCellFonts;
    QList< QList<int> >      mCellTextFlags;
    QList< QList<quint16> >  mCellMergeX;
    QList< QList<quint16> >  mCellMergeY;
    QList< QList<int> >      mCellMergeParentRow;
    QList< QList<int> >      mCellMergeParentColumn;

    QList< QList<QBrush *> > mHorizontalHeader_BackgroundBrushes;
    QList< QList<QColor *> > mHorizontalHeader_ForegroundColors;
    QList< QList<QFont *> >  mHorizontalHeader_CellFonts;
    QList< QList<int> >      mHorizontalHeader_CellTextFlags;
    QList< QList<quint16> >  mHorizontalHeader_CellMergeX;
    QList< QList<quint16> >  mHorizontalHeader_CellMergeY;
    QList< QList<int> >      mHorizontalHeader_CellMergeParentRow;
    QList< QList<int> >      mHorizontalHeader_CellMergeParentColumn;

    QList< QList<QBrush *> > mVerticalHeader_BackgroundBrushes;
    QList< QList<QColor *> > mVerticalHeader_ForegroundColors;
    QList< QList<QFont *> >  mVerticalHeader_CellFonts;
    QList< QList<int> >      mVerticalHeader_CellTextFlags;
    QList< QList<quint16> >  mVerticalHeader_CellMergeX;
    QList< QList<quint16> >  mVerticalHeader_CellMergeY;
    QList< QList<int> >      mVerticalHeader_CellMergeParentRow;
    QList< QList<int> >      mVerticalHeader_CellMergeParentColumn;

    void paintEvent(QPaintEvent *event);
    void paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent);

    void updateVisibleRange();
};

#endif // FASTTABLEWIDGET_H
