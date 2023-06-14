#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include "flatui.h"
#include "keystore.h"
#include "settings.h"
#include "sha256.h"
#include <QDebug>
MainWindow *mainWindow;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainWindow =this;
    //this->setWindowIcon(QIcon(":/system.ico"));
    this->setWindowTitle(QStringLiteral("ArtBox"));
//    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);//去掉最大化按钮，保留关闭、最小化按钮
    system_init();//系统初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::system_init()
{
    //链接槽函数
    connect(ui->btn_01,&QPushButton::clicked,this,&MainWindow::btn_KeyStore);
    connect(ui->btn_15,&QPushButton::clicked,this,&MainWindow::btn_Settings);
    connect(ui->btn_02,&QPushButton::clicked,this,&MainWindow::btn_OpenImage);
    connect(ui->btn_03,&QPushButton::clicked,this,&MainWindow::btn_Verify);
    connect(ui->btn_04,&QPushButton::clicked,this,&MainWindow::btn_Random);
    connect(ui->btn_11,&QPushButton::clicked,this,&MainWindow::OpenWeb1);
    connect(ui->btn_12,&QPushButton::clicked,this,&MainWindow::OpenWeb2);
    connect(ui->btn_13,&QPushButton::clicked,this,&MainWindow::OpenWeb3);
    connect(ui->btn_14,&QPushButton::clicked,this,&MainWindow::OpenWeb4);

    //风格样式
    this->setStyleSheet("*{outline:0px;}QWidget#MainWindow{background:#FFFFFF;}");
    FlatUI::setPushButtonQss(ui->btn_01, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_02, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_03, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_04, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_11, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_12, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_13, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_14, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_15, 5, 8, "#046DC8", "#FFFFFF", "#00aaff", "#FFFFFF", "#163ba0", "#FFFFFF");
    FlatUI::setPushButtonQss(ui->btn_16, 5, 8, "#046DC8", "#FFFFFF", "#00aaff", "#FFFFFF", "#163ba0", "#FFFFFF");
    FlatUI::setLineEditQss(ui->lineEdit_1, 5, 2, "#DCE4EC", "#1ABC9C");
    FlatUI::setLineEditQss(ui->lineEdit_2, 5, 2, "#DCE4EC", "#1ABC9C");
    FlatUI::setLineEditQss(ui->lineEdit_3, 5, 2, "#DCE4EC", "#1ABC9C");
    ui->label_image->setStyleSheet("QLabel{border:2px solid #DCE4EC;border-radius:5px}");
    ui->label_image->setScaledContents(true);
//    ui->label_image->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

}
void MainWindow::btn_OpenImage()
{
    QImage Image;
    QString OpenImage =  QFileDialog::getOpenFileName(this,"选择待签名文件","","All Files (*.*)");

    QFileInfo OpenImageInfo= QFileInfo(OpenImage);
    QString OpenImagePath= OpenImageInfo.filePath();
    QString OpenImageName= OpenImageInfo.fileName();
    QString OpenImageSuffix= OpenImageInfo.suffix();
    if (OpenImage != "")
    {
        if(OpenImageSuffix=="jpg"  || OpenImageSuffix=="jpeg"  || OpenImageSuffix=="png")
        {
            if (Image.load(OpenImage))
            {
                //仅仅只是导入之后的图片仍然是原来的大小，这个时候我们需要缩放
                ui->label_image->setPixmap(QPixmap::fromImage(Image).scaled(ui->label_image->size()));
            }
        }else
        {
            ui->label_image->setText(OpenImageName);
        }
    }
    QString SavePath= OpenImagePath.left(OpenImagePath.length() - OpenImageSuffix.length() - 1) + "-sig." + OpenImageSuffix;
    QFile imageFile(OpenImagePath);
    imageFile.open(QFile::ReadOnly);

    uint len = (uint)imageFile.size();
    char* buf = new char[len + 100];
    imageFile.read(buf,len);

    QString tm = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    ui->label_6->setText("Signed time：："+tm);
    qDebug()<<tm;
    memcpy(buf + len,tm.toLatin1(),14);
    uint8_t hash[32];
    sha256(buf, len + 14, hash);

    //    cmd[0] = 0x53;
    //    cmd[1] = 0x48;
    memcpy(cmd , hash, 32);
    //        sendcmd(32, 64);

    QByteArray filehash = QByteArray(cmd,32);
    QByteArray SH;
    SH.resize(3);
    SH[0]= 0x53;//N
    SH[1]= 0x48;//K
    SH[2]= select_row.toInt();//密钥编号

    global_port.write(SH+filehash);
    //    global_port.write(cmd);
    qDebug()<<filehash.toHex();
    QFile datFile(SavePath);
    datFile.open(QFile::WriteOnly);
    datFile.write(buf, len + 14);
    datFile.close();
    connect(&global_port,&QSerialPort::readyRead,this,[=](){

        arr.append(global_port.readAll());
        QString str =QString(arr.toHex().toUpper());
        memcpy(recv_data,arr,64);
        rec = QByteArray(recv_data,64).toHex().toUpper();
        ui->lineEdit_2->setText(rec);
        qDebug()<<rec;


        QFile datFile(SavePath);
        datFile.open(QFile::WriteOnly|QIODevice::Append);
        datFile.write(arr);
        datFile.close();

        arr.clear();
        disconnect(&global_port,0,0,0);
    });
    delete[] buf;

}

