#ifndef SUB1553_BUSPOWER_H
#define SUB1553_BUSPOWER_H

#include <QWidget>
#include <Globel_Define.h>
#include <map>
using namespace std;
namespace Ui {
class sub1553_busPower;
}

class sub1553_busPower : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_busPower(QWidget *parent = nullptr);
    ~sub1553_busPower();
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
    map<int,QString>OC_kind;
    map<int,QString>CAN_kind;
    bool succ_send;
signals:
 void Add_Order_ToList(QVariant varData);
 void success_snack(QString str);
 void fail_snack(QString str);

private slots:
 void on_pushButton_01_clicked();

 void on_pushButton_2_clicked();

 void on_pushButton_3_clicked();

 void on_pushButton_4_clicked();

 void on_pushButton_5_clicked();

 void on_pushButton_6_clicked();

 void on_pushButton_7_clicked();

 void on_pushButton_8_clicked();

 void on_pushButton_9_clicked();

 void on_pushButton_10_clicked();

 void on_pushButton_11_clicked();

 void on_pushButton_12_clicked();

 void on_pushButton_13_clicked();

 void on_pushButton_14_clicked();

 void on_pushButton_15_clicked();

 void on_pushButton_16_clicked();

 void on_pushButton_17_clicked();

 void on_pushButton_18_clicked();

 void on_pushButton_19_clicked();

 void on_pushButton_20_clicked();

 void on_pushButton_21_clicked();

 void on_pushButton_22_clicked();

 void on_pushButton_23_clicked();

 void on_pushButton_24_clicked();

 void on_pushButton_25_clicked();

 void on_pushButton_26_clicked();

 void on_pushButton_27_clicked();

 void on_pushButton_28_clicked();

 void on_pushButton_29_clicked();

 void on_pushButton_30_clicked();

 void on_pushButton_31_clicked();

 void on_pushButton_32_clicked();

 void on_pushButton_33_clicked();

 void on_pushButton_34_clicked();

 void on_pushButton_35_clicked();

 void on_pushButton_36_clicked();

 void on_pushButton_37_clicked();

 void on_pushButton_38_clicked();

 void on_pushButton_39_clicked();

 void on_pushButton_40_clicked();

 void on_pushButton_41_clicked();

 void on_pushButton_42_clicked();

 void on_pushButton_43_clicked();

 void on_pushButton_44_clicked();

 void on_pushButton_CAN_1_clicked();

 void on_pushButton_CAN_2_clicked();

 void on_pushButton_CAN_3_clicked();

 void on_pushButton_CAN_4_clicked();

 void on_pushButton_CAN_5_clicked();

 void on_pushButton_CAN_6_clicked();

 void on_pushButton_CAN_7_clicked();

 void on_pushButton_CAN_8_clicked();

 void on_pushButton_CAN_9_clicked();

 void on_pushButton_CAN_10_clicked();

 void on_pushButton_CAN_11_clicked();

 void on_pushButton_CAN_12_clicked();

 void on_pushButton_CAN_13_clicked();

 void on_pushButton_CAN_14_clicked();

 void on_pushButton_CAN_15_clicked();

 void on_pushButton_CAN_16_clicked();

 void on_pushButton_CAN_17_clicked();

 void on_pushButton_CAN_18_clicked();

 void on_pushButton_CAN_19_clicked();

 void on_pushButton_CAN_20_clicked();

 void on_pushButton_CAN_21_clicked();

 void on_pushButton_CAN_22_clicked();

 void on_pushButton_CAN_23_clicked();

 void on_pushButton_CAN_24_clicked();

 void on_pushButton_CAN_25_clicked();

 void on_pushButton_CAN_26_clicked();

 void on_pushButton_CAN_27_clicked();

 void on_pushButton_CAN_28_clicked();

 void on_pushButton_CAN_29_clicked();

 void on_pushButton_CAN_30_clicked();

 void on_pushButton_CAN_31_clicked();

 void on_pushButton_CAN_32_clicked();

 void on_pushButton_CAN_33_clicked();

 void on_pushButton_CAN_34_clicked();

 void on_pushButton_CAN_35_clicked();

 void on_pushButton_CAN_36_clicked();

 void on_pushButton_CAN_37_clicked();

 void on_pushButton_CAN_38_clicked();

 void on_pushButton_CAN_39_clicked();

 void on_pushButton_CAN_40_clicked();

 void on_pushButton_CAN_41_clicked();

 void on_pushButton_CAN_42_clicked();

 void on_pushButton_CAN_48_clicked();

 void on_pushButton_0x2C_clicked();

 void on_pushButton_OC_SUM_clicked();

 void on_pushButton_CAN_SUM_clicked();

 void on_pushButton_Clear_OC_clicked();

 void on_pushButton_Clear_CAN_clicked();


 void on_pushButton_0x2D_clicked();

 void on_pushButton_CAN_SUM_2_clicked();

 void on_pushButton_CAN_SUM_4_clicked();

 void on_pushButton_Clear_CAN_2_clicked();

 void on_pushButton_Clear_CAN_4_clicked();

private:
    Ui::sub1553_busPower *ui;
};

#endif // SUB1553_BUSPOWER_H
