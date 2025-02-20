#include "sub1553_tccontrol_sxku.h"
#include "ui_sub1553_tccontrol_sxku.h"
#include<qmath.h>

sub1553_tccontrol_sxku::sub1553_tccontrol_sxku(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_tccontrol_sxku)
{
    ui->setupUi(this);
}

sub1553_tccontrol_sxku::~sub1553_tccontrol_sxku()
{
    delete ui;
}

void sub1553_tccontrol_sxku::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 16;
    order_data.gap_time = 1;
    order_data.order_name ="透传-"+ buffname;

    order_data.order_kind =12;//发送类型

    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff,buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

uint sub1553_tccontrol_sxku::toHex_uint(QString qstr)
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

ushort sub1553_tccontrol_sxku::toHex_ushort(QString qstr)
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

uchar sub1553_tccontrol_sxku::toHex_uchar(QString qstr)
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

uchar *sub1553_tccontrol_sxku::toHex_buff(QString qstr)
{
    QString S_tmp;
    QByteArray hex_data;
    int strlen;
    S_tmp=qstr;
    S_tmp=S_tmp.replace("0x","");
    hex_data=QByteArray::fromHex(S_tmp.toLatin1());//将字节流转换位16进制,char型
    strlen=(S_tmp.size()+1)/2;
    uchar* buff=new uchar [strlen+1];

    memcpy(buff,(uchar*)hex_data.data(),strlen);

    return buff;
}


//9.2.1 遥测轮询C51
void sub1553_tccontrol_sxku::on_pushButton_C51_clicked()
{
    YccycleC51 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x51;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"遥测轮询");
    delete [] strcrc;
}
//9.2.1.1 阵面二次电源控制C52
void sub1553_tccontrol_sxku::on_pushButton_C52_clicked()
{
    second_power arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x52;
    //子阵
    arr.zz=pow(2,ui->comboBoxc52_1->currentIndex());
    //接收发射
    arr.recive_send=ui->comboBoxc52_2->currentIndex();
    //开关电
    arr.switch_power=ui->comboBoxc52_3->currentIndex();

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"阵面二次电源控制");
    delete [] strcrc;
}
//射频收发电源控制C53
void sub1553_tccontrol_sxku::on_pushButton_C53_clicked()
{
    sppowerC53 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x53;

    //接收发射
    arr.recive_send=ui->comboBoxc53_1->currentIndex();
    //开关电
    arr.switch_power=ui->comboBoxc53_2->currentIndex();

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"射频收发电源控制:"+ui->comboBoxc53_2->currentText());
    delete [] strcrc;
}

//射频收发开关控制c54
void sub1553_tccontrol_sxku::on_pushButton_C54_clicked()
{
    spswitchC54 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x54;

    //开关
    uchar tmp=0;
    switch (ui->comboBox_C54_1->currentIndex()) {
    case 0:
        tmp=0x1B;
        break;
    case 1:
        tmp=0x2D;
        break;
    case 2:
        tmp=0x36;
        break;
    default:
        break;
    }
    arr.switch_contrl=tmp;

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"射频收发开关控制");
    delete [] strcrc;
}


//RS422线路控制选择指令C55
void sub1553_tccontrol_sxku::on_pushButton_C55_clicked()
{
    Rs422chooseC55 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x55;

    //开关
    arr.contrlPower=ui->comboBox_C55_1->currentIndex();
    if(ui->comboBox_C55_1->currentIndex()==1)arr.contrlPower=0xFF;

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"RS422线路控制选择指令:"+ui->comboBox_C55_1->currentText());
    delete [] strcrc;
}


//9.2.4 FLASH编码读C56
void sub1553_tccontrol_sxku::on_pushButton_C56_clicked()
{
    flashReadC56 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x56;

    //FLASH起始地址(高字节）
    arr.addr_1=toHex_uchar(ui->lineEditC56_1->text());
    //FLASH起始地址(中字节）
    arr.addr_2=toHex_uchar(ui->lineEditC56_2->text());
    //FLASH起始地址(低字节）
    arr.addr_3=toHex_uchar(ui->lineEditC56_3->text());

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"FLASH编码读");
    delete [] strcrc;
}



//9.2.5 FLASH编码写C57
void sub1553_tccontrol_sxku::on_pushButton_C57_clicked()
{
    flashWriteC57 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x57;

    //FLASH起始地址(高字节）
    arr.addr_1=toHex_uchar(ui->lineEditC57_1->text());
    //FLASH起始地址(中字节）
    arr.addr_2=toHex_uchar(ui->lineEditC57_2->text());
    //FLASH起始地址(低字节）
    arr.addr_3=toHex_uchar(ui->lineEditC57_3->text());
    //FLASH内容
    QString str=ui->lineEditC57_4->text();
    str=str.replace("0x","");
    int strlen=(str.size()+1)/2;
    memcpy(arr.buff,toHex_buff(str),strlen);

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"FLASH编码写");
    delete [] strcrc;
}




//9.2.6 FLASH擦除C5A
void sub1553_tccontrol_sxku::on_pushButton_C5A_clicked()
{
    flashClearC5A arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x5A;

    //FLASH起始地址(高字节）
    arr.addr_1=toHex_uchar(ui->lineEditC5A_1->text());
    //FLASH起始地址(中字节）
    arr.addr_2=toHex_uchar(ui->lineEditC5A_2->text());
    //FLASH起始地址(低字节）
    arr.addr_3=toHex_uchar(ui->lineEditC5A_3->text());

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"FLASH擦除");
    delete [] strcrc;
}
//9.2.7 工作时长设置C5B
void sub1553_tccontrol_sxku::on_pushButton_C5B_clicked()
{
    worktimeC5B arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x5B;

    //工作时长
    arr.worktime=qToBigEndian(ui->lineEdit_C5B_1->text().toUShort());
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"工作时长设置");
    delete [] strcrc;
}
//9.2.8 子阵选择控制C5C
void sub1553_tccontrol_sxku::on_pushButton_5C_clicked()
{
    zzC5C arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x5C;

    //工作时长
    arr.zzchoose=ui->comboBox5C_1->currentIndex()+(ui->comboBox5C_2->currentIndex()<<1)
            +(ui->comboBox5C_3->currentIndex()<<2)+(ui->comboBox5C_4->currentIndex()<<3);
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"子阵选择控制");
    delete [] strcrc;
}
//9.2.9 天线工作模式设置指令C5D
void sub1553_tccontrol_sxku::on_pushButton_C5D_clicked()
{
    txworkC5D arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x5D;

    //天线工作模式
    arr.txwork=ui->comboBox_C5D_1->currentIndex()+1;

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"天线工作模式设置:"+ui->comboBox_C5D_1->currentText());
    delete [] strcrc;
}
//9.2.10 阵面解锁指令C5E
void sub1553_tccontrol_sxku::on_pushButton_C5E_clicked()
{
    zlunlockC5E arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x5E;

    //天线工作模式
    arr.unlock=0x31;

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"阵面解锁指令");
    delete [] strcrc;
}
