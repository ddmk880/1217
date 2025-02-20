#include "sub1553_tccontrol2.h"
#include "ui_sub1553_tccontrol2.h"

sub1553_tccontrol2::sub1553_tccontrol2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_tccontrol2)
{
    ui->setupUi(this);
    ui->cb_cardChooe->setStyleSheet("background-color:rgb(210,210,210)");

    ui->tableWidget_C93cyclist->setColumnCount(5);
    ui->tableWidget_C93cyclist->setHorizontalHeaderLabels(QStringList()<< "频率Hz"<< "经度"<< "纬度"<< "高度"<< "模式");
//    for(int i = 0;i < 5;i ++)
//    {
//        ui->tableWidget_C93cyclist->insertRow(i);

//        ui->tableWidget_C93cyclist->setItem(i,0,new QTableWidgetItem(QString::number(0)));
//        ui->tableWidget_C93cyclist->setItem(i,1,new QTableWidgetItem(QString::number(0)));
//    }
    ui->tableWidget_C93cyclist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 最小显示完整，出现滚动条
    ui->tableWidget_C93cyclist->verticalHeader()->setVisible(true);  // 隐藏行号
}

sub1553_tccontrol2::~sub1553_tccontrol2()
{
    delete ui;
}

void sub1553_tccontrol2::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 17;
    order_data.gap_time = 1;
    order_data.order_name ="透传-"+ buffname;

    if(ui->cb_cardChooe->currentIndex()==0)
    {
        order_data.order_kind = 4+ui->comboBox_gslChoose->currentIndex();//1553发送类型
    }
    else
    {
        order_data.order_kind =9;//can发送类型
        order_data.order_name ="CAN:"+buffname;
    }

    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff,buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

uint sub1553_tccontrol2::toHex_uint(QString qstr)
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

ushort sub1553_tccontrol2::toHex_ushort(QString qstr)
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



//9.4.13 系统参数初始化C8C
void sub1553_tccontrol2::on_pushButton_C8C_clicked()
{

    Str_sysC8C strc8C;
    memset(&strc8C,0,sizeof (strc8C));
    //指令长度
    strc8C.order_len=qToBigEndian((ushort) sizeof (strc8C));
    //指令标识
    strc8C.order_mark=0x8C;
    // 卫星标志
    strc8C.s_mark=ui->lineEdit_c8c_1->text().toUInt()+(ui->lineEdit_c8c_2->text().toUInt()<<8);
    // 管控单元主备标识
    strc8C.main_sub=ui->comboBox_c8c_3->currentIndex()+(ui->comboBox_c8c_3_2->currentIndex()<<1);
    //校验和
    uchar* strcrc=new uchar[sizeof (strc8C)+1];
    memcpy(strcrc,&strc8C,sizeof (strc8C));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc8C)-2;i++) {
        crc+=strcrc[i];
    }
    strc8C.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc8C,sizeof (strc8C),
                       QString("系统参数初始化 管控机:%1,交换机:%2")
                       .arg(ui->comboBox_c8c_3->currentText()).arg(ui->comboBox_c8c_3_2->currentText()));
    delete [] strcrc;
}


//9.4.14 模块上下电
void sub1553_tccontrol2::on_pushButton_C8D_clicked()
{
    Str_powC8D strc8D;
    memset(&strc8D,0,sizeof (strc8D));
    //指令长度
    strc8D.order_len=qToBigEndian((ushort) sizeof (strc8D));
    //指令标识
    strc8D.order_mark=0x8D;

    //AD/DA1
    strc8D.AD_DA1=ui->comboBox_C8D_1->currentIndex();
    //AD/DA2
    strc8D.AD_DA2=ui->comboBox_C8D_2->currentIndex();
    //AD/DA3
    strc8D.AD_DA3=ui->comboBox_C8D_3->currentIndex();

    //校验和
    uchar* strcrc=new uchar[sizeof (strc8D)+1];
    memcpy(strcrc,&strc8D,sizeof (strc8D));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc8D)-2;i++) {
        crc+=strcrc[i];
    }
    strc8D.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc8D,sizeof (strc8D),"模块上下电");
    delete [] strcrc;
}
//FLASH格式化C8E
void sub1553_tccontrol2::on_pushButton_C8E_clicked()
{
    Str_C8E strc8E;
    memset(&strc8E,0,sizeof (strc8E));
    //指令长度
    strc8E.order_len=qToBigEndian((ushort) sizeof (strc8E));
    //指令标识
    strc8E.order_mark=0x8E;

    //FLASH标识
    strc8E.flash_mark=ui->comboBox_C8E_1->currentIndex()+1;
     //擦除标识
    strc8E.ccMark=qToBigEndian((ushort)0xBCBA);
    //校验和
    uchar* strcrc=new uchar[sizeof (strc8E)+1];
    memcpy(strcrc,&strc8E,sizeof (strc8E));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc8E)-2;i++) {
        crc+=strcrc[i];
    }
    strc8E.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc8E,sizeof (strc8E),"FLASH格式化:"+ui->comboBox_C8E_1->currentText());
    delete [] strcrc;
}

