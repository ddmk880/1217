#include "TaskView.h"
#include <QDebug>

#include "mainwindow.h"
#include "ui_TaskView.h"


extern CardCtrl_1553B* Card_1553Can;

TaskView::TaskView(QWidget* parent) : QWidget(parent), ui(new Ui::TaskView) {
    ui->setupUi(this);
    Init_View_Main();
    Init_View_Sub();

    //连接函数
    RapidConnet();
    //千兆网发送函数
    trillionConnet();

    ui->checkBox_DJ_2->setStyleSheet("color:rgb(135,0,25)");//单机2标志
    ui->checkBox_DJ_3->setStyleSheet("color:rgb(65,70,200)");//单机3标志
    ui->checkBox_DJ_4->setStyleSheet("color:rgb(15,210,70)");//单机4标志
    ui->checkBox_DJ_all->setStyleSheet("color:rgb(140,50,140)");//单机全选标志
    //ui->checkBox_DJ_all->setStyleSheet("background-color:rgb(140,50,140)");

}

TaskView::~TaskView() {
    delete pview_busclass;
    delete pview_buspower;
    delete pview_overnote;
    delete pview_subtrillion;
    delete Filesend;
    delete pview_incontrol;
    delete pview_incontrol_2;
    delete pview_mayrffront;
    delete pview_maygsl;
    delete pview_beamcontrol;
    delete pveiw_tc_spi;
    delete pview_recohigh;
    delete pview_recohigh2;
    delete pview_can_L;
    delete pview_can_sxku;
    delete pview_can_front;
    delete pview_uptask;
    delete pview_modecontrl;
    delete pview_boardBC;
    delete pview_boardRT;
    delete device_1466;
    delete yxq_cr;
    delete auto_UDPcontrl;

    delete ui;
}

QVector<int> TaskView::Obj_ID()
{
    QVector<int>tmp;
    if(ui->checkBox_DJ_1->isChecked())tmp.append(0);
    if(ui->checkBox_DJ_2->isChecked())tmp.append(1);
    if(ui->checkBox_DJ_3->isChecked())tmp.append(2);
    if(ui->checkBox_DJ_4->isChecked())tmp.append(3);
    if(ui->checkBox_DJ_all->isChecked())tmp.append(4);

    return tmp;
}

void TaskView::RapidConnet()
{
    //连接rapidio发送
    card_rio=new CardCtrl_RapidIO;
    qthread_send=new QThread;
    card_rio->moveToThread(qthread_send);
    connect(card_rio,&CardCtrl_RapidIO::send_jxjd,pview_overnote,&subsrio_overnote::get_jxjd);//解析进度条
    connect(pview_overnote,&subsrio_overnote::send_riodata,card_rio,&CardCtrl_RapidIO::Send_qtSrio);//发送函数
    connect(pview_overnote,&subsrio_overnote::send_riodata,this,[=](){
        qthread_send->start();
    });
    connect(card_rio,&CardCtrl_RapidIO::qthfinish,this,[=]{//发送线程销毁
        qthread_send->quit();
        qthread_send->wait();
        qDebug()<<"endl";
    });
    connect(this,&TaskView::destroyed,this,[=](){//发送线程销毁

        qthread_send->quit();
        qthread_send->wait();

    });
    //连接rapidio收数
    card_rio_rec=new CardCtrl_RapidIO;
    qthread_rec=new QThread;
    card_rio_rec->moveToThread(qthread_rec);
    connect(pview_overnote,&subsrio_overnote::rec_riodata,card_rio_rec,&CardCtrl_RapidIO::Get_qtSrio);//发送函数
    connect(pview_overnote,&subsrio_overnote::rec_riodata,this,[=](){
        qthread_rec->start();
    });
    connect(pview_overnote,&subsrio_overnote::finshrec_riodata,this,[=](){//停止发送函数

        card_rio_rec->Rec_flag=false;
        qthread_rec->quit();
        qthread_rec->wait();
    });
    connect(pview_overnote,&subsrio_overnote::reset_srio,this,[=](){//重新初始化

        card_rio_rec->Init_PapidIO();
        qthread_rec->quit();
        qthread_rec->wait();
    });
    connect(this,&TaskView::destroyed,this,[=](){//发送线程销毁

        qthread_rec->quit();
        qthread_rec->wait();

    });
}

