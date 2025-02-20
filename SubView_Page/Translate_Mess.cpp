#include "Translate_Mess.h"
#include "ui_Translate_Mess.h"


#define mB 0
#define mR 1

Translate::Translate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Translate)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭，子窗口也关闭设置
    Init_contrlData();


    //Modeview1=new QTextEdit(ui->textEdit_Trans1);
    Modeview1=ui->textEdit_Trans1;
    Modeview2=ui->textEdit_Trans2;
    Modeview3=ui->textEdit_Trans3;
    //Modeview1->showMaximized();
    //‌使用QFont设置字体样式‌：
    //可以通过QFont类来设置字体样式，包括字体名称、大小、加粗、斜体等：
    //    QFont font = QFont("Microsoft YaHei", 12);
    //    font.setBold(true);
    //    Modeview1->setFont(font);

    //    Modeview1->setStyleSheet("background-color:grey;");
    Modeview1->setStyleSheet("background:rgb(245,245,225);");
    Modeview2->setStyleSheet("background:rgb(245,245,225);");
    Modeview3->setStyleSheet("background:rgb(245,245,225);");
    //Modeview1->setStyleSheet("background-image:url(:/new/prefix1/Pic/aq1.jpg);");
    //Modeview2->setStyleSheet("background-image:url(:/new/prefix1/Pic/aq1.jpg);");
    //Modeview3->setStyleSheet("background-image:url(:/new/prefix1/Pic/aq1.jpg);");
    //    Modeview1->setStyleSheet("border-image:url(:/new/prefix1/Pic/aq1.jpg);");//拉伸图片


    QPalette palette;//调色器
    QBrush brush;
    brush.setColor(Qt::blue);
    Modeview1->setFont(QFont("Microsoft Yahei",9));
    Modeview2->setFont(QFont("Microsoft Yahei",9));
    Modeview3->setFont(QFont("Microsoft Yahei",9));
    palette.setBrush(QPalette::Text,brush);
    Modeview1->setPalette(palette);
    Modeview2->setPalette(palette);
    Modeview3->setPalette(palette);

    //设置添加的文本样式，添加的文字，字体颜色:蓝色，字体：“微软雅黑”，子图大小：16px
    //    QTextCharFormat textform;
    //    textform.setForeground(Qt::blue);
    //    textform.setFontFamily("微软雅黑");
    //    textform.setFontPointSize(8);

    //获取textEdit文本块中的光标位置（是文本光标，而不是鼠标光标）；
    //   QTextCursor cursorPosition = Modeview1->textCursor();
    //在默认的最后添加文字
    //    cursorPosition.insertText("fffffff",textform);
    //    //移动文本块中的光标位置到最前面，添加文本
    //    cursorPosition.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor);
    //    textform.setForeground(Qt::green);
    //    //在文本最前面 加入文本
    //    cursorPosition.insertText("LLLLLLL",textform);
    //    //移动鼠标在任意位置插入文本，移动4个字节
    //    cursorPosition.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,4);
    //    textform.setForeground(Qt::darkYellow);
    //    cursorPosition.insertText("ZZZZZZ",textform);
    //只读，可以复制 的
    Modeview1->setReadOnly(true);
    Modeview2->setReadOnly(true);
    Modeview3->setReadOnly(true);

}

Translate::~Translate()
{
    delete ui;
}

QString Translate::ChangeColor(QString str, int kind)
{
    QString  strC;
    // 设置文字（样式+内容）HTML格式
    //QString  str= "<font size=\"9\" color=\"red\"> 信息 </font>";
    switch (kind) {
    case 0:
        strC= QString("<font  color=\"black\">%1</font>").arg(str);
        break;
    case 1:
        strC= QString("<font  color=\"red\">%1</font>").arg(str);
        break;
    case 2:
        strC= QString("<font  color=\"blue\">%1</font>").arg(str);
        break;
    default:
        break;
    }

    return strC;
}

void Translate::Init_contrlData()
{
    //上注任务界面
    // 功能模式
    UP_fun_mode[1]="1:电子侦察";
    UP_fun_mode[2]="2:L频段电子干扰";
    UP_fun_mode[3]="3:SXKu频段电子干扰";
    UP_fun_mode[4]="4:SXKu频段天线定标";
    UP_fun_mode[5]="5:SAR探测";
    UP_fun_mode[6]="6:备用导航";
    UP_fun_mode[7]="7:L频段类5G";
    UP_fun_mode[8]="8:SXKu频段类5G";
    UP_fun_mode[9]="9:J链";
    UP_fun_mode[10]="10:扩展功能";
    // 工作模式
    // 电子侦察页
    UP_work_mode[1][1]="全景工作模式";
    UP_work_mode[1][2]="频点控守工作模式";
    UP_work_mode[1][3]="频点扫描工作模式";
    // L频段电子干扰
    UP_work_mode[2][1]="预置强制干扰工作模式";
    UP_work_mode[2][2]="自主侦察引导干扰工作模式";
    UP_work_mode[2][3]="星间/星地感知引导干扰工作模式";
    // SXKu频段电子干扰
    UP_work_mode[3][1]="预置强制干扰工作模式";
    UP_work_mode[3][2]="自主侦察引导干扰工作模式";
    UP_work_mode[3][3]="星间/星地感知引导干扰工作模式";
    //SXKu天线定标任务
    UP_work_mode[4][1]="SXKu频段天线发射定标模式";
    UP_work_mode[4][2]="SXKu频段天线接收定标模式";
    //SAR探测
    UP_work_mode[5][1]="广域搜索模式";
    UP_work_mode[5][2]="滑动聚束模式";
    UP_work_mode[5][3]="条带模式";
    UP_work_mode[5][4]="TOP模式";
    UP_work_mode[5][5]="SAR定标";
    //备用导航任务
    UP_work_mode[6][1]="备用导航工作模式";
    //L频段类5G
    UP_work_mode[7][1]="终端通信";
    UP_work_mode[7][2]="高速下传";
    UP_work_mode[7][3]="数据上注";
    UP_work_mode[7][4]="高速下传重传";
    //SXKu频段类5G
    UP_work_mode[8][1]="终端通信";
    UP_work_mode[8][2]="高速下传";
    UP_work_mode[8][3]="数据上注";
    UP_work_mode[8][4]="高速下传重传";
    //J链
    UP_work_mode[9][1]="数据链应用模式";

    //任务模式--对应各种任务类型===[功能模式][工作模式][任务模型类型]
    //电子侦察
    UP_work_tsak[1][1][1]=1;    //1：全景扫描
    UP_work_tsak[1][2][1]=2;    //1：常规信号频点控守
    UP_work_tsak[1][2][2]=3;    //2：Link16信号频点控
    UP_work_tsak[1][2][3]=4;    //3：塔康信号频点控守
    UP_work_tsak[1][2][4]=5;    //4：敌我识别信号频点控守
    UP_work_tsak[1][2][5]=6;    //5：铱星信号频点控守
    UP_work_tsak[1][2][6]=7;    //6：海事信号频点控守
    UP_work_tsak[1][2][7]=8;    //7：雷达信号频点控守
    UP_work_tsak[1][2][8]=9;    //8：星链信号频点控守
    UP_work_tsak[1][2][9]=10;    //9：同步采样
    UP_work_tsak[1][2][10]=11;   //10：上注软件解调
    UP_work_tsak[1][3][1]=12;    //1：雷达信号频点扫描

    //L频段电子干扰/SXKu频段电子干扰
    for (int i=2;i<4;i++) {
        UP_work_tsak[i][1][1]=13;    //1：多频点快速干扰
        UP_work_tsak[i][1][2]=14;    //2：等间隔梳状谱干扰
        UP_work_tsak[i][1][3]=15;    //3：非等间隔梳状谱干扰
        UP_work_tsak[i][1][4]=16;    //4：多通道快速协同干扰
        UP_work_tsak[i][1][5]=17;    //5：多通道多带宽协同干扰
        UP_work_tsak[i][1][6]=18;    //6：雷达强制干扰
        UP_work_tsak[i][2][1]=19;    //1：雷达自主侦察干扰
        UP_work_tsak[i][3][1]=20;    //1：星间/星地感知引导干扰
    }
    //SXKu频段天线定标
    UP_work_tsak[4][1][0]=0;    //
    UP_work_tsak[4][2][0]=0;    //
    //SAR探测
    UP_work_tsak[5][1][0]=0;    //
    UP_work_tsak[5][2][0]=0;    //
    UP_work_tsak[5][3][0]=0;    //
    UP_work_tsak[5][4][0]=0;    //
    UP_work_tsak[5][5][0]=0;    //

    //备用导航
    UP_work_tsak[6][1][1]=21;    //1：备用导航
    //L频段类5G/SXKu频段类5G
    for (int i=7;i<9;i++) {
        UP_work_tsak[i][1][1]=22;    //1：类5G
        UP_work_tsak[i][2][1]=22;    //1：类5G
        UP_work_tsak[i][3][1]=22;    //1：类5G
        UP_work_tsak[i][4][1]=22;    //1：类5G
    }
    //J链
    UP_work_tsak[9][1][1]=23;    //1：J链


}
//动态背景图片方法，widegt类
void Translate::gifGround()
{
    // 创建 QLabel 并将其设置为 Widget 的子控件
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height()); // 初始大小
    backgroundLabel->setScaledContents(true); // 让 QLabel 自动缩放内容

    // 加载用于背景的 GIF 文件
    backgroundMovie = new QMovie(":/new/prefix1/Pic/xc.gif");//这里替换为你的GIF文件地址即可

    // 将 QMovie 关联到 QLabel
    backgroundLabel->setMovie(backgroundMovie);

    // 设置 QLabel 为透明背景
    backgroundLabel->setAttribute(Qt::WA_TranslucentBackground, true);

    // 设置 QLabel 在布局的最底层
    backgroundLabel->lower();

    // 开始播放背景 GIF 动画
    backgroundMovie->start();

    // 调整背景大小，使其始终填满窗口
    connect(backgroundMovie, &QMovie::frameChanged, this, [=]() {
        // 计算缩放后的尺寸
        QPixmap scaledPixmap = backgroundMovie->currentPixmap().scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        backgroundLabel->setPixmap(scaledPixmap);
    });

    // 创建用于 ui->lab_icon 的 QMovie 并加载 GIF 动图
    //    iconMovie = new QMovie(":/imgs/a.gif");

    //    // 设置 QLabel 的 QMovie
    //    ui->lab_icon->setMovie(iconMovie);

    //    // 启动动画
    //    iconMovie->start();

    //    connect(iconMovie, &QMovie::frameChanged, this, [=]() {
    //        // 获取当前帧并缩放
    //        QImage currentImage = iconMovie->currentImage(); // 获取当前帧
    //        QPixmap pixmap = QPixmap::fromImage(currentImage.scaled(ui->lab_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //        ui->lab_icon->setPixmap(pixmap); // 设置 QLabel 的 pixmap
    //    });

    //    iconMovie->stop();
}



//指令翻译
void Translate::Trans_to_Oder(const QVariant varData)
{
    Order_List_Object rec_data = varData.value<Order_List_Object>();
    if(rec_data.page_id==0)return;
    Modeview1->clear();
    Modeview2->clear();
    Modeview3->clear();
    Modeview2->setVisible(0);
    Modeview3->setVisible(0);
    int kind=rec_data.page_id;
    //指令名称
    QString s="指令名称 :  [ "+rec_data.order_name+" ]";
    Modeview1->append(ChangeColor(s,mR));

    switch (kind)
    {
    case 3://管控指令（一）
        Gkcontrol1(varData);
        break;
    case 11://上注任务指令页面号
        Tran_UpTask(varData);
        break;
    default:
        Modeview1->append("未解析");
        break;
    }

}

//管控指令1界面
void Translate::Gkcontrol1(QVariant varData)
{
    Order_List_Object rec_data = varData.value<Order_List_Object>();
//    QString str_oder;
//    for (int i=0;i<rec_data.order_len;i++) {
//        str_oder+=QString("%1 ").arg(rec_data.data_buf[i],2,16,QLatin1Char('0'));
//    }
//    ui->textEdit_Trans1->setText(str_oder);
    uchar* buff=rec_data.data_buf;
    QString name=rec_data.order_name;
    if(name.contains("任务执行设置"))
    {
        Gkcontrol1_rwzx(buff);
    }
    else
    {
        ui->textEdit_Trans1->setText("未识别管控指令");
    }
}

