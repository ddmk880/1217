#ifndef CARDCTRL_AD_OC_H
#define CARDCTRL_AD_OC_H

#include <QObject>
#include "include/PA_PCIe_1804.h"
#include<QTimer>
class CardCtrl_AD_OC : public QObject
{
    Q_OBJECT
public:
    explicit CardCtrl_AD_OC(QObject *parent = nullptr);
      ~CardCtrl_AD_OC();
    //demo代码
    void Demo_Card_AD_Init();
    //demo代码
    void Demo_Card_OC_Init();


    int Card_OC_Init();
    int Card_AD_Init();
    void OC_cotrl(int channel);
    QTimer* timer;

public:
    int m_vi;//板卡号
    bool oc_InitSuccess;
    bool ad_InitSuccess;

public slots:
    void AD_read();

signals:
    void Get_ADYc(double* Rxbuff,int Rxlen);//AD遥测

};

#endif // CARDCTRL_AD_OC_H
