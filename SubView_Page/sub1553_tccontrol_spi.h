#ifndef SUB1553_TCCONTROL_SPI_H
#define SUB1553_TCCONTROL_SPI_H

#include <QWidget>
#include <Globel_Define.h>
namespace Ui {
class sub1553_tccontrol_spi;
}

class sub1553_tccontrol_spi : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_tccontrol_spi(QWidget *parent = nullptr);
    ~sub1553_tccontrol_spi();

    void Pblic_Addorderlist(uchar* databuff,int buffLen,QString buffname);
signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);

private slots:
    void on_pushButton_Lpd_SendSet_clicked();

    void on_pushButton_sxkuReSet_clicked();

    void on_pushButton_sxkuSendSet_2_clicked();

    void on_pushButton_L_PDnumber_clicked();

    void on_pushButton_sxkuzxkg_clicked();

    void on_pushButton_clicked();

    void on_pushButton_sxku_ankyloko_clicked();

    void on_pushButton_Str_L_recvSet_clicked();

    void on_pB_gsl80_clicked();

    void on_comboBox_bkChoose_activated(int index);

private:
    Ui::sub1553_tccontrol_spi *ui;
};

#endif // SUB1553_TCCONTROL_SPI_H
