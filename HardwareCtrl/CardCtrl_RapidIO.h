#ifndef CARDCTRL_RAPIDIO_H
#define CARDCTRL_RAPIDIO_H

#include <QObject>
#include <QVector>
#include"include/pa_pcie_3401.h"
#include"Globel_Define.h"
#include<QFileDialog>
extern int msrio_vi;//获取板卡号
class CardCtrl_RapidIO : public QObject{
    Q_OBJECT
public:
    CardCtrl_RapidIO();
    ~CardCtrl_RapidIO();


    int Init_PapidIO();//硬件初始化
    int Send_qtSrio(QString strpth, bool ad0, bool ad1, DC_test dc_test);//Srio发送线程
    void Get_qtSrio(QFile* pfile_0,QFile* pfile_1);//Srio接收线程
    bool Rec_flag;//线程接收标志
    int srio_succ;
signals:
    void qthfinish(int statu);
    void start_get();
    void send_jxjd(double value);

};

#endif // CARDCTRL_RAPIDIO_H
