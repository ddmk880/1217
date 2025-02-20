#include "sub1553_gkcontrol2.h"
#include "ui_sub1553_gkcontrol2.h"

sub1553_gkcontrol2::sub1553_gkcontrol2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_gkcontrol2)
{
    ui->setupUi(this);
    QStringList list;

    list.append("手动填");
    list.append("0x0F01:(16MB收发版本接口控制)");
    list.append("0x0F02:(32MB采集与信道化接收)");
    list.append("0x0F04:(32MB波束合成发射)");
    list.append("0x0F05:(16MB处理接口控制)");
    list.append("0x0F06:(32MB数据分发)");
    list.append("0x0D09:(8MB综合调度)");
    list.append("0x5F01:(32MB类5G通信)");
    list.append("0x5D02:(8MB类5G协议控制)");
    list.append("0x0C20:(8MB管控软件)");
    list.append("0x0F10:(32MBV7A)");
    list.append("0x0F17:(32MBV7B)");
    list.append("0x1D22:(32MB DSP融合)");
    list.append("0x1D23:(32MB DSP定位TX)");
    list.append("0x1D24:(32MB DSP定位LD)");
    list.append("0x1C21:(32MB AI)");
    list.append("0x0FA0:(AI模型)");

    ui->comboBox_0x47_choose->addItems(list);
}

sub1553_gkcontrol2::~sub1553_gkcontrol2()
{
    delete ui;
}

void sub1553_gkcontrol2::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 6;
    order_data.gap_time = 1;
    order_data.order_name = buffname;
    order_data.order_kind = 2;
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff, buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

uint sub1553_gkcontrol2::toHex_uint(QString qstr)
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

ushort sub1553_gkcontrol2::toHex_ushort(QString qstr)
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
//开始软件包上载0x4B
void sub1553_gkcontrol2::on_pB_4B_start_clicked()
{
    str_4B str;
    memset(&str, 0, sizeof(str));
    // 指令标识
    str.ordermark = 0x4B;
    // 上载方式
    str.up_mark = ui->Combox_4B_1->currentIndex()+1;
    // 上载大小
    str.up_size=ui->lineEdit_4B_2->text().toInt();
    // 段号
    str.duan_num=ui->lineEdit_4B_3->text().toInt();

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "开始软件包上载 : "+ui->Combox_4B_1->currentText());
}


//结束软件包上载0x4C
void sub1553_gkcontrol2::on_pB_4C_end_clicked()
{
    uchar str[2];
    memset(&str, 0, sizeof(str));
    // 指令标识
    str[0] = 0x4C;
    //保留
    str[1]=0xFF;

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "结束软件包上载");
}

//更新软件0x47
void sub1553_gkcontrol2::on_pB_47_updata_clicked()
{
    str_47 str;
    memset(&str, 0, sizeof(str));
    // 指令标识
    str.ordermark = 0x47;
    //单机标志
    str.pc_mark=ui->Combox_47_1->currentIndex();
    //软件代号
    str.sorft_num=toHex_ushort(ui->lineEdit_47_2->text());
    //软件大小
    str.sorft_size=qToBigEndian(ui->lineEdit_47_3->text().toUShort());
    //FLASH编号
    str.flash_num=ui->comboBox_47_4->currentIndex()+1;
    //数据源
    str.to_duan=ui->comboBox_47_5->currentIndex()+1;
    //FLASH起始地址
    str.flash_s_addr=toHex_uint(ui->lineEdit_47_6->text());
    //算力通道选择
    str.sl_choose=ui->comboBox_47_7->currentIndex()+1;
//    //上注通道选择
//    str.up_choose=ui->comboBox_47_8->currentIndex();

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "更新软件 : "+ui->comboBox_47_4->currentText());
}
//软件更新 类型改变flash编号内容
void sub1553_gkcontrol2::on_Combox_47_1_activated(int index)
{
    ui->comboBox_47_4->clear();
    if((index==1)||(index==2))
    {
          ui->comboBox_47_4->addItem("1: Nor Flash1");
          ui->comboBox_47_4->addItem("2: Nor Flash2");
          ui->comboBox_47_4->addItem("3: Nand Flash");


    }
    else
    {
        ui->comboBox_47_4->addItem("1：/");
        ui->comboBox_47_4->addItem("2：P2020更新区A");
        ui->comboBox_47_4->addItem("3：P2020更新区B");
        ui->comboBox_47_4->addItem("4：P2020更新区C");
        ui->comboBox_47_4->addItem("5：管控V7更新区");
        ui->comboBox_47_4->addItem("6：管控V7基础区");
        ui->comboBox_47_4->addItem("7：/");
        ui->comboBox_47_4->addItem("8：/");
        ui->comboBox_47_4->addItem("9：融合DSP基础区");
        ui->comboBox_47_4->addItem("10：融合DSP更新区");
        ui->comboBox_47_4->addItem("11：通侦定位DSP基础区");
        ui->comboBox_47_4->addItem("12：通侦定位DSP更新区");
        ui->comboBox_47_4->addItem("13：雷侦定位DSP基础区");
        ui->comboBox_47_4->addItem("14：雷侦定位DSP更新区");
        ui->comboBox_47_4->addItem("15：AI基础区");
        ui->comboBox_47_4->addItem("16：AI更新区");
        ui->comboBox_47_4->addItem("17：6Gb三模");
        ui->comboBox_47_4->addItem("18：6Gb第一片");
        ui->comboBox_47_4->addItem("19：6Gb第二片");
        ui->comboBox_47_4->addItem("20：6Gb第三片");
        ui->comboBox_47_4->addItem("21：融合DSP的引导区");
        ui->comboBox_47_4->addItem("22：通侦定位DSP的引导区");
        ui->comboBox_47_4->addItem("23：雷侦定位DSP的引导区");
        ui->comboBox_47_4->addItem("24：AI的引导区");
        ui->comboBox_47_4->addItem("25：MRAM FLASH分区表");
        ui->comboBox_47_4->addItem("26：重点目标库");
        ui->comboBox_47_4->addItem("27：重点通信信号");
        ui->comboBox_47_4->addItem("28：雷达重点侦察库");
        ui->comboBox_47_4->addItem("29：p2020三模");
        ui->comboBox_47_4->addItem("30：处理V7三模 ");
        ui->comboBox_47_4->addItem("31：综合管控单元固态SSD");


        ui->comboBox_47_4->setCurrentIndex(1);
    }
}

