#include "mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "ui_mainwindow.h"
#include <math.h>
#include <algorithm>
#include <QtGlobal>
#include"include/zlgcan_x64/zlgcan.h"
#include <QValidator>
#include <QFileDialog>
#include <QSettings>
#include <math.h>
#define ORI_LEN 238 //原始数据一包最大长度
QMainWindow* P_MAIN_WIN;
CardCtrl_1553B* Card_1553Can;
using namespace QXlsx;
using namespace std;
uint send_div;
extern bool re_while;//can循环收数标志
int picNum=1;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    P_MAIN_WIN = this;




    //停靠窗口输出控件，创建浮动窗口
    m=new QMainWindow();
    //m->setMaximumHeight(170);
    //ui->dockWidget_log->showMaximized();
    ui->verticalLayout->addWidget(m);
    //使用 addDockWidget 方法, 把浮动窗口加入到子窗口中
    m->addDockWidget(Qt::TopDockWidgetArea,ui->dockWidget_log);
    mClass_label=new mylabel(m);
    mClass_label=ui->label_mgif;
    // 连接信号槽 左键单机切换Gif
    connect(mClass_label,SIGNAL(pressClicked()),this,SLOT(gif_change()));
    connect(mClass_label,SIGNAL(pressClicked_right()),this,SLOT(gif_change_right()));

    //pps发送测试按钮
    //this->setWindowFlags(this->windowFlags()|Qt::WindowMinMaxButtonsHint);
    ui->pushButtonxxx->setVisible(0);//测试按钮
    //初始化硬件设备
    Init_HardDevices();
    //主界面控件
    Init_Main_Ui();
    //子界面控件
    Init_Sub_Page();
    Init_Other_Ui();

    //初始化遥测子界面
    Init_Yc_Subview();

    //gif图片
    gifGround();
    //初始化任务列表存储
    order_data_list.clear();
    qRegisterMetaType<Order_List_Object>("Order_List_Object");
    qRegisterMetaType<DC_test>("DC_test");
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));//指令定时发送
    //timer->start(1000);

    //主界面内嵌游戏界面
    m_GamesInit();


    //右边界面（can接收，信号源控制）
    ui->tabWidget_2->setCurrentIndex(0);
    //左边快捷操作界面
    ui->m_tb_device->setCurrentIndex(0);
    //信号源控制初始化
    signal_init();

    //指令数据库初始化
    orderDB_init();
    //1553目标单机收地址
    OBJ_Addr["单机1"]=0;
    OBJ_Addr["单机2"]=1;
    OBJ_Addr["单机3"]=2;
    OBJ_Addr["单机4"]=3;
    OBJ_Addr["全选"]=4;
    //单机BUS选择颜色
    ui->checkBox_1553BCH2->setStyleSheet("color:rgb(135,0,25)");//BUS1单机2标志
    ui->checkBox_1553BCH3->setStyleSheet("color:rgb(65,70,200)");//BUS2单机3标志
    ui->checkBox_1553BCH4->setStyleSheet("color:rgb(15,210,70)");//BUS3单机4标志

    //can接收地址
    mRe_Addr[0]=0x10;//管控机
    mRe_Addr[1]=0x20;//可重构算力平台1
    mRe_Addr[2]=0x21;//可重构算力平台2
    mRe_Addr[3]=0x22;//可重构射频前端
    mRe_Addr[4]=0x23;//L频段数字综合单元
    mRe_Addr[5]=0x24;//SXKu频段波束控制器
    mRe_Addr[6]=0xFF;//广播地址

    Cycle_sendFlag=false;
    net_init=false;

    startOder_Tim=false;

    //存储封装后的指令
    STR_PackOder="";
    //启动默认读取指定路径表格
    Get_boardFirst();

    //指令类型，数字对应汉字类型
    //0081H	上注CAN透传指令-高算力平台1
    //0082H	上注CAN透传指令-高算力平台2
    //0083H	上注SPI透传指令-高算力平台1
    //0084H	上注SPI透传指令-高算力平台2
    //0085H	上注CAN透传指令-可重构射频前端
    //0086H	上注管控指令
    //0088H	上注任务
    //0089H	上注CAN透传指令-L频段数字综合单元
    //008AH	上注CAN透传指令-SXKu频段波速控制器
    //0x0010	网络发送文件
    //0x0011	网络接收文件
    //0x0012	网络停止发送
    //0x0013	网络停止接收
    //0x0014	总线接收文件
    //0x0015	总线停止接收

    Ord_Kind[0]="无";
    Ord_Kind[1]="总线指令";
    Ord_Kind[2]="上注指令0086";
    Ord_Kind[3]="上注指令0088";
    Ord_Kind[4]="上注指令0081";
    Ord_Kind[5]="上注指令0082";
    Ord_Kind[6]="模式控制指令";
    Ord_Kind[7]="上注指令0083";
    Ord_Kind[8]="上注指令0084";
    Ord_Kind[9]="Can指令";
    Ord_Kind[10]="星时指令";
    Ord_Kind[11]="上注指令0089";
    Ord_Kind[12]="上注指令008A";
    Ord_Kind[13]="上注指令0085";

    Ord_Kind[14]="网络发送文件0010";
    Ord_Kind[15]="网络接收文件0011";//
    Ord_Kind[16]="网络停止发送0012";
    Ord_Kind[17]="网络停止接收0013";//
    Ord_Kind[18]="总线接收文件0014";//
    Ord_Kind[19]="总线停止接收0015";//
    Ord_Kind[20]="信号源指令";//

    ////////////////////////////
    Ord_Kind2[""]=0;
    Ord_Kind2["总线指令"]=1;
    Ord_Kind2["上注指令0086"]=2;
    Ord_Kind2["上注指令0088"]=3;
    Ord_Kind2["上注指令0081"]=4;
    Ord_Kind2["上注指令0082"]=5;
    Ord_Kind2["模式控制指令"]=6;
    Ord_Kind2["上注指令0083"]=7;
    Ord_Kind2["上注指令0084"]=8;
    Ord_Kind2["Can指令"]=9;
    Ord_Kind2["星时指令"]=10;
    Ord_Kind2["上注指令0089"]=11;
    Ord_Kind2["上注指令008A"]=12;
    Ord_Kind2["上注指令0085"]=13;

    Ord_Kind2["网络发送文件0010"]=14;
    Ord_Kind2["网络接收文件0011"]=15;
    Ord_Kind2["网络停止发送0012"]=16;
    Ord_Kind2["网络停止接收0013"]=17;
    Ord_Kind2["总线接收文件0014"]=18;
    Ord_Kind2["总线停止接收0015"]=19;
    Ord_Kind2["信号源指令"]=20;

    //信号源信号样式
    Sig_type[0]="AM";
    Sig_type[1]="FM";
    Sig_type[2]="ASK";
    Sig_type[3]="BPSK";
    Sig_type[4]="QPSK";
    Sig_type[5]="AQPSk";
    Sig_type[6]="OQPSk";
    Sig_type[7]="8PSK";
    Sig_type[8]="16QAM";
    Sig_type[9]="MSK";
    Sig_type[10]="2FSK";
    Sig_type[11]="4FSK";
    Sig_type[12]="8FSK";
    Sig_type[13]="16FSK";

    for (uint i=0;i<Sig_type.size();i++) {
        ui->comboBox_type->addItem(Sig_type[i]);
    }

}

MainWindow::~MainWindow() {


    if(timer->isActive())
    {
        timer->stop();
    }
    timer->deleteLater();

    delete Card_1553Can;
    Card_1553Can=nullptr;
    delete Card_plusetime;
    delete Card_RapidIO;
    delete Card_AD_OC;
    delete Card_can;
    delete signalConrtl[0];
    delete signalConrtl[1];

    //delete Card_Net;
    if(net_init)PA_PCIe_1501_NET_Close(send_div);

    delete p_view_task;
    delete p_monitor;
    delete p_database;

    delete yc_slow;//慢速遥测
    delete yc_pack;//打包遥测
    delete yc_canc81;//打包遥测
    delete yc_ad;//ad电压遥测
    delete yc_rs422_rec;//rs422电平接收
    delete p_view_yc;
    delete ui;
}

// 初始化界面控件
void MainWindow::Init_Main_Ui() {
    // 启动时间显示定时器
    //        QTimer* time = new QTimer(this);
    //        connect(time, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    //        time->start(1000);
    //初始化主页面上侧导航栏
    m_tab_daohang = new QtMaterialTabs();
    m_tab_daohang->addTab("数据收发");
    m_tab_daohang->addTab("指令生成");
    m_tab_daohang->addTab("遥测显示");
    m_tab_daohang->addTab("记录回放");
    m_tab_daohang->addTab("总线监视");
    ui->layout_daohang->addWidget(m_tab_daohang);
    connect(m_tab_daohang, &QtMaterialTabs::currentChanged, this,&MainWindow::tab_index_change);
    //初始化主页面上侧导航栏----隐藏游戏
    m_tab_game = new QtMaterialTabs();
    m_tab_game->addTab(" ");//游戏
    m_tab_game->setFixedWidth(5);
    ui->Layout_game->addWidget(m_tab_game);
    connect(m_tab_game, &QtMaterialTabs::currentChanged, this,&MainWindow::tab_game_change);
    //左侧系统or软件设置区控件
    // 指令任务列表
    model_list = new QStandardItemModel();
    QStringList t_name_list;
    t_name_list.clear();
    t_name_list.append("单机");
    t_name_list.append("PID");  // page_id指令生成页下标
    t_name_list.append("发送时间");
    t_name_list.append("名称");
    t_name_list.append("类型");
    t_name_list.append("长度");
    t_name_list.append("指令内容");
    model_list->setColumnCount(t_name_list.size());
    for (int i = 0; i < t_name_list.size(); i++) {
        model_list->setHeaderData(i, Qt::Horizontal, t_name_list.at(i));
    }
    ui->ui_task_list->setModel(model_list);
    //ui->ui_task_list->verticalHeader()->hide();//隐藏列表行号
    ui->ui_task_list->setColumnWidth(0, 50); // 设置序号列宽60节省界面空间
    ui->ui_task_list->setColumnWidth(1, 50);
    ui->ui_task_list->setColumnWidth(2, 70);
    ui->ui_task_list->setColumnWidth(3, 150);
    ui->ui_task_list->setColumnWidth(4, 90);
    ui->ui_task_list->setColumnWidth(5, 60);
    ui->ui_task_list->horizontalHeader()->setStretchLastSection(true);

    ui->ui_task_list->setSelectionBehavior(QAbstractItemView::SelectRows);//设定选择行为，按行选中
    //    ui->ui_task_list->setEditTriggers(QTableView::NoEditTriggers);//不可编辑
    //双击
    connect(ui->ui_task_list,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(slotRowDoubleClicked(const QModelIndex &)));
    // 发送全部按钮
    m_button_send_all_task =new QtMaterialRaisedButton("发送全部");
    m_button_send_all_task->setRole(Material::Primary);
    ui->horizontalLayout_func_button->addWidget(m_button_send_all_task);
    connect(m_button_send_all_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_sendAll);
    // 发送选中按钮
    m_button_send_one_task =new QtMaterialRaisedButton("发送选中");
    m_button_send_one_task->setRole(Material::Primary);
    ui->horizontalLayout_func_button->addWidget(m_button_send_one_task);
    connect(m_button_send_one_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_sendOne);
    // 停止按钮
    QtMaterialRaisedButton* m_button_stop_task =new QtMaterialRaisedButton("停止");
    m_button_stop_task->setRole(Material::Secondary);
    ui->horizontalLayout_func_button->addWidget(m_button_stop_task);
    connect(m_button_stop_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_Stop);
    //循环发送
    m_button_cycle_task =new QtMaterialRaisedButton("循环发送开");
    m_button_cycle_task->setRole(Material::Primary);
    ui->horizontalLayout_func_button->addWidget(m_button_cycle_task);
    connect(m_button_cycle_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_cycle);
    // 删除全部按钮
    QtMaterialRaisedButton* m_button_delete_all_task =new QtMaterialRaisedButton(" 清空");
    m_button_delete_all_task->setRole(Material::Default);
    ui->horizontalLayout_func_button->addWidget(m_button_delete_all_task);
    connect(m_button_delete_all_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_delAll);
    // 删除选中按钮
    QtMaterialRaisedButton* m_button_delete_one_task =new QtMaterialRaisedButton("删除选中行");
    m_button_delete_one_task->setRole(Material::Default);
    ui->horizontalLayout_func_button->addWidget(m_button_delete_one_task);
    connect(m_button_delete_one_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_delOne);
    // 导入按钮
    QtMaterialRaisedButton* m_button_import_task =new QtMaterialRaisedButton("导入");
    m_button_import_task->setRole(Material::Secondary);
    ui->horizontalLayout_func_button->addWidget(m_button_import_task);
    connect(m_button_import_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_import);
    // 导出按钮
    QtMaterialRaisedButton* m_button_export_task =new QtMaterialRaisedButton("导出");
    m_button_export_task->setRole(Material::Secondary);
    ui->horizontalLayout_func_button->addWidget(m_button_export_task);
    connect(m_button_export_task, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_export);

    // 单行上移
    QtMaterialRaisedButton* m_button_orderUP =new QtMaterialRaisedButton("单行上移");
    m_button_orderUP->setRole(Material::Secondary);
    ui->horizontalLayout_func_button->addWidget(m_button_orderUP);
    connect(m_button_orderUP, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_orderup);
    // 单行下移
    QtMaterialRaisedButton* m_button_orderDown =new QtMaterialRaisedButton("单行下移");
    m_button_orderDown->setRole(Material::Secondary);
    ui->horizontalLayout_func_button->addWidget(m_button_orderDown);
    connect(m_button_orderDown, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_orderdown);
    // 加头导出
    QtMaterialRaisedButton* m_button_Packexport =new QtMaterialRaisedButton("加头导出");
    m_button_Packexport->setRole(Material::Secondary);
    ui->horizontalLayout_func_button->addWidget(m_button_Packexport);
    connect(m_button_Packexport, &QtMaterialRaisedButton::clicked, this,&MainWindow::button_click_Packexport);

    // 任务列表右键菜单
    ui->ui_task_list->setContextMenuPolicy(Qt::CustomContextMenu);
    m_list_task_menu = new QMenu(ui->ui_task_list);
    m_action_goto_view = new QAction(("查看指令信息"), this);
    m_action_export = new QAction(("导出全部指令"), this);
    m_action_export2 = new QAction(("导出指令源码"), this);
    m_action_export3 = new QAction(("跳转指令页面"), this);
    m_list_task_menu->addAction(m_action_goto_view);
    m_list_task_menu->addAction(m_action_export);
    m_list_task_menu->addAction(m_action_export2);
    m_list_task_menu->addAction(m_action_export3);
    connect(ui->ui_task_list, &QWidget::customContextMenuRequested, this,&MainWindow::show_tasklist_menu);
    connect(m_action_goto_view, &QAction::triggered, this,&MainWindow::Translate_Order);
    connect(m_action_export, &QAction::triggered, this,&MainWindow::Export_order);
    connect(m_action_export2, &QAction::triggered, this,&MainWindow::Export_orderSource);
    connect(m_action_export3, &QAction::triggered, this,&MainWindow::Return_To_SubView);
    connect(model_list, &QStandardItemModel::itemChanged, this, &MainWindow::change_list_time);



}

// 初始化子页面对象指针
void MainWindow::Init_Sub_Page(){
    // 任务列表页面
    QSizePolicy sp_retain = ui->m_Vector_Widget->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    //指令页面
    ui->m_Vector_Widget->setSizePolicy(sp_retain);
    p_view_task = new TaskView(ui->m_widget_main);
    p_view_task->setVisible(false);
    connect(this, &MainWindow::Return_order_toView, p_view_task,&TaskView::Transfer_to_subView);//查看指令

    //指令页面--模式控制指令//传递内存下卸回传数据
    connect(Card_1553Can,&CardCtrl_1553B::Send_MemoryData,p_view_task->pview_modecontrl,&sub1553_modecontrl::Rec_MemoryData);

    // 数据库查询
    p_database=new DatabaseView(ui->m_widget_main);
    p_database->setHidden(true);
    //遥测显示界面
    p_view_yc=new YcView(ui->m_widget_main);
    p_view_yc->setHidden(true);
    //监视界面
    p_monitor=new MonitorView(ui->m_widget_main);
    p_monitor->setHidden(true);

}