//9.4.16 重构状态查询C8F
void sub1553_tccontrol2::on_pushButton_C8F_clicked()
{
    Str_C8F strc8F;
    memset(&strc8F,0,sizeof (strc8F));
    //指令长度
    strc8F.order_len=qToBigEndian((ushort) sizeof (strc8F));
    //指令标识
    strc8F.order_mark=0x8F;

    //校验和
    uchar* strcrc=new uchar[sizeof (strc8F)+1];
    memcpy(strcrc,&strc8F,sizeof (strc8F));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc8F)-2;i++) {
        crc+=strcrc[i];
    }
    strc8F.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc8F,sizeof (strc8F),"重构状态查询");
    delete [] strcrc;
}
//任务下发C90
void sub1553_tccontrol2::on_pushButton_C90_clicked()
{
    Str_C90 strc90;
    memset(&strc90,0,sizeof (strc90));
    //指令长度
    strc90.order_len=qToBigEndian((ushort) sizeof (strc90));
    //指令标识
    strc90.order_mark=0x90;
    //总包数
    strc90.packSum=ui->lineEdit_C90_1->text().toInt();
    //包序号
    strc90.packNum=ui->lineEdit_C90_2->text().toInt();
    //任务内容
    QString strdata=ui->lineEdit_C90_3->text();
    strdata=strdata.replace(" ","");
    int tmplen1 = (strdata.size() + 1) / 2;
    strc90.order_len=qToBigEndian((ushort) (7+tmplen1));//指令长度...
    QByteArray hex_data = QByteArray::fromHex(strdata.toLatin1());  // 将字节流转换位16进制,char型
    memcpy(&strc90.data[0], (uchar *)hex_data.data(), tmplen1);  // 获取地址

    //指令变长拼接
    int Len=sizeof (strc90)-sizeof (strc90.data)+tmplen1;
    uchar *order_end=new uchar[Len];
    memcpy(order_end,(uchar*)&strc90,Len);


//    //校验和
//    uchar* strcrc=new uchar[sizeof (strc90)+1];
//    memcpy(strcrc,&strc90,sizeof (strc90));
//    ushort crc=0;
//    for (uint i=0;i<sizeof (strc90)-2;i++) {
//        crc+=strcrc[i];
//    }
//    strc90.crc=qToBigEndian(crc);

    //校验和
    uchar* strcrc=new uchar[Len+1];
    memcpy(strcrc,order_end,sizeof (Len));
    ushort crc=0;
    for (int i=0;i<Len-2;i++) {
        crc+=strcrc[i];
    }
    crc=qToBigEndian(crc);
    memcpy(order_end+Len-2,&crc,2);
    //列表封装
    Pblic_Addorderlist(order_end,Len,"任务下发:序号"+ui->lineEdit_C90_2->text());
    delete [] strcrc;
}



