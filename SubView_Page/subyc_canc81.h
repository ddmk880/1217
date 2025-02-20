#ifndef SUBYC_CANC81_H
#define SUBYC_CANC81_H

#include <QWidget>
#include <QStandardItemModel>
namespace Ui {
class subyc_canC81;
}

class subyc_canC81 : public QWidget
{
    Q_OBJECT

public:
    explicit subyc_canC81(QWidget *parent = nullptr);
    ~subyc_canC81();
    QStandardItemModel* model;
public slots:
 void Get_C81YcData(uchar* Rxbuff, int Rxlen);
private slots:
 void on_pushButton_clearList_clicked();

private:
    Ui::subyc_canC81 *ui;
};

#endif // SUBYC_CANC81_H
