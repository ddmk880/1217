#ifndef SUB1553_TCCONTROL2_H
#define SUB1553_TCCONTROL2_H

#include <QWidget>
#include <Globel_Define.h>
namespace Ui {
class sub1553_tccontrol2;
}

class sub1553_tccontrol2 : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_tccontrol2(QWidget *parent = nullptr);
    ~sub1553_tccontrol2();
    void Reverse_Data(Order_List_Object varData);
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
    uint toHex_uint(QString qstr);//qstring转16进制uint
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort
signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);
    void se_arg2(int a,int b);
public slots:
    void re_arg2(int a,int b);
private slots:
    void on_pushButton_C8C_clicked();

    void on_pushButton_C8D_clicked();

    void on_pushButton_C8E_clicked();

    void on_pushButton_C8F_clicked();

    void on_pushButton_C91_clicked();

    void on_pushButton_C92_clicked();

    void on_pushButton_C93_clicked();

    void on_pushButton_C94_clicked();

    void on_pushButton_C95_clicked();

    void on_pushButton_C96_clicked();

    void on_pushButton_C97_clicked();

    void on_pushButton_C93_Add_clicked();

    void on_pushButton_C93_clear_clicked();


    void on_comboBox_c93_1_activated(int index);


    void on_cb_cardChooe_currentIndexChanged(int index);

    void on_pushButton_C90_clicked();


private:
    Ui::sub1553_tccontrol2 *ui;
};

#endif // SUB1553_TCCONTROL2_H
