#include "CardCtrl_1553B.h"
#include<iostream>
#include<stdio.h>
#include<QtEndian>
#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <vector>

#define MY_CARD_TYPE	   PCCD1553
#define MY_INSTANCE     1
#define MY_CHANNEL		CHANNEL_1
#define LEN_C64 64   //1553can单帧最多64字节
#define LEN_S32 32   //1553can单帧最多64字节

using namespace std;
bool getHead=false;
int curr_YCindex=0;
CardCtrl_1553B*CardCtrl_1553B::sp_card1553=NULL;
QMutex CardCtrl_1553B::mtx_1553while;



int cnt_xx=0;
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

    m_CycMessno_CNT=0;
    Deal_vetor=0;
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
    setSendChannal(0);
    OpenFlag_1553=false;
    Flag_1553board=false;
    //timer1553=new QTimer(this);
    //connect(timer1553,SIGNAL(timeout()),this,SLOT(WriteOnTimerMessage()));
    //timer1553->start(1000);
    //m_nTimerCounter=Get_Time();
    m_nTimerCounter=1000;
    sp_card1553=this;
    msYC_buff=new ushort[32*8];
    //内存下卸存储
    QString qFileName ="./暂存数据存储.txt";
    if(qFileName.isEmpty())return;
    qFile.setFileName(qFileName);
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
    delete [] msYC_buff;
    qFile.close();
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
            status = PA_PCIe_4202_RS422_ClearStatus(pluse_gvi, PA_RS422_PULSE_OUT_CH1);
            RecvTimes++;
            //printf("RS422通道接收到脉冲次数%dn",RecvTimes);
            if(1)//0.5s
            {
                QDateTime time=QDateTime::currentDateTime();
                QString str=time.toString("MM-dd hh:mm:ss");
                qDebug()<<"pluse time ="<<str<<"\n";
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
int CardCtrl_1553B::BusTools_BC_Send(uint messageID)
{

    mtx_1553while.lock();
    int status=0;

    //首先,确保我们已经完成了以前的非周期性msg。
    while (BusTools_BC_AperiodicTest(m_ch_id, 1) == API_BC_APERIODIC_RUNNING);//调试模式会卡在这里？？？

    // Then send our aperiodic message.
    //然后发送我们的非周期消息。
    status += BusTools_BC_AperiodicRun(m_ch_id, messageID, 1, 0, 20);
    mtx_1553while.unlock();

    return status;

}


//时间码消息、系统同步消息、长抱环测试消息、在线自测试消息。
void CardCtrl_1553B::WriteOnTimerMessage(uint pluse_cnt)
{

//    ushort buff[100]={0};
//    for(uint i=0;i<sizeof (buff)/2;i++)buff[i]=i+m_nTimerCounter;
//    emit Get_1553Yc(buff,sizeof (buff)/2);


    if(OpenFlag_1553)//1553板卡是否初始化成功
    {
        if(Deal_vetor!=0)//0.5s
        {
            BC_Dealvetor(Deal_vetor);
            Deal_vetor=0;
        }
        if(Flag_1553board)//是否开启广播消息
        {
            if(pluse_cnt%2==0)//1s
            {
                printf("Board... \n");
                m_nTimerCounter++;

                emit send_1553time(m_nTimerCounter);//传递主界面时间

                Write_RT_Data(m_nTimerCounter);//RT广播

                StartTimeBroadMessage();//星时和能源状态广播（消息号50，1帧）

                if(m_nTimerCounter % 2==0)
                OrbitalMessage(m_nTimerCounter);//轨道姿态数据（公共发送，消息号）

    //            if(m_nTimerCounter % 256==0)
    //                LongringMessage();//长抱环消息（消息号54，1帧）

    //            if(m_nTimerCounter % 3600==0)
    //                SystemStepMessage();//系统同步消息（消息号56，1帧）

    //            if(m_nTimerCounter % 65536==0)
    //                OnlineMessage();//自测试消息（中断中取应答，但是与rt19的矢量字冲突）（消息号58，1帧）
            }

        }
    }

}


//星时和能源状态广播(A/B轮询发送)
int CardCtrl_1553B::StartTimeBroadMessage()
{
    int status=0;
    for(int ch=0;ch<1;ch++)
    {
        API_BC_MBUF bc_msg;

        //周期消息个数起为非周期消息起点(前面非周期消息)
        int tmpmess=50;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
        memset(&bc_msg, 0, sizeof(API_BC_MBUF));
        bc_msg.messno   = tmpmess+ch;              // Message number
        bc_msg.control = BC_CONTROL_MESSAGE;	// This is a standard BC message.
        if(ch==0)
        {
            bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
            bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
        }

        if(ch==1)
        {
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
        status += BusTools_BC_MessageWrite(m_ch_id, tmpmess+ch, &bc_msg);

        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(tmpmess+ch);
    }

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
    bc_msg.gap_time				= 10;		// Intermessage gap time in microseconds

    bc_msg.mframeno				= 0;
    bc_msg.mframeen				= 1;
    bc_msg.mframetime			= 1000;

    // Fill data buffer
    bc_msg.data[0][0] = 0x146F;//系统同步数据字

    // Write the message to board memory
    status += BusTools_BC_MessageWrite(m_ch_id, tmpmess, &bc_msg);


    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(tmpmess);


    return status;
}

//长抱环测试
int CardCtrl_1553B::LongringMessage()
{

    int status=0;
    for(int ch=0;ch<2;ch++)
    {
        API_BC_MBUF bc_msg;

        //周期消息个数起为非周期消息起点(前面非周期消息)
        int tmpmess=54;   //非周期消息号起点（前面有2个周期消息，16个矢量字请求消息）
        memset(&bc_msg, 0, sizeof(API_BC_MBUF));
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
            bc_msg.control |= BC_CONTROL_BUFFERB;	// Only using one buffer, buffer A.
        }
        bc_msg.control |= BC_CONTROL_MFRAME_END;	// End of minor frame.
        bc_msg.messno_next			= tmpmess+1;	// Next message number


        bc_msg.mess_command1.rtaddr	= 19;		// Command word 1, RT address
        bc_msg.mess_command1.subaddr = 15;		// Command word 1, Subaddress
        bc_msg.mess_command1.tran_rec = 0;		// Command word 1, transmit (1) or receive (0)//0：bc-rt,1:rt-bc
        bc_msg.mess_command1.wcount = 1;         //一帧发送的数据长度，0默认32字
        bc_msg.gap_time				= 10;		// Intermessage gap time in microseconds

        bc_msg.mframeno				= 0;
        bc_msg.mframeen				= 1;
        bc_msg.mframetime			= 1000;

        // Fill data buffer
        bc_msg.data[0][0] = 0xAABB;//自定义字

        // Write the message to board memory
        status += BusTools_BC_MessageWrite(m_ch_id, tmpmess, &bc_msg);

        //长抱环测试返回值接收
        bc_msg.messno   = tmpmess+1;            // Message number
        bc_msg.control |= BC_CONTROL_INTERRUPT;	//中断函数控制字
        bc_msg.messno_next			= 0xffff;	//Next message number
        bc_msg.mess_command1.tran_rec = 1;
        status += BusTools_BC_MessageWrite(m_ch_id, tmpmess+1, &bc_msg);

        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(tmpmess);

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
    status += BusTools_BC_MessageWrite(m_ch_id, tmpmess, &bc_msg[0]);

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
    status += BusTools_BC_MessageWrite(m_ch_id, tmpmess+1, &bc_msg[1]);

    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(tmpmess);

    return status;
}
//轨道姿态数据广播
int CardCtrl_1553B::OrbitalMessage(int cnt)
{

    Orbitalstance_Data strorbital;
    int aa=sizeof (Orbitalstance_Data);
    memset(&strorbital,0,aa);


    if((v_orb.size()!=0)&&((uint)cnt<v_orb[v_orb.size()-1].thistime+1)&&((uint)cnt>v_orb[0].thistime-1))
    {
        //int tmp_cnt=cnt%v_orb.size();
        int tmp_cnt=cnt-v_orb[0].thistime;
        //qDebug()<<tmp_cnt<<"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
        strorbital.pack_mark=0x3012;
        strorbital.pack_sequence=qToBigEndian((ushort)2);
        strorbital.pack_len=qToBigEndian((ushort)3);

        strorbital.satsllite_mark=4;
        strorbital.softstart_I=5;
        strorbital.softstart_II=6;
        strorbital.softstart_III=7;
        strorbital.softstart_IV=8;
        //strorbital.thistime[0]=9;
        uint tm=qToBigEndian(v_orb[tmp_cnt].thistime);
        memcpy(&strorbital.thistime[2],&tm,4);


        strorbital.rolling_angle=qToBigEndian(v_orb[tmp_cnt].rolling_angle);
        strorbital.pitch_angle=qToBigEndian(v_orb[tmp_cnt].pitch_angle);
        strorbital.yawing_angle=qToBigEndian(v_orb[tmp_cnt].yawing_angle);
        strorbital.rolling_anglespeed=qToBigEndian((uint)13);
        strorbital.yawing_anglespeed=qToBigEndian((uint)14);
        strorbital.sun_x=qToBigEndian((uint)15);
        strorbital.sun_y=qToBigEndian((uint)16);
        strorbital.sun_z=qToBigEndian((uint)17);

        strorbital.sorfttime_I[0]=21;
        strorbital.sorft_Iside_x=qToBigEndian((int)22);
        strorbital.sorft_Iside_y=qToBigEndian((int)23);
        strorbital.sorft_Iside_z=qToBigEndian((int)24);
        strorbital.sorft_Ispeed_x=qToBigEndian((int)25);
        strorbital.sorft_Ispeed_y=qToBigEndian((int)26);
        strorbital.sorft_Ispeed_z=qToBigEndian((int)27);

        strorbital.sorfttime_II[0]=21;
        strorbital.sorft_IIside_x=qToBigEndian(int)22);
        strorbital.sorft_IIside_y=qToBigEndian(int)23);
        strorbital.sorft_IIside_z=qToBigEndian(int)24);
        strorbital.sorft_IIspeed_x=qToBigEndian((int)25);
        strorbital.sorft_IIspeed_y=qToBigEndian((int)26);
        strorbital.sorft_IIspeed_z=qToBigEndian((int)27);

        strorbital.sorfttime_III[0]=21;
        strorbital.sorft_IIIside_x=qToBigEndian((int)22);
        strorbital.sorft_IIIside_y=qToBigEndian((int)23);
        strorbital.sorft_IIIside_z=qToBigEndian((int)24);
        strorbital.sorft_IIIspeed_x=qToBigEndian((int)25);
        strorbital.sorft_IIIspeed_y=qToBigEndian((int)26);
        strorbital.sorft_IIIspeed_z=qToBigEndian((int)27);

        strorbital.sorfttime_IV[0]=21;
        strorbital.sorft_IVside_x=qToBigEndian((int)22);
        strorbital.sorft_IVside_y=qToBigEndian((int)23);
        strorbital.sorft_IVside_z=qToBigEndian((int)24);
        strorbital.sorft_IVspeed_x=qToBigEndian((int)25);
        strorbital.sorft_IVspeed_y=qToBigEndian((int)26);
        strorbital.sorft_IVspeed_z=qToBigEndian((int)27);
    }
    else
    {
        strorbital.pack_mark=0x3012;
        strorbital.pack_sequence=qToBigEndian((ushort)2);
        strorbital.pack_len=qToBigEndian((ushort)3);

        strorbital.satsllite_mark=4;
        strorbital.softstart_I=5;
        strorbital.softstart_II=6;
        strorbital.softstart_III=7;
        strorbital.softstart_IV=8;
        strorbital.thistime[0]=9;


        strorbital.rolling_angle=qToBigEndian((uint)10);
        strorbital.pitch_angle=qToBigEndian((uint)11);
        strorbital.yawing_angle=qToBigEndian((uint)12);
        strorbital.rolling_anglespeed=qToBigEndian((uint)13);
        strorbital.yawing_anglespeed=qToBigEndian((uint)14);
        strorbital.sun_x=qToBigEndian((uint)15);
        strorbital.sun_y=qToBigEndian((uint)16);
        strorbital.sun_z=qToBigEndian((uint)17);

        strorbital.sorfttime_I[0]=21;
        strorbital.sorft_Iside_x=qToBigEndian((int)22);
        strorbital.sorft_Iside_y=qToBigEndian((int)23);
        strorbital.sorft_Iside_z=qToBigEndian((int)24);
        strorbital.sorft_Ispeed_x=qToBigEndian((int)25);
        strorbital.sorft_Ispeed_y=qToBigEndian((int)26);
        strorbital.sorft_Ispeed_z=qToBigEndian((int)27);

        strorbital.sorfttime_II[0]=21;
        strorbital.sorft_IIside_x=qToBigEndian((int)22);
        strorbital.sorft_IIside_y=qToBigEndian((int)23);
        strorbital.sorft_IIside_z=qToBigEndian((int)24);
        strorbital.sorft_IIspeed_x=qToBigEndian((int)25);
        strorbital.sorft_IIspeed_y=qToBigEndian((int)26);
        strorbital.sorft_IIspeed_z=qToBigEndian((int)27);

        strorbital.sorfttime_III[0]=21;
        strorbital.sorft_IIIside_x=qToBigEndian((int)22);
        strorbital.sorft_IIIside_y=qToBigEndian((int)23);
        strorbital.sorft_IIIside_z=qToBigEndian((int)24);
        strorbital.sorft_IIIspeed_x=qToBigEndian((int)25);
        strorbital.sorft_IIIspeed_y=qToBigEndian((int)26);
        strorbital.sorft_IIIspeed_z=qToBigEndian((int)27);

        strorbital.sorfttime_IV[0]=21;
        strorbital.sorft_IVside_x=qToBigEndian((int)22);
        strorbital.sorft_IVside_y=qToBigEndian((int)23);
        strorbital.sorft_IVside_z=qToBigEndian((int)24);
        strorbital.sorft_IVspeed_x=qToBigEndian((int)25);
        strorbital.sorft_IVspeed_y=qToBigEndian((int)26);
        strorbital.sorft_IVspeed_z=qToBigEndian((int)27);
    }


    uchar *buff=new uchar[256];

    memset(buff,0x2a,256);
    memcpy(buff,(uchar*)&strorbital,sizeof (Orbitalstance_Data));
    OnceSend_Data(buff,256,31,7);
    delete [] buff;
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
//    status += BusTools_BC_MessageWrite(m_ch_id, tmpmess, &bc_msg);


