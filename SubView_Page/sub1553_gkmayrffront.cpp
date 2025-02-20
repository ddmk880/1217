#include "sub1553_gkmayrffront.h"

#include "ui_sub1553_gkmayrffront.h"

sub1553_gkmayrffront::sub1553_gkmayrffront(QWidget *parent)
    : QWidget(parent), ui(new Ui::sub1553_gkmayrffront) {
    ui->setupUi(this);
}

sub1553_gkmayrffront::~sub1553_gkmayrffront() { delete ui; }

void sub1553_gkmayrffront::Pblic_Addorderlist(uchar *databuff, int buffLen,
                                              QString buffname) {
    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 5;
    order_data.gap_time = 1;
    order_data.order_name = buffname;
    order_data.order_kind = 2;//0x0086 功能识别码  管控-可重构射频前端
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff, buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

// 可重构射频前端通道、本振加电控制0x58
void sub1553_gkmayrffront::on_pB_channel_power_control_clicked() {
    Channel_local_powercontrol clpc;
    memset(&clpc, 0, sizeof(clpc));

    // 指令标识
    clpc.ordermark = 0x58;
    // L频段开关
    clpc.L_cSwitch = ui->cB_Lchannel_switch->currentIndex();
    // SXKu频段1、2接收通道开关
    clpc.SXKu_12receive_switch = ui->cB_SXKu_12receive_switch->currentIndex();
    // SXKu频段3、4接收通道开关
    clpc.SXKu_34receive_switch = ui->cB_SXKu_34receive_switch->currentIndex();
    // SXKu频段5、6接收通道开关
    clpc.SXKu_56receive_switch = ui->cB_SXKu_56receive_switch->currentIndex();
    // SXKu频段1、2发射通道开关
    clpc.SXKu_12emit_switch = ui->cB_SXKu_12emit_switch->currentIndex();
    // SXKu频段3、4发射通道开关
    clpc.SXKu_34emit_switch = ui->cB_SXKu_34emit_switch->currentIndex();
    // SXKu频段5、6发射通道开关
    clpc.SXKu_56emit_switch = ui->cB_SXKu_56emit_switch->currentIndex();
    // 宽带一本振开关
    clpc.broadband_onebook_switch = ui->cB_SXKu_broadband_switch->currentIndex();
    // 高相噪本振开关
    uchar tmp1=ui->cB_highphase_noise_1->currentIndex();
    uchar tmp2=ui->cB_highphase_noise_2->currentIndex();

    clpc.highnoise_switch = tmp1+(tmp2<<4);
    // 二本振开关
    tmp1=ui->cB_twoBooks_1->currentIndex();
    tmp2=ui->cB_twoBooks_2->currentIndex();
    clpc.twoBooks_switch =tmp1+(tmp2<<4);
    //校验和crc
//    uchar* strcrc=new uchar[sizeof (clpc)];
//    memcpy(strcrc,&clpc,sizeof (clpc));
//    ushort crcs=0;
//    for (uint i=0;i<sizeof (clpc)-2;i++) {
//        crcs+=strcrc[i];
//    }
//    clpc.crc=qToBigEndian(crcs);
    clpc.bl=0xff;
    // 列表封装
    Pblic_Addorderlist((uchar *)&clpc, sizeof(clpc), "可重构射频前端通道、本振加电控制");
}


// 可重构射频前端中频切换模块设置0x59
void sub1553_gkmayrffront::on_pB_zpchooseSet_clicked() {
    Mid_switch str;
    memset(&str, 0, sizeof(str));

    // 指令标识
    str.ordermark = 0x59;
    // 中频切换
    str.zp_qh = ui->cB_zpset->currentIndex();

    // 列表封装
    Pblic_Addorderlist((uchar *)&str, sizeof(str), "可重构射频前端中频切换模块设置 : "+ui->cB_zpset->currentText());
}



// 可重构射频前端通道、本振控制选择0x5A
void sub1553_gkmayrffront::on_pB_channel_control_choose_clicked() {
    Channel_local_controlchoose clcc;
    memset(&clcc, 0, sizeof(clcc));
    // 指令标识
    clcc.ordermark = 0x5A;
    // L频段通道1
    clcc.L_channel1 = ui->cB_Lchannel_1->currentIndex();
    // L频段通道2
    clcc.L_channel2 = ui->cB_Lchannel_2->currentIndex();
    // L频段通道3
    clcc.L_channel3 = ui->cB_Lchannel_3->currentIndex();
    // L频段通道4
    clcc.L_channel4 = ui->cB_Lchannel_4->currentIndex();
    // L频段通道5
    clcc.L_channel5 = ui->cB_Lchannel_5->currentIndex();
    // L频段通道6
    clcc.L_channel6 = ui->cB_Lchannel_6->currentIndex();
    // SXKu频段通道1和2
    clcc.SXKu_channel_12 = ui->cB_SXKu_channel_12->currentIndex();
    // SXKu频段通道3和4
    clcc.SXKu_channel_34 = ui->cB_SXKu_channel_34->currentIndex();
    // SXKu频段通道5和6
    clcc.SXKu_channel_56 = ui->cB_SXKu_channel_56->currentIndex();
    // 宽带一本振1频率
    clcc.broadband_onebook_1 = ui->cB_broadband_onebook_1->currentIndex();
    // 宽带一本振2频率
    clcc.broadband_onebook_2 = ui->cB_broadband_onebook_2->currentIndex();
    // 高相噪本振频率
    clcc.highnoise = ui->cB_highnoise_radio->currentIndex();
    //
    clcc.bl=0xff;
    // 列表封装
    Pblic_Addorderlist((uchar *)&clcc, sizeof(clcc), "可重构射频前端通道、本振控制选择");
}


void sub1553_gkmayrffront::on_cB_Lchannel_1_activated(int index) {
    ui->cB_Lchannel_2->setCurrentIndex(index);
    ui->cB_Lchannel_3->setCurrentIndex(index);
    ui->cB_Lchannel_4->setCurrentIndex(index);
    ui->cB_Lchannel_5->setCurrentIndex(index);
    ui->cB_Lchannel_6->setCurrentIndex(index);
}

void sub1553_gkmayrffront::on_cB_SXKu_channel_12_activated(int index) {
    ui->cB_SXKu_channel_34->setCurrentIndex(index);
    ui->cB_SXKu_channel_56->setCurrentIndex(index);
    ui->cB_broadband_onebook_1->setCurrentIndex(index);
    ui->cB_broadband_onebook_2->setCurrentIndex(index);
    ui->cB_highnoise_radio->setCurrentIndex(index);
}
