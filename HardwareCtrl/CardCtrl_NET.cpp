#include "CardCtrl_NET.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <process.h>

ViSession g_vi;

bool g_bRecvFlag1 = false;
bool g_bRecvFlag2 = false;
bool g_bRecvFlag3 = false;
bool g_bRecvFlag4 = false;

HANDLE g_recvHandle1;
HANDLE g_recvHandle2;
HANDLE g_recvHandle3;
HANDLE g_recvHandle4;
unsigned int __stdcall recvThraed1(LPVOID param);   // 读取消息线程
unsigned int __stdcall recvThraed2(LPVOID param);   // 读取消息线程
unsigned int __stdcall recvThraed3(LPVOID param);   // 读取消息线程
unsigned int __stdcall recvThraed4(LPVOID param);   // 读取消息线程

const int g_channel0 = 0;  // 通道0
const int g_channel1 = 1;  // 通道1
const int g_channel2 = 2;  // 通道2
const int g_channel3 = 3;  // 通道3

#define BUFFER_SIZE  0x400000  // 4MB

CardCtrl_NET::CardCtrl_NET(QObject *parent) : QObject(parent)
{
    //Init_MainNet();

}

CardCtrl_NET::~CardCtrl_NET()
{
    qDebug()<<"exit";

    PA_PCIe_1501_NET_Close(g_vi);

}

