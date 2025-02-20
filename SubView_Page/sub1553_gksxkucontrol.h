#ifndef SUB1553_SXKUPDCONTROL_H
#define SUB1553_SXKUPDCONTROL_H

#include <QWidget>
#include <Globel_Define.h>

namespace Ui {
class sub1553_gksxkucontrol;
}

class sub1553_gksxkucontrol : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_gksxkucontrol(QWidget *parent = nullptr);
    ~sub1553_gksxkucontrol();
    void Reverse_Data(Order_List_Object varData);
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
    uint toHex_uint(QString qstr);//qstring转16进制uint

signals:
 void Add_Order_ToList(QVariant varData);
 void success_snack(QString str);
 void fail_snack(QString str);

private slots:

 void on_pB_sxkuspon_off_clicked();

 void on_pB_RS422_choose_clicked();

 void on_pB_flashRead_clicked();

 void on_pB_flashWrite_clicked();

 void on_pB_flashzjRead_clicked();

 void on_pB_flash_clear_clicked();

 void on_pB_unity_T_R_clicked();

private:
    Ui::sub1553_gksxkucontrol *ui;
};

#endif // SUB1553_SXKUPDCONTROL_H
