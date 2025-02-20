#include "subyc_slowspeed.h"

#include <QThread>

#include "Globel_Define.h"
#include "ui_subyc_slowspeed.h"
#include <QSqlQuery>

using namespace std;
subyc_slowspeed::subyc_slowspeed(QWidget *parent)
    : QWidget(parent), ui(new Ui::subyc_slowspeed) {
    ui->setupUi(this);

//                qDebug()<<sizeof (slow_Group_1);
//                qDebug()<<sizeof (slow_Group_2);
//                qDebug()<<sizeof (slow_Group_3);

    // 修改界面表格
    model = new QStandardItemModel(ui->tView_yclist);

    g4_YC_Flag=0;//第四组遥测类型标志
    Outslow_dj=0;

    Init_ViewList();//遥测字段名
    Init_DBList();  //数据库字段名


    ////////////////////////////////////////////内容映射
    //第一组 综合管控单元-维护状态
    g1_gkUpstatus[0]="无:[0]";
    g1_gkUpstatus[1]="传输数据:[1]";
    g1_gkUpstatus[2]="帧序号检查:[2]";
    g1_gkUpstatus[3]="帧序号检查失败:[3]";
    g1_gkUpstatus[4]="帧序号检查成功:[4]";
    g1_gkUpstatus[5]="软件包合并:[5]";
    g1_gkUpstatus[6]="无有效数据块:[6]";
    g1_gkUpstatus[7]="写管控Flash:[7]";
    g1_gkUpstatus[8]="写管控Flash成功:[8]";
    g1_gkUpstatus[9]="RapidI0写高算力:[9]";
    g1_gkUpstatus[10]="RapidI0高算力更新进度:[10]";
    g1_gkUpstatus[11]="高算力更新完成:[11]";
    g1_gkUpstatus[12]="软件包缓存申请失败:[12]";
    g1_gkUpstatus[13]="软件包合并长度不匹配:[13]";
    g1_gkUpstatus[14]="软件包校验失败:[14]";
    g1_gkUpstatus[15]="软件属性匹配失败:[15]";
    g1_gkUpstatus[16]="高算力更新查询超时:[16]";
    g1_gkUpstatus[17]="高算力擦除进度查询:[17]";
    g1_gkUpstatus[18]="高算力擦除进度查询超时:[18]";
    g1_gkUpstatus[19]="Can模式写高算力:[19]";
    g1_gkUpstatus[20]="Can模式高算力更新进度:[20]";
    g1_gkUpstatus[21]="管控机擦除:[21]";
    g1_gkUpstatus[22]="读6GB:[22]";
    g1_gkUpstatus[23]="读6GB失败:[23]";
    g1_gkUpstatus[24]="管控机擦除Flash失败:[24]";
    g1_gkUpstatus[25]="管控写Flash失败:[25]";
    g1_gkUpstatus[26]="千兆回传开始:[26]";
    g1_gkUpstatus[27]="千兆回传结束:[27]";
    g1_gkUpstatus[28]="配置表校验成功:[28]";
    g1_gkUpstatus[29]="配置表校验失败:[29]";
    g1_gkUpstatus[30]="管控机写MRAM长度1错误:[30]";
    g1_gkUpstatus[31]="管控机写MRAM长度2错误:[31]";
    g1_gkUpstatus[32]="管控机写MRAM成功:[32]";
    g1_gkUpstatus[33]="RapidIO写高算力失败:[33]";
    g1_gkUpstatus[34]="内存下卸开始:[34]";
    g1_gkUpstatus[35]="内存下卸强制停止:[35]";
    g1_gkUpstatus[36]="手动软刷新开始:[36]";
    g1_gkUpstatus[37]="手动软刷新结束:[37]";

    //SAR成像-系统工作状态
    g2_SAR_workmode[0]="初态、待命及关机状态";
    for (int i=1;i<65;i++) {
        g2_SAR_workmode[i]="成像/子条带序号"+QString::number(i);
    }
    g2_SAR_workmode[80]="首噪声定标:[80]";
    g2_SAR_workmode[81]="首参考定标:[81]";
    g2_SAR_workmode[82]="首单T/R发射定标:[82]";
    g2_SAR_workmode[83]="首单T/R接收定标:[83]";
    g2_SAR_workmode[84]="首逐行发射定标:[84]";
    g2_SAR_workmode[85]="首逐行接收定标:[85]";
    g2_SAR_workmode[86]="首全阵面发射定标:[86]";
    g2_SAR_workmode[87]="首全阵面接收定标:[87]";
    g2_SAR_workmode[96]="尾噪声定标:[96]";
    g2_SAR_workmode[97]="尾参考定标:[97]";
    g2_SAR_workmode[98]="尾单T/R发射定标:[98]";
    g2_SAR_workmode[99]="尾单T/R接收定标:[99]";
    g2_SAR_workmode[100]="尾逐行发射定标:[100]";
    g2_SAR_workmode[101]="尾逐行接收定标:[101]";
    g2_SAR_workmode[102]="尾逐行接收定标:[102]";
    g2_SAR_workmode[103]="尾全阵面接收定标:[103]";
    g2_SAR_workmode[160]="连续噪声定标:[160]";
    g2_SAR_workmode[161]="连续参考定标:[161]";
    g2_SAR_workmode[162]="连续单T/R发射定标:[162]";
    g2_SAR_workmode[163]="连续单T/R接收定标:[163]";
    g2_SAR_workmode[164]="连续逐行发射定标:[164]";
    g2_SAR_workmode[165]="连续逐行接收定标:[165]";
    g2_SAR_workmode[166]="连续全阵面发射定标:[166]";
    g2_SAR_workmode[167]="连续全阵面接收定标:[167]";


    //1553B指令执行结果
    g1_orderResuit[0]="无效0";
    g1_orderResuit[1]="正常";
    g1_orderResuit[2]="第1层长度错误";
    g1_orderResuit[3]="第2层长度错误";
    g1_orderResuit[4]="第1层校验失败";
    g1_orderResuit[5]="第2层校验失败";
    g1_orderResuit[6]="模式码指令参数错误";
    g1_orderResuit[7]="未在上注传输阶段";
    g1_orderResuit[8]="上注块为空";
    g1_orderResuit[9]="总线注数的头帧序号非0";
    g1_orderResuit[10]="总线注数的帧标志错误";
    g1_orderResuit[11]="功能码错误";
    g1_orderResuit[12]="不是待机状态,不能上注配置表";
    g1_orderResuit[13]="上注块内存申请失败";
    g1_orderResuit[14]="正在上注阶段";
    g1_orderResuit[15]="不是待机状态，不能回传";
    g1_orderResuit[16]="上注回传的偏移长度错误";
    g1_orderResuit[17]="上注类型错误";
    g1_orderResuit[18]="不是待机状态，不能上注";
    g1_orderResuit[19]="CAN透传指令的目的地错误";
    g1_orderResuit[20]="管控指令输入数据为空或长度为0";
    g1_orderResuit[21]="总线注数指令ID错误";
    g1_orderResuit[22]="总线注数指令参数错误";
    g1_orderResuit[23]="任务执行类型错误";
    g1_orderResuit[24]="任务执行功能模式错误次数";
    g1_orderResuit[25]="任务执行非待机状态";
    g1_orderResuit[26]="任务执行的类型和ID不匹配";
    g1_orderResuit[27]="更新指令长度为0无效";
    g1_orderResuit[28]="更新指令匹配错误";
    g1_orderResuit[29]="更新指令管控机选择错误";
    g1_orderResuit[30]="高算力更新CAN通道仅支持NORFLASH";
    g1_orderResuit[31]="更新指令高算力更新SIRO通道未连接";
    g1_orderResuit[32]="更新指令高算力选择FLASH错误";
    g1_orderResuit[33]="更新指令高算力选择通道错误";
    g1_orderResuit[34]="更新指令选择设备错误";
    g1_orderResuit[35]="更新指令选择数据源错误";
    g1_orderResuit[36]="指令执行失败";
    g1_orderResuit[37]="总线指令ID错误";
    g1_orderResuit[38]="总线指令参数错误";
    g1_orderResuit[39]="总线指令的电控制保护";
    g1_orderResuit[40]="任务数据输入为空";
    g1_orderResuit[41]="任务数据检查有误";
    g1_orderResuit[42]="非待机状态不能三模运维";
    g1_orderResuit[43]="正在执行三模运维";
    g1_orderResuit[44]="非区域任务状态";
    g1_orderResuit[45]="非常规任务状态";
    g1_orderResuit[46]="非待机状态不能更新";
    g1_orderResuit[47]="无匹配模板";
    g1_orderResuit[48]="正在下电部署";
    g1_orderResuit[49]="独立事件正在执行";
    g1_orderResuit[50]="RapidIO输出占用";


    g1_gk_workmode[0]="待机";
    g1_gk_workmode[1]="维护";
    g1_gk_workmode[2]="无匹配任务";
    g1_gk_workmode[3]="部署上电";
    g1_gk_workmode[4]="功能时段结束";
    g1_gk_workmode[5]="部署下电";
    g1_gk_workmode[6]="模式运行-电子侦察";
    g1_gk_workmode[7]="模式运行-L频段电子干扰";
    g1_gk_workmode[8]="模式运行-SXKu电子干扰";
    g1_gk_workmode[9]="模式运行-SAR";
    g1_gk_workmode[10]="模式运行-备用导航";
    g1_gk_workmode[11]="模式运行-L频段类5G";
    g1_gk_workmode[12]="模式运行-SXKu频段类5G";
    g1_gk_workmode[13]="模式运行-J链";
    g1_gk_workmode[14]="模式运行-SXKu频段定标";
    g1_gk_workmode[15]="任务-空闲";


    g3_SARmode[0]="初始化";
    g3_SARmode[1]="SAR成像";
    g3_SARmode[2]="电子干扰";
    g3_SARmode[3]="数据通信";
    g3_SARmode[4]="备用导航";
    g3_SARmode[5]="电子侦察";
    g3_SARmode[6]="数据通信-J";
    g3_SARmode[7]="雷达自主引导干扰";
    g3_SARmode[8]="连续波TR测试定标";


    g3_FPGA_Status[0]="空闲";
    g3_FPGA_Status[1]="任务信息错误";
    g3_FPGA_Status[2]="收到任务待执行";
    g3_FPGA_Status[3]="开始指令错误";
    g3_FPGA_Status[4]="任务初始化";
    g3_FPGA_Status[5]="侦察-全景采集";
    g3_FPGA_Status[6]="侦察-频点扫描";
    g3_FPGA_Status[7]="侦察-频点控守";
    g3_FPGA_Status[8]="干扰-强制";
    g3_FPGA_Status[9]="干扰-自主";
    g3_FPGA_Status[10]="干扰-引导";
    g3_FPGA_Status[11]="备用导航";
    g3_FPGA_Status[12]="类5G";
    g3_FPGA_Status[13]="SXKU定标";
    g3_FPGA_Status[14]="J链";
    g3_FPGA_Status[15]="SAR";

    //第四组侦察 V7运行模式
    g4_ZC_yxMode[0]="空闲";
    g4_ZC_yxMode[1]="全景";
    g4_ZC_yxMode[2]="采集";
    g4_ZC_yxMode[3]="识别";
    g4_ZC_yxMode[4]="Link16";
    g4_ZC_yxMode[5]="tancan";
    g4_ZC_yxMode[6]="IFF";
    g4_ZC_yxMode[7]="软件上载";
    g4_ZC_yxMode[8]="测试数传";

    //第四组侦察 V7运行状态
    g4_ZC_yxStas[0]="正常";
    g4_ZC_yxStas[1]="校验和出错";
    g4_ZC_yxStas[2]="同步头出错";
    g4_ZC_yxStas[3]="指令参数出错";
    g4_ZC_yxStas[4]="全景执行出错";

    //第四组SAR 校正流程遥测-射频选择
    g4_SAR_sp[0]="DAC1DAC2DAC3输出";
    g4_SAR_sp[1]="DAC1DAC2输出,DAC3不输出";
    g4_SAR_sp[2]="DAC1DAC3输出,DAC2不输出";
    g4_SAR_sp[3]="DAC2DAC3输出,DAC1不输出";
    g4_SAR_sp[4]="DAC2DAC3_2输出,其余不输出";
    g4_SAR_sp[5]="DAC1_2输出,其余不输出";
    g4_SAR_sp[6]="DAC2_1输出,其余不输出";
    g4_SAR_sp[7]="DAC2_2输出,其余不输出";
    g4_SAR_sp[8]="DAC3_1输出,其余不输出";

}

subyc_slowspeed::~subyc_slowspeed() {
    delete ui;
}

double subyc_slowspeed::ret_fun100(double k, double c, double N) {
    double y = 0;
    y = k * N + c;
    return y;
}

double subyc_slowspeed::ret_fun104(double a, double b, double k, double c,int Rf, double d, double e, double f,double N) {
    double V = 0;
    if (N == 0)
        V = 0;
    else
        V = k * (a * N + b) + c;
    double Rt = Rf * (V / (5 - V));
    double T = 0;
    T = 2 * f / (-e + sqrt(e * e - 4 * f * (d - log(Rt)))) - 273.15;
    return T;
}

//温度计数新公式
double subyc_slowspeed::ret_fun104_tmp(int R25,int B,double N)
{
    double V=N*5.0/255.0;
    double Rt=(4700.0*V)/(4.65-V);
    double T=(298.15*B)/(B-298.15*log(R25/Rt))-273.15;
    return T;

}

QString subyc_slowspeed::ret_fun114(int yy, int mm, int nn, int h, int m, int s,int k, int Md) {
    QDateTime T0;
    T0.setDate(QDate(yy, mm, nn));
    T0.setTime(QTime(h, m, s));
    qint64 sec = k * Md / 10000;
    Q_UNUSED(sec);
    //QDateTime T = T0.QDateTime::addSecs(sec);
    return T0.toString();
}

QString subyc_slowspeed::ret_fun118(int yy, int mm, int nn, int h, int m, int s,int Md) {
    Q_UNUSED(Md);
    QDateTime T0;
    T0.setDate(QDate(yy, mm, nn));
    T0.setTime(QTime(h, m, s));
    // QDateTime T = T0.QDateTime::addSecs(Md);
    return T0.toString();
}