void MainWindow::Init_Other_Ui() {
    // 初始化页面下方弹出框
    m_snackbar_success = new QtMaterialSnackbar(this);
    m_snackbar_fail = new QtMaterialSnackbar(this);
    connect(this, &MainWindow::success_snack, this,&MainWindow::success_snack_slot);
    connect(this, &MainWindow::fail_snack, this, &MainWindow::fail_snack_slot);
    m_snackbar_success->setBackgroundColor(QColor(40, 240, 40));
    m_snackbar_success->setFontSize(13);
    m_snackbar_success->setAutoHideDuration(500);
    m_snackbar_fail->setBackgroundColor(QColor(232, 40, 40));
    m_snackbar_fail->setAutoHideDuration(500);
    m_snackbar_fail->setFontSize(13);
}

//初始化硬件设备
void MainWindow::Init_HardDevices()
{
    //软件起始时间
    QDateTime tm=QDateTime::currentDateTime();
    QString tms="软件启动时间:"+tm.toString("yyyy-MM-dd hh:mm:ss");

    ui->m_output->append(tms);
    //OC初始化
    Card_AD_OC=new CardCtrl_AD_OC;
    int stats=0;
    stats+=Card_AD_OC->Card_OC_Init();
    stats+=Card_AD_OC->Card_AD_Init();
    if(stats==API_SUCCESS){
        ui->m_output->append("OC_AD板卡初始化成功");
    }
    else{
        ui->m_output->append(ChangeColor("OC_AD板卡初始化失败",1));
    }
    connect(ui->oc_push,&QPushButton::clicked,this,[=]()
    {
        Card_AD_OC->OC_cotrl(ui->occhannel->currentIndex());
        emit success_snack("设置成功");

    });
    //RapidIO板卡初始化
    Card_RapidIO=new CardCtrl_RapidIO;
    if(Card_RapidIO->Init_PapidIO()==API_SUCCESS){
        ui->m_output->append("Rapdio板卡初始化成功");
    }
    else{
        ui->m_output->append(ChangeColor("Rapdio板卡初始化失败",1));
    }

    //1553板卡初始化
    Card_1553Can=new CardCtrl_1553B;
    Card_plusetime=new Pluse_1553Time();
    connect(Card_1553Can,&CardCtrl_1553B::send_pluseStatus,Card_plusetime,&Pluse_1553Time::get_pluseStatus);//传递1553初始成功参数
    connect(Card_1553Can,&CardCtrl_1553B::send_1553time,this,&MainWindow::get_1553time);//传递1553脉冲时间
    connect(Card_1553Can,&CardCtrl_1553B::send_1553fail,this,&MainWindow::fail_snack_slot);//传递1553脉冲时间
    connect(Card_1553Can,&CardCtrl_1553B::send_1553oupt,this,&MainWindow::Main_Oupt);//传递1553脉冲时间
    if(Card_1553Can->Init_BC1553Card()==API_SUCCESS){
        ui->m_output->append("1553板卡初始化成功");
        //1553板卡脉冲时间突发线程
        QThread* qthread_plusetime=new QThread();
        Card_plusetime->moveToThread(qthread_plusetime);
        connect(qthread_plusetime,&QThread::started,Card_plusetime,&Pluse_1553Time::StatusThread);
        connect(Card_plusetime,&Pluse_1553Time::send_pluse,Card_1553Can,&CardCtrl_1553B::WriteOnTimerMessage);
        qthread_plusetime->start();
        connect(this,&MainWindow::destroyed,this,[=](){
            qthread_plusetime->quit();
            qthread_plusetime->wait();
        });

    }
    else{
        ui->m_output->append(ChangeColor("1553板卡初始化失败",1));
    }
    if(Card_1553Can->Init_RT1553Card()==API_SUCCESS){
        ui->m_output->append("1553_RT初始化成功");
    }
    else{
        ui->m_output->append(ChangeColor("1553_RT初始化失败",1));
    }

    Card_1553Can->m_nTimerCounter=ui->UI_TIMES_IN->text().toUInt();

    //千兆网卡初始化（最后是界面配置参数，因为硬件第一次初始化有延时，影响1553广播发送，这里先无效初始化一次）2024.2.2
    ViSession devVi = 0;
    if(PA_PCIe_1501_NET_Init(&devVi)==API_SUCCESS){
        send_div=devVi;
        net_init=true;
        ui->m_output->append("千兆网卡初始化成功");
    }
    else{
        ui->m_output->append(ChangeColor("千兆网卡初始化失败",1));
    }
    //can板卡初始化
    Card_can=new CardCtrl_CAN();
    if(Card_can->InitCanCard()==API_SUCCESS){
        ui->m_output->append("CAN板卡初始化成功");
    }
    else{
        ui->m_output->append(ChangeColor("CAN板卡初始化失败",1));
    }
    QThread* thread_rec=new QThread();
    Card_can->moveToThread(thread_rec);
    connect(this,SIGNAL(statr_CanRec(bool)),Card_can,SLOT(Thread_CanRecv(bool)));
    connect(Card_can,&CardCtrl_CAN::add_output,this,&MainWindow::output_Data);//添加can应答输出
    thread_rec->start();
    emit statr_CanRec(1);
    connect(this,&MainWindow::destroyed,this,[=](){
        //Card_can->re_while=false;//加了会在debug调试模式下报内存出错
        re_while=false;
        thread_rec->quit();
        thread_rec->wait();
    });

    //    //Net网卡初始化
    //    Card_Net=new CardCtrl_NET;
    //    //net线程收数
    //    QThread* QThread_rec1=new QThread();
    //    QThread* QThread_rec2=new QThread();
    //    QThread* QThread_rec3=new QThread();
    //    QThread* QThread_rec4=new QThread();
    //    Rec_QThread1* Net_Qrec1=new Rec_QThread1();
    //    Rec_QThread2* Net_Qrec2=new Rec_QThread2();
    //    Rec_QThread3* Net_Qrec3=new Rec_QThread3();
    //    Rec_QThread4* Net_Qrec4=new Rec_QThread4();
    //    Net_Qrec1->moveToThread(QThread_rec1);
    //    Net_Qrec2->moveToThread(QThread_rec2);
    //    Net_Qrec3->moveToThread(QThread_rec3);
    //    Net_Qrec4->moveToThread(QThread_rec4);
    //    connect(Card_Net,&CardCtrl_NET::sendPath,Net_Qrec1,&Rec_QThread1::Rec_working1);
    //    connect(Card_Net,&CardCtrl_NET::sendPath,Net_Qrec2,&Rec_QThread2::Rec_working2);
    //    connect(Card_Net,&CardCtrl_NET::sendPath,Net_Qrec3,&Rec_QThread3::Rec_working3);
    //    connect(Card_Net,&CardCtrl_NET::sendPath,Net_Qrec4,&Rec_QThread4::Rec_working4);
    //    emit Card_Net->sendPath("");
    //    QThread_rec1->start();
    //    QThread_rec2->start();
    //    QThread_rec3->start();
    //    QThread_rec4->start();

    //    connect(this,&MainWindow::destroyed,this,[=](){
    //        QThread_rec1->quit();
    //        QThread_rec2->quit();
    //        QThread_rec3->quit();
    //        QThread_rec4->quit();
    //        QThread_rec1->wait();
    //        QThread_rec2->wait();
    //        QThread_rec3->wait();
    //        QThread_rec4->wait();
    //        Net_Qrec1->deleteLater();
    //        Net_Qrec2->deleteLater();
    //        Net_Qrec3->deleteLater();
    //        Net_Qrec4->deleteLater();


    //    });

}
//改变字体颜色
QString MainWindow::ChangeColor(QString str,int kind)
{

    QString  strC;
    // 设置文字（样式+内容）
    //QString  str= "<font size=\"9\" color=\"red\"> 信息 </font>";
    switch (kind) {
    case 0:
        strC= QString("<font  color=\"black\">%1</font>").arg(str);
        break;
    case 1:
        strC= QString("<font  color=\"red\">%1</font>").arg(str);
        break;
    case 2:
        strC= QString("<font  color=\"blue\">%1</font>").arg(str);
        break;
    default:
        break;
    }

    return strC;
}

//控件显示输出数据
void MainWindow::output_Data(QString str)
{

    ui->txt_command_rec->append(str);

}
//双击主界面列表
void MainWindow::slotRowDoubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    //int row=ui->ui_task_list->currentIndex().row();
    //QModelIndex index2=model_list->index(row,6);
    //    QString str=model_list->data(index).toString();

    //    qDebug()<<str;
}


//遥测子界面
void MainWindow::Init_Yc_Subview()
{
    //慢速遥测
    yc_slow=new subyc_slowspeed();
    p_view_yc->yc_slowspeed=yc_slow;
    connect(Card_1553Can,&CardCtrl_1553B::Get_1553Yc1,yc_slow,&subyc_slowspeed::Get_MsYcData1);
    connect(Card_1553Can,&CardCtrl_1553B::Get_1553Yc2,yc_slow,&subyc_slowspeed::Get_MsYcData2);
    connect(Card_1553Can,&CardCtrl_1553B::Get_1553Yc3,yc_slow,&subyc_slowspeed::Get_MsYcData3);
    connect(Card_1553Can,&CardCtrl_1553B::Get_1553Yc4,yc_slow,&subyc_slowspeed::Get_MsYcData4);

    //打包遥测
    yc_pack=new subyc_packspeed();
    p_view_yc->yc_packspeed=yc_pack;
    connect(Card_1553Can,&CardCtrl_1553B::Get_1553Yc_pack,yc_pack,&subyc_packspeed::Get_PackYcData);
    //CAN遥测0x81
    yc_canc81=new subyc_canC81();
    p_view_yc->yc_canc81=yc_canc81;
    connect(Card_can,&CardCtrl_CAN::Get_CanYc_81,yc_canc81,&subyc_canC81::Get_C81YcData);
    //AD电压遥测
    yc_ad=new subyc_AD();
    p_view_yc->yc_ad=yc_ad;
    connect(Card_AD_OC,&CardCtrl_AD_OC::Get_ADYc,yc_ad,&subyc_AD::Get_ADdata);
    //AD电压遥测
    yc_rs422_rec=new subrs422_Rec();
    p_view_yc->yc_rs422_rec=yc_rs422_rec;
    //遥测界面测试化
    p_view_yc->Init_View_Sub();

}



// 界面时间更新计时器
void MainWindow::timeUpdate() {
    QDateTime cur_time = QDateTime::currentDateTime();
    QString str = cur_time.toString("MM-dd hh:mm:ss");
    //ui->m_lcd_cur_time->display(str);
    qDebug()<<str;

    //读取信号源表格
    uint time=ssss_test++;//测试
    Get_ExlMess(time);
}

//1553星时显示
void MainWindow::get_1553time(LL times)
{

    //输出框
    //    QDateTime time=QDateTime::currentDateTime();
    //    QString str="pluse time ="+time.toString("MM-dd hh:mm:ss");
    //    ui->m_output->append(str);
    //    ui->m_output->moveCursor(QTextCursor::End);
    //界面显示星时
    QString qstr = QString::number(times);
    ui->m_lcd_cur_time->display(qstr);

    //读取信号源表格
    if(ui->rad_xlsxFile->isChecked())Get_ExlMess(times);

    //CAN广播
    if(!switch_CANboard)
    {
        //CAN卡 星时和能源状态广播(A/B轮询发送)
        Star_Power_broad str_power;
        memset(&str_power,0,sizeof (str_power));
        str_power.checktime_mode=0x5555;//GNSS校时
        LL start_time=times*10000;
        ushort tmp_ushort=0;
        tmp_ushort=start_time>>32;
        str_power.time_code[0]=qToBigEndian(tmp_ushort);
        tmp_ushort=start_time>>16;
        str_power.time_code[1]=qToBigEndian(tmp_ushort);
        tmp_ushort=start_time;
        str_power.time_code[2]=qToBigEndian(tmp_ushort);
        str_power.status=0x1111;//能源良好

        can_board canF1;//星时和能源状态广播结构体
        memset(&canF1,0,sizeof (canF1));
        ushort canLen=sizeof (canF1)+sizeof (str_power);
        canF1.CanorderLen=qToBigEndian(canLen);
        canF1.Canmark=0xF1;

        uchar *buff1=new uchar[canLen];
        //校验和crc
        memcpy(buff1,&canF1,3);
        memcpy(buff1+3,&str_power,sizeof (str_power));
        ushort crcs=0;
        for (ushort i=0;i<canLen-3;i++) {
            crcs+=buff1[i];
        }
        canF1.crc_add=qToBigEndian(crcs);
        memcpy(buff1+canLen-3,&canF1.bl,3);

        CAN_DataSend(buff1, canLen);//can封装发送

        delete [] buff1;

        Sleep(10);

        //CAN卡 GNSS时间码
        GNSS_Time str_gnsstime;
        memset(&str_gnsstime,0,sizeof (str_gnsstime));
        str_gnsstime.code1=0;
        tmp_ushort=0;
        tmp_ushort=times>>16;
        str_gnsstime.code2=qToBigEndian(tmp_ushort);
        tmp_ushort=times;
        str_gnsstime.code3=qToBigEndian(tmp_ushort);

        can_board canF2;//GNSS时间码结构体
        memset(&canF2,0,sizeof (canF2));
        ushort can2Len=sizeof (canF2)+sizeof (str_gnsstime);
        canF2.CanorderLen=qToBigEndian(can2Len);
        canF2.Canmark=0xF2;

        uchar *buff2=new uchar[can2Len];
        //校验和crc
        memcpy(buff2,&canF2,3);
        memcpy(buff2+3,&str_gnsstime,sizeof (str_gnsstime));
        ushort crc2s=0;
        for (ushort i=0;i<can2Len-3;i++) {
            crc2s+=buff2[i];
        }
        canF2.crc_add=qToBigEndian(crc2s);
        memcpy(buff2+can2Len-3,&canF2.bl,3);

        CAN_DataSend(buff2, can2Len);//can封装发送

        delete [] buff2;
        Sleep(10);
        //轨道姿态CAN
        gdzt_ssend(times);
        Sleep(10);
        //GNSS定位CAN
        gnss_dw_send(times);
        Sleep(10);
        //GNSS定轨CAN
        gnss_dg_send(times);
        Sleep(10);

        //遥测轮询C81,2秒一次（时序必须在最后，不然应答的时候发指令，会出错）
        if(times%2==0)
        {
            yccyc_C81 C81;
            memset(&C81,0,sizeof (C81));
            C81.order_len=qToBigEndian((ushort)6);
            C81.order_mark=0x81;
            //校验和crc
            uchar* strcrc=new uchar[sizeof (C81)];
            memcpy(strcrc,&C81,sizeof (C81));
            ushort crc81=0;
            for (uint i=0;i<sizeof (C81)-2;i++) {
                crc81+=strcrc[i];
            }
            C81.crc=qToBigEndian(crc81);
            delete [] strcrc;

            CAN_DataSend((uchar*)&C81, sizeof (C81));//can封装发送
            Sleep(10);
        }

    }

}
//轨道姿态CAN
void MainWindow::gdzt_ssend(int cnt)
{
    Orbitalstance_Data_CAN strorbital;
    int aa=sizeof (Orbitalstance_Data_CAN);
    memset(&strorbital,0,aa);


    if((v_orb_can.size()!=0)&&((uint)cnt<v_orb_can[v_orb_can.size()-1].thistime+1)&&((uint)cnt>v_orb_can[0].thistime-1))
    {
        //int tmp_cnt=cnt%v_orb.size();
        int tmp_cnt=cnt-v_orb_can[0].thistime;
        //qDebug()<<tmp_cnt<<"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
        strorbital.pack_len=qToBigEndian((ushort)sizeof (strorbital));

        strorbital.order_mark=0xF0;
        strorbital.satsllite_mark=0x01;
        //strorbital.thistime[0]=9;
        unsigned long long tm=v_orb_can[tmp_cnt].thistime;
        tm=tm*10000;//0.1ms
        tm=qToBigEndian(tm)>>16;
        memcpy(&strorbital.thistime[0],&tm,6);


        strorbital.rolling_angle=qToBigEndian(v_orb_can[tmp_cnt].rolling_angle[0]);
        strorbital.pitch_angle=qToBigEndian(v_orb_can[tmp_cnt].pitch_angle[0]);
        strorbital.yawing_angle=qToBigEndian(v_orb_can[tmp_cnt].yawing_angle[0]);
        strorbital.rolling_anglespeed=qToBigEndian((uint)0);
        strorbital.pitch_anglespeed=qToBigEndian((uint)0);
        strorbital.yawing_anglespeed=qToBigEndian((uint)0);
    }
    else
    {
        strorbital.pack_len=qToBigEndian((ushort)sizeof (strorbital));
        strorbital.order_mark=0xF0;
        strorbital.satsllite_mark=0x01;
        strorbital.thistime[0]=0;


        strorbital.rolling_angle=qToBigEndian((uint)0);
        strorbital.pitch_angle=qToBigEndian((uint)0);
        strorbital.yawing_angle=qToBigEndian((uint)0);
        strorbital.rolling_anglespeed=qToBigEndian((uint)0);
        strorbital.pitch_anglespeed=qToBigEndian((uint)0);
        strorbital.yawing_anglespeed=qToBigEndian((uint)0);

    }

    //校验和crc
    uchar* strcrc=new uchar[sizeof (strorbital)];
    memcpy(strcrc,&strorbital,sizeof (strorbital));
    ushort crc=0;
    for (uint i=0;i<sizeof (strorbital)-2;i++) {
        crc+=strcrc[i];
    }
    strorbital.crc_add=qToBigEndian(crc);
    delete [] strcrc;

    CAN_DataSend((uchar*)&strorbital, sizeof (strorbital));//can封装发送


}


