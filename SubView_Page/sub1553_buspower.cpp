#include "sub1553_buspower.h"
#include "ui_sub1553_buspower.h"
#include <QDebug>
#include <QVector>

sub1553_busPower::sub1553_busPower(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_busPower)
{
    ui->setupUi(this);

    succ_send=true;
    //OC电源控制
    OC_kind[0x01]="0x01:L频段消浪涌开";
    OC_kind[0x02]="0x02:L频段消浪涌关";
    OC_kind[0x03]="0x03:L频段31V总电源开";
    OC_kind[0x04]="0x04:L频段31V总电源关";
    OC_kind[0x05]="0x05:L频段数字综合单元雷达计算机加电";
    OC_kind[0x06]="0x06:L频段数字综合单元雷达计算机断电";
    OC_kind[0x07]="0x07:L频段数字综合单元雷达计算机切主";
    OC_kind[0x08]="0x08:L频段数字综合单元雷达计算机切备";
    OC_kind[0x09]="0x09:SXKu频段消浪涌开";
    OC_kind[0x0A]="0x0A:SXKu频段消浪涌关";
    OC_kind[0x0B]="0x0B:SXKu频段主份波束控制器开";
    OC_kind[0x0C]="0x0C:SXKu频段主份波束控制器关";
    OC_kind[0x0D]="0x0D:SXKu频段备份波束控制器开";
    OC_kind[0x0E]="0x0E:SXKu频段备份波束控制器关";
    OC_kind[0x0F]="0x0F:SXKu频段31V总电源开";
    OC_kind[0x10]="0x10:SXKu频段31V总电源关";
    OC_kind[0x11]="0x11:可重构射频前端主份加电";
    OC_kind[0x12]="0x12:可重构射频前端主份断电";
    OC_kind[0x13]="0x13:可重构射频前端备份加电";
    OC_kind[0x14]="0x14:可重构射频前端备份断电";
    OC_kind[0x15]="0x15:可重构高算力平台1加电";
    OC_kind[0x16]="0x16:可重构高算力平台1断电";
    OC_kind[0x17]="0x17:可重构高算力平台2加电";
    OC_kind[0x18]="0x18:可重构高算力平台2断电";
    OC_kind[0x19]="0x19:高算力平台1复位";
    OC_kind[0x1A]="0x1A:高算力平台2复位";
    OC_kind[0x1B]="0x1B:配电器A组放电开关接通指令";
    OC_kind[0x1C]="0x1C:配电器A组放电开关断开指令";
    OC_kind[0x1D]="0x1D:配电器A组消浪涌开关接通指令";
    OC_kind[0x1E]="0x1E:配电器A组消浪涌开关断开指令";
    OC_kind[0x1F]="0x1F:配电器B组放电开关接通指令";
    OC_kind[0x20]="0x20:配电器B组放电开关断开指令";
    OC_kind[0x21]="0x21:配电器B组消浪涌开关接通指令";
    OC_kind[0x22]="0x22:配电器B组消浪涌开关断开指令";
    OC_kind[0x23]="0x23:配电器C组放电开关接通指令";
    OC_kind[0x24]="0x24:配电器C组放电开关断开指令";
    OC_kind[0x25]="0x25:配电器C组消浪涌开关接通指令";
    OC_kind[0x26]="0x26:配电器C组消浪涌开关断开指令";
    OC_kind[0x27]="0x27:配电器D组放电开关接通指令";
    OC_kind[0x28]="0x28:配电器D组放电开关断开指令";
    OC_kind[0x29]="0x29:配电器D组消浪涌开关接通指令";
    OC_kind[0x2A]="0x2A:配电器D组消浪涌开关断开指令";
    OC_kind[0x2B]="0x2B:综合管控单元综合处理模块加电";
    OC_kind[0x2C]="0x2C:综合管控单元综合处理模块断电";


    //CAN电源控制
    CAN_kind[0x01]="0x01:SXKu频段射频收发单元-接收开";
    CAN_kind[0x02]="0x02:SXKu频段射频收发单元-接收关";
    CAN_kind[0x03]="0x03:SXKu频段射频收发单元-发射开";
    CAN_kind[0x04]="0x04:SXKu频段射频收发单元-发射关";
    CAN_kind[0x05]="0x05:SXKu频段天线阵面1接收加电";
    CAN_kind[0x06]="0x06:SXKu频段天线阵面1接收断电";
    CAN_kind[0x07]="0x07:SXKu频段天线阵面1发射加电";
    CAN_kind[0x08]="0x08:SXKu频段天线阵面1发射断电";
    CAN_kind[0x09]="0x09:SXKu频段天线阵面2接收加电";
    CAN_kind[0x0A]="0x0A:SXKu频段天线阵面2接收断电";
    CAN_kind[0x0B]="0x0B:SXKu频段天线阵面2发射加电";
    CAN_kind[0x0C]="0x0C:SXKu频段天线阵面2发射断电";
    CAN_kind[0x0D]="0x0D:SXKu频段天线阵面3接收加电";
    CAN_kind[0x0E]="0x0E:SXKu频段天线阵面3接收断电";
    CAN_kind[0x0F]="0x0F:SXKu频段天线阵面3发射加电";
    CAN_kind[0x10]="0x10:SXKu频段天线阵面3发射断电";
    CAN_kind[0x11]="0x11:SXKu频段天线阵面4接收加电";
    CAN_kind[0x12]="0x12:SXKu频段天线阵面4接收断电";
    CAN_kind[0x13]="0x13:SXKu频段天线阵面4发射加电";
    CAN_kind[0x14]="0x14:SXKu频段天线阵面4发射断电";
    CAN_kind[0x15]="0x15:L频段射频综合单元开";
    CAN_kind[0x16]="0x16:L频段射频综合单元关";
    CAN_kind[0x17]="0x17:L频段数字综合单元定时波控加电";
    CAN_kind[0x18]="0x18:L频段数字综合单元定时波控断电";
    CAN_kind[0x19]="0x19:L频段数字综合单元定时波控切主";
    CAN_kind[0x1A]="0x1A:L频段天线阵面1接收加电";
    CAN_kind[0x1B]="0x1B:L频段天线阵面1接收断电";
    CAN_kind[0x1C]="0x1C:L频段天线阵面1发射加电";
    CAN_kind[0x1D]="0x1D:L频段天线阵面1发射断电";
    CAN_kind[0x1E]="0x1E:L频段天线阵面2接收加电";
    CAN_kind[0x1F]="0x1F:L频段天线阵面2接收断电";
    CAN_kind[0x20]="0x20:L频段天线阵面2发射加电";
    CAN_kind[0x21]="0x21:L频段天线阵面2发射断电";
    CAN_kind[0x22]="0x22:L频段天线阵面3接收加电";
    CAN_kind[0x23]="0x23:L频段天线阵面3接收断电";
    CAN_kind[0x24]="0x24:L频段天线阵面3发射加电";
    CAN_kind[0x25]="0x25:L频段天线阵面3发射断电";
    CAN_kind[0x26]="0x26:L频段天线阵面4接收加电";
    CAN_kind[0x27]="0x27:L频段天线阵面4接收断电";
    CAN_kind[0x28]="0x28:L频段天线阵面4发射加电";
    CAN_kind[0x29]="0x29:L频段天线阵面4发射断电";
    CAN_kind[0x2A]="0x2A:L频段数字综合单元定时波控切备";
    CAN_kind[0x2B]="0x2B:L频段天线全阵面收发加电";
    CAN_kind[0x2C]="0x2C:L频段天线全阵面收发断电";
    CAN_kind[0x2D]="0x2D:SXKu频段天线全阵断电";
}

