#include "sub1553_tccontrol.h"
#include "ui_sub1553_tccontrol.h"

sub1553_tccontrol::sub1553_tccontrol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_tccontrol)
{
    ui->setupUi(this);
    ui->cb_cardChooe->setStyleSheet("background-color:rgb(210,210,210)");

}

sub1553_tccontrol::~sub1553_tccontrol()
{
    delete ui;
}



void sub1553_tccontrol::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 10;
    order_data.gap_time = 1;
    order_data.order_name = "透传-"+buffname;
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


//透传:开始软件上注
void sub1553_tccontrol::on_pushButton_startup_clicked()
{

    Str_startUp startup;
    memset(&startup,0,sizeof (startup));

    //指令长度
    startup.slen=qToBigEndian((ushort) sizeof (startup));
    //指令标志
    startup.zlmark=0x82;
    //上注方式
    startup.uomand=ui->comboBox_upmaind->currentIndex();
    if(ui->comboBox_upmaind->currentIndex()==1)startup.uomand=0xff;
    //FLASH编号
    startup.flash_mark=ui->comboBox_upmark->currentIndex()+1;
    //软件代号(16进制)    
    startup.sorftnumber=toHex_ushort(ui->lineEdit_sorftnum->text());
    //软件大小
    startup.sorftsize=qToBigEndian(ui->lineEdit_sorftsum->text().toUShort());
    //FLASH起始地址(16进制)
    startup.flash_startaddr=toHex_uint(ui->lineEdit_flashsaddr->text());
    //校验和crc
    uchar* strcrc=new uchar[sizeof (startup)];
    memcpy(strcrc,&startup,sizeof (startup));
    ushort crcs=0;
    for (uint i=0;i<sizeof (startup)-2;i++) {
        crcs+=strcrc[i];
    }
    startup.crc=qToBigEndian(crcs);


    //列表封装
    Pblic_Addorderlist((uchar*)&startup,sizeof (startup),"开始软件上注");


}
//软件重构
void sub1553_tccontrol::on_pushButton_rjcg_clicked()
{
    rjcg arr;
    memset(&arr,0,sizeof (arr));
    QString S_sorftnum;
    QByteArray hex_data;
    //指令长度
    arr.zlcd=qToBigEndian((ushort) sizeof (arr));
    //指令标识
    arr.zlbs=0x8A;
    //芯片代号1
    arr.xpdh1=qToBigEndian(ui->lineEdit_xpdh1->text().toUShort());
    //软件代号1
    S_sorftnum=ui->lineEdit_rjdh1->text();
    arr.rjdh1=toHex_ushort(S_sorftnum);
    //操作方式1
    arr.czfs1=ui->comboBox_czfs1->currentIndex()+1;
    //芯片代号2
    arr.xpdh2=qToBigEndian(ui->lineEdit_xpdh2->text().toUShort());
    //软件代号2
    S_sorftnum=ui->lineEdit_rjdh2->text();
    arr.rjdh2=toHex_ushort(S_sorftnum);
    //操作方式2
      arr.czfs2=ui->comboBox_czfs2->currentIndex()+1;
    //芯片代号3
    arr.xpdh3=qToBigEndian(ui->lineEdit_xpdh3->text().toUShort());
    //软件代号3
    S_sorftnum=ui->lineEdit_rjdh3->text();
    arr.rjdh3=toHex_ushort(S_sorftnum);
    //操作方式3
      arr.czfs3=ui->comboBox_czfs3->currentIndex()+1;
    //芯片代号4
    arr.xpdh4=qToBigEndian(ui->lineEdit_xpdh4->text().toUShort());
    //软件代号4
    S_sorftnum=ui->lineEdit_rjdh4->text();
    arr.rjdh4=toHex_ushort(S_sorftnum);
    //操作方式4
   arr.czfs4=ui->comboBox_czfs4->currentIndex()+1;
    //芯片代号5
    arr.xpdh5=qToBigEndian(ui->lineEdit_xpdh5->text().toUShort());
    //软件代号5
    S_sorftnum=ui->lineEdit_rjdh5->text();
    arr.rjdh5=toHex_ushort(S_sorftnum);
    //操作方式5
      arr.czfs5=ui->comboBox_czfs5->currentIndex()+1;
    //芯片代号6
    arr.xpdh6=qToBigEndian(ui->lineEdit_xpdh6->text().toUShort());
    //软件代号6
    S_sorftnum=ui->lineEdit_rjdh6->text();
    arr.rjdh6=toHex_ushort(S_sorftnum);
    //操作方式6
    arr.czfs6=ui->comboBox_czfs6->currentIndex()+1;
    //芯片代号7
    arr.xpdh7=qToBigEndian(ui->lineEdit_xpdh7->text().toUShort());
    //软件代号7
    S_sorftnum=ui->lineEdit_rjdh7->text();
    arr.rjdh7=toHex_ushort(S_sorftnum);
    //操作方式7
      arr.czfs7=ui->comboBox_czfs7->currentIndex()+1;
    //芯片代号8
    arr.xpdh8=qToBigEndian(ui->lineEdit_xpdh8->text().toUShort());
    //软件代号8
    S_sorftnum=ui->lineEdit_rjdh8->text();
    arr.rjdh8=toHex_ushort(S_sorftnum);
    //操作方式8
    arr.czfs8=ui->comboBox_czfs8->currentIndex()+1;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort jyhs=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        jyhs+=strcrc[i];
    }
    arr.jyh=qToBigEndian(jyhs);
    //列表封装
    int cg_tmpkind=ui->comboBox_czfs1->currentIndex()+
           ui->comboBox_czfs2->currentIndex()+
           ui->comboBox_czfs3->currentIndex()+
           ui->comboBox_czfs4->currentIndex()+
           ui->comboBox_czfs5->currentIndex()+
           ui->comboBox_czfs6->currentIndex()+
           ui->comboBox_czfs7->currentIndex()+
           ui->comboBox_czfs8->currentIndex();
    switch (cg_tmpkind) {
    case 0:
        Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"开始重构:一键御卸");
        break;
    case 8:
        Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"开始重构:一键重构");
        break;
    case 16:
        Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"开始重构:一键不重构");
        break;
    default:
        Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"开始重构");
        break;
    }

    delete [] strcrc;
}

