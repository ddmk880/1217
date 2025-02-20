#include "sgnal_1466.h"
#include "ui_sgnal_1466.h"

sgnal_1466::sgnal_1466(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sgnal_1466)
{
    ui->setupUi(this);
}

sgnal_1466::~sgnal_1466()
{
    delete ui;
}
