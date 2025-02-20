#include "sub1553_gkcontrol.h"

#include "ui_sub1553_gkcontrol.h"
#include <QFileDialog>
#include <QMessageBox>
sub1553_gkcontrol::sub1553_gkcontrol(QWidget* parent)
    : QWidget(parent), ui(new Ui::sub1553_gkcontrol) {
    ui->setupUi(this);

    // 隐藏控件

    ui->checkBox_csbit6->setVisible(false);
    ui->checkBox_csbit7->setVisible(false);
    ui->checkBox_csbit8->setVisible(false);

    // 预置模板任务删除(按任务ID)列表
    ui->tableWidget_taskUID->setColumnCount(2);
    ui->tableWidget_taskUID->setHorizontalHeaderLabels(QStringList()<< "序号"<< "流水ID ");

    // ui->tableWidget_taskUID->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // ui->tableWidget_taskUID->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//最小显示完整，出现滚动条
    ui->tableWidget_taskUID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 屏幕不够大自动缩小，不出现滚动条
    ui->tableWidget_taskUID->verticalHeader()->setVisible(false);  // 隐藏行号

    // 任务删除(按UID)列表
    ui->tableWidget_task_deleteUID->setColumnCount(3);
    ui->tableWidget_task_deleteUID->setHorizontalHeaderLabels(QStringList()<< "序号"<< "主任务UID"<<"子任务UID");
    ui->tableWidget_task_deleteUID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 屏幕不够大自动缩小，不出现滚动条
    ui->tableWidget_task_deleteUID->verticalHeader()->setVisible(false);  // 隐藏行号

    //flash下传0x3B,软件名字下拉框
    QStringList list;

    list.append("收发处理模块-采集与信道化接收软件");
    list.append("收发处理模块-波束合成接收软件");
    list.append("收发处理模块-波束合成发射软件");
    list.append("收发处理模块-调频源软件");
    list.append("收发处理模块-数据形成软件");


    list.append("电子侦察-宽带信号检测和存储软件");
    list.append("电子侦察-LINK16测向软件");
    list.append("电子侦察-塔康侦测软件");
    list.append("电子侦察-塔康全频段侦察软件");
    list.append("电子侦察-敌我侦测软件");
    list.append("电子侦察-铱星信号侦测软件");
    list.append("电子侦察-海事信号侦测软件");
    list.append("电子侦察-星链信号侦察软件");
    list.append("电子侦察-雷达信号预处理软件");
    list.append("电子侦察-通信信号处理软件");
    list.append("电子侦察-雷达信号主处理软件");
    list.append("电子侦察-LINK16测向软件");
    list.append("电子侦察-敌我侦测软件");
    list.append("电子侦察-雷达信号预处理软件");
    list.append("电子侦察-通信信号处理软件");
    list.append("电子侦察-雷达信号主处理软件");

    list.append("电子干扰-通信干扰处理软件");
    list.append("电子干扰-导航与星链干扰处理软件");
    list.append("电子干扰-通信与导航干扰策略与控制软件");
    list.append("电子干扰-雷达侦察干扰处理软件");
    list.append("电子干扰-雷达干扰策略与控制软件");
    list.append("电子干扰-通信干扰处理软件");
    list.append("电子干扰-导航与星链干扰处理软件");
    list.append("电子干扰-通信与导航干扰策略与控制软件");

    list.append("SAR成像-2m/3m模式成像预处理FPGA");
    list.append("SAR成像-2m/3m模式成像1FPGA");
    list.append("SAR成像-2m/3m模式成像2FPGA");
    list.append("SAR成像-10m模式成像预处理FPGA");
    list.append("SAR成像-10m模式成像1FPGA");
    list.append("SAR成像-10m模式成像2FPGA");
    list.append("SAR成像-2m/3m/10m模式一体化成像3FPGA");
    list.append("SAR成像-2m/3m/10m模式一体化成像4FPGA");
    list.append("SAR成像-2m/3m条带模式目标检测FPGA");
    list.append("SAR成像-2m/3m条带模式动目标精聚焦FPGA");
    list.append("SAR成像-2m/3m条带模式目标识别分类FPGA");
    list.append("SAR成像-广域搜索模式探测成像1FPGA");
    list.append("SAR成像-广域搜索模式探测成像2FPGA");
    list.append("SAR成像-广域搜索模式探测成像3FPGA");
    list.append("SAR成像-广域搜索模式目标检测FPGA");
    list.append("SAR成像-广域搜索模式目标军民分类FPGA");

    list.append("备用导航-星历拟合与控制软件");
    list.append("备用导航-导航信号生成软件");

    list.append("类5G通信-类5G通信软件(更新区)");
    list.append("类5G通信-类5G协议控制软件(更新区)");
    list.append("类5G通信-类5G通信软件(基础区)");
    list.append("类5G通信-类5G协议控制软件(基础区)");

    list.append("JIDS链-数据链信号处理软件");
    list.append("JIDS链-数据链信号处理软件");

    list.append("产生式欺骗-产生式欺骗干扰FPGA1");
    list.append("产生式欺骗-产生式欺骗干扰FPGA2");
    list.append("产生式欺骗-产生式欺骗干扰DSP1");

    list.append("数据参数-幅度表");
    list.append("数据参数-舰船检测网络参数");
    list.append("数据参数-舰船识别网络参数");
    list.append("数据参数-探测模式舰船分类网络参数");
    list.append("数据参数-海陆分割数据库");
    list.append("数据参数-零值补偿参数、功率参数");
    list.append("数据参数-通信参数");
    list.append("数据参数-雷达重点侦察库");
    list.append("数据参数-高算力平台FLASH分区表（存三份）");

    list.append("NOR FLASH1-接口控制软件1(收发模块)");
    list.append("NOR FLASH1-接口控制软件1(数据模块)");
    list.append("NOR FLASH1-数据传输软件更新区");
    list.append("NOR FLASH1-数据传输软件基础区1");
    list.append("NOR FLASH1-综合调度软件1");
    list.append("NOR FLASH1-CAN解析及重构更新区");
    list.append("NOR FLASH2-接口控制软件2(收发模块)");
    list.append("NOR FLASH2-接口控制软件2(数据模块)");
    list.append("NOR FLASH2-数据传输软件基础区2");
    list.append("NOR FLASH2-数据传输软件基础区3");
    list.append("NOR FLASH2-综合调度软件2");

    ui->comboBox__3B_3->addItems(list);
    ui->comboBox__3B_3->setEnabled(0);
    //flash下传0x3B,flash选择下拉框
    QStringList list2;

    list2.append("1:P2020基础区");
    list2.append("2：P2020更新区A");
    list2.append("3：P2020更新区B");
    list2.append("4：P2020更新区C");
    list2.append("5：管控V7更新区");
    list2.append("6：管控V7基础区");
    list2.append("7：/");
    list2.append("8：/");
    list2.append("9：融合DSP基础区");
    list2.append("10：融合DSP更新区");
    list2.append("11：通侦定位DSP基础区");
    list2.append("12：通侦定位DSP更新区");
    list2.append("13：雷侦定位DSP基础区");
    list2.append("14：雷侦定位DSP更新区");
    list2.append("15：AI基础区");
    list2.append("16：AI更新区");
    list2.append("17：6Gb三模");
    list2.append("18：6Gb第1片2Gb");
    list2.append("19：6Gb第2片2Gb");
    list2.append("20：6Gb第3片2Gb");
    list2.append("21：融合DSP的引导区");
    list2.append("22：通侦定位DSP的引导区");
    list2.append("23：雷侦定位DSP的引导区");
    list2.append("24：AI的引导区");
    list2.append("25：/");
    list2.append("26：重点目标库");
    list2.append("27：重点通信信号");
    list2.append("28：雷达重点侦察库");
    list2.append("29：P2020更新区总片区");
    list2.append("30：处理V7总片区");


    ui->comboBox__3B_2->addItems(list2);

}

