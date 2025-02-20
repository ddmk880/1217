#include "subyc_canc81.h"
#include "ui_subyc_canc81.h"

#include "Globel_Define.h"

subyc_canC81::subyc_canC81(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subyc_canC81)
{
    ui->setupUi(this);
    //qDebug()<<sizeof (YCLX_C81)<<"eeeee";
    // 修改界面表格
    model = new QStandardItemModel(ui->tableView_CanC81list);
    QStringList m_name_list;//表头
    m_name_list.append("控制接口模块");
    m_name_list.append("数值");
    m_name_list.append("收发处理模块");
    m_name_list.append("数值");
    m_name_list.append("数据处理模块1");
    m_name_list.append("数值");
    m_name_list.append("数据处理模块2");
    m_name_list.append("数值");
    m_name_list.append("软件信息");
    m_name_list.append("数值");
    int num = m_name_list.size();
    model->setColumnCount(num);
    model->setRowCount(0);
    for (int i = 0; i < num; i++) {
        model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
    }

    QStringList msyc_strName_1;//接口控制模块表头
    if(1)
    {
        //FPGAV2芯片

        msyc_strName_1.append("FPGAV2_接口控制 DSP6701加载状态");
        msyc_strName_1.append("FPGAV2_接口控制 DSP6678加载状态");
        msyc_strName_1.append("FPGAV2_接口控制 V7加载状态");
        msyc_strName_1.append("FPGAV2_收发处理 K7加载状态");
        msyc_strName_1.append("FPGAV2_数据处理1 K7加载状态");
        msyc_strName_1.append("FPGAV2_数据处理2 K7加载状态");

        msyc_strName_1.append("FPGAV2_版本号");
        msyc_strName_1.append("FPGAV7_版本号");
        msyc_strName_1.append("FPGAV7_软件代号");
        msyc_strName_1.append("DSP6701_版本号");
        msyc_strName_1.append("DSP6678_版本号");

        msyc_strName_1.append("FPGAV7_接收计数");
        msyc_strName_1.append("FPGAV7_发送计数");

        msyc_strName_1.append("FPGAV2_光模块供电指示(FIBER_3V3_PG)");
        msyc_strName_1.append("FPGAV2_DSP供电指示(PG_DSPVTT)");
        msyc_strName_1.append("FPGAV2_DSP供电指示(PG_DSP1V8)");
        msyc_strName_1.append("FPGAV2_DSP供电指示(PG_DSP1V5)");
        msyc_strName_1.append("FPGAV2_DSP供电指示(PG_DSP1V0_SMART)");
        msyc_strName_1.append("FPGAV2_DSP供电指示(PG_DSP1V0)");
        msyc_strName_1.append("FPGAV2_模块栓锁（5004KILL）");
        msyc_strName_1.append("FPGAV2_收发处理模块栓锁(LRM_PG1)");
        msyc_strName_1.append("FPGAV2_数据处理1模块栓锁(LRM_PG2）");
        msyc_strName_1.append("FPGAV2_数据处理2模块栓锁(LRM_PG3）");
        msyc_strName_1.append("FPGAV2_锁相环（V2_LD1）");
        msyc_strName_1.append("FPGAV2_锁相环（V2_LD2）");
        msyc_strName_1.append("FPGAV2_锁相环（V2_LD3）");


        //FPGAV7
        msyc_strName_1.append("FPGAV7_DSP6678心跳");
        msyc_strName_1.append("FPGAV7_V7温度");
        msyc_strName_1.append("FPGAV7_主份udp时钟锁定指示");
        msyc_strName_1.append("FPGAV7_备份udp时钟锁定指示");
        msyc_strName_1.append("FPGAV7_收发处理  K7时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理1 K7时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理2 K7时钟锁定指示");
        msyc_strName_1.append("FPGAV7_主份udp建链指示");
        msyc_strName_1.append("FPGAV7_备份udp建链指示");
        msyc_strName_1.append("FPGAV7_收发处理  K7建链指示");
        msyc_strName_1.append("FPGAV7_数据处理1 K7建链指示");
        msyc_strName_1.append("FPGAV7_数据处理2 K7建链指示");
        msyc_strName_1.append("FPGAV7_管控模块 V7备份时钟锁定指示");
        msyc_strName_1.append("FPGAV7_接口控制 DSP6678时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理1 V7_1时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理1 V7_2时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理1 DSP6678时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理2 V7_1时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理2 V7_2时钟锁定指示");
        msyc_strName_1.append("FPGAV7_数据处理2 DSP6678时钟锁定指示");
        msyc_strName_1.append("FPGAV7_管控模块 V7主份时钟锁定指示");
        msyc_strName_1.append("FPGAV7_管控模块 V7备份建链指示");
        msyc_strName_1.append("FPGAV7_接口控制 DSP6678建链指示");
        msyc_strName_1.append("FPGAV7_数据处理1 V7_1建链指示");
        msyc_strName_1.append("FPGAV7_数据处理1 V7_2建链指示");
        msyc_strName_1.append("FPGAV7_数据处理1 DSP6678建链指示");
        msyc_strName_1.append("FPGAV7_数据处理2 V7_1建链指示");
        msyc_strName_1.append("FPGAV7_数据处理2 V7_2建链指示");
        msyc_strName_1.append("FPGAV7_数据处理2 DSP6678建链指示");

        msyc_strName_1.append("FPGAV7_管控模块 管控机主备");
        msyc_strName_1.append("FPGAV7_管控模块 交换机主备");
        msyc_strName_1.append("FPGAV7_管控模块 V7主份建链指示");


        msyc_strName_1.append("DSP6678_与接口控制 V7建链指示");
        msyc_strName_1.append("DSP6678_与数据处理1 DSP6678建链指示");
        msyc_strName_1.append("DSP6678_与数据处理2 DSP6678建链指示");
    }

    QStringList msyc_strName_2;//收发处理模块表头
    if(1)
    {
        //FPGAK7表头
        msyc_strName_2.append("FPGAK7_FPGAV7_1加载状态");
        msyc_strName_2.append("FPGAK7_FPGAV7_2加载状态");

        msyc_strName_2.append("FPGAK7_版本号");
        msyc_strName_2.append("FPGAV7_1_版本号");
        msyc_strName_2.append("FPGAV7_1_软件代号");
        msyc_strName_2.append("FPGAV7_2_版本号");
        msyc_strName_2.append("FPGAV7_2_软件代号");


        msyc_strName_2.append("FPGAK7_ 软件预加载数量");
        msyc_strName_2.append("FPGAK7_收发处理 V7_1时钟指示");
        msyc_strName_2.append("FPGAK7_收发处理 V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAK7_接口控制 V7时钟锁定指示");

        msyc_strName_2.append("FPGAK7_ 软件预加载数量");
        msyc_strName_2.append("FPGAK7_收发处理 V7_1建链指示");
        msyc_strName_2.append("FPGAK7_收发处理 V7_2建链指示");
        msyc_strName_2.append("FPGAK7_接口控制 V7建链指示");
        //msyc_strName_2.append("FPGAK7_DSP、光模块电源");
        msyc_strName_2.append("FPGAK7_FPGA1的1DDRVTT电源PG指示");
        msyc_strName_2.append("FPGAK7_FPGA1的2DDRVTT电源PG指示");
        msyc_strName_2.append("FPGAK7_FPGA2的1DDRVTT电源PG指示");
        msyc_strName_2.append("FPGAK7_FPGA2的2DDRVTT电源PG指示");

        msyc_strName_2.append("FPGAK7_AD1电源1V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD1电源1_1V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD1电源1_2V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD1电源1.3VA电源PG指示");
        msyc_strName_2.append("FPGAK7_AD1电源2V电源PG指示");

        msyc_strName_2.append("FPGAK7_AD2电源1V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD2电源1_1V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD2电源1V_2电源PG指示");
        msyc_strName_2.append("FPGAK7_AD2电源1.3VB电源PG指示");
        msyc_strName_2.append("FPGAK7_AD2电源2V电源PG指示");

        msyc_strName_2.append("FPGAK7_AD3电源1V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD3电源1_1V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD3电源1V_2电源PG指示");
        msyc_strName_2.append("FPGAK7_AD3电源2V电源PG指示");

        msyc_strName_2.append("FPGAK7_1.5V电源PG指示");
        msyc_strName_2.append("FPGAK7_2_1.5V电源PG指示");
        msyc_strName_2.append("FPGAK7_AD1电源1.8V电源PG指示");
        msyc_strName_2.append("FPGAK7_2.8V电源PG指示");
        msyc_strName_2.append("FPGAK7_模拟3.3V电源PG指示");
        msyc_strName_2.append("FPGAK7_模拟3.3_2电源PG指示");
        msyc_strName_2.append("FPGAK7_ADC1温度");
        msyc_strName_2.append("FPGAK7_ADC2温度");
        msyc_strName_2.append("FPGAK7_ADC3温度");

        //FPGAV7_1

        msyc_strName_2.append("FPGAV7_1_V7温度");
        msyc_strName_2.append("FPGAV7_1_收发K7时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_收发V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_数据处理1 V7_1时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_数据处理1 V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_数据处理2 V7_1时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_数据处理2 V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_收发K7建链指示");
        msyc_strName_2.append("FPGAV7_1_收发V7_2建链指示 ");
        msyc_strName_2.append("FPGAV7_1_数据处理1 V7_1建链指示");
        msyc_strName_2.append("FPGAV7_1_数据处理1 V7_2建链指示");
        msyc_strName_2.append("FPGAV7_1_数据处理2 V7_1建链指示");
        msyc_strName_2.append("FPGAV7_1_数据处理2 V7_2建链指示");
        msyc_strName_2.append("FPGAV7_1_SRIO时钟锁定");
        msyc_strName_2.append("FPGAV7_1_SRIO建链");
        msyc_strName_2.append("FPGAV7_1_ADC1时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_ADC2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_ADC3时钟锁定指示");
        msyc_strName_2.append("FPGAV7_1_ADC1建链指示");
        msyc_strName_2.append("FPGAV7_1_ADC2建链指示");
        msyc_strName_2.append("FPGAV7_1_ADC3建链指示");

        //FPGAV7_2
        msyc_strName_2.append("FPGAV7_2_V7温度");
        msyc_strName_2.append("FPGAV7_2_收发K7时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_收发V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_数据处理1 V7_1时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_数据处理1 V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_数据处理2 V7_1时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_数据处理2 V7_2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_收发K7建链指示");
        msyc_strName_2.append("FPGAV7_2_收发V7_2建链指示 ");
        msyc_strName_2.append("FPGAV7_2_数据处理1 V7_1建链指示");
        msyc_strName_2.append("FPGAV7_2_数据处理1 V7_2建链指示");
        msyc_strName_2.append("FPGAV7_2_数据处理2 V7_1建链指示");
        msyc_strName_2.append("FPGAV7_2_数据处理2 V7_2建链指示");
        msyc_strName_2.append("FPGAV7_2_SRIO时钟锁定");
        msyc_strName_2.append("FPGAV7_2_SRIO建链");
        msyc_strName_2.append("FPGAV7_2_ADC1时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_ADC2时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_ADC3时钟锁定指示");
        msyc_strName_2.append("FPGAV7_2_ADC1建链指示");
        msyc_strName_2.append("FPGAV7_2_ADC2建链指示");
        msyc_strName_2.append("FPGAV7_2_ADC3建链指示");
    }
    QStringList msyc_strName_3;//数据处理模块1表头
    if(1)
    {
        //FPGAK7
        msyc_strName_3.append("FPGAK7_DSP6678心跳");
        msyc_strName_3.append("FPGAK7_DSP6678加载状态");
        msyc_strName_3.append("FPGAK7_FPGAV7_1加载状态");
        msyc_strName_3.append("FPGAK7_FPGAV7_2加载状态");

        msyc_strName_3.append("FPGAK7_版本号");
        msyc_strName_3.append("FPGAV7_1_版本号");
        msyc_strName_3.append("FPGAV7_1_软件代号");
        msyc_strName_3.append("FPGAV7_2_版本号");
        msyc_strName_3.append("FPGAV7_2_软件代号");
        msyc_strName_3.append("DSP6678_版本号");
        msyc_strName_3.append("DSP6678_软件代号");

        msyc_strName_3.append("FPGAk7_GTX时钟锁定软件预加载数量");
        msyc_strName_3.append("FPGAK7_数据处理1 V7_1时钟锁定");
        msyc_strName_3.append("FPGAK7_数据处理1 V7_2时钟锁定");
        msyc_strName_3.append("FPGAK7_接口控制 V7时钟锁定");
        msyc_strName_3.append("FPGAK7_GTX建链软件预加载数量");
        msyc_strName_3.append("FPGAK7_数据处理1 V7_1建链");
        msyc_strName_3.append("FPGAK7_数据处理1 V7_2建链");
        msyc_strName_3.append("FPGAK7_接口控制 V7建链 ");
        msyc_strName_3.append("FPGAK7_光模块(PG_FIB3V3)");
        msyc_strName_3.append("FPGAK7_DSP电源(PG_DSPVTT)");
        msyc_strName_3.append("FPGAK7_DSP电源(PG_DSP1V8)");
        msyc_strName_3.append("FPGAK7_DSP电源(PG_DSP1V5)");
        msyc_strName_3.append("FPGAK7_DSP电源(PG_DSP1V0_SMART)");
        msyc_strName_3.append("FPGAK7_DSP电源(PG_DSP1V0)");
        //FPGAV7_1

        msyc_strName_3.append("FPGAV7_1_V7温度");
        msyc_strName_3.append("FPGAV7_1_收发处理 V7_1时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_收发处理 V7_2时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_数据处理1 V7_2时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_数据处理2 V7_1时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_数据处理1 K7时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_算力2处理1 V7_1时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_收发处理 V7_1建链指示");
        msyc_strName_3.append("FPGAV7_1_收发处理 V7_2建链指示");
        msyc_strName_3.append("FPGAV7_1_数据处理1 V7_2建链指示");
        msyc_strName_3.append("FPGAV7_1_数据处理2 V7_1建链指示");
        msyc_strName_3.append("FPGAV7_1_数据处理1 K7建链指示");
        msyc_strName_3.append("FPGAV7_1_高算力2数据处理1 V7_1建链指示");
        msyc_strName_3.append("FPGAV7_1_接口控制 V7时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_数据处理1 DSP6678时钟锁定指示");
        msyc_strName_3.append("FPGAV7_1_接口控制 V7建链指示");
        msyc_strName_3.append("FPGAV7_1_数据处理1 DSP6678建链指示");
        //FPGAV7_2

        msyc_strName_3.append("FPGAV7_2_V7温度");
        msyc_strName_3.append("FPGAV7_2_收发处理 V7_1时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_收发处理 V7_2时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_数据处理1 V7_2时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_数据处理2 V7_1时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_数据处理1 K7时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_算力2处理1 V7_1时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_收发处理 V7_1建链指示");
        msyc_strName_3.append("FPGAV7_2_收发处理 V7_2建链指示");
        msyc_strName_3.append("FPGAV7_2_数据处理1 V7_2建链指示");
        msyc_strName_3.append("FPGAV7_2_数据处理2 V7_1建链指示");
        msyc_strName_3.append("FPGAV7_2_数据处理1 K7建链指示");
        msyc_strName_3.append("FPGAV7_2_高算力2数据处理1 V7_1建链指示");
        msyc_strName_3.append("FPGAV7_2_接口控制 V7时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_数据处理1 DSP6678时钟锁定指示");
        msyc_strName_3.append("FPGAV7_2_接口控制 V7建链指示");
        msyc_strName_3.append("FPGAV7_2_数据处理1 DSP6678建链指示");


    }

    QStringList msyc_strName_4;//数据处理模块2表头
    if(1)
    {
        //FPGAK7
        msyc_strName_4.append("FPGAK7_DSP6678心跳");
        msyc_strName_4.append("FPGAK7_DSP6678加载状态");
        msyc_strName_4.append("FPGAK7_FPGAV7_1加载状态");
        msyc_strName_4.append("FPGAK7_FPGAV7_2加载状态");

        msyc_strName_4.append("FPGAK7_版本号");
        msyc_strName_4.append("FPGAV7_1_版本号");
        msyc_strName_4.append("FPGAV7_1_软件代号");
        msyc_strName_4.append("FPGAV7_2_版本号");
        msyc_strName_4.append("FPGAV7_2_软件代号");
        msyc_strName_4.append("DSP6678_版本号");
        msyc_strName_4.append("DSP6678_软件代号");


        msyc_strName_4.append("FPGAK7_GTX时钟锁定软件预加载数量");
        msyc_strName_4.append("FPGAK7_数据处理1 V7_1时钟锁定");
        msyc_strName_4.append("FPGAK7_数据处理1 V7_2时钟锁定");
        msyc_strName_4.append("FPGAK7_接口控制 V7时钟锁定");
        msyc_strName_4.append("FPGAK7_GTX建链软件预加载数量");
        msyc_strName_4.append("FPGAK7_数据处理1 V7_1建链");
        msyc_strName_4.append("FPGAK7_数据处理1 V7_2建链");
        msyc_strName_4.append("FPGAK7_接口控制 V7建链 ");
        msyc_strName_4.append("FPGAK7_光模块(PG_FIB3V3)");
        msyc_strName_4.append("FPGAK7_DSP电源(PG_DSPVTT)");
        msyc_strName_4.append("FPGAK7_DSP电源(PG_DSP1V8)");
        msyc_strName_4.append("FPGAK7_DSP电源(PG_DSP1V5)");
        msyc_strName_4.append("FPGAK7_DSP电源(PG_DSP1V0_SMART)");
        msyc_strName_4.append("FPGAK7_DSP电源(PG_DSP1V0)");
        //FPGAV7_1
        msyc_strName_4.append("FPGAV7_1_V7温度");
        msyc_strName_4.append("FPGAV7_1_收发处理 V7_1时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_收发处理 V7_2时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_数据处理1 V7_2时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_数据处理2 V7_1时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_数据处理1 K7时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_算力2处理1 V7_1时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_收发处理 V7_1建链指示");
        msyc_strName_4.append("FPGAV7_1_收发处理 V7_2建链指示");
        msyc_strName_4.append("FPGAV7_1_数据处理1 V7_2建链指示");
        msyc_strName_4.append("FPGAV7_1_数据处理2 V7_1建链指示");
        msyc_strName_4.append("FPGAV7_1_数据处理1 K7建链指示");
        msyc_strName_4.append("FPGAV7_1_高算力2数据处理1 V7_1建链指示");
        msyc_strName_4.append("FPGAV7_1_接口控制 V7时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_数据处理1 DSP6678时钟锁定指示");
        msyc_strName_4.append("FPGAV7_1_接口控制 V7建链指示");
        msyc_strName_4.append("FPGAV7_1_数据处理1 DSP6678建链指示");
        //FPGAV7_2
        msyc_strName_4.append("FPGAV7_2_V7温度");
        msyc_strName_4.append("FPGAV7_2_收发处理 V7_1时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_收发处理 V7_2时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_数据处理1 V7_2时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_数据处理2 V7_1时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_数据处理1 K7时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_算力2处理1 V7_1时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_收发处理 V7_1建链指示");
        msyc_strName_4.append("FPGAV7_2_收发处理 V7_2建链指示");
        msyc_strName_4.append("FPGAV7_2_数据处理1 V7_2建链指示");
        msyc_strName_4.append("FPGAV7_2_数据处理2 V7_1建链指示");
        msyc_strName_4.append("FPGAV7_2_数据处理1 K7建链指示");
        msyc_strName_4.append("FPGAV7_2_高算力2数据处理1 V7_1建链指示");
        msyc_strName_4.append("FPGAV7_2_接口控制 V7时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_数据处理1 DSP6678时钟锁定指示");
        msyc_strName_4.append("FPGAV7_2_接口控制 V7建链指示");
        msyc_strName_4.append("FPGAV7_2_数据处理1 DSP6678建链指示");


    }

    QStringList msyc_strName_5;//软件信息
    if(1)
    {
        msyc_strName_5.append("接口DSP6701 ");
        msyc_strName_5.append("接口DSP6678 ");
        msyc_strName_5.append("收发V7_1    ");
        msyc_strName_5.append("收发V7_2    ");
        msyc_strName_5.append("数据1V7_1   ");
        msyc_strName_5.append("数据1V7_2   ");
        msyc_strName_5.append("数据1DSP6678");
        msyc_strName_5.append("数据2V7_1   ");
        msyc_strName_5.append("数据2V7_2   ");
        msyc_strName_5.append("数据2DSP6678");
    }


//    for (int i = 0; i < msyc_strName_1.size(); i++) {
//        model->setItem(i, 0, new QStandardItem(msyc_strName_1.at(i)));
//    }
    for (int i = 0; i < msyc_strName_1.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_1.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
        model->setItem(i, 0, table_item);
    }
    for (int i = 0; i < msyc_strName_2.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_2.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
        model->setItem(i, 2, table_item);
    }
    for (int i = 0; i < msyc_strName_3.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_3.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
        model->setItem(i, 4, table_item);
    }
    for (int i = 0; i < msyc_strName_4.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_4.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
        model->setItem(i, 6, table_item);
    }
    for (int i = 0; i < msyc_strName_5.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_5.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
        model->setItem(i, 8, table_item);
    }

    ui->tableView_CanC81list->setModel(model);  //(设置宽度要在后面)
    ui->tableView_CanC81list->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 是否可编辑
    //  ui->tableView_CanC81list->setColumnWidth(1,00);//设置第0列宽100
    ui->tableView_CanC81list->resizeColumnToContents(0);  // 设置第0列宽度自适应内容
    ui->tableView_CanC81list->resizeColumnToContents(2);  // 设置第2列宽度自适应内容
    ui->tableView_CanC81list->resizeColumnToContents(4);  // 设置第4列宽度自适应内容
    ui->tableView_CanC81list->resizeColumnToContents(6);  // 设置第4列宽度自适应内容
    ui->tableView_CanC81list->resizeColumnToContents(8);  // 设置第4列宽度自适应内容
    ui->tableView_CanC81list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_CanC81list->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView_CanC81list->horizontalHeader()->setMinimumSectionSize(100);
    //  ui->tableView_CanC81list->resizeColumnsToContents();//设置所有列宽度自适应
    //   ui->tableView_CanC81list->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);//设置第1列(表头)自动
    //   ui->tableView_CanC81list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置所有列自动
}

