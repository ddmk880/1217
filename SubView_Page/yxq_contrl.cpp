#include "yxq_contrl.h"
#include "ui_yxq_contrl.h"
#include <QValidator>
yxq_contrl::yxq_contrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yxq_contrl)
{
    ui->setupUi(this);
    // 正则表达式设置IP和MAC输入,信号源1
    QRegExp ipRegExp = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip = new QRegExpValidator(ipRegExp,this);
    ui->lineEdit_yxqIP->setValidator(m_ip);
}

yxq_contrl::~yxq_contrl()
{
    delete ui;
}
//连接
void yxq_contrl::on_pushButto_cont_clicked()
{

}
