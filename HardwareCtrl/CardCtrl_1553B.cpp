#include "CardCtrl_1553B.h"
#include<iostream>
#include<stdio.h>
#include<QtEndian>
#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <vector>
#include <QMessageBox>
#include <QFileInfo>

#define MY_CARD_TYPE	PCCD1553
#define MY_INSTANCE     1
#define MY_CHANNEL		CHANNEL_1
#define LEN_C64 64   //1553can单帧最多64字节
#define LEN_S32 32   //1553can单帧最多64字节

using namespace std;

#define MY_1553AD1    0
#define MY_1553AD2    1
#define MY_1553AD3    2
#define MY_1553AD4    3
#define MY_1553AD_ALL    4

CardCtrl_1553B*CardCtrl_1553B::sp_card1553=NULL;
//QMutex CardCtrl_1553B::mtx_1553while;
int cnt_xx=0;

int RS422_Device_num=-1;//定义
/********************Function*********************
 <函 数 名>   CardCtrl_1553B()
 <函数说明>    普通构造函数
 <参数说明>    无
   [返回值: 无]
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>
**************************************************/
CardCtrl_1553B::CardCtrl_1553B() {

    //1553AB通道选择必须赋初值
    m_sendChannal=0;
    m_sendChannal |= BC_CONTROL_CHANNELA;
    m_sendChannal |= BC_CONTROL_BUFFERA;
    //qDebug()<<"1553ch"<<m_sendChannal;
    Bus_AB=0;



    m_CycMessno_CNT=0;
    for(int i=0;i<4;i++)
    {
        Deal_vetor[i]=0;//矢量字
        msYC_buff[i]=new ushort[32*8];//8帧慢速遥测
        mPack_buff[i]=new ushort[32*4];//4帧打包遥测

        getHead[i]=false;
        curr_YCindex[i]=0;
        getHead_pack4[i]=false;
        curr_YCindex_pack4[i]=0;
    }

    Str_Subaddr[0]=9;//工作状态改变请求发送
    Str_Subaddr[1]=3;//慢速遥测请求发送
    Str_Subaddr[2]=4;//打包遥测
    Str_Subaddr[3]=0;
    Str_Subaddr[4]=0;
    Str_Subaddr[5]=6;   //快速遥测
    Str_Subaddr[6]=12;  //内存下卸
    Str_Subaddr[7]=17;  //GNSS数据
    Str_Subaddr[8]=19;  //原始观察量
    Str_Subaddr[9]=28;  //重构数据
    Str_Subaddr[10]=7;  //轨道姿态数据
    Str_Subaddr[11]=0;
    Str_Subaddr[12]=0;
    Str_Subaddr[13]=0;
    Str_Subaddr[14]=29; //远置单元测量数据
    Str_Subaddr[15]=0;

    OpenFlag_1553=false;
    Flag_1553board=false;
    Flag_CANboard=false;

    //定时器测试
    timer1553=new QTimer(this);
    connect(timer1553,SIGNAL(timeout()),this,SLOT(Write_OnTimer()));
//    timer1553->start(1000);

    //m_nTimerCounter=Get_Time();
    m_nTimerCounter=1000;
    sp_card1553=this;

    //内存下卸存储
//    QString qFileName ="./暂存数据存储.txt";
//    if(qFileName.isEmpty())return;
//    qFile.setFileName(qFileName);
    //    if(!qFile.open(QFile::WriteOnly | QFile::Text)) {
    //        qDebug()<<"xx_file error";
    //        return;
    //    }
    //    else
    //    {
    //        //qFile.write("444444");
    //    }

    //gnss定位数据容器
    v_gnss_postion.clear();
    //gnss定轨数据容器
    v_gnss_orbit.clear();
    //姿轨
    v_orb.clear();
    //
    flag_UP1553=false;
    cnt_1553send=0;

    //通道号发送标志
    m_check_chFlg[0]=true;
    m_check_chFlg[1]=false;
    m_check_chFlg[2]=false;
    m_check_chFlg[3]=false;

    UP_1553ch=0;

    xs_A=true;
    xs_B=false;

}

/********************Function*********************
 <函 数 名>   ~CardCtrl_1553B()
 <函数说明>    普通析构函数
 <参数说明>    无
   [返回值: 无]
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>
**************************************************/
CardCtrl_1553B::~CardCtrl_1553B() {
    Close1553B();
    for(int i=0;i<4;i++)
    {
        delete [] msYC_buff[i];
        delete [] mPack_buff[i];
    }
    //qFile.close();
    if(timer1553->isActive())
    {
        timer1553->stop();
    }
    timer1553->deleteLater();
}

Pluse_1553Time::Pluse_1553Time()
{
    pluse_flag=false;
    pluse_gvi=-1;
}

Pluse_1553Time::~Pluse_1553Time()
{
    pluse_flag=false;
}

unsigned int  Pluse_1553Time:: StatusThread()
{
    uchar en = 0;
    int status=0;
    int RecvTimes=0;
    while (pluse_flag)
    {
        en =0;
        status = PA_PCIe_4202_RS422_PluseStatus(pluse_gvi, PA_RS422_PULSE_OUT_CH1, &en);
        if(en == 1)
        {
            status = PA_PCIe_4202_RS422_ClearStatus(pluse_gvi, PA_RS422_PULSE_OUT_CH1);//脉冲不管用哪个通道都是0.5s
            RecvTimes++;
            //printf("RS422通道接收到脉冲次数%dn",RecvTimes);
            if(1)//0.5s
            {
//                QDateTime time=QDateTime::currentDateTime();
//                QString str=time.toString("MM-dd hh:mm:ss");
//                qDebug()<<"pluse time ="<<str<<"\n";
                emit send_pluse(RecvTimes);//通道以1553脉冲为单位，0.5s突发一次，两次为1s

            }
        }
    }
    //测试
    //    uint cnt=0;
    //    while (pluse_flag) {
    //        qDebug()<<cnt;
    //        Sleep(1000);
    //        cnt++;
    //        emit send_pluse();
    //    }

    return status;
}

void Pluse_1553Time::get_pluseStatus(bool flag_1553, int g_vi)
{
    pluse_flag=flag_1553;
    pluse_gvi=g_vi;
}



//封装1553非周期发送函数
int CardCtrl_1553B::BusTools_BC_Send(uint messageID,int addr)
{

    mtx_1553while.lock();
    int status=0;
    int ext=0;

    //首先,确保我们已经完成了以前的周期性msg。
    //double s_time = clock();
    //卡死原因，同时写入消息时会冲突，导致写入0的消息号，底层加了保护，确保不会写入冲突

    if(addr==MY_1553AD_ALL)//4台单机都发
    {
        for(int ch=0;ch<4;ch++)
        {
            if(m_check_chFlg[ch]==false)continue;//该路通道没勾选
            while (BusTools_BC_AperiodicTest(m_ch_id[ch], 1) == API_BC_APERIODIC_RUNNING)
            {
                ext++;
            }

            // Then send our aperiodic message.
            //然后发送我们的非周期消息。
            status += BusTools_BC_AperiodicRun(m_ch_id[ch], messageID, 1, 0, 20);
        }
    }
    else//只发送某一台单机
    {
        if(m_check_chFlg[addr]==false)//该路通道没勾选
        {
            mtx_1553while.unlock();
            return status;
        }
        while (BusTools_BC_AperiodicTest(m_ch_id[addr], 1) == API_BC_APERIODIC_RUNNING)
        {
            ext++;
        }

        // Then send our aperiodic message.
        //然后发送我们的非周期消息。
        status += BusTools_BC_AperiodicRun(m_ch_id[addr], messageID, 1, 0, 20);
    }


    mtx_1553while.unlock();
    return status;

}
//封装1553BC写消息函数
int CardCtrl_1553B::BusTools_BC_Write(int addr, uint messno, API_BC_MBUF *api_message )
{
    int status=0;
    if(addr==MY_1553AD_ALL)//4代表4路都发生
    {
        for(int ch=0;ch<4;ch++)
        {
            status += BusTools_BC_MessageWrite(m_ch_id[ch], messno, api_message);
        }
    }
    else//某一路发送
    {
        status += BusTools_BC_MessageWrite(m_ch_id[addr], messno, api_message);
    }

    return status;
}


//时间码消息、系统同步消息、长抱环测试消息、在线自测试消息。
void CardCtrl_1553B::WriteOnTimerMessage(uint pluse_cnt)
{


    if(OpenFlag_1553)//1553板卡是否初始化成功
    {
        for(int i=0;i<4;i++)
        {
            if(Deal_vetor[i]!=0)//矢量字0.5s。。。
            {
                BC_Dealvetor(Deal_vetor[i],i);
                Deal_vetor[i]=0;
            }
        }
        if(pluse_cnt%2==0)//1s。。。
        {
            if(Flag_CANboard)
            {
                //printf("CANBoard... \n");
                if(!Flag_1553board)m_nTimerCounter++;

                emit send_1553time(m_nTimerCounter);//传递主界面时间
            }

            if(Flag_1553board)//是否开启广播消息
            {

                //printf("1553Board... \n");
                m_nTimerCounter++;

                emit send_1553time(m_nTimerCounter);//传递主界面时间

                Write_RT_Data(m_nTimerCounter);//RT广播

                StartTimeBroadMessage(m_nTimerCounter);//星时和能源状态广播（消息号50，1帧）

                if(m_nTimerCounter % 2==0)
                    OrbitalMessage(m_nTimerCounter);//轨道姿态数据（公共发送，消息号）

                //            if(m_nTimerCounter % 256==0)
                //                LongringMessage();//长抱环消息,远端1字取反应答（消息号54，1帧）

                //            if(m_nTimerCounter % 3600==0)
                //                SystemStepMessage();//系统同步消息（消息号56，1帧）

                //            if(m_nTimerCounter % 65536==0)
                //                OnlineMessage();//自测试消息（中断中取应答，但是与rt19的矢量字冲突）（消息号58，1帧）
            }


        }
        if(flag_UP1553)//1553文件上注0.5s
        {

            if(cnt_1553send==0)
            {
                tmp_1553files.open(QIODevice::ReadOnly);
            }
            int farmecnt = (tmp_1553files.size() + 1024 - 1) / 1024;
            uchar tmbuff[1024]={0};
            tmp_1553files.read((char*)tmbuff,1024);
            OnceSend_Data((uchar*)tmbuff ,1024,19,28,UP_1553ch);//接口可以实现发送
            emit send_1553upjxjd((cnt_1553send+1) * 10000.00 / farmecnt);
            emit send_frame(cnt_1553send++ +1);
            if(cnt_1553send==farmecnt)
            {
                flag_UP1553=false;
                cnt_1553send=0;
                tmp_1553files.close();
            }
        }
    }

}

//定时器测试函数
void CardCtrl_1553B::Write_OnTimer()
{
    ushort buff[256]={0};
    for(uint i=0;i<sizeof (buff)/2;i++)buff[i]=i+m_nTimerCounter;
    //emit Get_1553Yc1(buff,sizeof (buff)/2,MY_1553AD1);
    emit sp_card1553->Send_MemoryData(0,buff,32);


}
//udp改变星时
void CardCtrl_1553B::udp_changeTime(uint stime)
{
    m_nTimerCounter=stime;
}


//星时和能源状态广播(A/B轮询发送)
int CardCtrl_1553B::StartTimeBroadMessage(int cnt)
{
    int status=0;

    API_BC_MBUF bc_msg;

    //周期消息个数起为非周期消息起点(前面非周期消息)
    int tmpmess=50;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
    memset(&bc_msg, 0, sizeof(API_BC_MBUF));
    bc_msg.messno   = tmpmess;              // Message number
    bc_msg.control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
    if((cnt%2)==0)
    {
        if(xs_A==false)return 0;//暂时关闭busA的发送
        bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
        bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    }

    else
    {
        if(xs_B==false)return 0;//暂时关闭busB的发送
        bc_msg.control |= BC_CONTROL_CHANNELB;
        bc_msg.control |= BC_CONTROL_BUFFERB;
    }
    bc_msg.control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
    bc_msg.control |= BC_CONTROL_INTERRUPT;	//中断函数控制字
    bc_msg.messno_next			= 0xFFFF;	// Next message number


    bc_msg.mess_command1.rtaddr	= 31;		// Command word 1, RT address
    bc_msg.mess_command1.subaddr = 13;		// Command word 1, Subaddress
    bc_msg.mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    bc_msg.mess_command1.wcount = 5;         //一帧发送的数据长度，0默认32字
    bc_msg.gap_time				= 1000;		// Intermessage gap time in microseconds

    bc_msg.mframeno				= 0;
    bc_msg.mframeen				= 1;
    bc_msg.mframetime			= 1000;

    // Fill data buffer
    LL time_ms=m_nTimerCounter*10000;
    Star_Power_broad str;
    memset(&str,0,sizeof (str));
    str.checktime_mode=0x5555;//GNSS校时
    str.time_code[0]=time_ms>>32;
    str.time_code[1]=time_ms>>16;
    str.time_code[2]=time_ms;
    str.status=0x1111;//能源良好
    memcpy(bc_msg.data,&str,sizeof (str));

    /*后期可删除*/
    //        bc_msg.data[0][0] = 0x5555;//GNSS校时
    //        //bc_msg.data[0][0] = 0xAAAA;//地面校时
    //        bc_msg.data[0][1]=time_ms>>32;
    //        bc_msg.data[0][2]=time_ms>>16;
    //        bc_msg.data[0][3]=time_ms;
    //        bc_msg.data[0][4]=0x1111;//能源良好


    // Write the message to board memory
    status += BusTools_BC_Write(MY_1553AD_ALL,tmpmess, &bc_msg);//自定义封装函数


    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(tmpmess,MY_1553AD_ALL);


    return status;
}

