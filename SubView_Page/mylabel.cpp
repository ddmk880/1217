#include "mylabel.h"

mylabel::mylabel(QWidget* parent):QLabel(parent)
{

}

void mylabel::mousePressEvent(QMouseEvent *ev)
{
    //鼠标右键
    if(ev->button()==Qt::RightButton)
    {
        emit pressClicked_right();
    }
    if(ev->button()==Qt::LeftButton)
    {
        emit pressClicked();
    }
    else
    {}
}


