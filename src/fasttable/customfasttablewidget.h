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

#include "qdebug.h"

#define FASTTABLE_DEBUG

#if 1
    #define START_PROFILE      qint64 profileStart=QDateTime::currentMSecsSinceEpoch();
    #define END_PROFILE(text)  qDebug()<<text" :"<<QDateTime::currentMSecsSinceEpoch()-profileStart;
#else
    #define START_PROFILE
    #define END_PROFILE(text)
#endif

#if 0
    #define START_FREQUENT_PROFILE      START_PROFILE
    #define END_FREQUENT_PROFILE(text)  END_PROFILE(text)
#else
    #define START_FREQUENT_PROFILE
    #define END_FREQUENT_PROFILE(text)
#endif

//------------------------------------------------------------------------------

class CustomFastTableWidget : public QAbstractScrollArea
{
    Q_OBJECT
    Q_PROPERTY(int     rowCount                               READ rowCount                               WRITE setRowCount)
    Q_PROPERTY(int     columnCount                            READ columnCount                            WRITE setColumnCount)
    Q_PROPERTY(qint16  horizontalHeaderRowCount               READ horizontalHeaderRowCount               WRITE setHorizontalHeaderRowCount)
    Q_PROPERTY(qint16  verticalHeaderColumnCount              READ verticalHeaderColumnCount              WRITE setVerticalHeaderColumnCount)
    Q_PROPERTY(quint16 defaultWidth                           READ defaultWidth                           WRITE setDefaultWidth)
    Q_PROPERTY(quint16 defaultHeight                          READ defaultHeight                          WRITE setDefaultHeight)
    Q_PROPERTY(int     totalWidth                             READ totalWidth)
    Q_PROPERTY(int     totalHeight                            READ totalHeight)
    Q_PROPERTY(int     verticalHeaderTotalWidth               READ verticalHeaderTotalWidth)
    Q_PROPERTY(int     horizontalHeaderTotalHeight            READ horizontalHeaderTotalHeight)
    Q_PROPERTY(QBrush  defaultBackgroundBrush                 READ defaultBackgroundBrush                 WRITE setDefaultBackgroundBrush)
    Q_PROPERTY(QColor  defaultForegroundColor                 READ defaultForegroundColor                 WRITE setDefaultForegroundColor)
    Q_PROPERTY(QColor  gridColor                              READ gridColor                              WRITE setGridColor)
    Q_PROPERTY(QBrush  horizontalHeaderDefaultBackgroundBrush READ horizontalHeaderDefaultBackgroundBrush WRITE setHorizontalHeaderDefaultBackgroundBrush)
    Q_PROPERTY(QColor  horizontalHeaderDefaultForegroundColor READ horizontalHeaderDefaultForegroundColor WRITE setHorizontalHeaderDefaultForegroundColor)
    Q_PROPERTY(QColor  horizontalHeaderGridColor              READ horizontalHeaderGridColor              WRITE setHorizontalHeaderGridColor)
    Q_PROPERTY(QBrush  verticalHeaderDefaultBackgroundBrush   READ verticalHeaderDefaultBackgroundBrush   WRITE setVerticalHeaderDefaultBackgroundBrush)
    Q_PROPERTY(QColor  verticalHeaderDefaultForegroundColor   READ verticalHeaderDefaultForegroundColor   WRITE setVerticalHeaderDefaultForegroundColor)
    Q_PROPERTY(QColor  verticalHeaderGridColor                READ verticalHeaderGridColor                WRITE setVerticalHeaderGridColor)
    Q_PROPERTY(QBrush  selectionBrush                         READ selectionBrush                         WRITE setSelectionBrush)

public:
    explicit CustomFastTableWidget(QWidget *parent = 0);
    ~CustomFastTableWidget();

    virtual void clearTable();

    virtual void selectRow(const int row);
    virtual void unselectRow(const int row);

    virtual void selectColumn(const int column);
    virtual void unselectColumn(const int column);

    void selectAll();
    void unselectAll();

    void addRow();
    virtual void insertRow(int row);
    virtual void deleteRow(int row);

    void addColumn();
    virtual void insertColumn(int column);
    virtual void deleteColumn(int column);

    void horizontalHeaderAddRow();
    virtual void horizontalHeaderInsertRow(int row);
    virtual void horizontalHeaderDeleteRow(int row);

    void verticalHeaderAddColumn();
    virtual void verticalHeaderInsertColumn(int column);
    virtual void verticalHeaderDeleteColumn(int column);

    int rowCount();
    void setRowCount(int count);

    int columnCount();
    void setColumnCount(int count);

    qint16 horizontalHeaderRowCount();
    void setHorizontalHeaderRowCount(qint16 count);

    qint16 verticalHeaderColumnCount();
    void setVerticalHeaderColumnCount(qint16 count);

    QBrush defaultBackgroundBrush();
    void setDefaultBackgroundBrush(QBrush brush);

    QColor defaultForegroundColor();
    void setDefaultForegroundColor(QColor color);

    QColor gridColor();
    void setGridColor(QColor color);

