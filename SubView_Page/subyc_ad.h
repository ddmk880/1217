#ifndef SUBYC_AD_H
#define SUBYC_AD_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class subyc_AD;
}

class subyc_AD : public QWidget
{
    Q_OBJECT

public:
    explicit subyc_AD(QWidget *parent = nullptr);
    ~subyc_AD();
    QStandardItemModel* model;
    double ret_fun124(double a, double b, double k, double c, double N);
    int Outpack_dj;

public slots:
 void Get_ADdata(double* Rxbuff, int Rxlen);

private slots:
 void on_pushButton_ADclear_clicked();

private:
    Ui::subyc_AD *ui;
};

#endif // SUBYC_AD_H