//GNSS定位CAN
void MainWindow::gnss_dw_send(int cnt)
{
    GNSS_Positioning_CAN str_postion;
    memset(&str_postion,0,sizeof (GNSS_Positioning_CAN));

    if((v_gnss_postion_can.size()!=0)&&((uint)cnt<v_gnss_postion_can[v_gnss_postion_can.size()-1].time_s+1)&&((uint)cnt>v_gnss_postion_can[0].time_s-1))//读取表格值
    {

        //int tmp_cnt=cnt%v_gnss_postion.size();
        int tmp_cnt=cnt-v_gnss_postion_can[0].time_s;
        //qDebug()<<tmp_cnt<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwww";

        str_postion.order_len=qToBigEndian((ushort)sizeof (str_postion));

        str_postion.order_mark=0xF3;
        str_postion.pack_mark=0x7206;
        str_postion.pack_sequence=qToBigEndian((short)0xC000);
        str_postion.pack_len=qToBigEndian((short)0x0039);

        str_postion.posit_mark=0;
        str_postion.use_startsum=0;
        str_postion.time_s=qToBigEndian(v_gnss_postion_can[tmp_cnt].time_s);
        str_postion.position_x=qToBigEndian(v_gnss_postion_can[tmp_cnt].position_x[0]);
        str_postion.position_y=qToBigEndian(v_gnss_postion_can[tmp_cnt].position_y[0]);
        str_postion.position_z=qToBigEndian(v_gnss_postion_can[tmp_cnt].position_z[0]);
        str_postion.speed_x=qToBigEndian(v_gnss_postion_can[tmp_cnt].speed_x[0]);
        str_postion.speed_y=qToBigEndian(v_gnss_postion_can[tmp_cnt].speed_y[0]);
        str_postion.speed_z=qToBigEndian(v_gnss_postion_can[tmp_cnt].speed_z[0]);

        str_postion.track_mark=0;

        str_postion.position15_x=qToBigEndian((int)0);
        str_postion.position15_y=qToBigEndian((int)0);
        str_postion.position15_z=qToBigEndian((int)0);
        str_postion.speed15_x=qToBigEndian((int)0);
        str_postion.speed15_y=qToBigEndian((int)0);
        str_postion.speed15_z=qToBigEndian((int)0);

    }
    else
    {
        str_postion.order_len=qToBigEndian((ushort)sizeof (str_postion));
        str_postion.order_mark=0xF3;
        str_postion.pack_mark=0x7206;
        str_postion.pack_sequence=qToBigEndian((short)0xC000);
        str_postion.pack_len=qToBigEndian((short)0x0039);

        str_postion.posit_mark=0;
        str_postion.use_startsum=0;

        str_postion.time_s=qToBigEndian((uint)0);
        str_postion.position_x=qToBigEndian((int)0);
        str_postion.position_y=qToBigEndian((int)0);
        str_postion.position_z=qToBigEndian((int)0);
        str_postion.speed_x=qToBigEndian((int)0);
        str_postion.speed_y=qToBigEndian((int)0);
        str_postion.speed_z=qToBigEndian((int)0);

        str_postion.track_mark=0;

        str_postion.position15_x=qToBigEndian((int)0);
        str_postion.position15_y=qToBigEndian((int)0);
        str_postion.position15_z=qToBigEndian((int)0);
        str_postion.speed15_x=qToBigEndian((int)0);
        str_postion.speed15_y=qToBigEndian((int)0);
        str_postion.speed15_z=qToBigEndian((int)0);


    }

    //校验和crc
    uchar* strcrc=new uchar[sizeof (str_postion)];
    memcpy(strcrc,&str_postion,sizeof (str_postion));
    ushort crc=0;
    for (uint i=0;i<sizeof (str_postion)-2;i++) {
        crc+=strcrc[i];
    }
    str_postion.crc_add=qToBigEndian(crc);
    delete [] strcrc;
    //OnceSend_Data((uchar*)&str_postion,sizeof (GNSS_Positioning),31,17);
    CAN_DataSend((uchar*)&str_postion, sizeof (str_postion));//can封装发送
}


//GNSS定轨CAN
void MainWindow::gnss_dg_send(int cnt)
{
    GNSS_Track_CAN str_track;
    memset(&str_track,0,sizeof (GNSS_Track_CAN));

    if((v_gnss_orbit_can.size()!=0)&&((uint)cnt<v_gnss_orbit_can[v_gnss_orbit_can.size()-1].time_s+1)&&((uint)cnt>v_gnss_orbit_can[0].time_s-1))//读取表格值
    {
        //int tmp_cnt=cnt%v_gnss_orbit.size();
        int tmp_cnt=cnt-v_gnss_orbit_can[0].time_s;
        //qDebug()<<tmp_cnt<<"ggggggggggggggggggggggggggggggggggg";

        str_track.order_len=qToBigEndian((ushort)sizeof (str_track));
        str_track.order_mark=0xF4;
        str_track.pack_mark=0x7306;
        str_track.pack_sequence=qToBigEndian((short)0xC000);
        str_track.pack_len=qToBigEndian((short)0x0039);

        str_track.track_mark=0;
        str_track.use_startsum=0;
        str_track.time_s=qToBigEndian(v_gnss_orbit_can[tmp_cnt].time_s);
        str_track.track_halflenth=qToBigEndian(v_gnss_orbit_can[tmp_cnt].track_halflenth[0]);
        str_track.track_offcenter=qToBigEndian(v_gnss_orbit_can[tmp_cnt].track_offcenter[0]);
        str_track.track_angle=qToBigEndian(v_gnss_orbit_can[tmp_cnt].track_angle[0]);
        str_track.up_point=qToBigEndian(v_gnss_orbit_can[tmp_cnt].up_point[0]);
        str_track.near_angle=qToBigEndian(v_gnss_orbit_can[tmp_cnt].near_angle[0]);
        str_track.flat_angle=qToBigEndian(v_gnss_orbit_can[tmp_cnt].flat_angle[0]);
        str_track.outpush_time=qToBigEndian((ushort)0);



        str_track.track_15halflenth=qToBigEndian((uint)0);
        str_track.track_15offcenter=qToBigEndian((uint)0);
        str_track.track_15angle=qToBigEndian((uint)0);
        str_track.up_15point=qToBigEndian((uint)0);
        str_track.near_15angle=qToBigEndian((uint)0);
        str_track.flat_15angle=qToBigEndian((uint)0);
    }
    else
    {
        str_track.order_len=qToBigEndian((ushort)sizeof (str_track));
        str_track.order_mark=0xF4;
        str_track.pack_mark=0x7306;
        str_track.pack_sequence=qToBigEndian((short)0xC000);
        str_track.pack_len=qToBigEndian((short)0x0039);

        str_track.track_mark=0;
        str_track.use_startsum=0;

        str_track.time_s=qToBigEndian((uint)0);
        str_track.track_halflenth=qToBigEndian((uint)0);
        str_track.track_offcenter=qToBigEndian((uint)0);
        str_track.track_angle=qToBigEndian((uint)0);
        str_track.up_point=qToBigEndian((uint)0);
        str_track.near_angle=qToBigEndian((uint)0);
        str_track.flat_angle=qToBigEndian((uint)0);
        str_track.outpush_time=qToBigEndian((ushort)0);



        str_track.track_15halflenth=qToBigEndian((uint)0);
        str_track.track_15offcenter=qToBigEndian((uint)0);
        str_track.track_15angle=qToBigEndian((uint)0);
        str_track.up_15point=qToBigEndian((uint)0);
        str_track.near_15angle=qToBigEndian((uint)0);
        str_track.flat_15angle=qToBigEndian((uint)0);
    }
    //校验和crc
    uchar* strcrc=new uchar[sizeof (str_track)];
    memcpy(strcrc,&str_track,sizeof (str_track));
    ushort crc=0;
    for (uint i=0;i<sizeof (str_track)-2;i++) {
        crc+=strcrc[i];
    }
    str_track.crc_add=qToBigEndian(crc);
    delete [] strcrc;

    //OnceSend_Data((uchar*)&str_track,sizeof (GNSS_Track),31,18);
    CAN_DataSend((uchar*)&str_track, sizeof (str_track));//can封装发送
}



//读取信号源表格内容发送
void MainWindow::Get_ExlMess(uint time)
{

    //信号源未连接不读取
    if((ui->rad_xh1->isChecked()!=true)&&(ui->rad_xh2->isChecked()!=true))
    {
        //ui->textBrowser__massages->append("未有信号源连接");
        return;
    }


    //读取表格参数内容（表格没读取开启定时器会出错）
    for(int i=2;i<Signal_xlsxR->dimension().rowCount()+1;i++)//跳过第一行
    {

        //(排除其他杂乱信息)
        //结束时间
        Cell* cell = Signal_xlsxR->cellAt(i, 2);
        if ( cell == NULL )continue;//结束时间为空
        //起始时间
        cell = Signal_xlsxR->cellAt(i, 1);
        if ( cell == NULL )continue;//开始时间为空

        //QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
        uint tmp_times=cell->value().toUInt();
        if(tmp_times==time)//与开始时间匹配
        {
            ui->textBrowser__massages->append("开始时间"+QString::number(tmp_times)+"开始执行");
            for(int ch=0;ch<2;ch++)
            {
                if((ui->rad_xh1->isChecked()!=true)&&(ch==0))continue;//信号源1
                if((ui->rad_xh2->isChecked()!=true)&&(ch==1))continue;//信号源2

                //信号源是否recall
                cell = Signal_xlsxR->cellAt(i, 3+ch*9);
                if(cell->value().toString()=="是")
                {
                    //recall序号
                    cell = Signal_xlsxR->cellAt(i, 4+ch*9);
                    signalConrtl[ch]->RCL(cell->value().toInt());
                    continue;
                }
                //频率(M)
                cell = Signal_xlsxR->cellAt(i, 5+ch*9);
                if(cell != NULL)signalConrtl[ch]->setFre(cell->value().toDouble()*1000000);
                //调制样式
                cell = Signal_xlsxR->cellAt(i, 6+ch*9);
                QString types=cell->value().toString();
                if(cell != NULL)
                {
                    if(types=="AM")
                    {
                        signalConrtl[ch]->setAM(1);
                        signalConrtl[ch]->setFM(0);
                    }
                    else if(types=="FM")
                    {
                        signalConrtl[ch]->setAM(0);
                        signalConrtl[ch]->setFM(1);
                    }
                    else
                    {
                        signalConrtl[ch]->setFM(0);
                        signalConrtl[ch]->setAM(0);
                        signalConrtl[ch]->setCustMode(types);
                    }
                }
                //幅度值(dBm)
                cell = Signal_xlsxR->cellAt(i, 7+ch*9);
                if(cell != NULL)signalConrtl[ch]->setPower(cell->value().toDouble());
                //码速率(K)
                cell = Signal_xlsxR->cellAt(i, 8+ch*9);
                if(cell != NULL)signalConrtl[ch]->setCustom(cell->value().toDouble()*1000);
                //频偏(K),只设置FSk跟FM的
                cell = Signal_xlsxR->cellAt(i, 9+ch*9);
                if(types.contains("FSK"))
                {
                    if(cell != NULL)signalConrtl[ch]->setFskOffs(cell->value().toDouble()*1000);
                }
                if(types=="FM")
                {
                    if(cell != NULL)signalConrtl[ch]->setFmOffs(cell->value().toDouble()*1000);
                }
                //AM调制深度%
                cell = Signal_xlsxR->cellAt(i, 10+ch*9);
                if(cell != NULL)signalConrtl[ch]->setAmDepth(cell->value().toUInt());
                //PN
                cell = Signal_xlsxR->cellAt(i, 11+ch*9);
                if(cell != NULL)signalConrtl[ch]->setCustomSoure(cell->value().toString());


                //开启RF，MOD发送
                signalConrtl[ch]->OUTPut_RF(true);
                signalConrtl[ch]->Custom_MOD(true);
            }

        }

        //结束时间
        cell = Signal_xlsxR->cellAt(i, 2);
        uint tmp_timee=cell->value().toUInt();
        if(tmp_timee==time)//与结束时间匹配
        {
            ui->textBrowser__massages->append("结束时间"+QString::number(tmp_timee)+"开始执行");
            for(int ch=0;ch<2;ch++)
            {
                if((ui->rad_xh1->isChecked()!=true)&&(ch==0))continue;//信号源1
                if((ui->rad_xh2->isChecked()!=true)&&(ch==1))continue;//信号源2
                //关闭RF，MOD发送
                signalConrtl[ch]->OUTPut_RF(false);
                signalConrtl[ch]->Custom_MOD(false);
            }

        }
    }

}


void MainWindow::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);
    QRect rect = ui->m_widget_main->geometry();
    main_frame_size = QSize(rect.width(), rect.height());
}


// 导航栏点击
void MainWindow::tab_index_change(int index) {
    // 先隐藏全部界面，再根据点击的下边显示对应界面
    p_view_task->setHidden(true);
    p_view_yc->setHidden(true);
    p_database->setHidden(true);
    p_monitor->setHidden(true);
    ui->m_Vector_Widget->setHidden(true);
    Sleep(10);
    switch (index) {
    case 0:  //主页面
        ui->m_Vector_Widget->show();
        break;
    case 1:  //任务生成页面
        p_view_task->setMinimumSize(main_frame_size);
        p_view_task->show();
        break;
    case 2:  //遥测显示界面
        p_view_yc->setMinimumSize(main_frame_size);
        p_view_yc->show();
        break;
    case 3:  //数据库查询
        p_database->setMinimumSize(main_frame_size);
        p_database->show();
        break;
    case 4:  // 监视页面
        p_monitor->setMinimumSize(main_frame_size);
        p_monitor->show();
        break;
    default:
        break;
    }
}



// 全部发送按钮
void MainWindow::button_click_sendAll() {
    if(order_data_list.isEmpty())return;
    for(int row=0;row<ui->ui_task_list->model()->rowCount();row++)
        for(int col=0;col<ui->ui_task_list->model()->columnCount();col++)
            model_list->item(row,col)->setBackground(QColor(Qt::white));
    if(timer->isActive()){
        timer->stop();//指令定时器发送停止
        //return;
    }

    uint s_time=ui->lE_Start_orderTime->text().toUInt();//设置全部指令发送的起始时间
    //TIME_CNT=0;
    TIME_CNT=s_time;
    timer->start(1000);//1s触发一次

}


