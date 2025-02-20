#include "sub1553_gkmaygsl.h"

#include "ui_sub1553_gkmaygsl.h"
#include<QFileDialog>
#include<QMessageBox>

sub1553_gkmaygsl::sub1553_gkmaygsl(QWidget *parent)
    : QWidget(parent), ui(new Ui::sub1553_gkmaygsl) {
  ui->setupUi(this);
}

sub1553_gkmaygsl::~sub1553_gkmaygsl() { delete ui; }

void sub1553_gkmaygsl::Pblic_Addorderlist(uchar *databuff, int buffLen,
                                          QString buffname) {
  // 列表封装
  Order_List_Object order_data;
  order_data.mode = false;
  order_data.page_id = 4;
  order_data.gap_time = 1;
  order_data.order_name = buffname;
  order_data.order_kind = 2;
  order_data.order_len = buffLen;
  order_data.data_buf = new uchar[order_data.order_len];
  memcpy(order_data.data_buf, databuff, buffLen);
  QVariant varData;
  varData.setValue(order_data);
  emit Add_Order_ToList(varData);
  emit success_snack("成功");
}

uint sub1553_gkmaygsl::toHex_uint(QString qstr)
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

// L频段天线子阵TR开关选择
void sub1553_gkmaygsl::on_on_PB_switch_clicked_clicked() {
  L_TRswitch l_tr;
  l_tr.ordermark = 0x60;
  uchar tmp = 0;
  tmp = (ui->L_Submatrix1->isChecked() << 0) +
        (ui->L_Submatrix2->isChecked() << 1) +
        (ui->L_Submatrix3->isChecked() << 2) +
        (ui->L_Submatrix4->isChecked() << 3);
  l_tr.TRswitch = tmp;

  // 列表封装
  Pblic_Addorderlist((uchar *)&l_tr, sizeof(L_TRswitch),
                     "L频段天线子阵TR开关选择");
}

// 内存下卸 0x61
void sub1553_gkmaygsl::on_PB_SAR_end_clicked() {
  SAR_shutdown sar_down;

  // 指令标识
  sar_down.ordermark = 0x61;
  // 启停标识
  sar_down.type = ui->CB__0x61_1->currentIndex();
  // 起始地址
  sar_down.s_addr=toHex_uint(ui->lineEdit_0x61_2->text());
  // 长度
  sar_down.len=qToBigEndian(ui->lineEdit_0x61_3->text().toUShort());

  // 列表封装
  Pblic_Addorderlist((uchar *)&sar_down, sizeof(SAR_shutdown), "内存下卸 : "+ui->CB__0x61_1->currentText());
}


// 清空雷达指令包
void sub1553_gkmaygsl::on_PB_radar_clear_clicked() {
  Radar_clear radar_clear;
  radar_clear.ordermark = 0x63;
  radar_clear.bl = 0xFF;

  // 列表封装
  Pblic_Addorderlist((uchar *)&radar_clear, sizeof(Radar_clear),
                     "清空雷达指令包");
}

// 删除单个雷达指令包
void sub1553_gkmaygsl::on_PB_single_delete_clicked() {
  Radar_delsingal radar_singal;
  radar_singal.ordermark = 0x64;
  radar_singal.bl = 0xFF;
  radar_singal.number = qToBigEndian(ui->LE_single_delete->text().toUShort());

  // 列表封装
  Pblic_Addorderlist((uchar *)&radar_singal, sizeof(Radar_delsingal),
                     "删除单个雷达指令包");
}

// 重要数据采集 0x65
void sub1553_gkmaygsl::on_PB_radar_modify_clicked() {
  Radar_modify radar_mod;
  radar_mod.ordermark = 0x65;
  radar_mod.bl = 0xFF;

  // 列表封装
  Pblic_Addorderlist((uchar *)&radar_mod, sizeof(Radar_modify),"重要数据采集");
}

