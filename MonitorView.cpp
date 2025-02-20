#include "MonitorView.h"
#include "ui_MonitorView.h"

MonitorView::MonitorView(QWidget *parent,QSqlDatabase *db) :
    QWidget(parent),
    ui(new Ui::MonitorView)
{
    ui->setupUi(this);
    myDB = db;
    initDatabase();
    //设置内容不可编辑
    ui->m_monistor_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选择模式
    //ui->m_monistor_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //Selecting single items.
    //ui->m_monistor_view->setSelectionBehavior(QAbstractItemView::SelectItems);
    //自动调整该部分的大小以填充可用空间。
    //ui->m_monistor_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //在具有交替行颜色的视图中用作备用背景颜色
    //ui->m_monistor_view->setAlternatingRowColors( true );
    ui->comboBox_choose->setCurrentIndex(0);
}

MonitorView::~MonitorView()
{
    delete ui;
    //timer->stop();
}

void MonitorView::initDatabase()
{

    //连接打开的数据库
//    mDB = QSqlDatabase::addDatabase("QSQLITE");
//    QString path=QApplication::applicationDirPath();
//    path=path.left(path.lastIndexOf("/"))+"/DB/"+"myDataBase.db";
//    mDB.setDatabaseName(path);
//    if(!mDB.open())qDebug()<<"数据库打开失败";
    pModel = new MySqlTableModel(this, myDB);
//    timer=new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    //timer->start(1000);

}

void MonitorView::timerUpdate()
{

    pModel->setTable("总线数据监视记录表");
    // 三种提交方式，改动即提交，选择其他行时提交，手动提交；经实际测试，其中只有手动提交在显示效果上是最好的
    pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    QString id="6";
//    int time=5;
//    if(!id.isEmpty())
//        pModel->setFilter(QObject::tr("ID='%1'").arg(id));//过滤
//    if(time!=0)
//        pModel->setFilter(QObject::tr("时间='%1'").arg(time));//过滤
    switch (ui->comboBox_choose->currentIndex()) {
    case 1:
        pModel->setFilter(QObject::tr("总线类型='%1'").arg("CAN"));
        break;
    case 2:
        pModel->setFilter(QObject::tr("总线类型='%1'").arg("1553can"));
        break;
    default:
        break;
    }
    pModel->setLimit(500);
    pModel->select();//开始查询整个表格，在筛选和排序的条件下，将数据库中符合要求的在mode表格中显示出来
    pModel->textMap.clear();
    pModel->textMap2.clear();
    for (int i = 0; i < pModel->rowCount(); ++i)
    {
        QSqlRecord record = pModel->record(i);
        QString tmp = record.value("总线类型").toString();//访问数据库
        //QString tmp=pModel->data(pModel->index(i,3)).toString();
        //qDebug()<<tmp;
        // ... 在此处理每一条的记录
        if(tmp == "1553can")
        {
            for(int n=0;n<pModel->columnCount();n++)
            {
                pModel->MapData(pModel->index(i,n),pModel->data(pModel->index(i,n)).toString(),1);
            }

        }
        else if(tmp == "CAN")
        {
            for(int n=0;n<pModel->columnCount();n++)
            {

                pModel->MapData(pModel->index(i,n),pModel->data(pModel->index(i,n)).toString(),2);
            }
        }
        else
        {}
    }
    // pModel->removeColumn(1); //不显示第二列,如果这时添加记录，则该属性的值添加不上
    m_name_list.clear();
    m_name_list.append("ID");
    m_name_list.append("时间");  // page_id 指令生成页下标
    m_name_list.append("总线类型");
    m_name_list.append("数据方向");
    m_name_list.append("数据名称");
    m_name_list.append("数据长度");
    m_name_list.append("数据内容");
    m_name_list.append("备注");
    for (int i = 0; i < m_name_list.size(); i++) {
      pModel->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
    }
    pModel->sort(0, Qt::AscendingOrder); // id属性第0列升序排序
    //pModel->sort(0, Qt::DescendingOrder); // id属性第0列降序排序


    ui->m_monistor_view->setModel(pModel);
    //ui->m_monistor_view->hideColumn(0); // don't show the ID
    //if(timer->isActive()){timer->stop();}//只执行一次
}


