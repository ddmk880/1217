#include "CardCtrl_RapidIO.h"
#include<QDebug>
#include <windows.h>
#include <QThread>
#include <QFile>
#include<QThread>
#include<QCoreApplication>
#define DMA_BUF_LEN					(4 * 1024 * 1024)

//存储通道0接收buf
ViUInt8 device0_rxbuf_ch0[4 * 1024 * 1024];
ViUInt32 device0_rxbuf_ch0_len = 0;
unsigned int device0_rxbuf_ch0_times = 0;
//存储通道1接收buf
ViUInt8 device0_rxbuf_ch1[4 * 1024 * 1024];
ViUInt32 device0_rxbuf_ch1_len = 0;
unsigned int device0_rxbuf_ch1_times = 0;

SYSTEMTIME sys;
char FileName0_0[100];
char FileName0_1[100];
FILE *pFile0_0;
FILE *pFile0_1;

DWORD device0_td = 0;
unsigned int sleepnum1 = 0;

//Save data thread
HANDLE device0_data_receive_thread = INVALID_HANDLE_VALUE;
UINT device0_data_receive_enable = 0;

int status = 0;

FILE *pFile0_tx_ch0;
FILE *pFile0_tx_ch1;

unsigned int device0_ch0_length_error_times;
unsigned int device0_ch1_length_error_times;

int msrio_vi= -1;

CardCtrl_RapidIO::CardCtrl_RapidIO()
{
    srio_succ=-1;
}
CardCtrl_RapidIO::~CardCtrl_RapidIO() {
    if(srio_succ==0)
    {
        PA_PCIe_3401_SRIO_Close(msrio_vi);
    }
}

//demo接收线程
DWORD __stdcall device0_dmadata_savedata(PVOID param)
{
    int device = 0;
    device = *((unsigned int*)param);
    while (device0_data_receive_enable != 1)
    {

        device0_rxbuf_ch0_len = (4 * 1024 * 1024);
        status = PA_PCIe_3401_SRIO_Receive(device, 0, device0_rxbuf_ch0, &device0_rxbuf_ch0_len);
        if (device0_rxbuf_ch0_len != 0)
        {
            if (device0_rxbuf_ch0_len != DMA_BUF_LEN)
            {
                device0_ch0_length_error_times++;
            }

            fwrite(&device0_rxbuf_ch0, sizeof(UCHAR), device0_rxbuf_ch0_len, pFile0_0);

            device0_rxbuf_ch0_times++;
        }

        device0_rxbuf_ch1_len = (4 * 1024 * 1024);
        status = PA_PCIe_3401_SRIO_Receive(device, 1, device0_rxbuf_ch1, &device0_rxbuf_ch1_len);
        if (device0_rxbuf_ch1_len != 0)
        {
            if (device0_rxbuf_ch1_len != DMA_BUF_LEN)
            {
                device0_ch1_length_error_times++;
            }

            fwrite(&device0_rxbuf_ch1, sizeof(UCHAR), device0_rxbuf_ch1_len, pFile0_1);

            device0_rxbuf_ch1_times++;
        }
    }

    device0_data_receive_enable = 0;

    return 0;
}


