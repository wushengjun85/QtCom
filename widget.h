#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "posix_qextserialport.h"
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;

    Posix_QextSerialPort *myCom;    //串口
    QTimer *readTimer;    //定时器

private slots:
//    void on_pushButton_clicked(); //“发送数据”按钮 槽函数
    void readMyCom(); //读取串口 槽函数

    void on_pushButton_clicked();
};

#endif // WIDGET_H
