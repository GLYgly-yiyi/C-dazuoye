#ifndef QWIDGETSERIALTX_H
#define QWIDGETSERIALTX_H

#include <QWidget>
#include<QtSerialPort/QSerialPort>
#include<QTimer>

class QWidgetSerialTx : public QWidget
{
    Q_OBJECT
public:
    QSerialPort *com;
    QTimer *timer;
    int index=0;
    int indexSpo2=0;
    int indexIbp2=0;

    explicit QWidgetSerialTx(QWidget *parent = nullptr);

    int serialInit(void);
    void sendEcgPkg();
    unsigned int getEcg2Data();

signals:

};

#endif // QWIDGETSERIALTX_H
