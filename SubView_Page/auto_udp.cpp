#include "auto_udp.h"
#include "ui_auto_udp.h"
#include <QDebug>
#include<QDateTime>
auto_udp::auto_udp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auto_udp)
{
    ui->setupUi(this);
    udpSocket=new QUdpSocket();//创建UDP套接字
    udpSocket->bind(QHostAddress::Any,54321);//绑定IP,端口 （监听本地所有可用的网络接口，54321端口号）
    //udpSocket->bind(QHostAddress("192.168.0.51"),54321);//绑定IP,端口 （监听所有可用的网络接口，54321端口号）
    connect(udpSocket,&QUdpSocket::readyRead,this,&auto_udp::readyRead_SLOT);//有可读取数据时，产生信号

    //qDebug()<<sizeof (str_1408);
    //单机选择标志
    check_dj[0]=true;//默认单机1
    for (int i=1;i<5;i++) {
        check_dj[i]=false;
    }
}

auto_udp::~auto_udp()
{
    udpSocket->deleteLater();
    delete ui;
}

//udp发送数据
void auto_udp::on_pB_UDPsend_clicked()
{
    QByteArray data=ui->lineEdit_sendtext->text().toLocal8Bit();//将数据转换危QByteArray类型
    udpSocket->writeDatagram(data,QHostAddress("127.0.0.2"),54321);

}

//处理接收的数据
void auto_udp::readyRead_SLOT()
{

    //定义缓存区
    QByteArray data;
    data.resize(1408);


    //读取接收到的数据，存储到data
    QHostAddress addr;
    ushort port;
    int sizeL=udpSocket->readDatagram(data.data(),data.size(),&addr,&port);
    data.resize(sizeL);
    if(sizeL !=1408)
    {
        QDateTime tm=QDateTime::currentDateTime();
        QString str=tm.toString("时间hh:mm:ss ");
        QString str2=QString("%1 本次接收数据长度为%2，不等于1408字节，不转发").arg(str).arg(sizeL);
        ui->textEdit_UDPrec->append(str2);
        ui->textEdit_UDPrec->append(data.toHex());

        return;
    }

    str_1408 str1408;
    memset(&str1408,0,sizeof (str_1408));
    memcpy(&str1408,(uchar*)data.data(),sizeof (str_1408));

    //显示
    //qDebug()<<addr.toString()<<":"<<QString::number(port)<<":"<<data;
    //ui->textEdit_UDPrec->append("发送端IP:"+addr.toString()+" 端口:"+QString::number(port));

    QDateTime tm=QDateTime::currentDateTime();
    QString str=tm.toString("时间hh:mm:ss - 符合格式，1553B接口256字节数据:");
    ui->textEdit_UDPrec->append(str);
    //ui->textEdit_UDPrec->append(data.toHex());

    //判断--包头
    if(str1408.head_4 != 0xEB905716 && str1408.head_4 != 0x165790EB) //格式头不对
    {
        ui->textEdit_UDPrec->append("数据头0xEB905716不正确！！");
        return;
    }
    //判断--大类号100
    if(str1408.str36_BandS[0]!=100)
    {
        QString tmp=QString("数据类型不正确！！大类号:%1").arg(str1408.str36_BandS[0]);
        ui->textEdit_UDPrec->append(tmp);
        return;
    }

    //小类号0转发 256字节内容
    if(str1408.str36_BandS[1]==0)
    {
        QString str1553B="类型号0::",tmp_byte;
        for (uint i=0;i<sizeof (str1408.data2);i++) {
            tmp_byte = QString().asprintf("%02x ", str1408.data2[i]);
            str1553B.append(tmp_byte);
        }


        for (int i=0;i<5;i++) {//单机1，2，3，4，全选
            if(check_dj[i]==false)continue;
            //1553板块发送
            emit send_order((uchar*)&str1408.data2[0],sizeof (str1408.data2),19,2,i);
            emit success_snack("发送成功 通道"+QString::number(i+1));
        }
        ui->textEdit_UDPrec->append(str1553B);//显示1553B发送256字节
    }
    //小类号1转发 4字节内容星时
    else if(str1408.str36_BandS[1]==1)
    {
        uint sTime=0;
        sTime=(str1408.data2[0]<<24)+(str1408.data2[1]<<16)+(str1408.data2[2]<<8)+str1408.data2[3];
        QString str_time="星时::"+QString::number(sTime);
        emit send_sTime(sTime);


        ui->textEdit_UDPrec->append(str_time);//显示1553B发送256字节

    }
    else if(str1408.str36_BandS[1]==2)//12字节总线指令
    {
        QString str1553B="类型号2::",tmp_byte;
        for (uint i=0;i<12;i++) {
            tmp_byte = QString().asprintf("%02x ", str1408.data2[i]);
            str1553B.append(tmp_byte);
        }

        for (int i=0;i<5;i++) {//单机1，2，3，4，全选
            if(check_dj[i]==false)continue;
            //1553板块发送
            emit send_order((uchar*)&str1408.data2[0],12,19,5,i);
            emit success_snack("发送成功 通道"+QString::number(i+1));
        }
        ui->textEdit_UDPrec->append(str1553B);//显示1553B发送2字节

    }
    else
    {
        QString str="小类型号错误::"+QString::number(str1408.str36_BandS[1]);
        ui->textEdit_UDPrec->append(str);//错误
    }


}

















