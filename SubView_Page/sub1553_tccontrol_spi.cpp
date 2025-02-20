#include "sub1553_tccontrol_spi.h"

#include "ui_sub1553_tccontrol_spi.h"

sub1553_tccontrol_spi::sub1553_tccontrol_spi(QWidget* parent)
    : QWidget(parent), ui(new Ui::sub1553_tccontrol_spi) {
    ui->setupUi(this);

    ui->comboBox_bkChoose->setStyleSheet("background-color:rgb(210,210,210)");
}

sub1553_tccontrol_spi::~sub1553_tccontrol_spi() { delete ui; }

void sub1553_tccontrol_spi::Pblic_Addorderlist(uchar* databuff, int buffLen,
                                               QString buffname) {
    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 14;
    order_data.gap_time = 1;
    order_data.order_name ="透传-"+ buffname;
    if(ui->comboBox_bkChoose->currentIndex()==0)
    {
        order_data.order_kind = 7 + ui->cB_gslChoose_spi->currentIndex();//1553发送类型
    }
    else
    {
        order_data.order_kind =9;//can发送类型
        order_data.order_name = buffname+" CAN";
    }
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff, buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

// 可重构射频前端L频段发射通道设置
void sub1553_tccontrol_spi::on_pushButton_Lpd_SendSet_clicked() {
    Str_L_SendSet L_sendset;
    memset(&L_sendset, 0, sizeof(L_sendset));
    // 帧头
    L_sendset.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    L_sendset.data_len = qToBigEndian((ushort)(sizeof(L_sendset) - 4));
    // 指令标识
    L_sendset.order_mark = 0x73;
    // 通道选择
    L_sendset.ad_choose = ui->comboBox_Lsendad->currentIndex();
    // 接收衰减
    L_sendset.send_down = ui->lineEdit_Lsenddown->text().toInt();

    // 保留
    // 校验和
    uchar* strcrc = new uchar[sizeof(L_sendset)];
    memcpy(strcrc, &L_sendset, sizeof(L_sendset));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(L_sendset) - 4; i++) {
        crc += strcrc[i];
    }
    L_sendset.crc = qToBigEndian(crc);
    // 帧尾
    L_sendset.frame_end = qToBigEndian((ushort)0x55AA);
    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (L_sendset);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &L_sendset, sizeof(L_sendset));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"可重构射频前端--L频段发射通道设置");

        delete[] strcrc;

        return;

    }
    // 列表封装
    Pblic_Addorderlist((uchar*)&L_sendset, sizeof(L_sendset),"可重构射频前端--L频段发射通道设置");
    delete[] strcrc;
}

// 可重构射频前端SXKu频段接收通道设置
void sub1553_tccontrol_spi::on_pushButton_sxkuReSet_clicked() {
    Str_SxkuReSetjs sxku_reset;
    memset(&sxku_reset, 0, sizeof(sxku_reset));
    // 帧头
    sxku_reset.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    sxku_reset.data_len = qToBigEndian((ushort)(sizeof(sxku_reset) - 4));
    // 指令标识
    sxku_reset.order_mark = 0x74;
    // 通道选择
    sxku_reset.ad_choose = ui->comboBox_adchoose->currentIndex();
    // SXKu频段第一级放大器使能
    sxku_reset.first_enable = ui->comboBox_firEnable->currentIndex();
    // SXKu频段射频衰减
    sxku_reset.sp_down = ui->comboBox_spdown->currentIndex();
    // 接收衰减
    sxku_reset.recive_down = ui->lineEdit_recdown->text().toInt();
    // 宽带一本振1频率
    sxku_reset.wide_fre1 = ui->lineEdit_wide1fre->text().toInt();
    // 宽带一本振2频率
    sxku_reset.wide_fre2 = ui->lineEdit_wide2fre->text().toInt();
    // 高相噪本振频率
    sxku_reset.gx_fre = ui->lineEdit_gxfre->text().toInt();
    // 保留
    // 校验和
    uchar* strcrc = new uchar[sizeof(sxku_reset)];
    memcpy(strcrc, &sxku_reset, sizeof(sxku_reset));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(sxku_reset) - 4; i++) {
        crc += strcrc[i];
    }
    sxku_reset.crc = qToBigEndian(crc);
    // 帧尾
    sxku_reset.frame_end = qToBigEndian((ushort)0x55AA);

    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (sxku_reset);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &sxku_reset, sizeof(sxku_reset));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"可重构射频前端--SXKu频段接收通道设置");

        delete[] strcrc;

        return;

    }
    // 列表封装
    Pblic_Addorderlist((uchar*)&sxku_reset, sizeof(sxku_reset), "可重构射频前端--SXKu频段接收通道设置");
    delete[] strcrc;
}

