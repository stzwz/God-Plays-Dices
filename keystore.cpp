#include "keystore.h"
#include "ui_keystore.h"
#include "flatui.h"
#include "settings.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
extern MainWindow *mainWindow;
#include <QDebug>
QString select_row;

Keystore::Keystore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keystore)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("Keystore"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);//去掉最大化、最小化按钮，保留关闭按钮
    this->initForm();
}

Keystore::~Keystore()
{

    delete ui;
}

void Keystore::initForm()
{
    //风格样式
    this->setStyleSheet("*{outline:0px;}QWidget#Keystore{background:#FFFFFF;}");
    FlatUI::setPushButtonQss(ui->btn_01, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_02, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_03, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    //表格
    QStringList headerText;
    headerText<<"NO"<<"Public Key";
    ui->tableWidget->setColumnCount(headerText.count());//根据标题数设置列数
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//选择整行
//    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能单选
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格内容不能编辑
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tableWidget->setAlternatingRowColors(true);//交替行颜色
    ui->tableWidget->verticalHeader()->setVisible(false);//垂直标题
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一列拉伸
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
    ui->tableWidget->setShowGrid(false);//网格线不可见
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{border:none;background-color:rgb(255,255,255);color: black;height: 32px;}");
        ui->tableWidget->setStyleSheet(
            "QTableWidget{border: none;}"
            "QTableWidget::Item{border:0px solid rgb(255,255,255);border-bottom:1px solid rgb(232,232,232);background-color:rgb(255,255,255);color: rgb(89,89,89);}"
            "QTableWidget::Item:selected{background-color:rgb(26,188,156);color: rgb(255,255,255);}"
        );
    ui->tableWidget->setColumnWidth(0, 30);

    QFile keytxt(curPath+"\\publickey.dat");
    keytxt.open(QFile::ReadOnly);
    //    QByteArray allkey = keytxt.readAll();
    int filesize = keytxt.size();
    int keyrow = filesize / 66;
    int keylen = 66;
    char* ch_key = new char[keylen];
    int length = 0;
    for (int row = 0;row<keyrow;row++)
    {
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(row,10),1000);
        item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(row,0,item1);
        length=keytxt.read(ch_key,66);
        QString str_key=QString::fromLocal8Bit(ch_key,66);
        QTableWidgetItem *key = new QTableWidgetItem(str_key);
        key->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->tableWidget->setItem(row,1,key);
        qDebug()<<str_key;
    }
    keytxt.close();


    connect(ui->btn_01, &QPushButton::clicked, this, &Keystore::btn_add);
    connect(ui->btn_03, &QPushButton::clicked, this, &Keystore::btn_select);
    connect(ui->btn_02, &QPushButton::clicked, this, &Keystore::btn_delete);
}



void Keystore::btn_add()
{
    connect(&global_port,&QSerialPort::readyRead,this,&Keystore::receive_data);
    QTableWidgetItem *item1;
    //获取当前所在行数
    row = ui->tableWidget->rowCount();
    if(row < 128)
    {
        ui->tableWidget->insertRow(row);
        item1 = new QTableWidgetItem(QString::number(row,10),1000);
        item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(row,0,item1);

    }
    QByteArray send_NK;
    send_NK.resize(3);
    send_NK[0]= 0x4E;//N
    send_NK[1]= 0x4B;//K
    send_NK[2]= row;//密钥编号
    global_port.write(send_NK);
}

void Keystore::btn_select()
{
    QString str;
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if(!items.empty()){
//         int count = items.count();
         QTableWidgetItem *item = items.at(1);
         QTableWidgetItem *item0 = items.at(0);
         str= item->text();
         select_row=item0->text();
     }
    mainWindow->ui->lineEdit_1->setText(str);
    this->close();
}

void Keystore::receive_data()
{
    QByteArray arr;
    arr.append(global_port.readAll());
    QString str =QString(arr.toHex().toUpper());
    QTableWidgetItem *key = new QTableWidgetItem(str);
    key->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->tableWidget->setItem(row,1,key);

    QFile keytxt(curPath+"\\publickey.dat");
    keytxt.open(QFile::WriteOnly|QFile::Append);
    keytxt.write(str.toLatin1());
    keytxt.close();
    arr.clear();
    disconnect(&global_port,0,0,0);
    qDebug()<<str;
    return;
}
void Keystore::btn_delete()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if(!items.empty()){
         QTableWidgetItem *item0 = items.at(0);
         select_row=item0->text();
     }

    QByteArray DK;
    DK.resize(3);
    DK[0]= 0x44;//D
    DK[1]= 0x4B;//K
    DK[2]= select_row.toInt();//密钥编号

    global_port.write(DK);
    connect(&global_port,&QSerialPort::readyRead,this,&Keystore::replace_key);
}
void Keystore::replace_key()
{
    QByteArray arr;
    arr.append(global_port.readAll());
    if(arr.size()==1)
    {
        int_arr=QString(arr.toHex()).toInt();
        qDebug()<<arr<<int_arr<<select_row;
        if(int_arr==select_row.toInt())
        {
            QByteArray send_NK;
            send_NK.resize(3);
            send_NK[0]= 0x4E;//N
            send_NK[1]= 0x4B;//K
            send_NK[2]= int_arr;//密钥编号
            global_port.write(send_NK);
            qDebug()<<send_NK;
            arr.clear();
        }
    }
    else{
        QString str =QString(arr.toHex().toUpper());
        QTableWidgetItem *key = new QTableWidgetItem(str);
        key->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->tableWidget->setItem(int_arr,1,key);
        QFile keytxt(curPath+"\\publickey.dat");
        keytxt.open(QFile::ReadOnly);
        QString str_key=keytxt.readAll();
        str_key.replace(66*(int_arr),66,str);
        keytxt.close();
        keytxt.open(QFile::WriteOnly);
        keytxt.write(str_key.toLatin1());
        keytxt.close();
        qDebug()<<str;
        arr.clear();
        disconnect(&global_port,0,0,0);
    }
}

//void Keystore::tableWidget_clicked(int row, int column)
//{
//    //判断选择状态
//    if(column == 1){
//        if(ui->tableWidget->item(row,1)->checkState() == Qt::Checked)
//        {
//            //设置选择状态
//            ui->tableWidget->item(row,1)->setCheckState(Qt::Unchecked);
//        }else{
//            ui->tableWidget->item(row,1)->setCheckState(Qt::Checked);
//        }

//    qDebug()<<row<<column;
//}
