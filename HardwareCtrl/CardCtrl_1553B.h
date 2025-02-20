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
    int BusTools_BC_Send(uint messageID,int addr);//封装1553非周期发送函数，加锁保护（多线程同时调用1553while（）卡死）
    int BusTools_BC_Write(int addr,uint messno,API_BC_MBUF * api_message);//封装1553BC端写消息
    int OnceSend_Data(unsigned char* Data,int Datalen,ushort rt,ushort sub,int addr);//单次发送接口（数据缓存，数据长度，发送rt地址，发送子地址,目标单机）
    void setSendChannal(int index);//设置AB通道发送标识
    static BT_INT _stdcall Return_Fun(BT_UINT cardnum, struct api_int_fifo *sIntFIFO);//中断回调函数（//非静态成员在类中会隐式传入一个this参数，在函数调用多出一个参数，会报错）
    static BT_INT _stdcall Return_Fun2(BT_UINT cardnum, struct api_int_fifo *sIntFIFO);
    static BT_INT _stdcall Return_Fun3(BT_UINT cardnum, struct api_int_fifo *sIntFIFO);
    static BT_INT _stdcall Return_Fun4(BT_UINT cardnum, struct api_int_fifo *sIntFIFO);
    ushort* msYC_buff[4];//慢速遥测缓存
    ushort* mPack_buff[4];//打包遥测缓存
    bool getHead[4];    //慢速遥测头
    int curr_YCindex[4];//慢速遥测帧
    bool getHead_pack4[4];      //打包遥测头
    int curr_YCindex_pack4[4];  //打包遥测帧

    int InitCycle_OderSend(int ch,uint ch_id);//周期发送
    int Init_DealVector(uint ch);//矢量字判断发送
    void BC_Dealvetor(USHORT sldata,int ch);
    ushort Deal_vetor[4];//接收中断矢量字
    int Close1553B(void);
    int Set_PPS(uchar tmp);//设置pps哪路输出
    int Set_PPStest();//设置pps哪路输出
    int cyc1553_onoff(bool switch_);//主界面按钮控制周期开关
    int cyc1553_AD(bool switch_);//主界面通道选择控制周期开关
    UINT Get_Time();//获取指定时间秒间隔
    int StartTimeBroadMessage(int cnt);//星时和能源状态广播
    int SystemStepMessage();//系统同步
    int LongringMessage();//长抱环测试
    int OnlineMessage();//在线自测试
    int GNSS_timecodeMessage();//GNSS时间码

    int OrbitalMessage(int cnt);//轨道姿态数据广播
    vector<Orbitalstance_Data_xlsx>v_orb;

    int GNSS_postionMessage(int cnt);//GNSS定位数据
    vector<GNSS_Positioning_xlsx> v_gnss_postion;

    int GNSS_trackMessage(int cnt);//GNSS定轨数据
    vector<GNSS_Orbit_xlsx> v_gnss_orbit;

    //变量
    bool Flag_1553board;//1553广播消息
    bool Flag_CANboard;//CAN广播消息
    static CardCtrl_1553B* sp_card1553;
    QTimer* timer1553;//1553周期消息定时器发送
    qulonglong m_nTimerCounter;//设置起始时间
    QFile qFile;//txt保存数据

    void Send_Updata_1553(QString strpth,vector<int> frame,ushort rt,ushort sub,int ch);//1553上注接口
    int UP_1553ch;//1553上注通道
    void Stop_1553UP();//停止1553上注
    //微秒级别定时器
    int USleep(int us);
    QFile tmp_1553files;//1553格式上注暂存文件
    bool flag_UP1553;//1553脉冲上注标志
    int cnt_1553send;//显示发送帧数
    int Bus_AB;
    bool m_check_chFlg[4]; //通用板卡通道号发送标志（4个通道）
    int change_RS422pps(int fl);//修改RS422脉冲输出
    bool xs_A,xs_B;//星时AB标志
    void XS_A_B(int ab,bool c);//主界面星时AB通道选择


private:
    API_INT_FIFO    sIntFIFO1;// 用于中断处理
    UINT m_CycMessno_CNT;//记录所有周期消息号总数
    map<int,int>Str_Subaddr;//矢量字数据类型字地址
    bool OpenFlag_1553;//1553板卡是否初始化成功
    //static QMutex mtx_1553while;//1553判断发送锁
    QMutex mtx_1553while;//1553判断发送锁
    QMutex mtx_1553write;//1553判断写入锁
    unsigned short m_sendChannal;//1553发送通道AB标识


    int m_ch_id[4]; //通用板卡通道号（4个通道）
    int m_g_vi;    //板卡设备号
public slots:
    void WriteOnTimerMessage(uint pluse_cnt);
    void Write_OnTimer ();//测试函数
    void udp_changeTime (uint stime);//udp改变星时
signals:
    void Get_1553Yc1(ushort* Rxbuff,int Rxlen,int ch);//慢速遥测单机1
    void Get_1553Yc2(ushort* Rxbuff,int Rxlen,int ch);//慢速遥测单机2
    void Get_1553Yc3(ushort* Rxbuff,int Rxlen,int ch);//慢速遥测单机3
    void Get_1553Yc4(ushort* Rxbuff,int Rxlen,int ch);//慢速遥测单机4

    void Get_1553Yc_pack(ushort* Rxbuff,int Rxlen,int ch);//打包遥测
    void send_pluseStatus(bool flag_1553,int g_vi);
    void send_1553time(uint cnt);//给主界面传递时间参数显示
    void send_1553upjxjd(double value);//1553上注进度条
    void send_frame(uint cnt);//1553上注1024帧数
    void send_1553fail(QString str);//1553发送失败在主界面弹出显示
    void send_1553oupt(QString str,int color);//1553发送信息在主界面输出框显示

    void Send_MemoryData(int ch,ushort* buff,int len);//接收内存下卸数据



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