//    //封装发送1553非周期发送函数
//    status +=BusTools_BC_Send(tmpmess);

    times=m_nTimerCounter;//使用设置的时间
    ushort time1=times>>16;
    ushort time2=times;

    GNSS_Time str;
    memset(&str,0,sizeof (str));
    str.code1=0;
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


    int status=BusTools_RT_MessageWrite(m_ch_id,7,16,1,0,&mbuf);
    if(status!=API_SUCCESS) return status;

    return status;
}

//GNSS定位数据
int CardCtrl_1553B::GNSS_postionMessage(int cnt)
{
    GNSS_Positioning str_postion;
    memset(&str_postion,0,sizeof (GNSS_Positioning));

    if((v_gnss_postion.size()!=0)&&((uint)cnt<v_gnss_postion[v_gnss_postion.size()-1].time_s+1)&&((uint)cnt>v_gnss_postion[0].time_s-1))//读取表格值
    {

        //int tmp_cnt=cnt%v_gnss_postion.size();
        int tmp_cnt=cnt-v_gnss_postion[0].time_s;
        //qDebug()<<tmp_cnt<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
        str_postion.pack_mark=0x7206;
        str_postion.pack_sequence=qToBigEndian((short)0xC000);
        str_postion.pack_len=qToBigEndian((short)0x0039);
        str_postion.posit_mark=0;
        str_postion.use_startsum=0;
        str_postion.time_s=qToBigEndian(v_gnss_postion[tmp_cnt].time_s);
        str_postion.position_x=qToBigEndian(v_gnss_postion[tmp_cnt].position_x);
        str_postion.position_y=qToBigEndian(v_gnss_postion[tmp_cnt].position_y);
        str_postion.position_z=qToBigEndian(v_gnss_postion[tmp_cnt].position_z);
        str_postion.speed_x=qToBigEndian(v_gnss_postion[tmp_cnt].speed_x);
        str_postion.speed_y=qToBigEndian(v_gnss_postion[tmp_cnt].speed_y);
        str_postion.speed_z=qToBigEndian(v_gnss_postion[tmp_cnt].speed_z);

        str_postion.track_mark=12;

        str_postion.position15_x=qToBigEndian((int)13);
        str_postion.position15_y=qToBigEndian((int)14);
        str_postion.position15_z=qToBigEndian((int)15);
        str_postion.speed15_x=qToBigEndian((int)16);
        str_postion.speed15_y=qToBigEndian((int)17);
        str_postion.speed15_z=qToBigEndian((int)18);

    }
    else
    {

        str_postion.pack_mark=0x7206;
        str_postion.pack_sequence=qToBigEndian((short)0xC000);
        str_postion.pack_len=qToBigEndian((short)0x0039);
        str_postion.posit_mark=0;
        str_postion.use_startsum=0;
        str_postion.time_s=qToBigEndian((uint)5);
        str_postion.position_x=qToBigEndian((int)6);
        str_postion.position_y=qToBigEndian((int)7);
        str_postion.position_z=qToBigEndian((int)8);
        str_postion.speed_x=qToBigEndian((int)9);
        str_postion.speed_y=qToBigEndian((int)10);
        str_postion.speed_z=qToBigEndian((int)11);

        str_postion.track_mark=12;

        str_postion.position15_x=qToBigEndian((int)13);
        str_postion.position15_y=qToBigEndian((int)14);
        str_postion.position15_z=qToBigEndian((int)15);
        str_postion.speed15_x=qToBigEndian((int)16);
        str_postion.speed15_y=qToBigEndian((int)17);
        str_postion.speed15_z=qToBigEndian((int)18);


    }


    //OnceSend_Data((uchar*)&str_postion,sizeof (GNSS_Positioning),31,17);
    ushort* buff=new ushort[sizeof(str_postion)/2+1];
    memcpy(buff,(uchar*)&str_postion,sizeof(str_postion));
    API_RT_MBUF_WRITE mbuf;
    mbuf.enable=0;
    mbuf.error_inj_id=0;
    for(int i=0;i<32;i++)
    {
        mbuf.mess_data[i]=qToBigEndian(buff[i]);
    }
    //memcpy(mbuf.mess_data,&str_postion,sizeof(str_postion));
    int status=BusTools_RT_MessageWrite(m_ch_id,7,17,1,0,&mbuf);
    if(status!=API_SUCCESS) return status;
    delete [] buff;
    return 0;
}

