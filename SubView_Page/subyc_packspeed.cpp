#include "subyc_packspeed.h"
#include "ui_subyc_packspeed.h"

#include "Globel_Define.h"

subyc_packspeed::subyc_packspeed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subyc_packspeed)
{
    ui->setupUi(this);
    Outpack_dj=0;

    //qDebug()<<sizeof (Pack_YCdata);
    // 修改界面表格
    model = new QStandardItemModel(ui->tView_packyclist);
    QStringList m_name_list;
    m_name_list.append("遥测名称");
    m_name_list.append("数值");
    m_name_list.append("32路雷达计算机遥测");
    m_name_list.append("数值");
    m_name_list.append("波控遥测");
    m_name_list.append("数值");
    //    m_name_list.append("4");
    //    m_name_list.append("数值");
    int num = m_name_list.size();
    model->setColumnCount(num);
    model->setRowCount(0);
    for (int i = 0; i < num; i++) {
        model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
    }

    QStringList msyc_strName_1;
    msyc_strName_1.append("本地时间");
    msyc_strName_1.append("SAR开机时间");
    msyc_strName_1.append("系统工作状态");
    msyc_strName_1.append("收指令计数");
    msyc_strName_1.append("分系统状态");
    msyc_strName_1.append("指令执行情况");
    msyc_strName_1.append("串注间接指令码");
    msyc_strName_1.append("指令队列长度");
    //msyc_strName_1.append("成像模式字");
    msyc_strName_1.append("成像模式字_极化方式");
    msyc_strName_1.append("成像模式字_通道模式");
    msyc_strName_1.append("成像模式字_成像模式");

    msyc_strName_1.append("任务类型");
    msyc_strName_1.append("任务号");
    msyc_strName_1.append("子任务号");
    msyc_strName_1.append("星上计算控制码");
    msyc_strName_1.append("子带个数");
//    msyc_strName_1.append("实时成像参数1");
    msyc_strName_1.append("参数1_图像输出选择");
    msyc_strName_1.append("参数1_量化方式选择");
//    msyc_strName_1.append("实时成像参数2");
    msyc_strName_1.append("参数2_海陆分割模式");
    msyc_strName_1.append("参数2_舰船检测模式");
    msyc_strName_1.append("参数2_舰船军民分类");
    msyc_strName_1.append("参数2_舰船精聚焦");
    msyc_strName_1.append("参数2_舰船目标定位");
    msyc_strName_1.append("参数2_输出切片选择");
    msyc_strName_1.append("参数2_输出文本信息");

    msyc_strName_1.append("EDAC错误计数");
    msyc_strName_1.append("CPU复位计数");

    for (int i = 0; i < msyc_strName_1.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_1.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
//        model->setItem(i, 0, new QStandardItem(msyc_strName_1.at(i)));
        model->setItem(i, 0, table_item);
    }


    ui->tView_packyclist->setModel(model);  //(设置宽度要在后面)
    ui->tView_packyclist->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 是否可编辑
    //  ui->tView_packyclist->setColumnWidth(1,00);//设置第0列宽100
    ui->tView_packyclist->resizeColumnToContents(0);  // 设置第0列宽度自适应内容
    ui->tView_packyclist->resizeColumnToContents(2);  // 设置第2列宽度自适应内容
    ui->tView_packyclist->resizeColumnToContents(4);  // 设置第4列宽度自适应内容
    ui->tView_packyclist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tView_packyclist->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tView_packyclist->horizontalHeader()->setMinimumSectionSize(100);
    //  ui->tView_packyclist->resizeColumnsToContents();//设置所有列宽度自适应
    //   ui->tView_packyclist->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);//设置第1列(表头)自动
    //   ui->tView_packyclist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置所有列自动
}

subyc_packspeed::~subyc_packspeed()
{
    delete ui;
}