double subyc_slowspeed::ret_fun124(double a, double b, double k, double c,double N) {
    double V = 0;
    if(N==0) return 0;
    V = k * (a * N + b) + c;
    return V;
}
//初始化列表显示
void subyc_slowspeed::Init_ViewList()
{

    model->clear();
    // 慢速遥测值名称
    // 第一组////////////////////////////////////////////////////////////////
    if (ui->radioButton_group1->isChecked()) {
        QStringList m_name_list;
        m_name_list.append("一遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("二遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("三遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("四遥测名称");
        m_name_list.append("遥测数值");
        int num = m_name_list.size();
        model->setColumnCount(num);
        model->setRowCount(0);
        for (int i = 0; i < num; i++) {
            model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
        }


        QStringList msyc_strName1_1;
        msyc_strName1_1.append("综合管控单元_重构进行状态");
        msyc_strName1_1.append("综合管控单元_重传标志");
        msyc_strName1_1.append("综合管控单元_重传前进通道");
        msyc_strName1_1.append("综合管控单元_重传包个数");
        msyc_strName1_1.append("综合管控单元_重传包位序号计数");


        msyc_strName1_1.append("L频段_触发PRF监测遥测");
        msyc_strName1_1.append("L频段_计算机状态监测遥测");
        msyc_strName1_1.append("L频段_总线状态监测遥测");
        msyc_strName1_1.append("L频段_数字综合单元主机电源");
        msyc_strName1_1.append("L频段_数字综合单元备机电源");
        msyc_strName1_1.append("L频段_组合定标功放电源监测");
        msyc_strName1_1.append("L频段_其他电源监测");
        msyc_strName1_1.append("L频段_射频收发模块1_2输出监测");
        msyc_strName1_1.append("L频段_射频收发模块3_6输出监测");
        msyc_strName1_1.append("L频段_组合定标模块输出监测");
        msyc_strName1_1.append("L频段_定时波控3_3V监测");
        msyc_strName1_1.append("L频段_定时波控主5V监测");
        msyc_strName1_1.append("L频段_定时波控备5V监测");
        msyc_strName1_1.append("L频段_阵面1天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面1天线发射电源开关状态");
        msyc_strName1_1.append("L频段_阵面2天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面2天线发射电源开关状态");
        msyc_strName1_1.append("L频段_阵面3天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面3天线发射电源开关状态");
        msyc_strName1_1.append("L频段_阵面4天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面4天线发射电源开关状态");


        msyc_strName1_1.append("SXKu频段_消浪涌开关遥测");
        msyc_strName1_1.append("SXKu频段_放电开关遥测");
        msyc_strName1_1.append("SXKu频段_波束控制器主机开关遥测");
        msyc_strName1_1.append("SXKu频段_波束控制器备机开关遥测");
        msyc_strName1_1.append("SXKu频段_波控机主机5V遥测");
        msyc_strName1_1.append("SXKu频段_波控机备机5V遥测");
        msyc_strName1_1.append("SxKu频段模块3二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块3二次电源发射开关遥测");
        msyc_strName1_1.append("SxKu频段模块1二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块1二次电源发射开关遥测");
        msyc_strName1_1.append("SxKu频段模块4二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块4二次电源发射开关遥测");
        msyc_strName1_1.append("SxKu频段模块2二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块2二次电源发射开关遥测");

        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态1");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态2");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态3");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态4");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态5");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态6");
        msyc_strName1_1.append("SXKu频段_射频收发接收电");
        msyc_strName1_1.append("SXKu频段_射频收发发射电");



        for (int i = 0; i < msyc_strName1_1.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName1_1.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            //table_item->setBackground(QBrush(QColor(250,150,150)));//淡红色
            model->setItem(i, 0, table_item);

        }

        QStringList msyc_strName1_2;
        msyc_strName1_2.append("载荷_A组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_B组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_C组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_D组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_A组母线电压遥测");
        msyc_strName1_2.append("载荷_B组母线电压遥测");
        msyc_strName1_2.append("载荷_C组母线电压遥测");
        msyc_strName1_2.append("载荷_D组母线电压遥测");

        msyc_strName1_2.append("可重构射频前端主份+6VA供电");
        msyc_strName1_2.append("可重构射频前端主份-6VA供电");
        msyc_strName1_2.append("可重构射频前端主份+15VA供电");
        msyc_strName1_2.append("可重构射频前端主份+5VD供电");
        msyc_strName1_2.append("可重构射频前端主份+6V2A供电");
        msyc_strName1_2.append("可重构射频前端备份+6VA供电");
        msyc_strName1_2.append("可重构射频前端备份-6VA供电");
        msyc_strName1_2.append("可重构射频前端备份+15VA供电");
        msyc_strName1_2.append("可重构射频前端备份+5VD供电");
        msyc_strName1_2.append("可重构射频前端备份+6V2A供电");

        msyc_strName1_2.append("可重构算力1供电遥测_+6VA");
        msyc_strName1_2.append("可重构算力1路1遥测_+5VD");
        msyc_strName1_2.append("可重构算力1路2遥测_+5VD");
        msyc_strName1_2.append("可重构算力1路3遥测_+5VD");
        msyc_strName1_2.append("可重构算力1路4遥测_+5VD");
        msyc_strName1_2.append("可重构算力2供电遥测_+6VA");
        msyc_strName1_2.append("可重构算力2路1遥测_+5VD");
        msyc_strName1_2.append("可重构算力2路2遥测_+5VD");
        msyc_strName1_2.append("可重构算力2路3遥测_+5VD");
        msyc_strName1_2.append("可重构算力2路4遥测_+5VD");
        for (int i = 0; i < msyc_strName1_2.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName1_2.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 2, table_item);
            //model->setItem(i, 2, new QStandardItem(msyc_strName1_2.at(i)));
        }
        QStringList msyc_strName1_3;
        msyc_strName1_3.append("L频段_天线收发状态");
        msyc_strName1_3.append("SXKu频段_天线收发状态");

        msyc_strName1_3.append("高算力1_接口控制模块DSP6678心跳");
        msyc_strName1_3.append("高算力1_接口控制模块DSP6701加载状态");
        msyc_strName1_3.append("高算力1_接口控制模块DSP6678加载状态");
        msyc_strName1_3.append("高算力1_接口控制模块V7加载状态");
        msyc_strName1_3.append("高算力1_收发处理模块K7加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块A的K7加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块B的K7加载状态");

        msyc_strName1_3.append("高算力1_收发处理模块V7_1加载状态");
        msyc_strName1_3.append("高算力1_收发处理模块V7_2加载状态");

        msyc_strName1_3.append("高算力1_数据处理模块A_DSP6678心跳");
        msyc_strName1_3.append("高算力1_数据处理模块A_DSP6678加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块A_V7_1加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块A_V7_2加载状态");

        msyc_strName1_3.append("高算力1_数据处理模块B_DSP6678心跳");
        msyc_strName1_3.append("高算力1_数据处理模块B_DSP6678加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块B_V7_1加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块B_V7_2加载状态");


        msyc_strName1_3.append("高算力2_接口控制模块DSP6678心跳");
        msyc_strName1_3.append("高算力2_接口控制模块DSP6701加载状态");
        msyc_strName1_3.append("高算力2_接口控制模块DSP6778加载状态");
        msyc_strName1_3.append("高算力2_接口控制模块V7加载状态");
        msyc_strName1_3.append("高算力2_收发处理模块K7加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块A的K7加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块B的K7加载状态");

        msyc_strName1_3.append("高算力2_收发处理模块_V7_1加载状态");
        msyc_strName1_3.append("高算力2_收发处理模块_V7_2加载状态");

        msyc_strName1_3.append("高算力2_数据处理模块A_DSP6678心跳");
        msyc_strName1_3.append("高算力2_数据处理模块A_DSP6678加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块A_V7_1加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块A_V7_2加载状态");

        msyc_strName1_3.append("高算力2_数据处理模块B_DSP6678心跳");
        msyc_strName1_3.append("高算力2_数据处理模块B_DSP6678加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块B_V7_1加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块B_V7_2加载状态");
        for (int i = 0; i < msyc_strName1_3.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName1_3.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 4, table_item);
            //model->setItem(i, 4, new QStandardItem(msyc_strName1_3.at(i)));
        }

        QStringList msyc_strName1_4;


        msyc_strName1_4.append("CAN通道A复位次数");
        msyc_strName1_4.append("CAN通道B复位次数");
        msyc_strName1_4.append("L频段_CAN接收异常帧次数");
        msyc_strName1_4.append("SXKu频段_CAN接收异常帧次数");
        msyc_strName1_4.append("射频前端_CAN接收异常帧次数");
        msyc_strName1_4.append("高算力1_CAN接收异常帧次数");
        msyc_strName1_4.append("高算力2_CAN接收异常帧次数");

        msyc_strName1_4.append("L频段_CAN接收计数");//
        msyc_strName1_4.append("SXKu频段_CAN接收计数");//
        msyc_strName1_4.append("射频前端_CAN接收计数");//
        msyc_strName1_4.append("高算力1_CAN接收计数");//
        msyc_strName1_4.append("高算力2_CAN接收计数");//

        msyc_strName1_4.append("1553B总线指令接收帧计数");
        msyc_strName1_4.append("1553B总线注数接收帧计数");//
        msyc_strName1_4.append("1553B总线帧接收异常次数");
        msyc_strName1_4.append("1553B总线复位次数");
        msyc_strName1_4.append("1553B指令执行结果_上一帧");
        msyc_strName1_4.append("1553B指令执行结果_当前帧");
        msyc_strName1_4.append("管控机星时");//后面移动到前面
        msyc_strName1_4.append("综合管控单元_工作状态");
        msyc_strName1_4.append("有效任务总数");
        msyc_strName1_4.append("已存任务总数");
        msyc_strName1_4.append("当前执行任务的流水号");
        msyc_strName1_4.append("高算力1处理FPGA1执行的主任务ID");
        msyc_strName1_4.append("高算力1处理FPGA2执行的主任务ID");
        msyc_strName1_4.append("高算力1处理FPGA3执行的主任务ID");
        msyc_strName1_4.append("高算力1处理FPGA4执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA1执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA2执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA3执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA4执行的主任务ID");


        msyc_strName1_4.append("管控_高算力1工作频段");
        msyc_strName1_4.append("管控_高算力2工作频段");
        msyc_strName1_4.append("管控_高算力1主从状态");
        msyc_strName1_4.append("管控_高算力2主从状态");

        msyc_strName1_4.append("管控单元_软件上注块存储快状态");
        msyc_strName1_4.append("管控单元_Can软件更新进度或6G刷新进度");
        msyc_strName1_4.append("千兆网口或1553B重构数据接收帧计数");
        msyc_strName1_4.append("千兆网口软件发送帧计数");
        msyc_strName1_4.append("管控单元_维护状态");
        for (int i = 0; i < msyc_strName1_4.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName1_4.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 6, table_item);
            //model->setItem(i, 6, new QStandardItem(msyc_strName1_4.at(i)));
        }


    }

    ///////////////////////////////////////////////////////////////////////////////////
    // 第二组
    if (ui->radioButton_group2->isChecked()) {
        QStringList m_name_list;
        m_name_list.append("一遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("二遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("三遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("四遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("五遥测名称");
        m_name_list.append("遥测数值");
        int num = m_name_list.size();
        model->setColumnCount(num);
        model->setRowCount(0);
        for (int i = 0; i < num; i++) {
            model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
        }


        QStringList msyc_strName2_1;
        msyc_strName2_1.append("L频段相控阵天线_波控发射PRF监测");
        msyc_strName2_1.append("L频段相控阵天线_波控接收PRF监测");

        msyc_strName2_1.append("L频段相控阵天线_天线子阵1通道1 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵1通道2 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵3通道2 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵3通道3 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵2通道4 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵2通道5 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵4通道5 ");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵4通道6 ");

        msyc_strName2_1.append("SAR成像_系统工作状态");
        msyc_strName2_1.append("SAR成像_SAR分系统状态");
        msyc_strName2_1.append("SAR成像_指令接收/处理状态");
        msyc_strName2_1.append("SAR成像_EDAC错误计数");
        msyc_strName2_1.append("SAR成像_CPU复位计数");
        msyc_strName2_1.append("SAR成像_CAN总线复位计数");
        msyc_strName2_1.append("SAR成像_收指令计数");

        msyc_strName2_1.append("L频段相控阵天线-射频收发单元-开关状态");

        msyc_strName2_1.append("SXKu_射频收发单元_开关状态");

        msyc_strName2_1.append("高算力1-V7与交换A光纤建链指示");
        msyc_strName2_1.append("高算力1-V7与交换B光纤建链指示");
        msyc_strName2_1.append("高算力1-V7与管控主Rapid IO建链指示");
        msyc_strName2_1.append("高算力1-V7与管控备Rapid IO建链指示");
        msyc_strName2_1.append("高算力2-V7与交换A光纤建链指示");
        msyc_strName2_1.append("高算力2-V7与交换B光纤建链指示");
        msyc_strName2_1.append("高算力2-V7与管控主Rapid IO建链指示");
        msyc_strName2_1.append("高算力2-V7与管控备Rapid IO建链指示");



        for (int i = 0; i < msyc_strName2_1.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName2_1.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 0, table_item);
            //model->setItem(i, 0, new QStandardItem(msyc_strName2_1.at(i)));
        }

        QStringList msyc_strName2_2;

        msyc_strName2_2.append("高算力1_接口模块_光模块参数更新状态");
        msyc_strName2_2.append("高算力1_接口模块_光模块供电指示(FIBER_3V3PG)");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示(PG_DSPVTT)");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示(PG_DSP1V8)");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示(PG_DSP1V5)");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示(PG_DSP1V0_SMART)");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示(PG_DSP1V0)");

        msyc_strName2_2.append("高算力1_收发模块_FPGA1的1DDRVTT电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_FPGA1的2DDRVTT电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_FPGA2的1DDRVTT电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_FPGA2的2DDRVTT电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_AD1电源1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1_1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1_2V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1.3VA电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源2V电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_AD2电源1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源1_1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源1_2V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源1.3VB电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源2V电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_AD3电源1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD3电源1_1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD3电源1_2V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD3电源2V电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_1.5V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_2_1.5V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1.8V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_2.8V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_模拟3.3V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_模拟3.3_2电源PG指示");

        msyc_strName2_2.append("高算力1_数据处理模块A_光模块参数更新状态");
        msyc_strName2_2.append("高算力1_数据处理模块A_光模块(PG_FIB3V3)");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源(PG_DSPVTT)");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源(PG_DSP1V8)");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源(PG_DSP1V5)");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源(PG_DSP1V0_SMART)");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源(PG_DSP1V0)");

        msyc_strName2_2.append("高算力1_数据处理模块B_光模块参数更新状态");
        msyc_strName2_2.append("高算力1_数据处理模块B_光模块(PG_FIB3V3)");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源(PG_DSPVTT)");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源(PG_DSP1V8)");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源(PG_DSP1V5)");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源(PG_DSP1V0_SMART)");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源(PG_DSP1V0)");

        for (int i = 0; i < msyc_strName2_2.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName2_2.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 2, table_item);
            //model->setItem(i, 2, new QStandardItem(msyc_strName2_2.at(i)));
        }

        QStringList msyc_strName2_3;

        msyc_strName2_3.append("高算力2_接口模块_光模块参数更新状态");
        msyc_strName2_3.append("高算力2_接口模块_光模块供电指示(FIBER_3V3PG)");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示(PG_DSPVTT)");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示(PG_DSP1V8)");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示(PG_DSP1V5)");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示(PG_DSP1V0_SMART)");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示(PG_DSP1V0)");

        msyc_strName2_3.append("高算力2_收发模块_FPGA1的1DDRVTT电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_FPGA1的2DDRVTT电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_FPGA2的1DDRVTT电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_FPGA2的2DDRVTT电源PG指示");

        msyc_strName2_3.append("高算力2_收发模块_AD1电源1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1_1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1_2V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1.3VA电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源2V电源PG指示");

        msyc_strName2_3.append("高算力2_收发模块_AD2电源1V电源PG指示   ");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源1_1V电源PG指示 ");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源1_2V电源PG指示 ");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源1.3VB电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源2V电源PG指示");/////(漏掉了)


        msyc_strName2_3.append("高算力2_收发模块_AD3电源1V电源PG指示   ");
        msyc_strName2_3.append("高算力2_收发模块_AD3电源1_1V电源PG指示 ");
        msyc_strName2_3.append("高算力2_收发模块_AD3电源1_2V电源PG指示 ");
        msyc_strName2_3.append("高算力2_收发模块_AD3电源2V电源PG指示   ");

        msyc_strName2_3.append("高算力2_收发模块_1.5V电源PG指示     ");
        msyc_strName2_3.append("高算力2_收发模块_2_1.5V电源PG指示   ");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1.8V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_2.8V电源PG指示     ");
        msyc_strName2_3.append("高算力2_收发模块_模拟3.3V电源PG指示   ");
        msyc_strName2_3.append("高算力2_收发模块_模拟3.3_2电源PG指示  ");

        msyc_strName2_3.append("高算力2_数据处理理模块A_光模块参数更新状态");
        msyc_strName2_3.append("高算力2_数据处理理模块A_光模块(PG_FIB3V3)");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源(PG_DSPVTT)");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源(PG_DSP1V8)");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源(PG_DSP1V5)");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源(PG_DSP1V0_SMART)");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源(PG_DSP1V0)");

        msyc_strName2_3.append("高算力2_数据处理理模块B_光模块参数更新状态");
        msyc_strName2_3.append("高算力2_数据处理理模块B_光模块(PG_FIB3V3)");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源(PG_DSPVTT)");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源(PG_DSP1V8)");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源(PG_DSP1V5)");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源(PG_DSP1V0_SMART)");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源(PG_DSP1V0)");

        for (int i = 0; i < msyc_strName2_3.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName2_3.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 4, table_item);
            //model->setItem(i, 4, new QStandardItem(msyc_strName2_3.at(i)));
        }

        QStringList msyc_strName2_4;//名称顺序跟后面协议有点不一致，调整顺序方便观看

        msyc_strName2_4.append("高算力1_模块栓锁");
        msyc_strName2_4.append("高算力1_收发处理模块栓锁(收发LRM_PG1)");
        msyc_strName2_4.append("高算力1_数据处理1模块栓锁(数据1LRM_PG2)");
        msyc_strName2_4.append("高算力1_数据处理2模块栓锁(数据2LRM_PG3)");
        msyc_strName2_4.append("高算力1_锁相环(V2_LD1)");
        msyc_strName2_4.append("高算力1_锁相环(V2_LD2)");
        msyc_strName2_4.append("高算力1_锁相环(V2_LD3)");


        msyc_strName2_4.append("高算力1_接口模块_V7与管控RapidIO主备");
        msyc_strName2_4.append("高算力1_接口模块_V7与高速交换机光纤主备");
        msyc_strName2_4.append("高算力1_接口DSP6678与接口控制V7建链指示");
        msyc_strName2_4.append("高算力1_接口DSP6678与数据处理1建链指示");
        msyc_strName2_4.append("高算力1_接口DSP6678与数据处理2建链指示");

        msyc_strName2_4.append("高算力1_接口板V7接收数据计数 ");
        msyc_strName2_4.append("高算力1_接口板V7发送数据计数 ");
        msyc_strName2_4.append("高算力1_接口板DSP6678星时");

        msyc_strName2_4.append("高算力1_收发处理模块_ADC1建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_ADC2建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_ADC3建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_DAC1建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_DAC2建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_DAC3建链指示");
        ///

        msyc_strName2_4.append("高算力2_模块栓锁");
        msyc_strName2_4.append("高算力2_收发处理模块栓锁(收发LRM_PG1)");
        msyc_strName2_4.append("高算力2_数据处理1模块栓锁(数据1LRM_PG2)");
        msyc_strName2_4.append("高算力2_数据处理2模块栓锁(数据2LRM_PG3)");
        msyc_strName2_4.append("高算力2_锁相环(V2_LD1)");
        msyc_strName2_4.append("高算力2_锁相环(V2_LD2)");
        msyc_strName2_4.append("高算力2_锁相环(V2_LD3)");

        msyc_strName2_4.append("高算力2_接口模块_V7与管控RapidIO主备");
        msyc_strName2_4.append("高算力2_接口模块_V7与高速交换机光纤主备");
        msyc_strName2_4.append("高算力2_接口DSP6678与接口控制V7建链指示");
        msyc_strName2_4.append("高算力2_接口DSP6678与数据处理1建链指示");
        msyc_strName2_4.append("高算力2_接口DSP6678与数据处理2建链指示");

        msyc_strName2_4.append("高算力2_接口板V7接收数据计数    ");
        msyc_strName2_4.append("高算力2_接口板V7发送数据计数    ");
        msyc_strName2_4.append("高算力2_接口板DSP6678星时   ");


        msyc_strName2_4.append("高算力2_收发处理模块_ADC1建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_ADC2建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_ADC3建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_DAC1建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_DAC2建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_DAC3建链指示");




        for (int i = 0; i < msyc_strName2_4.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName2_4.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 6, table_item);
            //model->setItem(i, 6, new QStandardItem(msyc_strName2_4.at(i)));
        }

        QStringList msyc_strName2_5;

        msyc_strName2_5.append("管控_OC开关状态_L频段相控阵天线消浪涌");
        msyc_strName2_5.append("管控_OC开关状态_L频段相控阵天线31V总电源");

        msyc_strName2_5.append("管控_综合处理模块_AI电压        ");
        msyc_strName2_5.append("管控_综合处理模块_3个DSP6678总电压");
        //msyc_strName2_5.append("管控_综合处理模块_V7电压        ");

        msyc_strName2_5.append("射频前端_SXKu频段射频通道56");
        msyc_strName2_5.append("射频前端_SXKu频段射频通道34");
        msyc_strName2_5.append("射频前端_SXKu频段射频通道12");
        msyc_strName2_5.append("射频前端_L波段射频切换调理模块遥测量");
        msyc_strName2_5.append("射频前端_中频切换模块1遥测量");
        msyc_strName2_5.append("射频前端_中频切换模块2遥测量");

        msyc_strName2_5.append("射频前端-宽带一本振2主环锁定指示");
        msyc_strName2_5.append("射频前端-宽带一本振2副环锁定指示");
        msyc_strName2_5.append("射频前端-备份高相噪一本振锁定指示");
        msyc_strName2_5.append("射频前端-备份二本振锁定指示");
        msyc_strName2_5.append("射频前端-宽带一本振1主环锁定指示");
        msyc_strName2_5.append("射频前端-宽带一本振1副环锁定指示");
        msyc_strName2_5.append("射频前端-主份高相噪一本振锁定指示");
        msyc_strName2_5.append("射频前端-主份二本振锁定指示");


        msyc_strName2_5.append("L频段相控阵天线_射频综合单元温度");
        msyc_strName2_5.append("L频段相控阵天线_数字综合单机温度");
        msyc_strName2_5.append("高算力1_接口控制模块_V7温度");
        msyc_strName2_5.append("高算力1_收发处理模块_ADC1温度");
        msyc_strName2_5.append("高算力1_收发处理模块_ADC2温度");
        msyc_strName2_5.append("高算力1_收发处理模块_ADC3温度");
        msyc_strName2_5.append("高算力1_收发处理模块_V7_1温度");
        msyc_strName2_5.append("高算力1_收发处理模块_V7_2温度");
        msyc_strName2_5.append("高算力1_数据处理模块A_V7_1温度");
        msyc_strName2_5.append("高算力1_数据处理模块A_V7_2温度");
        msyc_strName2_5.append("高算力1_数据处理模块B_V7_1温度");
        msyc_strName2_5.append("高算力1_数据处理模块B_V7_2温度");
        msyc_strName2_5.append("高算力2_接口控制模块_V7温度");
        msyc_strName2_5.append("高算力2_收发处理模块_ADC1温度");
        msyc_strName2_5.append("高算力2_收发处理模块_ADC2温度");
        msyc_strName2_5.append("高算力2_收发处理模块_ADC3温度");
        msyc_strName2_5.append("高算力2_收发处理模块_V7_1温度");
        msyc_strName2_5.append("高算力2_收发处理模块_V7_2温度");
        msyc_strName2_5.append("高算力2_数据处理模块A_V7_1温度");
        msyc_strName2_5.append("高算力2_数据处理模块A_V7_2温度");
        msyc_strName2_5.append("高算力2_数据处理模块B_V7_1温度");
        msyc_strName2_5.append("高算力2_数据处理模块B_V7_2温度");
        msyc_strName2_5.append("综合管控单元_管控模块_V7温度");
        msyc_strName2_5.append("综合管控单元_综合处理模块_V7温度");
        msyc_strName2_5.append("综合管控单元_综合处理模块_AI温度");
        msyc_strName2_5.append("综合管控单元-温度保护关断温度阈值-高算力1");
        msyc_strName2_5.append("综合管控单元-温度保护关断温度阈值-高算力2");
        msyc_strName2_5.append("高算力1模块A_与高算力2模块A_V7_1时钟锁定");
        msyc_strName2_5.append("高算力1模块A_与高算力2模块A_V7_1建链");
        msyc_strName2_5.append("高算力1模块B_与高算力2模块B_V7_1时钟锁定");
        msyc_strName2_5.append("高算力1模块B_与高算力2模块B_V7_1建链");
        msyc_strName2_5.append("高算力2模块A_与高算力1模块A_V7_1时钟锁定");
        msyc_strName2_5.append("高算力2模块A_与高算力1模块A_V7_1建链");
        msyc_strName2_5.append("高算力2模块B_与高算力1模块B_V7_1时钟锁定");
        msyc_strName2_5.append("高算力2模块B_与高算力1模块B_V7_1建链");



        for (int i = 0; i < msyc_strName2_5.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName2_5.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 8, table_item);
            //model->setItem(i, 8, new QStandardItem(msyc_strName2_5.at(i)));
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    // 第三组
    if (ui->radioButton_group3->isChecked()) {
        QStringList m_name_list;
        m_name_list.append("一遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("二遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("三遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("四遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append("五遥测名称");
        m_name_list.append("遥测数值");
        int num = m_name_list.size();
        model->setColumnCount(num);
        model->setRowCount(0);
        for (int i = 0; i < num; i++) {
            model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
        }


        QStringList msyc_strName3_1;

        msyc_strName3_1.append("高算力1_接口控制模块_V2大,小版本号");

        msyc_strName3_1.append("高算力1_接口控制模块_V7大,小版本号");

        msyc_strName3_1.append("高算力1_接口控制模块_DSP6701大,小版本号");

        msyc_strName3_1.append("高算力1_接口控制模块_DSP6678大,小版本号");

        msyc_strName3_1.append("高算力1_收发处理模块_K7大,小版本号");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_1大,小版本号 ");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_1软件代号");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_2大,小版本号");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_2软件代号");
        msyc_strName3_1.append("高算力1_收发处理模块_K7预加载软件数量");

        msyc_strName3_1.append("高算力1_数据处理模块A_K7大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_1大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_1软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_2大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_2软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块A_DSP6678大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_DSP6678软件代号");
        msyc_strName3_1.append("高算力1_数据处理模块A_K7预加载软件数量");

        msyc_strName3_1.append("高算力1_数据处理模块B_K7大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_1大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_1软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_2大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_2软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块B_DSP6678大,小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_DSP6678软件代号");
        msyc_strName3_1.append("高算力1_数据处理模块B_K7预加载软件数量");

        msyc_strName3_1.append("高算力1_接口V7三模运维状态");
        msyc_strName3_1.append("高算力1_软件引导方式_接口Can解析与重构调度软件");
        msyc_strName3_1.append("高算力1_软件引导方式_接口控制模块综合调度软件");
        msyc_strName3_1.append("高算力1_软件引导方式_数据处理模块A接口控制软件");
        msyc_strName3_1.append("高算力1_软件引导方式_数据处理模块B接口控制软件");
        msyc_strName3_1.append("高算力1_软件引导方式_收发处理模块接口控制软件");
        msyc_strName3_1.append("高算力1_软件引导方式_接口控制模块数据传输软件");


        for (int i = 0; i < msyc_strName3_1.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName3_1.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 0, table_item);
            //model->setItem(i, 0, new QStandardItem(msyc_strName3_1.at(i)));
        }


        QStringList msyc_strName3_2;
        msyc_strName3_2.append("高算力2_接口控制模块_V2大,小版本号");

        msyc_strName3_2.append("高算力2_接口控制模块_V7大,小版本号");

        msyc_strName3_2.append("高算力2_接口控制模块_DSP6701大,小版本号");

        msyc_strName3_2.append("高算力2_接口控制模块_DSP6678大,小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_K7大,小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_1大,小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_1软件代号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_2大,小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_2软件代号");
        msyc_strName3_2.append("高算力2_收发处理模块_K7预加载软件数量");

        msyc_strName3_2.append("高算力2_数据处理模块A_K7大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_1大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_1软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_2大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_2软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块A_DSP6678大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_DSP6678软件代号");
        msyc_strName3_2.append("高算力2_数据处理模块A_K7预加载软件数量");

        msyc_strName3_2.append("高算力2_数据处理模块B_K7大,小版本号 ");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_1大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_1软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_2大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_2软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块B_DSP6678大,小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_DSP6678软件代号");
        msyc_strName3_2.append("高算力2_数据处理模块B_K7预加载软件数量");

        msyc_strName3_2.append("高算力2_接口V7三模运维状态");
        msyc_strName3_2.append("高算力2_软件引导方式_接口Can解析与重构调度软件");
        msyc_strName3_2.append("高算力2_软件引导方式_接口控制模块综合调度软件");
        msyc_strName3_2.append("高算力2_软件引导方式_数据处理模块A接口控制软件");
        msyc_strName3_2.append("高算力2_软件引导方式_数据处理模块B接口控制软件");
        msyc_strName3_2.append("高算力2_软件引导方式_收发处理模块接口控制软件");
        msyc_strName3_2.append("高算力2_软件引导方式_接口控制模块数据传输软件");

        for (int i = 0; i < msyc_strName3_2.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName3_2.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 2, table_item);
            //model->setItem(i, 2, new QStandardItem(msyc_strName3_2.at(i)));
        }

        QStringList msyc_strName3_3;
        msyc_strName3_3.append("综合管控单元_管控模块_P2020大,小版本号");

        msyc_strName3_3.append("综合管控单元_管控模块_V7大,小版本号");

        msyc_strName3_3.append("综合管控单元_综合处理模块_V7大,小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_1大,小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_2大,小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_3大,小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_AI大,小版本号");

        msyc_strName3_3.append("综合管控单元_卫星编号");
        msyc_strName3_3.append("综合管控单元_轨道编号");

        msyc_strName3_3.append("综合管控单元_管控模块_V2看门狗使能");
        msyc_strName3_3.append("综合管控单元_主副卫星");
        msyc_strName3_3.append("综合管控单元_CAN应用通道");
        msyc_strName3_3.append("综合管控单元_千兆网应用通道");

        msyc_strName3_3.append("综合管控单元_任务自动清除使能");
        msyc_strName3_3.append("综合管控单元_区域或常规任务状态选择");

        msyc_strName3_3.append("综合管控单元_模板数量");
        msyc_strName3_3.append("综合管控单元_SSD存储余量");

        msyc_strName3_3.append("管控_flash软刷周期使能");
        msyc_strName3_3.append("管控_高算力1_接收机自动增益控制状态 ");
        msyc_strName3_3.append("管控_高算力2_接收机自动增益控制状态 ");
        msyc_strName3_3.append("管控_高算力1_接口板V7软件维护状态 ");
        msyc_strName3_3.append("管控_高算力2_接口板V7软件维护状态 ");
        msyc_strName3_3.append("管控_V7刷新芯片控制标志 ");
        msyc_strName3_3.append("管控_温度保护关断功能使能标志");

        msyc_strName3_3.append("管控_管控模块向平台发送数据计数");
        msyc_strName3_3.append("管控_管控接收路由数据计数 ");
        msyc_strName3_3.append("管控_管控向路由发送数据计数");

        msyc_strName3_3.append("管控_1553B长抱环计数");
        msyc_strName3_3.append("管控_1553B系统同步计数");
        msyc_strName3_3.append("管控_管控机关机准备次数   ");
        msyc_strName3_3.append("管控_下控单机关机准备次数  ");

        for (int i = 0; i < msyc_strName3_3.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName3_3.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 4, table_item);
            //model->setItem(i, 4, new QStandardItem(msyc_strName3_3.at(i)));
        }

        QStringList msyc_strName3_4;
        msyc_strName3_4.append("管控_万兆网路由连接状态主");
        msyc_strName3_4.append("管控_万兆网路由连接状态备");
        msyc_strName3_4.append("管控_管控模块V7与P2020互联的SRIOx1链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与P2020互联的SRIOx1端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力2互联的SRIOx2链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力2互联的SRIOx2端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力1互联的SRIOx2链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力1互联的SRIOx2端口初始化信号");

        msyc_strName3_4.append("管控_处理模块V7与810A互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与810A互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP0互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP0互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP1互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP1互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP2互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP2互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第0路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第0路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第1路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第1路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第0路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第0路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第1路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第1路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_V7万兆网与存储连接状态");
        msyc_strName3_4.append("管控_P2020软件引导方式");
        msyc_strName3_4.append("管控_综合管控模块_V7软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_V7软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_1软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_2软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_3软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_AI软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_1启动状态");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_2启动状态");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_3启动状态");
        msyc_strName3_4.append("管控_综合处理模块_AI启动状态");
        msyc_strName3_4.append("管控_SRIO接收异常帧次数");
        msyc_strName3_4.append("管控_累计已运行任务总数");
        msyc_strName3_4.append("管控_即将执行的任务时间");

        for (int i = 0; i < msyc_strName3_4.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName3_4.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 6, table_item);
            //model->setItem(i, 6, new QStandardItem(msyc_strName3_4.at(i)));
        }

        QStringList msyc_strName3_5;
        msyc_strName3_5.append("SAR成像-串注间接指令码特征码");
        msyc_strName3_5.append("SAR成像-导航闭锁信号");
        msyc_strName3_5.append("SAR-任务模式");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵1-子板1");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵1-子板2");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵2-子板1");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵2-子板2");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵3-子板1");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵3-子板2");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵4-子板1");
        msyc_strName3_5.append("SAR-L频段天线波控加载方式-子阵4-子板2");

        msyc_strName3_5.append("高算力1-数据处理模块A-FPGAV7-1任务状态");
        msyc_strName3_5.append("高算力1-数据处理模块A-FPGAV7-2任务状态");
        msyc_strName3_5.append("高算力1-数据处理模块B-FPGAV7-1任务状态");
        msyc_strName3_5.append("高算力1-数据处理模块B-FPGAV7-2任务状态");
        msyc_strName3_5.append("高算力2-数据处理模块A-FPGAV7-1任务状态");
        msyc_strName3_5.append("高算力2-数据处理模块A-FPGAV7-2任务状态");
        msyc_strName3_5.append("高算力2-数据处理模块B-FPGAV7-1任务状态");
        msyc_strName3_5.append("高算力2-数据处理模块B-FPGAV7-2任务状态");


        for (int i = 0; i < msyc_strName3_5.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName3_5.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 8, table_item);
            //model->setItem(i, 8, new QStandardItem(msyc_strName3_5.at(i)));
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////
    // 第四组
    if (ui->radioButton_group4->isChecked()) {

        map<int,QString> type_name;
        type_name[0x3507]="电子侦察任务包:";
        type_name[0x3607]="电子干扰任务包:";
        type_name[0x3707]="SAR成像任务包:";
        type_name[0x3807]="备用导航任务包:";
        type_name[0x3907]="类5G通信任务包:";
        type_name[0x3A07]="管控遥测:";

        QStringList m_name_list;
        m_name_list.append(type_name[g4_YC_Flag]+"一遥测名称");
        m_name_list.append("遥测数值");
        m_name_list.append(type_name[g4_YC_Flag]+"二遥测名称");
        m_name_list.append("遥测数值");

        int num = m_name_list.size();
        model->setColumnCount(num);
        model->setRowCount(0);
        for (int i = 0; i < num; i++) {
            model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
        }

        QStringList msyc_strName4_1;

        msyc_strName4_1.append("上次执行任务的流水号");
        msyc_strName4_1.append("管控高算力1_上次处理FPGA1主任务ID");
        msyc_strName4_1.append("管控高算力1_上次处理FPGA2主任务ID");
        msyc_strName4_1.append("管控高算力1_上次处理FPGA3主任务ID");
        msyc_strName4_1.append("管控高算力1_上次处理FPGA4主任务ID");
        msyc_strName4_1.append("管控高算力2_上次处理FPGA1主任务ID");
        msyc_strName4_1.append("管控高算力2_上次处理FPGA2主任务ID");
        msyc_strName4_1.append("管控高算力2_上次处理FPGA3主任务ID");
        msyc_strName4_1.append("管控高算力2_上次处理FPGA4主任务ID");
        msyc_strName4_1.append("管控_上次执行任务的实际起始时间");
        msyc_strName4_1.append("管控_上次执行任务的实际终止时间");
        msyc_strName4_1.append("管控_上一个任务任务强制终止标志");
        msyc_strName4_1.append("管控_上个任务异常结束标志");


        for (int i = 0; i < msyc_strName4_1.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName4_1.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 0, table_item);
            //model->setItem(i, 0, new QStandardItem(msyc_strName3_1.at(i)));
        }


        QStringList msyc_strName4_2;
        switch (g4_YC_Flag) {
        case 0x3507://第四组遥测解析-电子侦察任务包(2s)

            msyc_strName4_2.append("高算力1-处理模块A-V7-1运行模式");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1运行状态");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2运行模式");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2运行状态");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1运行模式");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1运行状态");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2运行模式");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2运行状态");
            msyc_strName4_2.append("高算力2-处理模块A-V7-1运行模式");
            msyc_strName4_2.append("高算力2-处理模块A-V7-1运行状态");
            msyc_strName4_2.append("高算力2-处理模块A-V7-2运行模式");
            msyc_strName4_2.append("高算力2-处理模块A-V7-2运行状态");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1运行模式");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1运行状态");
            msyc_strName4_2.append("高算力2-处理模块B-V7-2运行模式");
            msyc_strName4_2.append("高算力2-处理模块B-V7-2运行状态");

            break;
        case 0x3607://第四组遥测解析-电子干扰任务包(2s)

            break;
        case 0x3707://第四组遥测解析-SAR成像任务包(2s)
            msyc_strName4_2.append("SAR成像_成像模式字_极化方式");
            msyc_strName4_2.append("SAR成像_通道模式");
            msyc_strName4_2.append("SAR成像_成像模式");
            msyc_strName4_2.append("SAR成像_指令队列长度");
            msyc_strName4_2.append("SAR成像_SAR开机时间");
            msyc_strName4_2.append("SAR成像_本地时间码T5");
            msyc_strName4_2.append("SAR成像_本地时间码T4");
            msyc_strName4_2.append("SAR成像_本地时间码T3");
            msyc_strName4_2.append("SAR成像_本地时间码T2");
            msyc_strName4_2.append("SAR成像_包格式");
            msyc_strName4_2.append("SAR成像_任务类型");
            msyc_strName4_2.append("SAR成像_流水号");
            msyc_strName4_2.append("SAR成像_任务号");
            msyc_strName4_2.append("SAR成像_子任务号");
            msyc_strName4_2.append("SAR成像_聚束中心时刻星上修正控制");
            msyc_strName4_2.append("SAR成像_子带个数");
            msyc_strName4_2.append("SAR成像_星上计算结果错误状态1");
            msyc_strName4_2.append("SAR成像_星上计算结果错误状态2");
            msyc_strName4_2.append("SAR成像_当前待执行成像任务数");



            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-采集信号遥测-采集回波数据标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-采集信号遥测-辅助数据接收标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-采集信号遥测-数传数据输出标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-采集信号遥测-PRF接收标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-校正流程遥测-AD数据选择");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-校正流程遥测-校正流程开始标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-校正流程遥测-校正流程完成标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-1数据形成-校正完成遥测-AD同步流程");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-采集输入输出信号遥测-控制码接收标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-采集输入输出信号遥测-DAC数据输出标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-采集输入输出信号遥测-PRF接收标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-校正流程遥测-射频选择");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-校正流程遥测-数据可以开始输出标志");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-校正完成遥测-校准数据源选择");
            msyc_strName4_2.append("高算力1-收发处理模块-V7-2调频源-校正完成遥测-数据输出选择控制码");

            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点8完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点7完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点6完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点5完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点4完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点3完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前节点2完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-1探测成像预处理-探测成像1-当前程序处理节点1完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点8完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点7完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点6完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点5完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点4完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点3完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点2完成标志");
            msyc_strName4_2.append("高算力1-处理模块A-V7-2探测成像方位向处理-探测成像2-当前节点1完成标志");

            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-灰度图宽度");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-灰度图高度");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-接收数据开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-接收数据结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-发送数据开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-发送数据结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-接收数据时钟数计数");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-发送数据时钟数计数");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-CFAR处理步骤");
            msyc_strName4_2.append("高算力1-处理模块B-V7-2广域搜索模式舰船检测-检测目标数");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-网络运行层数");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-目标处理开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-切片写入开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-图像插值开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-参数写入开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-参数读取开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-发送数据开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-接收数据开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志1-网络运行开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-网络参数载入开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-参数包导入开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-网络计算最大值开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-网络归一化开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-全连接层开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-经纬度计算开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-经纬度计算参数有效标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志2-参数包导入开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-读取权重结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-读取权重开始标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-网络运行结束响应标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-AXI总线复位标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-网络计算流程复位标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-检测流程复位标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志3-处理全局复位标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-网络参数载入结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-海陆分割数据发送结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-图像插值结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-参数写入结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-参数读取结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-发送数据结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-接收数据结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志4-网络运行结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-网络参数载入结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-参数包导入结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-网络计算最大值结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-网络归一化结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-全连接层结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-经纬度计算结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-网络数据写入结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-流程标志5-参数包导入结束标志");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-相关参数1-检测目标个数");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-相关参数2-当前处理检测目标位置");
            msyc_strName4_2.append("高算力1-处理模块B-V7-1广域搜索模式舰船鉴别-状态参数3-舰船处理数据量");


            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-网络运行层数");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-目标处理开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-目标判据标志2");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-目标判据标志1");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-参数写入开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-参数读取开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-发送数据开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-接收数据开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志1-网络运行开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志2-网络参数载入开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志2-参数包导入开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志2-网络计算最大值开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志2-网络归一化开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志2-全连接层开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志2-参数包导入开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-读取权重结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-读取权重开始标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-网络运行结束响应标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-AXI总线复位标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-网络计算流程复位标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-检测流程复位标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志3-处理全局复位标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志4-网络参数载入结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志4-参数写入结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志4-参数读取结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志4-发送数据结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志4-接收数据结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志4-网络运行结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-网络参数载入结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-参数包导入结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-网络计算最大值结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-网络归一化结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-全连接层结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-网络数据写入结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-流程标志5-参数包导入结束标志");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-相关参数1-检测目标个数");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-相关参数2-当前处理检测目标位置");
            msyc_strName4_2.append("高算力2-处理模块B-V7-1广域搜索模式舰船二分类-状态参数3-舰船处理状态");


            break;
        case 0x3807://第四组遥测解析-备用导航任务包(2s)
            msyc_strName4_2.append("备用导航_DSP UTC时间状态");
            msyc_strName4_2.append("备用导航_FPGA PPS状态");
            msyc_strName4_2.append("备用导航_FPGA DDS信号生成状态");
            msyc_strName4_2.append("备用导航_轨道数据接收状态");
            msyc_strName4_2.append("备用导航_轨道数据连续性");
            msyc_strName4_2.append("备用导航_综合管控单元_保留");
            msyc_strName4_2.append("备用导航_伪码参数状态");
            msyc_strName4_2.append("备用导航_星历拟合状态");
            msyc_strName4_2.append("备用导航_历书拟合状态");
            msyc_strName4_2.append("备用导航_DSP 三模冗余错误计数");
            msyc_strName4_2.append("备用导航_轨道数据接收成功计数");
            msyc_strName4_2.append("备用导航_星历拟合误差");
            msyc_strName4_2.append("备用导航_数字功率衰减值");
            msyc_strName4_2.append("备用导航_备用导航信号导航时间");


            break;
        case 0x3907://第四组遥测解析-类5G通信任务包(2s)
            msyc_strName4_2.append("综合管控单元_5G关口站位置_经度");
            msyc_strName4_2.append("综合管控单元_5G关口站位置_纬度");
            msyc_strName4_2.append("类5G_5G工作模式");
            msyc_strName4_2.append("类5G_注册用户数");
            msyc_strName4_2.append("类5G_误块率");
            msyc_strName4_2.append("类5G_编码调制样式");
            msyc_strName4_2.append("类5G_编码码率");
            break;

        case 0x3A07:

            break;
        default:
            break;
        }

        for (int i = 0; i < msyc_strName4_2.size(); i++) {
            QStandardItem* table_item;
            table_item=new QStandardItem(msyc_strName4_2.at(i));
            table_item->setBackground(QBrush(QColor(223,236,213)));
            model->setItem(i, 2, table_item);
            //model->setItem(i, 0, new QStandardItem(msyc_strName3_1.at(i)));
        }
    }

    //    QStandardItem *tempItem;
    //    tempItem = new QStandardItem("错误标红");
    //    //tempItem->setBackground(QBrush(Qt::red));
    //    tempItem->setBackground(QBrush(QColor(250,150,150)));//淡红色

    //    model->setItem(0, 1, tempItem);

    ui->tView_yclist->setModel(model);  //(设置宽度要在后面)
    ui->tView_yclist->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 是否可编辑
    //  ui->tView_yclist->setColumnWidth(1,00);//设置第0列宽100
    //    ui->tView_yclist->resizeColumnToContents(0);  // 设置第0列宽度自适应内容
    //    ui->tView_yclist->resizeColumnToContents(2);  // 设置第2列宽度自适应内容
    //    ui->tView_yclist->resizeColumnToContents(4);  // 设置第4列宽度自适应内容
    ui->tView_yclist->resizeColumnsToContents();//设置所有列宽度自适应
    ui->tView_yclist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tView_yclist->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tView_yclist->horizontalHeader()->setMinimumSectionSize(100);

    //   ui->tView_yclist->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);//设置第1列(表头)自动
    //   ui->tView_yclist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置所有列自动
}
//数据库字段名初始化
void subyc_slowspeed::Init_DBList()
{
    // 慢速遥测值名称DB
    // 第一组////////////////////////////////////////////////////////////////
    if(1)
    {
        QStringList msyc_strName1_1;
        msyc_strName1_1.append("综合管控单元_重构进行状态");
        msyc_strName1_1.append("综合管控单元_重传标志");
        msyc_strName1_1.append("综合管控单元_重传前进通道");
        msyc_strName1_1.append("综合管控单元_重传包个数");
        msyc_strName1_1.append("综合管控单元_重传包位序号计数");


        msyc_strName1_1.append("L频段_触发PRF监测遥测");
        msyc_strName1_1.append("L频段_计算机状态监测遥测");
        msyc_strName1_1.append("L频段_总线状态监测遥测");
        msyc_strName1_1.append("L频段_数字综合单元主机电源");
        msyc_strName1_1.append("L频段_数字综合单元备机电源");
        msyc_strName1_1.append("L频段_组合定标功放电源监测");
        msyc_strName1_1.append("L频段_其他电源监测");
        msyc_strName1_1.append("L频段_射频收发模块1_2输出监测");
        msyc_strName1_1.append("L频段_射频收发模块3_6输出监测");
        msyc_strName1_1.append("L频段_组合定标模块输出监测");
        msyc_strName1_1.append("L频段_定时波控3_3V监测");
        msyc_strName1_1.append("L频段_定时波控主5V监测");
        msyc_strName1_1.append("L频段_定时波控备5V监测");
        msyc_strName1_1.append("L频段_阵面1天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面1天线发射电源开关状态");
        msyc_strName1_1.append("L频段_阵面2天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面2天线发射电源开关状态");
        msyc_strName1_1.append("L频段_阵面3天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面3天线发射电源开关状态");
        msyc_strName1_1.append("L频段_阵面4天线接收电源开关状态");
        msyc_strName1_1.append("L频段_阵面4天线发射电源开关状态");


        msyc_strName1_1.append("SXKu频段_消浪涌开关遥测");
        msyc_strName1_1.append("SXKu频段_放电开关遥测");
        msyc_strName1_1.append("SXKu频段_波束控制器主机开关遥测");
        msyc_strName1_1.append("SXKu频段_波束控制器备机开关遥测");
        msyc_strName1_1.append("SXKu频段_波控机主机5V遥测");
        msyc_strName1_1.append("SXKu频段_波控机备机5V遥测");
        msyc_strName1_1.append("SxKu频段模块3二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块3二次电源发射开关遥测");
        msyc_strName1_1.append("SxKu频段模块1二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块1二次电源发射开关遥测");
        msyc_strName1_1.append("SxKu频段模块4二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块4二次电源发射开关遥测");
        msyc_strName1_1.append("SxKu频段模块2二次电源接收开关遥测");
        msyc_strName1_1.append("SxKu频段模块2二次电源发射开关遥测");

        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态1");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态2");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态3");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态4");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态5");
        msyc_strName1_1.append("SXKu频段_射频收发二次电源状态6");
        msyc_strName1_1.append("SXKu频段_射频收发接收电");
        msyc_strName1_1.append("SXKu频段_射频收发发射电");

        QStringList msyc_strName1_2;
        msyc_strName1_2.append("载荷_A组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_B组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_C组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_D组消浪涌开关状态遥测");
        msyc_strName1_2.append("载荷_A组母线电压遥测");
        msyc_strName1_2.append("载荷_B组母线电压遥测");
        msyc_strName1_2.append("载荷_C组母线电压遥测");
        msyc_strName1_2.append("载荷_D组母线电压遥测");

        msyc_strName1_2.append("可重构射频前端主份正6VA供电");
        msyc_strName1_2.append("可重构射频前端主份负6VA供电");
        msyc_strName1_2.append("可重构射频前端主份正15VA供电");
        msyc_strName1_2.append("可重构射频前端主份正5VD供电");
        msyc_strName1_2.append("可重构射频前端主份正6V2A供电");
        msyc_strName1_2.append("可重构射频前端备份正6VA供电");
        msyc_strName1_2.append("可重构射频前端备份负6VA供电");
        msyc_strName1_2.append("可重构射频前端备份正15VA供电");
        msyc_strName1_2.append("可重构射频前端备份正5VD供电");
        msyc_strName1_2.append("可重构射频前端备份正6V2A供电");

        msyc_strName1_2.append("可重构算力1供电遥测_正6VA");
        msyc_strName1_2.append("可重构算力1路1遥测_正5VD");
        msyc_strName1_2.append("可重构算力1路2遥测_正5VD");
        msyc_strName1_2.append("可重构算力1路3遥测_正5VD");
        msyc_strName1_2.append("可重构算力1路4遥测_正5VD");
        msyc_strName1_2.append("可重构算力2供电遥测_正6VA");
        msyc_strName1_2.append("可重构算力2路1遥测_正5VD");
        msyc_strName1_2.append("可重构算力2路2遥测_正5VD");
        msyc_strName1_2.append("可重构算力2路3遥测_正5VD");
        msyc_strName1_2.append("可重构算力2路4遥测_正5VD");

        QStringList msyc_strName1_3;
        msyc_strName1_3.append("L频段_天线收发状态");
        msyc_strName1_3.append("SXKu频段_天线收发状态");

        msyc_strName1_3.append("高算力1_接口控制模块DSP6678心跳");
        msyc_strName1_3.append("高算力1_接口控制模块DSP6701加载状态");
        msyc_strName1_3.append("高算力1_接口控制模块DSP6678加载状态");
        msyc_strName1_3.append("高算力1_接口控制模块V7加载状态");
        msyc_strName1_3.append("高算力1_收发处理模块K7加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块A的K7加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块B的K7加载状态");

        msyc_strName1_3.append("高算力1_收发处理模块V7_1加载状态");
        msyc_strName1_3.append("高算力1_收发处理模块V7_2加载状态");

        msyc_strName1_3.append("高算力1_数据处理模块A_DSP6678心跳");
        msyc_strName1_3.append("高算力1_数据处理模块A_DSP6678加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块A_V7_1加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块A_V7_2加载状态");

        msyc_strName1_3.append("高算力1_数据处理模块B_DSP6678心跳");
        msyc_strName1_3.append("高算力1_数据处理模块B_DSP6678加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块B_V7_1加载状态");
        msyc_strName1_3.append("高算力1_数据处理模块B_V7_2加载状态");


        msyc_strName1_3.append("高算力2_接口控制模块DSP6678心跳");
        msyc_strName1_3.append("高算力2_接口控制模块DSP6701加载状态");
        msyc_strName1_3.append("高算力2_接口控制模块DSP6778加载状态");
        msyc_strName1_3.append("高算力2_接口控制模块V7加载状态");
        msyc_strName1_3.append("高算力2_收发处理模块K7加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块A的K7加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块B的K7加载状态");

        msyc_strName1_3.append("高算力2_收发处理模块_V7_1加载状态");
        msyc_strName1_3.append("高算力2_收发处理模块_V7_2加载状态");

        msyc_strName1_3.append("高算力2_数据处理模块A_DSP6678心跳");
        msyc_strName1_3.append("高算力2_数据处理模块A_DSP6678加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块A_V7_1加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块A_V7_2加载状态");

        msyc_strName1_3.append("高算力2_数据处理模块B_DSP6678心跳");
        msyc_strName1_3.append("高算力2_数据处理模块B_DSP6678加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块B_V7_1加载状态");
        msyc_strName1_3.append("高算力2_数据处理模块B_V7_2加载状态");

        QStringList msyc_strName1_4;


        msyc_strName1_4.append("CAN通道A复位次数");
        msyc_strName1_4.append("CAN通道B复位次数");
        msyc_strName1_4.append("L频段_CAN接收异常帧次数");
        msyc_strName1_4.append("SXKu频段_CAN接收异常帧次数");
        msyc_strName1_4.append("射频前端_CAN接收异常帧次数");
        msyc_strName1_4.append("高算力1_CAN接收异常帧次数");
        msyc_strName1_4.append("高算力2_CAN接收异常帧次数");

        msyc_strName1_4.append("L频段_CAN接收计数");
        msyc_strName1_4.append("SXKu频段_CAN接收计数");
        msyc_strName1_4.append("射频前端_CAN接收计数");
        msyc_strName1_4.append("高算力1_CAN接收计数");
        msyc_strName1_4.append("高算力2_CAN接收计数");

        msyc_strName1_4.append("_1553B总线指令接收帧计数");
        msyc_strName1_4.append("_1553B总线注数接收帧计数");
        msyc_strName1_4.append("_1553B总线帧接收异常次数");
        msyc_strName1_4.append("_1553B总线复位次数");
        //msyc_strName1_4.append("_1553B总线校验正常总帧数");

        msyc_strName1_4.append("_1553B指令执行结果_上一帧");
        msyc_strName1_4.append("_1553B指令执行结果_当前帧");
        msyc_strName1_4.append("管控机星时");//后面移动到前面
        msyc_strName1_4.append("综合管控单元_工作状态");
        msyc_strName1_4.append("有效任务总数");
        msyc_strName1_4.append("已存任务总数");
        msyc_strName1_4.append("当前执行任务的流水号");
        msyc_strName1_4.append("高算力1处理FPGA1执行的主任务ID");
        msyc_strName1_4.append("高算力1处理FPGA2执行的主任务ID");
        msyc_strName1_4.append("高算力1处理FPGA3执行的主任务ID");
        msyc_strName1_4.append("高算力1处理FPGA4执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA1执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA2执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA3执行的主任务ID");
        msyc_strName1_4.append("高算力2处理FPGA4执行的主任务ID");


        msyc_strName1_4.append("管控_高算力1工作频段");
        msyc_strName1_4.append("管控_高算力2工作频段");
        msyc_strName1_4.append("管控_高算力1主从状态");
        msyc_strName1_4.append("管控_高算力2主从状态");

        msyc_strName1_4.append("管控单元_软件上注块存储快状态");
        msyc_strName1_4.append("管控单元_Can软件更新进度或6G刷新进度");
        msyc_strName1_4.append("千兆网口软件接收帧计数");
        msyc_strName1_4.append("千兆网口软件发送帧计数");
        msyc_strName1_4.append("管控单元_维护状态");


        //数据库，字段名
        QStringList group1=QStringList()<<msyc_strName1_1<<msyc_strName1_2<<msyc_strName1_3<<msyc_strName1_4;
        QSqlQuery qureydb;//创建对象时，系统会自动完成与数据库的关联
        QString str=QString("CREATE TABLE IF NOT EXISTS YC1553_slowP1("
                            //"ID INTEGER PRIMARY KEY     NOT NULL,"
                            "时间 TEXT  PRIMARY KEY  NOT NULL,"
                            "单机 TEXT NOT NULL ,              ");

        for (int col=0;col<group1.size()-1;col++) {
            str+=group1[col]+" TEXT, ";
        }
        str+=group1[group1.size()-1]+" TEXT);";
        qureydb.exec(str);
        //qDebug()<<str;

    }
    // 第二组////////////////////////////////////////////////////////////////

    if(1)
    {
        QStringList msyc_strName2_1;
        msyc_strName2_1.append("L频段相控阵天线_波控发射PRF监测");
        msyc_strName2_1.append("L频段相控阵天线_波控接收PRF监测");

        msyc_strName2_1.append("L频段相控阵天线_天线子阵1通道1");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵1通道2");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵3通道2");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵3通道3");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵2通道4");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵2通道5");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵4通道5");
        msyc_strName2_1.append("L频段相控阵天线_天线子阵4通道6");

        msyc_strName2_1.append("SAR成像_系统工作状态");
        msyc_strName2_1.append("SAR成像_SAR分系统状态");
        msyc_strName2_1.append("SAR成像_指令接收_处理状态");
        msyc_strName2_1.append("SAR成像_EDAC错误计数");
        msyc_strName2_1.append("SAR成像_CPU复位计数");
        msyc_strName2_1.append("SAR成像_CAN总线复位计数");
        msyc_strName2_1.append("SAR成像_收指令计数");

        msyc_strName2_1.append("L频段相控阵天线_射频收发单元_开关状态");
        msyc_strName2_1.append("SXKu_射频收发单元_开关状态");

        msyc_strName2_1.append("高算力1_V7与交换A光纤建链指示");
        msyc_strName2_1.append("高算力1_V7与交换B光纤建链指示");
        msyc_strName2_1.append("高算力1_V7与管控主Rapid_IO建链指示");
        msyc_strName2_1.append("高算力1_V7与管控备Rapid_IO建链指示");
        msyc_strName2_1.append("高算力2_V7与交换A光纤建链指示");
        msyc_strName2_1.append("高算力2_V7与交换B光纤建链指示");
        msyc_strName2_1.append("高算力2_V7与管控主Rapid_IO建链指示");
        msyc_strName2_1.append("高算力2_V7与管控备Rapid_IO建链指示");


        QStringList msyc_strName2_2;

        msyc_strName2_2.append("高算力1_接口模块_光模块参数更新状态");
        msyc_strName2_2.append("高算力1_接口模块_光模块供电指示FIBER_3V3PG");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示PG_DSPVTT");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示PG_DSP1V8");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示PG_DSP1V5");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示PG_DSP1V0_SMART");
        msyc_strName2_2.append("高算力1_接口模块_DSP供电指示PG_DSP1V0");

        msyc_strName2_2.append("高算力1_收发模块_FPGA1的1DDRVTT电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_FPGA1的2DDRVTT电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_FPGA2的1DDRVTT电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_FPGA2的2DDRVTT电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_AD1电源1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1_1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1_2V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1点3VA电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源2V电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_AD2电源1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源1_1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源1_2V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源1点3VB电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD2电源2V电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_AD3电源1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD3电源1_1V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD3电源1_2V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD3电源2V电源PG指示");

        msyc_strName2_2.append("高算力1_收发模块_1点5V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_2_1点5V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_AD1电源1点8V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_2点8V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_模拟3点3V电源PG指示");
        msyc_strName2_2.append("高算力1_收发模块_模拟3点3_2电源PG指示");

        msyc_strName2_2.append("高算力1_数据处理模块A_光模块PG_FIB3V3");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源PG_DSPVTT");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源PG_DSP1V8");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源PG_DSP1V5");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源PG_DSP1V0_SMART");
        msyc_strName2_2.append("高算力1_数据处理模块A_DSP电源PG_DSP1V0");

        msyc_strName2_2.append("高算力1_数据处理模块B_光模块PG_FIB3V3");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源PG_DSPVTT");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源PG_DSP1V8");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源PG_DSP1V5");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源PG_DSP1V0_SMART");
        msyc_strName2_2.append("高算力1_数据处理模块B_DSP电源PG_DSP1V0");

        QStringList msyc_strName2_3;

        msyc_strName2_3.append("高算力2_接口模块_光模块参数更新状态");
        msyc_strName2_3.append("高算力2_接口模块_光模块供电指示FIBER_3V3PG");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示PG_DSPVTT");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示PG_DSP1V8");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示PG_DSP1V5");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示PG_DSP1V0_SMART");
        msyc_strName2_3.append("高算力2_接口模块_DSP供电指示PG_DSP1V0");

        msyc_strName2_3.append("高算力2_收发模块_FPGA1的1DDRVTT电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_FPGA1的2DDRVTT电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_FPGA2的1DDRVTT电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_FPGA2的2DDRVTT电源PG指示");

        msyc_strName2_3.append("高算力2_收发模块_AD1电源1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1_1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1_2V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1点3VA电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源2V电源PG指示");

        msyc_strName2_3.append("高算力2_收发模块_AD2电源1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源1_1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源1_2V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源1点3VB电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD2电源2V电源PG指示");/////(漏掉了)


        msyc_strName2_3.append("高算力2_收发模块_AD3电源1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD3电源1_1V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD3电源1_2V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD3电源2V电源PG指示");

        msyc_strName2_3.append("高算力2_收发模块_1点5V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_2_1点5V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_AD1电源1点8V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_2点8V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_模拟3点3V电源PG指示");
        msyc_strName2_3.append("高算力2_收发模块_模拟3点3_2电源PG指示");

        msyc_strName2_3.append("高算力2_数据处理理模块A_光模块PG_FIB3V3");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源PG_DSPVTT");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源PG_DSP1V8");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源PG_DSP1V5");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源PG_DSP1V0_SMART");
        msyc_strName2_3.append("高算力2_数据处理理模块A_DSP电源PG_DSP1V0");

        msyc_strName2_3.append("高算力2_数据处理理模块B_光模块PG_FIB3V3");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源PG_DSPVTT");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源PG_DSP1V8");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源PG_DSP1V5");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源PG_DSP1V0_SMART");
        msyc_strName2_3.append("高算力2_数据处理理模块B_DSP电源PG_DSP1V0");

        QStringList msyc_strName2_4;//名称顺序跟后面协议有点不一致，调整顺序方便观看

        msyc_strName2_4.append("高算力1_模块栓锁");
        msyc_strName2_4.append("高算力1_收发处理模块栓锁收发LRM_PG1");
        msyc_strName2_4.append("高算力1_数据处理1模块栓锁数据1LRM_PG2");
        msyc_strName2_4.append("高算力1_数据处理2模块栓锁数据2LRM_PG3");
        msyc_strName2_4.append("高算力1_锁相环V2_LD1");
        msyc_strName2_4.append("高算力1_锁相环V2_LD2");
        msyc_strName2_4.append("高算力1_锁相环V2_LD3");


        msyc_strName2_4.append("高算力1_接口模块_V7与管控RapidIO主备");
        msyc_strName2_4.append("高算力1_接口模块_V7与高速交换机光纤主备");
        msyc_strName2_4.append("高算力1_接口DSP6678与接口控制V7建链指示");
        msyc_strName2_4.append("高算力1_接口DSP6678与数据处理1建链指示");
        msyc_strName2_4.append("高算力1_接口DSP6678与数据处理2建链指示");

        msyc_strName2_4.append("高算力1_接口板V7接收数据计数");
        msyc_strName2_4.append("高算力1_接口板V7发送数据计数");
        msyc_strName2_4.append("高算力1_接口板DSP6678星时");

        msyc_strName2_4.append("高算力1_收发处理模块_ADC1建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_ADC2建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_ADC3建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_DAC1建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_DAC2建链指示");
        msyc_strName2_4.append("高算力1_收发处理模块_DAC3建链指示");
        ///

        msyc_strName2_4.append("高算力2_模块栓锁");
        msyc_strName2_4.append("高算力2_收发处理模块栓锁收发LRM_PG1");
        msyc_strName2_4.append("高算力2_数据处理1模块栓锁数据1LRM_PG2");
        msyc_strName2_4.append("高算力2_数据处理2模块栓锁数据2LRM_PG3");
        msyc_strName2_4.append("高算力2_锁相环V2_LD1");
        msyc_strName2_4.append("高算力2_锁相环V2_LD2");
        msyc_strName2_4.append("高算力2_锁相环V2_LD3");

        msyc_strName2_4.append("高算力2_接口模块_V7与管控RapidIO主备");
        msyc_strName2_4.append("高算力2_接口模块_V7与高速交换机光纤主备");
        msyc_strName2_4.append("高算力2_接口DSP6678与接口控制V7建链指示");
        msyc_strName2_4.append("高算力2_接口DSP6678与数据处理1建链指示");
        msyc_strName2_4.append("高算力2_接口DSP6678与数据处理2建链指示");

        msyc_strName2_4.append("高算力2_接口板V7接收数据计数");
        msyc_strName2_4.append("高算力2_接口板V7发送数据计数");
        msyc_strName2_4.append("高算力2_接口板DSP6678星时");


        msyc_strName2_4.append("高算力2_收发处理模块_ADC1建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_ADC2建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_ADC3建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_DAC1建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_DAC2建链指示");
        msyc_strName2_4.append("高算力2_收发处理模块_DAC3建链指示");

        QStringList msyc_strName2_5;

        msyc_strName2_5.append("管控_OC开关状态_L频段相控阵天线消浪涌");
        msyc_strName2_5.append("管控_OC开关状态_L频段相控阵天线31V总电源");

        msyc_strName2_5.append("管控_综合处理模块_AI电压");
        msyc_strName2_5.append("管控_综合处理模块_3个DSP6678总电压");
        //msyc_strName2_5.append("管控_综合处理模块_V7电压");

        msyc_strName2_5.append("射频前端_SXKu频段射频通道56");
        msyc_strName2_5.append("射频前端_SXKu频段射频通道34");
        msyc_strName2_5.append("射频前端_SXKu频段射频通道12");
        msyc_strName2_5.append("射频前端_L波段射频切换调理模块遥测量");
        msyc_strName2_5.append("射频前端_中频切换模块1遥测量");
        msyc_strName2_5.append("射频前端_中频切换模块2遥测量");

        msyc_strName2_5.append("射频前端_宽带一本振2主环锁定指示");
        msyc_strName2_5.append("射频前端_宽带一本振2副环锁定指示");
        msyc_strName2_5.append("射频前端_备份高相噪一本振锁定指示");
        msyc_strName2_5.append("射频前端_备份二本振锁定指示");
        msyc_strName2_5.append("射频前端_宽带一本振1主环锁定指示");
        msyc_strName2_5.append("射频前端_宽带一本振1副环锁定指示");
        msyc_strName2_5.append("射频前端_主份高相噪一本振锁定指示");
        msyc_strName2_5.append("射频前端_主份二本振锁定指示");


        msyc_strName2_5.append("L频段相控阵天线_射频综合单元温度");
        msyc_strName2_5.append("L频段相控阵天线_数字综合单机温度");
        msyc_strName2_5.append("高算力1_接口控制模块_V7温度");
        msyc_strName2_5.append("高算力1_收发处理模块_ADC1温度");
        msyc_strName2_5.append("高算力1_收发处理模块_ADC2温度");
        msyc_strName2_5.append("高算力1_收发处理模块_ADC3温度");
        msyc_strName2_5.append("高算力1_收发处理模块_V7_1温度");
        msyc_strName2_5.append("高算力1_收发处理模块_V7_2温度");
        msyc_strName2_5.append("高算力1_数据处理模块A_V7_1温度");
        msyc_strName2_5.append("高算力1_数据处理模块A_V7_2温度");
        msyc_strName2_5.append("高算力1_数据处理模块B_V7_1温度");
        msyc_strName2_5.append("高算力1_数据处理模块B_V7_2温度");
        msyc_strName2_5.append("高算力2_接口控制模块_V7温度");
        msyc_strName2_5.append("高算力2_收发处理模块_ADC1温度");
        msyc_strName2_5.append("高算力2_收发处理模块_ADC2温度");
        msyc_strName2_5.append("高算力2_收发处理模块_ADC3温度");
        msyc_strName2_5.append("高算力2_收发处理模块_V7_1温度");
        msyc_strName2_5.append("高算力2_收发处理模块_V7_2温度");
        msyc_strName2_5.append("高算力2_数据处理模块A_V7_1温度");
        msyc_strName2_5.append("高算力2_数据处理模块A_V7_2温度");
        msyc_strName2_5.append("高算力2_数据处理模块B_V7_1温度");
        msyc_strName2_5.append("高算力2_数据处理模块B_V7_2温度");
        msyc_strName2_5.append("综合管控单元_管控模块_V7温度");
        msyc_strName2_5.append("综合管控单元_综合处理模块_V7温度");
        msyc_strName2_5.append("综合管控单元_综合处理模块_AI温度");
        msyc_strName2_5.append("综合管控单元_温度保护关断温度阈值_高算力1");
        msyc_strName2_5.append("综合管控单元_温度保护关断温度阈值_高算力2");
        msyc_strName2_5.append("高算力1模块A_与高算力2模块A_V7_1时钟锁定");
        msyc_strName2_5.append("高算力1模块A_与高算力2模块A_V7_1建链");
        msyc_strName2_5.append("高算力1模块B_与高算力2模块B_V7_1时钟锁定");
        msyc_strName2_5.append("高算力1模块B_与高算力2模块B_V7_1建链");
        msyc_strName2_5.append("高算力2模块A_与高算力1模块A_V7_1时钟锁定");
        msyc_strName2_5.append("高算力2模块A_与高算力1模块A_V7_1建链");
        msyc_strName2_5.append("高算力2模块B_与高算力1模块B_V7_1时钟锁定");
        msyc_strName2_5.append("高算力2模块B_与高算力1模块B_V7_1建链");


        //数据库，字段名
        QStringList group2=QStringList()<<msyc_strName2_1<<msyc_strName2_2<<msyc_strName2_3<<msyc_strName2_4<<msyc_strName2_5;
        QSqlQuery qureydb;//创建对象时，系统会自动完成与数据库的关联
        QString str=QString("CREATE TABLE IF NOT EXISTS YC1553_slowP2("
                            //"ID INTEGER PRIMARY KEY     NOT NULL,"
                            "时间 TEXT  PRIMARY KEY  NOT NULL,"
                            "单机 TEXT NOT NULL ,              ");

        for (int col=0;col<group2.size()-1;col++) {
            str+=group2[col]+" TEXT, ";
        }
        str+=group2[group2.size()-1]+" TEXT);";
        qureydb.exec(str);
        //qDebug()<<str;
    }
    // 第三组////////////////////////////////////////////////////////////////
    if(1)
    {
        QStringList msyc_strName3_1;

        msyc_strName3_1.append("高算力1_接口控制模块_V2大_小版本号");

        msyc_strName3_1.append("高算力1_接口控制模块_V7大_小版本号");

        msyc_strName3_1.append("高算力1_接口控制模块_DSP6701大_小版本号");

        msyc_strName3_1.append("高算力1_接口控制模块_DSP6678大_小版本号");

        msyc_strName3_1.append("高算力1_收发处理模块_K7大_小版本号");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_1大_小版本号 ");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_1软件代号");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_2大_小版本号");

        msyc_strName3_1.append("高算力1_收发处理模块_V7_2软件代号");
        msyc_strName3_1.append("高算力1_收发处理模块_K7预加载软件数量");

        msyc_strName3_1.append("高算力1_数据处理模块A_K7大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_1大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_1软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_2大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_V7_2软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块A_DSP6678大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块A_DSP6678软件代号");
        msyc_strName3_1.append("高算力1_数据处理模块A_K7预加载软件数量");

        msyc_strName3_1.append("高算力1_数据处理模块B_K7大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_1大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_1软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_2大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_V7_2软件代号");

        msyc_strName3_1.append("高算力1_数据处理模块B_DSP6678大_小版本号");

        msyc_strName3_1.append("高算力1_数据处理模块B_DSP6678软件代号");
        msyc_strName3_1.append("高算力1_数据处理模块B_K7预加载软件数量");

        msyc_strName3_1.append("高算力1_接口V7三模运维状态");
        msyc_strName3_1.append("高算力1_软件引导方式_接口Can解析与重构调度软件");
        msyc_strName3_1.append("高算力1_软件引导方式_接口控制模块综合调度软件");
        msyc_strName3_1.append("高算力1_软件引导方式_数据处理模块A接口控制软件");
        msyc_strName3_1.append("高算力1_软件引导方式_数据处理模块B接口控制软件");
        msyc_strName3_1.append("高算力1_软件引导方式_收发处理模块接口控制软件");
        msyc_strName3_1.append("高算力1_软件引导方式_接口控制模块数据传输软件");

        QStringList msyc_strName3_2;
        msyc_strName3_2.append("高算力2_接口控制模块_V2大_小版本号");

        msyc_strName3_2.append("高算力2_接口控制模块_V7大_小版本号");

        msyc_strName3_2.append("高算力2_接口控制模块_DSP6701大_小版本号");

        msyc_strName3_2.append("高算力2_接口控制模块_DSP6678大_小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_K7大_小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_1大_小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_1软件代号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_2大_小版本号");

        msyc_strName3_2.append("高算力2_收发处理模块_V7_2软件代号");
        msyc_strName3_2.append("高算力2_收发处理模块_K7预加载软件数量");

        msyc_strName3_2.append("高算力2_数据处理模块A_K7大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_1大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_1软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_2大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_V7_2软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块A_DSP6678大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块A_DSP6678软件代号");
        msyc_strName3_2.append("高算力2_数据处理模块A_K7预加载软件数量");

        msyc_strName3_2.append("高算力2_数据处理模块B_K7大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_1大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_1软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_2大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_V7_2软件代号");

        msyc_strName3_2.append("高算力2_数据处理模块B_DSP6678大_小版本号");

        msyc_strName3_2.append("高算力2_数据处理模块B_DSP6678软件代号");
        msyc_strName3_2.append("高算力2_数据处理模块B_K7预加载软件数量");

        msyc_strName3_2.append("高算力2_接口V7三模运维状态");
        msyc_strName3_2.append("高算力2_软件引导方式_接口Can解析与重构调度软件");
        msyc_strName3_2.append("高算力2_软件引导方式_接口控制模块综合调度软件");
        msyc_strName3_2.append("高算力2_软件引导方式_数据处理模块A接口控制软件");
        msyc_strName3_2.append("高算力2_软件引导方式_数据处理模块B接口控制软件");
        msyc_strName3_2.append("高算力2_软件引导方式_收发处理模块接口控制软件");
        msyc_strName3_2.append("高算力2_软件引导方式_接口控制模块数据传输软件");


        QStringList msyc_strName3_3;
        msyc_strName3_3.append("综合管控单元_管控模块_P2020大_小版本号");

        msyc_strName3_3.append("综合管控单元_管控模块_V7大_小版本号");

        msyc_strName3_3.append("综合管控单元_综合处理模块_V7大_小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_1大_小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_2大_小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_3大_小版本号");

        msyc_strName3_3.append("管控_综合处理模块_DSP6678_AI大_小版本号");

        msyc_strName3_3.append("综合管控单元_卫星编号");
        msyc_strName3_3.append("综合管控单元_轨道编号");

        msyc_strName3_3.append("综合管控单元_管控模块_V2看门狗使能");
        msyc_strName3_3.append("综合管控单元_主副卫星");
        msyc_strName3_3.append("综合管控单元_CAN应用通道");
        msyc_strName3_3.append("综合管控单元_千兆网应用通道");

        msyc_strName3_3.append("综合管控单元_任务自动清除使能");
        msyc_strName3_3.append("综合管控单元_区域或常规任务状态选择");

        msyc_strName3_3.append("综合管控单元_模板数量");
        msyc_strName3_3.append("综合管控单元_SSD存储余量");

        msyc_strName3_3.append("管控_flash软刷周期使能");
        msyc_strName3_3.append("管控_高算力1_接收机自动增益控制状态");
        msyc_strName3_3.append("管控_高算力2_接收机自动增益控制状态");
        msyc_strName3_3.append("管控_高算力1_接口板V7软件维护状态");
        msyc_strName3_3.append("管控_高算力2_接口板V7软件维护状态");
        msyc_strName3_3.append("管控_V7刷新芯片控制标志");
        msyc_strName3_3.append("管控_温度保护关断功能使能标志");


        msyc_strName3_3.append("管控_管控模块向平台发送数据计数");
        msyc_strName3_3.append("管控_管控接收路由数据计数 ");
        msyc_strName3_3.append("管控_管控向路由发送数据计数");

        msyc_strName3_3.append("管控_1553B长抱环计数");
        msyc_strName3_3.append("管控_1553B系统同步计数");
        msyc_strName3_3.append("管控_管控机关机准备次数");
        msyc_strName3_3.append("管控_下控单机关机准备次数");

        QStringList msyc_strName3_4;
        msyc_strName3_4.append("管控_万兆网路由连接状态主");
        msyc_strName3_4.append("管控_万兆网路由连接状态备");
        msyc_strName3_4.append("管控_管控模块V7与P2020互联的SRIOx1链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与P2020互联的SRIOx1端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力2互联的SRIOx2链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力2互联的SRIOx2端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力1互联的SRIOx2链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与高算力1互联的SRIOx2端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与810A互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与810A互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP0互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP0互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP1互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP1互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP2互联SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与DSP2互联SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第0路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第0路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第1路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_管控模块V7与处理V7互联第1路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第0路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第0路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第1路SRIOx4链接初始化信号");
        msyc_strName3_4.append("管控_处理模块V7与管控V7互联第1路SRIOx4端口初始化信号");
        msyc_strName3_4.append("管控_V7万兆网与存储连接状态");
        msyc_strName3_4.append("管控_P2020软件引导方式");
        msyc_strName3_4.append("管控_综合管控模块_V7软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_V7软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_1软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_2软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_3软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_AI软件引导方式");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_1启动状态");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_2启动状态");
        msyc_strName3_4.append("管控_综合处理模块_DSP6678_3启动状态");
        msyc_strName3_4.append("管控_综合处理模块_AI启动状态");
        msyc_strName3_4.append("管控_SRIO接收异常帧次数");
        msyc_strName3_4.append("管控_累计已运行任务总数");
        msyc_strName3_4.append("管控_即将执行的任务时间");

        QStringList msyc_strName3_5;
        msyc_strName3_5.append("SAR成像_串注间接指令码特征码");
        msyc_strName3_5.append("SAR成像_导航闭锁信号");
        msyc_strName3_5.append("SAR_任务模式");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵1_子板1");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵1_子板2");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵2_子板1");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵2_子板2");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵3_子板1");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵3_子板2");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵4_子板1");
        msyc_strName3_5.append("SAR_L频段天线波控加载方式_子阵4_子板2");

        msyc_strName3_5.append("高算力1_数据处理模块A_FPGAV7_1任务状态");
        msyc_strName3_5.append("高算力1_数据处理模块A_FPGAV7_2任务状态");
        msyc_strName3_5.append("高算力1_数据处理模块B_FPGAV7_1任务状态");
        msyc_strName3_5.append("高算力1_数据处理模块B_FPGAV7_2任务状态");
        msyc_strName3_5.append("高算力2_数据处理模块A_FPGAV7_1任务状态");
        msyc_strName3_5.append("高算力2_数据处理模块A_FPGAV7_2任务状态");
        msyc_strName3_5.append("高算力2_数据处理模块B_FPGAV7_1任务状态");
        msyc_strName3_5.append("高算力2_数据处理模块B_FPGAV7_2任务状态");



        //数据库，字段名
        QStringList group3=QStringList()<<msyc_strName3_1<<msyc_strName3_2<<msyc_strName3_3<<msyc_strName3_4<<msyc_strName3_5;
        QSqlQuery qureydb;//创建对象时，系统会自动完成与数据库的关联
        QString str=QString("CREATE TABLE IF NOT EXISTS YC1553_slowP3("
                            //"ID INTEGER PRIMARY KEY     NOT NULL,"
                            "时间 TEXT  PRIMARY KEY  NOT NULL,"
                            "单机 TEXT NOT NULL,               ");

        for (int col=0;col<group3.size()-1;col++) {
            str+=group3[col]+" TEXT, ";
        }
        str+=group3[group3.size()-1]+" TEXT);";
        qureydb.exec(str);
        //qDebug()<<str;
    }
}
//信号槽函数
void subyc_slowspeed::Get_MsYcData1(ushort *Rxbuff, int Rxlen, int ch)
{
    if(ch!=Outslow_dj)return ;//暂时接收通道1
    GlobOut_View(Rxbuff,Rxlen,ch);
}

