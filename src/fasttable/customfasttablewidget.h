#ifndef CUSTOMCustomFastTableWidget_H
#define CUSTOMCustomFastTableWidget_H

#include <QAbstractScrollArea>
#include <QTableWidget>
#include <QList>
#include <QString>
#include <QStringList>
#include <QColor>
#include <QPainter>
#include <QScrollBar>
#include <QDateTime>
#include <QMouseEvent>
#include <QTimer>
#include <QApplication>
#include <QClipboard>

#include "qdebug.h"

#include "fastdefines.h"

//------------------------------------------------------------------------------

class CustomFastTableWidget : public QAbstractScrollArea
{
    Q_OBJECT
    Q_PROPERTY(int     rowCount                                READ rowCount                                WRITE setRowCount)
    Q_PROPERTY(int     columnCount                             READ columnCount                             WRITE setColumnCount)
    Q_PROPERTY(qint16  horizontalHeader_RowCount               READ horizontalHeader_RowCount               WRITE horizontalHeader_SetRowCount)
    Q_PROPERTY(qint16  verticalHeader_ColumnCount              READ verticalHeader_ColumnCount              WRITE verticalHeader_SetColumnCount)
    Q_PROPERTY(quint16 defaultWidth                            READ defaultWidth                            WRITE setDefaultWidth)
    Q_PROPERTY(quint16 defaultHeight                           READ defaultHeight                           WRITE setDefaultHeight)
    Q_PROPERTY(int     totalWidth                              READ totalWidth)
    Q_PROPERTY(int     totalHeight                             READ totalHeight)
    Q_PROPERTY(int     verticalHeader_TotalWidth               READ verticalHeader_TotalWidth)
    Q_PROPERTY(int     horizontalHeader_TotalHeight            READ horizontalHeader_TotalHeight)
    Q_PROPERTY(QBrush  defaultBackgroundBrush                  READ defaultBackgroundBrush                  WRITE setDefaultBackgroundBrush)
    Q_PROPERTY(QColor  defaultForegroundColor                  READ defaultForegroundColor                  WRITE setDefaultForegroundColor)
    Q_PROPERTY(QColor  gridColor                               READ gridColor                               WRITE setGridColor)
    Q_PROPERTY(QColor  cellBorderColor                         READ cellBorderColor                         WRITE setCellBorderColor)
    Q_PROPERTY(QBrush  horizontalHeader_DefaultBackgroundBrush READ horizontalHeader_DefaultBackgroundBrush WRITE horizontalHeader_SetDefaultBackgroundBrush)
    Q_PROPERTY(QColor  horizontalHeader_DefaultForegroundColor READ horizontalHeader_DefaultForegroundColor WRITE horizontalHeader_SetDefaultForegroundColor)
    Q_PROPERTY(QColor  horizontalHeader_GridColor              READ horizontalHeader_GridColor              WRITE horizontalHeader_SetGridColor)
    Q_PROPERTY(QColor  horizontalHeader_CellBorderColor        READ horizontalHeader_CellBorderColor        WRITE horizontalHeader_SetCellBorderColor)
    Q_PROPERTY(QBrush  verticalHeader_DefaultBackgroundBrush   READ verticalHeader_DefaultBackgroundBrush   WRITE verticalHeader_SetDefaultBackgroundBrush)
    Q_PROPERTY(QColor  verticalHeader_DefaultForegroundColor   READ verticalHeader_DefaultForegroundColor   WRITE verticalHeader_SetDefaultForegroundColor)
    Q_PROPERTY(QColor  verticalHeader_GridColor                READ verticalHeader_GridColor                WRITE verticalHeader_SetGridColor)
    Q_PROPERTY(QColor  verticalHeader_CellBorderColor          READ verticalHeader_CellBorderColor          WRITE verticalHeader_SetCellBorderColor)
    Q_PROPERTY(QBrush  selectionBrush                          READ selectionBrush                          WRITE setSelectionBrush)
    Q_PROPERTY(QColor  selectionTextColor                      READ selectionTextColor                      WRITE setSelectionTextColor)

public:

    enum DrawComponent {DrawCell, DrawHorizontalHeaderCell, DrawVerticalHeaderCell, DrawTopLeftCorner};
    enum Style {StyleSimple, StyleLinux, StyleWinXP, StyleWin7};
    enum MouseLocation {InMiddleWorld, InCell, InHorizontalHeaderCell, InVerticalHeaderCell, InTopLeftCorner};

    typedef void (*DrawFunction)(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);

    explicit CustomFastTableWidget(QWidget *parent = 0);
    ~CustomFastTableWidget();

    virtual void clear();

    virtual void selectRow(const int row);
    virtual void unselectRow(const int row);

    virtual void selectColumn(const int column);
    virtual void unselectColumn(const int column);

    Style style();
    void setStyle(Style style, bool keepColors=false);

