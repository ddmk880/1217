#include "sub1553_tcmayrffront.h"
#include "ui_sub1553_tcmayrffront.h"

sub1553_tcmayrffront::sub1553_tcmayrffront(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_tcmayrffront)
{
    ui->setupUi(this);
}

sub1553_tcmayrffront::~sub1553_tcmayrffront()
{
    delete ui;
}

void sub1553_tcmayrffront::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 18;
    order_data.gap_time = 1;
    order_data.order_name = "透传-"+buffname;
    order_data.order_kind = 13;
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff, buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

//通道、本振加电控制 C72
void sub1553_tcmayrffront::on_pB_channel_power_C72_clicked()
{
    Channel_local_powercontrolC72 clpc;
    memset(&clpc, 0, sizeof(clpc));
    // 指令长度
    clpc.order_len=qToBigEndian((ushort) sizeof (clpc));
    // 指令标识
    clpc.ordermark = 0x72;
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
    clpc.highnoise_switch = ui->cB_highphase_noise_1->currentIndex() +
                            (ui->cB_highphase_noise_2->currentIndex() << 4);
    // 二本振开关
    clpc.twoBooks_switch = ui->cB_twoBooks_1->currentIndex() +
                           (ui->cB_twoBooks_2->currentIndex() << 4);

    //校验和
    uchar* strcrc=new uchar[sizeof (clpc)];
    memcpy(strcrc,&clpc,sizeof (clpc));
    ushort crc=0;
    for (uint i=0;i<sizeof (clpc)-2;i++) {
        crc+=strcrc[i];
    }
    clpc.crc=qToBigEndian(crc);
    delete [] strcrc;
    // 列表封装
    Pblic_Addorderlist((uchar *)&clpc, sizeof(clpc), "通道,本振加电控制");
}

//中频切换模块设置 c73
void sub1553_tcmayrffront::on_pB_zpchooseSet_C73_clicked()
{
    str_C73 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.ordermark=0x73;
    //中频切换
    arr.zp_qh=ui->cB_zpset->currentIndex();
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    delete [] strcrc;
    // 列表封装
    Pblic_Addorderlist((uchar *)&arr, sizeof(arr), "中频切换模块设置");
}
//通道、本振控制选择c74
void sub1553_tcmayrffront::on_pB_channel_control_C74_clicked()
{
    Channel_local_controlchooseC74 clcc;
    memset(&clcc, 0, sizeof(clcc));
    // 指令长度
    clcc.order_len=qToBigEndian((ushort) sizeof (clcc));
    // 指令标识
    clcc.ordermark = 0x74;
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
    //校验和
    uchar* strcrc=new uchar[sizeof (clcc)];
    memcpy(strcrc,&clcc,sizeof (clcc));
    ushort crc=0;
    for (uint i=0;i<sizeof (clcc)-2;i++) {
        crc+=strcrc[i];
    }
    clcc.crc=qToBigEndian(crc);
    delete [] strcrc;
    // 列表封装
    Pblic_Addorderlist((uchar *)&clcc, sizeof(clcc), "通道,本振控制选择");
}