void sub1553_tccontrol::fantion(int n)
{

    if(!(n==1))ui->comboBox_sfclmk->setCurrentIndex(0);
    if(!(n==2))ui->comboBox_dzzcmk->setCurrentIndex(0);
    if(!(n==3))ui->comboBox_dzgr->setCurrentIndex(0);
    if(!(n==4))ui->comboBox_SARcx->setCurrentIndex(0);
    if(!(n==5))ui->comboBox_bydx->setCurrentIndex(0);
    if(!(n==6))ui->comboBox_l5gtx->setCurrentIndex(0);
    if(!(n==7))ui->comboBox_JIDSl->setCurrentIndex(0);
    if(!(n==8))ui->comboBox_csqp->setCurrentIndex(0);
    if(!(n==9))ui->comboBox_sjcs->setCurrentIndex(0);
    if(!(n==10))ui->comboBox_norflash->setCurrentIndex(0);
}


//qstring转16进制uint
uint sub1553_tccontrol::toHex_uint(QString qstr)
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

//qstring转16进制ushort
ushort sub1553_tccontrol::toHex_ushort(QString qstr)
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


//收发处理模块

void sub1553_tccontrol::on_comboBox_sfclmk_activated(int index)
{
    n=1;
     fantion(n);
    switch (index) {
    case 0:

        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");


        break;
    case 1:
        //采集与信道化接收软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F02");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x00000");


        break;
    case 2:
        //波束合成接收软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F03");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x00E00");


        break;
    case 3:
        //波束合成发射软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F04");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x01C00");



        break;
    case 4:
        //调频源软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F41");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x02A00");


        break;
    case 5:
        //数据形成软件
      ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F42");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x03800");


        break;
    }
}

