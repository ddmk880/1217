#ifndef SUB1553_BUSCLASS_H
#define SUB1553_BUSCLASS_H

#include <QWidget>
#include <Globel_Define.h>


namespace Ui {
class sub1553_busclass;
}

class sub1553_busclass : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_busclass(QWidget *parent = nullptr);
    ~sub1553_busclass();
    void Reverse_Data(Order_List_Object varData);
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
signals:
 void Add_Order_ToList(QVariant varData);
 void success_snack(QString str);
 void fail_snack(QString str);

private slots:
 void on_pB_shutdown_clicked();


 void on_pB_watchdog_control_clicked();

 void on_pB_software_load_clicked();

 void on_pB_flashformat_clicked();

 void on_pB_ssdclear_clicked();

 void on_pB_OCpower_control_clicked();

 void on_pB_Can_powercontrol_clicked();

 void on_pB_trans_software_clicked();

 void on_pushButton_task_clicked();

 void on_pushButton_downcontrl_clicked();

 void on_pushButton_enduptask_clicked();

 void on_pushButton_GDbh_clicked();


 void on_pushButton_0x13_clicked();

 void on_pushButton_0x14_clicked();

 void on_pB_0x15_clicked();

 void on_pB_0x17_clicked();

 void on_pB_0x18_clicked();

 void on_pB_0x1A_clicked();

 void on_pushButton_0x0A_down_clicked();

 void on_pB_0x1B_clicked();

 void on_pushButton_0x0B_clicked();

 void on_pB_0x0C_clicked();

 void on_pushButton_0x1C_clicked();

 void on_pB_0x0E_clicked();

 void on_pushButton_0x0F_clicked();

 void on_pushButton_0x10_clicked();

 void on_pushButton_0x11_clicked();

 void on_pushButton_0x0D_clicked();

 void on_pushButton_0x16_clicked();

 void on_pushButton_0x19_clicked();

private:
    Ui::sub1553_busclass *ui;

};

#endif // SUB1553_BUSCLASS_H
