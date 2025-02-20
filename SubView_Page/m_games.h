#ifndef M_GAMES_H
#define M_GAMES_H

#include <QWidget>
#include <QListWidgetItem>
#include "Globel_Define.h"
namespace Ui {
class m_games;
}

class m_games : public QWidget
{
    Q_OBJECT

public:
    explicit m_games(QWidget *parent = nullptr);
    ~m_games();
    QStringList m_Files;
    QString Open_path;//Game所在的文件路径
signals:
    void Show_ViewClose();

private slots:
    void on_pBGame1_saolei_clicked();

    void on_radioButton_More_clicked(bool checked);


    void on_listWidget_Gamelist_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::m_games *ui;
};

#endif // M_GAMES_H