//初始Rapidio化板块
int CardCtrl_RapidIO::Init_PapidIO()
{

    ViStatus status = PA_SUCCESS;
    ViSession vi = 0;
    PA_SRIO_NWRITEPAMETER nwrpameter;

    status = PA_PCIe_3401_SRIO_Init(&vi);
    srio_succ=status;
    if(status!=0)
    {
        //qDebug()<<"RapidIO Init Field！";
        return -1;
    }
    msrio_vi=vi;

    status = PA_PCIe_3401_SRIO_LoopEn(vi, LOOP_OFF);//自回环标志 LOOP_ON/LOOP_OFF

    //Sleep(100);

    //每通道设置运行CPU的核
    status = PA_PCIe_3401_SRIO_SetRxAffinity(vi, 0, 2);
    status = PA_PCIe_3401_SRIO_SetRxAffinity(vi, 1, 3);

    //每通道设置超时时间400
    //for (int ch = 0; ch < CH_NUM; ch++)
    //{
    //	status = PA_PCIe_3401_TLK2711_SetRxTimeOut(device0, ch, 400);
    //}

    //每通道分配256M数据缓存空间
    for (int ch = 0; ch < 2; ch++)
    {
        status = PA_PCIe_3401_SRIO_PreAllocRxBuffer(vi, ch, 256);
    }

    nwrpameter.NwriteDestAddr = 0x20;
    nwrpameter.NwriteType = 0x0;
    nwrpameter.NwriteSourceAddr_L = 0x03000000;
    nwrpameter.NwriteSourceAddr_H = 0x0;
    nwrpameter.NwritePackageLen = 0x20;

    //设置NWR发送的参数
    status = PA_PCIe_3401_SRIO_SetNwriteParam(vi, CH_2X_0, nwrpameter);
    status = PA_PCIe_3401_SRIO_SetNwriteParam(vi, CH_2X_1, nwrpameter);

    //设置接收的使能（在线程收数中开启）
    status = PA_PCIe_3401_SRIO_EnableReceive(vi, CH_2X_0, 1);
    status = PA_PCIe_3401_SRIO_EnableReceive(vi, CH_2X_1, 1);

    //设置NWR发送的使能
    status = PA_PCIe_3401_SRIO_EnableSend(vi, CH_2X_0, 1);
    status = PA_PCIe_3401_SRIO_EnableSend(vi, CH_2X_1, 1);


    Sleep(100);//必须延时,不然初始化报错

    return PA_SUCCESS;
}


//文件发送线程
int CardCtrl_RapidIO::Send_qtSrio(QString strpth, bool ad0, bool ad1, DC_test dc_test)
{
    //测试
//    for(int n=0;n<100;n++)
//    {
//        qDebug()<<n;
//    }
    int status = 0;
    //打开文件
    if(strpth.isEmpty())
    {
        emit qthfinish(status);
        return 0 ;
    }
    QFile* binFile = new QFile("");
    binFile->setFileName(strpth);
    if(binFile->open(QFile::ReadOnly)){
    }
    else{
    }
    //发送数据
    int fLen = binFile->size();
    char buff[1024] = {0};
    RapidIO_STR t_str;
    int farmecnt = (fLen + 1023) / 1024;
    for(int n = 0; n < farmecnt; n++)
    {
        memset(&t_str,0,sizeof (t_str));
        memset(buff,0,sizeof(buff));
        binFile->read((char*)buff,sizeof(buff));//超过长度不读取，是默认值
        //同步头0xeb905716
        //t_str.head=0x165790EB;
        t_str.head = 0xEB905716;
        //（主导头）。。。。。
        //分组标志
        if(n == 0)t_str.groupmark = 1;//头包
        else if(n == ((fLen + 1023) / 1024) - 1)t_str.groupmark = 2;//尾包
        else {
            t_str.groupmark = 0;//中间包
        }
        if(farmecnt==1)t_str.groupmark=3;//独立包
        //目的地址
        t_str.Rpartcode = dc_test.Rpartcode; //部位代码
        t_str.Rstartmark = dc_test.Rstartmark; //卫星标志
        t_str.Raddrtyp = dc_test.Raddrtyp;  //地址类型

        if(t_str.Raddrtyp == 17)
        {
            t_str.channelnum = dc_test.channelnum; //通道编号（1-12）
        }

        //序列计数
        t_str.ordercount = n;
        //（副导头）。。。。。
        //副导头类型
        t_str.subheadtyp = 0x12;
        //副导头长度
        t_str.subheadlen = 10;
        //有效数据长度1024
        //t_str.effectlen=qToBigEndian((ushort)1024);
        t_str.effectlen = 1024;
        //副导头内容
        t_str.subcontent = 0x011f;
        //数据区
        memcpy(t_str.datas,buff,sizeof (buff));
        //验证CRC校验(多字节高前低后发送)
        ushort* check = (ushort*)&t_str;
        auto crccal = CRC16(check,(sizeof (t_str)-2)/2);
        //t_str.crc=qToBigEndian(crccal);
        t_str.crc = crccal;
        //qDebug()<<n<<"0x"<<QString::number(crccal,16).toUpper();
        //发送（默认通道0，对于硬件2接口，通道1，对应硬件通道1接口）
        if(msrio_vi != -1)
        {
            if(ad0)status += PA_PCIe_3401_SRIO_Send(msrio_vi, CH_2X_0, (unsigned char*)&t_str, sizeof (RapidIO_STR));
            if(ad1)status += PA_PCIe_3401_SRIO_Send(msrio_vi, CH_2X_1, (unsigned char*)&t_str, sizeof (RapidIO_STR));
        }
        if(status != 0)
        {
            qDebug()<<"发送失败";
            break;
        }
        emit send_jxjd((n + 1) * 10000.00 / farmecnt);
    }
    //发送完成
    binFile->close();

    emit qthfinish(status);
    return  status;
}