//处理数据
void subyc_packspeed::Get_PackYcData(ushort *Rxbuff, int Rxlen,int ch) {

    if(ch!=Outpack_dj)return ;//暂时接收通道1
    //        打印显示
    //        qDebug()<<"pack_yc:";
    //        for(int i=0;i<Rxlen;i++)
    //        {
    //            printf("%04x ",Rxbuff[i]);

    //        }
    //        printf("\n");

    // 开辟缓存存储4帧*32字 数据
    ushort *Tran_Buff = new ushort[Rxlen];
    memset(Tran_Buff, 0, Rxlen * 2);
    QString ss;
    for (int i = 0; i < Rxlen; i++) {
        QString s1 =QString("%1 ").arg(Rxbuff[i], 4, 16, QLatin1Char('0')).toUpper();
        Tran_Buff[i] = qToBigEndian(Rxbuff[i]);
        ss.append(s1);
    }
    //qDebug() << ss;
    // 拷贝到遥测结构体
    Pack_YCdata strYC;
    memcpy(&strYC, Tran_Buff, sizeof(strYC));
    delete[] Tran_Buff;

    int colcnt = 0;
    QString qstr;
    uchar tmp_uchar = 0;
    //double tmp_double = 0;
    uint tmp_uint=0;
    uint tmp_ushort=0;

    // 主头版本号，包标志0x073E;
    if (strYC.Pack_Head != 0x3E07) return;
    // 主头包顺序控制
    //qDebug() << qToBigEndian(strYC.Pack_Number);
    // 主头包长度
    //qDebug() << qToBigEndian(strYC.Pack_Len);

    //遥测内容。。。。。。
    //本地时间码
    tmp_uint = strYC.curr_time;
    qstr = QString::number(qToBigEndian(tmp_uint)*6.5536);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //SAR开机时间
    tmp_ushort = strYC.open_time;
    qstr = QString::number(qToBigEndian(tmp_ushort));
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //系统工作状态
    tmp_uchar = strYC.sys_status;
    //qstr = "0x"+QString::number(tmp_uchar,16);
    qstr = QString("0x%1").arg(tmp_uchar,2,16,QLatin1Char('0')).toUpper();
    if(tmp_uchar==0) qstr ="0H:初态、待命及关机状态";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //收指令计数
    qstr = QString::number(strYC.order_cnt);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //分系统状态
    tmp_uchar = (strYC.sys_work&0xF0)>>4;
    switch (tmp_uchar) {
    case 0:
        qstr="0:SAR初态";
        break;
    case 3:
        qstr="3:待命状态";
        break;
    case 5:
        qstr="5:SAR准备";
        break;
    case 9:
        qstr="9:成像状态:SAR输出数据";
        break;
    case 0x0A:
        qstr="A:开机状态:SAR正在开机";
        break;
    case 0x0D:
        qstr="D:关机状态:SAR关机";
        break;
    case 0x0E:
        qstr="E:故障状态:SAR故障";
        break;
    default:
        qstr = "0x"+QString::number(tmp_uchar,16);
        break;
    }
    //qstr = "0x"+QString::number(tmp_uchar,16);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //及指令执行情况
    tmp_uchar = (strYC.sys_work&0x0F);
    switch (tmp_uchar) {
    case 0:
        qstr="0:SAR初态";
        break;
    case 3:
        qstr="3:指令包正确";
        break;
    case 5:
        qstr="5:指令包格式错误";
        break;
    case 6:
        qstr="6:指令包内容错误";
        break;
    case 9:
        qstr="9:指令包配合错误";
        break;
    case 0x0A:
        qstr="A:指令包执行正确";
        break;
    case 0x0C:
        qstr="C:间接指令执行错误";
        break;
    case 0x0D:
        qstr="D:SAR工作包/工作参数包过期";
        break;
    case 0x0F:
        qstr="F:指令队列满";
        break;
    default:
        qstr = "0x"+QString::number(tmp_uchar,16);
        break;
    }

    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //串注间接指令码
    qstr = QString::number(strYC.jz_zlcode);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //指令队列长度
    tmp_ushort = strYC.zl_teamLen;
    qstr = QString::number(qToBigEndian(tmp_ushort));
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //成像模式字
//    qstr ="0x"+ QString::number(strYC.cx_mode,16);
//    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D7：极化方式
    tmp_uchar = (strYC.cx_mode&0x80)>>7;
    if(tmp_uchar==0)qstr="HH";
    else qstr="VV";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D6-D5：通道模式
    tmp_uchar = (strYC.cx_mode&0x60)>>5;
    switch (tmp_uchar) {
    case 0:
        qstr="0:双通道A模式";
        break;
    case 1:
        qstr="1:双通道B模式";
        break;
    case 2:
        qstr="2:单通道A模式";
        break;
    case 3:
        qstr="3:单通道B模式";
        break;
    default:
        qstr="";
        break;
    }
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D4：保留
    //D3-D0：成像模式
    tmp_uchar = strYC.cx_mode&0x0F;
    switch (tmp_uchar) {
    case 0:
        qstr="0:连续测试定标";
        break;
    case 1:
        qstr="1:广域搜索模式";
        break;
    case 2:
        qstr="2:滑动聚束";
        break;
    case 3:
        qstr="3:条带模式1（2m）";
        break;
    case 4:
        qstr="4:条带模式2（3m）";
        break;
    case 5:
        qstr="5:TOP模式1（2子带）";
        break;
    case 6:
        qstr="6:TOP模式2（4子带）";
        break;
    case 7:
        qstr="7:多角度模式";
        break;
    default:
        qstr="";
        break;
    }
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //任务类型
    tmp_ushort = strYC.mask_kind;
    qstr ="0x"+ QString::number(tmp_ushort,16);

    //任务号
    tmp_ushort = strYC.mask_number;
    qstr = QString::number(qToBigEndian(tmp_ushort));
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //子任务号
    tmp_ushort = strYC.sub_masknum;
    qstr = QString::number(qToBigEndian(tmp_ushort));
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //本次成像聚束中心时刻星上计算控制码
    tmp_uchar = (strYC.starts_cnt&0x80)>>7;
    if(tmp_uchar==0)qstr="0:采用地面上注聚束中心时刻";
    else qstr="1:星上计算聚束中心时刻";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //及子带个数
    tmp_uchar = strYC.starts_cnt&0x3F;
    qstr = QString::number(tmp_uchar);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //实时成像参数1
    //D7-D6：图像输出选择
    tmp_uchar = (strYC.ss1&0xC0)>>6;
    switch (tmp_uchar) {
    case 0:
        qstr="0:正常截取输出(灰度图)";
        break;
    case 1:
        qstr="1:根据设置截取点数截取(灰度图)";
        break;
    case 2:
        qstr="2:正常截取输出(复图)";
        break;
    case 3:
        qstr="3:全输出(复图)";
        break;
    default:
        qstr="";
        break;
    }
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D5-D4：量化方式选择
    tmp_uchar = (strYC.ss1&0x30)>>4;
    switch (tmp_uchar) {
    case 0:
        qstr="0:飞机量化";
        break;
    case 1:
        qstr="1:舰船量化";
        break;
    case 2:
        qstr="2:平方量化";
        break;
    case 3:
        qstr="3:不量化";
        break;
    default:
        qstr="";
        break;
    }
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D3-D0：保留

    //实时成像参数2
    //D7-D6：海陆分割模式
    tmp_uchar = (strYC.ss2&0xC0)>>6;
    switch (tmp_uchar) {
    case 0:
        qstr="0:不分割";
        break;
    case 1:
        qstr="1:分割";
        break;
    case 2:
        qstr="2:根据数据库选择";
        break;
    default:
        qstr="";
        break;
    }
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D5：舰船检测模式
    tmp_uchar = (strYC.ss2&0x20)>>5;
    if(tmp_uchar==0)qstr="0:不检测";
    else qstr="1:检测";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D4：舰船军民分类
    tmp_uchar = (strYC.ss2&0x10)>>4;
    if(tmp_uchar==0)qstr="0:不分类";
    else qstr="1:分类";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D3：舰船精聚焦
    tmp_uchar = (strYC.ss2&0x80)>>3;
    if(tmp_uchar==0)qstr="0:不精聚焦";
    else qstr="1:精聚焦";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D2：舰船目标定位
    tmp_uchar = (strYC.ss2&0x04)>>2;
    if(tmp_uchar==0)qstr="0:不定位";
    else qstr="1:定位";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D1：输出切片选择
    tmp_uchar = (strYC.ss2&0x02)>>1;
    if(tmp_uchar==0)qstr="0:不输出";
    else qstr="1:输出";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //D0：输出文本信息
    tmp_uchar = strYC.ss2&0x01;
    if(tmp_uchar==0)qstr="0:不输出";
    else qstr="1:输出";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));

    //EDAC错误计数
    qstr = QString::number(strYC.EDAC_cnt);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //CPU复位计数
    qstr = QString::number(strYC.CPU_cnt);
    model->setItem(colcnt++, 1, new QStandardItem(qstr));


    return ;
}


//清空遥测表格
void subyc_packspeed::on_pushButton_clearlist_clicked()
{
    int cnt=model->rowCount();
    for (int n=0;n<cnt;n++) {

        model->setItem(n, 1, new QStandardItem(""));
        model->setItem(n, 3, new QStandardItem(""));
        model->setItem(n, 5, new QStandardItem(""));
    }

}


