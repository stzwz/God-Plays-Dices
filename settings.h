#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "mainwindow.h"
#include <QtSerialPort/QtSerialPort>
#include <QSerialPortInfo>

extern QSerialPort global_port;//端口函数
namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
QString port;
int index;
//    QSerialPort global_port;//端口函数

private slots:
    void initForm();
    void btn_openport();
};

#endif // SETTINGS_H
