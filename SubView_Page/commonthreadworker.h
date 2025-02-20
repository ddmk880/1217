#ifndef COMMONTHREADWORKER_H
#define COMMONTHREADWORKER_H
/*****************
功能：公共线程worker线程父类
作者：lengyuanjin
*****************/
#include <QThread>
#include <QVariant>

class CommonThreadWorker : public QObject
{
    Q_OBJECT
public:
    explicit CommonThreadWorker(QObject *parent = nullptr);
    ~CommonThreadWorker();
protected:
    QThread *m_Thread   = nullptr;  // 线程指针
    bool m_RunFlag      = false;    // 线程状态标识,true正在执行，false已停止执行
    bool m_PauseFlag    = false;    // 线程暂停标识，true暂停，false继续
public:
    virtual bool Start();   // 开始
    virtual bool Stop();    // 停止
    virtual bool Pause();   // 暂停
    virtual bool Go();      // 继续
protected:
    virtual bool InitParams();      // 界面参数初始化
    virtual bool RelieveParams();   // 界面参数释放
    virtual void ThreadRun() = 0;   // 线程数据处理函数
private:
    void CreateWorkThread();
public:
signals:
    void signal_startThread();          // 开始线程信号
    void signal_stopThread();           // 结束线程信号
    void signal_pauseThread();          // 暂停线程信号
    void signal_goThread();             // 继续线程信号
    void signal_error(QVariant param);  // 线程错误消息
private
    slots:
    void slot_Thread();                 // 线程处理函数
};

#endif // COMMONTHREADWORKER_H