//GNSS定轨数据
int CardCtrl_1553B::GNSS_trackMessage(int cnt)
{
    GNSS_Track str_track;
    memset(&str_track,0,sizeof (GNSS_Track));

    if((v_gnss_orbit.size()!=0)&&((uint)cnt<v_gnss_orbit[v_gnss_orbit.size()-1].time_s+1)&&((uint)cnt>v_gnss_orbit[0].time_s-1))//读取表格值
    {
        //int tmp_cnt=cnt%v_gnss_orbit.size();
        int tmp_cnt=cnt-v_gnss_orbit[0].time_s;
        //qDebug()<<tmp_cnt<<"ggggggggggggggggggggggggggggggggggg";
        str_track.pack_mark=0x7306;
        str_track.pack_sequence=qToBigEndian((short)0xC000);
        str_track.pack_len=qToBigEndian((short)0x0039);
        str_track.track_mark=0;
        str_track.use_startsum=0;
        str_track.time_s=qToBigEndian(v_gnss_orbit[tmp_cnt].time_s);
        str_track.track_halflenth=qToBigEndian(v_gnss_orbit[tmp_cnt].track_halflenth);
        str_track.track_offcenter=qToBigEndian(v_gnss_orbit[tmp_cnt].track_offcenter);
        str_track.track_angle=qToBigEndian(v_gnss_orbit[tmp_cnt].track_angle);
        str_track.up_point=qToBigEndian(v_gnss_orbit[tmp_cnt].up_point);
        str_track.near_angle=qToBigEndian(v_gnss_orbit[tmp_cnt].near_angle);
        str_track.flat_angle=qToBigEndian(v_gnss_orbit[tmp_cnt].flat_angle);
        str_track.outpush_time=qToBigEndian((ushort)12);



        str_track.track_15halflenth=qToBigEndian((uint)13);
        str_track.track_15offcenter=qToBigEndian((uint)14);
        str_track.track_15angle=qToBigEndian((uint)15);
        str_track.up_15point=qToBigEndian((uint)16);
        str_track.near_15angle=qToBigEndian((uint)17);
        str_track.flat_15angle=qToBigEndian((uint)18);
    }
    else
    {
        str_track.pack_mark=0x7306;
        str_track.pack_sequence=qToBigEndian((short)0xC000);
        str_track.pack_len=qToBigEndian((short)0x0039);
        str_track.track_mark=0;
        str_track.use_startsum=0;
        str_track.time_s=qToBigEndian((uint)5);
        str_track.track_halflenth=qToBigEndian((uint)6);
        str_track.track_offcenter=qToBigEndian((uint)7);
        str_track.track_angle=qToBigEndian((uint)8);
        str_track.up_point=qToBigEndian((uint)9);
        str_track.near_angle=qToBigEndian((uint)10);
        str_track.flat_angle=qToBigEndian((uint)11);
        str_track.outpush_time=qToBigEndian((ushort)12);



        str_track.track_15halflenth=qToBigEndian((uint)13);
        str_track.track_15offcenter=qToBigEndian((uint)14);
        str_track.track_15angle=qToBigEndian((uint)15);
        str_track.up_15point=qToBigEndian((uint)16);
        str_track.near_15angle=qToBigEndian((uint)17);
        str_track.flat_15angle=qToBigEndian((uint)18);
    }

    ushort* buff=new ushort[sizeof(str_track)/2+1];
    memcpy(buff,(uchar*)&str_track,sizeof(str_track));
    API_RT_MBUF_WRITE mbuf;
    mbuf.enable=0;
    mbuf.error_inj_id=0;
    for(int i=0;i<32;i++)
    {
        mbuf.mess_data[i]=qToBigEndian(buff[i]);
    }
    //memcpy(mbuf.mess_data,buff,sizeof(str_track));
    int status=BusTools_RT_MessageWrite(m_ch_id,7,18,1,0,&mbuf);
    if(status!=API_SUCCESS) return status;
    delete [] buff;
    //OnceSend_Data((uchar*)&str_track,sizeof (GNSS_Track),31,18);
    return 0;
}