//系统同步
int CardCtrl_1553B::SystemStepMessage()
{
    int status=0;

    API_BC_MBUF bc_msg;

    //周期消息个数起为非周期消息起点(前面非周期消息)
    int tmpmess=56;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
    memset(&bc_msg, 0, sizeof(API_BC_MBUF));
    bc_msg.messno   = tmpmess;              // Message number
    bc_msg.control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
    //    bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    bc_msg.control |= m_sendChannal;
    bc_msg.control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
    bc_msg.control |= BC_CONTROL_INTERRUPT;	//中断函数控制字
    bc_msg.messno_next			= 0xFFFF;	// Next message number


    bc_msg.mess_command1.rtaddr	= 31;		// Command word 1, RT address
    bc_msg.mess_command1.subaddr = 14;		// Command word 1, Subaddress
    bc_msg.mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    bc_msg.mess_command1.wcount = 1;         //一帧发送的数据长度，0默认32字
    bc_msg.gap_time				= 10000;	// （系统同步10ms内不安排总线通信）Intermessage gap time in microseconds

    bc_msg.mframeno				= 0;
    bc_msg.mframeen				= 1;
    bc_msg.mframetime			= 1000;

    // Fill data buffer
    bc_msg.data[0][0] = 0x146F;//系统同步数据字

    // Write the message to board memory

    status += BusTools_BC_Write(MY_1553AD_ALL,tmpmess, &bc_msg);//自定义封装函数

    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(tmpmess,MY_1553AD_ALL);

    emit send_1553oupt("启动系统同步",2);


    return status;
}

//长抱环测试
int CardCtrl_1553B::LongringMessage()
{

    int status=0;
    int cyc=1;
    if(Bus_AB==2)cyc=2;//AB同时发，1553B不支持一条消息同时AB发送
    API_BC_MBUF bc_msg;
    for(int ch=0;ch<cyc;ch++)
    {

        memset(&bc_msg, 0, sizeof(API_BC_MBUF));

        //周期消息个数起为非周期消息起点(前面非周期消息)
        int tmpmess=54+ch*2;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
        bc_msg.messno   = tmpmess;              // Message number
        bc_msg.control = BC_CONTROL_MESSAGE;	// This is a standard BC message.

        if(ch==0)
        {
            bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
            bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
        }
        else
        {
            bc_msg.control |= BC_CONTROL_CHANNELB;
            bc_msg.control |= BC_CONTROL_BUFFERB;	// Only using one buffer, buffer B.
        }

        if(Bus_AB==1)//单选通道B
        {
            bc_msg.control=0;
            bc_msg.control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
            bc_msg.control |= BC_CONTROL_CHANNELB;	// Send message on bus A (primary).
            bc_msg.control |= BC_CONTROL_BUFFERB;	// Only using one buffer, buffer A.
        }

        bc_msg.control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
        bc_msg.messno_next			= tmpmess+1;	// Next message number


        bc_msg.mess_command1.rtaddr	= 19;		// Command word 1, RT address
        bc_msg.mess_command1.subaddr = 15;		// Command word 1, Subaddress
        bc_msg.mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
        bc_msg.mess_command1.wcount = 1;         //一帧发送的数据长度，0默认32字
        bc_msg.gap_time				= 1000;		// Intermessage gap time in microseconds

        bc_msg.mframeno				= 0;
        bc_msg.mframeen				= 1;
        bc_msg.mframetime			= 1000;

        // Fill data buffer
        bc_msg.data[0][0] = 0xAABB;//自定义字(取反5544)
        //bc_msg.data[1][0] = 0x11FF;//自定义字(取反EE00),第二个是不使用的

        QString tmps;
        if(Bus_AB==0)//通道A
        {
            tmps=QString("A通道长抱环发送:0x%1(取反0x5544)").arg(bc_msg.data[0][0],4,16,QLatin1Char('0')).toUpper();
            emit sp_card1553->send_1553oupt(tmps,2);
        }
        else if(Bus_AB==1)//通道B
        {
            bc_msg.data[0][0] = 0x11FF;//自定义字(取反EE00)
            tmps=QString("B通道长抱环发送:0x%1(取反0xEE00)").arg(bc_msg.data[0][0],4,16,QLatin1Char('0')).toUpper();
            emit sp_card1553->send_1553oupt(tmps,2);
        }
        else{
        }


        // Write the message to board memory
        status += BusTools_BC_Write(MY_1553AD_ALL,tmpmess, &bc_msg);//自定义封装函数

        //长抱环测试返回值接收
        bc_msg.messno   = tmpmess+1;            // Message number
        bc_msg.control |= BC_CONTROL_INTERRUPT;	//中断函数控制字
        bc_msg.messno_next			= 0xffff;	//Next message number
        bc_msg.mess_command1.tran_rec = 1;

        status += BusTools_BC_Write(MY_1553AD_ALL,tmpmess+1, &bc_msg);//自定义封装函数

        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(tmpmess,MY_1553AD_ALL);

    }

    if(Bus_AB==2)//通道AB
    {
        QString tmps=QString("A_B通道长抱环发送:0x%1(取反0x5544)").arg(bc_msg.data[0][0],4,16,QLatin1Char('0')).toUpper();
        emit sp_card1553->send_1553oupt(tmps,2);
    }
    return status;
}

//在线自测试消息
int CardCtrl_1553B::OnlineMessage()
{

    int status=0;

    API_BC_MBUF bc_msg[2];

    //周期消息个数起为非周期消息起点(前面非周期消息)
    int tmpmess=58;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
    //启动自测试
    memset(&bc_msg[0], 0, sizeof(API_BC_MBUF));
    bc_msg[0].messno   = tmpmess;              // Message number
    bc_msg[0].control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
    //    bc_msg[0].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg[0].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    bc_msg[0].control |= m_sendChannal;
    bc_msg[0].control |= BC_CONTROL_MFRAME_BEG;	// End of minor frame.
    bc_msg[0].messno_next			= tmpmess+1;	// Next message number


    bc_msg[0].mess_command1.rtaddr	= 19;		// Command word 1, RT address
    bc_msg[0].mess_command1.subaddr = 0;		// Command word 1, Subaddress
    bc_msg[0].mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    bc_msg[0].mess_command1.wcount = 3;         //矢量字3，启动自测试
    bc_msg[0].gap_time				= 1000;		// Intermessage gap time in microseconds

    bc_msg[0].mframeno				= 0;
    bc_msg[0].mframeen				= 1;
    bc_msg[0].mframetime			= 1000;

    // Fill data buffer

    // Write the message to board memory

    status += BusTools_BC_Write(MY_1553AD_ALL,tmpmess,&bc_msg[0]);//自定义封装函数

    //发送自测试字
    memset(&bc_msg[1], 0, sizeof(API_BC_MBUF));
    bc_msg[1].messno   = tmpmess+1;              // Message number
    bc_msg[1].control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
    //    bc_msg[1].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg[1].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    bc_msg[1].control |= m_sendChannal;
    bc_msg[1].control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
    bc_msg[1].control |= BC_CONTROL_INTERRUPT;	//中断函数控制字（终端中取回返回值，但是rt地址是否是19）
    bc_msg[1].messno_next			= 0xffff;	// Next message number


    bc_msg[1].mess_command1.rtaddr	= 19;		// Command word 1, RT address
    bc_msg[1].mess_command1.subaddr = 0;		// Command word 1, Subaddress
    bc_msg[1].mess_command1.tran_rec = 1;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    bc_msg[1].mess_command1.wcount = 19;         //矢量字19，发送自测试字
    bc_msg[1].gap_time				= 1000;		// Intermessage gap time in microseconds

    bc_msg[1].mframeno				= 0;
    bc_msg[1].mframeen				= 1;
    bc_msg[1].mframetime			= 1000;
    // Write the message to board memory
    status += BusTools_BC_Write(MY_1553AD_ALL,tmpmess+1,&bc_msg[1]);//自定义封装函数

    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(tmpmess,MY_1553AD_ALL);//(结果通过遥测下传？中断应答)

    emit send_1553oupt("启动在线自测试",2);

    return status;
}





//轨道姿态数据广播
int CardCtrl_1553B::OrbitalMessage(int cnt)
{

    Orbitalstance_Data strorbital[4];
    int str_Len=sizeof (Orbitalstance_Data);

    bool a=(uint)cnt < v_orb[v_orb.size()-1].thistime+1;    //utc时间<表格最后一秒
    bool b=(uint)cnt > v_orb[0].thistime-1;                 //utc时间>表格第一秒

    for(int i=0;i<4;i++)
    {
        memset(&strorbital[i],0,str_Len);
        strorbital[i].pack_mark=0x3012;
        strorbital[i].pack_sequence=qToBigEndian((ushort)0xC000);
        strorbital[i].pack_len=qToBigEndian((ushort)0x00B9);

        strorbital[i].fun_mark=0xBBBB;
        strorbital[i].satsllite_mark=1;
        strorbital[i].softstart_I=0;
        strorbital[i].softstart_II=0;
        strorbital[i].softstart_III=0;
        strorbital[i].softstart_IV=0;
        strorbital[i].thistime[0]=9;


        strorbital[i].rolling_angle=qToBigEndian((uint)10);
        strorbital[i].pitch_angle=qToBigEndian((uint)11);
        strorbital[i].yawing_angle=qToBigEndian((uint)12);
        strorbital[i].rolling_anglespeed=qToBigEndian((uint)13);
        strorbital[i].yawing_anglespeed=qToBigEndian((uint)14);
        strorbital[i].sun_x=qToBigEndian((uint)15);
        strorbital[i].sun_y=qToBigEndian((uint)16);
        strorbital[i].sun_z=qToBigEndian((uint)17);

//        strorbital[i].sorfttime_I[0]=21;
//        strorbital[i].sorft_Iside_x=qToBigEndian((uint)22);
//        strorbital[i].sorft_Iside_y=qToBigEndian((uint)23);
//        strorbital[i].sorft_Iside_z=qToBigEndian((uint)24);
//        strorbital[i].sorft_Ispeed_x=qToBigEndian((uint)25);
//        strorbital[i].sorft_Ispeed_y=qToBigEndian((uint)26);
//        strorbital[i].sorft_Ispeed_z=qToBigEndian((uint)27);

//        strorbital[i].sorfttime_II[0]=21;
//        strorbital[i].sorft_IIside_x=qToBigEndian((uint)22);
//        strorbital[i].sorft_IIside_y=qToBigEndian((uint)23);
//        strorbital[i].sorft_IIside_z=qToBigEndian((uint)24);
//        strorbital[i].sorft_IIspeed_x=qToBigEndian((uint)25);
//        strorbital[i].sorft_IIspeed_y=qToBigEndian((uint)26);
//        strorbital[i].sorft_IIspeed_z=qToBigEndian((uint)27);

//        strorbital[i].sorfttime_III[0]=21;
//        strorbital[i].sorft_IIIside_x=qToBigEndian((uint)22);
//        strorbital[i].sorft_IIIside_y=qToBigEndian((uint)23);
//        strorbital[i].sorft_IIIside_z=qToBigEndian((uint)24);
//        strorbital[i].sorft_IIIspeed_x=qToBigEndian((uint)25);
//        strorbital[i].sorft_IIIspeed_y=qToBigEndian((uint)26);
//        strorbital[i].sorft_IIIspeed_z=qToBigEndian((uint)27);

//        strorbital[i].sorfttime_IV[0]=21;
//        strorbital[i].sorft_IVside_x=qToBigEndian((uint)22);
//        strorbital[i].sorft_IVside_y=qToBigEndian((uint)23);
//        strorbital[i].sorft_IVside_z=qToBigEndian((uint)24);
//        strorbital[i].sorft_IVspeed_x=qToBigEndian((uint)25);
//        strorbital[i].sorft_IVspeed_y=qToBigEndian((uint)26);
//        strorbital[i].sorft_IVspeed_z=qToBigEndian((uint)27);


        //是否读取表格
        if((v_orb.size()!=0) && a && b)
        {
            //int tmp_cnt=cnt%v_orb.size();
            int tmp_cnt=cnt-v_orb[0].thistime;

            //qDebug()<<tmp_cnt<<"zz";
            unsigned long long tm=v_orb[tmp_cnt].thistime;
            tm=tm*10000;//0.1ms
            tm=qToBigEndian(tm)>>16;
            memcpy(&strorbital[i].thistime[0],&tm,6);

            strorbital[i].rolling_angle=qToBigEndian(v_orb[tmp_cnt].rolling_angle[i]);
            strorbital[i].pitch_angle=qToBigEndian(v_orb[tmp_cnt].pitch_angle[i]);
            strorbital[i].yawing_angle=qToBigEndian(v_orb[tmp_cnt].yawing_angle[i]);

        }
        //和校验
        uchar* checkbuff=new uchar[str_Len];
        memcpy(checkbuff,(uchar*)&strorbital[i],str_Len);
        ushort crc=0;
        for(int n=0;n<str_Len-2;n++)
        {
            crc+=checkbuff[n];
        }
        strorbital[i].add_crc=qToBigEndian(crc);
        delete [] checkbuff;


        //发送
        uchar *buff=new uchar[256];
        memset(buff,0x2a,256);
        memcpy(buff,(uchar*)&strorbital[i],sizeof (Orbitalstance_Data));
        OnceSend_Data(buff,256,31,7,i);
        delete [] buff;
    }

    return 0;
}



