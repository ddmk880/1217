#include "sub1553_modecontrl.h"
#include "ui_sub1553_modecontrl.h"
#include <QFileDialog>
#include <QMessageBox>

sub1553_modecontrl::sub1553_modecontrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sub1553_modecontrl)
{
    ui->setupUi(this);
    for (int i=0;i<4;i++) {
        ncRe_Pfile[i]=new QFile(this);
    }
}

sub1553_modecontrl::~sub1553_modecontrl()
{
    for (int i=0;i<4;i++) {
        delete  ncRe_Pfile[i];
    }
    delete ui;
}



//内存下卸指令
void sub1553_modecontrl::on_pB_MemoryDown_clicked()
{
    Memory_down memory_str;
    memset(&memory_str,0,sizeof(memory_str));

    //包标志0x0731
    memory_str.pack_mark=qToBigEndian((ushort)0x1731);
    //包顺序0xc000
    memory_str.pack_number=qToBigEndian((ushort)0xc000);
    //包长0x000d
    memory_str.pack_Len=qToBigEndian((ushort)0x000d);
    //功能识别码0x000
    memory_str.fun_code=qToBigEndian((ushort)0x0003);
    //数据字1，0xd01
    memory_str.data_1=qToBigEndian((ushort)0xd01d);
    //数据字2，
    //0x0101:智能管控单元无权机
    //0x0202:网络交互机
    //0x0303:扩展单元
    //0x0505:姿轨控综合接口单元
    //0x0707:GNSS接收机
    //0x0808:S扩频应答机
    //0x0A0A:Ka/S多模扩频应答机
    //0x0B0B:数传调制器
    //0x1313:综合管控单元
    //0x1414:光通信处理机
    //0x1515:电源控制器
    //0x1717:高性能综合处理机
    //0xAAAA:智能管理单元有权机
    //0xEEEE:停止内存下卸
    ushort tmp=0;
    switch (ui->cB_data_word2->currentIndex()) {
    case 0:
        tmp=0x1313;
        break;
    case 1:
        tmp=0xEEEE;
        break;
    default:
        break;
    }

    memory_str.data_2=qToBigEndian((ushort)tmp);
    //起始地址高端
    memory_str.addr_high=qToBigEndian(ui->lineEdit_haddr->text().toUShort());
    //起始地址低端
    memory_str.addr_low=qToBigEndian(ui->lineEdit_laddr->text().toUShort());
    //长度
    memory_str.leng=qToBigEndian(ui->lineEdit_Long->text().toUShort());

    //按字异或和校验
     ushort* checkbuff=new ushort[sizeof (memory_str)/2-3];//功能识别码开始
     memcpy(checkbuff,(uchar*)&memory_str.fun_code,sizeof (memory_str));
     ushort crc2=0;
     for(uint n=0;n<sizeof (memory_str)/2-3;n++)
     {
         crc2=crc2^checkbuff[n];
     }
     //memory_str.addcrc=qToBigEndian(crc2);
     memory_str.addcrc=crc2;

    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 15;
    order_data.gap_time = 1;
    order_data.order_name = "内存下卸指令 : "+ui->cB_data_word2->currentText();
    order_data.order_kind = 6;
    order_data.order_len = sizeof(memory_str);
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, &memory_str,sizeof(memory_str));
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    //emit success_snack("成功");

    if(ui->lineEdit_memoryRec->text().isEmpty())return;
    for (int i=0;i<4;i++) {
        QFileInfo fileInfo(Tmpstr[i]);
        if (fileInfo.isFile()) {
            ncRe_Pfile[i]->remove();
            // qDebug()<<"文件存在";
        }
        ncRe_Pfile[i]->open(QIODevice::ReadWrite);
    }

}


//设置内存下卸接收目录
void sub1553_modecontrl::on_pushButton_RePath_clicked()
{
    QString qFileName = QFileDialog::getSaveFileName(this, tr("save file"),"",tr("dat(*.dat)"));
    if(qFileName.isEmpty())
    {
        return;
    }
    ui->lineEdit_memoryRec->setText(qFileName);

    for (int i=0;i<4;i++) {
        Tmpstr[i]=qFileName.left(qFileName.lastIndexOf("."))+"_1553Bch"+QString::number(i)+".dat";

        QFile qFile(Tmpstr[i]);
        if(!qFile.open(QFile::WriteOnly)) {
            QMessageBox::information(this,"提示","文件打开错误");
            return;
        }

        ncRe_Pfile[i]->setFileName(Tmpstr[i]);
        QFileInfo fileInfo(Tmpstr[i]);
        if (fileInfo.isFile()) {
            ncRe_Pfile[i]->remove();
            // qDebug()<<"文件存在";
        }
        ncRe_Pfile[i]->open(QIODevice::ReadWrite);
    }
}

//接收1553回传内存下卸数据
void sub1553_modecontrl::Rec_MemoryData(int ch,ushort *buff, int len)
{
    if (ch>=4)return ;
    if(ui->lineEdit_memoryRec->text().isEmpty())return;

    // 开辟缓存存储8帧*32字 数据
    ushort *Tran_Buff = new ushort[len];
    memset(Tran_Buff, 0, len * 2);
    //QString ss;
    for (int i = 0; i < len; i++) {
        //QString s1 =QString("%1 ").arg(buff[i], 4, 16, QLatin1Char('0')).toUpper();
        Tran_Buff[i] = qToBigEndian(buff[i]);
        //ss.append(s1);
    }
    //qDebug() << "NCxx::"<<ss;

    uchar* rebuff=new uchar[len*2];
    memcpy(rebuff, Tran_Buff, len*2);

    if(ncRe_Pfile[ch]->isOpen())
    {
        ncRe_Pfile[ch]->write((char*)rebuff,len*2);
    }

    delete [] rebuff;
    delete [] Tran_Buff;
}

//停止接收
void sub1553_modecontrl::on_pushButton_stopRec_clicked()
{
    if(ui->lineEdit_memoryRec->text().isEmpty())return;
    for (int ch=0;ch<4;ch++) {
        if(ncRe_Pfile[ch]->isOpen())
        {
            ncRe_Pfile[ch]->close();
        }
    }
}
