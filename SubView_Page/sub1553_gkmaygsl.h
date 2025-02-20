#ifndef sub1553_gkmaygsl_H
#define sub1553_gkmaygsl_H

#include <QWidget>

#include "Globel_Define.h"
// 上注指令类：可重构高算力平台

namespace Ui {
class sub1553_gkmaygsl;
}

class sub1553_gkmaygsl : public QWidget {
  Q_OBJECT

 public:
  explicit sub1553_gkmaygsl(QWidget *parent = nullptr);
  ~sub1553_gkmaygsl();
  void Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname);
  uint toHex_uint(QString qstr);//qstring转16进制uint
 signals:
  void Add_Order_ToList(QVariant varData);
  void success_snack(QString str);
  void fail_snack(QString str);
 private slots:

  void on_PB_SAR_end_clicked();

  void on_PB_radar_clear_clicked();

  void on_PB_single_delete_clicked();

  void on_PB_radar_modify_clicked();

  void on_on_PB_switch_clicked_clicked();

  void on_pushButton_5_clicked();

  void on_PB_clearall_clicked();

  void on_PB_L_link_clicked();

  void on_PB_navi_lock_clicked();

  void on_PB_T_protect_clicked();

  void on_pushButton_6A_in_clicked();

  void on_pushButton_6B_order_clicked();

  void on_pushButton_6A_read_clicked();

  void on_pushButton_6B_read_clicked();

  void on_pushButton_0x72_clicked();

  void on_PB_ssd_hy_clicked();

private:
  Ui::sub1553_gkmaygsl *ui;
};

#endif  // sub1553_gkmaygsl_H
