#include "qwidgetserialrx.h"
#include<QtSerialPort/QSerialPortInfo>
#include<QtSerialPort/QSerialPort>
#include<QDebug>

QWidgetSerialRx::QWidgetSerialRx(QWidget *parent) : QWidget(parent)
{
    //this->resize(1600,600);
  //this->map =   QPixmap(this->width(),this->height());
    //this->map =   QPixmap(this->width(),this->height());
    if(this->serialInit())
        return ;

    //绑定串口有数信号和串口接收函数
    connect(this->com, &QSerialPort::readyRead, this, &QWidgetSerialRx::serialRx);
}


void QWidgetSerialRx::serialRx()
{

    //qDebug()<<"rx:"<<com->readAll();
    //从串口取全部数
    while(!com->atEnd())
    {
        //定义数据接收缓存
        QByteArray data = this->com->read(1);

        //数据处理
        this->rxDataHandle(data[0]);

    }



}

void QWidgetSerialRx::rxDataHandle(unsigned char data)
{
    char tmpData;
    //数据包格式 ID+头+数据+校验
    //状态0.空闲时，判断进来的数据是否为ID，若是则根据不同的类型跳转状态1或5或7
    //状态1.接收数据头，进入下一步
    //状态2.接收数据并还原数据，达到指定数据长度时进入下一步
    //状态3.数据校验，若正确，下一步
    //状态4.数据接收完成

    //状态5，ID为血氧ID，接收数据头
    //状态6.接收血氧数据,接收校验位并打印

    //状态7，ID为血压ID，接收数据头
    //状态8,接收血压数据,接收校验位并打印

    //状态机复位，中间出错回到状态0
    if(data < 0x80)
        this->status = 0;

    //状态机数据处理
    switch(this->status)
    {
    case 0:
    {
        if(0x08 == data)
        {
            this->status=1;
            this->pkgDataCnt = 0;//有效数据计数
        }
        else if(0x09 == data)
        {
            this->status=5;
        }
        else if(0x0a == data)
        {
            this->status=7;
        }else
            qDebug()<<"unknown ID"<<data;
    }break;
    case 1://接收数据头
    {
        this->pkgDataHead = data;
        this->status = 2;
    }break;
    case 2://接收有效数据
    {
        //数据缓存
        tmpData = data&0x7F;
        //从数据头中取数据最高位，第一个数据最高位在数据头最低位中
        tmpData = tmpData | (((this->pkgDataHead >>(this->pkgDataCnt ))&0x01) << 7);
        this->pkgData[this->pkgDataCnt] = tmpData; //把数据存入缓冲区
        //接受有效数据+1
        this->pkgDataCnt +=1;
        //判断接收数据长度
        if(this->pkgDataCnt >=7)
            this->status = 3;
    }break;
    case 3: //接收校验值
    {
        //todo BCC校验

        //得到ECG数据
        ecg1 = this->pkgData[0];
        ecg1 = ecg1<<8;
        ecg1 = ecg1 + this->pkgData[1];

        ecg2 = this->pkgData[2];
        ecg2 = ecg2<<8;
        ecg2 = ecg2 + this->pkgData[3];

        ecg3 = this->pkgData[4];
        ecg3 = ecg3<<8;
        ecg3 = ecg3 + this->pkgData[5];

        emit ecgDataSignal(ecg1);

        //数据打印，调试用
        qDebug("ecgTx:********************by董汶陇");
        qDebug()<<"ecg1"<<ecg1<<"ecg2"<<ecg2<<"ecg3"<<ecg3;

        //发出数据用于显示
    }break;
    case 5:
    {
        this->spoDataHead = data;
        this->status = 6;
    }break;
    case 6:
    {
        spoData = data&0x7F;
        //从数据头中取数据最高位，第一个数据最高位在数据头最低位中
        spoData = spoData | ((this->spoDataHead &0x01) << 7);
        qDebug("spoTx:********************");
        qDebug("spo2Rx:");
        qDebug()<<"Spo:"<<(int)spoData;

        emit spoDataSignal(spoData);

        this->status = 7;
    }break;
    case 7:
    {
        this->ibpDataHead = data;
        this->status = 8;
    }break;
    case 8:
    {
        ibpData = data&0x7F;
        //从数据头中取数据最高位，第一个数据最高位在数据头最低位中
        ibpData = ibpData | ((this->ibpDataHead &0x01) << 7);
        qDebug("ibpTx:********************");
        qDebug("ibp2Rx:");
        qDebug()<<"Ibp:"<<(int)ibpData;
        this->status = 7;

        emit ibpDataSignal(ibpData);
    }break;
    }



}

int QWidgetSerialRx::serialInit()
{
    //查看设备串口信息
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();

    }
    //创建串口对象
    this->com = new QSerialPort();

    this->com->setPortName("COM2");


    //打开
    if(!this->com->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口错误"<<this->com->portName();
        return -1;
    }
    else
        qDebug()<<"open success";

    //参数配置
    this->com->setBaudRate(QSerialPort::Baud115200);
    this->com->setDataBits(QSerialPort::Data8);
    this->com->setFlowControl(QSerialPort::NoFlowControl);
    this->com->setParity(QSerialPort::NoParity);
    this->com->setStopBits(QSerialPort::OneStop);

    return 0 ;




}