//上注任务指令
void Translate::Tran_UpTask(QVariant varData)
{
    Order_List_Object rec_data = varData.value<Order_List_Object>();
    QString str_oder;
    //    for (int i=0;i<rec_data.order_len;i++) {
    //        str_oder+=QString("%1 ").arg(rec_data.data_buf[i],2,16,QLatin1Char('0'));
    //    }
    //    ui->textEdit_Trans1->setText(str_oder);
    uchar* buff=rec_data.data_buf;
    TaskContent str1;
    memset(&str1,0,sizeof (TaskContent));
    memcpy(&str1,buff+10,sizeof (TaskContent));//跳过 任务包总长度， 任务数量 ，保留
    memset(&Glob_Head,0,sizeof (TaskContent));
    memcpy(&Glob_Head,buff+10,sizeof (TaskContent));//公共拷贝，后续判断会用到

    ///////任务内容引导头
    // 任务流水号
    str_oder=ChangeColor("任务流水号: ",mB)+QString::number(qToBigEndian(str1.taskflowid));
    Modeview1->append(str_oder);
    // 主任务id
    str_oder=ChangeColor("主任务ID: ",mB)+QString::number(qToBigEndian(str1.main_id));
    Modeview1->append(str_oder);
    // 子任务id
    str_oder=ChangeColor("子任务ID: ",mB)+QString::number(str1.sub_id);
    Modeview1->append(str_oder);
    // 卫星代码
    str_oder=ChangeColor("卫星代码(16进制): ",mB)+QString("0x%1").arg(str1.start_code,4,16,QLatin1Char('0'));
    Modeview1->append(str_oder);
    // 主从标志
    str_oder=ChangeColor("主从标志: ",mB);
    switch (str1.mainsub_choose) {
    case 0:
        str_oder+="0:从星";
        break;
    case 1:
        str_oder+="1:主星";
        break;
    case 0xFF:
        str_oder+="2:无效0xFF";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.mainsub_choose);
        break;
    }
    Modeview1->append(str_oder);
    // 协同卫星数量
    str_oder=ChangeColor("协同卫星数量: ",mB)+QString::number(str1.start_sum);
    Modeview1->append(str_oder);
    // 功能模式
    if(str1.fun_mode>9)str_oder=ChangeColor("功能模式: ",mB)+ChangeColor("错误",mR);
    else str_oder=ChangeColor("功能模式: ",mB)+UP_fun_mode[str1.fun_mode];
    Modeview1->append(str_oder);
    // 工作模式
    if(str1.fun_mode>9 || str1.work_mode >5)str_oder=ChangeColor("工作模式: ",mB)+ChangeColor("错误",mR);
    else str_oder=ChangeColor("工作模式: ",mB)+UP_work_mode[str1.fun_mode][str1.work_mode];
    Modeview1->append(str_oder);
    // 任务类型
    str_oder=ChangeColor("任务类型: ",mB);
    switch (str1.tasktype) {
    case 1:
        str_oder+="1:运维管控任务(0-9999)";
        break;
    case 2:
        str_oder+="2:自主区域任务(10000-19999)";
        break;
    case 3:
        str_oder+="3:常规任务(20000-65535)";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.tasktype);
        break;
    }
    Modeview1->append(str_oder);
    // 任务个数
    str_oder=ChangeColor("任务个数: ",mB)+QString::number(str1.tasksum);
    Modeview1->append(str_oder);
    // 模板标志
    str_oder=ChangeColor("模板标志: ",mB);
    switch (str1.mb_mask) {
    case 1:
        str_oder+="1:模板";
        break;
    case 2:
        str_oder+="2:非模板";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.mb_mask);
        break;
    }
    Modeview1->append(str_oder);
    // 保留
    // 任务开始时刻
    str_oder=ChangeColor("任务开始时刻: ",mB)+QString::number(qToBigEndian(str1.task_starttime));
    Modeview1->append(str_oder);
    // 任务持续时长
    str_oder=ChangeColor("任务持续时长: ",mB)+QString::number(qToBigEndian(str1.task_holdtime));
    Modeview1->append(str_oder);

    ////////通用任务基本信息
    // 高算力平台选择
    str_oder=ChangeColor("高算力平台选择: ",mB);
    switch (str1.Gener_str.gsl_choose) {
    case 0:
        str_oder+="0:高算力1";
        break;
    case 1:
        str_oder+="1:高算力2";
        break;
    case 2:
        str_oder+="2:高算力1和2";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.gsl_choose);
        break;
    }
    Modeview1->append(str_oder);
    // 高算力主从选择
    str_oder=ChangeColor("高算力主从选择: ",mB);
    switch (str1.Gener_str.gsl_mainsub) {
    case 0:
        str_oder+="0:主";
        break;
    case 1:
        str_oder+="1:从";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.gsl_mainsub);
        break;
    }
    Modeview1->append(str_oder);
    // 频段选择
    str_oder=ChangeColor("频段选择: ",mB);
    switch (str1.Gener_str.pd_choose) {
    case 0:
        str_oder+="0:L频段";
        break;
    case 1:
        str_oder+="1:SXKu频段";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.pd_choose);
        break;
    }
    Modeview1->append(str_oder);
    //数传标志 Bit7-Bit4：一 ，
    str_oder=ChangeColor("数传标志_平台: ",mB);
    switch ((str1.Gener_str.data_choose&0xF0)>>4) {
    case 0:
        str_oder+="0:平台固存";
        break;
    case 1:
        str_oder+="1:载荷SSD";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.pd_choose);
        break;
    }
    Modeview1->append(str_oder);
    //Bit3-Bit0：二
    str_oder=ChangeColor("数传标志_存储: ",mB);
    switch (str1.Gener_str.data_choose&0x0F) {
    case 0:
        str_oder+="0:处理版数据不存储";
        break;
    case 1:
        str_oder+="1:处理版数据存储";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.pd_choose);
        break;
    }
    Modeview1->append(str_oder);

    // 数传传输速率
    str_oder=ChangeColor("数据传输速率Mbps: ",mB)+QString::number(qToBigEndian(str1.Gener_str.data_speed));
    Modeview1->append(str_oder);

    // 内校正输出通道
    str_oder=ChangeColor("内校正输出通道: ",mB);
    switch (str1.Gener_str.inch_choose) {
    case 0:
        str_oder+="0:4通道";
        break;
    case 1:
        str_oder+="1:5通道";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.inch_choose);
        break;
    }
    Modeview1->append(str_oder);
    // DA输出幅度衰减值
    str_oder=ChangeColor("DA输出幅度衰减值: ",mB)+QString::number(str1.Gener_str.DA_dbm);
    Modeview1->append(str_oder);
    // 保留3字节
    // 中频切换开关状态
    str_oder=ChangeColor("中频切换开关状态: ",mB);
    switch (str1.Gener_str.zp_change) {
    case 0:
        str_oder+="0:L-高算力1,SXKu-高算力2";
        break;
    case 1:
        str_oder+="1:同时L接收模式(仅接收)";
        break;
    case 2:
        str_oder+="2:同时SXKu接收模式(仅接收)";
        break;
    case 3:
        str_oder+="3:L-高算力2,SXKu-高算力1";
        break;
    default:
        str_oder+="未知:"+QString::number(str1.Gener_str.zp_change);
        break;
    }
    Modeview1->append(str_oder);
    // 收发FPGA_1(0x)
    str_oder=ChangeColor("收发FPGA_1: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.sf_fpga1),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 收发FPGA_2
    str_oder=ChangeColor("收发FPGA_2: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.sf_fpga2),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 数据处理板AFPGA_1
    str_oder=ChangeColor("处理板AFPGA_1: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.dataA_fpga1),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 数据处理板AFPGA_2
    str_oder=ChangeColor("处理板AFPGA_2: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.dataA_fpga2),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 数据处理板Adsp
    str_oder=ChangeColor("处理板Adsp: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.dataA_dsp),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 数据处理板BFPGA_1
    str_oder=ChangeColor("处理板BFPGA_1: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.dataB_fpga1),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 数据处理板BFPGA_2
    str_oder=ChangeColor("处理板BFPGA_2: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.dataB_fpga2),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);
    // 数据处理板Bdsp
    str_oder=ChangeColor("处理板Bdsp: ",mB)+QString("0x%1").arg(qToBigEndian(str1.Gener_str.dataB_dsp),4,16,QLatin1Char('0')).toUpper();
    Modeview1->append(str_oder);


    //(任务基本信息变长部分)功能模式区分类型
    uchar* buff2=new uchar[rec_data.order_len];
    int len2=10+sizeof (TaskContent); //总头10+通用基本信息TaskContent

    memset(buff2,0,rec_data.order_len);
    memcpy(buff2,buff+len2,rec_data.order_len-len2);//跳过定长
    //    str_oder="调试输出功能模式变长字节：";
    //    for (int i=0;i<rec_data.order_len;i++) {
    //        str_oder+=QString("%1 ").arg(buff2[i],2,16,QLatin1Char('0'));
    //    }
    //    ui->textEdit_Trans1->setText(str_oder);

    // 功能模式
    uint mode_Len=0;
    Modeview2->setVisible(1);
    Modeview3->setVisible(1);
    switch (str1.fun_mode)
    {
    case 1:  // 电子侦察任务
        mode_Len=Trans_Elec_ReconData(buff2);
        break;
    case 2:  // 电子干扰任务
    case 3:
        mode_Len=Trans_Elec_GrData(buff2);
        break;

    case 4: //SXKu天线定标任务
        Modeview2->append("未解析 SXKu天线定标任务");
        //return;
        break;
    case 5: //SAR探测任务基本信息
        mode_Len=Trans_SAR_probing(buff2);
        //Modeview3->setVisible(0);//显示读取文件信息
        break;
    case 6://备用导航任务
        Modeview2->append("未解析 备用导航任务");
        //return;
        break;
    case 7:
    case 8://类5G
        mode_Len=Trans_5G_kind(buff2);

        //return;
        break;
    case 9://J链
        Modeview2->append("未解析 J链");
        //return;
        break;
    default:  // 其余待定默认电子侦察任
        Modeview2->append("功能模式 未知类型");
        //return;
        break;
    }

    //任务模式参数
    uchar* buff3=new uchar[rec_data.order_len];
    int len3=10+sizeof (TaskContent)+mode_Len; //总头10+通用基本信息TaskContent+ 变长模式参数

    memset(buff3,0,rec_data.order_len);
    memcpy(buff3,buff+len3,rec_data.order_len-len3);//跳过定长
    //    str_oder="调试输出任务模式变长字节：";
    //    for (int i=0;i<rec_data.order_len;i++) {
    //        str_oder+=QString("%1 ").arg(buff3[i],2,16,QLatin1Char('0'));
    //    }
    //    ui->textEdit_Trans1->setText(str_oder);

    if(str1.fun_mode==5)//SAR任务没有第二个界面
    {
        //第3个界面，文件读取
        QString ss2="参数====SAR文件读取内容:";
        Modeview3->append(ChangeColor(ss2,mR));


        int need_data=rec_data.order_len-len3-2;//截取实际长度（最后有2字节校验）
        str_oder=QString("共%1字节:").arg(need_data);
        Modeview3->append(str_oder);
        str_oder="";
        for (int i=0;i<need_data;i++) {
            str_oder+=QString("%1 ").arg(buff3[i],2,16,QLatin1Char('0'));
        }
        Modeview3->append(str_oder);
        return ;//跳过第二个界面输出
    }
    // 任务模式参数（第二个界面）。。。。。。。。。。。。。。。。。。
    Task_ModeParameter str_Task;
    memset(&str_Task, 0, sizeof(Task_ModeParameter));
    memcpy(&str_Task,buff3,sizeof (Task_ModeParameter));
    // 任务执行fpga选择
    str_oder=ChangeColor("任务执行fpga选择: ",mB);
    if(str_Task.task_fpgachoose&0x01)str_oder+=" 数据板1的FPGA_1,";
    if(str_Task.task_fpgachoose&0x02)str_oder+=" 数据板1的FPGA_2,";
    if(str_Task.task_fpgachoose&0x04)str_oder+=" 数据板2的FPGA_1,";
    if(str_Task.task_fpgachoose&0x08)str_oder+=" 数据板2的FPGA_2";
    Modeview3->append(str_oder);
    // 单星定位标志
    str_oder=ChangeColor("定位标志: ",mB);
    switch (str_Task.dx_marsk) {
    case 0:
        str_oder+="0:不做定位";
        break;
    case 1:
        str_oder+="1:做单星定位";
        break;
    case 2:
        str_oder+="2:做三星定位";
        break;
    case 3:
        str_oder+="3:做四星定位";
        break;
    default:
        str_oder+="未知:"+QString::number(str_Task.dx_marsk);
        break;
    }
    Modeview3->append(str_oder);
    // bit7-bit4,融合标志  bit3-bit0,AI识别标志
    str_oder=ChangeColor("融合标志: ",mB)+(str_Task.RH_AI_mask&0xF0 ? "1:融合":"0:不融合");
    Modeview3->append(str_oder);
    str_oder=ChangeColor("AI识别标志: ",mB)+(str_Task.RH_AI_mask&0x0F ? "1:做AI识别":"0:不做AI识别");
    Modeview3->append(str_oder);
    // 三星定位主星地址12.1.1.165
    str_oder=ChangeColor("三星定位主星地址: ",mB);
    str_oder+=QString("%1. %2. %3. %4").arg(str_Task.third_site[0]).arg(str_Task.third_site[1])
            .arg(str_Task.third_site[2]).arg(str_Task.third_site[3]);
    Modeview3->append(str_oder);
    // 三星定位主星基地址
    str_oder=ChangeColor("三星定位主星基地址: ",mB)+QString("0x%1").arg(qToBigEndian(str_Task.third_base_site),4,16,QLatin1Char('0')).toUpper();
    Modeview3->append(str_oder);
    // 多星定位工作模式
    str_oder=ChangeColor("多星定位工作模式: ",mB);
    switch (str_Task.start_mode) {
    case 1:
        str_oder+="1:独立工作";
        break;
    case 2:
        str_oder+="2:引导工作";
        break;
    case 3:
        str_oder+="3:强制采样";
        break;
    default:
        str_oder+="未知:"+QString::number(str_Task.start_mode);
        break;
    }
    Modeview3->append(str_oder);
    // 定位参数卫星个数0-3
    str_oder=ChangeColor("定位参数卫星个数: ",mB)+QString::number(str_Task.satelliteSum);
    Modeview3->append(str_oder);
    int dw_len=str_Task.satelliteSum*4;
    if(str_Task.satelliteSum>3)dw_len=0;
    //引导参数卫星个数0-20
    uchar yd_cnt=0;
    memcpy(&yd_cnt,buff3+sizeof (str_Task)+dw_len,1);
    str_oder=ChangeColor("引导参数卫星个数: ",mB)+QString::number(yd_cnt);
    Modeview3->append(str_oder);
    int yd_len=yd_cnt*5;
    if(str_Task.satelliteSum>20)yd_len=0;

    //任务模式类型
    uchar task_Mode=0;
    int mode_flg=sizeof (str_Task)+1+dw_len+yd_len;//偏移至类型字节
    memcpy(&task_Mode,buff3+mode_flg,1);

    int tmp=UP_work_tsak[str1.fun_mode][str1.work_mode][task_Mode];
    switch (tmp) {
    case 1:// 全景模式
        Modeview3->append(ChangeColor("任务模式类型====[全景模式]",mR));
        mode_qj(buff3+mode_flg+1);
        break;
    case 2:// 常规信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[常规信号频点控守]",mR));
        mode_cgxhpdks_2(buff3+mode_flg+1);
        break;
    case 3:// Link16信号频点控守参数
        Modeview3->append(ChangeColor("任务模式类型====[Link16信号频点控守]",mR));
        mode_linkpdks_3(buff3+mode_flg+1);
        break;
    case 4:// 塔康信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[塔康信号频点控守]",mR));
        mode_tkxhpdks_4(buff3+mode_flg+1);
        break;
    case 5:// 敌我识别信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[敌我识别信号频点控守]",mR));
        mode_dwsbxh_5(buff3+mode_flg+1);
        break;
    case 6:// 铱星信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[铱星信号频点控守]",mR));
        mode_yxxhpdks_6(buff3+mode_flg+1);
        break;
    case 7:// 海事信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[海事信号频点控守]",mR));
        mode_hsxhpdks_7(buff3+mode_flg+1);
        break;
    case 8:// 雷达信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[雷达信号频点控守]",mR));
        mode_ldxhpdks_8(buff3+mode_flg+1);
        break;
    case 9:// 星链信号频点控守
        Modeview3->append(ChangeColor("任务模式类型====[星链信号频点控守]",mR));
        mode_xlxhpdks_9(buff3+mode_flg+1);
        break;
    case 10:// 同步采样
        Modeview3->append(ChangeColor("任务模式类型====[同步采样]",mR));
        mode_tbcy_18(buff3+mode_flg+1);
        break;
    case 11:// 上注软件解调
        Modeview3->append(ChangeColor("任务模式类型====[上注软件解调]",mR));
        mode_up_sorft_20(buff3+mode_flg+1);
        break;
    case 12:// 雷达信号频点扫描
        Modeview3->append(ChangeColor("任务模式类型====[雷达信号频点扫描]",mR));
        mode_ldxhpdsmT_11(buff3+mode_flg+1);
        break;
    case 13://多频点快速干扰
        Modeview3->append(ChangeColor("任务模式类型====[多频点快速干扰]",mR));
        mode_spgr_13(buff3+mode_flg+1);
        break;
    case 14://等间隔梳状谱干扰
        Modeview3->append(ChangeColor("任务模式类型====[等间隔梳状谱干扰]",mR));
        mode_szpgr_14(buff3+mode_flg+1);
        break;
    case 15:// 非等间隔梳状谱干扰
        Modeview3->append(ChangeColor("任务模式类型====[非等间隔梳状谱干扰]",mR));
        mode_not_szpgr_15(buff3+mode_flg+1);
        break;
    case 16:// 多通道快速协同干扰
        Modeview3->append(ChangeColor("任务模式类型====[多通道快速协同干扰]",mR));
        mode_dhmbgr_T16(buff3+mode_flg+1);
        break;
    case 17://多通道多带宽协同干扰
        Modeview3->append(ChangeColor("任务模式类型====[多通道多带宽协同干扰]",mR));
        mode_xlmbgr_T17(buff3+mode_flg+1);
        break;
    case 18://雷达强制干扰
        Modeview3->append(ChangeColor("任务模式类型====[雷达强制干扰]",mR));
        mode_LD_QZgr18(buff3+mode_flg+1);
        break;
    case 19://雷达侦察干扰
        Modeview3->append(ChangeColor("任务模式类型====[雷达侦察干扰]",mR));
        mode_LD_T19(buff3+mode_flg+1);
        break;
    case 22://类5G模式参数
        Modeview3->append(ChangeColor("任务模式类型====[类5G模式参数]",mR));
        mode_L5G_T22(buff3+mode_flg+1);
        break;
    default:
        Modeview3->append(ChangeColor("任务模式类型====未解析",mR));
        break;
    }


    delete [] buff2;
    delete [] buff3;
    return;
}

//电子侦察任务
uint Translate::Trans_Elec_ReconData(uchar *data)
{
    int Sum_Len=0;
    Elec_Recon str;
    memset(&str,0,sizeof (Elec_Recon));
    memcpy(&str,data,sizeof (Elec_Recon));
    QString str_oder;

    //下拉内容
    map<int,QString>clb;
    clb[0]="0:表示关闭接收通道";
    clb[1]="1:表示发送的Link16数据";
    clb[2]="2:表示发送的Tacan数据";
    clb[2]="3:错误3";
    clb[4]="4:表示发送通道测试数据";
    clb[5]="5:表示发送IFF数据";
    clb[6]="6:表示发送NCO1雷达数据";
    clb[7]="7:表示发送NCO2雷达数据";
    clb[8]="8:表示发送卫通数据";
    clb[9]="9:表示发送通道0数据";
    clb[10]="10:表示发送通道1数据";
    clb[11]="11:表示发送通道2数据";
    clb[12]="12:表示发送通道3数据";
    clb[13]="13:错误13";
    clb[14]="14:错误14";
    clb[15]="15:表示保留原状态（默认)";


    QString ss="功能模式信息====("+UP_fun_mode[Glob_Head.fun_mode]+")";
    Modeview2->append(ChangeColor(ss,mR));

    // 数据通道流向
    //--处理板1的FPGA_1
    ushort tmp_ushort=qToBigEndian(str.datastrim);
    str_oder=ChangeColor("处理板1的FPGA_1: ",mB)+clb[(tmp_ushort&0xF000)>>12];
    Modeview2->append(str_oder);
    //--处理板1的FPGA_2
    str_oder=ChangeColor("处理板1的FPGA_2: ",mB)+clb[(tmp_ushort&0x0F00)>>8];
    Modeview2->append(str_oder);
    //--处理板2的FPGA_1
    str_oder=ChangeColor("处理板2的FPGA_1: ",mB)+clb[(tmp_ushort&0x00F0)>>4];
    Modeview2->append(str_oder);
    //--处理板2的FPGA_2
    str_oder=ChangeColor("处理板2的FPGA_2: ",mB)+clb[tmp_ushort&0x000F];
    Modeview2->append(str_oder);

    // 限速速率
    str_oder=ChangeColor("限速速率(500Mbps): ",mB)+QString::number(str.limitspeed);
    Modeview2->append(str_oder);
    // 本振选择方式 L频段无效0，sxku有效1
    if(Glob_Head.Gener_str.pd_choose==1)
    {
        str_oder=ChangeColor("本振选择方式: ",mB)+(str.bz_choose ? "1:共本振":"0:独立本振");
        Modeview2->append(str_oder);
    }
    // 天线与通道对应模式
    str_oder=ChangeColor("天线与通道对应模式: ",mB);
    switch (str.aerial_ad) {
    case 1:
        str_oder+="1:天线子阵1234对应通道1234";
        break;
    case 2:
        str_oder+="2:天线子阵1234对应通道1256";
        break;
    case 3:
        str_oder+="3:天线子阵1234对应通道3456";
        break;
    default:
        str_oder+="未知:"+QString::number(str.aerial_ad);
        break;
    }
    Modeview2->append(str_oder);
    // 一本振使用信息

    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

    }else//sku频段
    {
        str_oder=ChangeColor("一本振使用信息: ",mB);
        switch (str.bz1_mess&0x01) {
        case 0:
            str_oder+="宽带一本振1";
            break;
        case 1:
            str_oder+="宽带一本振2";
            break;
        default:
            str_oder+="未知:"+QString::number(str.bz1_mess);
            break;
        }
        if(str.bz_choose==0)//独立本振
        {
            switch ((str.bz1_mess&0x02)>>1) {
            case 0:
                str_oder+=" ,组2:一本振1";
                break;
            case 1:
                str_oder+=" ,组2:一本振2";
                break;
            default:
                str_oder+=" ,未知:"+QString::number(str.bz1_mess);
                break;
            }
        }
        Modeview2->append(str_oder);
    }
    // 射频通道号
    str_oder=ChangeColor("射频通道号: ",mB);
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {
        switch (str.sp_ad[0]) {
        case 0:
            str_oder+="组1:通拨";
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            str_oder+="组1:通道"+QString::number(str.sp_ad[0]);
            break;
        default:
            str_oder+="未知:"+QString::number(str.sp_ad[0]);
            break;
        }
    }
    else//sku频段
    {
        switch (str.sp_ad[0]) {
        case 0:
            str_oder+="组1:通拨";
            break;
        case 1:
            str_oder+="组1:通道1和2";
            break;
        case 2:
            str_oder+="组1:通道3和4";
            break;
        case 3:
            str_oder+="组1:通道5和6";
            break;
        default:
            str_oder+="未知:"+QString::number(str.sp_ad[0]);
            break;
        }
        if(str.bz_choose==0)//独立本振
        {
            switch (str.sp_ad[1]) {
            case 0:
                str_oder+=" ,组2:通拨";
                break;
            case 1:
                str_oder+=" ,组2:通道1和2";
                break;
            case 2:
                str_oder+=" ,组2:通道3和4";
                break;
            case 3:
                str_oder+=" ,组2:通道5和6";
                break;
            case 0xFF:
                str_oder+=" ,组2:无效0xFF";
                break;
            default:
                str_oder+=" ,未知:"+QString::number(str.sp_ad[1]);
                break;
            }
        }
    }
    Modeview2->append(str_oder);
    // 射频通道参数设置
    str_oder=ChangeColor("射频通道参数设置: ",mB);
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {
        if(str.sp_addata[0]&0x01)str_oder+=" GSM选通陷波器使能;";
        if(str.sp_addata[0]&0x02)str_oder+=" 一级放大器使能;";
        if(str.sp_addata[0]&0x04)str_oder+=" 二级放大器使能;";
        if(str.sp_addata[0]&0x08)str_oder+=" 三级放大器使能;";
    }else//sku频段
    {

        if(str.sp_addata[0]&0x01)str_oder+="一级放大器使能;";
        switch ((str.sp_addata[0]&0x06)>>1) {
        case 0:
            str_oder+=" 组1:射频衰减0dB";
            break;
        case 1:
            str_oder+=" 组1:射频衰减10dB";
            break;
        case 2:
            str_oder+=" 组1:射频衰减20dB";
            break;
        default:
            str_oder+=" 未知:"+QString::number((str.sp_addata[0]&0x06)>>1);
            break;
        }
        if(str.bz_choose==0)//独立本振
        {
            if(str.sp_addata[1]&0x01)str_oder+=" ,组2:一级放大器使能;";
            switch ((str.sp_addata[1]&0x06)>>1) {
            case 0:
                str_oder+=" ,组2:射频衰减0dB";
                break;
            case 1:
                str_oder+=" ,组2:射频衰减10dB";
                break;
            case 2:
                str_oder+=" ,组2:射频衰减20dB";
                break;
            default:
                str_oder+="未知:"+QString::number((str.sp_addata[1]&0x06)>>1);
                break;
            }
        }
    }
    Modeview2->append(str_oder);
    // 射频通道接收衰减
    str_oder=ChangeColor("射频通道接收衰减(dB): ",mB)+QString::number(str.sp_adlow[0])+"dB";
    if(str.bz_choose==0)//独立本振
    {
        str_oder+=" ,组2:"+QString::number(str.sp_adlow[1])+"dB";
    }
    Modeview2->append(str_oder);
    // 天线子阵参数
    str_oder=ChangeColor("天线子阵参数: ",mB)+((str.aerial_patameter&0x80) ? "1:子阵指向一致":"0:子阵指向不一致");
    str_oder+=" 选择:";
    if(str.aerial_patameter&0x01)str_oder+=" 子阵1;";
    if(str.aerial_patameter&0x02)str_oder+=" 子阵2;";
    if(str.aerial_patameter&0x04)str_oder+=" 子阵3;";
    if(str.aerial_patameter&0x08)str_oder+=" 子阵4;";
    Modeview2->append(str_oder);
    //---天线使用方式

    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

        str_oder=ChangeColor("天线使用方式: ",mB);
        switch ((str.aerial_patameter&0x60)>>5) {
        case 0:
            str_oder+="0:独立孔径";
            break;
        case 1:
            str_oder+="1:合成孔径";
            break;
        case 2:
            str_oder+="2:双孔径";
            break;
        default:
            str_oder+="未知:"+QString::number((str.aerial_patameter&0x60)>>5);
            break;
        }
        Modeview2->append(str_oder);
    }
    else//sku频段
    {
        str_oder=ChangeColor("子阵1、3的天线使用方式: ",mB)+
                ((str.aerial_patameter&0x20) ? "1:启用V极化合成":"0:不启用V极化合成");
        Modeview2->append(str_oder);
        str_oder=ChangeColor("子阵2、4的天线使用方式: ",mB)+
                ((str.aerial_patameter&0x40) ? "1:启用H极化合成":"0:不启用H极化合成");
        Modeview2->append(str_oder);

    }
    // 天线控制间隔时间
    if(str.aerial_time!=0)
    {
        str_oder=ChangeColor("天线控制间隔时间: ",mB)+QString::number(str.aerial_time);
        Modeview2->append(str_oder);
    }
    // 天线指向算法数据源
    str_oder=ChangeColor("天线指向算法数据源: ",mB)+((str.aerial_data) ? "1:GPS数据源":"0:外推数据源");
    Modeview2->append(str_oder);
    //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值
    str_oder=ChangeColor("天线接收衰减值: ",mB);
    switch ((str.aerial_low&0xC0)>>6) {
    case 0:
        str_oder+="0:0dB";
        break;
    case 1:
        str_oder+="1:10dB";
        break;
    case 2:
        str_oder+="2:20dB";
        break;
    case 3:
        str_oder+="3:30dB";
        break;
    default:
        str_oder+="未知:"+QString::number((str.aerial_low&0xC0)>>6);
        break;
    }
    Modeview2->append(str_oder);
    //开关矩阵选择7.11
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

        str_oder=ChangeColor("开关矩阵选择: ",mB);
        switch (str.switch_Choose) {
        case 0x10:
            str_oder+="0x10:各子阵关闭6行6列";
            break;
        case 0x11:
            str_oder+="0x11:各子阵关闭4行4列";
            break;
        case 0x12:
            str_oder+="0x12:各子阵关闭4行6列";
            break;
        case 0xFF:
            str_oder+="0xFF:无效";
            break;
        default:
            str_oder+="未知:"+QString::number(str.switch_Choose);
            break;
        }
        Modeview2->append(str_oder);
    }
    else//sxkc频段--加权码
    {
        //X向接收相位/幅度加权码
        str_oder=ChangeColor("X向接收相位/幅度加权码: ",mB)+QString::number((str.switch_Choose&0xF0)>>4);
        Modeview2->append(str_oder);
        //Y向接收相位/幅度加权码
        str_oder=ChangeColor("Y向接收相位/幅度加权码: ",mB)+QString::number(str.switch_Choose&0x0F);
        Modeview2->append(str_oder);
    }
    //波束合成标志7.2
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

        str_oder=ChangeColor("波束合成标志: ",mB);
        switch (str.bs_hc) {
        case 1:
            str_oder+="1:合成";
            break;
        case 2:
            str_oder+="2:不合成";
            break;
        default:
            str_oder+="未知:"+QString::number(str.bs_hc);
            break;
        }
        Modeview2->append(str_oder);
    }
    else//sxkc频段--组件遥测数据类型
    {
        str_oder=ChangeColor("组件遥测数据类型: ",mB);
        switch (str.bs_hc) {
        case 0x1F:
            str_oder+="0x1F:组件移相衰减码遥测";
            break;
        case 0xD0:
            str_oder+="0xD0:组件温度遥测";
            break;
        default:
            str_oder+="未知:"+QString::number(str.bs_hc);
            break;
        }
        Modeview2->append(str_oder);
    }
    if(str.bs_hc==1)//波束合成才显示
    {
        //数字波束1偏置离轴角
        str_oder=ChangeColor("数字波束1偏置离轴角: ",mB)+QString::number(qToBigEndian(str.zz1_lz));
        Modeview2->append(str_oder);
        //数字波束1偏置方位角
        str_oder=ChangeColor("数字波束1偏置方位角: ",mB)+QString::number(qToBigEndian(str.zz1_fw));
        Modeview2->append(str_oder);
        //数字波束2偏置离轴角
        str_oder=ChangeColor("数字波束2偏置离轴角: ",mB)+QString::number(qToBigEndian(str.zz2_lz));
        Modeview2->append(str_oder);
        //数字波束2偏置方位角
        str_oder=ChangeColor("数字波束2偏置方位角: ",mB)+QString::number(qToBigEndian(str.zz2_fw));
        Modeview2->append(str_oder);
        //数字波束3偏置离轴角
        str_oder=ChangeColor("数字波束3偏置离轴角: ",mB)+QString::number(qToBigEndian(str.zz3_lz));
        Modeview2->append(str_oder);
        //数字波束3偏置方位角
        str_oder=ChangeColor("数字波束3偏置方位角: ",mB)+QString::number(qToBigEndian(str.zz3_fw));
        Modeview2->append(str_oder);
        //数字波束4偏置离轴角
        str_oder=ChangeColor("数字波束4偏置离轴角: ",mB)+QString::number(qToBigEndian(str.zz4_lz));
        Modeview2->append(str_oder);
        //数字波束4偏置方位角
        str_oder=ChangeColor("数字波束4偏置方位角: ",mB)+QString::number(qToBigEndian(str.zz4_fw));
        Modeview2->append(str_oder);
    }
    //。。。。。。。。。。。4个子阵参数内容
    int zz_L=0;//子阵总长
    aerial_ZCmode1_zxzl str_zxzl;
    aerial_ZCmode2_zxsm str_zxsm;
    aerial_ZCmode3_qyns str_qyns;
    aerial_ZCmode4_qysm str_qysm;
    int N=4;
    if(str.aerial_patameter&0x80)N=1;//天线指向一致，只输出子阵1
    for (int i=0;i<N;i++) {

        if(i==0)if(!(str.aerial_patameter&0x01))continue;//子阵1;
        if(i==1)if(!(str.aerial_patameter&0x02))continue;//子阵2;
        if(i==2)if(!(str.aerial_patameter&0x04))continue;//子阵3;
        if(i==3)if(!(str.aerial_patameter&0x08))continue;//子阵4;
        if(1)
        {
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));
            uchar kind=0;
            memcpy(&kind,data+sizeof (Elec_Recon)+zz_L+1,1);
            switch (kind) {
            case 1:// 指向驻留模式参数
                memcpy(&str_zxzl,data+sizeof (Elec_Recon)+zz_L,sizeof (str_zxzl));
                //天线子阵号
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
                if(str_zxzl.aerial_zznumber==0)str_oder+="全选";
                else str_oder+="子阵"+QString::number(str_zxzl.aerial_zznumber);
                Modeview2->append(str_oder);
                //天线子阵控制模式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"指向驻留模式";
                Modeview2->append(str_oder);
                //极化方式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
                switch (str_zxzl.polarmand) {
                case 0:
                    str_oder+="0:垂直";
                    break;
                case 1:
                    str_oder+="1:水平";
                    break;
                case 2:
                    str_oder+="2:自适应";
                    break;
                default:
                    str_oder+="未知:"+QString::number(str_zxzl.polarmand);
                    break;
                }
                Modeview2->append(str_oder);
                // 波束离轴角指向
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"波束离轴角指向0.1°: ",mB)+QString::number(qToBigEndian(str_zxzl.bs_offaxis));
                Modeview2->append(str_oder);
                // 波束方位角指向
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"波束方位角指向0.1°: ",mB)+QString::number(qToBigEndian(str_zxzl.bs_bearing));
                Modeview2->append(str_oder);
                zz_L+=sizeof (aerial_ZCmode1_zxzl);
                break;
            case 2:// 指向扫描模式参数
                memcpy(&str_zxsm,data+sizeof (Elec_Recon)+zz_L,sizeof (str_zxsm));
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
                if(str_zxsm.aerial_zznumber==0)str_oder+="全选";
                else str_oder+="子阵"+QString::number(str_zxsm.aerial_zznumber);
                Modeview2->append(str_oder);
                //天线子阵控制模式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"指向扫描模式";
                Modeview2->append(str_oder);
                //极化方式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
                switch (str_zxsm.polarmand) {
                case 0:
                    str_oder+="0:垂直";
                    break;
                case 1:
                    str_oder+="1:水平";
                    break;
                case 2:
                    str_oder+="2:自适应";
                    break;
                default:
                    str_oder+="未知:"+QString::number(str_zxsm.polarmand);
                    break;
                }
                Modeview2->append(str_oder);
                //指向驻留时间
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"指向驻留时间: ",mB)+QString::number(str_zxsm.zx_ontime);
                Modeview2->append(str_oder);
                // 指向个数
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"指向个数: ",mB)+QString::number(str_zxsm.pointsum);
                Modeview2->append(str_oder);
                //循环体。。。
                //波束离轴角指向
                //波束方位角指向

                zz_L+=sizeof (aerial_ZCmode2_zxsm_2)+str_zxsm.pointsum*4;
                break;
            case 3:// 区域凝视模式参数
                memcpy(&str_qyns,data+sizeof (Elec_Recon)+zz_L,sizeof (str_qyns));
                //天线子阵号
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
                if(str_qyns.aerial_zznumber==0)str_oder+="全选";
                else str_oder+="子阵"+QString::number(str_qyns.aerial_zznumber);
                Modeview2->append(str_oder);
                //天线子阵控制模式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"区域凝视模式";
                Modeview2->append(str_oder);
                //极化方式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
                switch (str_qyns.polarmand) {
                case 0:
                    str_oder+="0:垂直";
                    break;
                case 1:
                    str_oder+="1:水平";
                    break;
                case 2:
                    str_oder+="2:自适应";
                    break;
                default:
                    str_oder+="未知:"+QString::number(str_qyns.polarmand);
                    break;
                }
                Modeview2->append(str_oder);
                // 目标经度*(1000000)
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"目标经度(*1000000): ",mB)+QString::number(qToBigEndian(str_qyns.target_orb));
                Modeview2->append(str_oder);
                // 目标纬度*(1000000)
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"目标纬度(*1000000): ",mB)+QString::number(qToBigEndian(str_qyns.target_latitude));
                Modeview2->append(str_oder);
                zz_L+=sizeof (aerial_ZCmode3_qyns);
                break;
            case 4:// 区域扫描模式参数
                memcpy(&str_qysm,data+sizeof (Elec_Recon)+zz_L,sizeof (str_qysm));
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
                if(str_qysm.aerial_zznumber==0)str_oder+="全选";
                else str_oder+="子阵"+QString::number(str_qysm.aerial_zznumber);
                Modeview2->append(str_oder);
                //天线子阵控制模式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"区域扫描模式";
                Modeview2->append(str_oder);
                //极化方式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
                switch (str_qysm.polarmand) {
                case 0:
                    str_oder+="0:垂直";
                    break;
                case 1:
                    str_oder+="1:水平";
                    break;
                case 2:
                    str_oder+="2:自适应";
                    break;
                default:
                    str_oder+="未知:"+QString::number(str_qysm.polarmand);
                    break;
                }
                Modeview2->append(str_oder);
                //区域驻留时间
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"区域驻留时间: ",mB)+QString::number(str_qysm.region_onntime);
                Modeview2->append(str_oder);
                // 区域点个数
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"区域点个数: ",mB)+QString::number(qToBigEndian(str_qysm.region_sum));
                Modeview2->append(str_oder);
                //循环体。。。
                //区域点经度
                //区域点纬度
                zz_L+=sizeof (aerial_ZCmode4_qysm)+str_qysm.region_sum*8;
                break;
            default:
                break;
            }

        }

    }

    Sum_Len=sizeof (Elec_Recon)+zz_L;
    return Sum_Len;
}
// 电子干扰任务
uint Translate::Trans_Elec_GrData(uchar *data)
{
    int Sum_Len=0;
    Elec_Jamming str;
    memset(&str,0,sizeof (Elec_Jamming));
    memcpy(&str,data,sizeof (Elec_Jamming));
    //下拉内容
    map<int,QString>clb;
    clb[0]="0:表示关闭接收通道";
    clb[9]="9:表示发送通道0数据";

    QString str_oder;

    QString ss="功能模式信息====("+UP_fun_mode[Glob_Head.fun_mode]+")";
    Modeview2->append(ChangeColor(ss,mR));

    // 数据通道流向
    //--处理板1的FPGA_1
    ushort tmp_ushort=qToBigEndian(str.datastrim);
    str_oder=ChangeColor("处理板1的FPGA_1: ",mB)+clb[(tmp_ushort&0xF000)>>12];
    Modeview2->append(str_oder);
    //--处理板1的FPGA_2
    str_oder=ChangeColor("处理板1的FPGA_2: ",mB)+clb[(tmp_ushort&0x0F00)>>8];
    Modeview2->append(str_oder);
    //--处理板2的FPGA_1
    str_oder=ChangeColor("处理板2的FPGA_1: ",mB)+clb[(tmp_ushort&0x00F0)>>4];
    Modeview2->append(str_oder);
    //--处理板2的FPGA_2
    str_oder=ChangeColor("处理板2的FPGA_2: ",mB)+clb[tmp_ushort&0x000F];
    Modeview2->append(str_oder);


    // 本振选择方式 L频段无效0，sxku有效1
    if(Glob_Head.Gener_str.pd_choose==1)
    {
        str_oder=ChangeColor("本振选择方式: ",mB)+(str.bz_choose ? "1:共本振":"0:独立本振");
        Modeview2->append(str_oder);
    }
    // 天线与通道对应模式
    str_oder=ChangeColor("天线与通道对应模式: ",mB);
    switch (str.txytddyms) {
    case 1:
        str_oder+="1:天线子阵1234对应通道1234";
        break;
    case 2:
        str_oder+="2:天线子阵1234对应通道1256";
        break;
    case 3:
        str_oder+="3:天线子阵1234对应通道3456";
        break;
    default:
        str_oder+="未知:"+QString::number(str.txytddyms);
        break;
    }
    Modeview2->append(str_oder);
    // 一本振使用信息
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

    }else//sku频段
    {
        str_oder=ChangeColor("一本振使用信息: ",mB);
        switch (str.bz1_mess&0x01) {
        case 0:
            str_oder+="宽带一本振1";
            break;
        case 1:
            str_oder+="宽带一本振2";
            break;
        default:
            str_oder+="未知:"+QString::number(str.bz1_mess);
            break;
        }
        if(str.bz_choose==0)//独立本振
        {
            switch ((str.bz1_mess&0x02)>>1) {
            case 0:
                str_oder+=" ,组2:一本振1";
                break;
            case 1:
                str_oder+=" ,组2:一本振2";
                break;
            default:
                str_oder+=" ,未知:"+QString::number(str.bz1_mess);
                break;
            }
        }
        Modeview2->append(str_oder);
    }

    // 射频通道参数设置
    str_oder=ChangeColor("射频通道参数设置: ",mB);
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {
        if(str.sp_addata[0]&0x01)str_oder+=" GSM选通陷波器使能;";
        if(str.sp_addata[0]&0x02)str_oder+=" 一级放大器使能;";
        if(str.sp_addata[0]&0x04)str_oder+=" 二级放大器使能;";
        if(str.sp_addata[0]&0x08)str_oder+=" 三级放大器使能;";
    }else//sku频段
    {

        if(str.sp_addata[0]&0x01)str_oder+="一级放大器使能;";
        switch ((str.sp_addata[0]&0x06)>>1) {
        case 0:
            str_oder+=" 组1:射频衰减0dB";
            break;
        case 1:
            str_oder+=" 组1:射频衰减10dB";
            break;
        case 2:
            str_oder+=" 组1:射频衰减20dB";
            break;
        default:
            str_oder+=" 未知:"+QString::number((str.sp_addata[0]&0x06)>>1);
            break;
        }
        if(str.bz_choose==0)//独立本振
        {
            if(str.sp_addata[1]&0x01)str_oder+=" ,组2:一级放大器使能;";
            switch ((str.sp_addata[1]&0x06)>>1) {
            case 0:
                str_oder+=" ,组2:射频衰减0dB";
                break;
            case 1:
                str_oder+=" ,组2:射频衰减10dB";
                break;
            case 2:
                str_oder+=" ,组2:射频衰减20dB";
                break;
            default:
                str_oder+="未知:"+QString::number((str.sp_addata[1]&0x06)>>1);
                break;
            }
        }
    }
    Modeview2->append(str_oder);
    // 射频通道发射衰减
    str_oder=ChangeColor("射频通道发射衰减(dB): ",mB)+QString::number(str.sp_adlow[0])+"dB";
    if(str.bz_choose==0)//独立本振
    {
        str_oder+=" ,组2:"+QString::number(str.sp_adlow[1])+"dB";
    }
    Modeview2->append(str_oder);
    // 射频通道接收衰减
    str_oder=ChangeColor("射频通道接收衰减(dB): ",mB)+QString::number(str.sp_jslow[0])+"dB";
    if(str.bz_choose==0)//独立本振
    {
        str_oder+=" ,组2:"+QString::number(str.sp_jslow[1])+"dB";
    }
    Modeview2->append(str_oder);
    // 天线子阵参数
    str_oder=ChangeColor("天线子阵参数: ",mB);
    if(str.aerial_patameter&0x01)str_oder+=" 子阵1;";
    if(str.aerial_patameter&0x02)str_oder+=" 子阵2;";
    if(str.aerial_patameter&0x04)str_oder+=" 子阵3;";
    if(str.aerial_patameter&0x08)str_oder+=" 子阵4;";
    Modeview2->append(str_oder);
    //---天线使用方式

    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

        str_oder=ChangeColor("天线使用方式: ",mB);
        switch ((str.aerial_patameter&0x60)>>5) {
        case 0:
            str_oder+="0:独立孔径";
            break;
        case 1:
            str_oder+="1:合成孔径";
            break;
        case 2:
            str_oder+="2:双孔径";
            break;
        default:
            str_oder+="未知:"+QString::number((str.aerial_patameter&0x60)>>5);
            break;
        }
        Modeview2->append(str_oder);
    }
    else//sku频段
    {
        str_oder=ChangeColor("子阵1、3的天线使用方式: ",mB)+
                ((str.aerial_patameter&0x20) ? "1:启用V极化合成":"0:不启用V极化合成");
        Modeview2->append(str_oder);
        str_oder=ChangeColor("子阵2、4的天线使用方式: ",mB)+
                ((str.aerial_patameter&0x40) ? "1:启用H极化合成":"0:不启用H极化合成");
        Modeview2->append(str_oder);

    }
    // 天线子阵控制模式
    str_oder=ChangeColor("天线子阵控制模式: ",mB);
    switch (str.aerial_mode) {
    case 1:
        str_oder+="1:指向驻留模式";
        break;
    case 2:
        str_oder+="2:指向扫描模式";
        break;
    case 3:
        str_oder+="3:区域凝视模式";
        break;
    default:
        str_oder+="未知:"+QString::number(str.aerial_mode);
        break;
    }
    Modeview2->append(str_oder);
    // 天线控制间隔时间

    str_oder=ChangeColor("天线控制间隔时间(s): ",mB)+QString::number(str.aerial_time);
    Modeview2->append(str_oder);

    // 天线指向算法数据源
    str_oder=ChangeColor("天线指向算法数据源: ",mB)+((str.aerial_pointing) ? "1:GPS数据源":"0:外推数据源");
    Modeview2->append(str_oder);
    //,Bit7-Bit6：天线接收衰减值
    str_oder=ChangeColor("天线接收衰减值: ",mB);
    switch ((str.aerial_low&0xC0)>>6) {
    case 0:
        str_oder+="0:0dB";
        break;
    case 1:
        str_oder+="1:10dB";
        break;
    case 2:
        str_oder+="2:20dB";
        break;
    case 3:
        str_oder+="3:30dB";
        break;
    default:
        str_oder+="未知:"+QString::number((str.aerial_low&0xC0)>>6);
        break;
    }
    Modeview2->append(str_oder);
    //bit5-bit0:L段天线射频发射衰减值
    str_oder=ChangeColor("L段天线射频发射衰减值(0.5dB): ",mB)+QString::number(str.aerial_low&0x3F);
    Modeview2->append(str_oder);

    //天线子阵参数--干扰就1个模式
    aerial_GRmode1_zxzl str_GRmode1_zxzl;// 指向驻留模式参数
    aerial_GRmode2_zxsm2 str_GRmode2_zxsm2;// 指向扫描模式参数
    aerial_GRmode3_qyns str_GRmode3_qyns;// 区域凝视模式参数
    memset(&str_GRmode1_zxzl, 0, sizeof(str_GRmode1_zxzl));
    memset(&str_GRmode2_zxsm2, 0, sizeof(str_GRmode2_zxsm2));
    memset(&str_GRmode3_qyns, 0, sizeof(str_GRmode3_qyns));

    map<int,QString>jhfs;
    jhfs[0]="0:一直水平极化";
    jhfs[1]="1:水平到垂直，循环切";
    jhfs[2]="2:垂直到水平，循环切换";
    jhfs[3]="3:一直垂直极化";

    int kind=str.aerial_mode;
    int len2=0;
    uchar tmp_uchar=0;
    switch (kind) {
    case 1:
        memcpy(&str_GRmode1_zxzl,data+sizeof (Elec_Jamming),sizeof (aerial_GRmode1_zxzl));
        len2=sizeof (aerial_GRmode1_zxzl);
        // 极化方式
        //--天线子阵1
        tmp_uchar=str_GRmode1_zxzl.polarmand;
        str_oder=ChangeColor("天线子阵1: ",mB)+jhfs[tmp_uchar&0x03];
        Modeview2->append(str_oder);
        //--天线子阵2
        str_oder=ChangeColor("天线子阵2: ",mB)+jhfs[(tmp_uchar&0x0C)>>2];
        Modeview2->append(str_oder);
        //--天线子阵3
        str_oder=ChangeColor("天线子阵3: ",mB)+jhfs[(tmp_uchar&0x30)>>4];
        Modeview2->append(str_oder);
        //--天线子阵4
        str_oder=ChangeColor("天线子阵4: ",mB)+jhfs[(tmp_uchar&0xC0)>>6];
        Modeview2->append(str_oder);
        // 极化切换时间
        str_oder=ChangeColor("极化切换时间(us): ",mB)+QString::number(str_GRmode1_zxzl.qh_time);
        Modeview2->append(str_oder);
        // 保留
        // 波束离轴角指向
        str_oder=ChangeColor("波束离轴角指向: ",mB)+QString::number(qToBigEndian(str_GRmode1_zxzl.bs_offaxis));
        Modeview2->append(str_oder);
        // 波束方位角指向
        str_oder=ChangeColor("波束方位角指向: ",mB)+QString::number(qToBigEndian(str_GRmode1_zxzl.bs_bearing));
        Modeview2->append(str_oder);
        break;
    case 2:
        memcpy(&str_GRmode2_zxsm2,data+sizeof (Elec_Jamming),sizeof (aerial_GRmode2_zxsm2));
        len2=sizeof (aerial_GRmode2_zxsm2);
        // 极化方式
        //--天线子阵1
        tmp_uchar=str_GRmode2_zxsm2.polarmand;
        str_oder=ChangeColor("天线子阵1: ",mB)+jhfs[tmp_uchar&0x03];
        Modeview2->append(str_oder);
        //--天线子阵2
        str_oder=ChangeColor("天线子阵2: ",mB)+jhfs[(tmp_uchar&0x0C)>>2];
        Modeview2->append(str_oder);
        //--天线子阵3
        str_oder=ChangeColor("天线子阵3: ",mB)+jhfs[(tmp_uchar&0x30)>>4];
        Modeview2->append(str_oder);
        //--天线子阵4
        str_oder=ChangeColor("天线子阵4: ",mB)+jhfs[(tmp_uchar&0xC0)>>6];
        Modeview2->append(str_oder);
        // 极化切换时间
        str_oder=ChangeColor("极化切换时间(us): ",mB)+QString::number(str_GRmode2_zxsm2.qh_time);
        Modeview2->append(str_oder);
        // 指向驻留时间
        str_oder=ChangeColor("指向驻留时间(s): ",mB)+QString::number(str_GRmode2_zxsm2.zx_ontime);
        Modeview2->append(str_oder);
        // 指向个数
        str_oder=ChangeColor("指向个数: ",mB)+QString::number(str_GRmode2_zxsm2.pointsum);
        Modeview2->append(str_oder);
        //指向个数（。。。。1-255循环体）
        len2+=str_GRmode2_zxsm2.pointsum*4;
        break;
    case 3:
        memcpy(&str_GRmode3_qyns,data+sizeof (Elec_Jamming),sizeof (aerial_GRmode3_qyns));
        len2=sizeof (aerial_GRmode3_qyns);
        // 目标经度
        str_oder=ChangeColor("目标经度: ",mB)+QString::number(qToBigEndian(str_GRmode3_qyns.target_orb));
        Modeview2->append(str_oder);
        // 目标纬度
        str_oder=ChangeColor("目标纬度: ",mB)+QString::number(qToBigEndian(str_GRmode3_qyns.target_latitude));
        Modeview2->append(str_oder);
        // 极化方式
        //--天线子阵1
        tmp_uchar=str_GRmode3_qyns.polarmand;
        str_oder=ChangeColor("天线子阵1: ",mB)+jhfs[tmp_uchar&0x03];
        Modeview2->append(str_oder);
        //--天线子阵2
        str_oder=ChangeColor("天线子阵2: ",mB)+jhfs[(tmp_uchar&0x0C)>>2];
        Modeview2->append(str_oder);
        //--天线子阵3
        str_oder=ChangeColor("天线子阵3: ",mB)+jhfs[(tmp_uchar&0x30)>>4];
        Modeview2->append(str_oder);
        //--天线子阵4
        str_oder=ChangeColor("天线子阵4: ",mB)+jhfs[(tmp_uchar&0xC0)>>6];
        Modeview2->append(str_oder);
        // 极化切换时间
        str_oder=ChangeColor("极化切换时间(us): ",mB)+QString::number(str_GRmode3_qyns.qh_time);
        Modeview2->append(str_oder);
        break;
    default:
        break;
    }

    Sum_Len=sizeof (Elec_Jamming)+len2;
    return Sum_Len;
}
//SAR探测任务基本信息
uint Translate::Trans_SAR_probing(uchar *data)
{
    int Sum_Len=0;
    SAR_Str str;
    memset(&str,0,sizeof (SAR_Str));
    memcpy(&str,data,sizeof (SAR_Str));

    QString str_oder;

    QString ss="功能模式信息====("+UP_fun_mode[Glob_Head.fun_mode]+")";
    Modeview2->append(ChangeColor(ss,mR));
    // 收发FPGA_1(0x)
    str_oder=ChangeColor("收发FPGA_1: ",mB)+QString("0x%1").arg(qToBigEndian(str.sf_FPGA_1),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 收发FPGA_2
    str_oder=ChangeColor("收发FPGA_2: ",mB)+QString("0x%1").arg(qToBigEndian(str.sf_FPGA_2),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 数据处理板AFPGA_1
    str_oder=ChangeColor("数据处理板AFPGA_1: ",mB)+QString("0x%1").arg(qToBigEndian(str.A_FPGA_1),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 数据处理板AFPGA_2
    str_oder=ChangeColor("数据处理板AFPGA_2: ",mB)+QString("0x%1").arg(qToBigEndian(str.A_FPGA_2),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 数据处理板Adsp
    str_oder=ChangeColor("数据处理板Adsp: ",mB)+QString("0x%1").arg(qToBigEndian(str.A_dsp),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 数据处理板BFPGA_1
    str_oder=ChangeColor("数据处理板BFPGA_1: ",mB)+QString("0x%1").arg(qToBigEndian(str.B_FPGA_1),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 数据处理板BFPGA_2
    str_oder=ChangeColor("数据处理板BFPGA_2: ",mB)+QString("0x%1").arg(qToBigEndian(str.B_FPGA_2),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);
    // 数据处理板Bdsp
    str_oder=ChangeColor("数据处理板Bdsp: ",mB)+QString("0x%1").arg(qToBigEndian(str.B_dsp),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);

    //bit7-bit4:引导方式
    str_oder=ChangeColor("引导方式: ",mB);
    switch ((str.is_yd&0xF0)>>4) {
    case 0:
        str_oder+="0:自主成像";
        break;
    case 1:
        str_oder+="1:被引导成像";
        break;
    case 2:
        str_oder+="2:引导他星成像";
        break;

    default:
        str_oder+="未知:"+QString::number((str.is_yd&0xF0)>>4);
        break;
    }
    Modeview2->append(str_oder);
    //bit3-bit0:侦察定位模式
    str_oder=ChangeColor("侦察定位模式: ",mB)+((str.is_yd&0x0F) ? "1:多星定位":"0:单星定位");
    Modeview2->append(str_oder);
    //是否实时成像
    str_oder=ChangeColor("是否实时成像: ",mB)+((str.is_cx) ? "1:实时":"0:不实时");
    Modeview2->append(str_oder);
    // 天线与通道对应模式
    str_oder=ChangeColor("天线与通道对应模式: ",mB);
    switch (str.aerial_ad) {
    case 1:
        str_oder+="1:天线子阵1234对应通道1234";
        break;
    case 2:
        str_oder+="2:天线子阵1234对应通道1256";
        break;
    case 3:
        str_oder+="3:天线子阵1234对应通道3456";
        break;

    default:
        str_oder+="未知:"+QString::number(str.aerial_ad);
        break;
    }
    Modeview2->append(str_oder);
    // 射频通道号
    str_oder=ChangeColor("射频通道号: ",mB)+QString::number(str.sp_ad);
    Modeview2->append(str_oder);
    // 射频通道参数设置
    str_oder=ChangeColor("射频通道参数设置: ",mB);

    if(str.sp_addata&0x01)str_oder+=" GSM选通陷波器使能;";
    if(str.sp_addata&0x02)str_oder+=" 一级放大器使能;";
    if(str.sp_addata&0x04)str_oder+=" 二级放大器使能;";
    if(str.sp_addata&0x08)str_oder+=" 三级放大器使能;";
    Modeview2->append(str_oder);
    // 射频通道发射衰减
    str_oder=ChangeColor("射频通道发射衰减: ",mB)+QString::number(str.sp_fslow);
    Modeview2->append(str_oder);
    // 射频通道接收衰减
    str_oder=ChangeColor("射频通道接收衰减: ",mB)+QString::number(str.sp_jslow);
    Modeview2->append(str_oder);
    // 引导地址
    str_oder=ChangeColor("引导地址: ",mB)+QString("0x%1").arg(qToBigEndian(str.yddz),4,16,QLatin1Char('0')).toUpper();
    Modeview2->append(str_oder);




    Sum_Len=sizeof (SAR_Str);
    return Sum_Len;

}

//类5G任务基本信息
uint Translate::Trans_5G_kind(uchar *data)
{

    int Sum_Len=0;
    Kind5G_Str str;
    memset(&str,0,sizeof (Kind5G_Str));
    memcpy(&str,data,sizeof (Kind5G_Str));

    //下拉内容
    map<int,QString>clb;
    clb[9]=  "9:表示发送通道0数据";
    clb[10]="10:表示发送通道1数据";
    clb[11]="11:表示发送通道2数据";
    clb[12]="12:表示发送通道3数据";
    clb[15]="15:表示保留原状态";

    QString str_oder;

    QString ss="功能模式信息====("+UP_fun_mode[Glob_Head.fun_mode]+")";
    Modeview2->append(ChangeColor(ss,mR));

    // 数据通道流向
    //--处理板1的FPGA_1
    ushort tmp_ushort=qToBigEndian(str.datastrim);
    str_oder=ChangeColor("处理板1的FPGA_1: ",mB)+clb[(tmp_ushort&0xF000)>>12];
    Modeview2->append(str_oder);
    //--处理板1的FPGA_2
    str_oder=ChangeColor("处理板1的FPGA_2: ",mB)+clb[(tmp_ushort&0x0F00)>>8];
    Modeview2->append(str_oder);
    //--处理板2的FPGA_1
    str_oder=ChangeColor("处理板2的FPGA_1: ",mB)+clb[(tmp_ushort&0x00F0)>>4];
    Modeview2->append(str_oder);
    //--处理板2的FPGA_2
    str_oder=ChangeColor("处理板2的FPGA_2: ",mB)+clb[tmp_ushort&0x000F];
    Modeview2->append(str_oder);

    // 本振选择方式
    // 本振选择方式 L频段无效0，sxku有效1
    if(Glob_Head.Gener_str.pd_choose==1)
    {
        str_oder=ChangeColor("本振选择方式: ",mB)+(str.bz_choose ? "1:共本振":"0:独立本振");
        Modeview2->append(str_oder);
    }
    // 1本振使用信息 L频段无效0，sxku有效1
    if(Glob_Head.Gener_str.pd_choose==1)
    {
        str_oder=ChangeColor("1本振使用信息: ",mB);
        switch (str.bz1_mess) {
        case 0:
            str_oder+="0:宽带一本振1";
            break;
        case 1:
            str_oder+="1:宽带一本振2";
            break;
        case 2:
            str_oder+="2:使用SXKu高相噪一本振";
            break;
        default:
            str_oder+="未知:"+QString::number(str.bz1_mess);
            break;
        }
        Modeview2->append(str_oder);
    }
    // 天线与通道对应模式
    str_oder=ChangeColor("天线与通道对应模式: ",mB);
    switch (str.aerial_ad) {
    case 1:
        str_oder+="1:天线子阵1234对应通道1234";
        break;
    case 2:
        str_oder+="2:天线子阵1234对应通道1256";
        break;
    case 3:
        str_oder+="3:天线子阵1234对应通道3456";
        break;
    default:
        str_oder+="未知:"+QString::number(str.aerial_ad);
        break;
    }
    Modeview2->append(str_oder);
    // 射频通道号
    str_oder=ChangeColor("射频通道号: ",mB);
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {
        switch (str.sp_ad) {
        case 0:
            str_oder+="0:通拨";
            break;
        default:
            str_oder+="通道:"+QString::number(str.sp_ad);
            break;
        }
    }
    else//sku频段
    {
        switch (str.sp_ad) {
        case 0:
            str_oder+="0:通拨";
            break;
        case 1:
            str_oder+="1:通道1和2";
            break;
        case 2:
            str_oder+="2:通道3和4";
            break;
        case 3:
            str_oder+="3:通道5和6";
            break;
        default:
            str_oder+="未知:"+QString::number(str.sp_ad);
            break;
        }
    }
    Modeview2->append(str_oder);
    // 射频通道参数设置
    str_oder=ChangeColor("射频通道参数设置: ",mB);
    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {
        if(str.sp_addata&0x01)str_oder+=" GSM选通陷波器使能;";
        if(str.sp_addata&0x02)str_oder+=" 一级放大器使能;";
        if(str.sp_addata&0x04)str_oder+=" 二级放大器使能;";
        if(str.sp_addata&0x08)str_oder+=" 三级放大器使能;";
    }else//sku频段
    {

        if(str.sp_addata&0x01)str_oder+="一级放大器使能;";
        switch ((str.sp_addata&0x06)>>1) {
        case 0:
            str_oder+="0:射频衰减0dB";
            break;
        case 1:
            str_oder+="1:射频衰减10dB";
            break;
        case 2:
            str_oder+="2:射频衰减20dB";
            break;
        default:
            str_oder+=" 未知:"+QString::number((str.sp_addata&0x06)>>1);
            break;
        }
    }
    Modeview2->append(str_oder);
    // 射频通道接收衰减
    str_oder=ChangeColor("射频通道接收衰减(dB): ",mB)+QString::number(str.sp_adlow)+"dB";
    Modeview2->append(str_oder);
    // 射频通道发射衰减
    str_oder=ChangeColor("射频通道发射衰减(dB): ",mB)+QString::number(str.sp_fslow)+"dB";
    Modeview2->append(str_oder);
    // 天线子阵参数
    str_oder=ChangeColor("天线子阵参数: ",mB);
    if(str.aerial_patameter&0x01)str_oder+=" 天线子阵1;";
    if(str.aerial_patameter&0x02)str_oder+=" 天线子阵2;";
    if(str.aerial_patameter&0x04)str_oder+=" 天线子阵3;";
    if(str.aerial_patameter&0x08)str_oder+=" 天线子阵4;";
    Modeview2->append(str_oder);
    //---天线使用方式

    if(Glob_Head.Gener_str.pd_choose==0)//L频段
    {

        str_oder=ChangeColor("天线使用方式: ",mB);
        switch ((str.aerial_patameter&0x60)>>5) {
        case 0:
            str_oder+="0:独立孔径";
            break;
        case 1:
            str_oder+="1:合成孔径";
            break;
        case 2:
            str_oder+="2:双孔径";
            break;
        default:
            str_oder+="未知:"+QString::number((str.aerial_patameter&0x60)>>5);
            break;
        }
        Modeview2->append(str_oder);
    }
    else//sku频段
    {
        str_oder=ChangeColor("子阵1、3的天线使用方式: ",mB)+
                ((str.aerial_patameter&0x20) ? "1:启用V极化合成":"0:不启用V极化合成");
        Modeview2->append(str_oder);
        str_oder=ChangeColor("子阵2、4的天线使用方式: ",mB)+
                ((str.aerial_patameter&0x40) ? "1:启用H极化合成":"0:不启用H极化合成");
        Modeview2->append(str_oder);

    }
    // 天线控制间隔时间
    //if(str.aerial_time!=0)
    //{
        str_oder=ChangeColor("天线控制间隔时间ms: ",mB)+QString::number(str.aerial_time);
        Modeview2->append(str_oder);
    //}
    // 天线指向算法数据源
    str_oder=ChangeColor("天线指向算法数据源: ",mB)+((str.aerial_data) ? "1:GPS数据源":"0:外推数据源");
    Modeview2->append(str_oder);
    //天线射频发射衰减值,Bit5-Bit0：L频段天线发射衰减值
    str_oder=ChangeColor("天线接收衰减值: ",mB);
    switch ((str.aerial_low&0xC0)>>6) {
    case 0:
        str_oder+="0:0dB";
        break;
    case 1:
        str_oder+="1:10dB";
        break;
    case 2:
        str_oder+="2:20dB";
        break;
    case 3:
        str_oder+="3:30dB";
        break;
    default:
        str_oder+="未知:"+QString::number((str.aerial_low&0xC0)>>6);
        break;
    }
    Modeview2->append(str_oder);
    //bit5-bit0:L段天线射频发射衰减值
    str_oder=ChangeColor("L段天线射频发射衰减值(0.5dB): ",mB)+QString::number(str.aerial_low&0x3F);
    Modeview2->append(str_oder);
    //开关矩阵选择
    str_oder=ChangeColor("开关矩阵选择:",mB)+QString::number(str.switch_Choose);
    Modeview2->append(str_oder);

    //。。。。。。。。。。。4个子阵参数内容
    int zz_L=0;//子阵总长
    aerial_ZCmode1_zxzl str_zxzl;
    aerial_ZCmode2_zxsm str_zxsm;
    aerial_ZCmode3_qyns str_qyns;
    aerial_ZCmode4_qysm str_qysm;
    int N=4;
    for (int i=0;i<N;i++) {

        if(i==0)if(!(str.aerial_patameter&0x01))continue;//子阵1;
        if(i==1)if(!(str.aerial_patameter&0x02))continue;//子阵2;
        if(i==2)if(!(str.aerial_patameter&0x04))continue;//子阵3;
        if(i==3)if(!(str.aerial_patameter&0x08))continue;//子阵4;
        if(1)
        {
            memset(&str_zxzl, 0, sizeof(str_zxzl));
            memset(&str_zxsm, 0, sizeof(str_zxsm));
            memset(&str_qyns, 0, sizeof(str_qyns));
            memset(&str_qysm, 0, sizeof(str_qysm));
            uchar kind=0;
            memcpy(&kind,data+sizeof (Kind5G_Str)+zz_L+1,1);
            switch (kind) {
            case 1:// 指向驻留模式参数
                memcpy(&str_zxzl,data+sizeof (Kind5G_Str)+zz_L,sizeof (str_zxzl));
                //天线子阵号
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
                if(str_zxzl.aerial_zznumber==0)str_oder+="全选";
                else str_oder+="子阵"+QString::number(str_zxzl.aerial_zznumber);
                Modeview2->append(str_oder);
                //天线子阵控制模式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"指向驻留模式";
                Modeview2->append(str_oder);
                //极化方式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
                switch (str_zxzl.polarmand) {
                case 0:
                    str_oder+="0:垂直";
                    break;
                case 1:
                    str_oder+="1:水平";
                    break;
                case 2:
                    str_oder+="2:自适应";
                    break;
                default:
                    str_oder+="未知:"+QString::number(str_zxzl.polarmand);
                    break;
                }
                Modeview2->append(str_oder);
                // 波束离轴角指向
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"波束离轴角指向0.1°: ",mB)+QString::number(qToBigEndian(str_zxzl.bs_offaxis));
                Modeview2->append(str_oder);
                // 波束方位角指向
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"波束方位角指向0.1°: ",mB)+QString::number(qToBigEndian(str_zxzl.bs_bearing));
                Modeview2->append(str_oder);
                zz_L+=sizeof (aerial_ZCmode1_zxzl);
                break;
            case 2:// 指向扫描模式参数
//                memcpy(&str_zxsm,data+sizeof (Kind5G_Str)+zz_L,sizeof (str_zxsm));
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
//                if(str_zxsm.aerial_zznumber==0)str_oder+="全选";
//                else str_oder+="子阵"+QString::number(str_zxsm.aerial_zznumber);
//                Modeview2->append(str_oder);
//                //天线子阵控制模式
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"指向扫描模式";
//                Modeview2->append(str_oder);
//                //极化方式
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
//                switch (str_zxsm.polarmand) {
//                case 0:
//                    str_oder+="0:垂直";
//                    break;
//                case 1:
//                    str_oder+="1:水平";
//                    break;
//                case 2:
//                    str_oder+="2:自适应";
//                    break;
//                default:
//                    str_oder+="未知:"+QString::number(str_zxsm.polarmand);
//                    break;
//                }
//                Modeview2->append(str_oder);
//                //指向驻留时间
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"指向驻留时间: ",mB)+QString::number(str_zxsm.zx_ontime);
//                Modeview2->append(str_oder);
//                // 指向个数
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"指向个数: ",mB)+QString::number(str_zxsm.pointsum);
//                Modeview2->append(str_oder);
//                //循环体。。。
//                //波束离轴角指向
//                //波束方位角指向

//                zz_L+=sizeof (aerial_ZCmode2_zxsm_2)+str_zxsm.pointsum*4;
                break;
            case 3:// 区域凝视模式参数
                memcpy(&str_qyns,data+sizeof (Kind5G_Str)+zz_L,sizeof (str_qyns));
                //天线子阵号
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
                if(str_qyns.aerial_zznumber==0)str_oder+="全选";
                else str_oder+="子阵"+QString::number(str_qyns.aerial_zznumber);
                Modeview2->append(str_oder);
                //天线子阵控制模式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"区域凝视模式";
                Modeview2->append(str_oder);
                //极化方式
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
                switch (str_qyns.polarmand) {
                case 0:
                    str_oder+="0:垂直";
                    break;
                case 1:
                    str_oder+="1:水平";
                    break;
                case 2:
                    str_oder+="2:自适应";
                    break;
                default:
                    str_oder+="未知:"+QString::number(str_qyns.polarmand);
                    break;
                }
                Modeview2->append(str_oder);
                // 目标经度*(1000000)
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"目标经度(*1000000): ",mB)+QString::number(qToBigEndian(str_qyns.target_orb));
                Modeview2->append(str_oder);
                // 目标纬度*(1000000)
                str_oder=ChangeColor("子阵"+QString::number(i+1)+"目标纬度(*1000000): ",mB)+QString::number(qToBigEndian(str_qyns.target_latitude));
                Modeview2->append(str_oder);
                zz_L+=sizeof (aerial_ZCmode3_qyns);
                break;
            case 4:// 区域扫描模式参数
//                memcpy(&str_qysm,data+sizeof (Kind5G_Str)+zz_L,sizeof (str_qysm));
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵号: ",mB);
//                if(str_qysm.aerial_zznumber==0)str_oder+="全选";
//                else str_oder+="子阵"+QString::number(str_qysm.aerial_zznumber);
//                Modeview2->append(str_oder);
//                //天线子阵控制模式
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"天线子阵控制模式: ",mB)+"区域扫描模式";
//                Modeview2->append(str_oder);
//                //极化方式
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"极化方式: ",mB);
//                switch (str_qysm.polarmand) {
//                case 0:
//                    str_oder+="0:垂直";
//                    break;
//                case 1:
//                    str_oder+="1:水平";
//                    break;
//                case 2:
//                    str_oder+="2:自适应";
//                    break;
//                default:
//                    str_oder+="未知:"+QString::number(str_qysm.polarmand);
//                    break;
//                }
//                Modeview2->append(str_oder);
//                //区域驻留时间
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"区域驻留时间: ",mB)+QString::number(str_qysm.region_onntime);
//                Modeview2->append(str_oder);
//                // 区域点个数
//                str_oder=ChangeColor("子阵"+QString::number(i+1)+"区域点个数: ",mB)+QString::number(qToBigEndian(str_qysm.region_sum));
//                Modeview2->append(str_oder);
//                //循环体。。。
//                //区域点经度
//                //区域点纬度
//                zz_L+=sizeof (aerial_ZCmode4_qysm)+str_qysm.region_sum*8;
                break;
            default:
                break;
            }

        }

    }


    Sum_Len=sizeof (Kind5G_Str)+zz_L;
    return Sum_Len;
}