void subyc_slowspeed::Get_MsYcData2(ushort *Rxbuff, int Rxlen, int ch)
{
    if(ch!=Outslow_dj)return ;//暂时接收通道1
    GlobOut_View(Rxbuff,Rxlen,ch);
}

void subyc_slowspeed::Get_MsYcData3(ushort *Rxbuff, int Rxlen, int ch)
{
    if(ch!=Outslow_dj)return ;//暂时接收通道1
    GlobOut_View(Rxbuff,Rxlen,ch);
}

void subyc_slowspeed::Get_MsYcData4(ushort *Rxbuff, int Rxlen, int ch)
{
    if(ch!=Outslow_dj)return ;//暂时接收通道1
    GlobOut_View(Rxbuff,Rxlen,ch);
}

//慢速遥测显示
void subyc_slowspeed::GlobOut_View(ushort *Rxbuff, int Rxlen,int ch) {

    if(ch!=Outslow_dj)return ;//暂时接收通道1

    //    //打印显示
    //    qDebug()<<"get1553"<<QThread::currentThread();
    //    qDebug()<<"yc:";
    //    for(int i=0;i<Rxlen;i++)
    //    {
    //        printf("%04x ",Rxbuff[i]);

    //    }
    //    printf("\n");

    // 输出控件
    //     for(int j=0;j<Rxlen;j++)
    //     {
    //         for(int k=0;k<2;k++)
    //         {
    //             QString qstr=QString::number(Rxbuff[j]);
    //             model->setItem(j,k,new QStandardItem(qstr));

    //        }

    //    }

    // 开辟缓存存储8帧*32字 数据
    ushort *Tran_Buff = new ushort[Rxlen];
    memset(Tran_Buff, 0, Rxlen * 2);
    QString ss;
    for (int i = 0; i < Rxlen; i++) {
        QString s1 =QString("%1 ").arg(Rxbuff[i], 4, 16, QLatin1Char('0')).toUpper();
        Tran_Buff[i] = qToBigEndian(Rxbuff[i]);
        ss.append(s1);
    }
    //qDebug() << "Slow_YC::"<<ss;
    // 拷贝到遥测结构体
    slow_YCdata strYC;
    memcpy(&strYC, Tran_Buff, sizeof(strYC));
    delete[] Tran_Buff;

    int rowcnt = 0;//列表行
    QString qstr;
    uchar tmp_uchar = 0;
    double tmp_double = 0;

    // 主头版本号，包标志0x0731;
    if (strYC.Pack_Head != 0x3107)
    {
        qDebug()<<"slowYC_head_error!";
        return;
    }
    // 主头包顺序控制
    //qDebug() << qToBigEndian(strYC.Pack_Number);
    // 主头包长度
    //qDebug() << qToBigEndian(strYC.Pack_Len);


    // 第一组遥测
    if (strYC.group1.pack_head_1 == 0x3207) {

        //////////////////////////////////////////新列
        rowcnt=0;
//        Change_out str_change;      //判断变色结构体
//        QVector<Change_out> v_change;
//        v_change.resize(0);
        QStringList OUT_G1_c1;//遥测界面显示字符串
        QStringList DB_group1;//数据库存储字符串
        //（5bytes）
        //综合管控单元-重构进行状态
        tmp_uchar = strYC.group1.zh_ccststus;
        switch ((tmp_uchar&0xC0)>>6) {
        case 0:
            qstr="未开始:[0]";
            break;
        case 1:
            qstr="开始重构:[1]";
            break;
        case 2:
            qstr="重构完成:[2]";
            break;
        default:
            qstr="未知"+QString::number((tmp_uchar&0xC0)>>6);
            break;
        }
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-重传标志
        qstr=(tmp_uchar & 0x20)?"需要重传":"不需要重传";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-重传前进通道
        qstr=(tmp_uchar & 0x10)?"1553B总线":"网络";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-重传包个数
        qstr=QString::number(strYC.group1.cc_number);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-重传包位序号计数
        uint g1_cnt=0;
        g1_cnt=(strYC.group1.cc_cnt[0]<<16)+(strYC.group1.cc_cnt[1]<<8)+strYC.group1.cc_cnt[2];
        qstr=QString::number(g1_cnt);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);

        //(14bytes)
        // L频段-触发PRF监测遥测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_PRFmon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-计算机状态监测遥测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_computermon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-总线状态监测遥测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_busmon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-数字综合单元主机电源监测遥测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_ZJnumbermon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-数字综合单元备机电源监测遥测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_BJnumbermon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-组合定标功放电源监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_Powermon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-其他电源监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_otherpowermon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-射频收发模块1-2输出监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_12output);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-射频收发模块3-6输出监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_36output);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-组合定标模块输出监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group1.L_outputmon);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-定时波控3.3V监测
        tmp_double = ret_fun124(0.0196, 0, 1.32, 0, strYC.group1.L_33Vmon);
//        if(2.95<=tmp_double && tmp_double<=3.65)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=15;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-定时波控主5V监测
        tmp_double = ret_fun124(0.0196, 0, 1.666, 0, strYC.group1.L_Z5Vmon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=16;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // L频段-定时波控备5V监测
        tmp_double = ret_fun124(0.0196, 0, 1.666, 0, strYC.group1.L_B5Vmon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=17;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);

        //L频段-阵面1天线接收电源开关状态 bit7
        tmp_uchar=strYC.group1.L_zFace;
        qstr=(tmp_uchar&0x80)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面1天线发射电源开关状态 bit6
        qstr=(tmp_uchar&0x40)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面2天线接收电源开关状态 bit5
        qstr=(tmp_uchar&0x20)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面2天线发射电源开关状态 bit4
        qstr=(tmp_uchar&0x10)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面3天线接收电源开关状态 bit3
        qstr=(tmp_uchar&0x08)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面3天线发射电源开关状态 bit2
        qstr=(tmp_uchar&0x04)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面4天线接收电源开关状态 bit1
        qstr=(tmp_uchar&0x02)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //L频段-阵面4天线发射电源开关状态 bit0
        qstr=(tmp_uchar&0x01)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);


        // SXKu频段-消浪涌开关遥测(15bytes)
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxku_XLswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SXKu频段-放电开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxku_FDswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SXKu频段-波束控制器主机开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxku_Zbeamswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SXKu频段-波束控制器备机开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxku_Bbeamswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SXKu频段-波控机主机5V遥测
        tmp_double = ret_fun124(0.02, 0, 1.667, 0, strYC.group1.Sxku_BK_main5v);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SXKu频段-波控机备机5V遥测
        tmp_double = ret_fun124(0.02, 0, 1.667, 0, strYC.group1.Sxku_BK_sub5v);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);

        // SxKu频段模块1二次电源接收开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum1_jsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块1二次电源发射开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum1_fsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块2二次电源接收开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum2_jsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块2二次电源发射开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum2_fsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块3二次电源接收开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum3_jsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块3二次电源发射开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum3_fsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块4二次电源接收开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum4_jsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        // SxKu频段模块4二次电源发射开关遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.Sxkum4_fsswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);

        //SXKu频段-射频收发二次电源状态1 bit7
        tmp_uchar=strYC.group1.Sxku_sf_comunit;
        qstr=(tmp_uchar&0x80)?"供电":"未供电";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发二次电源状态2 bit6
        qstr=(tmp_uchar&0x40)?"供电":"未供电";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发二次电源状态3 bit5
        qstr=(tmp_uchar&0x20)?"供电":"未供电";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发二次电源状态4 bit4
        qstr=(tmp_uchar&0x10)?"供电":"未供电";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发二次电源状态5 bit3
        qstr=(tmp_uchar&0x08)?"供电":"未供电";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发二次电源状态6 bit2
        qstr=(tmp_uchar&0x04)?"供电":"未供电";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发接收电 bit1
        qstr=(tmp_uchar&0x02)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);
        //SXKu频段-射频收发发射电 bit0
        qstr=(tmp_uchar&0x01)?"开机":"关机";
        OUT_G1_c1.append(qstr);
        DB_group1.append(qstr);


        if(ui->radioButton_group1->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G1_c1.size();out++)
            {
                model->setItem(rowcnt++, 1, new QStandardItem(OUT_G1_c1.at(out)));
            }
