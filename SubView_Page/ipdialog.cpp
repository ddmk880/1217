#include "ipdialog.h"
#include "ui_ipdialog.h"
#include <QMessageBox>
#include <QValidator>

extern uint send_div;

IPDialog::IPDialog(ViSession &vi,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IPDialog),
    m_DevVi(vi)
{
    ui->setupUi(this);
    InitUI();
}

IPDialog::~IPDialog()
{
    delete ui;
}

void IPDialog::StringToUChar(QString str, unsigned char *recv)
{
    unsigned char i,j=0,k=0,sum=0,flag = 0;
    QByteArray ba = str.toLatin1();
    const char *char_t = ba.data();
    for(i=0;i<=ba.length();i++)
    {
        if((*char_t>='0')&&(*char_t<='9'))
        {
            flag = 1;
            k = (*char_t) - '0';//赋值
        }
        else {
            if(flag==1)
            {
                recv[j++]=sum;
            }
            //复位
            flag = 0;
            sum = 0;
        }
        if(flag == 1)
        {
            sum = sum*10;
            sum += k;
        }
        char_t++;
    }
}

int IPDialog::StringToMac(QString str, unsigned char *mac)
{
    int i;
    char *s,*e;
    QByteArray ba =str.toLatin1();
    const char *char_t=ba.data();
    if((mac == nullptr)||(*char_t==' '))
    {
        return -1;
    }
    s = (char*)char_t;
    for(i=0;i<6;i++)
    {
        mac[i]=s?strtoul(s,&e,16):0;
        if(s)
        {
            s=(*e)?e+1:e;
        }
    }
    return 0;
}

void IPDialog::Reverse(unsigned char *array, int len)
{
    int i=0;
    unsigned char temp = 0;
    for(;i<len/2;i++)
    {
        temp = array[i];
        array[i]=array[len-i-1];
        array[len-i-1]=temp;
    }
}
/*****************
功能：界面初始化
作者：lengyuanjin
*****************/
void IPDialog::InitUI()
{
    // 正则表达式设置IP和MAC输入
    QRegExp ipRegExp = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip = new QRegExpValidator(ipRegExp,this);
    QRegExp LocalMacRegExp = QRegExp("/^[A-F0-9]{2}(-[A-F0-9]{2}){5}$|^[A-F0-9]{2}(:[A-F0-9]{2}){5}$");
    QRegExpValidator *m_LocalMac = new QRegExpValidator(LocalMacRegExp,this);
    ui->linedit_localip0->setValidator(m_ip);
    ui->lineedit_loaclmac0->setValidator(m_LocalMac);
    ui->linedit_localip1->setValidator(m_ip);
    ui->lineedit_loaclmac2->setValidator(m_LocalMac);
    ui->linedit_localip2->setValidator(m_ip);
    ui->lineedit_loaclmac2->setValidator(m_LocalMac);
    ui->linedit_localip3->setValidator(m_ip);
    ui->lineedit_loaclmac3->setValidator(m_LocalMac);
}
/*****************
功能：保存通道0网络配置
作者：lengyuanjin
*****************/
bool IPDialog::SetChannel0Params()
{
    QString localip = ui->linedit_localip0->text();
    ushort localport = ui->linedit_localport0->text().toUShort();
    QString localmac = ui->lineedit_loaclmac0->text();
    QString remoteip = ui->lineedit_remoteip0->text();
    ushort remoteport = ui->lineedit_remoteport0->text().toUShort();
    return CreateChannelNet(0, localip, localport, localmac, remoteip, remoteport);
}
/*****************
功能：保存通道1网络配置
作者：lengyuanjin
*****************/
bool IPDialog::SetChannel1Params()
{
    QString localip = ui->linedit_localip1->text();
    ushort localport = ui->linedit_localport1->text().toUShort();
    QString localmac = ui->lineedit_loaclmac1->text();
    QString remoteip = ui->lineedit_remoteip1->text();
    ushort remoteport = ui->lineedit_remoteport1->text().toUShort();
    return CreateChannelNet(1, localip, localport, localmac, remoteip, remoteport);
}
/*****************
功能：保存通道2网络配置
作者：lengyuanjin
*****************/
bool IPDialog::SetChannel2Params()
{
    QString localip = ui->linedit_localip2->text();
    ushort localport = ui->linedit_localport2->text().toUShort();
    QString localmac = ui->lineedit_loaclmac2->text();
    QString remoteip = ui->lineedit_remoteip2->text();
    ushort remoteport = ui->lineedit_remoteport2->text().toUShort();
    return CreateChannelNet(2, localip, localport, localmac, remoteip, remoteport);
}
/*****************
功能：保存通道3网络配置
作者：lengyuanjin
*****************/
bool IPDialog::SetChannel3Params()
{
    QString localip = ui->linedit_localip3->text();
    ushort localport = ui->linedit_localport3->text().toUShort();
    QString localmac = ui->lineedit_loaclmac3->text();
    QString remoteip = ui->lineedit_remoteip3->text();
    ushort remoteport = ui->lineedit_remoteport3->text().toUShort();
    return CreateChannelNet(3, localip, localport, localmac, remoteip, remoteport);
}
/*****************
功能：创建通道网络配置
作者：lengyuanjin
*****************/
bool IPDialog::CreateChannelNet(ViUInt8 ch, QString localip, ushort localport, QString localmac, QString remoteip, ushort remoteport)
{
    TPA_NETParam netParam;
    StringToUChar(localip,netParam.LocalIp);//  本地IP
    Reverse(netParam.LocalIp,4);
    netParam.LocalPort = localport;//  本地端口
    StringToMac(localmac,netParam.LocalMac);//  本地mac
    Reverse(netParam.LocalMac,6);
    netParam.RemotePort = remoteport;//  远端端口
    StringToUChar(remoteip,netParam.RemoteIp);//  远端ip
    Reverse(netParam.RemoteIp,4);
    netParam.Baud = PA_NET_BAUD_1000M;//  传输速率

    ViStatus status = 0;
    //  设置参数
    status += PA_PCIe_1501_NET_SetParam(m_DevVi, ch, netParam);
    // 设置帧长
    status += PA_PCIe_1501_NET_SetSendFrameLength(m_DevVi, ch, 969);
    return status == 0 ? true : false;
}

/*****************
功能：保存网络配置
作者：lengyuanjin
*****************/
void IPDialog::on_pushButton_Ok_clicked()
{
    bool successed = true;
    ViSession devVi = send_div;
    ViStatus status = 0;
    status += PA_PCIe_1501_NET_Init(&devVi);
    m_DevVi = devVi;
    send_div=devVi;

    successed &= SetChannel0Params();
    successed &= SetChannel1Params();
    successed &= SetChannel2Params();
    successed &= SetChannel3Params();
    if(successed && status == 0)
    {
        QMessageBox::warning(this,"提示","参数设置成功！");
        accept();
    }
    else
    {
        QMessageBox::warning(this,"提示","设备初始化失败！");
    }
}
