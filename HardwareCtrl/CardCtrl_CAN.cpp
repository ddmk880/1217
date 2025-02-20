#include "CardCtrl_CAN.h"

#include <QDebug>
#include <QThread>
#include <windows.h>
#include <QTime>

#include <map>
using namespace std;
bool re_while; //can收数标志
/********************Function*********************
 <函 数 名>   CardCtrl_CAN()
 <函数说明>    普通构造函数
 <参数说明>    无
   [返回值: 无]
 <作    者>   zm
 <时    间>   2023-04-03
**************************************************/
CardCtrl_CAN::CardCtrl_CAN() {
    m_Handle=nullptr;
    outSendMess=false;
    //InitCanCard();
    re_while=false;

}

/********************Function*********************
 <函 数 名>   ~CardCtrl_CAN()
 <函数说明>    普通析构函数
 <参数说明>    无
   [返回值: 无]
 <作    者>   zm
 <时    间>   2023-04-03
**************************************************/
CardCtrl_CAN::~CardCtrl_CAN() {
    ZCAN_CloseDevice(m_Handle);

}

/********************Function*********************
 <函 数 名>   InitCanCard
 <函数说明>    板卡资源初始化
 <参数说明>
   [返回值: 无]
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>
**************************************************/
int CardCtrl_CAN::InitCanCard() {

    // CAN板卡
    //ZCAN_USBCAN_2E_U 为设备类型, 请根据实际修改（外接CAN盒子）
    //ZCAN_PCIe9120 为设备类型, 请根据实际修改（地检CAN卡）
    DEVICE_HANDLE dhandle = ZCAN_OpenDevice(ZCAN_PCIe9120, 0, 0);//一个设备只能被打开一次
    if (INVALID_DEVICE_HANDLE == dhandle)
    {
        //std::cout << "打开设备失败" << std::endl;
        return -1;
    }
    m_Handle=dhandle;
    //CAN 设备设置波特率的 key 为 baud_rate，值 1000000 为 1000kbps, 800000 为 800kbps, 其它请查看属性表
    //若为 CANFD 设备, 设置冲裁域波特率的 key 为 canfd_abit_baud_rate，数据域波特率为canfd_dbit_baud_rate，请注意区分 CAN 和 CANFD 设备设置波特率的区别。
    if (ZCAN_SetValue (dhandle , "0/baud_rate", "500000") != STATUS_OK)//1217项目can约定500波特率
    {
        //std::cout << "设置波特率失败" << std::endl;
        return -1;
    }
    ZCAN_CHANNEL_INIT_CONFIG cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.can_type = TYPE_CAN;//CANFD 设备为 TYPE_CANFD
    cfg.can.filter = 0;
    cfg.can.mode = 0; //正常模式, 1 为只听模式
    cfg.can.acc_code = 0;
    cfg.can.acc_mask = 0xffffffff;
    //设备句柄值;通道索引号，通道0的索引号为0，通道1的索引号为1;初始化结构。
    CHANNEL_HANDLE chHandle0 = ZCAN_InitCAN(dhandle, 0, &cfg);
    CHANNEL_HANDLE chHandle1 = ZCAN_InitCAN(dhandle, 1, &cfg);
    m_chHandle0=chHandle0;
    m_chHandle1=chHandle1;
    CHANNEL_HANDLE m_ch[2]={chHandle0,chHandle1};

    for(int n=0;n<2;n++)
    {
        if (INVALID_CHANNEL_HANDLE == m_ch[n])
        {
            //std::cout << "初始化通道失败" << std::endl;
            return -1;
        }
        if (ZCAN_StartCAN(m_ch[n]) != STATUS_OK)
        {
            //std::cout << "启动通道失败" << std::endl;
            return -1;
        }
    }



    return 0;
}

////can数据发送
//int CardCtrl_CAN::SendCanCardData(BYTE *pData, ULONG data_len)
//{

//    int frame_cnt=(data_len+7)/8;//can帧总数

//    uint index=0;
//    for(int n=0;n<frame_cnt;n++)
//    {
//        ZCAN_Transmit_Data frame;
//        memset(&frame, 0, sizeof(frame));
//        //发送方式，0=正常发送，1=单次发送，2=自发自收，3=单次自发自收。
//        frame.transmit_type=2;
//        if((n+1)==frame_cnt)//尾帧
//        {
//            frame.frame.can_id = MAKE_CAN_ID(0x100, 1, 0, 0);
//            //帧 ID，32 位
//            //第 31 位(最高位)代表扩展帧标志，=0 表示标准帧，=1 代表扩展帧，宏 IS_EFF 可获取
//            //第 30 位代表远程帧标志，=0 表示数据帧，=1 表示远程帧，宏 IS_RTR 可获取该标志；
//            //第 29 位代表错误帧标准，=0 表示 CAN 帧，=1 表示错误帧，目前只能设置为 0；
//            frame.frame.can_dlc = data_len-n*8;