//电子侦察模块
void sub1553_tccontrol::on_comboBox_dzzcmk_activated(int index)
{
      n=2;
       fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //宽带信号检测和存储软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x04600");

        break;
    case 2:
        //LINK16测向软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F02");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x05400");

        break;
    case 3:
        //塔康侦测软件
      ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F03");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x06200");

        break;
    case 4:
        //塔康全频段侦察软件
     ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F04");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x07000");

        break;
    case 5:
        //敌我侦测软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F05");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x07E00");

        break;
    case 6:
        //铱星信号侦测软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x08C00");

        break;
    case 7:
        //海事信号侦测软件
     ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F07");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x09A00");

        break;
    case 8:
        //星链信号侦察软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F08");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0A800");


        break;
    case 9:
        //雷达信号预处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F09");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0B600");

        break;
    case 10:
        //通信信号处理软件
       ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1D10");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x31000");

        break;
    case 11:
        //雷达信号主处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1D11");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x31400");

        break;
    case 12:
        //宽带信号检测和存储软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x21400");

        break;
    case 13:
        //高频段雷达信号预处理软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1F12");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x23000");

        break;
    case 14:
        //通信信号处理软件
       ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x1D10");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x33000");

        break;
    }
}
//电子干扰
void sub1553_tccontrol::on_comboBox_dzgr_activated(int index)
{
      n=3;
       fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //通信干扰处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0C400");

        break;
    case 2:
        //导航与星链干扰处理软件
       ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F02");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0D200");

        break;
    case 3:
        //通信与导航干扰策略与控制软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2D03");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x31800");

        break;
    case 4:
        //雷达侦察干扰处理软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F04");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0E000");

        break;
    case 5:
        //雷达干扰策略与控制软件
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2D05");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x31C00");

        break;
    case 6:
        //通信干扰处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x23E00");

        break;
    case 7:
        //导航与星链干扰处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F02");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x24C00");

        break;
    case 8:
        //通信与导航干扰策略与控制软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2D03");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x33800");

        break;
    }
}
//SAR成像
void sub1553_tccontrol::on_comboBox_SARcx_activated(int index)
{
      n=4;
       fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //2m/3m模式成像预处理FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0EE00");

        break;
    case 2:
        //2m/3m模式成像1FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F02");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x0FC00");

        break;
    case 3:
        //2m/3m模式成像2FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F03");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x10A00");

        break;
    case 4:
        //10m模式成像预处理FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F04");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x11800");

        break;
    case 5:
        //10m模式成像1FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F05");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x12600");

        break;
    case 6:
        //10m模式成像2FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x13400");

        break;
    case 7:
        //2m/3m/10m模式一体化成像3FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F07");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x14200");

        break;
    case 8:
        //2m/3m/10m模式一体化成像4FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F08");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x15000");

        break;
    case 9:
        //2m/3m条带模式目标检测FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F09");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x15E00");

        break;
    case 10:
        //2m/3m条带模式动目标精聚焦FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F10");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x16C00");

        break;
    case 11:
        //2m/3m条带模式目标识别分类FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F11");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x17A00");

        break;
    case 12:
        //(2m~5m)(R)*200m(A)广域搜索模式探测成像1FPGA
        ui->lineEdit_sorftnum->setText("0x3F12");
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x18800");

        break;
    case 13:
        //(2m~5m)(R)*200m(A)广域搜索模式探测成像2FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F13");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x19600");

        break;
    case 14:
        //(2m~5m)(R)*200m(A)广域搜索模式探测成像3FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F14");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1A400");

        break;
    case 15:
        //(2m~5m)(R)*200m(A)广域搜索模式目标检测FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F15");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1B200");

        break;
    case 16:
        //(2m~5m)(R)*200m(A)广域搜索模式目标军民分类FPGA
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x3F16");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1C000");

        break;
    }
}
//备用导航
void sub1553_tccontrol::on_comboBox_bydx_activated(int index)
{
      n=5;
       fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //星历拟合与控制软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x4D01");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x32000");

        break;
    case 2:
        //导航信号生成软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x4F02");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1CE00");

        break;
    }
}
//类5G通信
void sub1553_tccontrol::on_comboBox_l5gtx_activated(int index)
{
    n=6;
     fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //类5G通信软件更新区
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x5F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1DC00");

        break;
    case 2:
        //类5G协议控制软件更新区
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x5D02");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x32400");

        break;
    case 3:
        //类5G通信软件基础区
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x5F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x25A00");

        break;
    case 4:
        //类5G协议控制软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x5D02");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x33C00");

        break;
    }
}
//JIDS链
void sub1553_tccontrol::on_comboBox_JIDSl_activated(int index)
{
    n=7;
     fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //数据链信号处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x6F01");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1EA00");

        break;
    case 2:
        //数据链信息处理软件
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x6D02");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x32800");

        break;
    }
}
//产生式欺骗
void sub1553_tccontrol::on_comboBox_csqp_activated(int index)
{
      n=8;
       fantion(n);

    switch (index) {
    case 0:
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //产生式欺骗干扰FPGA1
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x1F800");

        break;
    case 2:
        //产生式欺骗干扰FPGA2
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2F07");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x20600");

        break;
    case 3:
        //产生式欺骗干扰DSP1
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x2D08");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x32C00");

        break;
    }
}
//数据参数
void sub1553_tccontrol::on_comboBox_sjcs_activated(int index)
{
    n=9;
     fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //幅度表
        ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F81");
        ui->lineEdit_sorftsum->setText(QString::number(1*1024));
        ui->lineEdit_flashsaddr->setText("0x36000");

        break;
    case 2:
        //舰船检测网络参数
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F82");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x36080");

        break;
    case 3:
        //舰船识别网络参数
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F83");
        ui->lineEdit_sorftsum->setText(QString::number(16*1024));
        ui->lineEdit_flashsaddr->setText("0x36480");

        break;
    case 4:
        //探测模式舰船分类网络参数
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F84");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x36C80");

        break;
    case 5:
        //海陆分割数据库
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F85");
        ui->lineEdit_sorftsum->setText(QString::number(130*1024));
        ui->lineEdit_flashsaddr->setText("0x37080");

        break;
    case 6:
        //零值补偿参数、功率参数
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F86");
        ui->lineEdit_sorftsum->setText(QString::number(1*1024));
        ui->lineEdit_flashsaddr->setText("0x3B180");

        break;
    case 7:
        //通信参数
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F87");
        ui->lineEdit_sorftsum->setText(QString::number(2*1024));
        ui->lineEdit_flashsaddr->setText("0x3B200");

        break;
    case 8:
        //雷达重点侦察库
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F88");
        ui->lineEdit_sorftsum->setText(QString::number(9*1024));
        ui->lineEdit_flashsaddr->setText("0x3B300");

        break;
    case 9:
        //高算力平台FLASH分区表（存三份）
         ui->comboBox_upmark->setCurrentIndex(2);
        ui->lineEdit_sorftnum->setText("0x0F89");
        ui->lineEdit_sorftsum->setText(QString::number(1*1024));
        ui->lineEdit_flashsaddr->setText("0x3B780");

        break;
    }
}
//NOR FLASH
void sub1553_tccontrol::on_comboBox_norflash_activated(int index)
{
    n=10;
    fantion(n);

    switch (index) {
    case 0:
        ui->lineEdit_sorftnum->setText("0");
        ui->lineEdit_sorftsum->setText(QString::number(0));
        ui->lineEdit_flashsaddr->setText("0");

        break;
    case 1:
        //接口控制软件1（收发处理模块）
         ui->comboBox_upmark->setCurrentIndex(0);
        ui->lineEdit_sorftnum->setText("0x0F01");
        ui->lineEdit_sorftsum->setText(QString::number(16*1024));
        ui->lineEdit_flashsaddr->setText("0x0000000");

        break;
    case 2:
        //接口控制软件1（数据处理模块）
         ui->comboBox_upmark->setCurrentIndex(0);
        ui->lineEdit_sorftnum->setText("0x0F05");
        ui->lineEdit_sorftsum->setText(QString::number(16*1024));
        ui->lineEdit_flashsaddr->setText("0x1000000");

        break;
    case 3:
        //数据传输软件更新区
         ui->comboBox_upmark->setCurrentIndex(0);
        ui->lineEdit_sorftnum->setText("0x0F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x2000000");

        break;
    case 4:
        //数据传输软件基础区1
         ui->comboBox_upmark->setCurrentIndex(0);
        ui->lineEdit_sorftnum->setText("0x0F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x4000000");

        break;
    case 5:
        //综合调度软件1
         ui->comboBox_upmark->setCurrentIndex(0);
        ui->lineEdit_sorftnum->setText("0x0D09");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x6000000");

        break;
    case 6:
        //CAN解析及重构调度软件更新区
         ui->comboBox_upmark->setCurrentIndex(0);
        ui->lineEdit_sorftnum->setText("0x0D08");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x6800000");

        break;
    case 7:
        //接口控制软件2（收发处理模块）
         ui->comboBox_upmark->setCurrentIndex(1);
        ui->lineEdit_sorftnum->setText("0x0F01");
        ui->lineEdit_sorftsum->setText(QString::number(16*1024));
        ui->lineEdit_flashsaddr->setText("0x0000000");

        break;
    case 8:
        //接口控制软件2（数据处理模块）
         ui->comboBox_upmark->setCurrentIndex(1);
        ui->lineEdit_sorftnum->setText("0x0F05");
        ui->lineEdit_sorftsum->setText(QString::number(16*1024));
        ui->lineEdit_flashsaddr->setText("0x1000000");

        break;
    case 9:
        //数据传输软件基础区2
         ui->comboBox_upmark->setCurrentIndex(1);
        ui->lineEdit_sorftnum->setText("0x0F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x2000000");

        break;
    case 10:
        //数据传输软件基础区3
         ui->comboBox_upmark->setCurrentIndex(1);
        ui->lineEdit_sorftnum->setText("0x0F06");
        ui->lineEdit_sorftsum->setText(QString::number(28*1024));
        ui->lineEdit_flashsaddr->setText("0x4000000");

        break;
    case 11:
        //综合调度软件2
         ui->comboBox_upmark->setCurrentIndex(1);
        ui->lineEdit_sorftnum->setText("0x0D09");
        ui->lineEdit_sorftsum->setText(QString::number(8*1024));
        ui->lineEdit_flashsaddr->setText("0x6000000");

        break;
    }
}



