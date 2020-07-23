#include "qwidgetdraw.h"
#include "QPainter"
#include<QTimer>
#include<QLabel>
#include<QDebug>

int ecgWave[]=
{
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2008, 2016, 2016, 2016, 2024, 2032, 2048,
           2064, 2064, 2064, 2072, 2080, 2080, 2080, 2088, 2096, 2104,
           2112, 2112, 2112, 2112, 2112, 2112, 2104, 2096, 2088,
           2080, 2080, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2032,
           2032, 2016, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 1992, 1984, 1976,
           1968, 1960, 1952, 1944, 1936, 1944, 1952, 2016, 2080, 2136,
           2192, 2256, 2320, 2376, 2432, 2488, 2544, 2568, 2592, 2536,
           2480, 2424, 2368, 2304, 2240, 2184, 2128, 2072, 2016, 1968,
           1920, 1928, 1936, 1944, 1952, 1960, 1968, 1984, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2008, 2016, 2024, 2032, 2032,
           2032, 2048, 2064, 2064, 2064, 2072, 2080, 2088, 2096, 2104,
           2112, 2112, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2160,
           2160, 2160, 2160, 2168, 2176, 2176, 2176, 2184, 2192,
           2192, 2192, 2192, 2200, 2208, 2208, 2208, 2208, 2208, 2208,
           2208, 2200, 2192, 2192, 2192, 2184, 2176, 2176, 2176, 2168,
           2160, 2160, 2160, 2144, 2128, 2128, 2128, 2128, 2128, 2112,
           2096, 2088, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2024,
           2016, 2016, 2016, 2008, 2000, 2000, 2000, 2000, 2000,
           2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
};




QWidgetDraw::QWidgetDraw(QWidget *parent) : QWidget(parent)
{
    this->label = new QLabel(this);
    this->label->setStyleSheet("color:white");
    this->resize(1600,600);
  //this->map =   QPixmap(this->width(),this->height());
    map =   QPixmap(this->width(),this->height());
    //QPixmap map =  QPixmap(this->width(),this->height());

    //this->map = new QPixmap(100,100);
    //this->map2 = new QPixmap(Wid,500,200,300,300);

    //this->map->fill(Qt::black);



    timer = new QTimer(this);

    //timerout是定时器的一个信号
    //refresh是一个槽函数
    //connect(timer, &QTimer::timeout,this, &QWidgetDraw::sendData);
    connect(this, &QWidgetDraw::rxDataSignal, this, &QWidgetDraw::refreshFromData);

    timer->start(10);//单位是ms
}

void QWidgetDraw::drawEcg(int ecgData)
{
    //qDebug()<<"nihao";
    //map =   QPixmap(this->width(),this->height());
    int ecgdata;
    int width = this->width();
    int height = this->height();
    ecgdata = height*0.8-ecgData*height/4196;
    //qDebug()<<"nihao"<<ecgdata;
    QPainter *painter = new QPainter();

    painter->begin (&this->map);
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::green);
    painter->setPen(*pen);



    pen->setWidth(6);
    pen->setColor(Qt::black);

    painter->save();
    painter->setPen(*pen);


    //擦除
    painter->drawLine(this->x+2,0,this->x+2,height);

    painter->restore();

    //painter->drawPoint(x,height-ecgWave[index]*height/4096);
    painter->drawLine(this->x-1,lastData,this->x,ecgdata);

    lastData = ecgdata;

    //步进
    this->x+=1;


    if(this->x>=width)
        this->x=0;
    painter->end();
    this->update();
}

void QWidgetDraw::drawSpo(int spoData)
{
    int spodata;
    int width = this->width();
    int height = this->height();
    spodata = height*0.8-spoData*height/512;
    //qDebug()<<"nihao"<<ecgdata;
    QPainter *painter = new QPainter();

    painter->begin (&this->map);
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::yellow);
    painter->setPen(*pen);



    pen->setWidth(6);
    pen->setColor(Qt::black);

    painter->save();
    painter->setPen(*pen);


    //擦除
    painter->drawLine(this->y+2,0,this->y+2,height);

    painter->restore();

    //painter->drawPoint(x,height-ecgWave[index]*height/4096);
    painter->drawLine(this->y-1,lastData2,this->y,spodata);

    lastData2 = spodata;

    //步进
    this->y+=1;


    if(this->y>=width)
        this->y=0;
    painter->end();
    this->update();
}

void QWidgetDraw::drawIbp(int ibpData)
{
    int ibpdata;
    int width = this->width();
    int height = this->height();
    ibpdata = height*0.8-ibpData*height/256;
    //qDebug()<<"nihao"<<ecgdata;
    QPainter *painter = new QPainter();

    painter->begin (&this->map);
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::red);
    painter->setPen(*pen);



    pen->setWidth(6);
    pen->setColor(Qt::black);

    painter->save();
    painter->setPen(*pen);


    //擦除
    painter->drawLine(this->z+2,0,this->z+2,height);

    painter->restore();

    //painter->drawPoint(x,height-ecgWave[index]*height/4096);
    painter->drawLine(this->z-1,lastData3,this->z,ibpdata);

    lastData3 = ibpdata;

    //步进
    this->z+=1;


    if(this->z>=width)
        this->z=0;
    painter->end();
    this->update();
}