// 重要数据恢复 0x66
void sub1553_gkmaygsl::on_pushButton_5_clicked() {
  Radar_backup back_up;
  back_up.ordermark = 0x66;
  back_up.bl = 0xFF;

  // 列表封装
  Pblic_Addorderlist((uchar *)&back_up, sizeof(Radar_backup),"重要数据恢复");
}

// 清空所有上注的补丁包
void sub1553_gkmaygsl::on_PB_clearall_clicked() {
  servicePack_Clear pack_clear;
  pack_clear.ordermark = 0x67;
  pack_clear.bl = 0xFF;

  // 列表封装
  Pblic_Addorderlist((uchar *)&pack_clear, sizeof(servicePack_Clear),
                     "清空所有上注的补丁包");
}

// L频段阵面与通道对应关系
void sub1553_gkmaygsl::on_PB_L_link_clicked() {
  L_matchup lmat;
  lmat.ordermark = 0x68;
  lmat.select = ui->CB_L_link->currentIndex() + 1;

  // 列表封装
  Pblic_Addorderlist((uchar *)&lmat, sizeof(L_matchup),
                     "L频段阵面与通道对应关系");
}

// 导航闭锁开关
void sub1553_gkmaygsl::on_PB_navi_lock_clicked() {
  Navi_lock navi_lock;
  navi_lock.ordermark = 0x69;
  navi_lock.switchset = ui->comboBox_navi_locks->currentIndex();

  // 列表封装
  Pblic_Addorderlist((uchar *)&navi_lock, sizeof(Navi_lock), "导航闭锁开关:"+ui->comboBox_navi_locks->currentText());
}



// 温度关断保护使能0x71
void sub1553_gkmaygsl::on_PB_T_protect_clicked() {
  T_protect t_prot;
  memset(&t_prot,0,sizeof (t_prot));
  t_prot.ordermark = 0x71;
  t_prot.T_switch = ui->CB_T_protect->currentIndex();

  // 列表封装
  Pblic_Addorderlist((uchar *)&t_prot, sizeof(T_protect), "温度关断保护使能："+ui->CB_T_protect->currentText());
}
//L频段数字综合单元CPU软件补丁注入0x6A
void sub1553_gkmaygsl::on_pushButton_6A_in_clicked()
{
    L_CPU6A arr;
    memset(&arr,0,sizeof (arr));
    // 指令标识
    arr.ordermark = 0x6A;
    //246字节数据
    QString path=ui->lineEdit_6A_path->text();
    QFile txt_file(path);
    if(!(txt_file.open(QIODevice::ReadOnly|QIODevice::Text)))
    {
        QMessageBox::warning(this,tr("打开文件失败"),tr("路径")+path);
        return ;
    }
    QTextStream txtInput(&txt_file);
    QString read_str;
    while (!txtInput.atEnd()) {
        read_str+=txtInput.readLine();
    }
    read_str.replace(" ","");
    read_str.replace("\n","");
    int this_len=(read_str.size() + 1) / 2;//当前文件数据长度

    QString tmps=read_str;
    QByteArray hex_data=QByteArray::fromHex(tmps.toLatin1());//将字节流转换位16进制,char型
    uchar* data_buf=(uchar*)hex_data.data();//获取地址
    if (this_len>256)this_len=256;
    memcpy(&arr.datas[0],data_buf,this_len);

    // 列表封装
    Pblic_Addorderlist((uchar *)&arr, sizeof(arr), "L频段数字综合单元CPU软件补丁注入");
}
//6A读取文件
void sub1553_gkmaygsl::on_pushButton_6A_read_clicked()
{
    //打开文件选择对话框
    QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt"));
    if(file_path.size() <= 0) return;
   // QFileInfo fileinfo(file_path.at(0));    //读取文件
    ui->lineEdit_6A_path->setText(file_path.at(0));
}

