#include "sub1553_tccontrol_l.h"
#include "ui_sub1553_tccontrol_l.h"
#include <QFileDialog>
#include <QMessageBox>


sub1553_tccontrol_L::sub1553_tccontrol_L(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_tccontrol_L)
{
    ui->setupUi(this);
}

sub1553_tccontrol_L::~sub1553_tccontrol_L()
{
    delete ui;
}

void sub1553_tccontrol_L::Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname)
{
    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 12;
    order_data.gap_time = 1;
    order_data.order_name ="透传-"+ buffname;

    order_data.order_kind =11;//发送类型

    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff,buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

//qstring转16进制ushort
ushort sub1553_tccontrol_L::toHex_ushort(QString qstr)
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

//间接指令C04
void sub1553_tccontrol_L::on_pB_indirect_order_clicked()
{
    Str_indirectC04 arr;
    memset(&arr,0,sizeof (arr));

    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x04;
    // 包标识
    arr.pack_mark=qToBigEndian((ushort)0x1731);
    // 顺序标识
    arr.sequence_mark=qToBigEndian((ushort)0xc000);
    // 包长
    arr.packLen=qToBigEndian((ushort)0x0005);;
    //  功能标识
    arr.fun_mark=0;
    //  间接指令码

    QString S_sorftnum=ui->lineEdit_indirect->text();
    arr.indirect_made=toHex_ushort(S_sorftnum);
    //  和校验
    ushort* checkbuff=new ushort[2];
    memcpy(checkbuff,(uchar*)&arr.fun_mark,4);
    ushort crc2=0;
    for(uint n=0;n<2;n++)
    {
        crc2+=crc2^checkbuff[n];
    }
    arr.add_crc=crc2;//不转字节序
    delete [] checkbuff;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"间接指令");
    delete [] strcrc;
}

//矢量字查询C01
void sub1553_tccontrol_L::on_pB_Vectorword_clicked()
{

    VectorC01 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x01;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"矢量字查询");
    delete [] strcrc;
}


//总线复位C02
void sub1553_tccontrol_L::on_pB_busrepos_clicked()
{
    busrespC02 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x02;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"总线复位");
    delete [] strcrc;
}

//数据注入C03
void sub1553_tccontrol_L::on_pushButton_C03_clicked()
{

    DatainC03 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x03;

    //256字节数据
    QString path=ui->lineEdit_C03Filepath->text();
    QFile txt_file(path);
    if(!(txt_file.open(QIODevice::ReadOnly|QIODevice::Text)))
    {
        QMessageBox::warning(this,tr("打开文件失败"),tr("路径")+path);
        return ;
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
    if (this_len>256)this_len=256;
    memcpy(arr.data,data_buf,this_len);

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"数据注入");
    delete [] strcrc;
}

//数据注入C03读取文件
void sub1553_tccontrol_L::on_pB_C03ReadFile_clicked()
{
    //打开文件选择对话框
    QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt"));
    if(file_path.size() <= 0) return;
   // QFileInfo fileinfo(file_path.at(0));    //读取文件
    ui->lineEdit_C03Filepath->setText(file_path.at(0));

}


//重要数据采集C06
void sub1553_tccontrol_L::on_pB_importdata_clicked()
{
    importdataC06 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x06;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"重要数据采集");
    delete [] strcrc;
}



//任务交互数据采集C07
void sub1553_tccontrol_L::on_pB_taskdata_clicked()
{
    taskdataC07 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x07;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"任务交互数据采集");
    delete [] strcrc;
}


//遥测轮询C08
void sub1553_tccontrol_L::on_pB_ycpolling_clicked()
{
    ycpolingC08 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x08;
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


//打包遥测C09
void sub1553_tccontrol_L::on_pB_packyc_clicked()
{
    packycC09 arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x09;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"打包遥测");
    delete [] strcrc;
}


//内存下卸C0A
void sub1553_tccontrol_L::on_pB_memorydown_clicked()
{
    MemoryC0A arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x0A;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"内存下卸");
    delete [] strcrc;
}

//工作状态报告C0B
void sub1553_tccontrol_L::on_pB_workstatus_clicked()
{
    workststus arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x0B;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"工作状态报告");
    delete [] strcrc;
}


//开始内存下卸模式C0C
void sub1553_tccontrol_L::on_pB_startMemory_clicked()
{
    startMemory arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x0C;
    // 起始地址高端
    QString S_sorftnum=ui->lineEdit_addr_up->text();
    arr.addr1=toHex_ushort(S_sorftnum);
    // 起始地址低端
    S_sorftnum=ui->lineEdit_addr_down->text();
    arr.addr2=toHex_ushort(S_sorftnum);
    // 长度
    arr.len=qToBigEndian(ui->lineEdit_0C_len->text().toUShort());

    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"开始内存下卸模式");
    delete [] strcrc;
}

//停止内存下卸模式C0D
void sub1553_tccontrol_L::on_pB_stopMemory_clicked()
{
    stopMemory arr;
    memset(&arr,0,sizeof (arr));
    // 指令长度
    arr.order_len=qToBigEndian((ushort) sizeof (arr));
    // 指令标识
    arr.order_mark=0x0D;
    //校验和
    uchar* strcrc=new uchar[sizeof (arr)];
    memcpy(strcrc,&arr,sizeof (arr));
    ushort crc=0;
    for (uint i=0;i<sizeof (arr)-2;i++) {
        crc+=strcrc[i];
    }
    arr.crc=qToBigEndian(crc);
    //列表封装
    Pblic_Addorderlist((uchar*)&arr,sizeof (arr),"停止内存下卸模式");
    delete [] strcrc;
}

