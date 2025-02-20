#include "m_games.h"
#include "ui_m_games.h"
#include <QMessageBox>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
m_games::m_games(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::m_games)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭，子窗口也关闭设置


    //QString str=QDir::currentPath();//当前工作目录（.pro不包含debug，快捷方式包含debug）
    QString str=QCoreApplication::applicationDirPath();//获取程序所在路径(debug目录下)
    //QString str2=qApp->applicationFilePath();//获取程序所在完整路径（包含exe）
    //QString str3="../";//当前程序上级目录

    QDir dirn(str);
    dirn.cdUp();//返回上一级目录
    Open_path=dirn.absolutePath();//debug上一级目录
    str=Open_path+"/Games";
    QDir dir(str);
    if(dir.exists())//当前目录下
    {
        m_Files=dir.entryList(QDir::Dirs);
        m_Files.removeOne(".");
        m_Files.removeOne("..");
        for (int i=0;i<m_Files.size();i++) {
            ui->listWidget_Gamelist->addItem(m_Files.at(i));
        }
    }
    else {//C盘目录下
        Open_path="C:";
        str=Open_path+"/Games";
        QDir dir2(str);
        if(dir2.exists())
        {
            m_Files=dir2.entryList(QDir::Dirs);
            m_Files.removeOne(".");
            m_Files.removeOne("..");
            for (int i=0;i<m_Files.size();i++) {
                ui->listWidget_Gamelist->addItem(m_Files.at(i));
            }
        }
    }

    ui->listWidget_Gamelist->setVisible(false);
}

m_games::~m_games()
{

    delete ui;
}

//扫雷
void m_games::on_pBGame1_saolei_clicked()
{
    QStringList depend_list;

    depend_list.append(Open_path+"/Games/01Minesweeper/Minesweeper.exe");
    //depend_list.append(QDir::currentPath()+"/Games/Minesweeper/Minesweeper.exe");//.pro启动
    //depend_list.append("../Games/Minesweeper/Minesweeper.exe");

    //QString tm=".\\Games\\Minesweeper\\Minesweeper.exe";
    QProcess::startDetached(depend_list.at(0));//,depend_list);

    emit Show_ViewClose();
}
//显示更多
void m_games::on_radioButton_More_clicked(bool checked)
{
    if(checked)
    {
        QMessageBox::StandardButton result=QMessageBox::information(this,"提示","1+1=2",QMessageBox::Yes|QMessageBox::No);
        switch (result) {
        case QMessageBox::Yes:

             QMessageBox::information(this,"提示","恭喜你答对了!");
             ui->radioButton_More->setChecked(0);
            break;
        case QMessageBox::No:
             ui->listWidget_Gamelist->setVisible(true);
            break;
        default:
            break;
        }

    }
    else
    {
        ui->listWidget_Gamelist->setVisible(false);
    }

}




void m_games::on_listWidget_Gamelist_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    int row=ui->listWidget_Gamelist->currentRow();
    QString strgame=Open_path+"/Games/"+m_Files.at(row)+"/";
    //QString strgame=QDir::currentPath()+"/Games/"+m_Files.at(row)+"/";//.pro路径
    //QString strgame="../Games/"+m_Files.at(row)+"/";
    QProcess p(NULL);
    switch (row) {
    case 0://01扫雷
        strgame+="Minesweeper.exe";
        QProcess::startDetached(strgame);
        break;
    case 1://02仓鼠球中文版（可以全屏）有些软件会崩溃，所有打开bat
        strgame+="开始游戏.bat";
        p.setWorkingDirectory(Open_path+"/Games/"+m_Files.at(row));
        p.start(strgame);
        p.waitForFinished();
        break;
    case 2://03斗地主单机版（可以全屏）
        strgame+="DJLand.exe";
        QProcess::startDetached(strgame);
        break;
    case 3://04愤怒的小鸟（可以全屏）
        strgame+="AngryBirds.exe";
        QProcess::startDetached(strgame);
        break;
    case 4://05雷电3（不可全屏）
        strgame+="00开始游戏.bat";
        p.setWorkingDirectory(Open_path+"/Games/"+m_Files.at(row));
        p.start(strgame);
        p.waitForFinished();
        break;
    case 5://06连连看4（不可全屏）
        strgame+="zzllk.exe";
        QProcess::startDetached(strgame);
        break;
    case 6://07麻将明星三缺一2013版（可以全屏）
        strgame+="开始游戏.bat";
        p.setWorkingDirectory(Open_path+"/Games/"+m_Files.at(row));
        p.start(strgame);
        p.waitForFinished();
        break;
    case 7://08五子棋单机版（不可全屏）
        strgame+="GOMOKU.EXE";
        QProcess::startDetached(strgame);
        break;
    case 8://09象棋单机版（不可全屏）
        strgame+="zgxqdz.exe";
        QProcess::startDetached(strgame);
        break;
    case 9://10象棋单机版2（不可全屏）
        strgame+="CCHESS.exe";
        QProcess::startDetached(strgame);
        break;
    case 10://11植物大战僵尸（可以全屏）
        strgame+="开始游戏.bat";
        p.setWorkingDirectory(Open_path+"/Games/"+m_Files.at(row));
        p.start(strgame);
        p.waitForFinished();
        break;
    case 11://12 四川麻将之血战到底（不可全屏）
        strgame+="scmj.exe";
        QProcess::startDetached(strgame);
        break;
    default:
        break;
    }
    //QProcess::startDetached(strgame);//,depend_list);

    emit Show_ViewClose();
    ui->radioButton_More->setChecked(0);//查看按钮
    ui->listWidget_Gamelist->setVisible(false);//游戏列表
}





