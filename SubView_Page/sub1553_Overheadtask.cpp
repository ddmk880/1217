#include "sub1553_Overheadtask.h"

#include <QVector>
#include <QMessageBox>
#include <QFileDialog>
#include "ui_sub1553_Overheadtask.h"


using namespace std;
using namespace QXlsx;
sub1553_Overheadtask::sub1553_Overheadtask(QWidget *parent)
    : QWidget(parent), ui(new Ui::sub1553_Overheadtask) {
    ui->setupUi(this);

    fre_dBm();
    // 输出界面
    model_mlist = new QStandardItemModel();
    QStringList t_name_list;
    t_name_list.clear();
    t_name_list.append("任务内容号");
    t_name_list.append("引导头与基本信息长度");
    t_name_list.append("引导头与基本信息");
    t_name_list.append("任务模式参数名称");
    t_name_list.append("参数长度");
    t_name_list.append("参数内容");
    model_mlist->setColumnCount(t_name_list.size());
    for (int i = 0; i < t_name_list.size(); i++) {
        model_mlist->setHeaderData(i, Qt::Horizontal, t_name_list.at(i));
    }
    ui->tableView_dataout->setModel(model_mlist);
    // ui->tableView_dataout->verticalHeader()->hide();//隐藏列表行号
    ui->tableView_dataout->setColumnWidth(0, 100);  // 设置序号列宽60节省界面空间
    ui->tableView_dataout->setColumnWidth(1, 200);
    ui->tableView_dataout->setColumnWidth(2, 150);
    ui->tableView_dataout->setColumnWidth(3, 150);
    ui->tableView_dataout->setColumnWidth(4, 100);
    ui->tableView_dataout->setColumnWidth(5, 300);
    ui->tableView_dataout->horizontalHeader()->setStretchLastSection(true);

    ui->tableView_dataout->setSelectionBehavior(QAbstractItemView::SelectRows);  // 设定选择行为，按行选中

    // 不同任务参数界面
    QLabel *lablemainTab1 = new QLabel("任务内容引导头+基本信息配置");
    QLabel *lablemainTab2 = new QLabel("任务模式参数配置");
    ui->tabWidget_5->tabBar()->setTabButton(0, QTabBar::ButtonPosition::RightSide,lablemainTab1);
    ui->tabWidget_5->tabBar()->setTabButton(1, QTabBar::ButtonPosition::RightSide,lablemainTab2);
    ui->tabWidget_5->tabBar()->tabButton(0, QTabBar::ButtonPosition::RightSide)->setFixedHeight(40);
    ui->tabWidget_5->tabBar()->tabButton(1, QTabBar::ButtonPosition::RightSide)->setFixedHeight(40);
    ui->tabWidget_5->setCurrentIndex(0);//默认显示第一个页面
    // 不同任务参数界面
    zl_kind["1:全景扫描"] = 1;
    zl_kind["1:常规信号频点控守"] = 2;
    zl_kind["2:Link16信号频点控守"] = 3;
    zl_kind["3:塔康信号频点控守"] = 4;
    zl_kind["4:敌我识别信号频点控守"] = 5;
    zl_kind["5:铱星信号频点控守"] = 6;
    zl_kind["6:海事信号频点控守"] = 7;
    zl_kind["7:雷达信号频点控守"] = 8;
    zl_kind["8:星链信号频点控守"] = 9;
    zl_kind["9:同步采样"] = 10;
    zl_kind["10:上注软件解调"] = 11;
    zl_kind["1:雷达信号频点扫描"] = 12;
    zl_kind["1:多频点快速干扰"] = 13;
    zl_kind["2:等间隔梳状谱干扰"] = 14;
    zl_kind["3:非等间隔梳状谱干扰"] = 15;
    zl_kind["4:多通道快速协同干扰"] = 16;
    zl_kind["5:多通道多带宽协同干扰"] = 17;
    zl_kind["6:雷达强制干扰"] = 18;
    zl_kind["1:雷达侦察干扰"] = 19;
    zl_kind["1:星间/星地感知引导干扰"] = 20;
    zl_kind["1:备用导航任务参数"] = 21;
    zl_kind["1:类5G模式参数"] = 22;
    zl_kind["1:J链任务模式参数"] = 23;
    QLabel *lableTab1 = new QLabel("1:全景扫描");
    QLabel *lableTab2 = new QLabel("2:常规信号频点控守");
    QLabel *lableTab3 = new QLabel("3:Link16信号频点控守");
    QLabel *lableTab4 = new QLabel("4:塔康信号频点控守");
    QLabel *lableTab5 = new QLabel("5:敌我识别信号频点控守");
    QLabel *lableTab6 = new QLabel("6:铱星信号频点控守");
    QLabel *lableTab7 = new QLabel("7:海事信号频点控守");
    QLabel *lableTab8 = new QLabel("8:雷达信号频点控守");
    QLabel *lableTab9 = new QLabel("9:星链信号频点控守");
    QLabel *lableTab10 = new QLabel("10:同步采样");
    QLabel *lableTab11 = new QLabel("11:上注软件解调");
    QLabel *lableTab12 = new QLabel("12:雷达信号频点扫描");
    QLabel *lableTab13 = new QLabel("13:多频点快速干扰");
    QLabel *lableTab14 = new QLabel("14:等间隔梳状谱干扰");
    QLabel *lableTab15 = new QLabel("15:非等间隔梳状谱干扰");
    QLabel *lableTab16 = new QLabel("16:多通道快速协同干扰");
    QLabel *lableTab17 = new QLabel("17:多通道多带宽协同干扰");
    QLabel *lableTab18 = new QLabel("18:雷达强制干扰");
    QLabel *lableTab19 = new QLabel("19:雷达侦察干扰");
    QLabel *lableTab20 = new QLabel("20:星间/星地感知引导干扰");
    QLabel *lableTab21 = new QLabel("21:备用导航任务参数");
    QLabel *lableTab22 = new QLabel("22:类5G模式参数");
    QLabel *lableTab23 = new QLabel("23:J链任务模式参数");

    for(int i=0;i<23;i++)
        ui->tabWidget_3->setTabText(i,"");

    ui->tabWidget_3->tabBar()->setTabButton(0, QTabBar::ButtonPosition::RightSide,lableTab1);
    ui->tabWidget_3->tabBar()->setTabButton(1, QTabBar::ButtonPosition::RightSide,lableTab2);
    ui->tabWidget_3->tabBar()->setTabButton(2, QTabBar::ButtonPosition::RightSide,lableTab3);
    ui->tabWidget_3->tabBar()->setTabButton(3, QTabBar::ButtonPosition::RightSide,lableTab4);
    ui->tabWidget_3->tabBar()->setTabButton(4, QTabBar::ButtonPosition::RightSide,lableTab5);
    ui->tabWidget_3->tabBar()->setTabButton(5, QTabBar::ButtonPosition::RightSide,lableTab6);
    ui->tabWidget_3->tabBar()->setTabButton(6, QTabBar::ButtonPosition::RightSide,lableTab7);
    ui->tabWidget_3->tabBar()->setTabButton(7, QTabBar::ButtonPosition::RightSide,lableTab8);
    ui->tabWidget_3->tabBar()->setTabButton(8, QTabBar::ButtonPosition::RightSide,lableTab9);
    ui->tabWidget_3->tabBar()->setTabButton(9, QTabBar::ButtonPosition::RightSide,lableTab10);
    ui->tabWidget_3->tabBar()->setTabButton(10, QTabBar::ButtonPosition::RightSide, lableTab11);
    ui->tabWidget_3->tabBar()->setTabButton(11, QTabBar::ButtonPosition::RightSide, lableTab12);
    ui->tabWidget_3->tabBar()->setTabButton(12, QTabBar::ButtonPosition::RightSide, lableTab13);
    ui->tabWidget_3->tabBar()->setTabButton(13, QTabBar::ButtonPosition::RightSide, lableTab14);
    ui->tabWidget_3->tabBar()->setTabButton(14, QTabBar::ButtonPosition::RightSide, lableTab15);
    ui->tabWidget_3->tabBar()->setTabButton(15, QTabBar::ButtonPosition::RightSide, lableTab16);
    ui->tabWidget_3->tabBar()->setTabButton(16, QTabBar::ButtonPosition::RightSide, lableTab17);
    ui->tabWidget_3->tabBar()->setTabButton(17, QTabBar::ButtonPosition::RightSide, lableTab18);
    ui->tabWidget_3->tabBar()->setTabButton(18, QTabBar::ButtonPosition::RightSide, lableTab19);
    ui->tabWidget_3->tabBar()->setTabButton(19, QTabBar::ButtonPosition::RightSide, lableTab20);
    ui->tabWidget_3->tabBar()->setTabButton(20, QTabBar::ButtonPosition::RightSide, lableTab21);
    ui->tabWidget_3->tabBar()->setTabButton(21, QTabBar::ButtonPosition::RightSide, lableTab22);
    ui->tabWidget_3->tabBar()->setTabButton(22, QTabBar::ButtonPosition::RightSide, lableTab23);
    ui->tabWidget_3->setCurrentIndex(0);
    // 字居中
    // ui->tabWidget_3->tabBar()->tabButton(0,QTabBar::ButtonPosition::RightSide)->setFixedHeight(40);
    // 按键在左
    ui->tabWidget_3->setTabPosition(QTabWidget::West);

    // 定位参数---引导卫星目的地址表格
    ui->tableWidget_startAddr->setColumnCount(1);
    ui->tableWidget_startAddr->setHorizontalHeaderLabels(QStringList()<< "定位参数卫星地址(0x)");
    for(int i = 0;i < 0;i ++)
    {
        ui->tableWidget_startAddr->insertRow(i);
        ui->tableWidget_startAddr->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_startAddr->item(i,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
    }
    ui->tableWidget_startAddr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，不出现滚动条
    //ui->tableWidget_startAddr->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，不出现滚动条
    ui->tableWidget_startAddr->verticalHeader()->setVisible(true);  // 隐藏行号
    // 引导参数 -- 引导卫星目的地址
    ui->tableWidget_YDCSaddr->setColumnCount(2);
    ui->tableWidget_YDCSaddr->setHorizontalHeaderLabels(QStringList()<< "引导参数工作模式"<< "引导参数卫星地址(0x)");
    for(int i = 0;i < 0;i ++)
    {
        ui->tableWidget_YDCSaddr->insertRow(i);
        ui->tableWidget_YDCSaddr->setItem(i,0,new QTableWidgetItem(QString::number(1)));//1：引导干扰2：引导SAR成像

        ui->tableWidget_YDCSaddr->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_YDCSaddr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，不出现滚动条
    //ui->tableWidget_YDCSaddr->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，不出现滚动条
    ui->tableWidget_YDCSaddr->verticalHeader()->setVisible(true);  // 隐藏行号

    //子界面表格设置
    Init_sublist();
    //天线子阵里表格始化设置
    Init_zzwideget();
    //备用导航天线子阵里表格始化设置
    //ui->tabWidget_11->clear();
    BYDHInit_zzwideget();
    // 一开始需要隐藏的部分控件

    ui->label_73->setVisible(0);//全景扫描任务
    ui->lineEdit_T1_6->setVisible(0);

    ui->label_92->setVisible(false);
    ui->comboBox_D8bit1_2->setVisible(false);
    ui->label_95->setVisible(false);
    ui->comboBox_D10bit6->setVisible(false);

    //类5G隐藏
    ui->label_622->setVisible(false);//子阵2,4天线使用方式
    ui->comboBox_D10b6->setVisible(false);


    //侦察天线本振控件
    ui->comboBox_2D5_b0->setVisible(0);
    ui->comboBox_2D5_b1->setVisible(0);
    //侦察 当天线子阵控制模式为1、2时，本字段无效。---(天线控制间隔时间ms)
    ui->label_42->setVisible(0);
    ui->lineEdit_D11->setVisible(0);
    //侦察 射频通道号
    ui->comboBox_D7_2->setVisible(false);
    //侦察  射频通道参数设置
    ui->comboBox_D8bit1_2_2->setVisible(false);
    //侦察  射频通道接收衰减(dB)
    ui->lineEdit_D9_2->setVisible(false);

    //侦察   开关矩阵选择
    ui->label_268->setVisible(false);//在SXKu频段下
    ui->lineEdit_D15_1->setVisible(false);
    ui->label_281->setVisible(false);
    ui->lineEdit_D15_2->setVisible(false);
    //侦察 数字波束控件隐藏，显示
    on_comboBox_D14_activated(1);
    //侦察  本振方式选择 L频段时该参数无效，隐藏
    ui->comboBox_D4->setVisible(0);
    ui->label_36->setVisible(0);
    //侦察  一本振使用信息  L频段时该参数无效，隐藏
    ui->comboBox_D5_b0->setVisible(0);
    ui->lineEdit_D9_5->setVisible(0);


    //干扰 本振选择方式
    ui->label_78->setVisible(0);
    ui->comboBox_E3->setVisible(0);
    //干扰 一本振使用信息：
    ui->label_79->setVisible(0);
    ui->comboBox_gr5_b0->setVisible(0);
    //干扰 通道射频衰减组2
    ui->label_65->setVisible(false);
    ui->comboBox_D8bit1_4->setVisible(false);
    ui->comboBox_D8bit1_4_2->setVisible(false);
    //干扰 射频通道发射衰减组2
    ui->lineEdit_E7_3->setVisible(false);
    ui->lineEdit_grglht_2->setVisible(false);//关联变化值 功率回退值
    ui->lineEdit_grfdzb_2->setVisible(false);//关联变化值 非单载波补偿值
    //干扰 射频通道接收衰减组2
    ui->lineEdit_E7_2_2->setVisible(false);

    //类5G
    //本振方式选择
    ui->label_477->setVisible(0);
    ui->comboBox_D4_2->setVisible(0);
    ui->comboBox_D4_2->setCurrentIndex(0);
    //本振方式选择
    ui->label_478->setVisible(0);
    ui->comboBox_D5_2->setVisible(0);
    ui->comboBox_D5_2->setCurrentIndex(0);

    ui->label_95->setVisible(false);

    ui->label_116->setVisible(false);
    ui->comboBox_E7bit6->setVisible(false);

    //任务基本信息 通用，拓展功能
    for (int i=0;i<2;i++) {
        ui->tabWidget_mess->removeTab(1);
    }
    //功能模式选择,先隐藏"电子干扰任务"窗口(8个子界面)
    for (int i=0;i<7;i++) {
        ui->tabWidget->removeTab(1);
    }
    //天线子阵参数,先隐藏"干扰"窗口(6个子界面)
    for (int i=0;i<5;i++) {
        ui->tabWidget_6->removeTab(1);
    }

    ui->label_509->setVisible(false);
    ui->label_510->setVisible(false);

    ui->checkBox_sxkuAmper_1->setVisible(false);
    ui->comboBox_reduceTD_1->setVisible(false);


    // 子阵234的tab先隐藏
    for (int i = 0; i < 3; i++) ui->tabWidget_7->removeTab(1);  // 移除
    // 4个控制模式都默认第一个tab
    ui->tabWidget_mess->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget_6->setCurrentIndex(0);

    //侦察模式的子阵内容
    for (int i = 0; i < 3; i++) ui->tabWidget_2->removeTab(1);  // 移除
    for (int i = 0; i < 3; i++) ui->tabWidget_8->removeTab(1);  // 移除
    for (int i = 0; i < 3; i++) ui->tabWidget_9->removeTab(1);  // 移除
    for (int i = 0; i < 3; i++) ui->tabWidget_10->removeTab(1);  // 移除
    //干扰模式的子阵内容
    ui->tabWidget_4->clear();
    ui->tabWidget_4->insertTab(0,ui->tab_39,"指向驻留模式");
    //备用导航的子阵内容
    for (int i = 0; i < 3; i++) ui->tabWidget_18->removeTab(1);  // 移除
    for (int i = 0; i < 3; i++) ui->tabWidget_19->removeTab(1);  // 移除
    for (int i = 0; i < 3; i++) ui->tabWidget_20->removeTab(1);  // 移除
    for (int i = 0; i < 3; i++) ui->tabWidget_21->removeTab(1);  // 移除


    // 子阵234的tab先隐藏--类5G
    for (int i = 0; i < 3; i++) ui->tabWidget_12->removeTab(1);  // 移除
    //干扰天线本振控件
    ui->comboBox_gr5_b0_->setVisible(0);
    ui->comboBox_gr5_b1->setVisible(0);
    //
    ui->cB_task_modetype->addItem("1:全景扫描");
    ui->cB_task_modetype->setCurrentIndex(0);
    //备用导航 子阵234的tab先隐藏
    for (int i = 0; i < 3; i++) ui->tabWidget_11->removeTab(1);  // 移除
    //J链 子阵234的tab先隐藏
    for (int i = 0; i < 3; i++) ui->tabWidget_13->removeTab(1);  // 移除
    //J链任务基本信息
    // 正则表达式设置IP和MAC输入
    QRegExp ipRegExp = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip = new QRegExpValidator(ipRegExp,this);
    ui->lineEdit_J_15->setValidator(m_ip);
    ui->lineEdit_J_16->setValidator(m_ip);
    ui->lineEdit_J_18->setValidator(m_ip);


}

sub1553_Overheadtask::~sub1553_Overheadtask() { delete ui; }

//子界面表格设置
void sub1553_Overheadtask::Init_sublist()
{

    //全景参数列表...
    ui->tableWidget_T1_QJlist->setColumnCount(3);
    ui->tableWidget_T1_QJlist->setHorizontalHeaderLabels(QStringList()<< "起始频率(MHz)"<< "终止频率(MHz)"<< "扫描步进(KHz)");

    for(int i = 0;i < 1;i ++)
    {
        ui->tableWidget_T1_QJlist->insertRow(i);
        if(i==0)
        {
            ui->tableWidget_T1_QJlist->setItem(i,0,new QTableWidgetItem(QString::number(960)));
            ui->tableWidget_T1_QJlist->setItem(i,1,new QTableWidgetItem(QString::number(1660)));
            ui->tableWidget_T1_QJlist->setItem(i,2,new QTableWidgetItem(QString::number(0)));
        }

    }
    ui->tableWidget_T1_QJlist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_T1_QJlist->verticalHeader()->setVisible(true);  // 隐藏行号

    // 常规信号频点控守...
    ui->tableWidget_T2_cytxbg->setColumnCount(3);
    ui->tableWidget_T2_cytxbg->setHorizontalHeaderLabels(QStringList()<< "处理板NCO频率/MHz"<<"采样带宽KHz"<<"检测门限");
    for(int i = 0;i < 1;i ++)
    {
        ui->tableWidget_T2_cytxbg->insertRow(i);

        ui->tableWidget_T2_cytxbg->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_T2_cytxbg->setItem(i,1,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_T2_cytxbg->setItem(i,2,new QTableWidgetItem(QString::number(0)));
    }
    //ui->tableWidget_T2_cytxbg->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，出现滚动条
    ui->tableWidget_T2_cytxbg->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_T2_cytxbg->verticalHeader()->setVisible(true);  // 隐藏行号


    //铱星信号频点控守
    ui->tableWidget_6yxch256->setColumnCount(2);
    ui->tableWidget_6yxch256->setHorizontalHeaderLabels(QStringList()<< "通道号"<< "0:不屏蔽/1:屏蔽");
    for(int i = 0;i < 256;i ++)
    {
        ui->tableWidget_6yxch256->insertRow(i);

        ui->tableWidget_6yxch256->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_6yxch256->setItem(i,1,new QTableWidgetItem(QString::number(0)));

    }
    //ui->tableWidget_6yxch256->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，出现滚动条
    ui->tableWidget_6yxch256->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_6yxch256->verticalHeader()->setVisible(false);  // 隐藏行号


    // 雷达信号频点扫描
    ui->tableWidget_LDpdsm->setColumnCount(1);
    ui->tableWidget_LDpdsm->setHorizontalHeaderLabels(QStringList()<< "接收机中心频率(KHz)");
    //    for(int i = 0;i < 256;i ++)
    //    {
    //        ui->tableWidget_LDpdsm->insertRow(i);

    //        ui->tableWidget_LDpdsm->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
    //        ui->tableWidget_LDpdsm->setItem(i,1,new QTableWidgetItem(QString::number(0)));

    //    }
    //ui->tableWidget_LDpdsm->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，出现滚动条
    ui->tableWidget_LDpdsm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_LDpdsm->verticalHeader()->setVisible(true);  // 隐藏行号


    //表格	星链信号频点控守
    ui->tWidget_T9xlNCO_list->setColumnCount(2);
    ui->tWidget_T9xlNCO_list->setHorizontalHeaderLabels(QStringList()<< "NCO频率(KHz)"<<"选择");

    //    QCheckBox *checkBox = new QCheckBox(ui->tWidget_T9xlNCO_list);
    //    checkBox->resize(40, 24);
    //    ui->tWidget_T9xlNCO_list->setCellWidget(1, 1, checkBox);
    //    checkBox->setStyleSheet("margin-left:4px;");//左侧的偏移量，不设置QCheckBox会紧靠左边，没有和下面的对齐；
    //    checkBox->setChecked(false);
    //    ui->tWidget_T9xlNCO_list->setColumnWidth(0, 24);
    //    ui->tWidget_T9xlNCO_list->setColumnWidth(1, 40);

    for(int i = 0;i < 8;i ++)
    {
        ui->tWidget_T9xlNCO_list->insertRow(i);
        QCheckBox *checkBox = new QCheckBox(ui->tWidget_T9xlNCO_list);
        checkBox->setChecked(true);
        ui->tWidget_T9xlNCO_list->setCellWidget(i, 1, checkBox);

        if(i==0)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("-208750"));
        if(i==1)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("-156250"));
        if(i==2)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("-93750"));
        if(i==3)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("-31250"));
        if(i==4)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("31250"));
        if(i==5)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("93750"));
        if(i==6)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("156250"));
        if(i==7)ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem("208750"));
    }


    //ui->tWidget_T9xlNCO_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tWidget_T9xlNCO_list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，不出现滚动条
    ui->tWidget_T9xlNCO_list->verticalHeader()->setVisible(true);  // 隐藏行号

    //多频点快速干扰列表
    ui->tableWidget_spgrCyc->setColumnCount(2);
    ui->tableWidget_spgrCyc->setHorizontalHeaderLabels(QStringList()<< "数字频率Hz"<< "内容参数置");
    ui->tableWidget_spgrCyc->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，出现滚动条
    ui->tableWidget_spgrCyc->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格变为禁止编辑

    //添加下拉框在表格
    //    QStringList listspgrCyc=QStringList() <<"数字频率"<<"模式选择"<<"扫频带宽"<<"扫频间隔"
    //                                        <<"扫频驻留时间"<<"干扰幅度"<<"干扰样式"<< "参数1(带宽/码速率)"<<"参数2(FSK频偏)"
    //                                        << "参数3(码流选择)"<< "参数4(多项式参数)"<<"参数5(多项式初始化参数)";
    //    ui->tableWidget_spgrCyc->setColumnCount(listspgrCyc.size());
    //    ui->tableWidget_spgrCyc->setHorizontalHeaderLabels(listspgrCyc);
    //    for(int i = 0;i < 8;i ++)
    //    {
    //        ui->tableWidget_spgrCyc->insertRow(i);
    //        for (int j=0;j<listspgrCyc.size();j++) {
    //            if(j==1)ui->tableWidget_spgrCyc->setCellWidget(i,j,ui->comboBox_T13grys);
    //            else
    //            {
    //                ui->tableWidget_spgrCyc->setItem(i,j,new QTableWidgetItem(QString::number(0)));
    //            }

    //        }
    //    }
    ui->tableWidget_spgrCyc->verticalHeader()->setVisible(true);  // 隐藏行号
    // 等间隔梳状谱干扰...
    ui->tableWidget_szp->setColumnCount(4);
    ui->tableWidget_szp->setHorizontalHeaderLabels(QStringList()<< "梳状谱幅度0.1dB"<< "梳状谱中心频率Hz"<< "梳状谱干扰带宽Hz"<< "梳状谱干扰间隔Hz");
    //    for(int i = 0;i < 20;i ++)
    //    {
    //        ui->tableWidget_szp->insertRow(i);

    //        ui->tableWidget_szp->setItem(i,0,new QTableWidgetItem(QString::number(0)));
    //        ui->tableWidget_szp->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    //        ui->tableWidget_szp->setItem(i,2,new QTableWidgetItem(QString::number(0)));
    //        ui->tableWidget_szp->setItem(i,3,new QTableWidgetItem(QString::number(0)));
    //    }
    ui->tableWidget_szp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_szp->verticalHeader()->setVisible(true);  // 隐藏行号
    // 非等间隔梳状谱干扰...
    ui->tableWidget_szpgr->setColumnCount(2);
    ui->tableWidget_szpgr->setHorizontalHeaderLabels(QStringList() << "梳状谱干扰幅度0.1dB"<< "梳状谱NCO频率Hz");
    //    for(int i = 0;i < 100;i ++)
    //    {
    //        ui->tableWidget_szpgr->insertRow(i);

    //        ui->tableWidget_szpgr->setItem(i,0,new QTableWidgetItem(QString::number(0)));
    //        ui->tableWidget_szpgr->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    //    }
    ui->tableWidget_szpgr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_szpgr->verticalHeader()->setVisible(true);  // 隐藏行号
    // 多通道快速协同干扰...
    ui->tableWidget_T16bgcc->setColumnCount(2);
    ui->tableWidget_T16bgcc->setHorizontalHeaderLabels(QStringList()<< "数字频率NCO"<< "内容参数置");
    ui->tableWidget_T16bgcc->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_T16bgcc->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格变为禁止编辑
    ui->tableWidget_T16bgcc->verticalHeader()->setVisible(true);  // 隐藏行号

    //多通道多带宽协同干扰(星链目标干扰)...
    ui->tableWidget_T17xlmbgr->setColumnCount(2);
    ui->tableWidget_T17xlmbgr->setHorizontalHeaderLabels(QStringList()<< "梳状谱中心频率Hz"<< "内容参数置");
    ui->tableWidget_T17xlmbgr->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，出现滚动条
    ui->tableWidget_T17xlmbgr->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格变为禁止编辑
    ui->tableWidget_T17xlmbgr->verticalHeader()->setVisible(true);  // 隐藏行号


    //雷达强制干扰--循环体
    ui->tableWidget_LDqzgr->setColumnCount(2);
    ui->tableWidget_LDqzgr->setHorizontalHeaderLabels(QStringList()<< "谱线干扰幅度dB"<< "谱线频率Hz");
    for (int i = 0; i < 1; i++) {
        ui->tableWidget_LDqzgr->insertRow(i);
        ui->tableWidget_LDqzgr->setItem(i, 0, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_LDqzgr->setItem(i, 1, new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_LDqzgr->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  // 最小显示完整，出现滚动条
    ui->tableWidget_LDqzgr->verticalHeader()->setVisible(true);  // 隐藏行号

    //SAR任务读取文件
    ui->tB_widget_SARFileList->setColumnCount(2);
    ui->tB_widget_SARFileList->setHorizontalHeaderLabels(QStringList()<< "文件名"<<"文件路径");
    ui->tB_widget_SARFileList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tB_widget_SARFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格变为禁止编辑
    //ui->tB_widget_SARFileList->verticalHeader()->setVisible(true);  // 隐藏行号
    //控制功能任务读取文件
    ui->tB_widget_SARFileList_2->setColumnCount(2);
    ui->tB_widget_SARFileList_2->setHorizontalHeaderLabels(QStringList()<< "文件名"<<"文件路径");
    ui->tB_widget_SARFileList_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tB_widget_SARFileList_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格变为禁止编辑
    //ui->tB_widget_SARFileList_2->verticalHeader()->setVisible(true);  // 隐藏行号
    ui->widget_tzw->setVisible(false);
    ui->label_494->setVisible(false);
    ui->comboBox_D8bit1_3->setVisible(false);
    ui->label_499->setVisible(false);
    ui->comboBox_D10bit6_2->setVisible(false);
    ui->comboBox_D7_5->setVisible(0);//射频通道号第2组
    ui->comboBox_D7_7->setVisible(0);//射频通道号第3组
    ui->comboBox_D7_6->setVisible(0);//射频通道号第4组
    ui->comboBox_2D5_b1_2->setVisible(0);//一本振使用信息第二组

    ui->label_505->setVisible(0);//接收相位/幅度加权码（SXKu频段）
    ui->lineEdit_tz5->setVisible(0);
    ui->label_513->setVisible(0);
    ui->lineEdit_tz6->setVisible(0);
    ui->label_514->setVisible(0);//组件遥测数据类型    （SXKu频段）
    ui->comboBox_tz7->setVisible(0);
    //类5G任务模式参数
    ui->tableWidget_L5G->setColumnCount(1);
    ui->tableWidget_L5G->setHorizontalHeaderLabels(QStringList()<< "文件名(16进制)(8字节)");

    for(int i = 0;i < 1;i ++)
    {
        ui->tableWidget_L5G->insertRow(i);
        if(i==0)
        {
            ui->tableWidget_L5G->setItem(i,0,new QTableWidgetItem(QString::number(0)));

        }

    }

    ui->tableWidget_L5G->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_L5G->verticalHeader()->setVisible(true);  // 隐藏行号

}
void sub1553_Overheadtask::Init_zzwideget()
{
    //子阵1指向扫描模式
    ui->tableWidget_DD2->setColumnCount(2);
    ui->tableWidget_DD2->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2->insertRow(i);

        ui->tableWidget_DD2->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2->setItem(i,1,new QTableWidgetItem(QString::number(0)));

    }
    ui->tableWidget_DD2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2->verticalHeader()->setVisible(true);  // 隐藏行号
    ui->tableWidget_DD2->setVisible(0);
    //子阵1区域扫描模式
    ui->tableWidget_DD4->setColumnCount(2);
    ui->tableWidget_DD4->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4->insertRow(i);

        ui->tableWidget_DD4->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4->verticalHeader()->setVisible(true);  // 隐藏行号
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //子阵2指向扫描模式
    ui->tableWidget_DD2_Z2->setColumnCount(2);
    ui->tableWidget_DD2_Z2->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_Z2->insertRow(i);

        ui->tableWidget_DD2_Z2->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_Z2->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD2_Z2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_Z2->verticalHeader()->setVisible(true);  // 隐藏行号
    ui->tableWidget_DD2_Z2->setVisible(0);
    //子阵2区域扫描模式
    ui->tableWidget_DD4_Z2->setColumnCount(2);
    ui->tableWidget_DD4_Z2->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_Z2->insertRow(i);

        ui->tableWidget_DD4_Z2->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_Z2->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_Z2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_Z2->verticalHeader()->setVisible(true);  // 隐藏行号
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //子阵3指向扫描模式
    ui->tableWidget_DD2_Z3->setColumnCount(2);
    ui->tableWidget_DD2_Z3->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_Z3->insertRow(i);

        ui->tableWidget_DD2_Z3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_Z3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD2_Z3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_Z3->verticalHeader()->setVisible(true);  // 隐藏行号
    ui->tableWidget_DD2_Z3->setVisible(0);

    //子阵2区域扫描模式
    ui->tableWidget_DD4_Z3->setColumnCount(2);
    ui->tableWidget_DD4_Z3->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_Z3->insertRow(i);

        ui->tableWidget_DD4_Z3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_Z3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_Z3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_Z3->verticalHeader()->setVisible(true);  // 隐藏行号
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //子阵4指向扫描模式
    ui->tableWidget_DD2_Z4->setColumnCount(2);
    ui->tableWidget_DD2_Z4->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_Z4->insertRow(i);

        ui->tableWidget_DD2_Z4->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_Z4->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD2_Z4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_Z4->verticalHeader()->setVisible(true);  // 隐藏行号
    ui->tableWidget_DD2_Z4->setVisible(0);
    //子阵2区域扫描模式
    ui->tableWidget_DD4_Z4->setColumnCount(2);
    ui->tableWidget_DD4_Z4->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_Z4->insertRow(i);

        ui->tableWidget_DD4_Z4->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_Z4->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_Z4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_Z4->verticalHeader()->setVisible(true);  // 隐藏行号


    //干扰模式 子阵参数
    //指向扫描模式
    ui->tableWidget_GR1_zxsm_4->setColumnCount(2);
    ui->tableWidget_GR1_zxsm_4->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_GR1_zxsm_4->insertRow(i);

        ui->tableWidget_GR1_zxsm_4->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_GR1_zxsm_4->setItem(i,1,new QTableWidgetItem(QString::number(0)));

    }
    ui->tableWidget_GR1_zxsm_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_GR1_zxsm_4->verticalHeader()->setVisible(true);  // 隐藏行号
}


//备用导航天线子阵里表格始化设置
void sub1553_Overheadtask::BYDHInit_zzwideget(){

    //子阵1指向扫描模式
    ui->tableWidget_DD2_3->setColumnCount(2);
    ui->tableWidget_DD2_3->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_3->insertRow(i);

        ui->tableWidget_DD2_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));

    }
    ui->tableWidget_DD2_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //子阵1区域扫描模式
    ui->tableWidget_DD4_3->setColumnCount(2);
    ui->tableWidget_DD4_3->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_3->insertRow(i);

        ui->tableWidget_DD4_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //子阵2指向扫描模式
    ui->tableWidget_DD2_Z2_3->setColumnCount(2);
    ui->tableWidget_DD2_Z2_3->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_Z2_3->insertRow(i);

        ui->tableWidget_DD2_Z2_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_Z2_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD2_Z2_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_Z2_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //子阵2区域扫描模式
    ui->tableWidget_DD4_Z2_3->setColumnCount(2);
    ui->tableWidget_DD4_Z2_3->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_Z2_3->insertRow(i);

        ui->tableWidget_DD4_Z2_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_Z2_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_Z2_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_Z2_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //子阵3指向扫描模式
    ui->tableWidget_DD2_Z3_3->setColumnCount(2);
    ui->tableWidget_DD2_Z3_3->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_Z3_3->insertRow(i);

        ui->tableWidget_DD2_Z3_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_Z3_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD2_Z3_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_Z3_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //子阵3区域扫描模式
    ui->tableWidget_DD4_Z3_3->setColumnCount(2);
    ui->tableWidget_DD4_Z3_3->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_Z3_3->insertRow(i);

        ui->tableWidget_DD4_Z3_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_Z3_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_Z3_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_Z3_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //子阵4指向扫描模式
    ui->tableWidget_DD2_Z4_3->setColumnCount(2);
    ui->tableWidget_DD2_Z4_3->setHorizontalHeaderLabels(QStringList()<< "波束离轴角指向"<< "波束方位角指向");
    for(int i = 0;i < 255;i ++)
    {
        ui->tableWidget_DD2_Z4_3->insertRow(i);

        ui->tableWidget_DD2_Z4_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD2_Z4_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD2_Z4_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD2_Z4_3->verticalHeader()->setVisible(true);  // 隐藏行号
    //子阵4区域扫描模式
    ui->tableWidget_DD4_Z4_3->setColumnCount(2);
    ui->tableWidget_DD4_Z4_3->setHorizontalHeaderLabels(QStringList()<< "区域点经度(度)"<< "区域点纬度(度)");
    for(int i = 0;i < 5;i ++)
    {
        ui->tableWidget_DD4_Z4_3->insertRow(i);

        ui->tableWidget_DD4_Z4_3->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_DD4_Z4_3->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
    ui->tableWidget_DD4_Z4_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_DD4_Z4_3->verticalHeader()->setVisible(true);  // 隐藏行号



}

// 电子侦察任务基本信息
uchar *sub1553_Overheadtask::set_Elec_ReconData(int &strlen) {
    uint tmp_uint = 0;
    ushort tmp_ushort = 0;
    Elec_Recon str_ElecRecon;
    memset(&str_ElecRecon, 0, sizeof(Elec_Recon));
    strlen = sizeof(Elec_Recon);  // 需要写入的侦察任务总长度
    //数据通道流向
    ushort bit15_12,bit11_8,bit7_4,bit3_0;
    bit15_12=ui->comboBox_D1_bit15_12->currentIndex();
    if(ui->comboBox_D1_bit15_12->currentIndex()==13)bit15_12=15;

    bit11_8=ui->comboBox_D1_bit11_8->currentIndex();
    if(ui->comboBox_D1_bit11_8->currentIndex()==13)bit11_8=15;

    bit7_4=ui->comboBox_D1_bit7_4->currentIndex();
    if(ui->comboBox_D1_bit7_4->currentIndex()==13)bit7_4=15;

    bit3_0=ui->comboBox_D1_bit3_0->currentIndex();
    if(ui->comboBox_D1_bit3_0->currentIndex()==13)bit3_0=15;

    str_ElecRecon.datastrim=(bit15_12<<12)+(bit11_8<<8)+(bit7_4<<4)+bit3_0;
    str_ElecRecon.datastrim=qToBigEndian(str_ElecRecon.datastrim);
    // 限速速率
    str_ElecRecon.limitspeed = ui->comboBox_D3->currentIndex()+1;
    // 本振选择方式
    str_ElecRecon.bz_choose = ui->comboBox_D4->currentIndex();
    // 天线与通道对应模式
    str_ElecRecon.aerial_ad = ui->comboBox_D6->currentIndex() + 1;
    // 1本振使用信息
    if(ui->comboBox_D4->currentIndex()==1)//共本振
    {
        str_ElecRecon.bz1_mess=ui->comboBox_D5_b0->currentIndex();
    }
    else//独立本振
    {
        str_ElecRecon.bz1_mess = ui->comboBox_2D5_b0->currentIndex()+(ui->comboBox_2D5_b1->currentIndex()<<1);
    }

    // 射频通道号
    str_ElecRecon.sp_ad[0]= ui->comboBox_D7->currentIndex();
    str_ElecRecon.sp_ad[1]= ui->comboBox_D7_2->currentIndex();
    if(ui->comboBox_D7_2->currentIndex()==4)str_ElecRecon.sp_ad[1]=0xFF;

    // 射频通道参数设置
    if (ui->comboBox_C3->currentIndex() == 0) {//L频段
        str_ElecRecon.sp_addata[0] = ui->checkBox_D8bit0->isChecked() +(ui->checkBox_D8bit1->isChecked() << 1)
                +(ui->checkBox_D8bit2->isChecked() << 2) +((ui->checkBox_D8bit3->isChecked() << 3));
        str_ElecRecon.sp_addata[1]=0xff;
    } else {//sxuk频段
        //共本振
        str_ElecRecon.sp_addata[0] = ui->checkBox_D8bit1->isChecked() +(ui->comboBox_D8bit1_2->currentIndex() << 1);
        str_ElecRecon.sp_addata[1]=str_ElecRecon.sp_addata[0];
        if(ui->comboBox_D4->currentIndex()==0)//独立本振
        {
            str_ElecRecon.sp_addata[0] = ui->checkBox_D8bit0->isChecked() +(ui->comboBox_D8bit1_2->currentIndex() << 1);
            str_ElecRecon.sp_addata[1] = ui->checkBox_D8bit1->isChecked() +(ui->comboBox_D8bit1_2_2->currentIndex() << 1);
        }
    }
    // 射频通道接收衰减
    if (ui->comboBox_C3->currentIndex() == 0) {
        str_ElecRecon.sp_adlow[0] = ui->lineEdit_D9->text().toInt();
        str_ElecRecon.sp_adlow[1] = 0xff;
    }
    else
    {
        //共本振
        str_ElecRecon.sp_adlow[0] = ui->lineEdit_D9->text().toInt();
        str_ElecRecon.sp_adlow[1] = str_ElecRecon.sp_adlow[1];
        if(ui->comboBox_D4->currentIndex()==0)//独立本振
        {
            str_ElecRecon.sp_adlow[0] = ui->lineEdit_D9->text().toInt();
            str_ElecRecon.sp_adlow[1] = ui->lineEdit_D9_2->text().toInt();
        }
    }


    // 天线子阵参数
    str_ElecRecon.aerial_patameter = ui->checkBox_D10bit0->isChecked() +
            (ui->checkBox_D10bit1->isChecked() << 1) +
            (ui->checkBox_D10bit2->isChecked() << 2) +
            (ui->checkBox_D10bit3->isChecked() << 3) +
            (ui->comboBox_D10bit5->currentIndex() << 5) +
            (ui->comboBox_D10bit6->currentIndex() << 6)+
            (ui->comboBox_D10bit7->currentIndex() << 7);
    // 天线控制间隔时间
    str_ElecRecon.aerial_time = ui->lineEdit_D11->text().toInt();
    // 天线指向算法数据源
    str_ElecRecon.aerial_data=ui->comboBox_D12->currentIndex();
    //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    str_ElecRecon.aerial_low=(ui->comboBox_D13b7_6->currentIndex()<<6);
    //开关矩阵选择
    str_ElecRecon.switch_Choose=ui->comboBox_D15->currentIndex();
    if(ui->comboBox_D15->currentIndex()==0)str_ElecRecon.switch_Choose=0x10;
    if(ui->comboBox_D15->currentIndex()==1)str_ElecRecon.switch_Choose=0x11;
    if(ui->comboBox_D15->currentIndex()==2)str_ElecRecon.switch_Choose=0x12;
    if(ui->comboBox_D15->currentIndex()==3)str_ElecRecon.switch_Choose=0x14;
    if(ui->comboBox_D15->currentIndex()==4)str_ElecRecon.switch_Choose=0xff;
    if(ui->comboBox_C3->currentIndex() == 1)
    {
        str_ElecRecon.switch_Choose=0;
        str_ElecRecon.switch_Choose=(ui->lineEdit_D15_2->text().toInt())+(ui->lineEdit_D15_1->text().toInt()<<4);
    }


    //波束合成标志7.2
    str_ElecRecon.bs_hc=ui->comboBox_D14->currentIndex()+1;
    if(ui->comboBox_C3->currentIndex() == 1)//SXKU
    {
        if(ui->comboBox_D14->currentIndex()==0)str_ElecRecon.bs_hc=0x1F;
        if(ui->comboBox_D14->currentIndex()==1)str_ElecRecon.bs_hc=0xD0;
    }

    //数字波束1偏置离轴角
    str_ElecRecon.zz1_lz=qToBigEndian(ui->lineEdit_zc_zz1lz->text().toUShort());
    //数字波束1偏置方位角
    str_ElecRecon.zz1_fw=qToBigEndian(ui->lineEdit_zc_zz1fw->text().toUShort());

    //数字波束2偏置离轴角
    str_ElecRecon.zz2_lz=qToBigEndian(ui->lineEdit_zc_zz2lz->text().toUShort());
    //数字波束2偏置方位角
    str_ElecRecon.zz2_fw=qToBigEndian(ui->lineEdit_zc_zz2fw->text().toUShort());

    //数字波束3偏置离轴角
    str_ElecRecon.zz3_lz=qToBigEndian(ui->lineEdit_zc_zz3lz->text().toUShort());
    //数字波束3偏置方位角
    str_ElecRecon.zz3_fw=qToBigEndian(ui->lineEdit_zc_zz3fw->text().toUShort());

    //数字波束4偏置离轴角
    str_ElecRecon.zz4_lz=qToBigEndian(ui->lineEdit_zc_zz4lz->text().toUShort());
    //数字波束4偏置方位角
    str_ElecRecon.zz4_fw=qToBigEndian(ui->lineEdit_zc_zz4fw->text().toUShort());

    // 天线子阵号(1-4个循环个数,按照天线子阵参数确定)。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。
    aerial_ZCmode1_zxzl str_zxzl;
    aerial_ZCmode2_zxsm str_zxsm;
    aerial_ZCmode3_qyns str_qyns;
    aerial_ZCmode4_qysm str_qysm;


    uchar *buff_mode_all4 =new uchar[5000];  // 不定总长，存储所以子阵数据（暂时开辟2k）
    memset(buff_mode_all4, 0, 5000);
    int modeLen_SUM = 0;  // 4个子阵的变长总长总长
    int sum_cntnum=0;//模式内的循环体计数

    //if(ui->comboBox_D10bit7->currentIndex()==1);//子阵一致，就只用1个循环
    // 子阵1
    if (ui->checkBox_D10bit0->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_elecZC_contrlmode->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_DD1_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_DD1_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_DD1_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 1:  // 指向扫描模式参数

            modeLen_1 = sizeof(str_zxsm);
            // 天线子阵号
            str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;
            // 极化方式
            str_zxsm.polarmand = ui->comboBox_DD2_1->currentIndex();
            // 指向驻留时间
            str_zxsm.zx_ontime = ui->lineEdit_DD2_5->text().toInt();
            // 指向个数
            str_zxsm.pointsum = ui->lineEdit_DD2_2->text().toInt();
            if(ui->lineEdit_DD2_2->text().toInt()>255)str_zxsm.pointsum=255;

            sum_cntnum=str_zxsm.pointsum;
            if(sum_cntnum>255)sum_cntnum=255;
            for (int i=0;i<sum_cntnum;i++) {
                // 波束离轴角指向
                tmp_ushort = ui->tableWidget_DD2->item(i,0)->text().toInt();
                str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->tableWidget_DD2->item(i,1)->text().toInt();
                str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
            }
            // 拷贝数据
            modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;

            // 极化方式
            str_qyns.polarmand = ui->comboBox_DD3_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_DD3_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_DD3_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        case 3:  // 区域扫描模式参数

            modeLen_1 = sizeof(str_qysm);
            // 天线子阵号
            str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_qysm.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;
            // 极化方式
            str_qysm.polarmand = ui->comboBox_DD4_1->currentIndex();
            // 区域驻留时间
            str_qysm.region_onntime = ui->lineEdit_DD4_5->text().toInt();
            // 区域点个数
            tmp_ushort = ui->lineEdit_DD4_2->text().toInt();
            str_qysm.region_sum = qToBigEndian(tmp_ushort);

            sum_cntnum=tmp_ushort;
            if(sum_cntnum>5)sum_cntnum=5;
            for (int i=0;i<sum_cntnum;i++) {
                // 区域点经度
                tmp_uint = ui->tableWidget_DD4->item(i,0)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                // 区域点纬度
                tmp_uint = ui->tableWidget_DD4->item(i,1)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
            }

            // 拷贝数据
            modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;
    };

    if(ui->comboBox_D10bit7->currentIndex()==0)//子阵不一致
    {
        // 子阵2
        if (ui->checkBox_D10bit1->isChecked()) {
            // 电子侦察任务--天线子阵参数变长部分
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));

            int modeLen_1 = 0;  // 当前子阵的总长
            switch (ui->cB_elecZC_contrlmode_Z2->currentIndex()) {
            case 0:  // 指向驻留模式参数

                modeLen_1 = sizeof(str_zxzl);
                // 天线子阵号
                str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_zxzl.polarmand = ui->comboBox_DD1Z2_1->currentIndex();
                // 波束离轴角指向
                tmp_ushort = ui->lineEdit_DD1Z2_2->text().toInt();
                str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->lineEdit_DD1Z2_3->text().toInt();
                str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
                break;
            case 1:  // 指向扫描模式参数

                modeLen_1 = sizeof(str_zxsm);
                // 天线子阵号
                str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_zxsm.polarmand = ui->comboBox_DD2Z2_1->currentIndex();
                // 指向驻留时间
                str_zxsm.zx_ontime = ui->lineEdit_DD2Z2_2->text().toInt();
                // 指向个数
                str_zxsm.pointsum = ui->lineEdit_DD2Z2_3->text().toInt();
                if(ui->lineEdit_DD2Z2_3->text().toInt()>255)str_zxsm.pointsum=255;

                sum_cntnum=str_zxsm.pointsum;
                if(sum_cntnum>255)sum_cntnum=255;
                for (int i=0;i<sum_cntnum;i++) {
                    // 波束离轴角指向
                    tmp_ushort = ui->tableWidget_DD2_Z2->item(i,0)->text().toInt();
                    str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                    // 波束方位角指向
                    tmp_ushort = ui->tableWidget_DD2_Z2->item(i,1)->text().toInt();
                    str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
                }
                // 拷贝数据
                modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
                break;

            case 2:  // 区域凝视模式参数

                modeLen_1 = sizeof(str_qyns);
                // 天线子阵号
                str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_qyns.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_qyns.polarmand = ui->comboBox_DD3Z2_1->currentIndex();
                // 目标经度
                tmp_uint = ui->lineEdit_DD3Z2_2->text().toDouble()*1000000;
                str_qyns.target_orb = qToBigEndian(tmp_uint);
                // 目标纬度
                tmp_uint = ui->lineEdit_DD3Z2_3->text().toDouble()*1000000;
                str_qyns.target_latitude = qToBigEndian(tmp_uint);
                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
                break;
            case 3:  // 区域扫描模式参数

                modeLen_1 = sizeof(str_qysm);
                // 天线子阵号
                str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_qysm.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_qysm.polarmand = ui->comboBox_DD4Z2_1->currentIndex();
                // 区域驻留时间
                str_qysm.region_onntime = ui->lineEdit_DD4Z2_2->text().toInt();
                // 区域点个数
                tmp_ushort = ui->lineEdit_DD4Z2_3->text().toInt();
                str_qysm.region_sum = qToBigEndian(tmp_ushort);

                sum_cntnum=tmp_ushort;
                if(sum_cntnum>5)sum_cntnum=5;
                for (int i=0;i<sum_cntnum;i++) {
                    // 区域点经度
                    tmp_uint = ui->tableWidget_DD4_Z2->item(i,0)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                    // 区域点纬度
                    tmp_uint = ui->tableWidget_DD4_Z2->item(i,1)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
                }

                // 拷贝数据
                modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
                break;

            default:
                break;
            }

            modeLen_SUM += modeLen_1;
        };
        // 子阵3
        if (ui->checkBox_D10bit2->isChecked()) {
            // 电子侦察任务--天线子阵参数变长部分
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));

            int modeLen_1 = 0;  // 当前子阵的总长
            switch (ui->cB_elecZC_contrlmode_Z3->currentIndex()) {
            case 0:  // 指向驻留模式参数

                modeLen_1 = sizeof(str_zxzl);

                // 天线子阵号
                str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_zxzl.polarmand = ui->comboBox_DD1Z3_1->currentIndex();
                // 波束离轴角指向
                tmp_ushort = ui->lineEdit_DD1Z3_2->text().toInt();
                str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->lineEdit_DD1Z3_3->text().toInt();
                str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
                break;
            case 1:  // 指向扫描模式参数

                modeLen_1 = sizeof(str_zxsm);
                // 天线子阵号
                str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_zxsm.polarmand = ui->comboBox_DD2Z3_1->currentIndex();
                // 指向驻留时间
                str_zxsm.zx_ontime = ui->lineEdit_DD2Z3_2->text().toInt();
                // 指向个数
                str_zxsm.pointsum = ui->lineEdit_DD2Z3_3->text().toInt();
                if(ui->lineEdit_DD2Z3_3->text().toInt()>255)str_zxsm.pointsum=255;


                sum_cntnum=str_zxsm.pointsum;
                if(sum_cntnum>255)sum_cntnum=255;
                for (int i=0;i<sum_cntnum;i++) {
                    // 波束离轴角指向
                    tmp_ushort = ui->tableWidget_DD2_Z3->item(i,0)->text().toInt();
                    str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                    // 波束方位角指向
                    tmp_ushort = ui->tableWidget_DD2_Z3->item(i,1)->text().toInt();
                    str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
                }
                // 拷贝数据
                modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
                break;
            case 2:  // 区域凝视模式参数

                modeLen_1 = sizeof(str_qyns);
                // 天线子阵号
                str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_qyns.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_qyns.polarmand = ui->comboBox_DD3Z3_1->currentIndex();
                // 目标经度
                tmp_uint = ui->lineEdit_DD3Z3_2->text().toDouble()*1000000;
                str_qyns.target_orb = qToBigEndian(tmp_uint);
                // 目标纬度
                tmp_uint = ui->lineEdit_DD3Z3_3->text().toDouble()*1000000;
                str_qyns.target_latitude = qToBigEndian(tmp_uint);
                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
                break;
            case 3:  // 区域扫描模式参数

                modeLen_1 = sizeof(str_qysm);
                // 天线子阵号
                str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_qysm.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_qysm.polarmand = ui->comboBox_DD4Z3_1->currentIndex();
                // 区域驻留时间
                str_qysm.region_onntime = ui->lineEdit_DD4Z3_2->text().toInt();
                // 区域点个数
                tmp_ushort = ui->lineEdit_DD4Z3_3->text().toInt();
                str_qysm.region_sum = qToBigEndian(tmp_ushort);

                sum_cntnum=tmp_ushort;
                if(sum_cntnum>5)sum_cntnum=5;
                for (int i=0;i<sum_cntnum;i++) {
                    // 区域点经度
                    tmp_uint = ui->tableWidget_DD4_Z3->item(i,0)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                    // 区域点纬度
                    tmp_uint = ui->tableWidget_DD4_Z3->item(i,1)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
                }

                // 拷贝数据
                modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
                break;
            default:
                break;
            }

            modeLen_SUM += modeLen_1;
            ;
        };
        // 子阵4
        if (ui->checkBox_D10bit3->isChecked()) {
            // 电子侦察任务--天线子阵参数变长部分
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));

            int modeLen_1 = 0;  // 当前子阵的总长
            switch (ui->cB_elecZC_contrlmode_Z4->currentIndex()) {
            case 0:  // 指向驻留模式参数

                modeLen_1 = sizeof(str_zxzl);
                // 天线子阵号
                str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_zxzl.polarmand = ui->comboBox_DD1Z4_1->currentIndex();
                // 波束离轴角指向
                tmp_ushort = ui->lineEdit_DD1Z4_2->text().toInt();
                str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->lineEdit_DD1Z4_3->text().toInt();
                str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
                break;
            case 1:  // 指向扫描模式参数

                modeLen_1 = sizeof(str_zxsm);
                // 天线子阵号
                str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_zxsm.polarmand = ui->comboBox_DD2Z4_1->currentIndex();
                // 指向驻留时间
                str_zxsm.zx_ontime = ui->lineEdit_DD2Z4_2->text().toInt();
                // 指向个数
                str_zxsm.pointsum = ui->lineEdit_DD2Z4_3->text().toInt();
                if(ui->lineEdit_DD2Z4_3->text().toInt()>255)str_zxsm.pointsum=255;

                sum_cntnum=str_zxsm.pointsum;
                if(sum_cntnum>255)sum_cntnum=255;
                for (int i=0;i<sum_cntnum;i++) {
                    // 波束离轴角指向
                    tmp_ushort = ui->tableWidget_DD2_Z4->item(i,0)->text().toInt();
                    str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                    // 波束方位角指向
                    tmp_ushort = ui->tableWidget_DD2_Z4->item(i,1)->text().toInt();
                    str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
                }
                // 拷贝数据
                modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
                break;
            case 2:  // 区域凝视模式参数

                modeLen_1 = sizeof(str_qyns);
                // 天线子阵号
                str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_qyns.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_qyns.polarmand = ui->comboBox_DD3Z4_1->currentIndex();
                // 目标经度
                tmp_uint = ui->lineEdit_DD3Z4_2->text().toDouble()*1000000;
                str_qyns.target_orb = qToBigEndian(tmp_uint);
                // 目标纬度
                tmp_uint = ui->lineEdit_DD3Z4_3->text().toDouble()*1000000;
                str_qyns.target_latitude = qToBigEndian(tmp_uint);
                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
                break;
            case 3:  // 区域扫描模式参数

                modeLen_1 = sizeof(str_qysm);
                // 天线子阵号
                str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_qysm.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_qysm.polarmand = ui->comboBox_DD4Z4_1->currentIndex();
                // 区域驻留时间
                str_qysm.region_onntime = ui->lineEdit_DD4Z4_2->text().toInt();
                // 区域点个数
                tmp_ushort = ui->lineEdit_DD4Z4_3->text().toInt();
                str_qysm.region_sum = qToBigEndian(tmp_ushort);

                sum_cntnum=tmp_ushort;
                if(sum_cntnum>5)sum_cntnum=5;
                for (int i=0;i<sum_cntnum;i++) {
                    // 区域点经度
                    tmp_uint = ui->tableWidget_DD4_Z4->item(i,0)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                    // 区域点纬度
                    tmp_uint = ui->tableWidget_DD4_Z4->item(i,1)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
                }

                // 拷贝数据
                modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
                break;
            default:
                break;
            }

            modeLen_SUM += modeLen_1;
        };


    }
    strlen += modeLen_SUM;

    uchar *buff_elec_aerial = new uchar[strlen + 1];
    memcpy(buff_elec_aerial, &str_ElecRecon, sizeof(Elec_Recon));
    memcpy(buff_elec_aerial + sizeof(Elec_Recon), buff_mode_all4, modeLen_SUM);

    return buff_elec_aerial;
}

// 电子干扰任务基本信息
uchar *sub1553_Overheadtask::set_Elec_JammingData(int &strlen) {
    uint tmp_uint = 0;
    ushort tmp_ushort = 0;

    Elec_Jamming str_Elecjamming;
    memset(&str_Elecjamming, 0, sizeof(Elec_Jamming));
    strlen = sizeof(Elec_Jamming);  // 需要写入的干扰任务总长度

    //数据通道流向
    ushort bit15_12,bit11_8,bit7_4,bit3_0;
    bit15_12=ui->comboBox_gr1_bit15_12->currentIndex();
    if(ui->comboBox_gr1_bit15_12->currentIndex()==1)bit15_12=9;

    bit11_8=ui->comboBox_gr1_bit11_8->currentIndex();
    if(ui->comboBox_gr1_bit11_8->currentIndex()==1)bit11_8=9;

    bit7_4=ui->comboBox_gr1_bit7_4->currentIndex();
    if(ui->comboBox_gr1_bit7_4->currentIndex()==1)bit7_4=9;

    bit3_0=ui->comboBox_gr1_bit3_0->currentIndex();
    if(ui->comboBox_gr1_bit3_0->currentIndex()==1)bit3_0=9;

    str_Elecjamming.datastrim=(bit15_12<<12)+(bit11_8<<8)+(bit7_4<<4)+bit3_0;
    str_Elecjamming.datastrim=qToBigEndian(str_Elecjamming.datastrim);

    // 本振选择方式
    str_Elecjamming.bz_choose = ui->comboBox_E3->currentIndex();

    //天线与通道对应模式选择
    str_Elecjamming.txytddyms=ui->comboBox_Dtxytddyms->currentIndex() + 1;

    // 1本振使用信息
    if(ui->comboBox_E3->currentIndex()==1)//共本振
    {
        str_Elecjamming.bz1_mess=ui->comboBox_gr5_b0->currentIndex();
    }
    else//独立本振
    {
        str_Elecjamming.bz1_mess = ui->comboBox_gr5_b0_->currentIndex()+(ui->comboBox_gr5_b1->currentIndex()<<1);
    }

    // 射频通道参数设置
    if (ui->comboBox_C3->currentIndex() == 0) {//L频段
        str_Elecjamming.sp_addata[0] = ui->checkBox_E6bit0->isChecked() +
                (ui->checkBox_E6bit1->isChecked() << 1) +
                (ui->checkBox_E6bit2->isChecked() << 2) +
                ((ui->checkBox_E6bit3->isChecked() << 3));
        str_Elecjamming.sp_addata[1]=0xFF;
    } else {//Sxku频段
        //共本振
        str_Elecjamming.sp_addata[0] = ui->checkBox_E6bit1->isChecked() +(ui->comboBox_D8bit1_4->currentIndex() << 1);
        str_Elecjamming.sp_addata[1]=str_Elecjamming.sp_addata[0];
        if(ui->comboBox_E3->currentIndex()==0)//独立本振
        {
            str_Elecjamming.sp_addata[0] = ui->checkBox_E6bit0->isChecked() +(ui->comboBox_D8bit1_4->currentIndex() << 1);
            str_Elecjamming.sp_addata[1] = ui->checkBox_E6bit1->isChecked() +(ui->comboBox_D8bit1_4_2->currentIndex() << 1);
        }
    }
    // 射频通道发射衰减
    //L频段
    if(ui->comboBox_C3->currentIndex()==0)
    {
        str_Elecjamming.sp_adlow[0] = ui->lineEdit_E7->text().toInt();
        str_Elecjamming.sp_adlow[1] = 0xFF;
    }
    //Sxku频段
    else {
        str_Elecjamming.sp_adlow[0]=ui->lineEdit_E7->text().toUInt();
        str_Elecjamming.sp_adlow[1]= str_Elecjamming.sp_adlow[0];
        if(ui->comboBox_E3->currentIndex()==0)str_Elecjamming.sp_adlow[1]= ui->lineEdit_E7_3->text().toUInt();//独立本振

    }
    // 射频通道接收衰减
    //L频段
    if(ui->comboBox_C3->currentIndex()==0)
    {
        str_Elecjamming.sp_jslow[0] = ui->lineEdit_E7_2->text().toInt();
        str_Elecjamming.sp_jslow[1] = 0xFF;
    }
    //Sxku频段
    else {
        str_Elecjamming.sp_jslow[0]=ui->lineEdit_E7_2->text().toUInt();
        str_Elecjamming.sp_jslow[1]= str_Elecjamming.sp_jslow[0];
        if(ui->comboBox_E3->currentIndex()==0)str_Elecjamming.sp_jslow[1]= ui->lineEdit_E7_2_2->text().toUInt();//独立本振


    }
    // 天线子阵参数
    str_Elecjamming.aerial_patameter =
            ui->checkBox_E7bit0->isChecked() +
            (ui->checkBox_E7bit1->isChecked() << 1) +
            (ui->checkBox_E7bit2->isChecked() << 2) +
            (ui->checkBox_E7bit3->isChecked() << 3) ;
    if(ui->comboBox_C3->currentIndex()==0)
    {
        str_Elecjamming.aerial_patameter =(ui->comboBox_E7bit5->currentIndex()+1) << 5;
    }
    else
    {
        str_Elecjamming.aerial_patameter =
                ((ui->comboBox_E7bit5->currentIndex()) << 5) +
                (ui->comboBox_E7bit6->currentIndex() << 6);
    }

    // 天线子阵控制模式
    str_Elecjamming.aerial_mode = ui->comboBox_E9->currentIndex()+1;
    // 天线间隔时间
    str_Elecjamming.aerial_time = ui->lineEdit_E11->text().toUInt();
    // 天线指向算法数据源
    str_Elecjamming.aerial_pointing = ui->comboBox_E12->currentIndex();

    //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    str_Elecjamming.aerial_low =ui->lineEdit_E13b5_0->text().toInt()+ (ui->comboBox_E13b7_6->currentIndex()<<6);


    // 3种模式参数
    aerial_GRmode1_zxzl str_GRmode1_zxzl;
    aerial_GRmode2_zxsm str_GRmode2_zxsm;
    aerial_GRmode3_qyns str_GRmode3_qyns;

    memset(&str_GRmode1_zxzl, 0, sizeof(str_GRmode1_zxzl));
    memset(&str_GRmode2_zxsm, 0, sizeof(str_GRmode2_zxsm));
    memset(&str_GRmode3_qyns, 0, sizeof(str_GRmode3_qyns));
    int sum_cntnum=0;//模式内的循环体计数
    int GRmode2_zxsm_len=0;

    int kind=ui->comboBox_E9->currentIndex() + 1;
    switch (kind) {
    case 1:
        strlen += sizeof(str_GRmode1_zxzl);
        // 极化方式
        str_GRmode1_zxzl.polarmand =
                ui->comboBox_GR1_zxzl_b1->currentIndex() +
                (ui->comboBox_GR1_zxzl_b2->currentIndex() << 2) +
                (ui->comboBox_GR1_zxzl_b3->currentIndex() << 4) +
                (ui->comboBox_GR1_zxzl_b4->currentIndex() << 6);
        //极化切换时间
        str_GRmode1_zxzl.qh_time=ui->lineEdit_GR1_zxzl_4->text().toInt();
        // 波束离轴角指向
        tmp_ushort = ui->lineEdit_GR1_zxzl_2->text().toInt();
        str_GRmode1_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
        // 波束方位角指向
        tmp_ushort = ui->lineEdit_GR1_zxzl_3->text().toInt();
        str_GRmode1_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

        break;
    case 2:
        // 极化方式
        str_GRmode2_zxsm.polarmand =
                ui->comboBox_GR1_zxsm_b1->currentIndex() +
                (ui->comboBox_GR1_zxsm_b2->currentIndex() << 2) +
                (ui->comboBox_GR1_zxsm_b3->currentIndex() << 4) +
                (ui->comboBox_GR1_zxsm_b4->currentIndex() << 6);
        //极化切换时间
        str_GRmode2_zxsm.qh_time=ui->lineEdit_GR1_zxsm_1->text().toInt();
        // 指向驻留时间
        str_GRmode2_zxsm.zx_ontime = ui->lineEdit_GR1_zxsm_2->text().toInt();
        // 指向个数
        str_GRmode2_zxsm.pointsum = ui->lineEdit_GR1_zxsm_3->text().toInt();
        if(ui->lineEdit_GR1_zxsm_3->text().toInt()>255)str_GRmode2_zxsm.pointsum=255;

        sum_cntnum=str_GRmode2_zxsm.pointsum;
        if(sum_cntnum>255)sum_cntnum=255;
        for (int i=0;i<sum_cntnum;i++) {
            // 波束离轴角指向
            tmp_ushort = ui->tableWidget_GR1_zxsm_4->item(i,0)->text().toInt();
            str_GRmode2_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->tableWidget_GR1_zxsm_4->item(i,1)->text().toInt();
            str_GRmode2_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
        }


        GRmode2_zxsm_len=sizeof(str_GRmode2_zxsm)-(255-sum_cntnum)*sizeof (Cyc_zxsm);
        strlen +=GRmode2_zxsm_len;


        break;
    case 3:
        strlen += sizeof(str_GRmode3_qyns);
        // 目标经度
        tmp_uint = ui->lineEdit_EE1_1->text().toUInt();
        str_GRmode3_qyns.target_orb = qToBigEndian(tmp_uint);
        // 目标纬度
        tmp_uint = ui->lineEdit_EE1_2->text().toUInt();
        str_GRmode3_qyns.target_latitude = qToBigEndian(tmp_uint);
        // 极化方式
        str_GRmode3_qyns.polarmand =
                ui->comboBox_EE3_bit0_1->currentIndex() +
                (ui->comboBox_EE3_bit2_3->currentIndex() << 2) +
                (ui->comboBox_EE3_bit4_5->currentIndex() << 4) +
                (ui->comboBox_EE3_bit6_7->currentIndex() << 6);
        //极化切换时间
        str_GRmode3_qyns.qh_time=ui->lineEdit_EE1_4->text().toInt();

        break;
    default:
        break;
    }

    uchar *buff_elec_aerial = new uchar[strlen + 1];
    memcpy(buff_elec_aerial, &str_Elecjamming, sizeof(Elec_Jamming));
    if(kind==1)memcpy(buff_elec_aerial + sizeof(Elec_Jamming), &str_GRmode1_zxzl,sizeof(aerial_GRmode1_zxzl));
    if(kind==2)memcpy(buff_elec_aerial + sizeof(Elec_Jamming), &str_GRmode2_zxsm,GRmode2_zxsm_len);
    if(kind==3)memcpy(buff_elec_aerial + sizeof(Elec_Jamming), &str_GRmode3_qyns,sizeof(aerial_GRmode3_qyns));

    return buff_elec_aerial;
}



//SXKu天线定标任务基本信息格式
uchar *sub1553_Overheadtask::set_Elec_sxkuDB(int &strlen) {

    //    uint tmp_uint = 0;
    //    ushort tmp_ushort = 0;
    //    Elec_Recon str_ElecRecon;
    //    memset(&str_ElecRecon, 0, sizeof(Elec_Recon));


    Elec_sxkuDB str_sxkuDB;
    strlen = sizeof(Elec_sxkuDB);  // 需要写入的侦察任务总长度
    memset(&str_sxkuDB, 0, sizeof(Elec_sxkuDB));
    //数据通道流向
    ushort bit15_12,bit11_8,bit7_4,bit3_0;
    bit15_12=13;//协议固定13
    bit11_8=13;
    bit7_4=13;
    bit3_0=13;
    str_sxkuDB.datastrim=(bit15_12<<12)+(bit11_8<<8)+(bit7_4<<4)+bit3_0;
    str_sxkuDB.datastrim=qToBigEndian(str_sxkuDB.datastrim);
    // 本振选择方式
    str_sxkuDB.bz_choose=ui->comboBox_PD5ybz->currentIndex();
    // 1本振使用信息
    str_sxkuDB.bz1_mess=ui->comboBox_PD6ybzxx->currentIndex();
    // 1本振使用信息
    str_sxkuDB.tx_mode=ui->comboBox_dbtx_4->currentIndex()+1;
    // 1本振使用信息
    str_sxkuDB.spAD=ui->comboBox_dbtx_5->currentIndex();
    // 射频通道参数设置
    uchar bit0,bit1_2;
    bit0=ui->comboBox_PD7yjfdsn->currentIndex();
    bit1_2=ui->comboBox_PD8tdjssj->currentIndex();
    str_sxkuDB.sp_addata=(bit1_2<<1)+bit0;
    // 射频通道接收衰减
    str_sxkuDB.sp_recvlow=ui->lineEdit_PD1js->text().toUInt();
    //射频通道发射衰减
    str_sxkuDB.sp_sendlow=ui->lineEdit_PD2fs->text().toUInt();
    //接收机频率
    str_sxkuDB.fre=qToBigEndian(ui->lineEdit_PD9fre->text().toUInt());
    //阵面H/V极化选择
    str_sxkuDB.ZMHV=ui->comboBox_PD9zmhvjh->currentIndex();

    //指定移相值
    str_sxkuDB.zdyx=ui->lineEdit_PD3yxz->text().toUInt();
    //指定衰减值
    str_sxkuDB.zdlow=ui->lineEdit_PD4sjz->text().toUInt();
    // str_sxkuDB.zdlow=ui->lineEdit_PD4sjz->text().toUInt();
    //指定延时（小位）值
    str_sxkuDB.zddelayed=ui->lineEdit_PD5ysxz->text().toUInt();
    //str_sxkuDB.zddelayed=ui->lineEdit_PD5ysxz->text().toUInt();
    //指定延时（大位/中位）值
    str_sxkuDB.zdbigdelayed=ui->lineEdit_PD6ysdz->text().toUInt();


    uchar *buff_elec_aerial = new uchar[strlen + 1];
    memcpy(buff_elec_aerial, &str_sxkuDB, sizeof(Elec_sxkuDB));
    return buff_elec_aerial;

}

//SAR探测任务基本信息
uchar *sub1553_Overheadtask::set_SAR_probing(int &strlen)
{

    SAR_Str str_SAR;

    memset(&str_SAR, 0, sizeof(str_SAR));
    strlen = sizeof(str_SAR);  // 需要写入的侦察任务总长度
    //收发FPGA_1
    str_SAR.sf_FPGA_1=toHex_ushort(ui->lineEdit_D4_1->text());
    //收发FPGA_2
    str_SAR.sf_FPGA_2=toHex_ushort(ui->lineEdit_D4_2->text());
    //数据处理板A的FPGA_1
    str_SAR.A_FPGA_1=toHex_ushort(ui->lineEdit_D4_3->text());
    //数据处理板A的FPGA_2
    str_SAR.A_FPGA_2=toHex_ushort(ui->lineEdit_D4_4->text());
    //数据处理板A的DSP
    str_SAR.A_dsp=toHex_ushort(ui->lineEdit_D4_5->text());
    //数据处理板B的FPGA_1
    str_SAR.B_FPGA_1=toHex_ushort(ui->lineEdit_D4_6->text());
    //数据处理板B的FPGA_2
    str_SAR.B_FPGA_2=toHex_ushort(ui->lineEdit_D4_7->text());
    //数据处理板B的DSP
    str_SAR.B_dsp=toHex_ushort(ui->lineEdit_D4_8->text());
    //bit7-bit4:引导方式 bit3-bit0:侦察定位模式
    str_SAR.is_yd=(ui->cB_D4_9->currentIndex()<<4)+ui->cB_D4_9_2->currentIndex();

    //是否实时成像
    str_SAR.is_cx=ui->comboBox_SAR_10->currentIndex();
    // 天线与通道对应模式
    str_SAR.aerial_ad=ui->comboBox_DH_aerial_ad_2->currentIndex()+1;
    // 射频通道号
    str_SAR.sp_ad=ui->comboBox_DH_sp_ad_2->currentIndex();
    // 射频通道参数设置
    str_SAR.sp_addata = ui->checkBox_sp_addata_bit0_2->isChecked() +
            (ui->checkBox_sp_addata_bit1_2->isChecked() << 1) +
            (ui->checkBox_sp_addata_bit2_2->isChecked() << 2) +
            ((ui->checkBox_sp_addata_bit3_2->isChecked() << 3));
    // 射频通道发射衰减
    str_SAR.sp_fslow=ui->lineEdit_DH_sp_fslow_2->text().toUInt();
    // 射频通道接收衰减
    str_SAR.sp_jslow = ui->lineEdit_DH_sp_jslow_2->text().toUInt();
    // 引导地址
    str_SAR.yddz = toHex_uint(ui->lineEdit_sar_yddz->text());

    //    QString add_data;//256字节一包
    //    add_data=ui->lineEdit_SAR_addData->text();
    //    add_data=add_data.replace(" ","");
    //    add_data=add_data.replace("\n","");
    //    int part_long = (add_data.size() + 1) / 2;//会多一个字节(有'\n')
    //    //if(part_long>256)part_long=256;
    //    uchar * addbuff=new uchar[part_long];//256一个完整包
    //    //qDebug()<<part_long;

    //    int tmplen = part_long;
    //    QByteArray hex_data2 = QByteArray::fromHex(add_data.toLatin1());  // 将字节流转换位16进制,char型
    //    memcpy(addbuff, (uchar *)hex_data2.data(),tmplen);  // 获取地址

    //    strlen+=part_long;
    //    uchar *buff_sar = new uchar[strlen + 1];
    //    memcpy(buff_sar, &str_SAR, sizeof(str_SAR));
    //    memcpy(buff_sar+sizeof(str_SAR), addbuff, part_long);

    //    delete [] addbuff;
    //    return buff_sar;

    uchar *buff_sar = new uchar[strlen + 1];
    memcpy(buff_sar, &str_SAR, sizeof(str_SAR));
    return buff_sar;

}

//备用导航任务基本信息
uchar *sub1553_Overheadtask::set_Elec_BYnavigation(int &strlen){
    uint tmp_uint = 0;
    ushort tmp_ushort = 0;
    Elec_BYnavigation str_byna;
    memset(&str_byna, 0, sizeof(Elec_BYnavigation));
    strlen = sizeof(Elec_BYnavigation);  // 需要写入的侦察任务总长度
    //数据通道流向
    tmp_ushort=ui->lineEdit_DH_1->text().toUShort();
    str_byna.datastrim=qToBigEndian(tmp_ushort);

    // 天线与通道对应模式
    str_byna.aerial_ad=ui->comboBox_DH_aerial_ad->currentIndex()+1;
    // 射频通道号
    str_byna.sp_ad=ui->comboBox_DH_sp_ad->currentIndex();

    // 射频通道发射衰减
    str_byna.sp_fslow=ui->lineEdit_DH_sp_fslow->text().toUInt();
    // 天线子阵参数
    str_byna.aerial_patameter = ui->checkBox_DH_TXbit0->isChecked() +
            (ui->checkBox_DH_TXbit1->isChecked() << 1) +
            (ui->checkBox_DH_TXbit2->isChecked() << 2) +
            (ui->checkBox_DH_TXbit3->isChecked() << 3) +
            (ui->comboBox_DHtxuse->currentIndex() << 5);
    //天线控制间隔时间
    str_byna.aerial_time=ui->lineEdit_DH_aerial_time->text().toUInt();
    // Bit0：天线指向算法数据源/Bit1-Bit6：天线射频发射衰减值
    str_byna.aerial_data=ui->comboBox_DH_aerial_pointing->currentIndex();
    //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    str_byna.aerial_low=ui->lineEdit_DH_aerial_sj->text().toUInt()+(ui->comboBox_DHsjb_6->currentIndex()<<6);

    // 天线子阵号(1-4个循环个数,按照天线子阵参数确定)。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。
    aerial_ZCmode1_zxzl str_zxzl;
    aerial_ZCmode2_zxsm str_zxsm;
    aerial_ZCmode3_qyns str_qyns;
    aerial_ZCmode4_qysm str_qysm;

    uchar *buff_mode_all4 =new uchar[5000];  // 不定总长，存储所以子阵数据（暂时开辟2k）
    memset(buff_mode_all4, 0, 5000);
    int modeLen_SUM = 0;  // 4个子阵的变长总长总长
    int sum_cntnum=0;//模式内的循环体计数
    //子阵1
    if (ui->checkBox_DH_TXbit0->isChecked()) {
        // 备用导航任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));
        int modeLen_1 = 0;  // 当前子阵的总长
        // ui->cB_elecDH_contrlmode->setCurrentIndex(2);
        QString str=ui->cB_elecDH_contrlmode->currentText();
        //int tempSize = ui->cB_elecDH_contrlmode->count();
        switch (ui->cB_elecDH_contrlmode->currentIndex()){
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_elecDH_txnumber->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_elecDH_contrlmode->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_DD1_3->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_DD1_6->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_DD1_7->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 1:  // 指向扫描模式参数

            modeLen_1 = sizeof(str_zxsm);
            // 天线子阵号
            str_zxsm.aerial_zznumber=ui->cB_elecDH_txnumber->currentIndex();
            // 天线子阵控制模式
            str_zxsm.aerial_mode = ui->cB_elecDH_contrlmode->currentIndex() + 1;
            // 极化方式
            str_zxsm.polarmand = ui->comboBox_DD2_3->currentIndex();
            // 指向驻留时间
            str_zxsm.zx_ontime = ui->lineEdit_DD2_7->text().toInt();
            // 指向个数
            str_zxsm.pointsum = ui->lineEdit_DD2_4->text().toInt();

            sum_cntnum=str_zxsm.pointsum;
            if(sum_cntnum>255)sum_cntnum=255;
            for (int i=0;i<sum_cntnum;i++) {
                // 波束离轴角指向
                tmp_ushort = ui->tableWidget_DD2_3->item(i,0)->text().toInt();
                str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->tableWidget_DD2_3->item(i,1)->text().toInt();
                str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
            }
            // 拷贝数据
            modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui-> cB_elecDH_txnumber->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui-> cB_elecDH_contrlmode->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_DD3_3->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_DD3_6->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_DD3_7->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        case 3:  // 区域扫描模式参数

            modeLen_1 = sizeof(str_qysm);
            // 天线子阵号
            str_qysm.aerial_zznumber=ui->cB_elecDH_txnumber->currentIndex();
            // 天线子阵控制模式
            str_qysm.aerial_mode = ui->cB_elecDH_contrlmode->currentIndex() + 1;
            // 极化方式
            str_qysm.polarmand = ui->comboBox_DD4_3->currentIndex();
            // 区域驻留时间
            str_qysm.region_onntime = ui->lineEdit_DD4_7->text().toInt();
            // 区域点个数
            tmp_ushort = ui->lineEdit_DD4_4->text().toInt();
            str_qysm.region_sum = qToBigEndian(tmp_ushort);

            sum_cntnum=tmp_ushort;
            if(sum_cntnum>5)sum_cntnum=5;
            for (int i=0;i<sum_cntnum;i++) {
                // 区域点经度
                tmp_uint = ui->tableWidget_DD4_3->item(i,0)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                // 区域点纬度
                tmp_uint = ui->tableWidget_DD4_3->item(i,1)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
            }

            // 拷贝数据
            modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;

    } ;

    if(ui->comboBox_DHtxuse->currentIndex()==0)
    {
        // 子阵2
        if (ui->checkBox_DH_TXbit1->isChecked()) {
            // 备用导航任务--天线子阵参数变长部分
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));

            int modeLen_1 = 0;  // 当前子阵的总长
            switch (ui->cB_elecDH_contrlmode_Z2->currentIndex()) {
            case 0:  // 指向驻留模式参数

                modeLen_1 = sizeof(str_zxzl);
                // 天线子阵号
                str_zxzl.aerial_zznumber=ui->cB_elecDH_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_zxzl.aerial_mode = ui->cB_elecDH_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_zxzl.polarmand = ui->comboBox_DD1Z2_3->currentIndex();
                // 波束离轴角指向
                tmp_ushort = ui->lineEdit_DD1Z2_6->text().toInt();
                str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->lineEdit_DD1Z2_7->text().toInt();
                str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
                break;
            case 1:  // 指向扫描模式参数

                modeLen_1 = sizeof(str_zxsm);
                // 天线子阵号
                str_zxsm.aerial_zznumber=ui->cB_elecDH_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_zxsm.aerial_mode = ui->cB_elecDH_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_zxsm.polarmand = ui->comboBox_DD2Z2_3->currentIndex();
                // 指向驻留时间
                str_zxsm.zx_ontime = ui->lineEdit_DD2Z2_6->text().toInt();
                // 指向个数
                str_zxsm.pointsum = ui->lineEdit_DD2Z2_7->text().toInt();


                sum_cntnum=str_zxsm.pointsum;
                if(sum_cntnum>255)sum_cntnum=255;
                for (int i=0;i<sum_cntnum;i++) {
                    // 波束离轴角指向
                    tmp_ushort = ui->tableWidget_DD2_Z2_3->item(i,0)->text().toInt();
                    str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                    // 波束方位角指向
                    tmp_ushort = ui->tableWidget_DD2_Z2_3->item(i,1)->text().toInt();
                    str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
                }
                // 拷贝数据
                modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
                break;

            case 2:  // 区域凝视模式参数

                modeLen_1 = sizeof(str_qyns);
                // 天线子阵号
                str_qyns.aerial_zznumber=ui->cB_elecDH_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_qyns.aerial_mode = ui->cB_elecDH_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_qyns.polarmand = ui->comboBox_DD3Z2_3->currentIndex();
                // 目标经度
                tmp_uint = ui->lineEdit_DD3Z2_6->text().toDouble()*1000000;
                str_qyns.target_orb = qToBigEndian(tmp_uint);
                // 目标纬度
                tmp_uint = ui->lineEdit_DD3Z2_7->text().toDouble()*1000000;
                str_qyns.target_latitude = qToBigEndian(tmp_uint);
                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
                break;
            case 3:  // 区域扫描模式参数

                modeLen_1 = sizeof(str_qysm);
                // 天线子阵号
                str_qysm.aerial_zznumber=ui->cB_elecDH_txnumber_Z2->currentIndex();
                // 天线子阵控制模式
                str_qysm.aerial_mode = ui->cB_elecDH_contrlmode_Z2->currentIndex() + 1;
                // 极化方式
                str_qysm.polarmand = ui->comboBox_DD4Z2_3->currentIndex();
                // 区域驻留时间
                str_qysm.region_onntime = ui->lineEdit_DD4Z2_6->text().toInt();
                // 区域点个数
                tmp_ushort = ui->lineEdit_DD4Z2_7->text().toInt();
                str_qysm.region_sum = qToBigEndian(tmp_ushort);

                sum_cntnum=tmp_ushort;
                if(sum_cntnum>5)sum_cntnum=5;
                for (int i=0;i<sum_cntnum;i++) {
                    // 区域点经度
                    tmp_uint = ui->tableWidget_DD4_Z2_3->item(i,0)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                    // 区域点纬度
                    tmp_uint = ui->tableWidget_DD4_Z2_3->item(i,1)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
                }

                // 拷贝数据
                modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
                break;

            default:
                break;
            }

            modeLen_SUM += modeLen_1;
        };

        // 子阵3
        if (ui->checkBox_DH_TXbit2->isChecked()) {
            // 电子侦察任务--天线子阵参数变长部分
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));

            int modeLen_1 = 0;  // 当前子阵的总长
            switch (ui->cB_elecDH_contrlmode_Z3->currentIndex()) {
            case 0:  // 指向驻留模式参数

                modeLen_1 = sizeof(str_zxzl);

                // 天线子阵号
                str_zxzl.aerial_zznumber=ui->cB_elecDH_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_zxzl.aerial_mode = ui->cB_elecDH_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_zxzl.polarmand = ui->comboBox_DD1Z3_3->currentIndex();
                // 波束离轴角指向
                tmp_ushort = ui->lineEdit_DD1Z3_6->text().toInt();
                str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->lineEdit_DD1Z3_7->text().toInt();
                str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
                break;
            case 1:  // 指向扫描模式参数

                modeLen_1 = sizeof(str_zxsm);
                // 天线子阵号
                str_zxsm.aerial_zznumber=ui->cB_elecDH_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_zxsm.aerial_mode = ui->cB_elecDH_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_zxsm.polarmand = ui->comboBox_DD2Z3_3->currentIndex();
                // 指向驻留时间
                str_zxsm.zx_ontime = ui->lineEdit_DD2Z3_6->text().toInt();
                // 指向个数
                str_zxsm.pointsum = ui->lineEdit_DD2Z3_7->text().toInt();

                sum_cntnum=str_zxsm.pointsum;
                if(sum_cntnum>255)sum_cntnum=255;
                for (int i=0;i<sum_cntnum;i++) {
                    // 波束离轴角指向
                    tmp_ushort = ui->tableWidget_DD2_Z3_3->item(i,0)->text().toInt();
                    str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                    // 波束方位角指向
                    tmp_ushort = ui->tableWidget_DD2_Z3_3->item(i,1)->text().toInt();
                    str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
                }
                // 拷贝数据
                modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
                break;
            case 2:  // 区域凝视模式参数

                modeLen_1 = sizeof(str_qyns);
                // 天线子阵号
                str_qyns.aerial_zznumber=ui->cB_elecDH_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_qyns.aerial_mode = ui->cB_elecDH_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_qyns.polarmand = ui->comboBox_DD3Z3_3->currentIndex();
                // 目标经度
                tmp_uint = ui->lineEdit_DD3Z3_6->text().toDouble()*1000000;
                str_qyns.target_orb = qToBigEndian(tmp_uint);
                // 目标纬度
                tmp_uint = ui->lineEdit_DD3Z3_7->text().toDouble()*1000000;
                str_qyns.target_latitude = qToBigEndian(tmp_uint);
                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
                break;
            case 3:  // 区域扫描模式参数

                modeLen_1 = sizeof(str_qysm);
                // 天线子阵号
                str_qysm.aerial_zznumber=ui->cB_elecDH_txnumber_Z3->currentIndex();
                // 天线子阵控制模式
                str_qysm.aerial_mode = ui->cB_elecDH_contrlmode_Z3->currentIndex() + 1;
                // 极化方式
                str_qysm.polarmand = ui->comboBox_DD4Z3_3->currentIndex();
                // 区域驻留时间
                str_qysm.region_onntime = ui->lineEdit_DD4Z3_6->text().toInt();
                // 区域点个数
                tmp_ushort = ui->lineEdit_DD4Z3_7->text().toInt();
                str_qysm.region_sum = qToBigEndian(tmp_ushort);

                sum_cntnum=tmp_ushort;
                if(sum_cntnum>5)sum_cntnum=5;
                for (int i=0;i<sum_cntnum;i++) {
                    // 区域点经度
                    tmp_uint = ui->tableWidget_DD4_Z3_3->item(i,0)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                    // 区域点纬度
                    tmp_uint = ui->tableWidget_DD4_Z3_3->item(i,1)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
                }

                // 拷贝数据
                modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
                break;
            default:
                break;
            }

            modeLen_SUM += modeLen_1;

        };

        // 子阵4
        if (ui->checkBox_DH_TXbit3->isChecked()) {
            // 电子侦察任务--天线子阵参数变长部分
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));

            int modeLen_1 = 0;  // 当前子阵的总长
            switch (ui->cB_elecDH_contrlmode_Z4->currentIndex()) {
            case 0:  // 指向驻留模式参数

                modeLen_1 = sizeof(str_zxzl);
                // 天线子阵号
                str_zxzl.aerial_zznumber=ui->cB_elecDH_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_zxzl.aerial_mode = ui->cB_elecDH_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_zxzl.polarmand = ui->comboBox_DD1Z4_3->currentIndex();
                // 波束离轴角指向
                tmp_ushort = ui->lineEdit_DD1Z4_6->text().toInt();
                str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->lineEdit_DD1Z4_7->text().toInt();
                str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
                break;
            case 1:  // 指向扫描模式参数

                modeLen_1 = sizeof(str_zxsm);
                // 天线子阵号
                str_zxsm.aerial_zznumber=ui->cB_elecDH_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_zxsm.aerial_mode = ui->cB_elecDH_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_zxsm.polarmand = ui->comboBox_DD2Z4_3->currentIndex();
                // 指向驻留时间
                str_zxsm.zx_ontime = ui->lineEdit_DD2Z4_6->text().toInt();
                // 指向个数
                str_zxsm.pointsum = ui->lineEdit_DD2Z4_7->text().toInt();

                sum_cntnum=str_zxsm.pointsum;
                if(sum_cntnum>255)sum_cntnum=255;
                for (int i=0;i<sum_cntnum;i++) {
                    // 波束离轴角指向
                    tmp_ushort = ui->tableWidget_DD2_Z4_3->item(i,0)->text().toInt();
                    str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                    // 波束方位角指向
                    tmp_ushort = ui->tableWidget_DD2_Z4_3->item(i,1)->text().toInt();
                    str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
                }
                // 拷贝数据
                modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
                break;
            case 2:  // 区域凝视模式参数

                modeLen_1 = sizeof(str_qyns);
                // 天线子阵号
                str_qyns.aerial_zznumber=ui->cB_elecDH_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_qyns.aerial_mode = ui->cB_elecDH_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_qyns.polarmand = ui->comboBox_DD3Z4_3->currentIndex();
                // 目标经度
                tmp_uint = ui->lineEdit_DD3Z4_6->text().toDouble()*1000000;
                str_qyns.target_orb = qToBigEndian(tmp_uint);
                // 目标纬度
                tmp_uint = ui->lineEdit_DD3Z4_7->text().toDouble()*1000000;
                str_qyns.target_latitude = qToBigEndian(tmp_uint);
                // 拷贝数据
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
                break;
            case 3:  // 区域扫描模式参数

                modeLen_1 = sizeof(str_qysm);
                // 天线子阵号
                str_qysm.aerial_zznumber=ui->cB_elecDH_txnumber_Z4->currentIndex();
                // 天线子阵控制模式
                str_qysm.aerial_mode = ui->cB_elecDH_contrlmode_Z4->currentIndex() + 1;
                // 极化方式
                str_qysm.polarmand = ui->comboBox_DD4Z4_3->currentIndex();
                // 区域驻留时间
                str_qysm.region_onntime = ui->lineEdit_DD4Z4_6->text().toInt();
                // 区域点个数
                tmp_ushort = ui->lineEdit_DD4Z4_7->text().toInt();
                str_qysm.region_sum = qToBigEndian(tmp_ushort);

                sum_cntnum=tmp_ushort;
                if(sum_cntnum>5)sum_cntnum=5;
                for (int i=0;i<sum_cntnum;i++) {
                    // 区域点经度
                    tmp_uint = ui->tableWidget_DD4_Z4_3->item(i,0)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                    // 区域点纬度
                    tmp_uint = ui->tableWidget_DD4_Z4_3->item(i,1)->text().toDouble()*1000000;
                    str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
                }

                // 拷贝数据
                modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
                memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
                break;
            default:
                break;
            }

            modeLen_SUM += modeLen_1;
        };
    }
    strlen += modeLen_SUM;

    uchar *buff_elec_aerial = new uchar[strlen + 1];
    memcpy(buff_elec_aerial, &str_byna, sizeof(Elec_BYnavigation));
    memcpy(buff_elec_aerial + sizeof(Elec_BYnavigation), buff_mode_all4, modeLen_SUM);

    return buff_elec_aerial;



}


//类5G任务基本信息
uchar *sub1553_Overheadtask::set_5G_kind(int &strlen){

    Kind5G_Str str;
    memset(&str, 0, sizeof(str));
    strlen = sizeof(str);  // 需要写入的侦察任务总长度
    //数据通道流向
    ushort bit15_12,bit11_8,bit7_4,bit3_0;
    bit15_12=ui->comboBox_D6_bit15_12->currentIndex()+9;
    if(ui->comboBox_D6_bit15_12->currentIndex()==4)bit15_12=15;

    bit11_8=ui->comboBox_D6_bit11_8->currentIndex()+9;
    if(ui->comboBox_D6_bit11_8->currentIndex()==4)bit11_8=15;

    bit7_4=ui->comboBox_D6_bit7_4->currentIndex()+9;
    if(ui->comboBox_D6_bit7_4->currentIndex()==4)bit7_4=15;

    bit3_0=ui->comboBox_D6_bit3_0->currentIndex()+9;
    if(ui->comboBox_D6_bit3_0->currentIndex()==4)bit3_0=15;

    str.datastrim=(bit15_12<<12)+(bit11_8<<8)+(bit7_4<<4)+bit3_0;
    str.datastrim=qToBigEndian(str.datastrim);

    // 本振选择方式
    str.bz_choose = ui->comboBox_D4_2->currentIndex();
    // 1本振使用信息
    str.bz1_mess = ui->comboBox_D5_2->currentIndex();
    // 天线与通道对应模式
    str.aerial_ad = ui->comboBox_D6_2->currentIndex() + 1;
    // 射频通道号
    str.sp_ad=ui->lineEdit_L5_D7->text().toInt();
    // 射频通道参数设置
    uchar tmp_char=0;
    if(ui->comboBox_C3->currentIndex()==0)//L频段
    {
        tmp_char=ui->checkBox_GSM0->isChecked()
                +(ui->checkBox_amper1_1->isChecked()<<1)
                +(ui->checkBox_amper2_1->isChecked()<<2)
                +(ui->checkBox_amper3_1->isChecked()<<3);



    }
    else//SXKU
    {
        tmp_char=ui->checkBox_sxkuAmper_1->isChecked()?1:0;
        tmp_char+=(ui->comboBox_reduceTD_1->currentIndex()<<1);
    }
    str.sp_addata=tmp_char;
    // 射频通道接收衰减
    str.sp_adlow=ui->lineEdit_sptd_jssj_1->text().toInt();
    // 射频通道发射衰减
    str.sp_fslow=ui->lineEdit_sptd_fssj_1->text().toInt();
    // 天线子阵参数
    str.aerial_patameter = ui->checkBox_D10bit0_2->isChecked() +
            (ui->checkBox_D10bit1_2->isChecked() << 1) +
            (ui->checkBox_D10bit2_2->isChecked() << 2) +
            (ui->checkBox_D10bit3_2->isChecked() << 3) +
            (ui->comboBox_D10b5->currentIndex()<<5)+(ui->comboBox_D10b6->currentIndex()<<6);


    int param_num=0;//计算子阵个数
    if(ui->checkBox_D10bit0_2->isChecked())param_num++;
    if(ui->checkBox_D10bit1_2->isChecked())param_num++;
    if(ui->checkBox_D10bit2_2->isChecked())param_num++;
    if(ui->checkBox_D10bit3_2->isChecked())param_num++;
    // 天线控制间隔时间
    str.aerial_time =ui->lineEdit_D11_2->text().toUInt();
    // 天线指向算法数据源
    str.aerial_data =ui->comboBox_D12_3->currentIndex();
    //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    str.aerial_low=ui->lineEdit_D11_5sj->text().toUInt()+(ui->comboBox_D11b7_6->currentIndex()<<6);
    //开关矩阵选择
    str.switch_Choose=ui->lineEdit_D11_5kgjz->text().toUInt();

    // 天线子阵号(1-4个循环个数,按照天线子阵参数确定)。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。
    uchar *buff_mode_all4 =new uchar[2000];  // 不定总长，存储所以子阵数据（暂时开辟2k）
    memset(buff_mode_all4, 0, 2000);
    int modeLen_SUM=0;

    aerial_ZCmode1_zxzl str_zxzl;
    aerial_ZCmode2_zxsm str_zxsm;
    aerial_ZCmode3_qyns str_qyns;
    aerial_ZCmode4_qysm str_qysm;

    ushort tmp_ushort=0;
    uint tmp_uint=0;
    // 子阵1
    if (ui->checkBox_D10bit0_2->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_L5_zz1_2->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_L5_zz1_1->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_L5_zz1_2->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_L5G_zz1_zxzl_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_L5G_zz1_zxzl_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_L5G_zz1_zxzl_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_L5_zz1_1->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_L5_zz1_2->currentIndex() + 1;

            // 极化方式
            str_qyns.polarmand = ui->comboBox_L5G_zz1_qyns_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_L5G_zz1_qyns_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_L5G_zz1_qyns_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;
    };


    // 子阵2
    if (ui->checkBox_D10bit1_2->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_L5_zz2_2->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_L5_zz2_1->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_L5_zz2_2->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_L5G_zz2_zxzl_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_L5G_zz2_zxzl_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_L5G_zz2_zxzl_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_L5_zz2_1->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_L5_zz2_2->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_L5G_zz2_qyns_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_L5G_zz2_qyns_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_L5G_zz2_qyns_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;

        default:
            break;
        }

        modeLen_SUM += modeLen_1;
    };
    // 子阵3
    if (ui->checkBox_D10bit2_2->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_L5_zz3_2->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);

            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_L5_zz3_1->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_L5_zz3_2->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_L5G_zz3_zxzl_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_L5G_zz3_zxzl_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_L5G_zz3_zxzl_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_L5_zz3_1->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_L5_zz3_2->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_L5G_zz3_qyns_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_L5G_zz3_qyns_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_L5G_zz3_qyns_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;
        ;
    };
    // 子阵4
    if (ui->checkBox_D10bit3_2->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_L5_zz4_2->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_L5_zz4_1->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_L5_zz4_2->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_L5G_zz4_zxzl_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_L5G_zz4_zxzl_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_L5G_zz4_zxzl_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_L5_zz4_1->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_L5_zz4_2->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_L5G_zz4_qyns_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_L5G_zz4_qyns_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_L5G_zz4_qyns_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;
    };



    strlen += modeLen_SUM;

    uchar *buff_elec_aerial = new uchar[strlen + 1];
    memcpy(buff_elec_aerial, &str, sizeof(str));
    memcpy(buff_elec_aerial + sizeof(str), buff_mode_all4, modeLen_SUM);

    return buff_elec_aerial;
}
//J链任务基本信息
uchar *sub1553_Overheadtask::set_J_chain(int &strlen)
{
    J_chainSTR str;
    memset(&str, 0, sizeof(str));
    strlen = sizeof(str);  // 需要写入的侦察任务总长度

    //数据通道流向
    ushort bit15_12,bit11_8,bit7_4,bit3_0;
    bit15_12=ui->comboBox_J_bit15_13->currentIndex()+8;
    if(ui->comboBox_J_bit15_13->currentIndex()==0)bit15_12=0;
    if(ui->comboBox_J_bit15_13->currentIndex()==5)bit15_12=15;

    bit11_8=ui->comboBox_J_bit11_9->currentIndex()+8;
    if(ui->comboBox_J_bit11_9->currentIndex()==0)bit11_8=0;
    if(ui->comboBox_J_bit11_9->currentIndex()==5)bit11_8=15;

    bit7_4=ui->comboBox_J_bit7_5->currentIndex()+8;
    if(ui->comboBox_J_bit7_5->currentIndex()==0)bit7_4=0;
    if(ui->comboBox_J_bit7_5->currentIndex()==5)bit7_4=15;

    bit3_0=ui->comboBox_J_bit3_1->currentIndex()+8;
    if(ui->comboBox_J_bit3_1->currentIndex()==0)bit3_0=0;
    if(ui->comboBox_J_bit3_1->currentIndex()==5)bit3_0=15;

    str.datastrim=(bit15_12<<12)+(bit11_8<<8)+(bit7_4<<4)+bit3_0;
    str.datastrim=qToBigEndian(str.datastrim);

    // 天线与通道对应模式
    str.txytddyms = ui->comboBox_J_1->currentIndex() + 1;
    //射频通道号
    str.sp_ad = ui->lineEdit_J_4->text().toInt();
    // 射频通道参数设置
    str.sp_addata2=ui->checkBox_J_4z1_b0->isChecked()+(ui->checkBox_J_4z1_b1->isChecked()<<1)
            +(ui->checkBox_J_4z1_b2->isChecked()<<2)+(ui->checkBox_J_4z1_b3->isChecked()<<3);

    // 射频通道接收衰减
    str.sp_recvlow2=ui->lineEdit_J_5_z1->text().toInt();


    // 射频通道发射衰减
    str.sp_sendlow=ui->lineEdit_J_6_z1->text().toInt();

    // 天线子阵参数+天线使用方式
    str.aerial_patameter = ui->checkBox_J_7b0->isChecked() +(ui->checkBox_J_7b1->isChecked() << 1)
            +(ui->checkBox_J_7b2->isChecked() << 2) +(ui->checkBox_J_7b3->isChecked() << 3)
            +(ui->comboBox_J_7b5_6->currentIndex()<<5);


    int param_num=0;//计算子阵个数
    if(ui->checkBox_J_7b0->isChecked())param_num++;
    if(ui->checkBox_J_7b0->isChecked())param_num++;
    if(ui->checkBox_J_7b0->isChecked())param_num++;
    if(ui->checkBox_J_7b0->isChecked())param_num++;

    // 天线控制间隔时间
    str.aerial_time =ui->lineEdit_J_8->text().toUInt();
    // 天线指向算法数据源
    str.aerial_data =ui->comboBox_J_9->currentIndex();
    //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    str.aerial_low=ui->lineEdit_J_10b5_0->text().toUInt()+(ui->comboBox_J_10b7_6->currentIndex()<<6);

    // 天线子阵号(1-4个循环个数,按照天线子阵参数确定)。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。
    uchar *buff_mode_all4 =new uchar[2000];  // 不定总长，存储所以子阵数据（暂时开辟2k）
    memset(buff_mode_all4, 0, 2000);
    int modeLen_SUM=0;
    J_TxZZCS tzzp[param_num];
    if(ui->checkBox_J_7b0->isChecked())
    {
        memset(&tzzp[0],0,sizeof (J_TxZZCS));
        tzzp[0].TzzZh=ui->comboBox_J_zz1_1->currentIndex()+1;
        tzzp[0].TzzctrlMode=ui->comboBox_J_zz1_2->currentIndex()+1;
        tzzp[0].area_X=qToBigEndian(ui->lineEdit_J_zz1_3->text().toInt());
        tzzp[0].area_Y=qToBigEndian(ui->lineEdit__J_zz1_4->text().toInt());
        memcpy(buff_mode_all4 + modeLen_SUM, &tzzp[0], sizeof (J_TxZZCS));
        modeLen_SUM+=sizeof (J_TxZZCS);
    }
    if(ui->checkBox_J_7b1->isChecked())
    {
        memset(&tzzp[1],0,sizeof (J_TxZZCS));
        tzzp[1].TzzZh=ui->comboBox_J_zz2_1->currentIndex()+1;
        tzzp[1].TzzctrlMode=ui->comboBox_J_zz2_2->currentIndex()+1;
        tzzp[1].area_X=qToBigEndian(ui->lineEdit_J_zz2_3->text().toInt());
        tzzp[1].area_Y=qToBigEndian(ui->lineEdit_J_zz2_4->text().toInt());
        memcpy(buff_mode_all4 + modeLen_SUM, &tzzp[1], sizeof (J_TxZZCS));
        modeLen_SUM+=sizeof (J_TxZZCS);
    }
    if(ui->checkBox_J_7b2->isChecked())
    {
        memset(&tzzp[2],0,sizeof (J_TxZZCS));
        tzzp[2].TzzZh=ui->comboBox_J_zz3_1->currentIndex()+1;
        tzzp[2].TzzctrlMode=ui->comboBox_J_zz3_2->currentIndex()+1;
        tzzp[2].area_X=qToBigEndian(ui->lineEdit_J_zz3_3->text().toInt());
        tzzp[2].area_Y=qToBigEndian(ui->lineEdit_J_zz3_4->text().toInt());
        memcpy(buff_mode_all4 + modeLen_SUM, &tzzp[2], sizeof (J_TxZZCS));
        modeLen_SUM+=sizeof (J_TxZZCS);
    }
    if(ui->checkBox_J_7b3->isChecked())
    {
        memset(&tzzp[3],0,sizeof (J_TxZZCS));
        tzzp[3].TzzZh=ui->comboBox_J_zz4_1->currentIndex()+1;
        tzzp[3].TzzctrlMode=ui->comboBox_J_zz4_2->currentIndex()+1;
        int a=ui->lineEdit_J_zz4_3->text().toInt();
        tzzp[3].area_X=qToBigEndian(a);
        tzzp[3].area_Y=qToBigEndian(ui->lineEdit_J_zz4_4->text().toInt());
        memcpy(buff_mode_all4 + modeLen_SUM, &tzzp[3], sizeof (J_TxZZCS));
        modeLen_SUM+=sizeof (J_TxZZCS);
    }

    strlen += modeLen_SUM;

    uchar *buff_ = new uchar[strlen + 1];
    memcpy(buff_, &str, sizeof(str));
    memcpy(buff_ + sizeof(str), buff_mode_all4, modeLen_SUM);

    return buff_;
}
//扩展功能
void sub1553_Overheadtask::tz_fun()
{
    uint tmp_uint = 0;
    ushort tmp_ushort = 0;
    //(任务N内容引导头)
    TaskContent_2 strTaskContent;
    memset(&strTaskContent, 0, sizeof(TaskContent_2));

    // 任务流水号
    tmp_ushort = ui->lineEdit_A2->text().toInt();
    strTaskContent.taskflowid = qToBigEndian(tmp_ushort);
    // 主任务id
    tmp_ushort = ui->lineEdit_A3->text().toInt();
    strTaskContent.main_id = qToBigEndian(tmp_ushort);
    // 子任务id
    strTaskContent.sub_id = ui->lineEdit_A4->text().toInt();
    // 卫星代码
    tmp_ushort = toHex_ushort(ui->lineEdit_A5->text());
    strTaskContent.start_code = tmp_ushort;
    // 主从标志
    strTaskContent.mainsub_choose = ui->comboBox_A6->currentIndex();
    if(ui->comboBox_A6->currentIndex()==2)strTaskContent.mainsub_choose=0xFF;
    // 协同卫星数量
    strTaskContent.start_sum = 0;
    // 功能模式
    strTaskContent.fun_mode = ui->cB_function_mode->currentIndex() + 1;
    // 工作内核
    strTaskContent.work_mode = ui->comboBox_A9->currentIndex() + 1;
    // 任务类型
    strTaskContent.tasktype = ui->comboBox_A10->currentIndex() + 1;
    // 任务个数
    strTaskContent.tasksum = ui->lineEdit_A11->text().toInt();
    // 模板标志
    strTaskContent.mb_mask = ui->comboBox_A12_->currentIndex() + 1;
    // 任务开始时刻
    tmp_uint = ui->lineEdit_A13->text().toUInt();
    strTaskContent.task_starttime = qToBigEndian(tmp_uint);
    // 任务持续时长
    tmp_uint = ui->lineEdit_A14->text().toUInt();
    strTaskContent.task_holdtime = qToBigEndian(tmp_uint);


    //(任务基本信息)
    // 高算力平台选择
    strTaskContent.Gener_str.gsl_choose = ui->comboBox_C1_2->currentIndex();
    // 高算力主从选择
    strTaskContent.Gener_str.gsl_mainsub = ui->comboBox_C2_2->currentIndex();
    // 频段选择
    strTaskContent.Gener_str.pd_choose = ui->comboBox_C3_2->currentIndex();
    // 中频切换开关状态
    strTaskContent.Gener_str.zp_change = ui->comboBox_C11_2->currentIndex();
    // 数传标志
    strTaskContent.Gener_str.data_choose = (ui->comboBox_C4_3->currentIndex()<<4)+ui->comboBox_C4_2->currentIndex();
    // 数传传输速率
    tmp_ushort = ui->lineEdit_C5_2->text().toInt();
    strTaskContent.Gener_str.data_speed = qToBigEndian(tmp_ushort);


    QString S_sorftnum;
    QByteArray hex_data;
    // 收发FPGA_1
    S_sorftnum = ui->lineEdit_C12_2->text();
    strTaskContent.Gener_str.sf_fpga1 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.sf_fpga1 = 0xffff;
    // 收发FPGA_2
    S_sorftnum = ui->lineEdit_C13_2->text();
    strTaskContent.Gener_str.sf_fpga2 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.sf_fpga2 = 0xffff;
    // 数据模块1FPGA_1
    S_sorftnum = ui->lineEdit_C14_2->text();
    strTaskContent.Gener_str.dataA_fpga1 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA_fpga1 = 0xffff;
    // 数据模块2FPGA_2
    S_sorftnum = ui->lineEdit_C15_2->text();
    strTaskContent.Gener_str.dataA_fpga2 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA_fpga2 = 0xffff;
    // 数据模块1DSP
    S_sorftnum = ui->lineEdit_C16_2->text();
    strTaskContent.Gener_str.dataA_dsp = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA_dsp = 0xffff;
    // 数据模块2FPGA_1
    S_sorftnum = ui->lineEdit_C17_2->text();
    strTaskContent.Gener_str.dataB_fpga1 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB_fpga1 = 0xffff;
    // 数据模块2FPGA_2
    S_sorftnum = ui->lineEdit_C18_2->text();
    strTaskContent.Gener_str.dataB_fpga2 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB_fpga2 = 0xffff;
    // 数据模块2DSP
    S_sorftnum = ui->lineEdit_C19_2->text();
    strTaskContent.Gener_str.dataB_dsp = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB_dsp = 0xffff;


    // （高算力2）收发FPGA_1
    S_sorftnum = ui->lineEdit_C19_3->text();
    strTaskContent.Gener_str.sf2_fpga1 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.sf2_fpga1 = 0xffff;
    // （高算力2）收发FPGA_2
    S_sorftnum = ui->lineEdit_C19_4->text();
    strTaskContent.Gener_str.sf2_fpga2 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.sf2_fpga2 = 0xffff;
    // （高算力2）数据模块1FPGA_1
    S_sorftnum = ui->lineEdit_C19_5->text();
    strTaskContent.Gener_str.dataA2_fpga1 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA2_fpga1 = 0xffff;
    // （高算力2）数据模块2FPGA_2
    S_sorftnum = ui->lineEdit_C19_6->text();
    strTaskContent.Gener_str.dataA2_fpga2 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA2_fpga2 = 0xffff;
    // （高算力2）数据模块1DSP
    S_sorftnum = ui->lineEdit_C19_7->text();
    strTaskContent.Gener_str.dataA2_dsp = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA2_dsp = 0xffff;
    // （高算力2）数据模块2FPGA_1
    S_sorftnum = ui->lineEdit_C19_8->text();
    strTaskContent.Gener_str.dataB2_fpga1 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB2_fpga1 = 0xffff;
    // （高算力2）数据模块2FPGA_2
    S_sorftnum = ui->lineEdit_C19_9->text();
    strTaskContent.Gener_str.dataB2_fpga2 = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB2_fpga2 = 0xffff;
    // （高算力2）数据模块2DSP
    S_sorftnum = ui->lineEdit_C19_10->text();
    strTaskContent.Gener_str.dataB2_dsp = toHex_ushort(S_sorftnum);
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB2_dsp = 0xffff;

    //(任务基本信息变长部分)
    uchar *p_str = NULL;
    int strLen = 0;
    bool f_modedata=false;//是否需要具体任务模式参数
    if(ui->lineEdit_A11->text().toUInt()==0)f_modedata=false;//任务个数为0时，不获取任务模式数据
    switch (ui->cB_function_mode->currentIndex())  // 功能模式
    {
    case 9:  // 电子侦察任务
        p_str = tz_fun_mess(strLen);
        break;
    default:

        break;
    }

    // 整个任务基本信息长度
    int gener_len=sizeof (strTaskContent.Gener_str);
    tmp_uint = gener_len + strLen;
    strTaskContent.Gener_str.task_massageLen = qToBigEndian(tmp_uint);  // 固定头+变长

    if(f_modedata){

    }
    else {//不需要第二个界面
        QStringList sarlist;
        uchar *p_str2 = nullptr;
        int strLen2 = 0;
        if(ui->cB_function_mode->currentIndex()==9)//拓展功能
        {
            if(ui->tB_widget_SARFileList_2->rowCount()==0)
            {
                QMessageBox::warning(this,tr("错误"),tr("未选择拓展功能参数内容文件"));
                return;
            }
            for (int n=0;n<ui->tB_widget_SARFileList_2->rowCount();n++) {
                sarlist.append(ui->tB_widget_SARFileList_2->item(n, 1)->text());
            }
            p_str2 = mode_SAR(sarlist,strLen2);
        }

        // 任务长度（任务长度到任务模式参数字节总长）
        uint tmpsumLen =sizeof(TaskContent_2) + strLen+strLen2;
        strTaskContent.taskSumlen = qToBigEndian(tmpsumLen);

        // 内容引导头
        uchar *Buff_1 = new uchar[sizeof(TaskContent_2) + strLen];
        memcpy(Buff_1, &strTaskContent, sizeof(TaskContent_2));
        memcpy(Buff_1 + sizeof(TaskContent_2), p_str, strLen);
        //////////////////////////////////////////////////////////////////
        // 生成到界面
        //  内容号
        int cnt = model_mlist->rowCount();
        model_mlist->setItem(cnt, 0,new QStandardItem(ui->lineEdit_TaskNumber->text()));
        // 引导长度
        model_mlist->setItem(cnt, 1, new QStandardItem(QString::number(sizeof(TaskContent_2) + strLen)));
        // 内容引导头
        QString str = "";
        QString tmp_byte;
        for (uint readLen = 0; readLen < sizeof(TaskContent_2) + strLen; readLen++) {
            tmp_byte = QString().asprintf("%02x ", Buff_1[readLen]);
            str.append(tmp_byte);
        }
        model_mlist->setItem(cnt, 2, new QStandardItem(str));
        // 名称
        model_mlist->setItem(cnt, 3, new QStandardItem(ui->cB_function_mode->currentText()));
        // 长度
        model_mlist->setItem(cnt, 4,new QStandardItem(QString::number(strLen2)));
        //内容参数类型
        str = "";
        for (int readLen = 0; readLen < strLen2;readLen++) {
            tmp_byte = QString().asprintf("%02x ", p_str2[readLen]);
            str.append(tmp_byte);
        }
        model_mlist->setItem(cnt, 5, new QStandardItem(str));


        delete[] p_str;
        delete[] Buff_1;
        // delete[] Buff_2;
    }


    return;
}
//扩展功能基本信息
uchar * sub1553_Overheadtask::tz_fun_mess(int &strlen)
{
    uint tmp_uint = 0;
    ushort tmp_ushort = 0;
    Tz_Mess str;
    memset(&str, 0, sizeof(Tz_Mess));
    strlen = sizeof(Tz_Mess);  // 需要写入的侦察任务总长度
    //数据通道流向
    ushort bit15_12,bit11_8,bit7_4,bit3_0;
    bit15_12=ui->comboBox_D1_bit15_13->currentIndex();
    if(ui->comboBox_D1_bit15_13->currentIndex()==13)bit15_12=15;

    bit11_8=ui->comboBox_D1_bit11_9->currentIndex();
    if(ui->comboBox_D1_bit11_9->currentIndex()==13)bit11_8=15;

    bit7_4=ui->comboBox_D1_bit7_5->currentIndex();
    if(ui->comboBox_D1_bit7_5->currentIndex()==13)bit7_4=15;

    bit3_0=ui->comboBox_D1_bit3_1->currentIndex();
    if(ui->comboBox_D1_bit3_1->currentIndex()==13)bit3_0=15;

    str.datastrim=(bit15_12<<12)+(bit11_8<<8)+(bit7_4<<4)+bit3_0;
    str.datastrim=qToBigEndian(str.datastrim);
    // 天线与通道对应模式
    str.aerial_ad = ui->comboBox_D6_3->currentIndex() + 1;


    // 内校正输出通道
    str.in_ad = ui->comboBox_tz8->currentIndex();
    // DA输出幅度衰减值
    str.DA_out = ui->lineEdit_tz1->text().toInt();
    // 本振选择方式
    str.bz_choose = ui->comboBox_tz2->currentIndex();


    // 1本振使用信息
    str.bz1_mess[0]=ui->comboBox_2D5_b0_2->currentIndex();
    str.bz1_mess[1]=ui->comboBox_2D5_b1_2->currentIndex();
    if(ui->comboBox_tz2->currentIndex()==1)//共本振
    {
        str.bz1_mess[1]=0xFF;
    }

    // 射频通道号
    str.sp_ad[0]=ui->comboBox_D7_3->currentIndex();
    str.sp_ad[1]=ui->comboBox_D7_5->currentIndex();
    str.sp_ad[2]=ui->comboBox_D7_7->currentIndex();
    str.sp_ad[3]=ui->comboBox_D7_6->currentIndex();
    if(ui->comboBox_D7_3->currentIndex()==0)
    {
        str.sp_ad[1]=0xFF;
        str.sp_ad[2]=0xFF;
        str.sp_ad[3]=0xFF;
    }
    // 放大器使能/射频衰减
    if (ui->comboBox_C3_2->currentIndex() == 0) {//L频段
        str.fd_sp[0] = ui->checkBox_D8bit0_2->isChecked() +(ui->checkBox_D8bit1_2->isChecked() << 1)
                +(ui->checkBox_D8bit2_2->isChecked() << 2) +((ui->checkBox_D8bit3_2->isChecked() << 3));
        str.fd_sp[1]=str.fd_sp[0];
        str.fd_sp[2]=str.fd_sp[0];
        str.fd_sp[3]=str.fd_sp[0];
    } else {//sxuk频段
        //共本振
        str.fd_sp[0] = ui->checkBox_D8bit1_2->isChecked() +(ui->comboBox_D8bit1_3->currentIndex() << 1);
        str.fd_sp[1]=str.fd_sp[0];
        str.fd_sp[2]=str.fd_sp[0];
        str.fd_sp[3]=str.fd_sp[0];
    }
    // 射频通道发射衰减
    str.sp_adfs[0] = ui->lineEdit_tz4->text().toInt();
    str.sp_adfs[1] = ui->lineEdit_tz4->text().toInt();
    str.sp_adfs[2] = ui->lineEdit_tz4->text().toInt();
    str.sp_adfs[3] = ui->lineEdit_tz4->text().toInt();
    // 射频通道接收衰减
    str.sp_adlow[0] = ui->lineEdit_tz3->text().toInt();
    str.sp_adlow[1] = ui->lineEdit_tz3->text().toInt();
    str.sp_adlow[2] = ui->lineEdit_tz3->text().toInt();
    str.sp_adlow[3] = ui->lineEdit_tz3->text().toInt();
    // 保留
    // 天线工作模式
    str.tx_mode = ui->comboBox_tz3->currentIndex()+1;

    // 天线子阵参数
    str.aerial_patameter = ui->checkBox_D10bit0_3->isChecked() +
            (ui->checkBox_D10bit1_3->isChecked() << 1) +
            (ui->checkBox_D10bit2_3->isChecked() << 2) +
            (ui->checkBox_D10bit3_3->isChecked() << 3);
    if(ui->comboBox_C3_2->currentIndex() == 0)//L频段
    {
         str.aerial_patameter=(ui->comboBox_D10bit5_2->currentIndex() << 5);
    }
    else//sxuk频段
    {
        str.aerial_patameter=(ui->comboBox_D10bit5_2->currentIndex() << 5) +
                               (ui->comboBox_D10bit6_2->currentIndex() << 6);
    }


    // 天线控制间隔时间
    str.aerial_time = ui->lineEdit_D11_3->text().toInt();
    // 天线指向算法数据源
    str.aerial_data=ui->comboBox_D12_2->currentIndex();
    //天线接收衰减
    str.aerial_low=ui->comboBox_D13b7_7->currentIndex();

    //射频发射衰减（L频段）
    str.sp_fsd=ui->lineEdit_tz4->text().toInt();
    //开关矩阵选择（L频段）
    if(ui->comboBox_tz4->currentIndex()==0)str.kgjzxz=0x10;
    if(ui->comboBox_tz4->currentIndex()==1)str.kgjzxz=0x11;
    if(ui->comboBox_tz4->currentIndex()==2)str.kgjzxz=0x12;
    if(ui->comboBox_tz4->currentIndex()==3)str.kgjzxz=0x14;
    if(ui->comboBox_tz4->currentIndex()==4)str.kgjzxz=0xff;
    //接收相位/幅度加权码（SXKu频段）
    str.rec_xw=(ui->lineEdit_tz5->text().toInt()<<4)+ui->lineEdit_tz6->text().toInt();
    //组件遥测数据类型（SXKu频段）
    if(ui->comboBox_tz7->currentIndex()==0)str.con_yc=0x1F;
    if(ui->comboBox_tz7->currentIndex()==1)str.con_yc=0xD0;

    // 天线子阵号(1-4个循环个数,按照天线子阵参数确定)。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。
    aerial_ZCmode1_zxzl str_zxzl;
    aerial_ZCmode2_zxsm str_zxsm;
    aerial_ZCmode3_qyns str_qyns;
    aerial_ZCmode4_qysm str_qysm;


    uchar *buff_mode_all4 =new uchar[5000];  // 不定总长，存储所以子阵数据（暂时开辟2k）
    memset(buff_mode_all4, 0, 5000);
    int modeLen_SUM = 0;  // 4个子阵的变长总长总长
    int sum_cntnum=0;//模式内的循环体计数

    // 子阵1

    // 电子侦察任务--天线子阵参数变长部分
    memset(&str_zxzl, 0, sizeof(str_zxzl));
    memset(&str_zxsm, 0, sizeof(str_zxsm));
    memset(&str_qyns, 0, sizeof(str_qyns));
    memset(&str_qysm, 0, sizeof(str_qysm));

    int modeLen_1 = 0;  // 当前子阵的总长
    // 子阵1
    if (ui->checkBox_D10bit0_3->isChecked()) {
        switch (ui->cB_elecZC_contrlmode->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_DD1_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_DD1_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_DD1_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 1:  // 指向扫描模式参数

            modeLen_1 = sizeof(str_zxsm);
            // 天线子阵号
            str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;
            // 极化方式
            str_zxsm.polarmand = ui->comboBox_DD2_1->currentIndex();
            // 指向驻留时间
            str_zxsm.zx_ontime = ui->lineEdit_DD2_5->text().toInt();
            // 指向个数
            str_zxsm.pointsum = ui->lineEdit_DD2_2->text().toInt();
            if(ui->lineEdit_DD2_2->text().toInt()>255)str_zxsm.pointsum=255;

            sum_cntnum=str_zxsm.pointsum;
            if(sum_cntnum>255)sum_cntnum=255;
            for (int i=0;i<sum_cntnum;i++) {
                // 波束离轴角指向
                tmp_ushort = ui->tableWidget_DD2->item(i,0)->text().toInt();
                str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->tableWidget_DD2->item(i,1)->text().toInt();
                str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
            }
            // 拷贝数据
            modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;

            // 极化方式
            str_qyns.polarmand = ui->comboBox_DD3_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_DD3_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_DD3_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        case 3:  // 区域扫描模式参数

            modeLen_1 = sizeof(str_qysm);
            // 天线子阵号
            str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber->currentIndex();
            // 天线子阵控制模式
            str_qysm.aerial_mode = ui->cB_elecZC_contrlmode->currentIndex() + 1;
            // 极化方式
            str_qysm.polarmand = ui->comboBox_DD4_1->currentIndex();
            // 区域驻留时间
            str_qysm.region_onntime = ui->lineEdit_DD4_5->text().toInt();
            // 区域点个数
            tmp_ushort = ui->lineEdit_DD4_2->text().toInt();
            str_qysm.region_sum = qToBigEndian(tmp_ushort);

            sum_cntnum=tmp_ushort;
            if(sum_cntnum>5)sum_cntnum=5;
            for (int i=0;i<sum_cntnum;i++) {
                // 区域点经度
                tmp_uint = ui->tableWidget_DD4->item(i,0)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                // 区域点纬度
                tmp_uint = ui->tableWidget_DD4->item(i,1)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
            }

            // 拷贝数据
            modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;}
    // 子阵2
    if (ui->checkBox_D10bit1_3->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_elecZC_contrlmode_Z2->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_DD1Z2_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_DD1Z2_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_DD1Z2_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 1:  // 指向扫描模式参数

            modeLen_1 = sizeof(str_zxsm);
            // 天线子阵号
            str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
            // 天线子阵控制模式
            str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
            // 极化方式
            str_zxsm.polarmand = ui->comboBox_DD2Z2_1->currentIndex();
            // 指向驻留时间
            str_zxsm.zx_ontime = ui->lineEdit_DD2Z2_2->text().toInt();
            // 指向个数
            str_zxsm.pointsum = ui->lineEdit_DD2Z2_3->text().toInt();
            if(ui->lineEdit_DD2Z2_3->text().toInt()>255)str_zxsm.pointsum=255;

            sum_cntnum=str_zxsm.pointsum;
            if(sum_cntnum>255)sum_cntnum=255;
            for (int i=0;i<sum_cntnum;i++) {
                // 波束离轴角指向
                tmp_ushort = ui->tableWidget_DD2_Z2->item(i,0)->text().toInt();
                str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->tableWidget_DD2_Z2->item(i,1)->text().toInt();
                str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
            }
            // 拷贝数据
            modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
            break;

        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_DD3Z2_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_DD3Z2_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_DD3Z2_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        case 3:  // 区域扫描模式参数

            modeLen_1 = sizeof(str_qysm);
            // 天线子阵号
            str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber_Z2->currentIndex();
            // 天线子阵控制模式
            str_qysm.aerial_mode = ui->cB_elecZC_contrlmode_Z2->currentIndex() + 1;
            // 极化方式
            str_qysm.polarmand = ui->comboBox_DD4Z2_1->currentIndex();
            // 区域驻留时间
            str_qysm.region_onntime = ui->lineEdit_DD4Z2_2->text().toInt();
            // 区域点个数
            tmp_ushort = ui->lineEdit_DD4Z2_3->text().toInt();
            str_qysm.region_sum = qToBigEndian(tmp_ushort);

            sum_cntnum=tmp_ushort;
            if(sum_cntnum>5)sum_cntnum=5;
            for (int i=0;i<sum_cntnum;i++) {
                // 区域点经度
                tmp_uint = ui->tableWidget_DD4_Z2->item(i,0)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                // 区域点纬度
                tmp_uint = ui->tableWidget_DD4_Z2->item(i,1)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
            }

            // 拷贝数据
            modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
            break;

        default:
            break;
        }

        modeLen_SUM += modeLen_1;
    };
    // 子阵3
    if (ui->checkBox_D10bit2_3->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_elecZC_contrlmode_Z3->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);

            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_DD1Z3_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_DD1Z3_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_DD1Z3_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 1:  // 指向扫描模式参数

            modeLen_1 = sizeof(str_zxsm);
            // 天线子阵号
            str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
            // 天线子阵控制模式
            str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
            // 极化方式
            str_zxsm.polarmand = ui->comboBox_DD2Z3_1->currentIndex();
            // 指向驻留时间
            str_zxsm.zx_ontime = ui->lineEdit_DD2Z3_2->text().toInt();
            // 指向个数
            str_zxsm.pointsum = ui->lineEdit_DD2Z3_3->text().toInt();
            if(ui->lineEdit_DD2Z3_3->text().toInt()>255)str_zxsm.pointsum=255;


            sum_cntnum=str_zxsm.pointsum;
            if(sum_cntnum>255)sum_cntnum=255;
            for (int i=0;i<sum_cntnum;i++) {
                // 波束离轴角指向
                tmp_ushort = ui->tableWidget_DD2_Z3->item(i,0)->text().toInt();
                str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->tableWidget_DD2_Z3->item(i,1)->text().toInt();
                str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
            }
            // 拷贝数据
            modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_DD3Z3_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_DD3Z3_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_DD3Z3_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        case 3:  // 区域扫描模式参数

            modeLen_1 = sizeof(str_qysm);
            // 天线子阵号
            str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber_Z3->currentIndex();
            // 天线子阵控制模式
            str_qysm.aerial_mode = ui->cB_elecZC_contrlmode_Z3->currentIndex() + 1;
            // 极化方式
            str_qysm.polarmand = ui->comboBox_DD4Z3_1->currentIndex();
            // 区域驻留时间
            str_qysm.region_onntime = ui->lineEdit_DD4Z3_2->text().toInt();
            // 区域点个数
            tmp_ushort = ui->lineEdit_DD4Z3_3->text().toInt();
            str_qysm.region_sum = qToBigEndian(tmp_ushort);

            sum_cntnum=tmp_ushort;
            if(sum_cntnum>5)sum_cntnum=5;
            for (int i=0;i<sum_cntnum;i++) {
                // 区域点经度
                tmp_uint = ui->tableWidget_DD4_Z3->item(i,0)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                // 区域点纬度
                tmp_uint = ui->tableWidget_DD4_Z3->item(i,1)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
            }

            // 拷贝数据
            modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;
        ;
    };
    // 子阵4
    if (ui->checkBox_D10bit3_3->isChecked()) {
        // 电子侦察任务--天线子阵参数变长部分
        memset(&str_zxzl, 0, sizeof(str_zxzl));
        memset(&str_zxsm, 0, sizeof(str_zxsm));
        memset(&str_qyns, 0, sizeof(str_qyns));
        memset(&str_qysm, 0, sizeof(str_qysm));

        int modeLen_1 = 0;  // 当前子阵的总长
        switch (ui->cB_elecZC_contrlmode_Z4->currentIndex()) {
        case 0:  // 指向驻留模式参数

            modeLen_1 = sizeof(str_zxzl);
            // 天线子阵号
            str_zxzl.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
            // 天线子阵控制模式
            str_zxzl.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
            // 极化方式
            str_zxzl.polarmand = ui->comboBox_DD1Z4_1->currentIndex();
            // 波束离轴角指向
            tmp_ushort = ui->lineEdit_DD1Z4_2->text().toInt();
            str_zxzl.bs_offaxis = qToBigEndian(tmp_ushort);
            // 波束方位角指向
            tmp_ushort = ui->lineEdit_DD1Z4_3->text().toInt();
            str_zxzl.bs_bearing = qToBigEndian(tmp_ushort);

            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxzl, modeLen_1);
            break;
        case 1:  // 指向扫描模式参数

            modeLen_1 = sizeof(str_zxsm);
            // 天线子阵号
            str_zxsm.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
            // 天线子阵控制模式
            str_zxsm.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
            // 极化方式
            str_zxsm.polarmand = ui->comboBox_DD2Z4_1->currentIndex();
            // 指向驻留时间
            str_zxsm.zx_ontime = ui->lineEdit_DD2Z4_2->text().toInt();
            // 指向个数
            str_zxsm.pointsum = ui->lineEdit_DD2Z4_3->text().toInt();
            if(ui->lineEdit_DD2Z4_3->text().toInt()>255)str_zxsm.pointsum=255;

            sum_cntnum=str_zxsm.pointsum;
            if(sum_cntnum>255)sum_cntnum=255;
            for (int i=0;i<sum_cntnum;i++) {
                // 波束离轴角指向
                tmp_ushort = ui->tableWidget_DD2_Z4->item(i,0)->text().toInt();
                str_zxsm.cyc[i].bs_offaxis = qToBigEndian(tmp_ushort);
                // 波束方位角指向
                tmp_ushort = ui->tableWidget_DD2_Z4->item(i,1)->text().toInt();
                str_zxsm.cyc[i].bs_bearing = qToBigEndian(tmp_ushort);
            }
            // 拷贝数据
            modeLen_1=modeLen_1-(255-sum_cntnum)*sizeof (Cyc_zxsm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_zxsm, modeLen_1);
            break;
        case 2:  // 区域凝视模式参数

            modeLen_1 = sizeof(str_qyns);
            // 天线子阵号
            str_qyns.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
            // 天线子阵控制模式
            str_qyns.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
            // 极化方式
            str_qyns.polarmand = ui->comboBox_DD3Z4_1->currentIndex();
            // 目标经度
            tmp_uint = ui->lineEdit_DD3Z4_2->text().toDouble()*1000000;
            str_qyns.target_orb = qToBigEndian(tmp_uint);
            // 目标纬度
            tmp_uint = ui->lineEdit_DD3Z4_3->text().toDouble()*1000000;
            str_qyns.target_latitude = qToBigEndian(tmp_uint);
            // 拷贝数据
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qyns, modeLen_1);
            break;
        case 3:  // 区域扫描模式参数

            modeLen_1 = sizeof(str_qysm);
            // 天线子阵号
            str_qysm.aerial_zznumber=ui->cB_elecZC_txnumber_Z4->currentIndex();
            // 天线子阵控制模式
            str_qysm.aerial_mode = ui->cB_elecZC_contrlmode_Z4->currentIndex() + 1;
            // 极化方式
            str_qysm.polarmand = ui->comboBox_DD4Z4_1->currentIndex();
            // 区域驻留时间
            str_qysm.region_onntime = ui->lineEdit_DD4Z4_2->text().toInt();
            // 区域点个数
            tmp_ushort = ui->lineEdit_DD4Z4_3->text().toInt();
            str_qysm.region_sum = qToBigEndian(tmp_ushort);

            sum_cntnum=tmp_ushort;
            if(sum_cntnum>5)sum_cntnum=5;
            for (int i=0;i<sum_cntnum;i++) {
                // 区域点经度
                tmp_uint = ui->tableWidget_DD4_Z4->item(i,0)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_orb = qToBigEndian(tmp_uint);
                // 区域点纬度
                tmp_uint = ui->tableWidget_DD4_Z4->item(i,1)->text().toDouble()*1000000;
                str_qysm.cyc[i].region_latitude = qToBigEndian(tmp_uint);
            }

            // 拷贝数据
            modeLen_1=modeLen_1-(5-sum_cntnum)*sizeof (Cyc_qysm);
            memcpy(buff_mode_all4 + modeLen_SUM, &str_qysm, modeLen_1);
            break;
        default:
            break;
        }

        modeLen_SUM += modeLen_1;
    };

    strlen += modeLen_SUM;

    uchar *buff_elec_aerial = new uchar[strlen + 1];
    memcpy(buff_elec_aerial, &str, sizeof(Tz_Mess));
    memcpy(buff_elec_aerial + sizeof(Tz_Mess), buff_mode_all4, modeLen_SUM);

    return buff_elec_aerial;
}


//制作完整上注任务指令
uchar *sub1553_Overheadtask::Make_orderBuff(int &sumlen)
{

    sumlen=0;
    // 多个任务模式参数(不同任务号，不同任务参数和成一条上注任务数据包)
    QString part1_sbuff, part2_sbuff;
    int part1_long = 0, part2_long = 0;
    QVector<int> part1_taskNum;  // 引导头的任务号存储
    // 获取一共有多少个任务号
    part1_taskNum.resize(0);
    for (int n = 0; n < model_mlist->rowCount(); n++)
    {
        int tmpNum = model_mlist->data(model_mlist->index(n, 0)).toInt();
        if (count(part1_taskNum.begin(), part1_taskNum.end(), tmpNum) == 0)
        {
            part1_taskNum.push_back(tmpNum);
        }
    }
    int taskpack = part1_taskNum.size();
    QVector<QString> part1_vstr[taskpack],part2_vstr[taskpack];  // 多个任务号的引导头参数,多个任务号的多个任务参数
    // 获取数据字符串内容
    for (int num = 0; num < part1_taskNum.size(); num++) {  // 任务号个数（多个任务）
        bool tmp_once = true;
        for (int n_row = 0; n_row < model_mlist->rowCount();n_row++)  // 遍历表格相同的任务号（多个任务模式参数）
        {
            int tmpNum = model_mlist->data(model_mlist->index(n_row, 0)).toInt();
            if (part1_taskNum[num] != tmpNum) continue;
            part1_sbuff = model_mlist->data(model_mlist->index(n_row, 2)).toString();  // 引导头内容数据
            part1_sbuff = part1_sbuff.replace(" ", "");
            if (tmp_once == true)  // 一个任务号只加一次引导头
            {
                part1_long += (part1_sbuff.size() + 1) / 2;
                tmp_once = false;
            }
            part1_vstr[num].push_back(part1_sbuff);

            part2_sbuff = model_mlist->data(model_mlist->index(n_row, 5)).toString();  // 参数内容数据
            part2_sbuff = part2_sbuff.replace(" ", "");
            part2_long += (part2_sbuff.size() + 1) / 2;
            part2_vstr[num].push_back(part2_sbuff);
        }

    }

    // 新建缓存存储所以参数
    uchar *databuff = new uchar[part1_long + part2_long + 1];
    int dataLen = 0;                                        // 递增拷贝缓存
    for (int num = 0; num < part1_taskNum.size(); num++)
    {   // 任务号个数
        uint task_len=0;//任务长度（每个任务单独的总长度）
        // 第一段
        int tmplen1 = (part1_vstr[num][0].size() + 1) / 2;
        QByteArray hex_data = QByteArray::fromHex(part1_vstr[num][0].toLatin1());  // 将字节流转换位16进制,char型
        memcpy(databuff + dataLen, (uchar *)hex_data.data(), tmplen1);  // 获取地址
        dataLen += tmplen1;
        task_len += tmplen1;
        // 第二段
        for (int s = 0; s < part2_vstr[num].size(); s++)
        {
            int tmplen2 = (part2_vstr[num][s].size() + 1) / 2;
            QByteArray hex_data2 = QByteArray::fromHex(part2_vstr[num][s].toLatin1());  // 将字节流转换位16进制,char型
            memcpy(databuff + dataLen, (uchar *)hex_data2.data(),tmplen2);  // 获取地址
            dataLen += tmplen2;
            task_len += tmplen2;
        }
        //合并需要改变的参数
        int offset=dataLen-task_len;//任务长度的位置
        task_len=qToBigEndian(task_len);
        memcpy(databuff+offset,(uchar *)&task_len,sizeof (task_len));//同一个任务多个任务模式参数
    }

    // 封装总包头//////////////////////////////////////////////
    OntaskFormat Task_Format;
    memset(&Task_Format,0,sizeof (Task_Format));
    // 任务包总长度
    Task_Format.sumLen = qToBigEndian(12 + part1_long + part2_long);
    // 任务数量
    ushort taskSum = ui->lineEdit_TaskNumber->text().toUInt();
    Task_Format.taskSum = qToBigEndian(taskSum);

    // crc-25
    ushort crccal;
    uint aa = 10 + part1_long + part2_long;
    if(aa%2!=0)aa+=1;//奇数补偶数
    uchar *str_check = new uchar[aa];
    memset(str_check,0,aa);

    memcpy(str_check, &Task_Format, sizeof(OntaskFormat));
    memcpy(str_check + sizeof(OntaskFormat), databuff, part1_long + part2_long);
    ushort *check = (ushort *)str_check;
    crccal = CRC16(check, aa / 2);
    crccal=qToBigEndian(crccal);//crc转字节序
    delete[] str_check;

    //制作完整指令缓存
    sumlen=sizeof(OntaskFormat) + part1_long + part2_long + 2;
    uchar* oder_buff = new uchar[sumlen+1];
    memcpy(oder_buff, &Task_Format, sizeof(OntaskFormat));
    memcpy(oder_buff + sizeof(OntaskFormat), databuff,part1_long + part2_long);
    memcpy(oder_buff + sumlen - 2, &crccal, 2);
    delete[] databuff;


    return oder_buff;
}


//改变SAR内容地址
void sub1553_Overheadtask::change_sarAddr(int curr)
{
    switch (curr) {
    case 1://广域搜索模式

        //高算力1
        ui->comboBox_C12->setCurrentIndex(1);
        ui->lineEdit_C12->setText("3F42");
        ui->comboBox_C13->setCurrentIndex(0);
        ui->lineEdit_C13->setText("3F41");

        ui->comboBox_C14->setCurrentIndex(11);
        ui->lineEdit_C14->setText("3F12");
        ui->comboBox_C15->setCurrentIndex(13);
        ui->lineEdit_C15->setText("3F14");
        ui->comboBox_C16->setCurrentIndex(17);
        ui->lineEdit_C16->setText("EEEE");
        ui->comboBox_C17->setCurrentIndex(15);
        ui->lineEdit_C17->setText("3F16");
        ui->comboBox_C18->setCurrentIndex(14);
        ui->lineEdit_C18->setText("3F15");
        ui->comboBox_C19->setCurrentIndex(17);
        ui->lineEdit_C19->setText("EEEE");
        //高算力2
        //ui->lineEdit_D4_1->setText("");
        //ui->lineEdit_D4_2->setText("");
        ui->lineEdit_D4_3->setText("EEEE");
        ui->lineEdit_D4_4->setText("EEEE");
        //ui->lineEdit_D4_5->setText("");
        ui->lineEdit_D4_6->setText("3F17");
        ui->lineEdit_D4_7->setText("EEEE");
        //ui->lineEdit_D4_8->setText("");
        break;
    case 2://滑动聚束模式
        //高算力1
        ui->comboBox_C12->setCurrentIndex(1);
        ui->lineEdit_C12->setText("3F42");
        ui->comboBox_C13->setCurrentIndex(0);
        ui->lineEdit_C13->setText("3F41");

        //ui->comboBox_C14->setCurrentIndex(11);
        ui->lineEdit_C14->setText("3F18");
        //ui->comboBox_C15->setCurrentIndex(12);
        ui->lineEdit_C15->setText("3F19");
        ui->comboBox_C16->setCurrentIndex(17);
        ui->lineEdit_C16->setText("EEEE");
        //ui->comboBox_C17->setCurrentIndex(14);
        ui->lineEdit_C17->setText("3F21");
        //ui->comboBox_C18->setCurrentIndex(13);
        ui->lineEdit_C18->setText("3F20");
        ui->comboBox_C19->setCurrentIndex(17);
        ui->lineEdit_C19->setText("EEEE");
        //高算力2
        //ui->lineEdit_D4_1->setText("");
        //ui->lineEdit_D4_2->setText("");
        ui->lineEdit_D4_3->setText("3F25");
        ui->lineEdit_D4_4->setText("3F24");
        //ui->lineEdit_D4_5->setText("");
        ui->lineEdit_D4_6->setText("3F22");
        ui->lineEdit_D4_7->setText("3F23");
        //ui->lineEdit_D4_8->setText("");
        break;
    case 3://条带模式
        //高算力1

        ui->comboBox_C12->setCurrentIndex(1);
        ui->lineEdit_C12->setText("3F42");
        ui->comboBox_C13->setCurrentIndex(0);
        ui->lineEdit_C13->setText("3F41");

        ui->comboBox_C14->setCurrentIndex(0);
        ui->lineEdit_C14->setText("3F01");
        ui->comboBox_C15->setCurrentIndex(1);
        ui->lineEdit_C15->setText("3F02");
        ui->comboBox_C16->setCurrentIndex(17);
        ui->lineEdit_C16->setText("EEEE");
        ui->comboBox_C17->setCurrentIndex(7);
        ui->lineEdit_C17->setText("3F08");
        ui->comboBox_C18->setCurrentIndex(6);
        ui->lineEdit_C18->setText("3F07");
        ui->comboBox_C19->setCurrentIndex(17);
        ui->lineEdit_C19->setText("EEEE");
        //高算力2
        //ui->lineEdit_D4_1->setText("");
        //ui->lineEdit_D4_2->setText("");
        ui->lineEdit_D4_3->setText("EEEE");
        ui->lineEdit_D4_4->setText("3F11");
        //ui->lineEdit_D4_5->setText("");
        ui->lineEdit_D4_6->setText("3F09");
        ui->lineEdit_D4_7->setText("3F10");
        //ui->lineEdit_D4_8->setText("");
        break;
    case 4://TOP模式
        //高算力1

        ui->comboBox_C12->setCurrentIndex(1);
        ui->lineEdit_C12->setText("3F42");
        ui->comboBox_C13->setCurrentIndex(0);
        ui->lineEdit_C13->setText("3F41");

        ui->comboBox_C14->setCurrentIndex(3);
        ui->lineEdit_C14->setText("3F04");
        ui->comboBox_C15->setCurrentIndex(4);
        ui->lineEdit_C15->setText("3F05");
        ui->comboBox_C16->setCurrentIndex(17);
        ui->lineEdit_C16->setText("EEEE");
        ui->comboBox_C17->setCurrentIndex(7);
        ui->lineEdit_C17->setText("3F08");
        ui->comboBox_C18->setCurrentIndex(6);
        ui->lineEdit_C18->setText("3F07");
        ui->comboBox_C19->setCurrentIndex(17);
        ui->lineEdit_C19->setText("EEEE");
        //高算力2
        //ui->lineEdit_D4_1->setText("");
        //ui->lineEdit_D4_2->setText("");
        ui->lineEdit_D4_3->setText("EEEE");
        ui->lineEdit_D4_4->setText("EEEE");
        //ui->lineEdit_D4_5->setText("");
        ui->lineEdit_D4_6->setText("EEEE");
        ui->lineEdit_D4_7->setText("EEEE");
        //ui->lineEdit_D4_8->setText("");
        break;
    default:
        break;
    }
}


//1553指令封装 上注任务0x0088
void sub1553_Overheadtask::on_pB_Overheadtask_clicked() {

    if (model_mlist->rowCount() <= 0) return;
    int order_len=0;    //指令总长
    uchar *BUFF=nullptr;//指令缓存区
    BUFF=Make_orderBuff(order_len);//指令拼接

    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 11;
    order_data.gap_time = 1;
    order_data.start_time = 0;
    if(model_mlist->rowCount()==1)//单个任务
    {
        QString tmp=model_mlist->data(model_mlist->index(0, 3)).toString();  // 任务模式参数名称
        tmp=tmp.right(tmp.size()-tmp.indexOf(":")-1);
        order_data.order_name = QString("上注任务--"+tmp);
    }
    else
    {
        order_data.order_name = QString("上注任务--多任务");
    }

    order_data.order_kind = 3;
    order_data.order_len = order_len;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, BUFF, order_data.order_len);

    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    delete [] BUFF;


}

//CAN指令封装  生成(上注任务指令)
void sub1553_Overheadtask::on_pB_Overheadtask_CAN_clicked()
{
    if (model_mlist->rowCount() <= 0) return;
    int order_len=0;    //指令总长
    uchar *BUFF=nullptr;//指令缓存区
    BUFF=Make_orderBuff(order_len);//指令拼接

    order_len-=12;//CAN类型指令去掉上注任务格式的最外层包，4任务包总长数+2任务数量+4保留++最后2CRC

    can_C90 can_kind;
    memset(&can_kind,0,sizeof (can_kind));
    //CAN另加封装 C90结构 +buff+2字节校验和
    ushort canLen=sizeof(can_kind)+order_len;
    uchar* can_buff=new uchar[canLen];

    can_kind.CanorderLen=qToBigEndian(canLen);
    can_kind.Canmark=0x90;       //指令标志（内部 ：任务下发C90）
    can_kind.pack_sum=1;        //超过2041字节就是多包（后期改）
    can_kind.pack_number=0;

    //拷贝数据到can格式缓存
    memcpy(can_buff,&can_kind,sizeof(can_kind)-2);//去掉2字节crc
    memcpy(can_buff+sizeof(can_kind)-2,BUFF+10,order_len);//N字节指令,跳过1553格式的前10字节头
    //校验和crc
    ushort crcs=0;
    for (int i=0;i<canLen-2;i++) {
        crcs+=can_buff[i];
    }
    can_kind.crc_add=qToBigEndian(crcs);
    memcpy(can_buff+canLen-2,&can_kind.crc_add,2);//2字节校验和

    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 5;
    order_data.gap_time = 1;
    order_data.start_time = 0;
    if(model_mlist->rowCount()==1)//单个任务
    {
        QString tmp=model_mlist->data(model_mlist->index(0, 3)).toString();  // 任务模式参数名称
        tmp=tmp.right(tmp.size()-tmp.indexOf(":")-1);
        order_data.order_name = QString("上注任务CAN--"+tmp);
    }
    else
    {
        order_data.order_name = QString("上注任务CAN--多任务");
    }
    order_data.order_kind = 9;
    order_data.order_len = canLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, can_buff, order_data.order_len);

    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);

    delete [] BUFF;
    delete [] can_buff;
}

// 指令生成
void sub1553_Overheadtask::on_pB_CommandGeneration_clicked() {

    if(ui->cB_function_mode->currentIndex()==9)//扩展功能(格式跟上注任务不一样)
    {
        tz_fun();
        return;
    }
    uint tmp_uint = 0;
    ushort tmp_ushort = 0;
    //(任务N内容引导头)
    TaskContent strTaskContent;
    memset(&strTaskContent, 0, sizeof(TaskContent));

    // 任务流水号
    tmp_ushort = ui->lineEdit_A2->text().toInt();
    strTaskContent.taskflowid = qToBigEndian(tmp_ushort);
    // 主任务id
    tmp_ushort = ui->lineEdit_A3->text().toInt();
    strTaskContent.main_id = qToBigEndian(tmp_ushort);
    // 子任务id
    strTaskContent.sub_id = ui->lineEdit_A4->text().toInt();
    // 卫星代码
    tmp_ushort = toHex_ushort(ui->lineEdit_A5->text());
    strTaskContent.start_code = tmp_ushort;
    // 主从标志
    strTaskContent.mainsub_choose = ui->comboBox_A6->currentIndex();
    if(ui->comboBox_A6->currentIndex()==2)strTaskContent.mainsub_choose=0xFF;
    // 协同卫星数量
    strTaskContent.start_sum = ui->lineEdit_A7->text().toInt();
    // 功能模式
    strTaskContent.fun_mode = ui->cB_function_mode->currentIndex() + 1;
    // 工作模式
    strTaskContent.work_mode = ui->comboBox_A9->currentIndex() + 1;
    // 任务类型
    strTaskContent.tasktype = ui->comboBox_A10->currentIndex() + 1;
    // 任务个数
    strTaskContent.tasksum = ui->lineEdit_A11->text().toInt();
    // 模板标志
    strTaskContent.mb_mask = ui->comboBox_A12_->currentIndex() + 1;
    // 任务开始时刻
    tmp_uint = ui->lineEdit_A13->text().toUInt();
    strTaskContent.task_starttime = qToBigEndian(tmp_uint);
    // 任务持续时长
    tmp_uint = ui->lineEdit_A14->text().toUInt();
    strTaskContent.task_holdtime = qToBigEndian(tmp_uint);
    //(任务基本信息)
    // 高算力平台选择
    strTaskContent.Gener_str.gsl_choose = ui->comboBox_C1->currentIndex();
    // 高算力主从选择
    strTaskContent.Gener_str.gsl_mainsub = ui->comboBox_C2->currentIndex();
    // 频段选择
    strTaskContent.Gener_str.pd_choose = ui->comboBox_C3->currentIndex();
    // 数传标志
    strTaskContent.Gener_str.data_choose = (ui->comboBox_C4->currentIndex()<<4)+ui->comboBox_C4_1->currentIndex();
    // 数传传输速率
    tmp_ushort = ui->lineEdit_C5->text().toInt();
    strTaskContent.Gener_str.data_speed = qToBigEndian(tmp_ushort);
    //内校正输出通道
    strTaskContent.Gener_str.inch_choose = ui->comboBox_C7->currentIndex();
    //DA_dbm
    strTaskContent.Gener_str.DA_dbm = ui->lineEdit_addC8->text().toInt();
    // 中频切换开关状态
    strTaskContent.Gener_str.zp_change = ui->comboBox_C11->currentIndex();

    QString S_sorftnum;
    QByteArray hex_data;
    // 收发FPGA_1
    S_sorftnum = ui->lineEdit_C12->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    int strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.sf_fpga1 = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.sf_fpga1 = 0xffff;
    // 收发FPGA_2
    S_sorftnum = ui->lineEdit_C13->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.sf_fpga2 = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.sf_fpga2 = 0xffff;
    // 数据处理板AFPGA_1
    S_sorftnum = ui->lineEdit_C14->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.dataA_fpga1 = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA_fpga1 = 0xffff;
    // 数据处理板AFPGA_2
    S_sorftnum = ui->lineEdit_C15->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.dataA_fpga2 = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA_fpga2 = 0xffff;
    // 数据处理板Adsp
    S_sorftnum = ui->lineEdit_C16->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  //将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.dataA_dsp = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataA_dsp = 0xffff;
    // 数据处理板BFPGA_1
    S_sorftnum = ui->lineEdit_C17->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.dataB_fpga1 = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB_fpga1 = 0xffff;
    // 数据处理板BFPGA_2
    S_sorftnum = ui->lineEdit_C18->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.dataB_fpga2 = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB_fpga2 = 0xffff;
    // 数据处理板Bdsp
    S_sorftnum = ui->lineEdit_C19->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    strlen = (S_sorftnum.size() + 1) / 2;
    tmp_ushort = 0;
    memcpy(&tmp_ushort, (uchar *)hex_data.data(), strlen);  // 获取地址
    strTaskContent.Gener_str.dataB_dsp = tmp_ushort;
    if (tmp_ushort == 0) strTaskContent.Gener_str.dataB_dsp = 0xffff;

    //(任务基本信息变长部分)
    uchar *p_str = NULL;
    int strLen = 0;
    bool f_modedata=true;//是否需要具体任务模式参数
    if(ui->lineEdit_A11->text().toUInt()==0)f_modedata=false;//任务个数为0时，不获取任务模式数据
    switch (ui->cB_function_mode->currentIndex())  // 功能模式
    {
    case 0:  // 电子侦察任务
        p_str = set_Elec_ReconData(strLen);
        break;
    case 1:  // 电子干扰任务
    case 2:
        p_str = set_Elec_JammingData(strLen);
        break;

    case 3: //SXKu天线定标任务
        p_str=set_Elec_sxkuDB(strLen);
        f_modedata=false;
        break;
    case 4: //SAR探测任务基本信息
        p_str=set_SAR_probing(strLen);
        f_modedata=false;
        break;
    case 5:
        //备用导航任务
        p_str=set_Elec_BYnavigation(strLen);
        break;
    case 6:
    case 7:
        //类5G
        p_str=set_5G_kind(strLen);
        break;
    case 8:
        //J链
        p_str=set_J_chain(strLen);
        break;
    default:  // 其余待定默认电子侦察任
        p_str = set_Elec_ReconData(strLen);
        break;
    }

    // 整个任务基本信息长度
    int gener_len=sizeof (strTaskContent.Gener_str);
    tmp_uint = gener_len + strLen;
    strTaskContent.Gener_str.task_massageLen = qToBigEndian(tmp_uint);  // 固定头+变长

    if(f_modedata)//是否需要获取任务模式参数配置界面数据
    {
        // 任务模式参数（第二个界面）。。。。。。。。。。。。。。。。。。
        Task_ModeParameter str_TaskModeParameter;
        memset(&str_TaskModeParameter, 0, sizeof(Task_ModeParameter));
        // 任务模式参数长度
        // 任务执行fpga选择
        str_TaskModeParameter.task_fpgachoose =
                ui->checkBox_F3bit0->isChecked() +
                (ui->checkBox_F3bit1->isChecked() << 1) +
                (ui->checkBox_F3bit2->isChecked() << 2) +
                (ui->checkBox_F3bit3->isChecked() << 3);
        // 融合标志
        str_TaskModeParameter.dx_marsk = ui->comboBox_F3->currentIndex();
        // AI识别标志
        str_TaskModeParameter.RH_AI_mask = (ui->comboBox_F4->currentIndex()<<4)+ ui->comboBox_F5->currentIndex();

        //...定位参数(不定长部分1)
        // 三星定位主星地址
        str_TaskModeParameter.third_site[0]=ui->lineEdit_F6_1ip1->text().toInt();
        str_TaskModeParameter.third_site[1]=ui->lineEdit_F6_1ip2->text().toInt();
        str_TaskModeParameter.third_site[2]=ui->lineEdit_F6_1ip3->text().toInt();
        str_TaskModeParameter.third_site[3]=ui->lineEdit_F6_1ip4->text().toInt();
        // 三星定位主星基地址
        str_TaskModeParameter.third_base_site = toHex_ushort(ui->lineEdit_F6_2->text());
        //多星定位工作模式
        str_TaskModeParameter.start_mode = ui->comboBox_F6_3_->currentIndex()+1;
        // 协同引导卫星个数
        int starNum= ui->lineEdit_F6_4->text().toInt();
        str_TaskModeParameter.satelliteSum =starNum;

        // 协同引导卫星目的地址
        if(starNum>3)starNum=3;//限制地址最多3个
        uint addrbuff[starNum];
        memset(addrbuff,0,sizeof (addrbuff));
        for(int adr=0;adr<starNum;adr++)//地址按16进制存入
        {
            QString S_sorftnum=ui->tableWidget_startAddr->item(adr,0)->text();//设置内容
            addrbuff[adr]=toHex_uint(S_sorftnum);
        }


        //...引导参数(不定长部分2）
        //引导卫星个数
        uchar yd_startNum=ui->lineEdit_F6_5->text().toInt();
        if(yd_startNum>20)yd_startNum=20;//限制地址最多20个
        ModePart_yd strN_yd[yd_startNum];
        memset(strN_yd,0,sizeof (strN_yd));
        //引导卫星工作模式(不定长)
        //引导卫星目的地址(不定长)
        for(int i=0;i<yd_startNum;i++)//地址按16进制存入
        {

            QString S_sorftnum=ui->tableWidget_YDCSaddr->item(i,0)->text();//设置内容1
            strN_yd[i].yd_startMode=S_sorftnum.toInt();

            QString S_sorftnum2=ui->tableWidget_YDCSaddr->item(i,1)->text();//设置内容2
            strN_yd[i].yd_startAddr=toHex_uint(S_sorftnum2);
        }
        int yd_len=1+sizeof (strN_yd);
        uchar* yd_buff=new uchar[yd_len];
        memcpy(yd_buff,&yd_startNum,1);
        memcpy(yd_buff+1,strN_yd,sizeof (strN_yd));

        //变长部分指令写入
        int part1Len=sizeof (addrbuff)+yd_len+1;//定位参数（变长）+引导参数（变长）+任务模式类型
        uchar* Buff_2part1=new uchar[part1Len];
        memset(Buff_2part1,0,part1Len);
        memcpy(Buff_2part1,addrbuff,sizeof (addrbuff));
        memcpy(Buff_2part1+sizeof (addrbuff),yd_buff,yd_len);

        // 任务模式类型
        uchar task_modetype =ui->cB_task_modetype->currentIndex() + 1;
        memcpy(Buff_2part1+sizeof (addrbuff)+yd_len,&task_modetype,1);
        delete [] yd_buff;


        //第二部分指令
        uchar *p_str2 = NULL;
        int part2Len = 0;
        // 任务模式类型
        QString modetype = ui->cB_task_modetype->currentText();
        int choose = zl_kind[modetype];

        switch (choose) {
        case 1:
            // 全景模式
            p_str2 = mode_qj_0(part2Len);
            break;
        case 2:
            // 常规信号频点控守
            p_str2 = mode_cgxhpdks_2(part2Len);
            break;
        case 3:
            // Link16信号频点控守参数
            p_str2 = mode_linkpdks_3(part2Len);
            break;
        case 4:
            // 塔康信号频点控守
            p_str2 = mode_tkxhpdks_4(part2Len);
            break;
        case 5:
            // 敌我识别信号频点控守
            p_str2 = mode_dwsbxh_5(part2Len);
            break;
        case 6:
            // 铱星信号频点控守
            p_str2 = mode_yxxhpdks_6(part2Len);
            break;
        case 7:
            // 海事信号频点控守
            p_str2 = mode_hsxhpdks_7(part2Len);
            break;
        case 8:
            // 雷达信号频点控守
            p_str2 = mode_ldxhpdks_8(part2Len);
            break;
        case 9:
            // 星链信号频点控守参数
            p_str2 = mode_xlxhpdks_9(part2Len);
            break;
        case 10:
            //同步采样
            p_str2 = mode_tbcy_18(part2Len);
            break;
        case 11:
            //上注软件解调
            p_str2 = mode_up_sorft_20(part2Len);
            break;
        case 12:
            //雷达信号频点扫描
            p_str2=mode_ldxhpdsmT_11(part2Len);
            break;
        case 13:
            //多频点快速干扰
            p_str2 = mode_spgr_13(part2Len);
            break;
        case 14:
            // 等间隔梳状谱干扰
            p_str2 = mode_szpgr_14(part2Len);
            break;
        case 15:
            // 非等间隔梳状谱干扰
            p_str2 = mode_not_szpgr_15(part2Len);
            break;
        case 16:
            // 多通道快速协同干扰
            p_str2=mode_dhmbgr_T16(part2Len);
            break;
        case 17:
            //多通道多带宽协同干扰
            p_str2=mode_xlmbgr_T17(part2Len);
            break;
        case 18:
            //雷达强制干扰
            p_str2=mode_LD_QZgr18(part2Len);
            break;
        case 19:
            //雷达侦察
            p_str2=mode_LD_T19(part2Len);
            break;
        case 20:
            //星间/星地感知引导干扰（待补充）

            break;
        case 21:
            //备用导航任务模式参数
            p_str2=mode_BY_T21(part2Len);
            break;
        case 22:
            //类5G模式参数
            p_str2=mode_L5G_T22(part2Len);
            break;
        case 23:
            //J链任务模式参数
            p_str2=mode_J_T23(part2Len);
            break;
        default:
            break;
        }

        // 任务参数长度（任务模式参数长度到任务模式参数字节总长）
        uint tmpsumLen = sizeof(Task_ModeParameter)+part1Len + part2Len;
        str_TaskModeParameter.taskmodeLen = qToBigEndian(tmpsumLen);

        // 任务长度（任务长度到任务模式参数字节总长）
        tmpsumLen =sizeof(TaskContent) + strLen + sizeof(Task_ModeParameter) +part1Len+ part2Len;
        strTaskContent.taskSumlen = qToBigEndian(tmpsumLen);

        // 内容引导头
        uchar *Buff_1 = new uchar[sizeof(TaskContent) + strLen];
        memcpy(Buff_1, &strTaskContent, sizeof(TaskContent));
        memcpy(Buff_1 + sizeof(TaskContent), p_str, strLen);

        // 内容参数
        uchar *Buff_2= new uchar[sizeof(Task_ModeParameter) +part1Len+ part2Len];
        memcpy(Buff_2, &str_TaskModeParameter, sizeof(Task_ModeParameter));
        memcpy(Buff_2+ sizeof(Task_ModeParameter), Buff_2part1, part1Len);
        memcpy(Buff_2 + sizeof(Task_ModeParameter)+part1Len, p_str2, part2Len);

        //////////////////////////////////////////////////////////////////
        // 生成到界面
        //  内容号
        int cnt = model_mlist->rowCount();
        model_mlist->setItem(cnt, 0,new QStandardItem(ui->lineEdit_TaskNumber->text()));
        // 引导长度
        model_mlist->setItem(cnt, 1, new QStandardItem(QString::number(sizeof(TaskContent) + strLen)));
        // 内容引导头
        QString str = "";
        QString tmp_byte;
        for (uint readLen = 0; readLen < sizeof(TaskContent) + strLen; readLen++) {
            tmp_byte = QString().asprintf("%02x ", Buff_1[readLen]);
            str.append(tmp_byte);
        }
        model_mlist->setItem(cnt, 2, new QStandardItem(str));
        // 名称。。。。。。。。。。。。。。。
        model_mlist->setItem(cnt, 3, new QStandardItem(ui->cB_task_modetype->currentText()));
        // 长度
        model_mlist->setItem(cnt, 4,new QStandardItem(QString::number(sizeof(Task_ModeParameter) +part1Len+ part2Len)));
        //内容参数类型
        str = "";
        for (uint readLen = 0; readLen < sizeof(Task_ModeParameter) +part1Len+ part2Len;readLen++) {
            tmp_byte = QString().asprintf("%02x ", Buff_2[readLen]);
            str.append(tmp_byte);
        }
        model_mlist->setItem(cnt, 5, new QStandardItem(str));

        delete[] p_str;
        delete[] p_str2;
        delete[] Buff_1;
        // delete[] Buff_2;
        delete[] Buff_2part1;
    }
    else{//不需要第二个界面数据

        QStringList sarlist;
        uchar *p_str2 = nullptr;
        int strLen2 = 0;
        if(ui->cB_function_mode->currentIndex()==4)//SAR文件读取参数
        {
            if(ui->tB_widget_SARFileList->rowCount()==0)
            {
                QMessageBox::warning(this,tr("错误"),tr("未选择SAR参数内容文件"));
                return;
            }
            for (int n=0;n<ui->tB_widget_SARFileList->rowCount();n++) {
                sarlist.append(ui->tB_widget_SARFileList->item(n, 1)->text());
            }
            p_str2 = mode_SAR(sarlist,strLen2);
        }

        // 任务长度（任务长度到任务模式参数字节总长）
        uint tmpsumLen =sizeof(TaskContent) + strLen+strLen2;
        strTaskContent.taskSumlen = qToBigEndian(tmpsumLen);

        // 内容引导头
        uchar *Buff_1 = new uchar[sizeof(TaskContent) + strLen];
        memcpy(Buff_1, &strTaskContent, sizeof(TaskContent));
        memcpy(Buff_1 + sizeof(TaskContent), p_str, strLen);
        //////////////////////////////////////////////////////////////////
        // 生成到界面
        //  内容号
        int cnt = model_mlist->rowCount();
        model_mlist->setItem(cnt, 0,new QStandardItem(ui->lineEdit_TaskNumber->text()));
        // 引导长度
        model_mlist->setItem(cnt, 1, new QStandardItem(QString::number(sizeof(TaskContent) + strLen)));
        // 内容引导头
        QString str = "";
        QString tmp_byte;
        for (uint readLen = 0; readLen < sizeof(TaskContent) + strLen; readLen++) {
            tmp_byte = QString().asprintf("%02x ", Buff_1[readLen]);
            str.append(tmp_byte);
        }
        model_mlist->setItem(cnt, 2, new QStandardItem(str));
        // 名称
        model_mlist->setItem(cnt, 3, new QStandardItem(ui->cB_function_mode->currentText()));
        // 长度
        model_mlist->setItem(cnt, 4,new QStandardItem(QString::number(strLen2)));
        //内容参数类型
        str = "";
        for (int readLen = 0; readLen < strLen2;readLen++) {
            tmp_byte = QString().asprintf("%02x ", p_str2[readLen]);
            str.append(tmp_byte);
        }
        model_mlist->setItem(cnt, 5, new QStandardItem(str));


        delete[] p_str;
        delete[] Buff_1;
        // delete[] Buff_2;
    }
}

//SAR探测参数
uchar *sub1553_Overheadtask::mode_SAR(QStringList qFileList,int &strlen)
{
    //数据读取
    QString Str = "";
    int part_Long=0;
    //uchar* sarbuff=new uchar[qFileList.size()*300];
    uchar* sarbuff=new uchar[256*16];//最多16个sar任务
    for(int i=0;i<qFileList.size();i++)
    {
        QFile txt_file(qFileList.at(i));
        if(!(txt_file.open(QIODevice::ReadOnly|QIODevice::Text)))
        {
            QMessageBox::warning(this,tr("打开文件失败"),tr("路径")+qFileList.at(i));
            return nullptr;
        }
        QTextStream txtInput(&txt_file);
        QString read_str;
        while (!txtInput.atEnd()) {
            read_str+=txtInput.readLine();
        }
        read_str.replace(" ","");
        read_str.replace("\n","");
        int this_len=(read_str.size() + 1) / 2;//当前文件数据长度

        QByteArray hex_data=QByteArray::fromHex(read_str.toLatin1());//将字节流转换位16进制,char型
        uchar* data_buf=(uchar*)hex_data.data();//获取地址


        //        QString tmp_byte = "";
        //        for (int readLen = 0; readLen<this_len;readLen++) {
        //            tmp_byte = QString().asprintf("%02x ", data_buf[readLen]);
        //            Str.append(tmp_byte);
        //        }

        memcpy(sarbuff+part_Long,data_buf,this_len);
        part_Long+= this_len;

    }
    strlen=part_Long;
    return sarbuff;

}

//全景扫描
uchar *sub1553_Overheadtask::mode_qj_0(int &strlen) {
    uint tmp_uint = 0;
    double tmp_double=0;
    Str_QJmode strQJ;
    strlen = sizeof(Str_QJmode);
    memset(&strQJ, 0, sizeof(Str_QJmode));

    //保留1
    //保留2
    // 单通道AD采样存储深度
    strQJ.AD_num = 14+ui->comboBox_T1_3->currentIndex();
    // 采集触发方式
    strQJ.cj_mand = ui->comboBox_T1_4->currentIndex();
    // 触发门限
    strQJ.cfmx = ui->lineEdit_T1_6->text().toInt();
    // 频段个数
    int cycsum=ui->lineEdit_T1_5->text().toInt();
    strQJ.pd_sum = cycsum;

    Str_QJmode_p2 qjcs[cycsum];
    int aa=sizeof (qjcs);
    memset(qjcs,0,aa);

    if(cycsum>100)cycsum=100;
    for(int i=0;i<cycsum;i++)
    {
        // 起始频率(KHz)
        QString tmpstr=ui->tableWidget_T1_QJlist->item(i,0)->text();//设置内容
        tmp_double = tmpstr.toDouble();
        tmp_uint=tmp_double*1000;//输入Mhz,转换Khz
        qjcs[i].start_fre = qToBigEndian(tmp_uint);
        // 终止频率(KHz)
        tmpstr=ui->tableWidget_T1_QJlist->item(i,1)->text();
        tmp_double = tmpstr.toDouble();
        tmp_uint=tmp_double*1000;
        qjcs[i].end_fre = qToBigEndian(tmp_uint);
        // 瞬时频率(Hz)
        tmpstr=ui->tableWidget_T1_QJlist->item(i,2)->text();
        tmp_double = tmpstr.toDouble();
        tmp_uint=tmp_double*1000;
        qjcs[i].mid_fre = qToBigEndian(tmp_uint);
    }

    strlen+=sizeof (qjcs);

    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &strQJ, sizeof(Str_QJmode));
    memcpy(databuff+sizeof(Str_QJmode), qjcs, sizeof (qjcs));

    return databuff;
}


// 常规信号频点控守参数
uchar *sub1553_Overheadtask::mode_cgxhpdks_2(int &strlen) {

    uint tmp_uint = 0;
    double tmp_double = 0;
    gen_Sig_Ctr_HEAD ptr;
    strlen = sizeof(gen_Sig_Ctr_HEAD);
    memset(&ptr, 0, sizeof(gen_Sig_Ctr_HEAD));

    // 侦察标志
    ptr.investMode = ui->comboBox_T2_zcbz->currentIndex();
    //参数测量次数
    ptr.cscl_sum = ui->lineEdit_T2csclSum->text().toUInt();
    // 接收机频率MHz
    ptr.reciveFre = qToBigEndian(ui->lineEdit_T2_jsjpl->text().toUInt()*1000);
    //iq长度
    ptr.iq_len=ui->comboBox_T2_iqlen->currentIndex()+1;
    // 采样信道总数N
    uchar N_Num = ui->lineEdit_T2_cytxzs->text().toUInt();
    ptr.CyChannelNum_N = N_Num;

    /*常规信号频点控守参数采样*/
    cgxhpdks_cy cy_datas[N_Num];
    int aa=sizeof (cy_datas);
    memset(cy_datas,0,aa);

    double sps=0;

    if (N_Num > 4) N_Num = 4;
    for(int i=0;i<N_Num;i++)
    {
        // 处理板NCO频率MHz
        QString tmpstr=ui->tableWidget_T2_cytxbg->item(i,0)->text();
        tmp_double = tmpstr.toDouble();
        tmp_uint=tmp_double*1000000;
        cy_datas[i].NCOFre_N = qToBigEndian(tmp_uint);
        // 采样带宽Khz
        tmpstr=ui->tableWidget_T2_cytxbg->item(i,1)->text();
        sps=tmpstr.toDouble();
        tmp_uint = sps*1000;
        cy_datas[i].CyPer_N = qToBigEndian(tmp_uint);
        // 检测门限
        tmpstr=ui->tableWidget_T2_cytxbg->item(i,2)->text();
        //Bit7：门限标志，恒为1
        //Bit6~0：门限值
        cy_datas[i].examDoorLimit_N =0x80+ tmpstr.toInt();
        //        if(tmpstr.toInt()==0)
        //        {
        //            cy_datas[i].examDoorLimit_N=0xFF;//默认值
        //        }
    }


    strlen+=sizeof (cy_datas);

    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &ptr, sizeof(gen_Sig_Ctr_HEAD));
    memcpy(databuff+sizeof(gen_Sig_Ctr_HEAD), cy_datas, sizeof (cy_datas));

    return databuff;
}



// LINK16信号频点控守参数
uchar *sub1553_Overheadtask::mode_linkpdks_3(int &strlen) {

    Link16_Signal_Ctrl arr;
    memset(&arr,0,sizeof (arr));
    strlen=sizeof(arr);
    // 频偏
    arr.FreError = qToBigEndian(ui->lineEdit_T3pp->text().toUInt());
    // 检测通道选择
    arr.examChannelSel =ui->comboBox_T3jctdxz->currentIndex();
    // 脉冲类型
    arr.mckind =ui->comboBox_T3mckind->currentIndex();
    // PDW数据是否下传标识
    arr.is_pdw =ui->comboBox_T3pdw->currentIndex();
    // 是否测向
    arr.measureFlag =ui->comboBox_T3sfpx->currentIndex();
    // 测向频段
    arr.cx_pd =ui->comboBox_T3cxpd->currentIndex();
    // 测向基线
    arr.measureLine =ui->lineEdit_T3cxjx->text().toInt();
    // 校正谱通道选择
    arr.corChannelSel =ui->comboBox_T3xztdxz->currentIndex();
    // 校正谱通道选择
    arr.cx_oder =ui->lineEdit_T3cxmx->text().toInt();
    //校正方式
    arr.jx_mainer =ui->comboBox_T3jzfs->currentIndex()+1;
    //搜索区域宽度 6.27新加
    arr.ssqy =ui->lineEdit_T3sskd->text().toInt();

    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(Link16_Signal_Ctrl));
    return databuff;
}


// 塔康信号频点控守
uchar *sub1553_Overheadtask::mode_tkxhpdks_4(int &strlen) {
    Tk_Signal_Ctrl ptr;
    memset(&ptr,0,sizeof(ptr));
    strlen=sizeof(ptr);

    // 检测通道选择
    ptr.examChannelSel = qToBigEndian(ui->lineEdit_T4_jctxxz->text().toUInt());
    // 是否测向
    ptr.measureFlag = ui->comboBox_T4_sfjc->currentIndex();

    //测向频段
    ptr.cxpd=ui->comboBox_T4_cxpd->currentIndex();
    // 测向基线
    ptr.measureLine = ui->lineEdit_T4_cxjx->text().toUInt();
    // 校正谱通道选择
    ptr.corChannelSel = ui->lineEdit_T4_jzptxxz->text().toUInt();
    // 测向门限
    ptr.cx_oder=ui->lineEdit_T4_cxmx->text().toUInt();
    // 塔康信号下传标志
    ptr.tc_downmark=ui->checkBox_tk7_b0->isChecked()+(ui->checkBox_tk7_b1->isChecked()<<1)+
            (ui->checkBox_tk7_b2->isChecked()<<2)+(ui->checkBox_tk7_b3->isChecked()<<3);
    // 校正方式
    ptr.jz_mand=ui->comboBox_tk8->currentIndex()+1;
    // 搜索区域宽度 6.27新加
    ptr.sskd=ui->lineEdit_tk9->text().toUInt();

    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &ptr, sizeof(Tk_Signal_Ctrl));
    return databuff;

}

// 敌我识别信号频点控守
uchar *sub1553_Overheadtask::mode_dwsbxh_5(int &strlen) {
    DW_Signal_Ctrl arr;
    uint tmp_uint=0;
    memset(&arr,0,sizeof (arr));
    strlen=sizeof (arr);


    // 检测通道选择
    tmp_uint=ui->comboBox_T5jctdxz->currentIndex();
    arr.examChannelSel =qToBigEndian(tmp_uint);

    // 脉冲最小截取脉度
    arr.pulseWidth_min = qToBigEndian(ui->lineEdit_T5mczxjhmk->text().toUInt());
    // 脉冲最大截取脉度
    arr.pulseWidth_max = qToBigEndian(ui->lineEdit_T5mczdjhmk->text().toUInt());
    // IFF信号工作模式
    tmp_uint=ui->comboBox_T5iffxhgzms->currentIndex()+1;
    arr.IFF_mode =qToBigEndian(tmp_uint);
    // 是否测向
    arr.measureFlag = ui->comboBox_T5sfcx->currentIndex();
    // 测向基线选择
    arr.measureLine = ui->lineEdit_T5cxjx->text().toUInt();
    // 校正谱通道选择
    tmp_uint=ui->comboBox_T5xzptdxz->currentIndex();
    arr.corChannelSel =qToBigEndian(tmp_uint);
    // 步进
    arr.pace = qToBigEndian(ui->lineEdit_T5bj->text().toUShort());
    // 测向门限
    arr.cx_oder=ui->lineEdit_T5cxmx->text().toUInt();
    // 敌我识别下传标志
    arr.dw_downmark=ui->checkBox_dw10_b0->isChecked()+(ui->checkBox_dw10_b1->isChecked()<<1)+(ui->checkBox_dw10_b2->isChecked()<<2)
            +(ui->checkBox_dw10_b3->isChecked()<<3)+(ui->checkBox_dw10_b4->isChecked()<<4)+(ui->checkBox_dw10_b5->isChecked()<<5)
            +(ui->checkBox_dw10_b6->isChecked()<<6)+(ui->checkBox_dw10_b7->isChecked()<<7);
    // 校正方式
    arr.jz_mand=ui->comboBox_dw11->currentIndex()+1;
    // 搜索区域宽度 6.27新加
    arr.sskd=ui->lineEdit_dw12->text().toUInt();



    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &arr, sizeof(DW_Signal_Ctrl));
    return databuff;
}

// 铱星信号频点控守
uchar *sub1553_Overheadtask::mode_yxxhpdks_6(int &strlen) {
    YX_Signal_Ctrl ptr;
    memset(&ptr,0,sizeof(ptr));
    strlen=sizeof(YX_Signal_Ctrl);
    //检测通道选择
    uint tmp_uint=0;
    tmp_uint=ui->comboBox_checkadchoose->currentIndex();
    ptr.DeTEctionChannel=qToBigEndian(tmp_uint);
    //突发时长 目前固定8ms
    ptr.uptimeon=ui->lineEdit_6yx_2->text().toInt();
    //检测门限 单位dB
    ptr.jc_door=ui->lineEdit_6yx_3->text().toInt();
    // 是否测向
    ptr.measureFlag = ui->comboBox_T6sfcx->currentIndex();
    //测向门限
    ptr.cxmx=ui->lineEdit_T6cxmx->text().toUInt();
    //测向校正方式
    ptr.jz_manner=ui->comboBox_T6jzfs->currentIndex()+1;
    //相关系数
    ptr.relationData=ui->lineEdit_6yx_7->text().toUInt();
    //特征模板选择
    ptr.tzmode=ui->lineEdit_6yx_8->text().toUInt();
    //Bit判决标志
    ptr.bitJudge=ui->comboBox_6yx_9->currentIndex();

    //通道屏蔽
    uint tmp=sizeof (ptr.ch_shield)*8;//32字节*8位
    for (uint i=0;i<tmp;i++) {
        int a=7-(i%8);
        int data=ui->tableWidget_6yxch256->item(i,1)->text().toInt();
        ptr.ch_shield[i/8]+=(uchar)data<<a;

    }

    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &ptr, sizeof( YX_Signal_Ctrl));
    return databuff;
}


// 海事信号频点控守
uchar *sub1553_Overheadtask::mode_hsxhpdks_7(int &strlen) {
    HS_Signal_Ctrl ptr;
    Q_UNUSED(ptr);
    strlen =0;


    return nullptr;
}

// 雷达信号频点控守
uchar *sub1553_Overheadtask::mode_ldxhpdks_8(int &strlen) {
    Radar_Siganl_Ctrl arr;
    memset(&arr,0,sizeof (Radar_Siganl_Ctrl));
    strlen =sizeof(arr);

    //接收机频率 KHz
    arr.reFre=qToBigEndian(ui->lineEdit_LDpdks_1->text().toUInt());
    //NCO频率 单位，Hz
    arr.ncoFre=qToBigEndian(ui->lineEdit_LDpdks_2->text().toInt());
    //FPGA检测门限
    arr.fpgaDoor=ui->lineEdit_LDpdks_3->text().toInt();
    //下行数据选择
    arr.downchoose=ui->checkBox_LDpdks_4bit0->isChecked()+
            (ui->checkBox_LDpdks_4bit1->isChecked()<<1)+
            (ui->checkBox_LDpdks_4bit2->isChecked()<<2)+
            (ui->checkBox_LDpdks_4bit3->isChecked()<<3)+
            (ui->checkBox_LDpdks_4bit6->isChecked()<<6);
    //处理板NCO频率
    arr.clb_NCO=qToBigEndian(ui->lineEdit_LDpdks_5_->text().toInt());
    //处理带宽
    arr.cl_wide=qToBigEndian(ui->lineEdit_LDpdks_6_->text().toUInt());
    //参数信息选择
    arr.csChoose=ui->comboBox_LDpdks_8->currentIndex()+1;
    //保留
    //分选任务标志
    arr.groupMark=ui->comboBox_LDpdks_5->currentIndex();
    //精分析任务标志
    arr.jfxMark=ui->checkBox_LDpdks_6bit0->isChecked()+
            (ui->checkBox_LDpdks_6bit1->isChecked()<<1);
    //侦察目标选择
    arr.zcChoose=ui->comboBox_LDpdks_7->currentIndex()+1;


    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &arr, sizeof(Radar_Siganl_Ctrl));
    return databuff;
}



// 星链信号频点控守参数
uchar *sub1553_Overheadtask::mode_xlxhpdks_9(int &strlen) {

    StarLink_Siganl_Ctrl ptr;

    memset(&ptr,0,sizeof(ptr));
    strlen=sizeof(ptr);
    //接收机频率KHz
    QString tmpstr=ui->lineEdit_tab9_xl1->text();//设置内容
    double tmp_double = tmpstr.toDouble();
    uint tmp_uint=tmp_double*1000;//输入Mhz,转换Khz
    ptr.re_fre=qToBigEndian(tmp_uint);
    //互相关与自相关比值
    ptr.hx_bz=ui->lineEdit_tab9_xl2->text().toInt();
    //双窗门限
    ptr.twoMc=ui->lineEdit_tab9_xl3->text().toInt();
    //NCO路数
    int nco_cnt=0;
    for (int n=0;n<8;n++) {
        QCheckBox *checkBox = new QCheckBox();
        checkBox=(QCheckBox *)ui->tWidget_T9xlNCO_list->cellWidget(n,1);
        bool cc=checkBox->isChecked();
        if(cc)nco_cnt++;
    }
    ui->lineEdit_tab9_xl4->setText(QString::number(nco_cnt));
    //int nco_cnt=ui->lineEdit_tab9_xl4->text().toInt();
    ptr.NCOs=nco_cnt;

    //NCO频率---多个
    int NCO[nco_cnt];
    int nxx=0;
    for (int i=0;i<8;i++) {
        QCheckBox *checkBox = new QCheckBox();
        checkBox=(QCheckBox *)ui->tWidget_T9xlNCO_list->cellWidget(i,1);
        bool cc=checkBox->isChecked();
        if(!cc)continue;
        // 起始频率(KHz)
        QString tmpstr=ui->tWidget_T9xlNCO_list->item(i,0)->text();//设置内容
        tmp_double = tmpstr.toDouble();
        tmp_uint=tmp_double*1000;//输入Khz,转换hz
        NCO[nxx]=qToBigEndian(tmp_uint);
        nxx++;
    }
    strlen+=sizeof (NCO);//总长
    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &ptr, sizeof(ptr));
    memcpy(databuff+sizeof(ptr), &NCO[0], sizeof(NCO));

    return databuff;

}

//同步采样
uchar *sub1553_Overheadtask::mode_tbcy_18(int &strlen)
{
    Str_tbCy str_tbcy;
    memset(&str_tbcy,0,sizeof(str_tbcy));
    strlen=sizeof(str_tbcy);
    //接收机频率KHz
    QString tmpstr=ui->lineEdit_recfre->text();//设置内容
    double tmp_double = tmpstr.toDouble();
    uint tmp_uint=tmp_double*1000;//输入Mhz,转换Khz
    str_tbcy.re_fre=qToBigEndian(tmp_uint);
    //NCO频率Hz
    tmpstr=ui->lineEdit_ncofre->text();//设置内容
    tmp_double = tmpstr.toDouble();
    int tmp_int=tmp_double*1000;//输入Khz,转换hz
    str_tbcy.nco_fre=qToBigEndian(tmp_int);

    //采样次数
    str_tbcy.cy_cnt=ui->lineEdit_cysum->text().toInt();
    // 单次采样深度
    str_tbcy.cy_deep=ui->lineEdit_cyontime->text().toInt();


    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &str_tbcy, sizeof(str_tbcy));
    return databuff;

}

//上注软件解调
uchar *sub1553_Overheadtask::mode_up_sorft_20(int &strlen)
{
    Str_upsorft str_up;
    memset(&str_up,0,sizeof(str_up));
    strlen=sizeof(str_up);

    double tmp_d=0;
    int tmp_uint=0;
    int tmp_int=0;
    //接收机频率khz
    tmp_d=ui->lineEdit_tab11_up1->text().toDouble();
    tmp_uint=tmp_d*1000;//输入Mhz,转换Khz
    str_up.re_fre=qToBigEndian(tmp_uint);
    //频偏khz
    tmp_d=ui->lineEdit_tab11_up2->text().toDouble();
    tmp_int=tmp_d*1000;//输入Khz,转换hz
    str_up.nco_fre=qToBigEndian(tmp_int);

    // 码速率
    tmp_d=ui->lineEdit_tab11_up3->text().toDouble();
    tmp_uint=tmp_d*1000;//输入Khz,转换hz
    str_up.cy_deep=qToBigEndian(tmp_uint);

    //数据帧数
    str_up.data_cnt=qToBigEndian(ui->lineEdit_tab11szjt_4->text().toUInt());
    //样式
    str_up.ys=ui->cBox_tab11szjt_5->currentIndex();


    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &str_up, sizeof(str_up));
    return databuff;
}



//雷达信号频点扫描
uchar *sub1553_Overheadtask::mode_ldxhpdsmT_11(int &strlen) {
    Radar_Siganl_Scan arr;
    memset(&arr,0,sizeof(Radar_Siganl_Scan));
    strlen =sizeof(arr);
    //FPGA检测门限
    arr.fpgaDoor=ui->lineEdit_LDpdsm_1->text().toInt();
    //下行数据选择
    arr.downchoose=ui->checkBox_LDpdsm_2bit0->isChecked()+
            (ui->checkBox_LDpdsm_2bit1->isChecked()<<1)+
            (ui->checkBox_LDpdsm_2bit2->isChecked()<<2)+
            (ui->checkBox_LDpdsm_2bit3->isChecked()<<3)+
            (ui->checkBox_LDpdsm_2bit6->isChecked()<<6);
    //分选任务标志
    arr.groupMark=ui->comboBox_LDpdsm_3->currentIndex();
    //精分析任务标志
    arr.groupMark2=ui->checkBox_LDpdsm_7_1->isChecked()+
            (ui->checkBox_LDpdsm_7_2->isChecked()<<1);
    //侦察目标选择
    arr.zcChoose=ui->comboBox_LDpdsm_8->currentIndex()+1;
    //扫描频点个数
    int num=ui->lineEdit_LDpdsm_5->text().toInt();
    arr.smFrenum=num;
    //扫描频点驻留时间
    arr.smFreontime=ui->lineEdit_LDpdsm_6->text().toInt();
    //---循环体
    uint* Frecyc=new uint [num];
    if(num>0)
    {
        //接收机中心频率单位：KHz
        strlen+=num*4;//结构体总长度
        memset(Frecyc,0,num*4);
        for (int i=0;i<num;i++) {
            uint tmp=ui->tableWidget_LDpdsm->item(i,0)->text().toUInt();
            Frecyc[i]=qToBigEndian(tmp);
        }
    }


    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &arr, sizeof(Radar_Siganl_Scan));
    memcpy(databuff + sizeof(Radar_Siganl_Scan), Frecyc, num*4);//拷贝循环体内容
    return databuff;
}


//雷达信号频点扫描参数--设置频点个数
void sub1553_Overheadtask::on_lineEdit_LDpdsm_5_textChanged(const QString &arg1)
{
    int num=arg1.toInt();//控件个数
    //    ui->tableWidget_LDpdsm->setRowCount(0);
    //    for (int i=0;i<num;i++) {
    //        ui->tableWidget_LDpdsm->insertRow(i);
    //        ui->tableWidget_LDpdsm->setItem(i,0,new QTableWidgetItem(QString::number(0)));
    //    }

    if((num>255)||(num<1))
    {
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_LDpdsm->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_LDpdsm->insertRow(i);
            ui->tableWidget_LDpdsm->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_LDpdsm->removeRow(ui->tableWidget_LDpdsm->rowCount()-1);
        }
    }
    else {

    }
}


// 多频点快速干扰
uchar *sub1553_Overheadtask::mode_spgr_13(int &strlen) {
    TxSp_Interfere_Task_Head strSpgr;
    memset(&strSpgr,0,sizeof (strSpgr));
    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_T13jsjpl->text().toDouble()*1000;
    strSpgr.recFre = qToBigEndian(tmpI);
    // 干扰频率数(频点数≤8个)
    uint sumNum = ui->lineEdit_T13grplNum->text().toUInt();
    if(sumNum>8)
    {
        QMessageBox::warning(this,tr("错误"),tr("频点数≤8个"));
        return nullptr;
    }
    strSpgr.interfereNum = sumNum;

    // 变长数据
    if (sumNum > 8) sumNum = 8;
    strlen = sizeof (strSpgr) + sumNum * sizeof(TxSp_Interfere_Task);
    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &strSpgr, sizeof (strSpgr));

    for (uint i = 0; i < sumNum; i++) {
        QString tmpstr = ui->tableWidget_spgrCyc->item(i, 1)->text();
        tmpstr = tmpstr.replace(" ", "");
        int tmplen1 = (tmpstr.size() + 1) / 2;
        QByteArray hex_data =QByteArray::fromHex(tmpstr.toLatin1());  // 将字节流转换位16进制,char型
        memcpy(databuff +sizeof (strSpgr) + i * sizeof(TxSp_Interfere_Task),(uchar *)hex_data.data(), tmplen1);  // 获取地址
    }

    return databuff;
}

// 等间隔梳状谱干扰
uchar *sub1553_Overheadtask::mode_szpgr_14(int &strlen) {

    pos_intervarComb_Head ptr;
    memset(&ptr,0,sizeof (ptr));
    strlen=sizeof (ptr);
    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_T14jsjpl->text().toDouble()*1000;
    ptr.recFre = qToBigEndian(tmpI);
    // 干扰幅度
    ptr.interfereRange = qToBigEndian(ui->lineEdit_T14grfd->text().toShort());
    // 干扰样式
    ptr.interfereStyle =ui->comboBox_T14dpchoose->currentIndex();
    // 干扰参数1
    ptr.interfereParam1 = qToBigEndian(ui->lineEdit_T14_grcs1->text().toUInt());
    // 干扰参数2
    ptr.interfereParam2 = qToBigEndian(ui->lineEdit_T14_grcs2->text().toUInt());
    // 干扰参数3
    ptr.interfereParam3 = qToBigEndian((uint)ui->comboBox_T14_grcs3->currentIndex());
    // 干扰参数4
    ptr.interfereParam4 = qToBigEndian(ui->lineEdit_T14_grcs4->text().toUInt());
    // 干扰参数5
    ptr.interfereParam5 = qToBigEndian(ui->lineEdit_T14_grcs5->text().toUInt());
    // 梳状谱段数
    uchar sumNum = ui->lineEdit_szpds->text().toUInt();
    ptr.combNum = sumNum;
    if (sumNum > 20) sumNum = 20;

    pos_intervarComb_2 str_pos[sumNum];
    int aa=sizeof (str_pos);
    memset(str_pos,0,aa);
    strlen+=sizeof (str_pos);

    for(int i=0;i<sumNum;i++)
    {
        // 梳状谱幅度0.1dB
        QString tmpstr=ui->tableWidget_szp->item(i,0)->text();//设置内容
        str_pos[i].combRange=qToBigEndian(tmpstr.toShort());
        // 梳状谱中心频率hz
        tmpstr=ui->tableWidget_szp->item(i,1)->text();
        str_pos[i].combFre=qToBigEndian(tmpstr.toUInt());
        // 梳状谱干扰带宽hz
        tmpstr=ui->tableWidget_szp->item(i,2)->text();
        str_pos[i].combWidth=qToBigEndian(tmpstr.toUInt());
        // 梳状谱干扰间隔hz
        tmpstr=ui->tableWidget_szp->item(i,3)->text();
        str_pos[i].combinterval=qToBigEndian(tmpstr.toUInt());
    }
    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &ptr, sizeof(ptr));
    memcpy(databuff+sizeof(ptr), str_pos, sizeof (str_pos));

    return databuff;
}


// 非等间隔梳状谱干扰
uchar *sub1553_Overheadtask::mode_not_szpgr_15(int &strlen) {
    nav_IntervarCombk_HEAD arr;
    memset(&arr,0,sizeof(arr));
    strlen=sizeof (arr);
    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_T15jsjpl->text().toDouble()*1000;
    arr.recFre = qToBigEndian(tmpI);
    // 干扰幅度
    arr.interfereRange = qToBigEndian(ui->lineEdit_T15grfd->text().toShort());
    // 干扰样式
    arr.interfereStyle = ui->comboBox_T15grys->currentIndex();
    // 干扰参数1
    arr.interfereParam1 = qToBigEndian(ui->lineEdit_T15sps->text().toUInt());
    // 干扰参数2
    arr.interfereParam2 = qToBigEndian(ui->lineEdit_T15fsk->text().toUInt());
    // 干扰参数3
    arr.interfereParam3 = ui->comboBox_T15ml->currentIndex();
    //   干扰参数4
    arr.interfereParam4 = qToBigEndian(ui->lineEdit_T15dxscs->text().toUInt());
    //   干扰参数5
    arr.interfereParam5 = qToBigEndian(ui->lineEdit_T15initcs->text().toUInt());
    // 梳状谱频率数
    uint sum = ui->lineEdit_T15ppsum->text().toUInt();
    arr.combFreNum = qToBigEndian(sum);
    // 变长数据
    if (sum > 100)sum = 100;
    nav_IntervarComb_2 str_pos[sum];
    int aa=sizeof (str_pos);
    memset(str_pos,0,aa);
    strlen+=sizeof (str_pos);

    for(uint i=0;i<sum;i++)
    {
        // 梳状谱干扰幅度
        QString tmpstr=ui->tableWidget_szpgr->item(i,0)->text();//设置内容
        str_pos[i].comInterfereRange=qToBigEndian(tmpstr.toShort());
        // 梳状谱干扰频率
        tmpstr=ui->tableWidget_szpgr->item(i,1)->text();
        str_pos[i].comInterfereFre=qToBigEndian(tmpstr.toInt());
    }
    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(arr));
    memcpy(databuff+sizeof(arr), str_pos, sizeof (str_pos));

    return databuff;
}

// 多通道快速协同干扰
uchar *sub1553_Overheadtask::mode_dhmbgr_T16(int &strlen)
{
    target_interfere_Task arr;
    memset(&arr,0,sizeof(target_interfere_Task));
    strlen = sizeof(target_interfere_Task);
    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_T16jsjpl->text().toDouble()*1000;
    arr.recFre=qToBigEndian(tmpI);
    // 是否同步L1，L2
    arr.L1_L2=ui->comboBoxxtgr_L1_L2->currentIndex();
    //子阵1、2第一级16个干扰信号数字频率
    arr.zz1216grxhszpl=qToBigEndian(ui->lineEdit_T16zz1216grxhszpl->text().toInt());
    // 子阵3、4第一级16个干扰信号数字频率
    arr.zz3416grxhszpl=qToBigEndian(ui->lineEdit_T16zz3416grxhszpl->text().toInt());
    //子阵1、2 QPSK数字频率
    arr.zz12QPSKszpl=qToBigEndian(ui->lineEdit_T16zz12QPSKszpl->text().toInt());
    //子阵1、2 QPSK数字信号开关
    arr.zz12QPSKszxhkg=ui->comboBox_T16zz12QPSK->currentIndex();
    //子阵1、2 QPSK数字信号符号速率
    arr.zz12QPSKszxhfhsl=qToBigEndian(ui->lineEdit_T16zz12QPSKszxhfhsl->text().toInt());
    //子阵1、2 QPSK数字信号干扰幅度
    arr.zz12QPSKszxhgrfd=qToBigEndian(ui->lineEdit_T16zz12QPSKszxhgrfd->text().toShort());
    //子阵3  4 QPSK数字频率
    arr.zz34QPSKszpl=qToBigEndian(ui->lineEdit_T16zz34QPSKszpl->text().toInt());
    //子阵3、4 QPSK数字信号开关
    arr.zz34QPSKszxhkg=ui->comboBox_T16zz34QPSKszxhkg->currentIndex();
    //子阵3、4 QPSK数字信号符号速率
    arr.zz34QPSKszxhfhsl=qToBigEndian(ui->lineEdit_T16zz34QPSKszxhfhsl->text().toInt());
    //子阵3、4 QPSK数字信号干扰幅度
    arr.zz34QPSKszxhgrfd=qToBigEndian(ui->lineEdit_T16zz34QPSKszxhgrfd->text().toShort());
    //子阵1、2的16个干扰信号个数
    uint sum1=ui->lineEdit_7_T16zz1216grxhgs->text().toUInt();
    if(sum1>16)
    {
        QMessageBox::warning(this,tr("警告"),tr("子阵1、2的16个干扰信号个数应<=16"));
        sum1=16;
    }
    arr.zz1216grxhgs=sum1;
    //子阵3、4的16个干扰信号个数
    uint sum2=ui->lineEdit_T16zz3416grxhgs->text().toUInt();
    if(sum2>16)
    {
        QMessageBox::warning(this,tr("警告"),tr("子阵3、4的16个干扰信号个数应<=16"));
        sum2=16;
    }
    arr.zz3416grxhgs=sum2;

    //变长数据
    int sum=sum1+sum2;
    if (sum > 32) sum = 32;
    if(ui->tableWidget_T16bgcc->rowCount()<sum)
    {
        QMessageBox::warning(this,tr("警告"),tr("表格内容<循环体设置个数"));
        sum=ui->tableWidget_T16bgcc->rowCount();
    }

    strlen+= sum * sizeof(target_interfere_Task_2);
    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &arr, sizeof(target_interfere_Task));
    for (int i = 0; i < sum; i++) {
        QString temparr = ui->tableWidget_T16bgcc->item(i, 1)->text();
        temparr = temparr.replace(" ", "");
        int tmplen1 = (temparr.size() + 1) / 2;
        QByteArray hex_data =QByteArray::fromHex(temparr.toLatin1());  // 将字节流转换位16进制,char型
        memcpy(databuff +sizeof(target_interfere_Task) + i * sizeof(target_interfere_Task_2),(uchar *)hex_data.data(), tmplen1);  // 获取地址
    }
    return databuff;
}

//多通道多带宽协同干扰
uchar *sub1553_Overheadtask::mode_xlmbgr_T17(int &strlen)
{
    StarLink_Siganl_Task arr;
    memset(&arr,0,sizeof(StarLink_Siganl_Task));
    strlen=sizeof(arr);
    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_T17jsjpl->text().toDouble()*1000;
    arr.recFre=qToBigEndian(tmpI);
    // 干扰幅度
    arr.interfereRange=qToBigEndian(ui->lineEdit_T17grfd->text().toShort());
    // 干扰样式
    arr.interfereStyle=ui->comboBox_T17grys->currentIndex();
    // 干扰参数1(带宽/码速率）
    arr.interfereParam1=qToBigEndian(ui->lineEdit_T17grcs1->text().toUInt());
    // 干扰参数2(FSK频偏）
    arr.interfereParam2=qToBigEndian(ui->lineEdit_T17grcs2->text().toUInt());
    // 干扰参数3(码流选择）
    arr.interfereParam3=qToBigEndian(ui->lineEdit_T17grcs3->text().toUInt());
    // 干扰参数4(多项式参数）
    arr.interfereParam4=qToBigEndian(ui->lineEdit_T17grcs4->text().toUInt());
    // 干扰参数5(多项式参数）
    arr.interfereParam5=qToBigEndian(ui->lineEdit_T17grcs5->text().toUInt());
    //梳状谱1扫频开关
    arr.szp1spkg=ui->comboBox_T17szp1spkg->currentIndex();
    //梳状谱1扫频总带宽
    arr.szp1spzdk=qToBigEndian(ui->lineEdit_T17szp1spzdk->text().toUInt());
    //梳状谱1扫频速度
    arr.szp1spsd=qToBigEndian(ui->lineEdit_T17szp1spsd->text().toUInt());

    // 梳状谱段数1
    uint sum1 = ui->lineEdit_T17szpds1->text().toUInt();
    if(sum1>20)
    {
        QMessageBox::warning(this,tr("警告"),tr("梳状谱1段数个数应<=20"));
        sum1=20;
    }
    arr.szpds1 = sum1;
    // 梳状谱段数2
    //    uint sum2 = ui->lineEdit_T17szpds2->text().toUInt();
    //    if(sum2>20)
    //    {
    //        QMessageBox::warning(this,tr("警告"),tr("梳状谱2段数个数应<=20"));
    //        sum2=20;
    //    }
    //    arr.szpds2 = sum2;

    // 变长数据
    int sum;
    sum=sum1;
    if (sum > 20) sum = 20;
    if(ui->tableWidget_T17xlmbgr->rowCount()<sum)
    {
        QMessageBox::warning(this,tr("警告"),tr("表格内容<循环体设置个数"));
        sum=ui->tableWidget_T17xlmbgr->rowCount();
    }
    strlen+= sum * sizeof(StarLink_Siganl_Task_1);
    uchar *databuff = new uchar[strlen + 1];
    memset(databuff, 0, strlen);
    memcpy(databuff, &arr,sizeof(StarLink_Siganl_Task));
    for (int i = 0; i < sum; i++) {
        QString temparr = ui->tableWidget_T17xlmbgr->item(i, 1)->text();
        temparr = temparr.replace(" ", "");
        int tmplen1 = (temparr.size() + 1) / 2;
        QByteArray hex_data =QByteArray::fromHex(temparr.toLatin1());  // 将字节流转换位16进制,char型
        memcpy(databuff + sizeof(StarLink_Siganl_Task) + i * sizeof(StarLink_Siganl_Task_1),(uchar *)hex_data.data(), tmplen1);  // 获取地址
    }
    return databuff;
}


//雷达强制干扰
uchar *sub1553_Overheadtask::mode_LD_QZgr18(int &strlen)
{
    Radar_force_Task arr;
    memset(&arr,0,sizeof(Radar_force_Task));
    strlen = sizeof(Radar_force_Task);
    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_LDqzgr_1->text().toDouble()*1000;
    arr.recFre=qToBigEndian(tmpI);
    //1234通道频偏开启
    arr.fSwitch1234=ui->comboBox_LDqzgr_4->currentIndex();
    //13通道频偏
    arr.ad13fpre=qToBigEndian(ui->lineEdit_LDqzgr_2->text().toUInt());
    //24通道频偏
    arr.ad24fpre=qToBigEndian(ui->lineEdit_LDqzgr_3->text().toUInt());

    //干扰样式
    QString ss=ui->comboBox_LDqzgr_5->currentText();
    ss=ss.left(ss.indexOf("："));
    arr.grMode=ss.toUInt();
    //干扰参数1（带宽/码速率
    arr.gr_data1=qToBigEndian(ui->lineEdit_LDqzgr_6->text().toUInt());
    //干扰参数2
    arr.gr_data2=qToBigEndian(ui->lineEdit_LDqzgr_7->text().toUInt());
    //干扰频点数

    ushort num=ui->lineEdit_LDqzgr_8->text().toUShort();
    arr.gr_frenum=qToBigEndian(num);

    if(num>400)num=0;
    CYC_force_Task cycstr[num];
    for (int n=0;n<num;n++) {
        ushort tmp1=ui->tableWidget_LDqzgr->item(n,0)->text().toUShort();
        cycstr[n].px_grdB=qToBigEndian(tmp1);
        int tmp2=ui->tableWidget_LDqzgr->item(n,1)->text().toInt();
        cycstr[n].px_fre=qToBigEndian(tmp2);
    }

    strlen+=sizeof (CYC_force_Task)*num;
    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(arr));
    memcpy(databuff+sizeof(arr), &cycstr, sizeof (CYC_force_Task)*num);

    return databuff;
}
//雷达强制干扰--循环体
void sub1553_Overheadtask::on_lineEdit_LDqzgr_8_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if(num>400)
    {
        return;
    }
    ui->tableWidget_LDqzgr->setRowCount(0);
    for (int i = 0; i < num; i++) {
        ui->tableWidget_LDqzgr->insertRow(i);
        ui->tableWidget_LDqzgr->setItem(i, 0, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_LDqzgr->setItem(i, 1, new QTableWidgetItem(QString::number(0)));
    }
}

//清空
void sub1553_Overheadtask::on_pB_ckearout_clicked() {
    model_mlist->removeRows(0, model_mlist->rowCount());
}

//清空单行
void sub1553_Overheadtask::on_pB_clearOnly_clicked()
{
    if (!ui->tableView_dataout->selectionModel()->hasSelection()) {
        QMessageBox::information(NULL, "提示", "没有选中");
        return;
    }
    //单行
    QModelIndex index = ui->tableView_dataout->selectionModel()->currentIndex();
    int irow = index.row();
    if (irow < 0)return;
    else {

        model_mlist->removeRow(irow);
    }


}


// 通用任务基本信息-频段选择-改变射频通道控件参数设置
void sub1553_Overheadtask::on_comboBox_C3_currentIndexChanged(int index) {

    if (index == 0)  // L频段
    {

        // 侦察
        // 1射频通道号。。。
        ui->comboBox_D7->clear();
        QStringList list;
        list << "组1:通拨"<< "组1:通道1"<< "组1:通道2"<< "组1:通道3"<< "组1:通道4"<< "组1:通道5"<< "组1:通道6";
        ui->comboBox_D7->addItems(list);
        // 控件回归初始化
        ui->comboBox_D7->setCurrentIndex(0);

        //本振方式选择
        ui->comboBox_D4->setCurrentIndex(1);
        ui->comboBox_D4->setVisible(0);
        ui->label_36->setVisible(0);
        //一本振使用信息：
        ui->comboBox_D5_b0->setVisible(0);
        ui->lineEdit_D9_5->setVisible(0);

        // 2射频通道参数设置。。。
        ui->checkBox_D8bit0->setVisible(true);
        ui->checkBox_D8bit2->setVisible(true);
        ui->checkBox_D8bit3->setVisible(true);
        ui->comboBox_D8bit1_2->setVisible(false);
        ui->label_92->setVisible(false);
        //波束合成标志（L频段）/组件遥测数据类型（SXku频段）
        ui->label_650->setText("波束合成标志");
        ui->comboBox_D14->clear();
        ui->comboBox_D14->addItem("1：合成");
        ui->comboBox_D14->addItem("2：不合成");
        ui->comboBox_D14->setCurrentIndex(1);

        //开关矩阵选择
        ui->comboBox_D15->setVisible(true);//在L频段下
        ui->label_19->setVisible(true);

        ui->label_268->setVisible(false);//在SXKu频段下
        ui->lineEdit_D15_1->setVisible(false);
        ui->label_281->setVisible(false);
        ui->lineEdit_D15_2->setVisible(false);


        // 控件回归初始化
        ui->checkBox_D8bit0->setChecked(0);
        ui->checkBox_D8bit2->setChecked(0);
        ui->checkBox_D8bit3->setChecked(1);
        ui->comboBox_D8bit1_2->setCurrentIndex(0);
        // 3天线子阵参数。。。
        ui->label_94->setText("天线使用方式");
        ui->comboBox_D10bit5->clear();
        ui->comboBox_D10bit5->addItem("0:独立孔径");
        ui->comboBox_D10bit5->addItem("1:合成孔径");
        ui->comboBox_D10bit5->addItem("2:双孔径");
        ui->label_95->setVisible(false);
        ui->comboBox_D10bit6->setVisible(false);
        // 控件回归初始化
        ui->comboBox_D10bit5->setCurrentIndex(0);
        ui->comboBox_D10bit5->setEnabled(0);
        ui->comboBox_D10bit6->setCurrentIndex(0);
        //射频通道号
        ui->comboBox_D7_2->setCurrentIndex(0);
        ui->comboBox_D7_2->clear();
        ui->comboBox_D7_2->addItem("组2:通拨");
        ui->comboBox_D7_2->addItem("组2:通道1");
        ui->comboBox_D7_2->addItem("组2:通道2");
        ui->comboBox_D7_2->addItem("组2:通道3");
        ui->comboBox_D7_2->addItem("组2:通道4");
        ui->comboBox_D7_2->addItem("组2:通道5");
        ui->comboBox_D7_2->addItem("组2:通道6");


        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // 干扰
        //本振方式选择
        ui->label_78->setVisible(0);
        ui->comboBox_E3->setVisible(0);
        ui->comboBox_E3->setCurrentIndex(1);
        //干扰 一本振使用信息：
        ui->label_79->setVisible(0);
        ui->comboBox_gr5_b0->setVisible(0);
        ui->comboBox_gr5_b0->setCurrentIndex(0);
        // 2射频通道参数设置。。。
        ui->checkBox_E6bit0->setVisible(true);
        ui->checkBox_E6bit1->setVisible(true);
        ui->checkBox_E6bit2->setVisible(true);
        ui->checkBox_E6bit3->setVisible(true);
        ui->label_65->setVisible(false);
        ui->comboBox_D8bit1_4->setVisible(false);

        // 控件回归初始化
        ui->checkBox_E6bit0->setChecked(0);
        ui->checkBox_E6bit1->setChecked(1);
        ui->checkBox_E6bit2->setChecked(0);
        ui->checkBox_E6bit3->setChecked(1);
        // 3天线子阵参数。。。
        ui->label_115->setText("天线使用方式");
        ui->comboBox_E7bit5->clear();
        ui->comboBox_E7bit5->addItem("1:合成孔径");
        ui->comboBox_E7bit5->addItem("2:双孔径");
        ui->label_116->setVisible(false);
        ui->comboBox_E7bit6->setVisible(false);
        // 控件回归初始化
        ui->comboBox_E7bit5->setEnabled(1);
        ui->comboBox_E7bit6->setEnabled(1);
        ui->comboBox_E7bit5->setCurrentIndex(0);
        ui->comboBox_E7bit6->setCurrentIndex(0);



        //类5G L频段
        //本振方式选择
        ui->label_477->setVisible(0);
        ui->comboBox_D4_2->setVisible(0);
        ui->comboBox_D4_2->setCurrentIndex(0);
        //本振方式选择
        ui->label_478->setVisible(0);
        ui->comboBox_D5_2->setVisible(0);
        ui->comboBox_D5_2->setCurrentIndex(0);

        ui->label_509->setVisible(false);
        ui->label_510->setVisible(false);

        ui->checkBox_sxkuAmper_1->setVisible(false);
        ui->comboBox_reduceTD_1->setVisible(false);


        ui->checkBox_GSM0->setVisible(true);
        ui->checkBox_amper1_1->setVisible(true);
        ui->checkBox_amper2_1->setVisible(true);
        ui->checkBox_amper3_1->setVisible(true);

        //L段天线射频发射衰减值--L固定0
        ui->lineEdit_D11_5sj->setText("56");

        // 天线子阵参数。。。
        ui->label_626->setText("天线使用方式");
        ui->comboBox_D10b5->clear();
        ui->comboBox_D10b5->addItem("0:独立孔径");
        ui->comboBox_D10b5->addItem("1:合成孔径");
        ui->comboBox_D10b5->addItem("2:双孔径");
        ui->label_622->setVisible(false);
        ui->comboBox_D10b6->setVisible(false);
        // 控件回归初始化
        ui->comboBox_D10b5->setCurrentIndex(0);
        ui->comboBox_D10b6->setCurrentIndex(0);

        //全景任务界面表格改动
        ui->tableWidget_T1_QJlist->setItem(0,0,new QTableWidgetItem(QString::number(960)));
        ui->tableWidget_T1_QJlist->setItem(0,1,new QTableWidgetItem(QString::number(1660)));
        ui->tableWidget_T1_QJlist->setItem(0,2,new QTableWidgetItem(QString::number(0)));

    } else  // SXKu频段
    {
        // 1射频通道号。。。
        ui->comboBox_D7->clear();
        QStringList list;
        list << "组1:通拨"<< "组1:通道1,2"<< "组1:通道3,4"<< "组1:通道5,6";
        ui->comboBox_D7->addItems(list);
        // 控件回归初始化
        ui->comboBox_D7->setCurrentIndex(0);

        //本振方式选择
        ui->comboBox_D4->setCurrentIndex(1);
        ui->comboBox_D4->setVisible(1);
        ui->label_36->setVisible(1);

        //一本振使用信息：
        ui->comboBox_D5_b0->setVisible(1);
        ui->lineEdit_D9_5->setVisible(1);

        // 2射频通道参数设置。。。
        ui->checkBox_D8bit0->setVisible(false);
        ui->checkBox_D8bit2->setVisible(false);
        ui->checkBox_D8bit3->setVisible(false);
        ui->comboBox_D8bit1_2->setVisible(true);
        ui->label_92->setVisible(true);

        //开关矩阵选择
        ui->comboBox_D15->setVisible(false);//在L频段下
        ui->label_19->setVisible(false);//在L频段下

        ui->label_268->setVisible(true);//在SXKu频段下
        ui->lineEdit_D15_1->setVisible(true);
        ui->label_281->setVisible(true);
        ui->lineEdit_D15_2->setVisible(true);

        //波束合成标志（L频段）/组件遥测数据类型（SXku频段）
        ui->label_650->setText("组件遥测数据类型");
        ui->comboBox_D14->clear();
        ui->comboBox_D14->addItem("0x1F:组件移相衰减码遥测");
        ui->comboBox_D14->addItem("0xD0:组件温度遥测");
        //侦察（SXku频段） 数字波束控件隐藏，显示
        on_comboBox_D14_activated(1);

        // 控件回归初始化
        ui->checkBox_D8bit0->setChecked(0);
        ui->checkBox_D8bit2->setChecked(0);
        ui->checkBox_D8bit3->setChecked(0);
        ui->comboBox_D8bit1_2->setCurrentIndex(0);


        // 3天线子阵参数。。。
        ui->label_94->setText("子阵1,3天线使用方式");
        ui->comboBox_D10bit5->clear();
        ui->comboBox_D10bit5->addItem("0:不启用V极化合成");
        ui->comboBox_D10bit5->addItem("1:启用V极化合成");
        ui->label_95->setVisible(true);
        ui->comboBox_D10bit6->setVisible(true);
        // 控件回归初始化
        ui->comboBox_D10bit5->setCurrentIndex(0);
        ui->comboBox_D10bit5->setEnabled(1);
        ui->comboBox_D10bit6->setCurrentIndex(0);
        //射频通道号
        ui->comboBox_D7_2->setCurrentIndex(0);
        ui->comboBox_D7_2->clear();
        ui->comboBox_D7_2->addItem("组2:通拨");
        ui->comboBox_D7_2->addItem("组2:通道1和2");
        ui->comboBox_D7_2->addItem("组2:通道3和4");
        ui->comboBox_D7_2->addItem("组2:通道5和6");
        ui->comboBox_D7_2->addItem("组2:无效0xFF");


        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // 干扰
        //本振方式选择
        ui->label_78->setVisible(1);
        ui->comboBox_E3->setVisible(1);
        ui->comboBox_E3->setCurrentIndex(1);
        //干扰 一本振使用信息：
        ui->label_79->setVisible(1);
        ui->comboBox_gr5_b0->setVisible(1);
        ui->comboBox_gr5_b0->setCurrentIndex(0);
        // 2射频通道参数设置。。。
        ui->checkBox_E6bit0->setVisible(false);
        ui->checkBox_E6bit2->setVisible(false);
        ui->checkBox_E6bit3->setVisible(false);
        ui->label_65->setVisible(true);
        ui->comboBox_D8bit1_4->setVisible(true);

        // 控件回归初始化
        ui->checkBox_E6bit0->setChecked(0);
        ui->checkBox_E6bit1->setChecked(1);
        ui->checkBox_E6bit2->setChecked(0);
        ui->checkBox_E6bit3->setChecked(0);

        // 3天线子阵参数。。。
        ui->label_115->setText("子阵1,3天线使用方式");
        ui->comboBox_E7bit5->clear();
        ui->comboBox_E7bit5->addItem("0:不启用V极化合成");
        ui->comboBox_E7bit5->addItem("1:启用V极化合成");
        ui->label_116->setVisible(true);
        ui->comboBox_E7bit6->setVisible(true);
        // 控件回归初始化
        ui->comboBox_E7bit5->setEnabled(0);
        ui->comboBox_E7bit6->setEnabled(0);
        ui->comboBox_E7bit5->setCurrentIndex(1);
        ui->comboBox_E7bit6->setCurrentIndex(1);


        //类5G SXKU频段

        //类5G L频段
        //本振方式选择
        ui->label_477->setVisible(1);
        ui->comboBox_D4_2->setVisible(1);
        ui->comboBox_D4_2->setCurrentIndex(1);
        //本振方式选择
        ui->label_478->setVisible(1);
        ui->comboBox_D5_2->setVisible(1);
        ui->comboBox_D5_2->setCurrentIndex(2);

        ui->label_509->setVisible(true);
        ui->label_510->setVisible(true);

        ui->checkBox_sxkuAmper_1->setVisible(true);
        ui->comboBox_reduceTD_1->setVisible(true);


        ui->checkBox_GSM0->setVisible(false);
        ui->checkBox_amper1_1->setVisible(false);
        ui->checkBox_amper2_1->setVisible(false);
        ui->checkBox_amper3_1->setVisible(false);

        //L段天线射频发射衰减值--sxku固定0
        ui->lineEdit_D11_5sj->setText("0");

        // 3天线子阵参数。。。
        ui->label_626->setText("子阵1,3天线使用方式");
        ui->comboBox_D10b5->clear();
        ui->comboBox_D10b5->addItem("0:不启用V极化合成");
        ui->comboBox_D10b5->addItem("1:启用V极化合成");
        ui->label_622->setVisible(true);
        ui->comboBox_D10b6->setVisible(true);
        // 控件回归初始化
        ui->comboBox_D10b5->setCurrentIndex(0);
        ui->comboBox_D10b6->setCurrentIndex(0);

        //全景任务界面表格改动
        ui->tableWidget_T1_QJlist->setItem(0,0,new QTableWidgetItem(QString::number(2650)));
        ui->tableWidget_T1_QJlist->setItem(0,1,new QTableWidgetItem(QString::number(14550)));
        ui->tableWidget_T1_QJlist->setItem(0,2,new QTableWidgetItem(QString::number(100000)));
    }
}

// 功能模式切换
void sub1553_Overheadtask::on_cB_function_mode_activated(int index) {

    //快捷填充版本号
    ui->comboBox_sorftBb->setCurrentIndex(0);


    //默认控件参数
    //高算力主从选择---通用任务基本信息,侦察模式可选择主从，其他模式固定主
    if(index==0)ui->comboBox_C2->setEnabled(1);
    else{
        ui->comboBox_C2->setCurrentIndex(0);//固定主
        ui->comboBox_C2->setEnabled(0);
    }
    //频段选择----电子侦察时可选
    if(index==0)ui->comboBox_C3->setEnabled(1);
    else if((index==2)||(index==3)||(index==7)){
        ui->comboBox_C3->setCurrentIndex(1);//sxku频段
        ui->comboBox_C3->setEnabled(0);
    }
    else{
        ui->comboBox_C3->setCurrentIndex(0);//L频段
        ui->comboBox_C3->setEnabled(0);
    }
    //3:SXKu频段电子干扰 显示 ┕功率回退值(dB) ┕非单载波补偿值(dB)
    if(index==2)
    {
        ui->lineEdit_E7->setEnabled(0);
        ui->lineEdit_E7->setText("0");
        ui->label_13->setVisible(1);//┕功率回退值(dB)
        ui->lineEdit_grglht_1->setText("0");
        ui->lineEdit_grglht_1->setVisible(1);
        ui->label_267->setVisible(1);//┕非单载波补偿值(dB)
        ui->lineEdit_grfdzb_1->setText("0");
        ui->lineEdit_grfdzb_1->setVisible(1);
    }
    else {
        ui->lineEdit_E7->setEnabled(1);
        ui->lineEdit_E7->setText("0");
        ui->label_13->setVisible(0);//┕功率回退值(dB)
        ui->lineEdit_grglht_1->setText("0");
        ui->lineEdit_grglht_1->setVisible(0);
        ui->label_267->setVisible(0);//┕非单载波补偿值(dB)
        ui->lineEdit_grfdzb_1->setText("0");
        ui->lineEdit_grfdzb_1->setVisible(0);
    }


    //函数
    change_funMode(index,true);
    change_Sorft_addr(index);

}

//改变功能模式控件
void sub1553_Overheadtask::change_funMode(int index,bool getcomBox)
{
    ui->comboBox_A9->clear();       //工作模式控件
    ui->tabWidget_mess->removeTab(0);//任务基本信息
    ui->tabWidget->removeTab(0);    // 移除1个tab;

    ui->tabWidget_6->removeTab(0);  // 移除1个tab;
    ui->label_6->setText("工作模式");
    ui->tabWidget_mess->insertTab(0, ui->tab_32, "基本任务信息");  // 添加通用任务基本参数
    ui->widget_tzw->setVisible(false);
    switch (index) {
    case 0:// 电子侦察页
        ui->comboBox_A9->addItem("全景工作模式");
        ui->comboBox_A9->addItem("频点控守工作模式");
        ui->comboBox_A9->addItem("频点扫描工作模式");

        ui->tabWidget->insertTab(0, ui->tab, "电子侦察任务");  // 添加
        ui->tabWidget_6->insertTab(0, ui->tab_27, "侦察");  // 添加

        break;
    case 1:// L频段电子干扰
    case 2:// SXKu频段电子干扰
        ui->comboBox_A9->addItem("预置强制干扰工作模式");
        ui->comboBox_A9->addItem("自主侦察引导干扰工作模式");
        ui->comboBox_A9->addItem("星间/星地感知引导干扰工作模式");

        ui->tabWidget->insertTab(0, ui->tab_2, "电子干扰任务");
        ui->tabWidget_6->insertTab(0, ui->tab_28, "干扰");
        break;
    case 3://SXKu天线定标任务
        ui->comboBox_A9->addItem("SXKu频段天线发射定标模式");
        ui->comboBox_A9->addItem("SXKu频段天线接收定标模式");
        ui->tabWidget->insertTab(0, ui->tab_3_w, "Sxku天线定标");
        break;
    case 4://SAR探测
        ui->comboBox_A9->addItem("广域搜索模式");
        ui->comboBox_A9->addItem("滑动聚束模式");
        ui->comboBox_A9->addItem("条带模式");
        ui->comboBox_A9->addItem("TOP模式");
        ui->comboBox_A9->addItem("SAR定标");
        ui->comboBox_A9->addItem("低分辨率聚束模式");
        ui->tabWidget->insertTab(0, ui->tab_31, "SAR探测");
        break;
    case 5://备用导航任务
        ui->comboBox_A9->addItem("备用导航工作模式");
        ui->comboBox_A9->addItem("导航欺骗工作模式");
        ui->tabWidget->insertTab(0, ui->tab_5, "备用导航任务参数");
        ui->tabWidget_6->insertTab(0, ui->tab_33, "导航");
        break;
    case 6://L频段类5G
        ui->comboBox_A9->addItem("终端通信");
        ui->comboBox_A9->addItem("高速下传");
        ui->comboBox_A9->addItem("数据上注");
        ui->comboBox_A9->addItem("高速下传重传");
        ui->tabWidget->insertTab(0, ui->tab_6, "L频段类5G");
        ui->tabWidget_6->insertTab(0, ui->tab_34, "类5G");
        break;
    case 7://SXKu频段类5G
        ui->comboBox_A9->addItem("终端通信");
        ui->comboBox_A9->addItem("高速下传");
        ui->comboBox_A9->addItem("数据上注");
        ui->comboBox_A9->addItem("高速下传重传");
        ui->tabWidget->insertTab(0, ui->tab_6, "SXKu频段类5G");
        ui->tabWidget_6->insertTab(0, ui->tab_34, "类5G");
        break;
    case 8://J链
        ui->comboBox_A9->addItem("数据链应用模式");
        ui->tabWidget->insertTab(0, ui->tab_35, "J链");
        ui->tabWidget_6->insertTab(0, ui->tab_36, "J链");
        break;
    case 9: //扩展功能
        ui->label_6->setText("工作内核");
        ui->tabWidget_mess->removeTab(0);//任务基本信息
        ui->tabWidget_mess->insertTab(0, ui->tab_65, "拓展功能参数");  // 添加拓展功能参数
        ui->tabWidget->insertTab(0, ui->tab_67, "拓展功能");
        //ui->tabWidget_6->insertTab(0, ui->tab_71, "拓展功能");  // 添加
        ui->tabWidget_6->insertTab(0, ui->tab_27, "拓展功能");  // 添加
        ui->widget_tzw->setVisible(true);
        ui->comboBox_A9->addItem("1");
        ui->comboBox_A9->addItem("2");
        ui->comboBox_A9->addItem("3");
        ui->comboBox_A9->addItem("4");
        ui->comboBox_A9->addItem("5");
        ui->comboBox_A9->addItem("6");
        ui->comboBox_A9->addItem("7");

        break;
    default:
        //        ui->comboBox_A9->addItem("全景工作模式");
        //        ui->comboBox_A9->addItem("频点控守工作模式");
        //        ui->comboBox_A9->addItem("频点扫描工作模式");

        //        ui->tabWidget->insertTab(0, ui->tab, "电子侦察任务");
        //        ui->tabWidget_6->insertTab(0, ui->tab_27, "干扰");
        break;
    }
    if(getcomBox)//通过下拉框改变
    {
        //工作模式控件
        ui->comboBox_A9->setCurrentIndex(0);
        change_taskkind(ui->comboBox_A9->currentText(),true);
    }

}


//改变软件配置地址
void sub1553_Overheadtask::change_Sorft_addr(int curr)
{

    QComboBox *cB[8];
    cB[0]=ui->comboBox_C12;
    cB[1]=ui->comboBox_C13;
    cB[2]=ui->comboBox_C14;
    cB[3]=ui->comboBox_C15;
    cB[4]=ui->comboBox_C16;
    cB[5]=ui->comboBox_C17;
    cB[6]=ui->comboBox_C18;
    cB[7]=ui->comboBox_C19;

    switch (curr) {
    case 0:// 电子侦察页
    case 3://SXKu天线定标任务
        for (int i=0;i<2;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x0F02采集与信道化接收软件");
            cB[i]->addItem("0x0F03波束合成接收软件  ");
            cB[i]->addItem("0x0F04波束合成发射软件  ");
            cB[i]->addItem("0xEEEE卸载  ");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C12->setCurrentIndex(0);
        ui->lineEdit_C12->setText("0F02");
        ui->comboBox_C13->setCurrentIndex(2);
        ui->lineEdit_C13->setText("0F04");
        for (int i=2;i<8;i++) {
            cB[i]->clear();

            if((i==2)||(i==3)||(i==5)||(i==6))
            {
                cB[i]->addItem("0x1F01宽带信号检测和存储软件");
                cB[i]->addItem("0x1F02LINK16测向软件 ");
                cB[i]->addItem("0x1F03塔康侦测软件     ");
                cB[i]->addItem("0x1F04塔康全频段侦察软件  ");
                cB[i]->addItem("0x1F05敌我侦测软件     ");
                cB[i]->addItem("0x1F06铱星信号侦测软件   ");
                cB[i]->addItem("0x1F07海事信号侦测软件   ");
                cB[i]->addItem("0x1F08星链信号侦察软件   ");
                cB[i]->addItem("0x1F09多通道雷达信号预处理软件  ");
                cB[i]->addItem("0x1F12单通道雷达信号预处理软件  ");
                cB[i]->addItem("0xEEEE卸载  ");
                cB[i]->addItem("0xFFFF无效");
            }
            else
            {
                cB[i]->addItem("0x1D10通信信号处理软件   ");
                cB[i]->addItem("0x1D11雷达信号主处理软件  ");
                cB[i]->addItem("0xEEEE卸载  ");
                cB[i]->addItem("0xFFFF无效");
            }

            //            cB[i]->addItem("0x1F01宽带信号检测和存储软件");
            //            cB[i]->addItem("0x1F02LINK16测向软件 ");
            //            cB[i]->addItem("0x1F03塔康侦测软件     ");
            //            cB[i]->addItem("0x1F04塔康全频段侦察软件  ");
            //            cB[i]->addItem("0x1F05敌我侦测软件     ");
            //            cB[i]->addItem("0x1F06铱星信号侦测软件   ");
            //            cB[i]->addItem("0x1F07海事信号侦测软件   ");
            //            cB[i]->addItem("0x1F08星链信号侦察软件   ");
            //            cB[i]->addItem("0x1F09雷达信号预处理软件  ");
            //            cB[i]->addItem("0x1D10通信信号处理软件   ");
            //            cB[i]->addItem("0x1D11雷达信号主处理软件  ");
            //            cB[i]->addItem("0x1F02LINK16测向软件 ");
            //            cB[i]->addItem("0x1F05敌我侦测软件     ");
            //            cB[i]->addItem("0x1F09雷达信号预处理软件  ");
            //            cB[i]->addItem("0x1D10通信信号处理软件   ");
            //            cB[i]->addItem("0x1D11雷达信号主处理软件  ");
            //            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C14->setCurrentIndex(0);
        ui->lineEdit_C14->setText("1F01");
        ui->comboBox_C15->setCurrentIndex(10);
        ui->lineEdit_C15->setText("EEEE");
        ui->comboBox_C16->setCurrentIndex(2);
        ui->lineEdit_C16->setText("EEEE");
        ui->comboBox_C17->setCurrentIndex(10);
        ui->lineEdit_C17->setText("EEEE");
        ui->comboBox_C18->setCurrentIndex(10);
        ui->lineEdit_C18->setText("EEEE");
        ui->comboBox_C19->setCurrentIndex(2);
        ui->lineEdit_C19->setText("EEEE");
        break;
    case 1:// L频段电子干扰
    case 2:// SXKu频段电子干扰
        for (int i=0;i<2;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x0F02采集与信道化接收软件");
            cB[i]->addItem("0x0F03波束合成接收软件  ");
            cB[i]->addItem("0x0F04波束合成发射软件  ");
            cB[i]->addItem("0xEEEE卸载  ");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C12->setCurrentIndex(0);
        ui->lineEdit_C12->setText("0F02");
        ui->comboBox_C13->setCurrentIndex(2);
        ui->lineEdit_C13->setText("0F04");
        for (int i=2;i<8;i++) {
            cB[i]->clear();
            if((i==2)||(i==3)||(i==5)||(i==6))
            {
                cB[i]->addItem("0x2F01通信干扰处理软件      ");
                cB[i]->addItem("0x2F02导航与星链干扰处理软件   ");
                cB[i]->addItem("0x2F04雷达侦察干扰处理软件    ");
                cB[i]->addItem("0xEEEE卸载    ");
                cB[i]->addItem("0xFFFF无效");
            }
            else
            {
                cB[i]->addItem("0x2D05雷达干扰策略与控制软件   ");
                cB[i]->addItem("0x2D03通信与导航干扰策略与控制软件");
                cB[i]->addItem("0xEEEE卸载");
                cB[i]->addItem("0xFFFF无效");
            }
            //            cB[i]->addItem("0x2F01通信干扰处理软件      ");
            //            cB[i]->addItem("0x2F02导航与星链干扰处理软件   ");
            //            cB[i]->addItem("0x2D03通信与导航干扰策略与控制软件");
            //            cB[i]->addItem("0x2F04雷达侦察干扰处理软件    ");
            //            cB[i]->addItem("0x2D05雷达干扰策略与控制软件   ");
            //            cB[i]->addItem("0x2F01通信干扰处理软件      ");
            //            cB[i]->addItem("0x2F02导航与星链干扰处理软件   ");
            //            cB[i]->addItem("0x2D03通信与导航干扰策略与控制软件");
            //            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C14->setCurrentIndex(0);
        ui->lineEdit_C14->setText("2F01");
        ui->comboBox_C15->setCurrentIndex(3);
        ui->lineEdit_C15->setText("EEEE");
        ui->comboBox_C16->setCurrentIndex(1);
        ui->lineEdit_C16->setText("2D03");
        ui->comboBox_C17->setCurrentIndex(3);
        ui->lineEdit_C17->setText("EEEE");
        ui->comboBox_C18->setCurrentIndex(3);
        ui->lineEdit_C18->setText("EEEE");
        ui->comboBox_C19->setCurrentIndex(2);
        ui->lineEdit_C19->setText("EEEE");
        break;

    case 4://SAR探测
        for (int i=0;i<2;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x3F41调频源软件 ");
            cB[i]->addItem("0x3F42数据形成软件");
            cB[i]->addItem("0xEEEE卸载");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C12->setCurrentIndex(1);
        ui->lineEdit_C12->setText("3F42");
        ui->comboBox_C13->setCurrentIndex(0);
        ui->lineEdit_C13->setText("3F41");
        for (int i=2;i<8;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x3F01条带模式成像预处理FPGA");
            cB[i]->addItem("0x3F02条带模式方位向处理FPGA");
            cB[i]->addItem("0x3F03条带模式距离向处理FPGA");
            cB[i]->addItem("0x3F04TOPS模式成像预处理FPGA");
            cB[i]->addItem("0x3F05TOPS模式方位向处理FPGA");
            cB[i]->addItem("0x3F06TOPS模式距离向处理FPGA");
            cB[i]->addItem("0x3F07条带/TOPS模式方位向处理2FPGA");
            cB[i]->addItem("0x3F08条带/TOPS模式图像量化处理FPGA");
            cB[i]->addItem("0x3F09条带模式舰船检测FPGA");
            cB[i]->addItem("0x3F10条带模式检测精聚焦FPGA");
            cB[i]->addItem("0x3F11条带模式舰船识别FPGA");
            cB[i]->addItem("0x3F12探测成像预处理FPGA");
            cB[i]->addItem("0x3F13探测成像方位向处理FPGA");
            cB[i]->addItem("0x3F14探测成像图像量化处理FPGA");
            cB[i]->addItem("0x3F15广域搜索模式舰船检测FPGA");
            cB[i]->addItem("0x3F16广域搜索模式舰船鉴别FPGA");
            cB[i]->addItem("0x3F17广域搜索模式舰船二分类FPGA");
            cB[i]->addItem("0xEEEE卸载");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C14->setCurrentIndex(11);
        ui->lineEdit_C14->setText("3F12");
        ui->comboBox_C15->setCurrentIndex(13);
        ui->lineEdit_C15->setText("3F14");
        ui->comboBox_C16->setCurrentIndex(0);
        ui->lineEdit_C16->setText("3F01");
        ui->comboBox_C17->setCurrentIndex(15);
        ui->lineEdit_C17->setText("3F16");
        ui->comboBox_C18->setCurrentIndex(14);
        ui->lineEdit_C18->setText("3F15");
        ui->comboBox_C19->setCurrentIndex(0);
        ui->lineEdit_C19->setText("3F01");
        break;
    case 5://备用导航任务
        for (int i=0;i<2;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x0F02采集与信道化接收软件");
            cB[i]->addItem("0x0F03波束合成接收软件  ");
            cB[i]->addItem("0x0F04波束合成发射软件  ");
            cB[i]->addItem("0xEEEE卸载  ");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C12->setCurrentIndex(0);
        ui->lineEdit_C12->setText("0F02");
        ui->comboBox_C13->setCurrentIndex(2);
        ui->lineEdit_C13->setText("0F04");
        for (int i=2;i<8;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x4D01星历拟合与控制软件");
            cB[i]->addItem("0x4F02导航信号生成软件 ");
            cB[i]->addItem("0xEEEE卸载 ");
            cB[i]->addItem("0xFFFF无效");

        }
        ui->comboBox_C14->setCurrentIndex(1);
        ui->lineEdit_C14->setText("4F02");
        ui->comboBox_C15->setCurrentIndex(2);
        ui->lineEdit_C15->setText("EEEE");
        ui->comboBox_C16->setCurrentIndex(0);
        ui->lineEdit_C16->setText("4D01");
        ui->comboBox_C17->setCurrentIndex(2);
        ui->lineEdit_C17->setText("EEEE");
        ui->comboBox_C18->setCurrentIndex(2);
        ui->lineEdit_C18->setText("EEEE");
        ui->comboBox_C19->setCurrentIndex(2);
        ui->lineEdit_C19->setText("EEEE");
        break;
    case 6://L频段类5G
    case 7://SXKu频段类5G
        for (int i=0;i<2;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x0F02采集与信道化接收软件");
            cB[i]->addItem("0x0F03波束合成接收软件  ");
            cB[i]->addItem("0x0F04波束合成发射软件  ");
            cB[i]->addItem("0xEEEE卸载");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C12->setCurrentIndex(0);
        ui->lineEdit_C12->setText("0F02");
        ui->comboBox_C13->setCurrentIndex(2);
        ui->lineEdit_C13->setText("0F04");
        for (int i=2;i<8;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x5F01类5G通信软件  ");
            cB[i]->addItem("0x5D02类5G协议控制软件");
            cB[i]->addItem("0xEEEE卸载");
            cB[i]->addItem("0xFFFF无效");

        }
        ui->comboBox_C14->setCurrentIndex(0);
        ui->lineEdit_C14->setText("5F01");
        ui->comboBox_C15->setCurrentIndex(0);
        ui->lineEdit_C15->setText("5F01");
        ui->comboBox_C16->setCurrentIndex(1);
        ui->lineEdit_C16->setText("5D02");
        ui->comboBox_C17->setCurrentIndex(0);
        ui->lineEdit_C17->setText("5F01");
        ui->comboBox_C18->setCurrentIndex(0);
        ui->lineEdit_C18->setText("5F01");
        ui->comboBox_C19->setCurrentIndex(1);
        ui->lineEdit_C19->setText("5D02");
        break;
    case 8://J链
        for (int i=0;i<2;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x0F02采集与信道化接收软件");
            cB[i]->addItem("0x0F03波束合成接收软件  ");
            cB[i]->addItem("0x0F04波束合成发射软件  ");
            cB[i]->addItem("0xEEEE卸载");
            cB[i]->addItem("0xFFFF无效");
        }
        ui->comboBox_C12->setCurrentIndex(0);
        ui->lineEdit_C12->setText("0F02");
        ui->comboBox_C13->setCurrentIndex(2);
        ui->lineEdit_C13->setText("0F04");
        for (int i=2;i<8;i++) {
            cB[i]->clear();
            cB[i]->addItem("0x6F01数据链信号处理软件");
            cB[i]->addItem("0x6D02数据链信息处理软件");
            cB[i]->addItem("0xEEEE卸载");
            cB[i]->addItem("0xFFFF无效");

        }
        ui->comboBox_C14->setCurrentIndex(0);
        ui->lineEdit_C14->setText("6F01");
        ui->comboBox_C15->setCurrentIndex(2);
        ui->lineEdit_C15->setText("EEEE");
        ui->comboBox_C16->setCurrentIndex(1);
        ui->lineEdit_C16->setText("6D02");
        ui->comboBox_C17->setCurrentIndex(2);
        ui->lineEdit_C17->setText("EEEE");
        ui->comboBox_C18->setCurrentIndex(2);
        ui->lineEdit_C18->setText("EEEE");
        ui->comboBox_C19->setCurrentIndex(2);
        ui->lineEdit_C19->setText("EEEE");
        break;
    default:
        break;
    }
}
//频率对应输出衰减值
void sub1553_Overheadtask::fre_dBm()
{

    //MHz
    Map_fredBm["3000"] =3 ;
    Map_fredBm["3100"] =4 ;
    Map_fredBm["3200"] =4 ;
    Map_fredBm["3300"] =5 ;
    Map_fredBm["3400"] =5 ;
    Map_fredBm["3500"] =6 ;
    Map_fredBm["3600"] =6 ;
    Map_fredBm["3700"] =6 ;
    Map_fredBm["3800"] =6 ;
    Map_fredBm["3900"] =6 ;
    Map_fredBm["4000"] =6 ;
    Map_fredBm["4100"] =7 ;
    Map_fredBm["4200"] =8 ;
    Map_fredBm["4300"] =8 ;
    Map_fredBm["4400"] =9 ;
    Map_fredBm["4500"] =10;
    Map_fredBm["4600"] =10;
    Map_fredBm["4700"] =10;
    Map_fredBm["4800"] =11;
    Map_fredBm["4900"] =11;
    Map_fredBm["5000"] =11;
    Map_fredBm["5100"] =12;
    Map_fredBm["5200"] =12;
    Map_fredBm["5300"] =12;
    Map_fredBm["5400"] =12;
    Map_fredBm["5500"] =12;
    Map_fredBm["5600"] =12;
    Map_fredBm["5700"] =12;
    Map_fredBm["5800"] =12;
    Map_fredBm["5900"] =12;
    Map_fredBm["6000"] =12;
    Map_fredBm["6100"] =12;
    Map_fredBm["6200"] =12;
    Map_fredBm["6300"] =11;
    Map_fredBm["6400"] =11;
    Map_fredBm["6500"] =10;
    Map_fredBm["6600"] =11;
    Map_fredBm["6700"] =11;
    Map_fredBm["6800"] =12;
    Map_fredBm["6900"] =12;
    Map_fredBm["7000"] =12;
    Map_fredBm["7100"] =12;
    Map_fredBm["7200"] =12;
    Map_fredBm["7300"] =12;
    Map_fredBm["7400"] =12;
    Map_fredBm["7500"] =12;
    Map_fredBm["7600"] =13;
    Map_fredBm["7700"] =13;
    Map_fredBm["7800"] =13;
    Map_fredBm["7900"] =13;
    Map_fredBm["8000"] =13;
    Map_fredBm["8100"] =13;
    Map_fredBm["8200"] =13;
    Map_fredBm["8300"] =13;
    Map_fredBm["8400"] =12;
    Map_fredBm["8500"] =12;
    Map_fredBm["8600"] =12;
    Map_fredBm["8700"] =12;
    Map_fredBm["8800"] =11;
    Map_fredBm["8900"] =11;
    Map_fredBm["9000"] =10;
    Map_fredBm["9100"] =10;
    Map_fredBm["9200"] =10;
    Map_fredBm["9300"] =9 ;
    Map_fredBm["9400"] =9 ;
    Map_fredBm["9500"] =9 ;
    Map_fredBm["9600"] =9 ;
    Map_fredBm["9700"] =8 ;
    Map_fredBm["9800"] =8 ;
    Map_fredBm["9900"] =8 ;
    Map_fredBm["10000"]=8 ;
    Map_fredBm["10100"]=8 ;
    Map_fredBm["10200"]=8 ;
    Map_fredBm["10300"]=8 ;
    Map_fredBm["10400"]=8 ;
    Map_fredBm["10500"]=8 ;
    Map_fredBm["10600"]=8 ;
    Map_fredBm["10700"]=8 ;
    Map_fredBm["10800"]=8 ;
    Map_fredBm["10900"]=8 ;
    Map_fredBm["11000"]=8 ;
    Map_fredBm["11100"]=8 ;
    Map_fredBm["11200"]=8 ;
    Map_fredBm["11300"]=8 ;
    Map_fredBm["11400"]=8 ;
    Map_fredBm["11500"]=8 ;
    Map_fredBm["11600"]=8 ;
    Map_fredBm["11700"]=8 ;
    Map_fredBm["11800"]=8 ;
    Map_fredBm["11900"]=8 ;
    Map_fredBm["12000"]=8 ;
    Map_fredBm["12100"]=8 ;
    Map_fredBm["12200"]=8 ;
    Map_fredBm["12300"]=8 ;
    Map_fredBm["12400"]=8 ;
    Map_fredBm["12500"]=8 ;


}



//改变任务类型控件
void sub1553_Overheadtask::change_taskkind(QString str,bool getcomBox)
{
    QString arg1=str;
    ui->cB_task_modetype->clear();
    if(arg1=="全景工作模式")//第一的界面的“工作模式下拉框”
    {
        ui->cB_task_modetype->addItem("1:全景扫描");
    }
    else if(arg1=="频点控守工作模式")
    {
        ui->cB_task_modetype->addItem("1:常规信号频点控守");
        ui->cB_task_modetype->addItem("2:Link16信号频点控守");
        ui->cB_task_modetype->addItem("3:塔康信号频点控守");
        ui->cB_task_modetype->addItem("4:敌我识别信号频点控守");
        ui->cB_task_modetype->addItem("5:铱星信号频点控守");
        ui->cB_task_modetype->addItem("6:海事信号频点控守");
        ui->cB_task_modetype->addItem("7:雷达信号频点控守");
        ui->cB_task_modetype->addItem("8:星链信号频点控守");
        ui->cB_task_modetype->addItem("9:同步采样");
        ui->cB_task_modetype->addItem("10:上注软件解调");
    }
    else if(arg1=="频点扫描工作模式")
    {
        ui->cB_task_modetype->addItem("1:雷达信号频点扫描");
    }
    else if(arg1=="预置强制干扰工作模式")
    {
        ui->cB_task_modetype->addItem("1:多频点快速干扰");
        ui->cB_task_modetype->addItem("2:等间隔梳状谱干扰");
        ui->cB_task_modetype->addItem("3:非等间隔梳状谱干扰");
        ui->cB_task_modetype->addItem("4:多通道快速协同干扰");
        ui->cB_task_modetype->addItem("5:多通道多带宽协同干扰");
        ui->cB_task_modetype->addItem("6:雷达强制干扰");
    }
    else if(arg1=="自主侦察引导干扰工作模式")
    {
        ui->cB_task_modetype->addItem("1:雷达侦察干扰");
    }
    else if(arg1=="星间/星地感知引导干扰工作模式")
    {
        ui->cB_task_modetype->addItem("1:星间/星地感知引导干扰");
    }
    else if(arg1=="备用导航工作模式")
    {
        ui->cB_task_modetype->addItem("1:备用导航任务参数");
    }
    else if((arg1=="终端通信")||(arg1=="高速下传")||(arg1=="数据上注")||(arg1=="高速下传重传"))
    {
        ui->cB_task_modetype->addItem("1:类5G模式参数");
    }
    else if(arg1=="数据链应用模式")
    {
        ui->cB_task_modetype->addItem("1:J链任务模式参数");
    }
    //SAR工作模式改变 地址内容
    else if(arg1=="广域搜索模式")
    {
        change_sarAddr(1);
    }
    else if(arg1=="滑动聚束模式")
    {
        change_sarAddr(2);
    }
    else if(arg1=="条带模式")
    {
        change_sarAddr(3);
    }
    else if(arg1=="TOP模式")
    {
        change_sarAddr(4);
    }
    else if(arg1=="SAR定标")
    {
        change_sarAddr(5);
    }
    else if(arg1=="低分辨率聚束模式")
    {
        change_sarAddr(5);
    }

    else{}

    if(getcomBox)
    {
        //任务模式类型控件s
        ui->cB_task_modetype->setCurrentIndex(0);
        //改任务模式类型tab随着下拉框变化
        change_tabkind(ui->cB_task_modetype->currentText());
    }

}
//改变任务类型tab
void sub1553_Overheadtask::change_tabkind(QString str)
{
    int page=zl_kind[str]-1;
    ui->tabWidget_3->setCurrentIndex(page);
}

//qstring转16进制ushort
ushort sub1553_Overheadtask::toHex_ushort(QString qstr)
{
    QString S_tmp;
    QByteArray hex_data;
    int strlen;
    ushort tmp_ushort=0;
    S_tmp=qstr;
    S_tmp=S_tmp.replace("0x","");
    hex_data=QByteArray::fromHex(S_tmp.toLatin1());//将字节流转换位16进制,char型
    strlen=(S_tmp.size()+1)/2;
    if(strlen>2)strlen=2;

    uchar tmparr[2]={0};
    memcpy(&tmparr[2-strlen],(uchar*)hex_data.data(),strlen);//获取地址(2字节，输入1个字节需要放在低位)
    memcpy(&tmp_ushort,tmparr,sizeof (tmparr));//(2字节，输入两个字节需要放在低位)
    return tmp_ushort;
}

uchar sub1553_Overheadtask::toHex_uchar(QString qstr)
{
    QString S_tmp;
    QByteArray hex_data;
    int strlen;
    uchar tmp_uchar=0;
    S_tmp=qstr;
    S_tmp=S_tmp.replace("0x","");
    hex_data=QByteArray::fromHex(S_tmp.toLatin1());//将字节流转换位16进制,char型
    strlen=(S_tmp.size()+1)/2;
    if(strlen>1)strlen=1;

    uchar tmparr[1]={0};
    memcpy(&tmparr,(uchar*)hex_data.data(),strlen);
    memcpy(&tmp_uchar,tmparr,sizeof (tmparr));
    return tmp_uchar;
}

uint sub1553_Overheadtask::toHex_uint(QString qstr)
{
    QString S_tmp;
    QByteArray hex_data;
    int strlen;
    uint tmp_uint=0;
    S_tmp=qstr;
    S_tmp=S_tmp.replace("0x","");
    hex_data=QByteArray::fromHex(S_tmp.toLatin1());//将字节流转换位16进制,char型
    strlen=(S_tmp.size()+1)/2;
    if(strlen>4)strlen=4;

    uchar tmparr[4]={0};
    memcpy(&tmparr[4-strlen],(uchar*)hex_data.data(),strlen);//获取地址(4字节，输入1个字节需要放在低位)
    memcpy(&tmp_uint,tmparr,sizeof (tmparr));//(4字节，输入两个字节需要放在低位)
    return tmp_uint;
}


// 工作模式
void sub1553_Overheadtask::on_comboBox_A9_activated(const QString &arg1)
{
    change_taskkind(arg1,true);


}

//任务模式类型改变控件
void sub1553_Overheadtask::on_cB_task_modetype_activated(const QString &arg1)
{
    change_tabkind(arg1);

}


// 子阵1扫描模式
void sub1553_Overheadtask::on_cB_elecZC_contrlmode_activated(int index) {
    switch (index) {
    case 0:
        ui->tabWidget_2->clear();
        ui->tabWidget_2->insertTab(0,ui->tab_115,"指向驻留模式");
        //侦察 当天线子阵控制模式为1、2时，本字段无效。---(天线控制间隔时间ms)
        ui->label_42->setVisible(0);
        ui->lineEdit_D11->setVisible(0);
        break;
    case 1:
        ui->tabWidget_2->clear();
        ui->tabWidget_2->insertTab(0,ui->tab_116,"指向扫描模式");
        ui->label_42->setVisible(0);
        ui->lineEdit_D11->setVisible(0);
        break;
    case 2:
        ui->tabWidget_2->clear();
        ui->tabWidget_2->insertTab(0,ui->tab_7,"区域凝视模式");
        ui->label_42->setVisible(1);
        ui->lineEdit_D11->setVisible(1);
        break;
    case 3:
        ui->tabWidget_2->clear();
        ui->tabWidget_2->insertTab(0,ui->tab_8,"区域扫描模式");
        ui->label_42->setVisible(1);
        ui->lineEdit_D11->setVisible(1);
        break;
    default:
        break;
    }
}
// 子阵2扫描模式
void sub1553_Overheadtask::on_cB_elecZC_contrlmode_Z2_activated(int index) {
    switch (index) {
    case 0:
        ui->tabWidget_8->clear();
        ui->tabWidget_8->insertTab(0,ui->tab_45,"指向驻留模式");
        break;
    case 1:
        ui->tabWidget_8->clear();
        ui->tabWidget_8->insertTab(0,ui->tab_46,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_8->clear();
        ui->tabWidget_8->insertTab(0,ui->tab_47,"区域凝视模式");

        break;
    case 3:
        ui->tabWidget_8->clear();
        ui->tabWidget_8->insertTab(0,ui->tab_48,"区域扫描模式");

        break;
    default:
        break;
    }
}

// 子阵3扫描模式
void sub1553_Overheadtask::on_cB_elecZC_contrlmode_Z3_activated(int index) {
    switch (index) {
    case 0:
        ui->tabWidget_9->clear();
        ui->tabWidget_9->insertTab(0,ui->tab_49,"区域扫描模式");
        break;
    case 1:
        ui->tabWidget_9->clear();
        ui->tabWidget_9->insertTab(0,ui->tab_50,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_9->clear();
        ui->tabWidget_9->insertTab(0,ui->tab_51,"区域凝视模式");
        break;
    case 3:
        ui->tabWidget_9->clear();
        ui->tabWidget_9->insertTab(0,ui->tab_52,"区域扫描模式");
        break;
    default:
        break;
    }
}
// 子阵4扫描模式
void sub1553_Overheadtask::on_cB_elecZC_contrlmode_Z4_activated(int index) {
    switch (index) {
    case 0:
        ui->tabWidget_10->clear();
        ui->tabWidget_10->insertTab(0,ui->tab_53,"区域扫描模式");
        break;
    case 1:
        ui->tabWidget_10->clear();
        ui->tabWidget_10->insertTab(0,ui->tab_54,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_10->clear();
        ui->tabWidget_10->insertTab(0,ui->tab_55,"区域凝视模式");
        break;
    case 3:
        ui->tabWidget_10->clear();
        ui->tabWidget_10->insertTab(0,ui->tab_56,"区域扫描模式");
        break;
    default:
        break;
    }
}


// 通信干扰快速多目标/多频点快速干扰 参数添加到列表
void sub1553_Overheadtask::on_pushButton_addQWidget_clicked() {

    if((ui->lineEdit_T13grplNum->text().toUInt()+1)>8)
    {
        QMessageBox::warning(this,tr("错误"),tr("干扰频率数<8"));
        return;
    }
    TxSp_Interfere_Task InterfereStr;
    memset(&InterfereStr, 0, sizeof(InterfereStr));

    uint tmp_uint=0;
    // 数字频率
    InterfereStr.digitFre = qToBigEndian(ui->lineEdit_T13szpl->text().toInt());
    // 模式选择
    InterfereStr.modeSelect =qToBigEndian((uint)ui->comboBox_T13dpchoose->currentIndex()+1);
    // 扫频带宽
    InterfereStr.scanWidth = qToBigEndian(ui->lineEdit_T13spdk->text().toUInt());
    // 扫频间隔
    InterfereStr.scanInterval =qToBigEndian(ui->lineEdit_T13spjg->text().toUInt());
    // 扫频驻留时间
    InterfereStr.scanStandTime =qToBigEndian(ui->lineEdit_T13spzltime->text().toUInt());
    // 干扰幅度
    InterfereStr.interfereRange =qToBigEndian(ui->lineEdit_T13grfd->text().toShort());
    // 干扰样式
    InterfereStr.interfereStyle = ui->comboBox_T13grys->currentIndex();
    // 干扰参数1(带宽/码速率）
    InterfereStr.interfereParam1 =qToBigEndian(ui->lineEdit_T13dk_sps->text().toUInt());
    // 干扰参数2(FSK频偏）
    InterfereStr.interfereParam2 =qToBigEndian(ui->lineEdit_T13pp->text().toUInt());
    // 干扰参数3(码流选择）
    tmp_uint=ui->comboBox_T13ml->currentIndex();
    InterfereStr.interfereParam3 =qToBigEndian(tmp_uint);
    // 干扰参数4(多项式参数）
    InterfereStr.interfereParam4 =qToBigEndian(ui->lineEdit_T13dxscs->text().toUInt());
    // 干扰参数5(多项式参数）
    InterfereStr.interfereParam5 =qToBigEndian(ui->lineEdit_T13cshcs->text().toUInt());

    // 内容参数
    int nrow = ui->tableWidget_spgrCyc->rowCount();
    ui->lineEdit_T13grplNum->setText(QString::number(nrow + 1));
    ui->tableWidget_spgrCyc->insertRow(nrow);
    uchar *Buff = new uchar[sizeof(InterfereStr) + 1];
    memcpy(Buff, &InterfereStr, sizeof(InterfereStr));
    QString str = "";
    QString tmp_byte;
    for (uint readLen = 0; readLen < sizeof(InterfereStr); readLen++) {
        tmp_byte = QString().asprintf("%02x ", Buff[readLen]);
        str.append(tmp_byte);
    }
    //参数序号
    ui->tableWidget_spgrCyc->setItem(nrow, 0, new QTableWidgetItem(ui->lineEdit_T13szpl->text()));
    ui->tableWidget_spgrCyc->item(nrow,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //参数内容
    ui->tableWidget_spgrCyc->setItem(nrow, 1, new QTableWidgetItem(str));

    delete[] Buff;
}

// 通信干扰快速多目标/多频点快速干扰 表格清空
void sub1553_Overheadtask::on_pushButton_T13widgetClear_clicked() {
    ui->tableWidget_spgrCyc->setRowCount(0);
    ui->lineEdit_T13grplNum->setText(QString::number(0));
}



// 非等间隔梳状谱干扰 清空列表
void sub1553_Overheadtask::on_pushButton_T15listClear_clicked()
{
    int nrow = ui->tableWidget_szpgr->rowCount();
    for(int i=0;i<nrow;i++)
    {
        ui->tableWidget_szpgr->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_szpgr->setItem(i,1,new QTableWidgetItem(QString::number(0)));
    }
}

//等间隔梳状谱干扰 清空列表
void sub1553_Overheadtask::on_pushButton_T13widgetClear_3_clicked() {
    int nrow = ui->tableWidget_szp->rowCount();
    for(int i=0;i<nrow;i++)
    {
        ui->tableWidget_szp->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_szp->setItem(i,1,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_szp->setItem(i,2,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_szp->setItem(i,3,new QTableWidgetItem(QString::number(0)));
    }
}

//天线子阵改变控件
void sub1553_Overheadtask::zz_change()
{
    ui->tabWidget_7->insertTab(1, ui->tab_41, "子阵1");  // 添加
    ui->tabWidget_7->insertTab(2, ui->tab_42, "子阵2");  // 添加
    ui->tabWidget_7->insertTab(3, ui->tab_43, "子阵3");  // 添加
    ui->tabWidget_7->insertTab(4, ui->tab_44, "子阵4");  // 添加

    if(!ui->checkBox_D10bit3->isChecked())ui->tabWidget_7->removeTab(3);  // 移除;
    if(!ui->checkBox_D10bit2->isChecked())ui->tabWidget_7->removeTab(2);  // 移除;
    if(!ui->checkBox_D10bit1->isChecked())ui->tabWidget_7->removeTab(1);  // 移除;
    if(!ui->checkBox_D10bit0->isChecked())ui->tabWidget_7->removeTab(0);  // 移除;
}

void sub1553_Overheadtask::zz_change2()
{
    ui->tabWidget_7->insertTab(1, ui->tab_41, "子阵1");  // 添加
    ui->tabWidget_7->insertTab(2, ui->tab_42, "子阵2");  // 添加
    ui->tabWidget_7->insertTab(3, ui->tab_43, "子阵3");  // 添加
    ui->tabWidget_7->insertTab(4, ui->tab_44, "子阵4");  // 添加

    if(!ui->checkBox_D10bit3_3->isChecked())ui->tabWidget_7->removeTab(3);  // 移除;
    if(!ui->checkBox_D10bit2_3->isChecked())ui->tabWidget_7->removeTab(2);  // 移除;
    if(!ui->checkBox_D10bit1_3->isChecked())ui->tabWidget_7->removeTab(1);  // 移除;
    if(!ui->checkBox_D10bit0_3->isChecked())ui->tabWidget_7->removeTab(0);  // 移除;
}
//备用导航天线子阵改变控件
void sub1553_Overheadtask::BYzz_change()
{
    ui->tabWidget_11->insertTab(1, ui->tab_100, "子阵1");  // 添加
    ui->tabWidget_11->insertTab(2, ui->tab_101, "子阵2");  // 添加
    ui->tabWidget_11->insertTab(3, ui->tab_102, "子阵3");  // 添加
    ui->tabWidget_11->insertTab(4, ui->tab_103, "子阵4");  // 添加

    if(!ui->checkBox_DH_TXbit3->isChecked())ui->tabWidget_11->removeTab(3);  // 移除;
    if(!ui->checkBox_DH_TXbit2->isChecked())ui->tabWidget_11->removeTab(2);  // 移除;
    if(!ui->checkBox_DH_TXbit1->isChecked())ui->tabWidget_11->removeTab(1);  // 移除;
    if(!ui->checkBox_DH_TXbit0->isChecked())ui->tabWidget_11->removeTab(0);  // 移除;
}

//天线子阵1(选择)
void sub1553_Overheadtask::on_checkBox_D10bit0_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change();
}
//天线子阵2(选择)
void sub1553_Overheadtask::on_checkBox_D10bit1_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change();
}
//天线子阵3(选择)
void sub1553_Overheadtask::on_checkBox_D10bit2_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change();
}
//天线子阵4(选择)
void sub1553_Overheadtask::on_checkBox_D10bit3_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change();
}


//多通道快速协同干扰--添加循环体内容
void sub1553_Overheadtask::on_pushButton_T16add_clicked()
{
    if(ui->tableWidget_T16bgcc->rowCount()+1>32)
    {
        QMessageBox::warning(this,tr("错误"),tr("循环体的总个数应<=32"));
        return;
    }

    target_interfere_Task_2 arr;
    memset(&arr,0,sizeof(target_interfere_Task_2));
    //数字频率
    arr.digitFre=qToBigEndian(ui->lineEdit_T16szpl->text().toInt());
    //干扰幅度
    arr.interfereRange=qToBigEndian(ui->lineEdit_T16grfd->text().toShort());
    //干扰样式
    arr.interfereStyle=ui->comboBox_T16grys->currentIndex();
    // 干扰参数1(带宽/码速率）
    arr.interfereParam1=qToBigEndian(ui->lineEdit_T16gcs1->text().toUInt());
    // 干扰参数2(FSK频偏）
    arr.interfereParam2=qToBigEndian(ui->lineEdit_T16grcs2->text().toUInt());
    // 干扰参数3(码流选择）
    arr.interfereParam3=ui->lineEdit_T16grcs3->text().toUInt();
    // 干扰参数4(多项式参数）
    arr.interfereParam4=ui->lineEdit_T16grcs4->text().toInt();
    // 干扰参数5(多项式参数）
    arr.interfereParam5=qToBigEndian(ui->lineEdit_T16grcs5->text().toUInt());
    // 内容参数
    int nrow = ui->tableWidget_T16bgcc->rowCount();

    ui->tableWidget_T16bgcc->insertRow(nrow);
    uchar *Buff = new uchar[sizeof(arr) + 1];
    memcpy(Buff, &arr, sizeof(arr));
    QString str = "";
    QString tmp_byte;
    for (uint readLen = 0; readLen < sizeof(arr); readLen++) {
        tmp_byte = QString().asprintf("%02x ", Buff[readLen]);
        str.append(tmp_byte);
    }
    // 数字频率NCO
    ui->tableWidget_T16bgcc->setItem(nrow, 0, new QTableWidgetItem(ui->lineEdit_T16szpl->text()));
    ui->tableWidget_T16bgcc->item(nrow, 0)->setTextAlignment(Qt::AlignHCenter |Qt::AlignVCenter);//居中
    // 参数内容
    ui->tableWidget_T16bgcc->setItem(nrow, 1, new QTableWidgetItem(str));
    delete[] Buff;
}


//多通道快速协同干扰 表格清除按钮
void sub1553_Overheadtask::on_pushButton_T16clear_clicked()
{
    ui->tableWidget_T16bgcc->setRowCount(0);
}

//多通道多带宽协同干扰--添加循环体
void sub1553_Overheadtask::on_pushButton_T17add_clicked()
{
    if(ui->tableWidget_T17xlmbgr->rowCount()+1>40)
    {
        QMessageBox::warning(this,tr("错误"),tr("循环体的总个数应<=40"));
        return;
    }
    StarLink_Siganl_Task_1 arr;
    memset(&arr,0,sizeof(StarLink_Siganl_Task_1));
    // 梳状谱中心频率
    arr.combFre=qToBigEndian(ui->lineEdit_T17szpzxpl->text().toInt());
    // 梳状谱干扰带宽
    arr.combWidth=qToBigEndian(ui->lineEdit_T17szpgrdk->text().toUInt());
    // 梳状谱干扰间隔
    arr.combinterval=qToBigEndian(ui->lineEdit_T17szpgrjg->text().toUInt());
    // 内容参数
    int nrow = ui->tableWidget_T17xlmbgr->rowCount();
    ui->tableWidget_T17xlmbgr->insertRow(nrow);
    uchar *Buff = new uchar[sizeof(arr) + 1];
    memcpy(Buff, &arr, sizeof(arr));
    QString str = "";
    QString tmp_byte;
    for (uint readLen = 0; readLen < sizeof(arr); readLen++) {
        tmp_byte = QString().asprintf("%02x ", Buff[readLen]);
        str.append(tmp_byte);
    }
    // 梳状谱中心频率
    ui->tableWidget_T17xlmbgr->setItem(nrow, 0, new QTableWidgetItem(ui->lineEdit_T17szpzxpl->text()));
    ui->tableWidget_T17xlmbgr->item(nrow, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // 参数内容
    ui->tableWidget_T17xlmbgr->setItem(nrow, 1, new QTableWidgetItem(str));
    delete[] Buff;
}
//多通道多带宽协同干扰--循环体表格清空
void sub1553_Overheadtask::on_pushButton_T17clear_clicked()
{
    ui->tableWidget_T17xlmbgr->setRowCount(0);
}


//任务类型确定任务流水号长度
void sub1553_Overheadtask::on_comboBox_A10_activated(int index)
{
    switch (index) {
    case 0://1：运维管控任务
        if(ui->lineEdit_A2->text().toUInt()>9999)
        {
            ui->lineEdit_A2->setText("1");
            ui->lineEdit_A3->setText("1");
        }

        //QMessageBox::warning(this,tr("错误"),tr("任务流水号范围0-9999"));
        break;
    case 1://2：自主区域任务
        if((ui->lineEdit_A2->text().toUInt()<10000)||(ui->lineEdit_A2->text().toUInt()>19999))
        {
            ui->lineEdit_A2->setText("10000");
            ui->lineEdit_A3->setText("10000");
        }
        //QMessageBox::warning(this,tr("错误"),tr("任务流水号范围10000-19999"));
        break;
    case 2://3：常规任务
        if((ui->lineEdit_A2->text().toUInt()<20000)||(ui->lineEdit_A2->text().toUInt()>65535))
        {
            ui->lineEdit_A2->setText("20000");
            ui->lineEdit_A3->setText("20000");
        }
        //QMessageBox::warning(this,tr("错误"),tr("任务流水号范围20000-65535"));
        break;
    default:
        break;
    }
}


//任务参数主界面下标改变--改变，功能模式，工作模式，任务类型模式
void sub1553_Overheadtask::on_tabWidget_3_currentChanged(int index)
{

    //功能模式控件
    map<int,int> m_funmode;
    ////电子侦察
    for(int i=0;i<12;i++)m_funmode[i]=0;
    ////电子干扰
    for(int i=12;i<20;i++)m_funmode[i]=1;//L频段电子干扰
    //for(int i=14;i<22;i++)m_funmode[i]=2;//SXKu频段电子干扰(公用不确定哪个，不改变下拉框)
    ////备用导航
    m_funmode[20]=5;
    ////类5G
    m_funmode[21]=6;//L频段
    m_funmode[22]=8;//J链

    int tmp=m_funmode[index];
    if(tmp==1)//干扰有2个类型
    {
        int t=ui->cB_function_mode->currentIndex();
        if((t!=1)&&(t!=2))ui->cB_function_mode->setCurrentIndex(t);
    }
    else if(tmp==6)//类5G有2个类型
    {
        int t=ui->cB_function_mode->currentIndex();
        if((t!=6)&&(t!=7))ui->cB_function_mode->setCurrentIndex(t);

    }
    else
    {
        ui->cB_function_mode->setCurrentIndex(tmp);//改变功能模式控件下拉值
    }


    //change_funMode(ui->cB_function_mode->currentIndex(),false);//设置工作模式控件下拉内容
    change_funMode(tmp,false);//设置工作模式控件下拉内容

    //工作模式控件--第一个界面下拉框
    map<int,int> m_workmode;
    m_workmode[0]=0;//电子侦察--全景工作模式
    for(int i=1;i<11;i++)m_workmode[i]=1;//电子侦察--频点控守工作模式
    for(int i=11;i<12;i++)m_workmode[i]=2;//电子侦察--频点扫描工作模式
    for(int i=12;i<18;i++)m_workmode[i]=0;//电子干扰--预置强制干扰工作模式
    m_workmode[18]=1;//电子干扰--自主侦察引导干扰工作模式
    m_workmode[19]=2;//电子干扰--星间/星地感知引导干扰工作模式
    m_workmode[20]=0;//备用导航任务模式参数
    m_workmode[21]=0;//类5G--初始工作模式
    m_workmode[22]=0;//J链任务模式参数--初始工作模式


    ui->comboBox_A9->setCurrentIndex(m_workmode[index]);//设置工作模式控件下拉值

    change_taskkind(ui->comboBox_A9->currentText(),false);//设置任务模式类型下拉内容

    //任务模式控件--第二个界面下拉类型控件
    map<int,int> m_taskmode;
    m_taskmode[0]=0;
    for(int i=1;i<11;i++)m_taskmode[i]=i-1;
    for(int i=11;i<12;i++)m_taskmode[i]=i-11;
    for(int i=12;i<18;i++)m_taskmode[i]=i-12;
    m_taskmode[18]=0;
    m_taskmode[19]=0;
    m_taskmode[20]=0;
    m_taskmode[21]=0;
    m_taskmode[22]=0;

    int a=m_taskmode[index];
    ui->cB_task_modetype->setCurrentIndex(a);//设置任务模式控件下拉值
}
//雷达侦察干扰
uchar *sub1553_Overheadtask::mode_LD_T19(int &strlen)
{
    Radar_Interfer_Task arr;
    memset(&arr,0,sizeof (Radar_Interfer_Task));
    strlen=sizeof (arr);


    // 接收机频率(协议Khz)Mhz
    int tmpI=ui->lineEdit_LDzzgr_1->text().toDouble()*1000;
    arr.recFre=qToBigEndian(tmpI);
    //1234通道频偏开启
    arr.fSwitch1234=ui->comboBox_LDzzgr_4->currentIndex();
    //13通道频偏Hz为单位
    arr.ad13fpre=qToBigEndian(ui->lineEdit_LDzzgr_2->text().toUInt());
    //24通道频偏Hz为单位
    arr.ad24fpre=qToBigEndian(ui->lineEdit_LDzzgr_3->text().toUInt());


    //侦察参数--侦察目标选择
    arr.zc_maskchoose=ui->comboBox_LDzzgr_5->currentIndex()+1;
    //保留字段1
    //保留字段2
    //保留字段3
    //保留字段4
    //处理板NCO频率
    arr.clb_nco=qToBigEndian(ui->lineEdit_LDzzgr_6->text().toInt());
    //处理带宽
    arr.clWide=qToBigEndian(ui->lineEdit_LDzzgr_7->text().toUInt());

    //干扰策略
    arr.gr_cl=ui->comboBox_LDzzgr_8->currentIndex()+1;
    //侦察参数--检测门限
    arr.zc_jcmx=ui->lineEdit_LDzzgr_9->text().toInt();

    //干扰参数--保护载频上限_1
    arr.gr_protecU1=qToBigEndian(ui->lineEdit_LDzzgr_10->text().toInt());
    //干扰参数--保护载频下限_1
    arr.gr_protecD1=qToBigEndian(ui->lineEdit_LDzzgr_11->text().toInt());
    //干扰参数--保护载频上限_2
    arr.gr_protecU2=qToBigEndian(ui->lineEdit_LDzzgr_12->text().toInt());
    //干扰参数--保护载频下限_2
    arr.gr_protecD2=qToBigEndian(ui->lineEdit_LDzzgr_13->text().toInt());





    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(arr));

    return databuff;
}


//5.1.3.4	备用导航任务模式参数（T41.1）
uchar *sub1553_Overheadtask::mode_BY_T21(int &strlen)
{
    SpareNavigat_Str arr;
    memset(&arr,0,sizeof (SpareNavigat_Str));
    strlen=sizeof (arr);

    //是否修改伪码
    arr.pseudo_code=ui->comboBox_T21_1->currentIndex();

    //G1多项式
    arr.G1polynomial=qToBigEndian(ui->lineEdit_T21_2->text().toUShort());
    //G1初相
    arr.G1initV=qToBigEndian(ui->lineEdit_T21_3->text().toUShort());
    //G2多项式
    arr.G2polynomial=qToBigEndian(ui->lineEdit_T21_4->text().toUShort());
    //G2初相
    arr.G2initV=qToBigEndian(ui->lineEdit_T21_5->text().toUShort());
    //信号模式
    arr.signal_mode=ui->comboBox_T21_6->currentIndex();
    //工作模式
    arr.work_mode=ui->comboBox_T21_7->currentIndex();
    //零值参数
    arr.zerodata=qToBigEndian(ui->lineEdit_T21_8->text().toUInt());


    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(arr));
    return databuff;

}

//4.3.3.5	类5G任务模式参数
uchar *sub1553_Overheadtask::mode_L5G_T22(int &strlen)
{
    L5G_Str arr;
    memset(&arr,0,sizeof (L5G_Str));
    strlen=sizeof (arr);
    //接收机频率
    arr.fre=qToBigEndian(ui->lineEdit_L5G_0->text().toUInt());
    //门限
    arr.l5_mx=qToBigEndian(ui->lineEdit_L5G_1->text().toUShort());
    //调制编码索引
    arr.codeIndex=ui->comboBox_L5G_2->currentIndex()+2;
    //DA幅度校平衰减1
    arr.DA1=ui->lineEdit_5Gda1->text().toUInt();
    //DA幅度校平衰减2
    arr.DA2=ui->lineEdit_5Gda2->text().toUInt();
    //DA幅度校平衰减3
    arr.DA3=ui->lineEdit_5Gda3->text().toUInt();
    //DA幅度校平衰减4
    arr.DA4=ui->lineEdit_5Gda4->text().toUInt();
    //保留

    //数传文件数量
    arr.fileSum=ui->lineEdit_L5G_six6->text().toUInt();

    // 频段个数
    int cycsum=ui->lineEdit_L5G_six6->text().toUInt();
    L5GStr_cycFile str_cyc[cycsum];

    if(cycsum>10)cycsum=10;
    for(int i=0;i<cycsum;i++)
    {
        memset(&str_cyc[i],0,8);
        // 起始频率(KHz)
        QString tmpstr=ui->tableWidget_L5G->item(i,0)->text();//设置内容
        tmpstr=tmpstr.replace(" ","");
        uint len=(tmpstr.size()+1)/2;
        if(len>8)len=8;
        QByteArray hex_data = QByteArray::fromHex(tmpstr.toLatin1());  // 将字节流转换位16进制,char型
        memcpy(&str_cyc[i], (uchar*)hex_data.data(), len);  // 获取地址
    }

    strlen+=sizeof (L5GStr_cycFile)*cycsum;

    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(arr));
    memcpy(databuff+sizeof(arr), &str_cyc, sizeof (L5GStr_cycFile)*cycsum);

    return databuff;
}


//J链任务模式参数
uchar *sub1553_Overheadtask::mode_J_T23(int &strlen)
{
    J_Str arr;
    memset(&arr,0,sizeof (J_Str));
    strlen=sizeof (arr);

    //卫星平台编识号
    arr.wx_mark=qToBigEndian(ui->lineEdit_J_1->text().toUShort());
    //网络设计ID
    arr.net_ID=qToBigEndian(ui->lineEdit_J_2->text().toUShort());
    //通信规划ID
    arr.tx_ID=qToBigEndian(ui->lineEdit_J_3->text().toUShort());
    //地面区域中心报告
    arr.cent_rep=ui->comboBox_J_4->currentIndex();
    //地面区域中心更新策略
    arr.cent_update=ui->comboBox_J_5->currentIndex();
    //保留
    //覆盖保障模式
    arr.fg_mode=ui->comboBox_J_6->currentIndex();
    //转发模式
    arr.zf_mode=ui->comboBox_J_7->currentIndex();
    //点频参数
    arr.dp_data=qToBigEndian(ui->lineEdit_J_9->text().toUShort());
    //跳频库号
    arr.dp_kh=ui->lineEdit_J_10->text().toUInt();
    //跳频序号
    arr.dp_xh=ui->lineEdit_J_11->text().toUInt();
    //测试模式1
    arr.test_m1=ui->comboBox_J_11->currentIndex();
    //测试模式2
    arr.test_m2=ui->comboBox_J_12->currentIndex();
    //测试模式3
    arr.test_m3=ui->comboBox_J_13->currentIndex();
    //测试模式4
    arr.test_m4=ui->comboBox_J_14->currentIndex();

    //ZHS落地IP
    QString tmpip=ui->lineEdit_J_15->text();
    QString sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.ZHS_IP[0]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.ZHS_IP[1]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.ZHS_IP[2]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    arr.ZHS_IP[3]=sss.toInt();

    //ZX落地IP
    tmpip=ui->lineEdit_J_16->text();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.ZX_IP[0]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.ZX_IP[1]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.ZX_IP[2]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    arr.ZX_IP[3]=sss.toInt();

    //卫星2平台编识号
    arr.wx2PTbh=qToBigEndian(ui->lineEdit_J_17->text().toUShort());
    //卫星2平台IP
    tmpip=ui->lineEdit_J_18->text();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.wx2PTip[0]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.wx2PTip[1]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    arr.wx2PTip[2]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    arr.wx2PTip[3]=sss.toInt();

    //过滤器选择
    arr.glChoose=ui->lineEdit_J_19->text().toUInt();
    //源NPG1
    arr.sour_NPG1=ui->lineEdit_J_20->text().toUInt();
    //源NPG2
    arr.sour_NPG2=ui->lineEdit_J_21->text().toUInt();
    //源NPG3
    arr.sour_NPG3=ui->lineEdit_J_22->text().toUInt();
    //源NPG4
    arr.sour_NPG4=ui->lineEdit_J_23->text().toUInt();
    //源NPG5
    arr.sour_NPG5=ui->lineEdit_J_24->text().toUInt();
    //源平台编识号1
    arr.PT_mark1=qToBigEndian(ui->lineEdit_J_25->text().toUShort());
    //源平台编识号2
    arr.PT_mark2=qToBigEndian(ui->lineEdit_J_26->text().toUShort());
    //源平台编识号3
    arr.PT_mark3=qToBigEndian(ui->lineEdit_J_27->text().toUShort());
    //源平台编识号4
    arr.PT_mark4=qToBigEndian(ui->lineEdit_J_28->text().toUShort());
    //源平台编识号5
    arr.PT_mark5=qToBigEndian(ui->lineEdit_J_29->text().toUShort());

    uchar *databuff = new uchar[strlen + 1];
    memcpy(databuff, &arr, sizeof(arr));

    return databuff;
}


void sub1553_Overheadtask::on_checkBox_DH_TXbit0_clicked(bool checked)
{
    Q_UNUSED(checked);
    BYzz_change();
}

void sub1553_Overheadtask::on_checkBox_DH_TXbit1_clicked(bool checked)
{
    Q_UNUSED(checked);
    BYzz_change();
}

void sub1553_Overheadtask::on_checkBox_DH_TXbit2_clicked(bool checked)
{
    Q_UNUSED(checked);
    BYzz_change();
}

void sub1553_Overheadtask::on_checkBox_DH_TXbit3_clicked(bool checked)
{
    Q_UNUSED(checked);
    BYzz_change();
}



// 备用导航子阵1扫描模式
void sub1553_Overheadtask::on_cB_elecDH_contrlmode_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_18->clear();
        ui->tabWidget_18->insertTab(0,ui->tab_74,"指向驻留模式");
        break;
    case 1:
        ui->tabWidget_18->clear();
        ui->tabWidget_18->insertTab(0,ui->tab_75,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_18->clear();
        ui->tabWidget_18->insertTab(0,ui->tab_76,"区域凝视模式");
        break;
    case 3:
        ui->tabWidget_18->clear();
        ui->tabWidget_18->insertTab(0,ui->tab_77,"区域扫描模式");
        break;
    default:
        break;
    }
}
// 备用导航子阵2扫描模式
void sub1553_Overheadtask::on_cB_elecDH_contrlmode_Z2_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_19->clear();
        ui->tabWidget_19->insertTab(0,ui->tab_79,"指向驻留模式");
        break;
    case 1:
        ui->tabWidget_19->clear();
        ui->tabWidget_19->insertTab(0,ui->tab_80,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_19->clear();
        ui->tabWidget_19->insertTab(0,ui->tab_81,"区域凝视模式");
        break;
    case 3:
        ui->tabWidget_19->clear();
        ui->tabWidget_19->insertTab(0,ui->tab_82,"区域扫描模式");
        break;
    default:
        break;
    }
}
// 备用导航子阵3扫描模式
void sub1553_Overheadtask::on_cB_elecDH_contrlmode_Z3_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_20->clear();
        ui->tabWidget_20->insertTab(0,ui->tab_84,"指向驻留模式");
        break;
    case 1:
        ui->tabWidget_20->clear();
        ui->tabWidget_20->insertTab(0,ui->tab_85,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_20->clear();
        ui->tabWidget_20->insertTab(0,ui->tab_86,"区域凝视模式");
        break;
    case 3:
        ui->tabWidget_20->clear();
        ui->tabWidget_20->insertTab(0,ui->tab_87,"区域扫描模式");
        break;
    default:
        break;
    }
}
// 备用导航子阵4扫描模式
void sub1553_Overheadtask::on_cB_elecDH_contrlmode_Z4_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_21->clear();
        ui->tabWidget_21->insertTab(0,ui->tab_89,"指向驻留模式");
        break;
    case 1:
        ui->tabWidget_21->clear();
        ui->tabWidget_21->insertTab(0,ui->tab_90,"指向扫描模式");
        break;
    case 2:
        ui->tabWidget_21->clear();
        ui->tabWidget_21->insertTab(0,ui->tab_91,"区域凝视模式");
        break;
    case 3:
        ui->tabWidget_21->clear();
        ui->tabWidget_21->insertTab(0,ui->tab_92,"区域扫描模式");
        break;
    default:
        break;
    }
}

void sub1553_Overheadtask::zizhenShow()
{
    if(ui->checkBox_D10bit0_2->isChecked())ui->tabWidget_12->insertTab(0,ui->tab_57,"子阵1");
    if(ui->checkBox_D10bit1_2->isChecked())ui->tabWidget_12->insertTab(1,ui->tab_58,"子阵2");
    if(ui->checkBox_D10bit2_2->isChecked())ui->tabWidget_12->insertTab(2,ui->tab_63,"子阵3");
    if(ui->checkBox_D10bit3_2->isChecked())ui->tabWidget_12->insertTab(3,ui->tab_68,"子阵4");
}

void sub1553_Overheadtask::on_checkBox_D10bit0_2_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_12->clear();
    zizhenShow();
}

void sub1553_Overheadtask::on_checkBox_D10bit1_2_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_12->clear();
    zizhenShow();
}

void sub1553_Overheadtask::on_checkBox_D10bit2_2_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_12->clear();
    zizhenShow();
}

void sub1553_Overheadtask::on_checkBox_D10bit3_2_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_12->clear();
    zizhenShow();
}

//选择任务模式参数-文件
void sub1553_Overheadtask::on_pB_chooseSarFile_clicked()
{
    //打开文件选择对话框
    QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt"));
    if(file_path.size() <= 0) return;
    ui->tB_widget_SARFileList->setRowCount(0);
    for(int i=0;i<file_path.size();i++)
    {
        QFileInfo fileinfo(file_path.at(i));    //读取文件
        // 内容参数
        int nrow = ui->tB_widget_SARFileList->rowCount();
        ui->tB_widget_SARFileList->insertRow(nrow);
        //文件名
        ui->tB_widget_SARFileList->setItem(nrow, 0, new QTableWidgetItem(fileinfo.fileName()));
        ui->tB_widget_SARFileList->item(nrow, 0)->setTextAlignment(Qt::AlignHCenter |Qt::AlignVCenter);//居中
        // 路径
        ui->tB_widget_SARFileList->setItem(nrow, 1, new QTableWidgetItem(file_path.at(i)));

    }
}



void sub1553_Overheadtask::on_pushButton_sarClear_clicked()
{
    ui->tB_widget_SARFileList->setRowCount(0);
}
//收发FPGA_1
void sub1553_Overheadtask::on_comboBox_C12_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C12->setText(tmp);

}
//收发FPGA_2
void sub1553_Overheadtask::on_comboBox_C13_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C13->setText(tmp);
}
//处理板A的FPGA_1
void sub1553_Overheadtask::on_comboBox_C14_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C14->setText(tmp);
}
//处理板A的FPGA_2
void sub1553_Overheadtask::on_comboBox_C15_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C15->setText(tmp);
}
//处理板A的DSP
void sub1553_Overheadtask::on_comboBox_C16_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C16->setText(tmp);
}
//处理板B的FPGA_1
void sub1553_Overheadtask::on_comboBox_C17_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C17->setText(tmp);
}
//处理板B的FPGA_2
void sub1553_Overheadtask::on_comboBox_C18_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C18->setText(tmp);
}
//处理板B的DSP
void sub1553_Overheadtask::on_comboBox_C19_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19->setText(tmp);
}




void sub1553_Overheadtask::zizhenShow_J()
{
    if(ui->checkBox_J_7b0->isChecked())ui->tabWidget_13->insertTab(0,ui->tab_59,"子阵1");
    if(ui->checkBox_J_7b1->isChecked())ui->tabWidget_13->insertTab(1,ui->tab_60,"子阵2");
    if(ui->checkBox_J_7b2->isChecked())ui->tabWidget_13->insertTab(2,ui->tab_64,"子阵3");
    if(ui->checkBox_J_7b3->isChecked())ui->tabWidget_13->insertTab(3,ui->tab_69,"子阵4");
}

//J链--天线子阵1
void sub1553_Overheadtask::on_checkBox_J_7b0_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_13->clear();
    zizhenShow_J();
}
//J链--天线子阵2
void sub1553_Overheadtask::on_checkBox_J_7b1_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_13->clear();
    zizhenShow_J();
}
//J链--天线子阵3
void sub1553_Overheadtask::on_checkBox_J_7b2_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    ui->tabWidget_13->clear();
    zizhenShow_J();
}
//J链--天线子阵4
void sub1553_Overheadtask::on_checkBox_J_7b3_stateChanged(int arg1)
{    Q_UNUSED(arg1);
     ui->tabWidget_13->clear();
      zizhenShow_J();

}


//侦察--本振方式选择
void sub1553_Overheadtask::on_comboBox_D4_currentIndexChanged(int index)
{
    if(index==0)//0：独立本振
    {
        //独立本振选择
        ui->comboBox_D5_b0->setVisible(0);
        ui->comboBox_2D5_b0->setVisible(1);
        ui->comboBox_2D5_b1->setVisible(1);
        ui->comboBox_D7_2->setVisible(1);
        ui->comboBox_D7_2->setCurrentIndex(1);
        ui->comboBox_D7->setCurrentIndex(1);//独立本振模块不能选择0通拨
        //天线子阵参数
        ui->comboBox_D10bit5->setCurrentIndex(0);
        ui->comboBox_D10bit5->setEnabled(0);
        ui->comboBox_D10bit6->setCurrentIndex(0);
        ui->comboBox_D10bit6->setEnabled(0);
    }
    else
    {
        //共本振
        ui->comboBox_D5_b0->setVisible(1);
        ui->comboBox_2D5_b0->setVisible(0);
        ui->comboBox_2D5_b1->setVisible(0);
        ui->comboBox_D7_2->setVisible(0);
        ui->comboBox_D7_2->setCurrentIndex(0);
        //天线子阵参数
        ui->comboBox_D10bit5->setCurrentIndex(0);
        ui->comboBox_D10bit5->setEnabled(1);
        ui->comboBox_D10bit6->setCurrentIndex(0);
        ui->comboBox_D10bit6->setEnabled(1);

    }
    //if(ui->comboBox_C3->currentIndex()==1)//sxku频段
    if(1)
    {
        if(index==0)//0：独立本振
        {

            ui->checkBox_D8bit0->setVisible(true);
            ui->checkBox_D8bit0->setChecked(1);
            ui->checkBox_D8bit0->setText("第一级放大器使能[0]");
            ui->checkBox_D8bit1->setText("第一级放大器使能[1]");
            ui->comboBox_D8bit1_2_2->setVisible(true);
            ui->lineEdit_D9_2->setVisible(true);

        }
        else//1：共本振
        {

            ui->checkBox_D8bit0->setVisible(false);
            ui->checkBox_D8bit0->setText("L频段GSM陷波器使能");
            ui->checkBox_D8bit1->setText("第一级放大器使能");
            ui->comboBox_D8bit1_2_2->setVisible(false);
            ui->lineEdit_D9_2->setVisible(false);
        }
    }
}

//四子阵指向是否一致
void sub1553_Overheadtask::on_comboBox_D10bit7_activated(int index)
{

    switch (index) {
    case 0://不一致
        ui->checkBox_D10bit0->setChecked(1);

        ui->checkBox_D10bit1->setChecked(0);
        ui->checkBox_D10bit1->setEnabled(1);
        ui->checkBox_D10bit2->setChecked(0);
        ui->checkBox_D10bit2->setEnabled(1);
        ui->checkBox_D10bit3->setChecked(0);
        ui->checkBox_D10bit3->setEnabled(1);

        ui->tabWidget_7->removeTab(3);  // 移除;
        ui->tabWidget_7->removeTab(2);  // 移除;
        ui->tabWidget_7->removeTab(1);  // 移除;

        ui->cB_elecZC_txnumber->setCurrentIndex(1);
        break;
    case 1://一致
        ui->checkBox_D10bit0->setChecked(1);

        ui->checkBox_D10bit1->setChecked(1);
        ui->checkBox_D10bit1->setEnabled(0);
        ui->checkBox_D10bit2->setChecked(1);
        ui->checkBox_D10bit2->setEnabled(0);
        ui->checkBox_D10bit3->setChecked(1);
        ui->checkBox_D10bit3->setEnabled(0);

        ui->tabWidget_7->removeTab(3);  // 移除;
        ui->tabWidget_7->removeTab(2);  // 移除;
        ui->tabWidget_7->removeTab(1);  // 移除;

        ui->cB_elecZC_txnumber->setCurrentIndex(0);
        break;
    default:
        break;
    }
}
//侦察，子帧1，指向扫描模式
void sub1553_Overheadtask::on_pushButton_ZZ_zz1_zxsmms_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"指向扫描模式","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    Document xlsxR(file_path);//软件关闭会显示异常关闭

    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    ui->lineEdit_DD2_2->setText(QString::number(rowsum-1));
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)ui->tableWidget_DD2->setItem(i-2,0,new QTableWidgetItem(QString::number(var.toUInt())));
                if(j==2)ui->tableWidget_DD2->setItem(i-2,1,new QTableWidgetItem(QString::number(var.toUInt())));
            }
        }

    }
}
//子帧2
void sub1553_Overheadtask::on_pushButton_ZZ_zz2_zxsmms_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"轨道姿态数据选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    Document xlsxR(file_path);//软件关闭会显示异常关闭

    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    ui->lineEdit_DD2Z2_3->setText(QString::number(rowsum-1));
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)ui->tableWidget_DD2_Z2->setItem(i-2,0,new QTableWidgetItem(QString::number(var.toUInt())));
                if(j==2)ui->tableWidget_DD2_Z2->setItem(i-2,1,new QTableWidgetItem(QString::number(var.toUInt())));
            }
        }

    }
}
//子阵3
void sub1553_Overheadtask::on_pushButton_ZZ_zz3_zxsmms_2_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"轨道姿态数据选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    Document xlsxR(file_path);//软件关闭会显示异常关闭

    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    ui->lineEdit_DD2Z3_3->setText(QString::number(rowsum-1));
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)ui->tableWidget_DD2_Z3->setItem(i-2,0,new QTableWidgetItem(QString::number(var.toUInt())));
                if(j==2)ui->tableWidget_DD2_Z3->setItem(i-2,1,new QTableWidgetItem(QString::number(var.toUInt())));
            }
        }

    }
}
//子阵4
void sub1553_Overheadtask::on_pushButton_ZZ_zz4_zxsmms_2_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"轨道姿态数据选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    Document xlsxR(file_path);//软件关闭会显示异常关闭

    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    ui->lineEdit_DD2Z4_3->setText(QString::number(rowsum-1));
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)ui->tableWidget_DD2_Z4->setItem(i-2,0,new QTableWidgetItem(QString::number(var.toUInt())));
                if(j==2)ui->tableWidget_DD2_Z4->setItem(i-2,1,new QTableWidgetItem(QString::number(var.toUInt())));
            }
        }

    }
}


//表41　全景扫描格式参数  当“采集触发方式”为0x01时，本字段有效
void sub1553_Overheadtask::on_comboBox_T1_4_currentIndexChanged(int index)
{
    if(index==1)
    {
        ui->label_73->setVisible(1);
        ui->lineEdit_T1_6->setVisible(1);

    }
    else {
        ui->label_73->setVisible(0);
        ui->lineEdit_T1_6->setVisible(0);
        ui->lineEdit_T1_6->setText("0");
    }
}
//表42　常规信号频点控守参数  当“侦察标志”为1时，本字段无效
void sub1553_Overheadtask::on_comboBox_T2_zcbz_currentIndexChanged(int index)
{
    if(index==1)
    {
        ui->label_164->setVisible(0);
        ui->lineEdit_T2csclSum->setVisible(0);
        ui->lineEdit_T2csclSum->setText("0");
        ui->label_566->setVisible(0);
        ui->comboBox_T2_iqlen->setVisible(0);
        ui->comboBox_T2_iqlen->setCurrentIndex(0);

    }
    else {
        ui->label_164->setVisible(1);
        ui->lineEdit_T2csclSum->setVisible(1);
        ui->label_566->setVisible(1);
        ui->comboBox_T2_iqlen->setVisible(1);
    }
}

//表41　全景扫描格式参数---指示后续循环体，循环体从“起始频率”到“瞬时带宽”，有效范围1-100
void sub1553_Overheadtask::on_lineEdit_T1_5_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>100)||(num<1))
    {
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_T1_QJlist->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_T1_QJlist->insertRow(i);
            ui->tableWidget_T1_QJlist->setItem(i,0,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_T1_QJlist->setItem(i,1,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_T1_QJlist->setItem(i,2,new QTableWidgetItem(QString::number(0)));
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_T1_QJlist->removeRow(ui->tableWidget_T1_QJlist->rowCount()-1);
        }
    }
    else {

    }

}
//表42　常规信号频点控守参数 --有效值1~4指示后续循环体个数，循环体为“采样信道参数”
void sub1553_Overheadtask::on_lineEdit_T2_cytxzs_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>4)||(num<1))
    {
        QMessageBox::warning(this,tr("警告"),tr("个数最大为4"));
        ui->lineEdit_T2_cytxzs->setText("4");
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_T2_cytxbg->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_T2_cytxbg->insertRow(i);
            ui->tableWidget_T2_cytxbg->setItem(i,0,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_T2_cytxbg->setItem(i,1,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_T2_cytxbg->setItem(i,2,new QTableWidgetItem(QString::number(0)));
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_T2_cytxbg->removeRow(ui->tableWidget_T2_cytxbg->rowCount()-1);
        }
    }
    else {

    }
}




void sub1553_Overheadtask::on_comboBox_E3_currentIndexChanged(int index)
{

    if(index==0)//0：独立本振
    {
        //独立本振选择
        ui->comboBox_gr5_b0->setVisible(0);
        ui->comboBox_gr5_b0_->setVisible(1);
        ui->comboBox_gr5_b1->setVisible(1);
    }
    else
    {
        //共本振
        ui->comboBox_gr5_b0->setVisible(1);
        ui->comboBox_gr5_b0_->setVisible(0);
        ui->comboBox_gr5_b1->setVisible(0);
    }
    //if(ui->comboBox_C3->currentIndex()==1)//sxku频段
    if(1)
    {
        if(index==0)//0：独立本振
        {

            ui->checkBox_E6bit0->setVisible(true);
            ui->checkBox_E6bit0->setChecked(1);
            ui->checkBox_E6bit0->setText("第一级放大器使能[0]");
            ui->checkBox_E6bit1->setText("第一级放大器使能[1]");
            ui->checkBox_E6bit1->setVisible(true);
            ui->checkBox_E6bit1->setChecked(1);
            ui->lineEdit_E7_3->setVisible(true);
            ui->lineEdit_E7_3->setText("0");
            ui->lineEdit_grglht_2->setVisible(true);//关联变化值 功率回退值
            ui->lineEdit_grglht_2->setText("0");
            ui->lineEdit_grfdzb_2->setVisible(true);//关联变化值 非单载波补偿值
            ui->lineEdit_grfdzb_2->setText("0");
            ui->lineEdit_E7_2_2->setVisible(true);
            ui->comboBox_D8bit1_4_2->setVisible(true);

        }
        else//1：共本振
        {
            ui->checkBox_E6bit0->setVisible(false);
            ui->checkBox_E6bit0->setChecked(0);
            ui->checkBox_E6bit0->setText("L频段GSM陷波器使能");
            ui->checkBox_E6bit1->setText("第一级放大器使能");
            ui->checkBox_E6bit1->setVisible(true);
            ui->checkBox_E6bit1->setChecked(1);
            ui->lineEdit_E7_3->setVisible(false);
            ui->lineEdit_E7_3->setText("0");
            ui->lineEdit_grglht_2->setVisible(false);//关联变化值 功率回退值
            ui->lineEdit_grglht_2->setText("0");
            ui->lineEdit_grfdzb_2->setVisible(false);//关联变化值 非单载波补偿值
            ui->lineEdit_grfdzb_2->setText("0");
            ui->lineEdit_E7_2_2->setVisible(false);
            ui->comboBox_D8bit1_4_2->setVisible(false);
        }
    }
}


//侦察--波束合成标志
void sub1553_Overheadtask::on_comboBox_D14_activated(int index)
{
    if(ui->comboBox_C3->currentIndex()==1)index=1;
    switch (index) {
    case 0:

        ui->label_590->setVisible(1);
        ui->lineEdit_zc_zz1lz->setVisible(1);
        ui->label_591->setVisible(1);
        ui->lineEdit_zc_zz1fw->setVisible(1);

        ui->label_592->setVisible(1);
        ui->lineEdit_zc_zz2lz->setVisible(1);
        ui->label_593->setVisible(1);
        ui->lineEdit_zc_zz2fw->setVisible(1);

        ui->label_594->setVisible(1);
        ui->lineEdit_zc_zz3lz->setVisible(1);
        ui->label_596->setVisible(1);
        ui->lineEdit_zc_zz3fw->setVisible(1);

        ui->label_597->setVisible(1);
        ui->lineEdit_zc_zz4lz->setVisible(1);
        ui->label_595->setVisible(1);
        ui->lineEdit_zc_zz4fw->setVisible(1);
        break;
    case 1:
        ui->label_590->setVisible(0);
        ui->lineEdit_zc_zz1lz->setVisible(0);
        ui->label_591->setVisible(0);
        ui->lineEdit_zc_zz1fw->setVisible(0);

        ui->label_592->setVisible(0);
        ui->lineEdit_zc_zz2lz->setVisible(0);
        ui->label_593->setVisible(0);
        ui->lineEdit_zc_zz2fw->setVisible(0);

        ui->label_594->setVisible(0);
        ui->lineEdit_zc_zz3lz->setVisible(0);
        ui->label_596->setVisible(0);
        ui->lineEdit_zc_zz3fw->setVisible(0);

        ui->label_597->setVisible(0);
        ui->lineEdit_zc_zz4lz->setVisible(0);
        ui->label_595->setVisible(0);
        ui->lineEdit_zc_zz4fw->setVisible(0);
        break;
    default:
        break;
    }
}

//干扰-天线子阵控制模式
void sub1553_Overheadtask::on_comboBox_E9_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_4->clear();
        ui->tabWidget_4->insertTab(0,ui->tab_39,"指向驻留模式");

        break;
    case 1:
        ui->tabWidget_4->clear();
        ui->tabWidget_4->insertTab(0,ui->tab_18,"指向扫描模式");

        break;
    case 2:
        ui->tabWidget_4->clear();
        ui->tabWidget_4->insertTab(0,ui->tab_24,"区域凝视模式");

        break;
    default:
        break;
    }
}
//干扰--指向扫描模式参数 读取表格
void sub1553_Overheadtask::on_pushButton_GR1_zxsm_4_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"指向扫描数据选取","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    Document xlsxR(file_path);//软件关闭会显示异常关闭

    if(!xlsxR.selectSheet("Sheet1"))
    {
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    ui->lineEdit_GR1_zxsm_3->setText(QString::number(rowsum-1));
    int colsum=xlsxR.dimension().columnCount();
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {
            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                if(j==1)ui->tableWidget_GR1_zxsm_4->setItem(i-2,0,new QTableWidgetItem(QString::number(var.toUInt())));
                if(j==2)ui->tableWidget_GR1_zxsm_4->setItem(i-2,1,new QTableWidgetItem(QString::number(var.toUInt())));
            }
        }

    }
}
//类5G 子阵1
void sub1553_Overheadtask::on_cB_L5_zz1_2_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_14->setCurrentIndex(0);
        break;
    case 2:
        ui->tabWidget_14->setCurrentIndex(1);
        break;
    default:
        break;
    }
}
//类5G 子阵2
void sub1553_Overheadtask::on_cB_L5_zz2_2_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_15->setCurrentIndex(0);
        break;
    case 2:
        ui->tabWidget_15->setCurrentIndex(1);
        break;
    default:
        break;
    }
}
//类5G 子阵3
void sub1553_Overheadtask::on_cB_L5_zz3_2_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_16->setCurrentIndex(0);
        break;
    case 2:
        ui->tabWidget_16->setCurrentIndex(1);
        break;
    default:
        break;
    }
}

//类5G 子阵4
void sub1553_Overheadtask::on_cB_L5_zz4_2_activated(int index)
{
    switch (index) {
    case 0:
        ui->tabWidget_17->setCurrentIndex(0);
        break;
    case 2:
        ui->tabWidget_17->setCurrentIndex(1);
        break;
    default:
        break;
    }
}
//备用导航 L频段天线使用方式
void sub1553_Overheadtask::on_comboBox_DHtxuse_currentIndexChanged(int index)
{
    switch (index) {
    case 0://独立孔径
        ui->checkBox_DH_TXbit0->setChecked(1);
        ui->checkBox_DH_TXbit1->setChecked(0);
        ui->checkBox_DH_TXbit2->setChecked(0);
        ui->checkBox_DH_TXbit3->setChecked(0);

        ui->tabWidget_11->clear();
        ui->tabWidget_11->insertTab(1, ui->tab_100, "子阵1");  // 添加
        ui->cB_elecDH_txnumber->setCurrentIndex(1);
        ui->lineEdit_DH_aerial_sj->setText("56");
        break;
    case 1://合成孔径
        ui->checkBox_DH_TXbit0->setChecked(1);
        ui->checkBox_DH_TXbit1->setChecked(1);
        ui->checkBox_DH_TXbit2->setChecked(1);
        ui->checkBox_DH_TXbit3->setChecked(1);
        ui->tabWidget_11->clear();
        ui->tabWidget_11->insertTab(1, ui->tab_100, "全选子阵");  // 添加
        ui->cB_elecDH_txnumber->setCurrentIndex(0);
        ui->lineEdit_DH_aerial_sj->setText("0");
        break;
    default:
        break;
    }
}

//类5G 数传文件数量
void sub1553_Overheadtask::on_lineEdit_L5G_six6_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>10)||(num<1))
    {
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_L5G->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_L5G->insertRow(i);
            ui->tableWidget_L5G->setItem(i,0,new QTableWidgetItem(QString::number(0)));

        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_L5G->removeRow(ui->tableWidget_L5G->rowCount()-1);
        }
    }
    else {

    }
}


//（电子干扰任务）功率回退值dBm（1） 对应衰减+
void sub1553_Overheadtask::on_lineEdit_grglht_1_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    int a=0;//干扰任务参数 频率对应的衰减值
    switch (ui->tabWidget_3->currentIndex()) {
    case 12://通信）多频点快速干扰
        a=Map_fredBm[ui->lineEdit_T13jsjpl->text()];
        break;
    case 13://等间隔梳状谱干扰
        a=Map_fredBm[ui->lineEdit_T14jsjpl->text()];
        break;
    case 14://非等间隔梳状谱干扰
        a=Map_fredBm[ui->lineEdit_T15jsjpl->text()];
        break;
    case 15://多通道快速协同干扰
        a=Map_fredBm[ui->lineEdit_T16jsjpl->text()];
        break;
    case 16://多通道多带宽协同干扰
        a=Map_fredBm[ui->lineEdit_T17jsjpl->text()];
        break;
    case 17://雷达强制干扰
        a=Map_fredBm[ui->lineEdit_LDqzgr_1->text()];
        break;
    default:
        break;
    }
    int b=ui->lineEdit_grglht_1->text().toInt();    //功率回退值dBm
    int c=ui->lineEdit_grfdzb_1->text().toInt();    //非单载波补偿值dBm

    int value=a+b-c;
    ui->lineEdit_E7->setText(QString::number(value));
}
//（电子干扰任务）非单载波补偿值dBm（1） 对应衰减-
void sub1553_Overheadtask::on_lineEdit_grfdzb_1_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    int a=0;//干扰任务参数 频率对应的衰减值
    switch (ui->tabWidget_3->currentIndex()) {
    case 12:
        a=Map_fredBm[ui->lineEdit_T13jsjpl->text()];
        break;
    case 13:
        a=Map_fredBm[ui->lineEdit_T14jsjpl->text()];
        break;
    case 14:
        a=Map_fredBm[ui->lineEdit_T15jsjpl->text()];
        break;
    case 15:
        a=Map_fredBm[ui->lineEdit_T16jsjpl->text()];
        break;
    case 16:
        a=Map_fredBm[ui->lineEdit_T17jsjpl->text()];
        break;
    case 17:
        a=Map_fredBm[ui->lineEdit_LDqzgr_1->text()];
        break;
    default:
        break;
    }
    int b=ui->lineEdit_grglht_1->text().toInt();    //功率回退值dBm
    int c=ui->lineEdit_grfdzb_1->text().toInt();    //非单载波补偿值dBm

    int value=a+b-c;
    ui->lineEdit_E7->setText(QString::number(value));
}
//（电子干扰任务）功率回退值dBm（2） 对应衰减+
void sub1553_Overheadtask::on_lineEdit_grglht_2_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    int a=0;//干扰任务参数 频率对应的衰减值
    switch (ui->tabWidget_3->currentIndex()) {
    case 12:
        a=Map_fredBm[ui->lineEdit_T13jsjpl->text()];
        break;
    case 13:
        a=Map_fredBm[ui->lineEdit_T14jsjpl->text()];
        break;
    case 14:
        a=Map_fredBm[ui->lineEdit_T15jsjpl->text()];
        break;
    case 15:
        a=Map_fredBm[ui->lineEdit_T16jsjpl->text()];
        break;
    case 16:
        a=Map_fredBm[ui->lineEdit_T17jsjpl->text()];
        break;
    case 17:
        a=Map_fredBm[ui->lineEdit_LDqzgr_1->text()];
        break;
    default:
        break;
    }
    int b=ui->lineEdit_grglht_2->text().toInt();    //功率回退值dBm
    int c=ui->lineEdit_grfdzb_2->text().toInt();    //非单载波补偿值dBm

    int value=a+b-c;
    ui->lineEdit_E7_3->setText(QString::number(value));
}
//（电子干扰任务）非单载波补偿值dBm（2） 对应衰减-
void sub1553_Overheadtask::on_lineEdit_grfdzb_2_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    int a=0;//干扰任务参数 频率对应的衰减值
    switch (ui->tabWidget_3->currentIndex()) {
    case 12:
        a=Map_fredBm[ui->lineEdit_T13jsjpl->text()];
        break;
    case 13:
        a=Map_fredBm[ui->lineEdit_T14jsjpl->text()];
        break;
    case 14:
        a=Map_fredBm[ui->lineEdit_T15jsjpl->text()];
        break;
    case 15:
        a=Map_fredBm[ui->lineEdit_T16jsjpl->text()];
        break;
    case 16:
        a=Map_fredBm[ui->lineEdit_T17jsjpl->text()];
        break;
    case 17:
        a=Map_fredBm[ui->lineEdit_LDqzgr_1->text()];
        break;
    default:
        break;
    }
    int b=ui->lineEdit_grglht_2->text().toInt();    //功率回退值dBm
    int c=ui->lineEdit_grfdzb_2->text().toInt();    //非单载波补偿值dBm

    int value=a+b-c;
    ui->lineEdit_E7_3->setText(QString::number(value));
}

void sub1553_Overheadtask::Change_dBm(int a)//通用实际输出衰减公式
{
    int b=ui->lineEdit_grglht_1->text().toInt();    //功率回退值dBm
    int c=ui->lineEdit_grfdzb_1->text().toInt();    //非单载波补偿值dBm
    int value=a+b-c;
    ui->lineEdit_E7->setText(QString::number(value));

    b=ui->lineEdit_grglht_2->text().toInt();    //功率回退值2  dBm
    c=ui->lineEdit_grfdzb_2->text().toInt();    //非单载波补偿值2  dBm
    value=a+b-c;
    ui->lineEdit_E7_3->setText(QString::number(value));
}


//基本任务信息内（电子干扰任务）--多频点快速干扰--频率值变化改变
void sub1553_Overheadtask::on_lineEdit_T13jsjpl_textChanged(const QString &arg1)
{

    int a=Map_fredBm[arg1];
    Change_dBm(a);

}
//基本任务信息内（电子干扰任务）--等间隔梳状谱干扰--频率值变化改变
void sub1553_Overheadtask::on_lineEdit_T14jsjpl_textChanged(const QString &arg1)
{
    int a=Map_fredBm[arg1];
    Change_dBm(a);
}
//基本任务信息内（电子干扰任务）--非等间隔梳状谱干扰--频率值变化改变
void sub1553_Overheadtask::on_lineEdit_T15jsjpl_textChanged(const QString &arg1)
{
    int a=Map_fredBm[arg1];
    Change_dBm(a);
}
//基本任务信息内（电子干扰任务）--多通道快速协同干扰--频率值变化改变
void sub1553_Overheadtask::on_lineEdit_T16jsjpl_textChanged(const QString &arg1)
{
    int a=Map_fredBm[arg1];
    Change_dBm(a);
}
//基本任务信息内（电子干扰任务）--多通道多带宽协同干扰--频率值变化改变
void sub1553_Overheadtask::on_lineEdit_T17jsjpl_textChanged(const QString &arg1)
{
    int a=Map_fredBm[arg1];
    Change_dBm(a);
}
//基本任务信息内（电子干扰任务）--雷达强制干扰--频率值变化改变
void sub1553_Overheadtask::on_lineEdit_LDqzgr_1_textChanged(const QString &arg1)
{
    int a=Map_fredBm[arg1];
    Change_dBm(a);
}
//定位参数卫星个数(<3)
void sub1553_Overheadtask::on_lineEdit_F6_4_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>3)||(num<0))
    {
        QMessageBox::warning(this,tr("警告"),tr("个数最大为3"));
        ui->lineEdit_F6_4->setText("3");
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_startAddr->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_startAddr->insertRow(i);
            ui->tableWidget_startAddr->setItem(i,0,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_startAddr->item(i,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_startAddr->removeRow(ui->tableWidget_startAddr->rowCount()-1);
        }
    }
    else {

    }
}
//引导参数卫星个数(<20)
void sub1553_Overheadtask::on_lineEdit_F6_5_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>20)||(num<0))
    {
        QMessageBox::warning(this,tr("警告"),tr("个数最大为20"));
        ui->lineEdit_F6_5->setText("20");
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_YDCSaddr->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_YDCSaddr->insertRow(i);
            ui->tableWidget_YDCSaddr->setItem(i,0,new QTableWidgetItem(QString::number(1)));
            ui->tableWidget_YDCSaddr->setItem(i,1,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_YDCSaddr->item(i,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
            ui->tableWidget_YDCSaddr->item(i,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_YDCSaddr->removeRow(ui->tableWidget_YDCSaddr->rowCount()-1);
        }
    }
    else {

    }
}
//星链信号频点控守---指示后续循环体，NCO频率个数
void sub1553_Overheadtask::on_lineEdit_tab9_xl4_textChanged(const QString &arg1)
{
    //    int num=arg1.toUInt();
    //    if((num>255)||(num<0))
    //    {
    //        return;
    //    }
    //    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    //    int sumRow=ui->tWidget_T9xlNCO_list->rowCount();
    //    if(num>sumRow)
    //    {
    //        for (int i = sumRow; i < num; i++) {
    //            ui->tWidget_T9xlNCO_list->insertRow(i);
    //            ui->tWidget_T9xlNCO_list->setItem(i,0,new QTableWidgetItem(QString::number(0)));
    //        }
    //    }
    //    else if (num<sumRow) {
    //        for (int i = 0; i < (sumRow-num); i++) {
    //            ui->tWidget_T9xlNCO_list->removeRow(ui->tWidget_T9xlNCO_list->rowCount()-1);
    //        }
    //    }
    //    else {

    //    }
}

//等间隔梳状谱干扰（T21.2）
void sub1553_Overheadtask::on_lineEdit_szpds_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>20)||(num<0))
    {
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_szp->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_szp->insertRow(i);

            ui->tableWidget_szp->setItem(i,0,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_szp->setItem(i,1,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_szp->setItem(i,2,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_szp->setItem(i,3,new QTableWidgetItem(QString::number(0)));
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_szp->removeRow(ui->tableWidget_szp->rowCount()-1);
        }
    }
    else {

    }
}


//非等间隔梳状谱干扰（T21.3）
void sub1553_Overheadtask::on_lineEdit_T15ppsum_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if((num>100)||(num<0))
    {
        return;
    }
    //设置值大于现有表格，不清除；；小于表格清楚底部多的
    int sumRow=ui->tableWidget_szpgr->rowCount();
    if(num>sumRow)
    {
        for (int i = sumRow; i < num; i++) {
            ui->tableWidget_szpgr->insertRow(i);

            ui->tableWidget_szpgr->setItem(i,0,new QTableWidgetItem(QString::number(0)));
            ui->tableWidget_szpgr->setItem(i,1,new QTableWidgetItem(QString::number(0)));
        }
    }
    else if (num<sumRow) {
        for (int i = 0; i < (sumRow-num); i++) {
            ui->tableWidget_szpgr->removeRow(ui->tableWidget_szpgr->rowCount()-1);
        }
    }
    else {

    }
}

void sub1553_Overheadtask::on_pB_chooseSarFile_2_clicked()
{
    //打开文件选择对话框
    QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt"));
    if(file_path.size() <= 0) return;
    ui->tB_widget_SARFileList_2->setRowCount(0);
    for(int i=0;i<file_path.size();i++)
    {
        QFileInfo fileinfo(file_path.at(i));    //读取文件
        // 内容参数
        int nrow = ui->tB_widget_SARFileList_2->rowCount();
        ui->tB_widget_SARFileList_2->insertRow(nrow);
        //文件名
        ui->tB_widget_SARFileList_2->setItem(nrow, 0, new QTableWidgetItem(fileinfo.fileName()));
        ui->tB_widget_SARFileList_2->item(nrow, 0)->setTextAlignment(Qt::AlignHCenter |Qt::AlignVCenter);//居中
        // 路径
        ui->tB_widget_SARFileList_2->setItem(nrow, 1, new QTableWidgetItem(file_path.at(i)));

    }
}

void sub1553_Overheadtask::on_pushButton_sarClear_2_clicked()
{
        ui->tB_widget_SARFileList_2->setRowCount(0);
}

//拓展功能--一键版本号配置无效
void sub1553_Overheadtask::on_pushButton_bbh_nomorl_2_clicked()
{
    //高算力1
    int tmp=ui->comboBox_C12_2->count();
    ui->comboBox_C12_2->setCurrentIndex(tmp-1);
    ui->lineEdit_C12_2->setText("FFFF");
    ui->comboBox_C13_2->setCurrentIndex(ui->comboBox_C13_2->count()-1);
    ui->lineEdit_C13_2->setText("FFFF");
    ui->comboBox_C14_2->setCurrentIndex(ui->comboBox_C14_2->count()-1);
    ui->lineEdit_C14_2->setText("FFFF");
    ui->comboBox_C15_2->setCurrentIndex(ui->comboBox_C15_2->count()-1);
    ui->lineEdit_C15_2->setText("FFFF");
    ui->comboBox_C16_2->setCurrentIndex(ui->comboBox_C16_2->count()-1);
    ui->lineEdit_C16_2->setText("FFFF");
    ui->comboBox_C17_2->setCurrentIndex(ui->comboBox_C17_2->count()-1);
    ui->lineEdit_C17_2->setText("FFFF");
    ui->comboBox_C18_2->setCurrentIndex(ui->comboBox_C18_2->count()-1);
    ui->lineEdit_C18_2->setText("FFFF");
    ui->comboBox_C19_2->setCurrentIndex(ui->comboBox_C19_2->count()-1);
    ui->lineEdit_C19_2->setText("FFFF");

    //高算力2
    int tmp2=ui->comboBox_C19_3->count();
    ui->comboBox_C19_3->setCurrentIndex(tmp2-1);
    ui->lineEdit_C19_3->setText("FFFF");
    ui->comboBox_C19_4->setCurrentIndex(ui->comboBox_C19_4->count()-1);
    ui->lineEdit_C19_4->setText("FFFF");
    ui->comboBox_C19_5->setCurrentIndex(ui->comboBox_C19_5->count()-1);
    ui->lineEdit_C19_5->setText("FFFF");
    ui->comboBox_C19_6->setCurrentIndex(ui->comboBox_C19_6->count()-1);
    ui->lineEdit_C19_6->setText("FFFF");
    ui->comboBox_C19_7->setCurrentIndex(ui->comboBox_C19_7->count()-1);
    ui->lineEdit_C19_7->setText("FFFF");
    ui->comboBox_C19_8->setCurrentIndex(ui->comboBox_C19_8->count()-1);
    ui->lineEdit_C19_8->setText("FFFF");
    ui->comboBox_C19_9->setCurrentIndex(ui->comboBox_C19_9->count()-1);
    ui->lineEdit_C19_9->setText("FFFF");
    ui->comboBox_C19_10->setCurrentIndex(ui->comboBox_C19_10->count()-1);
    ui->lineEdit_C19_10->setText("FFFF");
}





void sub1553_Overheadtask::on_comboBox_C12_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C12_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C13_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C13_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C14_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C14_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C15_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C15_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C16_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C16_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C17_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C17_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C18_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C18_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_2_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_2->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_3_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_3->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_4_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_4->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_5_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_5->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_6_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_6->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_7_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_7->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_8_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_8->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_9_activated(const QString &arg1)
{

    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_9->setText(tmp);
}

void sub1553_Overheadtask::on_comboBox_C19_10_activated(const QString &arg1)
{
    QString tmp=arg1;
    tmp=tmp.left(6);
    tmp=tmp.right(tmp.size()-tmp.indexOf("x")-1);
    //qDebug()<<tmp;
    ui->lineEdit_C19_10->setText(tmp);
}
//拓展功能-本振方式选择
void sub1553_Overheadtask::on_comboBox_tz2_activated(int index)
{
    if(index==0)//0：独立本振
    {
        ui->comboBox_2D5_b1_2->setVisible(1);//一本振使用信息
    }
    else//1：共本振
    {
        ui->comboBox_2D5_b1_2->setVisible(0);
    }
}
//拓展功能-射频通道号
void sub1553_Overheadtask::on_comboBox_D7_3_activated(int index)
{
    if(index==0)//0：通拨
    {
        ui->comboBox_D7_5->setVisible(0);//射频通道号第2组
        ui->comboBox_D7_7->setVisible(0);//射频通道号第3组
        ui->comboBox_D7_6->setVisible(0);//射频通道号第4组
    }
    else
    {
        ui->comboBox_D7_5->setVisible(1);//2组
        ui->comboBox_D7_7->setVisible(1);//3组
        ui->comboBox_D7_6->setVisible(1);//4组
    }
}
//拓展功能-频段选择
void sub1553_Overheadtask::on_comboBox_C3_2_activated(int index)
{
    if (index == 0)  // L频段
    {

        // 1射频通道号
        ui->comboBox_D7_3->clear();
        ui->comboBox_D7_5->clear();
        ui->comboBox_D7_7->clear();
        ui->comboBox_D7_6->clear();
        QStringList list,list1,list2,list3;
        list  << "通拨"<< "通道1"<< "通道2"<< "通道3"<< "通道4"<< "通道5"<< "通道6";
        list1 << "组2:通拨"<< "组2:通道1"<< "组2:通道2"<< "组2:通道3"<< "组2:通道4"<< "组2:通道5"<< "组2:通道6";
        list2 << "组3:通拨"<< "组3:通道1"<< "组3:通道2"<< "组3:通道3"<< "组3:通道4"<< "组3:通道5"<< "组3:通道6";
        list3 << "组4:通拨"<< "组4:通道1"<< "组4:通道2"<< "组4:通道3"<< "组4:通道4"<< "组4:通道5"<< "组4:通道6";
        ui->comboBox_D7_3->addItems(list);
        ui->comboBox_D7_5->addItems(list1);
        ui->comboBox_D7_7->addItems(list2);
        ui->comboBox_D7_6->addItems(list3);
        // 控件回归初始化
        ui->comboBox_D7_3->setCurrentIndex(0);

        ui->comboBox_D7_5->setVisible(0);//射频通道号第2组
        ui->comboBox_D7_7->setVisible(0);//射频通道号第3组
        ui->comboBox_D7_6->setVisible(0);//射频通道号第4组
        ui->comboBox_D7_5->setCurrentIndex(0);
        ui->comboBox_D7_7->setCurrentIndex(0);
        ui->comboBox_D7_6->setCurrentIndex(0);

        //放大器使能/射频衰减
        ui->checkBox_D8bit0_2->setVisible(1);
        ui->checkBox_D8bit2_2->setVisible(1);
        ui->checkBox_D8bit3_2->setVisible(1);
        ui->label_494->setVisible(0);
        ui->comboBox_D8bit1_3->setVisible(0);



        // 天线子阵参数。。。
        ui->label_497->setText("天线使用方式");
        ui->comboBox_D10bit5_2->clear();
        ui->comboBox_D10bit5_2->addItem("0:独立孔径");
        ui->comboBox_D10bit5_2->addItem("1:合成孔径");
        ui->comboBox_D10bit5_2->addItem("2:双孔径");
        ui->label_499->setVisible(false);
        ui->comboBox_D10bit6_2->setVisible(false);
        // 控件回归初始化
        ui->comboBox_D10bit5_2->setCurrentIndex(0);
        ui->comboBox_D10bit6_2->setCurrentIndex(0);


        //
        ui->label_503->setVisible(1);//射频发射衰减（l频段）
        ui->lineEdit_tz4->setVisible(1);
        ui->label_504->setVisible(1);//射频发射衰减（l频段）
        ui->comboBox_tz4->setVisible(1);


        ui->label_505->setVisible(0);//接收相位/幅度加权码（SXKu频段）
        ui->lineEdit_tz5->setVisible(0);
        ui->label_513->setVisible(0);
        ui->lineEdit_tz6->setVisible(0);
        ui->label_514->setVisible(0);//组件遥测数据类型    （SXKu频段）
        ui->comboBox_tz7->setVisible(0);
    }
    else// sxku频段
    {
        // 1射频通道号
        ui->comboBox_D7_3->clear();
        ui->comboBox_D7_5->clear();
        ui->comboBox_D7_7->clear();
        ui->comboBox_D7_6->clear();
        QStringList list,list1,list2,list3;
        list  << "通拨"<< "通道1和2"<< "通道3和4"<< "通道5和6";
        list1 << "组2:通拨"<< "组2:通道1和2"<< "组2:通道3和4"<< "组2:通道5和6";
        list2 << "组3:通拨"<< "组3:通道1和2"<< "组3:通道3和4"<< "组3:通道5和6";
        list3 << "组4:通拨"<< "组4:通道1和2"<< "组4:通道3和4"<< "组4:通道5和6";
        ui->comboBox_D7_3->addItems(list);
        ui->comboBox_D7_5->addItems(list1);
        ui->comboBox_D7_7->addItems(list2);
        ui->comboBox_D7_6->addItems(list3);
        // 控件回归初始化
        ui->comboBox_D7_3->setCurrentIndex(0);
        ui->comboBox_D7_5->setVisible(0);//射频通道号第2组
        ui->comboBox_D7_7->setVisible(0);//射频通道号第3组
        ui->comboBox_D7_6->setVisible(0);//射频通道号第4组
        ui->comboBox_D7_5->setCurrentIndex(0);
        ui->comboBox_D7_7->setCurrentIndex(0);
        ui->comboBox_D7_6->setCurrentIndex(0);


        //放大器使能/射频衰减
        ui->checkBox_D8bit0_2->setVisible(0);
        ui->checkBox_D8bit2_2->setVisible(0);
        ui->checkBox_D8bit3_2->setVisible(0);
        ui->label_494->setVisible(1);
        ui->comboBox_D8bit1_3->setVisible(1);


        // 3天线子阵参数。。。
        ui->label_497->setText("子阵1,3天线使用方式");
        ui->comboBox_D10bit5_2->clear();
        ui->comboBox_D10bit5_2->addItem("0:不启用V极化合成");
        ui->comboBox_D10bit5_2->addItem("1:启用V极化合成");
        ui->label_499->setVisible(true);
        ui->comboBox_D10bit6_2->setVisible(true);
        // 控件回归初始化
        ui->comboBox_D10bit5_2->setCurrentIndex(0);
        ui->comboBox_D10bit6_2->setCurrentIndex(0);

        //

        ui->label_503->setVisible(0);//射频发射衰减（l频段）
        ui->lineEdit_tz4->setVisible(0);
        ui->label_504->setVisible(0);//射频发射衰减（l频段）
        ui->comboBox_tz4->setVisible(0);

        ui->label_505->setVisible(1);//接收相位/幅度加权码（SXKu频段）
        ui->lineEdit_tz5->setVisible(1);
        ui->label_513->setVisible(1);
        ui->lineEdit_tz6->setVisible(1);
        ui->label_514->setVisible(1);//组件遥测数据类型    （SXKu频段）
        ui->comboBox_tz7->setVisible(1);
    }
}
//拓展任务 子阵1
void sub1553_Overheadtask::on_checkBox_D10bit0_3_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change2();
}
//拓展任务 子阵2
void sub1553_Overheadtask::on_checkBox_D10bit1_3_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change2();
}
//拓展任务 子阵3
void sub1553_Overheadtask::on_checkBox_D10bit2_3_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change2();
}
//拓展任务 子阵4
void sub1553_Overheadtask::on_checkBox_D10bit3_3_clicked(bool checked)
{
    Q_UNUSED(checked);
    zz_change2();
}
//电子干扰--天线使用方式
void sub1553_Overheadtask::on_comboBox_E7bit5_activated(int index)
{
    if(index==0)//独立孔径---L段天线射频发射衰减值56
    {
        ui->lineEdit_E13b5_0->setText("56");
    }
    else
    {
        ui->lineEdit_E13b5_0->setText("0");
    }
}
//基本任务信息，快捷设置版本号
void sub1553_Overheadtask::on_comboBox_sorftBb_activated(int index)
{
    int mode=ui->cB_function_mode->currentIndex();

    switch (index) {
    case 0:
        break;
    case 1:

        ui->comboBox_C12->setCurrentIndex(ui->comboBox_C12->count()-1);
        ui->lineEdit_C12->setText("FFFF");
        ui->comboBox_C13->setCurrentIndex(ui->comboBox_C13->count()-1);
        ui->lineEdit_C13->setText("FFFF");
        ui->comboBox_C14->setCurrentIndex(ui->comboBox_C14->count()-1);
        ui->lineEdit_C14->setText("FFFF");
        ui->comboBox_C15->setCurrentIndex(ui->comboBox_C15->count()-1);
        ui->lineEdit_C15->setText("FFFF");
        ui->comboBox_C16->setCurrentIndex(ui->comboBox_C16->count()-1);
        ui->lineEdit_C16->setText("FFFF");
        ui->comboBox_C17->setCurrentIndex(ui->comboBox_C17->count()-1);
        ui->lineEdit_C17->setText("FFFF");
        ui->comboBox_C18->setCurrentIndex(ui->comboBox_C18->count()-1);
        ui->lineEdit_C18->setText("FFFF");
        ui->comboBox_C19->setCurrentIndex(ui->comboBox_C19->count()-1);
        ui->lineEdit_C19->setText("FFFF");
        break;
    case 2:
        ui->comboBox_C12->setCurrentIndex(ui->comboBox_C12->count()-2);
        ui->lineEdit_C12->setText("EEEE");
        ui->comboBox_C13->setCurrentIndex(ui->comboBox_C13->count()-2);
        ui->lineEdit_C13->setText("EEEE");
        ui->comboBox_C14->setCurrentIndex(ui->comboBox_C14->count()-2);
        ui->lineEdit_C14->setText("EEEE");
        ui->comboBox_C15->setCurrentIndex(ui->comboBox_C15->count()-2);
        ui->lineEdit_C15->setText("EEEE");
        ui->comboBox_C16->setCurrentIndex(ui->comboBox_C16->count()-2);
        ui->lineEdit_C16->setText("EEEE");
        ui->comboBox_C17->setCurrentIndex(ui->comboBox_C17->count()-2);
        ui->lineEdit_C17->setText("EEEE");
        ui->comboBox_C18->setCurrentIndex(ui->comboBox_C18->count()-2);
        ui->lineEdit_C18->setText("EEEE");
        ui->comboBox_C19->setCurrentIndex(ui->comboBox_C19->count()-2);
        ui->lineEdit_C19->setText("EEEE");
        break;
    case 3://雷达干扰模式
        if((mode==1)||(mode==2))
        {
            ui->comboBox_C12->setCurrentIndex(0);
            ui->lineEdit_C12->setText("0F02");
            ui->comboBox_C13->setCurrentIndex(2);
            ui->lineEdit_C13->setText("0F04");
            ui->comboBox_C14->setCurrentIndex(ui->comboBox_C14->count()-2);
            ui->lineEdit_C14->setText("EEEE");
            ui->comboBox_C15->setCurrentIndex(ui->comboBox_C15->count()-2);
            ui->lineEdit_C15->setText("EEEE");
            ui->comboBox_C16->setCurrentIndex(ui->comboBox_C16->count()-2);
            ui->lineEdit_C16->setText("EEEE");
            ui->comboBox_C17->setCurrentIndex(2);
            ui->lineEdit_C17->setText("2F04");
            ui->comboBox_C18->setCurrentIndex(2);
            ui->lineEdit_C18->setText("2F04");
            ui->comboBox_C19->setCurrentIndex(0);
            ui->lineEdit_C19->setText("2D05");
        }
        else
        {
            QMessageBox::information(this,"提示","功能模式不匹配");
            //快捷填充版本号
            ui->comboBox_sorftBb->setCurrentIndex(0);
        }
        break;

    default:
        break;
    }
}
