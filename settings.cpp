#include "settings.h"
#include "ui_settings.h"
#include "flatui.h"
#include "mainwindow.h"
#include <QFile>
#include <QMessageBox>
QSerialPort global_port;//端口函数
Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("Settings"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);//去掉最大化、最小化按钮，保留关闭按钮
    this->initForm();
}

Settings::~Settings()
{
    delete ui;
}
void Settings::initForm()
{
    ui->com_1->clear();//清空当前列表

    //检索端口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->com_1->addItem(info.portName());

    }

    //串口8,n,1
    global_port.setDataBits(QSerialPort::Data8);
    global_port.setParity(QSerialPort::NoParity);
    global_port.setStopBits(QSerialPort::OneStop);
    global_port.setBaudRate(460800);//设置波特率460800
    connect(ui->btn_2,&QPushButton::clicked,this,&Settings::btn_openport);
    if(global_port.isOpen())
    {
        ui->btn_2->setText("Close port");
    }

    //加载样式表
    QFile file(":/qss/flatgray.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
void Settings::btn_openport()
{
    if(ui->btn_2->text() == "Open port")
    {
        global_port.setPortName(ui->com_1->currentText());//设置端口号
        port=ui->com_1->currentText();
        index = ui->com_1->currentIndex();
        qDebug()<<port;
        if(global_port.open(QIODevice::ReadWrite))
        {
            ui->btn_2->setText("Close port");
        }else
        {
            QMessageBox::critical(this, "information", "Failed to open");
            return;
        }
    }else
    {
        ui->btn_2->setText("Open port");
        global_port.close();
    }
}
