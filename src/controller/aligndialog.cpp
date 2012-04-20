#include "aligndialog.h"
#include "ui_aligndialog.h"

AlignDialog::AlignDialog(int initAlignment, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlignDialog)
{
    ui->setupUi(this);

    ui->topLeftButton    ->setIcon((initAlignment & (Qt::AlignTop     | Qt::AlignLeft))==(Qt::AlignTop        | Qt::AlignLeft)    ? QIcon(":/images/CellTopLeftSelected.png")     : QIcon(":/images/CellTopLeft.png"));
    ui->topButton        ->setIcon((initAlignment & (Qt::AlignTop     | Qt::AlignHCenter))==(Qt::AlignTop     | Qt::AlignHCenter) ? QIcon(":/images/CellTopSelected.png")         : QIcon(":/images/CellTop.png"));
    ui->topRightButton   ->setIcon((initAlignment & (Qt::AlignTop     | Qt::AlignRight))==(Qt::AlignTop       | Qt::AlignRight)   ? QIcon(":/images/CellTopRightSelected.png")    : QIcon(":/images/CellTopRight.png"));
    ui->leftButton       ->setIcon((initAlignment & (Qt::AlignVCenter | Qt::AlignLeft))==(Qt::AlignVCenter    | Qt::AlignLeft)    ? QIcon(":/images/CellLeftSelected.png")        : QIcon(":/images/CellLeft.png"));
    ui->centerButton     ->setIcon((initAlignment &                     Qt::AlignCenter)==Qt::AlignCenter                         ? QIcon(":/images/CellCenterSelected.png")      : QIcon(":/images/CellCenter.png"));
    ui->rightButton      ->setIcon((initAlignment & (Qt::AlignVCenter | Qt::AlignRight))==(Qt::AlignVCenter   | Qt::AlignRight)   ? QIcon(":/images/CellRightSelected.png")       : QIcon(":/images/CellRight.png"));
    ui->bottomLeftButton ->setIcon((initAlignment & (Qt::AlignBottom  | Qt::AlignLeft))==(Qt::AlignBottom     | Qt::AlignLeft)    ? QIcon(":/images/CellBottomLeftSelected.png")  : QIcon(":/images/CellBottomLeft.png"));
    ui->bottomButton     ->setIcon((initAlignment & (Qt::AlignBottom  | Qt::AlignHCenter))==(Qt::AlignBottom  | Qt::AlignHCenter) ? QIcon(":/images/CellBottomSelected.png")      : QIcon(":/images/CellBottom.png"));
    ui->bottomRightButton->setIcon((initAlignment & (Qt::AlignBottom  | Qt::AlignRight))==(Qt::AlignBottom    | Qt::AlignRight)   ? QIcon(":/images/CellBottomRightSelected.png") : QIcon(":/images/CellBottomRight.png"));
}

AlignDialog::~AlignDialog()
{
    delete ui;
}

void AlignDialog::on_topLeftButton_clicked()
{
    resultAlignment=Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_topButton_clicked()
{
    resultAlignment=Qt::AlignTop | Qt::AlignHCenter | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_topRightButton_clicked()
{
    resultAlignment=Qt::AlignTop | Qt::AlignRight | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_leftButton_clicked()
{
    resultAlignment=Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_centerButton_clicked()
{
    resultAlignment=Qt::AlignCenter | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_rightButton_clicked()
{
    resultAlignment=Qt::AlignVCenter | Qt::AlignRight | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_bottomLeftButton_clicked()
{
    resultAlignment=Qt::AlignBottom | Qt::AlignLeft | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_bottomButton_clicked()
{
    resultAlignment=Qt::AlignBottom | Qt::AlignHCenter | Qt::TextWordWrap;
    accept();
}

void AlignDialog::on_bottomRightButton_clicked()
{
    resultAlignment=Qt::AlignBottom | Qt::AlignRight | Qt::TextWordWrap;
    accept();
}
