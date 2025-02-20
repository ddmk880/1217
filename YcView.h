#ifndef YCVIEW_H
#define YCVIEW_H
#include <QStandardItemModel>
#include <QTreeWidget>
#include <QWidget>

#include "Globel_Define.h"
#include "SubView_Page/subyc_slowspeed.h"
#include "SubView_Page/subyc_packspeed.h"
#include "SubView_Page/subyc_canc81.h"
#include "SubView_Page/subyc_ad.h"
#include "SubView_Page/subrs422_rec.h"

namespace Ui {
class YcView;
}

class YcView : public QWidget
{
    Q_OBJECT

public:
    explicit YcView(QWidget *parent = nullptr);
    ~YcView();
    void Init_View_Sub();//初始化子界面
    subyc_slowspeed*    yc_slowspeed;  //慢速遥测
    subyc_packspeed*    yc_packspeed;  //打包遥测
    subyc_canC81*       yc_canc81;  //can遥测
    subyc_AD*           yc_ad;      //ad遥测
    subrs422_Rec*       yc_rs422_rec;      //rs422电平接收
    void Hide_view();
    void Show_view(int index);//显示界面
private slots:
    void on_m_yctree_list_doubleClicked(const QModelIndex &index);

    void on_radioButton_dj1YC_clicked(bool checked);

    void on_radioButton_dj2YC_clicked(bool checked);

    void on_radioButton_dj3YC_clicked(bool checked);

    void on_radioButton_dj4YC_clicked(bool checked);


private:
    Ui::YcView *ui;
    QStandardItemModel *model_tree_list;





};

#endif // YCVIEW_H