//定时，选中发送公共函数
void MainWindow::Order_Send_Fun(int cnt)
{

    LL time=0;
    int status=0;
    int objAddr=order_data_list.at(cnt).obj_id;//单机编号

    switch (order_data_list.at(cnt).order_kind) {
    case 1://总线指令
        status=Send_1553SubOrder(cnt,false,objAddr);
        break;
    case 6://模式控制指令
        status=Send_1553ModeOeder(cnt,objAddr);
        break;
    case 9://Can指令
        status=Send_CancardOeder(cnt);
        break;
        //总线注数指令（上注指令）
    case 2: //功能识别码0x0086
    case 3: //功能识别码0x0088
    case 4: //功能识别码0x0081
    case 5: //功能识别码0x0082
    case 7: //功能识别码0x0083
    case 8: //功能识别码0x0084
    case 11://功能识别码0x0089
    case 12://功能识别码0x008A
    case 13://功能识别码0x0085
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        status=Send_1553OverOrder(cnt,false,objAddr);
        break;
    case 10://星时指令
        memcpy(&time,order_data_list.at(cnt).data_buf,sizeof (time));
        Card_1553Can->m_nTimerCounter=time;
        status=0;
        break;
    case 20://信号源控制
        status=Send_Signal(cnt);
        break;
    default:
        break;
    }
    //每次发送写入数据库
    Write_orDB(cnt,status);
    //界面输出发送名称
    QDateTime tm=QDateTime::currentDateTime();
    QString send_time="时间"+tm.toString("hh:mm:ss")+"发送指令："+order_data_list.at(cnt).order_name;
    ui->m_output->append(send_time);
}
 //加头导出
void MainWindow::HeadOrd_Send_Fun(int cnt)
{
    int status=0;
    switch (order_data_list.at(cnt).order_kind) {
    case 1://总线指令
        status=Send_1553SubOrder(cnt,true,0);
        break;
        //总线注数指令（上注指令）
    case 2: //功能识别码0x0086
    case 3: //功能识别码0x0088
    case 4: //功能识别码0x0081
    case 5: //功能识别码0x0082
    case 7: //功能识别码0x0083
    case 8: //功能识别码0x0084
    case 11://功能识别码0x0089
    case 12://功能识别码0x008A
    case 13://功能识别码0x0085
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        status=Send_1553OverOrder(cnt,true,0);
        break;
    default:
        break;
    }

    return ;
}


//指令发送内容写入数据库
void MainWindow::Write_orDB(int num,int status)
{
    //指令发送数据库写入
    QSqlQuery qureydb;//创建对象时，系统会自动完成与数据库的关联
    QString str=QString("INSERT INTO ORDER_LIST('时间', '状态', '单机','PID', '发送时间', '名称', '类型', '长度', '指令内容') ");

    //时间
    QDateTime cur_time = QDateTime::currentDateTime();
    QString strtime = cur_time.toString("MM-dd hh:mm:ss");
    //指令状态
    QString s_status="正常";
    if(status!=0)s_status="异常";
    //单机
    QString DJ="单机"+QString::number(order_data_list.at(num).obj_id+1);
    if(order_data_list.at(num).obj_id==4)DJ="全选";
    //指令内容
    QString strbuff;
    strbuff = "";
    QString tmp_byte;
    for (int readLen = 0; readLen < order_data_list.at(num).order_len; readLen++) {
        tmp_byte = QString().asprintf("%02x ", order_data_list.at(num).data_buf[readLen]);
        strbuff.append(tmp_byte);
    }

    QString str2=QString("VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9' );")
            //时间，状态
            .arg(strtime).arg(s_status)
            //单机
            .arg(DJ)
            //PID
            .arg(order_data_list.at(num).page_id)
            //发送时间
            .arg(order_data_list.at(num).start_time)
            //名称
            .arg(order_data_list.at(num).order_name)
            //类型
            .arg(Ord_Kind[order_data_list.at(num).order_kind])
            //长度
            .arg(order_data_list.at(num).order_len)
            //指令内容
            .arg(strbuff);

    str+=str2;
    qDebug()<<str;
    qureydb.exec(str);
}

void MainWindow::Get_PackOrder(unsigned char *Data, int Datalen)
{
    QString pack_order="";
    for (int i=0;i<Datalen;i++) {
        pack_order+=QString("%1 ").arg(Data[i],2,16,QLatin1Char('0'));

    }
    STR_PackOder=pack_order;
    //qDebug()<<pack_order;
}


// 移动表格行
void MainWindow::moveRow(QTableView *tableView, int currentRow, int toRow)
{
    if( currentRow == toRow ){
        return;
    }

    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(tableView->model());
    if (model == nullptr) {
        qDebug() << "model is null";
        return;
    }

    int column = tableView->currentIndex().column();
    if(nullptr == model || currentRow < 0 || currentRow > model->rowCount()-1)
    {
        QMessageBox::information(this,"tip","invalid");
        return ;
    }

    if( currentRow < toRow ){
        //下移需要判断最后一行，不移动
        if(currentRow == model->rowCount()-1)
        {
            QMessageBox::information(this,"提示","已经最后一行");
            return ;
        }
    }else{
        //上移需要判断是否第一行，不移动
        if(0 == currentRow)
        {
            QMessageBox::information(this,"提示","已经是第一行");
            return ;
        }
    }

    QList<QStandardItem *> listItem = model->takeRow(currentRow);
    model->insertRow(toRow,listItem);

    tableView->setCurrentIndex( model->index(toRow, column) );
    tableView->selectRow(toRow);
}




//指令定时发送
void MainWindow::timerUpdate()
{
    uint max_time=0;
    for(int cnt=0;cnt<order_data_list.count();cnt++)
    {
        //获取每条指令的发送时间
        uint send_time = order_data_list.at(cnt).start_time;
        max_time = qMax(max_time, send_time);//记录最后一条指令的发送时间
        if(TIME_CNT==send_time)
        {
            for(int col=0;col<ui->ui_task_list->model()->columnCount();col++)
                model_list->item(cnt,col)->setBackground(QColor(150,230,240));//淡蓝色

            Order_Send_Fun(cnt);//公共发送函数
        }
    }
    //emit success_snack("发送成功");
    if (max_time < TIME_CNT)//如果当前时间超过列表内全部指令则停止计时器
    {
        if(Cycle_sendFlag==true)//指令循环发送
        {

            for(int row=0;row<ui->ui_task_list->model()->rowCount();row++)
                for(int col=0;col<ui->ui_task_list->model()->columnCount();col++)
                    model_list->item(row,col)->setBackground(QColor(Qt::white));
            TIME_CNT=0;
        }
        else
        {
            timer->stop();
        }

    }
    TIME_CNT++;
    //timer->stop();

}

// 单条发送按钮
void MainWindow::button_click_sendOne() {

    if (!ui->ui_task_list->selectionModel()->hasSelection()) {
        QMessageBox::information(NULL, "提示", "没有选中");
        return;
    }

    if(timer->isActive()){
        timer->stop();//指令定时器发送停止
        //return;
    }
    //多行
    QModelIndexList index_list=ui->ui_task_list->selectionModel()->selectedIndexes();
    QList<int>list;
    int prev=-1,curr=-1;
    prev=index_list.at(0).row();
    list.append(prev);
    for(int i=0;i<index_list.length();i++)
    {
        //qDebug()<<index_list.at(i).row();
        curr=index_list.at(i).row();
        if(prev==curr)
        {
            continue;
        }
        else
        {
            prev=curr;
            list.append(prev);
        }
    }

    //单行
    //QModelIndex index = ui->ui_task_list->selectionModel()->currentIndex();
    //int irow = index.row();
    for(int row=0;row<ui->ui_task_list->model()->rowCount();row++)
        for(int col=0;col<ui->ui_task_list->model()->columnCount();col++)
            model_list->item(row,col)->setBackground(QColor(Qt::white));
    for(int n=0;n<list.size();n++)
    {
        //qDebug()<<list.at(n);
        int cnt=list.at(n);
        for(int col=0;col<ui->ui_task_list->model()->columnCount();col++)
            model_list->item(cnt,col)->setBackground(QColor(150,230,240));//淡蓝色


        Order_Send_Fun(cnt);//公共发送函数

        Sleep(5);
    }
    emit success_snack("发送成功");
}




// 停止按钮
void MainWindow::button_click_Stop() {
    //QMessageBox::information(NULL, "提示", "信号触发");

    timer->stop();//指令定时器发送停止
    emit success_snack("指令发送暂停");
}

// 列表指令循环发送
void MainWindow::button_click_cycle()
{

    if(Cycle_sendFlag==true)
    {
        m_button_send_all_task->setEnabled(true);
        m_button_send_one_task->setEnabled(true);
        Cycle_sendFlag=false;
        m_button_cycle_task->setText("循环发送开");
        timer->stop();
    }
    else
    {
        m_button_send_all_task->setEnabled(false);
        m_button_send_one_task->setEnabled(false);
        Cycle_sendFlag=true;
        m_button_cycle_task->setText("循环发送关");

        if(order_data_list.isEmpty())return;
        for(int row=0;row<ui->ui_task_list->model()->rowCount();row++)
            for(int col=0;col<ui->ui_task_list->model()->columnCount();col++)
                model_list->item(row,col)->setBackground(QColor(Qt::white));
        if(timer->isActive()){
            return;
            //timer->stop();
        }

        uint s_time=ui->lE_Start_orderTime->text().toUInt();//设置全部指令发送的起始时间
        //TIME_CNT=0;
        TIME_CNT=s_time;
        timer->start(1000);//1s触发一次
    }

}

// 删除全部按钮
void MainWindow::button_click_delAll() {
    model_list->removeRows(0, model_list->rowCount());
    order_data_list.clear();
    ui->lE_Start_orderTime->setText("0");//指令发送起始时间
}

bool larger(int a,int b)
{
    return  a>b;
}

// 删除一条按钮
void MainWindow::button_click_delOne() {

    if (!ui->ui_task_list->selectionModel()->hasSelection()) {
        QMessageBox::information(NULL, "提示", "没有选中");
        return;
    }
    //    //单行
    //    QModelIndex index = ui->ui_task_list->selectionModel()->currentIndex();
    //    int irow = index.row();
    //    if (irow < 0)return;
    //    else {

    //        model_list->removeRow(irow);
    //        order_data_list.removeAt(irow);
    //    }


    //多行
    QModelIndexList index_list=ui->ui_task_list->selectionModel()->selectedIndexes();
    QList<int>list;
    int prev=-1,curr=-1;
    prev=index_list.at(0).row();
    list.append(prev);
    for(int i=0;i<index_list.length();i++)
    {
        //qDebug()<<index_list.at(i).row();
        curr=index_list.at(i).row();
        if(prev==curr)
        {
            continue;
        }
        else
        {
            prev=curr;
            list.append(prev);
        }
    }
    //QMessageBox::information(NULL, "提示", "信号触发");

    sort(list.begin(),list.end(),larger);//默认小->大（当前大->小）
    for(int n=0;n<list.size();n++)
    {
        int irow=list.at(n);
        model_list->removeRow(irow);
        order_data_list.removeAt(irow);
    }

}

// 导出按钮
void MainWindow::button_click_export()
{


    //选择保存文件
    QString qFileName = QFileDialog::getSaveFileName(this, tr("选择保存路径"),"",tr("*.xlsx ;; *.txt "));
    if(qFileName.isEmpty())return;

    //判断后缀
    QFileInfo fileinfo(qFileName);
    QString Fsuffix=fileinfo.suffix();

    //区分类型保存
    if(Fsuffix=="xlsx")
    {
        QXlsx::Document xlsx;
        int row=ui->ui_task_list->model()->rowCount();
        int col=ui->ui_task_list->model()->columnCount();
        int tmpi=0;

        //设置列宽
        xlsx.setColumnWidth(4,5,20);//开始列，结束列，列宽
        xlsx.setColumnWidth(7,100);//第7列，20列宽
        //获取列表头
        for (int n=0;n<col;n++) {
            QString strhead=ui->ui_task_list->model()->headerData(n,Qt::Horizontal).toString();
            xlsx.write(1, n+1,strhead);
        }

        //只选择---单行
        if(ui->ui_task_list->selectionModel()->hasSelection())
        {
            QMessageBox::information(this,"提示","已选择单行导出");
            QModelIndex qMIndex = ui->ui_task_list->selectionModel()->currentIndex();
            tmpi = qMIndex.row();
            //获取内容
            for (int i=0;i<1;i++) {
                for (int j=0;j<col;j++) {
                    QString tmp_str;
                    int tmp_int=0;

                    QModelIndex index=ui->ui_task_list->model()->index(tmpi,j);
                    if((j==1)||(j==2)||(j==5))
                    {
                        tmp_int=index.data().toInt();//整型
                        xlsx.write(i+2, j+1,tmp_int);
                    }
                    else
                    {
                        tmp_str=index.data().toString();//字符串格式
                        xlsx.write(i+2, j+1,tmp_str);
                    }

                }
            }
        }
        else //全部导出
        {
            //获取内容
            for (int i=0;i<row;i++) {
                for (int j=0;j<col;j++) {
                    QString tmp_str;
                    int tmp_int=0;

                    QModelIndex index=ui->ui_task_list->model()->index(i,j);
                    if((j==1)||(j==2)||(j==5))
                    {
                        tmp_int=index.data().toInt();//整型
                        xlsx.write(i+2, j+1,tmp_int);
                    }
                    else
                    {
                        tmp_str=index.data().toString();//字符串格式
                        xlsx.write(i+2, j+1,tmp_str);
                    }

                }
            }
        }

        if (!xlsx.saveAs(qFileName)) {
            QMessageBox::warning(this, "提示", "文件保存失败");
            return;
        }
        xlsx.deleteLater();//释放指针
    }
    else if(Fsuffix=="txt")
    {

        QFile qFile(qFileName);
        if(!qFile.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::information(this,"提示","文件打开错误");
            return;
        }

        int tmpi=0;//表格起始行
        int tmpsum=order_data_list.size();//表格总行
        if(ui->ui_task_list->selectionModel()->hasSelection())//只选择单行
        {
            QMessageBox::information(this,"提示","已选择单行导出");
            QModelIndex qMIndex = ui->ui_task_list->selectionModel()->currentIndex();
            tmpi = qMIndex.row();
            tmpsum=tmpi+1;
        }

        QByteArray data;
        QString str;

        for (int i = tmpi; i < tmpsum; i++) {
            data.clear();
            str = QString("单机;%1\n").arg(model_list->item(i,0)->text());
            data.append(str);

            str = QString("PID;%1\n").arg(order_data_list[i].page_id);
            data.append(str);

            str = QString("发送时间;%1\n").arg(order_data_list[i].start_time);
            data.append(str);

            //str = QString("名称: %1 \n").arg(order_data_list[i].order_name);//生成内存内容导出
            str = QString("名称;%1\n").arg(model_list->item(i,3)->text());//根据界面修改名字导出
            data.append(str);

            str = QString("类型;%1\n").arg(order_data_list[i].order_kind);
            data.append(str);

            str = QString("长度;%1\n").arg(order_data_list[i].order_len);
            data.append(str);

            QString byteArray;
            for (int j = 0; j < order_data_list[i].order_len; j++) {
                byteArray += QString().asprintf("%02x ", order_data_list[i].data_buf[j]); // 末尾会留出一个空格
            }
            str = QString("指令内容;%1\r\n").arg(byteArray);
            data.append(str);

            qFile.write(data.data()); // 数据写入文件
        }
        qFile.close();

    }
    else
    {
        QMessageBox::information(this,"提示","文件未识别后缀");
        return;
    }

    emit success_snack_slot("导出成功");
}

