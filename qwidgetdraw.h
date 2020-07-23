#ifndef QWIDGETDRAW_H
#define QWIDGETDRAW_H

#include <QWidget>
#include<QLabel>

class QWidgetDraw : public QWidget
{
    Q_OBJECT
public:
    QTimer *timer,*timer2;
    QPixmap map;
    QLabel *label;
    explicit QWidgetDraw(QWidget *parent = nullptr);
    int x = 0;
    int y = 0;
    int z=0;
    int dir = 0;
    int cnt = 0;
    int lastData = 0;
    int lastData2 = 0;
    int lastData3 = 0;
    unsigned int index=0;
    unsigned int index_sin=0;
    void draw(QPainter *painter);
    void drawDemo(QPainter *painter);
    void drawTriangle(QPainter *painter);
    void drawTriangle1(QPainter *painter);
    void sendData();
    void refresh();
    void drawWaveFromArray(QPainter *painter);
    //void drawWave(QPainter *painter,int data,int sindata);
    void drawWave(QPainter *painter,int data,int sindata);
    void refreshFromData(int data,int sindata);
    void testmap();
    void testSend();
    void setLabelText(QString labelText);
    void drawEcg(int data);
    void drawSpo(int data);
    void drawIbp(int data);




private:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event)override ;

signals:
    void rxDataSignal(int data,int sindata);
    //void sinDataSignal(int data);

};

#endif // QWIDGETDRAW_H
