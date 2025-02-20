#ifndef subsrio_overnote_H
#define subsrio_overnote_H

//rapidio文件发送

#include <QWidget>
#include <Globel_Define.h>
#include "HardwareCtrl/CardCtrl_RapidIO.h"
#include <QFileDialog>
#include <qtimer.h>
namespace Ui {
class subsrio_overnote;
}

class subsrio_overnote : public QWidget
{
    Q_OBJECT

public:
    explicit subsrio_overnote(QWidget *parent = nullptr);
    ~subsrio_overnote();
    CardCtrl_RapidIO* cardSRIO;

    void Reverse_Data(Order_List_Object varData);
    void get_jxjd(double value);
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort
    QString Dirpath;
    QString Filepath0;
    QString Filepath1;
    QFile* Pfile0;
    QFile* Pfile1;
    QTimer* time1;

signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);
    void send_riodata(QString str, bool ad0, bool ad1, DC_test dc_test);
    void rec_riodata(QFile* pfile_0,QFile* pfile_1);
    void finshrec_riodata();
    void reset_srio();

private slots:
    void updata_Size();
    void on_pB_ReadbinFile_clicked();

    void on_pB_SRIOsend_clicked();

    void on_pB_getFilepath_clicked();

    void on_pB_startOrstop_clicked();

    void on_pushButton_statusNew_clicked();

    void on_pB_csv_dat_clicked();

private:
    Ui::subsrio_overnote *ui;
};

#endif // subsrio_overnote_H
