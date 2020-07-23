#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include "mytcpsocket.h"
#include <QTcpSocket>

//练习：按照上午的课程，建立一个sever,用调试工具可以进行接收，显示到ui的textedit1上


//练习：开两个调试工具连接我们的server 然后分别发送 socket的槽函数打印一下thread地址





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCount = 0;

    mServer = new QTcpServer(this);
    mServer->setMaxPendingConnections(2);

    connect(mServer, SIGNAL(newConnection()), this, SLOT(tcpNewConnect()));

    mServer->listen(QHostAddress::Any,1234);//监听
  //  mServer->listen(QHostAddress::Any,1235);//监听
    qDebug()<<"thread = "<<QThread::currentThread();   //打印当前线程

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tcpNewConnect()
{
    mSocket = mServer->nextPendingConnection();
    if(mSocket)
    {

        MyTcpSocket *mySocket = new MyTcpSocket();
        mySocket->setSocketDescriptor(mSocket->socketDescriptor());
        QThread *thread = new QThread();

     // connect(mySocket,SIGNAL(signalRecDa(QByteArray)), this, SLOT(slotReceiveDa(QByteArray)));
      //QThread *thread = new QThread();

        mySocket->moveToThread(thread);//把mysocket放到Thread中运行
        thread->start();
if(mCount ==0)
{
    connect(mySocket,SIGNAL(signalRecDa(QByteArray)), this, SLOT(slotReceiveDa(QByteArray)));
}
else
{
    connect(mySocket,SIGNAL(signalRecDa(QByteArray)), this, SLOT(slotReceiveDa2(QByteArray)));

}
mCount++;

        connect(mSocket,SIGNAL(readyRead()),this,SLOT(tcpReadyRead()));
      //  connect(mSocket, SIGNAL(disconnected()),this,SLOT(tcpDisconnect()));
      //  ui->label->setText("Connected:"); //建立
    }
}


void MainWindow::tcpReadyRead()
{
  qDebug()<<"tcpReadyRead::Thread = "<<QThread::currentThread();//打印当前线程地址
    ui->textEdit1->append(mSocket->readAll());
   // ui->textEdit_2->append(mSocket->readAll());

}

void MainWindow::slotReceiveDa(QByteArray ba)
{
    qDebug()<<"  slotreceive1 thread  ="<<QThread::currentThread();
    ui->textEdit1->append(ba);

}

void MainWindow::slotReceiveDa2(QByteArray ba)
{
    qDebug()<<"  slotreceive2 thread  ="<<QThread::currentThread();
    ui->textEdit_2->append(ba);

}
