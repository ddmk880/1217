#ifndef SIGNAL_1466_H
#define SIGNAL_1466_H

#include <QWidget>
#include <Globel_Define.h>
#include "CN_SignalContrl.h"
#include"xlsxdocument.h"

using namespace QXlsx;

namespace Ui {
class signal_1466;
}

class signal_1466 : public QWidget
{
    Q_OBJECT

public:
    explicit signal_1466(QWidget *parent = nullptr);
    ~signal_1466();
    CN_SignalContrl* signalConrtl;
    void Get_TcpMess(QString str);//tcp接收数据显示


signals:
    void Add_Order_ToList(QVariant varData);
    void success_snack(QString str);
    void fail_snack(QString str);

private slots:
    void on_pB_IPConnet_clicked();

    void on_pB_disconnect_clicked();

    void on_pB_send_clicked();

    void on_pB_readXlsx_clicked();

private:
    Ui::signal_1466 *ui;
};

#endif // SIGNAL_1466_H
