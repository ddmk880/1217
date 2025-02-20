#ifndef TASKVIEW_H
#define TASKVIEW_H

#include <Globel_Define.h>
#include <QStandardItemModel>
#include <QTreeWidget>
#include <QWidget>
#include <QThread>
#include <QVector>
#include "HardwareCtrl/CardCtrl_RapidIO.h"

#include "SubView_Page/subsrio_overnote.h"
#include "SubView_Page/subtrillion_overnote.h"
#include "SubView_Page/sub1553_busclass.h"
#include "SubView_Page/sub1553_buspower.h"
#include "SubView_Page/sub1553_gkcontrol.h"
#include "SubView_Page/sub1553_gkcontrol2.h"
#include "SubView_Page/sub1553_gkmaygsl.h"
#include "SubView_Page/sub1553_gkmayrffront.h"
#include "SubView_Page/sub1553_gksxkucontrol.h"
#include "SubView_Page/sub1553_tccontrol.h"
#include "SubView_Page/sub1553_tccontrol2.h"
#include "SubView_Page/sub1553_tccontrol_spi.h"
#include "SubView_Page/subboard_bc.h"
#include "SubView_Page/subboard_rt.h"
#include "SubView_Page/sub1553_Overheadtask.h"
#include "SubView_Page/sub1553_modecontrl.h"
#include "SubView_Page/sub1553_tccontrol_l.h"
#include "SubView_Page/sub1553_tccontrol_sxku.h"
#include "SubView_Page/sub1553_tcmayrffront.h"
#include "SubView_Page/signal_1466.h"
#include "SubView_Page/auto_udp.h"
#include "SubView_Page/m_games.h"
#include "SubView_Page/yxq_contrl.h"
#include "SubView_Page/Translate_Mess.h"

using namespace std;
namespace Ui {
class TaskView;
}

class TaskView : public QWidget {
  Q_OBJECT

 public:
  explicit TaskView(QWidget *parent = nullptr);
  QTreeView *m_yctreeView;
  ~TaskView();

  QThread* qthread_send;
  QThread* qthread_rec;
  CardCtrl_RapidIO* card_rio;
  CardCtrl_RapidIO* card_rio_rec;
  QVector<int> Obj_ID();//存储发送不同目标单机
  sub1553_modecontrl*   pview_modecontrl;         //模式控制指令
 private:
  void Init_View_Sub();
  void Init_View_Main();
  void Hide_view();//隐藏界面
  void Show_view(int index);//显示界面
  void RapidConnet();//rapidio连接
  void trillionConnet();//千兆网连接
  void check1234();//界面单机选择栏
  Ui::TaskView *ui;
  QStandardItemModel *model_tree_list;


  sub1553_busclass* pview_busclass;             //总线指令类
  sub1553_busPower* pview_buspower;             //电源指令类
  subsrio_overnote* pview_overnote;             //rapidio文件发送
  subtrillion_overnote* pview_subtrillion;      //千兆网文件发送接收
  File_sendQthread* Filesend;                   //千兆网上注

  sub1553_gkcontrol*      pview_incontrol;        //上注指令类：综合管控单元
  sub1553_gkcontrol2*     pview_incontrol_2;        //上注指令类：综合管控单元第二部分
  sub1553_gkmayrffront*   pview_mayrffront;     //上注指令类：可重构射频前端
  sub1553_gkmaygsl*       pview_maygsl;         //上注指令类：可重构高算力平台

  sub1553_gksxkucontrol*  pview_beamcontrol;    // SPI协议指令：SXKu频段波束控制单元
  sub1553_tccontrol_spi*  pveiw_tc_spi;          // SPI协议指令：可重构高算力平台
  sub1553_tccontrol*      pview_recohigh;        // CAN协议指令(内部)：（前）可重构高算力平台1，2
  sub1553_tccontrol2*     pview_recohigh2;        // CAN协议指令(内部)：（后）可重构高算力平台1，2
  sub1553_tccontrol_L*    pview_can_L;        // CAN协议指令(内部)： L频段数字综合单元
  sub1553_tccontrol_sxku* pview_can_sxku;        // CAN协议指令(内部):SXKu频段波束控制器
  sub1553_tcmayrffront*   pview_can_front;        // CAN协议指令(内部):可重构射频前端

  sub1553_Overheadtask* pview_uptask;           //上注任务

  subboard_bc* pview_boardBC;                   //bc广播参数设置界面
  subboard_rt* pview_boardRT;                   //rt广播参数设置界面

  signal_1466* device_1466;                   //信号源1466
  yxq_contrl* yxq_cr;                           //移相器控制
  auto_udp* auto_UDPcontrl;                   //配合自动化UDP发送转发1553数据



 private slots:
  void on_m_tree_list_doubleClicked(const QModelIndex &index);

  void on_checkBox_DJ_all_clicked(bool checked);

  void on_checkBox_DJ_1_clicked(bool checked);

  void on_checkBox_DJ_2_clicked(bool checked);

  void on_checkBox_DJ_3_clicked(bool checked);

  void on_checkBox_DJ_4_clicked(bool checked);

public:
  void Transfer_to_subView(const QVariant varData);
};

#endif  // TASKVIEW_H
