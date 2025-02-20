#include "subboard_rt.h"
#include "ui_subboard_rt.h"
#include "Globel_Define.h"

subboard_rt::subboard_rt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subboard_rt)
{
    ui->setupUi(this);
}

subboard_rt::~subboard_rt()
{
    delete ui;
}

//GNSS定位
void subboard_rt::on_pB_GNSS_position_clicked()
{
    GNSS_position_data GNSS_position;
    memset(&GNSS_position,0,sizeof (GNSS_position));
    GNSS_position.page_reco=0x0672;
    GNSS_position.page_order_control=0x0003;
    GNSS_position.page_len=0x0039;


}

//GNSS定轨
void subboard_rt::on_pB_GNSS_track_clicked()
{
    Orbit_Determination_data GNSS_track;
    memset(&GNSS_track,0,sizeof (Orbit_Determination_data));

    GNSS_track.page_reco=0x0673;
    GNSS_track.page_order_control=0x0003;
    GNSS_track.page_len=0x0039;

}
