sub1553_gkcontrol::~sub1553_gkcontrol() { delete ui; }


//软件名--对于地址，大小
void sub1553_gkcontrol::on_comboBox__3B_3_activated(const QString &arg1)
{
    QString str1,str2;

    if(arg1=="收发处理模块-采集与信道化接收软件")        {str1="0x00000000";str2="28672";}
    else if(arg1=="收发处理模块-波束合成接收软件")        {str1="0x00000E00";str2="28672";}
    else if(arg1=="收发处理模块-波束合成发射软件")        {str1="0x00001C00";str2="28672";}
    else if(arg1=="收发处理模块-调频源软件")        {str1="0x00002A00";str2="28672";}
    else if(arg1=="收发处理模块-数据形成软件")        {str1="0x00003800";str2="28672";}

    else if(arg1=="电子侦察-宽带信号检测和存储软件")        {str1="0x00004600";str2="28672";}
    else if(arg1=="电子侦察-LINK16测向软件")        {str1="0x00005400";str2="28672";}
    else if(arg1=="电子侦察-塔康侦测软件")        {str1="0x00006200";str2="28672";}
    else if(arg1=="电子侦察-塔康全频段侦察软件")     {str1="0x00007000";str2="28672";}
    else if(arg1=="电子侦察-敌我侦测软件")            {str1="0x00007E00";str2="28672";}
    else if(arg1=="电子侦察-铱星信号侦测软件")      {str1="0x00008C00";str2="28672";}
    else if(arg1=="电子侦察-海事信号侦测软件")      {str1="0x00009A00";str2="28672";}
    else if(arg1=="电子侦察-星链信号侦察软件")      {str1="0x0000A800";str2="28672";}
    else if(arg1=="电子侦察-雷达信号预处理软件")     {str1="0x0000B600";str2="28672";}
    else if(arg1=="电子侦察-通信信号处理软件")      {str1="0x00031000";str2="8192";}
    else if(arg1=="电子侦察-雷达信号主处理软件")     {str1="0x00031400";str2="8192";}
    else if(arg1=="电子侦察-LINK16测向软件")        {str1="0x00021400";str2="28672";}
    else if(arg1=="电子侦察-敌我侦测软件")        {str1="0x00022200";str2="28672";}
    else if(arg1=="电子侦察-雷达信号预处理软件")     {str1="0x00023000";str2="28672";}
    else if(arg1=="电子侦察-通信信号处理软件")      {str1="0x00033000";str2="8192";}
    else if(arg1=="电子侦察-雷达信号主处理软件")     {str1="0x00033400";str2="8192";}

    else if(arg1=="电子干扰-通信干扰处理软件")        {str1="0x0000C400";str2="28672";}
    else if(arg1=="电子干扰-导航与星链干扰处理软件")      {str1="0x0000D200";str2="28672";}
    else if(arg1=="电子干扰-通信与导航干扰策略与控制软件")  {str1="0x00031800";str2="8192";}
    else if(arg1=="电子干扰-雷达侦察干扰处理软件")         {str1="0x0000E000";str2="28672";}
    else if(arg1=="电子干扰-雷达干扰策略与控制软件")     {str1="0x00031C00";str2="8192";}
    else if(arg1=="电子干扰-通信干扰处理软件")         {str1="0x00023E00";str2="28672";}
    else if(arg1=="电子干扰-导航与星链干扰处理软件")         {str1="0x00024C00";str2="28672";}
    else if(arg1=="电子干扰-通信与导航干扰策略与控制软件")   {str1="0x00033800";str2="8192";}

    else if(arg1=="SAR成像-2m/3m模式成像预处理FPGA") {str1="0x0000EE00";str2="28672";}
    else if(arg1=="SAR成像-2m/3m模式成像1FPGA")       {str1="0x0000FC00";str2="28672";}
    else if(arg1=="SAR成像-2m/3m模式成像2FPGA")       {str1="0x00010A00";str2="28672";}
    else if(arg1=="SAR成像-10m模式成像预处理FPGA")       {str1="0x00011800";str2="28672";}
    else if(arg1=="SAR成像-10m模式成像1FPGA")         {str1="0x00012600";str2="28672";}
    else if(arg1=="SAR成像-10m模式成像2FPGA")         {str1="0x00013400";str2="28672";}
    else if(arg1=="SAR成像-2m/3m/10m模式一体化成像3FPGA"){str1="0x00014200";str2="28672";}
    else if(arg1=="SAR成像-2m/3m/10m模式一体化成像4FPGA"){str1="0x00015000";str2="28672";}
    else if(arg1=="SAR成像-2m/3m条带模式目标检测FPGA")    {str1="0x00015E00";str2="28672";}
    else if(arg1=="SAR成像-2m/3m条带模式动目标精聚焦FPGA"){str1="0x00016C00";str2="28672";}
    else if(arg1=="SAR成像-2m/3m条带模式目标识别分类FPGA"){str1="0x00017A00";str2="28672";}
    else if(arg1=="SAR成像-广域搜索模式探测成像1FPGA")  {str1="0x00018800";str2="28672";}
    else if(arg1=="SAR成像-广域搜索模式探测成像2FPGA")  {str1="0x00019600";str2="28672";}
    else if(arg1=="SAR成像-广域搜索模式探测成像3FPGA")  {str1="0x0001A400";str2="28672";}
    else if(arg1=="SAR成像-广域搜索模式目标检测FPGA")   {str1="0x0001B200";str2="28672";}
    else if(arg1=="SAR成像-广域搜索模式目标军民分类FPGA"){str1="0x0001C000";str2="28672";}


    else if(arg1=="备用导航-星历拟合与控制软件")         {str1="0x00032000";str2="8192";}
    else if(arg1=="备用导航-导航信号生成软件")          {str1="0x0001CE00";str2="28672";}

    else if(arg1=="类5G通信-类5G通信软件(更新区)")         {str1="0x0001DC00";str2="28672";}
    else if(arg1=="类5G通信-类5G协议控制软件(更新区)")   {str1="0x00032400";str2="8192";}
    else if(arg1=="类5G通信-类5G通信软件(基础区)")         {str1="0x00025A00";str2="28672";}
    else if(arg1=="类5G通信-类5G协议控制软件(基础区)")   {str1="0x00033C00";str2="8192";}

    else if(arg1=="JIDS链-数据链信号处理软件")            {str1="0x0001EA00";str2="28672";}
    else if(arg1=="JIDS链-数据链信号处理软件")            {str1="0x00032800";str2="8192";}

    else if(arg1=="产生式欺骗-产生式欺骗干扰FPGA1")         {str1="0x0001F800";str2="28672";}
    else if(arg1=="产生式欺骗-产生式欺骗干扰FPGA2")         {str1="0x00020600";str2="28672";}
    else if(arg1=="产生式欺骗-产生式欺骗干扰DSP1")          {str1="0x00032C00";str2="8192";}

    else if(arg1=="数据参数-幅度表")                       {str1="0x00036000";str2=QString::number(1*1024);}
    else if(arg1=="数据参数-舰船检测网络参数")              {str1="0x00036080";str2=QString::number(8*1024);}
    else if(arg1=="数据参数-舰船识别网络参数")              {str1="0x00036480";str2=QString::number(16*1024);}
    else if(arg1=="数据参数-探测模式舰船分类网络参数")      {str1="0x00036C80";str2=QString::number(8*1024);}
    else if(arg1=="数据参数-海陆分割数据库")               {str1="0x00037080";str2=QString::number(13*1024);}
    else if(arg1=="数据参数-零值补偿参数、功率参数")           {str1="0x0003B180";str2=QString::number(1*1024);}
    else if(arg1=="数据参数-通信参数")                      {str1="0x0003B200";str2=QString::number(2*1024);}
    else if(arg1=="数据参数-雷达重点侦察库")                   {str1="0x0003B300";str2=QString::number(9*1024);}
    else if(arg1=="数据参数-高算力平台FLASH分区表（存三份）")   {str1="0x0003B780";str2=QString::number(1*1024);}


    else if(arg1=="NOR FLASH1-接口控制软件1(收发模块)")         {str1="0x0000000";str2="16384";}
    else if(arg1=="NOR FLASH1-接口控制软件1(数据模块)")         {str1="0x1000000";str2="16384";}
    else if(arg1=="NOR FLASH1-数据传输软件更新区")   {str1="0x2000000";str2="32768";}
    else if(arg1=="NOR FLASH1-数据传输软件基础区1")  {str1="0x4000000";str2="32768";}
    else if(arg1=="NOR FLASH1-综合调度软件1")         {str1="0x6000000";str2="8192";}
    else if(arg1=="NOR FLASH1-CAN解析及重构更新区") {str1="0x6800000";str2="8192";}

    else if(arg1=="NOR FLASH2-接口控制软件2(收发模块)")         {str1="0x0000000";str2="16384";}
    else if(arg1=="NOR FLASH2-接口控制软件2(数据模块)")         {str1="0x1000000";str2="16384";}
    else if(arg1=="NOR FLASH2-数据传输软件基础区2")      {str1="0x2000000";str2="32768";}
    else if(arg1=="NOR FLASH2-数据传输软件基础区3")      {str1="0x4000000";str2="32768";}
    else if(arg1=="NOR FLASH2-综合调度软件2")         {str1="0x6000000";str2="8192";}
    else{};

    ui->lineEdit_3B_4->setText(str1);//起始地址
    ui->lineEdit__3B_5->setText(str2);//长度

}