// 可重构射频前端SXKu频段发射通道设置
void sub1553_tccontrol_spi::on_pushButton_sxkuSendSet_2_clicked() {
    Str_SxkuReSetfs sxku_reset;
    memset(&sxku_reset, 0, sizeof(sxku_reset));
    // 帧头
    sxku_reset.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    sxku_reset.data_len = qToBigEndian((ushort)(sizeof(sxku_reset) - 4));
    // 指令标识
    sxku_reset.order_mark = 0x75;
    // 通道选择
    sxku_reset.ad_choose = ui->comboBox_adchoose_2->currentIndex();
    // 接收衰减
    sxku_reset.recive_down = ui->lineEdit_recdown_2->text().toInt();
    // 宽带一本振1频率
    sxku_reset.wide_fre1 = ui->lineEdit_wide1fre_2->text().toInt();
    // 宽带一本振2频率
    sxku_reset.wide_fre2 = ui->lineEdit_wide2fre_2->text().toInt();
    // 高相噪本振频率
    sxku_reset.gx_fre = ui->lineEdit_gxfre_2->text().toInt();
    // 保留
    sxku_reset.bl[0] = sxku_reset.bl[1] = 0;
    // 校验和
    uchar* strcrc = new uchar[sizeof(sxku_reset)];
    memcpy(strcrc, &sxku_reset, sizeof(sxku_reset));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(sxku_reset) - 4; i++) {
        crc += strcrc[i];
    }
    sxku_reset.crc = qToBigEndian(crc);
    // 帧尾
    sxku_reset.frame_end = qToBigEndian((ushort)0x55AA);

    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (sxku_reset);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &sxku_reset, sizeof(sxku_reset));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"可重构射频前端--SXKu频段发射通道设置");

        delete[] strcrc;

        return;

    }
    // 列表封装
    Pblic_Addorderlist((uchar*)&sxku_reset, sizeof(sxku_reset),"可重构射频前端--SXKu频段发射通道设置");
    delete[] strcrc;
}

