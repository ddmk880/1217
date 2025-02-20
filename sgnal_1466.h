#ifndef SGNAL_1466_H
#define SGNAL_1466_H

#include <QWidget>

namespace Ui {
class sgnal_1466;
}

class sgnal_1466 : public QWidget
{
    Q_OBJECT

public:
    explicit sgnal_1466(QWidget *parent = nullptr);
    ~sgnal_1466();

private:
    Ui::sgnal_1466 *ui;
};

#endif // SGNAL_1466_H
