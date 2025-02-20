#include "CardCtrl_AD_OC.h"
#include <windows.h>
#include<QDebug>


CardCtrl_AD_OC::CardCtrl_AD_OC(QObject *parent) : QObject(parent)
{
    m_vi=0;
    oc_InitSuccess=false;
    ad_InitSuccess=false;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AD_read()));//指令定时发送
    //timer->start(1000);
}

CardCtrl_AD_OC::~CardCtrl_AD_OC()
{

    if(oc_InitSuccess)
    {

        PA_PCIe_1804_OC_Close(m_vi);
        //printf("Close OC!\n");
    }
    if(ad_InitSuccess)
    {
        PA_PCIe_1804_AD_Close(m_vi);

    }
    if(oc_InitSuccess&&ad_InitSuccess)
    {
        PA_PCIe_1804_Close(m_vi);
        printf("AD_OC Close!\n");
    }
    if(timer->isActive())
    {
        timer->stop();
    }
    timer->deleteLater();

}

//demo
void CardCtrl_AD_OC::Demo_Card_AD_Init()
{
    int device0 = 0;
    ViStatus status = PA_SUCCESS;
    ViSession vi = 0;
    ViReal64 adcvalue = 0.0;
    ViChar c = 0;

    //初始化模块
    device0 = PA_PCIe_1804_Init(&vi);

    //初始化AD接口
    status = PA_PCIe_1804_AD_Init(&vi);

    //设置所有AD接口量程为±5V
    for (int i = 0; i < PA_1804_AD_MAX_CHANNEL; i++)
    {
        status = PA_PCIe_1804_AD_SetRange(vi, i, PA_AD_RANGE_5V);
    }

    printf("Start Read ADC Value!.\n");
    //读取所有AD接口电压
    do
    {
        scanf("%c", &c);

        if (c != 'Q')
        {
            for (int i = 0; i < PA_1804_AD_MAX_CHANNEL; i++)
            {
                Sleep(1000);
                status = PA_PCIe_1804_AD_GetValue(vi, i, &adcvalue);
                printf("AD Channle%02d Voltage is %f\n", i, adcvalue);
            }
        }
    }while (c != 'Q');

    status = PA_PCIe_1804_AD_Close(vi);
    printf("Close!\n");

    return ;
}
//demo
void CardCtrl_AD_OC::Demo_Card_OC_Init()
{
    int device0 = 0;
    ViStatus status = PA_SUCCESS;
    ViSession vi = 0;
    char c = 0;
    ViUInt32 channeltx = 0;

    //初始化模块
    device0 = PA_PCIe_1804_Init(&vi);

    //初始化OC接口
    status = PA_PCIe_1804_OC_Init(&vi);

    //设置OC接口工作在单次脉冲
    status += PA_PCIe_1804_OC_SetPulseMode(vi, channeltx, PA_PULSEMODE_SINGLE);

    //设置OC接口输出脉冲为负极性，脉宽单位为ms，脉冲大小为160ms
    status += PA_PCIe_1804_OC_SetPulseOut(vi, channeltx, PA_LEVEL_LOW, PA_PRECISION_MS, 80, 1000);

    status += PA_PCIe_1804_OC_EnableSend(vi, channeltx, PA_ENABLE);

    printf("Start OC pluse!.\n");
    if(status!=0)return;
    do
    {
        printf("Input A to send OC pluse.\n");
        scanf("%c", &c);

        if (c == 'A')
        {
            //通道输出单次脉冲
            status += PA_PCIe_1804_OC_SendSinglePulse(vi, channeltx);
        }
    }
    while (c != 'Q');

    status += PA_PCIe_1804_OC_EnableSend(vi, channeltx, PA_DISABLE);

    status = PA_PCIe_1804_OC_Close(vi);
    printf("Close OC!\n");

    status = PA_PCIe_1804_Close(vi);
    printf("Close!\n");
    return ;
}

int CardCtrl_AD_OC::Card_OC_Init()
{
    int device0 = 0;
    ViStatus status = PA_SUCCESS;
    ViSession vi = 0;

    //初始化模块
    device0 = PA_PCIe_1804_Init(&vi);
    m_vi=vi;
    if(device0!=0)
    {
        //qDebug()<<"OCcard Init Field！";
        return -1;
    }
    //初始化OC接口
    status = PA_PCIe_1804_OC_Init(&vi);
    oc_InitSuccess=true;
    return PA_SUCCESS;
}

int CardCtrl_AD_OC::Card_AD_Init()
{
    ViStatus status = PA_SUCCESS;
    ViSession vi = 0;

    //初始化模块(AD跟OC一张卡)
    if(oc_InitSuccess==false)status = PA_PCIe_1804_Init(&vi);

    //初始化AD接口
    status += PA_PCIe_1804_AD_Init(&vi);

    if(status!=PA_SUCCESS)
    {
        return -1;
    }
    //设置所有AD接口量程为±5V
    for (int i = 0; i < PA_1804_AD_MAX_CHANNEL; i++)
    {
        status += PA_PCIe_1804_AD_SetRange(vi, i, PA_AD_RANGE_5V);
    }

    ad_InitSuccess=true;
    timer->start(2000);//2秒读取AD电压值
    return status;


}

void CardCtrl_AD_OC::OC_cotrl(int channel)
{
    ViStatus status = PA_SUCCESS;
    ViSession vi = m_vi;
    ViUInt32 channeltx = channel;
    if(channel>16)return;

    //设置OC接口工作在单次脉冲
    status += PA_PCIe_1804_OC_SetPulseMode(vi, channeltx, PA_PULSEMODE_SINGLE);

    //设置OC接口输出脉冲为负极性，脉宽单位为ms，脉冲大小为160ms
    status += PA_PCIe_1804_OC_SetPulseOut(vi, channeltx, PA_LEVEL_LOW, PA_PRECISION_MS, 160, 1000);

    status += PA_PCIe_1804_OC_EnableSend(vi, channeltx, PA_ENABLE);

    printf("Start OC pluse!.\n");
    if(status!=0)return;

    //通道输出单次脉冲
    status += PA_PCIe_1804_OC_SendSinglePulse(vi, channeltx);

    //status += PA_PCIe_1804_OC_EnableSend(vi, channeltx, PA_DISABLE);


    return ;
}

void CardCtrl_AD_OC::AD_read()
{
    //for (int i = 0; i < PA_1804_AD_MAX_CHANNEL; i++)

    double elec[16]={0.0};//一台单机4路，4台16路
    for (int i = 0; i < 16; i++)
    {
        Sleep(1);
        PA_PCIe_1804_AD_GetValue(m_vi, i, &elec[i]);
    }
//    elec[0]=0.131;
//    elec[1]=2.03231;
//    elec[2]=0.133;
//    elec[3]=1.98655656;
//    elec[4]=0.135;
//    elec[5]=0.136;
//    elec[6]=0.137;
//    elec[7]=0.138;
//    elec[8]=0.139;
//    elec[9]=0.141;
//    elec[10]=0.42;
//    elec[11]=0.143;

    emit Get_ADYc(elec,16);
}