//GNSS时间码
int CardCtrl_1553B::GNSS_timecodeMessage()
{
    //获取系统当前时间
    time_t now = time(NULL);
    struct tm* t;
    t = localtime(&now);
    //cout << asctime(t)<<endl;//将结构体中的信息转换成真实世界的时间，以结构体显示
    t->tm_year += 0;//会自己减掉1900
    t->tm_mon += 0;
    t->tm_mday += 0;//当前天数不用加1
    time_t now_s = mktime(t);

    UINT times=now_s;

    //    API_BC_MBUF bc_msg;

    //    //周期消息个数起为非周期消息起点(前面非周期消息)
    //    int tmpmess=52;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
    //    memset(&bc_msg, 0, sizeof(API_BC_MBUF));
    //    bc_msg.messno   = tmpmess;              // Message number
    //    bc_msg.control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
    //    bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    //    bc_msg.control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
    //    bc_msg.control |= BC_CONTROL_INTERRUPT;	//中断函数控制字
    //    bc_msg.messno_next			= 0xFFFF;	// Next message number


    //    bc_msg.mess_command1.rtaddr	= 31;		// Command word 1, RT address
    //    bc_msg.mess_command1.subaddr = 16;		// Command word 1, Subaddress
    //    bc_msg.mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    //    bc_msg.mess_command1.wcount = 3;         //一帧发送的数据长度，0默认32字
    //    bc_msg.gap_time				= 1000;		// Intermessage gap time in microseconds

    //    bc_msg.mframeno				= 0;
    //    bc_msg.mframeen				= 1;
    //    bc_msg.mframetime			= 1000;

    // Fill data buffer

    //    times=m_nTimerCounter;//使用设置的时间
    //    ushort time1=times>>16;
    //    ushort time2=times;

    //    bc_msg.data[0][0] = 0;//
    //    bc_msg.data[0][1] = time1 ;//
    //    bc_msg.data[0][2] = time2 ;//

    //    // Write the message to board memory
    //      status += BusTools_BC_Write(0,tmpmess,&bc_msg);//自定义封装函数

    //    //封装发送1553非周期发送函数
    //    status +=BusTools_BC_Send(tmpmess);

    times=m_nTimerCounter;//使用设置的时间
    ushort time1=times>>16;
    ushort time2=times;

    GNSS_Time str;
    memset(&str,0,sizeof (str));
    str.code1=0xAAAA;
    str.code2=time1;
    str.code3=time2;


    API_RT_MBUF_WRITE mbuf;
    mbuf.enable=0;
    mbuf.error_inj_id=0;

    memcpy(mbuf.mess_data,&str,sizeof(str));

    //    ushort tmptime[3]={0};
    //    tmptime[0] = 0;
    //    tmptime[1] = time1 ;
    //    tmptime[2] = time2 ;

    //    ushort* buff=new ushort[sizeof(tmptime)/2+1];
    //    memcpy(buff,(uchar*)&tmptime,sizeof(tmptime));

    //    API_RT_MBUF_WRITE mbuf;
    //    mbuf.enable=0;
    //    mbuf.error_inj_id=0;
    //    for(int i=0;i<3;i++)
    //    {
    //        mbuf.mess_data[i]=qToBigEndian(buff[i]);
    //    }
    //    delete [] buff;
    //    memcpy(mbuf.mess_data,&tmptime,sizeof(tmptime));

    int status=0;
    for(int ch=0;ch<4;ch++)
    {
        status+=BusTools_RT_MessageWrite(m_ch_id[ch],7,16,1,0,&mbuf);
    }

    if(status!=API_SUCCESS) return status;

    return status;
}



//GNSS定位数据
int CardCtrl_1553B::GNSS_postionMessage(int cnt)
{
    GNSS_Positioning str_postion[4];

    bool a=(uint)cnt<v_gnss_postion[v_gnss_postion.size()-1].time_s+1;    //utc时间<表格最后一秒
    bool b=(uint)cnt>v_gnss_postion[0].time_s-1;                 //utc时间>表格第一秒

    ushort* buff=new ushort[sizeof(GNSS_Positioning)/2+1];
    for(int i=0;i<4;i++)
    {
        memset(&str_postion[i],0,sizeof(GNSS_Positioning));

        str_postion[i].pack_mark=0x7206;
        str_postion[i].pack_sequence=qToBigEndian((short)0xC000);
        str_postion[i].pack_len=qToBigEndian((short)0x0039);
        str_postion[i].posit_mark=0x6F;
        str_postion[i].use_startsum=0;

//        str_postion[i].time_s=qToBigEndian((uint)5);
//        str_postion[i].position_x=qToBigEndian((int)6);
//        str_postion[i].position_y=qToBigEndian((int)7);
//        str_postion[i].position_z=qToBigEndian((int)8);
//        str_postion[i].speed_x=qToBigEndian((int)9);
//        str_postion[i].speed_y=qToBigEndian((int)10);
//        str_postion[i].speed_z=qToBigEndian((int)11);

//        str_postion[i].track_mark=0xFF;

//        str_postion[i].position15_x=qToBigEndian((int)13);
//        str_postion[i].position15_y=qToBigEndian((int)14);
//        str_postion[i].position15_z=qToBigEndian((int)15);
//        str_postion[i].speed15_x=qToBigEndian((int)16);
//        str_postion[i].speed15_y=qToBigEndian((int)17);
//        str_postion[i].speed15_z=qToBigEndian((int)18);

        //是否读取表格
        if((v_gnss_postion.size()!=0) && a && b)
        {
            //int tmp_cnt=cnt%v_gnss_postion.size();
            uint tmp_cnt=cnt-v_gnss_postion[0].time_s;

            //qDebug()<<tmp_cnt<<"ww";
            str_postion[i].time_s=qToBigEndian(v_gnss_postion[tmp_cnt].time_s);
            str_postion[i].position_x=qToBigEndian(v_gnss_postion[tmp_cnt].position_x[i]);
            str_postion[i].position_y=qToBigEndian(v_gnss_postion[tmp_cnt].position_y[i]);
            str_postion[i].position_z=qToBigEndian(v_gnss_postion[tmp_cnt].position_z[i]);
            str_postion[i].speed_x=qToBigEndian(v_gnss_postion[tmp_cnt].speed_x[i]);
            str_postion[i].speed_y=qToBigEndian(v_gnss_postion[tmp_cnt].speed_y[i]);
            str_postion[i].speed_z=qToBigEndian(v_gnss_postion[tmp_cnt].speed_z[i]);

            str_postion[i].track_mark=0xFF;

            if((tmp_cnt+900)<v_gnss_postion.size()){
                str_postion[i].position15_x=qToBigEndian(v_gnss_postion[tmp_cnt+900].position_x[i]);
                str_postion[i].position15_y=qToBigEndian(v_gnss_postion[tmp_cnt+900].position_y[i]);
                str_postion[i].position15_z=qToBigEndian(v_gnss_postion[tmp_cnt+900].position_z[i]);
                str_postion[i].speed15_x=qToBigEndian(v_gnss_postion[tmp_cnt+900].speed_x[i]);
                str_postion[i].speed15_y=qToBigEndian(v_gnss_postion[tmp_cnt+900].speed_y[i]);
                str_postion[i].speed15_z=qToBigEndian(v_gnss_postion[tmp_cnt+900].speed_z[i]);

            }

        }

        //OnceSend_Data((uchar*)&str_postion,sizeof (GNSS_Positioning),31,17);

        memcpy(buff,(uchar*)&str_postion[i],sizeof(GNSS_Positioning));
        API_RT_MBUF_WRITE mbuf;
        mbuf.enable=0;
        mbuf.error_inj_id=0;
        for(int i=0;i<32;i++)
        {
            mbuf.mess_data[i]=qToBigEndian(buff[i]);
        }
        //memcpy(mbuf.mess_data,&str_postion,sizeof(str_postion));'
        int status=0;
        status+=BusTools_RT_MessageWrite(m_ch_id[i],7,17,1,0,&mbuf);
        if(status!=API_SUCCESS) return status;


    }

    delete [] buff;
    return 0;
}

//GNSS定轨数据
int CardCtrl_1553B::GNSS_trackMessage(int cnt)
{

    GNSS_Track str_track[4];

    bool a=(uint)cnt<v_gnss_orbit[v_gnss_orbit.size()-1].time_s+1;    //utc时间<表格最后一秒
    bool b=(uint)cnt>v_gnss_orbit[0].time_s-1;                 //utc时间>表格第一秒

    ushort* buff=new ushort[sizeof(GNSS_Track)/2+1];
    for(int i=0;i<4;i++)
    {
        memset(&str_track[i],0,sizeof(GNSS_Track));

        str_track[i].pack_mark=0x7306;
        str_track[i].pack_sequence=qToBigEndian((short)0xC000);
        str_track[i].pack_len=qToBigEndian((short)0x0039);
        str_track[i].track_mark=0;
        str_track[i].use_startsum=0;
//        str_track[i].time_s=qToBigEndian((uint)5);
//        str_track[i].track_halflenth=qToBigEndian((uint)0xAAAAAAAA);
//        str_track[i].track_offcenter=qToBigEndian((uint)0xAAAAAAAA);
//        str_track[i].track_angle=qToBigEndian((uint)0xAAAAAAAA);
//        str_track[i].up_point=qToBigEndian((uint)0xAAAAAAAA);
//        str_track[i].near_angle=qToBigEndian((uint)0xAAAAAAAA);
//        str_track[i].flat_angle=qToBigEndian((uint)0xAAAAAAAA);
        str_track[i].outpush_time=qToBigEndian((ushort)0);



        str_track[i].track_15halflenth=qToBigEndian((uint)0xAAAAAAAA);
        str_track[i].track_15offcenter=qToBigEndian((uint)0xAAAAAAAA);
        str_track[i].track_15angle=qToBigEndian((uint)0xAAAAAAAA);
        str_track[i].up_15point=qToBigEndian((uint)0xAAAAAAAA);
        str_track[i].near_15angle=qToBigEndian((uint)0xAAAAAAAA);
        str_track[i].flat_15angle=qToBigEndian((uint)0xAAAAAAAA);

        //是否读取表格
        if((v_gnss_orbit.size()!=0) && a && b)
        {
            //int tmp_cnt=cnt%v_gnss_orbit.size();
            int tmp_cnt=cnt-v_gnss_orbit[0].time_s;
            //qDebug()<<tmp_cnt<<"gg";

            str_track[i].time_s=qToBigEndian(v_gnss_orbit[tmp_cnt].time_s);

            str_track[i].track_halflenth=qToBigEndian(v_gnss_orbit[tmp_cnt].track_halflenth[i]);
            str_track[i].track_offcenter=qToBigEndian(v_gnss_orbit[tmp_cnt].track_offcenter[i]);
            str_track[i].track_angle=qToBigEndian(v_gnss_orbit[tmp_cnt].track_angle[i]);
            str_track[i].up_point=qToBigEndian(v_gnss_orbit[tmp_cnt].up_point[i]);
            str_track[i].near_angle=qToBigEndian(v_gnss_orbit[tmp_cnt].near_angle[i]);
            str_track[i].flat_angle=qToBigEndian(v_gnss_orbit[tmp_cnt].flat_angle[i]);
        }

        memcpy(buff,(uchar*)&str_track[i],sizeof(GNSS_Track));
        API_RT_MBUF_WRITE mbuf;
        mbuf.enable=0;
        mbuf.error_inj_id=0;
        for(int i=0;i<32;i++)
        {
            mbuf.mess_data[i]=qToBigEndian(buff[i]);
        }
        //memcpy(mbuf.mess_data,buff,sizeof(str_track));
        int status=0;

        status+=BusTools_RT_MessageWrite(m_ch_id[i],7,18,1,0,&mbuf);
        //OnceSend_Data((uchar*)&str_track,sizeof (GNSS_Track),31,18);
        if(status!=API_SUCCESS) return status;
    }


    delete [] buff;
    return 0;
}

