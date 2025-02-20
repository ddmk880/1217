#ifndef NETWORKER_H
#define NETWORKER_H

#include "commonthreadworker.h"
#include "PA_PCIe_1501.h"
#include <windows.h>

#define RX_BUFFER_MAX_LEN 4 * 1024 * 1024

class NetWorker : public CommonThreadWorker
{
    Q_OBJECT
public:
    NetWorker(ViUInt32 vi, QObject *parent = nullptr);
    ~NetWorker();
private:
    // 通道数据缓存
    uchar m_RxBuffer[RX_BUFFER_MAX_LEN] = {0};
    // 设备操作句柄
    ViUInt32 m_DevVi = 0;
    // 通道总数据量（字节）
    uint16_t m_SumBytes = 0;
protected:
    bool InitParams();
    bool RelieveParams();
    void ThreadRun();   // 线程数据处理函数
public:
    bool NetConnect();      // 网络连接
    bool DisNetConnect();   // 网络断开
    uint64_t NetSend(ViUInt8 ch, uchar *buffer, uint len);
signals:
    void signal_RecvDatas(uchar ch, uchar* buffer,uint len);
};

#endif // NETWORKER_H