//千兆网连接
void TaskView::trillionConnet()
{
    //千兆网上注
    Filesend=new File_sendQthread();
    QThread* qthread_qz=new QThread();
    Filesend->moveToThread(qthread_qz);
    connect(pview_subtrillion,&subtrillion_overnote::send1,Filesend,&File_sendQthread::send_UDP);//udp发送函数
    connect(pview_subtrillion,&subtrillion_overnote::send_thre,Filesend,&File_sendQthread::sendThr_UDP);//udp发送函数(漏帧上注)
    connect(Filesend,&File_sendQthread::send_qzjxjd,pview_subtrillion,&subtrillion_overnote::get_jxjd);//udp解析进度条
    connect(Filesend,&File_sendQthread::send_frame,pview_subtrillion,&subtrillion_overnote::get_farme);//udp发送帧数
    qthread_qz->start();

    //1553上注
    QThread* sendthread_1553up=new QThread();
    Card_1553Can->moveToThread(sendthread_1553up);
    connect(pview_subtrillion, &subtrillion_overnote::send2,Card_1553Can, &CardCtrl_1553B::Send_Updata_1553);//1553上注发送函数
    connect(pview_subtrillion, &subtrillion_overnote::send_order,Card_1553Can, &CardCtrl_1553B::OnceSend_Data);//1553上注界面指令发送
    connect(pview_subtrillion, &subtrillion_overnote::send_1553upStop,Card_1553Can, &CardCtrl_1553B::Stop_1553UP);//1553停止上


    connect(Card_1553Can, &CardCtrl_1553B::send_1553upjxjd,pview_subtrillion,&subtrillion_overnote::get_jxjd);//1553解析进度条
    connect(Card_1553Can, &CardCtrl_1553B::send_frame,pview_subtrillion,&subtrillion_overnote::get_farme);//udp发送帧数
    sendthread_1553up->start();

    connect(this,&TaskView::destroyed,this,[=](){//发送线程销毁

        qthread_qz->quit();
        qthread_qz->wait();
        sendthread_1553up->quit();
        sendthread_1553up->wait();

    });

}


