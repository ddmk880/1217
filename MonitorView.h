#ifndef MONITOR_H
#define MONITOR_H
#include <QObject>
#include <QWidget>
#include <QSqlTableModel>
#include <QStandardItemModel>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qtimer.h>



//重构类 继承QSqlTableModel
class MySqlTableModel : public QSqlTableModel
{
    int mLimit;
public:
    MySqlTableModel(QObject *parent = 0,  QSqlDatabase *db = new QSqlDatabase());
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
    void MapData(const QModelIndex &index, const QVariant &value,int type);
    void setLimit(int limit)
    {
        if(limit>0)mLimit=limit;
    }
    QMap<QModelIndex,QVariant> textMap;
    QMap<QModelIndex,QVariant> textMap2;
protected:
    QString selectStatement() const override;
};

namespace Ui {
class MonitorView;
}

class MonitorView : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorView(QWidget *parent = nullptr,QSqlDatabase *db = new QSqlDatabase());
    ~MonitorView();
    QTimer* timer;
    QStringList m_name_list;
private slots:
    void on_pushButto_on_clicked();
    void timerUpdate();

    void on_checkBox_stateChanged(int arg1);
private:
    Ui::MonitorView *ui;
    void initDatabase();
    MySqlTableModel *pModel=nullptr;
    QSqlDatabase mDB;
    QSqlDatabase *myDB;
};

#endif // MONITOR_H