//FLASH擦除C83
void sub1553_tccontrol::on_pushButton_flashcc_clicked()
{
    QString S_sorftnum;
    QByteArray hex_data;
    flashcc arr;
    memset(&arr,0,sizeof (arr));
    //指令长度
    arr.zlcd=qToBigEndian((ushort) sizeof (arr));
    //指令标识
    arr.zlbs=0x83;
    //起始块地址
    S_sorftnum=ui->lineEdit_ccqskdz->text();

    arr.qskdz=toHex_ushort(S_sorftnum);

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort jyhs=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        jyhs+=strcrc[i];
    }
    arr.jyh=qToBigEndian(jyhs);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"FLASH擦除");
    delete [] strcrc;
}
//FLASH擦除状态查询C84
void sub1553_tccontrol::on_pushButton_clicked()
{
    flashccztcx arr;
    memset(&arr,0,sizeof (arr));
    //指令长度
    arr.zlcd=qToBigEndian((ushort) sizeof (arr));
    //指令标识
    arr.zlbs=0x84;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort jyhs=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        jyhs+=strcrc[i];
    }
    arr.jyh=qToBigEndian(jyhs);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"FLASH擦除状态查询");
    delete [] strcrc;

}


//软件上注C85
void sub1553_tccontrol::on_pushButton_sorftUp_clicked()
{
    QString S_sorftnum;
    QByteArray hex_data;
    Str_sorftupC85 Str_sorftup;
    memset(&Str_sorftup,0,sizeof (Str_sorftup));
    //指令长度
    Str_sorftup.order_len=qToBigEndian((ushort) sizeof (Str_sorftup));
    //指令标识
    Str_sorftup.order_mark=0x85;
    //页地址
    S_sorftnum=ui->lineEdit_firstAddr->text();
    Str_sorftup.page_addr=toHex_uint(S_sorftnum);
    //序号
    Str_sorftup.number=ui->lineEdit_Number->text().toInt();
    //（读取文件，多条）
    for (int i=0;i<1024;i++) {
        Str_sorftup.datas[i]=i+1;
    }
    //校验和
    uchar* strcrc=new uchar[sizeof (Str_sorftup)+1];
    memcpy(strcrc,&Str_sorftup,sizeof (Str_sorftup));
    ushort crc=0;
    for (uint i=0;i<sizeof (Str_sorftup)-2;i++) {
        crc+=strcrc[i];
    }
    Str_sorftup.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&Str_sorftup,sizeof (Str_sorftup),"软件上注");
    delete [] strcrc;
}