// 公用添加到主界面窗口
void sub1553_gkcontrol::Pblic_Addorderlist(uchar* databuff, int buffLen,
                                           QString buffname) {
    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 3;
    order_data.gap_time = 1;
    order_data.order_name = buffname;
    order_data.order_kind = 2;
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff, buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");
}

uint sub1553_gkcontrol::toHex_uint(QString qstr)
{
    QString S_tmp;
    QByteArray hex_data;
    int strlen;
    uint tmp_uint=0;
    S_tmp=qstr;
    S_tmp=S_tmp.replace("0x","");
    hex_data=QByteArray::fromHex(S_tmp.toLatin1());//将字节流转换位16进制,char型
    strlen=(S_tmp.size()+1)/2;
    if(strlen>4)strlen=4;

    uchar tmparr[4]={0};
    memcpy(&tmparr[4-strlen],(uchar*)hex_data.data(),strlen);//获取地址(4字节，输入1个字节需要放在低位)
    memcpy(&tmp_uint,tmparr,sizeof (tmparr));//(4字节，输入两个字节需要放在低位)
    return tmp_uint;

}

//qstring转16进制ushort
ushort sub1553_gkcontrol::toHex_ushort(QString qstr)
{
    QString S_tmp;
    QByteArray hex_data;
    int strlen;
    ushort tmp_ushort=0;
    S_tmp=qstr;
    S_tmp=S_tmp.replace("0x","");
    hex_data=QByteArray::fromHex(S_tmp.toLatin1());//将字节流转换位16进制,char型
    strlen=(S_tmp.size()+1)/2;
    if(strlen>2)strlen=2;

    uchar tmparr[2]={0};
    memcpy(&tmparr[2-strlen],(uchar*)hex_data.data(),strlen);//获取地址(2字节，输入1个字节需要放在低位)
    memcpy(&tmp_ushort,tmparr,sizeof (tmparr));//(2字节，输入两个字节需要放在低位)
    return tmp_ushort;
}