//            //判断变色部分
//            for (int i=0;i<v_change.size();i++) {
//                if(v_change.at(i).chan==true)
//                    model->setData(model->index(v_change.at(i).rows,1),QBrush(QColor(0,255,0)),Qt::TextColorRole);//绿色
//            }
        }
        //////////////////////////////////////////新列
        rowcnt=0;
//        v_change.resize(0);
        QStringList OUT_G1_c3;
        // 载荷-A组消浪涌开关状态遥测(8bytes)
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.ZH_Aswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-B组消浪涌开关状态遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.ZH_Bswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-C组消浪涌开关状态遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.ZH_Cswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-D组消浪涌开关状态遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.ZH_Dswitch);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-A组母线电压遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.A_Voltagemon);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-B组母线电压遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.B_Voltagemon);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-C组母线电压遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.C_Voltagemon);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 载荷-D组母线电压遥测
        tmp_double = ret_fun124(0.02, 0, 1, 0, strYC.group1.D_Voltagemon);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);

        // 可重构射频前端主份+6VA供电(10bytes)
        tmp_double = ret_fun124(0.02, 0, 2.4, 0, strYC.group1.z_up6VA);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端主份-6VA供电
        tmp_double = ret_fun124(0.02, 0, -2.4, 0, strYC.group1.z_down6VA);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端主份+15VA供电
        tmp_double = ret_fun124(0.02, 0, 6.1, 0, strYC.group1.z_up15VA);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端主份+5VD供电
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.z_up5VD);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端主份+6V2A供电
        tmp_double = ret_fun124(0.02, 0, 2.4, 0, strYC.group1.z_up6V2A);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端备份+6VA供电
        tmp_double = ret_fun124(0.02, 0, 2.4, 0, strYC.group1.b_up6VA);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端备份-6VA供电
        tmp_double = ret_fun124(0.02, 0, -2.4, 0, strYC.group1.b_down6VA);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端备份+15VA供电
        tmp_double = ret_fun124(0.02, 0, 6.1, 0, strYC.group1.b_up15VA);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端备份+5VD供电
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.b_up5VD);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        // 可重构射频前端备份+6V2A供电
        tmp_double = ret_fun124(0.02, 0, 2.4, 0, strYC.group1.b_up6V2A);
        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);

        //可重构算力1供电遥测-(+6VA)
        tmp_double = ret_fun124(0.02, 0, 2.4, 0, strYC.group1.gsl1_6Vpowemon);