void CardCtrl_1553B::setSendChannal(int index)
{
    //    bc_msg.control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
    //    bc_msg.control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
    if(0 == index)
    {
        m_sendChannal |= BC_CONTROL_CHANNELA;
        m_sendChannal |= BC_CONTROL_BUFFERA;
    }
    else if(1 == index)
    {
        m_sendChannal |= BC_CONTROL_CHANNELB;
        m_sendChannal |= BC_CONTROL_BUFFERB;
    }
    else if(2 == index)
    {
        m_sendChannal |= BC_CONTROL_CHANNELA;
        m_sendChannal |= BC_CONTROL_BUFFERA;
        m_sendChannal |= BC_CONTROL_CHANNELA;
        m_sendChannal |= BC_CONTROL_BUFFERB;
    }
    else{}
}

//1553板卡BC端初始化
int CardCtrl_1553B::Init_BC1553Card()
{

    int				status=0;
    BT_UINT			mode,ch_id;

    int dev_num;
    ViSession g_vi;
    ViUInt8 channeltx = PA_RS422_PULSE_OUT_CH1;// 输出控制接口
    ViUInt8 channelrx = PA_RS422_PULSE_IN_CH1;// 输入控制接口
    Q_UNUSED(channelrx);//未使用

    // 首先以类型和实例为基础查找设备。
    dev_num = BusTools_FindDevice(MY_CARD_TYPE, MY_INSTANCE);
    if(dev_num<0)//未找1553到设备
    {
        return -1;
    }
    //初始化rs422，以rs422脉冲为周期
    status += PA_PCIe_4202_RS422_Init(&g_vi);
    m_g_vi=g_vi;//传递设备号全局变量
    if(status<0)
    {
        return -1;
    }
    // 打开设备并获得通道id。
    mode = API_B_MODE | API_SW_INTERRUPT;  // 1553B协议,使用SW中断。
    status += BusTools_API_OpenChannel( &ch_id, mode, dev_num, MY_CHANNEL);//得到通道id
    m_ch_id=ch_id; //传递通道号全局变量
    if (status == API_SUCCESS) {
        //判断是否初始化成功标志
        OpenFlag_1553=true;
        emit send_pluseStatus(OpenFlag_1553,g_vi);//给脉冲时间突发传递参数
        //配置rs422参数
        status += PA_PCIe_4202_RS422_EnableSend(g_vi, channeltx, PA_DISABLE);
        // 脉冲发生模式：周期模式
        status += PA_PCIe_4202_RS422_SetPulseMode(g_vi, channeltx, PA_PULSEMODE_PERIOD);
        // 脉冲发送参数：低有效、MS精度、脉宽：10ms、周期：1s
        status += PA_PCIe_4202_RS422_SetPulseOut(g_vi, channeltx, PA_LEVEL_HIGH, PA_PRECISION_US, 10000, 1000000);//脉冲输出用
        // 开启发送使能
        status += PA_PCIe_4202_RS422_EnableSend(g_vi, channeltx, PA_ENABLE);

        //配置rs422参数
        status += PA_PCIe_4202_RS422_EnableSend(g_vi, PA_RS422_PULSE_OUT_CH3, PA_DISABLE);
        // 脉冲发生模式：周期模式
        status += PA_PCIe_4202_RS422_SetPulseMode(g_vi, PA_RS422_PULSE_OUT_CH3, PA_PULSEMODE_PERIOD);
        // 脉冲发送参数：低有效、MS精度、脉宽：10ms、周期：0.5s
        status += PA_PCIe_4202_RS422_SetPulseOut(g_vi, PA_RS422_PULSE_OUT_CH3, PA_LEVEL_HIGH, PA_PRECISION_US, 10000, 500000);//1553周期用ch3,ch2给管控备用，不能输出
        // 开启发送使能
        status += PA_PCIe_4202_RS422_EnableSend(g_vi, PA_RS422_PULSE_OUT_CH3, PA_ENABLE);


        // 初始化和重置内存。最小BM设置。
        status += BusTools_BM_Init(ch_id, 1, 1);
        if (status != API_SUCCESS) printf("BM_ERROR = %d\n",status);

        // 选择外部总线。(内外)
        status += BusTools_SetInternalBus(ch_id, 0);
        if (status != API_SUCCESS) printf("BUS_ERROR = %d\n",status);

        //现在让我们建立一个简单的BC。
        //初始化BC无中断,没有重试,没有resp在16us,延迟resp在14us,
        //小帧时间20000us,每个消息1个数据缓冲区。
        status += BusTools_BC_Init(ch_id, 0, 0, 0, 16, 14, 20000, 1);
        if (status != API_SUCCESS) printf("BC_ERROR = %d\n",status);

        //分配2个消息内存
        status += BusTools_BC_MessageAlloc(ch_id, 100);//先分配100个消息内存
        if (status != API_SUCCESS) printf("Alloc_ERROR = %d\n",status);

        // 设置发送的PPS的同步源
        status += BusTools_SetSynchronousSource(ch_id, PA_1553B_SYNCSOURCE_IN, PA_RS422_PULSE_OUT_CH3);

        //周期消息发送配置。。。。。。。。。。消息号0-1；
        InitCycle_OderSend(ch_id);
        //矢量字判断发送初始化。。。。。。。。消息号10-33；
        Init_DealVector(ch_id);

        //////////////////////////////////////////////////////////////////////////////////////////////////
        //中断函数注册，在设备初始化成功后注册。
        memset(&sIntFIFO1, 0, sizeof(sIntFIFO1));
        sIntFIFO1.function       = Return_Fun;  //中断回调函数
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
        status += BusTools_RegisterFunction(ch_id, &sIntFIFO1, REGISTER_FUNCTION);//注册一个回调功能。
        //调用register函数取消注册并停止BC线程。(可以配合BusTools_BC_StartStop(ch_id, 1)启动/停止 BC 模式。使用。)
        //status += BusTools_RegisterFunction(ch_id, &sIntFIFO1, UNREGISTER_FUNCTION);//取消一个回调功能。

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
    ch_id=m_ch_id;
    status=-1;
    if(OpenFlag_1553==true)
        status=API_SUCCESS;
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

    int status=BusTools_BC_MessageWrite(m_ch_id,52,&msg);
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

    status=BusTools_BC_MessageWrite(m_ch_id,53,&msg);
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

    status=BusTools_BC_MessageWrite(m_ch_id,54,&msg);
    if(status!=API_SUCCESS) return status;

    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(52);

    return status;

}



//周期发送函数
int CardCtrl_1553B::InitCycle_OderSend(uint ch_id)//轮询消息，循环发送，间隔0.5秒,包括状态字查询和矢量字查询(远程终端19轮询)
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
    status += BusTools_BC_MessageWrite(ch_id,0, &bc_msg[0]);

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
    status += BusTools_BC_MessageWrite(ch_id,1, &bc_msg[1]);

    //开启周期发送
    status += BusTools_BC_StartStop(ch_id, 1);

    return status;
}