// L频段数字综合单元波束控制指令
void sub1553_tccontrol_spi::on_pushButton_L_PDnumber_clicked() {
    L_PDnumber l_pdnumber;
    memset(&l_pdnumber,0,sizeof (l_pdnumber));
    BWcs bwcs[4];
    memset(&l_pdnumber, 0, sizeof(l_pdnumber));
    // 帧头
    l_pdnumber.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    l_pdnumber.data_len = qToBigEndian((ushort)(sizeof(l_pdnumber) - 4));
    // 指令标识
    l_pdnumber.order_mark = 0x01;
    // 基态相位补偿码(bit7-bit4接收相位，bit3-bit0发射相位)
    l_pdnumber.jt_sendBC =(ui->lineEdit_jt_recvBC->text().toUInt()<<4)+ui->lineEdit_jt_sendBC->text().toUInt();
    // 基态接收幅度补偿码(bit3-bit0)
    l_pdnumber.jt_rangerecv = 0x0F&(ui->lineEdit_jt_rangerecv->text().toUInt());
    //   方位向相位补偿码(bit7-bit4接收相位，bit3-bit0发射相位)
    l_pdnumber.fx_sendBC = (ui->lineEdit_fx_recvBC->text().toUInt()<<4)+ui->lineEdit_fx_sendBC->text().toUInt();
    //小位延时相位补偿码(bit7-bit4接收相位，bit3-bit0发射相位)
    l_pdnumber.small_rangerecv=(ui->lineEdit_small_recvBC->text().toUInt()<<4)+ui->lineEdit_small_sendBC->text().toUInt();
    // 小位延时接收幅度补偿码
    l_pdnumber.small_YSBC = 0x0F&(ui->lineEdit_small_rangerecv->text().toUInt());
    //  大位延时相位补偿码(bit7-bit4接收相位，bit3-bit0发射相位)
    l_pdnumber.big_sendBC = (ui->lineEdit_big_recvdBC->text().toUInt()<<4)+ui->lineEdit_big_sendBC->text().toUInt();
    // 大位延时接收幅度补偿码
    l_pdnumber.big_rangerecv = 0x0F&(ui->lineEdit_big_rangerecv->text().toUInt());
    // 发射数控衰减
    l_pdnumber.SPsend = 0x3F&(ui->lineEdit_lineEdit_send_attenuation->text().toUInt());
    // 接收数控衰减
    l_pdnumber.SPDY_connect = 0x3F&(ui->lineEdit_recv_attenuation->text().toUInt());
    //全阵统一衰减量
    l_pdnumber.QZ_low=ui->lineEdit_QZ_low->text().toUInt();
    // 开关矩阵选择
    l_pdnumber.kgjzxz = ui->lineEdit_kgjzxz->text().toUInt();
    // 孔径工作模式
    l_pdnumber.KJworke_mode = ui->comboBox_KJworke_mode->currentIndex();
    //收发组件发射/接收控制码
    l_pdnumber.controy_code=(ui->lineEdit_controy_semdcode->text().toUInt()<<4)+ui->lineEdit_controy_recvcode->text().toUInt();
    //内定标发射控制码
    l_pdnumber.L_DBsend=0x3F&(ui->lineEdit_L_DBsend->text().toUInt());
    //内定标接收控制码
    l_pdnumber.L_Drecv=0x3F&(ui->lineEdit_L_Drecv->text().toUInt());

    // 波位参数............................(4个子阵)
    bwcs[0].bl1[0]=0;
    //子阵1——方位向发射波位号
    bwcs[0].position_send1=ui->lineEdit_position_send1->text().toUInt();
    //子阵1——距离向发射波位号
    bwcs[0].distance_send1=qToBigEndian(ui->lineEdit_distance_send1->text().toUShort());
    //子阵1——距离向波束指向角
    bwcs[0].distance_B1=qToBigEndian(ui->lineEdit_distance_B1->text().toUShort());
    //子阵1——方位向发射波束起始角
    bwcs[0].position_sendBS1=qToBigEndian(ui->lineEdit_position_sendBS1->text().toUShort());
    //子阵1——方位向接收波束起始角
    bwcs[0].position_recvBS1=qToBigEndian(ui->lineEdit_position_recvBS1->text().toUShort());


    //子阵2——方位向发射波位号
    bwcs[1].bl1[0]=0;
    bwcs[1].position_send1=ui->lineEdit_position_send2->text().toUInt();
    //子阵2——距离向发射波位号
    bwcs[1].distance_send1=qToBigEndian(ui->lineEdit_distance_send2->text().toUShort());
    //子阵2——距离向波束指向角
    bwcs[1].distance_B1=qToBigEndian(ui->lineEdit_distance_B2->text().toUShort());
    //子阵2——方位向发射波束起始角
    bwcs[1].position_sendBS1=qToBigEndian(ui->lineEdit_position_sendBS2->text().toUShort());
    //子阵2——方位向接收波束起始角
    bwcs[1].position_recvBS1=qToBigEndian(ui->lineEdit_position_recvBS2->text().toUShort());

    //子阵3——方位向发射波位号
    bwcs[2].bl1[0]=0;
    bwcs[2].position_send1=ui->lineEdit_position_send3->text().toUInt();
    //子阵3——距离向发射波位号
    bwcs[2].distance_send1=qToBigEndian(ui->lineEdit_distance_send3->text().toUShort());
    //子阵3——距离向波束指向角
    bwcs[2].distance_B1=qToBigEndian(ui->lineEdit_distance_B3->text().toUShort());
    //子阵3——方位向发射波束起始角
    bwcs[2].position_sendBS1=qToBigEndian(ui->lineEdit_position_sendBS3->text().toUShort());
    //子阵3——方位向接收波束起始角
    bwcs[2].position_recvBS1=qToBigEndian(ui->lineEdit_position_recvBS3->text().toUShort());


    //子阵4——方位向发射波位号
    bwcs[3].bl1[0]=0;
    bwcs[3].position_send1=ui->lineEdit_position_send4->text().toUInt();
    //子阵4——距离向发射波位号
    bwcs[3].distance_send1=qToBigEndian(ui->lineEdit_distance_send4->text().toUShort());
    //子阵4——距离向波束指向角
    bwcs[3].distance_B1=qToBigEndian(ui->lineEdit_distance_B4->text().toUShort());
    //子阵4——方位向发射波束起始角
    bwcs[3].position_sendBS1=qToBigEndian(ui->lineEdit_position_sendBS4->text().toUShort());
    //子阵4——方位向接收波束起始角
    bwcs[3].position_recvBS1=qToBigEndian(ui->lineEdit_position_recvBS4->text().toUShort());

    memcpy(l_pdnumber.b_CS,&bwcs,40);

    // 校验和
    uchar* strcrc = new uchar[sizeof(l_pdnumber)];
    memcpy(strcrc, &l_pdnumber, sizeof(l_pdnumber));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(l_pdnumber) - 4; i++) {
        crc += strcrc[i];
    }
    l_pdnumber.crc = qToBigEndian(crc);
    // 帧尾
    l_pdnumber.frame_end = qToBigEndian((ushort)0x55AA);

    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (l_pdnumber);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &l_pdnumber, sizeof(l_pdnumber));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"L频段数字综合单元波束控制指令设置");

        delete[] strcrc;

        return;

    }
    Pblic_Addorderlist((uchar*)&l_pdnumber, sizeof(l_pdnumber),"L频段数字综合单元波束控制指令设置");
    delete[] strcrc;
}
// SXKu频段波束控制单元波束指向控制
void sub1553_tccontrol_spi::on_pushButton_sxkuzxkg_clicked() {
    sxkuPd sxkupd;
    memset(&sxkupd, 0, sizeof(sxkupd));
    // 帧头
    sxkupd.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    sxkupd.data_len = qToBigEndian((ushort)(sizeof(sxkupd) - 4));
    // 指令标识
    sxkupd.order_mark = 0x50;
    // 工作模式
    sxkupd.work_mode = ui->comboBox_work_mode->currentIndex() + 2;
    // 极化及计算模式
    sxkupd.jhj_mode = ui->lineEdit_jhj_mode->text().toUInt();
    // 补偿组别
    sxkupd.Comoen_Group = ui->lineEdit_Comoen_Group->text().toUInt();
    // 功率及负载态矩阵
    sxkupd.power = ui->lineEdit_power->text().toUInt();
    // 组件遥测数据类型（高4位）
    sxkupd.componet_high = ui->lineEdit_componet_high->text().toUInt();
    // 组件遥测数据类型（低8位）
    sxkupd.componet_low = ui->lineEdit_componet_low->text().toUInt();
    // 接收衰减控制
    sxkupd.recv_attenuation = ui->lineEdit_recv_attenuation->text().toUInt();
    // X向发射相位加权码（128组）
    sxkupd.x_send = ui->lineEdit_x_send->text().toUInt();
    // X向接收相位/幅度加权码（128组）
    sxkupd.x_recvfd = ui->lineEdit_x_recvfd->text().toUInt();
    // Y向发射相位加权码（128组）
    sxkupd.y_send = ui->lineEdit_y_send->text().toUInt();
    // y向接收相位/幅度加权码（128组）
    sxkupd.y_recvfd = ui->lineEdit_y_recvfd->text().toUInt();
    // 指定移相值
    sxkupd.specifies_yx = ui->lineEdit_specifies_yx->text().toUInt();
    // 指定衰减值
    sxkupd.specifies_sj = ui->lineEdit_specifies_sj->text().toUInt();
    // 指定延时值
    sxkupd.specifies_ys = ui->lineEdit_specifies_ys->text().toUInt();

    // 波位参数
    // 校验和
    uchar* strcrc = new uchar[sizeof(sxkupd)];
    memcpy(strcrc, &sxkupd, sizeof(sxkupd));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(sxkupd) - 4; i++) {
        crc += strcrc[i];
    }
    sxkupd.crc = qToBigEndian(crc);
    // 帧尾
    sxkupd.frame_end = qToBigEndian((ushort)0x55AA);

    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (sxkupd);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &sxkupd, sizeof(sxkupd));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"SXKu频段波束控制单元波束指向控制设置");

        delete[] strcrc;

        return;

    }
    Pblic_Addorderlist((uchar*)&sxkupd, sizeof(sxkupd),"SXKu频段波束控制单元波束指向控制设置");
    delete[] strcrc;
}
// 可重构射频前端射频校正开关状态设置
void sub1553_tccontrol_spi::on_pushButton_clicked() {
    Str_Switch str_switch;
    memset(&str_switch, 0, sizeof(str_switch));
    // 帧头
    str_switch.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    str_switch.data_len = qToBigEndian((ushort)(sizeof(str_switch) - 4));
    // 指令标识
    str_switch.order_mark = 0x70;
    // 频段选择
    str_switch.frequency = ui->comboBox_frequency->currentIndex();
    // 校正方式
    str_switch.correction_mode = ui->comboBox_correction_mode->currentIndex();
    // 校验和
    uchar* strcrc = new uchar[sizeof(str_switch)];
    memcpy(strcrc, &str_switch, sizeof(str_switch));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(str_switch) - 4; i++) {
        crc += strcrc[i];
    }
    str_switch.crc = qToBigEndian(crc);
    // 帧尾
    str_switch.frame_end = qToBigEndian((ushort)0x55AA);


    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (str_switch);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &str_switch, sizeof(str_switch));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"可重构射频前端--射频校正开关状态设置");

        delete[] strcrc;

        return;

    }
    Pblic_Addorderlist((uchar*)&str_switch, sizeof(str_switch),"可重构射频前端--射频校正开关状态设置");

    delete[] strcrc;
}
// 可重构射频前端SXKu频段一本振选择设置
void sub1553_tccontrol_spi::on_pushButton_sxku_ankyloko_clicked() {
    sxku_ankyloko sxku_set;
    memset(&sxku_set, 0, sizeof(sxku_set));
    // 帧头
    sxku_set.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    sxku_set.data_len = qToBigEndian((ushort)(sizeof(sxku_set) - 4));
    // 指令标识
    sxku_set.order_mark = 0x71;
    // 通道选择
    sxku_set.CHannel_xz = ui->comboBox_CHannel_xz->currentIndex();
    // 一本振使用信息
    sxku_set.one_use = ui->comboBox_one_use->currentIndex();
    // 校验和
    uchar* strcrc = new uchar[sizeof(sxku_set)];
    memcpy(strcrc, &sxku_set, sizeof(sxku_set));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(sxku_set) - 4; i++) {
        crc += strcrc[i];
    }
    sxku_set.crc = qToBigEndian(crc);
    // 帧尾
    sxku_set.frame_end = qToBigEndian((ushort)0x55AA);

    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (sxku_set);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &sxku_set, sizeof(sxku_set));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"可重构射频前端--SXKu频段一本振选择设置");

        delete[] strcrc;

        return;

    }
    Pblic_Addorderlist((uchar*)&sxku_set, sizeof(sxku_set),"可重构射频前端--SXKu频段一本振选择设置");
    delete[] strcrc;
}
// 可重构射频前端L频段接收通道设置
void sub1553_tccontrol_spi::on_pushButton_Str_L_recvSet_clicked() {
    Str_L_recvSet str_recvset;
    memset(&str_recvset, 0, sizeof(str_recvset));
    // 帧头
    str_recvset.frame_head = qToBigEndian((ushort)0xAA55);
    // 数据长度
    str_recvset.data_len = qToBigEndian((ushort)(sizeof(str_recvset) - 4));
    // 指令标识
    str_recvset.order_mark = 0x72;
    // 通道选择
    str_recvset.ad_choose = ui->comboBox_L_ad_choose->currentIndex();
    // L频段GSM陷波器使能
    str_recvset.L_GSmEnable = ui->comboBox_L_GSmEnable->currentIndex();
    // L频段第一级放大器使能
    str_recvset.L_oneEnable = ui->comboBox_L_oneEnable->currentIndex();
    // L频段第二级放大器使能
    str_recvset.L_twoEnable = ui->comboBox_L_twoEnable->currentIndex();
    // L频段第三级放大器使能
    str_recvset.L_threeEnable = ui->comboBox_L_threeEnable->currentIndex();
    // 接收衰减
    str_recvset.recv_down = ui->lineEdit_L_recv_down->text().toUInt();
    // 校验和
    uchar* strcrc = new uchar[sizeof(str_recvset)];
    memcpy(strcrc, &str_recvset, sizeof(str_recvset));
    ushort crc = 0;
    for (uint i = 2; i < sizeof(str_recvset) - 4; i++) {
        crc += strcrc[i];
    }
    str_recvset.crc = qToBigEndian(crc);
    // 帧尾
    str_recvset.frame_end = qToBigEndian((ushort)0x55AA);
    if(ui->comboBox_bkChoose->currentIndex()==1)//CAN模式
    {
        packSpi_can strcan;
        memset(&strcan,0,sizeof (strcan));

        // CAN数据长度
        ushort tmp=sizeof (strcan)+sizeof (str_recvset);
        strcan.can_data_len = qToBigEndian(tmp);
        // can指令标识
        strcan.can_order_mark = 0x80;

        //can校验和
        uchar* strcrc2 = new uchar[tmp];
        memset(strcrc2,0,tmp);
        memcpy(strcrc2, &strcan, 3);
        memcpy(strcrc2+3, &str_recvset, sizeof(str_recvset));

        ushort crc2 = 0;
        for (int i = 0; i < tmp - 2; i++) {
            crc2 += strcrc2[i];
        }
        strcan.can_crc = qToBigEndian(crc2);
        memcpy(strcrc2+(tmp-2),&strcan.can_crc,2);
        Pblic_Addorderlist((uchar*)strcrc2, tmp,"可重构射频前端--L频段接收通道设置");

        delete[] strcrc;

        return;

    }
    Pblic_Addorderlist((uchar*)&str_recvset, sizeof(str_recvset),"可重构射频前端--L频段接收通道设置");
    delete[] strcrc;
}
//高算力平台调试指令1553
void sub1553_tccontrol_spi::on_pB_gsl80_clicked()
{

    if(ui->comboBox_bkChoose->currentIndex()==0)//1553发送类型
    {
        gsl_test str_test;
        memset(&str_test, 0, sizeof(str_test));
        // 帧头
        str_test.frame_head = qToBigEndian((ushort)0xAA55);
        // 数据长度
        str_test.data_len = qToBigEndian((ushort)(sizeof(str_test) - 4));
        // 指令标识
        str_test.order_mark = 0x80;
        // 频段选择
        str_test.pd_xz=ui->cB_gsl80_1->currentIndex();
        // 参数1
        str_test.cs1=ui->cB_gsl80_2->currentIndex()+1;
        if(ui->cB_gsl80_2->currentIndex()>11)str_test.cs1=ui->cB_gsl80_2->currentIndex()+88;
        // 参数2
        str_test.cs2=ui->lineEdit_gsl80_3->text().toUInt();
        // 参数3
        str_test.cs3=ui->lineEdit_gsl80_4->text().toUInt();
        // 参数4
        str_test.cs4=ui->lineEdit_gsl80_5->text().toUInt();
        // 参数5
        str_test.cs5=ui->lineEdit_gsl80_6->text().toUInt();
        // 参数6
        str_test.cs6=ui->lineEdit_gsl80_7->text().toUInt();
        // 校验和
        uchar* strcrc = new uchar[sizeof(str_test)];
        memcpy(strcrc, &str_test, sizeof(str_test));
        ushort crc = 0;
        for (uint i = 2; i < sizeof(str_test) - 4; i++) {
            crc += strcrc[i];
        }
        str_test.crc = qToBigEndian(crc);
        // 帧尾
        str_test.frame_end = qToBigEndian((ushort)0x55AA);
        Pblic_Addorderlist((uchar*)&str_test, sizeof(str_test),"高算力调试指令"+ui->cB_gsl80_2->currentText());
        delete[] strcrc;
    }
    else//can发送类型
    {
        gsl_test_CAN str_test;
        memset(&str_test, 0, sizeof(str_test));

        // CAN数据长度
        str_test.can_data_len = qToBigEndian((ushort)sizeof (str_test));
        // can指令标识
        str_test.can_order_mark = 0x80;

        // 帧头
        str_test.frame_head = qToBigEndian((ushort)0xAA55);
        // 数据长度
        str_test.data_len = qToBigEndian((ushort)(sizeof(str_test) - 10));
        // 指令标识
        str_test.order_mark = 0x80;
        // 频段选择
        str_test.pd_xz=ui->cB_gsl80_1->currentIndex();
        // 参数1
        str_test.cs1=ui->cB_gsl80_2->currentIndex()+1;
        if(ui->cB_gsl80_2->currentIndex()>10)str_test.cs1=ui->cB_gsl80_2->currentIndex()+89;
        // 参数2
        str_test.cs2=ui->lineEdit_gsl80_3->text().toUInt();
        // 参数3
        str_test.cs3=ui->lineEdit_gsl80_4->text().toUInt();
        // 参数4
        str_test.cs4=ui->lineEdit_gsl80_5->text().toUInt();
        // 参数5
        str_test.cs5=ui->lineEdit_gsl80_6->text().toUInt();
        // 参数6
        str_test.cs6=ui->lineEdit_gsl80_7->text().toUInt();
        // 校验和
        int len=sizeof(str_test)-6;
        uchar* strcrc = new uchar[len];
        memcpy(strcrc, &str_test.frame_head, len);
        ushort crc = 0;
        for (int i = 2; i < len-2; i++) {
            crc += strcrc[i];
        }
        str_test.crc = qToBigEndian(crc);
        // 帧尾
        str_test.frame_end = qToBigEndian((ushort)0x55AA);

        //can校验和
        uchar* strcrc2 = new uchar[sizeof(str_test)];
        memcpy(strcrc2, &str_test, sizeof(str_test));
        ushort crc2 = 0;
        for (uint i = 0; i < sizeof(str_test) - 2; i++) {
            crc2 += strcrc2[i];
        }
        str_test.can_crc = qToBigEndian(crc2);

        Pblic_Addorderlist((uchar*)&str_test, sizeof(str_test),"高算力调试指令"+ui->cB_gsl80_2->currentText());
        delete[] strcrc2;
    }


}
//板卡发送选择
void sub1553_tccontrol_spi::on_comboBox_bkChoose_activated(int index)
{
    if(index==0)//1553板卡
    {
        ui->cB_gslChoose_spi->setEnabled(true);
    }
    else
    {
        ui->cB_gslChoose_spi->setEnabled(false);
    }
}