//1553上注接口
void CardCtrl_1553B::Send_Updata_1553(QString strpth, vector<int> frame, ushort rt, ushort sub,int ch)
{
    if(flag_UP1553==true)
    {
        qDebug()<<"wait 1553UP...";
        return;
    }

    // 打开上注文件
    if (strpth.isEmpty()) {
        return ;
    }
    QFile* binFile = new QFile("");
    binFile->setFileName(strpth);
    if (binFile->open(QFile::ReadOnly)) {
    }
    else {
        flag_UP1553=false;
        return ;
    }

    //创建1553上注格式文件
    QFileInfo fileinfo(strpth);    //读取文件

    QString last_=fileinfo.suffix();
    QString path_1553=fileinfo.filePath();
    QString end_Path="";
    path_1553 = path_1553.left(path_1553.indexOf("."));
    end_Path=path_1553+"_1553UP."+last_;
    if(frame.size()!=0)end_Path=path_1553+"_1553UP补包"+QString::number(frame.size())+"."+last_;//补包上注文件
    // 创建暂存上注文件
    //    QFile tmp_1553files;
    tmp_1553files.setFileName(end_Path);
    QFileInfo fileInfo(end_Path);
    if (fileInfo.isFile()) {
        tmp_1553files.remove();
        // qDebug()<<"文件存在";
    }

    if (!tmp_1553files.open(QIODevice::ReadWrite)) {
        qDebug() << "1553files_create_fail";
        //return;
    }

    if(frame.size()==0)//没有选择帧号，全上
    {
        // 发送数据
        str_1553up str_1553up;

        char File_buff[922] = {0};  // 每次文件922字节
        int fLen = binFile->size();
        int farmecnt = (fLen + 922 - 1) / 922;

        //uint cnt_frame=1;//帧从第一帧开始
        for (int n = 0; n < farmecnt; n++)
        {
            memset(&str_1553up, 0, sizeof(str_1553up));
            memset(File_buff, 0, sizeof(File_buff));

            binFile->read((char*)File_buff, sizeof(File_buff));  // 超过长度不读取，是默认值

            //包标志0x1731
            str_1553up.pack_mark=qToBigEndian((ushort)0x1731);
            //包顺序控制
            str_1553up.pack_number=qToBigEndian((ushort)n);
            //包长
            str_1553up.pack_len=qToBigEndian((ushort)0x039D);//？最后一帧不足914，暂时按914
            //功能识别0x0009
            str_1553up.fun_mode=qToBigEndian((ushort)0x0009);

            //数据
            memcpy(str_1553up.data922,File_buff,sizeof (File_buff));//922封装好的文件

            //异或和和校验

            ushort* checkbuff=new ushort[932/2];
            memcpy(checkbuff,(uchar*)&str_1553up,932);

            ushort crc=0;
            for(uint n=3;n<(932-2)/2;n++)
            {
                crc=crc^checkbuff[n];
            }
            //str_1553up.addcrc=qToBigEndian(crc);
            str_1553up.addcrc=crc;
            delete [] checkbuff;


            //        for(int j=0;j<4;j++)
            //        {
            //            OnceSend_Data((uchar*)&str_1553up + j*256,256,rt,sub);//接口可以实现发送
            //            USleep(60);
            //        }
            //        emit send_1553upjxjd((n + 1) * 10000.00 / farmecnt);
            //        emit send_frame(cnt_frame++);

            tmp_1553files.write((char*)&str_1553up,sizeof (str_1553up));

        }

    }
    else//选择了帧号
    {

        // 发送数据
        str_1553up str_1553up;

        char File_buff[922] = {0};  // 每次文件922字节

        int farmecnt = frame.size();
        for (int n = 0; n < farmecnt; n++)
        {
            //qDebug()<<frame.at(n);

            memset(&str_1553up, 0, sizeof(str_1553up));
            memset(File_buff, 0, sizeof(File_buff));

            binFile->seek(frame.at(n)*922);
            binFile->read((char*)File_buff, sizeof(File_buff));  // 超过长度不读取，是默认值

            //包标志0x1731
            str_1553up.pack_mark=qToBigEndian((ushort)0x1731);
            //包顺序控制
            str_1553up.pack_number=qToBigEndian((ushort)frame.at(n));
            //包长
            str_1553up.pack_len=qToBigEndian((ushort)0x039D);//？最后一帧不足914，暂时按914
            //功能识别0x0009
            str_1553up.fun_mode=qToBigEndian((ushort)0x0009);

            //数据
            memcpy(str_1553up.data922,File_buff,sizeof (File_buff));//922封装好的文件

            //异或和和校验

            ushort* checkbuff=new ushort[932/2];
            memcpy(checkbuff,(uchar*)&str_1553up,932);

            ushort crc=0;
            for(uint n=3;n<(932-2)/2;n++)
            {
                crc=crc^checkbuff[n];
            }
            //str_1553up.addcrc=qToBigEndian(crc);
            str_1553up.addcrc=crc;
            delete [] checkbuff;
            tmp_1553files.write((char*)&str_1553up,sizeof (str_1553up));
        }
    }

    tmp_1553files.close();
    cnt_1553send=0;
    UP_1553ch=ch;
    flag_UP1553=true;
    // 发送完成
    binFile->close();

    //    通道测试
    //    uchar databuff[256]={0};
    //    for(int k=0;k<256;k++)
    //    {
    //        databuff[k]=k+1;
    //    }
    //    //1553板块发送
    //    for(int i=0;i<100;i++)
    //    {
    //        Card_1553Can->OnceSend_Data(databuff,256,7,7);//接口可以实现发送
    //        Sleep(1);
    //    }
}

void CardCtrl_1553B::Stop_1553UP()
{
    qDebug()<<"stop_1553up";
    flag_UP1553=false;
    cnt_1553send=0;
    tmp_1553files.close();
}

int CardCtrl_1553B::USleep(int us)
{
    LARGE_INTEGER fre;
    if (QueryPerformanceFrequency(&fre)) {
        LARGE_INTEGER run, priv, curr;
        run.QuadPart = fre.QuadPart * us / 1000000;
        QueryPerformanceCounter(&priv);
        do {
            QueryPerformanceCounter(&curr);
        } while ((curr.QuadPart - priv.QuadPart) < run.QuadPart);
        curr.QuadPart -= priv.QuadPart;
        int nres = (curr.QuadPart * 1000000 / fre.QuadPart);
        return nres;
    }
    return -1;
}

//RS422改变内外源输出
int CardCtrl_1553B::change_RS422pps(int fl)
{
    int status=0;
    switch (fl) {
    case 0:
        status += PA_PCIe_4202_RS422_SetChronous(m_g_vi, PA_RS422_SYNCSOURCE_IN);
        break;
    case 1:
        status += PA_PCIe_4202_RS422_SetChronous(m_g_vi, PA_RS422_SYNCSOURCE_OUT);
        break;
    default:
        break;
    }
    return status;
}
//主界面星时AB通道选择
void CardCtrl_1553B::XS_A_B(int ab, bool c)
{

    switch (ab) {
    case 0://通道A
        xs_A=c;
        break;
    case 1://通道B
        xs_B=c;
        break;
    default:
        break;
    }


}



//AB通道切换
void CardCtrl_1553B::setSendChannal(int index)
{
    //    bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    m_sendChannal=0;
    if(0 == index)//通道A
    {

        m_sendChannal |= BC_CONTROL_CHANNELA;
        m_sendChannal |= BC_CONTROL_BUFFERA;
    }
    else if(1 == index)//通道B
    {
        m_sendChannal |= BC_CONTROL_CHANNELB;
        m_sendChannal |= BC_CONTROL_BUFFERB;
    }
    else if(2 == index)
    {
        m_sendChannal |= BC_CONTROL_CHANNELA;
        m_sendChannal |= BC_CONTROL_BUFFERA;
        m_sendChannal |= BC_CONTROL_CHANNELB;
        m_sendChannal |= BC_CONTROL_BUFFERB;
    }
    else{}

    Bus_AB=index;

    if(OpenFlag_1553==1)//切换通道，周期消息需要改变通路
    {
        //关闭周期发送
        int status=0;
        for(int ch=0;ch<4;ch++)
        {
//            if(m_check_chFlg[ch]==false)continue;
            status += BusTools_BC_StartStop(m_ch_id[ch], 0);
            InitCycle_OderSend(ch,m_ch_id[ch]);
        }

    }
}

//1553板卡BC端初始化
int CardCtrl_1553B::Init_BC1553Card()
{
    int				status=0;
    BT_UINT			mode,ch_id[4];

    int dev_num;
    ViSession g_vi;

    // 首先以类型和实例为基础查找设备。
    dev_num = BusTools_FindDevice(MY_CARD_TYPE, MY_INSTANCE);
    if(dev_num<0)//未找1553到设备
    {
        return -1;
    }
    //初始化rs422，以rs422脉冲为周期
    status += PA_PCIe_4202_RS422_Init(&g_vi);
    m_g_vi=g_vi;//传递设备号全局变量
    RS422_Device_num=g_vi;
    if(status<0)
    {
        return -1;
    }
    // 打开设备并获得通道id。
    mode = API_B_MODE | API_SW_INTERRUPT;  // 1553B协议,使用SW中断。



    //4个通道，每个通道AB路
    BT_UINT MY_CH[4];
    MY_CH[0]=CHANNEL_1;
    MY_CH[1]=CHANNEL_2;
    MY_CH[2]=CHANNEL_3;
    MY_CH[3]=CHANNEL_4;
    for(int ch=0;ch<4;ch++)
    {
        status += BusTools_API_OpenChannel( &ch_id[ch], mode, dev_num, MY_CH[ch]);//得到通道id（1553B的AB通道都有4路输出，配置4个通道都会发送数据）
        m_ch_id[ch]=ch_id[ch]; //传递通道号全局变量

        // 初始化和重置内存。最小BM设置。
        status += BusTools_BM_Init(ch_id[ch], 1, 1);
        if (status != API_SUCCESS) printf("BM_ERROR = %d\n",status);

        // 选择外部总线。(内外)
        status += BusTools_SetInternalBus(ch_id[ch], 0);
        if (status != API_SUCCESS) printf("BUS_ERROR = %d\n",status);

        //现在让我们建立一个简单的BC。
        //初始化BC无中断,没有重试,没有resp在16us,延迟resp在14us,
        //小帧时间20000us,每个消息1个数据缓冲区。
        status += BusTools_BC_Init(ch_id[ch], 0, 0, 0, 16, 14, 20000, 1);
        if (status != API_SUCCESS) printf("BC_ERROR = %d\n",status);

        //分配2个消息内存
        status += BusTools_BC_MessageAlloc(ch_id[ch], 200);//先分配200个消息内存
        if (status != API_SUCCESS) printf("Alloc_ERROR = %d\n",status);

        // 设置发送的PPS的同步源
        status += BusTools_SetSynchronousSource(ch_id[ch], PA_1553B_SYNCSOURCE_IN, PA_RS422_PULSE_OUT_CH8);

        //周期消息发送配置。。。。。。。。。。消息号0-1；
        InitCycle_OderSend(ch,ch_id[ch]);
        //矢量字判断发送初始化。。。。。。。。消息号10-33；
        Init_DealVector(ch);

        //////////////////////////////////////////////////////////////////////////////////////////////////
        //中断函数注册，在设备初始化成功后注册。
        memset(&sIntFIFO1, 0, sizeof(sIntFIFO1));
        if(ch==0)sIntFIFO1.function       = Return_Fun;  //中断回调函数
        if(ch==1)sIntFIFO1.function       = Return_Fun2;  //中断回调函数
        if(ch==2)sIntFIFO1.function       = Return_Fun3;  //中断回调函数
        if(ch==3)sIntFIFO1.function       = Return_Fun4;  //中断回调函数
        sIntFIFO1.iPriority      = THREAD_PRIORITY_BELOW_NORMAL;
        sIntFIFO1.dwMilliseconds = INFINITE;
        sIntFIFO1.iNotification  = 0;

        // Register for BC message events
        sIntFIFO1.FilterType     = EVENT_BC_MESSAGE;//BC中断
        for (int rt=0; rt < 32; rt++ )
            for (int tr = 0; tr < 2; tr++ )
                for (int sa = 0; sa < 32; sa++ )
                    sIntFIFO1.FilterMask[rt][tr][sa] = 0xFFFFFFFF; // Enable all messages
        //调用register函数来注册并启动线程。
        status += BusTools_RegisterFunction(ch_id[ch], &sIntFIFO1, REGISTER_FUNCTION);//注册一个回调功能。
        //调用register函数取消注册并停止BC线程。(可以配合BusTools_BC_StartStop(ch_id[ch], 1)启动/停止 BC 模式。使用。)
        //status += BusTools_RegisterFunction(ch_id[ch], &sIntFIFO1, UNREGISTER_FUNCTION);//取消一个回调功能。
    }

    if (status == API_SUCCESS) {

        // 设置RS422的时钟工作源为内部源，即由板上晶振提供
        // PA_RS422_SYNCSOURCE_OUT表示时钟工作源由外部标频源提供
        status += PA_PCIe_4202_RS422_SetChronous(g_vi, PA_RS422_SYNCSOURCE_IN);

        //判断是否初始化成功标志
        OpenFlag_1553=true;
        emit send_pluseStatus(OpenFlag_1553,g_vi);//给脉冲时间突发传递参数(422设备号)，广播根据脉冲发送

        //对应位0不输出，1输出(新加12.9)//暂时只开通0，4，6路
        status+=PA_PCIe_4202_RS422_SetSyncPluseEnable(g_vi,0x51);
        //配置输出主路，其他均以这一路对齐输出(新加12.9)
        status+=PA_PCIe_4202_RS422_SetSyncPluseMode(g_vi,PA_RS422_PULSE_OUT_CH8);

        //配置rs422参数
        status += PA_PCIe_4202_RS422_EnableSend(g_vi, PA_RS422_PULSE_OUT_CH8, PA_DISABLE);
        // 脉冲发生模式：周期模式
        status += PA_PCIe_4202_RS422_SetPulseMode(g_vi, PA_RS422_PULSE_OUT_CH8, PA_PULSEMODE_PERIOD);
        // 脉冲发送参数：低有效、MS精度、脉宽：10ms、周期：0.5s
        status += PA_PCIe_4202_RS422_SetPulseOut(g_vi, PA_RS422_PULSE_OUT_CH8, PA_LEVEL_HIGH, PA_PRECISION_US, 1000, 500000);
                                                            //1553周期用ch3,ch2给管控备用，不能输出，第8路固定给1553B脉冲突发
        // 开启发送使能
        status += PA_PCIe_4202_RS422_EnableSend(g_vi, PA_RS422_PULSE_OUT_CH8, PA_ENABLE);

        //新版另外7路根据第8路，0.5s的1553输出同步输出，不用再配置
//        uchar arr_ch[8];
//        arr_ch[0]=PA_RS422_PULSE_OUT_CH1;
//        arr_ch[1]=PA_RS422_PULSE_OUT_CH2;
//        arr_ch[2]=PA_RS422_PULSE_OUT_CH3;
//        arr_ch[3]=PA_RS422_PULSE_OUT_CH4;
//        arr_ch[4]=PA_RS422_PULSE_OUT_CH5;
//        arr_ch[5]=PA_RS422_PULSE_OUT_CH6;
//        arr_ch[6]=PA_RS422_PULSE_OUT_CH7;
//        arr_ch[7]=PA_RS422_PULSE_OUT_CH8;
//        for(int ch=0;ch<8;ch++)
//        {
//            if(ch==7)continue;
//            //配置rs422参数
//            status += PA_PCIe_4202_RS422_EnableSend(g_vi, arr_ch[ch], PA_DISABLE);
//            // 脉冲发生模式：周期模式
//            status += PA_PCIe_4202_RS422_SetPulseMode(g_vi,  arr_ch[ch], PA_PULSEMODE_PERIOD);
//            // 脉冲发送参数：低有效、MS精度、脉宽：10ms、周期：1s
//            status += PA_PCIe_4202_RS422_SetPulseOut(g_vi,  arr_ch[ch], PA_LEVEL_HIGH, PA_PRECISION_US, 1000, 1000000);//脉冲输出用
//            // 开启发送使能
//            status += PA_PCIe_4202_RS422_EnableSend(g_vi,  arr_ch[ch], PA_ENABLE);

//        }

        //设置输入脉冲
        uchar arr_inch[8];
        arr_inch[0]=PA_RS422_PULSE_IN_CH1;
        arr_inch[1]=PA_RS422_PULSE_IN_CH2;
        arr_inch[2]=PA_RS422_PULSE_IN_CH3;
        arr_inch[3]=PA_RS422_PULSE_IN_CH4;
        arr_inch[4]=PA_RS422_PULSE_IN_CH5;
        arr_inch[5]=PA_RS422_PULSE_IN_CH6;
        arr_inch[6]=PA_RS422_PULSE_IN_CH7;
        arr_inch[7]=PA_RS422_PULSE_IN_CH8;

        for(int i=0;i<8;i++)
        {
            status += PA_PCIe_4202_RS422_EnableReceive(g_vi,  arr_inch[i], PA_DISABLE);
            status += PA_PCIe_4202_RS422_SetPulseIn(g_vi, arr_inch[i], PA_LEVEL_HIGH, PA_PRECISION_US);
            status += PA_PCIe_4202_RS422_EnableReceive(g_vi,  arr_inch[i], PA_ENABLE);
        }

    }
    else printf("1553can Init Field! %d\n", status);



    return  status;
}



