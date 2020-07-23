#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
       void tcpNewConnect();
       void tcpReadyRead();


       void slotReceiveDa(QByteArray ba);
        void slotReceiveDa2(QByteArray ba);


private:
    Ui::MainWindow *ui;

       QTcpServer *mServer;
       QTcpSocket *mSocket;

       int mCount;
};
#endif // MAINWINDOW_H
