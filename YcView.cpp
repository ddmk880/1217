#include "YcView.h"
#include "ui_YcView.h"

YcView::YcView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YcView)
{
    ui->setupUi(this);
    // 初始化可选任务页tree
    model_tree_list = new QStandardItemModel;
    // 添加一级节点
    QStandardItem* root_1553 = new QStandardItem("1553B总线");
    // 添加二级子节点
    QList<QStandardItem*> root_1553_2;
    root_1553_2.append(new QStandardItem("1:1553慢速遥测"));
    root_1553_2.append(new QStandardItem("2:1553打包遥测"));
    root_1553->appendRows(root_1553_2);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 添加一级节点
    QStandardItem* root_CAN = new QStandardItem("CAN总线");
    // 添加二级子节点
    QList<QStandardItem*> root_CAN_2;
    root_CAN_2.append(new QStandardItem("10:CAN遥测C81"));
    root_CAN->appendRows(root_CAN_2);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 添加一级节点
    QStandardItem* root_AD = new QStandardItem("其他遥测接收");
    // 添加二级子节点
    QList<QStandardItem*> root_AD1;
    root_AD1.append(new QStandardItem("20:AD遥测"));
    root_AD1.append(new QStandardItem("21:RS422接收"));
    root_AD->appendRows(root_AD1);

    model_tree_list->appendRow(root_1553);
    model_tree_list->appendRow(root_CAN);
    model_tree_list->appendRow(root_AD);

    ui->m_yctree_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_yctree_list->setHeaderHidden(true);
    ui->m_yctree_list->setSelectionBehavior(QTreeView::SelectItems);
    ui->m_yctree_list->setModel(model_tree_list);
    ui->m_yctree_list->setItemsExpandable(true);
    ui->m_yctree_list->expandAll();


    //单机标志颜色
    ui->radioButton_dj2YC->setStyleSheet("color:rgb(135,0,25)");//单机2标志
    ui->radioButton_dj3YC->setStyleSheet("color:rgb(65,70,200)");//单机3标志
    ui->radioButton_dj4YC->setStyleSheet("color:rgb(15,210,70)");//单机4标志
}

YcView::~YcView()
{
    delete ui;
}

//在主界面初始化调用
void YcView::Init_View_Sub()
{
    //慢速遥测
    ui->verticalLayout_4->addWidget(yc_slowspeed);
    //yc_slowspeed->showMaximized();
    //打包遥测
    ui->verticalLayout_4->addWidget(yc_packspeed);
    yc_packspeed->hide();
    //canc81遥测
    ui->verticalLayout_4->addWidget(yc_canc81);
    yc_canc81->hide();
    //AD遥测
    ui->verticalLayout_4->addWidget(yc_ad);
    yc_ad->hide();
    //rs422电平接收
    ui->verticalLayout_4->addWidget(yc_rs422_rec);
    yc_rs422_rec->hide();

}

void YcView::Hide_view()
{
    yc_slowspeed->hide();
    yc_packspeed->hide();
    yc_canc81->hide();
    yc_ad->hide();
    yc_rs422_rec->hide();
}

void YcView::Show_view(int index)
{
    bool viewF=true;//单机选择栏界面显示
    int page_index=index;
    switch (page_index) {

    case 1:
        ui->groupBox_ycname->setTitle("遥测显示:1553慢速遥测");
        yc_slowspeed->showMaximized();
        break;
    case 2:
        ui->groupBox_ycname->setTitle("遥测显示:1553打包遥测");
        yc_packspeed->showMaximized();
        break;
    case 10:
        ui->groupBox_ycname->setTitle("遥测显示:canC81遥测");
        yc_canc81->showMaximized();
        viewF=false;
        break;
    case 20:
        ui->groupBox_ycname->setTitle("遥测显示:AD电压遥测");
        yc_ad->showMaximized();
        break;
    case 21:
        ui->groupBox_ycname->setTitle("遥测显示:RS422电平接收");
        yc_rs422_rec->showMaximized();
        viewF=false;
        break;
    default:
        break;
    }
    //是否隐藏单机选择
    for(int i=0;i<ui->horizontalLayout_2->count();++i){
        QWidget* w=ui->horizontalLayout_2->itemAt(i)->widget();
        if(w!=NULL)
            w->setVisible(viewF);
    }
    return;
}

//双击跳转界面
void YcView::on_m_yctree_list_doubleClicked(const QModelIndex &index)
{
    QString str =ui->m_yctree_list->model()->itemData(index).values()[0].toString();
    str = str.left(str.indexOf(":"));
    int page_index = str.toUInt();
    if (page_index == 0) return;
    // 先隐藏所有页面然后显示选中的页面
    Hide_view();
    Show_view(page_index);
}

//单机1遥测
void YcView::on_radioButton_dj1YC_clicked(bool checked)
{
    if(checked)
    {
        yc_slowspeed->Outslow_dj=0;
        yc_packspeed->Outpack_dj=0;
        yc_ad->Outpack_dj=0;

    }
}
//单机2遥测
void YcView::on_radioButton_dj2YC_clicked(bool checked)
{
    if(checked)
    {
        yc_slowspeed->Outslow_dj=1;
        yc_packspeed->Outpack_dj=1;
        yc_ad->Outpack_dj=1;

    }
}
//单机3遥测
void YcView::on_radioButton_dj3YC_clicked(bool checked)
{
    if(checked)
    {
        yc_slowspeed->Outslow_dj=2;
        yc_packspeed->Outpack_dj=2;
        yc_ad->Outpack_dj=2;

    }
}
//单机4遥测
void YcView::on_radioButton_dj4YC_clicked(bool checked)
{
    if(checked)
    {
        yc_slowspeed->Outslow_dj=3;
        yc_packspeed->Outpack_dj=3;
        yc_ad->Outpack_dj=3;

    }
}