//9.4.18 开始任务C91
void sub1553_tccontrol2::on_pushButton_C91_clicked()
{
    Str_c91_c92 strcc91_c92;
    memset(&strcc91_c92,0,sizeof (strcc91_c92));
    //指令长度
    strcc91_c92.order_len=qToBigEndian((ushort) sizeof (strcc91_c92));
    //指令标识
    strcc91_c92.order_mark=0x91;
    //任务号
    uint tmp= ui->lineEdit_c91_1->text().toUInt();
    memset(&strcc91_c92.task,0,sizeof (strcc91_c92.task));
    strcc91_c92.task[0]=tmp>>16;
    strcc91_c92.task[1]=tmp>>8;
    strcc91_c92.task[2]=tmp;

    //校验和
    uchar* strcrc=new uchar[sizeof (strcc91_c92)+1];
    memcpy(strcrc,&strcc91_c92,sizeof (strcc91_c92));
    ushort crc=0;
    for (uint i=0;i<sizeof (strcc91_c92)-2;i++) {
        crc+=strcrc[i];
    }
    strcc91_c92.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strcc91_c92,sizeof (strcc91_c92),"开始任务");
    delete [] strcrc;
}
//9.4.19 停止任务C92
void sub1553_tccontrol2::on_pushButton_C92_clicked()
{
    Str_c91_c92 strcc91_c92;
    memset(&strcc91_c92,0,sizeof (strcc91_c92));
    //指令长度
    strcc91_c92.order_len=qToBigEndian((ushort) sizeof (strcc91_c92));
    //指令标识
    strcc91_c92.order_mark=0x92;
    //任务号
    uint tmp= ui->lineEdit_c92_1->text().toUInt();
    memset(&strcc91_c92.task,0,sizeof (strcc91_c92.task));
    strcc91_c92.task[0]=tmp>>16;
    strcc91_c92.task[1]=tmp>>8;
    strcc91_c92.task[2]=tmp;
    //校验和
    uchar* strcrc=new uchar[sizeof (strcc91_c92)+1];
    memcpy(strcrc,&strcc91_c92,sizeof (strcc91_c92));
    ushort crc=0;
    for (uint i=0;i<sizeof (strcc91_c92)-2;i++) {
        crc+=strcrc[i];
    }
    strcc91_c92.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strcc91_c92,sizeof (strcc91_c92),"停止任务");
    delete [] strcrc;
}
//9.4.20 干扰引导信息C93
void sub1553_tccontrol2::on_pushButton_C93_clicked()
{
    Str_C93 strC93;
    memset(&strC93,0,sizeof (strC93));
    //指令长度
    ushort order_len=0;
    int cyc_sum=ui->lineEdit_c93_2_1->text().toInt();//循环体个数
    order_len=10+18*cyc_sum;
    strC93.order_len=qToBigEndian((ushort)order_len);
    //指令标识
    strC93.order_mark=0x93;
    //信号类型
    strC93.signal_kind=ui->comboBox_c93_1->currentIndex()+1;
    //目标数量
    strC93.mask_sum=qToBigEndian(ui->lineEdit_c93_2_1->text().toUShort());

    //处理循环体内容
    uchar* databuff=new uchar[order_len+1];//存储数据缓存
    memcpy(databuff,&strC93,sizeof (strC93));

    Str_C93_cyc str_cyc;
    for (int i=0;i<cyc_sum;i++) {


        memset(&str_cyc,0,sizeof (str_cyc));
        //频率
        str_cyc.fre=qToBigEndian(ui->tableWidget_C93cyclist->item(i,0)->text().toUInt());
        //经度
        str_cyc.jd=qToBigEndian(ui->tableWidget_C93cyclist->item(i,1)->text().toInt());
        //纬度
        str_cyc.wd=qToBigEndian(ui->tableWidget_C93cyclist->item(i,2)->text().toInt());
        //高度
        str_cyc.gd=qToBigEndian(ui->tableWidget_C93cyclist->item(i,3)->text().toInt());
        //模式（指侦察到类型）
        str_cyc.mode_type=qToBigEndian(ui->tableWidget_C93cyclist->item(i,4)->text().toUShort());

        memcpy(databuff + sizeof (strC93) + sizeof (str_cyc)*i,&str_cyc,sizeof (str_cyc));//拷贝数据

    }


    //循环体后面部分
    Str_C93_end str_end;
    memset(&str_end,0,sizeof (str_end));
    //校验和
    memcpy(databuff + sizeof (strC93) + sizeof (str_cyc)*cyc_sum,&str_end,sizeof (str_end));//拷贝数据
    ushort crc=0;
    for (int i=0;i<order_len-2;i++) {
        crc+=databuff[i];
    }
    str_end.crc=qToBigEndian(crc);

    memcpy(databuff + sizeof (strC93) + sizeof (str_cyc)*cyc_sum,&str_end,sizeof (str_end));//拷贝数据
    //列表封装
    Pblic_Addorderlist((uchar*)databuff,order_len,"干扰引导信息");
    delete [] databuff;
}