//软件上注完成C86
void sub1553_tccontrol::on_pushButton_C86upFinash_clicked()
{

    Str_sorftfinash arr;
    memset(&arr,0,sizeof (arr));

    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x86;
    // 包数
    arr.pack_num=qToBigEndian(ui->lineEdit_c86packnum->text().toUShort());
    // 保留
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort jyhs=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        jyhs+=strcrc[i];
    }
    arr.crc=qToBigEndian(jyhs);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"软件上注完成");
    delete [] strcrc;
}



//软件写入状态查询C87
void sub1553_tccontrol::on_pushButton_writeStatus_clicked()
{
    Str_sorftWriteC87 strc87;
    memset(&strc87,0,sizeof (strc87));
    //指令长度
    strc87.order_len=qToBigEndian((ushort) sizeof (strc87));
    //指令标识
    strc87.order_mark=0x87;
    //保留
    //校验和
    uchar* strcrc=new uchar[sizeof (strc87)+1];
    memcpy(strcrc,&strc87,sizeof (strc87));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc87)-2;i++) {
        crc+=strcrc[i];
    }
    strc87.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc87,sizeof (strc87),"软件写入状态查询");
    delete [] strcrc;
}
//接口控制板FPGAV7维护C88
void sub1553_tccontrol::on_pushButton_C88_clicked()
{
    FPGAV7whC88 strc88;
    memset(&strc88,0,sizeof (strc88));
    //指令长度
    strc88.order_len=qToBigEndian((ushort) sizeof (strc88));
    //指令标识
    strc88.order_mark=0x88;
    //保留
    //校验和
    uchar* strcrc=new uchar[sizeof (strc88)+1];
    memcpy(strcrc,&strc88,sizeof (strc88));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc88)-2;i++) {
        crc+=strcrc[i];
    }
    strc88.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc88,sizeof (strc88),"接口控制板FPGAV7维护");
    delete [] strcrc;
}


