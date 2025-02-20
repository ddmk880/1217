#ifndef CN_SIGNALCONTRL_H
#define CN_SIGNALCONTRL_H
#include <QTcpSocket>
#include <QMap>

using namespace std;

//QT += core network :.pro添加

/* 国产信号源控制------整理控制命令接口函数
 * 说明：有两种网络控制，1：通过VISA库实现网络程控。
 *                    2：通过socket实现网络程控（本文件采样socket控制，不需要visa驱动）*/

;
#pragma pack(push,1)

//自定义信号源结构体
struct Signal_Str{

    bool rel;       //是否rel
    double fre;     //频率
    double power;   //幅度
    double custom;  //码速率
    uchar type;   //信号样式

};

#pragma pack(pop)

class CN_SignalContrl: public QObject
{
    Q_OBJECT
public:
    CN_SignalContrl();
    ~CN_SignalContrl();
    QTcpSocket* tcpSocket;

    bool Tcp_Connet(QString ip,unsigned short port);//连接到服务端网络
    int Tcp_SendData(char* data,long long len);     //发送数据到服务端
    void Tcp_DisConnet();                           //断开服务端网络
    bool setSignal_data(Signal_Str sigstr);        //设置信号源内容

    map<int,QString> Type;        //调制类型
signals:
    void GetMess(QString str);
private slots:
    void connected_SLOT();//连接触发槽
    void readyRead_SLOT();//接收槽tcp信息

public:

    //1通用命令
    //通用命令用来控制仪器状态寄存器、状态报告、同步、数据存储及其它通用功能，
    //通用命令的用法和作用适用不同的仪器。所有的通用命令都可以通过命令字中的第一个“*”被识别，在 IEEE488.2 中详细定义了这些通用命令

    bool clearState();            //清空仪器状态 == *CLS
    bool setStorage(int value);   //设置或查询标准事件状态使能寄存器。0禁止。1使能 == *ESE <value>/*ESE?/(举例: *ESE 60 使能第4+8+16+32 相应位即第2、3、4、5位。)
    int readStorage();             //读取事件状态寄存器的值，并清0该寄存器 == *ESR? ,范围 [ 0，255 ]

    bool RCL(int value);            //该命令从指定的信号发生器内部寄存器调用仪器状态 == *RCL <value>
    bool resetState();              //设置为仪器默认状态 ==  *RST
    bool saveState(int value);      //该命令存储信号发生器当前状态在指定的内部寄存器中  [ 0，99 ]== *SAV <value>
    bool Trigger();                 //该命令在信号发生器选择触发键作为触发源时使用,用于触发动作，触发所有等待触发的事件 == *TRG

    //2仪器子系统命令

    bool OUTPut_RF(bool flag);     //设置所有通道的射频开关 == :OUTPut:ALL[:STATe] ON|OFF|1|0
    bool OUTPut_MOD(bool flag);     //设置所有通道的调制总开关 == :OUTPut:MODulation:ALL[:STATe] ON|OFF|1|0
    bool Custom_MOD(bool flag);     //令使能信号发生器数字调制开关 == [:SOURce[1]|2]:RADio:CUSTom:STATe ON|OFF|1|0


    bool setFreCenter(double value);     //设置步进扫描的中心频率(6KHz~13Ghz) == [:SOURce[1]|2]:FREQuency:CENTer <val>
    bool setFre(double value);       //在连续波模式下设置信号发生器输出频率(Hz) ==[:SOURce[1]|2]:FREQuency:CW <val>
    bool setFreOffs(double value);     //频率偏置(Hz) ==[:SOURce[1]|2]:FREQuency:OFFSet <val>
    bool setFmOffs(double value);      //器调频通道1或通道2调频频偏FM(Hz) ==[:SOURce[1]|2]:FM[1]|2[:DEViation] <val>
    bool setFskOffs(double value);     //设置FSK的调频频偏FSK(Hz) ==[:SOURce[1]|2]:RADio:CUSTom:MODulation:FSK[:DEViation] <val>
    bool setAmDepth(int value);         //设置调幅通道1或通道2以百分比为单位的调幅信号深度[0,100] == [:SOURce[1]|2]:AM[1]|2[:DEPTh][:LINear] <.val>


    bool setPower(double value);      //功率电平(幅度)(-150~30dBm) ==[:SOURce[1]|2]:POWer[:LEVel][:IMMediate][:AMPLitude] <value>
    bool setPowOffs(double value);     //功率偏置值(Hz) ==[:SOURce[1]|2]:POWer[:LEVel][:IMMediate]:OFFSet <value>

    bool setCustom(double value);      //设置信号发生器数字调制码元速率(50sps~312.5Msps)== [:SOURce[1]|2]:RADio:CUSTom:SRATe <val>
    bool setCustomSoure(QString strtmp);//设置信号发生器数字调制信号的数据源 == [:SOURce[1]|2]:RADio:CUSTom:DATA PN9|A PN9|PN11|PN15|PN16|PN20|PN21|PN23|ZERO|ONE|PATTern|PRAM

    bool setCustMode(QString strtmp);   //该命令设置基带的调制格式（信号样式）== [:SOURce[1]|2]:RADio:CUSTom:MODulation[:TYPE] <Mode>
                                       /* Mode值:  ASK|BPSK|QPSK|QPSK45|QEDGe|AQPSk|OQPSk|P4QPsk|P2DBpsk|P4DQpsk|P8D8psk|8PSK|
                                        * 8PEDGe|16QAM|16QEDgE|32QAM|32QEDGe| 64QAM|128QAM|256QAM|512QAM|1024QAM|2048QAM|
                                        * 4096QAM|MSK|2FSK|4FSK|8FSK|16FSK|32FSK|64FSK|UFSK|16APSK|32APSK|UIQ*/
    bool setFM(bool flag);              //设置信号发生器调频通道1或2的开关状态== [:SOURce[1]|2]:FM[1]|2:STATe ON|OFF|1|0
    bool setAM(bool flag);              //设置信号发生器调幅通道1或2的开关状态==[:SOURce]:AM[1]|2:STATe ON|OFF|1|0




};

#endif // CN_SIGNALCONTRL_H
