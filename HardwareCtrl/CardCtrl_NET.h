#ifndef CARDCTRL_NET_H
#define CARDCTRL_NET_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "include/PA_PCIe_1501.h"
class CardCtrl_NET : public QObject
{
    Q_OBJECT
public:
    explicit CardCtrl_NET(QObject *parent = nullptr);
    ~CardCtrl_NET();
    int Init_Net();//demo函数
    int Init_MainNet();
signals:
    void sendPath(QString path);

};

class Rec_QThread1 : public QObject
{
    Q_OBJECT
public:
    explicit Rec_QThread1(QObject *parent = nullptr);

    int Rec_working1(QString path);
signals:

};


class Rec_QThread2 : public QObject
{
    Q_OBJECT
public:
    explicit Rec_QThread2(QObject *parent = nullptr);

    int Rec_working2(QString path);
signals:

};


class Rec_QThread3 : public QObject
{
    Q_OBJECT
public:
    explicit Rec_QThread3(QObject *parent = nullptr);

    int Rec_working3(QString path);
signals:

};


class Rec_QThread4 : public QObject
{
    Q_OBJECT
public:
    explicit Rec_QThread4(QObject *parent = nullptr);

    int Rec_working4(QString path);
signals:

};



#endif // CARDCTRL_NET_H