// 导入按钮
void MainWindow::button_click_import()
{

    ui->lE_Start_orderTime->setText("0");//指令发送起始时间

    //打开指令文件
    QString qFileName = QFileDialog::getOpenFileName(this, tr("open file"), "", tr("*.xlsx *.txt"));
    if(qFileName.isEmpty())return;
    //判断后缀
    QFileInfo fileinfo(qFileName);
    QString Fsuffix=fileinfo.suffix();

    //区分类型保存
    if(Fsuffix=="xlsx")
    {
        QXlsx::Document xlsxR(qFileName);

        if(!xlsxR.load())
        {
            qDebug()<<"excel打开失败";
        }
        //检查表格格式是否有正确
        if(!xlsxR.selectSheet("Sheet1"))
        {
            qDebug()<<"未找到页“Sheet1";
            return;
        }

        int rowsum=xlsxR.dimension().rowCount();
        int colsum=xlsxR.dimension().columnCount();
        colsum=7;//指令格式固定7列，防止出错
        for(int i=2;i<rowsum+1;i++)//行
        {
            // 封装到指令队列里
            Order_List_Object order_data;
            for(int j=1;j<colsum+1;j++)//列
            {

                Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
                if ( cell != NULL )
                {
                    QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                    //qDebug()<< var.toString();
                    if(j==1)
                    {
                        order_data.mode = 0;
                        order_data.obj_id = OBJ_Addr[var.toString()];//不匹配默认单机1（值0）
                    }
                    if(j==2)order_data.page_id=var.toInt();
                    if(j==3)order_data.start_time = var.toUInt();
                    if(j==4)
                    {
                        order_data.gap_time=1;
                        order_data.order_name = var.toString();
                    }
                    if(j==5)order_data.order_kind = Ord_Kind2[var.toString()];
                    if(j==6)order_data.order_len = var.toUInt();
                    //指令内容数据
                    if(j==7)
                    {
                        order_data.data_buf = new uchar[order_data.order_len];
                        QString tmp_str = var.toString();

                        QByteArray hex_data=QByteArray::fromHex(tmp_str.toLatin1());//将字节流转换位16进制,char型
                        uchar* data_buf=(uchar*)hex_data.data();//获取地址
                        memcpy(order_data.data_buf, data_buf, order_data.order_len);
                    }
                }

            }
            QVariant varData;
            varData.setValue(order_data);
            inOder_falg=true;
            add_order_toList(varData);

        }
        xlsxR.deleteLater();//释放指针
    }
    else if(Fsuffix=="txt")
    {
        QFile qFile(qFileName);
        if(!qFile.open(QFile::ReadWrite | QFile::Text)) {
            QMessageBox::information(this,"提示","文件打开错误");
            return;
        }

        QByteArray txtdata; // 用于读取txt中每行数据
        QList<QByteArray> strList; // 分割完 ';' 后的链表
        QList<QString> txt_buf; // 存放目标数据

        while (!qFile.atEnd())
        {
            strList.clear();
            txt_buf.clear();

            //7行数据为一个完整指令
            for (int i = 0; i < 7; i++) {
                txtdata = qFile.readLine();
                if(!txtdata.contains(";"))break;//格式不对直接退出
                txtdata.replace(" ","");
                txtdata.replace("\n","");

                strList = txtdata.split(';');   //用;进行分割存储
                txt_buf.append(strList.at(1));// 取';'后面的元素,用;进行分割存储
            }

            if(txt_buf.size()==0)continue;
            // 封装到指令队列里
            Order_List_Object order_data;
            order_data.mode = 0;
            order_data.obj_id = OBJ_Addr[QString(txt_buf.at(0))];//不匹配默认单机1（值0）
            order_data.page_id = txt_buf.at(1).toInt();
            order_data.start_time = txt_buf.at(2).toUInt();
            order_data.gap_time=1;
            order_data.order_name = QString(txt_buf.at(3));
            order_data.order_kind = txt_buf.at(4).toUInt();
            order_data.order_len = txt_buf.at(5).toUShort();
            //指令内容数据
            order_data.data_buf = new uchar[order_data.order_len];
            QString tmp_str = txt_buf.at(6);

            QByteArray hex_data=QByteArray::fromHex(tmp_str.toLatin1());//将字节流转换位16进制,char型
            uchar* data_buf=(uchar*)hex_data.data();//获取地址
            memcpy(order_data.data_buf, data_buf, order_data.order_len);

            QVariant varData;
            varData.setValue(order_data);
            inOder_falg=true;
            add_order_toList(varData);
        }
        qFile.close();
    }
    else
    {
        QMessageBox::information(this,"提示","文件未识别后缀");
        return;
    }

    emit success_snack_slot("导入成功");
}
//单行上移
void MainWindow::button_click_orderup()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->ui_task_list->model());
    if (model == nullptr) {
        qDebug() << "model is null";
        return;
    }

    int row = ui->ui_task_list->currentIndex().row();
    int nRowInsert = row - 1;
    if(nRowInsert==-1)return;
    moveRow(ui->ui_task_list, row, nRowInsert);

    //交换表格缓存数据
    swap(order_data_list[row],order_data_list[nRowInsert]);
    swap(order_data_list[row].data_buf,order_data_list[nRowInsert].data_buf);
}
//单行下移
void MainWindow::button_click_orderdown()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->ui_task_list->model());
    if (model == nullptr) {
        qDebug() << "model is null";
        return;
    }

    int row = ui->ui_task_list->currentIndex().row();
    int nRowInsert = row + 1;
    int tmp=ui->ui_task_list->model()->rowCount();
    if((nRowInsert+1)>tmp)return;
    moveRow(ui->ui_task_list, row, nRowInsert);

    //交换表格缓存数据
    swap(order_data_list[row],order_data_list[nRowInsert]);
    swap(order_data_list[row].data_buf,order_data_list[nRowInsert].data_buf);
}


//指令加头导出（直接提供8院）
void MainWindow::button_click_Packexport()
{

    //选择保存文件
    QString qFileName = QFileDialog::getSaveFileName(this, tr("选择保存路径"),"",tr("*.xlsx"));
    if(qFileName.isEmpty())return;

    //判断后缀
    QFileInfo fileinfo(qFileName);
    QString Fsuffix=fileinfo.suffix();

    //区分类型保存
    if(Fsuffix=="xlsx")
    {
        QXlsx::Document xlsx;
        int row=ui->ui_task_list->model()->rowCount();
        int col=ui->ui_task_list->model()->columnCount();

        //设置列宽
        xlsx.setColumnWidth(4,5,20);//开始列，结束列，列宽
        xlsx.setColumnWidth(7,100);//第7列，20列宽
        //获取列表头
        for (int n=0;n<col;n++) {
            QString strhead=ui->ui_task_list->model()->headerData(n,Qt::Horizontal).toString();
            if(n==(col-1))strhead="(加头尾封装)"+strhead;
            xlsx.write(1, n+1,strhead);
        }
        //获取内容
        for (int i=0;i<row;i++) {

            STR_PackOder="不封装";
            //发送时封装指令
            HeadOrd_Send_Fun(i);

            for (int j=0;j<col;j++) {
                QString tmp_str;
                int tmp_int=0;

                QModelIndex index=ui->ui_task_list->model()->index(i,j);

                /////////////////////////////////////////////判断是否封装
                if(STR_PackOder=="不封装")
                {
                    if((j==1)||(j==2)||(j==5))
                    {
                        tmp_int=index.data().toInt();//整型
                        xlsx.write(i+2, j+1,tmp_int);
                    }
                    else
                    {
                        tmp_str=index.data().toString();//字符串格式
                        xlsx.write(i+2, j+1,tmp_str);
                    }
                }
                else//封装指令
                {
                    if((j==1)||(j==2))
                    {
                        tmp_int=index.data().toInt();//整型
                        xlsx.write(i+2, j+1,tmp_int);
                    }
                    else if(j==5)
                    {
                        tmp_int=STR_PackOder.length()/3;//整型
                        xlsx.write(i+2, j+1,tmp_int);
                    }
                    else if(j==6)
                    {
                        xlsx.write(i+2, j+1,STR_PackOder);
                    }
                    else
                    {
                        tmp_str=index.data().toString();//字符串格式
                        xlsx.write(i+2, j+1,tmp_str);
                    }
                }


            }
        }
        if (!xlsx.saveAs(qFileName)) {
            QMessageBox::warning(this, "提示", "文件保存失败");
            return;
        }
        xlsx.deleteLater();//释放指针
    }

    else
    {
        QMessageBox::information(this,"提示","文件未识别后缀");
        return;
    }

    emit success_snack_slot("导出成功");
}



// 任务列表右键菜单
void MainWindow::show_tasklist_menu(QPoint pos) {
    // 传入当前位置坐标，执行
    Q_UNUSED(pos);
    m_list_task_menu->exec(QCursor::pos());
}

// 成功消息弹窗
void MainWindow::success_snack_slot(QString str) {
    m_snackbar_success->addMessage(str);
}

// 失败消息弹窗
void MainWindow::fail_snack_slot(QString str) {
    m_snackbar_fail->addMessage(str);
}

void MainWindow::Main_Oupt(QString str,int color)
{
    ui->m_output->append(ChangeColor(str,color));
}



/*************************************************
 <函数名>      add_order_toList
 <概要说明>    任务指令添加
 <详细说明>
    Order_List_Object结构体为参数结构体
    mode代表指令模式 0-新增模式 1-修改模式

 <作    者>   zm
 <时    间>   2023-03-21
 <修    改>
**************************************************/
void MainWindow::add_order_toList(const QVariant varData) {

    m_tab_daohang->QtMaterialTabs::currentChanged(0);
    Order_List_Object rec_data = varData.value<Order_List_Object>();
    // 判断指令模式
    if (rec_data.mode)  // 修改模式
    {
    } else {  // 新增模式
        disconnect(model_list, &QStandardItemModel::itemChanged, this, &MainWindow::change_list_time);

        QVector<int> sum_id;
        if(inOder_falg)//如果是导入指令
        {
            sum_id.append(rec_data.obj_id);
        }
        else
        {
            if(startOder_Tim==true)//星时指令标志（特殊指令，一条全选单机指令）
            {
                startOder_Tim=false;
                sum_id.append(4);//全选单机标志
            }
            else
            {
                sum_id=p_view_task->Obj_ID();//获取单机编号
            }
        }

        int cnt = order_data_list.size();
        if(!inOder_falg)//不是导入指令，发送时间固定+1
        {
            rec_data.start_time = ORDER_GAP_TIME;
            //rec_data.order_id = cnt;
            if (cnt != 0) {
                Order_List_Object t_last = order_data_list[cnt - 1];
                rec_data.start_time = (t_last.start_time + rec_data.gap_time);
            }
        }
        for(int id=0;id<sum_id.size();id++)//生成对应单机指令
        {
            cnt = order_data_list.size();//一次性多条指令，发送时间一样
            // 显示指令内容到界面上
            QString str = "";
            // 目标单机
            //str = QString("%1").arg(cnt);
            str = QString("单机%1").arg(sum_id.at(id)+1);
            if(sum_id.at(id)==4)str="全选";
            rec_data.obj_id=sum_id.at(id);//获取单机序号
            model_list->setItem(cnt, 0, new QStandardItem(str));

            //if(id==0)model_list->setData(model_list->index(cnt,0),QBrush(Qt::red),Qt::TextColorRole);//单机1
            if(sum_id.at(id)==1)model_list->setData(model_list->index(cnt,0),QBrush(QColor(135,0,25)),Qt::TextColorRole);//单机2，深红色
            if(sum_id.at(id)==2)model_list->setData(model_list->index(cnt,0),QBrush(QColor(65,70,200)),Qt::TextColorRole);//单机3，深蓝色
            if(sum_id.at(id)==3)model_list->setData(model_list->index(cnt,0),QBrush(QColor(15,210,70)),Qt::TextColorRole);//单机4，深绿色
            if(sum_id.at(id)==4)model_list->setData(model_list->index(cnt,0),QBrush(QColor(140,50,140)),Qt::TextColorRole);//单机全选,紫色
            // PID
            str = QString("%1").arg(rec_data.page_id);
            model_list->setItem(cnt, 1, new QStandardItem(str));
            // 发送时间
            str = QString("%1").arg(rec_data.start_time);
            model_list->setItem(cnt, 2, new QStandardItem(str));
            // 名称
            model_list->setItem(cnt, 3, new QStandardItem(rec_data.order_name));
            // 类型
            //str = QString("%1").arg(rec_data.order_kind);
            str=Ord_Kind[rec_data.order_kind];
            model_list->setItem(cnt, 4, new QStandardItem(str));
            // 长度
            str = QString("%1").arg(rec_data.order_len);
            model_list->setItem(cnt, 5, new QStandardItem(str));
            // 内容
            str = "";
            QString tmp_byte;
            for (int readLen = 0; readLen < rec_data.order_len; readLen++) {
                tmp_byte = QString().asprintf("%02x ", rec_data.data_buf[readLen]);
                str.append(tmp_byte);
            }
            model_list->setItem(cnt, 6, new QStandardItem(str));
            Order_List_Object new_order = rec_data;
            order_data_list.append(new_order);
        }


        inOder_falg=false;//导入指令标志
        connect(model_list, &QStandardItemModel::itemChanged, this, &MainWindow::change_list_time);
    }
}




//总线指令
int MainWindow::Send_1553SubOrder(int num,bool head,int addr)
{

    //总线指令长度短，不考虑多帧情况
    uchar* Txbuf=new uchar[sizeof (STR_1553BusInstr)];
    //第一层封装
    STR_1553BusInstr strbusInstr;
    strbusInstr.packmark_a=0;
    strbusInstr.packmark_b=1;
    strbusInstr.packmark_c=0;
    strbusInstr.packmark_d1=0x07;
    strbusInstr.packmark_d2=0x31;

    strbusInstr.packsequence_a=3;
    strbusInstr.packsequence_b1=0;
    strbusInstr.packsequence_b2=0;

    strbusInstr.packLen=qToBigEndian((ushort)5);
    strbusInstr.funrecog=0;
    //读取原始数据
    memcpy(strbusInstr.applybuff,order_data_list.at(num).data_buf,sizeof (strbusInstr.applybuff));

    //按字异或和校验
    ushort* checkbuff=new ushort[(2+sizeof (strbusInstr.applybuff))/2];
    memcpy(checkbuff,(uchar*)&strbusInstr.funrecog,2+sizeof(strbusInstr.applybuff));
    ushort crc2=0;
    for(uint n=0;n<(2+sizeof(strbusInstr.applybuff))/2;n++)
    {
        crc2=crc2^checkbuff[n];
    }
    //strbusInstr.andcheck=qToBigEndian(crc2);
    strbusInstr.andcheck=crc2;
    delete [] checkbuff;

    memcpy(Txbuf,(uchar*)&strbusInstr,sizeof(strbusInstr));

    //1553板块发送
    int status=-1;
    if(head)
    {
        Get_PackOrder(Txbuf,sizeof (strbusInstr));
    }
    else status=Card_1553Can->OnceSend_Data(Txbuf,sizeof (strbusInstr),19,5,addr);

    delete [] Txbuf;

    return status;
}


