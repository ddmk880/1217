#ifndef sub1553_gkcontrol_H
#define sub1553_gkcontrol_H

#include <QWidget>

#include "Globel_Define.h"
// 上注指令类：综合管控单元

namespace Ui {
class sub1553_gkcontrol;
}

class sub1553_gkcontrol : public QWidget {
  Q_OBJECT

 public:
  explicit sub1553_gkcontrol(QWidget *parent = nullptr);
  ~sub1553_gkcontrol();
  void Pblic_Addorderlist(uchar *databuff, int buffLen, QString buffname);
  uint toHex_uint(QString qstr);//qstring转16进制uint
  ushort toHex_ushort(QString qstr);//qstring转16进制ushort
signals:
  void Add_Order_ToList(QVariant varData);
  void success_snack(QString str);
  void fail_snack(QString str);


 private slots:

  void on_pB_pre_taskmode_eliminate_clicked();

  void on_pB_task_eliminate_highfrequencyband_clicked();

  void on_pB_task_eliminate_high_clicked();

  void on_pB_outdata_task_eliminate_clicked();

  void on_pB_outdata_task_autoeli_clicked();

  void on_pB_ssd_datadownload_clicked();

  void on_pB_controlmachine_can_reset_clicked();

  void on_pB_test_numbertrans_clicked();

  void on_pB_teststop_clicked();

  void on_pB_task_execute_clicked();

  void on_pB_function_model_set_clicked();

  void on_pB_softwate_download_clicked();


  void on_pB_controlmachine_file_check_clicked();

  void on_cB_startalone_sign_currentIndexChanged(int index);

  void on_pB_pre_task_deleteUID_clicked();

  void on_comboBox_3B_1_activated(int index);

  void on_comboBox__3B_3_activated(const QString &arg1);



  void on_pB_0x39_clicked();

  void on_pushButton_0x39chppsefile_clicked();

  void on_pB_stop0x39_clicked();

  void on_pB_0x32_clicked();


  void on_LineEdit_task_deleteUID_textChanged(const QString &arg1);

  void on_LineEdit_task_number_textChanged(const QString &arg1);


  void on_comboBox__3B_2_currentIndexChanged(const QString &arg1);


  void on_pushButton_0x3C_clicked();

  void on_pB_0x3D_clicked();

private:
  Ui::sub1553_gkcontrol *ui;
};

#endif  // sub1553_gkcontrol_H
