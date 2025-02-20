#ifndef TRANSLATE_MESS_H
#define TRANSLATE_MESS_H

#include <QWidget>
#include <Globel_Define.h>
#include <map>
#include <QTextEdit>
#include <QMovie>
#include <QLabel>
using namespace std;
namespace Ui {
class Translate;
}

class Translate : public QWidget
{
    Q_OBJECT

public:
    explicit Translate(QWidget *parent = nullptr);
    ~Translate();
    QString ChangeColor(QString str,int kind);//改变字体颜色
    void Init_contrlData();//初始化控件默认内容

    void gifGround();//动态背景
    QLabel *backgroundLabel; // 用于显示背景 GIF 的 QLabel
    QMovie *backgroundMovie; // 用于背景的 QMovie
    QMovie *iconMovie;       // 用于其他动画的 QMovie

    TaskContent Glob_Head;  //上注任务 头部全局结构体，后续依据判断
    QTextEdit* Modeview1;
    QTextEdit* Modeview2;
    QTextEdit* Modeview3;
    map<int,QString>UP_fun_mode;
    QString UP_work_mode[10][6];//功能模式
    int UP_work_tsak[10][10][11];//任务模式[功能模式][工作模式][任务模型类型]

    void Tran_UpTask(QVariant varData);//上注任务页面指令 解析
    void Gkcontrol1(QVariant varData);//管控指令1界面 解析

    uint Trans_Elec_ReconData(uchar * data);//电子侦察任务
    uint Trans_Elec_GrData(uchar * data);   // 电子干扰任务
    uint Trans_SAR_probing(uchar * data);   // //SAR探测任务基本信息

    uint Trans_5G_kind(uchar * data);       //类5G任务基本信息

    uint mode_qj(uchar * data);             // 全景模式
    uint mode_cgxhpdks_2(uchar * data);     // 常规信号频点控守
    uint mode_linkpdks_3(uchar * data);     // Link16信号频点控守参数
    uint mode_tkxhpdks_4(uchar * data);     // 塔康信号频点控守
    uint mode_dwsbxh_5(uchar * data);       // 敌我识别信号频点控守
    uint mode_yxxhpdks_6(uchar * data);     // 铱星信号频点控守
    uint mode_hsxhpdks_7(uchar * data);     // 海事信号频点控守
    uint mode_ldxhpdks_8(uchar * data);     // 雷达信号频点控守
    uint mode_xlxhpdks_9(uchar * data);     // 星链信号频点控守参数
    uint mode_tbcy_18(uchar * data);        // 同步采样
    uint mode_up_sorft_20(uchar * data);    //上注软件解调
    uint mode_ldxhpdsmT_11(uchar * data);   //雷达信号频点扫描
    uint mode_spgr_13(uchar * data);        //多频点快速干扰
    uint mode_szpgr_14(uchar * data);       //等间隔梳状谱干扰
    uint mode_not_szpgr_15(uchar * data);   // 非等间隔梳状谱干扰
    uint mode_dhmbgr_T16(uchar * data);     // 多通道快速变极化协同干扰
    uint mode_xlmbgr_T17(uchar * data);     //多通道多带宽协同干扰
    uint mode_LD_QZgr18(uchar * data);      //雷达强制干扰
    uint mode_LD_T19(uchar * data);         //雷达侦察
    uint mode_L5G_T22(uchar * data);         //类5G模式参数

    uint Gkcontrol1_rwzx(uchar * data); //任务执行设置

public:
  void Trans_to_Oder(const QVariant varData);
private:
    Ui::Translate *ui;
};

#endif // TRANSLATE_MESS_H
