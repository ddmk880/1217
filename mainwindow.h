#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Globel_Define.h>
#include <qtmaterialsnackbar.h>
#include <qtmaterialtabs.h>
#include<QThread>
#include <QStandardItemModel>
#include"xlsxdocument.h"
#include <qtmaterialraisedbutton.h>
#include"ui_sub1553_busclass.h"
#include <QMovie>
#include <QLabel>

#include "DatabaseView.h"
#include "YcView.h"
#include "TaskView.h"
#include "MonitorView.h"
#include "HardwareCtrl/CardCtrl_CAN.h"
#include "HardwareCtrl/CardCtrl_1553B.h"
#include "HardwareCtrl/CardCtrl_RapidIO.h"
#include "HardwareCtrl/CardCtrl_AD_OC.h"
#include "HardwareCtrl/CardCtrl_NET.h"
//遥测界面子界面
#include "SubView_Page/subyc_slowspeed.h"

#include "SubView_Page/CN_SignalContrl.h"
#include"xlsxdocument.h"
#include "SubView_Page/mylabel.h"


using namespace QXlsx;




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow  {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QMainWindow* m;
  mylabel* mClass_label;
  QTimer* timer;
  uint TIME_CNT;
  bool net_init;//千兆网初始化成功标志
 private:
  QtMaterialTabs *m_tab_daohang;
  QtMaterialTabs *m_tab_game;
  const static quint16 ORDER_GAP_TIME = 1;  // 默认指令间隔时间
  Ui::MainWindow *ui;
  QStandardItemModel *model_list;  // 界面table_view
  void Init_Main_Ui();             // 初始化界面控件
  void Init_Sub_Page();            // 初始化子页面
  void Init_Other_Ui();            // 初始化其余控件
  void Init_HardDevices();         // 初始化硬件设备
  void Init_Yc_Subview();          //遥测子界面
  void Order_Send_Fun(int cnt);     //定时，选中发送公共函数
  void HeadOrd_Send_Fun(int cnt);    //加头导出
  void m_GamesInit();               //游戏窗口配置
  map<int,QString> Ord_Kind;        //指令类型
  map<QString,int> Ord_Kind2;        //指令类型
  void Get_boardFirst();        //启动默认读取指定路径表格
  void gifGround();//动态背景
  QStringList yyh_ListPic;//gif图片路径
  QLabel *backgroundLabel; // 用于显示背景 GIF 的 QLabel
  QMovie *backgroundMovie; // 用于背景的 QMovie
  QMovie *iconMovie;       // 用于其他动画的 QMovie
  //轨道姿态
  void gdzt_ssend(int cnt);
  void gdzt_read(QString path);//轨道姿态数据读取xlsx
  vector<Orbitalstance_Data_xlsx>v_orb_can;
  //GNSS定位
  void gnss_dw_send(int cnt);
  void gnss_dw(QString path);//GNSS定位读取xlsx
  vector<GNSS_Positioning_xlsx> v_gnss_postion_can;
  //GNSS定轨
  void gnss_dg_send(int cnt);
  void gnss_dg(QString path);//GNSS定轨读取xlsx
  vector<GNSS_Orbit_xlsx> v_gnss_orbit_can;
  //读取信号源表格
  void Get_ExlMess(uint time);
  Document* Signal_xlsxR;
  QString Path_xlsx;
  map<int,QString> Sig_type;        //指令类型
  int ssss_test=0;      //测试信号源用变量


  void moveRow(QTableView *tableView, int currentRow, int toRow);  // 移动表格行

  CN_SignalContrl* signalConrtl[2];    //信号源
  void Get_TcpMess(QString str);//tcp接收数据显示
  void signal_init();           //信号源控制初始化
  void orderDB_init();           //指令数据库初始化
  m_games* Games;                   //内嵌游戏
  Translate* Tran_Mess;             //翻译指令
  TaskView    *p_view_task;           // 任务列表页面
  MonitorView *p_monitor;           // 监视页面

  DatabaseView* p_database;         //数据库
  YcView      * p_view_yc;          //遥测显示界面
  subyc_slowspeed* yc_slow;//慢速遥测
  subyc_packspeed* yc_pack;//打包遥测
  subyc_canC81*    yc_canc81;//打包遥测
  subyc_AD*        yc_ad;//ad电压遥测
  subrs422_Rec*    yc_rs422_rec;      //rs422电平接收

  CardCtrl_CAN* Card_can;
//  CardCtrl_1553B* Card_1553Can;
  Pluse_1553Time* Card_plusetime;
  CardCtrl_RapidIO* Card_RapidIO;
  CardCtrl_AD_OC* Card_AD_OC;
  CardCtrl_NET* Card_Net;
  QList<Order_List_Object> order_data_list;
  QMenu *m_list_task_menu;
  QSize main_frame_size;
  QAction *m_action_goto_view;
  QAction *m_action_export;
  QAction *m_action_export2;
  QAction *m_action_export3;
  QtMaterialSnackbar *m_snackbar_success;  // 成功弹框
  QtMaterialSnackbar *m_snackbar_fail;     // 失败弹框
  QtMaterialRaisedButton* m_button_send_all_task;// 发送全部按钮
  QtMaterialRaisedButton* m_button_send_one_task;// 发送选中按钮
  QtMaterialRaisedButton* m_button_cycle_task;//循环发送
  bool switch_1553cyc=false;//1553周期发送开关(默认开)
  bool switch_1553board=true;//1553广播开关(默认关)
  bool switch_CANboard=true;//CAN广播开关(默认关)
  bool CAN_seccues=true;//CAN通道是否正常
  bool inOder_falg=false;//判断是否是导入的指令
  void contrl_pB();//控件使能是否
  bool Cycle_sendFlag;                  //列表指令循环发送标志
  QString STR_PackOder;
  void pps_set();

 signals:
  void success_snack(QString str);
  void fail_snack(QString str);
  void Return_order_toView(const QVariant varData);
  void Trans_order_toView(const QVariant varData);
  void send_path(QString path);

 private slots:
  void timeUpdate();                 // 系统时间更新计时器
  void tab_index_change(int index);  // 导航栏页面切换
  void tab_game_change(int index);  // 导航栏页面切换(右边隐藏游戏)
  void button_click_sendAll();       // 发送全部按钮
  void button_click_sendOne();       // 发送一条按钮
  void button_click_Stop();          // 停止按钮
  void button_click_cycle();          // 列表指令循环发送

  void button_click_delAll();        // 清空按钮
  void button_click_delOne();        // 删除一条按钮
  void button_click_export();        // 导出按钮
  void button_click_import();        // 导入按钮
  void button_click_orderup();        // 单行上移
  void button_click_orderdown();       // 单行下移
  void button_click_Packexport();      // 加头导出

  void get_1553time(LL times);     //获取1553时间
  void show_tasklist_menu(QPoint pos);
  void resizeEvent(QResizeEvent *event);
  void timerUpdate();

  void on_pB_OcPowerup_clicked();

  void on_pB_OcPowerlow_clicked();

  void on_m_button_delog_clicked();


  void on_pB_1553on_off_clicked();

  void on_pushButton_starttime_test_clicked();

  void on_pushButton_Orbitalstance_test_clicked();

  void on_pB_GNSStimecode_test_clicked();

  void on_pB_GNSSposition_test_clicked();

  void on_pB_GNSStrack_test_clicked();

  void on_pushButton_board_onoff_clicked();

  void on_pushButton_ChangTimeUI_clicked();

  void on_pushButton_SelfTest_clicked();

  void on_pushButton_xttb_clicked();

  void on_pushButton_longbh_clicked();

  void on_pB_GnssPostion_xlsx_clicked();

  void on_pB_GDZT_clicked();

  void on_pB_orbit_xlsx_clicked();

  void on_pB_outputClear_clicked();

  void on_cB_AB_choose_currentIndexChanged(int index);

  void on_pB_orderTime_clicked();

  void on_pB_CAN_board_onoff_clicked();

  void on_pB_taskUp_down_elec_clicked();

  void on_pB_task_reset_clicked();

  void on_pB_IPConnet_clicked();

  void on_pB_disconnect_clicked();

  void on_pB_send_clicked();

  void on_pB_readXlsx_clicked();

  void on_pB_signal_send_clicked();

  void on_checkBox_RF_ON_clicked(bool checked);

  void on_checkBox_MOD_ON_clicked(bool checked);

  void on_pB_saveStates_clicked();

  void on_pB_REL_clicked();

  void on_pB_reSet_clicked();

  void on_pB_signal_create_clicked();

  void on_pB_IPConnet_2_clicked();

  void on_pB_disconnect_2_clicked();

  void on_pushButton_clearSignal_clicked();

  void on_checkBox_PPSch1_clicked(bool checked);

  void on_checkBox_PPSch4_clicked(bool checked);

  void on_checkBox_PPSch5_clicked(bool checked);

  void on_checkBox_PPSch6_clicked(bool checked);

  void on_pushButtonxxx_clicked();

  void on_checkBox_CANoutSend_clicked(bool checked);

  void on_pB_canDataExport_clicked();

  void on_checkBox_PPSch7_clicked(bool checked);

  void on_checkBox_PPSch8_clicked(bool checked);

  void on_checkBox_PPSch2_clicked(bool checked);

  void on_checkBox_PPSch3_clicked(bool checked);


  void on_checkBox_1553BCH1_clicked(bool checked);

  void on_checkBox_1553BCH2_clicked(bool checked);

  void on_checkBox_1553BCH3_clicked(bool checked);

  void on_checkBox_1553BCH4_clicked(bool checked);

  void on_comboBox_activated(int index);

  void on_cB_XS_A_clicked(bool checked);

  void on_cB_XS_B_clicked(bool checked);

public:
  void success_snack_slot(QString str);  // 成功弹窗
  void fail_snack_slot(QString str);     // 失败弹窗
  void Main_Oupt(QString str,int color);     // 主窗口输出
  void Translate_Order();//翻译指令
  void Export_order();
  void Export_orderSource();//导出指令16进制dat文件
  void Return_To_SubView();//跳转页面翻译
  void add_order_toList(const QVariant varData);

  int Send_1553SubOrder(int num,bool head,int addr); //总线指令
  int Send_1553OverOrder(int num,bool head,int addr);//总线注数指令
  int Send_1553ModeOeder(int num,int addr);//模式控制指令
  int Send_CancardOeder(int num);//CAN数据发送
  int CAN_DataSend(uchar* pData,int order_len);//CAN公共封装发送
  int Send_Signal(int num);//信号源指令发送
  void Write_orDB(int num,int status); //指令发送内容写入数据库
  void Get_PackOrder(unsigned char* Data,int Datalen); //获取封装后的指令

  void change_list_time(QStandardItem *item);
  QString ChangeColor(QString str,int kind);//改变字体颜色
  map<uchar,uchar>mRe_Addr;//can接收地址
  map<QString,uchar>OBJ_Addr;//1553目标单机收地址
  bool startOder_Tim;//星时指令标志

signals:
  void statr_CanRec(bool st);

public slots:
  void output_Data(QString str);
  void slotRowDoubleClicked(const QModelIndex & index);
  void close_GameView();//打开游戏界面
  void gif_change();//gif图片更换
  void gif_change_right();//gif图片更换（右键）




};
#endif  // MAINWINDOW_H