    void setDrawCellFunction(DrawFunction aDrawCellFunction);
    void setDrawHeaderCellFunction(DrawFunction aDrawHeaderCellFunction);

    void selectAll();
    void unselectAll();

    void addRow();
    virtual void insertRow(int row);
    virtual void removeRow(int row);

    void addColumn();
    virtual void insertColumn(int column);
    virtual void removeColumn(int column);

    void horizontalHeader_AddRow();
    virtual void horizontalHeader_InsertRow(int row);
    virtual void horizontalHeader_RemoveRow(int row);

    void verticalHeader_AddColumn();
    virtual void verticalHeader_InsertColumn(int column);
    virtual void verticalHeader_RemoveColumn(int column);

    int rowCount();
    void setRowCount(int count);

    int columnCount();
    void setColumnCount(int count);

    qint16 horizontalHeader_RowCount();
    void horizontalHeader_SetRowCount(qint16 count);

    qint16 verticalHeader_ColumnCount();
    void verticalHeader_SetColumnCount(qint16 count);

    void setSizes(int aRowCount, int aColumnCount, qint16 aHorizontalHeaderRowCount=1, qint16 aVerticalHeaderColumnCount=1);

    QBrush defaultBackgroundBrush();
    void setDefaultBackgroundBrush(QBrush brush);

    QColor defaultForegroundColor();
    void setDefaultForegroundColor(QColor color);

    QColor gridColor();
    void setGridColor(QColor color);

    QColor cellBorderColor();
    void setCellBorderColor(QColor color);

    QBrush horizontalHeader_DefaultBackgroundBrush();
    void horizontalHeader_SetDefaultBackgroundBrush(QBrush brush);

    QColor horizontalHeader_DefaultForegroundColor();
    void horizontalHeader_SetDefaultForegroundColor(QColor color);

    QColor horizontalHeader_GridColor();
    void horizontalHeader_SetGridColor(QColor color);

    QColor horizontalHeader_CellBorderColor();
    void horizontalHeader_SetCellBorderColor(QColor color);

    QBrush verticalHeader_DefaultBackgroundBrush();
    void verticalHeader_SetDefaultBackgroundBrush(QBrush brush);

    QColor verticalHeader_DefaultForegroundColor();
    void verticalHeader_SetDefaultForegroundColor(QColor color);

    QColor verticalHeader_GridColor();
    void verticalHeader_SetGridColor(QColor color);

    QColor verticalHeader_CellBorderColor();
    void verticalHeader_SetCellBorderColor(QColor color);

    QBrush selectionBrush();
    void setSelectionBrush(QBrush brush);

    QColor selectionTextColor();
    void setSelectionTextColor(QColor color);

    quint16 defaultWidth();
    void setDefaultWidth(quint16 width);

    quint16 defaultHeight();
    void setDefaultHeight(quint16 height);

    quint16 columnWidth(const int column);
    void setColumnWidth(const int column, quint16 width);

    quint16 rowHeight(const int row);
    void setRowHeight(const int row, quint16 height);

    quint16 verticalHeader_ColumnWidth(const int column);
    void verticalHeader_SetColumnWidth(const int column, quint16 width);

    quint16 horizontalHeader_RowHeight(const int row);
    void horizontalHeader_SetRowHeight(const int row, quint16 height);

    int totalWidth();
    int totalHeight();
    int verticalHeader_TotalWidth();
    int horizontalHeader_TotalHeight();

    bool columnVisible(const int column);
    void setColumnVisible(const int column, bool visible);

    bool rowVisible(const int row);
    void setRowVisible(const int row, bool visible);

    bool verticalHeader_ColumnVisible(const int column);
    void verticalHeader_SetColumnVisible(const int column, bool visible);

    bool horizontalHeader_RowVisible(const int row);
    void horizontalHeader_SetRowVisible(const int row, bool visible);

    QRect visibleRange();
    QRect horizontalHeader_VisibleRange();
    QRect verticalHeader_VisibleRange();

    virtual QRect cellRectangle(const int row, const int column);
    virtual QRect horizontalHeader_CellRectangle(const int row, const int column);
    virtual QRect verticalHeader_CellRectangle(const int row, const int column);
    void scrollToCell(const int row, const int column);

    QString text(const int row, const int column);
    void setText(const int row, const int column, const QString text);

    QString horizontalHeader_Text(const int row, const int column);
    QString horizontalHeader_Text(const int column);
    void horizontalHeader_SetText(const int row, const int column, const QString text);
    void horizontalHeader_SetText(const int column, const QString text);

    QString verticalHeader_Text(const int row, const int column);
    QString verticalHeader_Text(const int row);
    void verticalHeader_SetText(const int row, const int column, const QString text);
    void verticalHeader_SetText(const int row, const QString text);

    virtual bool cellSelected(const int row, const int column);
    virtual void setCellSelected(const int row, const int column, const bool selected);

