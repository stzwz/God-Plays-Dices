#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include <QImage>
#include <QFileInfo>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    /////////////
    void system_init();//系统初始化函数
    void sendcmd(int cmd_len, int recv_len);
    QString curPath = QDir::currentPath();  //系统当前目录

    char cmd[256];
    char recv_data[2048];
    QByteArray arr;
    QByteArray rec;
    char pass=0x01;

private slots:
    void OpenWeb1();
    void OpenWeb2();
    void OpenWeb3();
    void OpenWeb4();
    void btn_OpenImage();
    void btn_KeyStore();
    void btn_Settings();
    void btn_Verify();
    void btn_Random();




};
#endif // MAINWINDOW_H
