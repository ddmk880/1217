#ifndef SUB1553_TCCONTROL_L_H
#define SUB1553_TCCONTROL_L_H

#include <QWidget>
#include <Globel_Define.h>
namespace Ui {
class sub1553_tccontrol_L;
}

class sub1553_tccontrol_L : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_tccontrol_L(QWidget *parent = nullptr);
    ~sub1553_tccontrol_L();
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
    ushort toHex_ushort(QString qstr);//qstring转16进制ushort

signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);

private slots:
    void on_pB_indirect_order_clicked();

    void on_pB_Vectorword_clicked();

    void on_pB_busrepos_clicked();

    void on_pB_importdata_clicked();

    void on_pB_taskdata_clicked();

    void on_pB_ycpolling_clicked();

    void on_pB_packyc_clicked();

    void on_pB_memorydown_clicked();

    void on_pB_workstatus_clicked();

    void on_pB_startMemory_clicked();

    void on_pB_stopMemory_clicked();

    void on_pushButton_C03_clicked();

    void on_pB_C03ReadFile_clicked();

private:
    Ui::sub1553_tccontrol_L *ui;
};

#endif // SUB1553_TCCONTROL_L_H
