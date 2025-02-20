#include "networker.h"
#include <QException>
#include <QDebug>

NetWorker::NetWorker(ViUInt32 vi,QObject *parent)
    :
      CommonThreadWorker(parent),
      m_DevVi(vi)
{

}

NetWorker::~NetWorker()
{
    //  关闭设备
    //PA_PCIe_1501_NET_Close(m_DevVi);
}
/*****************
功能：初始化设备
作者：lengyuanjin
*****************/
bool NetWorker::InitParams()
{
    m_SumBytes = 0;
    return true;
}
/*****************
功能：释放设备资源
作者：lengyuanjin
*****************/
bool NetWorker::RelieveParams()
{
    return true;
}

/*****************
功能：线程处理UDP数据
作者：lengyuanjin
*****************/
void NetWorker::ThreadRun()
{
    try
    {
        //ZeroMemory(m_RxBuffer, RX_BUFFER_MAX_LEN);
        ViUInt32 curRxLen = 0;
        // 4个通道
        for (ViUInt8  i = 0; i < 4; ++i)
        {
            PA_PCIe_1501_NET_Receive(m_DevVi, i, m_RxBuffer, RX_BUFFER_MAX_LEN, &curRxLen);
            if(curRxLen != 0)
            {
                m_SumBytes += curRxLen;
                emit signal_RecvDatas(i, m_RxBuffer, curRxLen);
            }
        }
    } catch (QException ex) {
        qDebug() << ex.what();
    }
}

/*****************
功能：网络连接
作者：lengyuanjin
*****************/
bool NetWorker::NetConnect()
{
    ViStatus status = 0;
    // 4个通道
    for (ViUInt8  i = 0; i < 4; ++i)
    {
        //  打开使能
        status += PA_PCIe_1501_NET_EnableSend(m_DevVi, i, 1);   // 发送使能
        status += PA_PCIe_1501_NET_EnableReceive(m_DevVi, i, 1);// 接收使能
    }

    if(status != 0)
    {
        return false;
    }
    return true;
}

/*****************
功能：网络断开
作者：lengyuanjin
*****************/
bool NetWorker::DisNetConnect()
{
    ViStatus status = 0;
    //  关闭使能
    // 4个通道
    for (ViUInt8  i = 0; i < 4; ++i)
    {
        status += PA_PCIe_1501_NET_EnableSend(m_DevVi, i, 0);     // 关闭发送使能
        status += PA_PCIe_1501_NET_EnableReceive(m_DevVi, i, 0);  // 关闭接收使能
    }
    if(status != 0)
    {
        return false;
    }
    return true;
}

/*****************
功能：数据发送
作者：lengyuanjin
*****************/
uint64_t NetWorker::NetSend(ViUInt8 ch, uchar *buffer, uint len)
{
    if(buffer == nullptr || len <= 0)
    {
        return 0;
    }
    uchar *sendBuf = new uchar[len];
    memcpy(sendBuf, buffer, len);

    ViStatus status = 0;
    status = PA_PCIe_1501_NET_Send(m_DevVi, ch, sendBuf, len);
    // 发送成功则添加总通信数据量
    if(status == 0)
    {
        m_SumBytes += len;
    }
    return len;
}