    QList<QPoint> selectedCells();
    QList<QRect> selectedRanges();
    QPoint topLeftSelectedCell();
    bool columnHasSelection(const int column);
    bool rowHasSelection(const int row);

    QPoint currentCell();
    virtual void setCurrentCell(int row, int column, const bool keepSelection=false);

    int currentRow();
    void setCurrentRow(const int row, const bool keepSelection=false);

    int currentColumn();
    void setCurrentColumn(const int column, const bool keepSelection=false);

    QPoint cellAt(const int x, const int y);
    QPoint horizontalHeader_CellAt(const int x, const int y);
    QPoint verticalHeader_CellAt(const int x, const int y);
    bool atTopLeftCorner(const int x, const int y);

protected:
    Style mStyle;

    DrawFunction mDrawCellFunction;
    DrawFunction mDrawHeaderCellFunction;

    int mRowCount;
    int mColumnCount;
    qint16 mHorizontalHeader_RowCount;
    qint16 mVerticalHeader_ColumnCount;

    QBrush mDefaultBackgroundBrush;
    QColor mDefaultForegroundColor;
    QColor mGridColor;
    QColor mCellBorderColor;

    QBrush mHorizontalHeader_DefaultBackgroundBrush;
    QColor mHorizontalHeader_DefaultForegroundColor;
    QColor mHorizontalHeader_GridColor;
    QColor mHorizontalHeader_CellBorderColor;

    QBrush mVerticalHeader_DefaultBackgroundBrush;
    QColor mVerticalHeader_DefaultForegroundColor;
    QColor mVerticalHeader_GridColor;
    QColor mVerticalHeader_CellBorderColor;

    QBrush mSelectionBrush;
    QColor mSelectionTextColor;

    quint16 mDefaultWidth;
    quint16 mDefaultHeight;
    int mTotalWidth;
    int mTotalHeight;
    int mVerticalHeader_TotalWidth;
    int mHorizontalHeader_TotalHeight;

    int mVisibleLeft;
    int mVisibleRight;
    int mVisibleTop;
    int mVisibleBottom;

    int mHorizontalHeader_VisibleBottom;

    int mVerticalHeader_VisibleRight;

    QList< QStringList > mData;
    QList< qint16 >      mRowHeights;
    QList< qint16 >      mColumnWidths;
    QList< int >         mOffsetX;
    QList< int >         mOffsetY;

    QList< QStringList > mHorizontalHeader_Data;
    QList< qint16 >      mHorizontalHeader_RowHeights;
    QList< int >         mHorizontalHeader_OffsetY;

    QList< QStringList > mVerticalHeader_Data;
    QList< qint16 >      mVerticalHeader_ColumnWidths;
    QList< int >         mVerticalHeader_OffsetX;

    QList< QList<bool> > mSelectedCells;
    QList< QPoint >      mCurSelection;
    QList< int >         mHorizontalHeader_SelectedColumns;
    QList< int >         mVerticalHeader_SelectedRows;

    int mCurrentRow;
    int mCurrentColumn;

    int mLastX;
    int mLastY;
    int mMouseXForShift;
    int mMouseYForShift;
    int mMouseResizeLineX;
    int mMouseResizeLineY;
    int mMouseResizeCell;

    bool mMousePressed;
    bool mCtrlPressed;
    bool mShiftPressed;

    MouseLocation mMouseLocation;
    MouseLocation mMouseLocationForShift;

    QList< QList<bool> > mMouseSelectedCells;

    QTimer mMouseHoldTimer;
    QMouseEvent mMouseEvent;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    virtual void selectRangeForHandlers(int resX, int resY);
    virtual void horizontalHeader_SelectRangeForHandlers(int resX);
    virtual void verticalHeader_SelectRangeForHandlers(int resY);

    virtual void paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column, const DrawComponent drawComponent);
    virtual void paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const DrawComponent drawComponent, bool headerPressed, QColor *aGridColor,
                           QBrush *aBackgroundBrush, QColor *aBorderColor, QColor *aTextColor, QString *aText, QFont *aFont, int aTextFlags);

    static void paintCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);
    static void paintCellDefault(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);
    static void paintHeaderCellLinux(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);
    static void paintHeaderCellWinXP(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);
    static void paintHeaderCellWin7(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);
    static void paintHeaderCellDefault(QPainter &painter, const int x, const int y, const int width, const int height, const bool headerPressed, QColor *aGridColor, QBrush *aBackgroundBrush, QColor *aBorderColor);

    void updateBarsRanges();
    virtual void updateVisibleRange();
    void initShiftSelectionForKeyboard();
    void initShiftSelection();
    void fillShiftSelection();

public slots:
    void scrollToTop();
    void scrollToBottom();
    void scrollToCurrentCell();

protected slots:
    void scrollBarValueChanged(int value);

    void mouseHoldTick();
};

#endif // CUSTOMCustomFastTableWidget_H
