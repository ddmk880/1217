#include "subyc_ad.h"
#include "ui_subyc_ad.h"
#include <QDebug>

subyc_AD::subyc_AD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subyc_AD)
{
    ui->setupUi(this);
    // 修改界面表格
    model = new QStandardItemModel(ui->tableView_ADlist);
    QStringList m_name_list;
    m_name_list.append("遥测名称");
    m_name_list.append("计算值");
    m_name_list.append("实际值");
    int num = m_name_list.size();
    model->setColumnCount(num);
    model->setRowCount(0);
    for (int i = 0; i < num; i++) {
        model->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
    }

    QStringList msyc_strName_1;
    msyc_strName_1.append("DC5V主模拟量遥测");
    msyc_strName_1.append("DC5V备模拟量遥测");
    msyc_strName_1.append("DC12V主模拟量遥测");
    msyc_strName_1.append("DC12V备模拟量遥测");

//    for (int i = 0; i < msyc_strName_1.size(); i++) {
//        model->setItem(i, 0, new QStandardItem(msyc_strName_1.at(i)));
//    }
    for (int i = 0; i < msyc_strName_1.size(); i++) {
        QStandardItem* table_item;
        table_item=new QStandardItem(msyc_strName_1.at(i));
        table_item->setBackground(QBrush(QColor(223,236,213)));
        model->setItem(i, 0, table_item);
    }

    ui->tableView_ADlist->setModel(model);  //(设置宽度要在后面)
    ui->tableView_ADlist->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 是否可编辑
    //  ui->tableView_ADlist->setColumnWidth(1,00);//设置第0列宽100
    ui->tableView_ADlist->resizeColumnToContents(0);  // 设置第0列宽度自适应内容
    ui->tableView_ADlist->resizeColumnToContents(2);  // 设置第2列宽度自适应内容
    ui->tableView_ADlist->resizeColumnToContents(4);  // 设置第4列宽度自适应内容
    ui->tableView_ADlist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_ADlist->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView_ADlist->horizontalHeader()->setMinimumSectionSize(100);
    //  ui->tableView_ADlist->resizeColumnsToContents();//设置所有列宽度自适应
    //   ui->tableView_ADlist->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);//设置第1列(表头)自动
    //   ui->tableView_ADlist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置所有列自动

    Outpack_dj=0;
    //ret_fun124(0.0196,0,4.8,0,2.2);
}

subyc_AD::~subyc_AD()
{
    delete ui;
}

double subyc_AD::ret_fun124(double a, double b, double k, double c, double N)
{
    double V = 0;
    if(N==0) return 0;
    V = k * (a * N + b) + c;
    return V;
}

void subyc_AD::Get_ADdata(double *Rxbuff, int Rxlen)
{
//    //打印显示（16路）
//    qDebug()<<"AD_yc:";
//    for(int i=0;i<Rxlen;i++)
//    {
//        printf("%f ",Rxbuff[i]);

//    }
//    printf("\n");

    // 开辟缓存存储4帧*32字 数据
    double *Tran_Buff = new double[Rxlen];
    memset(Tran_Buff, 0, Rxlen *8);
    memcpy(Tran_Buff, Rxbuff, Rxlen*8);


    int colcnt = 0;
    QString qstr;
    double tmp_d=0;
    int djNum=Outpack_dj*4;//第几台单机
    //DC5V主模拟量遥测
    tmp_d=Tran_Buff[0+djNum];
    model->setItem(colcnt, 2, new QStandardItem(QString::number(tmp_d,'f',3)));//实际值

    tmp_d=ret_fun124(1, 0, 2.5, 0,tmp_d);
    //tmp_d=ret_fun124(0.0196, 0, 2, 0,tmp_d);
    qstr = QString::number(tmp_d,'f',3)+" (V)";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //DC5V备模拟量遥测
    tmp_d=Tran_Buff[1+djNum];
    model->setItem(colcnt, 2, new QStandardItem(QString::number(tmp_d,'f',3)));//实际值

    tmp_d=ret_fun124(1, 0, 2.5, 0,tmp_d);
    //tmp_d=ret_fun124(0.0196, 0, 2, 0,tmp_d);
    qstr = QString::number(tmp_d,'f',3)+" (V)";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //DC12V主模拟量遥测
    tmp_d=Tran_Buff[2+djNum];
    model->setItem(colcnt, 2, new QStandardItem(QString::number(tmp_d,'f',3)));//实际值

    tmp_d=ret_fun124(1, 0, 6, 0,tmp_d);
    //tmp_d=ret_fun124(0.0196, 0, 4.8, 0,tmp_d);
    qstr = QString::number(tmp_d,'f',3)+" (V)";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));
    //DC12V备模拟量遥测
    tmp_d=Tran_Buff[3+djNum];
    model->setItem(colcnt, 2, new QStandardItem(QString::number(tmp_d,'f',3)));//实际值

    tmp_d=ret_fun124(1, 0, 6, 0,tmp_d);
    //tmp_d=ret_fun124(0.0196, 0, 4.8, 0,tmp_d);
    qstr = QString::number(tmp_d,'f',3)+" (V)";
    model->setItem(colcnt++, 1, new QStandardItem(qstr));


    delete [] Tran_Buff;
    return;
}

void subyc_AD::on_pushButton_ADclear_clicked()
{
    int cnt=model->rowCount();
    for (int n=0;n<cnt;n++) {

        model->setItem(n, 1, new QStandardItem(""));
    }
}
