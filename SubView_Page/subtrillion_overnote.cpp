#include "subtrillion_overnote.h"

#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QString>
#include "ipdialog.h"
#include "ui_subtrillion_overnote.h"
#include <QVector>
#include <algorithm>
#include <map>
#include <QStandardPaths>
#define ORI_LEN 238 //原始数据一包最大长度

bool send_flag = true;  // 是否可以发送文件
bool thtest_flag = false;  // 测试丢帧发送文件


int us_change=100;

using namespace std;

subtrillion_overnote::subtrillion_overnote(QWidget* parent)
    : QWidget(parent), ui(new Ui::subtrillion_overnote) {
    ui->setupUi(this);
    sBar->show();
    ui->horizontalLayout->addWidget(sBar);
    ui->progressBar_qzsend->setAlignment(Qt::AlignVCenter);
    ui->progressBar_qzsend->setRange(0, 10000);
    ui->progressBar_qzsend->setValue(0);
    InitUI();

    ui->groupBox->setVisible(false);//收发数据
    ui->groupBox_2->setVisible(false);//发送数据
    //sBar->hide();//下面状态栏

    // 多文件上注表格
    ui->tableWidget_SumUpFile->setColumnCount(4);
    ui->tableWidget_SumUpFile->setHorizontalHeaderLabels(QStringList()
                                                         << "软件代号0x(2bytes)"
                                                         << "软件版本号0x(2bytes)"
                                                         << "软件写入地址0x(4bytes)"
                                                         << "文件路径");
    //    ui->tableWidget_SumUpFile->setColumnWidth(0, 150);
    //    ui->tableWidget_SumUpFile->setColumnWidth(1, 150);
    //    ui->tableWidget_SumUpFile->setColumnWidth(2, 160);
    //    ui->tableWidget_SumUpFile->setColumnWidth(3, 600);

    ui->tableWidget_SumUpFile->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自适应列宽
    ui->tableWidget_SumUpFile->horizontalHeader()->setMinimumSectionSize(100);
    ui->tableWidget_SumUpFile->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);




    models = new QStandardItemModel;

    // ui->tableWidget_SumUpFile->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // // 最小显示完整，出现滚动条
    // ui->tableWidget_SumUpFile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_SumUpFile->verticalHeader()->setVisible(true);  // 隐藏行号

    //文件上注
    //ui->pushButton_muchFileSend->setEnabled(false);

    //删除上注中转文件
    Remove_oldFile();

    Over_files="";

    for (int i=0;i<4;i++) {
        Re_Pfile[i]=new QFile(this);
    }

    //IP,MAC
    // 正则表达式设置IP和MAC输入
    QRegExp ipRegExp = QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_ip = new QRegExpValidator(ipRegExp,this);
    ui->lineEdit_s_IP->setValidator(m_ip);
    ui->lineEdit_m_IP->setValidator(m_ip);

    m_NetWorker = new NetWorker(m_DevVi);
    //单机选择标志
    check_dj[0]=true;//默认单机1
    for (int i=1;i<5;i++) {
        check_dj[i]=false;
    }

}

subtrillion_overnote::~subtrillion_overnote() {

    if(m_RxTimer->isActive())
    {
        m_RxTimer->stop();
    }
    m_RxTimer->deleteLater();
    if(m_TxTimer->isActive())
    {
        m_TxTimer->stop();
    }
    m_TxTimer->deleteLater();

    delete m_NetWorker;
    delete ui;

}

// 千兆发送进度
void subtrillion_overnote::get_jxjd(double value) {
    ui->progressBar_qzsend->setValue(value);
}

void subtrillion_overnote::get_farme(uint frame)
{
    workTxSum->setText(QString::number(frame));
}

uint subtrillion_overnote::toHex_uint(QString qstr)
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

ushort subtrillion_overnote::toHex_ushort(QString qstr)
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



// 界面初始化
void subtrillion_overnote::InitUI() {
    // resize(1000, 680);
    //  禁用连接，等待配置ip结束
    ui->pushButton_ConnectNet->setEnabled(false);
    // 创建接收定时器
    m_RxTimer = new QTimer(this);
    connect(m_RxTimer, SIGNAL(timeout()), this, SLOT(slot_RxTimerOut()));
    // 创建发送定时器
    m_TxTimer = new QTimer(this);
    connect(m_TxTimer, SIGNAL(timeout()), this, SLOT(slot_TxTimerOut()));
    // 创建状态栏
    workStatus = AddStatusWidget("状态：", "--");
    workStatus->setFixedWidth(100);
    workRxSum = AddStatusWidget("接收计数：", "--");
    workRxSum->setFixedWidth(90);
    workTxSum = AddStatusWidget("发送计数：", "--");
    workTxSum->setFixedWidth(90);
}
/*****************
功能：在状态栏添加参数
输入：data-指定转换的数据
作者：lengyuanjin
*****************/
QLabel* subtrillion_overnote::AddStatusWidget(QString name, QString value) {
    QLabel* nameLabel = new QLabel(name);
    QLabel* valueLabel = new QLabel(value);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(valueLabel);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    sBar->addWidget(widget);
    return valueLabel;
}

/*****************
功能：QByteArray数据转换成16进制字符串
输入：data-指定转换的数据
作者：lengyuanjin
*****************/
QString subtrillion_overnote::QByteArrayToHex(QByteArray data) {
    QString msg = "";
    for (int i = 0; i < data.length(); ++i) {
        msg += QString("%1 ")
                .arg((unsigned char)data[i], 2, 16, QLatin1Char('0'))
                .toUpper();
    }
    return msg;
}
/*****************
功能：QByteArray数据转换成ASCII字符串
输入：data-指定转换的数据
作者：lengyuanjin
*****************/
QString subtrillion_overnote::QByteArrayToAscii(QByteArray data) {
    QString msg = "";
    for (int i = 0; i < data.length(); ++i) {
        msg += data[i];
    }
    return msg;
}
/*****************
功能：十六进制字符串数据转换成QByteArray
输入：hex-十六进制字符串
作者：lengyuanjin
*****************/
QByteArray subtrillion_overnote::HexStrToQByteArray(QString hex) {
    QByteArray array;
    if (!hex.isEmpty()) {
        hex.remove(" ");
        array = QByteArray::fromHex(hex.toLatin1());
    }
    return array;
}
/*****************
功能：十六进制字符串数据转换成QByteArray（暂时无用）
输入：ascii-ASCII码字符串
作者：lengyuanjin
*****************/
QByteArray subtrillion_overnote::AsciiStrToQByteArray(QString ascii) {
    QByteArray array;
    if (!ascii.isEmpty()) {
        array = ascii.toLatin1();
    }
    return array;
}

/*****************
功能：数据接收更新UI定时器
作者：lengyuanjin
*****************/
void subtrillion_overnote::slot_RxTimerOut() {
    // 刷新消息总量
    workRxSum->setText(QString::number(m_RxSumBytes));

    QString msg = "";
    // 计算当前应该显示的数量
    for (uchar ch = 0; ch < 4; ++ch) {
        int surShowSum = m_RxRecordDatas[ch].count() - m_RxTimerSumMap[ch];
        if (surShowSum != 0) {
            for (int i = 0; i < surShowSum; ++i) {
                int sum = m_RxTimerSumMap[ch] + i;
                msg = QByteArrayToHex(m_RxRecordDatas[ch][sum]);
                ui->plainTextEdit_DatasRecord->appendPlainText(
                            QString("<通道%1>接收：%2").arg(ch).arg(msg));
            }
            m_RxTimerSumMap[ch] += surShowSum;
        }
    }
}
/*****************
功能：数据发送定时器（用于定时发送）
作者：lengyuanjin
*****************/
void subtrillion_overnote::slot_TxTimerOut() {
    if (m_NetWorker == nullptr || !m_NetConnectedFlag) {
        return;
    }
    // 获取发送区数据
    QString txtStr = ui->textEdit_TxDatas->toPlainText();
    QByteArray byteArray = HexStrToQByteArray(txtStr);
    uchar curCh = ui->comboBox_TxChannel->currentIndex();
    // 发送数据
    uint64_t count =
            m_NetWorker->NetSend(curCh, (uchar*)byteArray.data(), byteArray.length());
    if (count != 0) {
        ui->plainTextEdit_DatasRecord->appendPlainText(
                    QString("<通道%1>发送：%2").arg(curCh).arg(txtStr.toUpper()));
        m_TxSumBytes += count;
        workTxSum->setText(QString::number(m_TxSumBytes));
    }
}

