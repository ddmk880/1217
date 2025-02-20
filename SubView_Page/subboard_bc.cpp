#include "subboard_bc.h"
#include "ui_subboard_bc.h"
#include "Globel_Define.h"

subboard_bc::subboard_bc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subboard_bc)
{
    ui->setupUi(this);

    //this->setStyleSheet("border-image:url(:/new/prefix1/Pic/1342sig.jpg);");//图片平铺，顶层窗口不显示，子窗口使用，
    this->setStyleSheet("image:url(:/new/prefix1/Pic/1342sig.jpg);");//图片平铺，顶层窗口不显示，子窗口使用，
}

subboard_bc::~subboard_bc()
{
    delete ui;
}