//矢量字判断发送
int CardCtrl_1553B::Init_DealVector(uint ch_id)
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
    BC_msgs.gap_time				= 10;       // Intermessage gap time in microseconds

    BC_msgs.mframeno				= 0;
    BC_msgs.mframeen				= 1;        //周期发送使能(0,关，1，开)
    BC_msgs.mframetime			= 1000;

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
            BusTools_BC_MessageWrite(ch_id,TempMess+i, &BC_msgs);
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
            BusTools_BC_MessageWrite(m_ch_id,TempMess+i, &BC_msgs);
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
            BusTools_BC_MessageWrite(m_ch_id,22+i, &BC_msgs);
        }

    }

    return 0;
}


//依据应发送非周期消息
void CardCtrl_1553B::BC_Dealvetor(USHORT sldata)
{
    //总线通信消息
    printf("MSG quest . . . \n");
    STR_Vectorword Vword;
    memcpy(&Vword,&sldata,sizeof(sldata));

    //判断标志位请求是否置1
    int status=0;
    if(Vword.b1)//慢速遥测请求发送
    {
        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(10);
    }
    if(Vword.b2)//打包遥测请求发送
    {
        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(18);
    }
    if(Vword.b6)//内存下卸请求发送
    {
        //封装发送1553非周期发送函数
        status +=BusTools_BC_Send(22);
    }

}

