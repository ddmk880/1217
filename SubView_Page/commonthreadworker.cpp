#include "commonthreadworker.h"
#include <QMessageBox>

CommonThreadWorker::CommonThreadWorker(QObject *parent) : QObject(parent)
{
    CreateWorkThread();
}

CommonThreadWorker::~CommonThreadWorker()
{
    if(m_Thread != nullptr)
    {
        Stop();
        delete m_Thread;
        m_Thread = nullptr;
    }
}
/*****************
功能：开始线程
作者：lengyuanjin
*****************/
bool CommonThreadWorker::Start()
{
    if(m_RunFlag)
    {
        QMessageBox::warning(nullptr, "提示", "请先停止.");
        return false;
    }
    if(!InitParams())
    {
        return false;
    }
    m_RunFlag = true;
    m_PauseFlag = false;
    m_Thread->start();
    emit signal_startThread();
    return true;
}
/*****************
功能：停止线程
作者：lengyuanjin
*****************/
bool CommonThreadWorker::Stop()
{    
    m_RunFlag = false;
    if(m_Thread != nullptr)
    {
        m_Thread->quit();
        m_Thread->wait();
    }
    if(!RelieveParams())
    {
        return false;
    }
    emit signal_stopThread();
    return true;
}
/*****************
功能：暂停线程
作者：lengyuanjin
*****************/
bool CommonThreadWorker::Pause()
{
    if(m_Thread == nullptr)
    {
        return false;
    }
    // 继续线程
    m_PauseFlag = true;
    emit signal_pauseThread();
    return true;
}
/*****************
功能：继续线程
作者：lengyuanjin
*****************/
bool CommonThreadWorker::Go()
{
    if(m_Thread == nullptr)
    {
        return false;
    }
    // 继续线程
    m_PauseFlag = false;
    emit signal_goThread();
    return true;
}
/*****************
功能：初始化参数
作者：lengyuanjin
*****************/
bool CommonThreadWorker::InitParams()
{
    return true;
}
/*****************
功能：解除参数
作者：lengyuanjin
*****************/
bool CommonThreadWorker::RelieveParams()
{
    return true;
}
/*****************
功能：创建线程
作者：lengyuanjin
*****************/
void CommonThreadWorker::CreateWorkThread()
{
    // 重新创建线程
    if(m_Thread == nullptr)
    {
        // 创建线程
        m_Thread = new QThread();
        // 将模块移动到新的线程
        moveToThread(m_Thread);
        connect(this, SIGNAL(signal_startThread()), this, SLOT(slot_Thread()));
    }
}
/*****************
功能：线程处理函数
作者：lengyuanjin
*****************/
void CommonThreadWorker::slot_Thread()
{
    // 线程循环
    while(m_RunFlag)
    {
        // true表示暂停，则不处理数据
        if(m_PauseFlag)
        {
            continue;
        }
        ThreadRun();    // 处理数据
    }
}