void MonitorView::on_pushButto_on_clicked()
{

    pModel->setTable("总线数据监视记录表");
    // 三种提交方式，改动即提交，选择其他行时提交，手动提交；经实际测试，其中只有手动提交在显示效果上是最好的
    pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    QString id="6";
//    int time=5;
//    if(!id.isEmpty())
//        pModel->setFilter(QObject::tr("ID='%1'").arg(id));//过滤
//    if(time!=0)
//        pModel->setFilter(QObject::tr("时间='%1'").arg(time));//过滤
    pModel->setLimit(500);
    pModel->select();//开始查询整个表格，在筛选和排序的条件下，将数据库中符合要求的在mode表格中显示出来
    pModel->textMap.clear();
    pModel->textMap2.clear();
    for (int i = 0; i < pModel->rowCount(); ++i)
    {
        QSqlRecord record = pModel->record(i);
        QString tmp = record.value("总线类型").toString();//访问数据库
        //QString tmp=pModel->data(pModel->index(i,3)).toString();
        //qDebug()<<tmp;
        // ... 在此处理每一条的记录
        if(tmp=="1553can")
        {
            for(int n=0;n<pModel->columnCount();n++)
            {
                //第二个参数可改为bool类型，只做一个有无数据标志
                pModel->MapData(pModel->index(i,n),pModel->data(pModel->index(i,n)).toString(),1);
            }

        }
        else if(tmp=="CAN")
        {
            for(int n=0;n<pModel->columnCount();n++)
            {

                pModel->MapData(pModel->index(i,n),pModel->data(pModel->index(i,n)).toString(),2);
            }
        }
        else
        {}
    }
    // pModel->removeColumn(1); //不显示第二列,如果这时添加记录，则该属性的值添加不上
    m_name_list.clear();
    m_name_list.append("ID");
    m_name_list.append("时间");  // page_id 指令生成页下标
    m_name_list.append("总线类型");
    m_name_list.append("数据方向");
    m_name_list.append("数据名称");
    m_name_list.append("数据长度");
    m_name_list.append("数据内容");
    m_name_list.append("备注");
    for (int i = 0; i < m_name_list.size(); i++) {
      pModel->setHeaderData(i, Qt::Horizontal, m_name_list.at(i));
    }
    pModel->sort(0, Qt::AscendingOrder); // id属性第0列升序排序
    //pModel->sort(0, Qt::DescendingOrder); // id属性第0列降序排序


    ui->m_monistor_view->setModel(pModel);
    //ui->m_monistor_view->hideColumn(0); // don't show the ID



}


void MonitorView::on_checkBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    bool status=ui->checkBox->isChecked();
    if(status)
    {
        timer->start(1000);
    }
    else
    {
        timer->stop();
    }
}

MySqlTableModel::MySqlTableModel(QObject *parent, QSqlDatabase* db) :
    QSqlTableModel(parent, *db)
{
    mLimit=0;
}

QString MySqlTableModel::selectStatement() const
{

    QString strSql = QSqlTableModel::selectStatement();
    if(mLimit>0)
    strSql += QString(" LIMIT %1").arg(mLimit);  // 注意字符串的第一个字符需要有空格
    return strSql;

}

//表格内容是动态刷新,重写函数
QVariant MySqlTableModel::data(const QModelIndex &idx, int role) const
{
    QVariant value  = QSqlTableModel::data(idx,role);
    //qDebug()<<idx.row()<<idx<<role;
    if(Qt::TextAlignmentRole == role)//控制对齐方式
    {
        value   = int(Qt::AlignCenter | Qt::AlignHCenter);
        return value;
    }
    if(Qt::ForegroundRole == role )//控制前景色
    {
//        if(idx.column()==2)//类型列
//        {
//            QString text=idx.model()->data(idx,Qt::DisplayRole).toString();
//            if(text=="CAN")
//            {
//                //qDebug()<<idx.row();
//                //return QVariant(QColor(255,144,144));
//            }
//        }
//        return value;

        QString tmp=textMap.value(idx).toString();
        if(!textMap.value(idx).isNull())
            return QVariant(QColor(255,144,144));
        QString tmp2=textMap2.value(idx).toString();
        if(!textMap2.value(idx).isNull())
            return QVariant(QColor(100,200,50));
    }
    if(Qt::FontRole == role)//控制字体
    {
        if(0)//加粗
        {
            QFont font;
            font.setBold(true);
            return QVariant(font);
        }
    }
    return value;
}


void MySqlTableModel::MapData(const QModelIndex &index, const QVariant &value,int type)
{
    switch (type) {
    case 1:
            textMap.insert(index,value);//数据库坐标对应是否有值需要填充颜色
        break;
    case 2:
            textMap2.insert(index,value);
        break;
    default:
        break;
    }

}
