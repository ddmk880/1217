#include "sub1553_gksxkucontrol.h"

#include "ui_sub1553_gksxkucontrol.h"

sub1553_gksxkucontrol::sub1553_gksxkucontrol(QWidget *parent)
    : QWidget(parent), ui(new Ui::sub1553_gksxkucontrol) {
    ui->setupUi(this);
}

sub1553_gksxkucontrol::~sub1553_gksxkucontrol() { delete ui; }

void sub1553_gksxkucontrol::Pblic_Addorderlist(uchar *databuff, int buffLen,QString buffname) {
    // 列表封装
    Order_List_Object order_data;
    order_data.mode = false;
    order_data.page_id = 8;
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

//qstring转16进制uint
uint sub1553_gksxkucontrol::toHex_uint(QString qstr)
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

// SXKu频段射频收发开关控制 0x50
void sub1553_gksxkucontrol::on_pB_sxkuspon_off_clicked() {
    Str_spsf str;
    memset(&str,0,sizeof (str));
    str.order_mark=0x50;

    uchar tmp=0;
    switch (ui->comboBox_0x51_1->currentIndex()) {
    case 0:
        tmp=0x1B;
        break;
    case 1:
        tmp=0x2D;
        break;
    case 2:
        tmp=0x36;
        break;
    default:
        break;
    }
    str.switch_cotrl=tmp;
    // 列表封装
    Pblic_Addorderlist((uchar *)&str, sizeof(str), "SXKu频段射频收发开关控制:"+ui->comboBox_0x51_1->currentText());
}

//RS422线路控制选择指令0x51
void sub1553_gksxkucontrol::on_pB_RS422_choose_clicked() {

    Str_RS422oeder str;
    memset(&str,0,sizeof (str));
    str.order_mark=0x51;
    str.cotrl= ui->cB_rs422gsl->currentIndex();
    // 列表封装
    Pblic_Addorderlist((uchar *)&str, sizeof(str), "SXKuRS422线路控制选择:"+ui->cB_rs422gsl->currentText());
}

// SXKu频段FLASH编码读0x52
void sub1553_gksxkucontrol::on_pB_flashRead_clicked() {
    Str_flashRead str;
    memset(&str,0,sizeof (str));
    str.order_mark = 0x52;
    //地址
    QString S_sorftnum = ui->lineEdit_c56_addr->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    QByteArray hex_data = QByteArray::fromHex(
                S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    int strlen = (S_sorftnum.size() + 1) / 2;
    if (strlen > 3) strlen = 3;
    memcpy(str.flashaddr, (uchar *)hex_data.data(), strlen);  // 获取地址
    // 列表封装
    Pblic_Addorderlist((uchar *)&str, sizeof(str), "SXKu频段FLASH编码读");
}

// SXKu频段FLASH编码写0x53
void sub1553_gksxkucontrol::on_pB_flashWrite_clicked() {
    Str_flashWrite flashsrt;
    memset(&flashsrt, 0, sizeof(flashsrt));
    // 指令标识
    flashsrt.ordermark = 0x53;
    // flash起始地址
    QString S_sorftnum = ui->lineEdit_flashaddr->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    QByteArray hex_data = QByteArray::fromHex(
                S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    int strlen = (S_sorftnum.size() + 1) / 2;
    if (strlen > 3) strlen = 3;
    memcpy(flashsrt.flashaddr, (uchar *)hex_data.data(), strlen);  // 获取地址
    // 保留
    memset(flashsrt.bl,0xFF,sizeof (flashsrt.bl));
    // flash内容（低前高后）
    S_sorftnum = ui->lineEdit_flashin->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    S_sorftnum = S_sorftnum.replace(" ", "");
    S_sorftnum = S_sorftnum.replace("\n", "");
    hex_data = QByteArray::fromHex(S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    int tmp=S_sorftnum.size();
    strlen = (tmp + 1) / 2;
    if(strlen>240)strlen=240;
    memcpy(flashsrt.flashin, (uchar *)hex_data.data(), strlen);  // 获取地址

    // 列表封装
    Pblic_Addorderlist((uchar *)&flashsrt, sizeof(flashsrt),"SXKu频段FLASH编码写");
}


// SXKu阵面解锁0x55
void sub1553_gksxkucontrol::on_pB_flashzjRead_clicked() {
    uchar arr[2] = {0};
    arr[0] = 0x55;
    arr[1] = 0x31;
    // 列表封装
    Pblic_Addorderlist((uchar *)&arr, sizeof(arr), "SXKu频段阵面解锁");
}
// SXKu频段FLASH擦除0x56
void sub1553_gksxkucontrol::on_pB_flash_clear_clicked() {
    uchar arr[4] = {0};
    arr[0] = 0x56;
    // flash起始地址
    QString S_sorftnum = ui->lineEdit_flashstart->text();
    S_sorftnum = S_sorftnum.replace("0x", "");
    QByteArray hex_data = QByteArray::fromHex(
                S_sorftnum.toLatin1());  // 将字节流转换位16进制,char型
    int strlen = (S_sorftnum.size() + 1) / 2;
    if (strlen > 3) strlen = 3;
    memcpy(&arr[1], (uchar *)hex_data.data(), strlen);  // 获取地址
    // 列表封装
    Pblic_Addorderlist((uchar *)&arr, sizeof(arr), "SXKu频段FLASH擦除");
}

//子阵选择控制0x57
void sub1553_gksxkucontrol::on_pB_unity_T_R_clicked() {
    uchar arr[2] = {0};
    arr[0] = 0x57;
    arr[1] = ui->checkBox_trbit0->isChecked() +
            (ui->checkBox_trbit1->isChecked() << 1) +
            (ui->checkBox_trbit2->isChecked() << 2) +
            (ui->checkBox_trbit3->isChecked() << 3);
    // 列表封装
    Pblic_Addorderlist((uchar *)&arr, sizeof(arr), "子阵选择控制");
}
