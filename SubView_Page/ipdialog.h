#ifndef IPDIALOG_H
#define IPDIALOG_H

#include <QDialog>
#include "PA_PCIe_1501.h"
namespace Ui {
class IPDialog;
}

class IPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IPDialog(ViSession &vi, QWidget *parent = nullptr);
    ~IPDialog();

public:
    void StringToUChar(QString str,unsigned char *recv);
    int  StringToMac(QString str,unsigned char *mac);
    void Reverse(unsigned char *array,int len);
protected:
    void InitUI(void);
    bool SetChannel0Params();
    bool SetChannel1Params();
    bool SetChannel2Params();
    bool SetChannel3Params();
    bool CreateChannelNet(ViUInt8 ch, QString localip, ushort localport, QString localmac, QString remoteip, ushort remoteport);
private slots:
    void on_pushButton_Ok_clicked();

private:
    Ui::IPDialog *ui;
    TPA_NETParam m_netparam0;
    TPA_NETParam m_netparam1;
    TPA_NETParam m_netparam2;
    TPA_NETParam m_netparam3;
    ViSession &m_DevVi;
};

#endif // IPDIALOG_H