//更新配置
void sub1553_gkcontrol2::on_pB_4A_clicked()
{
    str_4A str;
    memset(&str, 0, sizeof(str));
    // 指令标识
    str.ordermark = 0x4A;
    //单机标志
    str.pc_mark = ui->Combox_4A_1->currentIndex();
    //配置代号
    str.set_num =toHex_ushort(ui->lineEdit_4A_2->text());
    //起始地址
    str.addr_str =toHex_uint( ui->lineEdit_4A_3->text());
    //配置大小
    str.set_size =qToBigEndian(ui->lineEdit_4A_4->text().toUInt());

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "更新配置 : "+ui->Combox_4A_1->currentText());
}

//软件更新自动填地址
void sub1553_gkcontrol2::on_comboBox_0x47_choose_activated(const QString &arg1)
{
    QString str1;

    if (arg1=="手动填")                             {str1="0";}
//    else if(arg1=="0x0F01:(16MB收发版本接口控制)")      {str1="0x0F01";}
//    else if(arg1=="0x0F02:(32MB采集与信道化接收)")  {str1="0x0F02";}
//    else if(arg1=="0x0F04:(32MB波束合成发射)")        {str1="0x0F04";}
//    else if(arg1=="0x0F05:(16MB处理接口控制)")        {str1="0x0F05";}
//    else if(arg1=="0x0F06:(32MB数据分发)")          {str1="0x0F06";}
//    else if(arg1=="0x0D09:(8MB综合调度)")           {str1="0x0D09";}
//    else if(arg1=="0x5F01:(32MB类5G通信)")         {str1="0x5F01";}
//    else if(arg1=="0x5D02:(8MB类5G协议控制)")        {str1="0x5D02";}
//    else if(arg1=="0x0C20:(8MB管控软件)")           {str1="0x0C20";}
//    else if(arg1=="0x0F10:(32MBV7A)")           {str1="0x0F10";}
//    else if(arg1=="0x0F17:(32MBV7B)")           {str1="0x0F17";}
//    else if(arg1=="0x1D22:(32MB DSP融合)")        {str1="0x1D22";}
//    else if(arg1=="0x1D23:(32MB DSP定位TX)")          {str1="0x1D23";}
//    else if(arg1=="0x1D24:(32MB DSP定位LD)")          {str1="0x1D24";}
//    else if(arg1=="0x1C21:(32MB AI)")               {str1="0x1C21";}
//    else if(arg1=="0x0FA0:(AI模型)")               {str1="0x0FA0";}
    else {
        str1=arg1.left(arg1.indexOf(":"));
    }

    ui->lineEdit_47_2->setText(str1);
}
//数据源改变大小使能
void sub1553_gkcontrol2::on_comboBox_47_5_activated(int index)
{
    if(index==0)
    {
        ui->lineEdit_47_3->setEnabled(true);
    }
    else{
        ui->lineEdit_47_3->setEnabled(false);
    }
}
//综合管控单元6Gb三维运维0x43
void sub1553_gkcontrol2::on_pushButton_0x43_clicked()
{
    str_43 str;
    memset(&str, 0, sizeof(str));
    // 指令标识
    str.ordermark = 0x43;
    // 对象标识
    str.objmark=ui->comboBox_0x43_0->currentIndex();
    //控制
    str.contorl=ui->comboBox_0x43_1->currentIndex()+1;
    //起始地址
    str.startADDr=qToBigEndian(ui->lineEdit_0x43_2->text().toInt());
    //大小
    str.sorft_size=qToBigEndian(ui->lineEdit_0x43_3->text().toInt());

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "综合管控单元6Gb三维运维 : "+ui->comboBox_0x43_1->currentText());
}
