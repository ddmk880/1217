#ifndef sub1553_tccontrol_H
#define sub1553_tccontrol_H

#include <QWidget>
#include <Globel_Define.h>

namespace Ui {
class sub1553_tccontrol;
}

class sub1553_tccontrol : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_tccontrol(QWidget *parent = nullptr);
    ~sub1553_tccontrol();
    void Reverse_Data(Order_List_Object varData);
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
    void fantion(int n);
    uint toHex_uint(QString qstr);//qstring转16进制uint
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort
signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);
    void se_arg1(int a,int b);
public slots:
    void re_arg1(int a,int b);


private slots:
    void on_pushButton_startup_clicked();

    void on_comboBox_dzzcmk_activated(int index);

    void on_comboBox_dzgr_activated(int index);

    void on_comboBox_SARcx_activated(int index);

    void on_comboBox_bydx_activated(int index);

    void on_comboBox_l5gtx_activated(int index);

    void on_comboBox_JIDSl_activated(int index);

    void on_comboBox_csqp_activated(int index);

    void on_comboBox_sjcs_activated(int index);

    void on_comboBox_norflash_activated(int index);



    void on_comboBox_sfclmk_activated(int index);

    void on_pushButton_rjcg_clicked();

    void on_pushButton_flashcc_clicked();

    void on_pushButton_clicked();

    void on_pushButton_sorftUp_clicked();

    void on_pushButton_writeStatus_clicked();

    void on_pushButton_sorftDown_clicked();

    void on_comboBox_high_activated(int index);

    void on_pushButton_C86upFinash_clicked();

    void on_pushButton_dsp6678_A0_clicked();

    void on_pushButton_yjcg_clicked();

    void on_pushButton_yjbcg_clicked();

    void on_pushButton_ykyx_clicked();


    void on_pushButton_C88_clicked();

    void on_cb_cardChooe_currentIndexChanged(int index);

    void on_pushButton_C89_clicked();

private:
    Ui::sub1553_tccontrol *ui;
    int n;

};

#endif // sub1553_tccontrol_H