sub1553_busPower::~sub1553_busPower()
{
    delete ui;
}

void sub1553_busPower::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 2;
    order_data.gap_time = 1;
    order_data.order_name = buffname;
    order_data.order_kind = 1;
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff,buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    if(succ_send)emit success_snack("成功");
}

//0x01：L频段消浪涌开
void sub1553_busPower::on_pushButton_01_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x01;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x01:L频段消浪涌开");
}
//0x02:L频段消浪涌关
void sub1553_busPower::on_pushButton_2_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x02;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x02:L频段消浪涌关");
}
//0x03：L频段31V总电源开
void sub1553_busPower::on_pushButton_3_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x03;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x03:L频段31V总电源开");
}
//0x04：L频段31V总电源关
void sub1553_busPower::on_pushButton_4_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x04;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x04:L频段31V总电源关");
}
//0x05：L频段数字综合单元雷达计算机加电
void sub1553_busPower::on_pushButton_5_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x05;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x05:L频段雷达计算机加电");
}
//0x06：L频段数字综合单元雷达计算机断电
void sub1553_busPower::on_pushButton_6_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x06;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x06:L频段雷达计算机断电");
}
//0x07：L频段数字综合单元雷达计算机切主
void sub1553_busPower::on_pushButton_7_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x07;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x07:L频段雷达计算机切主");
}
//0x08：L频段数字综合单元雷达计算机切备
void sub1553_busPower::on_pushButton_8_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x08;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x07:L频段雷达计算机切备");
}
//0x09：SXKu频段消浪涌开
void sub1553_busPower::on_pushButton_9_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x09;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x09:SXKu频段消浪涌开");
}
//0x0A：SXKu频段消浪涌关
void sub1553_busPower::on_pushButton_10_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x0A;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x0A:SXKu频段消浪涌关");
}
//0x0B：SXKu频段主份波束控制器开
void sub1553_busPower::on_pushButton_11_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x0B;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x0B:SXKu频段主份波束控制器开");
}
//0x0C：SXKu频段主份波束控制器关
void sub1553_busPower::on_pushButton_12_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x0C;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x0C:SXKu频段主份波束控制器关");
}
//0x0D：SXKu频段备份波束控制器开
void sub1553_busPower::on_pushButton_13_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x0D;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x0D:SXKu频段备份波束控制器开");
}
//0x0E：SXKu频段备份波束控制器关
void sub1553_busPower::on_pushButton_14_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x0E;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x0E:SXKu频段备份波束控制器关");
}
//0x0F：SXKu频段放电开关接通
void sub1553_busPower::on_pushButton_15_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x0F;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x0F:SXKu频段31V总电源开");
}
//0x10：SXKu频段放电开关断开
void sub1553_busPower::on_pushButton_16_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x10;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x10:SXKu频段31V总电源关");
}
//0x11：射频前端主加电
void sub1553_busPower::on_pushButton_17_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x11;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x11:可重构射频前端主份加电");
}
//0x12：射频前端主断电
void sub1553_busPower::on_pushButton_18_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x12;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x12:可重构射频前端主份断电");
}
//0x13：射频前端备加电
void sub1553_busPower::on_pushButton_19_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x13;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x13:可重构射频前端备份加电");
}
//0x14：射频前端备断电
void sub1553_busPower::on_pushButton_20_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x14;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x14:可重构射频前端备份断电");
}
//0x15：高算力平台1开
void sub1553_busPower::on_pushButton_21_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x15;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x15:可重构高算力平台1加电");
}
//0x16：高算力平台1关
void sub1553_busPower::on_pushButton_22_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x16;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x16:可重构高算力平台1断电");
}
//0x17：高算力平台2开
void sub1553_busPower::on_pushButton_23_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x17;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x17:可重构高算力平台2加电");
}
//0x18：高算力平台2关
void sub1553_busPower::on_pushButton_24_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x18;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x18:可重构高算力平台2断电");
}
//0x19：高算力平台1复位
void sub1553_busPower::on_pushButton_25_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x19;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x19:高算力平台1复位");
}
//0x1A：高算力平台2复位
void sub1553_busPower::on_pushButton_26_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x1A;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x1A:高算力平台2复位");
}
//0x1B：配电单元A组放电开关接通
void sub1553_busPower::on_pushButton_27_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x1B;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x1B:配电器A组放电开关接通指令");
}
//0x1C：配电单元A组放电开关断开
void sub1553_busPower::on_pushButton_28_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x1C;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x1C:配电器A组放电开关断开指令");
}
//0x1D：配电单元A组消浪涌开
void sub1553_busPower::on_pushButton_29_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x1D;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x1D:配电器A组消浪涌开关接通指令");
}
//0x1E：配电单元A组消浪涌关
void sub1553_busPower::on_pushButton_30_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x1E;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x1E:配电器A组消浪涌开关断开指令");
}
//0x1F：配电单元B组放电开关接通
void sub1553_busPower::on_pushButton_31_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x1F;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x1F:配电器B组放电开关接通指令");
}
//0x20：配电单元B组放电开关断开
void sub1553_busPower::on_pushButton_32_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x20;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x20:配电器B组放电开关断开指令");
}
//0x21：配电单元B组消浪涌开
void sub1553_busPower::on_pushButton_33_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x21;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x21:配电器B组消浪涌开关接通指令");
}
//0x22：配电单元B组消浪涌关
void sub1553_busPower::on_pushButton_34_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x22;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x22:配电器B组消浪涌开关断开指令");
}
//0x23：配电单元C组放电开关接通
void sub1553_busPower::on_pushButton_35_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x23;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x23:配电器C组放电开关接通指令");
}
//0x24：配电单元C组放电开关断开
void sub1553_busPower::on_pushButton_36_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x24;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x24:配电器C组放电开关断开指令");
}
//0x25：配电单元C组消浪涌开
void sub1553_busPower::on_pushButton_37_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x25;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x25:配电器C组消浪涌开关接通指令");
}
//0x26：配电单元C组消浪涌关
void sub1553_busPower::on_pushButton_38_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x26;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x26:配电器C组消浪涌开关断开指令");
}
//0x27：配电单元D组放电开关接通
void sub1553_busPower::on_pushButton_39_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x27;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x27:配电器D组放电开关接通指令");
}
//0x28：配电单元D组放电开关断开
void sub1553_busPower::on_pushButton_40_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x28;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x28:配电器D组放电开关断开指令");
}
//0x29：配电单元D组消浪涌开
void sub1553_busPower::on_pushButton_41_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x29;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x29:配电器D组消浪涌开关接通指令");
}
//0x2A：配电单元D组消浪涌关
void sub1553_busPower::on_pushButton_42_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x2A;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x2A:配电器D组消浪涌开关断开指令");
}
//0x2B：综合处理模块加电
void sub1553_busPower::on_pushButton_43_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x2B;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x2B:综合管控单元综合处理模块加电");
}
//0x2C：综合处理模块断电
void sub1553_busPower::on_pushButton_44_clicked()
{
    OC_power_control opc;
    memset(&opc,0,sizeof (opc));
    opc.ordermark = 0x07;
    opc.power_choose = 0x2C;

    //列表封装
    Pblic_Addorderlist((uchar*)&opc,sizeof (opc),"OC电源控制:0x2C:综合管控单元综合处理模块断电");
}


