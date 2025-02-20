#ifndef SUBBOARD_BC_H
#define SUBBOARD_BC_H

#include <QWidget>

namespace Ui {
class subboard_bc;
}

class subboard_bc : public QWidget
{
    Q_OBJECT

public:
    explicit subboard_bc(QWidget *parent = nullptr);
    ~subboard_bc();

private:
    Ui::subboard_bc *ui;
};

#endif // SUBBOARD_BC_H
