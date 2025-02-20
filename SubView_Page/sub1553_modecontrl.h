#ifndef SUB1553_MODECONTRL_H
#define SUB1553_MODECONTRL_H

#include <QWidget>
#include "Globel_Define.h"
#include <QFile>
#include <QFileInfo>
namespace Ui {
class sub1553_modecontrl;
}

class sub1553_modecontrl : public QWidget
{
    Q_OBJECT

public:
    explicit sub1553_modecontrl(QWidget *parent = nullptr);
    ~sub1553_modecontrl();
    void Rec_MemoryData(int ch,ushort* buff,int len);//接收内存下卸数据
    QFile* ncRe_Pfile[4];//4个通道文件
    QString Tmpstr[4];
signals:
 void Add_Order_ToList(QVariant varData);

private slots:
 void on_pB_MemoryDown_clicked();

 void on_pushButton_RePath_clicked();

 void on_pushButton_stopRec_clicked();

private:
    Ui::sub1553_modecontrl *ui;


};

#endif // SUB1553_MODECONTRL_H
