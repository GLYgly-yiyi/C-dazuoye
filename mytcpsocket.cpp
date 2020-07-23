#include "mytcpsocket.h"
#include <QDebug>
#include <QThread>


MyTcpSocket::MyTcpSocket(QObject *parent) : QTcpSocket(parent)
{

    connect(this, SIGNAL(readyRead()), this, SLOT(slotReadDa()));

}

void MyTcpSocket::slotReadDa()
{
    QByteArray ba = this->readAll();


    emit signalRecDa(ba);

    qDebug()<<"slotReadDa : receive da  = " <<ba<<"curr thread = "<<QThread::currentThread();

}