//        if(5.4<=tmp_double && tmp_double<=6.6)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=18;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力1路1遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl1_5Vl1powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=19;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力1路2遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl1_5Vl2powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=20;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力1路3遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl1_5Vl3powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=21;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力1路4遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl1_5Vl4powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=22;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);


        //可重构算力2供电遥测-(+6VA)
        tmp_double = ret_fun124(0.02, 0, 2.4, 0, strYC.group1.gsl2_6Vpowemon);
//        if(5.4<=tmp_double && tmp_double<=6.6)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=23;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力2路1遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl2_5Vl1powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=24;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力2路2遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl2_5Vl2powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=25;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力2路3遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl2_5Vl3powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=26;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);
        //可重构算力2路4遥测-(+5VD)
        tmp_double = ret_fun124(0.02, 0, 2, 0, strYC.group1.gsl2_5Vl4powemon);
//        if(4.5<=tmp_double && tmp_double<=5.5)str_change.chan=true;//判断变色
//        else str_change.chan=false;
//        str_change.rows=27;
//        v_change.append(str_change);

        qstr = QString::number(tmp_double);
        OUT_G1_c3.append(qstr);
        DB_group1.append(qstr);


        if(ui->radioButton_group1->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G1_c3.size();out++)
            {
                model->setItem(rowcnt++, 3, new QStandardItem(OUT_G1_c3.at(out)));
            }
