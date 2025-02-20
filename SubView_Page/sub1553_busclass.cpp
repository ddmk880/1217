#include "sub1553_busclass.h"
#include "ui_sub1553_busclass.h"
#include <QDebug>
sub1553_busclass::sub1553_busclass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_busclass)
{
    ui->setupUi(this);

    QStringList tmp;
    tmp.append("0x01:L频段消浪涌开");
    tmp.append("0x02:L频段消浪涌关");
    tmp.append("0x03:L频段31V总电源开");
    tmp.append("0x04:L频段31V总电源关");
    tmp.append("0x05:L频段数字综合单元雷达计算机加电");
    tmp.append("0x06:L频段数字综合单元雷达计算机断电");
    tmp.append("0x07:L频段数字综合单元雷达计算机切主");
    tmp.append("0x08:L频段数字综合单元雷达计算机切备");
    tmp.append("0x09:SXKu频段消浪涌开");
    tmp.append("0x0A:SXKu频段消浪涌关");
    tmp.append("0x0B:SXKu频段主份波束控制器开");
    tmp.append("0x0C:SXKu频段主份波束控制器关");
    tmp.append("0x0D:SXKu频段备份波束控制器开");
    tmp.append("0x0E:SXKu频段备份波束控制器关");
    tmp.append("0x0F:SXKu频段31V总电源开");
    tmp.append("0x10:SXKu频段31V总电源关");
    tmp.append("0x11:可重构射频前端主份加电");
    tmp.append("0x12:可重构射频前端主份断电");
    tmp.append("0x13:可重构射频前端备份加电");
    tmp.append("0x14:可重构射频前端备份断电");
    tmp.append("0x15:可重构高算力平台1加电");
    tmp.append("0x16:可重构高算力平台1断电");
    tmp.append("0x17:可重构高算力平台2加电");
    tmp.append("0x18:可重构高算力平台2断电");
    tmp.append("0x19:高算力平台1复位");
    tmp.append("0x1A:高算力平台2复位");
    tmp.append("0x1B:载荷天线配电器A组放电开关接通指令");
    tmp.append("0x1C:载荷天线配电器A组放电开关断开指令");
    tmp.append("0x1D:载荷天线配电器A组消浪涌开关接通指令");
    tmp.append("0x1E:载荷天线配电器A组消浪涌开关断开指令");
    tmp.append("0x1F:载荷天线配电器B组放电开关接通指令");
    tmp.append("0x20:载荷天线配电器B组放电开关断开指令");
    tmp.append("0x21:载荷天线配电器B组消浪涌开关接通指令");
    tmp.append("0x22:载荷天线配电器B组消浪涌开关断开指令");
    tmp.append("0x23:载荷天线配电器C组放电开关接通指令");
    tmp.append("0x24:载荷天线配电器C组放电开关断开指令");
    tmp.append("0x25:载荷天线配电器C组消浪涌开关接通指令");
    tmp.append("0x26:载荷天线配电器C组消浪涌开关断开指令");
    tmp.append("0x27:载荷天线配电器D组放电开关接通指令");
    tmp.append("0x28:载荷天线配电器D组放电开关断开指令");
    tmp.append("0x29:载荷天线配电器D组消浪涌开关接通指令");
    tmp.append("0x2A:载荷天线配电器D组消浪涌开关断开指令");
    tmp.append("0x2B:综合管控单元综合处理模块加电");
    tmp.append("0x2C:综合管控单元综合处理模块断电");

    //OC控制的电源操作
    ui->cB_OCpower_control->addItems(tmp);

    QStringList tmp2;
    tmp2.append("0x01:SXKu频段射频收发单元-接收开");
    tmp2.append("0x02:SXKu频段射频收发单元-接收关");
    tmp2.append("0x03:SXKu频段射频收发单元-发射开");
    tmp2.append("0x04:SXKu频段射频收发单元-发射关");
    tmp2.append("0x05:SXKu频段天线阵面1接收加电");
    tmp2.append("0x06:SXKu频段天线阵面1接收断电");
    tmp2.append("0x07:SXKu频段天线阵面1发射加电");
    tmp2.append("0x08:SXKu频段天线阵面1发射断电");
    tmp2.append("0x09:SXKu频段天线阵面2接收加电");
    tmp2.append("0x0A:SXKu频段天线阵面2接收断电");
    tmp2.append("0x0B:SXKu频段天线阵面2发射加电");
    tmp2.append("0x0C:SXKu频段天线阵面2发射断电");
    tmp2.append("0x0D:SXKu频段天线阵面3接收加电");
    tmp2.append("0x0E:SXKu频段天线阵面3接收断电");
    tmp2.append("0x0F:SXKu频段天线阵面3发射加电");
    tmp2.append("0x10:SXKu频段天线阵面3发射断电");
    tmp2.append("0x11:SXKu频段天线阵面4接收加电");
    tmp2.append("0x12:SXKu频段天线阵面4接收断电");
    tmp2.append("0x13:SXKu频段天线阵面4发射加电");
    tmp2.append("0x14:SXKu频段天线阵面4发射断电");
    tmp2.append("0x15:L频段射频综合单元开");
    tmp2.append("0x16:L频段射频综合单元关");
    tmp2.append("0x17:L频段数字综合单元定时波控加电");
    tmp2.append("0x18:L频段数字综合单元定时波控断电");
    tmp2.append("0x19:L频段数字综合单元定时波控切主");
    tmp2.append("0x1A:L频段天线阵面1接收加电");
    tmp2.append("0x1B:L频段天线阵面1接收断电");
    tmp2.append("0x1C:L频段天线阵面1发射加电");
    tmp2.append("0x1D:L频段天线阵面1发射断电");
    tmp2.append("0x1E:L频段天线阵面2接收加电");
    tmp2.append("0x1F:L频段天线阵面2接收断电");
    tmp2.append("0x20:L频段天线阵面2发射加电");
    tmp2.append("0x21:L频段天线阵面2发射断电");
    tmp2.append("0x22:L频段天线阵面3接收加电");
    tmp2.append("0x23:L频段天线阵面3接收断电");
    tmp2.append("0x24:L频段天线阵面3发射加电");
    tmp2.append("0x25:L频段天线阵面3发射断电");
    tmp2.append("0x26:L频段天线阵面4接收加电");
    tmp2.append("0x27:L频段天线阵面4接收断电");
    tmp2.append("0x28:L频段天线阵面4发射加电");
    tmp2.append("0x29:L频段天线阵面4发射断电");
    tmp2.append("0x2A:L频段数字综合单元定时波控切备");
    tmp2.append("0x2B:L频段天线全阵面收发加电");
    tmp2.append("0x2C:L频段天线全阵面收发断电");
    tmp2.append("0x2D:SXKu频段天线全阵断电");

    //CAN控制的电源操作
    ui->cB_Can_powercontrol->addItems(tmp2);

}