/*****************
功能：数据接收
输入：ch-消息通道，buffer-接收的缓存，len缓存长度
作者：lengyuanjin
*****************/
void subtrillion_overnote::slot_GetRecvDatas(uchar ch, uchar* buffer,uint len) {
    if (len != 0) {
        m_RxSumBytes += len;
        QByteArray rxBuffer((char*)buffer, len);


        if(Re_Pfile[ch]->isOpen())
        {
            Re_Pfile[ch]->write((char*)buffer,len);
        }

        // 当前总接收数据量大于最大设置的最大数据量（条）怎清除掉第一个数据
        if (m_RxRecordDatas[ch].count() > ui->spinBox_RecordSum->value()) {
            m_RxRecordDatas[ch].removeAt(0);
        }
        m_RxRecordDatas[ch].append(rxBuffer);
    }
}

/*****************
功能：连接网络
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_pushButton_ConnectNet_clicked() {
    // false失败,true成功
    bool successed = true;
    // 开启连接或关闭连接
    if (!m_NetConnectedFlag) {
        //  开启接收线程
        successed &= m_NetWorker->Start();
        successed &= m_NetWorker->NetConnect();
    } else {
        //  先关闭使能（防止漏数）
        successed &= m_NetWorker->DisNetConnect();
        //  再停止接收线程
        successed &= m_NetWorker->Stop();
    }

    // 成功则需要处理界面状态
    if (successed) {
        m_NetConnectedFlag = !m_NetConnectedFlag;
        ui->pushButton_NetConfig->setEnabled(!m_NetConnectedFlag);
        ui->pushButton_ConnectNet->setText(m_NetConnectedFlag ? "断开连接": "连接");
        workStatus->setText(m_NetConnectedFlag ? "已连接" : "已断开");
        ui->checkBox_TimerSend->setChecked(!m_NetConnectedFlag);
        // 开启接收定时器
        if (m_RxTimer != nullptr) {
            if (m_NetConnectedFlag) {
                m_RxTimer->start(100);
            } else {
                m_RxTimer->stop();
            }
        }
        //文件上注
        ui->pushButton_muchFileSend->setEnabled(true);

    }
}

/*****************
功能：保存当前记录的数据
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_pushButton_SaveRecord_clicked() {
    QString filename =
            QFileDialog::getSaveFileName(this, "打开文本文件", "C:/", "*.txt");
    QFile file(filename);
    bool success = file.open(QIODevice::WriteOnly);
    if (!success) {
        return;
    }
    QString text = ui->plainTextEdit_DatasRecord->toPlainText();
    file.write(text.toUtf8());
    file.close();
}

/*****************
功能：清除接收
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_pushButton_ClearRxRecord_clicked() {
    ui->plainTextEdit_DatasRecord->clear();
    for (uchar ch = 0; ch < 4; ++ch) {
        m_RxRecordDatas[ch].clear();
        m_RxTimerSumMap[ch] = 0;
    }
    m_RxSumBytes = 0;
    workRxSum->setText("0");
}

/*****************
功能：清除发送
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_pushButton_ClearTxRecord_clicked() {
    m_TxRecordDatas.clear();
    ui->textEdit_TxDatas->setText("0");
    m_TxSumBytes = 0;
    workTxSum->setText("0");
}

/*****************
功能：开启定时发送
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_checkBox_TimerSend_clicked(bool checked) {
    if (checked) {
        if (m_TxTimer != nullptr) {
            m_TxTimer->start(ui->spinBox_RepTime->value());
        }
    } else {
        if (m_TxTimer != nullptr) {
            m_TxTimer->stop();
        }
    }
    // 禁用和启用发送按钮、发送编辑框
    ui->pushButton_NetSend->setEnabled(!checked);
    ui->textEdit_TxDatas->setEnabled(!checked);
}

/*****************
功能：网络配置弹窗
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_pushButton_NetConfig_clicked() {
    IPDialog* dlg = new IPDialog(m_DevVi, this);
    if (dlg->exec() == QDialog::Accepted) {
        ui->pushButton_ConnectNet->setEnabled(true);
        workStatus->setText("参数设置成功!");
        //  创建接收线程
        m_NetWorker = new NetWorker(m_DevVi);
        connect(m_NetWorker, SIGNAL(signal_RecvDatas(uchar, uchar*, uint)), this,SLOT(slot_GetRecvDatas(uchar, uchar*, uint)));
    }
    delete dlg;
    dlg = nullptr;
}

/*****************
功能：网络数据发送
作者：lengyuanjin
*****************/
void subtrillion_overnote::on_pushButton_NetSend_clicked() {
    if (m_NetWorker == nullptr || !m_NetConnectedFlag) {
        return;
    }
    // 获取发送区数据
    QString txtStr = ui->textEdit_TxDatas->toPlainText();
    QByteArray byteArray;
    byteArray = HexStrToQByteArray(txtStr);

    // 发送数据
    uchar curCh = ui->comboBox_TxChannel->currentIndex();
    uint64_t count =
            m_NetWorker->NetSend(curCh, (uchar*)byteArray.data(), byteArray.length());
    if (count != 0) {
        ui->plainTextEdit_DatasRecord->appendPlainText(
                    QString("<通道%1>发送：%2").arg(curCh).arg(txtStr.toUpper()));
        m_TxSumBytes += count;
        workTxSum->setText(QString::number(m_TxSumBytes));
    }
}


File_sendQthread::File_sendQthread(QObject* parent) : QObject(parent) {}

File_sendQthread::~File_sendQthread() {}


////单个文件读取文件
//void subtrillion_overnote::on_pushButton_readFile_clicked() {
//    // 打开文件选择对话框
//    // QString curPath=QCoreApplication::applicationDirPath();//引用程序路径
//    QString file_path = QFileDialog::getOpenFileName(this, tr("选择bin文件"), ui->lineEdit_upFilepath->text(), "*.bin *.dat");
//    if (file_path.isEmpty()) return;
//    ui->lineEdit_upFilepath->setText(file_path);
//}

////单个文件发送
//void subtrillion_overnote::on_pushButton_FileSend_clicked() {

//    //    qDebug()<<"1线程地址："<<QThread::currentThread();
//    // 创建暂存上注文件
//    QFile tmp_files;
//    QString fpath_end = QDir::currentPath() + "/千兆网上注暂存文件/Over_tmpFles.bin";
//    tmp_files.setFileName(fpath_end);
//    QFileInfo fileInfo(fpath_end);
//    if (fileInfo.isFile()) {
//        tmp_files.remove();
//        // qDebug()<<"文件存在";
//    }

//    if (!tmp_files.open(QIODevice::ReadWrite)) {
//        qDebug() << "files_create_fail";
//        //return;
//    }

