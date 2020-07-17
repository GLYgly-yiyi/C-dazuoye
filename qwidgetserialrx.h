#ifndef QWIDGETSERIALRX_H
#define QWIDGETSERIALRX_H

#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

class QWidgetSerialRx : public QWidget
{
    Q_OBJECT
public:
    QSerialPort *com;
    char status = 0;
    char pkgDataCnt;
    char pkgDataHead;
    unsigned char pkgData[7];
    char pkgDataCrc;
    int ecg1, ecg2, ecg3;

    explicit QWidgetSerialRx(QWidget *parent = nullptr);
    int serialInit();
    void serialRx();
    void rxDataHandle(unsigned char data);

signals:

};

#endif // QWIDGETSERIALRX_H
