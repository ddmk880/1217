#ifndef sub1553_Overheadtask_H
#define sub1553_Overheadtask_H

#include <Globel_Define.h>

#include <QStandardItemModel>
#include <QWidget>
#include <map>

#include"xlsxdocument.h"
using namespace std;
namespace Ui {
class sub1553_Overheadtask;
}

class sub1553_Overheadtask : public QWidget {
    Q_OBJECT

public:
    explicit sub1553_Overheadtask(QWidget *parent = nullptr);
    ~sub1553_Overheadtask();
    QStandardItemModel *model_mlist;  // 界面table_view
    map<QString, int> zl_kind;
    void zizhenShow();
    void zizhenShow_J();
    void zz_change();
    void zz_change2();
    void BYzz_change();
    void Init_sublist();//子界面表格初始化设置
    void Init_zzwideget();//天线子阵里表格始化设置
    void BYDHInit_zzwideget();//备用导航天线子阵里表格始化设置
    uchar *set_Elec_ReconData(int &strlen);     // 电子侦察任务基本信息
    uchar *set_Elec_JammingData(int &strlen);   // 电子干扰任务基本信息
    uchar *set_Elec_sxkuDB(int &strlen);        //SXKu天线定标任务基本信息
    uchar *set_SAR_probing(int &strlen);        //SAR探测任务基本信息
    uchar *set_Elec_BYnavigation(int &strlen);  //备用导航任务基本信息
    uchar *set_5G_kind(int &strlen);            //类5G任务基本信息
    uchar *set_J_chain(int &strlen);            //J链任务基本信息
    void tz_fun();                              //扩展功能
    uchar * tz_fun_mess(int &strlen);                       //扩展功能基本信息
    void change_funMode(int index,bool getcomBox);        //改变功能模式控件(bool判断是否是控件下拉框动作)
    void change_taskkind(QString str,bool getcomBox);     //改变任务类型控件(判断是否是控件下拉框)
    void change_tabkind(QString str);        //改变任务类型tab
    ushort toHex_ushort(QString qstr);      //qstring转16进制ushort
    uchar toHex_uchar(QString qstr);        //qstring转16进制uchar
    uint toHex_uint(QString qstr);          //qstring转16进制uint
    uchar* Make_orderBuff(int &sumlen);     //制作完整上注任务指令
    void change_sarAddr(int curr);          //改变SAR内容地址
    void change_Sorft_addr(int curr);       //改变软件配置地址
    void fre_dBm();                         //频率对应输出衰减值
    map<QString, int> Map_fredBm;           //干扰频率对应实际输出衰减
    void Change_dBm(int a);                 //际输出衰减控件改变



    uchar *mode_SAR(QStringList qFileList,int &strlen);//SAR探测参数
    uchar *mode_qj_0(int &strlen);// 全景模式
    uchar *mode_cgxhpdks_2(int &strlen);// 常规信号频点控守
    uchar *mode_linkpdks_3(int &strlen);// Link16信号频点控守参数
    uchar *mode_tkxhpdks_4(int &strlen);// 塔康信号频点控守
    uchar *mode_dwsbxh_5(int &strlen);// 敌我识别信号频点控守
    uchar *mode_yxxhpdks_6(int &strlen);// 铱星信号频点控守
    uchar *mode_hsxhpdks_7(int &strlen);// 海事信号频点控守
    uchar *mode_ldxhpdks_8(int &strlen);// 雷达信号频点控守
    uchar *mode_xlxhpdks_9(int &strlen);// 星链信号频点控守参数
    uchar *mode_tbcy_18(int &strlen);   //同步采样
    uchar *mode_up_sorft_20(int &strlen);//上注软件解调
    uchar *mode_ldxhpdsmT_11(int &strlen);//雷达信号频点扫描
    uchar *mode_spgr_13(int &strlen);//多频点快速干扰
    uchar *mode_szpgr_14(int &strlen);// 等间隔梳状谱干扰
    uchar *mode_not_szpgr_15(int &strlen);// 非等间隔梳状谱干扰
    uchar *mode_dhmbgr_T16(int &strlen);// 多通道快速变极化协同干扰
    uchar *mode_xlmbgr_T17(int &strlen);//多通道多带宽协同干扰
    uchar *mode_LD_QZgr18(int &strlen);//雷达强制干扰
    uchar *mode_LD_T19(int &strlen);    //雷达侦察
    uchar *mode_BY_T21(int &strlen);//备用导航
    uchar *mode_L5G_T22(int &strlen);//类5G模式参数
    uchar *mode_J_T23(int &strlen);//J链任务模式参数

private slots:
    void on_pB_Overheadtask_clicked();
    void on_pB_CommandGeneration_clicked();

