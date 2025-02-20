#ifndef subboard_rt_H
#define subboard_rt_H

#include <QWidget>

namespace Ui {
class subboard_rt;
}

class subboard_rt : public QWidget
{
    Q_OBJECT

public:
    explicit subboard_rt(QWidget *parent = nullptr);
    ~subboard_rt();

private slots:
    void on_pB_GNSS_position_clicked();

    void on_pB_GNSS_track_clicked();

private:
    Ui::subboard_rt *ui;
};

#endif // subboard_rt_H