//L频段数字综合单元CPU波控码0x6B
void sub1553_gkmaygsl::on_pushButton_6B_order_clicked()
{
    L_CPU6B arr;
    memset(&arr,0,sizeof (arr));
    // 指令标识
    arr.ordermark = 0x6B;
    //246字节数据
    QString path=ui->lineEdit_6A_path->text();
    QFile txt_file(path);
    if(!(txt_file.open(QIODevice::ReadOnly|QIODevice::Text)))
    {
        QMessageBox::warning(this,tr("打开文件失败"),tr("路径")+path);
        return ;
    }
    QTextStream txtInput(&txt_file);
    QString read_str;
    while (!txtInput.atEnd()) {
        read_str+=txtInput.readLine();
    }
    read_str.replace(" ","");
    read_str.replace("\n","");
    int this_len=(read_str.size() + 1) / 2;//当前文件数据长度

    QString tmps=read_str;
    QByteArray hex_data=QByteArray::fromHex(read_str.toLatin1());//将字节流转换位16进制,char型
    uchar* data_buf=(uchar*)hex_data.data();//获取地址
    if (this_len>256)this_len=256;
    memcpy(&arr.datas[0],data_buf,this_len);

    // 列表封装
    Pblic_Addorderlist((uchar *)&arr, sizeof(arr), "L频段数字综合单元CPU波控码");
}

//6B读取文件
void sub1553_gkmaygsl::on_pushButton_6B_read_clicked()
{
    //打开文件选择对话框
    QStringList file_path = QFileDialog::getOpenFileNames(NULL,"数据选取","",tr("*.txt"));
    if(file_path.size() <= 0) return;
   // QFileInfo fileinfo(file_path.at(0));    //读取文件
    ui->lineEdit_6B_path->setText(file_path.at(0));
}



//SSD盘还原  0x6c
void sub1553_gkmaygsl::on_PB_ssd_hy_clicked()
{
    uchar str[3];
    str[0]= 0x6c;
    str[1]= ui->lineEdit_ssdhy_1->text().toInt();
    str[2]=ui->lineEdit_ssdhy_2->text().toInt();

    // 列表封装
    Pblic_Addorderlist((uchar *)&str, sizeof(str),"SSD盘还原");
}


//设备主备启动设置0x72
void sub1553_gkmaygsl::on_pushButton_0x72_clicked()
{

    str_0x72 str;
    memset(&str,0,sizeof (str));
    //指令ID
    str.orderID = 0x72;
    //设备选择
    uchar a1=2,a2=2,a3=2,a4=2;
    if(ui->checkBox_0x72_1bit0_1->isChecked())a1=1;
    if(ui->checkBox_0x72_1bit2_3->isChecked())a2=1;
    if(ui->checkBox_0x72_1bit4_5->isChecked())a3=1;
    if(ui->checkBox_0x72_1bit6_7->isChecked())a4=1;
    str.devchoose = (a1)+(a2<<2)+(a3<<4)+(a4<<6);
    //可重构射频前端主备
    str.kcgspqd=ui->comboBox_0x72_2->currentIndex()+1;
    //L频段数字主控机主备
    str.L_data=ui->comboBox_0x72_3->currentIndex()+1;
    //L频段定时波控机主备
    str.L_time=ui->comboBox_0x72_4->currentIndex()+1;
    //SXKu波束控制机主备
    str.sxku_bs=ui->comboBox_0x72_5->currentIndex()+1;
    //设备选择2
    uchar b1=2,b2=2;
    if(ui->checkBox_0x72_6bit2_3->isChecked())b1=1;
    if(ui->checkBox_0x72_6bit0_1->isChecked())b2=1;
    str.devchoose2 = (b1)+(b2<<2);
    //可重构射频前端二本振主备
    str.zb_ebz=ui->comboBox_0x72_7->currentIndex()+1;
    //可重构射频前端高相噪主备
    str.zb_gxz=ui->comboBox_0x72_8->currentIndex()+1;
    // 列表封装
    Pblic_Addorderlist((uchar *)&str, sizeof(str_0x72), "设备主备启动设置");
}