//1553板卡RT端初始化
int CardCtrl_1553B::Init_RT1553Card()
{

    BT_INT status;
    BT_UINT ch_id;
    API_RT_ABUF Abuf_RT1;                   // RT address buffer structure.//addressbuf地址缓冲区
    API_RT_CBUF Cbuf_RT1SA1R; // RT control buffer structures.//controlbuf控制缓存区
    API_RT_MBUF_WRITE msg_buffer_write;     //rt消息写入结构体
    //    int dev_num, mode;
    //    //-------------------------- Initialize API and board -----------------------------
    //    // First find the device based on type and instance.
    //    dev_num = BusTools_FindDevice(MY_CARD_TYPE, MY_INSTANCE);//查找设备号
    //    if (dev_num < 0)
    //    {
    //        return -1;
    //    }
    //    // Open the device and get the channel id.
    //    mode = API_B_MODE | API_SW_INTERRUPT; // 1553B protocol, use SW interrupts.
    //    status = BusTools_API_OpenChannel( &ch_id, mode, dev_num, MY_CHANNEL);//得到通道id
    //沿用1553BC初始化函数
    status=-1;
    if(OpenFlag_1553==true)
        status=API_SUCCESS;
    for(int ch=0;ch<4;ch++)
    {
        ch_id=m_ch_id[ch];
        if (status == API_SUCCESS)
        {
            // Select External Bus.
            //选择外部总线
            status = BusTools_SetInternalBus(ch_id, 0);
            if (status != API_SUCCESS)
            {
                return -1;
            }
            // Now lets set up an RT.
            status = BusTools_RT_Init(ch_id, 0);//初始化RT无中断
            if (status == API_SUCCESS)
            {

                memset(&Abuf_RT1,0,sizeof(API_RT_ABUF));
                //Setup RT address buffer for our RT (RT1)
                Abuf_RT1.enable_a = 1; // Respond on bus A
                Abuf_RT1.enable_b = 1; // Respond on bus B
                //功能：写 RT 地址控制缓存。
                status = BusTools_RT_AbufWrite(ch_id, 31, &Abuf_RT1);//RT地址31
                status = BusTools_RT_AbufWrite(ch_id, 7, &Abuf_RT1);//RT地址7
                //status = BusTools_RT_AbufWrite(ch_id, 19, &Abuf_RT1);//RT地址19
                if (status != API_SUCCESS)
                {
                    return -1;
                }
                msg_buffer_write.enable = 0;            // No interrupts enabled
                msg_buffer_write.error_inj_id = 0;      // No error injection
                //            for(int i=0;i<32;i++)
                //            {
                //                msg_buffer_write.mess_data[i]=0xAA00+i;
                //            }
                //memset(msg_buffer_write.mess_data,0,sizeof (msg_buffer_write.mess_data));
                for(int j=0;j<32;j++)
                {
                    // Setup a control buffer - RT1, SA1, Receive, 1 buffer.
                    Cbuf_RT1SA1R.legal_wordcount = 0xFFFFFFFF; // any word count is legal.
                    //功能：写 RT 控制缓冲区。
                    BusTools_RT_CbufWrite(ch_id,31,j,1,1,&Cbuf_RT1SA1R);//0，Receive；1，Transmit
                    BusTools_RT_CbufWrite(ch_id,31,j,0,1,&Cbuf_RT1SA1R);
                    BusTools_RT_CbufWrite(ch_id,7,j,1,1,&Cbuf_RT1SA1R);
                    BusTools_RT_CbufWrite(ch_id,7,j,0,1,&Cbuf_RT1SA1R);
                    if (status != API_SUCCESS)
                    {
                        return -1;
                    }
                    // Put some data in our transmit buffer

                    //能：写 RT 消息。
                    BusTools_RT_MessageWrite(ch_id,31,j,1,0,&msg_buffer_write);
                    BusTools_RT_MessageWrite(ch_id,31,j,0,0,&msg_buffer_write);
                    BusTools_RT_MessageWrite(ch_id,7,j,1,0,&msg_buffer_write);
                    BusTools_RT_MessageWrite(ch_id,7,j,0,0,&msg_buffer_write);

                    if (status != API_SUCCESS)
                    {
                        return -1;
                    }
                }
                // Now lets turn on our RT
                status = BusTools_RT_StartStop(ch_id, 1);
                if (status != API_SUCCESS)
                {
                    return -1;
                }
            }
        }
        else
        {
            return -1;
        }
    }


    return status;
}

//RT消息改变
void CardCtrl_1553B::Write_RT_Data(int cnt)
{

    GNSS_timecodeMessage();//GNSS时间码（消息号52，1帧）BT广播

    GNSS_postionMessage(cnt);//GNSS定位（65公共发送，消息号）BT广播

    GNSS_trackMessage(cnt);//GNSS定轨（68公共发送，消息号）BT广播

    RT_Message();//配置发送

}

//RT消息配置
int CardCtrl_1553B::RT_Message()
{
    API_BC_MBUF msg;
    msg.control=BC_CONTROL_MESSAGE;
    //    msg.control|=BC_CONTROL_CHANNELA;//BC_CONTROL_CHANNELB;
    //    msg.control|=BC_CONTROL_BUFFERA;
    msg.control|= m_sendChannal;
    msg.control|=BC_CONTROL_RTRTFORMAT;
    msg.messno=52;
    msg.messno_next=53;   //0xffff

    msg.gap_time=1000;
    msg.mess_command1.rtaddr=31;
    msg.mess_command1.subaddr=16;
    msg.mess_command1.tran_rec=0;//接收
    msg.mess_command1.wcount=3;
    msg.mess_command2.rtaddr=7;
    msg.mess_command2.subaddr=16;
    msg.mess_command2.tran_rec=1;//发送
    msg.mess_command2.wcount=3;

    msg.mframeno				= 0;
    msg.mframeen				= 1;
    msg.mframetime              = 1000;


    int status=0;

    status += BusTools_BC_Write(MY_1553AD_ALL,52,&msg);//自定义封装函数

    if(status!=API_SUCCESS) return status;

    msg.messno=53;
    msg.messno_next=54;
    msg.gap_time=1000;
    msg.mess_command1.rtaddr=31;
    msg.mess_command1.subaddr=17;
    msg.mess_command1.tran_rec=0;//接收
    msg.mess_command2.rtaddr=7;
    msg.mess_command2.subaddr=17;
    msg.mess_command2.tran_rec=1;//发送
    msg.mess_command1.wcount=0;

    status += BusTools_BC_Write(MY_1553AD_ALL,53,&msg);//自定义封装函数
    if(status!=API_SUCCESS) return status;

    msg.messno=54;
    msg.messno_next=0xffff;
    msg.gap_time=1000;
    msg.mess_command1.rtaddr=31;
    msg.mess_command1.subaddr=18;
    msg.mess_command1.tran_rec=0;//接收
    msg.mess_command2.rtaddr=7;
    msg.mess_command2.subaddr=18;
    msg.mess_command2.tran_rec=1;//发送
    msg.mess_command1.wcount=0;

    status += BusTools_BC_Write(MY_1553AD_ALL,54,&msg);//自定义封装函数

    if(status!=API_SUCCESS) return status;

    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(52,MY_1553AD_ALL);

    return status;

}




//周期发送函数
int CardCtrl_1553B::InitCycle_OderSend(int ch,uint ch_id)//轮询消息，循环发送，间隔0.5秒,包括状态字查询和矢量字查询(远程终端19轮询)
{

    //周期消息初始化设置
    int status=0;
    //周期消息个数
    m_CycMessno_CNT=2;
    API_BC_MBUF		bc_msg[2];
    //yyh 23.10.19
    // 发送状态字命令（如果RT的子地址是0，或者31，就是返回方式指令的数据）
    printf("MSG 0 . . . \n");
    bc_msg[0].messno				= 0;		// Message number
    bc_msg[0].control = BC_CONTROL_MESSAGE;		// This is a standard BC message.
    //    bc_msg[0].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg[0].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A
    bc_msg[0].control |= m_sendChannal;
    bc_msg[0].control |= BC_CONTROL_MFRAME_BEG;	// Beginning of minor frame.
    bc_msg[0].control |= BC_CONTROL_INTERRUPT;	//中断函数控制字

    bc_msg[0].messno_next			= 1;		// Next message number, go to msg #1
    bc_msg[0].mess_command1.rtaddr	= 19;		// Command word 1, RT address
    bc_msg[0].mess_command1.subaddr = 0;		// Command word 1, Subaddress
    bc_msg[0].mess_command1.tran_rec = 1;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    bc_msg[0].mess_command1.wcount = 2;         //方式指令，发送上一状态字
    bc_msg[0].gap_time				= 10;		// Intermessage gap time in microseconds

    bc_msg[0].mframeno				= 0;
    bc_msg[0].mframeen				= 1;        //周期发送使能
    bc_msg[0].mframetime			= 1000;

    // Fill data buffer
    for (int i=0; i<32; i++) bc_msg[0].data[0][i] = 0xAB00 + i;

    // Write the message to board memory
    status += BusTools_BC_Write(ch,0,&bc_msg[0]);//自定义封装函数

    // 发送矢量字命令
    printf("MSG 1 . . . \n");
    memset(&bc_msg[1], 0, sizeof(bc_msg[1]));    // Clear all fields.
    bc_msg[1].messno				= 1;		// Message number
    bc_msg[1].control = BC_CONTROL_MESSAGE;		// This is a standard BC message.
    //    bc_msg[1].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg[1].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A
    bc_msg[1].control |= m_sendChannal;
    bc_msg[1].control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
    bc_msg[1].control |= BC_CONTROL_INTERRUPT;	//中断函数控制字

    bc_msg[1].messno_next			= 0;		// Next message number, go to msg #1
    bc_msg[1].mess_command1.rtaddr	= 19;		// Command word 1, RT address
    bc_msg[1].mess_command1.subaddr = 0;		// Command word 1, Subaddress
    bc_msg[1].mess_command1.tran_rec = 1;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    bc_msg[1].mess_command1.wcount = 16;        //发送矢量字方式命令
    bc_msg[1].gap_time				= 2000;		// Intermessage gap time in microseconds//与上一帧时间间隔微秒

    bc_msg[1].mframeno				= 0;
    bc_msg[1].mframeen				= 1;        //周期发送使能
    bc_msg[1].mframetime			= 1000;

    // Fill data buffer
    for (int i=0; i<32; i++) bc_msg[0].data[0][i] = 0xAB00 + i;

    // Write the message to board memory
    status += BusTools_BC_Write(ch,1,&bc_msg[1]);//自定义封装函数
    //开启周期发送
    if(m_check_chFlg[ch]==true)status += BusTools_BC_StartStop(ch_id, 1);

    return status;
}