// 任务执行设置
void sub1553_gkcontrol::on_pB_task_execute_clicked() {
    Task_execute_set tes;
    memset(&tes, 0, sizeof(tes));
    tes.ordermark = 0x30;
    // 任务类型
    tes.task_type = ui->cB_taskexecute_type->currentIndex() + 1;
    // 时间长度
    // 任务流水号
    tes.task_number =qToBigEndian(ui->LineEdit_taskexecute_number->text().toUShort());
    //功能模式段数
    tes.Mode_Fun_cnt =ui->comboBox_taskmode->currentIndex()+1;
    //功能模式1开始时间
    tes.mode1_starts=qToBigEndian(ui->lineEdit_mode1_1->text().toUInt());
    //功能模式1结束时间
    tes.mode1_ends=qToBigEndian(ui->lineEdit_mode1_2->text().toUInt());
    //功能模式1
    tes.mode1_choose=ui->cB_mode1_3->currentIndex()+1;
    //功能模式2开始时间
    tes.mode2_starts=qToBigEndian(ui->lineEdit_mode2_1->text().toUInt());
    //功能模式2结束时间
    tes.mode2_ends=qToBigEndian(ui->lineEdit_mode2_2->text().toUInt());
    //功能模式2
    tes.mode2_choose=ui->cB_mode2_3->currentIndex()+1;
    // 列表封装
    Pblic_Addorderlist((uchar*)&tes, sizeof(tes), "任务执行设置 : "+ui->cB_mode1_3->currentText());
}

// 管控内存下传
void sub1553_gkcontrol::on_pB_function_model_set_clicked() {
    Function_model_set fms;
    memset(&fms, 0, sizeof(fms));
    // 指令标识
    fms.ordermark = 0x31;
    // 数传通道
    fms.task_choose =ui->cB_func_model_set_tasktype->currentIndex() + 1;
    // 内存起始地址
    fms.memory_1 =toHex_uint(ui->LineEdit_0x31_2->text());
    // 内存结束地址
    fms.memory_2 =toHex_uint(ui->lineEdit_0x31_3->text());
    // 列表封装
    Pblic_Addorderlist((uchar*)&fms, sizeof(fms), "管控内存下传 : "+ui->cB_func_model_set_tasktype->currentText());
}

// 预置模板任务删除(按任务ID)
void sub1553_gkcontrol::on_pB_pre_taskmode_eliminate_clicked() {
    Premodel_task_elibyid pt;
    memset(&pt, 0, sizeof(pt));
    pt.ordermark = 0x33;
    int tasknum = ui->LineEdit_task_number->text().toUInt();
    if (tasknum > 50) tasknum = 50;
    pt.tasknum = tasknum;
    // 任务n UID。。。最多50
    for (int i = 0; i < tasknum; i++) {
        QString tmpstr = ui->tableWidget_taskUID->item(i, 1)->text();  // 设置内容
        pt.task_UID[i] = qToBigEndian(tmpstr.toUShort());
    }
    int len=2+tasknum*2;
    // 列表封装
    Pblic_Addorderlist((uchar*)&pt, len, "预置任务模板删除");
}

//预置任务模板删除--改变表格
void sub1553_gkcontrol::on_LineEdit_task_number_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if(num>50)
    {
        return;
    }
    ui->tableWidget_taskUID->setRowCount(0);
    for (int i = 0; i < num; i++) {
        ui->tableWidget_taskUID->insertRow(i);
        ui->tableWidget_taskUID->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->tableWidget_taskUID->setItem(i, 1, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_taskUID->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
    }
}

// 任务删除(按照频段)
void sub1553_gkcontrol::on_pB_task_eliminate_highfrequencyband_clicked() {
    Task_eli_byHighFrequency tf;
    memset(&tf, 0, sizeof(tf));
    tf.ordermark = 0x34;
    tf.task_type = ui->cB_tasktype->currentIndex() + 1;
    tf.frequencyband_num = ui->cB_frequencyband_num->currentIndex() + 1;
    tf.bl = 0xff;
    // 列表封装
    Pblic_Addorderlist((uchar*)&tf, sizeof(tf), "任务删除(按频段) : "+ui->cB_tasktype->currentText()
                       +ui->cB_frequencyband_num->currentText());
}