    QBrush horizontalHeaderDefaultBackgroundBrush();
    void setHorizontalHeaderDefaultBackgroundBrush(QBrush brush);

    QColor horizontalHeaderDefaultForegroundColor();
    void setHorizontalHeaderDefaultForegroundColor(QColor color);

    QColor horizontalHeaderGridColor();
    void setHorizontalHeaderGridColor(QColor color);

    QBrush verticalHeaderDefaultBackgroundBrush();
    void setVerticalHeaderDefaultBackgroundBrush(QBrush brush);

    QColor verticalHeaderDefaultForegroundColor();
    void setVerticalHeaderDefaultForegroundColor(QColor color);

    QColor verticalHeaderGridColor();
    void setVerticalHeaderGridColor(QColor color);

    QBrush selectionBrush();
    void setSelectionBrush(QBrush brush);

    quint16 defaultWidth();
    void setDefaultWidth(quint16 width);

    quint16 defaultHeight();
    void setDefaultHeight(quint16 height);

    quint16 columnWidth(const int column);
    void setColumnWidth(const int column, const quint16 width);

    quint16 rowHeight(const int row);
    void setRowHeight(const int row, const quint16 height);

    quint16 verticalHeaderColumnWidth(const int column);
    void setVerticalHeaderColumnWidth(const int column, const quint16 width);

    quint16 horizontalHeaderRowHeight(const int row);
    void setHorizontalHeaderRowHeight(const int row, const quint16 height);

    int totalWidth();
    int totalHeight();
    int verticalHeaderTotalWidth();
    int horizontalHeaderTotalHeight();

    QRect visibleRange();
    QRect horizontalHeaderVisibleRange();
    QRect verticalHeaderVisibleRange();

    QString text(const int row, const int column);
    void setText(const int row, const int column, const QString text);

    QString horizontalHeaderText(const int row, const int column);
    QString horizontalHeaderText(const int column);
    void setHorizontalHeaderText(const int row, const int column, const QString text);
    void setHorizontalHeaderText(const int column, const QString text);

    QString verticalHeaderText(const int row, const int column);
    QString verticalHeaderText(const int row);
    void setVerticalHeaderText(const int row, const int column, const QString text);
    void setVerticalHeaderText(const int row, const QString text);

    virtual bool cellSelected(const int row, const int column);
    virtual void setCellSelected(const int row, const int column, const bool selected);

protected:
    int mRowCount;
    int mColumnCount;
    qint16 mHorizontalHeaderRowCount;
    qint16 mVerticalHeaderColumnCount;

    QBrush mDefaultBackgroundBrush;
    QColor mDefaultForegroundColor;
    QColor mGridColor;

    QBrush mHorizontalHeaderDefaultBackgroundBrush;
    QColor mHorizontalHeaderDefaultForegroundColor;
    QColor mHorizontalHeaderGridColor;

    QBrush mVerticalHeaderDefaultBackgroundBrush;
    QColor mVerticalHeaderDefaultForegroundColor;
    QColor mVerticalHeaderGridColor;

    QBrush mSelectionBrush;

    quint16 mDefaultWidth;
    quint16 mDefaultHeight;
    int mTotalWidth;
    int mTotalHeight;
    int mVerticalHeaderTotalWidth;
    int mHorizontalHeaderTotalHeight;

    int mVisibleLeft;
    int mVisibleRight;
    int mVisibleTop;
    int mVisibleBottom;

    int mHorizontalHeaderVisibleLeft;
    int mHorizontalHeaderVisibleRight;
    int mHorizontalHeaderVisibleTop;
    int mHorizontalHeaderVisibleBottom;

    int mVerticalHeaderVisibleLeft;
    int mVerticalHeaderVisibleRight;
    int mVerticalHeaderVisibleTop;
    int mVerticalHeaderVisibleBottom;

    QList< QStringList > mData;
    QList< quint16 > mRowHeights;
    QList< quint16 > mColumnWidths;
    QList< int > mOffsetX;
    QList< int > mOffsetY;

    QList< QStringList > mHorizontalHeaderData;
    QList< quint16 > mHorizontalHeaderRowHeights;
    QList< quint16 > mHorizontalHeaderColumnWidths;
    QList< int > mHorizontalHeaderOffsetX;
    QList< int > mHorizontalHeaderOffsetY;

    QList< QStringList > mVerticalHeaderData;
    QList< quint16 > mVerticalHeaderRowHeights;
    QList< quint16 > mVerticalHeaderColumnWidths;
    QList< int > mVerticalHeaderOffsetX;
    QList< int > mVerticalHeaderOffsetY;

    QList< QList<bool> > mSelectedCells;
    QList< QPoint > mCurSelection;

    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    virtual void paintCell(QPainter &painter, const int x, const int y, const int width, const int height, const int row, const int column);

    void updateBarsRanges();
    virtual void updateVisibleRange();

protected slots:
    void horizontalScrollBarValueChanged(int value);
    void verticalScrollBarValueChanged(int value);
};

#endif // CUSTOMCustomFastTableWidget_H