//矢量字判断发送
int CardCtrl_1553B::Init_DealVector(uint ch)
{
    API_BC_MBUF BC_msgs;
    int TempMess=10;
    memset(&BC_msgs, 0, sizeof(BC_msgs));       // Clear all fields.
    BC_msgs.messno				=TempMess;		// Message number
    BC_msgs.control = BC_CONTROL_MESSAGE;       // This is a standard BC message.
    //    BC_msgs.control |= BC_CONTROL_CHANNELA;     // Send message on bus A (primary).
    //    BC_msgs.control |= BC_CONTROL_BUFFERA;      // Only using one buffer, buffer A
    BC_msgs.control |= m_sendChannal;
    BC_msgs.control |= BC_CONTROL_INTERRUPT;    //中断函数控制字
    BC_msgs.messno_next	= TempMess+1;           // Next message number, go to msg #1

    BC_msgs.mess_command1.rtaddr	= 19;       // Command word 1, RT address
    BC_msgs.mess_command1.subaddr = 0;          // Command word 1, Subaddress
    BC_msgs.mess_command1.tran_rec = 1;         // Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
    BC_msgs.mess_command1.wcount = 0;
    BC_msgs.gap_time				= 10;       // //非周期帧间隔us  Intermessage gap time in microseconds

    BC_msgs.mframeno				= 0;
    BC_msgs.mframeen				= 1;        //周期发送使能(0,关，1，开)
    BC_msgs.mframetime			= 1000;         //周期帧间隔us

    if(1)//慢速遥测（512字节，需要发送8帧）消息号10-17；
    {
        TempMess=10;//起始消息号
        BC_msgs.mess_command1.subaddr =3;      // Command word 1, Subaddress
        for(int i=0;i<8;i++)
        {
            BC_msgs.messno=TempMess+i;		// Message number
            BC_msgs.messno_next	= TempMess+i+1;
            if(i==0)BC_msgs.control |= BC_CONTROL_MFRAME_BEG;
            if(i==7)
            {
                BC_msgs.control |= BC_CONTROL_MFRAME_END;
                BC_msgs.messno_next=0xFFFF;
            }
            //写入
            BusTools_BC_Write(ch,TempMess+i, &BC_msgs);//自定义封装函数
        }
    }
    if(1)//打包遥测（256字节，需要发送4帧）消息号18-21；
    {
        TempMess=18;//起始消息号
        BC_msgs.mess_command1.subaddr =4;      // Command word 1, Subaddress
        for(int i=0;i<4;i++)
        {
            BC_msgs.messno=TempMess+i;		// Message number（尽量不要公用一块任务ID，速度太快会来不及缓存发送）
            BC_msgs.messno_next	=TempMess+i+1;
            if(i==0)BC_msgs.control |= BC_CONTROL_MFRAME_BEG;
            if(i==3)
            {
                BC_msgs.control |= BC_CONTROL_MFRAME_END;
                BC_msgs.messno_next=0xFFFF;
            }
            //写入
            BusTools_BC_Write(ch,TempMess+i, &BC_msgs);//自定义封装函数
        }
    }
    if(1)//内存下卸请求发送（256字节，需要发送4帧*3次）消息号22-33；
    {
        TempMess=22;//起始消息号
        BC_msgs.mess_command1.subaddr =12;      // Command word 1, Subaddress
        for(int i=0;i<12;i++)
        {
            BC_msgs.messno=22+i;		// Message number（尽量不要公用一块任务ID，速度太快会来不及缓存发送）
            BC_msgs.messno_next	= 22+i+1;
            if(i==0)BC_msgs.control |= BC_CONTROL_MFRAME_BEG;
            if(i==11)
            {
                BC_msgs.control |= BC_CONTROL_MFRAME_END;
                BC_msgs.messno_next=0xFFFF;
            }
            //写入
            BusTools_BC_Write(ch,22+i, &BC_msgs);//自定义封装函数
        }

    }

    return 0;
}


//依据应发送非周期消息
void CardCtrl_1553B::BC_Dealvetor(USHORT sldata,int ch)
{
    //总线通信消息
    //printf("MSG quest . . . \n");
    STR_Vectorword Vword;
    memcpy(&Vword,&sldata,sizeof(sldata));

    //判断标志位请求是否置1
    int status=0;
    if(Vword.b1)//慢速遥测请求发送
    {
        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(10,ch);
    }
    if(Vword.b2)//打包遥测请求发送
    {
        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(18,ch);
    }
    if(Vword.b6)//内存下卸请求发送
    {
        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(22,ch);
    }

}

int CardCtrl_1553B::Close1553B()
{
    int status=0;
    if(OpenFlag_1553)
    {
        for(int ch=0;ch<4;ch++)
        {
            status+=BusTools_BC_StartStop(m_ch_id[ch], 0);
            status+=BusTools_API_Close(m_ch_id[ch]);
        }
        status+=PA_PCIe_4202_RS422_Close(m_g_vi);
        status+=BusTools_RT_StartStop(m_g_vi, 0);

    }

    return status;
}
//设置pps哪路输出
int CardCtrl_1553B::Set_PPS(uchar tmp)
{

    //PA_RS422_PULSE_OUT_CH1 4
    //PA_RS422_PULSE_OUT_CH2 5
    //PA_RS422_PULSE_OUT_CH3 6
    //PA_RS422_PULSE_OUT_CH4 7
    //PA_RS422_PULSE_OUT_CH5 12
    //PA_RS422_PULSE_OUT_CH6 13
    //PA_RS422_PULSE_OUT_CH7 14
    //PA_RS422_PULSE_OUT_CH8 15

    uchar pps_set=tmp;
    if(!OpenFlag_1553)return -1;
    //对应位0不输出，1输出 //pps_set初始值0x51...暂时只开通0，4，6路
    int status=PA_PCIe_4202_RS422_SetSyncPluseEnable(m_g_vi,pps_set);

    return status;
}

int CardCtrl_1553B::Set_PPStest()
{
//    uchar arr_ch[4];
//    arr_ch[0]=PA_RS422_PULSE_OUT_CH1;
//    arr_ch[1]=PA_RS422_PULSE_OUT_CH4;
//    arr_ch[2]=PA_RS422_PULSE_OUT_CH5;
//    arr_ch[3]=PA_RS422_PULSE_OUT_CH6;

//    unsigned long wide=0,period1=0;
//    int a;
//    for(int i=0;i<4;i++)
//    {
//        a=PA_PCIe_4202_RS422_ReadPulseIn(m_g_vi, arr_ch[i], &wide, &period1);
//        qDebug()<<i<<"_wide:"<<wide<<"period:"<<period1<<"\n";
//    }

//    return a;

    uchar arr_inch[8];
    arr_inch[0]=PA_RS422_PULSE_IN_CH1;//实际读取0
    arr_inch[1]=PA_RS422_PULSE_IN_CH2;//实际读取0
    arr_inch[2]=PA_RS422_PULSE_IN_CH3;//实际读取1
    arr_inch[3]=PA_RS422_PULSE_IN_CH4;//实际读取1
    arr_inch[4]=PA_RS422_PULSE_IN_CH5;//实际读取0
    arr_inch[5]=PA_RS422_PULSE_IN_CH6;//实际读取0
    arr_inch[6]=PA_RS422_PULSE_IN_CH7;//实际读取1
    arr_inch[7]=PA_RS422_PULSE_IN_CH8;//实际读取1

    int a=0;
    for(int i=0;i<8;i++)
    {
        uchar level=0;
        a+=PA_PCIe_4202_RS422_ReadLevel(m_g_vi,arr_inch[i],&level);
        qDebug()<<"lecel:ch"<<arr_inch[i]<<":"<<level;
    }

    return a;

}
//界面按钮总控制
int CardCtrl_1553B::cyc1553_onoff(bool switch_)
{
    int status=0;
    if(switch_){
        //开启周期发送
        for(int ch=0;ch<4;ch++)
        {
            if(m_check_chFlg[ch]==false)continue;//该路通道没勾选
            status += BusTools_BC_StartStop(m_ch_id[ch], 1);
        }

    }
    else{
        //关闭周期发送
        for(int ch=0;ch<4;ch++)
        {
            status += BusTools_BC_StartStop(m_ch_id[ch], 0);
        }

    }
    return status;
}

//选择单独控制
int CardCtrl_1553B::cyc1553_AD(bool switch_)
{
    int status=0;
    if(switch_)
    {
        //开启周期发送
        for(int ch=0;ch<4;ch++)
        {
            if(m_check_chFlg[ch]==false)continue;//该路通道没勾选
            status += BusTools_BC_StartStop(m_ch_id[ch], 1);
        }
    }else
    {
        for(int ch=0;ch<4;ch++)
        {
            if(m_check_chFlg[ch]==true)continue;//关闭没有开启的通道
            status += BusTools_BC_StartStop(m_ch_id[ch], 0);
        }
    }
    return status;
}

UINT CardCtrl_1553B::Get_Time()
{
    struct tm t1;//year从1900年1.1开始，月从0开始
    //时间2000-1-1 12:00:00
    t1.tm_sec = 0;
    t1.tm_min = 0;
    t1.tm_hour = 12;
    t1.tm_mday = 1;
    t1.tm_mon = 0;
    t1.tm_year = 2000-1900;
    //基于当前系统的当前日期/时间
    time_t now1 = mktime(&t1);//将struct tm 结构的时间转换为从1970年至今的秒数

    //获取系统当前时间
    time_t now = time(NULL);
    struct tm* t;
    t = localtime(&now);
    //cout << asctime(t)<<endl;//将结构体中的信息转换成真实世界的时间，以结构体显示
    t->tm_year += 0;//会自己减掉1900
    t->tm_mon += 0;
    t->tm_mday += 0;//当前天数不用加1
    time_t now_s = mktime(t);


    time_t def_sec;
    def_sec = difftime(now_s, now1);//返回两个时间差的秒值
    //cout << "时间差:" << def_sec << "s" << endl;
    //输出tm 结构体各部分
    //tm* ltm = gmtime(&now_s);//将time_t表示的时间转换为没有经过时区转换的UTC时间
    //cout << "时间差:";
    //cout << ltm->tm_year  << "年";
    //cout << ltm->tm_mon << "月";
    //cout << ltm->tm_mday << "日";
    //cout << ltm->tm_hour << "时";
    //cout << ltm->tm_min<< "分";
    //cout << ltm->tm_sec << "秒"<<endl;

    return def_sec;

}




//1553单步发送接口
int CardCtrl_1553B::OnceSend_Data(unsigned char* Data, int Datalen,ushort rt,ushort sub,int addr)
{
    if((rt==31)||(rt==7)||(sub==28))//广播消息,1553上注 控制台不显示
    {

    }
    else
    {
        //        QByteArray ss;
        //        if(!qFile.open(QFile::WriteOnly | QFile::Text)) {
        //            qDebug()<<"xx_file error";
        //            return 0;
        //        }
        //        for(int i=0;i<Datalen;i++)
        //        {
        //            //测试
        //            if(i%64==0)
        //            {
        //                printf("\n");
        //                //ss.append("\r\n");
        //            }
        //            printf("%02x ",Data[i]);
        //            QString s1=QString("%1 ").arg(Data[i],2,16,QLatin1Char('0')).toUpper();
        //            ss.append(s1);

        //        }
        //        qFile.write(ss);
        //        qFile.close();



        //显示输出1
//        for(int i=0;i<Datalen;i++)
//        {
//            if(i%64==0)printf("\n");
//            printf("%02x ",Data[i]);
//        }
        //显示输出2
//        QString outMess;
//        for(int i=0;i<Datalen;i++)
//        {
//            outMess+=QString("%1 ").arg(Data[i],2,16,QLatin1Char('0'));
//        }
//        qDebug()<<outMess;
    }
    if(OpenFlag_1553==false)return -1;


    int status=0;
    QVector<ushort> V_TxBuff;
    V_TxBuff.resize(0);
    //uchar转ushort
    for(int i=0;i<Datalen/2;i++)
    {
        V_TxBuff.push_back((Data[2*i]<<8)+Data[2*i+1]);
    }
    if(Datalen%2)V_TxBuff.push_back(Data[Datalen-1]<<8);

    //数据发送
    int framesum=(V_TxBuff.size()+LEN_S32-1)/LEN_S32;
    API_BC_MBUF bc_msg[framesum];//消息帧数
    //周期消息个数起为非周期消息起点(前面非周期消息)
    //int tmpmess=Cyc_Messno_CNT;
    int tmpmess=80;//非周期消息号起点
    if(rt==31&&sub==7)tmpmess=60;
    if(rt==31&&sub==17)tmpmess=65;
    if(rt==31&&sub==18)tmpmess=68;
    for(int i=0;i<framesum;i++)
    {
        memset(&bc_msg[i], 0, sizeof(API_BC_MBUF));
        bc_msg[i].messno				= tmpmess+i;		// Message number
        bc_msg[i].control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
        //        bc_msg[i].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
        //        bc_msg[i].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
        bc_msg[i].control |= m_sendChannal;
        bc_msg[i].messno_next			= tmpmess+i+1;	// Next message number
        //首帧
        if(i==0){
            bc_msg[i].control |= BC_CONTROL_MFRAME_BEG;	// End of minor frame.
        }
        //尾帧
        if(i==(framesum-1)){
            bc_msg[i].control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
            bc_msg[i].messno_next			= 0xFFFF;	// Next message number
        }

        bc_msg[i].mess_command1.rtaddr	= rt;		// Command word 1, RT address
        bc_msg[i].mess_command1.subaddr = sub;		// Command word 1, Subaddress
        bc_msg[i].mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
        bc_msg[i].mess_command1.wcount = 0;         //一帧发送的数据长度，0默认32字
        bc_msg[i].gap_time				= 1000;		// Intermessage gap time in microseconds

        bc_msg[i].mframeno				= 0;
        bc_msg[i].mframeen				= 1;
        bc_msg[i].mframetime			= 1000;

        int tmpdata=LEN_S32;
        if(i==(framesum-1)){        //最后一帧长度
            if((V_TxBuff.size()%LEN_S32)!=0)
            {
                tmpdata=V_TxBuff.size()%LEN_S32;
                bc_msg[i].mess_command1.wcount = tmpdata;
            }
        }
        for(int j=0;j<tmpdata;j++)
            bc_msg[i].data[0][j]=V_TxBuff[(i*LEN_S32)+j];

        // Write the message to board memory
        status +=BusTools_BC_Write(addr,tmpmess+i, &bc_msg[i]);//自定义封装函数

    }
    //封装发送1553非周期发送函数
    //qDebug()<<"Mssg::"<<tmpmess;
    status +=BusTools_BC_Send(tmpmess,addr);

    return status;
}