sub1553_busclass::~sub1553_busclass()
{
    delete ui;
}

void sub1553_busclass::Reverse_Data(Order_List_Object varData)
{
    Order_List_Object* order_data = &varData;
    Q_UNUSED(order_data);

}

//公用添加到主界面窗口
void sub1553_busclass::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 1;
    order_data.gap_time = 1;
    order_data.order_name = buffname;
    order_data.order_kind = 1;
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff,buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}


//关机准备
void sub1553_busclass::on_pB_shutdown_clicked()
{
    Sorder_shutdown shutdown;
    memset(&shutdown,0,sizeof (shutdown));
    //指令标志
    shutdown.ordermark=0x01;
    //管控单元(暂时保留)
    shutdown.controlunit=0xff;


    Pblic_Addorderlist((uchar*)&shutdown,sizeof (shutdown),"管控机关机准备");
}

//下控单机关机准备
void sub1553_busclass::on_pushButton_downcontrl_clicked()
{
    uchar str[2]={0};
    //标志
    str[0]=0x02;
    //保留
    str[1]=0xff;

    Pblic_Addorderlist((uchar*)str,sizeof (str),"下控单机关机准备");
}

// 综合管控单元SSD清空
void sub1553_busclass::on_pB_ssdclear_clicked()
{
    SSD_clear ssdclear;
    memset(&ssdclear,0,sizeof(ssdclear));
    // 指令标志
    ssdclear.ordermark = 0x03;
    //分区
    ssdclear.reserve = ui->comboBox_ssdclear->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&ssdclear,sizeof (ssdclear),"综合管控单元SSD清空");

}