//    if("0x30:L频段综合单元定时波控切备"==ui->cB_Can_powercontrol->currentText())
//        cpc.power_choose=0x30;

//0x01：SXKu频段射频收发单元-接收开
void sub1553_busPower::on_pushButton_CAN_1_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x01;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x01：SXKu频段射频收发单元-接收开");
}
//0x02：SXKu频段射频收发单元-接收关
void sub1553_busPower::on_pushButton_CAN_2_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x02;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x02：SXKu频段射频收发单元-接收关");
}
//0x03：SXKu频段射频收发单元-发射开
void sub1553_busPower::on_pushButton_CAN_3_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x03;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x03：SXKu频段射频收发单元-发射开");
}
//0x04：SXKu频段射频收发单元-发射关
void sub1553_busPower::on_pushButton_CAN_4_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x04;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x04：SXKu频段射频收发单元-发射关");
}
//0x05：SXKu频段天线阵面1接收加电
void sub1553_busPower::on_pushButton_CAN_5_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x05;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x05：SXKu频段天线阵面1接收加电");
}
//0x06：SXKu频段天线阵面1接收断电
void sub1553_busPower::on_pushButton_CAN_6_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x06;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x06：SXKu频段天线阵面1接收断电");
}
//0x07：SXKu频段天线阵面1发射加电
void sub1553_busPower::on_pushButton_CAN_7_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x07;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x07：SXKu频段天线阵面1发射加电");
}
//0x08：SXKu频段天线阵面1发射断电
void sub1553_busPower::on_pushButton_CAN_8_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x08;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x08：SXKu频段天线阵面1发射断电");
}
//0x09：SXKu频段天线阵面2接收加电
void sub1553_busPower::on_pushButton_CAN_9_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x09;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x09：SXKu频段天线阵面2接收加电");
}
//0x0A：SXKu频段天线阵面2接收断电
void sub1553_busPower::on_pushButton_CAN_10_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x0A;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x0A：SXKu频段天线阵面2接收断电");
}
//0x0B：SXKu频段天线阵面2发射加电
void sub1553_busPower::on_pushButton_CAN_11_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x0B;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x0B：SXKu频段天线阵面2发射加电");
}
//0x0C：SXKu频段天线阵面2发射断电
void sub1553_busPower::on_pushButton_CAN_12_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x0C;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x0C：SXKu频段天线阵面2发射断电");
}
//0x0D：SXKu频段天线阵面3接收加电
void sub1553_busPower::on_pushButton_CAN_13_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x0D;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x0D：SXKu频段天线阵面3接收加电");
}
//0x0E：SXKu频段天线阵面3接收断电
void sub1553_busPower::on_pushButton_CAN_14_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x0E;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x0E：SXKu频段天线阵面3接收断电");
}
//0x0F：SXKu频段天线阵面3发射加电
void sub1553_busPower::on_pushButton_CAN_15_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x0F;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x0F：SXKu频段天线阵面3发射加电");
}
//0x10：SXKu频段天线阵面3发射断电
void sub1553_busPower::on_pushButton_CAN_16_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x10;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x10：SXKu频段天线阵面3发射断电");
}
//0x11：SXKu频段天线阵面4接收加电
void sub1553_busPower::on_pushButton_CAN_17_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x11;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x11：SXKu频段天线阵面4接收加电");
}
//0x12：SXKu频段天线阵面4接收断电
void sub1553_busPower::on_pushButton_CAN_18_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x12;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x12：SXKu频段天线阵面4接收断电");
}
//0x13：SXKu频段天线阵面4发射加电
void sub1553_busPower::on_pushButton_CAN_19_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x13;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x13：SXKu频段天线阵面4发射加电");
}
//0x14：SXKu频段天线阵面4发射断电
void sub1553_busPower::on_pushButton_CAN_20_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x14;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x14：SXKu频段天线阵面4发射断电");
}
//0x15：L频段射频综合单元开
void sub1553_busPower::on_pushButton_CAN_21_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x15;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x15：L频段射频综合单元开");
}
//0x16：L频段射频综合单元关
void sub1553_busPower::on_pushButton_CAN_22_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x16;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x16：L频段射频综合单元关");
}
//0x17：L频段数字综合单元定时波控加电
void sub1553_busPower::on_pushButton_CAN_23_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x17;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x17：L频段数字综合单元定时波控加电");
}
//0x18：L频段数字综合单元定时波控断电
void sub1553_busPower::on_pushButton_CAN_24_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x18;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x18：L频段数字综合单元定时波控断电");
}
//0x19：L频段数字综合单元定时波控切主
void sub1553_busPower::on_pushButton_CAN_25_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x19;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x19：L频段数字综合单元定时波控切主");
}
//0x1A：L频段天线阵面1接收加电
void sub1553_busPower::on_pushButton_CAN_26_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x1A;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x1A：L频段天线阵面1接收加电");
}
//0x1B：L频段天线阵面1接收断电
void sub1553_busPower::on_pushButton_CAN_27_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x1B;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x1B：L频段天线阵面1接收断电");
}
//0x1C：L频段天线阵面1发射加电
void sub1553_busPower::on_pushButton_CAN_28_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x1C;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x1C：L频段天线阵面1发射加电");
}
//0x1D：L频段天线阵面1发射断电
void sub1553_busPower::on_pushButton_CAN_29_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x1D;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x1D：L频段天线阵面1发射断电");
}
//0x1E：L频段天线阵面2接收加电
void sub1553_busPower::on_pushButton_CAN_30_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x1E;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x1E：L频段天线阵面2接收加电");
}
//0x1F：L频段天线阵面2接收断电
void sub1553_busPower::on_pushButton_CAN_31_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x1F;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x1F：L频段天线阵面2接收断电");
}
//0x20：L频段天线阵面2发射加电
void sub1553_busPower::on_pushButton_CAN_32_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x20;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x20：L频段天线阵面2发射加电");
}
//0x21：L频段天线阵面2发射断电
void sub1553_busPower::on_pushButton_CAN_33_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x21;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x21：L频段天线阵面2发射断电");
}
//0x22：L频段天线阵面3接收加电
void sub1553_busPower::on_pushButton_CAN_34_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x22;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x22：L频段天线阵面3接收加电");
}
//0x23：L频段天线阵面3接收断电
void sub1553_busPower::on_pushButton_CAN_35_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x23;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x23：L频段天线阵面3接收断电");
}
//0x24：L频段天线阵面3发射加电
void sub1553_busPower::on_pushButton_CAN_36_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x24;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x24：L频段天线阵面3发射加电");
}
//0x25：L频段天线阵面3发射断电
void sub1553_busPower::on_pushButton_CAN_37_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x25;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x25：L频段天线阵面3发射断电");
}
//0x26：L频段天线阵面4接收加电
void sub1553_busPower::on_pushButton_CAN_38_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x26;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x26：L频段天线阵面4接收加电");
}
//0x27：L频段天线阵面4接收断电
void sub1553_busPower::on_pushButton_CAN_39_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x27;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x27：L频段天线阵面4接收断电");
}
//0x28：L频段天线阵面4发射加电
void sub1553_busPower::on_pushButton_CAN_40_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x28;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x28：L频段天线阵面4发射加电");
}
//0x29：L频段天线阵面4发射断电
void sub1553_busPower::on_pushButton_CAN_41_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x29;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x29：L频段天线阵面4发射断电");
}
//0x2A：L频段数字综合单元定时波控切备
void sub1553_busPower::on_pushButton_CAN_42_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x2A;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x2A：L频段数字综合单元定时波控切备");
}
//0x2B：L频段天线全阵面收发加电
void sub1553_busPower::on_pushButton_CAN_48_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x2B;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x2B:L频段天线全阵面收发加电");
}
//0x2C：L频段天线全阵面收发断电
void sub1553_busPower::on_pushButton_0x2C_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x2C;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x2C:L频段天线全阵面收发断电");
}
//0x2D:SXKu频段全阵断电
void sub1553_busPower::on_pushButton_0x2D_clicked()
{
    Can_power_control cpc;
    memset(&cpc,0,sizeof (cpc));
    cpc.ordermark = 0x08;
    cpc.power_choose = 0x2D;

    //列表封装
    Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),"CAN电源控制:0x2D:SXKu频段全阵断电");
}

