#ifndef CARDCTRL_1553B_H
#define CARDCTRL_1553B_H
#include <QObject>
#include <qtimer.h>
#include <QVector>
#include <QFile>
#include <QMutex>
#include <Globel_Define.h>


#include"include/busapi.h"
#include"include/pacom.h"
#include"include/visa.h"
#include"include/visatype.h"
#include"include/target_defines.h"
#include"include/rs422.h"
/***********************Class*********************
 <类    名>   CardCtrl_1553B
 <类 定 义>   1553B板卡控制接口
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>
**************************************************/
using namespace std;

//yyh 23.10.19
//矢量字16位数据类型定义
typedef struct quest_kind{
    ushort b0:1;//工作状态改变请求发送
    ushort b1:1;//慢速遥测请求发送
    ushort b2:1;//打包遥测请求发送
    ushort b3:1;//无
    ushort b4:1;//无
    ushort b5:1;//快速遥测请求发送
    ushort b6:1;//内存下卸请求发送
    ushort b7:1;//GNSS数据请求发送
    ushort b8:1;//原始观察量请求发送
    ushort b9:1;//重构数据请求发送
    ushort b10:1;//轨道姿态数据请求发送
    ushort b11:1;//无
    ushort b12:1;//无
    ushort b13:1;//无
    ushort b14:1;//远置单元测量数据请求发送
    ushort b15:1;//无
} STR_Vectorword;

class CardCtrl_1553B : public QObject{
    Q_OBJECT
public:
    CardCtrl_1553B();
    ~CardCtrl_1553B();
    int Init_BC1553Card();  //1553板卡BC端初始化
    int Init_RT1553Card();  //1553板卡RT端初始化
    void Write_RT_Data(int cnt);   //RT消息改变
    int RT_Message();               //rt消息配置发送
    int BusTools_BC_Send(uint messageID);//封装1553非周期发送函数，加锁保护（多线程同时调用1553while（）卡死）
    int OnceSend_Data(unsigned char* Data,int Datalen,ushort rt,ushort sub);//单次发送接口（数据缓存，数据长度，发送rt地址，发送子地址）
    void setSendChannal(int index);//设置AB通道发送标识
    static BT_INT _stdcall Return_Fun(BT_UINT cardnum, struct api_int_fifo *sIntFIFO);//中断回调函数（//非静态成员在类中会隐式传入一个this参数，在函数调用多出一个参数，会报错）
    ushort* msYC_buff;//慢速遥测缓存
    int InitCycle_OderSend(uint ch_id);//周期发送
    int Init_DealVector(uint ch_id);//矢量字判断发送
    void BC_Dealvetor(USHORT sldata);
    ushort Deal_vetor;//接收中断矢量字
    int Close1553B(void);
    int cyc1553_onoff(bool switch_);
    UINT Get_Time();//获取指定时间秒间隔
    int StartTimeBroadMessage();//星时和能源状态广播
    int SystemStepMessage();//系统同步
    int LongringMessage();//长抱环测试
    int OnlineMessage();//在线自测试
    int OrbitalMessage(int cnt);//轨道姿态数据广播
    vector<Orbitalstance_Data_xlsx>v_orb;
    int GNSS_timecodeMessage();//GNSS时间码

    int GNSS_postionMessage(int cnt);//GNSS定位数据
    vector<GNSS_Positioning_xlsx> v_gnss_postion;
    int GNSS_trackMessage(int cnt);//GNSS定轨数据
    vector<GNSS_Orbit_xlsx> v_gnss_orbit;
    //变量
    bool Flag_1553board;//1553广播消息
    static CardCtrl_1553B* sp_card1553;
    QTimer* timer1553;//1553周期消息定时器发送
    qulonglong m_nTimerCounter;//设置起始时间
    QFile qFile;//txt保存数据





private:
    API_INT_FIFO    sIntFIFO1;// 用于中断处理
    UINT m_CycMessno_CNT;//记录所有周期消息号总数
    map<int,int>Str_Subaddr;//矢量字数据类型字地址
    bool OpenFlag_1553;//1553板卡是否初始化成功
    static QMutex mtx_1553while;//1553判断发送锁
    unsigned short m_sendChannal;//1553发送通道AB标识


    int m_ch_id;
    int m_g_vi;
public slots:
    void WriteOnTimerMessage(uint pluse_cnt);
signals:
    void Get_1553Yc(ushort* Rxbuff,int Rxlen);
    void send_pluseStatus(bool flag_1553,int g_vi);
    void send_1553time(LL cnt);//给主界面传递时间参数显示


};

class Pluse_1553Time:public QObject{
    Q_OBJECT
public:
    Pluse_1553Time();
    ~Pluse_1553Time();

    unsigned int  StatusThread();

    bool pluse_flag;//1553初始成功标志
    int pluse_gvi;
public slots:
    void get_pluseStatus(bool flag_1553,int g_vi);
signals:
    void send_pluse(uint pluse_cnt);




};


#endif  // CARDCTRL_1553B_H
