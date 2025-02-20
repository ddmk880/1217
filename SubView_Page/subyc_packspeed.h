#ifndef SUBYC_PACKSPEED_H
#define SUBYC_PACKSPEED_H

#include <QWidget>
#include <QStandardItemModel>
namespace Ui {
class subyc_packspeed;
}

class subyc_packspeed : public QWidget
{
    Q_OBJECT

public:
    explicit subyc_packspeed(QWidget *parent = nullptr);
    ~subyc_packspeed();
    QStandardItemModel* model;
    int Outpack_dj;//输出哪个地检打包遥测

public slots:
 void Get_PackYcData(ushort* Rxbuff, int Rxlen,int ch);
private slots:
 void on_pushButton_clearlist_clicked();

private:
    Ui::subyc_packspeed *ui;
};

#endif // SUBYC_PACKSPEED_H