// 任务删除(按UID)
void sub1553_gkcontrol::on_pB_pre_task_deleteUID_clicked() {
    Task_eli_byUID str;
    memset(&str, 0, sizeof(str));
    str.ordermark = 0x35;
    int tasknum = ui->LineEdit_task_deleteUID->text().toUInt();
    if (tasknum > 50) tasknum = 50;
    str.tasknum = tasknum;
    // 任务n UID。。。最多50
    for (int i = 0; i < tasknum; i++) {
        QString tmpstr1 =ui->tableWidget_task_deleteUID->item(i, 1)->text();  // 设置内容
        QString tmpstr2 =ui->tableWidget_task_deleteUID->item(i, 2)->text();  // 设置内容
        str.task_UID[i].main_uid = qToBigEndian(tmpstr1.toUShort());
        str.task_UID[i].sub_uid = qToBigEndian(tmpstr2.toUShort());
    }
    int len=2+tasknum*4;
    // 列表封装
    Pblic_Addorderlist((uchar*)&str, len, "任务删除(按UID)");
}
//任务删除(按UID)---uid任务个数控件
void sub1553_gkcontrol::on_LineEdit_task_deleteUID_textChanged(const QString &arg1)
{
    int num=arg1.toUInt();
    if(num>50)
    {
        return;
    }
    ui->tableWidget_task_deleteUID->setRowCount(0);
    for (int i = 0; i < num; i++) {
        ui->tableWidget_task_deleteUID->insertRow(i);
        ui->tableWidget_task_deleteUID->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->tableWidget_task_deleteUID->setItem(i, 1, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_task_deleteUID->setItem(i, 2, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget_task_deleteUID->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
    }
}


// 任务删除(按高算力平台)
void sub1553_gkcontrol::on_pB_task_eliminate_high_clicked() {
    Task_eli_byHighCalculate tc;
    memset(&tc, 0, sizeof(tc));
    tc.ordermark = 0x36;
    tc.startalone_mask = ui->cB_task_eliminate_high->currentIndex() + 1;

    // 列表封装
    Pblic_Addorderlist((uchar*)&tc, sizeof(tc), "任务删除(算力平台) : "+ui->cB_task_eliminate_high->currentText());
}

// 任务清除
void sub1553_gkcontrol::on_pB_outdata_task_eliminate_clicked() {
    Outdate_task_clear otc;
    memset(&otc, 0, sizeof(otc));
    // 指令标识
    otc.ordermark = 0x37;
    otc.task_type = ui->cB_outdata_task_eliminate->currentIndex() + 1;
    otc.clear_type =ui->cB_outdata_task_clear->currentIndex() + 1;

    // 列表封装
    Pblic_Addorderlist((uchar*)&otc, sizeof(otc), "任务清除 : "+ui->cB_outdata_task_eliminate->currentText());
}

// 过时任务自动清除功能
void sub1553_gkcontrol::on_pB_outdata_task_autoeli_clicked() {
    Outdate_task_autoclear oac;
    memset(&oac, 0, sizeof(oac));
    oac.ordermark = 0x38;
    oac.autoclear_mask = ui->cB_outdata_task_autoeli->currentIndex() + 1;

    // 列表封装
    Pblic_Addorderlist((uchar*)&oac, sizeof(oac), "过时任务自动清除 : "+ui->cB_outdata_task_autoeli->currentText());
}


// Flash下传
void sub1553_gkcontrol::on_pB_softwate_download_clicked() {
    Flash_down str;
    memset(&str, 0, sizeof(str));

    // 指令标识
    str.ordermark = 0x3B;
    // 类型号
    str.type_num =ui->cB_downtrans->currentIndex()+1;
    // 单机标志
    str.pc_number =ui->comboBox_3B_1->currentIndex()+1;
    // Flash选择
    str.flash_ch =ui->comboBox__3B_2->currentIndex()+1;
    // 起始地址
    str.start_addr =toHex_uint(ui->lineEdit_3B_4->text());
    // 软件大小
    str.sorft_size =qToBigEndian(ui->lineEdit__3B_5->text().toUShort());
    // 数传通道
    str.data_ch =ui->comboBox__3B_6->currentIndex()+1;
    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "Flash下传 : "+ui->comboBox__3B_2->currentText());
}



// Flash下传--单机标志改变
void sub1553_gkcontrol::on_comboBox_3B_1_activated(int index)
{
    switch (index) {
    case 0:
        ui->comboBox__3B_2->clear();

        ui->comboBox__3B_2->addItem("1：P2020基础区");
        ui->comboBox__3B_2->addItem("2：P2020更新区A");
        ui->comboBox__3B_2->addItem("3：P2020更新区B");
        ui->comboBox__3B_2->addItem("4：P2020更新区C");
        ui->comboBox__3B_2->addItem("5：管控V7基础区");
        ui->comboBox__3B_2->addItem("6：管控V7更新区");
        ui->comboBox__3B_2->addItem("7：处理V7基础区");
        ui->comboBox__3B_2->addItem("8：处理V7更新区");
        ui->comboBox__3B_2->addItem("9：融合DSP基础区");
        ui->comboBox__3B_2->addItem("10：融合DSP更新区");
        ui->comboBox__3B_2->addItem("11：通侦定位DSP基础区");
        ui->comboBox__3B_2->addItem("12：通侦定位DSP更新区");
        ui->comboBox__3B_2->addItem("13：雷侦定位DSP基础区");
        ui->comboBox__3B_2->addItem("14：雷侦定位DSP更新区");
        ui->comboBox__3B_2->addItem("15：AI基础区");
        ui->comboBox__3B_2->addItem("16：AI更新区");
        ui->comboBox__3B_2->addItem("17：6Gb三模");
        ui->comboBox__3B_2->addItem("18：6Gb第1片2Gb");
        ui->comboBox__3B_2->addItem("19：6Gb第2片2Gb");
        ui->comboBox__3B_2->addItem("20：6Gb第3片2Gb");
        ui->comboBox__3B_2->addItem("21：融合DSP的引导区");
        ui->comboBox__3B_2->addItem("22：通侦定位DSP的引导区");
        ui->comboBox__3B_2->addItem("23：雷侦定位DSP的引导区");
        ui->comboBox__3B_2->addItem("24：AI的引导区");
        ui->comboBox__3B_2->addItem("25：MRAM FLASH分区表");
        ui->comboBox__3B_2->addItem("26：重点目标库");
        ui->comboBox__3B_2->addItem("27：重点通信信号");
        ui->comboBox__3B_2->addItem("28：雷达重点侦察库");

        ui->comboBox__3B_3->setEnabled(0);
        break;
    case 1:
    case 2:
        ui->comboBox__3B_2->clear();
        ui->comboBox__3B_2->addItem("1：Nor Flash1");
        ui->comboBox__3B_2->addItem("2: Nor Flash2");
        ui->comboBox__3B_2->addItem("3: Nand Flash");

        ui->comboBox__3B_3->setEnabled(1);
        break;
    default:
        break;
    }
}
//高温阈值设置 0x3D
void sub1553_gkcontrol::on_pB_0x3D_clicked()
{
    uchar str[3];
    memset(&str, 0, sizeof(str));

    // 指令标识
    str[0] = 0x3D;
    // 单机标志
    str[1] =ui->cB_0x3D_1->currentIndex();
    // 温度阈值
    str[2] =ui->lineEdit_0x3D_2->text().toInt();

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "高温阈值设置 : "+ui->cB_0x3D_1->currentText());
}

