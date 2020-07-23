#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);

signals:
    void signalRecDa(QByteArray ba);

 private slots:
    void slotReadDa();

signals:




};

#endif // MYTCPSOCKET_H
