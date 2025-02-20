#include "subsrio_overnote.h"
#include "ui_subsrio_overnote.h"
#include <Globel_Define.h>
#include <QStandardPaths>
#include <QMessageBox>
#include <windows.h>

subsrio_overnote::subsrio_overnote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subsrio_overnote)
{
    ui->setupUi(this);
    ui->lineEdit_part_code->setText("41");
    ui->lineEdit_satellite_sign->setText("0101");
    ui->lineEdit_addr_type->setText("12");
    ui->lineEdit_ad_number->setText("12");
    ui->m_progress_jxjd->setAlignment(Qt::AlignVCenter);
    ui->m_progress_jxjd->setRange(0,10000);
    ui->m_progress_jxjd->setValue(0);
    Dirpath="";
    time1=new QTimer(this);
    connect(time1,SIGNAL(timeout()),this,SLOT(updata_Size()));
}

subsrio_overnote::~subsrio_overnote()
{
    if(time1->isActive())
    {
        time1->stop();
    }
    time1->deleteLater();
    delete ui;

}

void subsrio_overnote::Reverse_Data(Order_List_Object varData) {

    Q_UNUSED(varData);

}

//解析进度条
void subsrio_overnote::get_jxjd(double value)
{
    ui->m_progress_jxjd->setValue(value);
}

ushort subsrio_overnote::toHex_ushort(QString qstr)
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

//更新读取文件大小
void subsrio_overnote::updata_Size()
{
    QString str;
    if(ui->cB_channel0->isChecked())
            str+=QString("通道0已接收%L1字节\n").arg(Pfile0->size());//千分号分隔符，表达
    if(ui->cB_channel1->isChecked())
            str+=QString("通道1已接收%L1字节\n").arg(Pfile1->size());
    ui->lb_output->setText(str);
    //qDebug()<<Pfile0->size()<<"...";
    //qDebug()<<Pfile1->size()<<"...";
}


//选取bin文件
void subsrio_overnote::on_pB_ReadbinFile_clicked()
{
    //打开文件选择对话框
    //QString curPath=QCoreApplication::applicationDirPath();//引用程序路径
    QString file_path = QFileDialog::getOpenFileName(this,tr("选择bin文件"),ui->lineEdit_binPath->text(),"*.bin *.dat");
    if(file_path.isEmpty()) return;
    ui->lineEdit_binPath->setText(file_path);

}




//调用SRIO发送bin文件
void subsrio_overnote::on_pB_SRIOsend_clicked()
{
    DC_test dc_test;
    QString path;
    path=ui->lineEdit_binPath->text();
    bool AD0=ui->checkBox_sendad0->isChecked();
    bool AD1=ui->checkBox_sendad1->isChecked();

    dc_test.Raddrtyp = ui->lineEdit_addr_type->text().toUShort();
    dc_test.Rpartcode = ui->lineEdit_part_code->text().toUShort();
    dc_test.Rstartmark =qToBigEndian(toHex_ushort(ui->lineEdit_satellite_sign->text()));
    dc_test.channelnum = ui->lineEdit_ad_number->text().toUShort();
    emit send_riodata(path, AD0, AD1, dc_test);
}


//设置接收目录
void subsrio_overnote::on_pB_getFilepath_clicked()
{

    if(ui->textBrowser->toPlainText().count()==0)
    {
        QString desktop_path=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);//桌面路径
        Dirpath = QFileDialog::getExistingDirectory(this,tr("选择文件路径"),desktop_path);
    }
    else
    {
        Dirpath = QFileDialog::getExistingDirectory(this,tr("选择文件路径"),"");
    }

    if(Dirpath.isEmpty())//确保选择了文件路径
    {
        ui->pB_startOrstop->setEnabled(0);
        return;
    }
    ui->pB_startOrstop->setEnabled(1);
    ui->textBrowser->append("设置接收目录为:"+Dirpath);
}