//干扰引导信息C93 添加循环体内容
void sub1553_tccontrol2::on_pushButton_C93_Add_clicked()
{
    int row=ui->tableWidget_C93cyclist->rowCount();
    ui->tableWidget_C93cyclist->insertRow(row);
    ui->lineEdit_c93_2_1->setText(QString::number(row+1));

    //频率
    ui->tableWidget_C93cyclist->setItem(row,0,new QTableWidgetItem(ui->lineEdit_c93_2->text()));
    //经度
    ui->tableWidget_C93cyclist->setItem(row,1,new QTableWidgetItem(ui->lineEdit_c93_3->text()));
    //纬度
    ui->tableWidget_C93cyclist->setItem(row,2,new QTableWidgetItem(ui->lineEditc93_4->text()));
    //高度
    ui->tableWidget_C93cyclist->setItem(row,3,new QTableWidgetItem(ui->lineEdit_c93_5->text()));
    //模式（指侦察到类型）
    int tmp=ui->comboBox_c93_6->currentIndex();
    ui->tableWidget_C93cyclist->setItem(row,4,new QTableWidgetItem(QString::number(tmp)));




}
//干扰引导信息C93 清空表格
void sub1553_tccontrol2::on_pushButton_C93_clear_clicked()
{
    ui->tableWidget_C93cyclist->setRowCount(0);
    ui->lineEdit_c93_2_1->setText(QString::number(0));
}

//干扰引导信息C93 根据类型改变下拉框
void sub1553_tccontrol2::on_comboBox_c93_1_activated(int index)
{
    switch (index) {
    case 0://1：Link16
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("无效");


        break;
    case 1://2：塔康
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("0:TACAN询问X模式");
        ui->comboBox_c93_6->addItem("1:TACAN询问Y模式");
        ui->comboBox_c93_6->addItem("2:TACAN应答X模式");
        ui->comboBox_c93_6->addItem("3:TACAN应答Y模式");



        break;
    case 2://3：敌我识别 IFF
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("0:模式4询问");
        ui->comboBox_c93_6->addItem("1:模式5询问");
        ui->comboBox_c93_6->addItem("2:询问所有类型");
        ui->comboBox_c93_6->addItem("3:模式4应答");
        ui->comboBox_c93_6->addItem("4:模式5应答");
        ui->comboBox_c93_6->addItem("5:应答所有类型");


        break;
    case 3://4：铱星
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("无效");

        break;
    case 4://5：海事
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("无效");

        break;
    case 5://6：雷达
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("无效");

        break;
    case 6://7：星链
        //模式（指侦察到类型）
        ui->comboBox_c93_6->clear();
        ui->comboBox_c93_6->addItem("无效");
        break;
    default:
        break;
    }
}

