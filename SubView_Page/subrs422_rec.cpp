#include "subrs422_rec.h"
#include "ui_subrs422_rec.h"

#include<QRandomGenerator>

extern int RS422_Device_num;//声明

subrs422_Rec::subrs422_Rec(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subrs422_Rec)
{
    ui->setupUi(this);

    Timer_Re = new QTimer();
    connect(Timer_Re,SIGNAL(timeout()),this,SLOT(time_Active()));
    //Timer_Re->start(500);


    //if(RS422_Device_num==-1)return;
    //PA_RS422_PULSE_IN_CH1;//实际读取0
    //PA_RS422_PULSE_IN_CH2;//实际读取0
    //PA_RS422_PULSE_IN_CH3;//实际读取1
    //PA_RS422_PULSE_IN_CH4;//实际读取1
    //PA_RS422_PULSE_IN_CH5;//实际读取0
    //PA_RS422_PULSE_IN_CH6;//实际读取0
    //PA_RS422_PULSE_IN_CH7;//实际读取1
    //PA_RS422_PULSE_IN_CH8;//实际读取1
    Arr_inch[0]=PA_RS422_PULSE_IN_CH1;
    Arr_inch[1]=PA_RS422_PULSE_IN_CH2;
    Arr_inch[2]=PA_RS422_PULSE_IN_CH3;
    Arr_inch[3]=PA_RS422_PULSE_IN_CH4;

    qc_Widget[0]=ui->widget;
    qc_Widget[1]=ui->widget_2;
    qc_Widget[2]=ui->widget_3;
    qc_Widget[3]=ui->widget_4;

    Init_Plot();
    //qDebug()<< RS422_Device_num;
}

subrs422_Rec::~subrs422_Rec()
{
    if(Timer_Re->isActive())
    {
        Timer_Re->stop();
    }
    Timer_Re->deleteLater();
    delete ui;
}

void subrs422_Rec::Init_Plot()
{

    QString st[4];
    st[0]="通道1";
    st[1]="通道2";
    st[2]="通道3";
    st[3]="通道4";

    //4个通道
    for (int n=0;n<4;n++) {

        //设置标题
        qc_Widget[n]->plotLayout()->insertRow(0);
        QCPTextElement *title = new QCPTextElement(qc_Widget[n],st[n]);
        //title->setFont(QFont("幼圆",13,QFont::Black));
        title->setTextColor(QColor(0,0,150));
        qc_Widget[n]->plotLayout()->addElement(0,0,title);
        //为坐标添加标签
        qc_Widget[n]->xAxis->setLabel("时间(10s)");
        qc_Widget[n]->yAxis->setLabel("电平");
        //    qc_Widget[n]->xAxis2->setVisible(true);//设置顶部轴线可见
        //    qc_Widget[n]->yAxis2->setVisible(true);//设置右部轴线可见
        //当修改左和底坐标轴时，使之右和上坐标轴也跟着变化
        //    connect(ui->widget->xAxis,SIGNAL(rangeChanged(QCPRnge)),ui->widget->xAxis2,SLOT(setRange(QCPRange)));
        //    connect(ui->widget->yAxis,SIGNAL(rangeChanged(QCPRnge)),ui->widget->yAxis2,SLOT(setRange(QCPRange)));
        //设置拖动，缩放，选择
        //qc_Widget[n]->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);



        qc_Widget[n]->yAxis->setRange(-1,2);//设置y轴范围
        qc_Widget[n]->xAxis->setRange(0,10);//设置x轴范围
        qc_Widget[n]->addGraph();//创建画布


        for(int i=0;i<11;i++)//x轴(10个点)秒级
        {
            Vplot_x[n].append(i);
            Vplot_y[n].append(0);
        }
        for(int i=0;i<1000;i++)// ---微妙秒级（5秒*1000毫秒）*每毫秒10个满足条件点==50000
        {
            Vplot_x_MS[n].append(i);
            Vplot_y_MS[n].append(0);
        }
    }

}

//定时器读取电平值
void subrs422_Rec::time_Active()
{

    if(ui->checkBox_read422Pluse->isChecked())//秒级别读取
    {
        int status=0;
        for(int i=0;i<4;i++)
        {
            uchar level=0;
            status+=PA_PCIe_4202_RS422_ReadLevel(RS422_Device_num,Arr_inch[i],&level);
            //double rand=QRandomGenerator::global()->generateDouble();//生成0.0-1.0之间的浮点数
            //int randi=QRandomGenerator::global()->bounded(100);//生成0-100随机数
            Vplot_y[i].push_back(level);
            Vplot_y[i].erase(Vplot_y[i].begin());

            qc_Widget[i]->graph(0)->setData(Vplot_x[i],Vplot_y[i]);
            qc_Widget[i]->replot();//进行重绘

        }
    }
    if(ui->checkBox_read422Pluse_US->isChecked())//毫秒级别读取
    {
        int status=0;
        for(int i=0;i<4;i++)
        {
            uchar level=0;
            status+=PA_PCIe_4202_RS422_ReadLevel(RS422_Device_num,Arr_inch[i],&level);
            //double rand=QRandomGenerator::global()->generateDouble();//生成0.0-1.0之间的浮点数
            Vplot_y_MS[i].push_back(level);
            Vplot_y_MS[i].erase(Vplot_y_MS[i].begin());

            qc_Widget[i]->graph(0)->setData(Vplot_x_MS[i],Vplot_y_MS[i]);
            qc_Widget[i]->replot();//进行重绘

        }
    }

}



//开启，关闭，读取脉冲  S
void subrs422_Rec::on_checkBox_read422Pluse_clicked(bool checked)
{

    if(checked)
    {
        ui->checkBox_read422Pluse_US->setChecked(0);
        for (int n=0;n<4;n++) {
            qc_Widget[n]->xAxis->setRange(0,10);//设置x轴范围
            qc_Widget[n]->xAxis->setLabel("时间(10s)");
        }
        if(Timer_Re->isActive())
        {
            Timer_Re->stop();
        }
        Timer_Re->start(1000);
    }
    else
    {
        if(Timer_Re->isActive())
        {
            Timer_Re->stop();

            for (int i=0;i<4;i++) {
                qc_Widget[i]->graph(0)->data().data()->clear();//清除一条曲线上的数据
                qc_Widget[i]->replot();//进行重绘
            }

        }
    }
}
//开启，关闭，读取脉冲US
void subrs422_Rec::on_checkBox_read422Pluse_US_clicked(bool checked)
{
    if(checked)
    {
        for (int n=0;n<4;n++) {
            qc_Widget[n]->xAxis->setRange(0,1000);//设置x轴范围
            qc_Widget[n]->xAxis->setLabel("时间(1s)");
        }
        ui->checkBox_read422Pluse->setChecked(0);
        if(Timer_Re->isActive())
        {
            Timer_Re->stop();
        }
        Timer_Re->start(1);//最低1MS
    }
    else
    {
        if(Timer_Re->isActive())
        {
            Timer_Re->stop();

            for (int i=0;i<4;i++) {
                qc_Widget[i]->graph(0)->data().data()->clear();//清除一条曲线上的数据
                qc_Widget[i]->replot();//进行重绘
            }

        }
    }
}
