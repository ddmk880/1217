#ifndef SUB1553_TCMAYRFFRONT_H
#define SUB1553_TCMAYRFFRONT_H

#include <QWidget>
#include <Globel_Define.h>
namespace Ui {
class sub1553_tcmayrffront;
}

class sub1553_tcmayrffront : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_tcmayrffront(QWidget *parent = nullptr);
    ~sub1553_tcmayrffront();
    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);
private slots:
    void on_pB_channel_power_C72_clicked();

    void on_pB_zpchooseSet_C73_clicked();

    void on_pB_channel_control_C74_clicked();

private:
    Ui::sub1553_tcmayrffront *ui;
};

#endif // SUB1553_TCMAYRFFRONT_H