//OC控制的电源_多项生成
void sub1553_busPower::on_pushButton_OC_SUM_clicked()
{
    QVector<char> v_oc;

    if(ui->checkBox_OC_0x11->isChecked())v_oc.push_back(0x11);
    if(ui->checkBox_OC_0x12->isChecked())v_oc.push_back(0x12);
    if(ui->checkBox_OC_0x13->isChecked())v_oc.push_back(0x13);
    if(ui->checkBox_OC_0x14->isChecked())v_oc.push_back(0x14);
    if(ui->checkBox_OC_0x15->isChecked())v_oc.push_back(0x15);
    if(ui->checkBox_OC_0x16->isChecked())v_oc.push_back(0x16);
    if(ui->checkBox_OC_0x17->isChecked())v_oc.push_back(0x17);
    if(ui->checkBox_OC_0x18->isChecked())v_oc.push_back(0x18);
    if(ui->checkBox_OC_0x19->isChecked())v_oc.push_back(0x19);
    if(ui->checkBox_OC_0x1A->isChecked())v_oc.push_back(0x1A);

    if(ui->checkBox_OC_0x2B->isChecked())v_oc.push_back(0x2B);
    if(ui->checkBox_OC_0x2C->isChecked())v_oc.push_back(0x2C);


    succ_send=false;
    for (int i=0;i<v_oc.size();i++) {
        OC_power_control opc;
        memset(&opc,0,sizeof (opc));
        opc.ordermark = 0x07;
        opc.power_choose = v_oc.at(i);

        //列表封装
        //QString str=QString("OC电源控制:0x%1").arg(v_oc.at(i),2,16,QLatin1Char('0')).toUpper();
        Pblic_Addorderlist((uchar*)&opc,sizeof (opc),OC_kind[v_oc.at(i)]);

    }
    succ_send=true;
    if(v_oc.size())emit success_snack("成功");
}


