#ifndef YXQ_CONTRL_H
#define YXQ_CONTRL_H

#include <QWidget>
//#include "iBHDataAdapter.h"

namespace Ui {
class yxq_contrl;
}

class yxq_contrl : public QWidget
{
    Q_OBJECT

public:
    explicit yxq_contrl(QWidget *parent = nullptr);
    ~yxq_contrl();

private slots:
    void on_pushButto_cont_clicked();

private:
    Ui::yxq_contrl *ui;
};

#endif // YXQ_CONTRL_H