// CAN解析及重构调度软件切换到更新区C89
void sub1553_tccontrol::on_pushButton_C89_clicked()
{
    Str_C89 strc89;
    memset(&strc89,0,sizeof (strc89));
    //指令长度
    strc89.order_len=qToBigEndian((ushort) sizeof (strc89));
    //指令标识
    strc89.order_mark=0x89;
    //保留
    //校验和
    uchar* strcrc=new uchar[sizeof (strc89)+1];
    memcpy(strcrc,&strc89,sizeof (strc89));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc89)-2;i++) {
        crc+=strcrc[i];
    }
    strc89.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc89,sizeof (strc89),"CAN解析及重构软件切换更新区");
    delete [] strcrc;
}

//软件下传
void sub1553_tccontrol::on_pushButton_sorftDown_clicked()
{
    QString S_sorftnum;
    QByteArray hex_data;
    Str_sorftDownC8B strc8B;
    memset(&strc8B,0,sizeof (strc8B));
    //指令长度
    strc8B.order_len=qToBigEndian((ushort) sizeof (strc8B));
    //指令标识
    strc8B.order_mark=0x8B;
    //Flash编号
    strc8B.flash_num=ui->comboBox_C8B_1->currentIndex()+1;

    //Flashd地址
    S_sorftnum=ui->lineEdit_flashaddr->text();
    strc8B.flash_addr=toHex_uint(S_sorftnum);
    //软件大小
    strc8B.Sorftware_size=qToBigEndian(ui->lineEdit_Software_size->text().toUShort());
    // 数传通道
    strc8B.data_Ad=ui->comboBox_C8B_4->currentIndex()+1;
    //校验和
    uchar* strcrc=new uchar[sizeof (strc8B)+1];
    memcpy(strcrc,&strc8B,sizeof (strc8B));
    ushort crc=0;
    for (uint i=0;i<sizeof (strc8B)-2;i++) {
        crc+=strcrc[i];
    }
    strc8B.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strc8B,sizeof (strc8B),"软件下传："+ui->comboBox_C8B_1->currentText());
    delete [] strcrc;
}