//OC控制的电源_多项生成
void sub1553_busPower::on_pushButton_CAN_SUM_clicked()
{
    QVector<char> v_can;

    if(ui->checkBox_OC_0x1B->isChecked())v_can.push_back(0x1B);
    if(ui->checkBox_OC_0x1C->isChecked())v_can.push_back(0x1C);
    if(ui->checkBox_OC_0x1D->isChecked())v_can.push_back(0x1D);
    if(ui->checkBox_OC_0x1E->isChecked())v_can.push_back(0x1E);
    if(ui->checkBox_OC_0x1F->isChecked())v_can.push_back(0x1F);
    if(ui->checkBox_OC_0x20->isChecked())v_can.push_back(0x20);
    if(ui->checkBox_OC_0x21->isChecked())v_can.push_back(0x21);
    if(ui->checkBox_OC_0x22->isChecked())v_can.push_back(0x22);
    if(ui->checkBox_OC_0x23->isChecked())v_can.push_back(0x23);
    if(ui->checkBox_OC_0x24->isChecked())v_can.push_back(0x24);
    if(ui->checkBox_OC_0x25->isChecked())v_can.push_back(0x25);
    if(ui->checkBox_OC_0x26->isChecked())v_can.push_back(0x26);
    if(ui->checkBox_OC_0x27->isChecked())v_can.push_back(0x27);
    if(ui->checkBox_OC_0x28->isChecked())v_can.push_back(0x28);
    if(ui->checkBox_OC_0x29->isChecked())v_can.push_back(0x29);
    if(ui->checkBox_OC_0x2A->isChecked())v_can.push_back(0x2A);

    succ_send=false;
    for (int i=0;i<v_can.size();i++) {
        OC_power_control opc;
        memset(&opc,0,sizeof (opc));
        opc.ordermark = 0x07;
        opc.power_choose = v_can.at(i);

        //列表封装
        //QString str=QString("OC电源控制:0x%1").arg(v_oc.at(i),2,16,QLatin1Char('0')).toUpper();
        Pblic_Addorderlist((uchar*)&opc,sizeof (opc),OC_kind[v_can.at(i)]);

    }
    succ_send=true;
    if(v_can.size())emit success_snack("成功");
}





