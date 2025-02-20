#include "DatabaseView.h"
#include "ui_DatabaseView.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>


DatabaseView::DatabaseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseView)
{
    ui->setupUi(this);
    //qDebug()<<QSqlDatabase::drivers();//显示可用数据库驱动
    connectDB();//连接数据库
    queryDB();//访问数据库
    connectView();//绑定控件

    ui->checkBox_TimeSelect->setChecked(1);
    //控件日期开始，结束时间
    ui->dateTimeEdit_startTime->setDate(QDate::currentDate());//设置时间会进入函数
    ui->dateTimeEdit_endTime->setDate(QDate::currentDate().addDays(1));//设置时间会进入函数,设置为明天

    //添加按钮隐藏
    ui->pB_addData->setVisible(0);

}

DatabaseView::~DatabaseView()
{
    mydb.close();
    delete ui;
}

//连接数据库
void DatabaseView::connectDB()
{
    //创建数据库存储路径
    QString path = QCoreApplication::applicationDirPath();
    QDir dir1(path);
    dir1.cdUp();//返回上一级目录
    path=dir1.absolutePath()+"/myDB";
    QDir dir(path);
    if (!dir.exists()) {
        if (!dir.mkdir(path)) {
            QMessageBox::warning(this, "提示", "DB文件夹不存在且创建失败");
            return;
        }
    }


    //数据库命名--每天新建
    //QString dbName=path+"/"+QDate::currentDate().toString("yyyyMMdd_")+"DATA.db";

    //数据库命名--每2天新建
    //获取日期1-31天
    QString tmdd=QDate::currentDate().toString("dd");
    int dd=tmdd.toUInt();
    //qDebug()<<dd;
    QString names;
    if(dd%2==0)
    {
        names=QDate::currentDate().toString("yyyyMMdd_");
    }
    else
    {
        names=QDate::currentDate().toString("yyyyMM")+QString::number(dd-1)+"_";
    }
    QString dbName=path+"/"+names+"DATA.db";

    //连接数据库
    mydb=QSqlDatabase::addDatabase("QSQLITE");//连接sqlite3类型数据库
    mydb.setDatabaseName(dbName);//库文件后缀db

    //打开数据库，不存在就创建
    if(!mydb.open())
    {
        qDebug()<<"sql OPen UnSucess!"<<mydb.lastError();
    }


}
//访问数据库
void DatabaseView::queryDB()
{
    //访问数据库的操作包括：创建表，添加数据，删除数据，更新数据，查询数据
    QSqlQuery qureydb;//创建对象时，系统会自动完成与数据库的关联
    QString str=QString("CREATE TABLE IF NOT EXISTS COMPANY("
                        "ID INTEGER PRIMARY KEY     NOT NULL,"
                        "NAME           TEXT    NOT NULL,"
                        "AGE            INT     NOT NULL,"
                        "ADDRESS        CHAR(50),"
                        "SALARY         REAL)");
    qureydb.exec(str);


}

void DatabaseView::connectView()
{
    viewMode=new QSqlQueryModel();
    viewMode->setQuery("select * from ORDER_LIST;",mydb);
    while (viewMode->canFetchMore()) {
        viewMode->fetchMore();//为了显示全部数据，不然会出现只显示在256条数据问题
    }
    //设置表格
    ui->tableView_DB->setModel(viewMode);
    ui->tableView_DB->horizontalHeader()->setStyleSheet("QHeaderView::section{background:white;color:black;}"); //区分列表头
    //ui->tableView_DB->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中
    //ui->tableView_DB->setSelectionMode(QAbstractItemView::SingleSelection); //单行选中
    //ui->tableView_DB->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置只读
    //ui->tableView_DB->verticalHeader()->hide(); //隐藏行头
    //ui->tableView_DB->verticalHeader()->setDefaultSectionSize(33); //设置行宽
    //ui->tableView_DB->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行宽
    //ui->tableView_DB->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列度
//    ui->tableView_DB->setShowGrid(true); //表格网格线显示
//    ui->tableView_DB->setGridStyle(Qt::SolidLine); //网格线画笔
//    ui->tableView_DB->setFocusPolicy(Qt::NoFocus); //去除选中时虚线框
//    ui->tableView_DB->scrollToBottom(); //保持滚动条在底部

    ui->tableView_DB->resizeColumnsToContents();//设置所有列宽度自适应
    ui->tableView_DB->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_DB->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView_DB->horizontalHeader()->setMinimumSectionSize(100);
}