//            //判断变色部分
//            for (int i=0;i<v_change.size();i++) {
//                if(v_change.at(i).chan==true)
//                    model->setData(model->index(v_change.at(i).rows,3),QBrush(QColor(0,255,0)),Qt::TextColorRole);//绿色
//            }
        }

        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G1_c5;

        // bit7-bit2:保留，bit1-bit0:L频段-天线收发状态
        tmp_uchar = strYC.group1.L_sendrecv;
        uchar switmp = tmp_uchar;
        switch (switmp) {
        case 0:
            qstr="0:发射状态";
            break;
        case 1:
            qstr="1:待机状态";
            break;
        case 2:
            qstr="2:接收状态";
            break;
        default:
            qstr="无";
            break;
        }
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit7-bit2:保留，bit1-bit0:SXKu频段-天线收发状态
        tmp_uchar = strYC.group1.Sxku_sendrecv;
        switmp = tmp_uchar;
        switch (switmp) {
        case 0:
            qstr="0:发射状态";
            break;
        case 1:
            qstr="1:待机状态";
            break;
        case 2:
            qstr="2:接收状态";
            break;
        default:
            qstr="无";
            break;
        }
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit7保留
        //bit6,可重构高算力平台1-接口控制模块-接口控制模块DSP6678心跳
        tmp_uchar = strYC.group1.gsl1_interDSP6701;
        qstr=(tmp_uchar & 0x40)?"正常":"故障";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit5,高算力1-接口控制模块-接口控制模块DSP6701加载状态;
        qstr=(tmp_uchar & 0x20)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit4,DSP6678加载状态,
        qstr=(tmp_uchar & 0x10)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit3,接口控制模块V7加载状态
        qstr=(tmp_uchar & 0x08)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit2,收发处理模块K7加载状态
        qstr=(tmp_uchar & 0x04)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit1,数据处理模块A的K7加载状态
        qstr=(tmp_uchar & 0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0,数据处理模块B的K7加载状态
        qstr=(tmp_uchar & 0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7-bit2:保留
        // bit1,可重构高算力平台1-收发处理模块-V7_1加载状态
        tmp_uchar = strYC.group1.gsl1_V71;
        qstr=(tmp_uchar & 0x02)>>1?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0,可重构高算力平台1-收发处理模块-V7_2加载状态
        qstr=(tmp_uchar & 0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7-bit4:保留
        //bit3,可重构高算力平台1-数据处理模块A-DSP6678心跳
        tmp_uchar = strYC.group1.gsl1_SJA_DSP6678;
        qstr=(tmp_uchar & 0x08)?"正常":"故障";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit2，可重构高算力平台1-数据处理模块A-DSP6678加载状态
        qstr=(tmp_uchar & 0x04)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit1，可重构高算力平台1-数据处理模块A-V7_1加载状态
        qstr=(tmp_uchar & 0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0，可重构高算力平台1-数据处理模块A-V7_2加载状态
        qstr=(tmp_uchar & 0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7-bit4:保留
        //bit3可重构高算力平台1-数据处理模块B-DSP6678心跳
        tmp_uchar = strYC.group1.gsl1_SJB_DSP6678;
        qstr=(tmp_uchar&0x08)?"正常":"故障";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit2，可重构高算力平台1-数据处理模块B-DSP6678加载状态
        qstr=(tmp_uchar&0x04)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit1，可重构高算力平台1-数据处理模块B-V7_1加载状态
        qstr=(tmp_uchar&0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0，可重构高算力平台1-数据处理模块B-V7_2加载状态
        qstr=(tmp_uchar&0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7:保留
        //bit6,可重构高算力平台2-接口控制模块-接口控制模块DSP6678心跳
        tmp_uchar = strYC.group1.gsl2_interDSP6701;
        qstr=(tmp_uchar&0x40)?"正常":"故障";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit5可重构高算力平台2-接口控制模块-接口控制模块DSP6701加载状态
        qstr=(tmp_uchar&0x20)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit4可重构高算力平台2-接口控制模块-接口控制模块DSP6778加载状态
        qstr=(tmp_uchar&0x10)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit3可重构高算力平台2-接口控制模块-接口控制模块V7加载状态
        qstr=(tmp_uchar&0x08)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit2可重构高算力平台2-接口控制模块-收发处理模块K7加载状态
        qstr=(tmp_uchar&0x04)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit1可重构高算力平台2-接口控制模块-数据处理模块A的K7加载状态
        qstr=(tmp_uchar&0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0可重构高算力平台2-接口控制模块-数据处理模块B的K7加载状态
        qstr=(tmp_uchar&0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7-bit2:保留
        // bit1可重构高算力平台2-收发处理模块-V7_1加载状态
        tmp_uchar = strYC.group1.gsl2_V71;
        qstr=(tmp_uchar&0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0可重构高算力平台2-收发处理模块-V7_2加载状态
        qstr=(tmp_uchar&0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7-bit4:保留
        // bit3,可重构高算力平台2-数据处理模块A-DSP6678心跳
        tmp_uchar = strYC.group1.gsl2_SJA_DSP6678;
        qstr=(tmp_uchar&0x08)?"正常":"故障";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit2可重构高算力平台2-数据处理模块A-DSP6678加载状态
        qstr=(tmp_uchar&0x04)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit1可重构高算力平台2-数据处理模块A-V7_1加载状态
        qstr=(tmp_uchar&0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0可重构高算力平台2-数据处理模块A-V7_2加载状态
        qstr=(tmp_uchar&0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        // bit7-bit4:保留
        // bit3,可重构高算力平台2-数据处理模块B-DSP6678心跳
        tmp_uchar = strYC.group1.gsl2_SJB_DSP6678;
        qstr=(tmp_uchar&0x08)?"正常":"故障";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit2可重构高算力平台2-数据处理模块B-DSP6678加载状态
        qstr=(tmp_uchar&0x04)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit1可重构高算力平台2-数据处理模块B-V7_1加载状态
        qstr=(tmp_uchar&0x02)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);
        // bit0可重构高算力平台2-数据处理模块B-V7_2加载状态
        qstr=(tmp_uchar&0x01)?"已加载":"未加载";
        OUT_G1_c5.append(qstr);
        DB_group1.append(qstr);

        if(ui->radioButton_group1->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G1_c5.size();out++)
            {
                model->setItem(rowcnt++, 5, new QStandardItem(OUT_G1_c5.at(out)));
            }
        }
        //////////////////////////////////////////新列
        rowcnt=0;

        QStringList OUT_G1_c7;
        // 综合管控单元-CAN通道A复位次数
        qstr = QString::number(strYC.group1.comper_canA);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-CAN通道B复位次数
        qstr = QString::number(strYC.group1.comper_canB);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-L频段相控阵天线-CAN接收异常帧次数
        qstr = QString::number(strYC.group1.L_canexception);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-SXKu频段相控阵天线-CAN接收异常帧次数
        qstr = QString::number(strYC.group1.Sxku_canexception);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构射频前端-CAN接收异常帧次数
        qstr = QString::number(strYC.group1.kcg_canexception);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台1-CAN接收异常帧次数
        qstr = QString::number(strYC.group1.gsl1_canexption);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台2-CAN接收异常帧次数
        qstr = QString::number(strYC.group1.gsl2_canexption);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);


        //综合管控单元-L频段相控阵天线-CAN接收计数
        qstr = QString::number(strYC.group1.L_recount);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-SXKu频段相控阵天线-CAN接收计数
        qstr = QString::number(strYC.group1.SXKu_recount);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-可重构射频前端-CAN接收计数
        qstr = QString::number(strYC.group1.kcgspqd_recount);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-可重构高算力平台1-CAN接收计数
        qstr = QString::number(strYC.group1.gsl1_recount);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-可重构高算力平台2-CAN接收计数
        qstr = QString::number(strYC.group1.gsl2_recount);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);

        // 综合管控单元-1553B总线指令接收帧计数
        qstr = QString::number(strYC.group1.ZL_1553number);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);

        // 综合管控单元-1553B总线注数接收帧计数
        qstr = QString::number(strYC.group1.ZS_1553number);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-1553B总线帧接收异常次数
        qstr = QString::number(strYC.group1.Z_1553number);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-1553B总线复位次数
        qstr = QString::number(strYC.group1.FW_1553number);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);

        // 1553B指令执行结果-上一帧
        qstr = g1_orderResuit[strYC.group1.front_frame];
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 1553B指令执行结果-当前帧
        qstr = g1_orderResuit[strYC.group1.now_frame];
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-管控机星时（后面移动到前面）
        uint time = strYC.group1.gk_time;
        time = qToBigEndian(time);
        qstr = QString::number(time, 10);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-工作状态
        tmp_uchar = strYC.group1.comper_work;
        qstr =g1_gk_workmode[tmp_uchar];
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-有效任务总数
        qstr = QString::number(strYC.group1.Effective);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);

        // 综合管控单元-已存任务总数
        qstr = QString::number(strYC.group1.YCnumber);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-当前执行任务的流水号
        qstr = QString::number(qToBigEndian(strYC.group1.Currently_number));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台1-当前处理FPGA1执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl1_miss1));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台1-当前处理FPGA2执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl1_miss2));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台1-当前处理FPGA3执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl1_miss3));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台1-当前处理FPGA4执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl1_miss4));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台2-当前处理FPGA1执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl2_miss1));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台2-当前处理FPGA2执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl2_miss2));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台2-当前处理FPGA3执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl2_miss3));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-可重构高算力平台2-当前处理FPGA4执行的主任务ID
        qstr = QString::number(qToBigEndian(strYC.group1.gsl2_miss4));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);


        // bit7综合管控单元-可重构高算力平台1-工作频段
        tmp_uchar = strYC.group1.gsl1_workpd;
        qstr=(tmp_uchar&0x08)?"SXku 频段":"L频段";
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // bit6综合管控单元-可重构高算力平台2-工作频段
        qstr=(tmp_uchar&0x04)?"SXku 频段":"L频段";
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // bit5综合管控单元-可重构高算力平台1-主从（控射频前端）状态
        qstr=(tmp_uchar&0x02)?"从状态":"主状态";
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // bit4综合管控单元-可重构高算力平台2-主从（控射频前端）状态
        qstr=(tmp_uchar&0x01)?"从状态":"主状态";
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);

        //综合管控单元-软件上注块存储快状态
        tmp_uchar = strYC.group1.sorft_status;
        qstr=(tmp_uchar&0x80)?"有效":"无效";
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-Can软件更新进度或6G刷新进度
        qstr=QString::number(tmp_uchar&0x7F);
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-千兆网口软件接收帧计数
        qstr = QString::number(qToBigEndian(strYC.group1.K_recvnumber));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        // 综合管控单元-千兆网口软件发送帧计数
        qstr = QString::number(qToBigEndian(strYC.group1.K_sendnumber));
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);
        //综合管控单元-维护状态
        qstr=g1_gkUpstatus[strYC.group1.up_status];
        OUT_G1_c7.append(qstr);
        DB_group1.append(qstr);


        if(ui->radioButton_group1->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G1_c7.size();out++)
            {
                model->setItem(rowcnt++, 7, new QStandardItem(OUT_G1_c7.at(out)));
            }
        }

        //yc1写入数据库
        QSqlQuery qureydb;
        QString stryc=QString("insert into YC1553_slowP1 values(");
        //ID,时间
        QDateTime cur_time = QDateTime::currentDateTime();
        QString strtime = cur_time.toString("MM-dd hh:mm:ss");
        //单机
        QString dj="单机"+QString::number(ch+1);
        stryc+=QString("'%1','%2',").arg(strtime).arg(dj);

        for (int n=0;n<DB_group1.size()-1;n++) {
            stryc+=QString("'%1',").arg(DB_group1.at(n));
        }
        stryc+=QString("'%1');").arg(DB_group1.last());
        //qDebug()<<stryc;
        qureydb.exec(stryc);
    }

    // 第二组遥测
    if (strYC.group2.pack_head_2 == 0x3307) {
        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G2_c1;
        QStringList DB_group2;
        // L频段相控阵天线-波控发射PRF监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_sendPRF);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-波控接收PRF监测
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_recvPRF);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵1通道1
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z1Access1);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵1通道2
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z1Access2);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵3通道2
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z3Access2);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵3通道3
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z3Access3);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵2通道4
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z2Access4);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵2通道5
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z2Access5);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵4通道5
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z4Access5);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-天线子阵4通道6
        tmp_double = ret_fun124(0.0196, 0, 1, 0, strYC.group2.L_Z4Access6);
        qstr = QString::number(tmp_double);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);

        //SAR成像-系统工作状态
        qstr=g2_SAR_workmode[strYC.group2.SAR_WorkMode];
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //SAR成像-SAR分系统状态
        switch (strYC.group2.SAR_Status>>4) {
        case 0:
            qstr="SAR初态:[0]";
            break;
        case 3:
            qstr="待命状态:[3]";
            break;
        case 5:
            qstr="SAR准备:[5]";
            break;
        case 9:
            qstr="成像状态-SAR输出数据:[9]";
            break;
        case 13:
            qstr="SAR关机:[13]";
            break;
        case 14:
            qstr="SAR故障:[14]";
            break;
        default:
            qstr="未知";
            break;
        }
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //SAR成像-指令接收/处理状态
        switch (strYC.group2.SAR_Status&0x0F) {
        case 0:
            qstr="SAR初态:[0]";
            break;
        case 3:
            qstr="指令包正确:[3]";
            break;
        case 5:
            qstr="指令包格式错误:[5]";
            break;
        case 6:
            qstr="指令包内容错误:[6]";
            break;
        case 9:
            qstr="指令包配合错误:[9]";
            break;
        case 10:
            qstr="指令包执行正确:[10]";
            break;
        case 12:
            qstr="工作参数包过期:[12]";
            break;
        case 15:
            qstr="指令队列满:[15]";
            break;
        default:
            qstr="未知";
            break;
        }
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //SAR成像-EDAC错误计数
        qstr = QString::number(strYC.group2.SAR_EDAC);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //SAR成像-CPU复位计数
        qstr = QString::number(strYC.group2.SAR_CPU);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //SAR成像-CAN总线复位计数
        qstr = QString::number(strYC.group2.SAR_CAN);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //SAR成像-收指令计数
        qstr = QString::number(strYC.group2.SAR_reCount);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);

        //L频段相控阵天线-射频收发单元-开关状态
        tmp_uchar = strYC.group2.L_reseSwitch;
        switch (tmp_uchar) {
        case 0:
            qstr="初始状态";
            break;
        case 1:
            qstr="1234路开";
            break;
        case 2:
            qstr="1256路开";
            break;
        case 3:
            qstr="3456路开";
            break;
        default:
            qstr="无有效值:"+QString::number(tmp_uchar);
            break;
        }
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);

        // SXKu频段相控阵天线-射频收发单元-开关状态
        tmp_uchar = strYC.group2.Sxku_RFswitch;
        map<int,QString> g2_sxku_s;
        g2_sxku_s[0]="初始状态";
        g2_sxku_s[85]="1234路开";
        g2_sxku_s[153]="1256路开";
        g2_sxku_s[170]="3456路开";
        qstr=g2_sxku_s[tmp_uchar];
        if(g2_sxku_s[tmp_uchar]=="")qstr="未知:"+QString::number(tmp_uchar);
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);


        //bit7:高算力1-V7与交换A光纤建链指示
        tmp_uchar = strYC.group2.GSL_jianLian;
        qstr=(tmp_uchar & 0x80)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit6:高算力1-V7与交换B光纤建链指示
        qstr=(tmp_uchar & 0x40)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit5:高算力1-V7与管控主Rapid IO建链指示
        qstr=(tmp_uchar & 0x20)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit4:高算力1-V7与管控备Rapid IO建链指示
        qstr=(tmp_uchar & 0x10)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit3:高算力2-V7与交换A光纤建链指示
        qstr=(tmp_uchar & 0x08)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit2:高算力2-V7与交换B光纤建链指示
        qstr=(tmp_uchar & 0x04)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit1:高算力2-V7与管控主Rapid IO建链指示
        qstr=(tmp_uchar & 0x02)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);
        //bit0:高算力2-V7与管控备Rapid IO建链指示
        qstr=(tmp_uchar & 0x01)?"建链":"未建链";
        OUT_G2_c1.append(qstr);
        DB_group2.append(qstr);

        if(ui->radioButton_group2->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G2_c1.size();out++)
            {
                model->setItem(rowcnt++, 1, new QStandardItem(OUT_G2_c1.at(out)));
            }
        }

        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G2_c3;
        // bit7-
        tmp_uchar = strYC.group2.gsl1_JKpower;
        //bit6-可重构高算力平台1-接口控制模块-光模块参数更新状态
        qstr=(tmp_uchar & 0x40)?"成功":"失败";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台1-接口控制模块-光模块供电指示(FIBER_3V3_PG)
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSPVTT)
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V8)
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V5)
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V0_SMART)
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V0)
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit4保留
        // bit3-可重构高算力平台1-收发处理模块-FPGA1的1DDR
        tmp_uchar = strYC.group2.gsl1_SFFPGApower;
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-收发处理模块-FPGA1的2DDR
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-收发处理模块-FPGA2的1DDR
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-收发处理模块-FPGA2的2DDR
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit5保留
        // bit4-可重构高算力平台1-收发处理模块-AD1电源1V电源P
        tmp_uchar = strYC.group2.gsl1_SFAD1power;
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-收发处理模块-AD1电源1_1V电
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-收发处理模块-AD1电源1_2V电
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-收发处理模块-AD1电源1.3VA
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-收发处理模块-AD1电源2V电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit5保留
        // bit4-可重构高算力平台1-收发处理模块-AD2电源1V电源P
        tmp_uchar = strYC.group2.gsl1_SFAD2power;
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-收发处理模块-AD2电源1_1V电
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-收发处理模块-AD2电源1_2V电
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-收发处理模块-AD2电源1.3VB
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-收发处理模块-AD2电源2V电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit6保留
        // bit5-可重构高算力平台1-收发处理模块-AD3电源1V电源P
        tmp_uchar = strYC.group2.gsl1_SFAD3power;
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台1-收发处理模块-AD3电源1_1V电
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-收发处理模块-AD3电源1_2V电
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-收发处理模块-AD3电源2V电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit6保留
        // bit5-可重构高算力平台1-收发处理模块-1.5V电源PG指示
        tmp_uchar = strYC.group2.gsl1_SFpower;
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台1-收发处理模块-2_1.5V电源PG
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-收发处理模块-AD1电源1.8V电
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-收发处理模块-2.8V电源PG指示
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-收发处理模块-模拟3.3V电源PG
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-收发处理模块-模拟3.3_2电源Ps
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7
        tmp_uchar = strYC.group2.gsl1_SJAlightpower;
        //bit6可重构高算力平台1-数据处理模块A-光模块参数更新状态
        qstr=(tmp_uchar & 0x40)?"成功":"失败";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台1-数据处理模块A-光模块(PG_FI
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台1-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        // bit7
        tmp_uchar = strYC.group2.gsl1_SJBlightpower;
        //bit6可重构高算力平台1-数据处理模块B-光模块参数更新状态
        qstr=(tmp_uchar & 0x40)?"成功":"失败";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台1-数据处理模块B-光模块(PG_FI
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台1-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c3.append(qstr);
        DB_group2.append(qstr);

        if(ui->radioButton_group2->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G2_c3.size();out++)
            {
                model->setItem(rowcnt++, 3, new QStandardItem(OUT_G2_c3.at(out)));
            }
        }
        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G2_c5;
        // bit7
        //bit6可重构高算力平台1-接口控制模块-光模块参数更新状态
        tmp_uchar = strYC.group2.gsl2_JKlightpower;
        qstr=(tmp_uchar & 0x40)?"成功":"失败";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台2-接口控制模块-光模块供电指示(FI
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台2-接口控制模块-DSP供电指示(PG
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-接口控制模块-DSP供电指示(PG
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-接口控制模块-DSP供电指示(PG
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-接口控制模块-DSP供电指示(PG
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-接口控制模块-DSP供电指示(PG
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit4保留
        // bit3-可重构高算力平台2-收发处理模块-FPGA1的1DDR
        tmp_uchar = strYC.group2.gsl2_SFFPGA;
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-收发处理模块-FPGA1的2DDR
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-收发处理模块-FPGA2的1DDR
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-收发处理模块-FPGA2的2DDR
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit5保留
        // bit4-可重构高算力平台2-收发处理模块-AD1电源1V电源P
        tmp_uchar = strYC.group2.gsl2_SFAD1power;
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-收发处理模块-AD1电源1_1V电
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-收发处理模块-AD1电源1_2V电
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-收发处理模块-AD1电源1.3VA
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-收发处理模块-AD1电源2V电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit5保留
        // bit4-可重构高算力平台2-收发处理模块-AD2电源1V电源P
        tmp_uchar = strYC.group2.gsl2_SFAD2power;
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-收发处理模块-AD2电源1_1V电
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-收发处理模块-AD2电源1_2V电
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-收发处理模块-AD2电源1.3VB
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-收发处理模块-AD2电源2V电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit4保留
        // bit3可重构高算力平台2-收发处理模块-AD3电源1V电源P
        tmp_uchar = strYC.group2.gsl2_SFAD3power;
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-收发处理模块-AD3电源1_1V电
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-收发处理模块-AD3电源1_2V电
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-收发处理模块-AD3电源2V电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit6保留
        // bit5-可重构高算力平台2-收发处理模块-1.5V电源PG指示
        tmp_uchar = strYC.group2.gsl2_SFpower;
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台2-收发处理模块-2_1.5V电源PG
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-收发处理模块-AD1电源1.8V电
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-收发处理模块-2.8V电源PG指示
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-收发处理模块-模拟3.3V电源PG
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-收发处理模块-模拟3.3_2电源P
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7-
        tmp_uchar = strYC.group2.gsl2_SJAlightpower;
        //bit6可重构高算力平台2-数据处理模块A-光模块参数更新状态
        qstr=(tmp_uchar & 0x40)?"成功":"失败";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台2-数据处理模块A-光模块(PG_FI
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台2-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-数据处理模块A-DSP电源(PG_
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        // bit7
        tmp_uchar = strYC.group2.gsl2_SJBlightpower;
        //bit6 可重构高算力平台2-数据处理模块B-光模块参数更新状态
        qstr=(tmp_uchar & 0x40)?"成功":"失败";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台2-数据处理模块B-光模块(PG_FI
        qstr=(tmp_uchar & 0x20)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台2-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x10)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-数据处理模块B-DSP电源(PG_
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c5.append(qstr);
        DB_group2.append(qstr);

        if(ui->radioButton_group2->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G2_c5.size();out++)
            {
                model->setItem(rowcnt++, 5, new QStandardItem(OUT_G2_c5.at(out)));
            }
        }

        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G2_c7;
        // bit7-保留
        // bit6-可重构高算力平台1-接口控制模块-模块栓锁
        tmp_uchar = strYC.group2.gsl1_JKlock;
        qstr=(tmp_uchar & 0x40)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台1-接口控制模块-收发处理模块栓锁(收
        qstr=(tmp_uchar & 0x20)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台1-接口控制模块-数据处理1模块栓锁(
        qstr=(tmp_uchar & 0x10)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台1-接口控制模块-数据处理2模块栓锁(
        qstr=(tmp_uchar & 0x08)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台1-接口控制模块-锁相环(V2_LD1
        qstr=(tmp_uchar & 0x04)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台1-接口控制模块-锁相环(V2_LD2
        qstr=(tmp_uchar & 0x02)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台1-接口控制模块-锁相环(V2_LD3
        qstr=(tmp_uchar & 0x01)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);

        //bit4,可重构高算力平台1-接口控制模块-V7与综合管控单元RapidIO主备
        tmp_uchar = strYC.group2.gsl1_jk_v7;
        qstr=(tmp_uchar&0x10)?"备":"主";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit3,可重构高算力平台1-接口控制模块-V7与高速交换机光纤主备
        qstr=(tmp_uchar&0x08)?"备":"主";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit2,可重构高算力平台1-接口DSP6678与接口控制 V7建链指示
        qstr=(tmp_uchar&0x04)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit1,可重构高算力平台1-接口DSP6678与数据处理1 DSP6678建链指示
        qstr=(tmp_uchar&0x02)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit0,可重构高算力平台1-接口DSP6678与数据处理2 DSP6678建链指示
        qstr=(tmp_uchar&0x01)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);

        // 可重构高算力平台1-接口板V7接收数据计数
        qstr = QString::number(qToBigEndian(strYC.group2.gsl1_JKV7recv));
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-接口板V7发送数据计数
        qstr = QString::number(qToBigEndian(strYC.group2.gsl1_JKV7send));
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-接口板DSP6678星时
        uint time2 = 0;
        time2=strYC.group2.gsl1_DSP_time;
        time2=qToBigEndian(time2);
        qstr = QString::number(time2, 10);
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);


        //bit7-6
        //bit5,可重构高算力平台1-收发处理模块-ADC1建链指示
        tmp_uchar = strYC.group2.gsl1_ADC_DAC;
        qstr=(tmp_uchar&0x20)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit4,可重构高算力平台1-收发处理模块-ADC2建链指示
        qstr=(tmp_uchar&0x10)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit3,可重构高算力平台1-收发处理模块-ADC3建链指示
        qstr=(tmp_uchar&0x08)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit2,可重构高算力平台1-收发处理模块-DAC1建链指示
        qstr=(tmp_uchar&0x04)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit1,可重构高算力平台1-收发处理模块-DAC2建链指示
        qstr=(tmp_uchar&0x02)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit0,可重构高算力平台1-收发处理模块-DAC3建链指示
        qstr=(tmp_uchar&0x01)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);



        // bit7-保留
        // bit6-可重构高算力平台2-接口控制模块-模块栓锁
        tmp_uchar = strYC.group2.gsl2_JKlock;
        qstr=(tmp_uchar & 0x40)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构高算力平台2-接口控制模块-收发处理模块栓锁(收
        qstr=(tmp_uchar & 0x20)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构高算力平台2-接口控制模块-数据处理1模块栓锁(
        qstr=(tmp_uchar & 0x10)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构高算力平台2-接口控制模块-数据处理2模块栓锁(
        qstr=(tmp_uchar & 0x08)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构高算力平台2-接口控制模块-锁相环(V2_LD1
        qstr=(tmp_uchar & 0x04)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构高算力平台2-接口控制模块-锁相环(V2_LD2
        qstr=(tmp_uchar & 0x02)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构高算力平台2-接口控制模块-锁相环(V2_LD3
        qstr=(tmp_uchar & 0x01)?"锁定":"失锁";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);

        //bit4,可重构高算力平台2-接口控制模块-V7与综合管控单元RapidIO主备
        tmp_uchar = strYC.group2.gsl2_jk_v7;
        qstr=(tmp_uchar&0x10)?"备":"主";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit3,可重构高算力平台2-接口控制模块-V7与高速交换机光纤主备
        qstr=(tmp_uchar&0x08)?"备":"主";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit2,可重构高算力平台2-接口DSP6678与接口控制 V7建链指示
        qstr=(tmp_uchar&0x04)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit1,可重构高算力平台2-接口DSP6678与数据处理1 DSP6678建链指示
        qstr=(tmp_uchar&0x02)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit0,可重构高算力平台2-接口DSP6678与数据处理2 DSP6678建链指示
        qstr=(tmp_uchar&0x01)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);

        // 可重构高算力平台2-接口板V7接收数据计数
        qstr = QString::number(qToBigEndian(strYC.group2.gsl2_JKV7recv));
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-接口板V7发送数据计数
        qstr = QString::number(qToBigEndian(strYC.group2.gsl2_JKV7send));
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-接口板DSP6678星时
        uint time3 = 0;
        time3 =strYC.group2.gsl2_DSP_time;
        time3=qToBigEndian(time3);
        // qstr = ret_fun114(2000, 1, 1, 0, 0, 0, 1, time3);
        qstr = QString::number(time3, 10);
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);


        //bit7-6
        //bit5,可重构高算力平台2-收发处理模块-ADC1建链指示
        tmp_uchar = strYC.group2.gsl2_ADC_DAC;
        qstr=(tmp_uchar&0x20)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit4,可重构高算力平台2-收发处理模块-ADC2建链指示
        qstr=(tmp_uchar&0x10)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit3,可重构高算力平台2-收发处理模块-ADC3建链指示
        qstr=(tmp_uchar&0x08)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit2,可重构高算力平台2-收发处理模块-DAC1建链指示
        qstr=(tmp_uchar&0x04)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit1,可重构高算力平台2-收发处理模块-DAC2建链指示
        qstr=(tmp_uchar&0x02)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);
        //bit0,可重构高算力平台2-收发处理模块-DAC3建链指示
        qstr=(tmp_uchar&0x01)?"建链":"未建链";
        OUT_G2_c7.append(qstr);
        DB_group2.append(qstr);


        if(ui->radioButton_group2->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G2_c7.size();out++)
            {
                model->setItem(rowcnt++, 7, new QStandardItem(OUT_G2_c7.at(out)));
            }
        }

        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G2_c9;
        // bit7-bit2保留
        // bit1-综合管控单元-OC开关状态-L频段相控阵天线消浪涌
        tmp_uchar = strYC.group2.ZH_OCCANstatus;
        qstr=(tmp_uchar & 0x02)?"开机":"关机";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit0-综合管控单元-OC开关状态-L频段相控阵天线31V总电
        qstr=(tmp_uchar & 0x01)?"开机":"关机";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);



        // 综合管控单元-综合处理模块-AI电压
        tmp_double = ret_fun124(0.01, 0, 1, 0, strYC.group2.ZH_aivoltage);
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 综合管控单元-综合处理模块-3个DSP6678总电压
        tmp_double = ret_fun124(0.01, 0, 1, 0, strYC.group2.ZH_DSp6678);
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);

        // bit7-bit6保留
        // bit5-可重构射频前端-SXKu频段射频通道56
        tmp_uchar = strYC.group2.L_RFswitch;
        qstr=(tmp_uchar & 0x20)?"开":"关";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构射频前端-SXKu频段射频通道34
        qstr=(tmp_uchar & 0x10)?"开":"关";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构射频前端-SXKu频段射频通道12
        qstr=(tmp_uchar & 0x08)?"开":"关";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构射频前端-L波段射频切换调理模
        qstr=(tmp_uchar & 0x04)?"开":"关";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构射频前端-中频切换模块1遥测量
        qstr=(tmp_uchar & 0x02)?"开":"关";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构射频前端-中频切换模块2遥测量
        qstr=(tmp_uchar & 0x01)?"开":"关";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);

        // bit7-可重构射频前端-宽带一本振2主环锁定指示
        tmp_uchar = strYC.group2.RF_SxkuPH35;
        qstr=(tmp_uchar & 0x80)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit6-可重构射频前端-宽带一本振2副环锁定指示
        qstr=(tmp_uchar & 0x40)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit5-可重构射频前端-备份高相噪一本振锁定指示
        qstr=(tmp_uchar & 0x20)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit4-可重构射频前端-备份二本振锁定指示
        qstr=(tmp_uchar & 0x10)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit3-可重构射频前端-宽带一本振1主环锁定指示
        qstr=(tmp_uchar & 0x08)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit2-可重构射频前端-宽带一本振1副环锁定指示
        qstr=(tmp_uchar & 0x04)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit1-可重构射频前端-主份高相噪一本振锁定指示
        qstr=(tmp_uchar & 0x02)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // bit0-可重构射频前端-主份二本振锁定指示
        qstr=(tmp_uchar & 0x01)?"锁定":"失锁";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);



        // L频段相控阵天线-射频综合单元温度
        //        tmp_double = ret_fun104(0.0196, 0, 1, 0, 10000, -6.011336, 4622.237168,-86381.470189, strYC.group2.L_RFWD);
        tmp_double = ret_fun104_tmp(10139,3506, strYC.group2.L_RFWD);
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // L频段相控阵天线-数字综合单机温度
        //        tmp_double = ret_fun104(0.0196, 0, 1, 0, 10000, -6.011336, 4622.237168,-86381.470189, strYC.group2.L_numberWD);
        tmp_double = ret_fun104_tmp(9862,3504, strYC.group2.L_numberWD);
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-接口控制模块-V7温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_JKV7WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-收发处理模块-ADC1温度
        qstr = QString::number(qToBigEndian(strYC.group2.gsl1_JKADC1WD));

        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-收发处理模块-ADC2温度
        qstr = QString::number(qToBigEndian(strYC.group2.gsl1_JKADC2WD));

        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-收发处理模块-ADC3温度
        qstr = QString::number(qToBigEndian(strYC.group2.gsl1_JKADC3WD));
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-收发处理模块-V7_1温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_SFV71WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-收发处理模块-V7_2温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_SFV72WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-数据处理模块A-V 7_1温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_SJAV71WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-数据处理模块A-V 7_2温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_SJAV72WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-数据处理模块B-V 7_1温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_SJBV71WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台1-数据处理模块B-V 7_2温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl1_SJBV72WD));
        // qDebug()<<"可重构高算力平台1-数据处理模块B-V
        // 7_2温度"<<strYC.group2.gsl1_SJBV72WD;
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-接口控制模块-V7温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_JKV7WD));

        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-收发处理模块-ADC1温度
        qstr = QString::number(qToBigEndian(strYC.group2.gsl2_JKADC1WD));
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-收发处理模块-ADC2温度
        qstr = QString::number(qToBigEndian(strYC.group2.gsl2_JKADC2WD));
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-收发处理模块-ADC3温度
        qstr = QString::number(qToBigEndian(strYC.group2.gsl2_JKADC3WD));
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-收发处理模块-V7_1温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_SFV71WD));

        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-收发处理模块-V7_2温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_SFV72WD));

        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-数据处理模块A-V 7_1温度
        tmp_double =
                ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_SJAV71WD));
        // qDebug()<<"可重构高算力平台2-数据处理模块A-V
        // 7_1温度"<<strYC.group2.gsl2_SJAV71WD;
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-数据处理模块A-V 7_2温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_SJAV72WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-数据处理模块B-V 7_1温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_SJBV71WD));
        // qDebug()<<"可重构高算力平台2-数据处理模块B-V
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 可重构高算力平台2-数据处理模块B-V 7_2温度
        tmp_double =ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.gsl2_SJBV72WD));

        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        // 综合管控单元-管控模块-V7温度
        tmp_double = ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.ZH_V7WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //综合管控单元-综合处理模块-V7温度
        tmp_double = ret_fun100(0.123, -273.15, qToBigEndian(strYC.group2.GK_clV7WD));
        qstr = QString::number(tmp_double);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //综合管控单元-综合处理模块-AI温度
        qstr = QString::number(qToBigEndian(strYC.group2.GK_AIWD));
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //综合管控单元-温度保护关断温度阈值-高算力1
        qstr = QString::number(strYC.group2.Tprotect_gsl1);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //综合管控单元-温度保护关断温度阈值-高算力2
        qstr = QString::number(strYC.group2.Tprotect_gsl2);
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);

        //bit7:可重构高算力平台1-数据处理模块A-与高算力2数据处理模块A V7-1时钟锁定
        tmp_uchar = strYC.group2.Mess_gsl1_2;
        qstr=(tmp_uchar & 0x80)?"锁定":"未锁定";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit6:可重构高算力平台1-数据处理模块A-与高算力2数据处理模块A V7-1建链
        qstr=(tmp_uchar & 0x40)?"建链":"未建链";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit5:可重构高算力平台1-数据处理模块B-与高算力2数据处理模块B V7-1时钟锁定
        qstr=(tmp_uchar & 0x20)?"锁定":"未锁定";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit4:可重构高算力平台1-数据处理模块B-与高算力2数据处理模块B V7-1建链
        qstr=(tmp_uchar & 0x10)?"建链":"未建链";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit3:可重构高算力平台2-数据处理模块A-与高算力1数据处理模块A V7-1时钟锁定
        qstr=(tmp_uchar & 0x08)?"供电":"未供电";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit2:可重构高算力平台2-数据处理模块A-与高算力1数据处理模块A V7-1建链
        qstr=(tmp_uchar & 0x04)?"供电":"未供电";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit1:可重构高算力平台2-数据处理模块B-与高算力1数据处理模块B V7-1时钟锁定
        qstr=(tmp_uchar & 0x02)?"供电":"未供电";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);
        //bit0:可重构高算力平台2-数据处理模块B-与高算力1数据处理模块B V7-1建链
        qstr=(tmp_uchar & 0x01)?"供电":"未供电";
        OUT_G2_c9.append(qstr);
        DB_group2.append(qstr);



        if(ui->radioButton_group2->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G2_c9.size();out++)
            {
                model->setItem(rowcnt++, 9, new QStandardItem(OUT_G2_c9.at(out)));
            }
        }

        //yc2写入数据库
        QSqlQuery qureydb;
        QString stryc=QString("insert into YC1553_slowP2 values(");
        //ID,时间
        QDateTime cur_time = QDateTime::currentDateTime();
        QString strtime = cur_time.toString("MM-dd hh:mm:ss");

        //单机
        QString dj="单机"+QString::number(ch+1);
        stryc+=QString("'%1','%2',").arg(strtime).arg(dj);

        for (int n=0;n<DB_group2.size()-1;n++) {
            stryc+=QString("'%1',").arg(DB_group2.at(n));
        }
        stryc+=QString("'%1');").arg(DB_group2.last());
        //qDebug()<<stryc;
        qureydb.exec(stryc);
    }

    // 第三组遥测
    if (strYC.group3.pack_head_3 == 0x3407) {
        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G3_c1;
        QStringList DB_group3;
        ushort tmpus=0;
        uchar tmp_uchar2=0;
        QString s1;
        // bit7-bit5可重构高算力平台1-接口控制模块-V2大版本号
        tmp_uchar = strYC.group3.gsl1_JKV2 >> 5;
        // bit4-bit0可重构高算力平台1-接口控制模块-V2小版本号
        tmp_uchar2 = strYC.group3.gsl1_JKV2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-接口控制模块-V7大版本号
        tmp_uchar = strYC.group3.gsl1_JKV7 >> 5;
        // bit4-bit0可重构高算力平台1-接口控制模块-V7小版本号
        tmp_uchar2 = strYC.group3.gsl1_JKV7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-接口控制模块-DSP6701大版本号
        tmp_uchar = strYC.group3.gsl1_JKDSP6701 >> 5;
        // bit4-bit0可重构高算力平台1-接口控制模块-DSP6701小版本号
        tmp_uchar2 = strYC.group3.gsl1_JKDSP6701 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-接口控制模块-DSP6678大版本号
        tmp_uchar = strYC.group3.gsl1_JKDSP6678 >> 5;
        // bit4-bit0可重构高算力平台1-接口控制模块-DSP6678小版本号
        tmp_uchar2 = strYC.group3.gsl1_JKDSP6678 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-收发处理模块-K7大版本号
        tmp_uchar = strYC.group3.gsl1_SFK7 >> 5;
        // bit4-bit0可重构高算力平台1-收发处理模块-K7小版本号
        tmp_uchar2 = strYC.group3.gsl1_SFK7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-收发处理模块-V7-1大版本号
        tmp_uchar = strYC.group3.gsl1_SFV7_1 >> 5;
        // bit4-bit0可重构高算力平台1-收发处理模块-V7-1小版本号
        tmp_uchar2 = strYC.group3.gsl1_SFV7_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-收发处理模块-V7-1软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SFV7_1soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-收发处理模块-V7-2大版本号
        tmp_uchar = strYC.group3.gsl1_SFV7_2 >> 5;
        // bit4-bit0可重构高算力平台1-收发处理模块-V7-2小版本号
        tmp_uchar2 = strYC.group3.gsl1_SFV7_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-收发处理模块-V7-2软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SFV7_2soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-收发处理模块-K7预加载软件数量
        qstr = QString::number(strYC.group3.gsl1_SFK7_sum);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块A-K7大版本号
        tmp_uchar = strYC.group3.gsl1_SJAK7 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块A-K7大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJAK7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块A-V7-1大版本号
        tmp_uchar = strYC.group3.gsl1_SJAV7_1 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块A-V7-1大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJAV7_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-数据处理模块A-V7-1软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SJAV7_1soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块A-V7-2大版本号
        tmp_uchar = strYC.group3.gsl1_SJAV7_2 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块A-V7-2大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJAV7_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-数据处理模块A-V7-2软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SJAV7_2soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块A-DSP6678大版本号
        tmp_uchar = strYC.group3.gsl1_SJADSP6678 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块A-DSP6678大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJADSP6678 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-数据处理模块A-DSP6678软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SJADSP6678soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        //可重构高算力平台1-数据处理模块A-K7预加载软件数量
        qstr = QString::number(strYC.group3.gsl1_CLAK7_sum);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块B-K7大版本号
        tmp_uchar = strYC.group3.gsl1_SJBK7 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块B-K7大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJBK7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块B-V7-1大版本号
        tmp_uchar = strYC.group3.gsl1_SJBV7_1 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块B-V7-1大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJBV7_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-数据处理模块B-V7-1软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SJBV7_1soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块B-V7-2大版本号
        tmp_uchar = strYC.group3.gsl1_SJBV7_2 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块B-V7-2大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJBV7_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-数据处理模块B-V7-2软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SJBV7_2soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台1-数据处理模块B-DSP6678大版本号
        tmp_uchar = strYC.group3.gsl1_SJBDSP6678 >> 5;
        // bit4-bit0可重构高算力平台1-数据处理模块B-DSP6678大版本号
        tmp_uchar2 = strYC.group3.gsl1_SJBDSP6678 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台1-数据处理模块B-DSP6678软件代号
        tmpus=qToBigEndian(strYC.group3.gsl1_SJBDSP6678soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        //可重构高算力平台1-数据处理模块B-K7预加载软件数量
        qstr = QString::number(strYC.group3.gsl1_CLBK7_sum);
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        //bit7
        //bit6 可重构高算力平台1-接口V7三模运维状态
        tmp_uchar2 = strYC.group3.sorft1_guiding;
        qstr=(tmp_uchar2 & 0x40)?"运维中":"未运维";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);
        //bit5,可重构高算力平台1-软件引导方式-接口控制模块Can解析与重构调度软件
        qstr=(tmp_uchar2 & 0x20)?"Norflash1[1]":"PROM[0]";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);
        //bit4,可重构高算力平台1-软件引导方式-接口控制模块综合调度软件
        qstr=(tmp_uchar2 & 0x10)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);
        //bit3,可重构高算力平台1-软件引导方式-数据处理模块A接口控制软件
        qstr=(tmp_uchar2 & 0x08)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);
        //bit2,可重构高算力平台1-软件引导方式-数据处理模块B接口控制软件
        qstr=(tmp_uchar2 & 0x04)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);
        //bit1,可重构高算力平台1-软件引导方式-收发处理模块接口控制软件
        qstr=(tmp_uchar2 & 0x02)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);
        //bit0,可重构高算力平台1-软件引导方式-接口控制模块数据传输软件
        qstr=(tmp_uchar2 & 0x01)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c1.append(qstr);
        DB_group3.append(qstr);

        if(ui->radioButton_group3->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G3_c1.size();out++)
            {
                model->setItem(rowcnt++, 1, new QStandardItem(OUT_G3_c1.at(out)));
            }
        }
        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G3_c3;

        // bit7-bit5可重构高算力平台2-接口控制模块-V2大版本号
        tmp_uchar = strYC.group3.gsl2_JKV2 >> 5;
        // bit4-bit0可重构高算力平台2-接口控制模块-V2小版本号
        tmp_uchar2 = strYC.group3.gsl2_JKV2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-接口控制模块-V7大版本号
        tmp_uchar = strYC.group3.gsl2_JKV7 >> 5;
        // bit4-bit0可重构高算力平台2-接口控制模块-V7小版本号
        tmp_uchar2 = strYC.group3.gsl2_JKV7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-接口控制模块-DSP6701大版本号
        tmp_uchar = strYC.group3.gsl2_JKDSP6701 >> 5;
        // bit4-bit0可重构高算力平台2-接口控制模块-DSP6701小版本号
        tmp_uchar2 = strYC.group3.gsl2_JKDSP6701 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-接口控制模块-DSP6678大版本号
        tmp_uchar = strYC.group3.gsl2_JKDSP6678 >> 5;
        // bit4-bit0可重构高算力平台2-接口控制模块-DSP6678小版本号
        tmp_uchar2 = strYC.group3.gsl2_JKDSP6678 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7- //bit7-bit5可重构高算力平台2-收发处理模块-K7大版本号
        tmp_uchar = strYC.group3.gsl2_SFK7 >> 5;
        // bit4- //bit4-bit0可重构高算力平台2-收发处理模块-K7小版本号
        tmp_uchar2 = strYC.group3.gsl2_SFK7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-收发处理模块-V7-1大版本号
        tmp_uchar = strYC.group3.gsl2_SFV7_1 >> 5;
        // bit4-bit0可重构高算力平台2-收发处理模块-V7-1小版本号
        tmp_uchar2 = strYC.group3.gsl2_SFV7_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-收发处理模块-V7-1软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SFV7_1soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-收发处理模块-V7-2大版本号
        tmp_uchar = strYC.group3.gsl2_SFV7_2 >> 5;
        // bit4-bit0可重构高算力平台2-收发处理模块-V7-2小版本号
        tmp_uchar2 = strYC.group3.gsl2_SFV7_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-收发处理模块-V7-2软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SFV7_2soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        //可重构高算力平台2-收发处理模块-K7预加载软件数量
        qstr = QString::number(strYC.group3.gsl2_SFK7_sum);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块A-K7大版本号
        tmp_uchar = strYC.group3.gsl2_SJAK7 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块A-K7大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJAK7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块A-V7-1大版本号
        tmp_uchar = strYC.group3.gsl2_SJAV7_1 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块A-V7-1大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJAV7_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-数据处理模块A-V7-1软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SJAV7_1soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块A-V7-2大版本号
        tmp_uchar = strYC.group3.gsl2_SJAV7_2 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块A-V7-2大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJAV7_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-数据处理模块A-V7-2软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SJAV7_2soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块A-DSP6678大版本号
        tmp_uchar = strYC.group3.gsl2_SJADSP6678 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块A-DSP6678大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJADSP6678 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-数据处理模块A-DSP6678软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SJADSP6678soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //可重构高算力平台2-数据处理模块A-K7预加载软件数量
        qstr = QString::number(strYC.group3.gsl2_CLAK7_sum);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块B-K7大版本号
        tmp_uchar = strYC.group3.gsl2_SJBK7 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块B-K7大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJBK7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块B-V7-1大版本号
        tmp_uchar = strYC.group3.gsl2_SJBV7_1 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块B-V7-1大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJBV7_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-数据处理模块B-V7-1软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SJBV7_1soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块B-V7-2大版本号
        tmp_uchar = strYC.group3.gsl2_SJBV7_2 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块B-V7-2大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJBV7_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-数据处理模块B-V7-2软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SJBV7_2soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5可重构高算力平台2-数据处理模块B-DSP6678大版本号
        tmp_uchar = strYC.group3.gsl2_SJBDSP6678 >> 5;
        // bit4-bit0可重构高算力平台2-数据处理模块B-DSP6678大版本号
        tmp_uchar2 = strYC.group3.gsl2_SJBDSP6678 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        // 可重构高算力平台2-数据处理模块B-DSP6678软件代号
        tmpus=qToBigEndian(strYC.group3.gsl2_SJBDSP6678soft);
        s1=QString("0x%1").arg(tmpus,4,16,QLatin1Char('0')).toUpper();
        qstr = s1;
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        //可重构高算力平台2-数据处理模块B-K7预加载软件数量
        qstr = QString::number(strYC.group3.gsl2_CLBK7_sum);
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        //bit7
        //bit6 可重构高算力平台2-接口V7三模运维状态
        tmp_uchar2 = strYC.group3.sorft2_guiding;
        qstr=(tmp_uchar2 & 0x40)?"运维中":"未运维";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //bit5,可重构高算力平台2-软件引导方式-接口控制模块Can解析与重构调度软件
        qstr=(tmp_uchar2 & 0x20)?"Norflash1[1]":"PROM[0]";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //bit4,可重构高算力平台2-软件引导方式-接口控制模块综合调度软件
        qstr=(tmp_uchar2 & 0x10)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //bit3,可重构高算力平台2-软件引导方式-数据处理模块A接口控制软件
        qstr=(tmp_uchar2 & 0x08)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //bit2,可重构高算力平台2-软件引导方式-数据处理模块B接口控制软件
        qstr=(tmp_uchar2 & 0x04)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //bit1,可重构高算力平台2-软件引导方式-收发处理模块接口控制软件
        qstr=(tmp_uchar2 & 0x02)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);
        //bit0,可重构高算力平台2-软件引导方式-接口控制模块数据传输软件
        qstr=(tmp_uchar2 & 0x01)?"Norflash2[1]":"Norflash1[0]";
        OUT_G3_c3.append(qstr);
        DB_group3.append(qstr);

        if(ui->radioButton_group3->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G3_c3.size();out++)
            {
                model->setItem(rowcnt++, 3, new QStandardItem(OUT_G3_c3.at(out)));
            }
        }

        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G3_c5;

        // bit7-bit5综合管控单元-管控模块-P2020大版本号
        tmp_uchar = strYC.group3.ZH_GKP2020 >> 5;
        // bit4-bit0综合管控单元-管控模块-P2020小版本号
        tmp_uchar2 = strYC.group3.ZH_GKP2020 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-管控模块-V7大版本号
        tmp_uchar = strYC.group3.ZH_GKV7 >> 5;
        // bit4-bit0综合管控单元-管控模块-V7小版本号
        tmp_uchar2 = strYC.group3.ZH_GKV7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-综合处理模块-V7大版本号
        tmp_uchar = strYC.group3.ZH_ZHV7 >> 5;
        // bit4-bit0综合管控单元-综合处理模块-V7小版本号
        tmp_uchar2 = strYC.group3.ZH_ZHV7 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-综合处理模块-DSP6678_1大版本号
        tmp_uchar = strYC.group3.ZH_ZHDSP6678_1 >> 5;
        // bit4-bit0综合管控单元-综合处理模块-DSP6678_1小版本号
        tmp_uchar2 = strYC.group3.ZH_ZHDSP6678_1 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-综合处理模块-DSP6678_2大版本号
        tmp_uchar = strYC.group3.ZH_ZHDSP6678_2 >> 5;
        // bit4-bit0综合管控单元-综合处理模块-DSP6678_2小版本号
        tmp_uchar2 = strYC.group3.ZH_ZHDSP6678_2 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-综合处理模块-DSP6678_3大版本号
        tmp_uchar = strYC.group3.ZH_ZHDSP6678_3 >> 5;
        // bit4-bit0综合管控单元-综合处理模块-DSP6678_3小版本号
        tmp_uchar2 = strYC.group3.ZH_ZHDSP6678_3 & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-综合处理模块-AI大版本号
        tmp_uchar = strYC.group3.ZH_ZHai >> 5;
        // bit4-bit0综合管控单元-综合处理模块-AI小版本号
        tmp_uchar2 = strYC.group3.ZH_ZHai & 0x1F;
        qstr=QString("%1.%2").arg(tmp_uchar).arg(tmp_uchar2);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit5综合管控单元-卫星编号
        tmp_uchar = strYC.group3.ZH_GKsatetrack >> 4;
        qstr = QString::number(tmp_uchar);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit4-bit0综合管控单元-轨道编号
        tmp_uchar = strYC.group3.ZH_GKsatetrack & 0x0F;
        qstr = QString::number(tmp_uchar);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit6综合管控单元-管控模块-V2看门狗使能
        tmp_uchar = strYC.group3.ZH_GKV2;
        switch ((tmp_uchar & 0xC0) >> 6) {
        case 1:
            qstr="开";
            break;
        case 2:
            qstr="关";
            break;
        default:
            qstr="无";
            break;
        }
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit5-bit4综合管控单元-主副卫星
        switch ((tmp_uchar & 0x30) >> 4) {
        case 0:
            qstr="单星";
            break;
        case 1:
            qstr="多星联合主";
            break;
        case 2:
            qstr="多星联合副";
            break;
        default:
            qstr="无";
            break;
        }
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit3-bit2综合管控单元-CAN应用通道
        qstr=(tmp_uchar & 0x0C)?"B路":"A路";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit1-bit0综合管控单元-千兆网应用通道
        qstr=(tmp_uchar & 0x03)?"B路":"A路";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // bit7-bit6保留
        // bit3-bit2综合管控单元-任务自动清除使能
        tmp_uchar = strYC.group3.ZH_AreaClear;
        qstr=(((tmp_uchar & 0x0C)>>2)-1)?"关":"开";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit1-bit0综合管控单元-运维规划使能
        qstr=((tmp_uchar & 0x03)-1)?"区域任务":"常规任务";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // 综合管控单元-模板数量
        qstr = QString::number(strYC.group3.ZH_templates_number);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-SSD存储余量
        tmp_double = qToBigEndian(strYC.group3.ZH_SSD);
        qstr = QString::number(tmp_double);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);


        //bit6管控_flash软刷周期使能
        tmp_uchar = strYC.group3.ZH_gsl12_receiverup;
        qstr=(tmp_uchar & 0x40)?"启用":"不启用";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit5综合管控单元-可重构高算力平台1-接收机自动增益控制状态
        qstr=(tmp_uchar & 0x20)?"启用":"不启用";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit4-综合管控单元-可重构高算力平台2-接收机自动增益控制状态
        qstr=(tmp_uchar & 0x10)?"启用":"不启用";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit3-综合管控单元-可重构高算力平台1-接口板V7软件维护状态
        qstr=(tmp_uchar & 0x08)?"纠错":"不纠错";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit2-综合管控单元-可重构高算力平台2-接口板V7软件维护状态
        qstr=(tmp_uchar & 0x04)?"纠错":"不纠错";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // bit1-综合管控单元-V7刷新芯片控制标志
        qstr=(tmp_uchar & 0x02)?"刷新":"不刷新";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        //bit0温度保护关断功能使能标志
        qstr=(tmp_uchar & 0x01)?"使能":"不使能";
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        // 综合管控单元-管控模块向平台发送数据计数
        qstr = QString::number(qToBigEndian(strYC.group3.ZH_GKptsendnumber));
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-管控模块接收路由数据计数
        qstr = QString::number(qToBigEndian(strYC.group3.ZH_GKlyrecvnumber));
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-管控模块向路由发送数据计数
        qstr = QString::number(qToBigEndian(strYC.group3.ZH_GKlysendnumber));
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        //综合管控单元-1553B长抱环计数
        qstr = QString::number(strYC.group3.ZH_1553cbh_cnt);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        //综合管控单元-1553B系统同步计数
        qstr = QString::number(strYC.group3.ZH_1553sys_cnt);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-管控机关机准备次数
        qstr = QString::number(strYC.group3.ZH_GKoffnumber);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-下控单机关机准备次数
        qstr = QString::number(strYC.group3.XKoffnumber);
        OUT_G3_c5.append(qstr);
        DB_group3.append(qstr);

        if(ui->radioButton_group3->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G3_c5.size();out++)
            {
                model->setItem(rowcnt++, 5, new QStandardItem(OUT_G3_c5.at(out)));
            }
        }
        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G3_c7;
        //bit7        管控_万兆网路由连接状态主
        tmp_uchar = strYC.group3.signal_1;
        qstr=(tmp_uchar & 0x80)?"连接":"未连接";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        //bit6        管控_万兆网路由连接状态备
        qstr=(tmp_uchar & 0x40)?"连接":"未连接";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        //bit5综合管控单元-管控模块V7与P2020互联的SRIOx1链接初始化信号
        qstr=(tmp_uchar & 0x20)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit4综合管控单元-管控模块V7与P2020互联的SRIOx1端口初始化信号
        qstr=(tmp_uchar & 0x10)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit3综合管控单元-管控模块V7与高算力备份互联的SRIOx2链接初始化信号
        qstr=(tmp_uchar & 0x08)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit2综合管控单元-管控模块V7与高算力备份互联的SRIOx2端口初始化信号
        qstr=(tmp_uchar & 004)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit1综合管控单元-管控模块V7与高算力主份互联的SRIOx2链接初始化信号
        qstr=(tmp_uchar & 0x02)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit0综合管控单元-管控模块V7与高算力主份互联的SRIOx2端口初始化信号
        qstr=(tmp_uchar & 0x01)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        //bit7综合管控单元-处理模块V7与810A互联SRIOx4链接初始化信号
        tmp_uchar = strYC.group3.signal_2;
        qstr=(tmp_uchar & 0x80)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit6综合管控单元-处理模块V7与810A互联SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x40)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit5综合管控单元-处理模块V7与DSP0互联SRIOx4链接初始化信号
        qstr=(tmp_uchar & 0x20)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit4综合管控单元-处理模块V7与DSP0互联SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x10)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit3综合管控单元-处理模块V7与DSP1互联SRIOx4链接初始化信号
        qstr=(tmp_uchar & 0x08)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit2综合管控单元-处理模块V7与DSP1互联SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x04)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit1综合管控单元-处理模块V7与DSP2互联SRIOx4链接初始化信号
        qstr=(tmp_uchar & 0x02)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit0综合管控单元-处理模块V7与DSP2互联SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x01)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        //bit7综合管控单元-管控模块V7与处理模块V7互联第0路SRIOx4链接初始化信号
        tmp_uchar = strYC.group3.signal_3;
        qstr=(tmp_uchar & 0x80)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit6综合管控单元-管控模块V7与处理模块V7互联第0路SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x40)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit5综合管控单元-综合管控模块V7与综合处理模块V7互联第1路SRIOx4链接初始化信号
        qstr=(tmp_uchar & 0x20)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit4综合管控单元-综合管控模块V7与综合处理模块V7互联第1路SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x10)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit3综合管控单元-综合处理模块V7与综合管控模块V7互联第0路SRIOx4链接初始化信号
        qstr=(tmp_uchar & 0x08)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit2综合管控单元-综合处理模块V7与综合管控模块V7互联第0路SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x04)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit1综合管控单元-综合处理模块V7与综合管控模块V7互联第1路SRIOx4链接初始化信号
        qstr=(tmp_uchar & 0x02)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit0综合管控单元-综合处理模块V7与综合管控模块V7互联第1路SRIOx4端口初始化信号
        qstr=(tmp_uchar & 0x01)?"正常":"错误";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);


        //bit7管控_V7万兆网与存储连接状态
        tmp_uchar = strYC.group3.guiding_main1;
        qstr=(tmp_uchar & 0x80)?"连接":"未连接";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit5-4综合管控单元-P2020软件引导方式

        switch ((tmp_uchar&0x30)>>4) {
        case 0:
            qstr="基础区";
            break;
        case 1:
            qstr="更新区a";
            break;
        case 2:
            qstr="更新区b";
            break;
        case 3:
            qstr="更新区c";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit3-2综合管控单元-综合管控模块-V7软件引导方式
        switch ((tmp_uchar&0x0C)>>2) {
        case 0:
            qstr="更新区:[0]";
            break;
        case 1:
            qstr="基础区:[1]";
            break;
        case 2:
            qstr="未知:[2]";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit1-0综合管控单元-综合处理模块-V7软件引导方式
        switch (tmp_uchar&0x03) {
        case 0:
            qstr="未知:[0]";
            break;
        case 1:
            qstr="更新区:[1]";
            break;
        case 2:
            qstr="未知:[2]";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        //bit7-6综合管控单元-综合处理模块-DSP6678_1软件引导方式
        tmp_uchar = strYC.group3.guiding_main2;
        switch ((tmp_uchar&0xC0)>>6) {
        case 0:
            qstr="基础区:[0]";
            break;
        case 1:
            qstr="更新区:[1]";
            break;
        case 2:
            qstr="未知:[2]";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit5-4综合管控单元-综合处理模块-DSP6678_2软件引导方式
        switch ((tmp_uchar&0x30)>>4) {
        case 0:
            qstr="基础区:[0]";
            break;
        case 1:
            qstr="更新区:[1]";
            break;
        case 2:
            qstr="未知:[2]";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit3-2综合管控单元-综合处理模块-DSP6678_3软件引导方式
        switch ((tmp_uchar&0x0C)>>2) {
        case 0:
            qstr="基础区:[0]";
            break;
        case 1:
            qstr="更新区:[1]";
            break;
        case 2:
            qstr="未知:[2]";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit1-0综合管控单元-综合处理模块-AI软件引导方式
        switch (tmp_uchar&0x03) {
        case 0:
            qstr="基础区:[0]";
            break;
        case 1:
            qstr="更新区:[1]";
            break;
        case 2:
            qstr="未知:[2]";
            break;
        default:
            break;
        }
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        //bit7-4保留
        //bit3综合管控单元-综合处理模块-DSP6678_1启动状态
        tmp_uchar = strYC.group3.guiding_main3;
        qstr=(tmp_uchar&0x08)?"启动正常":"启动超时";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit2综合管控单元-综合处理模块-DSP6678_2启动状态
        qstr=(tmp_uchar&0x04)?"启动正常":"启动超时";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit1综合管控单元-综合处理模块-DSP6678_3启动状态
        qstr=(tmp_uchar&0x02)?"启动正常":"启动超时";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //bit0综合管控单元-综合处理模块-AI启动状态
        qstr=(tmp_uchar&0x01)?"启动正常":"启动超时";
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-SRIO接收异常帧次数
        qstr = QString::number(strYC.group3.SRIO_number);
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        // 综合管控单元-累计已运行任务总数
        qstr = QString::number(strYC.group3.ALLnumber);
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);
        //综合管控单元-即将执行的任务时间
        qstr = QString::number(qToBigEndian(strYC.group3.zhMake_time));
        OUT_G3_c7.append(qstr);
        DB_group3.append(qstr);

        if(ui->radioButton_group3->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G3_c7.size();out++)
            {
                model->setItem(rowcnt++, 7, new QStandardItem(OUT_G3_c7.at(out)));
            }
        }

        //////////////////////////////////////////新列
        rowcnt=0;
        QStringList OUT_G3_c9;

        //SAR成像-串注间接指令码特征码
        qstr = QString::number(strYC.group3.SAR_code);
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit7-bit6:保留
        tmp_uchar = strYC.group3.SAR_mode;
        //bit5-bit4:SAR成像-导航闭锁信号
        switch ((tmp_uchar&0x30)>>4) {
        case 0:
            qstr="初态";
            break;
        case 1:
            qstr="关";
            break;
        case 2:
            qstr="开";
            break;
        default:
            qstr="未知";
            break;
        }
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);

        //bit3-bit0:SAR-任务模式
        qstr=g3_SARmode[tmp_uchar&0x0F];
        if(qstr.isEmpty())qstr="未知"+QString::number(tmp_uchar&0x0F);
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);

        //bit6:SAR-L频段天线波控加载方式-子阵1-子板1
        tmp_uchar = strYC.group3.SAR_LManer;
        qstr=(tmp_uchar&0x80)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);

        //bit6:SAR-L频段天线波控加载方式-子阵1-子板2
        qstr=(tmp_uchar&0x40)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit5:SAR-L频段天线波控加载方式-子阵2-子板1
        qstr=(tmp_uchar&0x20)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit4:SAR-L频段天线波控加载方式-子阵2-子板2
        qstr=(tmp_uchar&0x10)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit3:SAR-L频段天线波控加载方式-子阵3-子板1
        qstr=(tmp_uchar&0x08)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit2:SAR-L频段天线波控加载方式-子阵3-子板2
        qstr=(tmp_uchar&0x04)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit1:SAR-L频段天线波控加载方式-子阵4-子板1
        qstr=(tmp_uchar&0x02)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit0:SAR-L频段天线波控加载方式-子阵4-子板2
        qstr=(tmp_uchar&0x01)?"内部Flash":"外部Flash";
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);


        //..bit7-bit4:可重构高算力平台1-数据处理模块A-FPGAV7-1任务状态
        tmp_uchar = strYC.group3.gsl1_Av7;
        qstr=g3_FPGA_Status[(tmp_uchar&0xF0)>>4];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit3-bt0:可重构高算力平台1-数据处理模块A-FPGAV7-2任务状态
        qstr=g3_FPGA_Status[(tmp_uchar&0x0F)];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //..bit7-bit4可重构高算力平台1-数据处理模块B-FPGAV7-1任务状态
        tmp_uchar = strYC.group3.gsl1_Bv7;
        qstr=g3_FPGA_Status[(tmp_uchar&0xF0)>>4];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit3-bt0:可重构高算力平台1-数据处理模块B-FPGAV7-2任务状态
        qstr=g3_FPGA_Status[(tmp_uchar&0x0F)];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //..bit7-bit4可重构高算力平台2-数据处理模块A-FPGAV7-1任务状态
        tmp_uchar = strYC.group3.gsl2_Av7;
        qstr=g3_FPGA_Status[(tmp_uchar&0xF0)>>4];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit3-bt0:可重构高算力平台2-数据处理模块A-FPGAV7-2任务状态
        qstr=g3_FPGA_Status[(tmp_uchar&0x0F)];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //..bit7-bit4可重构高算力平台2-数据处理模块B-FPGAV7-1任务状态
        tmp_uchar = strYC.group3.gsl2_Bv7;
        qstr=g3_FPGA_Status[(tmp_uchar&0xF0)>>4];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);
        //bit3-bt0:可重构高算力平台2-数据处理模块B-FPGAV7-2任务状态
        qstr=g3_FPGA_Status[(tmp_uchar&0x0F)];
        OUT_G3_c9.append(qstr);
        DB_group3.append(qstr);

        if(ui->radioButton_group3->isChecked())
        {
            rowcnt=0;
            for(int out=0;out<OUT_G3_c9.size();out++)
            {
                model->setItem(rowcnt++, 9, new QStandardItem(OUT_G3_c9.at(out)));
            }
        }

        //yc3写入数据库
        QSqlQuery qureydb;
        QString stryc=QString("insert into YC1553_slowP3 values(");
        //ID,时间
        QDateTime cur_time = QDateTime::currentDateTime();
        QString strtime = cur_time.toString("MM-dd hh:mm:ss");

        //单机
        QString dj="单机"+QString::number(ch+1);
        stryc+=QString("'%1','%2',").arg(strtime).arg(dj);

        for (int n=0;n<DB_group3.size()-1;n++) {
            stryc+=QString("'%1',").arg(DB_group3.at(n));
        }
        stryc+=QString("'%1');").arg(DB_group3.last());
        //qDebug()<<stryc;
        qureydb.exec(stryc);
    }

    // 第四组遥测
    g4_YC_Flag=strYC.pack_head_4;//传递类型标志，显示表头名称
    if (ui->radioButton_group4->isChecked())
    {
        //qDebug() <<"g4head_0x"+QString::number( strYC.pack_head_4,16);

        switch (strYC.pack_head_4) {
        case 0x3507:
            show_yc0735((uchar *)strYC.group4);        //第四组遥测解析-电子侦察任务包(2s)
            break;
        case 0x3607:
            show_yc0736((uchar *)strYC.group4);        //第四组遥测解析-电子干扰任务包(2s)
            break;
        case 0x3707:
            show_yc0737((uchar *)strYC.group4);        //第四组遥测解析-SAR成像任务包(2s)
            break;
        case 0x3807:
            show_yc0738((uchar *)strYC.group4);        //第四组遥测解析-备用导航任务包(2s)
            break;
        case 0x3907:
            show_yc0739((uchar *)strYC.group4);        //第四组遥测解析-类5G通信任务包(2s)
            break;
        case 0x3A07:
            show_yc073A((uchar *)strYC.group4);        //第四组遥测解析-头
            break;
        default:
            break;
        }
    }


}