//sxku分类
void sub1553_busPower::on_pushButton_CAN_SUM_2_clicked()
{
    QVector<char> v_oc;
    if(ui->checkBox_OC_0x09->isChecked())v_oc.push_back(0x09);
    if(ui->checkBox_OC_0x0A->isChecked())v_oc.push_back(0x0A);
    if(ui->checkBox_OC_0x0B->isChecked())v_oc.push_back(0x0B);
    if(ui->checkBox_OC_0x0C->isChecked())v_oc.push_back(0x0C);
    if(ui->checkBox_OC_0x0D->isChecked())v_oc.push_back(0x0D);
    if(ui->checkBox_OC_0x0F->isChecked())v_oc.push_back(0x0F);
    if(ui->checkBox_OC_0x10->isChecked())v_oc.push_back(0x10);

    QVector<char> v_can;
    if(ui->checkBox_CAN_0x01->isChecked())v_can.push_back(0x01);
    if(ui->checkBox_CAN_0x02->isChecked())v_can.push_back(0x02);
    if(ui->checkBox_CAN_0x03->isChecked())v_can.push_back(0x03);
    if(ui->checkBox_CAN_0x04->isChecked())v_can.push_back(0x04);
    if(ui->checkBox_CAN_0x05->isChecked())v_can.push_back(0x05);
    if(ui->checkBox_CAN_0x06->isChecked())v_can.push_back(0x06);
    if(ui->checkBox_CAN_0x07->isChecked())v_can.push_back(0x07);
    if(ui->checkBox_CAN_0x08->isChecked())v_can.push_back(0x08);
    if(ui->checkBox_CAN_0x09->isChecked())v_can.push_back(0x09);
    if(ui->checkBox_CAN_0x0A->isChecked())v_can.push_back(0x0A);
    if(ui->checkBox_CAN_0x0B->isChecked())v_can.push_back(0x0B);
    if(ui->checkBox_CAN_0x0C->isChecked())v_can.push_back(0x0C);
    if(ui->checkBox_CAN_0x0D->isChecked())v_can.push_back(0x0D);
    if(ui->checkBox_CAN_0x0F->isChecked())v_can.push_back(0x0F);
    if(ui->checkBox_CAN_0x10->isChecked())v_can.push_back(0x10);
    if(ui->checkBox_CAN_0x11->isChecked())v_can.push_back(0x11);
    if(ui->checkBox_CAN_0x12->isChecked())v_can.push_back(0x12);
    if(ui->checkBox_CAN_0x13->isChecked())v_can.push_back(0x13);
    if(ui->checkBox_CAN_0x14->isChecked())v_can.push_back(0x14);
    if(ui->checkBox_CAN_0x2D->isChecked())v_can.push_back(0x2D);


    succ_send=false;
    for (int i=0;i<v_oc.size();i++) {
        OC_power_control opc;
        memset(&opc,0,sizeof (opc));
        opc.ordermark = 0x07;
        opc.power_choose = v_oc.at(i);

        //列表封装
        //QString str=QString("OC电源控制:0x%1").arg(v_oc.at(i),2,16,QLatin1Char('0')).toUpper();
        Pblic_Addorderlist((uchar*)&opc,sizeof (opc),OC_kind[v_oc.at(i)]);

    }
    for (int i=0;i<v_can.size();i++) {
        Can_power_control cpc;
        memset(&cpc,0,sizeof (cpc));
        cpc.ordermark = 0x08;
        cpc.power_choose = v_can.at(i);

        //列表封装
        Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),CAN_kind[v_can.at(i)]);

    }
    succ_send=true;
    if(v_oc.size())emit success_snack("成功");
    else if(v_can.size())emit success_snack("成功");
    else{}
}
//L频段
void sub1553_busPower::on_pushButton_CAN_SUM_4_clicked()
{
        QVector<char> v_oc;
        if(ui->checkBox_OC_0x01->isChecked())v_oc.push_back(0x01);
        if(ui->checkBox_OC_0x02->isChecked())v_oc.push_back(0x02);
        if(ui->checkBox_OC_0x03->isChecked())v_oc.push_back(0x03);
        if(ui->checkBox_OC_0x04->isChecked())v_oc.push_back(0x04);
        if(ui->checkBox_OC_0x05->isChecked())v_oc.push_back(0x05);
        if(ui->checkBox_OC_0x06->isChecked())v_oc.push_back(0x06);
        if(ui->checkBox_OC_0x07->isChecked())v_oc.push_back(0x07);
        if(ui->checkBox_OC_0x08->isChecked())v_oc.push_back(0x08);

        QVector<char> v_can;
        if(ui->checkBox_CAN_0x15->isChecked())v_can.push_back(0x15);
        if(ui->checkBox_CAN_0x16->isChecked())v_can.push_back(0x16);
        if(ui->checkBox_CAN_0x17->isChecked())v_can.push_back(0x17);
        if(ui->checkBox_CAN_0x18->isChecked())v_can.push_back(0x18);
        if(ui->checkBox_CAN_0x19->isChecked())v_can.push_back(0x19);
        if(ui->checkBox_CAN_0x1A->isChecked())v_can.push_back(0x1A);
        if(ui->checkBox_CAN_0x1B->isChecked())v_can.push_back(0x1B);
        if(ui->checkBox_CAN_0x1C->isChecked())v_can.push_back(0x1C);
        if(ui->checkBox_CAN_0x1D->isChecked())v_can.push_back(0x1D);
        if(ui->checkBox_CAN_0x1E->isChecked())v_can.push_back(0x1E);
        if(ui->checkBox_CAN_0x1F->isChecked())v_can.push_back(0x1F);
        if(ui->checkBox_CAN_0x20->isChecked())v_can.push_back(0x20);
        if(ui->checkBox_CAN_0x21->isChecked())v_can.push_back(0x21);
        if(ui->checkBox_CAN_0x22->isChecked())v_can.push_back(0x22);
        if(ui->checkBox_CAN_0x23->isChecked())v_can.push_back(0x23);
        if(ui->checkBox_CAN_0x24->isChecked())v_can.push_back(0x24);
        if(ui->checkBox_CAN_0x25->isChecked())v_can.push_back(0x25);
        if(ui->checkBox_CAN_0x26->isChecked())v_can.push_back(0x26);
        if(ui->checkBox_CAN_0x27->isChecked())v_can.push_back(0x27);
        if(ui->checkBox_CAN_0x28->isChecked())v_can.push_back(0x28);
        if(ui->checkBox_CAN_0x29->isChecked())v_can.push_back(0x29);
        if(ui->checkBox_CAN_0x2A->isChecked())v_can.push_back(0x2A);
        if(ui->checkBox_CAN_0x2B->isChecked())v_can.push_back(0x2B);
        if(ui->checkBox_CAN_0x2C->isChecked())v_can.push_back(0x2C);

        succ_send=false;
        for (int i=0;i<v_oc.size();i++) {
            OC_power_control opc;
            memset(&opc,0,sizeof (opc));
            opc.ordermark = 0x07;
            opc.power_choose = v_oc.at(i);

            //列表封装
            //QString str=QString("OC电源控制:0x%1").arg(v_oc.at(i),2,16,QLatin1Char('0')).toUpper();
            Pblic_Addorderlist((uchar*)&opc,sizeof (opc),OC_kind[v_oc.at(i)]);

        }
        for (int i=0;i<v_can.size();i++) {
            Can_power_control cpc;
            memset(&cpc,0,sizeof (cpc));
            cpc.ordermark = 0x08;
            cpc.power_choose = v_can.at(i);

            //列表封装
            Pblic_Addorderlist((uchar*)&cpc,sizeof (cpc),CAN_kind[v_can.at(i)]);

        }
        succ_send=true;
        if(v_oc.size())emit success_snack("成功");
        else if(v_can.size())emit success_snack("成功");
        else{}
}

