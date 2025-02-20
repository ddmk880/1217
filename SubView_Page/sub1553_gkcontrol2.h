#ifndef SUB1553_GKCONTROL2_H
#define SUB1553_GKCONTROL2_H

#include <QWidget>
#include "Globel_Define.h"
namespace Ui {
class sub1553_gkcontrol2;
}

class sub1553_gkcontrol2 : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_gkcontrol2(QWidget *parent = nullptr);
    ~sub1553_gkcontrol2();
    void Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname);
    uint toHex_uint(QString qstr);//qstring转16进制uint
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort
signals:
  void Add_Order_ToList(QVariant varData);
  void success_snack(QString str);
  void fail_snack(QString str);

private slots:
  void on_pB_4B_start_clicked();

  void on_pB_4C_end_clicked();

  void on_pB_47_updata_clicked();

  void on_Combox_47_1_activated(int index);

  void on_pB_4A_clicked();


  void on_comboBox_0x47_choose_activated(const QString &arg1);

  void on_comboBox_47_5_activated(int index);

  void on_pushButton_0x43_clicked();

private:
    Ui::sub1553_gkcontrol2 *ui;
};

#endif // SUB1553_GKCONTROL2_H