//显示第四组公共头
void subyc_slowspeed::shoe_pub_g4head(uchar *g4buff)
{
    slow_Group_4_Head str_head;
    memset(&str_head,0,sizeof(str_head));
    memcpy(&str_head,g4buff,sizeof(str_head));

    int rowcnt = 0;//列表行
    QString qstr;
    uchar tmp_uchar=0;
    //综合管控单元-上次执行任务的流水号
    qstr = QString::number(qToBigEndian(str_head.last_number));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台1-上次处理FPGA1执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl1_lastID1));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台1-上次处理FPGA2执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl1_lastID2));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台1-上次处理FPGA3执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl1_lastID3));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台1-上次处理FPGA4执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl1_lastID4));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台2-上次处理FPGA1执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl2_lastID1));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台2-上次处理FPGA2执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl2_lastID2));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台2-上次处理FPGA3执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl2_lastID3));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-可重构高算力平台2-上次处理FPGA4执行的主任务ID
    qstr = QString::number(qToBigEndian(str_head.gsl2_lastID4));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-上次执行任务的实际起始时间
    qstr = QString::number(qToBigEndian(str_head.start_time));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //综合管控单元-上次执行任务的实际终止时间
    qstr = QString::number(qToBigEndian(str_head.end_time));
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //bit7-bit2,综合管控单元-保留
    tmp_uchar=str_head.gk_lastMask;
    //bit1,综合管控单元-上一个任务任务强制终止标志
    qstr=(tmp_uchar&0x02)?"强制终止":"正常终止";
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
    //bit0,综合管控单元-上个任务异常结束标志
    qstr=(tmp_uchar&0x01)?"强制终止":"正常终止";
    model->setItem(rowcnt++, 1, new QStandardItem(qstr));
}