void MainWindow::btn_Verify()
{
    QString OpenFile =  QFileDialog::getOpenFileName(this,"选择签名数据包文件","","签名数据包文件(*-sig.*)");
    QFileInfo OpenFileInfo= QFileInfo(OpenFile);
    QString OpenFilePath= OpenFileInfo.filePath();
    QString OpenFileName= OpenFileInfo.fileName();
    QString OpenFileSuffix= OpenFileInfo.suffix();
    QFile sigFile(OpenFilePath);
    sigFile.open(QFile::ReadOnly);
    uint len = (uint)sigFile.size();
    char* buf = new char[len + 100];
    sigFile.read(buf, len);

    QImage Image;
    if (OpenFile != "")
    {
        if(OpenFileSuffix=="jpg"  || OpenFileSuffix=="jpeg"  || OpenFileSuffix=="png")
        {
            if (Image.load(OpenFile))
            {
                //仅仅只是导入之后的图片仍然是原来的大小，这个时候我们需要缩放
                ui->label_image->setPixmap(QPixmap::fromImage(Image.scaled(ui->label_image->size())));
            }
        }else
        {
            ui->label_image->setText(OpenFileName);
        }
    }
    QString str_key=ui->lineEdit_1->text();
    QByteArray key = QByteArray::fromHex(str_key.toLatin1());

    uint8_t hash[32];
    sha256(buf, len - 64, hash);
    //    cmd[0] = 0x56;
    //    cmd[1] = 0x53;
    memcpy(cmd , key, 33);
    memcpy(cmd + 33, buf +len - 64, 64);
    memcpy(cmd + 97, hash, 32);
    QByteArray filevs = QByteArray(cmd,129);
    QByteArray signature = QByteArray(cmd+33,64);
    QString sig = QString(signature.toHex().toUpper());
    ui->lineEdit_2->setText(sig);

    char tm[15];
    memcpy(tm, buf + len - 78, 14);
    for (int i = 0; i < 14; i++) {
        if (tm[i] > '9' || tm[i] < '0') {
            tm[i] = '0';
        }
    }
    tm[14] = '\0';
    QByteArray arr_tm = QByteArray(tm,14);
    QString str_tm = QString("Signed time："+arr_tm);
    ui->label_6->setText(str_tm);

    QByteArray VS;
    VS.resize(2);
    VS[0]= 0x56;//V
    VS[1]= 0x53;//S
    qDebug()<<filevs.toHex()<<sig<<str_tm;

    //    str_key= key.toHex();
    //    key = str_key.toLatin1();
    //    global_port.write(VS+key);
    global_port.write(VS+filevs);
    connect(&global_port,&QSerialPort::readyRead,this,[=](){
        QByteArray arr1;
        arr1.append(global_port.readAll());

        if(arr1[0]==pass)
        {
            ui->label_7->setText("Validation result：Pass");
            qDebug()<<arr1<<"验证通过";
        }else{
            ui->label_7->setText("Validation result：Fail");
            qDebug()<<arr1<<"验证失败";
        }
        arr1.clear();
        disconnect(&global_port,0,0,0);
    });

    //    qDebug()<<filevs;
}

void MainWindow::btn_Random()
{
    QString savepath = QFileDialog::getExistingDirectory(this, "选择保存路径", "./");
    if(savepath.isEmpty())
    {
        savepath = curPath;
    }
    QByteArray OR;
    OR.resize(2);
    OR[0]= 0x4F;//O
    OR[1]= 0x52;//R
    global_port.write(OR);

    connect(&global_port,&QSerialPort::readyRead,this,[=](){
        QByteArray arr;
        arr.append(global_port.readAll());
        QString str =QString(arr.toHex().toUpper());
        QString createTime = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
        QFile randomnumber(savepath+"\\"+"randomnumber"+createTime+".dat");
        randomnumber.open(QFile::WriteOnly|QFile::Append);
        randomnumber.write(str.toLatin1());
        randomnumber.close();
        arr.clear();
        disconnect(&global_port,0,0,0);
    });

}

void MainWindow::btn_KeyStore()
{
    Keystore *keystore=new Keystore;
    keystore->setWindowModality(Qt::ApplicationModal);
    keystore->show();
}
void MainWindow::btn_Settings()
{
    Settings *settings=new Settings;
    settings->setWindowModality(Qt::ApplicationModal);
    settings->show();
}

void MainWindow::OpenWeb1()
{
    QDesktopServices::openUrl(QUrl(QString("https://stablediffusionweb.com")));
}
void MainWindow::OpenWeb2()
{
    QDesktopServices::openUrl(QUrl(QString("https://www.midjourney.com/app/")));
}
void MainWindow::OpenWeb3()
{
    QDesktopServices::openUrl(QUrl(QString("https://openai.com/product/dall-e-2")));
}
void MainWindow::OpenWeb4()
{
    QDesktopServices::openUrl(QUrl(QString("https://frame.infmonkeys.com")));
}