//接收线程
void CardCtrl_RapidIO::Get_qtSrio(QFile* pfile_0,QFile* pfile_1)
{
    //线程文件测试
//    uchar arr[100];
//    for(uint i=0;i<sizeof(arr);i++)
//    {
//        arr[i]=i;
//    }
//    if(pfile_0->isOpen())pfile_0->write((char*)arr,sizeof (arr));
//    if(pfile_1->isOpen())pfile_1->write((char*)arr,sizeof (arr));

     //获取当前线程数量
//      qDebug()<<QCoreApplication::instance()->thread()->idealThreadCount();

    int device = msrio_vi;
    if(device==-1)return;

    Rec_flag=true;
    int status=0;
    int cnt0=0,cnt1=0;
    unsigned long rxbuf_ch0_len=(4 * 1024 * 1024);
    unsigned long rxbuf_ch1_len=(4 * 1024 * 1024);

    uchar* rxbuf_ch0=new uchar[4 * 1024 * 1024];
    uchar* rxbuf_ch1=new uchar[4 * 1024 * 1024];

//    status = PA_PCIe_3401_SRIO_EnableReceive(device, CH_2X_0, 1);//启停使能会乱数，开启接收会在缓存内
//    status = PA_PCIe_3401_SRIO_EnableReceive(device, CH_2X_1, 1);

    while (Rec_flag)
    {

        //qDebug()<<cnt0++;
        if(pfile_0->isOpen())
        {
            status = PA_PCIe_3401_SRIO_Receive(device, 0, rxbuf_ch0, &rxbuf_ch0_len);
            if (rxbuf_ch0_len != 0)//接收长度不为0
            {
                if (rxbuf_ch0_len != DMA_BUF_LEN)//不满一个缓存
                {
                    //device0_ch0_length_error_times++;
                }

                pfile_0->write((char*)rxbuf_ch0,rxbuf_ch0_len);

                cnt0++;
            }
        }

        if(pfile_1->isOpen())
        {
            status = PA_PCIe_3401_SRIO_Receive(device, 1, rxbuf_ch1, &rxbuf_ch1_len);
            if (rxbuf_ch1_len != 0)
            {
                if (rxbuf_ch1_len != DMA_BUF_LEN)
                {
                    //device0_ch1_length_error_times++;
                }

                pfile_1->write((char*)rxbuf_ch1,rxbuf_ch1_len);
                cnt1++;
            }
        }

    }


//    status = PA_PCIe_3401_SRIO_EnableReceive(device, CH_2X_0, 0);
//    status = PA_PCIe_3401_SRIO_EnableReceive(device, CH_2X_1, 0);

    delete [] rxbuf_ch0;
    delete [] rxbuf_ch1;
}