    void on_pB_ckearout_clicked();

    void on_comboBox_C3_currentIndexChanged(int index);

    void on_cB_function_mode_activated(int index);

    void on_cB_elecZC_contrlmode_activated(int index);

    void on_cB_elecZC_contrlmode_Z2_activated(int index);

    void on_cB_elecZC_contrlmode_Z3_activated(int index);

    void on_cB_elecZC_contrlmode_Z4_activated(int index);

    void on_pushButton_addQWidget_clicked();

    void on_pushButton_T13widgetClear_clicked();

    void on_pushButton_T13widgetClear_3_clicked();


    void on_checkBox_D10bit0_clicked(bool checked);

    void on_checkBox_D10bit1_clicked(bool checked);

    void on_checkBox_D10bit2_clicked(bool checked);

    void on_checkBox_D10bit3_clicked(bool checked);

    void on_pushButton_T15listClear_clicked();

    void on_pushButton_T16add_clicked();

    void on_pushButton_T16clear_clicked();

    void on_pushButton_T17add_clicked();

    void on_pushButton_T17clear_clicked();

    void on_comboBox_A10_activated(int index);


    void on_comboBox_A9_activated(const QString &arg1);

    void on_cB_task_modetype_activated(const QString &arg1);

    void on_tabWidget_3_currentChanged(int index);

    void on_checkBox_DH_TXbit0_clicked(bool checked);

    void on_checkBox_DH_TXbit1_clicked(bool checked);

    void on_checkBox_DH_TXbit2_clicked(bool checked);

    void on_checkBox_DH_TXbit3_clicked(bool checked);



    void on_cB_elecDH_contrlmode_activated(int index);

    void on_cB_elecDH_contrlmode_Z2_activated(int index);

    void on_cB_elecDH_contrlmode_Z3_activated(int index);

    void on_cB_elecDH_contrlmode_Z4_activated(int index);


    void on_pB_Overheadtask_CAN_clicked();

    void on_checkBox_D10bit0_2_stateChanged(int arg1);

    void on_checkBox_D10bit1_2_stateChanged(int arg1);

    void on_checkBox_D10bit2_2_stateChanged(int arg1);

    void on_checkBox_D10bit3_2_stateChanged(int arg1);

    void on_pB_chooseSarFile_clicked();

    void on_pushButton_sarClear_clicked();

    void on_comboBox_C12_activated(const QString &arg1);

    void on_comboBox_C13_activated(const QString &arg1);

    void on_comboBox_C14_activated(const QString &arg1);

    void on_comboBox_C15_activated(const QString &arg1);

    void on_comboBox_C16_activated(const QString &arg1);

    void on_comboBox_C17_activated(const QString &arg1);

    void on_comboBox_C18_activated(const QString &arg1);

    void on_comboBox_C19_activated(const QString &arg1);

    void on_checkBox_J_7b0_stateChanged(int arg1);

    void on_checkBox_J_7b1_stateChanged(int arg1);

    void on_checkBox_J_7b2_stateChanged(int arg1);

    void on_checkBox_J_7b3_stateChanged(int arg1);

    void on_comboBox_D10bit7_activated(int index);

    void on_pushButton_ZZ_zz1_zxsmms_clicked();

    void on_pushButton_ZZ_zz2_zxsmms_clicked();

    void on_pushButton_ZZ_zz3_zxsmms_2_clicked();

    void on_pushButton_ZZ_zz4_zxsmms_2_clicked();

    void on_lineEdit_LDpdsm_5_textChanged(const QString &arg1);

    void on_lineEdit_LDqzgr_8_textChanged(const QString &arg1);

