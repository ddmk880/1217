#ifndef CARDCTRL_CAN_H
#define CARDCTRL_CAN_H
#include <QMutex>
#include <QObject>
#include <Globel_Define.h>

#include"include/zlgcan_x64/canframe.h"
#include"include/zlgcan_x64/config.h"
#include"include/zlgcan_x64/typedef.h"
#include"include/zlgcan_x64/zlgcan.h"


/***********************Class*********************
 <类    名>   CardCtrl_1553B
 <类 定 义>   1553B板卡控制接口
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>
**************************************************/
class CardCtrl_CAN : public QObject {
    Q_OBJECT
public:
    CardCtrl_CAN();
    ~CardCtrl_CAN();


    int InitCanCard();
    int SendCanCardData(ZCAN_Transmit_Data* pCanData, ULONG frame_cnt,UINT ch);//（CAN数据格式结构体，帧数，通道号）can数据帧发送
    static UINT Thread_CanRecv(void* pParam);
    inline CAN_DATA reFun_canId(UINT id_data);//解析can_id内容
    QString ChangeColor(QString str,int kind);//改变字体颜色
    QMutex mtx_canSend;//1553判断发送锁
    bool outSendMess;//输出CAN发送数据
    //bool re_while;  //can收数标志
signals:
    void add_output(QString str);//添加界面输出
    void Get_CanYc_81(uchar* Rxbuff,int Rxlen);//CAN遥测0x81
private:
    DEVICE_HANDLE m_Handle;		//Can板卡返回句柄
    CHANNEL_HANDLE m_chHandle0;//通道句柄值
    CHANNEL_HANDLE m_chHandle1;
public slots:
    void Thread_CanRecv(bool start_);







};

#endif  // CARDCTRL_CAN_H
