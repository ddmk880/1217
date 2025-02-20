#ifndef SUBTRILLION_OVERNOTE_H
#define SUBTRILLION_OVERNOTE_H

#include <QWidget>
#include <Globel_Define.h>
#include <QTimer>
#include <QMap>
#include <QLabel>
#include "networker.h"
#include "PA_PCIe_1501.h"
#include "HardwareCtrl/CardCtrl_1553B.h"
#include <QStatusBar>
#include <QStandardItemModel>
#include<QTableWidgetItem>
#include<vector>
#include"xlsxdocument.h"
using namespace std;
using namespace QXlsx;
namespace Ui {
class subtrillion_overnote;
}


class subtrillion_overnote : public QWidget
{
    Q_OBJECT

public:
    explicit subtrillion_overnote(QWidget *parent = nullptr);
    ~subtrillion_overnote();
    QStatusBar *sBar=new QStatusBar(this);
    void get_jxjd(double value);
    void get_farme(uint frame);
    QStandardItemModel *models;
    uint toHex_uint(QString qstr);//qstring转16进制uint
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort
    QString Create_UpFile();// 创建暂存上注文件
    QString Create_922_UpFile(QString filesPath);// 创建暂存上注文件(加头尾)
    void Remove_oldFile();//删除上注中转文件
    void SendUP_1553OverOrder(int kind,uchar* data,int len);//总线注数指令
    void Public_Addorderlist(uchar *databuff, int buffLen, QString buffname,int kind);//发送到界面
    QString Over_files;
    QFile* Re_Pfile[4];//4个通道文件
    bool check_dj[5];//任务界面单机选择
signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);
    int send1(QString strpth,uchar ch,uint divce);//UDP上注
    int send_thre(QString strpth,uchar ch,uint divce,vector<int> frame);//UDP上注
    int send2(QString strpth, vector<int> frame, ushort rt, ushort sub,int ch);//1553上注
    int send_order(uchar* data , int Datalen, ushort rt, ushort sub,int addr);//1553上注界面指令
    void send_1553upStop();//结束1553上注

private:
    Ui::subtrillion_overnote *ui;
    // 设备句柄
    ViSession m_DevVi;
    // 当前通道号
    ViUInt8 m_Channel;
    // 传输对象
    NetWorker *m_NetWorker = nullptr;
    //  连接标志false-未连接，true-已连接
    bool m_NetConnectedFlag = false;
    //  接收定时器
    QTimer *m_RxTimer = nullptr;
    //  发送定时器
    QTimer *m_TxTimer = nullptr;

    // 发送记录数据
    QList<QByteArray> m_TxRecordDatas;
    uint64_t m_TxSumBytes = 0;  // 发送总字节数
    // 接收记录数据<通道号，通道数据>
    QMap<uchar, QList<QByteArray> >m_RxRecordDatas;
    uint64_t m_RxSumBytes = 0;  // 接收总字节数
    // 用于记录定时其已记录的接收数量
    QMap<uchar, uint> m_RxTimerSumMap;

    // 状态栏参数
    QLabel *workStatus = nullptr;
    QLabel *workRxSum = nullptr;
    QLabel *workTxSum = nullptr;
    

private slots:
    void slot_RxTimerOut();
    void slot_TxTimerOut();
    void slot_GetRecvDatas(uchar ch, uchar* buffer,uint len);
    void on_pushButton_ConnectNet_clicked();
    void on_pushButton_SaveRecord_clicked();
    void on_pushButton_ClearRxRecord_clicked();
    void on_checkBox_TimerSend_clicked(bool checked);
    void on_pushButton_ClearTxRecord_clicked();
    void on_pushButton_NetConfig_clicked();
    void on_pushButton_NetSend_clicked();

    void on_pushButton_SumFileRead_clicked();

    void on_pushButton_muchFileSend_clicked();

    void on_pushButton_clearfileChoose_clicked();

    void on_cB_change_sendus_activated(int index);

    void on_pB_startUP_clicked();

    void on_pB_endUP_clicked();

    void on_pushButton_creatoverfile_clicked();

    void on_pB_threadframe_clicked();

    void on_pB_choosepackUP_clicked();

    void on_pushButton_rePath_clicked();

    void on_pushButton_reStart_clicked();

    void on_pushButton_reEnd_clicked();

    void on_comboBox_3_activated(int index);

    void on_pushButton_chooseDivision_clicked();

    void on_pB_xlsx_dat_clicked();

    void on_pB_chooseUpFile_clicked();

    void on_pB_xlsx_dat2_clicked();

protected:
    void InitUI();
    QString QByteArrayToHex(QByteArray data);
    QString QByteArrayToAscii(QByteArray data);
    QByteArray HexStrToQByteArray(QString hex);
    QByteArray AsciiStrToQByteArray(QString ascii);
    QLabel *AddStatusWidget(QString name, QString value);
};


class File_sendQthread : public QObject
{
    Q_OBJECT

public:
    explicit File_sendQthread(QObject *parent = nullptr);
    ~File_sendQthread();
    int send_UDP(QString strpth,uchar ch,uint divce);//udp上注
    int sendThr_UDP(QString strpth,uchar ch,uint divce,vector<int> up_frame);//udp丢帧上注
    //微秒级别定时器
    int USleep(int us);


signals:
    void Add_Order_ToList(QVariant varData);
    void send_qzjxjd(double value);
    void send_frame(uint cnt);
    void success_snack(QString str);


};

#endif // SUBTRILLION_OVERNOTE_H
