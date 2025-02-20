#include "signal_1466.h"
#include "ui_signal_1466.h"
#include <QValidator>
#include <QFileDialog>


signal_1466::signal_1466(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signal_1466)
{
    ui->setupUi(this);

    // 正则表达式设置IP和MAC输入
    QRegExp ipRegExp = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip = new QRegExpValidator(ipRegExp,this);
    ui->lineEdit_inputIP->setValidator(m_ip);

    //tcp
    //signalConrtl=new CN_SignalContrl();

    //connect(signalConrtl,&CN_SignalContrl::GetMess,this,&signal_1466::Get_TcpMess);
}

signal_1466::~signal_1466()
{
    delete ui;
}

void signal_1466::Get_TcpMess(QString str)
{
    ui->textBrowser__massages->append(str);
}

//创建连接ip
void signal_1466::on_pB_IPConnet_clicked()
{
    //连接服务端
    bool ret=signalConrtl->Tcp_Connet(ui->lineEdit_inputIP->text(),ui->lineEdit_inputport->text().toUInt());
    if(ret)
    {
        ui->textBrowser__massages->append("连接成功");
    }
    else
    {
        ui->textBrowser__massages->append("连接失败");
    }


}

//断开连接
void signal_1466::on_pB_disconnect_clicked()
{
    signalConrtl->Tcp_DisConnet();

    ui->textBrowser__massages->append("断开连接");

}
//客户端发送数据
void signal_1466::on_pB_send_clicked()
{
    int isize=signalConrtl->Tcp_SendData(0,0);
    if(isize==-1)
    {
        ui->textBrowser__massages->append("发送失败");
    }
     //tcpsocket->write(ui->sendwd->text().toLocal8Bit().data());//网上
     //tcpsocket->write(ui->sendwd->toPlainText().toLatin1());//xie宏伟

         /*
         QString str;
         int iSize = tcpsocket->write(str.toUtf8().data());//返回字节的大小
         //等待write写完再写下一次的write
         if(!tcpsocket->waitForBytesWritten(50000))
         {
             return;
         }
         if(iSize ==-1) //判断发送是否成功
         {
             qDebug() << "write error";
             return;
         }
         若要多次向服务端发消息,可以while循环或者是其他.在这里要注意如果要多次发消息的
         话,waitForBytesWritten()这个函数是必不可少的,不然多次的话可能通信会失败.
         注:write()函数和被触发的读的readyRead()信号并不是一一对应的,比如可能你客户端
         write了三次,服务端那边的readyRead可能才被触发一次.
         */
}

//读取xlsx
void signal_1466::on_pB_readXlsx_clicked()
{
    //打开文件选择对话框
    QString file_path = QFileDialog::getOpenFileName(NULL,"信号源表格","",tr("Excel file(*.xls *.xlsx)"));
    if(file_path.isEmpty()) return;

    Document xlsxR(file_path);//软件关闭会显示异常关闭

    if(!xlsxR.selectSheet("Sheet1"))
    {
        qDebug()<<"为找到页“Sheet1”";
        return;
    }
    for(int i=0;i<xlsxR.dimension().rowCount();i++)
    {
        Cell* cell = xlsxR.cellAt(i, 1);
        if ( cell != NULL )
        {
            QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
            QString tmp=var.toString();
            qDebug()<<tmp;

        }
    }
}
