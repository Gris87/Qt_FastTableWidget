#include "viewdialog.h"
#include "ui_viewdialog.h"

#include <QDebug>

ViewDialog::ViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;
}

ViewDialog::ViewDialog(int aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setText(0, 0, valueToString(aValue));
}

ViewDialog::ViewDialog(bool aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setText(0, 0, valueToString(aValue));
}

ViewDialog::ViewDialog(CustomFastTableWidget::MouseLocation aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->horizontalHeader_SetText(0, "MouseLocation");

    mFastTableWidget->setText(0, 0, valueToString(aValue));
}

ViewDialog::ViewDialog(QPoint aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setColumnCount(2);

    mFastTableWidget->horizontalHeader_SetText(0, "X");
    mFastTableWidget->horizontalHeader_SetText(1, "Y");

    mFastTableWidget->setText(0, 0, valueToString(aValue.x()));
    mFastTableWidget->setText(0, 1, valueToString(aValue.y()));
}

ViewDialog::ViewDialog(QRect aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setColumnCount(4);

    mFastTableWidget->horizontalHeader_SetText(0, "Left");
    mFastTableWidget->horizontalHeader_SetText(1, "Top");
    mFastTableWidget->horizontalHeader_SetText(2, "Right");
    mFastTableWidget->horizontalHeader_SetText(3, "Bottom");

    mFastTableWidget->setText(0, 0, valueToString(aValue.left()));
    mFastTableWidget->setText(0, 1, valueToString(aValue.top()));
    mFastTableWidget->setText(0, 2, valueToString(aValue.right()));
    mFastTableWidget->setText(0, 3, valueToString(aValue.bottom()));
}

ViewDialog::ViewDialog(QList<qint16> *aValues, bool isVertical, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    if (isVertical)
    {
        mFastTableWidget->setRowCount(aValues->length());

        for (int i=0; i<aValues->length(); i++)
        {
            mFastTableWidget->setText(i, 0, valueToString(aValues->at(i)));
        }
    }
    else
    {
        mFastTableWidget->setColumnCount(aValues->length());

        for (int i=0; i<aValues->length(); i++)
        {
            mFastTableWidget->setText(0, i, valueToString(aValues->at(i)));
        }
    }
}

ViewDialog::ViewDialog(QList<int> *aValues, bool isVertical, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    if (isVertical)
    {
        mFastTableWidget->setRowCount(aValues->length());

        for (int i=0; i<aValues->length(); i++)
        {
            mFastTableWidget->setText(i, 0, valueToString(aValues->at(i)));
        }
    }
    else
    {
        mFastTableWidget->setColumnCount(aValues->length());

        for (int i=0; i<aValues->length(); i++)
        {
            mFastTableWidget->setText(0, i, valueToString(aValues->at(i)));
        }
    }
}

ViewDialog::ViewDialog(QList<bool> *aValues, bool isVertical, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    if (isVertical)
    {
        mFastTableWidget->setRowCount(aValues->length());

        for (int i=0; i<aValues->length(); i++)
        {
            mFastTableWidget->setText(i, 0, valueToString(aValues->at(i)));
        }
    }
    else
    {
        mFastTableWidget->setColumnCount(aValues->length());

        for (int i=0; i<aValues->length(); i++)
        {
            mFastTableWidget->setText(0, i, valueToString(aValues->at(i)));
        }
    }
}

ViewDialog::ViewDialog(QList<QPoint> *aValues, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setRowCount(aValues->length());
    mFastTableWidget->setColumnCount(2);

    mFastTableWidget->horizontalHeader_SetText(0, "X");
    mFastTableWidget->horizontalHeader_SetText(1, "Y");

    for (int i=0; i<aValues->length(); i++)
    {
         mFastTableWidget->setText(i, 0, valueToString(aValues->at(i).x()));
         mFastTableWidget->setText(i, 1, valueToString(aValues->at(i).y()));
    }
}