void QWidgetDraw::setLabelText(QString labelText)
{
    this->label->setText(labelText);
}

void QWidgetDraw::sendData()
{
    //this->map = new QPixmap(this->width(),this->height());
     //this->map->fill(Qt::black);
    int sindata=0;

    int height = this->height();
    sindata = height*0.8-ecgWave[index_sin]*height/8192;

    index_sin +=3;
    if(index_sin >=sizeof(ecgWave)/sizeof(int))
        index_sin=0;

    int data=0;
   //int height = this->height();
    data = height/3-ecgWave[index]*height/8192;

    index +=3;
    if(index >=sizeof(ecgWave)/sizeof(int))
        index=0;

    //emit rxDataSignal(data);
     emit rxDataSignal(data,sindata);


}

void QWidgetDraw:: refreshFromData(int data,int sindata)
{
    QPainter *painter = new QPainter();

    painter->begin (&this->map);
    //painter->begin(this);


    //配置画笔
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::red);
    painter->setPen(*pen);


    //drawWave(painter, data,sindata);
    drawWave(painter,data,sindata);
    //drawWave(painter, sindata);
    painter->end();




    //this->map->fill(Qt::black);

    //触发event，将画布内容更新到窗口上
    this->update();

}

void QWidgetDraw:: refresh()
{
    QPainter *painter = new QPainter();
    painter->begin(&this->map);

    this->draw(painter);
    painter->end();

    //this->map->fill(Qt::black);

    //触发event，将画布内容更新到窗口上
    this->update();

}

void QWidgetDraw::resizeEvent(QResizeEvent *event)
{
    QPixmap cleanmap = QPixmap(this->width(),this->height());
    cleanmap.fill(Qt::black);
    this->map= cleanmap;
}

//事件机制
void QWidgetDraw:: paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter();

    painter->begin(this);

    //this->draw(painter);
    painter->drawPixmap(0,0, this->map);

    painter->end();
}

void QWidgetDraw::drawDemo(QPainter *painter)
{
    QPen *pen = new QPen();
    pen->setWidth(4);

    //重新配置
    pen->setColor(Qt::green);
    painter->save();
    painter->setPen(*pen);

    //画图
    painter->drawRect(0,0,100,100);


    //重新加载原来的配置
    painter->restore();
}

void QWidgetDraw::draw(QPainter *painter)
{
    //配置画笔
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::red);
    painter->setPen(*pen);
    //this->drawTriangle1(painter);
    //drawTriangle1(painter);
    //drawWaveFromArray(painter);
}

void QWidgetDraw::drawTriangle1(QPainter *painter)
{
    int width = this->width();
    int height = this->height();


    //创建画笔
    QPen *pen = new QPen();
    pen->setWidth(4);
    pen->setColor(Qt::black);

    painter->save();
    //新的配置
    painter->setPen(*pen);

    //擦除

    painter->drawLine(x,0,x,height);


    painter->restore();




        painter->drawPoint(x,height-y);
        x+=1;

        if(0 == dir)
        {
        y+=1;

        if( y > height/2)
            dir=1;

        }else
        {
            y-=1;
            if(0 == y)
                dir=0;
        }

        if (x>=width)
            x=0;


}


void QWidgetDraw::drawTriangle(QPainter *painter)
{
    int width = this->width();
    int height = this->height();

    int cnt;
    int x,y;
    int dir=0;

    x=0;
    y=0;

    for(cnt=0;cnt<width;cnt ++)
    {
        painter->drawPoint(x,height-y);
        x+=1;

        if(0 == dir)
        {
        y+=1;

        if( y > height/2)
            dir=1;

        }else
        {
            y-=1;
            if(0 == y)
                dir=0;
        }
    }

}



/*void QWidgetDraw::drawWaveFromArray(QPainter *painter)
{
    int data=0;

    int height = this->height();
    data = height-ecgWave[index]*height/4096;
    //drawWave(painter, data);
    index +=3;
    if(index >=sizeof(ecgWave)/sizeof(int))
        index=0;


}*/


void QWidgetDraw::drawWave(QPainter *painter,int data, int sindata)
{
    int width = this->width();
    int height = this->height();
    //int width = 200;

    QPen *pen = new QPen();

    pen->setWidth(6);
    pen->setColor(Qt::black);

    painter->save();
    painter->setPen(*pen);


    //擦除
    painter->drawLine(x+2,0,x+2,height);

    painter->restore();

    //painter->drawPoint(x,height-ecgWave[index]*height/4096);
    painter->drawLine(x-1,lastData,x,data);
    painter->drawLine(x-1,lastData2,x,sindata);
    lastData = data;
    lastData2 = sindata;

    //步进
    x+=1;
    //index +=3;

    //if(index >=sizeof(ecgWave)/sizeof(int))
       // index=0;

    if(x>=width)
        x=0;
}