//第四组遥测解析-电子侦察任务包(2s)
void subyc_slowspeed::show_yc0735(uchar *g4buff)
{
    slow_Group_4_ElecZZ str_ElecZZ;
    memset(&str_ElecZZ,0,sizeof (str_ElecZZ));
    memcpy(&str_ElecZZ,g4buff,sizeof (str_ElecZZ));

    //显示第四组公共头
    shoe_pub_g4head((uchar *)&str_ElecZZ.g4_Head);


    int rowcnt = 0;//列表行
    QString qstr;
    uchar tmp_uchar=0;
    //可重构高算力平台1-数据处理模块A-V7-1运行模式
    tmp_uchar=str_ElecZZ.gsl1_AV71Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块A-V7-1运行状态
    tmp_uchar=str_ElecZZ.gsl1_AV71Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块A-V7-2运行模式
    tmp_uchar=str_ElecZZ.gsl1_AV72Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块A-V7-2运行状态
    tmp_uchar=str_ElecZZ.gsl1_AV72Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-1运行模式
    tmp_uchar=str_ElecZZ.gsl1_BV71Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-1运行状态
    tmp_uchar=str_ElecZZ.gsl1_BV71Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-2运行模式
    tmp_uchar=str_ElecZZ.gsl1_BV72Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-2运行状态
    tmp_uchar=str_ElecZZ.gsl1_BV72Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块A-V7-1运行模式
    tmp_uchar=str_ElecZZ.gsl2_AV71Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块A-V7-1运行状态
    tmp_uchar=str_ElecZZ.gsl2_AV71Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块A-V7-2运行模式
    tmp_uchar=str_ElecZZ.gsl2_AV72Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块A-V7-2运行状态
    tmp_uchar=str_ElecZZ.gsl2_AV72Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块B-V7-1运行模式
    tmp_uchar=str_ElecZZ.gsl2_BV71Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块B-V7-1运行状态
    tmp_uchar=str_ElecZZ.gsl2_BV71Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块B-V7-2运行模式
    tmp_uchar=str_ElecZZ.gsl2_BV72Mode;
    qstr = g4_ZC_yxMode[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块B-V7-2运行状态
    tmp_uchar=str_ElecZZ.gsl2_BV72Stas;
    qstr = g4_ZC_yxStas[tmp_uchar];
    if(qstr.isEmpty())qstr="未知:"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));


}
//第四组遥测解析-电子干扰任务包(2s)
void subyc_slowspeed::show_yc0736(uchar *g4buff)
{
    slow_Group_4_ElecGR str_ElecGR;
    memset(&str_ElecGR,0,sizeof (str_ElecGR));
    memcpy(&str_ElecGR,g4buff,sizeof (str_ElecGR));

    //显示第四组公共头
    shoe_pub_g4head((uchar *)&str_ElecGR.g4_Head);
}

//第四组遥测解析-SAR成像任务包(2s)
void subyc_slowspeed::show_yc0737(uchar *g4buff)
{
    slow_Group_4_SAR str_SAR;
    memset(&str_SAR,0,sizeof (str_SAR));
    memcpy(&str_SAR,g4buff,sizeof (str_SAR));

    //显示第四组公共头
    shoe_pub_g4head((uchar *)&str_SAR.g4_Head);

    int rowcnt = 0;//列表行
    QString qstr;
    uchar tmp_uchar=0;
    ushort tmp_ushort=0;
    //SAR成像-成像模式字-极化方式
    tmp_uchar=str_SAR.imaging_mode;
    qstr = (tmp_uchar&0x80)?"VV":"HH";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-通道模式
    switch ((tmp_uchar&0x60)>>6) {
    case 0:
        qstr="双通道A模式:[0]";
        break;
    case 1:
        qstr="双通道B模式:[1]";
        break;
    case 2:
        qstr="单通道A模式:[2]";
        break;
    case 3:
        qstr="单通道B模式:[3]";
        break;
    default:
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-成像模式
    switch (tmp_uchar&0x0F) {
    case 0:
        qstr="连续测试定标:[0]";
        break;
    case 1:
        qstr="广域搜索模式:[1]";
        break;
    case 2:
        qstr="滑动聚束:[2]";
        break;
    case 3:
        qstr="条带模式1(2m):[3]";
        break;
    case 4:
        qstr="条带模式2（3m）:[4]";
        break;
    case 5:
        qstr="TOP模式1(2子带):[5]";
        break;
    case 6:
        qstr="TOP模式2(4子带):[6]";
        break;
    case 7:
        qstr="多角度模式:[7]";
        break;
    default:
        qstr="无对应模式";
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-指令队列长度
    qstr = QString::number(qToBigEndian(str_SAR.order_len));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-SAR开机时间
    qstr = QString::number(qToBigEndian(str_SAR.open_time));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //SAR成像-本地时间码T5
    qstr = QString::number(str_SAR.curr_timeT5);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-本地时间码T4
    qstr = QString::number(str_SAR.curr_timeT4);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-本地时间码T3
    qstr = QString::number(str_SAR.curr_timeT3);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-本地时间码T2
    qstr = QString::number(str_SAR.curr_timeT2);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2,SAR成像-包格式
    tmp_uchar=str_SAR.sar_pack;
    qstr = (tmp_uchar&0x04)?"未知[1]":"标准成像模式:[0]";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1-0,SAR成像-任务类型
    switch (tmp_uchar&0x03) {
    case 0:
        qstr="程控任务(他星引导)";
        break;
    case 1:
        qstr="程控任务(地面上注)";
        break;
    case 2:
        qstr="程控任务(计划任务)";
        break;
    default:
        qstr="未知:"+QString::number(tmp_uchar&0x03);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-流水号
    qstr = QString::number(qToBigEndian(str_SAR.stream_number));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-任务号 高字节
    qstr = QString::number(qToBigEndian(str_SAR.task_mainnumber));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-子任务号 高字节,低字节
    qstr = QString::number(qToBigEndian(str_SAR.task_subnumber));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit7,SAR成像-聚束中心时刻星上修正控制
    tmp_uchar=str_SAR.sar_amendment;
    qstr = (tmp_uchar&0x80)?"星上计算聚束中心时刻":"采用地面上注聚束中心时刻";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5-0,SAR成像-子带个数
    qstr = QString::number(tmp_uchar&0x3F);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-星上参数计算结果错误状态1
    tmp_uchar=str_SAR.start_err1;
    qstr = (tmp_uchar)?("错误类型"+QString::number(tmp_uchar)):"无错误:[0]";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-星上参数计算结果错误状态2
    tmp_uchar=str_SAR.start_err2;
    qstr = (tmp_uchar)?("错误类型"+QString::number(tmp_uchar)):"无错误:[0]";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //SAR成像-当前待执行成像任务数
    qstr = QString::number(qToBigEndian(str_SAR.sar_taskSum));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //////////////////////////////////////////////////////////////////新加
    //bit7-4保留
    //bit3可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-采集回波数据标志
    tmp_uchar=str_SAR.V7_1inSignal;
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-辅助数据接收标志
    qstr = (tmp_uchar&0x04)?"有辅助数据":"无辅助数据";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-数传数据输出标志
    qstr = (tmp_uchar&0x02)?"有输出":"无输出";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-PRF接收标志
    qstr = (tmp_uchar&0x01)?"有PRF":"无PRF";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7-2可重构高算力平台1-收发处理模块-V7-1数据形成-校正流程遥测-AD数据选择
    tmp_uchar=str_SAR.V7_1inJz;
    switch ((tmp_uchar&0xFC)>>2) {
    case 0:
        qstr ="使用ADC0AD1ADC2ADC3的数据";
        break;
    case 1:
        qstr ="使用ADC0AD1ADC4ADC5的数据";
        break;
    case 2:
        qstr ="使用ADC2AD3ADC4ADC5的数据";
        break;
    default:
        qstr="不用:"+QString::number((tmp_uchar&0xFC)>>2);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1可重构高算力平台1-收发处理模块-V7-1数据形成-校正流程遥测-校正流程开始标志
    qstr = (tmp_uchar&0x02)?"djust_start拉高过":"djust_start";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0可重构高算力平台1-收发处理模块-V7-1数据形成-校正流程遥测-校正流程完成标志
    qstr = (tmp_uchar&0x01)?"adjust_over拉高过":"adjust_over";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7-1保留
    //bit0可重构高算力平台1-收发处理模块-V7-1数据形成-校正完成遥测-AD同步流程
    tmp_uchar=str_SAR.V7_1inJzAD;
    qstr = (tmp_uchar&0x01)?"8通道AD同步完成":"8通道AD同步未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));


    //bit7-bit3保留
    //bit2可重构高算力平台1-收发处理模块-V7-2调频源-采集输入输出信号遥测-控制码接收标志
    tmp_uchar=str_SAR.V7_2inJzSignal;
    qstr = (tmp_uchar&0x04)?"无控制码":"接收到控制";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1可重构高算力平台1-收发处理模块-V7-2调频源-采集输入输出信号遥测-DAC数据输出标志
    qstr = (tmp_uchar&0x02)?"DAC输出数据":"DAC无输出数据";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0可重构高算力平台1-收发处理模块-V7-2调频源-采集输入输出信号遥测-PRF接收标志
    qstr = (tmp_uchar&0x01)?"有PRF":"无PRF";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));


    //bit7-bit5保留
    //bit4-1可重构高算力平台1-收发处理模块-V7-2调频源-校正流程遥测-射频选择
    tmp_uchar=str_SAR.V7_2inJz;
    qstr = g4_SAR_sp[(tmp_uchar&0x1E)>>1];
    if(qstr.isEmpty())qstr="不输出"+QString::number((tmp_uchar&0x1E)>>1);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0可重构高算力平台1-收发处理模块-V7-2调频源-校正流程遥测-数据可以开始输出标志
    qstr = (tmp_uchar&0x01)?"DAC可以输出数据":"DAC不可以输出数据";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //保留
    //bit5-3可重构高算力平台1-收发处理模块-V7-2调频源-校正完成遥测-校准数据源选择
    tmp_uchar=str_SAR.V7_2jz;
    switch ((tmp_uchar&0x38)>>3) {
    case 1  :
        qstr="dds数据产生";
        break;
    case 2  :
        qstr="空天院调频源数据";
        break;
    case 7  :
        qstr="梳状谱数据";
        break;
    default:
        qstr="未知:"+QString::number((tmp_uchar&0x38)>>3);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2-0可重构高算力平台1-收发处理模块-V7-2调频源-校正完成遥测-数据输出选择控制码
    switch (tmp_uchar&0x07) {
    case 0  :
        qstr="dds数据产生";
        break;
    case 1  :
        qstr="梳状谱数据";
        break;
    case 2 :
        qstr="校准后数据";
        break;
    case 3 :
        qstr="无";
        break;
    default:
        qstr="未知:"+QString::number(tmp_uchar&0x07);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点8完成标志
    tmp_uchar=str_SAR.A_V71mark;
    qstr = (tmp_uchar&0x80)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点7完成标志
    qstr = (tmp_uchar&0x40)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点6完成标志
    qstr = (tmp_uchar&0x20)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点5完成标志
    qstr = (tmp_uchar&0x10)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点4完成标志
    qstr = (tmp_uchar&0x08)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点3完成标志
    qstr = (tmp_uchar&0x04)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点2完成标志
    qstr = (tmp_uchar&0x02)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点1完成标志
    qstr = (tmp_uchar&0x01)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点8完成标志
    tmp_uchar=str_SAR.A_V72mark;
    qstr = (tmp_uchar&0x80)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点7完成标志
    qstr = (tmp_uchar&0x40)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点6完成标志
    qstr = (tmp_uchar&0x20)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点5完成标志
    qstr = (tmp_uchar&0x10)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点4完成标志
    qstr = (tmp_uchar&0x08)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点3完成标志
    qstr = (tmp_uchar&0x04)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点2完成标志
    qstr = (tmp_uchar&0x02)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点1完成标志
    qstr = (tmp_uchar&0x01)?"完成":"未完成";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-灰度图宽度
    tmp_ushort=qToBigEndian(str_SAR.B_V72gyssWide);
    if((tmp_ushort >= 128)&&(tmp_ushort <= 2048))qstr="正常";
    else qstr="错误"+QString::number(tmp_ushort);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-灰度图高度
    tmp_ushort=qToBigEndian(str_SAR.B_V72gysshigh);
    if((tmp_ushort >= 4096)&&(tmp_ushort <= 16384))qstr="正常";
    else qstr="错误"+QString::number(tmp_ushort);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7-4 保留
    //bit3 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-接收数据开始标志
    tmp_uchar=str_SAR.B_V7cllc;
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-接收数据结束标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-发送数据开始标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-发送数据结束标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-接收数据时钟数计数
    qstr = QString::number(qToBigEndian(str_SAR.B_V72Re_cnt));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-发送数据时钟数计数
    qstr = QString::number(qToBigEndian(str_SAR.B_V72Se_cnt));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-CFAR处理步骤
    qstr = QString::number(str_SAR.B_V72_CFAR);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-检测目标数
    qstr = QString::number(qToBigEndian(str_SAR.B_V72_jcmb));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-网络运行层数
    tmp_uchar=str_SAR.B_V71_net;
    if(tmp_uchar <= 15)qstr="正确:"+QString::number(tmp_uchar);
    else qstr="错误"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-目标处理开始标志
    tmp_uchar=str_SAR.B_V71_clbz1;
    qstr = (tmp_uchar&0x80)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-切片写入开始标志
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-图像插值开始标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-参数写入开始标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-参数读取开始标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-发送数据开始标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-接收数据开始标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-网络运行开始标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-网络参数载入开始标志
    tmp_uchar=str_SAR.B_V71_clbz2;
    qstr = (tmp_uchar&0x80)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-参数包导入开始标志
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-网络计算最大值开始标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-网络归一化开始标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-全连接层开始标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-经纬度计算开始标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-经纬度计算参数有效标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-参数包导入开始标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 保留
    //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-读取权重结束标志
    tmp_uchar=str_SAR.B_V71_clbz3;
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-读取权重开始标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-网络运行结束响应标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-AXI总线复位标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-网络计算流程复位标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-检测流程复位标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-处理全局复位标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-网络参数载入结束标志
    tmp_uchar=str_SAR.B_V71_clbz4;
    qstr = (tmp_uchar&0x80)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-海陆分割数据发送结束标志
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-图像插值结束标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-参数写入结束标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-参数读取结束标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-发送数据结束标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-接收数据结束标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-网络运行结束标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络参数载入结束标志
    tmp_uchar=str_SAR.B_V71_clbz5;
    qstr = (tmp_uchar&0x80)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-参数包导入结束标志
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络计算最大值结束标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络归一化结束标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-全连接层结束标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-经纬度计算结束标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络数据写入结束标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-参数包导入结束标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理相关参数1-检测目标个数
    qstr = QString::number(qToBigEndian(str_SAR.B_V71xgcs1));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理相关参数2-当前处理检测目标位置
    qstr = QString::number(qToBigEndian(str_SAR.B_V71xgcs2));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理状态参数3-舰船处理数据量
    qstr = QString::number(str_SAR.B_V71xgcs3);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));


    //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-网络运行层数
    tmp_uchar=str_SAR.B2_V71_net;
    if(tmp_uchar <= 15)qstr="正确:"+QString::number(tmp_uchar);
    else qstr="错误"+QString::number(tmp_uchar);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-目标处理开始标志
    tmp_uchar=str_SAR.B2_V7_1clbz1;
    qstr = (tmp_uchar&0x80)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-目标判据标志2
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-目标判据标志1
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-参数写入开始标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-参数读取开始标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-发送数据开始标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-接收数据开始标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-网络运行开始标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7-6 保留
    //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-网络参数载入开始标志
    tmp_uchar=str_SAR.B2_V7_1clbz2;
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-参数包导入开始标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-网络计算最大值开始标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-网络归一化开始标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-全连接层开始标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-参数包导入开始标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 保留
    //bit6 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-读取权重结束标志
    tmp_uchar=str_SAR.B2_V7_1clbz3;
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-读取权重开始标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-网络运行结束响应标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-AXI总线复位标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-网络计算流程复位标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-检测流程复位标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-处理全局复位标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7-6保留
    //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-网络参数载入结束标志
    tmp_uchar=str_SAR.B2_V7_1clbz4;
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-参数写入结束标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-参数读取结束标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-发送数据结束标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-接收数据结束标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-网络运行结束标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //bit7 保留
    //bit6 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络参数载入结束标志
    tmp_uchar=str_SAR.B2_V7_1clbz5;
    qstr = (tmp_uchar&0x40)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-参数包导入结束标志
    qstr = (tmp_uchar&0x20)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络计算最大值结束标志
    qstr = (tmp_uchar&0x10)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络归一化结束标志
    qstr = (tmp_uchar&0x08)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-全连接层结束标志
    qstr = (tmp_uchar&0x04)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络数据写入结束标志
    qstr = (tmp_uchar&0x02)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-参数包导入结束标志
    qstr = (tmp_uchar&0x01)?"有效":"无效";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理相关参数1-检测目标个数
    qstr = QString::number(qToBigEndian(str_SAR.B2_V71xgcs1));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理相关参数2-当前处理检测目标位置
    qstr = QString::number(qToBigEndian(str_SAR.B2_V71xgcs2));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理状态参数3-舰船处理状态
    qstr = QString::number(str_SAR.B2_V71xgcs3);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

}


//第四组遥测解析-备用导航任务包(2s)
void subyc_slowspeed::show_yc0738(uchar *g4buff)
{
    slow_Group_4_BY str_BY;
    memset(&str_BY,0,sizeof (str_BY));
    memcpy(&str_BY,g4buff,sizeof (str_BY));

    //显示第四组公共头
    shoe_pub_g4head((uchar *)&str_BY.g4_Head);

    int rowcnt = 0;//列表行
    QString qstr;
    uchar tmp_uchar=0;

    //bit7,DSP  UTC时间状态
    tmp_uchar=str_BY.sorft_status;
    qstr = (tmp_uchar&0x80)?"UTC时间连续":"UTC时间不连续";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit6,FPGA PPS状态
    qstr = (tmp_uchar&0x40)?"正常":"异常";
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5-4,FPGA DDS信号生成状态
    switch ((tmp_uchar&0x30)>>4) {
    case 0:
        qstr="未生成:[0]";
        break;
    case 1:
        qstr="生成中:[1]";
        break;
    case 2:
        qstr="暂停生成:[2]";
        break;
    default:
        qstr="未知:"+QString::number((tmp_uchar&0x30)>>4);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3-2,轨道数据接收状态
    switch ((tmp_uchar&0x0C)>>2) {
    case 0:
        qstr="未接收到:[0]";
        break;
    case 1:
        qstr="成功接收但校验错误:[1]";
        break;
    case 2:
        qstr="成功接收且校验无误:[2]";
        break;
    default:
        qstr="未知:"+QString::number((tmp_uchar&0xC0)>>2);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1-0,轨道数据连续性
    switch (tmp_uchar&0x03) {
    case 0:
        qstr="连续:[0]";
        break;
    case 1:
        qstr="时间不连续:[1]";
        break;
    case 2:
        qstr="轨道不连续:[2]";
        break;
    default:
        qstr="未知:"+QString::number(tmp_uchar&0x03);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));



    //bit7-6综合管控单元-保留
    tmp_uchar=str_BY.sorft_status2;
    qstr = QString::number((tmp_uchar&0xc0)>>6);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit5-4伪码参数状态
    switch ((tmp_uchar&0x30)>>4) {
    case 0:
        qstr="未设置:[0]";
        break;
    case 1:
        qstr="使用初始化参数:[1]";
        break;
    case 2:
        qstr="使用上注参数:[2]";
        break;
    default:
        qstr="未知:"+QString::number((tmp_uchar&0x30)>>4);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit3-2星历拟合状态
    switch ((tmp_uchar&0x0C)>>2) {
    case 0:
        qstr="拟合正常:[0]";
        break;
    case 1:
        qstr="拟合不收敛:[1]";
        break;
    case 2:
        qstr="星历超限:[2]";
        break;
    default:
        qstr="未知:"+QString::number((tmp_uchar&0x0C)>>2);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1-0,历书拟合状态
    switch (tmp_uchar&0x03) {
    case 0:
        qstr="拟合正常:[0]";
        break;
    case 1:
        qstr="拟合不收敛:[1]";
        break;
    case 2:
        qstr="历书超限:[2]";
        break;
    default:
        qstr="未知:"+QString::number(tmp_uchar&0x03);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

    //DSP  三模冗余错误计数
    qstr = QString::number(str_BY.dsp_errcnt);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //轨道数据接收成功计数
    qstr = QString::number(str_BY.gd_reccnt);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //星历拟合误差
    qstr = QString::number(qToBigEndian(str_BY.xl_err));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //数字功率衰减值
    qstr = QString::number(str_BY.data_down);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //备用导航信号导航时间
    qstr = QString::number(qToBigEndian(str_BY.by_time));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));

}


//第四组遥测解析-类5G通信任务包(2s)
void subyc_slowspeed::show_yc0739(uchar *g4buff)
{
    slow_Group_4_kind5G str_kind5G;
    memset(&str_kind5G,0,sizeof (str_kind5G));
    memcpy(&str_kind5G,g4buff,sizeof (str_kind5G));

    //显示第四组公共头
    shoe_pub_g4head((uchar *)&str_kind5G.g4_Head);

    int rowcnt = 0;//列表行
    QString qstr;
    uchar tmp_uchar=0;
    //综合管控单元-5G关口站位置-经度
    qstr=QString::number(qToBigEndian(str_kind5G.position_orb));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //综合管控单元-5G关口站位置-纬度
    qstr=QString::number(qToBigEndian(str_kind5G.latitude_latitude));
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //bit1-0,5G工作模式
    tmp_uchar=str_kind5G.workMode_5G;
    switch (tmp_uchar&0x03) {
    case 0:
        qstr="高速数传:[0]";
        break;
    case 1:
        qstr="数据上注:[1]";
        break;
    case 2:
        qstr="终端间通信:[2]";
        break;
    default:
        qstr="未知"+QString::number(tmp_uchar&0x03);
        break;
    }
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //注册用户数
    qstr=QString::number(str_kind5G.register_user);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //误块率
    qstr=QString::number(str_kind5G.err_rate);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //编码调制样式
    map<int ,QString> type;
    type[2]="BPSK";
    type[4]="QPSK";
    type[6]="16QAM";
    type[8]="64QAM";
    qstr=type[str_kind5G.code_maind];
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));
    //编码码率
    qstr=QString::number(str_kind5G.code_rate);
    model->setItem(rowcnt++, 3, new QStandardItem(qstr));


}

void subyc_slowspeed::show_yc073A(uchar *g4buff)
{
    slow_Group_4_Head str_g4head;
    memset(&str_g4head,0,sizeof (str_g4head));
    memcpy(&str_g4head,g4buff,sizeof (str_g4head));

    //显示第四组公共头
    shoe_pub_g4head((uchar *)&str_g4head);
}




// 清空慢速遥测内容
void subyc_slowspeed::on_pB_Clearmsyclist_clicked() {

    int cnt=model->rowCount();
    int col=model->columnCount();
    for (int n=0;n<cnt;n++) {

        for (int c=1;c<col;c+=2) {
            model->setItem(n, c, new QStandardItem(""));
        }
    }

}


//第1组遥测
void subyc_slowspeed::on_radioButton_group1_clicked()
{
    Init_ViewList();
}

//第2组遥测
void subyc_slowspeed::on_radioButton_group2_clicked()
{
    Init_ViewList();
}

//第3组遥测
void subyc_slowspeed::on_radioButton_group3_clicked()
{
    Init_ViewList();
}
//第4组遥测
void subyc_slowspeed::on_radioButton_group4_clicked()
{
    Init_ViewList();
}
