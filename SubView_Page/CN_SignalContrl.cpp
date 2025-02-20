#include "CN_SignalContrl.h"
#include<windows.h>
#include<QTime>
CN_SignalContrl::CN_SignalContrl()
{
    //    //当前时间
    //    QDateTime cur_time = QDateTime::currentDateTime();
    //    QString time=cur_time.toString("hh:mm:ss");
    //    QString Str1;
    //    Str1 =QString("时间:%1 ").arg(time);
    //    qDebug()<<Str1;

    tcpSocket=new QTcpSocket();
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected_SLOT()));

    //信号源信号样式
    Type[0]="AM";
    Type[1]="FM";
    Type[2]="ASK";
    Type[3]="BPSK";
    Type[4]="QPSK";
    Type[5]="AQPSk";
    Type[6]="OQPSk";
    Type[7]="8PSK";
    Type[8]="16QAM";
    Type[9]="MSK";
    Type[10]="2FSK";
    Type[11]="4FSK";
    Type[12]="8FSK";
    Type[13]="16FSK";

}

CN_SignalContrl::~CN_SignalContrl()
{
    delete tcpSocket;
}

void CN_SignalContrl::Tcp_DisConnet()
{
    //    tcpSocket->close();
    //1
    tcpSocket->flush();//刷新缓存
    tcpSocket->disconnectFromHost();
    //    //2
    //    tcpSocket->abort();
}



bool CN_SignalContrl::Tcp_Connet(QString ip,unsigned short port)
{

    //连接服务端
    tcpSocket->connectToHost(ip,port);
    //等待是否连接成功
    return tcpSocket->waitForConnected();

}
//设置信号源参数
bool CN_SignalContrl::setSignal_data(Signal_Str sigstr)
{
    int status=0;
    //是否rel
    sigstr.rel=0;
    //频率
    status+=setFre(sigstr.fre * 1000000);//MHz单位
    //幅度
    status+=setPower(sigstr.power);
    //码速率
    status+=setCustom(sigstr.custom * 1000);//Ksps单位
    //信号样式
    if(Type[sigstr.type]=="AM")
    {
        status+=setAM(1);
        status+=setFM(0);
    }
    else if(Type[sigstr.type]=="FM")
    {
        status+=setAM(0);
        status+=setFM(1);
    }
    else
    {
        status+=setAM(0);
        status+=setFM(0);
        status+=setCustMode(Type[sigstr.type]);
    }

    return status;
}

int CN_SignalContrl::Tcp_SendData(char *data, long long len)
{

    QString str=":RADio:CUSTom:MODulation:FSK 666Hz\n";//发送测试
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        qDebug()<<"发送失败";
    }
    //tcpsocket->write(ui->sendwd->text().toLocal8Bit().data());//网上
    //tcpsocket->write(ui->sendwd->toPlainText().toLatin1());//xie宏伟

    /*
             QString str;
             int iSize = tcpsocket->write(str.toUtf8().data());//返回字节的大小
             //等待write写完再写下一次的write
             if(!tcpsocket->waitForBytesWritten(50000))
             {
                 return;
             }
             if(iSize ==-1) //判断发送是否成功
             {
                 qDebug() << "write error";
                 return;
             }
             若要多次向服务端发消息,可以while循环或者是其他.在这里要注意如果要多次发消息的
             话,waitForBytesWritten()这个函数是必不可少的,不然多次的话可能通信会失败.
             注:write()函数和被触发的读的readyRead()信号并不是一一对应的,比如可能你客户端
             write了三次,服务端那边的readyRead可能才被触发一次.
             */
    return isize;

}

void CN_SignalContrl::connected_SLOT()
{
    //当套接字有可供读取新数据时发出信号
    connect(tcpSocket,&QTcpSocket::readyRead,this,&CN_SignalContrl::readyRead_SLOT);
}

void CN_SignalContrl::readyRead_SLOT()
{
    QString buf;
    buf=tcpSocket->readAll();
    //ui->textEdit_massages->append(buf);//接收由tcp发过来的信息
    //ui->textEdit_massages->append(buf.toUtf8());
    emit GetMess(buf);
}



//...通用命令

bool CN_SignalContrl::clearState()
{
    QString str="*CLS\n";
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setStorage(int value)
{
    QString str=QString("*ESE %1\n").arg(value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());

    if(isize==-1)
    {
        return false;
    }
    return true;
}

int CN_SignalContrl::readStorage()
{
    QString str="*ESR?\n";
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());

    if(isize==-1)
    {

    }
    else {

        tcpSocket->waitForReadyRead();//等待服务端回应，如果不回应会一直阻塞
        QByteArray tmp=tcpSocket->readAll();//获取应答需要屏蔽tcp信号接收
        int tmp2=tmp.toInt();
        return tmp2;
    }
    return -1;
}

bool CN_SignalContrl::RCL(int value)
{
    QString str=QString("*RCL %1\n").arg(value);//设置

    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::resetState()
{
    QString str="*RST\n";
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::saveState(int value)
{
    QString str=QString("*SAV %1\n").arg(value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::Trigger()
{
    QString str="*TRG\n";
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

//...输出子系统

bool CN_SignalContrl::OUTPut_RF(bool flag)
{
    QString str=QString(":OUTPut:ALL %1\n").arg(flag);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::OUTPut_MOD(bool flag)
{
    QString str=QString(":OUTPut:MODulation:ALL %1\n").arg(flag);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::Custom_MOD(bool flag)
{
    QString str=QString(":RADio:CUSTom:STATe %1\n").arg(flag);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setFreCenter(double value)
{
    QString str=QString(":FREQuency:CENTer %1Hz\n").arg((LONGLONG)value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setFre(double value)
{
    QString str=QString(":FREQuency %1Hz\n").arg((LONGLONG)value);//浮点转字符串 小数点后3位会丢弃
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setFreOffs(double value)
{
    QString str=QString(":FREQuency:OFFSet %1Hz\n").arg((LONGLONG)value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setFmOffs(double value)
{
    QString str=QString(":FM:DEViation %1Hz\n").arg((LONGLONG)value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setFskOffs(double value)
{
    QString str=QString(":RADio:CUSTom:MODulation:FSK %1Hz\n").arg((LONGLONG)value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setAmDepth(int value)
{
    QString str=QString(":AM:DEPTh %1\n").arg(value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}


bool CN_SignalContrl::setPower(double value)
{
    QString str=QString(":POWer %1dBm\n").arg((LONGLONG)value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setPowOffs(double value)
{
    QString str=QString(":POWer:OFFS %1dB\n").arg((LONGLONG)value);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setCustom(double value)
{
    QString str=QString(":RADio:CUSTom:SRATe %1sps\n").arg((LONGLONG)value);//浮点转字符串 小数点后3位会丢弃
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setCustomSoure(QString strtmp)
{
    QString str=QString(":RADio:CUSTom:DATA %1\n").arg(strtmp);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setCustMode(QString strtmp)
{
    QString str=QString(":RADio:CUSTom:MODulation %1\n").arg(strtmp);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setFM(bool flag)
{
    QString str=QString(":FM:STATe %1\n").arg(flag);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}

bool CN_SignalContrl::setAM(bool flag)
{
    QString str=QString(":AM:STATe %1\n").arg(flag);
    int isize=tcpSocket->write(str.toLocal8Bit().data(),str.size());
    if(isize==-1)
    {
        return false;
    }
    return true;
}