int CardCtrl_NET::Init_Net()
{
    ViStatus status = PA_SUCCESS;
    char c;
    ViUInt8 udpdata[1024];
    ViUInt32 udplen = 20;

    status = PA_PCIe_1501_NET_Init(&g_vi);
    if (status != PA_SUCCESS)
    {
        printf("初始化失败!\n");
        return -1;
    }
    //PA_PCIe_1501_NET_LoopEn(g_vi, PA_ENABLE);

    TPA_NETParam paramChannel0;
    paramChannel0.LocalIp[3] = 192, paramChannel0.LocalIp[2] = 168, paramChannel0.LocalIp[1] = 0, paramChannel0.LocalIp[0] = 130;
    paramChannel0.LocalMac[5] = 0x7c, paramChannel0.LocalMac[4] = 0xc2, paramChannel0.LocalMac[3] = 0x55, paramChannel0.LocalMac[2] = 0x10, paramChannel0.LocalMac[1] = 0xcc, paramChannel0.LocalMac[0] = 0xb6;  // Mac: 8c8caa44e880
    paramChannel0.RemoteIp[3] = 192, paramChannel0.RemoteIp[2] = 168, paramChannel0.RemoteIp[1] = 0, paramChannel0.RemoteIp[0] = 131;
    paramChannel0.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel0.LocalPort = 1000;
    paramChannel0.RemotePort = 2000;

    TPA_NETParam paramChannel1;
    paramChannel1.LocalIp[3] = 192, paramChannel1.LocalIp[2] = 168, paramChannel1.LocalIp[1] = 0, paramChannel1.LocalIp[0] = 131;
    paramChannel1.LocalMac[5] = 0x7c, paramChannel1.LocalMac[4] = 0xc2, paramChannel1.LocalMac[3] = 0x55, paramChannel1.LocalMac[2] = 0x10, paramChannel1.LocalMac[1] = 0xcc, paramChannel1.LocalMac[0] = 0xb5;  // Mac: 8c8caa44e880
    paramChannel1.RemoteIp[3] = 192, paramChannel1.RemoteIp[2] = 168, paramChannel1.RemoteIp[1] = 0, paramChannel1.RemoteIp[0] = 130;
    paramChannel1.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel1.LocalPort = 2000;
    paramChannel1.RemotePort = 1000;

    TPA_NETParam paramChannel2;
    paramChannel2.LocalIp[3] = 192, paramChannel2.LocalIp[2] = 168, paramChannel2.LocalIp[1] = 0, paramChannel2.LocalIp[0] = 132;
    paramChannel2.LocalMac[5] = 0x7c, paramChannel2.LocalMac[4] = 0xc2, paramChannel2.LocalMac[3] = 0x55, paramChannel2.LocalMac[2] = 0x10, paramChannel2.LocalMac[1] = 0xcc, paramChannel2.LocalMac[0] = 0xb4;  // Mac: 8c8caa44e880
    paramChannel2.RemoteIp[3] = 192, paramChannel2.RemoteIp[2] = 168, paramChannel2.RemoteIp[1] = 0, paramChannel2.RemoteIp[0] = 133;
    paramChannel2.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel2.LocalPort = 3000;
    paramChannel2.RemotePort = 4000;

    TPA_NETParam paramChannel3;
    paramChannel3.LocalIp[3] = 192, paramChannel3.LocalIp[2] = 168, paramChannel3.LocalIp[1] = 0, paramChannel3.LocalIp[0] = 133;
    paramChannel3.LocalMac[5] = 0x7c, paramChannel3.LocalMac[4] = 0xc2, paramChannel3.LocalMac[3] = 0x55, paramChannel3.LocalMac[2] = 0x10, paramChannel3.LocalMac[1] = 0xcc, paramChannel3.LocalMac[0] = 0xb3;  // Mac: 8c8caa44e880
    paramChannel3.RemoteIp[3] = 192, paramChannel3.RemoteIp[2] = 168, paramChannel3.RemoteIp[1] = 0, paramChannel3.RemoteIp[0] = 132;
    paramChannel3.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel3.LocalPort = 4000;
    paramChannel3.RemotePort = 3000;

    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel0, paramChannel0);  // 配置参数
    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel1, paramChannel1);  // 配置参数
    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel2, paramChannel2);  // 配置参数
    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel3, paramChannel3);  // 配置参数
    if (status != PA_SUCCESS)
    {
        printf("配置参数失败!\n");
        return -1;
    }

    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel0, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel0, PA_ENABLE);	// 打开接收使能
    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel1, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel1, PA_ENABLE);	// 打开接收使能
    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel2, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel2, PA_ENABLE);	// 打开接收使能
    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel3, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel3, PA_ENABLE);	// 打开接收使能

    char file1[9] = "ret1.bin";
    char file2[9] = "ret2.bin";
    char file3[9] = "ret3.bin";
    char file4[9] = "ret4.bin";

    g_bRecvFlag1 = true;
    g_recvHandle1 = (HANDLE)_beginthreadex(0, 0, &recvThraed1, (void*)file1, 0, 0);
    g_bRecvFlag2 = true;
    g_recvHandle2 = (HANDLE)_beginthreadex(0, 0, &recvThraed2, (void*)file2, 0, 0);
    g_bRecvFlag3 = true;
    g_recvHandle3 = (HANDLE)_beginthreadex(0, 0, &recvThraed3, (void*)file3, 0, 0);
    g_bRecvFlag4 = true;
    g_recvHandle4 = (HANDLE)_beginthreadex(0, 0, &recvThraed4, (void*)file4, 0, 0);

    printf("Start UDP message!.\n");
    do
    {
        printf("Input A to send UDP message.\n");
        scanf("%c", &c);

        // Send the Aperiodic message.
        if (c == 'A')
        {
            for (uint i = 0; i < udplen; i++)
            {
                udpdata[i] = (i & 0xFF);
            }

            status = PA_PCIe_1501_NET_Send(g_vi, g_channel0, udpdata, udplen);
            Sleep(1000);
            status = PA_PCIe_1501_NET_Send(g_vi, g_channel1, udpdata, udplen);
            Sleep(1000);
            status = PA_PCIe_1501_NET_Send(g_vi, g_channel2, udpdata, udplen);
            Sleep(1000);
            status = PA_PCIe_1501_NET_Send(g_vi, g_channel3, udpdata, udplen);
            Sleep(1000);

            if (status == PA_SUCCESS)
            {
                printf("发送成功");
            }
            else
            {
                printf("发送失败");
            }
        } // End of if (c == 'A')
    } while (c != 'Q'); // End of do-while

    g_bRecvFlag1 = false;
    g_bRecvFlag2 = false;
    g_bRecvFlag3 = false;
    g_bRecvFlag4 = false;
    WaitForSingleObject(g_recvHandle1, INFINITE);
    WaitForSingleObject(g_recvHandle2, INFINITE);
    WaitForSingleObject(g_recvHandle3, INFINITE);
    WaitForSingleObject(g_recvHandle4, INFINITE);

    status = PA_PCIe_1501_NET_Close(g_vi);

    return 0;
}