//总线注数
int MainWindow::Send_1553OverOrder(int num,bool head,int addr)
{
    //功能识别码
    map<char,ushort> funkind;
    funkind[2]=0x0086;
    funkind[3]=0x0088;
    funkind[4]=0x0081;
    funkind[5]=0x0082;
    funkind[7]=0x0083;
    funkind[8]=0x0084;
    funkind[11]=0x0089;
    funkind[12]=0x008A;
    funkind[13]=0x0085;

    funkind[14]=0x0010;
    funkind[15]=0x0011;
    funkind[16]=0x0012;
    funkind[17]=0x0013;
    funkind[18]=0x0014;
    funkind[19]=0x0015;


    int orderlen=order_data_list.at(num).order_len;
    int framecnt=(orderlen+ORI_LEN-1)/ORI_LEN;
    uchar* Txbuf=new uchar[sizeof (STR_1553OverInstr)*framecnt+1];
    for(int i=0;i<framecnt;i++)
    {
        ushort thislen=ORI_LEN;//当前帧长度
        if(i==(framecnt-1))thislen=orderlen % ORI_LEN;//最后一帧
        int tmplen=thislen;//原始数据奇数长度需要补0x2A到偶数
        //第一层封装
        STR1553_SubPack str1553over;
        str1553over.Len=qToBigEndian(thislen);
        if(framecnt==1){
            str1553over.framemark=0;
        }
        else{
            if(i==0)str1553over.framemark=qToBigEndian((ushort)1);
            else if(i==(framecnt-1))str1553over.framemark=qToBigEndian((ushort)3);
            else str1553over.framemark=qToBigEndian((ushort)2);
        }
        str1553over.frameNUM=qToBigEndian((uint)i);

        //拷贝原始数据
        if(thislen%2!=0)tmplen+=1;
        str1553over.priDataBuff=new uchar[tmplen];
        memset(str1553over.priDataBuff,0x2A,tmplen);
        memcpy(str1553over.priDataBuff,order_data_list.at(num).data_buf+(i*ORI_LEN),thislen);

        //计算校验位
        //        ushort* checkbuff=new ushort[(4+tmplen)/2];
        //        memcpy(checkbuff,(uchar*)&str1553over.framemark,4);
        //        memcpy(checkbuff+2,str1553over.priDataBuff,tmplen);
        //        ushort crc=0;
        //        for(int n=0;n<(4+tmplen)/2;n++)
        //        {
        //            crc+=checkbuff[n];
        //        }
        //        crc=~crc;
        //        str1553over.checksum=qToBigEndian(crc);
        //        delete [] checkbuff;
        //第二层封装////////////////////////////////////////////////////////////
        STR_1553OverInstr stroverInstr;
        stroverInstr.packmark_a=0;
        stroverInstr.packmark_b=1;
        stroverInstr.packmark_c=0;
        stroverInstr.packmark_d1=0x07;
        stroverInstr.packmark_d2=0x31;

        stroverInstr.packsequence_a=3;
        stroverInstr.packsequence_b1=(i&0x3F00)>>8;
        stroverInstr.packsequence_b2=i;

        //stroverInstr.packLen=qToBigEndian((ushort)(4+thislen));
        stroverInstr.packLen=qToBigEndian((ushort)(249));//写死
        stroverInstr.funrecog=qToBigEndian(funkind[order_data_list.at(num).order_kind]);

        memset(stroverInstr.applybuff,0x2A,sizeof (stroverInstr.applybuff));
        //读取应用数据
        memcpy(stroverInstr.applybuff,&str1553over,8);
        memcpy(stroverInstr.applybuff+8,str1553over.priDataBuff,tmplen);
        //memcpy(stroverInstr.applybuff+8+tmplen,&str1553over.checksum,2);
        //按字异或和校验
        ushort* checkbuff2=new ushort[(2+sizeof (stroverInstr.applybuff))/2];
        memcpy(checkbuff2,(uchar*)&stroverInstr.funrecog,2+sizeof(stroverInstr.applybuff));
        ushort crc2=0;
        for(uint n=0;n<(2+sizeof(stroverInstr.applybuff))/2;n++)
        {
            crc2=crc2^checkbuff2[n];
        }
        //stroverInstr.andcheck=qToBigEndian(crc2);
        stroverInstr.andcheck=crc2;
        delete [] checkbuff2;
        delete [] str1553over.priDataBuff;

        //存储数据
        memcpy(Txbuf+(i*sizeof (stroverInstr)),(uchar*)&stroverInstr,sizeof (stroverInstr));

    }

    int status=-1;
    //1553板块发送
    if(head)
    {
        Get_PackOrder(Txbuf,sizeof (STR_1553OverInstr)*framecnt);
    }
    else status=Card_1553Can->OnceSend_Data(Txbuf,sizeof (STR_1553OverInstr)*framecnt,19,2,addr);

    delete [] Txbuf;

    return status;
}

//模式控制指令
int MainWindow::Send_1553ModeOeder(int num,int addr)
{
    //1553板块发送
    int status=-1;

    status=Card_1553Can->OnceSend_Data(order_data_list.at(num).data_buf,order_data_list.at(num).order_len,19,1,addr);


    return status;
}

uint Remove_canid(CAN_DATA cd)
{
    uint tmp=0;
    tmp=cd.frameN+(cd.comtype<<8)+(cd.tr_addr<<10)+(cd.re_addr<<18)+(cd.priotity<<27)+(cd.send_mark<<28);
    return tmp;
}

//CAN数据发送
int MainWindow::Send_CancardOeder(int num)
{
    int order_len=order_data_list.at(num).order_len;
    uchar* pData=order_data_list.at(num).data_buf;//传递数据地址

    CAN_seccues=true;//

    int status=-1;

    status=CAN_DataSend(pData, order_len);//can封装发送


    return status;
}


//CAN发送封装函数
int MainWindow::CAN_DataSend(uchar *pData, int order_len)
{

    int frame_cnt=(order_len+7)/8;//can帧总数(一帧8字节)
    ZCAN_Transmit_Data* Frame_can=new ZCAN_Transmit_Data[257];//一条指令可以由多个数据帧组成，最多为256帧，包含2048字节数据。
    if(frame_cnt>256)
    {
        delete [] Frame_can;
        return -1;
    }
    uint index=0;
    uint canid=0;
    //canID帧头仲裁场标识符定义0~28bit
    CAN_DATA cd;
    cd.send_mark=0; //发送标志
    cd.priotity=0;  //动态优先级标志
    cd.tr_addr=0x10;//发送节点站地址

    uchar addrtmp=ui->cB_can_RecvieAddr->currentIndex();
    cd.re_addr=mRe_Addr[addrtmp];//接收节点站地址
    //qDebug()<<cd.re_addr;


    for(int n=0;n<frame_cnt;n++)//发送多条can帧
    {
        //发送方式，0=正常发送，1=单次发送，2=自发自收，3=单次自发自收。
        Frame_can[n].transmit_type=0;

        //单帧。。。。。。。。
        if(frame_cnt==1)
        {
            cd.comtype=0;   //指令数据帧类型
            cd.frameN=n;    //帧序号
            canid=Remove_canid(cd);
            Frame_can[n].frame.can_id = MAKE_CAN_ID(canid, 1, 0, 0);
            //帧 ID，32 位
            //第 31 位(最高位)代表扩展帧标志，=0 表示标准帧，=1 代表扩展帧，宏 IS_EFF 可获取
            //第 30 位代表远程帧标志，=0 表示数据帧，=1 表示远程帧，宏 IS_RTR 可获取该标志；
            //第 29 位代表错误帧标准，=0 表示 CAN 帧，=1 表示错误帧，目前只能设置为 0；
            Frame_can[n].frame.can_dlc = order_len;
            memcpy(Frame_can[n].frame.data, &pData[index], Frame_can[n].frame.can_dlc);
            index+=8;
        }
        //多帧。。。。。。。。
        else
        {
            if(n==0)//首帧
            {
                cd.comtype=1;//指令数据帧类型
                cd.frameN=n;//帧序号
                canid=Remove_canid(cd);
                Frame_can[n].frame.can_id = MAKE_CAN_ID(canid, 1, 0, 0);
                Frame_can[n].frame.can_dlc = 8;
                memcpy(Frame_can[n].frame.data, &pData[index], Frame_can[n].frame.can_dlc);
                index+=8;
            }
            else if((n+1)==frame_cnt)//尾帧
            {

                cd.comtype=3;//指令数据帧类型
                cd.frameN=n;//帧序号
                canid=Remove_canid(cd);
                Frame_can[n].frame.can_id = MAKE_CAN_ID(canid, 1, 0, 0);
                Frame_can[n].frame.can_dlc = order_len-n*8;
                memcpy(Frame_can[n].frame.data, &pData[index], Frame_can[n].frame.can_dlc);

            }
            else//中间帧
            {
                cd.comtype=2;//指令数据帧类型
                cd.frameN=n;//帧序号
                canid=Remove_canid(cd);
                Frame_can[n].frame.can_id = MAKE_CAN_ID(canid, 1, 0, 0);
                Frame_can[n].frame.can_dlc = 8;
                memcpy(Frame_can[n].frame.data, &pData[index], Frame_can[n].frame.can_dlc);
                index+=8;

            }
        }

    }

    //处理待发送数据，传入（封装数据，数据帧长度）
    uint ch=ui->cB_can_channel->currentIndex();//发送通道
    int status=0;
    if(CAN_seccues)status=Card_can->SendCanCardData(Frame_can,frame_cnt,ch);//CAN发送
    if(status==-1)
    {
        if(switch_CANboard==false)//界面点击了开启
        {
            Card_1553Can->Flag_CANboard=false;//关闭can广播，否则会一直发卡死
            ui->pB_CAN_board_onoff->setText("CAN广播消息_开启");
            switch_CANboard=true;
            CAN_seccues=false;
            ui->pB_1553on_off->setEnabled(1);//1553周期消息
            ui->pushButton_board_onoff->setEnabled(1);//1553广播消息
            QDateTime tm=QDateTime::currentDateTime();
            QString stm=tm.toString("hh:mm:ss");
            QMessageBox::information(this,"提示",QString("CAN链路不通 %1,正在关闭广播").arg(stm));
        }
        else
        {
            QMessageBox::information(this,"提示","CAN链路不通");
        }


    }

    delete [] Frame_can;

    return status;
}
//信号源指令发送
int MainWindow::Send_Signal(int num)
{
    int status=0;
    Signal_Str str;
    memset(&str,0,sizeof (str));
    memcpy(&str,order_data_list.at(num).data_buf,sizeof (str));

    if(ui->rad_xh1->isChecked())status+=signalConrtl[0]->setSignal_data(str);
    if(ui->rad_xh2->isChecked())status+=signalConrtl[1]->setSignal_data(str);
    return status;
}


void MainWindow::change_list_time(QStandardItem *item)
{
    if(2 == item->column())
    {
        QString tempString = item->text();
        order_data_list[item->row()].start_time = tempString.toInt();
    }
}
//游戏界面初始化
void MainWindow::m_GamesInit()
{
    Games=new m_games();
    Games->setWindowTitle("x.x");
    Games->setFixedSize(300,400);
    connect(Games, &m_games::Show_ViewClose,this,&MainWindow::close_GameView);//关闭界面

    //指令翻译初始化
    Tran_Mess=new Translate();
    Tran_Mess->setWindowTitle("指令解析");
    QPoint globalPos=this->pos();
    int wid = this->width();
    int hig = this->height();
//    Tran_Mess->setFixedSize(wid/3,hig/1.5);
    Tran_Mess->move(globalPos.x()+wid-Tran_Mess->width(),globalPos.y()+(hig-Tran_Mess->height())/2);
    connect(this,&MainWindow::Trans_order_toView,Tran_Mess, &Translate::Trans_to_Oder);
}

//隐藏游戏
void MainWindow::tab_game_change(int index)
{
    Q_UNUSED(index);
    Games->show();
}

//关闭游戏窗口
void MainWindow::close_GameView()
{
    Games->close();
}

void MainWindow::gif_change()
{
    //qDebug()<<"mouse";

    //加载用于背景的 GIF 文件(随机)
    int ss=rand()%yyh_ListPic.size();
    backgroundMovie = new QMovie(":/new/prefix1/Pic/"+yyh_ListPic.at(ss));//这里替换为你的GIF文件地址即可
    // 加载用于背景的 GIF 文件(循环)
//    backgroundMovie = new QMovie(":/new/prefix1/Pic/"+yyh_ListPic.at(picNum++));//这里替换为你的GIF文件地址即可
//    if(picNum>yyh_ListPic.size()-1)picNum=0;
    // 将 QMovie 关联到 QLabel
    backgroundLabel->setMovie(backgroundMovie);
    // 开始播放背景 GIF 动画
    backgroundMovie->start();
}

void MainWindow::gif_change_right()
{
    // 加载用于背景的 GIF 文件
    //backgroundMovie = new QMovie(":/new/prefix1/Pic/face-sad.png");//这里替换为你的GIF文件地址即可
    backgroundMovie = new QMovie();//这里替换为你的GIF文件地址即可
    // 将 QMovie 关联到 QLabel
    backgroundLabel->setMovie(backgroundMovie);
    // 开始播放背景 GIF 动画
    //backgroundMovie->start();
}

//翻译指令内容
void MainWindow::Translate_Order()
{
    QModelIndex index = ui->ui_task_list->selectionModel()->currentIndex();
    int row = index.row();
    if (row < 0) return;
    QVariant varData;
    varData.setValue(order_data_list[row]);
    emit Trans_order_toView(varData);

    //翻译界面显示
//    QPoint globalPos=this->mapToGlobal(QPoint(0,0));
//    Tran_Mess->move(globalPos.x()+wid,globalPos.y()+100);



    Tran_Mess->showNormal();
    Tran_Mess->activateWindow();

}

/*************************************************
 <函数名>   Return_To_SubView
 <概要说明>    无
 <详细说明>    无

 <作    者>   zm
 <时    间>   2023-03-23
 <修    改>
**************************************************/
void MainWindow::Return_To_SubView() {
    QModelIndex index = ui->ui_task_list->selectionModel()->currentIndex();
    int row = index.row();
    if (row < 0) return;
    m_tab_daohang->QtMaterialTabs::currentChanged(1);
    QVariant varData;
    varData.setValue(order_data_list[row]);
    emit Return_order_toView(varData);
}

//右键导出指令(全部导出，没有单行)
void MainWindow::Export_order()
{
    //选择保存文件
    QString qFileName = QFileDialog::getSaveFileName(this, tr("选择保存路径"),"",tr("*.xlsx ;; *.txt "));
    if(qFileName.isEmpty())return;

    //判断后缀
    QFileInfo fileinfo(qFileName);
    QString Fsuffix=fileinfo.suffix();

    //取消选中区域
    ui->ui_task_list->clearSelection();
    //区分类型保存
    if(Fsuffix=="xlsx")
    {
        QXlsx::Document xlsx;
        int row=ui->ui_task_list->model()->rowCount();
        int col=ui->ui_task_list->model()->columnCount();
        int tmpi=0;
        //        if(ui->ui_task_list->selectionModel()->hasSelection())//只选择单行
        //        {
        //            QMessageBox::information(this,"提示","已选择单行导出");
        //            QModelIndex qMIndex = ui->ui_task_list->selectionModel()->currentIndex();
        //            tmpi = qMIndex.row();
        //            row=tmpi+1;
        //        }
        //设置列宽
        xlsx.setColumnWidth(4,5,20);//开始列，结束列，列宽
        xlsx.setColumnWidth(7,100);//第7列，20列宽
        //获取列表头
        for (int n=0;n<col;n++) {
            QString strhead=ui->ui_task_list->model()->headerData(n,Qt::Horizontal).toString();
            xlsx.write(1, n+1,strhead);
        }
        //获取内容
        for (int i=tmpi;i<row;i++) {
            for (int j=0;j<col;j++) {
                QString tmp_str;
                int tmp_int=0;

                QModelIndex index=ui->ui_task_list->model()->index(i,j);
                if((j==0)||(j==1)||(j==2)||(j==5))
                {
                    tmp_int=index.data().toInt();//整型
                    xlsx.write(i+2, j+1,tmp_int);
                }
                else
                {
                    tmp_str=index.data().toString();//字符串格式
                    xlsx.write(i+2, j+1,tmp_str);
                }

            }
        }
        if (!xlsx.saveAs(qFileName)) {
            QMessageBox::warning(this, "提示", "文件保存失败");
            return;
        }
        xlsx.deleteLater();//释放指针
    }
    else if(Fsuffix=="txt")
    {

        QFile qFile(qFileName);
        if(!qFile.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::information(this,"提示","文件打开错误");
            return;
        }

        int tmpi=0;//表格起始行
        int tmpsum=order_data_list.size();//表格总行
        //        if(ui->ui_task_list->selectionModel()->hasSelection())//只选择单行
        //        {
        //            QMessageBox::information(this,"提示","已选择单行导出");
        //            QModelIndex qMIndex = ui->ui_task_list->selectionModel()->currentIndex();
        //            tmpi = qMIndex.row();
        //            tmpsum=tmpi+1;
        //        }

        QByteArray data;
        QString str;

        for (int i = tmpi; i < tmpsum; i++) {
            data.clear();
            str = QString("OID;%1\n").arg(i);
            data.append(str);

            str = QString("PID;%1\n").arg(order_data_list[i].page_id);
            data.append(str);

            str = QString("发送时间;%1\n").arg(order_data_list[i].start_time);
            data.append(str);

            //str = QString("名称: %1 \n").arg(order_data_list[i].order_name);//生成内存内容导出
            str = QString("名称;%1\n").arg(model_list->item(i,3)->text());//根据界面修改名字导出
            data.append(str);

            str = QString("类型;%1\n").arg(order_data_list[i].order_kind);
            data.append(str);

            str = QString("长度;%1\n").arg(order_data_list[i].order_len);
            data.append(str);

            QString byteArray;
            for (int j = 0; j < order_data_list[i].order_len; j++) {
                byteArray += QString().asprintf("%02x ", order_data_list[i].data_buf[j]); // 末尾会留出一个空格
            }
            str = QString("指令内容;%1\r\n").arg(byteArray);
            data.append(str);

            qFile.write(data.data()); // 数据写入文件
        }
        qFile.close();

    }
    else
    {
        QMessageBox::information(this,"提示","文件未识别后缀");
        return;
    }

    emit success_snack_slot("导出成功");

}

