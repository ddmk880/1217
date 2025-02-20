#ifndef DATABASEVIEW_H
#define DATABASEVIEW_H

#include <QWidget>
#include <QSqlError>
#include <QSqlDatabase>//建立数据库连接类
#include <QSqlQuery>//访问数据库类
#include <QSqlQueryModel>
#include"xlsxdocument.h"

namespace Ui {
class DatabaseView;
}

class DatabaseView : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseView(QWidget *parent = nullptr);
    ~DatabaseView();
    void connectDB();//连接数据库
    void queryDB();//访问数据库
    void connectView();//绑定界面控件
    void check_DB(int n,QString stro);//查询数据库
    void check_DB_add(int n,QString stro);//查询附加数据库
    void STRcontrol_DB();  //控制数据库查询
    QString selcet_Time(QString tmS,QString tmE);//时间筛选查询

    QSqlDatabase mydb;//数据库对象
    QSqlQueryModel* viewMode;

private slots:
    void on_pB_addData_clicked();

    void on_cB_tableKind_activated(int index);

    void on_pushButton_outExcel_clicked();

    void on_pB_freshenDB_clicked();

    void on_dateTimeEdit_endTime_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_startTime_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_OpenNewDB_clicked();

    void on_checkBox_addDB_clicked(bool checked);

private:
    Ui::DatabaseView *ui;
};

#endif // DATABASEVIEW_H