//高算力下拉框
void sub1553_tccontrol::on_comboBox_high_activated(int index)
{
    switch (index) {
       case 0:
        ui->lineEdit_xpdh1->setText(QString::number(0));
        ui->lineEdit_rjdh1->setText("0");
        ui->comboBox_czfs1->setCurrentIndex(0);

        ui->lineEdit_xpdh2->setText(QString::number(0));
        ui->lineEdit_rjdh2->setText("0");
        ui->comboBox_czfs2->setCurrentIndex(0);

        ui->lineEdit_xpdh3->setText(QString::number(0));
        ui->lineEdit_rjdh3->setText("0");
        ui->comboBox_czfs3->setCurrentIndex(0);

        ui->lineEdit_xpdh4->setText(QString::number(0));
        ui->lineEdit_rjdh4->setText("0");
        ui->comboBox_czfs4->setCurrentIndex(0);

        ui->lineEdit_xpdh5->setText(QString::number(0));
        ui->lineEdit_rjdh5->setText("0");
        ui->comboBox_czfs5->setCurrentIndex(0);

        ui->lineEdit_xpdh6->setText(QString::number(0));
        ui->lineEdit_rjdh6->setText("0");
        ui->comboBox_czfs6->setCurrentIndex(0);

        ui->lineEdit_xpdh7->setText(QString::number(0));
        ui->lineEdit_rjdh7->setText("0");
        ui->comboBox_czfs7->setCurrentIndex(0);

        ui->lineEdit_xpdh8->setText(QString::number(0));
        ui->lineEdit_rjdh8->setText("0");
        ui->comboBox_czfs8->setCurrentIndex(0);
        break;
    case 1:
        ui->comboBox_gslChoose->setCurrentIndex(0);//高算力1，2选择

        ui->lineEdit_xpdh1->setText(QString::number(112));
        ui->lineEdit_rjdh1->setText("0F02");
        ui->comboBox_czfs1->setCurrentIndex(2);

        ui->lineEdit_xpdh2->setText(QString::number(113));
        ui->lineEdit_rjdh2->setText("0F04");
        ui->comboBox_czfs2->setCurrentIndex(2);

        ui->lineEdit_xpdh3->setText(QString::number(122));
        ui->lineEdit_rjdh3->setText("1F01");
        ui->comboBox_czfs3->setCurrentIndex(2);

        ui->lineEdit_xpdh4->setText(QString::number(123));
        ui->lineEdit_rjdh4->setText("1F01");
        ui->comboBox_czfs4->setCurrentIndex(2);

        ui->lineEdit_xpdh5->setText(QString::number(125));
        ui->lineEdit_rjdh5->setText("1D10");
        ui->comboBox_czfs5->setCurrentIndex(2);

        ui->lineEdit_xpdh6->setText(QString::number(132));
        ui->lineEdit_rjdh6->setText("1F01");
        ui->comboBox_czfs6->setCurrentIndex(2);

        ui->lineEdit_xpdh7->setText(QString::number(133));
        ui->lineEdit_rjdh7->setText("1F01");
        ui->comboBox_czfs7->setCurrentIndex(2);

        ui->lineEdit_xpdh8->setText(QString::number(135));
        ui->lineEdit_rjdh8->setText("1D10");
        ui->comboBox_czfs8->setCurrentIndex(2);
        break;
    case 2:
        ui->comboBox_gslChoose->setCurrentIndex(1);//高算力1，2选择

        ui->lineEdit_xpdh1->setText(QString::number(12));
        ui->lineEdit_rjdh1->setText("0F02");
        ui->comboBox_czfs1->setCurrentIndex(2);

        ui->lineEdit_xpdh2->setText(QString::number(13));
        ui->lineEdit_rjdh2->setText("0F04");
        ui->comboBox_czfs2->setCurrentIndex(2);

        ui->lineEdit_xpdh3->setText(QString::number(22));
        ui->lineEdit_rjdh3->setText("1F01");
        ui->comboBox_czfs3->setCurrentIndex(2);

        ui->lineEdit_xpdh4->setText(QString::number(23));
        ui->lineEdit_rjdh4->setText("1F01");
        ui->comboBox_czfs4->setCurrentIndex(2);

        ui->lineEdit_xpdh5->setText(QString::number(25));
        ui->lineEdit_rjdh5->setText("1D10");
        ui->comboBox_czfs5->setCurrentIndex(2);

        ui->lineEdit_xpdh6->setText(QString::number(32));
        ui->lineEdit_rjdh6->setText("1F01");
        ui->comboBox_czfs6->setCurrentIndex(2);

        ui->lineEdit_xpdh7->setText(QString::number(33));
        ui->lineEdit_rjdh7->setText("1F01");
        ui->comboBox_czfs7->setCurrentIndex(2);

        ui->lineEdit_xpdh8->setText(QString::number(35));
        ui->lineEdit_rjdh8->setText("1D10");
        ui->comboBox_czfs8->setCurrentIndex(2);
        break;
    }
}