// 综合管控单元SSD文件删除  0x3E
void sub1553_gkcontrol::on_pB_controlmachine_file_check_clicked() {
    Controlmachine_file_delete cfd;
    memset(&cfd, 0, sizeof(cfd));
    cfd.ordermark = 0x3E;
    //文件节点
    QString tmpstr = ui->LineEdit_ssdfiledele->text();
    QByteArray ba = QByteArray::fromHex(tmpstr.toLatin1());
    char* arr = ba.data();
    tmpstr.replace(" ","");
    int strlen = (tmpstr.size()+1)/2;
    if(strlen>8)strlen=8;
    memcpy(&cfd.file_name[0], (uchar*)arr, strlen);
    //分区
    cfd.fq=ui->cB_ssdfiledele_2->currentIndex()+1;
    // 列表封装
    Pblic_Addorderlist((uchar*)&cfd, sizeof(cfd), "综合管控SSD文件删除 ");
}

// 管控机SSD文件回读下传0x3F
void sub1553_gkcontrol::on_pB_ssd_datadownload_clicked() {
    SSD_data_download sdd;
    memset(&sdd, 0, sizeof(sdd));
    // 指令标识
    sdd.ordermark = 0x3F;
    // 保留0xFF
    sdd.bl = 0xFF;
    // 文件名
    QString tmpstr = ui->LineEdit_0x3f_1->text();
    QByteArray ba = QByteArray::fromHex(tmpstr.toLatin1());
    char* arr = ba.data();
    int strlen =(tmpstr.size()+1)/2;
    if(strlen>8)strlen=8;
    memcpy(sdd.file_name, arr, strlen);
    // 偏移量
    sdd.py = qToBigEndian(ui->lineEdit_0x3f_2->text().toLongLong());
    // 数据总量
    sdd.dataSum = qToBigEndian(ui->lineEdit_0x3f_3->text().toLongLong());

    // 列表封装
    Pblic_Addorderlist((uchar*)&sdd, sizeof(sdd), "管控机SSD文件回读下传");
}

// 管控机CAN复位
void sub1553_gkcontrol::on_pB_controlmachine_can_reset_clicked() {
    ControlMachine_CAN_reset ccr;
    memset(&ccr, 0, sizeof(ccr));
    ccr.ordermark = 0x40;
    ccr.reset_choose = ui->cB_controlmachine_can_resetchoose->currentIndex()+1;

    // 列表封装
    Pblic_Addorderlist((uchar*)&ccr, sizeof(ccr), "管控机CAN复位 : "+ui->cB_controlmachine_can_resetchoose->currentText());
}

// 测试数传
void sub1553_gkcontrol::on_pB_test_numbertrans_clicked() {
    Test_num_trans tnt;
    memset(&tnt, 0, sizeof(tnt));
    // 指令标识
    tnt.ordermark = 0x41;
    // 单机标志
    tnt.startalone_mask = ui->cB_startalone_sign->currentIndex() + 1;
    // 处理模块标识
    ushort tmp = 0;
    tmp = ui->checkBox_csbit0->isChecked() +
            (ui->checkBox_csbit1->isChecked() << 1) +
            (ui->checkBox_csbit2->isChecked() << 2) +
            (ui->checkBox_csbit3->isChecked() << 3) +
            (ui->checkBox_csbit4->isChecked() << 4) +
            (ui->checkBox_csbit5->isChecked() << 5) +
            (ui->checkBox_csbit6->isChecked() << 6) +
            (ui->checkBox_csbit7->isChecked() << 7) +
            (ui->checkBox_csbit8->isChecked() << 8);

    tnt.handlemodel_sign = qToBigEndian(tmp);
    // 数据传输速率
    tnt.data_trans_rate =
            qToBigEndian(ui->LineEdit_data_trans_rate->text().toUShort());
    // 发送的帧数
    tnt.frame_num = qToBigEndian(ui->LineEdit_sendframe_num->text().toUInt());
    // 标志（仅对高算力平台有效）
    tnt.sign = ui->cB_test_numbertrans_sign->currentIndex() + 1;
    //卫星代码
    tnt.start_code=toHex_ushort(ui->lineEdit_41_startcode->text());
    // 保留
    tnt.bl = 0xff;
    // 列表封装
    Pblic_Addorderlist((uchar*)&tnt, sizeof(tnt), "测试数传");
}