//清空OC勾选
void sub1553_busPower::on_pushButton_Clear_OC_clicked()
{



    ui->checkBox_OC_0x11->setChecked(0);
    ui->checkBox_OC_0x12->setChecked(0);
    ui->checkBox_OC_0x13->setChecked(0);
    ui->checkBox_OC_0x14->setChecked(0);
    ui->checkBox_OC_0x15->setChecked(0);
    ui->checkBox_OC_0x16->setChecked(0);
    ui->checkBox_OC_0x17->setChecked(0);
    ui->checkBox_OC_0x18->setChecked(0);
    ui->checkBox_OC_0x19->setChecked(0);
    ui->checkBox_OC_0x1A->setChecked(0);



    ui->checkBox_OC_0x2B->setChecked(0);
    ui->checkBox_OC_0x2C->setChecked(0);
}
//清空CAN勾选
void sub1553_busPower::on_pushButton_Clear_CAN_clicked()
{
    ui->checkBox_OC_0x1B->setChecked(0);
    ui->checkBox_OC_0x1C->setChecked(0);
    ui->checkBox_OC_0x1D->setChecked(0);
    ui->checkBox_OC_0x1E->setChecked(0);
    ui->checkBox_OC_0x1F->setChecked(0);
    ui->checkBox_OC_0x20->setChecked(0);
    ui->checkBox_OC_0x21->setChecked(0);
    ui->checkBox_OC_0x22->setChecked(0);
    ui->checkBox_OC_0x23->setChecked(0);
    ui->checkBox_OC_0x24->setChecked(0);
    ui->checkBox_OC_0x25->setChecked(0);
    ui->checkBox_OC_0x26->setChecked(0);
    ui->checkBox_OC_0x27->setChecked(0);
    ui->checkBox_OC_0x28->setChecked(0);
    ui->checkBox_OC_0x29->setChecked(0);
    ui->checkBox_OC_0x2A->setChecked(0);



}