////            BYTE data[] = {1, 2, 3, 4, 5, 6, 7, 8};
////            memcpy(frame.frame.data, data, sizeof(data));
//            memcpy(frame.frame.data, &pData[index], frame.frame.can_dlc);
//            index+=8;
//            if (ZCAN_Transmit(m_Handle, &frame, 1) != 1)//返回报文数目
//            {
//                qDebug()<<"can_send_faild!!";
//            }
//        }
//        else
//        {
//            frame.frame.can_id = MAKE_CAN_ID(0x100, 1, 0, 0);
//            frame.frame.can_dlc = 8;
////            BYTE data[] = {1, 2, 3, 4, 5, 6, 7, 8};
////            memcpy(frame.frame.data, data, sizeof(data));
//            memcpy(frame.frame.data, &pData[index], frame.frame.can_dlc);
//            index+=8;
//            if (ZCAN_Transmit(m_Handle, &frame, 1) != 1)
//            {
//                qDebug()<<"can_send_faild!!";
//            }
//        }
//    }

//    return 0;
//}

//can数据发送
int CardCtrl_CAN::SendCanCardData(ZCAN_Transmit_Data *pCanData, ULONG frame_cnt,UINT ch)
{

    mtx_canSend.lock();

    for(uint n=0;n<frame_cnt;n++)
    {

        //输出发送内容
        if(outSendMess)
        {
            //当前时间
            QDateTime cur_time = QDateTime::currentDateTime();
            QString time=cur_time.toString("hh:mm:ss");
            QString Str1;
            Str1 =QString("%1 ch%2:").arg(time).arg(ch);

            QString Str2="发送指令 ";

            QString dataStr;
            for(int i=0;i<pCanData[n].frame.can_dlc;i++)//备注（长度固定为8时，can卡读取数据最后一帧小于8时，最后一帧不足8会读取上次缓存的数据，（可能是can卡底层问题24.2.28））
            {
                dataStr+=QString("%1 ").arg(pCanData[n].frame.data[i],2,16,QLatin1Char('0')).toUpper();
            }
            QString str=Str1+Str2+dataStr;
            QString strcolor=ChangeColor(str,0);//改变颜色
            emit add_output(strcolor);//主界面显示
        }

        //发送数据
        switch (ch) {
        case 0://通道0
            if (ZCAN_Transmit(m_chHandle0, &pCanData[n], 1) != 1)//返回报文数目
            {
                qDebug()<<"can0_send_faild!!";
                return -1;
            }
            break;
        case 1://通道1
            if (ZCAN_Transmit(m_chHandle1, &pCanData[n], 1) != 1)//返回报文数目
            {
                qDebug()<<"can1_send_faild!!";
                return -1;
            }
            break;
        case 2://通道0,通道1
            if (ZCAN_Transmit(m_chHandle0, &pCanData[n], 1) != 1)//返回报文数目
            {
                qDebug()<<"can0_send_faild!!";
                return -1;
            }
            if (ZCAN_Transmit(m_chHandle1, &pCanData[n], 1) != 1)//返回报文数目
            {
                qDebug()<<"can1_send_faild!!";
                return -1;
            }
            break;
        default:
            break;
        }

    }

    mtx_canSend.unlock();
    return 0;
}
//解析can_id内容
inline CAN_DATA CardCtrl_CAN::reFun_canId(UINT id_data)
{
    CAN_DATA data;
    memset(&data,0,sizeof (data));
    //帧序号
    data.frameN=id_data;
    //帧类型(独立，起始，中间，尾帧)
    data.comtype=id_data>>8;
    //发送节点站地址
    data.tr_addr=id_data>>10;
    //接收节点站地址
    data.re_addr=id_data>>18;

    //动态优先级标志
    data.priotity=id_data>>27;
    //发送标志
    data.send_mark=id_data>>28;

    return data;
}

//改变字体颜色
QString CardCtrl_CAN::ChangeColor(QString str,int kind)
{
    // 设置文字（样式+内容）
    //QString  str= "<font size=\"9\" color=\"red\"> 信息 </font>";
    //QString  strC= QString("<font  color=\"red\">%1</font>").arg(str);

    QString strC=str;
    switch (kind) {
    case 0://黑色
        strC= QString("<font  color=\"#000000\">%1</font>").arg(str);
        break;
    case 1://蓝色
        strC= QString("<font  color=\"#0000FF\">%1</font>").arg(str);
        break;
    case 2://紫色
        strC= QString("<font  color=\"#aa4ded\">%1</font>").arg(str);
        break;
    default:

        break;
    }

    return strC;
}

