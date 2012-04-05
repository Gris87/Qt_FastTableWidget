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
    Q_PROPERTY(int     rowCount               READ rowCount               WRITE setRowCount)
    Q_PROPERTY(int     columnCount            READ columnCount            WRITE setColumnCount)
    Q_PROPERTY(quint16 defaultHeight          READ defaultHeight          WRITE setDefaultHeight)
    Q_PROPERTY(quint16 defaultWidth           READ defaultWidth           WRITE setDefaultWidth)
    Q_PROPERTY(QBrush  defaultBackgroundBrush READ defaultBackgroundBrush WRITE setDefaultBackgroundBrush)
    Q_PROPERTY(QColor  defaultForegroundColor READ defaultForegroundColor WRITE setDefaultForegroundColor)
    Q_PROPERTY(QColor  gridColor              READ gridColor              WRITE setGridColor)
    Q_PROPERTY(QBrush  selectionBrush         READ selectionBrush         WRITE setSelectionBrush)
    Q_PROPERTY(int     totalHeight            READ totalHeight)
    Q_PROPERTY(int     totalWidth             READ totalWidth)

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

    virtual void insertRow(int row);
    void addRow();
    virtual void deleteRow(int row);

    virtual void insertColumn(int column);
    void addColumn();
    virtual void deleteColumn(int column);

    int rowCount();
    void setRowCount(int count);

    int columnCount();
    void setColumnCount(int count);

    QBrush defaultBackgroundBrush();
    void setDefaultBackgroundBrush(QBrush brush);

    QColor defaultForegroundColor();
    void setDefaultForegroundColor(QColor color);

    QColor gridColor();
    void setGridColor(QColor color);

    QBrush selectionBrush();
    void setSelectionBrush(QBrush brush);

    quint16 defaultHeight();
    void setDefaultHeight(quint16 height);

    quint16 defaultWidth();
    void setDefaultWidth(quint16 width);

    int totalHeight();
    int totalWidth();

    QRect visibleRange();

    QString text(const int row, const int column);
    void setText(const int row, const int column, const QString text);

    quint16 rowHeight(const int row);
    void setRowHeight(const int row, const quint16 height);

    quint16 columnWidth(const int column);
    void setColumnWidth(const int column, const quint16 width);

    virtual bool cellSelected(const int row, const int column);
    virtual void setCellSelected(const int row, const int column, const bool selected);

protected:
    int mRowCount;
    int mColumnCount;

    quint16 mDefaultHeight;
    quint16 mDefaultWidth;
    int mTotalHeight;
    int mTotalWidth;

    QBrush mDefaultBackgroundBrush;
    QColor mDefaultForegroundColor;
    QColor mGridColor;
    QBrush mSelectionBrush;

    int mVisibleLeft;
    int mVisibleRight;
    int mVisibleTop;
    int mVisibleBottom;

    QList< QStringList > mData;
    QList< quint16 > mRowHeights;
    QList< quint16 > mColumnWidths;
    QList< int > mOffsetX;
    QList< int > mOffsetY;
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