unsigned int __stdcall recvThraed1(LPVOID param)
{
    char* filename = (char*)param;
    FILE* fp = NULL;
    fopen_s(&fp, filename, "wb+");

    unsigned char* buffer = new unsigned char[BUFFER_SIZE];
    while (g_bRecvFlag1)
    {
        unsigned long len = 0;
        PA_PCIe_1501_NET_Receive(g_vi, g_channel0, buffer, BUFFER_SIZE, &len);
        if (len == 0)
        {
            continue;
        }
        else
        {
            fwrite(buffer, 1, len, fp);
            printf("通道1接收到数据.\n");
        }
    }

    delete[] buffer;
    fclose(fp);

    _endthreadex(0);
    return 0;
}

unsigned int __stdcall recvThraed2(LPVOID param)
{
    char* filename = (char*)param;
    FILE* fp = NULL;
    fopen_s(&fp, filename, "wb+");

    unsigned char* buffer = new unsigned char[BUFFER_SIZE];
    while (g_bRecvFlag2)
    {
        unsigned long len = 0;
        PA_PCIe_1501_NET_Receive(g_vi, g_channel1, buffer, BUFFER_SIZE, &len);
        if (len == 0)
        {
            continue;
        }
        else
        {
            fwrite(buffer, 1, len, fp);
            printf("通道2接收到数据.\n");
        }
    }

    delete[] buffer;
    fclose(fp);

    _endthreadex(0);
    return 0;
}

unsigned int __stdcall recvThraed3(LPVOID param)
{
    char* filename = (char*)param;
    FILE* fp = NULL;
    fopen_s(&fp, filename, "wb+");

    unsigned char* buffer = new unsigned char[BUFFER_SIZE];
    while (g_bRecvFlag3)
    {
        unsigned long len = 0;
        PA_PCIe_1501_NET_Receive(g_vi, g_channel2, buffer, BUFFER_SIZE, &len);
        if (len == 0)
        {
            continue;
        }
        else
        {
            fwrite(buffer, 1, len, fp);
            printf("通道3接收到数据.\n");
        }
    }

    delete[] buffer;
    fclose(fp);

    _endthreadex(0);
    return 0;
}

unsigned int __stdcall recvThraed4(LPVOID param)
{
    char* filename = (char*)param;
    FILE* fp = NULL;
    fopen_s(&fp, filename, "wb+");

    unsigned char* buffer = new unsigned char[BUFFER_SIZE];
    while (g_bRecvFlag4)
    {
        unsigned long len = 0;
        PA_PCIe_1501_NET_Receive(g_vi, g_channel3, buffer, BUFFER_SIZE, &len);
        if (len == 0)
        {
            continue;
        }
        else
        {
            fwrite(buffer, 1, len, fp);
            printf("通道4接收到数据.\n");
        }
    }

    delete[] buffer;
    fclose(fp);

    _endthreadex(0);
    return 0;
}