void TaskView::Init_View_Main() {
    // 初始化可选任务页tree
    model_tree_list = new QStandardItemModel;
    // 添加根节点上注任务///////////////////////////////////////////////////
    QStandardItem* root_uptask = new QStandardItem("上注数据指令");
    // 一级子节点
    QList<QStandardItem*> root_uptask_row;
    root_uptask_row.append(new QStandardItem("11:上注任务"));
    root_uptask_row.append(new QStandardItem("13:上注参数"));
    // 二级子节点
    QStandardItem* root_1553_22 = new QStandardItem("上注指令类");
    QList<QStandardItem*> root_1553_2row2;
    root_1553_2row2.append(new QStandardItem("1:总线指令"));
    root_1553_2row2.append(new QStandardItem("2:电源指令"));
    root_1553_2row2.append(new QStandardItem("3:管控指令(一)"));
    root_1553_2row2.append(new QStandardItem("6:管控指令(二)"));
    root_1553_2row2.append(new QStandardItem("4:管控指令(三)"));
    root_1553_2row2.append(new QStandardItem("8:管控sxku频段"));
    root_1553_2row2.append(new QStandardItem("5:管控可重构射频前端"));
    root_1553_2row2.append(new QStandardItem("10:透传c指令高算力(一)"));
    root_1553_2row2.append(new QStandardItem("17:透传c指令高算力(二)"));
    root_1553_2row2.append(new QStandardItem("12:透传c指令L频段"));
    root_1553_2row2.append(new QStandardItem("16:透传c指令SXKu频段"));
    root_1553_2row2.append(new QStandardItem("18:透传c指令射频前端"));
    root_1553_2row2.append(new QStandardItem("14:透传c指令SPI"));

    root_1553_22->appendRows(root_1553_2row2);

    root_uptask->appendRows(root_uptask_row);
    root_uptask->appendRow(root_1553_22);
    //其他数据指令/////////////////////////////////////////////////////////
    QStandardItem* root_other = new QStandardItem("其他数据指令");
    //一级子节点
    QList<QStandardItem*> root_other_row;
    root_other_row.append(new QStandardItem("15:模式控制指令"));

    root_other->appendRows(root_other_row);


    // 添加根节点SRIO总线//////////////////////////////////////////////////
    QStandardItem* root_QZ_SRIO = new QStandardItem("SRIO/千兆网总线");
    //一级子节点
    QList<QStandardItem*> root_SRIO_row;
    root_SRIO_row.append(new QStandardItem("20:RapidIo上注/接收"));
    root_SRIO_row.append(new QStandardItem("21:千兆网/1553B上注"));

    root_QZ_SRIO->appendRows(root_SRIO_row);
    // 添加根节点广播设置///////////////////////////////////////////////////
    QStandardItem* root_board = new QStandardItem("广播设置");
    // 一级子节点
    QList<QStandardItem*> root_board_row;
    root_board_row.append(new QStandardItem("30:BC广播"));
    root_board_row.append(new QStandardItem("31:RT广播"));

    root_board->appendRows(root_board_row);

    // 添加根节点设备控制///////////////////////////////////////////////////
    QStandardItem* root_device = new QStandardItem("设备控制");
    // 一级子节点
    QList<QStandardItem*> root_device_row;
    root_device_row.append(new QStandardItem("41:信号源控制1466"));
    root_device_row.append(new QStandardItem("42:自动化UDP"));
    root_device_row.append(new QStandardItem("43:静态移相器控制"));

    root_device->appendRows(root_device_row);


    //根目录
    model_tree_list->appendRow(root_uptask);
    model_tree_list->appendRow(root_other);
    model_tree_list->appendRow(root_QZ_SRIO);
    model_tree_list->appendRow(root_board);
    model_tree_list->appendRow(root_device);
    ui->m_tree_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tree_list->setHeaderHidden(true);
    ui->m_tree_list->setSelectionBehavior(QTreeView::SelectItems);
    ui->m_tree_list->setModel(model_tree_list);
    ui->m_tree_list->setItemsExpandable(true);
    ui->m_tree_list->expandAll();

}
/*************************************************
 <函数名>   Init_View_Sub
 <概要说明>    无
 <详细说明>    无

 <作    者>   zm
 <时    间>   2023-03-22
 <修    改>
**************************************************/
void TaskView::Init_View_Sub() {
    // 初始化子页面对象

    ui->gBox_TaskView->setTitle("上注任务(0088H)");//默认初始界面


    //1553总线指令类界面 1
    pview_busclass=new sub1553_busclass();
    ui->verticalLayout->addWidget(pview_busclass);
    connect(pview_busclass, &sub1553_busclass::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);//连接发送成功弹窗
    connect(pview_busclass, &sub1553_busclass::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);//连接发送失败弹窗
    connect(pview_busclass, &sub1553_busclass::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);//发送容器数据到主界面
    pview_busclass->hide();//隐藏(不隐藏就显示)

    //1553总线指令类界面2
    pview_buspower=new sub1553_busPower();
    ui->verticalLayout->addWidget(pview_buspower);
    connect(pview_buspower, &sub1553_busPower::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);//连接发送成功弹窗
    connect(pview_buspower, &sub1553_busPower::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);//连接发送失败弹窗
    connect(pview_buspower, &sub1553_busPower::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);//发送容器数据到主界面
    pview_buspower->hide();//隐藏(不隐藏就显示)


    // 总线注数类CAN//////////////////////////////////////////////////////////////////
    // 1553上注指令类：综合管控单元 3
    pview_incontrol=new sub1553_gkcontrol();
    ui->verticalLayout->addWidget(pview_incontrol);
    connect(pview_incontrol, &sub1553_gkcontrol::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_incontrol, &sub1553_gkcontrol::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_incontrol, &sub1553_gkcontrol::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_incontrol->hide();

    // 1553上注指令类：综合管控单元 6
    pview_incontrol_2=new sub1553_gkcontrol2();
    ui->verticalLayout->addWidget(pview_incontrol_2);
    connect(pview_incontrol_2, &sub1553_gkcontrol2::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_incontrol_2, &sub1553_gkcontrol2::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_incontrol_2, &sub1553_gkcontrol2::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_incontrol_2->hide();


   // 1553上注指令类：可重构射频前端 5
    pview_mayrffront=new sub1553_gkmayrffront();
    ui->verticalLayout->addWidget(pview_mayrffront);
    connect(pview_mayrffront, &sub1553_gkmayrffront::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_mayrffront, &sub1553_gkmayrffront::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_mayrffront, &sub1553_gkmayrffront::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_mayrffront->hide();
   // 1553上注指令类：可重构高算力平台 4
    pview_maygsl=new sub1553_gkmaygsl();
    ui->verticalLayout->addWidget(pview_maygsl);
    connect(pview_maygsl, &sub1553_gkmaygsl::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_maygsl, &sub1553_gkmaygsl::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_maygsl, &sub1553_gkmaygsl::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_maygsl->hide();


    // 1553上注指令类：SXKu频段波束控制单元 8
    pview_beamcontrol = new sub1553_gksxkucontrol();
    ui->verticalLayout->addWidget(pview_beamcontrol);
    connect(pview_beamcontrol, &sub1553_gksxkucontrol::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_beamcontrol, &sub1553_gksxkucontrol::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_beamcontrol, &sub1553_gksxkucontrol::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_beamcontrol->hide();

    // 1553上注指令类：透传can内部 10
    pview_recohigh = new sub1553_tccontrol();
    ui->verticalLayout->addWidget(pview_recohigh);
    connect(pview_recohigh, &sub1553_tccontrol::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_recohigh, &sub1553_tccontrol::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_recohigh, &sub1553_tccontrol::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_recohigh->hide();
    // 1553上注指令类：透传can内部 17
    pview_recohigh2 = new sub1553_tccontrol2();
    ui->verticalLayout->addWidget(pview_recohigh2);
    connect(pview_recohigh2, &sub1553_tccontrol2::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_recohigh2, &sub1553_tccontrol2::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_recohigh2, &sub1553_tccontrol2::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_recohigh2->hide();

    //can高算力平台1、2控件关联
    connect(pview_recohigh, &sub1553_tccontrol::se_arg1,pview_recohigh2, &sub1553_tccontrol2::re_arg2);
    connect(pview_recohigh2, &sub1553_tccontrol2::se_arg2,pview_recohigh, &sub1553_tccontrol::re_arg1);

    // CAN协议指令(内部)： L频段数字综合单元12
    pview_can_L = new sub1553_tccontrol_L();
    ui->verticalLayout->addWidget(pview_can_L);
    connect(pview_can_L, &sub1553_tccontrol_L::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_can_L, &sub1553_tccontrol_L::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_can_L, &sub1553_tccontrol_L::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_can_L->hide();
    // CAN协议指令(内部):SXKu频段波束控制器16
    pview_can_sxku = new sub1553_tccontrol_sxku();
    ui->verticalLayout->addWidget(pview_can_sxku);
    connect(pview_can_sxku, &sub1553_tccontrol_sxku::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_can_sxku, &sub1553_tccontrol_sxku::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_can_sxku, &sub1553_tccontrol_sxku::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_can_sxku->hide();

    // CAN协议指令(内部):可重构射频前端
    pview_can_front = new sub1553_tcmayrffront();
    ui->verticalLayout->addWidget(pview_can_front);
    connect(pview_can_front, &sub1553_tcmayrffront::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_can_front, &sub1553_tcmayrffront::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_can_front, &sub1553_tcmayrffront::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_can_front->hide();

    // 1553上注指令类：透传spi 14
    pveiw_tc_spi = new sub1553_tccontrol_spi();
    ui->verticalLayout->addWidget(pveiw_tc_spi);
    connect(pveiw_tc_spi, &sub1553_tccontrol_spi::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pveiw_tc_spi, &sub1553_tccontrol_spi::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pveiw_tc_spi, &sub1553_tccontrol_spi::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pveiw_tc_spi->hide();

    // 上注任务
    pview_uptask = new sub1553_Overheadtask();
    ui->verticalLayout->addWidget(pview_uptask);
    connect(pview_uptask, &sub1553_Overheadtask::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    //pview_uptask->hide();

    // 模式控制指令
    pview_modecontrl = new sub1553_modecontrl();
    ui->verticalLayout->addWidget(pview_modecontrl);
    connect(pview_modecontrl, &sub1553_modecontrl::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_modecontrl->hide();



    // SRIO总线
    // RipidIO文件上注 20
    pview_overnote = new subsrio_overnote();
    ui->verticalLayout->addWidget(pview_overnote);
    connect(pview_overnote, &subsrio_overnote::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_overnote, &subsrio_overnote::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_overnote, &subsrio_overnote::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_overnote->hide();

    // 千兆网文件上注 21
    pview_subtrillion = new subtrillion_overnote();
    ui->verticalLayout->addWidget(pview_subtrillion);
    connect(pview_subtrillion, &subtrillion_overnote::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);
    connect(pview_subtrillion, &subtrillion_overnote::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);
    connect(pview_subtrillion, &subtrillion_overnote::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);
    pview_subtrillion->hide();

    // BC广播30
    pview_boardBC = new subboard_bc();
    ui->verticalLayout->addWidget(pview_boardBC);
    pview_boardBC->hide();
    // RT广播31
    pview_boardRT = new subboard_rt();
    ui->verticalLayout->addWidget(pview_boardRT);
    pview_boardRT->hide();

    //信号源1466
    device_1466=new signal_1466();
    ui->verticalLayout->addWidget(device_1466);
    connect(device_1466, &signal_1466::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);//连接发送成功弹窗
    connect(device_1466, &signal_1466::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);//连接发送失败弹窗
    connect(device_1466, &signal_1466::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);//发送容器数据到主界面
    device_1466->hide();//隐藏(不隐藏就显示)

    //信号源1466
    yxq_cr=new yxq_contrl();
    ui->verticalLayout->addWidget(yxq_cr);
    yxq_cr->hide();//隐藏(不隐藏就显示)

    //自动化UDP转发
    auto_UDPcontrl=new auto_udp();
    ui->verticalLayout->addWidget(auto_UDPcontrl);
    connect(auto_UDPcontrl, &auto_udp::success_snack,(MainWindow*)P_MAIN_WIN, &MainWindow::success_snack_slot);//连接发送成功弹窗
    connect(auto_UDPcontrl, &auto_udp::fail_snack, (MainWindow*)P_MAIN_WIN,&MainWindow::fail_snack_slot);//连接发送失败弹窗
    connect(auto_UDPcontrl, &auto_udp::Add_Order_ToList,(MainWindow*)P_MAIN_WIN, &MainWindow::add_order_toList);//发送容器数据到主界面
    connect(auto_UDPcontrl, &auto_udp::send_order,Card_1553Can, &CardCtrl_1553B::OnceSend_Data);//udp转发1553指令发送
    connect(auto_UDPcontrl, &auto_udp::send_sTime,Card_1553Can, &CardCtrl_1553B::udp_changeTime);//udp转发星时发送
    auto_UDPcontrl->hide();//隐藏(不隐藏就显示)






}

//先隐藏界面
void TaskView::Hide_view()
{
    pview_overnote->hide();
    pview_subtrillion->hide();
    pview_busclass->hide();
    pview_buspower->hide();
    pview_incontrol->hide();
    pview_incontrol_2->hide();
    pview_mayrffront->hide();
    pview_maygsl->hide();
    pview_beamcontrol->hide();
    pview_recohigh->hide();
    pview_recohigh2->hide();
    pview_can_L->hide();
    pview_can_sxku->hide();
    pview_can_front->hide();
    pveiw_tc_spi->hide();
    pview_boardBC->hide();
    pview_boardRT->hide();
    pview_uptask->hide();
    pview_modecontrl->hide();
    device_1466->hide();
    yxq_cr->hide();
    auto_UDPcontrl->hide();

}

//显示界面
void TaskView::Show_view(int index)
{

    bool viewF=true;//1553指令发送单机选择栏界面
    int page_index=index;

    switch (page_index) {
    case 1:
        ui->gBox_TaskView->setTitle("总线指令类");
        pview_busclass->showMaximized();
        break;
    case 2:
        ui->gBox_TaskView->setTitle("电源指令");
        pview_buspower->showMaximized();
        break;
    case 3:
        ui->gBox_TaskView->setTitle("上注指令类：综合管控单元(0086H)");
        pview_incontrol->showMaximized();
        break;
    case 6:
        ui->gBox_TaskView->setTitle("上注指令类：综合管控单元2");
        pview_incontrol_2->showMaximized();
        break;
    case 4:
        ui->gBox_TaskView->setTitle("上注指令类：综合管控单元3");
        pview_maygsl->showMaximized();
        break;
    case 5:
        ui->gBox_TaskView->setTitle("上注指令类：可重构射频前端");
        pview_mayrffront->showMaximized();
        break;
    case 8:
        ui->gBox_TaskView->setTitle("上注指令类：SXku频段波束控制");
        pview_beamcontrol->showMaximized();
        break;
    case 10:
        ui->gBox_TaskView->setTitle("CAN透传:可重构高算力平台1/2(0081H,0082H)");
        pview_recohigh->showMaximized();
        break;
    case 17:
        ui->gBox_TaskView->setTitle("CAN透传:可重构高算力平台2/2(0081H,0082H)");
        pview_recohigh2->showMaximized();
        break;
    case 11:
        ui->gBox_TaskView->setTitle("上注任务(0088H)");
        pview_uptask->showMaximized();
        break;
    case 12:
        ui->gBox_TaskView->setTitle("CAN透传：L频段数字综合单元(0089H)");
        pview_can_L->showMaximized();
        break;
    case 16:
        ui->gBox_TaskView->setTitle("CAN透传：SXKu频段波速控制器(008AH)");
        pview_can_sxku->showMaximized();
        break;
    case 18:
        ui->gBox_TaskView->setTitle("CAN透传：可重构射频前端(0085H)");
        pview_can_front->showMaximized();
        break;

    case 14:
        ui->gBox_TaskView->setTitle("透传指令SPI协议(0083H,0084H)");
        pveiw_tc_spi->showMaximized();
        break;
    case 15:
        ui->gBox_TaskView->setTitle("模式控制指令");
        pview_modecontrl->showMaximized();
        break;
    case 20:
        ui->gBox_TaskView->setTitle("SRIO总线：RapidIO文件上注");
        pview_overnote->showMaximized();
        viewF=false;
        break;
    case 21:
        ui->gBox_TaskView->setTitle("千兆网总线：千兆网文件上注");
        pview_subtrillion->showMaximized();
        break;
    case 30:
        ui->gBox_TaskView->setTitle("BC广播设置");
        pview_boardBC->showMaximized();
        viewF=false;
        break;
    case 31:
        ui->gBox_TaskView->setTitle("RT广播设置");
        pview_boardRT->showMaximized();
        viewF=false;
        break;
    case 41:
        ui->gBox_TaskView->setTitle("信号源控制1466");
        device_1466->showMaximized();
        viewF=false;
        break;
    case 42:
        ui->gBox_TaskView->setTitle("自动化UDP转发");
        auto_UDPcontrl->showMaximized();
        break;
    case 43:
        ui->gBox_TaskView->setTitle("静态移相器控制");
        yxq_cr->showMaximized();
        viewF=false;
        break;
    default:
        break;
    }

    //是否隐藏1553发送单机选择
    for(int i=0;i<ui->horizontalLayout_2->count();++i){
        QWidget* w=ui->horizontalLayout_2->itemAt(i)->widget();
        if(w!=NULL)
            w->setVisible(viewF);
    }
    return;

}


/*************************************************
 <函数名>   on_m_tree_list_doubleClicked
 <概要说明>    无
 <详细说明>    无

 <作    者>   zm
 <时    间>   2023-03-22
 <修    改>
**************************************************/
//双击跳转界面
void TaskView::on_m_tree_list_doubleClicked(const QModelIndex& index) {
    QString str =ui->m_tree_list->model()->itemData(index).values()[0].toString();
    str = str.left(str.indexOf(":"));
    int page_index = str.toUInt();
    if (page_index == 0) return;
    // 先隐藏所有页面然后显示选中的页面
    Hide_view();
    Show_view(page_index);
}

//指令翻译回显到指定界面控件
void TaskView::Transfer_to_subView(const QVariant varData) {

    Order_List_Object rec_data = varData.value<Order_List_Object>();
    if(rec_data.page_id==0)return;
    Hide_view();
    Show_view(rec_data.page_id);
    switch (rec_data.page_id) {
    case 1:
        pview_busclass->Reverse_Data(rec_data);
        break;
    case 20:
        pview_overnote->Reverse_Data(rec_data);
        break;
    default:
        break;
    }
}

//指令单机标志-全选
void TaskView::on_checkBox_DJ_all_clicked(bool checked)
{
    if(checked)//勾选了单机全选，单独选择屏蔽
    {
        ui->checkBox_DJ_1->setEnabled(0);
        ui->checkBox_DJ_2->setEnabled(0);
        ui->checkBox_DJ_3->setEnabled(0);
        ui->checkBox_DJ_4->setEnabled(0);

        ui->checkBox_DJ_1->setChecked(0);
        ui->checkBox_DJ_2->setChecked(0);
        ui->checkBox_DJ_3->setChecked(0);
        ui->checkBox_DJ_4->setChecked(0);

        //千兆网上注单机标志
        for (int i=0;i<4;i++) {
            pview_subtrillion->check_dj[i]=false;
            auto_UDPcontrl->check_dj[i]=false;
        }
        pview_subtrillion->check_dj[4]=true;
        auto_UDPcontrl->check_dj[4]=true;
    }
    else
    {
        ui->checkBox_DJ_1->setEnabled(1);
        ui->checkBox_DJ_2->setEnabled(1);
        ui->checkBox_DJ_3->setEnabled(1);
        ui->checkBox_DJ_4->setEnabled(1);

        ui->checkBox_DJ_1->setChecked(0);
        ui->checkBox_DJ_2->setChecked(0);
        ui->checkBox_DJ_3->setChecked(0);
        ui->checkBox_DJ_4->setChecked(0);

        //千兆网上注单机标志
        for (int i=0;i<4;i++) {
            pview_subtrillion->check_dj[i]=false;
            auto_UDPcontrl->check_dj[i]=false;
        }
        pview_subtrillion->check_dj[4]=false;
        auto_UDPcontrl->check_dj[4]=false;
    }
}

void TaskView::check1234()
{
    if(ui->checkBox_DJ_1->isChecked()||ui->checkBox_DJ_2->isChecked()
            ||ui->checkBox_DJ_3->isChecked()||ui->checkBox_DJ_4->isChecked())//勾选了单独选择，单机全选屏蔽
    {
        ui->checkBox_DJ_all->setEnabled(0);
        ui->checkBox_DJ_all->setChecked(0);
    }
    else
    {
        ui->checkBox_DJ_all->setEnabled(1);
        ui->checkBox_DJ_all->setChecked(0);
    }
}
//指令单机标志-单机1
void TaskView::on_checkBox_DJ_1_clicked(bool checked)
{
    check1234();
    //千兆网上注单机标志
    pview_subtrillion->check_dj[0]=checked;
    auto_UDPcontrl->check_dj[0]=checked;
}
//指令单机标志--单机2
void TaskView::on_checkBox_DJ_2_clicked(bool checked)
{
    check1234();
    //千兆网上注单机标志
    pview_subtrillion->check_dj[1]=checked;
    auto_UDPcontrl->check_dj[1]=checked;
}
//指令单机标志--单机3
void TaskView::on_checkBox_DJ_3_clicked(bool checked)
{
    check1234();
    //千兆网上注单机标志
    pview_subtrillion->check_dj[2]=checked;
    auto_UDPcontrl->check_dj[2]=checked;
}
//指令单机标志--单机4
void TaskView::on_checkBox_DJ_4_clicked(bool checked)
{
    check1234();
    //千兆网上注单机标志
    pview_subtrillion->check_dj[3]=checked;
    auto_UDPcontrl->check_dj[3]=checked;
}