//导出指令内容源码16进制
void MainWindow::Export_orderSource()
{


    QModelIndex qMIndex = ui->ui_task_list->selectionModel()->currentIndex();
    int table_row = qMIndex.row();

    QDateTime cur_time = QDateTime::currentDateTime();
    QString strtime = cur_time.toString("hh-mm-ss");

    //    QSettings setting("./Setting.ini",QSettings::IniFormat);
    //    QString lastPath=setting.value("LastFilePath").toString();

    //    QString qFileName = QFileDialog::getSaveFileName(this, tr("save file(.dat)"),
    //                                                     "/"+order_data_list[table_row].order_name + strtime,tr("dat(*.dat)"));
    QString qFileName = QFileDialog::getSaveFileName(this, tr("save file(.dat)"),"",tr("dat(*.dat)"));

    if(qFileName.isEmpty())return;
    QFile qFile(qFileName);
    if(!qFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(this,"提示","文件打开错误");
        return;
    }

    //写入dat文件
    qFile.write((char*)order_data_list[table_row].data_buf,order_data_list[table_row].order_len);
    qFile.close();

    //qDebug()<<"source...";
    emit success_snack_slot("导出成功");

}

//OC上电
void MainWindow::on_pB_OcPowerup_clicked()
{

    uchar oc_order1[6]={1,15,2,12,14,11};//最后主份波束控制器开
    uchar oc_order2[6]={1,15,2,12,14,13};//最后备份波束控制器开

    for(int i=0;i<6;i++)
    {
        OC_power_control opc;
        opc.ordermark = 0x07;
        if(ui->cB_ocpowerZB->currentIndex())//1备份
        {
            opc.power_choose = oc_order2[i];
        }
        else
        {
            opc.power_choose = oc_order1[i];
        }


        //列表封装
        Order_List_Object order_data;
        order_data.mode = false;
        order_data.page_id = 0;
        order_data.start_time=10;
        order_data.gap_time = 1;
        order_data.order_name = QString("OC电压控制");
        order_data.order_kind = 1;
        order_data.order_len = sizeof(opc);
        order_data.data_buf = new uchar[order_data.order_len];
        memcpy(order_data.data_buf, &opc, sizeof(opc));
        QVariant varData;
        varData.setValue(order_data);
        add_order_toList(varData);
    }

}


void MainWindow::on_pB_OcPowerlow_clicked()
{
    uchar oc_order[3]={12,14,16};//最后主份波束控制器开

    for(int i=0;i<3;i++)
    {
        OC_power_control opc;
        opc.ordermark = 0x07;

        opc.power_choose = oc_order[i];

        //列表封装
        Order_List_Object order_data;
        order_data.mode = false;
        order_data.page_id = 0;
        order_data.start_time=0;
        order_data.gap_time = 1;
        order_data.order_name = QString("OC电压控制");
        order_data.order_kind = 1;
        order_data.order_len = sizeof(opc);
        order_data.data_buf = new uchar[order_data.order_len];
        memcpy(order_data.data_buf, &opc, sizeof(opc));
        QVariant varData;
        varData.setValue(order_data);
        add_order_toList(varData);
    }
}

void MainWindow::on_m_button_delog_clicked()
{
    ui->m_output->clear();

}





void MainWindow::on_pushButton_starttime_test_clicked()
{
    Card_1553Can->StartTimeBroadMessage(0);//A路
}


void MainWindow::on_pushButton_Orbitalstance_test_clicked()
{
    Card_1553Can->OrbitalMessage(0);
    Card_1553Can->v_orb.resize(0);
}

//GNSS时间码
void MainWindow::on_pB_GNSStimecode_test_clicked()
{
    Card_1553Can->GNSS_timecodeMessage();
}


//GNSS定位数据
void MainWindow::on_pB_GNSSposition_test_clicked()
{
    Card_1553Can->GNSS_postionMessage(0);
    Card_1553Can->v_gnss_postion.resize(0);

}
//GNSS定轨数据
void MainWindow::on_pB_GNSStrack_test_clicked()
{
    Card_1553Can->GNSS_trackMessage(0);
    Card_1553Can->v_gnss_orbit.resize(0);
}


void MainWindow::contrl_pB()
{
    if(switch_1553cyc && switch_1553board && switch_CANboard)
    {
        ui->pB_1553on_off->setEnabled(1);//1553周期消息
        ui->pushButton_board_onoff->setEnabled(1);//1553广播消息
        ui->pB_CAN_board_onoff->setEnabled(1);//CAN广播消息
    }
    else if(!switch_CANboard)
    {
        ui->pB_1553on_off->setEnabled(0);//1553周期消息
        ui->pushButton_board_onoff->setEnabled(0);//1553广播消息
    }
    else if((!switch_1553cyc)||(!switch_1553board))
    {
        ui->pB_CAN_board_onoff->setEnabled(0);//CAN广播消息
    }
    else{}
}


//1553周期发送开关(默认开)
void MainWindow::on_pB_1553on_off_clicked()
{

    //默认开启1553周期发送，所以界面显示关闭
    if(switch_1553cyc)//开启
    {
        Card_1553Can->cyc1553_onoff(switch_1553cyc);
        ui->pB_1553on_off->setText("1553周期消息_关闭");
        switch_1553cyc=false;

        if(1)//15553周期开启后 关闭CAN通信
        {
            Card_1553Can->Flag_CANboard=false;
            ui->pB_CAN_board_onoff->setText("CAN广播消息_开启");
            switch_CANboard=true;

        }


    }
    else {//关闭
        Card_1553Can->cyc1553_onoff(switch_1553cyc);
        ui->pB_1553on_off->setText("1553周期消息_开启");
        switch_1553cyc=true;
    }

    contrl_pB();//控件使能


}

//1553广播开关(默认关)
void MainWindow::on_pushButton_board_onoff_clicked()
{

    //默认关闭1553广播发送，所以界面显示开启
    if(switch_1553board)//开启
    {
        //Card_1553Can->timer1553->start(1000);
        Card_1553Can->Flag_1553board=true;
        ui->pushButton_board_onoff->setText("1553广播消息_关闭");
        switch_1553board=false;

        if(1)//15553广播开启后 关闭CAN通信
        {
            Card_1553Can->Flag_CANboard=false;
            ui->pB_CAN_board_onoff->setText("CAN广播消息_开启");
            switch_CANboard=true;
        }
    }
    else {//关闭
        //Card_1553Can->timer1553->stop();
        Card_1553Can->Flag_1553board=false;
        ui->pushButton_board_onoff->setText("1553广播消息_开启");
        switch_1553board=true;
    }
    contrl_pB();//控件使能
}

//CAN广播消息开启 关闭
void MainWindow::on_pB_CAN_board_onoff_clicked()
{
    //默认关闭CAN广播发送，所以界面显示开启
    if(switch_CANboard)//开启
    {

        Card_1553Can->Flag_CANboard=true;
        ui->pB_CAN_board_onoff->setText("CAN广播消息_关闭");
        switch_CANboard=false;
        CAN_seccues=true;

        if(1)//CAN开启后 关闭1553通信
        {
            Card_1553Can->cyc1553_onoff(switch_1553cyc);
            ui->pB_1553on_off->setText("1553周期消息_开启");
            switch_1553cyc=true;

            Card_1553Can->Flag_1553board=false;
            ui->pushButton_board_onoff->setText("1553广播消息_开启");
            switch_1553board=true;
        }

    }
    else {//关闭

        Card_1553Can->Flag_CANboard=false;
        ui->pB_CAN_board_onoff->setText("CAN广播消息_开启");
        switch_CANboard=true;
    }
    contrl_pB();//控件使能
}

//星时,GNSS时间设置
void MainWindow::on_pushButton_ChangTimeUI_clicked()
{
    Card_1553Can->m_nTimerCounter=ui->UI_TIMES_IN->text().toUInt();
    ssss_test=ui->UI_TIMES_IN->text().toUInt();
}
//在线自测试
void MainWindow::on_pushButton_SelfTest_clicked()
{
    Card_1553Can->OnlineMessage();
}
//系统同步
void MainWindow::on_pushButton_xttb_clicked()
{
    Card_1553Can->SystemStepMessage();
}
//长抱环
void MainWindow::on_pushButton_longbh_clicked()
{
    Card_1553Can->LongringMessage();
}



//启动默认读取指定路径表格
void MainWindow::Get_boardFirst()
{
    //打开文件选择对话框
    QString file_path =QCoreApplication::applicationDirPath();//引用程序路径
    file_path=file_path.left(file_path.lastIndexOf("/"));
    if(file_path.isEmpty()) return;

    gdzt_read(file_path+"/地检广播数据存放/姿轨广播.xlsx");     //轨道姿态数据读取xlsx
    gnss_dw(file_path+"/地检广播数据存放/定位广播.xlsx");       //GNSS定位读取xlsx
    gnss_dg(file_path+"/地检广播数据存放/定轨广播.xlsx");       //GNSS定轨读取xlsx
}

void MainWindow::gifGround()
{
    //QString str=QDir::currentPath();//当前工作目录（.pro不包含debug，快捷方式包含debug）
    //QString str=QCoreApplication::applicationDirPath();//获取程序所在路径(debug目录下)
    QString str=":/new/prefix1/Pic";//获取程序所在路径(debug目录下)
    //QString str2=qApp->applicationFilePath();//获取程序所在完整路径（包含exe）
    //QString str3="../";//当前程序上级目录

    QDir dir(str);
    QStringList filename;
    filename<<"*.gif";

    if(dir.exists())//当前目录下
    {
        QStringList results;
        results = dir.entryList(filename,QDir::Files | QDir::Readable,QDir::Name);
        //qDebug()<<results;//results里就是获取的所有文件名了
        yyh_ListPic=results;
    }


    // 创建 QLabel 并将其设置为 Widget 的子控件
    backgroundLabel = ui->label_mgif;
    //backgroundLabel->setGeometry(0, 0, this->width(), this->height()); // 初始大小
    backgroundLabel->setScaledContents(true); // 让 QLabel 自动缩放内容

    // 加载用于背景的 GIF 文件
    backgroundMovie = new QMovie(":/new/prefix1/Pic/yyh_22.gif");//这里替换为你的GIF文件地址即可 yyh_0.gif(猫)

    // 将 QMovie 关联到 QLabel
    backgroundLabel->setMovie(backgroundMovie);

    // 设置 QLabel 为透明背景
    backgroundLabel->setAttribute(Qt::WA_TranslucentBackground, true);

    // 设置 QLabel 在布局的最底层
    backgroundLabel->lower();

    // 开始播放背景 GIF 动画
    backgroundMovie->start();

    // 调整背景大小，使其始终填满窗口
//    connect(backgroundMovie, &QMovie::frameChanged, ui->label_mgif, [=]() {
//        // 计算缩放后的尺寸
//        QPixmap scaledPixmap = backgroundMovie->currentPixmap().scaled(ui->label_mgif->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
//        backgroundLabel->setPixmap(scaledPixmap);
//    });

    // 创建用于 ui->lab_icon 的 QMovie 并加载 GIF 动图
//    iconMovie = new QMovie(":/imgs/a.gif");

//    // 设置 QLabel 的 QMovie
//    ui->lab_icon->setMovie(iconMovie);

//    // 启动动画
//    iconMovie->start();

//    connect(iconMovie, &QMovie::frameChanged, this, [=]() {
//        // 获取当前帧并缩放
//        QImage currentImage = iconMovie->currentImage(); // 获取当前帧
//        QPixmap pixmap = QPixmap::fromImage(currentImage.scaled(ui->lab_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        ui->lab_icon->setPixmap(pixmap); // 设置 QLabel 的 pixmap
//    });

//    iconMovie->stop();
}



//轨道姿态数据广播xlsx表格读取
void MainWindow::on_pB_GDZT_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"轨道姿态数据选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;
    gdzt_read(file_path);


}
//轨道姿态数据读取xlsx
void MainWindow::gdzt_read(QString path)
{
    Document xlsxR(path);//软件关闭会显示异常关闭

    Card_1553Can->v_orb.resize(0);//1553的
    v_orb_can.resize(0);//can的
    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }
    Orbitalstance_Data_xlsx v_slsx;

    int rowsum=xlsxR.dimension().rowCount();
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        memset(&v_slsx,0,sizeof(v_slsx));
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)v_slsx.thistime=var.toUInt();
                //单机1,2,3,4
                if(j==2||j==5||j==8||j==11)v_slsx.rolling_angle[j/3]=var.toInt()*10000;//(0.0001度)
                if(j==3||j==6||j==9||j==12)v_slsx.pitch_angle[(j-1)/3]=var.toInt()*10000;
                if(j==4||j==7||j==10||j==13)v_slsx.yawing_angle[(j-2)/3]=var.toInt()*10000;
            }
        }
        Card_1553Can->v_orb.push_back(v_slsx);//1553B的
        v_orb_can.push_back(v_slsx);//can的

    }
    ui->radioButton_zg_flag->setChecked(1);//轨道姿态读表标志
}

//读取gnss定位数据xlxs
void MainWindow::on_pB_GnssPostion_xlsx_clicked()
{

    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"GNSS定位数据选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;
    gnss_dw(file_path);

}
//GNSS定位读取xlsx
void MainWindow::gnss_dw(QString path)
{
    Document xlsxR(path);//软件关闭会显示异常关闭

    Card_1553Can->v_gnss_postion.resize(0);//1553的
    v_gnss_postion_can.resize(0);//can的
    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }
    int rowsum=xlsxR.dimension().rowCount();
    int colsum=xlsxR.dimension().columnCount();
    GNSS_Positioning_xlsx v_slsx;

    for(int i=2;i<rowsum+1;i++)//行
    {
        memset(&v_slsx,0,sizeof(v_slsx));
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)//Time (UTCG)
                {
                    int tmp=var.toInt();
                    //qDebug()<<tmp;
                    v_slsx.time_s=tmp;
                }
                else
                {
                    double tmpd=var.toDouble();
                    if(j==2||j==8||j==14||j==20)v_slsx.position_x[j/6]=(int)(tmpd*100000);//(km)->(0.01m)
                    if(j==3||j==9||j==15||j==21)v_slsx.position_y[(j-1)/6]=(int)(tmpd*100000);
                    if(j==4||j==10||j==16||j==22)v_slsx.position_z[(j-2)/6]=(int)(tmpd*100000);

                    if(j==5||j==11||j==17||j==23)v_slsx.speed_x[(j-3)/6]=(int)(tmpd*10000000);//(km/s) ->(0.01cm/s)
                    if(j==6||j==12||j==18||j==24)v_slsx.speed_y[(j-4)/6]=(int)(tmpd*10000000);
                    if(j==7||j==13||j==19||j==25)v_slsx.speed_z[(j-5)/6]=(int)(tmpd*10000000);
                }

            }
        }

        Card_1553Can->v_gnss_postion.push_back(v_slsx);//1553的
        v_gnss_postion_can.push_back(v_slsx);//can的
    }

    ui->radioButton_dw_flag->setChecked(1);//定位读表标志
}



//读取GNSS定轨数据xlxs
void MainWindow::on_pB_orbit_xlsx_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"GNSS定轨选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    gnss_dg(file_path);
}


