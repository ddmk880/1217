#ifndef SUBYC_SLOWSPEED_H
#define SUBYC_SLOWSPEED_H

#include <math.h>
#include <map>

#include <QStandardItemModel>
#include <QWidget>

//存储变色信息
struct Change_out
{
    int rows;
    bool chan;
};

using namespace std;
namespace Ui {
class subyc_slowspeed;
}

class subyc_slowspeed : public QWidget {
  Q_OBJECT

 public:
  explicit subyc_slowspeed(QWidget* parent = nullptr);
  ~subyc_slowspeed();
  QStandardItemModel* model;
  double ret_fun100(double k, double c, double N);
  double ret_fun104(double a, double b, double k, double c, int Rf, double d,double e, double f, double N);
  double ret_fun104_tmp(int R25,int B,double N);//温度计数新公式
  QString ret_fun114(int yy, int mm, int nn, int h, int m, int s, int k,int Md);
  QString ret_fun118(int yy, int mm, int nn, int h, int m, int s, int Md);
  double ret_fun124(double a, double b, double k, double c, double N);

  void Init_ViewList();//初始化列表显示
  void Init_DBList();//初始化数据库字段名
  int Outslow_dj;//输出哪个地检慢速遥测
  void GlobOut_View(ushort* Rxbuff, int Rxlen,int ch);//最终输出函数

  map<int,QString> g1_gkUpstatus;       //第一组 综合管控单元-管控机软件上注更新状态
  map<int,QString> g1_orderResuit;      //第一组 1553B指令执行结果
  map<int,QString> g1_gk_workmode;      //第一组 综合管控单元-工作状态
  map<int,QString> g3_SARmode;          //第三组 SAR-任务模式
  map<int,QString> g3_FPGA_Status;      //第三组 FPGAV7任务状态
  map<int,QString> g4_ZC_yxMode;      //第四组侦察 V7运行模式
  map<int,QString> g4_ZC_yxStas;      //第四组侦察 V7运行状态
  map<int,QString> g4_SAR_sp;      //第四组SAR 校正流程遥测-射频选择

  map<int,QString> g2_SAR_workmode;//SAR成像-系统工作状态



  ushort g4_YC_Flag;//第四组遥测类型标志
  void shoe_pub_g4head(uchar* g4buff);//显示第四组公共头

  void show_yc0735(uchar* g4buff);//第四组遥测解析-电子侦察任务包(2s)
  void show_yc0736(uchar* g4buff);//第四组遥测解析-电子干扰任务包(2s)
  void show_yc0737(uchar* g4buff);//第四组遥测解析-SAR成像任务包(2s)
  void show_yc0738(uchar* g4buff);//第四组遥测解析-备用导航任务包(2s)
  void show_yc0739(uchar* g4buff);//第四组遥测解析-类5G通信任务包(2s)
  void show_yc073A(uchar* g4buff);//第四组遥测解析-头

 private:
  Ui::subyc_slowspeed* ui;

 public slots:
  void Get_MsYcData1(ushort* Rxbuff, int Rxlen,int ch);//单机1
  void Get_MsYcData2(ushort* Rxbuff, int Rxlen,int ch);//单机2
  void Get_MsYcData3(ushort* Rxbuff, int Rxlen,int ch);//单机3
  void Get_MsYcData4(ushort* Rxbuff, int Rxlen,int ch);//单机4
 private slots:
  void on_pB_Clearmsyclist_clicked();
  void on_radioButton_group2_clicked();
  void on_radioButton_group1_clicked();
  void on_radioButton_group3_clicked();
  void on_radioButton_group4_clicked();
};

#endif  // SUBYC_SLOWSPEED_H