//10.4.21 测试数传C94
void sub1553_tccontrol2::on_pushButton_C94_clicked()
{
    Str_C94 strC94;
    memset(&strC94,0,sizeof (strC94));
    //指令长度
    strC94.order_len=qToBigEndian((ushort) sizeof (strC94));
    //指令标识
    strC94.order_mark=0x94;

    // 处理模块标识
    ushort tmp = 0;
    tmp = ui->checkBox_csbit0->isChecked() +
            (ui->checkBox_csbit1->isChecked() << 1) +
            (ui->checkBox_csbit2->isChecked() << 2) +
            (ui->checkBox_csbit3->isChecked() << 3) +
            (ui->checkBox_csbit4->isChecked() << 4) +
            (ui->checkBox_csbit5->isChecked() << 5) +
            (ui->checkBox_csbit6->isChecked() << 6) +
            (ui->checkBox_csbit7->isChecked() << 7) +
            (ui->checkBox_csbit8->isChecked() << 8);

    strC94.cl_mark = qToBigEndian(tmp);
    // 数据传输速率
    strC94.speed =qToBigEndian(ui->LineEdit_data_trans_rate->text().toUShort());
    // 发送的帧数
    strC94.sendFrame = qToBigEndian(ui->LineEdit_sendframe_num->text().toUInt());
    // 标志
    strC94.datamark = ui->cB_test_numbertrans_sign->currentIndex() + 1;
    //卫星代码
    strC94.startCode=toHex_ushort(ui->lineEdit_41_startcode->text());


    //校验和
    uchar* strcrc=new uchar[sizeof (strC94)+1];
    memcpy(strcrc,&strC94,sizeof (strC94));
    ushort crc=0;
    for (uint i=0;i<sizeof (strC94)-2;i++) {
        crc+=strcrc[i];
    }
    strC94.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strC94,sizeof (strC94),"测试数传");
    delete [] strcrc;
}
//10.4.22 测试数传停止C95
void sub1553_tccontrol2::on_pushButton_C95_clicked()
{
    Str_C95 strC95;
    memset(&strC95,0,sizeof (strC95));
    //指令长度
    strC95.order_len=qToBigEndian((ushort) sizeof (strC95));
    //指令标识
    strC95.order_mark=0x95;

    //校验和
    uchar* strcrc=new uchar[sizeof (strC95)+1];
    memcpy(strcrc,&strC95,sizeof (strC95));
    ushort crc=0;
    for (uint i=0;i<sizeof (strC95)-2;i++) {
        crc+=strcrc[i];
    }
    strC95.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strC95,sizeof (strC95),"测试数传停止");
    delete [] strcrc;
}
//10.4.23 射频前端自动增益开关C96
void sub1553_tccontrol2::on_pushButton_C96_clicked()
{
    Str_C96 strC96;
    memset(&strC96,0,sizeof (strC96));
    //指令长度
    strC96.order_len=qToBigEndian((ushort) sizeof (strC96));
    //指令标识
    strC96.order_mark=0x96;

    //开关使能
    strC96.switch_kg=ui->comboBox_C96_1->currentIndex();
    //校验和
    uchar* strcrc=new uchar[sizeof (strC96)+1];
    memcpy(strcrc,&strC96,sizeof (strC96));
    ushort crc=0;
    for (uint i=0;i<sizeof (strC96)-2;i++) {
        crc+=strcrc[i];
    }
    strC96.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strC96,sizeof (strC96),"射频前端自动增益开关:"+ui->comboBox_C96_1->currentText());
    delete [] strcrc;
}
//10.4.24 接口DSP6678内存下传C97
void sub1553_tccontrol2::on_pushButton_C97_clicked()
{
    Str_C97 strC97;
    memset(&strC97,0,sizeof (strC97));
    //指令长度
    strC97.order_len=qToBigEndian((ushort) sizeof (strC97));
    //指令标识
    strC97.order_mark=0x97;
    //数传通道
    strC97.dataAD=ui->comboBox_C97_1->currentIndex()+1;
    //内存开始地址
    strC97.memSaddr=toHex_uint(ui->lineEdit_C97_2->text());
    //内存结束地址
    strC97.memEaddr=toHex_uint(ui->lineEdit_C97_3->text());

    //校验和
    uchar* strcrc=new uchar[sizeof (strC97)+1];
    memcpy(strcrc,&strC97,sizeof (strC97));
    ushort crc=0;
    for (uint i=0;i<sizeof (strC97)-2;i++) {
        crc+=strcrc[i];
    }
    strC97.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strC97,sizeof (strC97),"接口DSP6678内存下传:"+ui->comboBox_C97_1->currentText());
    delete [] strcrc;
}
//板卡发送选择
void sub1553_tccontrol2::on_cb_cardChooe_currentIndexChanged(int index)
{
    emit se_arg2(index,ui->comboBox_gslChoose->currentIndex());
    if(index==0)//1553板卡
    {
        ui->comboBox_gslChoose->setEnabled(true);
    }
    else
    {
        ui->comboBox_gslChoose->setEnabled(false);
    }
}

void sub1553_tccontrol2::re_arg2(int a, int b)
{
    ui->cb_cardChooe->setCurrentIndex(a);
    ui->comboBox_gslChoose->setCurrentIndex(b);
}