subyc_canC81::~subyc_canC81()
{
    delete ui;
}


void subyc_canC81::Get_C81YcData(uchar *Rxbuff, int Rxlen)
{
    // 开辟缓存存储4帧*32字 数据
    uchar *Tran_Buff = new uchar[Rxlen];
    QString ss;
    for (int i = 0; i < Rxlen; i++) {
        QString s1 =QString("%1 ").arg(Rxbuff[i], 2, 16, QLatin1Char('0')).toUpper();
        ss.append(s1);
    }
    //qDebug() <<"C81_YC::"+ ss;
    memcpy(Tran_Buff,Rxbuff,Rxlen);

    // 拷贝到遥测结构体
    YCLX_C81 strYC;
    memcpy(&strYC, Tran_Buff+3, sizeof(strYC));
    delete[] Tran_Buff;

    int colcnt = 0;
    QString qstr;
    ushort tmp_ushort = 0;
    short tmp_short = 0;

    /******************接口控制模块**********************/
    if(1)
    {
        //FPGAV2程序加载DONE指令---(排序前移)
        //D7-D6	保留
        //D5接口控制 DSP6701加载状态
        qstr=((strYC.appLoadDone&0x20)>>5)?"加载":"未加载";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D4接口控制 DSP6678加载状态
        qstr=((strYC.appLoadDone&0x10)>>4)?"加载":"未加载";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D3接口控制 V7加载状态
        qstr=((strYC.appLoadDone&0x8)>>3)?"加载":"未加载";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D2收发处理 K7加载状态
        qstr=((strYC.appLoadDone&0x4)>>2)?"加载":"未加载";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D1数据处理1 K7加载状态
        qstr=((strYC.appLoadDone&0x2)>>1)?"加载":"未加载";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D0数据处理2 K7加载状态
        qstr=((strYC.appLoadDone&0x1)>>0)?"加载":"未加载";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //FPGAV2软件版本号
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.softwareVersion&0xE0)>>5).arg(strYC.softwareVersion&0x1F);
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //FPGAV7版本号---(排序前移)
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.Version_FPGAV7&0xE0)>>5).arg(strYC.Version_FPGAV7&0x1F);
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //FPGAV7软件代号---(排序前移)
        tmp_ushort=qToBigEndian(strYC.softwareNumber);
        QString qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 1, new QStandardItem(qstr_sorft));

        //DSP6701版本号
        //D7-D5	大版本号//D4-D0	小版本号---(排序前移)
        qstr=QString("%1.%2").arg((strYC.Version_DSP6701&0xE0)>>5).arg(strYC.Version_DSP6701&0x1F);
        model->setItem(colcnt++, 1, new QStandardItem(qstr));


        //DSP6678版本号
        //D7-D5	大版本号//D4-D0	小版本号---(排序前移)
        qstr=QString("%1.%2").arg((strYC.Version_DSP6678&0xE0)>>5).arg(strYC.Version_DSP6678&0x1F);
        model->setItem(colcnt++, 1, new QStandardItem(qstr));




        //接收计数	4---(排序前移)
        model->setItem(colcnt++, 1, new QStandardItem(QString ::number(qToBigEndian(strYC.re_cnt))));
        //发送计算	4---(排序前移)
        model->setItem(colcnt++, 1, new QStandardItem(QString ::number(qToBigEndian(strYC.send_cnt))));


        //FPGAV2模块供电指示
        //bit7-bit6保留
        //bit5-可重构高算力平台2-接口控制模块-光模块供电指示(FIBER_3V3_PG)
        qstr=(strYC.MKlightpower&0x20)>>5?"供电":"未供电";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit4-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSPVTT)
        qstr=(strYC.MKlightpower&0x10)>>4?"供电":"未供电";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit3-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V8)
        qstr=(strYC.MKlightpower&0x8)>>3?"供电":"未供电";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit2-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V5)
        qstr=(strYC.MKlightpower&0x4)>>2?"供电":"未供电";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit1-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V0_
        qstr=(strYC.MKlightpower&0x2)>>1?"供电":"未供电";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit0-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V0)
        qstr=(strYC.MKlightpower&0x1)?"供电":"未供电";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //FPGAV2栓锁、锁相环锁指示
        // bit7-保留
        // bit6-可重构高算力平台2-接口控制模块-模块栓锁
        qstr=((strYC.JKlock&0x40)>>6)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit5-可重构高算力平台2-接口控制模块-收发处理模块栓锁(收发LRM_P5)));
        qstr=((strYC.JKlock&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit4-可重构高算力平台2-接口控制模块-数据处理1模块栓锁(数据1LRM
        qstr=((strYC.JKlock&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit3-可重构高算力平台2-接口控制模块-数据处理2模块栓锁(数据2LRM
        qstr=((strYC.JKlock&0x8)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit2-可重构高算力平台2-接口控制模块-锁相环(V2_LD1)
        qstr=((strYC.JKlock&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit1-可重构高算力平台2-接口控制模块-锁相环(V2_LD2)
        qstr=((strYC.JKlock&0x2)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //bit0-可重构高算力平台2-接口控制模块-锁相环(V2_LD3)
        qstr=((strYC.JKlock&0x1)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));


        //FPGAV7温度
        tmp_ushort=qToBigEndian(strYC.Temperature);
        //D15	DSP6678心跳
        model->setItem(colcnt++, 1, new QStandardItem(QString ::number(tmp_ushort>>15)));
        //D14-D12	保留
        //D11-D0	V7温度
        model->setItem(colcnt++, 1, new QStandardItem(QString ::number((tmp_ushort&0xFFF)*503.975/4096.0-273.15)+"℃"));

        //FPGAV7GTX/UDP时钟锁定
        //D7	主份udp时钟锁定指示
        qstr=((strYC.GTX_UDP_ClockLock&0x80)>>7)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D6	备份udp时钟锁定指示
        qstr=((strYC.GTX_UDP_ClockLock&0x40)>>6)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(QString ::number((strYC.GTX_UDP_ClockLock&0x40)>>6)));
        //D5-D3	保留
        //D2	收发处理  K7时钟锁定指示
        qstr=((strYC.GTX_UDP_ClockLock&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D1	数据处理1 K7时钟锁定指示
        qstr=((strYC.GTX_UDP_ClockLock&0x2)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D0	数据处理2 K7时钟锁定指示
        qstr=((strYC.GTX_UDP_ClockLock&0x1)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //FPGAV7GTX/UDP建链指示
        //D7	主份udp建链指示
        qstr=(strYC.JLZS_GTX_UDP&0x80)>>7?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D6	备份udp建链指示
        qstr=(strYC.JLZS_GTX_UDP&0x40)>>6?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D5-D3	保留
        //D2	收发处理  K7建链指示
        qstr=(strYC.JLZS_GTX_UDP&0x4)>>2?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D1	数据处理1 K7建链指示
        qstr=(strYC.JLZS_GTX_UDP&0x2)>>1?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D0	数据处理2 K7建链指示
        qstr=(strYC.JLZS_GTX_UDP&0x1)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //FPGAV7SRIO时钟锁定指示
        //D7	管控模块 V7备份时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x8000)>>15)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D6	接口控制 DSP6678时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x4000)>>14)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D5	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x2000)>>13)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D4	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x1000)>>12)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D3	数据处理1 DSP6678时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x800)>>11)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D2	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x400)>>10)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D1	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x200)>>9)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D0	数据处理2 DSP6678时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&0x100)>>8)?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D7-D1	保留
        //D0	管控模块 V7主份时钟锁定指示
        qstr=((strYC.SRIO_ClockLockFlag&1))?"锁定":"未锁定";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));


        //FPGAV7SRIO建链指示
        //D7	管控模块 V7备份建链指示
        qstr=((strYC.JLZS_SRIO&0x8000)>>15)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D6	接口控制 DSP6678建链指示
        qstr=((strYC.JLZS_SRIO&0x4000)>>14)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D5	数据处理1 V7-1建链指示
        qstr=((strYC.JLZS_SRIO&0x2000)>>13)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D4	数据处理1 V7-2建链指示
        qstr=((strYC.JLZS_SRIO&0x1000)>>12)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D3	数据处理1 DSP6678建链指示
        qstr=((strYC.JLZS_SRIO&0x0800)>>11)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D2	数据处理2 V7-1建链指示
        qstr=((strYC.JLZS_SRIO&0x0400)>>10)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D1	数据处理2 V7-2建链指示
        qstr=((strYC.JLZS_SRIO&0x0200)>>9)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D0	数据处理2 DSP6678建链指示
        qstr=((strYC.JLZS_SRIO&0x0100)>>8)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));

        //D7	管控机主备
        qstr=((strYC.JLZS_SRIO&0x0080)>>7)?"备":"主";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D6	交换机主备
        qstr=((strYC.JLZS_SRIO&0x0040)>>6)?"备":"主";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D5-D1	保留
        //D0	管控模块 V7主份建链指示
        qstr=((strYC.JLZS_SRIO&0x0001))?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));


        //建链指示
        //D7-D3	保留
        //D2	与接口控制 V7建链指示
        qstr=(strYC.JLZS_DSP6678&0x04)>>2?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
        //D1	与数据处理1 DSP6678建链指示
        qstr=(strYC.JLZS_DSP6678&0x02)>>1?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem( qstr));
        //D0	与数据处理2 DSP6678建链指示
        qstr= (strYC.JLZS_DSP6678&0x01)?"建链":"未建链";
        model->setItem(colcnt++, 1, new QStandardItem(qstr));
    }

    /*********************收发处理模块********************/
    if(1)
    {
        colcnt=0;
        //FPGAK7版本号
        //软件加载状态
        //D7-D2	保留
        //D1	FPGAV7-1加载状态
        qstr=((strYC.softwareLoad_FPGAK7&0x02)>>1)?"加载":"未加载";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	FPGAV7-2加载状态
        qstr=(strYC.softwareLoad_FPGAK7&0x01)?"加载":"未加载";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.Version_FPGAK7&0xE0)>>5).arg(strYC.Version_FPGAK7&0x1F);
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //FPGAV7-1版本号
        //大版本号//小版本号---（位置前移）
        qstr=QString("%1.%2").arg((strYC.Fpgav7_1.version&0xE0)>>5).arg(strYC.Fpgav7_1.version&0x1F);
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //软件代号---（位置前移）
        tmp_ushort=qToBigEndian(strYC.Fpgav7_1.software);
        QString qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 3, new QStandardItem(qstr_sorft));

        //FPGAV7-2版本号---（位置前移）
        //大版本号//小版本号
        qstr=QString("%1.%2").arg((strYC.Fpgav7_2.version&0xE0)>>5).arg(strYC.Fpgav7_2.version&0x1F);
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //软件代号---（位置前移）
        tmp_ushort=qToBigEndian(strYC.Fpgav7_2.software);
        qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 3, new QStandardItem(qstr_sorft));



        //GTX时钟锁定
        //D7-D4	软件预加载数量高4位
        model->setItem(colcnt++, 3, new QStandardItem(QString ::number((strYC.GTX_ClockLock_FPGAK7&0xF0)>>4)));
        //D3	保留
        //D2	收发处理 V7-1时钟锁定指示
        qstr=((strYC.GTX_ClockLock_FPGAK7&0x04)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 3 , new QStandardItem(qstr));
        //D1	收发处理 V7-2时钟锁定指示
        qstr=((strYC.GTX_ClockLock_FPGAK7&0x02)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++,3, new QStandardItem(qstr));
        //D0	接口控制 V7时钟锁定指示
        qstr=((strYC.GTX_ClockLock_FPGAK7&0x01))?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //GTX建链
        //D7-D4	软件预加载数量低4位
        model->setItem(colcnt++, 3, new QStandardItem(QString ::number((strYC.GTX_JL_FPGAK7&0xF0)>>4)));
        //D3	保留
        //D2	收发处理 V7-1建链指示
        qstr= ((strYC.GTX_JL_FPGAK7&0x04)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	收发处理 V7-2建链指示
        qstr= ((strYC.GTX_JL_FPGAK7&0x02)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	接口控制 V7建链指示
        qstr= ((strYC.GTX_JL_FPGAK7&0x01) )?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

//        //DSP、光模块电源(保留)
//        model->setItem(colcnt++, 3, new QStandardItem("保留"));

        //DDR电源
        //D7-D4	保留
        //D3	FPGA1的1DDRVTT电源PG指示
        qstr= ((strYC.DDR_source_FPGAK7&0x08)>>3)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	FPGA1的2DDRVTT电源PG指示
        qstr= ((strYC.DDR_source_FPGAK7&0x04)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	FPGA2的1DDRVTT电源PG指示
        qstr= ((strYC.DDR_source_FPGAK7&0x02)>>1)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	FPGA2的2DDRVTT电源PG指示
        qstr= ((strYC.DDR_source_FPGAK7&0x01)>>0)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));


        //电源指示1
        //D7-D6	保留
        //D4	AD1电源1V电源PG指示(DVDD1PG)
        qstr= ((strYC.sourceFlag1_FPAGK7&0x10)>>4)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	AD1电源1_1V电源PG指示(AVDD1_1PG)
        qstr= ((strYC.sourceFlag1_FPAGK7&0x08)>>3)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	AD1电源1_2V电源PG指示(AVDD1_2PG)
        qstr= ((strYC.sourceFlag1_FPAGK7&0x4)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	AD1电源1.3VA电源PG指示(VCC1.3APG)
        qstr= ((strYC.sourceFlag1_FPAGK7&0x2)>>1)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	AD1电源2V电源PG指示(AVDD2PG)
        qstr= ((strYC.sourceFlag1_FPAGK7&0x1)>>0)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //电源指示2
        //D7-D6	保留
        //D4	AD2电源1V电源PG指示(2DVDD1PG)
        qstr= ((strYC.sourceFlag2_FPAGK7&0x10)>>4)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	AD2电源1_1V电源PG指示(2AVDD1_1PG)
        qstr= ((strYC.sourceFlag2_FPAGK7&0x08)>>3)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	AD2电源1V_2电源PG指示(2AVDD1_2PG)
        qstr= ((strYC.sourceFlag2_FPAGK7&0x4)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	AD2电源1.3VB电源PG指示(2VCC1.3BPG)
        qstr= ((strYC.sourceFlag2_FPAGK7&0x2)>>1)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	AD2电源2V电源PG指示(2AVDD2PG)
        qstr= ((strYC.sourceFlag2_FPAGK7&0x1)>>0)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //电源指示3
        //D7-D6	保留
        //D3	AD3电源1V电源PG指示(3DVDD1PG)
        qstr=((strYC.sourceFlag3_FPAGK7&0x08)>>3)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	AD3电源1_1V电源PG指示(3AVDD1_1PG)
        qstr=((strYC.sourceFlag3_FPAGK7&0x04)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	AD3电源1V_2电源PG指示(3AVDD1_2PG)
        qstr=((strYC.sourceFlag3_FPAGK7&0x2)>>1)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	AD3电源2V电源PG指示(3AVDD2PG)
        qstr=((strYC.sourceFlag3_FPAGK7&0x1))?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //电源指示4
        //D7-D6	保留
        //D5	1.5V电源PG指示(VCC1.5PG)
        qstr=((strYC.sourceFlag4_FPAGK7&0x20)>>5)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	2_1.5V电源PG指示(2VCC1.5PG)
        qstr=((strYC.sourceFlag4_FPAGK7&0x10)>>4)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	AD1电源1.8V电源PG指示(DVDD1P8PG)
        qstr=((strYC.sourceFlag4_FPAGK7&0x8)>>3)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	2.8V电源PG指示(VCC2.8PG)
        qstr=((strYC.sourceFlag4_FPAGK7&0x4)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	模拟3.3V电源PG指示(VCC3.3CLKPG)
        qstr=((strYC.sourceFlag4_FPAGK7&0x2 )>>1)?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	模拟3.3_2电源PG指示(VCC3.3CLK2PG)
        qstr=((strYC.sourceFlag4_FPAGK7&0x1))?"供电":"未供电";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //D15-D9	保留
        //D8-D0	ADC1温度
        tmp_short=qToBigEndian(strYC.ADC1_T_FPGAK7);
        qstr=QString ::number(tmp_short);
        if((tmp_short&0x0100))
        {
            tmp_short=tmp_short&0x00FF;
            tmp_short=256-tmp_short;
            qstr="-"+QString ::number(tmp_short);
        }
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D15-D9	保留
        //D8-D0	ADC2温度
        tmp_short=qToBigEndian(strYC.ADC2_T_FPGAK7);
        qstr=QString ::number(tmp_short);
        if((tmp_short&0x0100))
        {
            tmp_short=tmp_short & 0x00FF;
            tmp_short=256-tmp_short;
            qstr="-"+QString ::number(tmp_short);
        }
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        qstr=QString ::number(tmp_short);
        //D15-D9	保留
        //D8-D0	ADC3温度
        tmp_short=qToBigEndian(strYC.ADC3_T_FPGAK7);
        if((tmp_short&0x0100))
        {
            tmp_short=tmp_short&0x00FF;
            tmp_short=256-tmp_short;
            qstr="-"+QString ::number(tmp_short);
        }
        model->setItem(colcnt++, 3, new QStandardItem(qstr));



        //温度
        //保留
        //D11-D0	V7温度
        tmp_ushort=qToBigEndian(strYC.Fpgav7_1.Tem);
        model->setItem(colcnt++, 3, new QStandardItem(QString ::number((tmp_ushort&0xFFF)*503.975/4096.0-273.15)+"℃"));

        //GTX时钟锁定
        //D7-D6	保留
        //D5	收发K7时钟锁定指示
        qstr=((strYC.Fpgav7_1.GTX_CL&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	收发V7-2时钟锁定指示
        qstr=((strYC.Fpgav7_1.GTX_CL&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.Fpgav7_1.GTX_CL&0x8)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.Fpgav7_1.GTX_CL&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.Fpgav7_1.GTX_CL&0x2)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.Fpgav7_1.GTX_CL&0x1))?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //GTX建链
        //D7-D6	保留
        //D5	收发K7建链指示
        qstr=((strYC.Fpgav7_1.GTX_JL&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	收发V7-2建链指示
        qstr=((strYC.Fpgav7_1.GTX_JL&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	数据处理1 V7-1建链指示
        qstr=((strYC.Fpgav7_1.GTX_JL&0x8)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	数据处理1 V7-2建链指示
        qstr=((strYC.Fpgav7_1.GTX_JL&0x4)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	数据处理2 V7-1建链指示
        qstr=((strYC.Fpgav7_1.GTX_JL&0x2 )>>1)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	数据处理2 V7-2建链指示
        qstr=((strYC.Fpgav7_1.GTX_JL&0x1))?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //SRIO时钟锁定
        //保留
        model->setItem(colcnt++, 3, new QStandardItem("保留"));

        //SRIO建链
        model->setItem(colcnt++, 3, new QStandardItem("保留"));
        //保留

        //ADC/DAC时钟锁定
        //D7-D6	保留
        //D5	ADC1时钟锁定指示
        qstr=((strYC.ADC_DAC_CL_1&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	ADC2时钟锁定指示
        qstr=((strYC.ADC_DAC_CL_1&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	ADC3时钟锁定指示
        qstr=((strYC.ADC_DAC_CL_1&0x8)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2-D0	保留

        //ADC/DAC建链
        //D7-D6	保留
        //D5	ADC1建链指示
        qstr=((strYC.ADC_DAC_JL_1&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	ADC2建链指示
        qstr=((strYC.ADC_DAC_JL_1&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	ADC3建链指示
        qstr=((strYC.ADC_DAC_JL_1&0x8)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2-D0	保留


        //温度
        //保留
        //D11-D0 V7温度
        tmp_ushort=qToBigEndian(strYC.Fpgav7_2.Tem);
        model->setItem(colcnt++, 3, new QStandardItem(QString ::number((tmp_ushort&0x0FFF)*503.975/4096.0-273.15)+"℃"));

        //GTX时钟锁定
        //D7-D6	保留
        //D5	收发K7时钟锁定指示
        qstr=((strYC.Fpgav7_2.GTX_CL&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	收发V7-2时钟锁定指示
        qstr=((strYC.Fpgav7_2.GTX_CL&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.Fpgav7_2.GTX_CL&0x08)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.Fpgav7_2.GTX_CL&0x04)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.Fpgav7_2.GTX_CL&0x02)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.Fpgav7_2.GTX_CL&0x01))?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //GTX建链
        //D7-D6	保留
        //D5	收发K7建链指示
        qstr=((strYC.Fpgav7_2.GTX_JL&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	收发V7-2建链指示
        qstr=((strYC.Fpgav7_2.GTX_JL&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	数据处理1 V7-1建链指示
        qstr=((strYC.Fpgav7_2.GTX_JL&0x08)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2	数据处理1 V7-2建链指示
        qstr=((strYC.Fpgav7_2.GTX_JL&0x04)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D1	数据处理2 V7-1建链指示
        qstr=((strYC.Fpgav7_2.GTX_JL&0x02 )>>1)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D0	数据处理2 V7-2建链指示
        qstr=((strYC.Fpgav7_2.GTX_JL&0x01))?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));

        //SRIO时钟锁定
        //    保留
        model->setItem(colcnt++, 3, new QStandardItem("保留"));

        //SRIO建链
        model->setItem(colcnt++, 3, new QStandardItem("保留"));
        //    保留

        //ADC/DAC时钟锁定
        //D7-D6	保留
        //D5	ADC1时钟锁定指示
        qstr=((strYC.ADC_DAC_CL_2&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	ADC2时钟锁定指示
        qstr=((strYC.ADC_DAC_CL_2&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	ADC3时钟锁定指示
        qstr=((strYC.ADC_DAC_CL_2&0x08)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2-D0	保留

        //ADC/DAC建链
        //D7-D6	保留
        //D5	ADC1建链指示
        qstr=((strYC.ADC_DAC_JL_2&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D4	ADC2建链指示
        qstr=((strYC.ADC_DAC_JL_2&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D3	ADC3建链指示
        qstr=((strYC.ADC_DAC_JL_2&0x08)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 3, new QStandardItem(qstr));
        //D2-D0	保留

    }
    /******************数据处理模块1********************/
    if(1)
    {
        colcnt=0;

        //软件加载状态
        //D7-D4	保留
        //D3	DSP6678心跳
        qstr=((strYC.DataDealmk[0].softwareLoad_&0x8)>>3)?"存活":"死亡";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D2	DSP6678加载状态
        qstr=((strYC.DataDealmk[0].softwareLoad_&0x4)>>2)?"加载":"未加载";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	FPGAV7-1加载状态
        qstr=((strYC.DataDealmk[0].softwareLoad_&0x2)>>1)?"加载":"未加载";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	FPGAV7-2加载状态
        qstr=((strYC.DataDealmk[0].softwareLoad_&0x1)>>0)?"加载":"未加载";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //FPGAk7版本号
        //D7-D5	大版本号/D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.DataDealmk[0].version_FPGAK7&0xE0)>>5).arg(strYC.DataDealmk[0].version_FPGAK7&0x1F);
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //FPGAV7-1版本号
        //D7-D5	大版本号//D4-D0	小版本号---（排序前移）
        qstr=QString("%1.%2").arg((strYC.DataDealmk[0].Fpgav7[0].version&0xE0)>>5).arg(strYC.DataDealmk[0].Fpgav7[0].version&0x1F);
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //软件代号---（排序前移）
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[0].software);
        QString qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 5, new QStandardItem(qstr_sorft));
        //FPGAV7-2版本号---（排序前移）
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.DataDealmk[0].Fpgav7[1].version&0xE0)>>5).arg(strYC.DataDealmk[0].Fpgav7[1].version&0x1F);
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //软件代号---（排序前移）
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[1].software);
        qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 5, new QStandardItem(qstr_sorft));
        //DSP6678版本号
        //D7-D5	大版本号//D4-D0	小版本号---（排序前移）
        qstr=QString("%1.%2").arg((strYC.DataDealmk[0].versionDSP6678&0xE0)>>5).arg(strYC.DataDealmk[0].versionDSP6678&0x1F);
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //软件代号---（排序前移）
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].softwareNumber);
        qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 5, new QStandardItem(qstr_sorft));



        //GTX时钟锁定
        //    D7-D4 软件预加载数量高4位
        model->setItem(colcnt++, 5, new QStandardItem(QString ::number((strYC.DataDealmk[0].GTX_CL&0xF0)>>4)));
        //    D3	保留
        //D2	数据处理1 V7-1时钟锁定
        qstr=((strYC.DataDealmk[0].GTX_CL&0x04)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	数据处理1 V7-2时钟锁定
        qstr=((strYC.DataDealmk[0].GTX_CL&0x02)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	接口控制 V7时钟锁定
        qstr=(strYC.DataDealmk[0].GTX_CL&0x01)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //GTX建链D7-D3
        //    D7-D4 软件预加载数量低4位
        model->setItem(colcnt++, 5, new QStandardItem(QString ::number((strYC.DataDealmk[0].GTX_JL&0xF0)>>4)));
        //    D3	保留
        //D2	数据处理1 V7-1建链
        qstr=((strYC.DataDealmk[0].GTX_JL&0x4)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	数据处理1 V7-2建链
        qstr=((strYC.DataDealmk[0].GTX_JL&0x2)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	接口控制 V7建链
        qstr=((strYC.DataDealmk[0].GTX_JL&0x1)>>0)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //DSP、光模块电源
        //D7-D6	保留
        //D5	光模块(PG_FIB3V3)
        qstr=((strYC.DataDealmk[0].DSP_Source&0x20)>>5)?"供电":"未供电";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D4	DSP电源(PG_DSPVTT)
        qstr=((strYC.DataDealmk[0].DSP_Source&0x10)>>4)?"供电":"未供电";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D3	DSP电源(PG_DSP1V8)
        qstr=((strYC.DataDealmk[0].DSP_Source&0x08)>>3)?"供电":"未供电";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D2	DSP电源(PG_DSP1V5)
        qstr=((strYC.DataDealmk[0].DSP_Source&0x04)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	DSP电源(PG_DSP1V0_SMART)
        qstr=((strYC.DataDealmk[0].DSP_Source&0x02)>>1)?"供电":"未供电";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	DSP电源(PG_DSP1V0)
        qstr=((strYC.DataDealmk[0].DSP_Source&0x01)>>0)?"供电":"未供电";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));



        //温度
        //D15-D12	保留
        //D11-D0	V7温度
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[0].Tem);
        model->setItem(colcnt++, 5, new QStandardItem(QString ::number((tmp_ushort&0x0FFF)*503.975/4096.0-273.15)+"℃"));

        //GTX时钟锁定
        //D7-D6	保留
        //D5	收发K7时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_CL&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D4	收发V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_CL&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D3	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_CL&0x08)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D2	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_CL&0x04)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_CL&0x02 )>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_CL&0x01)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //GTX建链
        //D7-D6	保留
        //D5	收发K7建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_JL&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D4	收发V7-2建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_JL&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D3	数据处理1 V7-1建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_JL&0x08)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D2	数据处理1 V7-2建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_JL&0x04)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	数据处理2 V7-1建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_JL&0x02)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理2 V7-2建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[0].GTX_JL&0x01)>>0)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //SRIO时钟锁定
        //D7-D2	保留
        //D1	接口控制 V7时钟锁定指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[0].SRIO_CL);
        qstr=((tmp_ushort&0x0002)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678时钟锁定指示
        qstr=(tmp_ushort&0x0001)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //    保留

        //SRIO建链
        //D7-D2	保留
        //D1	接口控制 V7建链指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[0].SRIO_JL);
        qstr=((tmp_ushort&0x0002)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678建链指示
        qstr=(tmp_ushort&0x0001)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));


        //温度
        //D15-D12	保留
        //D11-D0	V7温度
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[1].Tem);
        model->setItem(colcnt++, 5, new QStandardItem(QString ::number((tmp_ushort&0x0FFF)*503.975/4096.0-273.15)+"℃"));

        //GTX时钟锁定
        //D7-D6	保留
        //D5	收发K7时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_CL&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D4	收发V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_CL&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D3	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_CL&0x8)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D2	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_CL&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_CL&0x2 )>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_CL&0x1)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //GTX建链
        //D7-D6	保留
        //D5	收发K7建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_JL&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D4	收发V7-2建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_JL&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D3	数据处理1 V7-1建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_JL&0x8)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D2	数据处理1 V7-2建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_JL&0x4)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D1	数据处理2 V7-1建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_JL&0x2)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理2 V7-2建链指示
        qstr=((strYC.DataDealmk[0].Fpgav7[1].GTX_JL&0x1)>>0)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));

        //SRIO时钟锁定
        //D7-D2	保留
        //D1	接口控制 V7时钟锁定指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[1].SRIO_CL);
        qstr=((tmp_ushort&0x0002)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678时钟锁定指示
        qstr=(tmp_ushort&0x0001)?"锁定":"未锁定";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //    保留

        //SRIO建链
        //D7-D2	保留
        //D1	接口控制 V7建链指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[0].Fpgav7[1].SRIO_JL);
        qstr=((tmp_ushort&0x0001)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678建链指示
        qstr=(tmp_ushort&0x0001)?"建链":"未建链";
        model->setItem(colcnt++, 5, new QStandardItem(qstr));


    }

    /******************数据处理模块2********************/
    if(1)
    {
        colcnt=0;
        //软件加载状态
        //D7-D4	保留
        //D3	DSP6678心跳
        qstr=((strYC.DataDealmk[1].softwareLoad_&0x8)>>3)?"存活":"死亡";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D2	DSP6678加载状态
        qstr=((strYC.DataDealmk[1].softwareLoad_&0x4)>>2)?"加载":"未加载";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D1	FPGAV7-1加载状态
        qstr=((strYC.DataDealmk[1].softwareLoad_&0x2)>>1)?"加载":"未加载";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	FPGAV7-2加载状态
        qstr=((strYC.DataDealmk[1].softwareLoad_&0x1)>>0)?"加载":"未加载";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //FPGAK7版本号
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.DataDealmk[1].version_FPGAK7&0xE0)>>5).arg(strYC.DataDealmk[1].version_FPGAK7&0x1F);
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //FPGAV7-1版本号---（排序前移）
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.DataDealmk[1].Fpgav7[0].version&0xE0)>>5).arg(strYC.DataDealmk[1].Fpgav7[0].version&0x1F);
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //软件代号---（排序前移）
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[0].software);
        QString qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 7, new QStandardItem(qstr_sorft));

        //FPGAV7-2版本号---（排序前移）
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.DataDealmk[1].Fpgav7[1].version&0xE0)>>5).arg(strYC.DataDealmk[1].Fpgav7[1].version&0x1F);
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //软件代号---（排序前移）
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[1].software);
        qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 7, new QStandardItem(qstr_sorft));

        //DSP6678版本号---（排序前移）
        //D7-D5	大版本号//D4-D0	小版本号
        qstr=QString("%1.%2").arg((strYC.DataDealmk[1].versionDSP6678&0xE0)>>5).arg(strYC.DataDealmk[1].versionDSP6678&0x1F);
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //DSP6678软件代号---（排序前移）
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].softwareNumber);
        qstr_sorft=QString("0x%1").arg(tmp_ushort,4,16,QLatin1Char('0')).toUpper();
        model->setItem(colcnt++, 7, new QStandardItem(qstr_sorft));



        //GTX时钟锁定
        //    D7-D4 软件预加载数量高4位
        model->setItem(colcnt++, 7, new QStandardItem(QString ::number((strYC.DataDealmk[1].GTX_CL&0xF0)>>4)));
        //    D3	保留
        //D2	数据处理1 V7-1时钟锁定
        qstr=((strYC.DataDealmk[1].GTX_CL&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D1	数据处理1 V7-2时钟锁定
        qstr=((strYC.DataDealmk[1].GTX_CL&0x2)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	接口控制 V7时钟锁定
        qstr=((strYC.DataDealmk[1].GTX_CL&0x1)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //GTX建链
        //    D7-D4 软件预加载数量高4位
        model->setItem(colcnt++, 7, new QStandardItem(QString ::number((strYC.DataDealmk[1].GTX_JL&0xF0)>>4)));
        //    D3	保留
        //D2	数据处理1 V7-1建链
        qstr=((strYC.DataDealmk[1].GTX_JL&0x4)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D1	数据处理1 V7-2建链
        qstr=((strYC.DataDealmk[1].GTX_JL&0x2)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	接口控制 V7建链
        qstr=((strYC.DataDealmk[1].GTX_JL&0x1)>>0)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //DSP、光模块电源
        //D7-D6	保留
        //D5	光模块(PG_FIB3V3)
        qstr=((strYC.DataDealmk[1].DSP_Source&0x20)>>5)?"供电":"未供电";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D4	DSP电源(PG_DSPVTT)
        qstr=((strYC.DataDealmk[1].DSP_Source&0x10)>>4)?"供电":"未供电";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D3	DSP电源(PG_DSP1V8)
        qstr=((strYC.DataDealmk[1].DSP_Source&0x8)>>3)?"供电":"未供电";
        model->setItem(colcnt++,7, new QStandardItem(qstr));
        //D2	DSP电源(PG_DSP1V5)
        qstr=((strYC.DataDealmk[1].DSP_Source&0x4)>>2)?"供电":"未供电";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D1	DSP电源(PG_DSP1V0_SMART)
        qstr=((strYC.DataDealmk[1].DSP_Source&0x2)>>1)?"供电":"未供电";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	DSP电源(PG_DSP1V0)
        qstr=((strYC.DataDealmk[1].DSP_Source&0x1)>>0)?"供电":"未供电";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));



        //温度
        //D15-D12	保留
        //D11-D0	V7温度
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[0].Tem);
        model->setItem(colcnt++, 7, new QStandardItem(QString ::number((tmp_ushort&0x0FFF)*503.975/4096.0-273.15)+"℃"));

        //GTX时钟锁定
        //D7-D6	保留
        //D5	收发K7时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_CL&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D4	收发V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_CL&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D3	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_CL&0x8)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D2	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_CL&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++,7, new QStandardItem(qstr));
        //D1	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_CL&0x2 )>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_CL&0x1)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //GTX建链
        //D7-D6	保留
        //D5	收发K7建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_JL&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D4	收发V7-2建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_JL&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D3	数据处理1 V7-1建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_JL&0x8)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D2	数据处理1 V7-2建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_JL&0x4)>>2)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D1	数据处理2 V7-1建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_JL&0x2)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理2 V7-2建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[0].GTX_JL&0x1)>>0)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //SRIO时钟锁定
        //D7-D2	保留
        //D1	接口控制 V7时钟锁定指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[0].SRIO_CL);
        qstr=((tmp_ushort&0x0002)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678时钟锁定指示
        qstr=(tmp_ushort&0x0001)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //    保留

        //SRIO建链
        //D7-D2	保留
        //D1	接口控制 V7建链指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[0].SRIO_JL);
        qstr=((tmp_ushort&0x0002)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678建链指示
        qstr=(tmp_ushort&0x0001)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));


        //温度
        //D15-D12	保留
        //D11-D0	V7温度
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[1].Tem);
        model->setItem(colcnt++, 7, new QStandardItem(QString ::number((tmp_ushort&0x0FFF)*503.975/4096.0-273.15)+"℃"));

        //GTX时钟锁定
        //D7-D6	保留
        //D5	收发K7时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_CL&0x20)>>5)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D4	收发V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_CL&0x10)>>4)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D3	数据处理1 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_CL&0x8)>>3)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D2	数据处理1 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_CL&0x4)>>2)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D1	数据处理2 V7-1时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_CL&0x2 )>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理2 V7-2时钟锁定指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_CL&0x1)>>0)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //GTX建链
        //D7-D6	保留
        //D5	收发K7建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_JL&0x20)>>5)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D4	收发V7-2建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_JL&0x10)>>4)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D3	数据处理1 V7-1建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_JL&0x8)>>3)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D2	数据处理1 V7-2建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_JL&0x4)>>2)?"建链":"未建链";
        model->setItem(colcnt++,7, new QStandardItem(qstr));
        //D1	数据处理2 V7-1建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_JL&0x2)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理2 V7-2建链指示
        qstr=((strYC.DataDealmk[1].Fpgav7[1].GTX_JL&0x1)>>0)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

        //SRIO时钟锁定
        //D7-D2	保留
        //D1	接口控制 V7时钟锁定指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[1].SRIO_CL);
        qstr=((tmp_ushort&0x0002)>>1)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678时钟锁定指示
        qstr=(tmp_ushort&0x0001)?"锁定":"未锁定";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //    保留

        //SRIO建链
        //D7-D2	保留
        //D1	接口控制 V7建链指示
        tmp_ushort=qToBigEndian(strYC.DataDealmk[1].Fpgav7[1].SRIO_JL);
        qstr=((tmp_ushort&0x0002)>>1)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));
        //D0	数据处理1 DSP6678建链指示
        qstr=(tmp_ushort&0x0001)?"建链":"未建链";
        model->setItem(colcnt++, 7, new QStandardItem(qstr));

    }

    /***************软件信息****************/
    if(1)
    {
    colcnt=0;
    //接口DSP6701
    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.Dsp6701_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));

    //接口DSP6678
    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.DSP6678_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //收发V7-1

    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.V7_1_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //收发V7-2

    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.V7_2_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //数据1V7-1

    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.D1V7_1_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++,9, new QStandardItem(qstr));
    //数据1V7-2

    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.D1V7_2_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //数据1DSP6678

    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.D1DSP6678_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //数据2V7-1
    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.D2V7_1_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //数据2V7-1
    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.D2V7_2_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    //数据1DSP6678

    qstr="";
    for(int i=0;i<16;i++)
    {
        qstr+=QString::number(strYC.D2DSP6678_S_I[i],16).toUpper()+" ";
    }
    model->setItem(colcnt++, 9, new QStandardItem(qstr));
    }

    return ;
}










//清空表格
void subyc_canC81::on_pushButton_clearList_clicked()
{
    int cnt=model->rowCount();
    for (int n=0;n<cnt;n++) {

        model->setItem(n, 1, new QStandardItem(""));
        model->setItem(n, 3, new QStandardItem(""));
        model->setItem(n, 5, new QStandardItem(""));
        model->setItem(n, 7, new QStandardItem(""));
        model->setItem(n, 9, new QStandardItem(""));
    }
}

