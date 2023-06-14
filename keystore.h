#ifndef KEYSTORE_H
#define KEYSTORE_H

#include <QWidget>
#include "mainwindow.h"

extern QString select_row;
namespace Ui {
class Keystore;
}

class Keystore : public QWidget
{
    Q_OBJECT

public:
    explicit Keystore(QWidget *parent = nullptr);
    ~Keystore();


private:
    Ui::Keystore *ui;
    int row;
    int int_arr;
    QString str_arr;
    QString curPath = QDir::currentPath();  //系统当前目录


private slots:
    void initForm();
//    void tableWidget_clicked(int row, int column);
    void btn_add();
    void btn_select();
    void receive_data();//接收数据槽函数
    void btn_delete();
    void replace_key();
};

#endif // KEYSTORE_H