//中断回调函数 1
BT_INT _stdcall CardCtrl_1553B::Return_Fun(BT_UINT cardnum, struct api_int_fifo *sIntFIFO)
{

    int head_index, tail_index;
    API_RT_MBUF_READ msg_buffer_read;//struct to read RT message
    API_BC_MBUF bc_msg_read; //struct to read BC message
    head_index = sIntFIFO->head_index;
    tail_index = sIntFIFO->tail_index;
    //调试信息
    QDateTime cur_time = QDateTime::currentDateTime();
    //    QString str = cur_time.toString("MM-dd hh:mm:ss");
    //    qDebug()<<"rFun..."<<str;
    //    qDebug()<<head_index;
    //    qDebug()<<tail_index;
    while(head_index!=tail_index)
    {
        //bc消息中断
        if(sIntFIFO->fifo[tail_index].event_type == EVENT_BC_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid,wordcount;
            rtaddress=sIntFIFO->fifo[tail_index].rtaddress;
            subaddress=sIntFIFO->fifo[tail_index].subaddress;
            transrec=sIntFIFO->fifo[tail_index].transrec;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            wordcount=sIntFIFO->fifo[tail_index].wordcount;
            BusTools_BC_MessageRead(cardnum, messnoid, &bc_msg_read);//bc信息读取（cardnum不是同通道）


            if(transrec==1)//BC receive
            {
                //对19-0的矢量字进行判断
                if(rtaddress==19 && subaddress==0 && wordcount==16)
                {
                    //读取矢量字，同时有状态字yyh 23.10.26
                    //有无服务请求（状态字）
                    if(bc_msg_read.mess_status1.sr)
                    {
                        BT_U16BIT sl_datas=bc_msg_read.data[0][0];//获取矢量字，区分类型
                        sp_card1553->Deal_vetor[0]=sl_datas;//终端请求处理....(1553通道1)
                    }
                }
                //对19-0，wordcount=19的自测试字回应
                if(rtaddress==19 && subaddress==0 && wordcount==19)
                {
                    //添加输出
                    //printf("SelfTest........_return:%x\n",bc_msg_read.data[0][0]);
                    QString tmps=QString("自测试结果:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                    emit sp_card1553->send_1553oupt(tmps,2);
                }
                //对19-3的慢速遥测进行判断（一共8帧）
                if(rtaddress==19 &&subaddress==3)
                {
                    if(bc_msg_read.data[0][0]==0x0731)//头标志(头帧)
                    {
                        memset(sp_card1553->msYC_buff[0],0,64*8);
                        memcpy(sp_card1553->msYC_buff[0],bc_msg_read.data[0],64);
                        sp_card1553->getHead[0]=true;
                        sp_card1553->curr_YCindex[0]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead[0])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->msYC_buff[0]+sp_card1553->curr_YCindex[0]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex[0]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex[0]==8)
                    {
                        emit sp_card1553->Get_1553Yc1(sp_card1553->msYC_buff[0],32*8,MY_1553AD1);
                        sp_card1553->getHead[0]=false;
                        sp_card1553->curr_YCindex[0]=0;

                    }
                    //添加输出
                    //                    printf("index:%d_messageid:%d status1:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");
                }
                //对19-4的打包遥测进行判断(一共4帧)...............
                if(rtaddress==19 &&subaddress==4)
                {
                    if(bc_msg_read.data[0][0]==0x073E)//头标志(头帧)
                    {
                        memset(sp_card1553->mPack_buff[0],0,64*4);
                        memcpy(sp_card1553->mPack_buff[0],bc_msg_read.data[0],64);
                        sp_card1553->getHead_pack4[0]=true;
                        sp_card1553->curr_YCindex_pack4[0]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead_pack4[0])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->mPack_buff[0]+sp_card1553->curr_YCindex_pack4[0]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex_pack4[0]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex_pack4[0]==4)
                    {
                        emit sp_card1553->Get_1553Yc_pack(sp_card1553->mPack_buff[0],32*4,MY_1553AD1);
                        sp_card1553->getHead_pack4[0]=false;
                        sp_card1553->curr_YCindex_pack4[0]=0;

                    }
                    //                    //添加输出
                    //                    printf("index:%d_messageid:%d status1 DB:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");


                }
                //对19-12的内存下卸
                if(rtaddress==19 &&subaddress==12)
                {
//                    QByteArray ss;
//                    //添加输出
//                    printf("index:%d_messageid:%d status1 Memory:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
//                    QString xx=QString::number(cnt_xx);
//                    ss.append(xx);
//                    ss.append("..........\r\n");
//                    for(int rtn=0;rtn<32;rtn++)
//                    {
//                        printf("%02x ",bc_msg_read.data[0][rtn]);
//                        QString s1=QString("%1 ").arg(bc_msg_read.data[0][rtn],8,16,QLatin1Char('0')).toUpper();
//                        ss.append(s1);
//                    }
//                    printf("\n");
//                    ss.append("\r\n");
//                    sp_card1553->qFile.write(ss);
                    emit sp_card1553->Send_MemoryData(MY_1553AD1,bc_msg_read.data[0],32);

                }
                //对19-15的长抱环值取回
                if(rtaddress==19 &&subaddress==15)
                {
                    //添加输出
                    //printf("longPack........_return:%x\n",bc_msg_read.data[0][0]);
                    if((bc_msg_read.control&0x0500)&&(bc_msg_read.control&0x0A00))
                    {
                        QString tmpsA=QString("A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                        QString tmpsB=QString("B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else if(bc_msg_read.control&0x0500)//0101,bus_A通路
                    {
                        QString tmpsA=QString("A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                    }
                    else if(bc_msg_read.control&0x0A00)//1010,bus_B通路
                    {
                        QString tmpsB=QString("B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else
                    {}

                }

            }
        }
        //rt消息中断
        else if(sIntFIFO->fifo[sIntFIFO->tail_index].event_type== EVENT_RT_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            rtaddress = sIntFIFO->fifo[tail_index].rtaddress;
            transrec = sIntFIFO->fifo[tail_index].transrec;
            subaddress = sIntFIFO->fifo[tail_index].subaddress;
            if (sIntFIFO->fifo[tail_index].transrec == 0) //RT receive
            {
                BusTools_RT_MessageRead(cardnum,rtaddress,subaddress,transrec,
                                        sIntFIFO->fifo[tail_index].bufferID, &msg_buffer_read);
            }
        }
        tail_index = (tail_index + 1) & sIntFIFO->mask_index;// Next entry，Wrap the index
        head_index = sIntFIFO->head_index;
    }
    sIntFIFO->tail_index = tail_index;// Save the index
    return true;
}

//中断函数 2
int CardCtrl_1553B::Return_Fun2(unsigned int cardnum, api_int_fifo *sIntFIFO)
{
    int head_index, tail_index;
    API_RT_MBUF_READ msg_buffer_read;//struct to read RT message
    API_BC_MBUF bc_msg_read; //struct to read BC message
    head_index = sIntFIFO->head_index;
    tail_index = sIntFIFO->tail_index;
    //调试信息
    QDateTime cur_time = QDateTime::currentDateTime();
    //    QString str = cur_time.toString("MM-dd hh:mm:ss");
    //    qDebug()<<"rFun..."<<str;
    //    qDebug()<<head_index;
    //    qDebug()<<tail_index;
    while(head_index!=tail_index)
    {
        //bc消息中断
        if(sIntFIFO->fifo[tail_index].event_type == EVENT_BC_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid,wordcount;
            rtaddress=sIntFIFO->fifo[tail_index].rtaddress;
            subaddress=sIntFIFO->fifo[tail_index].subaddress;
            transrec=sIntFIFO->fifo[tail_index].transrec;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            wordcount=sIntFIFO->fifo[tail_index].wordcount;
            BusTools_BC_MessageRead(cardnum, messnoid, &bc_msg_read);//bc信息读取（cardnum不是同通道）


            if(transrec==1)//BC receive
            {
                //对19-0的矢量字进行判断
                if(rtaddress==19 && subaddress==0 && wordcount==16)
                {
                    //读取矢量字，同时有状态字yyh 23.10.26
                    //有无服务请求（状态字）
                    if(bc_msg_read.mess_status1.sr)
                    {
                        BT_U16BIT sl_datas=bc_msg_read.data[0][0];//获取矢量字，区分类型
                        sp_card1553->Deal_vetor[1]=sl_datas;//终端请求处理....(1553通道2)
                    }
                }
                //对19-0，wordcount=19的自测试字回应
                if(rtaddress==19 && subaddress==0 && wordcount==19)
                {
                    //添加输出
                    //printf("SelfTest........_return:%x\n",bc_msg_read.data[0][0]);
                    QString tmps=QString("单机2 自测试结果:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                    emit sp_card1553->send_1553oupt(tmps,2);
                }
                //对19-3的慢速遥测进行判断（一共8帧）
                if(rtaddress==19 &&subaddress==3)
                {
                    if(bc_msg_read.data[0][0]==0x0731)//头标志(头帧)
                    {
                        memset(sp_card1553->msYC_buff[1],0,64*8);
                        memcpy(sp_card1553->msYC_buff[1],bc_msg_read.data[0],64);
                        sp_card1553->getHead[1]=true;
                        sp_card1553->curr_YCindex[1]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead[1])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->msYC_buff[1]+sp_card1553->curr_YCindex[1]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex[1]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex[1]==8)
                    {
                        emit sp_card1553->Get_1553Yc2(sp_card1553->msYC_buff[1],32*8,MY_1553AD2);
                        sp_card1553->getHead[1]=false;
                        sp_card1553->curr_YCindex[1]=0;

                    }
                    //添加输出
                    //                    printf("index:%d_messageid:%d status1:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");
                }
                //对19-4的打包遥测进行判断(一共4帧)...............
                if(rtaddress==19 &&subaddress==4)
                {
                    if(bc_msg_read.data[0][0]==0x073E)//头标志(头帧)
                    {
                        memset(sp_card1553->mPack_buff[1],0,64*4);
                        memcpy(sp_card1553->mPack_buff[1],bc_msg_read.data[0],64);
                        sp_card1553->getHead_pack4[1]=true;
                        sp_card1553->curr_YCindex_pack4[1]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead_pack4[1])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->mPack_buff[1]+sp_card1553->curr_YCindex_pack4[1]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex_pack4[1]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex_pack4[1]==4)
                    {
                        emit sp_card1553->Get_1553Yc_pack(sp_card1553->mPack_buff[1],32*4,MY_1553AD2);
                        sp_card1553->getHead_pack4[1]=false;
                        sp_card1553->curr_YCindex_pack4[1]=0;

                    }
                    //                    //添加输出
                    //                    printf("index:%d_messageid:%d status1 DB:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");


                }
                //对19-12的内存下卸
                if(rtaddress==19 &&subaddress==12)
                {
//                    QByteArray ss;
//                    //添加输出
//                    printf("index:%d_messageid:%d status1 Memory:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
//                    QString xx=QString::number(cnt_xx);
//                    ss.append(xx);
//                    ss.append("..........\r\n");
//                    for(int rtn=0;rtn<32;rtn++)
//                    {
//                        printf("%02x ",bc_msg_read.data[0][rtn]);
//                        QString s1=QString("%1 ").arg(bc_msg_read.data[0][rtn],8,16,QLatin1Char('0')).toUpper();
//                        ss.append(s1);
//                    }
//                    printf("\n");
//                    ss.append("\r\n");
                    //sp_card1553->qFile.write(ss);
                    emit sp_card1553->Send_MemoryData(MY_1553AD2,bc_msg_read.data[0],32);
                }
                //对19-15的长抱环值取回
                if(rtaddress==19 &&subaddress==15)
                {
                    //添加输出
                    //printf("longPack........_return:%x\n",bc_msg_read.data[0][0]);
                    if((bc_msg_read.control&0x0500)&&(bc_msg_read.control&0x0A00))
                    {
                        QString tmpsA=QString("单机2 A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                        QString tmpsB=QString("单机2 B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else if(bc_msg_read.control&0x0500)//0101,bus_A通路
                    {
                        QString tmpsA=QString("单机2 A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                    }
                    else if(bc_msg_read.control&0x0A00)//1010,bus_B通路
                    {
                        QString tmpsB=QString("单机2 B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else
                    {}

                }

            }
        }
        //rt消息中断
        else if(sIntFIFO->fifo[sIntFIFO->tail_index].event_type== EVENT_RT_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            rtaddress = sIntFIFO->fifo[tail_index].rtaddress;
            transrec = sIntFIFO->fifo[tail_index].transrec;
            subaddress = sIntFIFO->fifo[tail_index].subaddress;
            if (sIntFIFO->fifo[tail_index].transrec == 0) //RT receive
            {
                BusTools_RT_MessageRead(cardnum,rtaddress,subaddress,transrec,
                                        sIntFIFO->fifo[tail_index].bufferID, &msg_buffer_read);
            }
        }
        tail_index = (tail_index + 1) & sIntFIFO->mask_index;// Next entry，Wrap the index
        head_index = sIntFIFO->head_index;
    }
    sIntFIFO->tail_index = tail_index;// Save the index
    return true;
}

//中断函数 3
int CardCtrl_1553B::Return_Fun3(unsigned int cardnum, api_int_fifo *sIntFIFO)
{
    int head_index, tail_index;
    API_RT_MBUF_READ msg_buffer_read;//struct to read RT message
    API_BC_MBUF bc_msg_read; //struct to read BC message
    head_index = sIntFIFO->head_index;
    tail_index = sIntFIFO->tail_index;
    //调试信息
    QDateTime cur_time = QDateTime::currentDateTime();
    //    QString str = cur_time.toString("MM-dd hh:mm:ss");
    //    qDebug()<<"rFun..."<<str;
    //    qDebug()<<head_index;
    //    qDebug()<<tail_index;
    while(head_index!=tail_index)
    {
        //bc消息中断
        if(sIntFIFO->fifo[tail_index].event_type == EVENT_BC_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid,wordcount;
            rtaddress=sIntFIFO->fifo[tail_index].rtaddress;
            subaddress=sIntFIFO->fifo[tail_index].subaddress;
            transrec=sIntFIFO->fifo[tail_index].transrec;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            wordcount=sIntFIFO->fifo[tail_index].wordcount;
            BusTools_BC_MessageRead(cardnum, messnoid, &bc_msg_read);//bc信息读取（cardnum不是同通道）


            if(transrec==1)//BC receive
            {
                //对19-0的矢量字进行判断
                if(rtaddress==19 && subaddress==0 && wordcount==16)
                {
                    //读取矢量字，同时有状态字yyh 23.10.26
                    //有无服务请求（状态字）
                    if(bc_msg_read.mess_status1.sr)
                    {
                        BT_U16BIT sl_datas=bc_msg_read.data[0][0];//获取矢量字，区分类型
                        sp_card1553->Deal_vetor[2]=sl_datas;//终端请求处理....(1553通道3)
                    }
                }
                //对19-0，wordcount=19的自测试字回应
                if(rtaddress==19 && subaddress==0 && wordcount==19)
                {
                    //添加输出
                    //printf("SelfTest........_return:%x\n",bc_msg_read.data[0][0]);
                    QString tmps=QString("单机3 自测试结果:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                    emit sp_card1553->send_1553oupt(tmps,2);
                }
                //对19-3的慢速遥测进行判断（一共8帧）
                if(rtaddress==19 &&subaddress==3)
                {
                    if(bc_msg_read.data[0][0]==0x0731)//头标志(头帧)
                    {
                        memset(sp_card1553->msYC_buff[2],0,64*8);
                        memcpy(sp_card1553->msYC_buff[2],bc_msg_read.data[0],64);
                        sp_card1553->getHead[2]=true;
                        sp_card1553->curr_YCindex[2]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead[2])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->msYC_buff[2]+sp_card1553->curr_YCindex[2]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex[2]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex[2]==8)
                    {
                        emit sp_card1553->Get_1553Yc3(sp_card1553->msYC_buff[2],32*8,MY_1553AD3);
                        sp_card1553->getHead[2]=false;
                        sp_card1553->curr_YCindex[2]=0;

                    }
                    //添加输出
                    //                    printf("index:%d_messageid:%d status1:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");
                }
                //对19-4的打包遥测进行判断(一共4帧)...............
                if(rtaddress==19 &&subaddress==4)
                {
                    if(bc_msg_read.data[0][0]==0x073E)//头标志(头帧)
                    {
                        memset(sp_card1553->mPack_buff[2],0,64*4);
                        memcpy(sp_card1553->mPack_buff[2],bc_msg_read.data[0],64);
                        sp_card1553->getHead_pack4[2]=true;
                        sp_card1553->curr_YCindex_pack4[2]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead_pack4[2])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->mPack_buff[2]+sp_card1553->curr_YCindex_pack4[2]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex_pack4[2]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex_pack4[2]==4)
                    {
                        emit sp_card1553->Get_1553Yc_pack(sp_card1553->mPack_buff[2],32*4,MY_1553AD3);
                        sp_card1553->getHead_pack4[2]=false;
                        sp_card1553->curr_YCindex_pack4[2]=0;

                    }
                    //                    //添加输出
                    //                    printf("index:%d_messageid:%d status1 DB:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");


                }
                //对19-12的内存下卸
                if(rtaddress==19 &&subaddress==12)
                {
//                    QByteArray ss;
//                    //添加输出
//                    printf("index:%d_messageid:%d status1 Memory:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
//                    QString xx=QString::number(cnt_xx);
//                    ss.append(xx);
//                    ss.append("..........\r\n");
//                    for(int rtn=0;rtn<32;rtn++)
//                    {
//                        printf("%02x ",bc_msg_read.data[0][rtn]);
//                        QString s1=QString("%1 ").arg(bc_msg_read.data[0][rtn],8,16,QLatin1Char('0')).toUpper();
//                        ss.append(s1);
//                    }
//                    printf("\n");
//                    ss.append("\r\n");
                    //sp_card1553->qFile.write(ss);
                    emit sp_card1553->Send_MemoryData(MY_1553AD3,bc_msg_read.data[0],32);
                }
                //对19-15的长抱环值取回
                if(rtaddress==19 &&subaddress==15)
                {
                    //添加输出
                    //printf("longPack........_return:%x\n",bc_msg_read.data[0][0]);
                    if((bc_msg_read.control&0x0500)&&(bc_msg_read.control&0x0A00))
                    {
                        QString tmpsA=QString("单机3 A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                        QString tmpsB=QString("单机3 B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else if(bc_msg_read.control&0x0500)//0101,bus_A通路
                    {
                        QString tmpsA=QString("单机3 A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                    }
                    else if(bc_msg_read.control&0x0A00)//1010,bus_B通路
                    {
                        QString tmpsB=QString("单机3 B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else
                    {}

                }

            }
        }
        //rt消息中断
        else if(sIntFIFO->fifo[sIntFIFO->tail_index].event_type== EVENT_RT_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            rtaddress = sIntFIFO->fifo[tail_index].rtaddress;
            transrec = sIntFIFO->fifo[tail_index].transrec;
            subaddress = sIntFIFO->fifo[tail_index].subaddress;
            if (sIntFIFO->fifo[tail_index].transrec == 0) //RT receive
            {
                BusTools_RT_MessageRead(cardnum,rtaddress,subaddress,transrec,
                                        sIntFIFO->fifo[tail_index].bufferID, &msg_buffer_read);
            }
        }
        tail_index = (tail_index + 1) & sIntFIFO->mask_index;// Next entry，Wrap the index
        head_index = sIntFIFO->head_index;
    }
    sIntFIFO->tail_index = tail_index;// Save the index
    return true;
}

//中断函数 4
int CardCtrl_1553B::Return_Fun4(unsigned int cardnum, api_int_fifo *sIntFIFO)
{
    int head_index, tail_index;
    API_RT_MBUF_READ msg_buffer_read;//struct to read RT message
    API_BC_MBUF bc_msg_read; //struct to read BC message
    head_index = sIntFIFO->head_index;
    tail_index = sIntFIFO->tail_index;
    //调试信息
    QDateTime cur_time = QDateTime::currentDateTime();
    //    QString str = cur_time.toString("MM-dd hh:mm:ss");
    //    qDebug()<<"rFun..."<<str;
    //    qDebug()<<head_index;
    //    qDebug()<<tail_index;
    while(head_index!=tail_index)
    {
        //bc消息中断
        if(sIntFIFO->fifo[tail_index].event_type == EVENT_BC_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid,wordcount;
            rtaddress=sIntFIFO->fifo[tail_index].rtaddress;
            subaddress=sIntFIFO->fifo[tail_index].subaddress;
            transrec=sIntFIFO->fifo[tail_index].transrec;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            wordcount=sIntFIFO->fifo[tail_index].wordcount;
            BusTools_BC_MessageRead(cardnum, messnoid, &bc_msg_read);//bc信息读取（cardnum不是同通道）


            if(transrec==1)//BC receive
            {
                //对19-0的矢量字进行判断
                if(rtaddress==19 && subaddress==0 && wordcount==16)
                {
                    //读取矢量字，同时有状态字yyh 23.10.26
                    //有无服务请求（状态字）
                    if(bc_msg_read.mess_status1.sr)
                    {
                        BT_U16BIT sl_datas=bc_msg_read.data[0][0];//获取矢量字，区分类型
                        sp_card1553->Deal_vetor[3]=sl_datas;//终端请求处理....(1553通道4)
                    }
                }
                //对19-0，wordcount=19的自测试字回应
                if(rtaddress==19 && subaddress==0 && wordcount==19)
                {
                    //添加输出
                    //printf("SelfTest........_return:%x\n",bc_msg_read.data[0][0]);
                    QString tmps=QString("单机4 自测试结果:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                    emit sp_card1553->send_1553oupt(tmps,2);
                }
                //对19-3的慢速遥测进行判断（一共8帧）
                if(rtaddress==19 &&subaddress==3)
                {
                    if(bc_msg_read.data[0][0]==0x0731)//头标志(头帧)
                    {
                        memset(sp_card1553->msYC_buff[3],0,64*8);
                        memcpy(sp_card1553->msYC_buff[3],bc_msg_read.data[0],64);
                        sp_card1553->getHead[3]=true;
                        sp_card1553->curr_YCindex[3]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead[3])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->msYC_buff[3]+sp_card1553->curr_YCindex[3]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex[3]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex[3]==8)
                    {
                        emit sp_card1553->Get_1553Yc4(sp_card1553->msYC_buff[3],32*8,MY_1553AD4);
                        sp_card1553->getHead[3]=false;
                        sp_card1553->curr_YCindex[3]=0;

                    }
                    //添加输出
                    //                    printf("index:%d_messageid:%d status1:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");
                }
                //对19-4的打包遥测进行判断(一共4帧)...............
                if(rtaddress==19 &&subaddress==4)
                {
                    if(bc_msg_read.data[0][0]==0x073E)//头标志(头帧)
                    {
                        memset(sp_card1553->mPack_buff[3],0,64*4);
                        memcpy(sp_card1553->mPack_buff[3],bc_msg_read.data[0],64);
                        sp_card1553->getHead_pack4[3]=true;
                        sp_card1553->curr_YCindex_pack4[3]++;

                    }
                    else
                    {
                        if(sp_card1553->getHead_pack4[3])//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->mPack_buff[3]+sp_card1553->curr_YCindex_pack4[3]*32,bc_msg_read.data[0],64);
                            sp_card1553->curr_YCindex_pack4[3]++;
                        }
                    }
                    if(sp_card1553->curr_YCindex_pack4[3]==4)
                    {
                        emit sp_card1553->Get_1553Yc_pack(sp_card1553->mPack_buff[3],32*4,MY_1553AD4);
                        sp_card1553->getHead_pack4[3]=false;
                        sp_card1553->curr_YCindex_pack4[3]=0;

                    }
                    //                    //添加输出
                    //                    printf("index:%d_messageid:%d status1 DB:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    //                    for(int rtn=0;rtn<32;rtn++)
                    //                    {
                    //                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    //                    }
                    //                    printf("\n");


                }
                //对19-12的内存下卸
                if(rtaddress==19 &&subaddress==12)
                {
//                    QByteArray ss;
//                    //添加输出
//                    printf("index:%d_messageid:%d status1 Memory:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
//                    QString xx=QString::number(cnt_xx);
//                    ss.append(xx);
//                    ss.append("..........\r\n");
//                    for(int rtn=0;rtn<32;rtn++)
//                    {
//                        printf("%02x ",bc_msg_read.data[0][rtn]);
//                        QString s1=QString("%1 ").arg(bc_msg_read.data[0][rtn],8,16,QLatin1Char('0')).toUpper();
//                        ss.append(s1);
//                    }
//                    printf("\n");
//                    ss.append("\r\n");
                    //sp_card1553->qFile.write(ss);
                    emit sp_card1553->Send_MemoryData(MY_1553AD4,bc_msg_read.data[0],32);
                }
                //对19-15的长抱环值取回
                if(rtaddress==19 &&subaddress==15)
                {
                    //添加输出
                    //printf("longPack........_return:%x\n",bc_msg_read.data[0][0]);
                    if((bc_msg_read.control&0x0500)&&(bc_msg_read.control&0x0A00))
                    {
                        QString tmpsA=QString("单机4 A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                        QString tmpsB=QString("单机4 B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else if(bc_msg_read.control&0x0500)//0101,bus_A通路
                    {
                        QString tmpsA=QString("单机4 A通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsA,2);
                    }
                    else if(bc_msg_read.control&0x0A00)//1010,bus_B通路
                    {
                        QString tmpsB=QString("单机4 B通道长抱环取反回复:0x%1").arg(bc_msg_read.data[0][0],4,16,QLatin1Char('0')).toUpper();
                        emit sp_card1553->send_1553oupt(tmpsB,2);//BUSB待添加验证
                    }
                    else
                    {}

                }

            }
        }
        //rt消息中断
        else if(sIntFIFO->fifo[sIntFIFO->tail_index].event_type== EVENT_RT_MESSAGE)
        {
            BT_INT rtaddress, subaddress, transrec,messnoid;
            messnoid = sIntFIFO->fifo[tail_index].bufferID;
            rtaddress = sIntFIFO->fifo[tail_index].rtaddress;
            transrec = sIntFIFO->fifo[tail_index].transrec;
            subaddress = sIntFIFO->fifo[tail_index].subaddress;
            if (sIntFIFO->fifo[tail_index].transrec == 0) //RT receive
            {
                BusTools_RT_MessageRead(cardnum,rtaddress,subaddress,transrec,
                                        sIntFIFO->fifo[tail_index].bufferID, &msg_buffer_read);
            }
        }
        tail_index = (tail_index + 1) & sIntFIFO->mask_index;// Next entry，Wrap the index
        head_index = sIntFIFO->head_index;
    }
    sIntFIFO->tail_index = tail_index;// Save the index
    return true;
}


