int CardCtrl_1553B::Close1553B()
{
    int status=0;
    if(OpenFlag_1553)
    {
        status+=BusTools_BC_StartStop(m_ch_id, 0);
        status+=BusTools_API_Close(m_ch_id);
        status+=PA_PCIe_4202_RS422_Close(m_g_vi);
        status+=BusTools_RT_StartStop(m_g_vi, 0);

    }
    return status;
}

int CardCtrl_1553B::cyc1553_onoff(bool switch_)
{
    int status=0;
    if(switch_){
        //开启周期发送
        status = BusTools_BC_StartStop(m_ch_id, 1);
    }
    else{
        //关闭周期发送
        status = BusTools_BC_StartStop(m_ch_id, 0);
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
int CardCtrl_1553B::OnceSend_Data(unsigned char* Data, int Datalen,ushort rt,ushort sub)
{
    if(rt==31)//广播消息控制台不显示
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
        for(int i=0;i<Datalen;i++)
        {
            if(i%64==0)printf("\n");
            printf("%02x ",Data[i]);


        }
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
    int tmpmess=70;//非周期消息号起点
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
        status += BusTools_BC_MessageWrite(m_ch_id, tmpmess+i, &bc_msg[i]);

    }
    //封装发送1553非周期发送函数
    status +=BusTools_BC_Send(tmpmess);

    return status;
}

//中断回调函数
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
            BusTools_BC_MessageRead(cardnum, messnoid, &bc_msg_read);
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
                        //sp_card1553->BC_Dealvetor(sl_datas);//终端请求处理
                        sp_card1553->Deal_vetor=sl_datas;//终端请求处理
                    }
                }
                //对19-0的矢量字进行判断
                if(rtaddress==19 && subaddress==0 && wordcount==19)
                {
                    //添加输出
                    printf("Test............._return:%x\n",bc_msg_read.data[0][0]);
                }
                //对19-3的慢速遥测进行判断（一共8帧）
                if(rtaddress==19 &&subaddress==3)
                {
                    if(bc_msg_read.data[0][0]==0x0731)//头标志(头帧)
                    {
                        memset(sp_card1553->msYC_buff,0,64*8);
                        memcpy(sp_card1553->msYC_buff,bc_msg_read.data[0],64);
                        getHead=true;
                        curr_YCindex++;

                    }
                    else
                    {
                        if(getHead)//(中间帧+尾帧)
                        {
                            memcpy(sp_card1553->msYC_buff+curr_YCindex*32,bc_msg_read.data[0],64);
                            curr_YCindex++;
                        }
                    }
                    if(curr_YCindex==8)
                    {
                        emit sp_card1553->Get_1553Yc(sp_card1553->msYC_buff,32*8);
                        getHead=false;
                        curr_YCindex=0;

                    }
                    //添加输出
//                    printf("index:%d_messageid:%d status1:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
//                    for(int rtn=0;rtn<32;rtn++)
//                    {
//                        printf("%02x ",bc_msg_read.data[0][rtn]);
//                    }
//                    printf("\n");
                }
                if(rtaddress==19 &&subaddress==4)//对19-4的打包遥测进行判断
                {
                    //添加输出
                    printf("index:%d_messageid:%d status1 DB:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    for(int rtn=0;rtn<32;rtn++)
                    {
                        printf("%02x ",bc_msg_read.data[0][rtn]);
                    }
                    printf("\n");
                }
                if(rtaddress==19 &&subaddress==12)//对19-12的内存下卸
                {
                    QByteArray ss;
                    //添加输出
                    printf("index:%d_messageid:%d status1 Memory:%u\n",tail_index,messnoid,bc_msg_read.mess_status1);
                    QString xx=QString::number(cnt_xx);
                    ss.append(xx);
                    ss.append("..........\r\n");
                    for(int rtn=0;rtn<32;rtn++)
                    {
                        printf("%02x ",bc_msg_read.data[0][rtn]);
                        QString s1=QString("%1 ").arg(bc_msg_read.data[0][rtn],8,16,QLatin1Char('0')).toUpper();
                        ss.append(s1);
                    }
                    printf("\n");
                    ss.append("\r\n");
                    sp_card1553->qFile.write(ss);
                }
                //对19-15的长抱环值取回
                if(rtaddress==19 &&subaddress==15)
                {
                    //添加输出
                    printf("longPack........_return:%x\n",bc_msg_read.data[0][0]);
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


