// 全景模式
uint Translate::mode_qj(uchar *data)
{
    Str_QJmode strQJ;
    memset(&strQJ, 0, sizeof(Str_QJmode));
    memcpy(&strQJ,data,sizeof (Str_QJmode));

    QString str_oder;

    // 单通道AD采样存储深度
    str_oder=ChangeColor("单通道AD采样存储深度: ",mB)+QString::number(strQJ.AD_num);
    Modeview3->append(str_oder);
    // 采集触发方式
    str_oder=ChangeColor("采集触发方式: ",mB);
    switch (strQJ.cj_mand) {
    case 0:
        str_oder+="0:不触发";
        break;
    case 1:
        str_oder+="1:门限触发";
        break;
    case 2:
        str_oder+="2:-";
        break;
    case 3:
        str_oder+="3:-";
        break;
    default:
        str_oder+="未知:"+QString::number(strQJ.cj_mand);
        break;
    }
    Modeview3->append(str_oder);
    // 触发门限
    if(strQJ.cj_mand==1)
    {
        str_oder=ChangeColor("触发门限: ",mB)+QString::number(strQJ.cfmx);
        Modeview3->append(str_oder);
    }
    // 频段个数0-100
    str_oder=ChangeColor("频段个数: ",mB)+QString::number(strQJ.pd_sum);
    Modeview3->append(str_oder);

    int cnt=0;
    cnt=strQJ.pd_sum;
    if(cnt>100)cnt=0;
    Str_QJmode_p2 strp2[cnt];
    memcpy(strp2,data+sizeof (Str_QJmode),sizeof (strp2));
    double tmp_d=0.0;
    for (int i=0;i<cnt;i++) {
        // 起始频率(MHz)
        tmp_d=qToBigEndian(strp2[i].start_fre);
        str_oder=ChangeColor(QString::number(i+1)+"起始频率(MHz): ",mB)+QString::number(tmp_d/1000);
        Modeview3->append(str_oder);
        // 终止频率(MHz)
        tmp_d=qToBigEndian(strp2[i].end_fre);
        str_oder=ChangeColor(QString::number(i+1)+"终止频率(MHz): ",mB)+QString::number(tmp_d/1000);
        Modeview3->append(str_oder);
        // 瞬时频率(kHz)
        tmp_d=qToBigEndian(strp2[i].mid_fre);
        str_oder=ChangeColor(QString::number(i+1)+"瞬时频率(KHz): ",mB)+QString::number(tmp_d/1000);
        Modeview3->append(str_oder);
    }

    return 0;
}
// 常规信号频点控守
uint Translate::mode_cgxhpdks_2(uchar *data)
{
    gen_Sig_Ctr_HEAD str;
    memset(&str, 0, sizeof(gen_Sig_Ctr_HEAD));
    memcpy(&str,data,sizeof (gen_Sig_Ctr_HEAD));

    QString str_oder;

    // 侦察模式
    str_oder=ChangeColor("侦察模式: ",mB);
    switch (str.investMode) {
    case 0:
        str_oder+="0:只进行参数测量";
        break;
    case 1:
        str_oder+="1:只进行采样";
        break;
    case 2:
        str_oder+="2:参数测量和采样";
        break;
    default:
        str_oder+="未知:"+QString::number(str.investMode);
        break;
    }
    Modeview3->append(str_oder);
    // 参数测量次数
    str_oder=ChangeColor("参数测量次数: ",mB)+QString::number(str.cscl_sum);
    Modeview3->append(str_oder);
    // 接收机频率MHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.reciveFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // iq长度
    str_oder=ChangeColor("IQ长度: ",mB);
    switch (str.iq_len) {
    case 1:
        str_oder+="1:4K";
        break;
    case 2:
        str_oder+="2:8K";
        break;
    case 3:
        str_oder+="3:16K";
        break;
    case 4:
        str_oder+="3:32K";
        break;
    default:
        str_oder+="未知:"+QString::number(str.investMode);
        break;
    }
    Modeview3->append(str_oder);
    // 采样信道总数N有效值1~4
    str_oder=ChangeColor("采样信道总数N: ",mB)+QString::number(str.CyChannelNum_N);
    Modeview3->append(str_oder);
    // /*常规信号频点控守参数采样*/
    int cnt=0;
    cnt=str.CyChannelNum_N;
    if(cnt>4)cnt=4;
    cgxhpdks_cy strp2[cnt];
    memcpy(strp2,data+sizeof (gen_Sig_Ctr_HEAD),sizeof (strp2));
    tmp_d=0.0;
    for (int i=0;i<cnt;i++) {
        // 处理板NCO频率Hz->Mhz
        tmp_d=qToBigEndian(strp2[i].NCOFre_N);
        str_oder=ChangeColor(QString::number(i+1)+"处理板NCO频率(MHz): ",mB)+QString::number(tmp_d/1000000);
        Modeview3->append(str_oder);
        // 采样带宽KHz
        tmp_d=qToBigEndian(strp2[i].CyPer_N);
        str_oder=ChangeColor(QString::number(i+1)+"采样带宽(KHz): ",mB)+QString::number(tmp_d/1000);
        Modeview3->append(str_oder);
        // 检测门限
        str_oder=ChangeColor(QString::number(i+1)+"检测门限: ",mB)+QString::number(strp2[i].examDoorLimit_N&0x7F);
        Modeview3->append(str_oder);
    }

    return 0;
}
// Link16信号频点控守
uint Translate::mode_linkpdks_3(uchar *data)
{

    Link16_Signal_Ctrl str;
    memset(&str, 0, sizeof(Link16_Signal_Ctrl));
    memcpy(&str,data,sizeof (Link16_Signal_Ctrl));

    QString str_oder;
    // 频偏Hz
    str_oder=ChangeColor("频偏(Hz): ",mB)+QString::number(qToBigEndian(str.FreError));
    Modeview3->append(str_oder);
    //检测通道选择
    str_oder=ChangeColor("检测通道选择: ",mB);
    switch (str.examChannelSel) {
    case 0:
        str_oder+="0:通道1";
        break;
    case 1:
        str_oder+="1:通道2";
        break;
    case 2:
        str_oder+="2:通道3";
        break;
    case 3:
        str_oder+="3:通道4";
        break;
    default:
        str_oder+="未知:"+QString::number(str.examChannelSel);
        break;
    }
    Modeview3->append(str_oder);
    // 脉冲类型
    str_oder=ChangeColor("脉冲类型: ",mB);
    switch (str.mckind) {
    case 0:
        str_oder+="0:16信号";
        break;
    case 1:
        str_oder+="1:J链信号";
        break;
    default:
        str_oder+="未知:"+QString::number(str.mckind);
        break;
    }
    Modeview3->append(str_oder);
    // PDW数据是否下传标识
    str_oder=ChangeColor("PDW数据是否下传标识: ",mB);
    switch (str.is_pdw) {
    case 0:
        str_oder+="0:只下FPGA原始PDW";
        break;
    case 1:
        str_oder+="1:只下DPS分选后PDW";
        break;
    case 2:
        str_oder+="2:全部下传";
        break;
    default:
        str_oder+="未知:"+QString::number(str.is_pdw);
        break;
    }
    Modeview3->append(str_oder);
    // 是否测向
    str_oder=ChangeColor("是否测向: ",mB)+(str.measureFlag ? "1:不测向":"0:测向");
    Modeview3->append(str_oder);
    // 测向频段
    str_oder=ChangeColor("测向频段: ",mB);
    switch (str.cx_pd) {
    case 0:
        str_oder+="0:987";
        break;
    case 1:
        str_oder+="1:1059";
        break;
    case 2:
        str_oder+="2:1140";
        break;
    case 3:
        str_oder+="3:1197";
        break;
    default:
        str_oder+="未知:"+QString::number(str.cx_pd);
        break;
    }
    Modeview3->append(str_oder);
    // 测向基线
    str_oder=ChangeColor("测向基线: ",mB)+QString::number(str.measureLine);
    Modeview3->append(str_oder);
    // 校正谱通道选择
    str_oder=ChangeColor("校正谱通道选择: ",mB);
    switch (str.corChannelSel) {
    case 0:
        str_oder+="0:通道1";
        break;
    case 1:
        str_oder+="1:通道2";
        break;
    case 2:
        str_oder+="2:通道3";
        break;
    case 3:
        str_oder+="3:通道4";
        break;
    default:
        str_oder+="未知:"+QString::number(str.corChannelSel);
        break;
    }
    Modeview3->append(str_oder);
    // 测向门限
    str_oder=ChangeColor("测向门限: ",mB)+QString::number(str.cx_oder);
    Modeview3->append(str_oder);
    // 校正方式 5.31新加
    str_oder=ChangeColor("校正方式: ",mB);
    switch (str.jx_mainer) {
    case 1:
        str_oder+="1:外校正";
        break;
    case 2:
        str_oder+="2:内校正";
        break;
    default:
        str_oder+="未知:"+QString::number(str.jx_mainer);
        break;
    }
    Modeview3->append(str_oder);
    // 搜索区域宽度 6.27新加
    str_oder=ChangeColor("搜索区域宽度: ",mB)+QString::number(str.ssqy);
    Modeview3->append(str_oder);

    return 0;
}
//塔康信号频点控守
uint Translate::mode_tkxhpdks_4(uchar *data)
{

    Tk_Signal_Ctrl str;
    memset(&str, 0, sizeof(Tk_Signal_Ctrl));
    memcpy(&str,data,sizeof (Tk_Signal_Ctrl));

    QString str_oder;
    // 检测通道选择
    str_oder=ChangeColor("检测通道选择: ",mB)+QString::number(qToBigEndian(str.examChannelSel));
    Modeview3->append(str_oder);
    // 是否测向
    str_oder=ChangeColor("是否测向: ",mB)+(str.measureFlag ? "1:不测向":"0:测向");
    Modeview3->append(str_oder);
    // 测向频段
    str_oder=ChangeColor("测向频段: ",mB);
    switch (str.cxpd) {
    case 0:
        str_oder+="0:962-1087";
        break;
    case 1:
        str_oder+="1:1088-1213";
        break;
    default:
        str_oder+="未知:"+QString::number(str.cxpd);
        break;
    }
    Modeview3->append(str_oder);
    // 测向基线
    str_oder=ChangeColor("测向基线: ",mB)+QString::number(str.measureLine);
    Modeview3->append(str_oder);
    // 校正谱通道选择
    str_oder=ChangeColor("校正谱通道选择: ",mB)+QString::number(str.corChannelSel);
    Modeview3->append(str_oder);
    // 测向门限
    str_oder=ChangeColor("测向门限: ",mB)+QString::number(str.cx_oder);
    Modeview3->append(str_oder);
    // 塔康信号下传标志
    str_oder=ChangeColor("塔康信号下传标志: ",mB);
    if(str.tc_downmark&0x01)str_oder+=" 基准脉冲群使能,";
    if(str.tc_downmark&0x02)str_oder+=" 辅助基准脉冲使能,";
    if(str.tc_downmark&0x04)str_oder+=" 识别脉冲使能,";
    if(str.tc_downmark&0x08)str_oder+=" 询问脉冲使能";
    Modeview3->append(str_oder);
    // 校正方式
    str_oder=ChangeColor("校正方式: ",mB);
    switch (str.jz_mand) {
    case 1:
        str_oder+="1:外校正";
        break;
    case 2:
        str_oder+="2:内校正";
        break;
    default:
        str_oder+="未知:"+QString::number(str.jz_mand);
        break;
    }
    Modeview3->append(str_oder);
    // 搜索区域宽度 6.27新加
    str_oder=ChangeColor("搜索区域宽度: ",mB)+QString::number(str.sskd);
    Modeview3->append(str_oder);
    return 0;
}
// 敌我识别信号频点控守
uint Translate::mode_dwsbxh_5(uchar *data)
{

    DW_Signal_Ctrl str;
    memset(&str, 0, sizeof(DW_Signal_Ctrl));
    memcpy(&str,data,sizeof (DW_Signal_Ctrl));

    QString str_oder;
    // 检测通道选择
    str_oder=ChangeColor("检测通道选择: ",mB)+"通道"+QString::number(qToBigEndian(str.examChannelSel)+1);
    Modeview3->append(str_oder);
    // 脉冲最小截取宽度
    str_oder=ChangeColor("脉冲最小截取宽度: ",mB)+QString::number(qToBigEndian(str.pulseWidth_min));
    Modeview3->append(str_oder);
    // 脉冲最大截取宽度
    str_oder=ChangeColor("脉冲最大截取宽度: ",mB)+QString::number(qToBigEndian(str.pulseWidth_max));
    Modeview3->append(str_oder);
    // IFF信号工作模式
    str_oder=ChangeColor("IFF信号工作模式: ",mB);
    switch (qToBigEndian(str.IFF_mode)) {
    case 1:
        str_oder+="1:询问(NCO频率对应1030MHz)";
        break;
    case 2:
        str_oder+="2:应答(NCO频率对应1090MHz)";
        break;
    case 3:
        str_oder+="3:询问和应答";
        break;
    default:
        str_oder+="未知:"+QString::number(qToBigEndian(str.IFF_mode));
        break;
    }
    Modeview3->append(str_oder);
    // 测向基线选择
    str_oder=ChangeColor("测向基线选择: ",mB)+QString::number(str.measureLine);
    Modeview3->append(str_oder);
    // 是否测向
    str_oder=ChangeColor("是否测向: ",mB)+(str.measureFlag ? "1:不测向":"0:测向");
    Modeview3->append(str_oder);

    // 校正谱通道选择
    str_oder=ChangeColor("校正谱通道选择: ",mB)+"通道"+QString::number(qToBigEndian(str.corChannelSel)+1);
    Modeview3->append(str_oder);
    // 步进
    str_oder=ChangeColor("步进: ",mB)+QString::number(qToBigEndian(str.pace));
    Modeview3->append(str_oder);
    // 测向门限
    str_oder=ChangeColor("测向门限: ",mB)+QString::number(str.cx_oder);
    Modeview3->append(str_oder);
    // 敌我识别下传标志
    str_oder=ChangeColor("敌我识别下传标志: ",mB);
    if(str.dw_downmark&0x01)str_oder+=" b0询问123AC使能信号,";
    if(str.dw_downmark&0x02)str_oder+=" b1询问4使能信号,";
    if(str.dw_downmark&0x04)str_oder+=" b2询问S使能信号,";
    if(str.dw_downmark&0x08)str_oder+=" b3讯号5使能信号,";
    if(str.dw_downmark&0x10)str_oder+=" b4应答123AC使能信号,";
    if(str.dw_downmark&0x20)str_oder+=" b5应答4使能信号,";
    if(str.dw_downmark&0x40)str_oder+=" b6应答S使能信号,";
    if(str.dw_downmark&0x80)str_oder+=" b7应答5使能信号";
    Modeview3->append(str_oder);
    // 校正方式
    str_oder=ChangeColor("校正方式: ",mB);
    switch (str.jz_mand) {
    case 1:
        str_oder+="1:外校正";
        break;
    case 2:
        str_oder+="2:内校正";
        break;
    default:
        str_oder+="未知:"+QString::number(str.jz_mand);
        break;
    }
    Modeview3->append(str_oder);
    // 搜索区域宽度 6.27新加
    str_oder=ChangeColor("搜索区域宽度: ",mB)+QString::number(str.sskd);
    Modeview3->append(str_oder);

    return 0;
}
// 铱星信号频点控守
uint Translate::mode_yxxhpdks_6(uchar *data)
{
    YX_Signal_Ctrl str;
    memset(&str, 0, sizeof(YX_Signal_Ctrl));
    memcpy(&str,data,sizeof (YX_Signal_Ctrl));

    QString str_oder;
    // 检测通道选择
    str_oder=ChangeColor("检测通道选择: ",mB)+"通道"+QString::number(qToBigEndian(str.DeTEctionChannel)+1);
    Modeview3->append(str_oder);
    //突发时长 目前固定8ms
    str_oder=ChangeColor("突发时长ms: ",mB)+QString::number(str.uptimeon);
    Modeview3->append(str_oder);
    //检测门限 单位dB
    str_oder=ChangeColor("突发时长dB: ",mB)+QString::number(str.jc_door);
    Modeview3->append(str_oder);
    // 是否测向
    str_oder=ChangeColor("是否测向: ",mB)+(str.measureFlag ? "1:不测向":"0:测向");
    Modeview3->append(str_oder);
    // 测向门限
    str_oder=ChangeColor("测向门限: ",mB)+QString::number(str.cxmx);
    Modeview3->append(str_oder);
    // 测向校正方式
    str_oder=ChangeColor("测向校正方式: ",mB);
    switch (str.jz_manner) {
    case 1:
        str_oder+="1:外校正";
        break;
    case 2:
        str_oder+="2:内校正";
        break;
    default:
        str_oder+="未知:"+QString::number(str.jz_manner);
        break;
    }
    Modeview3->append(str_oder);
    //相关系数
    str_oder=ChangeColor("相关系数: ",mB)+QString::number(str.relationData);
    Modeview3->append(str_oder);
    //特征模板选择
    str_oder=ChangeColor("特征模板选择: ",mB)+QString::number(str.tzmode);
    Modeview3->append(str_oder);
    //Bit判决标志
    str_oder=ChangeColor("Bit判决标志: ",mB);
    switch (str.bitJudge) {
    case 0:
        str_oder+="0:判决";
        break;
    case 1:
        str_oder+="1:不判决";
        break;
    default:
        str_oder+="未知:"+QString::number(str.bitJudge);
        break;
    }
    Modeview3->append(str_oder);
    //通道屏蔽,256个通道，bit值为0表示不屏蔽，为1表示屏蔽
    //32字节暂时不写
    return 0;
}
// 海事信号频点控守
uint Translate::mode_hsxhpdks_7(uchar *data)
{
    HS_Signal_Ctrl str;
    memset(&str, 0, sizeof(HS_Signal_Ctrl));
    memcpy(&str,data,sizeof (HS_Signal_Ctrl));

    QString str_oder;

    str_oder="待补充";
    Modeview3->append(str_oder);

    return 0;
}
// 雷达信号频点控守
uint Translate::mode_ldxhpdks_8(uchar *data)
{
    Radar_Siganl_Ctrl str;
    memset(&str, 0, sizeof(Radar_Siganl_Ctrl));
    memcpy(&str,data,sizeof (Radar_Siganl_Ctrl));

    QString str_oder;
    //接收机频率 KHz
    str_oder=ChangeColor("接收机频率KHz: ",mB)+QString::number(qToBigEndian(str.reFre));
    Modeview3->append(str_oder);
    //NCO频率 单位，Hz
    str_oder=ChangeColor("NCO频率Hz: ",mB)+QString::number(qToBigEndian(str.ncoFre));
    Modeview3->append(str_oder);
    //FPGA检测门限
    str_oder=ChangeColor("FPGA检测门限: ",mB)+QString::number(str.fpgaDoor);
    Modeview3->append(str_oder);
    //下行数据选择
    str_oder=ChangeColor("下行数据选择: ",mB);
    if(str.downchoose&0x01)str_oder+=" b0DSP下行原始PDW数据,";
    if(str.downchoose&0x02)str_oder+=" b1DSP下行分选后PDW数据,";
    if(str.downchoose&0x04)str_oder+=" b2DSP下行PDW-脉内配对数据,";
    if(str.downchoose&0x08)str_oder+=" b3DSP下行EDW数据,";
    if(str.downchoose&0x40)str_oder+=" b6FPGA下行原始PDW数据";
    Modeview3->append(str_oder);
    //处理板NCO频率Hz
    str_oder=ChangeColor("处理板NCO频率Hz: ",mB)+QString::number(qToBigEndian(str.clb_NCO));
    Modeview3->append(str_oder);
    //处理带宽KHz
    str_oder=ChangeColor("处理带宽KHz: ",mB)+QString::number(qToBigEndian(str.cl_wide));
    Modeview3->append(str_oder);
    //参数信息选择
    str_oder=ChangeColor("参数信息选择: ",mB);
    switch (str.csChoose) {
    case 1:
        str_oder+="1:多通道相位信息";
        break;
    case 2:
        str_oder+="2:脉冲幅度信息";
        break;
    default:
        str_oder+="未知:"+QString::number(str.csChoose);
        break;
    }
    Modeview3->append(str_oder);
    //保留
    //分选任务标志
    str_oder=ChangeColor("分选任务标志: ",mB);
    switch (str.groupMark) {
    case 0:
        str_oder+="0:不执行分选";
        break;
    case 1:
        str_oder+="1:执行分选";
        break;
    default:
        str_oder+="未知:"+QString::number(str.groupMark);
        break;
    }
    Modeview3->append(str_oder);
    //精分析任务标志
    str_oder=ChangeColor("精分析任务标志: ",mB)+((str.jfxMark&0x01) ? "1:采集脉内数据,":"0:不采集脉内数据,")
            +((str.jfxMark&0x02) ? " 1:执行精分析任务":" 0:不执行精分析任务");
    Modeview3->append(str_oder);
    //侦察目标选择
    str_oder=ChangeColor("侦察目标选择: ",mB);
    switch (str.zcChoose) {
    case 1:
        str_oder+="1:眼镜蛇";
        break;
    case 2:
        str_oder+="2:费尔康";
        break;
    case 3:
        str_oder+="3:宙斯盾";
        break;
    case 4:
        str_oder+="4:爱国者";
        break;
    case 5:
        str_oder+="5:萨德";
        break;
    case 6:
        str_oder+="6:GBR";
        break;
    case 7:
        str_oder+="7:SBX";
        break;
    case 8:
        str_oder+="8:不启用";
        break;
    default:
        str_oder+="未知:"+QString::number(str.zcChoose);
        break;
    }
    Modeview3->append(str_oder);
    return 0;
}
// 星链信号频点控守参数
uint Translate::mode_xlxhpdks_9(uchar *data)
{


    StarLink_Siganl_Ctrl str;
    memset(&str, 0, sizeof(StarLink_Siganl_Ctrl));
    memcpy(&str,data,sizeof (StarLink_Siganl_Ctrl));

    QString str_oder;
    //接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.re_fre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    //互相关与自相关比值
    str_oder=ChangeColor("互相关与自相关比值: ",mB)+QString::number(str.hx_bz);
    Modeview3->append(str_oder);
    //双窗门限
    str_oder=ChangeColor("双窗门限: ",mB)+QString::number(str.twoMc);
    Modeview3->append(str_oder);
    //NCO路数
    str_oder=ChangeColor("NCO路数: ",mB)+QString::number(str.NCOs);
    Modeview3->append(str_oder);
    //...多个
    //NCO频率
    int cnt=0;
    cnt=str.NCOs;
    if(cnt>8)cnt=8;
    int strp2[cnt];
    memcpy(strp2,data+sizeof (StarLink_Siganl_Ctrl),sizeof (strp2));

    for (int i=0;i<cnt;i++) {
        // NCO频率Khz
        tmp_d=qToBigEndian(strp2[i]);
        str_oder=ChangeColor(QString::number(i+1)+"NCO频率(KHz): ",mB)+QString::number(tmp_d/1000);
        Modeview3->append(str_oder);
    }
    return 0;
}
//同步采样
uint Translate::mode_tbcy_18(uchar *data)
{
    Str_tbCy str;
    memset(&str, 0, sizeof(Str_tbCy));
    memcpy(&str,data,sizeof (Str_tbCy));

    QString str_oder;
    //接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.re_fre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 收发板NCO频率 Hz
    tmp_d=qToBigEndian(str.nco_fre);
    str_oder=ChangeColor("收发板NCO频率KHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 采样次数
    str_oder=ChangeColor("采样次数: ",mB)+QString::number(str.cy_cnt);
    Modeview3->append(str_oder);
    // 单次采样深度(14-30)
    str_oder=ChangeColor("单次采样深度(14-30): ",mB)+QString::number(str.cy_deep);
    Modeview3->append(str_oder);
    return 0;
}
//上注软件解调
uint Translate::mode_up_sorft_20(uchar *data)
{
    Str_upsorft str;
    memset(&str, 0, sizeof(Str_upsorft));
    memcpy(&str,data,sizeof (Str_upsorft));

    QString str_oder;
    //接收机频率KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.re_fre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 频偏 Hz
    tmp_d=qToBigEndian(str.nco_fre);
    str_oder=ChangeColor("频偏KHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 码速率Hz
    tmp_d=qToBigEndian(str.cy_deep);
    str_oder=ChangeColor("频偏KHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    //数据帧数
    str_oder=ChangeColor("数据帧数: ",mB)+QString::number(qToBigEndian(str.data_cnt));
    Modeview3->append(str_oder);
    //样式
    str_oder=ChangeColor("样式    : ",mB);
    switch (str.ys) {
    case 0:
        str_oder+="0:BPSK";
        break;
    case 1:
        str_oder+="1:QPSK";
        break;
    default:
        str_oder+="未知:"+QString::number(str.ys);
        break;
    }
    Modeview3->append(str_oder);
    return 0;
}
//雷达信号频点扫描
uint Translate::mode_ldxhpdsmT_11(uchar *data)
{

    Radar_Siganl_Scan str;
    memset(&str, 0, sizeof(Radar_Siganl_Scan));
    memcpy(&str,data,sizeof (Radar_Siganl_Scan));

    QString str_oder;
    //FPGA检测门限
    str_oder=ChangeColor("FPGA检测门限dB: ",mB)+QString::number(str.fpgaDoor);
    Modeview3->append(str_oder);
    //下行数据选择
    str_oder=ChangeColor("下行数据选择: ",mB);
    if(str.downchoose&0x01)str_oder+=" b0DSP下行原始PDW数据,";
    if(str.downchoose&0x02)str_oder+=" b1DSP下行分选后PDW数据,";
    if(str.downchoose&0x04)str_oder+=" b2DSP下行PDW-脉内IQ配对数据,";
    if(str.downchoose&0x08)str_oder+=" b3DSP下行EDW数据,";
    if(str.downchoose&0x40)str_oder+=" b6FPGA下行原始PDW数据";
    Modeview3->append(str_oder);
    //分选任务标志
    str_oder=ChangeColor("分选任务标志: ",mB);
    switch (str.groupMark) {
    case 0:
        str_oder+="0:不执行分选";
        break;
    case 1:
        str_oder+="1:执行分选";
        break;
    default:
        str_oder+="未知:"+QString::number(str.groupMark);
        break;
    }
    Modeview3->append(str_oder);
    //精分析任务标志
    str_oder=ChangeColor("精分析任务标志: ",mB)+((str.groupMark&0x01) ? "1:采集脉内数据,":"0:不采集脉内数据,")
            +((str.groupMark&0x02) ? " 1:执行精分析任务":" 0:不执行精分析任务");
    Modeview3->append(str_oder);
    //侦察目标选择
    str_oder=ChangeColor("侦察目标选择: ",mB);
    switch (str.zcChoose) {
    case 1:
        str_oder+="1:眼镜蛇";
        break;
    case 2:
        str_oder+="2:费尔康";
        break;
    case 3:
        str_oder+="3:宙斯盾";
        break;
    case 4:
        str_oder+="4:爱国者";
        break;
    case 5:
        str_oder+="5:萨德";
        break;
    case 6:
        str_oder+="6:GBR";
        break;
    case 7:
        str_oder+="7:SBX";
        break;
    case 8:
        str_oder+="8:不启用";
        break;
    default:
        str_oder+="未知:"+QString::number(str.zcChoose);
        break;
    }
    Modeview3->append(str_oder);
    //扫描频点个数
    str_oder=ChangeColor("扫描频点个数: ",mB)+QString::number(str.smFrenum);
    Modeview3->append(str_oder);
    //扫描频点驻留时间
    str_oder=ChangeColor("扫描频点驻留时间(s): ",mB)+QString::number(str.smFreontime);
    Modeview3->append(str_oder);
     //循环体----根据上面扫描频点个数,接收机中心频率单位：KHz
    int cnt=0;
    cnt=str.smFrenum;
    if(cnt>256)cnt=256;
    uint strp2[cnt];
    memcpy(strp2,data+sizeof (Radar_Siganl_Scan),sizeof (strp2));

    for (int i=0;i<cnt;i++) {
        // 接收机中心频率KHz
        uint tmp=qToBigEndian(strp2[i]);
        str_oder=ChangeColor(QString::number(i+1)+"接收机中心频率(KHz): ",mB)+QString::number(tmp);
        Modeview3->append(str_oder);
    }
    return 0;
}
//多频点快速干扰
uint Translate::mode_spgr_13(uchar *data)
{
    //干扰样式
    map<int,QString>grys;

    grys[0]="0:点频";
    grys[1]="1:噪声FM";
    grys[2]="2:单音FM";
    grys[3]="3:FSK";
    grys[4]="4:MSK";
    grys[5]="5:GMSK";
    grys[6]="6:AM";
    grys[7]="7:BPSK";
    grys[8]="8:QPSK";
    grys[9]="9:PSK";
    grys[10]="10:QAM";
    grys[11]="11:扩频BPSK输入";
    grys[12]="12:扩频QPSK输入";

    TxSp_Interfere_Task_Head str;
    memset(&str, 0, sizeof(TxSp_Interfere_Task_Head));
    memcpy(&str,data,sizeof (TxSp_Interfere_Task_Head));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 干扰频率数(频点数≤8个)
    str_oder=ChangeColor("干扰频率数: ",mB)+QString::number(str.interfereNum);
    Modeview3->append(str_oder);

    // 多频点快速干扰--循环体
    int cnt=str.interfereNum;
    TxSp_Interfere_Task str2;
    memset(&str2, 0, sizeof(TxSp_Interfere_Task));
    for (int i=0;i<cnt;i++) {
        memcpy(&str2,data+sizeof (str)+(i*sizeof (str2)),sizeof (str2));
        // 数字频率
        str_oder=ChangeColor(QString::number(i+1)+"数字频率Hz: ",mB)+QString::number(qToBigEndian(str2.digitFre));
        Modeview3->append(str_oder);
        // 模式选择
        str_oder=ChangeColor(QString::number(i+1)+"模式选择: ",mB);
        switch (qToBigEndian(str2.modeSelect)) {
        case 1:
            str_oder+="1:定频干扰";
            break;
        case 2:
            str_oder+="2:扫频干扰";
            break;
        case 3:
            str_oder+="3:Tacan灵巧干扰";
            break;
        case 4:
            str_oder+="4:IFF灵巧干扰";
            break;
        default:
            str_oder+="未知:"+QString::number(qToBigEndian(str2.modeSelect));
            break;
        }
        Modeview3->append(str_oder);
        // 扫频带宽
        str_oder=ChangeColor(QString::number(i+1)+"扫频带宽Hz: ",mB)+QString::number(qToBigEndian(str2.scanWidth));
        Modeview3->append(str_oder);
        // 扫频间隔
        str_oder=ChangeColor(QString::number(i+1)+"扫频间隔Hz: ",mB)+QString::number(qToBigEndian(str2.scanInterval));
        Modeview3->append(str_oder);
        // 扫频驻留时间
        str_oder=ChangeColor(QString::number(i+1)+"扫频驻留时间(us): ",mB)+QString::number(qToBigEndian(str2.scanStandTime));
        Modeview3->append(str_oder);
        // 干扰幅度
        str_oder=ChangeColor(QString::number(i+1)+"干扰幅度(0.1dB): ",mB)+QString::number(qToBigEndian(str2.interfereRange));
        Modeview3->append(str_oder);
        // 干扰样式
        str_oder=ChangeColor(QString::number(i+1)+"干扰样式: ",mB)+grys[str2.interfereStyle];
        Modeview3->append(str_oder);
        // 干扰参数1(带宽/码速率）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数1(带宽/码速率): ",mB)+QString::number(qToBigEndian(str2.interfereParam1));
        Modeview3->append(str_oder);
        // 干扰参数2(FSK频偏）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数2(FSK频偏): ",mB)+QString::number(qToBigEndian(str2.interfereParam2));
        Modeview3->append(str_oder);
        // 干扰参数3(码流选择）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数3(码流选择): ",mB);
        switch (qToBigEndian(str2.interfereParam3)) {
        case 0:
            str_oder+="0:本地伪随机码";
            break;
        case 1:
            str_oder+="1:M码";
            break;
        default:
            str_oder+="未知:"+QString::number(qToBigEndian(str2.interfereParam3));
            break;
        }
        Modeview3->append(str_oder);
        // 干扰参数4(多项式参数）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数4(多项式参数): ",mB)+QString::number(qToBigEndian(str2.interfereParam4));
        Modeview3->append(str_oder);
        // 干扰参数5(多项式参数）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数5(多项式参数): ",mB)+QString::number(qToBigEndian(str2.interfereParam5));
        Modeview3->append(str_oder);


    }


    return 0;
}
// 等间隔梳状谱干扰
uint Translate::mode_szpgr_14(uchar *data)
{
    //干扰样式
    map<int,QString>grys;

    grys[0]="0:点频";
    grys[1]="1:噪声FM";
    grys[2]="2:单音FM";
    grys[3]="3:FSK";
    grys[4]="4:MSK";
    grys[5]="5:GMSK";
    grys[6]="6:AM";
    grys[7]="7:BPSK";
    grys[8]="8:QPSK";
    grys[9]="9:PSK";
    grys[10]="10:QAM";
    grys[11]="11:扩频BPSK输入";
    grys[12]="12:扩频QPSK输入";

    pos_intervarComb_Head str;
    memset(&str, 0, sizeof(pos_intervarComb_Head));
    memcpy(&str,data,sizeof (pos_intervarComb_Head));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 干扰幅度
    str_oder=ChangeColor("干扰幅度(0.1dB): ",mB)+QString::number(qToBigEndian(str.interfereRange));
    Modeview3->append(str_oder);
    // 干扰样式
    str_oder=ChangeColor("干扰样式: ",mB)+grys[str.interfereStyle];
    Modeview3->append(str_oder);
    // 干扰参数1(带宽/码速率）
    str_oder=ChangeColor("干扰参数1(带宽/码速率): ",mB)+QString::number(qToBigEndian(str.interfereParam1));
    Modeview3->append(str_oder);
    // 干扰参数2(FSK频偏）
    str_oder=ChangeColor("干扰参数2(FSK频偏): ",mB)+QString::number(qToBigEndian(str.interfereParam2));
    Modeview3->append(str_oder);
    // 干扰参数3(码流选择）
    str_oder=ChangeColor("干扰参数3(码流选择): ",mB);
    switch (qToBigEndian(str.interfereParam3)) {
    case 0:
        str_oder+="0:本地伪随机码";
        break;
    case 1:
        str_oder+="1:M码";
        break;
    default:
        str_oder+="未知:"+QString::number(qToBigEndian(str.interfereParam3));
        break;
    }
    Modeview3->append(str_oder);
    // 干扰参数4(多项式参数）
    str_oder=ChangeColor("干扰参数4(多项式参数): ",mB)+QString::number(qToBigEndian(str.interfereParam4));
    Modeview3->append(str_oder);
    // 干扰参数5(多项式参数）
    str_oder=ChangeColor("干扰参数5(多项式参数): ",mB)+QString::number(qToBigEndian(str.interfereParam5));
    Modeview3->append(str_oder);
    // 梳状谱段数
    str_oder=ChangeColor("梳状谱段数: ",mB)+QString::number(str.combNum);
    Modeview3->append(str_oder);

    // 等间隔梳状谱干扰--循环体
    int cnt=str.combNum;
    pos_intervarComb_2 str2;
    memset(&str2, 0, sizeof(pos_intervarComb_2));
    for (int i=0;i<cnt;i++) {
        memcpy(&str2,data+sizeof (str)+(i*sizeof (str2)),sizeof (str2));
        // 梳状谱幅度0.1dB
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱幅度0.1dB: ",mB)+QString::number(qToBigEndian(str2.combRange));
        Modeview3->append(str_oder);
        // 梳状谱中心频率hz
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱中心频率hz: ",mB)+QString::number(qToBigEndian(str2.combFre));
        Modeview3->append(str_oder);
        // 梳状谱干扰带宽hz
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱干扰带宽hz: ",mB)+QString::number(qToBigEndian(str2.combWidth));
        Modeview3->append(str_oder);
        // 梳状谱干扰间隔hz
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱干扰间隔hz: ",mB)+QString::number(qToBigEndian(str2.combinterval));
        Modeview3->append(str_oder);
    }
    return 0;
}
// 非等间隔梳状谱干扰
uint Translate::mode_not_szpgr_15(uchar *data)
{
    //干扰样式
    map<int,QString>grys;

    grys[0]="0:点频";
    grys[1]="1:噪声FM";
    grys[2]="2:单音FM";
    grys[3]="3:FSK";
    grys[4]="4:MSK";
    grys[5]="5:GMSK";
    grys[6]="6:AM";
    grys[7]="7:BPSK";
    grys[8]="8:QPSK";
    grys[9]="9:PSK";
    grys[10]="10:QAM";
    grys[11]="11:扩频BPSK输入";
    grys[12]="12:扩频QPSK输入";

    nav_IntervarCombk_HEAD str;
    memset(&str, 0, sizeof(nav_IntervarCombk_HEAD));
    memcpy(&str,data,sizeof (nav_IntervarCombk_HEAD));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 干扰幅度
    str_oder=ChangeColor("干扰幅度(0.1dB): ",mB)+QString::number(qToBigEndian(str.interfereRange));
    Modeview3->append(str_oder);
    // 干扰样式
    str_oder=ChangeColor("干扰样式: ",mB)+grys[str.interfereStyle];
    Modeview3->append(str_oder);
    // 干扰参数1(带宽/码速率）
    str_oder=ChangeColor("干扰参数1(带宽/码速率): ",mB)+QString::number(qToBigEndian(str.interfereParam1));
    Modeview3->append(str_oder);
    // 干扰参数2(FSK频偏）
    str_oder=ChangeColor("干扰参数2(FSK频偏): ",mB)+QString::number(qToBigEndian(str.interfereParam2));
    Modeview3->append(str_oder);
    // 干扰参数3(码流选择）
    str_oder=ChangeColor("干扰参数3(码流选择): ",mB);
    switch (str.interfereParam3) {
    case 0:
        str_oder+="0:本地伪随机码";
        break;
    case 1:
        str_oder+="1:M码";
        break;
    default:
        str_oder+="未知:"+QString::number(str.interfereParam3);
        break;
    }
    Modeview3->append(str_oder);
    // 干扰参数4(多项式参数）
    str_oder=ChangeColor("干扰参数4(多项式参数): ",mB)+QString::number(qToBigEndian(str.interfereParam4));
    Modeview3->append(str_oder);
    // 干扰参数5(多项式参数）
    str_oder=ChangeColor("干扰参数5(多项式参数): ",mB)+QString::number(qToBigEndian(str.interfereParam5));
    Modeview3->append(str_oder);
    // 梳状谱段数
    str_oder=ChangeColor("梳状谱段数: ",mB)+QString::number(qToBigEndian(str.combFreNum));
    Modeview3->append(str_oder);

    // 等间隔梳状谱干扰--循环体
    int cnt=qToBigEndian(str.combFreNum);
    nav_IntervarComb_2 str2;
    memset(&str2, 0, sizeof(nav_IntervarComb_2));
    for (int i=0;i<cnt;i++) {
        memcpy(&str2,data+sizeof (str)+(i*sizeof (str2)),sizeof (str2));
        // 梳状谱干扰幅度
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱幅度0.1dB: ",mB)+QString::number(qToBigEndian(str2.comInterfereRange));
        Modeview3->append(str_oder);
        // 梳状谱干扰频率
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱中心频率hz: ",mB)+QString::number(qToBigEndian(str2.comInterfereFre));
        Modeview3->append(str_oder);
    }
    return 0;
}
// 多通道快速协同干扰
uint Translate::mode_dhmbgr_T16(uchar *data)
{

    //干扰样式
    map<int,QString>grys;

    grys[0]="0:点频";
    grys[1]="1:噪声FM";
    grys[2]="2:单音FM";
    grys[3]="3:FSK";
    grys[4]="4:MSK";
    grys[5]="5:GMSK";
    grys[6]="6:AM";
    grys[7]="7:BPSK";
    grys[8]="8:QPSK";
    grys[9]="9:8PSK";
    grys[10]="10:QAM";
    grys[11]="11:CA/P码";
    grys[12]="12:P码";
    grys[13]="13:CP码信号";
    grys[14]="14:伪随机QPSK";



    target_interfere_Task str;
    memset(&str, 0, sizeof(target_interfere_Task));
    memcpy(&str,data,sizeof (target_interfere_Task));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    //L1，L2是否同步
    str_oder=ChangeColor("L1,L2是否同步:",mB);
    switch (str.L1_L2) {
    case 0:
        str_oder+="0:只发L1";
        break;
    case 1:
        str_oder+="1:只发L2";
        break;
    case 2:
        str_oder+="2:同时发L1和L2";
        break;
    default:
        str_oder+="未知:"+QString::number(str.L1_L2);
        break;
    }
    Modeview3->append(str_oder);
    // 子阵1、2第一级16个干扰信号数字频率
    str_oder=ChangeColor("子阵1、2第一级16个数字频率: ",mB)+QString::number(qToBigEndian(str.zz1216grxhszpl));
    Modeview3->append(str_oder);
    // 子阵3、4第一级16个干扰信号数字频率
    str_oder=ChangeColor("子阵3、4第一级16个数字频率: ",mB)+QString::number(qToBigEndian(str.zz3416grxhszpl));
    Modeview3->append(str_oder);
    // 子阵1、2 QPSK数字频率
    str_oder=ChangeColor("子阵1、2 QPSK数字频率: ",mB)+QString::number(qToBigEndian(str.zz12QPSKszpl));
    Modeview3->append(str_oder);
    // 子阵1、2 QPSK数字信号开关 0：关闭；1：开启
    str_oder=ChangeColor("子阵1、2 QPSK数字信号开关: ",mB)+(str.zz12QPSKszxhkg ? "1:开启":"0:关闭");
    Modeview3->append(str_oder);
    // 子阵1、2 QPSK数字信号符号速率
    str_oder=ChangeColor("子阵1、2 QPSK数字信号符号速率: ",mB)+QString::number(qToBigEndian(str.zz12QPSKszxhfhsl));
    Modeview3->append(str_oder);
    // 子阵1、2 QPSK数字信号干扰幅度 单位：0.1dB
    str_oder=ChangeColor("子阵1、2 QPSK数字信号干扰幅度0.1dB: ",mB)+QString::number(qToBigEndian(str.zz12QPSKszxhgrfd));
    Modeview3->append(str_oder);
    // 子阵3、4 QPSK数字频率
    str_oder=ChangeColor("子阵3、4 QPSK数字频率: ",mB)+QString::number(qToBigEndian(str.zz34QPSKszpl));
    Modeview3->append(str_oder);
    // 子阵3、4 QPSK数字信号 开 关
    str_oder=ChangeColor("子阵3、4 QPSK数字信号开关: ",mB)+(str.zz34QPSKszxhkg ? "1:开启":"0:关闭");
    Modeview3->append(str_oder);
    // 子阵3、4 QPSK数字信号符号速率
    str_oder=ChangeColor("子阵3、4 QPSK数字信号符号速率: ",mB)+QString::number(qToBigEndian(str.zz34QPSKszxhfhsl));
    Modeview3->append(str_oder);
    // 子阵3、4 QPSK数字信号干扰幅度 单 位：0.1dB
    str_oder=ChangeColor("子阵3、4 QPSK数字信号干扰幅度0.1dB: ",mB)+QString::number(qToBigEndian(str.zz34QPSKszxhgrfd));
    Modeview3->append(str_oder);
    // 子阵1、2的16个干扰信号个数
    str_oder=ChangeColor("子阵1、2的16个干扰信号个数: ",mB)+QString::number(str.zz1216grxhgs);
    Modeview3->append(str_oder);
    // 子阵3、4的16个干扰信号个数
    str_oder=ChangeColor("子阵3、4的16个干扰信号个数: ",mB)+QString::number(str.zz3416grxhgs);
    Modeview3->append(str_oder);

    // 多通道快速协同干扰---循环体
    int cnt=str.zz1216grxhgs+str.zz3416grxhgs;
    target_interfere_Task_2 str2;
    memset(&str2, 0, sizeof(target_interfere_Task_2));

    for (int i=0;i<cnt;i++) {
        memcpy(&str2,data+sizeof (str)+(i*sizeof (str2)),sizeof (str2));

        // 数字频率
        str_oder=ChangeColor(QString::number(i+1)+"数字频率NCO: ",mB)+QString::number(qToBigEndian(str2.digitFre));
        Modeview3->append(str_oder);
        // 干扰幅度 单位：0.1dB
        str_oder=ChangeColor(QString::number(i+1)+"干扰幅度0.1dB: ",mB)+QString::number(qToBigEndian(str2.interfereRange));
        Modeview3->append(str_oder);
        // 干扰样式
        str_oder=ChangeColor(QString::number(i+1)+"干扰样式: ",mB)+grys[str2.interfereStyle];
        Modeview3->append(str_oder);
        // 干扰参数1(带宽/码速率）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数1(带宽Hz/码速率): ",mB)+QString::number(qToBigEndian(str2.interfereParam1));
        Modeview3->append(str_oder);
        // 干扰参数2(FSK频偏）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数2(FSK频偏): ",mB)+QString::number(qToBigEndian(str2.interfereParam2));
        Modeview3->append(str_oder);
        // 干扰参数3(码流选择）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数3(码流选择): ",mB)+QString::number(str2.interfereParam3);
        Modeview3->append(str_oder);
        // 干扰参数4(多项式参数）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数4(多项式参数): ",mB)+QString::number(str2.interfereParam4);
        Modeview3->append(str_oder);
        // 干扰参数5(预留）
        str_oder=ChangeColor(QString::number(i+1)+"干扰参数5(预留): ",mB)+QString::number(qToBigEndian(str2.interfereParam5));
        Modeview3->append(str_oder);
    }


    return 0;
}
//多通道多带宽协同干扰
uint Translate::mode_xlmbgr_T17(uchar *data)
{
    //干扰样式
    map<int,QString>grys;

    grys[0]="0:点频";
    grys[1]="1:噪声FM";
    grys[2]="2:单音FM";
    grys[3]="3:FSK";
    grys[4]="4:MSK";
    grys[5]="5:GMSK";
    grys[6]="6:AM";
    grys[7]="7:BPSK";
    grys[8]="8:QPSK";
    grys[9]="9:8PSK";
    grys[10]="10:QAM";
    grys[11]="11:CA/P码";
    grys[12]="12:P码";
    grys[13]="13:CP码信号";
    grys[14]="14:伪随机QPSK";



    StarLink_Siganl_Task str;
    memset(&str, 0, sizeof(StarLink_Siganl_Task));
    memcpy(&str,data,sizeof (StarLink_Siganl_Task));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    // 干扰幅度 单位：0.1dB
    str_oder=ChangeColor("干扰幅度0.1dB: ",mB)+QString::number(qToBigEndian(str.interfereRange));
    Modeview3->append(str_oder);
    // 干扰样式
    str_oder=ChangeColor("干扰样式: ",mB)+grys[str.interfereStyle];
    Modeview3->append(str_oder);
    // 干扰参数1(带宽/码速率）
    str_oder=ChangeColor("干扰参数1(带宽Hz/码速率): ",mB)+QString::number(qToBigEndian(str.interfereParam1));
    Modeview3->append(str_oder);
    // 干扰参数2(FSK频偏）
    str_oder=ChangeColor("干扰参数2(FSK频偏): ",mB)+QString::number(qToBigEndian(str.interfereParam2));
    Modeview3->append(str_oder);
    // 干扰参数3(码流选择）
    str_oder=ChangeColor("干扰参数3(码流选择): ",mB)+QString::number(qToBigEndian(str.interfereParam3));
    Modeview3->append(str_oder);
    // 干扰参数4(多项式参数）
    str_oder=ChangeColor("干扰参数4(多项式参数): ",mB)+QString::number(qToBigEndian(str.interfereParam4));
    Modeview3->append(str_oder);
    // 干扰参数5(预留）
    str_oder=ChangeColor("干扰参数5(多项式参数): ",mB)+QString::number(qToBigEndian(str.interfereParam5));
    Modeview3->append(str_oder);
    // 梳状谱1扫频开关
    str_oder=ChangeColor("梳状谱1扫频开关: ",mB)+(str.szp1spkg ? "1:开启":"0:关闭");
    Modeview3->append(str_oder);
    // 梳状谱1扫频总带宽
    str_oder=ChangeColor("梳状谱1扫频总带宽: ",mB)+QString::number(qToBigEndian(str.szp1spzdk));
    Modeview3->append(str_oder);
    // 梳状谱1扫频速度
    str_oder=ChangeColor("梳状谱1扫频速度: ",mB)+QString::number(qToBigEndian(str.szp1spsd));
    Modeview3->append(str_oder);
    // 梳状谱段数1
    str_oder=ChangeColor("梳状谱段数1: ",mB)+QString::number(str.szpds1);
    Modeview3->append(str_oder);

    // 多通道多带宽协同干扰(星链目标干扰)---循环体
    int cnt=qToBigEndian(str.szpds1);
    StarLink_Siganl_Task_1 str2;
    memset(&str2, 0, sizeof(StarLink_Siganl_Task_1));
    for (int i=0;i<cnt;i++) {
        memcpy(&str2,data+sizeof (str)+(i*sizeof (str2)),sizeof (str2));
        // 梳状谱中心频率hz
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱中心频率hz: ",mB)+QString::number(qToBigEndian(str2.combFre));
        Modeview3->append(str_oder);
        // 梳状谱干扰带宽hz
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱干扰带宽hz: ",mB)+QString::number(qToBigEndian(str2.combWidth));
        Modeview3->append(str_oder);
        // 梳状谱干扰间隔
        str_oder=ChangeColor(QString::number(i+1)+"梳状谱干扰间隔: ",mB)+QString::number(qToBigEndian(str2.combinterval));
        Modeview3->append(str_oder);
    }
    return 0;
}
//雷达强制干扰
uint Translate::mode_LD_QZgr18(uchar *data)
{
    //干扰样式
    map<int,QString>grys;

    grys[0]="0:点频";
    grys[1]="1:噪声FM";
    grys[2]="2:未知";
    grys[3]="3:未知";
    grys[4]="4:未知";
    grys[5]="5:未知";
    grys[6]="6:未知";
    grys[7]="7:BPSK";
    grys[8]="8:QPSK";
    grys[9]="9:未知";
    grys[10]="10:未知";
    grys[11]="11:未知";
    grys[12]="12:未知";
    grys[13]="13:未知";
    grys[14]="14:未知";
    grys[15]="15:线性调频";
    grys[16]="16:脉冲";
    Radar_force_Task str;
    memset(&str, 0, sizeof(Radar_force_Task));
    memcpy(&str,data,sizeof (Radar_force_Task));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    //1234通道频偏开启
    str_oder=ChangeColor("1234通道频偏开启: ",mB)+(str.fSwitch1234 ? "1:开启":"0:关闭");
    Modeview3->append(str_oder);
    //13通道频偏
    str_oder=ChangeColor("13通道频偏Hz: ",mB)+QString::number(qToBigEndian(str.ad13fpre));
    Modeview3->append(str_oder);
    //24通道频偏
    str_oder=ChangeColor("24通道频偏Hz: ",mB)+QString::number(qToBigEndian(str.ad24fpre));
    Modeview3->append(str_oder);
    //干扰样式
    str_oder=ChangeColor("干扰样式: ",mB)+grys[str.grMode];
    Modeview3->append(str_oder);
    //干扰参数1（带宽/码速率）
    str_oder=ChangeColor("干扰参数1(带宽/码速率): ",mB)+QString::number(qToBigEndian(str.gr_data1));
    Modeview3->append(str_oder);
    //干扰参数2
    str_oder=ChangeColor("干扰参数2: ",mB)+QString::number(qToBigEndian(str.gr_data2));
    Modeview3->append(str_oder);
    //干扰频点数
    str_oder=ChangeColor("干扰频点数: ",mB)+QString::number(qToBigEndian(str.gr_frenum));
    Modeview3->append(str_oder);


    // 雷达强制干扰任务格式--循环体
    int cnt=qToBigEndian(str.gr_frenum);
    CYC_force_Task str2;
    memset(&str2, 0, sizeof(CYC_force_Task));
    for (int i=0;i<cnt;i++) {
        memcpy(&str2,data+sizeof (str)+(i*sizeof (str2)),sizeof (str2));
        //谱线干扰幅度dB
        str_oder=ChangeColor(QString::number(i+1)+"谱线干扰幅度dB: ",mB)+QString::number(qToBigEndian(str2.px_grdB));
        Modeview3->append(str_oder);
        //谱线基带频率Hz
        str_oder=ChangeColor(QString::number(i+1)+"谱线基带频率Hz: ",mB)+QString::number(qToBigEndian(str2.px_fre));
        Modeview3->append(str_oder);

    }
    return 0;
}
//雷达侦察干扰
uint Translate::mode_LD_T19(uchar *data)
{
    //干扰样式
    map<int,QString>grys;


    grys[1]="1:眼镜蛇";
    grys[2]="2:费尔康";
    grys[3]="3:宙斯盾";
    grys[4]="4:爱国者";
    grys[5]="5:萨德";
    grys[6]="6:GBR";
    grys[7]="7:SBX";


    Radar_Interfer_Task str;
    memset(&str, 0, sizeof(Radar_Interfer_Task));
    memcpy(&str,data,sizeof (Radar_Interfer_Task));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.recFre);
    str_oder=ChangeColor("接收机频率MHz: ",mB)+QString::number(tmp_d/1000);
    Modeview3->append(str_oder);
    //1234通道频偏开启
    str_oder=ChangeColor("1234通道频偏开启: ",mB)+(str.fSwitch1234 ? "1:开启":"0:关闭");
    Modeview3->append(str_oder);
    //13通道频偏
    str_oder=ChangeColor("13通道频偏Hz: ",mB)+QString::number(qToBigEndian(str.ad13fpre));
    Modeview3->append(str_oder);
    //24通道频偏
    str_oder=ChangeColor("24通道频偏Hz: ",mB)+QString::number(qToBigEndian(str.ad24fpre));
    Modeview3->append(str_oder);
    //侦察参数--侦察目标选择
    str_oder=ChangeColor("侦察目标选择: ",mB)+grys[str.zc_maskchoose];
    Modeview3->append(str_oder);
    //处理板NCO频率
    str_oder=ChangeColor("处理板NCO频率Hz: ",mB)+QString::number(qToBigEndian(str.clb_nco));
    Modeview3->append(str_oder);
    //处理带宽
    str_oder=ChangeColor("处理带宽KHz: ",mB)+QString::number(qToBigEndian(str.clWide));
    Modeview3->append(str_oder);
    //干扰策略
    str_oder=ChangeColor("干扰策略: ",mB)+"策略"+QString::number(str.gr_cl);
    Modeview3->append(str_oder);
    //侦察参数--检测门限
    str_oder=ChangeColor("检测门限: ",mB)+QString::number(str.zc_jcmx);
    Modeview3->append(str_oder);
    //保护载频上限_1 hz
    str_oder=ChangeColor("保护载频上限_1(Hz): ",mB)+QString::number(qToBigEndian(str.gr_protecU1));
    Modeview3->append(str_oder);
    //保护载频下限_1
    str_oder=ChangeColor("保护载频下限_1(Hz): ",mB)+QString::number(qToBigEndian(str.gr_protecD1));
    Modeview3->append(str_oder);
    //保护载频上限_2
    str_oder=ChangeColor("保护载频上限_2(Hz): ",mB)+QString::number(qToBigEndian(str.gr_protecU2));
    Modeview3->append(str_oder);
    //保护载频下限_2
    str_oder=ChangeColor("保护载频下限_2(Hz): ",mB)+QString::number(qToBigEndian(str.gr_protecD2));
    Modeview3->append(str_oder);


    return 0;
}
//类5G模式参数
uint Translate::mode_L5G_T22(uchar *data)
{

    //调制编码索引
    map<int,QString>sy;


    sy[2]="2:QPSK、编码码率0.4301、单波束速率111.19Mbps";
    sy[3]="3:QPSK、编码码率0.8603、单波束速率222.39Mbps";
    sy[4]="4:16QAM、编码码率0.4314、单波束速率222.39Mbps";
    sy[5]="5:16QAM、编码码率0.6471、单波束速率333.59Mbps";
    sy[6]="6:16QAM、编码码率0.8603、单波束速率444.78Mbps";
    sy[7]="7:64QAM、编码码率0.5735、单波束速率444.78Mbps";
    sy[8]="8:64QAM、编码码率0.7213、单波束速率555.98Mbps";
    sy[9]="9:64QAM、编码码率0.8627、单波束速率667.18Mbps";


    L5G_Str str;
    memset(&str, 0, sizeof(L5G_Str));
    memcpy(&str,data,sizeof (L5G_Str));

    QString str_oder;
    // 接收机频率 KHz
    double tmp_d=0.0;
    tmp_d=qToBigEndian(str.fre);
    str_oder=ChangeColor("接收机频率KHz: ",mB)+QString::number(tmp_d);
    Modeview3->append(str_oder);
    //门限
    str_oder=ChangeColor("门限: ",mB)+QString::number(qToBigEndian(str.l5_mx));
    Modeview3->append(str_oder);
    //调制编码索引
    str_oder=ChangeColor("调制编码索引: ",mB)+sy[str.codeIndex];
    Modeview3->append(str_oder);
    //DA幅度校平衰减1
    str_oder=ChangeColor("DA幅度校平衰减1: ",mB)+QString::number(str.DA1);
    Modeview3->append(str_oder);
    //DA幅度校平衰减2
    str_oder=ChangeColor("DA幅度校平衰减2: ",mB)+QString::number(str.DA2);
    Modeview3->append(str_oder);
    //DA幅度校平衰减3
    str_oder=ChangeColor("DA幅度校平衰减3: ",mB)+QString::number(str.DA3);
    Modeview3->append(str_oder);
    //DA幅度校平衰减4
    str_oder=ChangeColor("DA幅度校平衰减4: ",mB)+QString::number(str.DA4);
    Modeview3->append(str_oder);
    //保留

    //数传文件数量
    str_oder=ChangeColor("数传文件数量: ",mB)+QString::number(str.fileSum);
    Modeview3->append(str_oder);
    return 0;

}
//任务执行设置
uint Translate::Gkcontrol1_rwzx(uchar *data)
{
    Task_execute_set tes;
    memset(&tes, 0, sizeof(tes));
    memcpy(&tes,data,sizeof(tes));

    QString str_oder;
    // 指令标识
    str_oder=ChangeColor("指令标识: ",mB)+"0x"+QString::number(tes.ordermark,16);
    Modeview1->append(str_oder);
    // 任务类型
    str_oder=ChangeColor("分选任务标志: ",mB);
    switch (tes.task_type) {
    case 1:
        str_oder+="0x01:运维管控任务";
        break;
    case 2:
        str_oder+="0x02:自主区域任务";
        break;
    case 3:
        str_oder+="0x03:常规任务";
        break;
    default:
        str_oder+="未知:"+QString::number(tes.task_type);
        break;
    }
    Modeview1->append(str_oder);
    // 时间长度
//    str_oder=ChangeColor("时间长度: ",mB)+(tes.time_len);
//    Modeview1->append(str_oder);
    // 任务流水号
    str_oder=ChangeColor("任务流水号: ",mB)+QString::number(qToBigEndian(tes.task_number));
    Modeview1->append(str_oder);
    //功能模式段数
    str_oder=ChangeColor("功能模式段数: ",mB)+QString::number(tes.Mode_Fun_cnt);
    Modeview1->append(str_oder);
    //功能模式1开始时间
    str_oder=ChangeColor("功能模式1开始时间: ",mB)+QString::number(qToBigEndian(tes.mode1_starts));
    Modeview1->append(str_oder);
    //功能模式1结束时间
    str_oder=ChangeColor("功能模式1结束时间: ",mB)+QString::number(qToBigEndian(tes.mode1_ends));
    Modeview1->append(str_oder);
    //功能模式1
    str_oder=ChangeColor("功能模式1: ",mB)+(UP_fun_mode[tes.mode1_choose]);
    Modeview1->append(str_oder);
    //功能模式2开始时间
    str_oder=ChangeColor("功能模式2开始时间: ",mB)+QString::number(qToBigEndian(tes.mode2_starts));
    Modeview1->append(str_oder);
    //功能模式2结束时间
    str_oder=ChangeColor("功能模式2开始时间: ",mB)+QString::number(qToBigEndian(tes.mode2_ends));
    Modeview1->append(str_oder);
    //功能模式2
    str_oder=ChangeColor("功能模式2: ",mB)+(UP_fun_mode[tes.mode2_choose]);
    Modeview1->append(str_oder);

    return 0;
}