//    // 获取单个文件路径
//    QString path_one =ui->lineEdit_upFilepath->text();
//    // 选取单个数据
//    QFile Data_file(path_one);
//    if (!(Data_file.open(QIODevice::ReadOnly))) {
//        qDebug() << "read_fail";
//        return;
//    }
//    // qDebug()<<path;
//    // 上注软件数据包格式(内层包)
//    One_pack one_pack;
//    // 软件总长度
//    uint tmp_uint = Data_file.size() + sizeof(one_pack);
//    one_pack.sorft_len = qToBigEndian(tmp_uint);
//    // 软件代号
//    one_pack.sorft_mark = toHex_ushort(ui->lineEdit_only_up1->text());
//    // 软件版本号
//    one_pack.sorft_version = toHex_ushort(ui->lineEdit_only_up2->text());
//    // 软件写入地址
//    one_pack.write_addr = toHex_uint(ui->lineEdit_only_up3->text());
//    // 写入单个头内容
//    tmp_files.write((char*)&one_pack, sizeof(one_pack));

//    // 写入单个上注文件
//    int file_len = Data_file.size();
//    uchar* ptr = Data_file.map(0, file_len);
//    tmp_files.write((char*)ptr, file_len);

//    Data_file.unmap(ptr);
//    Data_file.close();

//    tmp_files.close();
//    // tmp_files.remove();//删除文件

////    uchar curCh = ui->comboBox_TxChannel->currentIndex();
////    QString path =fpath_end;
////    if (send_flag)
////        emit send1(path, curCh, m_DevVi);
////    else {
////        QMessageBox::warning(this, "提示", "正在执行");
////    }
//}