    void on_pB_clearOnly_clicked();

    void on_comboBox_T1_4_currentIndexChanged(int index);

    void on_comboBox_T2_zcbz_currentIndexChanged(int index);

    void on_lineEdit_T1_5_textChanged(const QString &arg1);

    void on_lineEdit_T2_cytxzs_textChanged(const QString &arg1);

    void on_comboBox_D4_currentIndexChanged(int index);

    void on_comboBox_E3_currentIndexChanged(int index);

    void on_comboBox_D14_activated(int index);

    void on_comboBox_E9_activated(int index);

    void on_pushButton_GR1_zxsm_4_clicked();

    void on_cB_L5_zz1_2_activated(int index);

    void on_cB_L5_zz2_2_activated(int index);

    void on_cB_L5_zz3_2_activated(int index);


    void on_cB_L5_zz4_2_activated(int index);

    void on_comboBox_DHtxuse_currentIndexChanged(int index);

    void on_lineEdit_L5G_six6_textChanged(const QString &arg1);

    void on_lineEdit_T13jsjpl_textChanged(const QString &arg1);

    void on_lineEdit_grglht_1_textChanged(const QString &arg1);

    void on_lineEdit_grfdzb_1_textChanged(const QString &arg1);

    void on_lineEdit_grglht_2_textChanged(const QString &arg1);

    void on_lineEdit_grfdzb_2_textChanged(const QString &arg1);

    void on_lineEdit_T14jsjpl_textChanged(const QString &arg1);

    void on_lineEdit_T15jsjpl_textChanged(const QString &arg1);

    void on_lineEdit_T16jsjpl_textChanged(const QString &arg1);

    void on_lineEdit_T17jsjpl_textChanged(const QString &arg1);

    void on_lineEdit_LDqzgr_1_textChanged(const QString &arg1);

    void on_lineEdit_F6_4_textChanged(const QString &arg1);

    void on_lineEdit_F6_5_textChanged(const QString &arg1);

    void on_lineEdit_tab9_xl4_textChanged(const QString &arg1);

    void on_lineEdit_szpds_textChanged(const QString &arg1);


    void on_lineEdit_T15ppsum_textChanged(const QString &arg1);

    void on_pB_chooseSarFile_2_clicked();

    void on_pushButton_sarClear_2_clicked();


    void on_pushButton_bbh_nomorl_2_clicked();

    void on_comboBox_C12_2_activated(const QString &arg1);
    void on_comboBox_C13_2_activated(const QString &arg1);
    void on_comboBox_C14_2_activated(const QString &arg1);
    void on_comboBox_C15_2_activated(const QString &arg1);
    void on_comboBox_C16_2_activated(const QString &arg1);
    void on_comboBox_C17_2_activated(const QString &arg1);
    void on_comboBox_C18_2_activated(const QString &arg1);
    void on_comboBox_C19_2_activated(const QString &arg1);
    void on_comboBox_C19_3_activated(const QString &arg1);
    void on_comboBox_C19_4_activated(const QString &arg1);
    void on_comboBox_C19_5_activated(const QString &arg1);
    void on_comboBox_C19_6_activated(const QString &arg1);
    void on_comboBox_C19_7_activated(const QString &arg1);
    void on_comboBox_C19_8_activated(const QString &arg1);
    void on_comboBox_C19_9_activated(const QString &arg1);
    void on_comboBox_C19_10_activated(const QString &arg1);

    void on_comboBox_tz2_activated(int index);

    void on_comboBox_D7_3_activated(int index);

    void on_comboBox_C3_2_activated(int index);

    void on_checkBox_D10bit0_3_clicked(bool checked);

    void on_checkBox_D10bit1_3_clicked(bool checked);

    void on_checkBox_D10bit2_3_clicked(bool checked);

    void on_checkBox_D10bit3_3_clicked(bool checked);

    void on_comboBox_E7bit5_activated(int index);

    void on_comboBox_sorftBb_activated(int index);

signals:
    void Add_Order_ToList(QVariant varData);

private:
    Ui::sub1553_Overheadtask *ui;
};

#endif  // sub1553_Overheadtask_H