int CardCtrl_NET::Init_MainNet()
{

    ViStatus status = PA_SUCCESS;
    char c;
    ViUInt8 udpdata[1024];
    ViUInt32 udplen = 20;

    status = PA_PCIe_1501_NET_Init(&g_vi);
    if (status != PA_SUCCESS)
    {
        printf("初始化失败!\n");
        return -1;
    }
    //PA_PCIe_1501_NET_LoopEn(g_vi, PA_ENABLE);

    TPA_NETParam paramChannel0;
    paramChannel0.LocalIp[3] = 192, paramChannel0.LocalIp[2] = 168, paramChannel0.LocalIp[1] = 0, paramChannel0.LocalIp[0] = 130;
    paramChannel0.LocalMac[5] = 0x7c, paramChannel0.LocalMac[4] = 0xc2, paramChannel0.LocalMac[3] = 0x55, paramChannel0.LocalMac[2] = 0x10, paramChannel0.LocalMac[1] = 0xcc, paramChannel0.LocalMac[0] = 0xb6;  // Mac: 8c8caa44e880
    paramChannel0.RemoteIp[3] = 192, paramChannel0.RemoteIp[2] = 168, paramChannel0.RemoteIp[1] = 0, paramChannel0.RemoteIp[0] = 131;
    paramChannel0.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel0.LocalPort = 1000;
    paramChannel0.RemotePort = 2000;

    TPA_NETParam paramChannel1;
    paramChannel1.LocalIp[3] = 192, paramChannel1.LocalIp[2] = 168, paramChannel1.LocalIp[1] = 0, paramChannel1.LocalIp[0] = 131;
    paramChannel1.LocalMac[5] = 0x7c, paramChannel1.LocalMac[4] = 0xc2, paramChannel1.LocalMac[3] = 0x55, paramChannel1.LocalMac[2] = 0x10, paramChannel1.LocalMac[1] = 0xcc, paramChannel1.LocalMac[0] = 0xb5;  // Mac: 8c8caa44e880
    paramChannel1.RemoteIp[3] = 192, paramChannel1.RemoteIp[2] = 168, paramChannel1.RemoteIp[1] = 0, paramChannel1.RemoteIp[0] = 130;
    paramChannel1.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel1.LocalPort = 2000;
    paramChannel1.RemotePort = 1000;

    TPA_NETParam paramChannel2;
    paramChannel2.LocalIp[3] = 192, paramChannel2.LocalIp[2] = 168, paramChannel2.LocalIp[1] = 0, paramChannel2.LocalIp[0] = 132;
    paramChannel2.LocalMac[5] = 0x7c, paramChannel2.LocalMac[4] = 0xc2, paramChannel2.LocalMac[3] = 0x55, paramChannel2.LocalMac[2] = 0x10, paramChannel2.LocalMac[1] = 0xcc, paramChannel2.LocalMac[0] = 0xb4;  // Mac: 8c8caa44e880
    paramChannel2.RemoteIp[3] = 192, paramChannel2.RemoteIp[2] = 168, paramChannel2.RemoteIp[1] = 0, paramChannel2.RemoteIp[0] = 133;
    paramChannel2.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel2.LocalPort = 3000;
    paramChannel2.RemotePort = 4000;

    TPA_NETParam paramChannel3;
    paramChannel3.LocalIp[3] = 192, paramChannel3.LocalIp[2] = 168, paramChannel3.LocalIp[1] = 0, paramChannel3.LocalIp[0] = 133;
    paramChannel3.LocalMac[5] = 0x7c, paramChannel3.LocalMac[4] = 0xc2, paramChannel3.LocalMac[3] = 0x55, paramChannel3.LocalMac[2] = 0x10, paramChannel3.LocalMac[1] = 0xcc, paramChannel3.LocalMac[0] = 0xb3;  // Mac: 8c8caa44e880
    paramChannel3.RemoteIp[3] = 192, paramChannel3.RemoteIp[2] = 168, paramChannel3.RemoteIp[1] = 0, paramChannel3.RemoteIp[0] = 132;
    paramChannel3.Baud = PA_NET_BAUD_1000M; // 速率1000MB
    paramChannel3.LocalPort = 4000;
    paramChannel3.RemotePort = 3000;

    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel0, paramChannel0);  // 配置参数
    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel1, paramChannel1);  // 配置参数
    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel2, paramChannel2);  // 配置参数
    status = PA_PCIe_1501_NET_SetParam(g_vi, g_channel3, paramChannel3);  // 配置参数
    if (status != PA_SUCCESS)
    {
        printf("配置参数失败!\n");
        return -1;
    }

    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel0, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel0, PA_ENABLE);	// 打开接收使能
    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel1, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel1, PA_ENABLE);	// 打开接收使能
    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel2, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel2, PA_ENABLE);	// 打开接收使能
    status = PA_PCIe_1501_NET_EnableSend(g_vi, g_channel3, PA_ENABLE);		// 打开发送使能
    status = PA_PCIe_1501_NET_EnableReceive(g_vi, g_channel3, PA_ENABLE);	// 打开接收使能

    char file1[9] = "ret1.bin";
    char file2[9] = "ret2.bin";
    char file3[9] = "ret3.bin";
    char file4[9] = "ret4.bin";

    return 0;

}

Rec_QThread1::Rec_QThread1(QObject *parent) : QObject(parent)
{

}

int Rec_QThread1::Rec_working1(QString path)
{
    qDebug()<<path<<"线程rec1地址："<<QThread::currentThread();
    return 0;
}

Rec_QThread2::Rec_QThread2(QObject *parent) : QObject(parent)
{


}

int Rec_QThread2::Rec_working2(QString path)
{

    qDebug()<<path<<"线程rec2地址："<<QThread::currentThread();
    return 0;
}

Rec_QThread3::Rec_QThread3(QObject *parent) : QObject(parent)
{

}

int Rec_QThread3::Rec_working3(QString path)
{

    qDebug()<<path<<"线程rec3地址："<<QThread::currentThread();
    return 0;
}

Rec_QThread4::Rec_QThread4(QObject *parent) : QObject(parent)
{

}

int Rec_QThread4::Rec_working4(QString path)
{
    qDebug()<<path<<"线程rec4地址："<<QThread::currentThread();
    return 0;
}