//GNSS定轨读取xlsx
void MainWindow::gnss_dg(QString path)
{
    Document xlsxR(path);//软件关闭会显示异常关闭

    Card_1553Can->v_gnss_orbit.resize(0);//1553的
    v_gnss_orbit_can.resize(0);//can的
    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }
    GNSS_Orbit_xlsx v_slsx;
    int rowsum=xlsxR.dimension().rowCount();
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        memset(&v_slsx,0,sizeof(v_slsx));
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)v_slsx.time_s=var.toUInt();

                if(j==2||j==9||j==16||j==23)v_slsx.track_halflenth[j/7]=var.toDouble()*10000;//(km)->(0.1m)
                if(j==3||j==10||j==17||j==24)v_slsx.track_offcenter[(j-1)/7]=var.toDouble()/(3*pow(10,-3))/pow(2,-27);//单位(3*10^-3)*(2^-27)
                if(j==4||j==11||j==18||j==25)v_slsx.track_angle[(j-2)/7]=var.toDouble()/180/pow(2,-30);//单位：Pi*(2^-30)rad)
                if(j==5||j==12||j==19||j==26)v_slsx.up_point[(j-3)/7]=var.toDouble()/180/pow(2,-30);//单位：Pi*(2^-30)rad)
                if(j==6||j==13||j==20||j==27)v_slsx.near_angle[(j-4)/7]=var.toDouble()/180/pow(2,-30);
                if(j==7||j==14||j==21||j==28)v_slsx.flat_angle[(j-5)/7]=var.toDouble()/180/pow(2,-30);
                if(j==8||j==15||j==22||j==29)continue;//表格多了一行
            }
        }
        Card_1553Can->v_gnss_orbit.push_back(v_slsx);//1553的
        v_gnss_orbit_can.push_back(v_slsx);//can的

    }
    ui->radioButton_dg_flag->setChecked(1);//定轨读表标志
}

//清空主界面输出
void MainWindow::on_pB_outputClear_clicked()
{
    ui->txt_command_rec->clear();
    ui->dockWidget_log->setVisible(1);
}

//1553AB通道发送选择
void MainWindow::on_cB_AB_choose_currentIndexChanged(int index)
{
    Card_1553Can->setSendChannal(index);
}

//星时,GNSS时间设置生成指令
void MainWindow::on_pB_orderTime_clicked()
{

    unsigned long long time;
    time=ui->UI_TIMES_IN->text().toUInt();
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 0;
    order_data.obj_id = 4;//全选单机，因为只改变一个星时
    order_data.start_time=0;
    order_data.gap_time = 1;
    order_data.order_name = QString("星时,GNSS时间 "+QString::number(time));
    order_data.order_kind = 10;
    order_data.order_len = sizeof(time);
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, &time, sizeof(time));
    QVariant varData;
    varData.setValue(order_data);
    startOder_Tim=true;
    add_order_toList(varData);
}


//任务上下电部署开关生成指令
void MainWindow::on_pB_taskUp_down_elec_clicked()
{
    uchar str[2];
    memset(str,0,sizeof (str));
    str[0]=0xFD;
    str[1]=ui->cB_taskUp_down_elec1->currentIndex()+1;
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 0;
    order_data.start_time=0;
    order_data.gap_time = 1;
    order_data.order_name = QString("任务上下电部署开关");
    order_data.order_kind = 1;
    order_data.order_len = sizeof(str);
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, &str, sizeof(str));
    QVariant varData;
    varData.setValue(order_data);
    add_order_toList(varData);
}
//运行任务列表复位生成指令
void MainWindow::on_pB_task_reset_clicked()
{
    uchar str[2];
    memset(str,0,sizeof (str));
    str[0]=0xFE;
    str[1]=0xFF;
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 0;
    order_data.start_time=0;
    order_data.gap_time = 1;
    order_data.order_name = QString("运行任务列表复位");
    order_data.order_kind = 1;
    order_data.order_len = sizeof(str);
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, &str, sizeof(str));
    QVariant varData;
    varData.setValue(order_data);
    add_order_toList(varData);
}


//信号源控制初始化
void MainWindow::signal_init()
{
    ui->pB_send->setVisible(0);//隐藏测试发送按钮
    // 正则表达式设置IP和MAC输入,信号源1
    QRegExp ipRegExp = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip = new QRegExpValidator(ipRegExp,this);
    ui->lineEdit_inputIP->setValidator(m_ip);
    // 正则表达式设置IP和MAC输入，信号源2
    QRegExp ipRegExp2 = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip2 = new QRegExpValidator(ipRegExp2,this);
    ui->lineEdit_inputIP_2->setValidator(m_ip2);

    //tcp
    for(int i=0;i<2;i++)
    {
        signalConrtl[i]=new CN_SignalContrl();

        connect(signalConrtl[i],&CN_SignalContrl::GetMess,this,&MainWindow::Get_TcpMess);
    }

}
//指令数据库初始化
void MainWindow::orderDB_init()
{
    QSqlQuery qureydb;//创建对象时，系统会自动完成与数据库的关联
    QString str=QString("CREATE TABLE IF NOT EXISTS ORDER_LIST("
                        "ID INTEGER PRIMARY KEY     NOT NULL,"
                        "时间           TEXT    NOT NULL,"
                        "状态           TEXT    NOT NULL,"
                        "单机           TEXT        ,"
                        "PID           INTEGER     ,"
                        "发送时间       INTEGER     ,"
                        "名称           TEXT       ,"
                        "类型           TEXT       ,"
                        "长度           INTEGER    ,"
                        "指令内容        TEXT); ");
    qureydb.exec(str);
    //qDebug()<<str;
}


//连接 信号源1
void MainWindow::on_pB_IPConnet_clicked()
{
    //连接服务端
    bool ret=signalConrtl[0]->Tcp_Connet(ui->lineEdit_inputIP->text(),ui->lineEdit_inputport->text().toUInt());
    if(ret)
    {
        ui->textBrowser__massages->append("信号源1连接成功");
        ui->rad_xh1->setChecked(1);
    }
    else
    {
        ui->textBrowser__massages->append("信号源1连接失败");
        ui->rad_xh1->setChecked(0);
    }
}

//断开连接 信号源1
void MainWindow::on_pB_disconnect_clicked()
{
    signalConrtl[0]->Tcp_DisConnet();

    ui->textBrowser__massages->append("信号源1断开连接");
    ui->rad_xh1->setChecked(0);

}
//信号源2 连接
void MainWindow::on_pB_IPConnet_2_clicked()
{
    //连接服务端
    bool ret=signalConrtl[1]->Tcp_Connet(ui->lineEdit_inputIP_2->text(),ui->lineEdit_inputport_2->text().toUInt());
    if(ret)
    {
        ui->textBrowser__massages->append("信号源2连接成功");
        ui->rad_xh2->setChecked(1);
    }
    else
    {
        ui->textBrowser__massages->append("信号源2连接失败");
        ui->rad_xh2->setChecked(0);
    }
}
//信号源2 断开
void MainWindow::on_pB_disconnect_2_clicked()
{
    signalConrtl[1]->Tcp_DisConnet();

    ui->textBrowser__massages->append("信号源2断开连接");
    ui->rad_xh2->setChecked(0);
}


//显示接收消息
void MainWindow::Get_TcpMess(QString str)
{
    ui->textBrowser__massages->append(str);
}


//tcp客户端发送数据(测试发送)
void MainWindow::on_pB_send_clicked()
{
    int isize=signalConrtl[1]->Tcp_SendData(0,0);
    if(isize==-1)
    {
        ui->textBrowser__massages->append("信号源2发送失败");
    }
    //tcpsocket->write(ui->sendwd->text().toLocal8Bit().data());//网上
    //tcpsocket->write(ui->sendwd->toPlainText().toLatin1());//xie宏伟

    /*
         QString str;
         int iSize = tcpsocket->write(str.toUtf8().data());//返回字节的大小
         //等待write写完再写下一次的write
         if(!tcpsocket->waitForBytesWritten(50000))
         {
             return;
         }
         if(iSize ==-1) //判断发送是否成功
         {
             qDebug() << "write error";
             return;
         }
         若要多次向服务端发消息,可以while循环或者是其他.在这里要注意如果要多次发消息的
         话,waitForBytesWritten()这个函数是必不可少的,不然多次的话可能通信会失败.
         注:write()函数和被触发的读的readyRead()信号并不是一一对应的,比如可能你客户端
         write了三次,服务端那边的readyRead可能才被触发一次.
         */
}

//读取xlsx
void MainWindow::on_pB_readXlsx_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"信号源表格","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty())
    {
        ui->textBrowser__massages->append("读取信号源表格失败！");
        ui->rad_xlsxFile->setChecked(0);
        ui->lineEdit_xlsxPath->setText("");
        return;
    }
    ui->textBrowser__massages->append("读取信号源表格成功！");
    ui->lineEdit_xlsxPath->setText(file_path);//文件路径
    Signal_xlsxR=new Document(file_path);

    ui->rad_xlsxFile->setChecked(1);

    //检查表格格式是否有正确
    if(!Signal_xlsxR->selectSheet("Sheet1"))
    {
        qDebug()<<"为找到页“Sheet1”";
        return;
    }

    Cell* cell = Signal_xlsxR->cellAt(1, 1);//起始时间项
    QString tmps=cell->value().toString();
    if(tmps!="起始时间")
    {
        qDebug()<<"为找到“起始时间项”";
        return;
    }
    cell = Signal_xlsxR->cellAt(1, 2);//结束时间项
    QString tmpe=cell->value().toString();
    if(tmpe!="结束时间")
    {
        qDebug()<<"为找到“结束时间项”";
        return;
    }

    //定时器，自己测试开
    //    QTimer* time = new QTimer(this);
    //    connect(time, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    //    time->start(1000);

}
//直接设置信号源参数
void MainWindow::on_pB_signal_send_clicked()
{
    Signal_Str str;
    memset(&str,0,sizeof (str));

    str.fre=ui->lineEdit_fre->text().toDouble();
    str.power=ui->lineEdit_power->text().toDouble();
    str.custom=ui->lineEdit_custom->text().toDouble();
    str.type=ui->comboBox_type->currentIndex();

    if((ui->rad_xh1->isChecked()!=true)&&(ui->rad_xh2->isChecked()!=true))
        ui->textBrowser__massages->append("未有信号源连接");
    if(ui->rad_xh1->isChecked())signalConrtl[0]->setSignal_data(str);
    if(ui->rad_xh2->isChecked())signalConrtl[1]->setSignal_data(str);
    emit success_snack("设置成功");
}

//生成指令发送
void MainWindow::on_pB_signal_create_clicked()
{
    Signal_Str str;
    memset(&str,0,sizeof (str));

    str.fre=ui->lineEdit_fre->text().toDouble();
    str.power=ui->lineEdit_power->text().toDouble();
    str.custom=ui->lineEdit_custom->text().toDouble();
    str.type=ui->comboBox_type->currentIndex();

    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 0;
    order_data.start_time=0;
    order_data.gap_time = 1;
    order_data.order_name = QString("%1MHz,%2dBm").arg(str.fre).arg(str.custom);
    order_data.order_kind = 12;
    order_data.order_len = sizeof(str);
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, &str, sizeof(str));
    QVariant varData;
    varData.setValue(order_data);
    add_order_toList(varData);
}

//RF
void MainWindow::on_checkBox_RF_ON_clicked(bool checked)
{
    if(ui->rad_xh1->isChecked())signalConrtl[0]->OUTPut_RF(checked);
    if(ui->rad_xh2->isChecked())signalConrtl[1]->OUTPut_RF(checked);

}
//MOD
void MainWindow::on_checkBox_MOD_ON_clicked(bool checked)
{
    if(ui->rad_xh1->isChecked())signalConrtl[0]->Custom_MOD(checked);
    if(ui->rad_xh2->isChecked())signalConrtl[1]->Custom_MOD(checked);
}
//保存状态文件
void MainWindow::on_pB_saveStates_clicked()
{
    if(ui->rad_xh1->isChecked())signalConrtl[0]->saveState(ui->lineEdit_saveFile->text().toInt());
    if(ui->rad_xh2->isChecked())signalConrtl[1]->saveState(ui->lineEdit_saveFile->text().toInt());
}
//rel文件
void MainWindow::on_pB_REL_clicked()
{
    if(ui->rad_xh1->isChecked())signalConrtl[0]->RCL(ui->lineEdit_relFile->text().toInt());
    if(ui->rad_xh2->isChecked())signalConrtl[1]->RCL(ui->lineEdit_relFile->text().toInt());
}
//信号源复位
void MainWindow::on_pB_reSet_clicked()
{
    if(ui->rad_xh1->isChecked())signalConrtl[0]->resetState();
    if(ui->rad_xh2->isChecked())signalConrtl[1]->resetState();
}


//清空信息输出
void MainWindow::on_pushButton_clearSignal_clicked()
{
    ui->textBrowser__massages->clear();
}


void MainWindow::pps_set()
{
    uchar tmp=0;
    tmp=(ui->checkBox_PPSch8->isChecked()<<7)
            +(ui->checkBox_PPSch7->isChecked()<<6)
            +(ui->checkBox_PPSch6->isChecked()<<5)
            +(ui->checkBox_PPSch5->isChecked()<<4)
            +(ui->checkBox_PPSch4->isChecked()<<3)
            +(ui->checkBox_PPSch3->isChecked()<<2)
            +(ui->checkBox_PPSch2->isChecked()<<1)
            +ui->checkBox_PPSch1->isChecked();
    Card_1553Can->Set_PPS(tmp);
}

//PPS通路CH1输出
void MainWindow::on_checkBox_PPSch1_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}
//PPS通路CH2输出
void MainWindow::on_checkBox_PPSch2_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}
//PPS通路CH3输出
void MainWindow::on_checkBox_PPSch3_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}

//PPS通路CH4输出
void MainWindow::on_checkBox_PPSch4_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}
//PPS通路CH5输出
void MainWindow::on_checkBox_PPSch5_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}
//PPS通路CH6输出
void MainWindow::on_checkBox_PPSch6_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}

//PPS通路CH7输出
void MainWindow::on_checkBox_PPSch7_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}
//PPS通路CH8输出
void MainWindow::on_checkBox_PPSch8_clicked(bool checked)
{
    Q_UNUSED(checked);
    pps_set();
}

void MainWindow::on_pushButtonxxx_clicked()
{
    Card_1553Can->Set_PPStest();
}
//显示can发送内容
void MainWindow::on_checkBox_CANoutSend_clicked(bool checked)
{
    Card_can->outSendMess=checked;
}
//can输出导出表格
void MainWindow::on_pB_canDataExport_clicked()
{

    QString qFileName = QFileDialog::getSaveFileName(this, tr("save file(.txt)"),"",tr("text(*.txt)"));
    if(qFileName.isEmpty())return;
    QFile qFile(qFileName);
    if(!qFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this,"提示","文件打开错误");
        return;
    }
    QTextStream out(&qFile);
    out<<ui->txt_command_rec->toPlainText()<<endl;

    qFile.close();

    emit success_snack_slot("导出成功");
}


//1553B通道1是否勾选  (初始1)
void MainWindow::on_checkBox_1553BCH1_clicked(bool checked)
{
    Card_1553Can->m_check_chFlg[0]=checked;//通道1发送标志
    if(switch_1553cyc==false)//周期消息处于开启状态
    {
        Card_1553Can->cyc1553_AD(checked);
    }

}
//1553B通道2是否勾选  (初始0)
void MainWindow::on_checkBox_1553BCH2_clicked(bool checked)
{
    Card_1553Can->m_check_chFlg[1]=checked;//通道2发送标志
    if(switch_1553cyc==false)//周期消息处于开启状态
    {
        Card_1553Can->cyc1553_AD(checked);
    }
}
//1553B通道3是否勾选  (初始0)
void MainWindow::on_checkBox_1553BCH3_clicked(bool checked)
{
    Card_1553Can->m_check_chFlg[2]=checked;//通道3发送标志
    if(switch_1553cyc==false)//周期消息处于开启状态
    {
        Card_1553Can->cyc1553_AD(checked);
    }
}
//1553B通道4是否勾选  (初始0)
void MainWindow::on_checkBox_1553BCH4_clicked(bool checked)
{
    Card_1553Can->m_check_chFlg[3]=checked;//通道4发送标志
    if(switch_1553cyc==false)//周期消息处于开启状态
    {
        Card_1553Can->cyc1553_AD(checked);
    }
}

//RS422内外时钟源选择
void MainWindow::on_comboBox_activated(int index)
{

    Card_1553Can->change_RS422pps(index);
}



//主界面A星时标志
void MainWindow::on_cB_XS_A_clicked(bool checked)
{
    Card_1553Can->XS_A_B(0,checked);
}
//主界面B星时标志
void MainWindow::on_cB_XS_B_clicked(bool checked)
{
    Card_1553Can->XS_A_B(1,checked);
}
