#ifndef SUB1553_TCCONTROL_SXKU_H
#define SUB1553_TCCONTROL_SXKU_H

#include <QWidget>
#include <Globel_Define.h>

namespace Ui {
class sub1553_tccontrol_sxku;
}

class sub1553_tccontrol_sxku : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_tccontrol_sxku(QWidget *parent = nullptr);
    ~sub1553_tccontrol_sxku();

    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
    uint toHex_uint(QString qstr);//qstring转16进制uint
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort
    uchar toHex_uchar(QString qstr);//qstring转16进制uchar
    uchar* toHex_buff(QString qstr);//qstring转16进制缓存区

signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);


private slots:
    void on_pushButton_C51_clicked();

    void on_pushButton_C52_clicked();

    void on_pushButton_C53_clicked();

    void on_pushButton_C54_clicked();

    void on_pushButton_C55_clicked();

    void on_pushButton_C56_clicked();

    void on_pushButton_C57_clicked();

    void on_pushButton_C5A_clicked();

    void on_pushButton_C5B_clicked();

    void on_pushButton_5C_clicked();

    void on_pushButton_C5D_clicked();

    void on_pushButton_C5E_clicked();

private:
    Ui::sub1553_tccontrol_sxku *ui;
};

#endif // SUB1553_TCCONTROL_SXKU_H