// Flash格式化
void sub1553_busclass::on_pB_flashformat_clicked()
{
    Flash_Format ff;
    memset(&ff,0,sizeof(ff));
    ff.ordermark = 0x04;
    ff.capacity_choose = ui->cB_flash_format->currentIndex()+2;

    //列表封装
    Pblic_Addorderlist((uchar*)&ff,sizeof (ff),"Flash格式化 : "+ui->cB_flash_format->currentText());
}

// 管控软件-V2看门狗控制
void sub1553_busclass::on_pB_watchdog_control_clicked()
{
    WatchDog_control wdc;
    memset(&wdc,0,sizeof(wdc));
    wdc.ordermark = 0x05;
    wdc.magcontrol_mode = ui->cB_watchdog_control->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&wdc,sizeof (wdc),"管控软件-V2看门狗控制 : "+ui->cB_watchdog_control->currentText());
}

// 管控软件加载选择
void sub1553_busclass::on_pB_software_load_clicked()
{
    Software_load_choose slc;
    memset(&slc,0,sizeof(slc));
    slc.ordermark = 0x06;
    slc.software_choose = ui->cB_software_load_choose->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&slc,sizeof (slc),"管控软件加载选择 : "+ui->cB_software_load_choose->currentText());
}

// OC电压控制
void sub1553_busclass::on_pB_OCpower_control_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = ui->cB_OCpower_control->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制 : "+ui->cB_OCpower_control->currentText());
}

// Can电压控制
void sub1553_busclass::on_pB_Can_powercontrol_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = ui->cB_Can_powercontrol->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制 : "+ui->cB_Can_powercontrol->currentText());
}

//管控模块复位0X09
void sub1553_busclass::on_pushButton_task_clicked()
{
    uchar str[2]={0};
    str[0]= 0x09;
    str[1]=0xFF;

    //列表封装
    Pblic_Addorderlist((uchar*)&str,sizeof (str),"管控模块复位");
}

//模板清除 0x10
void sub1553_busclass::on_pushButton_0x10_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x10;
    //参数
    arr[1]= ui->comboBox_0x10_1->currentIndex()+1;
    if(ui->comboBox_0x10_1->currentIndex()==2)arr[1]=4;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"模板清除 : "+ui->comboBox_0x10_1->currentText());
}
//光模块参数更新0x11
void sub1553_busclass::on_pushButton_0x11_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x11;
    //参数
    arr[1]= ui->comboBox_0x11_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"光模块参数更新 : "+ui->comboBox_0x11_1->currentText());
}





//轨道编号0x12
void sub1553_busclass::on_pushButton_GDbh_clicked()
{

    Software_GD arr;
    memset(&arr,0,sizeof (Software_GD));
    // 指令标志
    arr.ordermark = 0x12;
    //状态
    arr.BH= ui->lineEdit_GDbh->text().toUInt();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"轨道编号 : "+QString::number(ui->lineEdit_GDbh->text().toInt()));
}
//Mram参数配置区还原0x13
void sub1553_busclass::on_pushButton_0x13_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x13;
    //状态
    arr[1]= ui->comboBox_0x13_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"Mram参数配置区还原 : "+ui->comboBox_0x13_1->currentText());
}
//卫星编号0x14
void sub1553_busclass::on_pushButton_0x14_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x14;
    //状态
    arr[1]= ui->lineEdit_0x14_1->text().toInt();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"卫星编号 : "+QString::number(ui->lineEdit_0x14_1->text().toInt()));
}
//综合管控单元三模运维使能 0x16
void sub1553_busclass::on_pushButton_0x16_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x16;
    //状态
    arr[1]= ui->comboBox_0x16_1->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"三模运维使能 : "+ui->comboBox_0x16_1->currentText());
}