//Can收数线程
void CardCtrl_CAN::Thread_CanRecv(bool start_)
{


    //    int n=1;
    //    while (start_) {
    //        Sleep(1000);
    //        n++;
    //        qDebug()<<QString::number(n)+"....";
    //    }

    bool flag_c81=false;
    int len_c81=0;

    ZCAN_Receive_Data can_data[100];
    UINT len;
    CAN_DATA Can_IDdata;
    CHANNEL_HANDLE m_ch[2]={m_chHandle0,m_chHandle1};//通道0，1接收
    UCHAR* YC_REC_BUF = new UCHAR[1024];//遥测收数缓存区
    memset(YC_REC_BUF, 0, 1024);

    map<int,QString> mapAddr;
    mapAddr[0x10]="管控机";
    mapAddr[0x20]="算力1";
    mapAddr[0x21]="算力2";
    mapAddr[0x22]="射频前端";
    mapAddr[0x23]="L数字综合单元";
    mapAddr[0x24]="SXKu波束控制器";
    mapAddr[0xFF]="广播地址";

    int tupe_color=0;
    re_while=start_;
    while(re_while)
    {
        for(int cn=0;cn<2;cn++)
        {

            if ((len = ZCAN_GetReceiveNum(m_ch[cn], TYPE_CAN)))//获取缓冲区中CAN或CANFD报文数目。
            {
                //该函数用于接收CAN报文，建议使用ZCAN_GetReceiveNum确保缓冲区有数据再使用。
                //参数100:数组长度（本次接收的最大报文数目，实际返回值小于等于这个值）50:阻塞等待时间，单位毫秒
                memset(can_data,0,sizeof (can_data));
                len = ZCAN_Receive(m_ch[cn], can_data, 100, 50);
                //当前时间
                QDateTime cur_time = QDateTime::currentDateTime();
                QString time=cur_time.toString("hh:mm:ss");
                QString Str1;
                Str1 =QString("%1 ch%2:").arg(time).arg(cn);

                //处理一次应答的所以帧
                for(uint framecnt=0;framecnt<len;framecnt++)
                {
                    //自定义字体颜色类型
                    tupe_color=1;//蓝色
                    //周立功CAN结构体格式没有首位帧标志，在应答帧ID里
                    //dataStr+=QString("帧ID:0x%2 ").arg(can_data[framecnt].frame.can_id,2,16,QLatin1Char('0')).toUpper();
                    QString dataStr;
                    for(int i=0;i<can_data[framecnt].frame.can_dlc;i++)//备注（长度固定为8时，can卡读取数据最后一帧小于8时，最后一帧不足8会读取上次缓存的数据，（可能是can卡底层问题24.2.28））
                    {
                        dataStr+=QString("%1 ").arg(can_data[framecnt].frame.data[i],2,16,QLatin1Char('0')).toUpper();
                    }

                    //解析帧ID内的数据，存储到自定义结构体
                    Can_IDdata=reFun_canId(can_data[framecnt].frame.can_id);
                    QString Str2=mapAddr[Can_IDdata.tr_addr]+"接收指令 ";

                    if(Can_IDdata.comtype==0)//独立帧
                    {

                    }
                    else//多帧
                    {
                        if(Can_IDdata.comtype==1)//起始帧
                        {
                            //CAN遥测轮询C81,0x20高算力1，0x21高算力2
                            if(can_data[framecnt].frame.data[2]==0x81)
                            {
                                tupe_color=0;//黑色
                                Str2=mapAddr[Can_IDdata.tr_addr]+"遥测应答 ";
                                flag_c81=true;
                                len_c81=0;
                                memcpy(YC_REC_BUF+len_c81,can_data[framecnt].frame.data, 8);
                                len_c81+=8;
                            }
                        }
                        else if(Can_IDdata.comtype==3)//尾帧
                        {
                            if(flag_c81)
                            {
                                tupe_color=0;//黑色
                                Str2=mapAddr[Can_IDdata.tr_addr]+"遥测应答 ";
                                memcpy(YC_REC_BUF+len_c81,can_data[framecnt].frame.data, can_data[framecnt].frame.can_dlc);
                                len_c81+=can_data[framecnt].frame.can_dlc;
                                flag_c81=false;
                                emit Get_CanYc_81(YC_REC_BUF,len_c81);

                            }
                        }
                        else//中间帧
                        {
                            if(flag_c81)
                            {
                                tupe_color=0;//黑色
                                Str2=mapAddr[Can_IDdata.tr_addr]+"遥测应答 ";
                                memcpy(YC_REC_BUF+len_c81,can_data[framecnt].frame.data, 8);
                                len_c81+=8;
                            }
                        }
                    }


                    QString str=Str1 + Str2 + dataStr;//最终显示字符串

                    QString strcolor=ChangeColor(str,tupe_color);//改变颜色

                    emit add_output(strcolor);//主界面显示
                }

            }
        }
        //避免无数据时变成While(1),会占用大量的CPU
        Sleep(15);

    }
    delete [] YC_REC_BUF;
}