void DatabaseView::on_pB_addData_clicked()
{
    QSqlQuery qureydb;
    QString str=QString("insert into COMPANY ('NAME','AGE','ADDRESS','SALARY')"
                        "values('yyh',27,'上海',6666)");
    qureydb.exec(str);
    viewMode->setQuery("select * from COMPANY;",mydb);
}


//查询数据库
void DatabaseView::check_DB(int n,QString stro)
{
    QString str_oder;

    switch (n) {
    case 0://指令发送记录
        str_oder="select * from ORDER_LIST;";//默认查询全部
        if(!stro.isEmpty())str_oder="select * from ORDER_LIST"+stro;//拼接查询语句
        break;
    case 1://1553B慢速遥测记录组1
        str_oder="select * from YC1553_slowP1;";
        if(!stro.isEmpty())str_oder="select * from YC1553_slowP1"+stro;
        break;
    case 2://1553B慢速遥测记录组2
        str_oder="select * from YC1553_slowP2;";
        if(!stro.isEmpty())str_oder="select * from YC1553_slowP2"+stro;
        break;
    case 3://1553B慢速遥测记录组3
        str_oder="select * from YC1553_slowP3;";
        if(!stro.isEmpty())str_oder="select * from YC1553_slowP3"+stro;
        break;
    case 4://CAN遥测记录
        str_oder="select * from COMPANY;";
        break;
    default:
        return;
        break;
    }
    viewMode->setQuery(str_oder,mydb);
    while (viewMode->canFetchMore()) {
        viewMode->fetchMore();//为了显示全部数据，不然会出现只显示在256条数据问题
    }
    ui->tableView_DB->setModel(viewMode);
}
//查询附加数据库
void DatabaseView::check_DB_add(int n, QString stro)
{
    QString str_oder;

    switch (n) {
    case 0://指令发送记录
        str_oder="select * from tmp1.ORDER_LIST;";//默认查询全部
        if(!stro.isEmpty())str_oder="select * from tmp1.ORDER_LIST"+stro;//拼接查询语句
        break;
    case 1://1553B慢速遥测记录组1
        str_oder="select * from tmp1.YC1553_slowP1;";
        if(!stro.isEmpty())str_oder="select * from tmp1.YC1553_slowP1"+stro;
        break;
    case 2://1553B慢速遥测记录组2
        str_oder="select * from tmp1.YC1553_slowP2;";
        if(!stro.isEmpty())str_oder="select * from tmp1.YC1553_slowP2"+stro;
        break;
    case 3://1553B慢速遥测记录组3
        str_oder="select * from tmp1.YC1553_slowP3;";
        if(!stro.isEmpty())str_oder="select * from tmp1.YC1553_slowP3"+stro;
        break;
    case 4://CAN遥测记录
        str_oder="select * from tmp1.COMPANY;";
        break;
    default:
        return;
        break;
    }
    viewMode->setQuery(str_oder,mydb);
    while (viewMode->canFetchMore()) {
        viewMode->fetchMore();//为了显示全部数据，不然会出现只显示在256条数据问题
    }
    ui->tableView_DB->setModel(viewMode);
}



//表格进行时间筛选
QString DatabaseView::selcet_Time(QString tmS, QString tmE)
{
    QString tm1 = tmS;
    QString tm2 = tmE;

    QString str=QString(" WHERE 时间 > '%1' AND 时间 < '%2';").arg(tm1).arg(tm2);

    return  str;

}


//切换表格
void DatabaseView::on_cB_tableKind_activated(int index)
{
    Q_UNUSED(index);
    STRcontrol_DB();
}

//刷新数据库
void DatabaseView::on_pB_freshenDB_clicked()
{
    STRcontrol_DB();
}


//开始时间
void DatabaseView::on_dateTimeEdit_startTime_dateTimeChanged(const QDateTime &dateTime)
{
//    QString tms = dateTime.toString("MM-dd hh:mm:ss");
//    QString strselect=QString(" WHERE 时间 > '%1';").arg(tms);

//    int index=ui->cB_tableKind->currentIndex();//表类型
//    check_DB(index,strselect);
    QString t1=dateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString t2=ui->dateTimeEdit_endTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    if(t1>t2)
    {
        //QMessageBox::warning(this, "提示", "起始时间应小于结束时间");
        return;
    }
    STRcontrol_DB();

}