//界面开启收数
void subsrio_overnote::on_pB_startOrstop_clicked()
{

    if(ui->pB_startOrstop->text()=="开启接收")
    {

        //通道选择不使能
        ui->cB_channel0->setDisabled(true);
        ui->cB_channel1->setDisabled(true);
        //
        ui->pB_startOrstop->setText("停止接收");
        ui->pB_startOrstop->setStyleSheet("background-color:rgb(255,100,100)");
        QDateTime current_date=QDateTime::currentDateTime();
        QString current_time=current_date.toString("yyyy-MM-dd hh-mm-ss");
        ui->textBrowser->append("----");
        ui->textBrowser->append("开始测试时间："+current_time);

        //通道0勾选,创建数据包
        Pfile0=new QFile(this);
        if(ui->cB_channel0->isChecked())
        {
            Filepath0=Dirpath+"/ad0_"+ui->filename_1->text()+"_"+ current_time+".dat";
            Pfile0->setFileName(Filepath0);

            bool ret=Pfile0->open(QIODevice::ReadWrite);
            ui->textBrowser->append("通道0接收文件:"+Filepath0);
            if(!ret)
            {
                QMessageBox::information(this, "提示", "ad0文件打开错误");
                return;
            }
        }
        //通道1勾选,创建数据包
        Pfile1=new QFile(this);
        if(ui->cB_channel1->isChecked())
        {
            Filepath1=Dirpath+"/ad1_"+ui->filename_1->text()+ "_"+current_time+".dat";
            Pfile1->setFileName(Filepath1);

            bool ret=Pfile1->open(QIODevice::ReadWrite);
            ui->textBrowser->append("通道1接收文件:"+Filepath1);
            if(!ret)
            {
                QMessageBox::information(this, "提示", "ad1文件打开错误");
                return;
            }

        }
        //文件打开成功开启线程
        emit rec_riodata(Pfile0,Pfile1);
        Sleep(10);
        //读取文件大小，并显示s
        updata_Size();
        time1->start(250);
    }
    else if(ui->pB_startOrstop->text()=="停止接收")
    {
        //通道选择使能
        ui->cB_channel0->setDisabled(false);
        ui->cB_channel1->setDisabled(false);
        //
        ui->pB_startOrstop->setText("开启接收");
        ui->pB_startOrstop->setStyleSheet("");
        //停止线程，循环收数 while (Rec_flag) 结束
        emit finshrec_riodata();
        Sleep(10);
        if(Pfile0->isOpen())Pfile0->close();
        if(Pfile1->isOpen())Pfile1->close();
        time1->stop();
    }
    else
    {
        return;
    }


}

//重新初始化rapdio板卡（通道未连接发送线程卡死）
void subsrio_overnote::on_pushButton_statusNew_clicked()
{
    emit reset_srio();
}
//.csv->.dat转换
void subsrio_overnote::on_pB_csv_dat_clicked()
{
    QString tmp_list = QFileDialog::getOpenFileName(this,tr("选择csv文件"),ui->lineEdit_binPath->text(),"*.csv *.dat");
    if(tmp_list.isEmpty()) return;
    QFileInfo filExtName;
    filExtName = tmp_list;
    if(filExtName.suffix()=="csv")
    {
        //打开CSV文件
        QFile csv_data(tmp_list);
        if (false == csv_data.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,"错误","csv打开失败");
            return ;
        }
        //创建dat文件
        QString dat_path=tmp_list;
        int a=dat_path.indexOf(".");
        QDateTime tm=QDateTime::currentDateTime();
        QString qtm=tm.toString("hh_mm_ss");
        dat_path=dat_path.left(a)+qtm+".dat";
        QFile dat_file(dat_path);
        if(!dat_file.open(QIODevice::ReadWrite))
        {
            QMessageBox::warning(this,"提示","创建失败");
        }

        //读取CSV文件
        QString tmp_cstr=csv_data.readLine();//跳过表头
        QString tmp;
        uint uint_pl=0;
        ushort ushort_fd=0;

        uint pack_len=4;//在开头添加文件长度
        dat_file.write((char*)&pack_len,4);
        while(csv_data.atEnd()==false)
        {
            tmp_cstr = csv_data.readLine();
            tmp_cstr.replace("\r\n","");
            //频率值
            tmp = tmp_cstr.left(tmp_cstr.indexOf(','));
            //qDebug()<<tmp;
            uint_pl=tmp.toUInt();
            dat_file.write((char*)&uint_pl,4);
            pack_len+=4;


            QStringList col=tmp_cstr.split(",");//列数
            for(int c=0;c<col.size()-1;c++)
            {
                //幅度值
                tmp_cstr = tmp_cstr.mid(tmp_cstr.indexOf(',') + 1,tmp_cstr.size() - tmp_cstr.indexOf(','));
                tmp = tmp_cstr.left(tmp_cstr.indexOf(','));
                //qDebug()<<tmp;
                ushort_fd=tmp.toUShort();
                dat_file.write((char*)&ushort_fd,2);
                pack_len+=2;
            }


        }
        dat_file.seek(0);
        dat_file.write((char*)&pack_len,4);
        dat_file.close();
        csv_data.close();
        QMessageBox::warning(this,"提示","转换完成");

    }
    else
    {
        QMessageBox::warning(this,"错误","选取正确的csv表");
    }
    return;
}