// 下拉框改变控件显示
void sub1553_gkcontrol::on_cB_startalone_sign_currentIndexChanged(int index) {
    ui->checkBox_csbit0->setChecked(0);
    ui->checkBox_csbit1->setChecked(0);
    ui->checkBox_csbit2->setChecked(0);
    ui->checkBox_csbit3->setChecked(0);
    ui->checkBox_csbit4->setChecked(0);
    ui->checkBox_csbit5->setChecked(0);
    ui->checkBox_csbit6->setChecked(0);
    ui->checkBox_csbit7->setChecked(0);
    ui->checkBox_csbit8->setChecked(0);
    if (index == 0) {
        ui->checkBox_csbit0->setText("D0管控机p2020");
        ui->checkBox_csbit1->setText("D1管控机DSP6678_1");
        ui->checkBox_csbit2->setText("D2管控机DSP6678_2");
        ui->checkBox_csbit3->setText("D3管控机DSP6678_3");
        ui->checkBox_csbit4->setText("D4管控机AI");
        ui->checkBox_csbit5->setText("D5管控机综合管控模块-v7");

        ui->checkBox_csbit6->setVisible(false);
        ui->checkBox_csbit7->setVisible(false);
        ui->checkBox_csbit8->setVisible(false);
    } else {
        ui->checkBox_csbit0->setText("D0处理板1的FPGA1-V7");
        ui->checkBox_csbit1->setText("D1处理板1的FPGA2-V7");
        ui->checkBox_csbit2->setText("D2处理板1的DSP6678");
        ui->checkBox_csbit3->setText("D3数据处理板2的FPGA1-V7");
        ui->checkBox_csbit4->setText("D4数据处理板2的FPGA2-V7");
        ui->checkBox_csbit5->setText("D5数据处理板2的DSP6678");
        ui->checkBox_csbit6->setText("D6接口板的DSP6678");
        ui->checkBox_csbit7->setText("D7收发处理板FPGA-V7-1");
        ui->checkBox_csbit8->setText("D8收发处理板FPGA-V7-2");

        ui->checkBox_csbit6->setVisible(true);
        ui->checkBox_csbit7->setVisible(true);
        ui->checkBox_csbit8->setVisible(true);
    }
}

// 测试数传停止
void sub1553_gkcontrol::on_pB_teststop_clicked() {
    Test_num_stop tns;
    memset(&tns, 0, sizeof(tns));
    tns.ordermark = 0x42;
    tns.startalone_mask = ui->cB_teststop_startalone_sign->currentIndex() + 1;

    // 列表封装
    Pblic_Addorderlist((uchar*)&tns, sizeof(tns), "测试数传停止 : "+ui->cB_teststop_startalone_sign->currentText());
}


//上注配置
void sub1553_gkcontrol::on_pB_0x39_clicked()
{
    UP_set str;
    memset(&str, 0, sizeof(str));
    // 指令标识
    str.ordermark = 0x3A;
    //配置代号
    str.set_num=qToBigEndian(ui->lineEdit_0x39_2->text().toUShort());
    //起始地址
    str.str_addr=toHex_uint(ui->lineEdit_0x39_3->text());
    //配置大小
    str.set_size=ui->lineEdit_0x39_4->text().toInt();


    //配置内容最大40kb
    QString qFileList=ui->lineEdit_0x39_5->text();
    if(qFileList.isEmpty()){}
    else//不为空
    {
        QFileInfo infoFile(qFileList);
        if(infoFile.suffix()=="txt")
        {
            QString Str = "";
            uchar* sarbuff=new uchar[40960];
            memset(sarbuff,0,40960);

            QFile txt_file(qFileList);
            if(!(txt_file.open(QIODevice::ReadOnly|QIODevice::Text)))
            {
                QMessageBox::warning(this,tr("打开文件失败"),tr("路径")+qFileList);
                return ;
            }
            QTextStream txtInput(&txt_file);
            QString read_str;
            while (!txtInput.atEnd()) {
                read_str+=txtInput.readLine();
            }
            read_str.replace(" ","");
            read_str.replace("\n","");
            int this_len=(read_str.size() + 1) / 2;//当前文件数据长度

            QByteArray hex_data=QByteArray::fromHex(read_str.toLatin1());//将字节流转换位16进制,char型
            uchar* data_buf=(uchar*)hex_data.data();//获取地址

            if(this_len>40960)this_len=40960;
            memcpy(sarbuff,data_buf,this_len);

            int aa=sizeof (str.data);
            memset(str.data,0,aa);
            memcpy(str.data,sarbuff,this_len);
            delete [] sarbuff;

        }
        else {
            uchar* sarbuff=new uchar[40960];
            memset(sarbuff,0,40960);
            QFile* binFile = new QFile("");
            binFile->setFileName(qFileList);
            if (binFile->open(QFile::ReadOnly)) {
            }
            else {
            }

            binFile->read((char*)sarbuff,40960);  // 超过长度不读取，是默认值

            int aa=sizeof (str.data);
            memset(str.data,0,aa);
            memcpy(str.data,sarbuff,40960);
            delete [] sarbuff;
        }
    }

    //异或和校验 从指令标识至配置内容的校验
    str.crc=0;

    ushort* checkbuff=new ushort[sizeof(str)];
    memcpy(checkbuff,(uchar*)&str,sizeof(str));
    ushort crc2=0;
    for(uint n=0;n<(sizeof(str))/2-1;n++)
    {
        crc2+=crc2^checkbuff[n];
    }
    //strbusInstr.andcheck=qToBigEndian(crc2);
    str.crc=crc2;
    delete [] checkbuff;

    // 列表封装
    Pblic_Addorderlist((uchar*)&str, sizeof(str), "上注配置");
}
//上注配置选择配置文件
void sub1553_gkcontrol::on_pushButton_0x39chppsefile_clicked()
{
    //打开文件选择对话框
    //QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt;;*.bin;;*.dat"));
    QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt *.bin *.dat"));
    if(file_path.size() <= 0) return;
    ui->lineEdit_0x39_5->setText(file_path.at(0));

}
//停止当前执行的任务
void sub1553_gkcontrol::on_pB_stop0x39_clicked()
{
    str_39 trs;
    memset(&trs, 0, sizeof(trs));
    // 指令标识
    trs.ordermark = 0x39;
    //停止任务数量
    trs.stop_sum=ui->comboBox_stop0x39_1->currentIndex()+1;
    //任务流水号
    trs.mask_stream=qToBigEndian(ui->lineEdit_stop0x39_2->text().toUShort());
    //任务主UID
    trs.main_uid=qToBigEndian(ui->lineEdit_stop0x39_3->text().toUShort());
    // 列表封装
    Pblic_Addorderlist((uchar*)&trs, sizeof(trs), "停止当前执行的任务");
}
//管控任务数据下传0x32
void sub1553_gkcontrol::on_pB_0x32_clicked()
{
    str_32 trs;
    memset(&trs, 0, sizeof(trs));
    // 指令标识
    trs.ordermark = 0x32;
    //任务类型
    trs.task_kind=ui->cB_0x32_1->currentIndex()+1;
    if(ui->cB_0x32_1->currentIndex()==2)trs.task_kind=4;
    //数传通道
    trs.data_ch=ui->comboBox_0x32_2->currentIndex()+1;

    //保留
    // 列表封装
    Pblic_Addorderlist((uchar*)&trs, sizeof(trs), "管控任务数据下传");
}

