#ifndef SUBRS422_REC_H
#define SUBRS422_REC_H

#include <QWidget>
#include <QVector>
#include<QTimer>
#include "qcustomplot.h"
#include"include/rs422.h"
namespace Ui {
class subrs422_Rec;
}

class subrs422_Rec : public QWidget
{
    Q_OBJECT

public:
    explicit subrs422_Rec(QWidget *parent = nullptr);
    ~subrs422_Rec();
    void Init_Plot();//初始化
    QTimer* Timer_Re;
    uchar Arr_inch[4];
    QCustomPlot* qc_Widget[4];
    QVector<double> Vplot_x[4],Vplot_y[4];//秒级容器
    QVector<double> Vplot_x_MS[4],Vplot_y_MS[4];//微秒级容器
public slots:
    void time_Active();
private slots:
    void on_checkBox_read422Pluse_clicked(bool checked);

    void on_checkBox_read422Pluse_US_clicked(bool checked);

private:
    Ui::subrs422_Rec *ui;
};

#endif // SUBRS422_REC_H
