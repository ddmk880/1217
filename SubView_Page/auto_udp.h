#ifndef AUTO_UDP_H
#define AUTO_UDP_H
#include <Globel_Define.h>
#include <QWidget>
#include <QUdpSocket>

//转发数据结构体

struct str_1408{
    uint head_4; //0xEB905716

    //。。。。。。。。。。36字节
    uchar str36_1;
    uchar str36_2;
    uchar str36_3;
    uchar str36_4;
    uint  str36_5;
    uint  str36_6;
    LL    str36_7;
    uchar str36_8[3];
    uchar  str36_9;
    uchar str36_BandS[2]; //大类号：100 ，小类型号：0
    ushort str36_10;
    uint  str36_11;
    uchar str36_12;
    uchar str36_13;
    uchar str36_14;
    uchar str36_15;

    //。。。。。。。。。。。。1360字节数据
    uchar data1[24];    //24字节头
    uchar data2[256];   //1553B内容256字节,或者4字节星时（大端）
    uchar data3[1080];  //其余内容

    uchar final[8];


};
namespace Ui {
class auto_udp;
}

class auto_udp : public QWidget
{
    Q_OBJECT

public:
    explicit auto_udp(QWidget *parent = nullptr);
    ~auto_udp();
    bool check_dj[5];//任务界面单机选择
    QUdpSocket* udpSocket;

signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);
    int send_order(uchar* data , int Datalen, ushort rt, ushort sub,int addr);//1553上注界面指令
    int send_sTime(uint time);//改变星时

private slots:
    void readyRead_SLOT();//接收槽udp信息

    void on_pB_UDPsend_clicked();

private:
    Ui::auto_udp *ui;
};

#endif // AUTO_UDP_H
