#ifndef sub1553_gkmayrffront_H
#define sub1553_gkmayrffront_H

#include <QWidget>
#include "Globel_Define.h"
//上注指令类：可重构射频前端


namespace Ui {
class sub1553_gkmayrffront;
}

class sub1553_gkmayrffront : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_gkmayrffront(QWidget *parent = nullptr);
    ~sub1553_gkmayrffront();
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);

signals:
 void Add_Order_ToList(QVariant varData);
 void success_snack(QString str);
 void fail_snack(QString str);
private slots:
 void on_pB_channel_power_control_clicked();

 void on_pB_channel_control_choose_clicked();

 void on_pB_zpchooseSet_clicked();

 void on_cB_Lchannel_1_activated(int index);



 void on_cB_SXKu_channel_12_activated(int index);

private:
    Ui::sub1553_gkmayrffront *ui;
};

#endif // sub1553_gkmayrffront_H