//DSP6678加载测试A0
void sub1553_tccontrol::on_pushButton_dsp6678_A0_clicked()
{
    Str_A0 strcA0;
    memset(&strcA0,0,sizeof (strcA0));
    //指令长度
    strcA0.order_len=qToBigEndian((ushort) sizeof (strcA0));
    //指令标识
    strcA0.order_mark=0xA0;
    //校验和
    uchar* strcrc=new uchar[sizeof (strcA0)+1];
    memcpy(strcrc,&strcA0,sizeof (strcA0));
    ushort crc=0;
    for (uint i=0;i<sizeof (strcA0)-2;i++) {
        crc+=strcrc[i];
    }
    strcA0.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&strcA0,sizeof (strcA0),"DSP6678加载测试");
    delete [] strcrc;
}

//板卡发送选择
void sub1553_tccontrol::on_cb_cardChooe_currentIndexChanged(int index)
{
    emit se_arg1(index,ui->comboBox_gslChoose->currentIndex());
    if(index==0)//1553板卡
    {
        ui->comboBox_gslChoose->setEnabled(true);
    }
    else
    {
        ui->comboBox_gslChoose->setEnabled(false);
    }
}



void sub1553_tccontrol::re_arg1(int a, int b)
{
    ui->cb_cardChooe->setCurrentIndex(a);
    ui->comboBox_gslChoose->setCurrentIndex(b);
}
//一键御卸
void sub1553_tccontrol::on_pushButton_ykyx_clicked()
{
    ui->comboBox_czfs1->setCurrentIndex(0);
    ui->comboBox_czfs2->setCurrentIndex(0);
    ui->comboBox_czfs3->setCurrentIndex(0);
    ui->comboBox_czfs4->setCurrentIndex(0);
    ui->comboBox_czfs5->setCurrentIndex(0);
    ui->comboBox_czfs6->setCurrentIndex(0);
    ui->comboBox_czfs7->setCurrentIndex(0);
    ui->comboBox_czfs8->setCurrentIndex(0);
}

//一键重构
void sub1553_tccontrol::on_pushButton_yjcg_clicked()
{
    ui->comboBox_czfs1->setCurrentIndex(1);
    ui->comboBox_czfs2->setCurrentIndex(1);
    ui->comboBox_czfs3->setCurrentIndex(1);
    ui->comboBox_czfs4->setCurrentIndex(1);
    ui->comboBox_czfs5->setCurrentIndex(1);
    ui->comboBox_czfs6->setCurrentIndex(1);
    ui->comboBox_czfs7->setCurrentIndex(1);
    ui->comboBox_czfs8->setCurrentIndex(1);
}
//一键不重构
void sub1553_tccontrol::on_pushButton_yjbcg_clicked()
{
    ui->comboBox_czfs1->setCurrentIndex(2);
    ui->comboBox_czfs2->setCurrentIndex(2);
    ui->comboBox_czfs3->setCurrentIndex(2);
    ui->comboBox_czfs4->setCurrentIndex(2);
    ui->comboBox_czfs5->setCurrentIndex(2);
    ui->comboBox_czfs6->setCurrentIndex(2);
    ui->comboBox_czfs7->setCurrentIndex(2);
    ui->comboBox_czfs8->setCurrentIndex(2);
}