ViewDialog::ViewDialog(QList<QRect> *aValues, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setRowCount(aValues->length());
    mFastTableWidget->setColumnCount(4);

    mFastTableWidget->horizontalHeader_SetText(0, "Left");
    mFastTableWidget->horizontalHeader_SetText(1, "Top");
    mFastTableWidget->horizontalHeader_SetText(2, "Right");
    mFastTableWidget->horizontalHeader_SetText(3, "Bottom");

    for (int i=0; i<aValues->length(); i++)
    {
         mFastTableWidget->setText(i, 0, valueToString(aValues->at(i).left()));
         mFastTableWidget->setText(i, 1, valueToString(aValues->at(i).top()));
         mFastTableWidget->setText(i, 2, valueToString(aValues->at(i).right()));
         mFastTableWidget->setText(i, 3, valueToString(aValues->at(i).bottom()));
    }
}

ViewDialog::ViewDialog(QList<QList<int> > *aValues, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setRowCount(aValues->length());

    if (aValues->length()>0)
    {
        mFastTableWidget->setColumnCount(aValues->at(0).length());

        for (int i=0; i<aValues->length(); i++)
        {
            for (int j=0; j<aValues->at(i).length(); j++)
            {
                mFastTableWidget->setText(i, j, valueToString(aValues->at(i).at(j)));
            }
        }
    }
    else
    {
         mFastTableWidget->setColumnCount(0);
    }
}

ViewDialog::ViewDialog(QList<QList<bool> > *aValues, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setRowCount(aValues->length());

    if (aValues->length()>0)
    {
        mFastTableWidget->setColumnCount(aValues->at(0).length());

        for (int i=0; i<aValues->length(); i++)
        {
            for (int j=0; j<aValues->at(i).length(); j++)
            {
                mFastTableWidget->setText(i, j, valueToString(aValues->at(i).at(j)));
            }
        }
    }
    else
    {
         mFastTableWidget->setColumnCount(0);
    }
}

ViewDialog::ViewDialog(QList<QStringList> *aValues, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    VIEWDIALOG_BASE_CONSTRUCTOR;

    mFastTableWidget->setRowCount(aValues->length());

    if (aValues->length()>0)
    {
        mFastTableWidget->setColumnCount(aValues->at(0).length());

        for (int i=0; i<aValues->length(); i++)
        {
            for (int j=0; j<aValues->at(i).length(); j++)
            {
                mFastTableWidget->setText(i, j, valueToString(aValues->at(i).at(j)));
            }
        }
    }
    else
    {
         mFastTableWidget->setColumnCount(0);
    }
}

ViewDialog::~ViewDialog()
{
    delete ui;
}

QString ViewDialog::valueToString(int aValue)
{
    return QString::number(aValue);
}

QString ViewDialog::valueToString(bool aValue)
{
    if (aValue)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

QString ViewDialog::valueToString(CustomFastTableWidget::MouseLocation aValue)
{
    switch (aValue)
    {
        case CustomFastTableWidget::InMiddleWorld:          return "InMiddleWorld";
        case CustomFastTableWidget::InCell:                 return "InCell";
        case CustomFastTableWidget::InHorizontalHeaderCell: return "InHorizontalHeaderCell";
        case CustomFastTableWidget::InVerticalHeaderCell:   return "InVerticalHeaderCell";
        case CustomFastTableWidget::InTopLeftCorner:        return "InTopLeftCorner";
    }

    return "";
}

QString ViewDialog::valueToString(QString aValue)
{
    return aValue;
}

int ViewDialog::exec()
{
    int aWidth=mFastTableWidget->totalWidth()+30;
    int aHeight=mFastTableWidget->totalHeight()+30;

    if (aWidth>800)
    {
        aWidth=800;
    }

    if (aHeight>600)
    {
        aHeight=600;
    }

    resize(aWidth, aHeight);

    for (int i=0; i<mFastTableWidget->columnCount(); i++)
    {
        if (mFastTableWidget->horizontalHeader_Text(i)=="")
        {
            mFastTableWidget->horizontalHeader_SetText(i, QString::number(i+1));
        }
    }

    return QDialog::exec();
}