//Flash下传--flash选择自动填写
void sub1553_gkcontrol::on_comboBox__3B_2_currentIndexChanged(const QString &arg1)
{
    QString str1,str2;

    if(arg1=="1:P2020基础区")              {str1="0x00000000";str2="8192";}
    else if(arg1=="2：P2020更新区A")        {str1="0x00000000";str2="8192";}
    else if(arg1=="3：P2020更新区B")        {str1="0x00000000";str2="8192";}
    else if(arg1=="4：P2020更新区C")        {str1="0x00000000";str2="8192";}
    else if(arg1=="5：管控V7更新区")        {str1="0x00000000";str2="32768";}
    else if(arg1=="6：管控V7基础区")        {str1="0x00000000";str2="32768";}
    else if(arg1=="7：处理V7基础区")        {str1="0x00000000";str2="32768";}
    else if(arg1=="8：处理V7更新区")        {str1="0x00000000";str2="32768";}
    else if(arg1=="9：融合DSP基础区")        {str1="0x00000000";str2="16384";}
    else if(arg1=="10：融合DSP更新区")        {str1="0x00000000";str2="16384";}
    else if(arg1=="11：通侦定位DSP基础区")        {str1="0x00000000";str2="16384";}
    else if(arg1=="12：通侦定位DSP更新区")        {str1="0x00000000";str2="16384";}
    else if(arg1=="13：雷侦定位DSP基础区")        {str1="0x00000000";str2="16384";}
    else if(arg1=="14：雷侦定位DSP更新区")        {str1="0x00000000";str2="16384";}
    else if(arg1=="15：AI基础区")        {str1="0x00000000";str2="0";}
    else if(arg1=="16：AI更新区")        {str1="0x00000000";str2="0";}
    else if(arg1=="17：6Gb三模")        {str1="0x00000000";str2="0";}
    else if(arg1=="18：6Gb第1片2Gb")        {str1="0x00000000";str2="0";}
    else if(arg1=="19：6Gb第2片2Gb")        {str1="0x00000000";str2="0";}
    else if(arg1=="20：6Gb第3片2Gb")        {str1="0x00000000";str2="0";}
    else if(arg1=="21：融合DSP的引导区")        {str1="0x00000000";str2="0";}
    else if(arg1=="22：通侦定位DSP的引导区")        {str1="0x00000000";str2="0";}
    else if(arg1=="23：雷侦定位DSP的引导区")        {str1="0x00000000";str2="0";}
    else if(arg1=="24：AI的引导区")        {str1="0x00000000";str2="0";}
    else if(arg1=="25： ")        {str1="0x00000000";str2="0";}
    else if(arg1=="26：重点目标库")        {str1="0x00000000";str2="0";}
    else if(arg1=="27：重点通信信号")        {str1="0x00000000";str2="0";}
    else if(arg1=="28：雷达重点侦察库")        {str1="0x00000000";str2="0";}

    else{str1="0x00000000";str2="0";};

    ui->lineEdit_3B_4->setText(str1);//起始地址
    ui->lineEdit__3B_5->setText(str2);//长度
}


//模板调用 0x3C
void sub1553_gkcontrol::on_pushButton_0x3C_clicked()
{
    str_3C trs;
    memset(&trs, 0, sizeof(trs));
    // 指令标识
    trs.ordermark = 0x3C;
    //流水号
    trs.streamID=qToBigEndian(ui->lineEdit_0x3c_1->text().toUShort());
    //起始时间
    trs.sTime=qToBigEndian(ui->lineEdit_0x3c_2->text().toUInt());
    //结束时间
    trs.eTime=qToBigEndian(ui->lineEdit_0x3c_3->text().toUInt());
    //保留

    // 列表封装
    Pblic_Addorderlist((uchar*)&trs, sizeof(trs), "模板调用 :流水号"+ui->lineEdit_0x3c_1->text());
}