// 多文件读取
void subtrillion_overnote::on_pushButton_SumFileRead_clicked() {

    QStringList files_path = QFileDialog::getOpenFileNames(this, tr("选择bin文件"),"", "*.bin *.dat");
    if (files_path.isEmpty()) return;
    int nrow = files_path.size();
    ui->tableWidget_SumUpFile->setRowCount(0);//文件信息
    QString tmp = "";
    for (int i = 0; i < nrow; i++) {
        ui->tableWidget_SumUpFile->insertRow(i);
        tmp = files_path.at(i);
        ui->tableWidget_SumUpFile->setItem(i, 0, new QTableWidgetItem("0000"));
        ui->tableWidget_SumUpFile->item(i,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
        ui->tableWidget_SumUpFile->setItem(i, 1, new QTableWidgetItem("0000"));
        ui->tableWidget_SumUpFile->item(i,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
        ui->tableWidget_SumUpFile->setItem(i, 2, new QTableWidgetItem("00000000"));
        ui->tableWidget_SumUpFile->item(i,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
        ui->tableWidget_SumUpFile->setItem(i, 3, new QTableWidgetItem(tmp));

    }


}

// 多文件上注
void subtrillion_overnote::on_pushButton_muchFileSend_clicked() {


    // 发送文件
    uchar curCh = ui->comboBox_TxChannel->currentIndex();
    QString path = ui->lineEdit_sectionUp2->text();
    if(path.isEmpty())
    {
         QMessageBox::warning(this, "提示", "路径错误");
        return;
    }
    if (send_flag)
    {
        thtest_flag=false;
        if(ui->comboBox_3->currentIndex()==0)//千兆网发送
        {
            //发送帧数
            workTxSum->setText(QString::number(0));
            emit send1(path, curCh, m_DevVi);
        }
        else//1553上注
        {
            //发送帧数
            workTxSum->setText(QString::number(0));
            vector<int> v_fr;
            v_fr.resize(0);
            emit send2(path,v_fr,19,28,curCh);
        }
    }
    else {
        QMessageBox::warning(this, "提示", "正在执行");
    }
}
// 创建暂存上注文件
QString subtrillion_overnote::Create_UpFile()
{

    QString fpath_end;
    // 创建暂存上注文件
    QFile tmp_files;
    fpath_end = QDir::currentPath() + "/千兆网上注暂存文件/Over_tmpFles代号_"+ui->tableWidget_SumUpFile->item(0, 0)->text()+".bin";
    tmp_files.setFileName(fpath_end);
    QFileInfo fileInfo(fpath_end);
    if (fileInfo.isFile()) {
        tmp_files.remove();
        // qDebug()<<"文件存在";
    }

    if (!tmp_files.open(QIODevice::ReadWrite)) {
        qDebug() << "files_create_fail";
        //return;
    }

    int cnt = ui->tableWidget_SumUpFile->rowCount();//获取列表文件个数
    // 上注软件数据包格式(最外层包)
    uint pack_Len = 0;
    UP_Sorft_pack out_pack;
    memset(&out_pack, 0, sizeof(out_pack));
    out_pack.sum_len = qToBigEndian(0);  // 长度先写入0，计算完长度添加
    out_pack.sorft_num = cnt;
    tmp_files.write((char*)&out_pack, sizeof(out_pack));
    pack_Len += sizeof(out_pack);

    for (int i = 0; i < cnt; i++) {
        // 获取单个路径
        QString path_one = ui->tableWidget_SumUpFile->item(i, 3)->text();
        // 选取单个数据
        QFile Data_file(path_one);
        if (!(Data_file.open(QIODevice::ReadOnly))) {
            qDebug() << "read_fail";
            return "";
        }
        // qDebug()<<path;
        // 上注软件数据包格式(内层包)
        One_pack one_pack;
        // 软件总长度
        uint tmp_uint = Data_file.size() + sizeof(one_pack);
        if(tmp_uint%2==1)tmp_uint+=1;//文件长度补双数
        one_pack.sorft_len = qToBigEndian(tmp_uint);
        // 软件代号(支持0x输入)
        one_pack.sorft_mark = toHex_ushort(ui->tableWidget_SumUpFile->item(i, 0)->text());
        // 软件版本号(支持0x输入)
        one_pack.sorft_version = toHex_ushort(ui->tableWidget_SumUpFile->item(i, 1)->text());
        // 软件写入地址(支持0x输入)
        one_pack.write_addr = toHex_uint(ui->tableWidget_SumUpFile->item(i, 2)->text());
        // 写入单个头内容
        tmp_files.write((char*)&one_pack, sizeof(one_pack));
        pack_Len += sizeof(one_pack);

        // 写入单个上注文件
        int file_len = Data_file.size();
        uchar* ptr = Data_file.map(0, file_len);
        tmp_files.write((char*)ptr, file_len);
        pack_Len += file_len;

        Data_file.unmap(ptr);
        Data_file.close();
    }

    if(pack_Len%2==1)pack_Len+=1;//文件长度补双数
    out_pack.sum_len = qToBigEndian(pack_Len);  // 数据包总长
    tmp_files.seek(0);                          // 移动文件光标到开头
    tmp_files.write((char*)&out_pack, sizeof(out_pack));

    // 计算CRC校验码
    char* tmps = new char[pack_Len + 1];
    tmp_files.seek(0);
    tmp_files.read(tmps, pack_Len);

    ushort* check = (ushort*)tmps;
    auto crccal = CRC16(check, (pack_Len + 1) / 2);
    // t_str.crc=qToBigEndian(crccal);
    ushort pack_crc =qToBigEndian(crccal);


    // 文件最后写入crc
    tmp_files.seek(pack_Len);
    tmp_files.write((char*)&pack_crc, 2);

    tmp_files.close();
    delete[] tmps;
    // tmp_files.remove();//删除文件
    QString p922=Create_922_UpFile(fpath_end);
    ui->lineEdit_sectionUp2->setText(p922);

    return p922;
}

//封装922上注文件
QString subtrillion_overnote::Create_922_UpFile(QString filesPath)
{

    if (filesPath.isEmpty()) {
        return "";
    }
    //打开封装好的上注文件
    QFile* File = new QFile("");
    File->setFileName(filesPath);
    if (File->open(QFile::ReadOnly)) {
    }
    else {
        return "";
    }
    //打开新文件封装922格式（每帧914字节+8字节头）
    QString tmpPath922=filesPath.left(filesPath.lastIndexOf("/"))+
            "/Over_922Fles代号_"+ui->tableWidget_SumUpFile->item(0, 0)->text()+".bin";
    QFile* File922 = new QFile("");
    File922->setFileName(tmpPath922);
    QFileInfo fileInfo2(tmpPath922);
    if (fileInfo2.isFile()) {
        File922->remove();
        // qDebug()<<"文件存在";
    }
    if (File922->open(QFile::ReadWrite)) {
    }
    else {
        return "";
    }

    // 发送数据
    int fLen = File->size();
    str_QZ t_str;
    char buff[sizeof(t_str.buff)] = {0};  // 每次文件906字节
    int farmecnt = (fLen + sizeof(t_str.buff) - 1) / sizeof(t_str.buff);

    for (int n = 0; n < farmecnt; n++)
    {
        memset(&t_str, 0, sizeof(t_str));
        memset(buff, 0xFF, sizeof(buff));

        int r_len=File->read((char*)buff, sizeof(buff));  // 超过长度不读取，是默认值（默认补齐914）
        //PDU
        t_str.PDU4[0]=0X15;//(0001 0101)
        //914=0x0392
        t_str.PDU4[1]=0x03;
        t_str.PDU4[2]=0x92;

        t_str.PDU4[3]=0;

        // 源实体ID
        t_str.soure_ID=10;
        // 包序号
        t_str.number = qToBigEndian((ushort)n);
        //目标实体ID
        t_str.goal_ID=19;


        ////914字节
        //数据头0x1731
        t_str.qzdata_head=qToBigEndian((ushort)0x1731);
        //0xC000开始
        t_str.list_mark=qToBigEndian((ushort)(0xC000+n));
        //包长N+1;906+1
        t_str.pack_len=qToBigEndian((ushort)(r_len+1));
        //qDebug()<<r_len;
        // 数据
        memcpy(&t_str.buff, buff, sizeof(buff));
        //有效数据校验
        ushort* checkbuff=new ushort[906/2];
        memcpy(checkbuff,(uchar*)&t_str.buff,sizeof (t_str.buff));
        ushort crc2=0;
        for(uint n=0;n<((uint)r_len/2);n++)
        {
            crc2=crc2^checkbuff[n];
        }
        t_str.qz_crc=crc2;
        //最后 一帧情况。。
        if(n==(farmecnt-1))//最后一帧，校验跟在有效数据后面，后面填充
        {
            if(r_len!=906)//最后一帧不满906
            {
                t_str.qz_crc=0xFFFF;
                memcpy(&t_str.buff[0]+r_len,&crc2,sizeof (crc2));//校验填充在前面
            }
        }
        delete [] checkbuff;
        // qDebug()<<n<<"0x"<<QString::number(crccal,16).toUpper();
        File922->write((char*)&t_str,sizeof (t_str));//922每帧写入

    }

    // 封封装完成
    File->close();
    File922->close();

    File->remove();//删除914无封装原始文件
    return tmpPath922;
}


//删除上注中转文件
void subtrillion_overnote::Remove_oldFile()
{

    //获取路径下所有文件
    QString path[2];
    path[0]=QDir::currentPath()+"/千兆网上注暂存文件/";
    path[1]=QDir::currentPath()+"/debug/千兆网上注暂存文件/";
    for (int p=0;p<2;p++) {

        QDir dir(path[p]);
        QStringList filename;
        filename<<"*.bin";//可叠加
        QStringList results;
        results=dir.entryList(filename,QDir::Files|QDir::Readable,QDir::Name);
        //qDebug()<<p<<results;
        //遍历删除
        for(int i=0;i<results.size();i++)
        {
            // 暂存上注文件
            QFile over_files;
            QString fpath_end = path[p]+results.at(i);
            over_files.setFileName(fpath_end);
            QFileInfo fileInfo(fpath_end);
            if (fileInfo.isFile()) {
                over_files.remove();
                // qDebug()<<"文件存在";
            }
        }
    }


}

void subtrillion_overnote::SendUP_1553OverOrder(int kind,uchar* data,int len)
{
    //功能识别码
    map<char,ushort> funkind;
    funkind[1]=0x0010;//网络发送文件
    funkind[2]=0x0011;//网络接收文件
    funkind[3]=0x0012;//网络停止发送
    funkind[4]=0x0013;//网络停止接收
    funkind[5]=0x0014;//总线接收文件
    funkind[6]=0x0015;//总线停止接收


    int orderlen=len;
    int framecnt=(orderlen+ORI_LEN-1)/ORI_LEN;
    uchar* Txbuf=new uchar[sizeof (STR_1553OverInstr)*framecnt+1];
    for(int i=0;i<framecnt;i++)
    {
        ushort thislen=ORI_LEN;//当前帧长度
        if(i==(framecnt-1))thislen=orderlen % ORI_LEN;//最后一帧
        int tmplen=thislen;//原始数据奇数长度需要补0x2A到偶数
        //第一层封装
        STR1553_SubPack str1553over;
        str1553over.Len=qToBigEndian(thislen);
        if(framecnt==1){
            str1553over.framemark=0;
        }
        else{
            if(i==0)str1553over.framemark=qToBigEndian((ushort)1);
            else if(i==(framecnt-1))str1553over.framemark=qToBigEndian((ushort)3);
            else str1553over.framemark=qToBigEndian((ushort)2);
        }
        str1553over.frameNUM=qToBigEndian((uint)i);

        //拷贝原始数据
        if(thislen%2!=0)tmplen+=1;
        str1553over.priDataBuff=new uchar[tmplen];
        memset(str1553over.priDataBuff,0x2A,tmplen);
        memcpy(str1553over.priDataBuff,data+(i*ORI_LEN),thislen);

        //计算校验位
        //        ushort* checkbuff=new ushort[(4+tmplen)/2];
        //        memcpy(checkbuff,(uchar*)&str1553over.framemark,4);
        //        memcpy(checkbuff+2,str1553over.priDataBuff,tmplen);
        //        ushort crc=0;
        //        for(int n=0;n<(4+tmplen)/2;n++)
        //        {
        //            crc+=checkbuff[n];
        //        }
        //        crc=~crc;
        //        str1553over.checksum=qToBigEndian(crc);
        //        delete [] checkbuff;
        //第二层封装////////////////////////////////////////////////////////////
        STR_1553OverInstr stroverInstr;
        stroverInstr.packmark_a=0;
        stroverInstr.packmark_b=1;
        stroverInstr.packmark_c=0;
        stroverInstr.packmark_d1=0x07;
        stroverInstr.packmark_d2=0x31;

        stroverInstr.packsequence_a=3;
        stroverInstr.packsequence_b1=(i&0x3F00)>>8;
        stroverInstr.packsequence_b2=i;

        //stroverInstr.packLen=qToBigEndian((ushort)(4+thislen));
        stroverInstr.packLen=qToBigEndian((ushort)(249));//写死
        stroverInstr.funrecog=qToBigEndian(funkind[kind]);

        memset(stroverInstr.applybuff,0x2A,sizeof (stroverInstr.applybuff));
        //读取应用数据
        memcpy(stroverInstr.applybuff,&str1553over,8);
        memcpy(stroverInstr.applybuff+8,str1553over.priDataBuff,tmplen);
        //memcpy(stroverInstr.applybuff+8+tmplen,&str1553over.checksum,2);
        //和校验
        ushort* checkbuff2=new ushort[(2+sizeof (stroverInstr.applybuff))/2];
        memcpy(checkbuff2,(uchar*)&stroverInstr.funrecog,2+sizeof(stroverInstr.applybuff));
        ushort crc2=0;
        for(uint n=0;n<(2+sizeof(stroverInstr.applybuff))/2;n++)
        {
            crc2=crc2^checkbuff2[n];
        }
        //stroverInstr.andcheck=qToBigEndian(crc2);
        stroverInstr.andcheck=crc2;
        delete [] checkbuff2;
        delete [] str1553over.priDataBuff;

        //存储数据
        memcpy(Txbuf+(i*sizeof (stroverInstr)),(uchar*)&stroverInstr,sizeof (stroverInstr));

    }

    for (int i=0;i<5;i++) {//单机1，2，3，4，全选
        if(check_dj[i]==false)continue;
        //1553板块发送
        emit send_order(Txbuf,sizeof (STR_1553OverInstr)*framecnt,19,2,i);
        emit success_snack("发送成功 通道"+QString::number(i+1));
    }


    //delete [] Txbuf;//(删除内存数据出错)

    return;
}

//公用添加到主界面窗口
void subtrillion_overnote::Public_Addorderlist(uchar *databuff, int buffLen, QString buffname,int kind)
{

    //列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 21;
    //order_data.obj_id = 0;//主任务界面选择
    order_data.gap_time = 1;
    order_data.order_name = buffname;
    order_data.order_kind = kind;
    order_data.order_len = buffLen;
    order_data.data_buf = new uchar[order_data.order_len];
    memcpy(order_data.data_buf, databuff,buffLen);
    QVariant varData;
    varData.setValue(order_data);
    emit Add_Order_ToList(varData);
    emit success_snack("成功");



}

//开始上注指令
void subtrillion_overnote::on_pB_startUP_clicked()
{

    //QString strpth = QDir::currentPath() + "/千兆网上注暂存文件/Over_tmpFles.bin";
    QString strpth = ui->lineEdit_sectionUp2->text();
    if (strpth.isEmpty()) {
        // emit qthfinish(status);
        QMessageBox::information(NULL, "提示", "未生成上注数据包");
        return ;
    }
    QFile* binFile = new QFile("");
    binFile->setFileName(strpth);
    if (binFile->open(QFile::ReadOnly)) {
    }
    else {
        //        QMessageBox::information(NULL, "提示", "文件打开错误");
        return;
    }
    uint tmp_size=0;
    //多少个922帧
    if (binFile->size() % (922) == 0)
        tmp_size = binFile->size() / (922);
    else
        tmp_size = binFile->size() / (922) + 1;

    //算总长
    tmp_size=tmp_size*922;

    // 开始帧
    upOrder_1553str start_QZ;
    memset(&start_QZ, 0, sizeof(start_QZ));

    if(ui->comboBox_3->currentIndex()==0)//千兆网发送
    {


        start_QZ.file_sendsize=qToBigEndian(tmp_size);
        start_QZ.only_masssize=qToBigEndian((ushort)922);
        if(ui->comboBox_upMode->currentIndex()==1)
        {
            start_QZ.file_sendsize=qToBigEndian((uint)922);
            start_QZ.file_path[0]=1;
        }

        if(ui->checkBox_sendson->isChecked())
        {
            SendUP_1553OverOrder(2,(uchar*)&start_QZ,sizeof (start_QZ));

        }
        else Public_Addorderlist((uchar*)&start_QZ,sizeof (start_QZ),"网络接收文件_代号"+ui->tableWidget_SumUpFile->item(0, 0)->text(),15);

    }

    else//1553上注
    {
        start_QZ.sur_IP[0]=0xFF;
        start_QZ.sur_IP[1]=0xFF;
        start_QZ.sur_IP[2]=0xFF;
        start_QZ.sur_IP[3]=0xFF;
        start_QZ.sur_port=0xFFFF;
        start_QZ.md_IP[0]=0xFF;
        start_QZ.md_IP[1]=0xFF;
        start_QZ.md_IP[2]=0xFF;
        start_QZ.md_IP[3]=0xFF;
        start_QZ.md_port=0xFFFF;
        start_QZ.file_sendsize=qToBigEndian(tmp_size);
        start_QZ.only_masssize=qToBigEndian((ushort)922);
        if(ui->comboBox_upMode->currentIndex()==1)
        {
            start_QZ.file_sendsize=qToBigEndian((uint)922);
            start_QZ.file_path[0]=1;
        }

        if(ui->checkBox_sendson->isChecked())
        {
            SendUP_1553OverOrder(5,(uchar*)&start_QZ,sizeof (start_QZ));
        }
        else Public_Addorderlist((uchar*)&start_QZ,sizeof (start_QZ),"总线接收文件_代号"+ui->tableWidget_SumUpFile->item(0, 0)->text(),18);

    }


    binFile->close();


}
//结束上注指令
void subtrillion_overnote::on_pB_endUP_clicked()
{

    QString tmp=ui->lineEdit_sectionUp2->text();
    if(tmp.isEmpty())
    {
        QMessageBox::information(NULL, "提示", "未生成上注数据包");
        return;
    }
    // 结束帧
    upOrder_1553str start_QZ;
    memset(&start_QZ, 0, sizeof(start_QZ));

    if(ui->comboBox_3->currentIndex()==0)//千兆网发送
    {
        //加上PDU 8字节，算总长
        start_QZ.file_sendsize=qToBigEndian(0);
        start_QZ.only_masssize=qToBigEndian((ushort)922);


        if(ui->checkBox_sendson->isChecked())
        {
            SendUP_1553OverOrder(4,(uchar*)&start_QZ,sizeof (start_QZ));
        }
        else Public_Addorderlist((uchar*)&start_QZ,sizeof (start_QZ),"网络停止接收",17);
    }
    else//1553上注
    {
        start_QZ.sur_IP[0]=0xFF;
        start_QZ.sur_IP[1]=0xFF;
        start_QZ.sur_IP[2]=0xFF;
        start_QZ.sur_IP[3]=0xFF;
        start_QZ.sur_port=0xFFFF;
        start_QZ.md_IP[0]=0xFF;
        start_QZ.md_IP[1]=0xFF;
        start_QZ.md_IP[2]=0xFF;
        start_QZ.md_IP[3]=0xFF;
        start_QZ.md_port=0xFFFF;
        //加上PDU 8字节，算总长
        start_QZ.file_sendsize=qToBigEndian(0);
        start_QZ.only_masssize=qToBigEndian((ushort)922);


        if(ui->checkBox_sendson->isChecked())
        {
            SendUP_1553OverOrder(6,(uchar*)&start_QZ,sizeof (start_QZ));
        }
        else Public_Addorderlist((uchar*)&start_QZ,sizeof (start_QZ),"总线停止接收",19);
    }

    emit send_1553upStop();


}

// 文件-千兆网发送线程
int File_sendQthread::send_UDP(QString strpth, uchar ch, uint divce)
{
    //    qDebug()<<"2线程地址："<<QThread::currentThread();
    //    qDebug()<<a<<"xxxxxx";

    // 打开文件
    send_flag = false;
    int status = 0;
    if (strpth.isEmpty()) {
        // emit qthfinish(status);
        return 0;
    }
    QFile* binFile = new QFile("");
    binFile->setFileName(strpth);
    if (binFile->open(QFile::ReadOnly)) {

    }
    else {
        send_flag = true;
        return 0;
    }

    uint cnt_frame=1;//帧从第一帧开始
    //int cnt_send_=0;
    // 发送数据
    int fLen = binFile->size();
    str_QZ str922;
    uchar buff[sizeof(str922)] = {0};  // 每次文件922字节
    int farmecnt = (fLen + sizeof(buff) - 1) / sizeof(buff);

    for (int n = 0; n < farmecnt; n++)
    {
        if(thtest_flag)//丢帧测试
        {
            if(n==0)continue;
            if(n==2)continue;
            if(n==4)continue;
            if(n==(farmecnt-5))continue;
            if(n==(farmecnt-4))continue;
            if(n==(farmecnt-3))continue;
            if(n==(farmecnt-2))continue;
            if(n==(farmecnt-1))continue;
        }
        memset(buff, 0, sizeof(buff));

        binFile->read((char*)buff, sizeof(buff));  // 超过长度不读取，是默认值（默认补齐922）

        // qDebug()<<n<<"0x"<<QString::number(crccal,16).toUpper();
        //qDebug()<<"send_cnt:"<<cnt_send_++;//（内容计数）

        //        QString sss="";
        //        int cc=sizeof (buff);
        //        for(int xx=0;xx<cc;xx++)
        //        {
        //            sss+=QString("%1 ").arg((uchar)buff[xx],2,16,QLatin1Char('0'));
        //        }
        //        qDebug()<<sss;
        //        ushort tmp=0;
        //        memcpy(&tmp,&buff[5],2);
        //        qDebug()<<qToBigEndian(tmp);

        if(ch==4)//千兆网单通道发送
        {
            for(int x=0;x<4;x++)
                status = PA_PCIe_1501_NET_Send(divce, x, (uchar*)buff, sizeof(buff));

        }
        else//千兆网4单通道全发送
        {
            status = PA_PCIe_1501_NET_Send(divce, ch, (uchar*)buff, sizeof(buff));
        }

        USleep(us_change);
        if (status != 0) {
            qDebug() << "send_mid_fail";
            break;
        }
        emit send_qzjxjd((n + 1) * 10000.00 / farmecnt);
        emit send_frame(cnt_frame++);
    }

    // 发送完成
    binFile->close();
    send_flag = true;

    return 0;
}

//千兆补包上注
int File_sendQthread::sendThr_UDP(QString strpth, uchar ch, uint divce, vector<int> up_frame) {
    //    qDebug()<<"2线程地址："<<QThread::currentThread();
    //    qDebug()<<a<<"xxxxxx";

    // 打开文件
    send_flag = false;
    int status = 0;
    if (strpth.isEmpty()) {
        // emit qthfinish(status);
        return 0;
    }
    QFile* binFile = new QFile("");
    binFile->setFileName(strpth);
    if (binFile->open(QFile::ReadOnly)) {

    }
    else {
        send_flag = true;
        return 0;
    }

    uint cnt_frame=1;//帧从第一帧开始
    //int cnt_send_=0;
    // 发送数据

    str_QZ t_str;// 每次文件922字节
    int farmecnt = up_frame.size();

    for (int n = 0; n < farmecnt; n++)
    {
        memset(&t_str, 0, sizeof(t_str));

        binFile->seek(up_frame.at(n)*922);
        // 数据
        binFile->read((char*)&t_str, sizeof(t_str));  // 超过长度不读取，是默认值
        // 包序号
        t_str.number = qToBigEndian((ushort)up_frame.at(n));

        // qDebug()<<n<<"0x"<<QString::number(crccal,16).toUpper();
        //qDebug()<<"send_cnt:"<<cnt_send_++;//（内容计数）
        status = PA_PCIe_1501_NET_Send(divce, ch, (uchar*)&t_str, sizeof(t_str));
        USleep(us_change);
        if (status != 0) {
            qDebug() << "send_mid_fail";
            break;
        }
        emit send_qzjxjd((n + 1) * 10000.00 / farmecnt);
        emit send_frame(cnt_frame++);
    }


    // 发送完成
    binFile->close();
    send_flag = true;

    return 0;
}


// 微秒级别定时器
int File_sendQthread::USleep(int us) {
    LARGE_INTEGER fre;
    if (QueryPerformanceFrequency(&fre)) {
        LARGE_INTEGER run, priv, curr;
        run.QuadPart = fre.QuadPart * us / 1000000;
        QueryPerformanceCounter(&priv);
        do {
            QueryPerformanceCounter(&curr);
        } while ((curr.QuadPart - priv.QuadPart) < run.QuadPart);
        curr.QuadPart -= priv.QuadPart;
        int nres = (curr.QuadPart * 1000000 / fre.QuadPart);
        return nres;
    }
    return -1;
}








//清空文件选取
void subtrillion_overnote::on_pushButton_clearfileChoose_clicked()
{
    ui->tableWidget_SumUpFile->setRowCount(0);//文件信息
    ui->lineEdit_sectionUp2->setText("");


}

//改变千兆上注发送速率
void subtrillion_overnote::on_cB_change_sendus_activated(int index)
{
    switch (index) {
    case 0://60us默认
        us_change=60;
        break;
    case 1://100us
        us_change=100;
        break;
    case 2://100ms
        us_change=100000;
        break;
    case 3://200ms
        us_change=200000;
        break;
    default:
        us_change=60;
        break;
    }
}

//生成上注文件
void subtrillion_overnote::on_pushButton_creatoverfile_clicked()
{
    if(ui->tableWidget_SumUpFile->rowCount()==0)
    {
        QMessageBox::information(NULL, "提示", "未读取文件");
        return;//获取列表文件个数
    }

    QString fpath_end=Create_UpFile();// 创建暂存上注文件
    Over_files=fpath_end;
}
//丢帧测试
void subtrillion_overnote::on_pB_threadframe_clicked()
{

    // 发送文件
    uchar curCh = ui->comboBox_TxChannel->currentIndex();
    QString path = ui->lineEdit_sectionUp2->text();
    if(path.isEmpty())return;
    if (send_flag)
    {
        thtest_flag=true;
        if(ui->comboBox_3->currentIndex()==0)//千兆网发送
        {
            //发送帧数
            workTxSum->setText(QString::number(0));
            emit send1(path, curCh, m_DevVi);
        }
        else//1553上注
        {
            vector<int> v_fr;
            v_fr.resize(0);
            emit send2(path,v_fr,0,0,curCh);
        }
    }
    else {
        QMessageBox::warning(this, "提示", "正在执行");
    }
}
//选择帧序号上注
void subtrillion_overnote::on_pB_choosepackUP_clicked()
{

    // 发送文件
    uchar curCh = ui->comboBox_TxChannel->currentIndex();
    QString path = ui->lineEdit_sectionUp2->text();
    if(path.isEmpty())return;
    if (send_flag)
    {
        vector<int> v_fr;
        v_fr.resize(0);
        QString tmp_cstr=ui->lineEdit_dNum->text();
        tmp_cstr.replace("，",",");
        QString tmp;
        QStringList col=tmp_cstr.split(",");//个数
        for(int c=0;c<col.size()-1;c++)
        {
            //幅度值
            tmp = tmp_cstr.left(tmp_cstr.indexOf(','));
            tmp_cstr = tmp_cstr.mid(tmp_cstr.indexOf(',') + 1,tmp_cstr.size() - tmp_cstr.indexOf(','));
            v_fr.push_back(tmp.toInt());
        }

        if(ui->comboBox_3->currentIndex()==0)//千兆网发送
        {
            //发送帧数
            workTxSum->setText(QString::number(0));
            emit send_thre(path, curCh, m_DevVi,v_fr);
        }
        else//1553上注
        {
            emit send2(path,v_fr,0,0,curCh);
        }
    }
    else {
        QMessageBox::warning(this, "提示", "正在执行");
    }
}
//接收目录
void subtrillion_overnote::on_pushButton_rePath_clicked()
{

    //    QString desktop_path=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);//桌面路径
    //    QString Dirpath = QFileDialog::getExistingDirectory(this,tr("选择文件路径"),desktop_path);

    QString qFileName = QFileDialog::getSaveFileName(this, tr("save file"),"",tr("dat(*.dat);;bin(*.bin)"));
    if(qFileName.isEmpty())
    {
        return;
    }
    ui->lineEdit_rePath->setText(qFileName);
    QString tmpstr[4];//4个网络通道的文件
    for (int i=0;i<4;i++) {
        tmpstr[i]=qFileName.left(qFileName.lastIndexOf("."))+"_ch"+QString::number(i+1)+".dat";

        QFile qFile(tmpstr[i]);
        if(!qFile.open(QFile::WriteOnly)) {
            QMessageBox::information(this,"提示","文件打开错误");
            return;
        }

        Re_Pfile[i]->setFileName(tmpstr[i]);
        QFileInfo fileInfo(tmpstr[i]);
        if (fileInfo.isFile()) {
            Re_Pfile[i]->remove();
            // qDebug()<<"文件存在";
        }
        Re_Pfile[i]->open(QIODevice::ReadWrite);
    }




}
//上注回传开始
void subtrillion_overnote::on_pushButton_reStart_clicked()
{

    if(ui->lineEdit_rePath->text().isEmpty())
    {
        QMessageBox::information(this,"提示","未设置接收路径");
        return;
    }
    upOrder_1553str start_QZ;
    memset(&start_QZ, 0, sizeof(start_QZ));


    QString tmpip=ui->lineEdit_s_IP->text();
    QString sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    start_QZ.sur_IP[0]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    start_QZ.sur_IP[1]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    start_QZ.sur_IP[2]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    start_QZ.sur_IP[3]=sss.toInt();
    start_QZ.sur_port=qToBigEndian(ui->lineEdit_s_sock->text().toUShort());


    QString tmp2ip=ui->lineEdit_m_IP->text();
    QString sss2=tmp2ip.left(tmp2ip.indexOf("."));
    tmp2ip=tmp2ip.right(tmp2ip.length()-tmp2ip.indexOf(".")-1);
    start_QZ.md_IP[0]=sss2.toInt();
    sss2=tmp2ip.left(tmp2ip.indexOf("."));
    tmp2ip=tmp2ip.right(tmp2ip.length()-tmp2ip.indexOf(".")-1);
    start_QZ.md_IP[1]=sss2.toInt();
    sss2=tmp2ip.left(tmp2ip.indexOf("."));
    tmp2ip=tmp2ip.right(tmp2ip.length()-tmp2ip.indexOf(".")-1);
    start_QZ.md_IP[2]=sss2.toInt();
    sss2=tmp2ip.left(tmp2ip.indexOf("."));
    start_QZ.md_IP[3]=sss2.toInt();
    start_QZ.md_port=qToBigEndian(ui->lineEdit_m_sock->text().toUShort());

    start_QZ.file_py=qToBigEndian(ui->lineEdit_re_py->text().toUInt());
    start_QZ.file_sendsize=qToBigEndian(ui->lineEdit_re_sendsize->text().toUInt());
    start_QZ.only_masssize=qToBigEndian((ushort)922);
    start_QZ.send_cyc=qToBigEndian(ui->lineEdit_re_sendcyc->text().toUShort());



    if(ui->checkBox_sendson->isChecked())
    {
        SendUP_1553OverOrder(1,(uchar*)&start_QZ,sizeof (start_QZ));

    }
    else Public_Addorderlist((uchar*)&start_QZ,sizeof (start_QZ),"网络发送文件",14);

}
//上注回传停止
void subtrillion_overnote::on_pushButton_reEnd_clicked()
{
    upOrder_1553str start_QZ;
    memset(&start_QZ, 0, sizeof(start_QZ));


    QString tmpip=ui->lineEdit_s_IP->text();
    QString sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    start_QZ.sur_IP[0]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    start_QZ.sur_IP[1]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    tmpip=tmpip.right(tmpip.length()-tmpip.indexOf(".")-1);
    start_QZ.sur_IP[2]=sss.toInt();
    sss=tmpip.left(tmpip.indexOf("."));
    start_QZ.sur_IP[3]=sss.toInt();
    start_QZ.sur_port=qToBigEndian(ui->lineEdit_s_sock->text().toUShort());


    QString tmp2ip=ui->lineEdit_m_IP->text();
    QString sss2=tmp2ip.left(tmp2ip.indexOf("."));
    tmp2ip=tmp2ip.right(tmp2ip.length()-tmp2ip.indexOf(".")-1);
    start_QZ.md_IP[0]=sss2.toInt();
    sss2=tmp2ip.left(tmp2ip.indexOf("."));
    tmp2ip=tmp2ip.right(tmp2ip.length()-tmp2ip.indexOf(".")-1);
    start_QZ.md_IP[1]=sss2.toInt();
    sss2=tmp2ip.left(tmp2ip.indexOf("."));
    tmp2ip=tmp2ip.right(tmp2ip.length()-tmp2ip.indexOf(".")-1);
    start_QZ.md_IP[2]=sss2.toInt();
    sss2=tmp2ip.left(tmp2ip.indexOf("."));
    start_QZ.md_IP[3]=sss2.toInt();
    start_QZ.md_port=qToBigEndian(ui->lineEdit_m_sock->text().toUShort());



    start_QZ.file_py=qToBigEndian(ui->lineEdit_re_py->text().toUInt());
    start_QZ.file_sendsize=qToBigEndian(ui->lineEdit_re_sendsize->text().toUInt());
    start_QZ.only_masssize=qToBigEndian((ushort)922);
    start_QZ.send_cyc=qToBigEndian(ui->lineEdit_re_sendcyc->text().toUShort());


    if(ui->checkBox_sendson->isChecked())
    {
        SendUP_1553OverOrder(3,(uchar*)&start_QZ,sizeof (start_QZ));

    }
    else Public_Addorderlist((uchar*)&start_QZ,sizeof (start_QZ),"网络停止发送",16);
    if(ui->lineEdit_rePath->text()!="")
    {
        for (int i=0;i<4;i++) {
            Re_Pfile[i]->close();
        }

    }

}

void subtrillion_overnote::on_comboBox_3_activated(int index)
{
    switch (index) {
    case 0://UDP千兆口
        ui->pushButton_NetConfig->setEnabled(1);
        if(m_NetConnectedFlag)
        {
            //文件上注
            ui->pushButton_muchFileSend->setEnabled(true);
        }
        else
        {
            //文件上注
            ui->pushButton_muchFileSend->setEnabled(false);
        }

        ui->comboBox_TxChannel->setItemText(0,"千兆网_通道1");
        ui->comboBox_TxChannel->setItemText(1,"千兆网_通道2");
        ui->comboBox_TxChannel->setItemText(2,"千兆网_通道3");
        ui->comboBox_TxChannel->setItemText(3,"千兆网_通道4");
        ui->comboBox_TxChannel->setItemText(4,"千兆网_全选4个通道");
        break;
    case 1://1553接口
        ui->pushButton_NetConfig->setEnabled(0);
        //文件上注
        ui->pushButton_muchFileSend->setEnabled(true);

        ui->comboBox_TxChannel->setItemText(0,"1553B_通道1");
        ui->comboBox_TxChannel->setItemText(1,"1553B_通道2");
        ui->comboBox_TxChannel->setItemText(2,"1553B_通道3");
        ui->comboBox_TxChannel->setItemText(3,"1553B_通道4");
        ui->comboBox_TxChannel->setItemText(4,"1553B_全选4个通道");
        break;
    default:
        break;
    }
}

//对dat,bin 文件进行帧分割导出xlsx
void subtrillion_overnote::on_pushButton_chooseDivision_clicked()
{
    //打开数据文件
    QString files_path = QFileDialog::getOpenFileName(this, tr("选择数据文件"),QDir::currentPath() + "/千兆网上注暂存文件", "*.bin *.dat");
    if (files_path.isEmpty()) return;
    QFile tmp_file;
    tmp_file.setFileName(files_path);
    if (!tmp_file.open(QIODevice::ReadOnly)) {
        qDebug() << "files_create_fail";
        return;
    }

    //创建xlsx文件
    QDateTime tm=QDateTime::currentDateTime();
    QString strtm=tm.toString("hh_mm_ss");
    QString xlsxFileName = files_path.left(files_path.lastIndexOf("."))+"时间"+strtm+"分帧导出.xlsx";
    QXlsx::Document xlsx;

    //设置列宽
    xlsx.setColumnWidth(2,100);//第1列，20列宽
    //获取列表头

    xlsx.write(1, 1,"帧序号");
    xlsx.write(1, 2,"帧内容");
    //循环写入xlsx
    uint fLen=tmp_file.size();
    int frameLen=ui->lineEdit_outPutLen_excel->text().toInt();
    int cnt=(fLen + frameLen - 1) /frameLen;

    uchar* frame_Data=new uchar[frameLen];
    QString pack_order="";

    for (int n=0;n<cnt;n++) {
        //qDebug()<<i;
        memset(frame_Data,0,frameLen);
        tmp_file.read((char*)frame_Data,frameLen);

        pack_order="";
        for (int i=0;i<frameLen;i++) {
            pack_order+=QString("%1 ").arg(frame_Data[i],2,16,QLatin1Char('0'));
        }

        xlsx.write(n+2, 1,n+1);
        xlsx.write(n+2, 2,pack_order);
    }
    if (!xlsx.saveAs(xlsxFileName)) {
        QMessageBox::warning(this, "提示", "文件保存失败");
        return;
    }
    xlsx.deleteLater();//释放指针
    tmp_file.close();
    emit success_snack("生成xlsx成功");
}


//xlsx->dat
void subtrillion_overnote::on_pB_xlsx_dat_clicked()
{
    //打开指令文件
    QString qFileName = QFileDialog::getOpenFileName(this, tr("open file"), "", tr("*.xlsx  *.xls"));
    if(qFileName.isEmpty())return;
    //创建dat文件
    QString dat_path=qFileName;
    int a=dat_path.indexOf(".");
    QDateTime tm=QDateTime::currentDateTime();
    QString qtm=tm.toString("_时间hh_mm_ss");
    QString path1=dat_path.left(a)+qtm+".dat";
    QString path2=dat_path.left(a)+qtm+"重复3份.dat";

    QFile dat_file(path1);
    if(!dat_file.open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this,"提示","创建失败");
        return;
    }

    //读取xlsx
    QXlsx::Document xlsxR(qFileName);

    if(!xlsxR.load())
    {
        QMessageBox::warning(this,"提示","excel打开失败");
        qDebug()<<"excel打开失败";
    }
    //检查表格格式是否有正确
    if(!xlsxR.selectSheet("Sheet1"))
    {
        qDebug()<<"未找到页“Sheet1";
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    int colsum=xlsxR.dimension().columnCount();
    uint pack_len=4;//在开头添加文件长度
    dat_file.write((char*)&pack_len,4);

    uint uint_pl;
    ushort ushort_pl;
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {

            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                //qDebug()<< var.toString();


                if(j==1)//软件代号
                {
                    ushort_pl=toHex_ushort(var.toString());
                    dat_file.write((char*)&ushort_pl,2);
                    pack_len+=2;
                }
                if(j==2)//起始页地址
                {
                    uint_pl=toHex_uint(var.toString());
                    dat_file.write((char*)&uint_pl,4);
                    pack_len+=4;
                }
                if(j==3)//长度
                {
                    ushort_pl=toHex_ushort(var.toString());
                    dat_file.write((char*)&ushort_pl,2);
                    pack_len+=2;
                }

            }

        }

    }

    dat_file.seek(0);
    pack_len=qToBigEndian(pack_len);
    dat_file.write((char*)&pack_len,4);
    xlsxR.deleteLater();//释放指针


    //拷贝三份
    QFile dat_file2(path2);
    if(!dat_file2.open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this,"提示","创建失败");
        return;
    }

    //拷贝三份
    dat_file.seek(0);
    dat_file2.write(dat_file.readAll());
    dat_file.seek(0);
    dat_file2.write(dat_file.readAll());
    dat_file.seek(0);
    dat_file2.write(dat_file.readAll());

    dat_file.close();
    dat_file.remove();
    dat_file2.close();
    QMessageBox::warning(this,"提示","转换完成");
}