//结束时间（界面初始化，界面会自动读取当日的数据记录）
void DatabaseView::on_dateTimeEdit_endTime_dateTimeChanged(const QDateTime &dateTime)
{
//    QString tme = dateTime.toString("MM-dd hh:mm:ss");
//    QString strselect=QString(" WHERE 时间 < '%1';").arg(tme);

//    int index=ui->cB_tableKind->currentIndex();//表类型
//    check_DB(index,strselect);

    QString t1=ui->dateTimeEdit_startTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString t2=dateTime.toString("yyyy-MM-dd hh:mm:ss");
    if(t1>t2)
    {
        QMessageBox::warning(this, "提示", "结束时间 应大于 起始时间");
        return;
    }

    STRcontrol_DB();
}
 //控制数据库查询操作
void DatabaseView::STRcontrol_DB()
{
    QString str;
    if(ui->checkBox_TimeSelect->isChecked())
    {
        //数据库查询不需要年份内容
        str=selcet_Time(ui->dateTimeEdit_startTime->dateTime().toString("MM-dd hh:mm:ss"),
                        ui->dateTimeEdit_endTime->dateTime().toString("MM-dd hh:mm:ss"));
    }


    int kind=ui->cB_tableKind->currentIndex();//类型
    if(ui->checkBox_addDB->isChecked())//附加库
    {
        check_DB_add(kind,str);
    }
    else
    {
        check_DB(kind,str);
    }
}

//打开附加数据库
void DatabaseView::on_pushButton_OpenNewDB_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,tr("选择数据库文件"),"","*.db ");
    if(file_path.isEmpty()) return;

    QSqlQuery qureydb;
    if(ui->checkBox_addDB->isChecked()==1)
    {
        QString str1=QString("DETACH DATABASE 'tmp1'");// 分离附加数据库（因为附加库名字固定tmp1）
        qureydb.exec(str1);
    }
    QString str2=QString("ATTACH DATABASE '%1' AS 'tmp1'").arg(file_path);//添加附加数据库
    ui->checkBox_addDB->setChecked(1);//附加库标志
    qureydb.exec(str2);
    //viewMode->setQuery("select * from tmp1.ORDER_LIST;",mydb);//查询附加数据库

    //访问数据库
    STRcontrol_DB();

}

void DatabaseView::on_checkBox_addDB_clicked(bool checked)
{

    if(checked==false)//勾选取消后操作
    {
        ui->checkBox_addDB->setChecked(0);
        QSqlQuery qureydb;
        QString str=QString("DETACH DATABASE 'tmp1'");// 分离附加数据库（因为附加库名字固定tmp1）
        qureydb.exec(str);

        //访问数据库
        STRcontrol_DB();
    }
    else//没勾选，勾选不上
    {
        ui->checkBox_addDB->setChecked(0);
    }

}



//界面导出表格
void DatabaseView::on_pushButton_outExcel_clicked()
{
    QString filePath =QFileDialog::getSaveFileName(this, "选择保存路径", "", "*.xlsx");
    QXlsx::Document xlsx;
    int row=ui->tableView_DB->model()->rowCount();
    int col=ui->tableView_DB->model()->columnCount();

    //设置列宽
    xlsx.setColumnWidth(2,15);
    xlsx.setColumnWidth(7,8,20);//开始列，结束列，列宽
    xlsx.setColumnWidth(10,100);

    //获取列表头
    for (int n=0;n<col;n++) {
        QString strhead=ui->tableView_DB->model()->headerData(n,Qt::Horizontal).toString();
        xlsx.write(1, n+1,strhead);
    }
    //获取内容
    for (int i=0;i<row;i++) {
        for (int j=0;j<col;j++) {
            QString tmp_str;
            int tmp_int=0;

            QModelIndex index=ui->tableView_DB->model()->index(i,j);
            if(ui->cB_tableKind->currentIndex()==0)//发送指令格式的导出
            {
                if((j==0)||(j==4)||(j==5)||(j==8))
                {
                    tmp_int=index.data().toInt();//整型
                    xlsx.write(i+2, j+1,tmp_int);
                }
                else
                {
                    tmp_str=index.data().toString();
                    xlsx.write(i+2, j+1,tmp_str);
                }
            }
            else//其他表格格式
            {
                tmp_str=index.data().toString();
                xlsx.write(i+2, j+1,tmp_str);
            }
        }
    }
    if (!xlsx.saveAs(filePath)) {
        //QMessageBox::warning(this, "提示", "文件保存失败");
        return;
    }
    xlsx.deleteLater();

    QMessageBox::warning(this, "提示", "导出成功");
}

//附加库标志，没有不能勾选，有可取消勾选
