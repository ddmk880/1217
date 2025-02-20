#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class mylabel : public QLabel
{
    Q_OBJECT
public:
    mylabel(QWidget *parent);
signals:
    void pressClicked();
    void pressClicked_right();

protected:
    virtual void mousePressEvent(QMouseEvent *ev) override;
};

#endif // MYLABEL_H