//选择上注数据包
void subtrillion_overnote::on_pB_chooseUpFile_clicked()
{
    QString files_path = QFileDialog::getOpenFileName(this, tr("选择bin文件"),"", "*.bin *.dat");
    if (files_path.isEmpty()) return;
    ui->lineEdit_sectionUp2->setText(files_path);//文件路径
}
//xlsx->dat格式2
void subtrillion_overnote::on_pB_xlsx_dat2_clicked()
{
    //打开指令文件
    QString qFileName = QFileDialog::getOpenFileName(this, tr("open file"), "", tr("*.xlsx  *.xls"));
    if(qFileName.isEmpty())return;
    //创建dat文件
    QString dat_path=qFileName;
    int a=dat_path.indexOf(".");
    QDateTime tm=QDateTime::currentDateTime();
    QString qtm=tm.toString("_时间hh_mm_ss");
    QString path1=dat_path.left(a)+qtm+".dat";

    QFile dat_file(path1);
    if(!dat_file.open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this,"提示","创建失败");
        return;
    }

    //读取xlsx
    QXlsx::Document xlsxR(qFileName);

    if(!xlsxR.load())
    {
        QMessageBox::warning(this,"提示","excel打开失败");
        qDebug()<<"excel打开失败";
    }
    //检查表格格式是否有正确
    if(!xlsxR.selectSheet("Sheet1"))
    {
        qDebug()<<"未找到页“Sheet1";
        return;
    }

    int rowsum=xlsxR.dimension().rowCount();
    int colsum=xlsxR.dimension().columnCount();
    uint pack_len=4;//在开头添加文件长度
    dat_file.write((char*)&pack_len,4);

    uint uint_pl;
    ushort ushort_pl;
    uchar uchar_pl;
    for(int i=2;i<rowsum+1;i++)//行
    {
        for(int j=1;j<colsum+1;j++)//列
        {

            Cell* cell = xlsxR.cellAt(i, j);//(1,1)第一个格子内容
            if ( cell != NULL )
            {
                QVariant var = cell->value(); // read cell value (number(double), QDateTime, QString ...)
                //qDebug()<< var.toString();


                if(j==1)//软件代号
                {
                    ushort_pl=toHex_ushort(var.toString());
                    dat_file.write((char*)&ushort_pl,2);
                    pack_len+=2;
                }
                if(j==2)//起始页地址
                {
                    uint_pl=toHex_uint(var.toString());
                    dat_file.write((char*)&uint_pl,4);
                    pack_len+=4;
                }
                if(j==3)//长度
                {
                    ushort_pl=toHex_ushort(var.toString());
                    dat_file.write((char*)&ushort_pl,2);
                    pack_len+=2;
                }
                if(j==4)//单机标识
                {
                    uchar_pl=var.toInt();
                    dat_file.write((char*)&uchar_pl,1);
                    pack_len+=1;
                }
                if(j==5)//模块标识
                {
                    uchar_pl=var.toInt();
                    dat_file.write((char*)&uchar_pl,1);
                    pack_len+=1;
                }

            }

        }

    }

    dat_file.seek(0);
    pack_len=qToBigEndian(pack_len);
    dat_file.write((char*)&pack_len,4);
    xlsxR.deleteLater();//释放指针


    dat_file.close();

    QMessageBox::warning(this,"提示","转换完成");
}