void sub1553_busPower::on_pushButton_Clear_CAN_2_clicked()
{
    ui->checkBox_OC_0x09->setChecked(0);
    ui->checkBox_OC_0x0A->setChecked(0);
    ui->checkBox_OC_0x0B->setChecked(0);
    ui->checkBox_OC_0x0C->setChecked(0);
    ui->checkBox_OC_0x0D->setChecked(0);
    ui->checkBox_OC_0x0E->setChecked(0);
    ui->checkBox_OC_0x0F->setChecked(0);
    ui->checkBox_OC_0x10->setChecked(0);

    ui->checkBox_CAN_0x01->setChecked(0);
    ui->checkBox_CAN_0x02->setChecked(0);
    ui->checkBox_CAN_0x03->setChecked(0);
    ui->checkBox_CAN_0x04->setChecked(0);
    ui->checkBox_CAN_0x05->setChecked(0);
    ui->checkBox_CAN_0x06->setChecked(0);
    ui->checkBox_CAN_0x07->setChecked(0);
    ui->checkBox_CAN_0x08->setChecked(0);
    ui->checkBox_CAN_0x09->setChecked(0);
    ui->checkBox_CAN_0x0A->setChecked(0);
    ui->checkBox_CAN_0x0B->setChecked(0);
    ui->checkBox_CAN_0x0C->setChecked(0);
    ui->checkBox_CAN_0x0D->setChecked(0);
    ui->checkBox_CAN_0x0E->setChecked(0);
    ui->checkBox_CAN_0x0F->setChecked(0);
    ui->checkBox_CAN_0x10->setChecked(0);
    ui->checkBox_CAN_0x11->setChecked(0);
    ui->checkBox_CAN_0x12->setChecked(0);
    ui->checkBox_CAN_0x13->setChecked(0);
    ui->checkBox_CAN_0x14->setChecked(0);
    ui->checkBox_CAN_0x2D->setChecked(0);
}

void sub1553_busPower::on_pushButton_Clear_CAN_4_clicked()
{
    ui->checkBox_OC_0x01->setChecked(0);
    ui->checkBox_OC_0x02->setChecked(0);
    ui->checkBox_OC_0x03->setChecked(0);
    ui->checkBox_OC_0x04->setChecked(0);
    ui->checkBox_OC_0x05->setChecked(0);
    ui->checkBox_OC_0x06->setChecked(0);
    ui->checkBox_OC_0x07->setChecked(0);
    ui->checkBox_OC_0x08->setChecked(0);

    ui->checkBox_CAN_0x15->setChecked(0);
    ui->checkBox_CAN_0x16->setChecked(0);
    ui->checkBox_CAN_0x17->setChecked(0);
    ui->checkBox_CAN_0x18->setChecked(0);
    ui->checkBox_CAN_0x19->setChecked(0);
    ui->checkBox_CAN_0x1A->setChecked(0);
    ui->checkBox_CAN_0x1B->setChecked(0);
    ui->checkBox_CAN_0x1C->setChecked(0);
    ui->checkBox_CAN_0x1D->setChecked(0);
    ui->checkBox_CAN_0x1E->setChecked(0);
    ui->checkBox_CAN_0x1F->setChecked(0);
    ui->checkBox_CAN_0x20->setChecked(0);
    ui->checkBox_CAN_0x21->setChecked(0);
    ui->checkBox_CAN_0x22->setChecked(0);
    ui->checkBox_CAN_0x23->setChecked(0);
    ui->checkBox_CAN_0x24->setChecked(0);
    ui->checkBox_CAN_0x25->setChecked(0);
    ui->checkBox_CAN_0x26->setChecked(0);
    ui->checkBox_CAN_0x27->setChecked(0);
    ui->checkBox_CAN_0x28->setChecked(0);
    ui->checkBox_CAN_0x29->setChecked(0);
    ui->checkBox_CAN_0x2A->setChecked(0);
    ui->checkBox_CAN_0x2B->setChecked(0);
    ui->checkBox_CAN_0x2C->setChecked(0);
}
