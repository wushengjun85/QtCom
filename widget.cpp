#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //myCom = new Win_QextSerialPort("COM1",QextSerialBase::EventDriven);
    //【windows下使用】定义串口对象，指定串口名和查询模式，这里使用事件驱动EventDriven
   //// myCom = new Posix_QextSerialPort("/dev/ttyUSB0",QextSerialBase::Polling);
     myCom = new Posix_QextSerialPort("/dev/ttyS1",QextSerialBase::Polling);
    //【linux下使用】定义串口对象，指定串口名和查询模式,这里使用Polling，若报错，拔插USB     //【此次不同于windows下的开发，非常重要】
    myCom ->open(QIODevice::ReadWrite);     //以读写方式打开串口
    //myCom->setBaudRate(BAUD9600);     //波特率设置，我们设置为9600

    myCom->setBaudRate(BAUD115200);     //波特率设置，我们设置为9600


    myCom->setDataBits(DATA_8);     //数据位设置，我们设置为8位数据位
    myCom->setParity(PAR_NONE);     //奇偶校验设置，我们设置为无校验
    myCom->setStopBits(STOP_1);     //停止位设置，我们设置为1位停止位
    myCom->setFlowControl(FLOW_OFF);     //数据流控制设置，我们设置为无数据流控制
    myCom->setTimeout(200);     //延时设置，我们设置为延时200ms,如果设置为500ms的话，会造成程序无响应，原因未知
       //connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //【windows下使用】信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作,linux不支持，只能用定时
    readTimer = new QTimer(this);      //设置读取计时器
     readTimer->start(100);     //设置延时为100ms
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
    //【linux下使用】信号和槽函数关联，当达到定时时间时，进行读串口操作
    //【以上三条与君不同于windows下的开发，非常重要】
}

Widget::~Widget()
{
    delete ui;
}


void Widget::readMyCom() //读取串口数据并显示出来
{
    QByteArray temp = myCom->readAll();     //读取串口缓冲区的所有数据给临时变量temp
    //Ui->textBrowser->insertPlainText(temp);     //将串口的数据显示在窗口的文本浏览器中
    ui->textBrowser->insertPlainText(temp);
}

void Widget::on_pushButton_clicked()
{
    myCom->write(ui->lineEdit->text().toAscii());     //以ASCII码形式将数据写入串口,在Qt5中使用toLatin1
}