//千兆网口通信选择0x15
void sub1553_busclass::on_pB_0x15_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x15;
    //状态
    arr[1]= ui->cB_0x15_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"千兆网口通信选择 : "+ui->cB_0x15_1->currentText());
}

//CAN通道切换0x17
void sub1553_busclass::on_pB_0x17_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x17;
    //状态
    arr[1]= ui->cB_0x17_1->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"CAN通道切换 : "+ui->cB_0x17_1->currentText());
}
//开关记录状态复位0x18
void sub1553_busclass::on_pB_0x18_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x18;
    //状态
    arr[1]= 0xFF;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"开关记录状态复位");
}

//暂停软件预加载 0x19
void sub1553_busclass::on_pushButton_0x19_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x19;
    //状态
    arr[1]= ui->comboBox_0x19_1->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"暂停软件预加载 : "+ui->comboBox_0x19_1->currentText());
}


//清除块内数据0x1A
void sub1553_busclass::on_pB_0x1A_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x1A;
    //状态
    arr[1]= 0xFF;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"清除块内数据");
}
//管控广播、日志数据下传0x0A
void sub1553_busclass::on_pushButton_0x0A_down_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x0A;
    //状态
    arr[1]= ui->comboBox_0x0A_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"管控广播、日志数据下传 : "+ui->comboBox_0x0A_1->currentText());
}
//可重构射频前端自动增益开关0x1B
void sub1553_busclass::on_pB_0x1B_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x1B;
    //状态
    arr[1]= ui->cB_0x1B_1->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"可重构射频前端自动增益开关 : "+ui->cB_0x1B_1->currentText());
}
//高算力接口v7三模运维 0x0B
void sub1553_busclass::on_pushButton_0x0B_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x0B;
    //参数
    arr[1]= ui->comboBox_0x0B_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"高算力接口v7三模运维 : "+ui->comboBox_0x0B_1->currentText());
}
//CAN解析及重构调度软件切换到更新区0x0c
void sub1553_busclass::on_pB_0x0C_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x0C;
    //参数
    arr[1]= ui->cB_0x0C_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"CAN解析及重构软件切更新区 : "+ui->cB_0x0C_1->currentText());
}
//管控三模运维周期设置 0x0D
void sub1553_busclass::on_pushButton_0x0D_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x0D;
    //参数
    arr[1]= ui->lineEdit_0x0D1->text().toInt();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"管控三模运维周期设置 :时间 "+QString::number(arr[1]));
}

//管控机SSD分区和目录查询0x1C
void sub1553_busclass::on_pushButton_0x1C_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x1C;
    //状态
    arr[1]= ui->comboBox_0x1C_1->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"管控机SSD分区和目录查询");
}

//管控V7刷新使能0x0E
void sub1553_busclass::on_pB_0x0E_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x0E;
    //参数
    arr[1]= ui->cB_0x0E_1->currentIndex();

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"管控V7刷新使能 : "+ui->cB_0x0E_1->currentText());
}
//区域/常规任务选择0x0F
void sub1553_busclass::on_pushButton_0x0F_clicked()
{
    uchar arr[2];
    memset(&arr,0,sizeof (arr));
    // 指令标志
    arr[0] = 0x0F;
    //参数
    arr[1]= ui->comboBox_0x0F_1->currentIndex()+1;

    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"区域/常规任务选择 : "+ui->comboBox_0x0F_1->currentText());
}

//任务上下电部署开关0xFD
void sub1553_busclass::on_pushButton_enduptask_clicked()
{
    uchar str[2]={0};
    str[0]= 0xFD;
    str[1]=ui->comboBox_0xFD_1->currentIndex()+1;


    //列表封装
    Pblic_Addorderlist((uchar*)&str,sizeof (str),"任务上下电部署开关："+ui->comboBox_0xFD_1->currentText());
}



//运行任务列表复位0xFE
void sub1553_busclass::on_pB_trans_software_clicked()
{
    uchar str[2]={0};

    str[0]=0xFE;
    str[1]=0xFF;


    //列表封装
    Pblic_Addorderlist((uchar*)&str,sizeof (str),"运行任务列表复位");
}

