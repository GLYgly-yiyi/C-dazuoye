#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "layoutDemo.h"
#include "qwidgetdraw.h"
#include "qwidgetserialtx.h"
#include "qwidgetserialrx.h"
//数据库
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include<QSqlError>
#include <QDateTime>
#include <QTableView>
#include <QSqlQueryModel>

#include "mainwindow.h"

void shujuku();

class PatientModel: public QSqlQueryModel
{
   public:
    PatientModel()
    {
        this->setQuery("select *from patient");
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
      {
         //  qDebug()<<"i am here"<<index.row()<<index.column();
           Qt::ItemFlags flags = QSqlQueryModel::flags(index);
           if (index.column() ==1 ||  index.column() ==2 )
           flags |= Qt::ItemIsEditable;
           return flags;
      }


   bool setName(int id, QString name)
   {

       bool ok;
      QSqlQuery query;

      query.prepare("UPDATE patient SET name = ? where id = ?");
      query.addBindValue(name);
      query.addBindValue(id);

      ok = query.exec();
    //  if (!ok)
  //    {
  //        qDebug<<"error:"<<query.lastError();
  //    }
      return ok;
   }

   bool setSex(int id, QString sex)
   {

       bool ok;
      QSqlQuery query;

      query.prepare("UPDATE patient SET sex = ? where id = ?");
      query.addBindValue(sex);
      query.addBindValue(id);

      ok = query.exec();
    //  if (!ok)
  //    {
  //        qDebug<<"error:"<<query.lastError();
  //    }
      return ok;
   }

    bool setData(const QModelIndex &index, const QVariant &value,int) override
    {
        if (index.column() < 1|| index.column()>2)
            return false;

        //获取当前列，当前行，用sql更新数据
        //获取当前行第一个单元格的对象
        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0 );

        //从单元格对象得到得到第0列的内容
        int id = this->data(primaryKeyIndex).toInt();
        qDebug()<<"id="<<id;
        bool ok = false;
        if(index.column() == 1)
        {
              //todo :更新姓名
            qDebug()<<"更新姓名";
            ok = setName(id, value.toString());
        }else if(index.column() == 2)
        {
            //todo :更新性别
            qDebug()<<"更新性别";
            ok = setSex(id, value.toString());
        }else
        {
            qDebug()<<"错误";
        }
        if(ok)
        {
            this->setQuery("select *from patient");
        }
        return ok;
    }

};

int main(int argc, char * argv[])
{
    //控件
    QApplication a(argc, argv);

    // shujuku();//数据库
//画图
    QWidget *mainWin = new QWidget();
    QWidgetSerialTx  *serialTx = new QWidgetSerialTx();
    QWidgetSerialRx  *serialRx = new QWidgetSerialRx();
    QWidgetDraw *drawWidgetEcg = new QWidgetDraw();
    QWidgetDraw *drawWidgetSpo = new QWidgetDraw();
    QWidgetDraw *drawWidgetIbp = new QWidgetDraw();

    QVBoxLayout *layoutMain = new QVBoxLayout();

    layoutMain->addWidget(drawWidgetEcg);
    layoutMain->addWidget(drawWidgetSpo);
    layoutMain->addWidget(drawWidgetIbp);

    drawWidgetEcg->setLabelText("ECG  I");
    drawWidgetSpo->setLabelText("Spo");
    drawWidgetIbp->setLabelText("Ibp");

    QLabel *widgetHr = new QLabel();
        QLabel *widgetNihp = new QLabel();

        widgetHr->setText("HR");
        widgetNihp->setText("NIBP");

        QPushButton *btnUp = new QPushButton("UP");
        QPushButton *btnDown = new QPushButton("WODN");

        //修改按钮策略为可任意缩放
        btnUp->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        btnDown->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

        QVBoxLayout *layoutLabelAndBtn = new QVBoxLayout();

        layoutLabelAndBtn->addWidget(widgetHr);
        layoutLabelAndBtn->addWidget(widgetNihp);
        layoutLabelAndBtn->addWidget(btnUp);
        layoutLabelAndBtn->addWidget(btnDown);

        QHBoxLayout *layoutMain1 = new QHBoxLayout();

        layoutMain1->addLayout(layoutMain);
        layoutMain1->addLayout(layoutLabelAndBtn);

        layoutMain1->setStretchFactor(layoutMain,2);
        layoutMain1->setStretchFactor(layoutLabelAndBtn,1);


        mainWin->setWindowTitle("TeamName 1600 x 600");
        mainWin->setLayout(layoutMain1);
        //mainWin->resize(1600, 600);
    //mainWin->setLayout(layoutMain);
    mainWin->connect(serialRx, &QWidgetSerialRx::ecgDataSignal, drawWidgetEcg, &QWidgetDraw::drawEcg);
    mainWin->connect(serialRx, &QWidgetSerialRx::spoDataSignal, drawWidgetSpo, &QWidgetDraw::drawSpo);
    mainWin->connect(serialRx, &QWidgetSerialRx::ibpDataSignal, drawWidgetIbp, &QWidgetDraw::drawIbp);
    mainWin->resize(1600,600);
    mainWin->show();
 /*
   QWidgetDraw *drawWidget = new QWidgetDraw();
    drawWidget->setWindowTitle("火箭团队");
    drawWidget->resize(1000,500);
    drawWidget->show();
   */
layoutDemo2();
layoutDemo1();
layoutDemo0();

//串口

//QWidget *mainWin = new QWidget();
//QWidgetSerialTx *serialTx = new QWidgetSerialTx(mainWin);
//QWidgetSerialRx *serialRx = new QWidgetSerialRx(mainWin);

//mainWin->resize(300,300);
//mainWin->show();

//登录

//创建layout
QHBoxLayout *LayoutUsername  = new QHBoxLayout();
 QHBoxLayout *layoutPassword  = new QHBoxLayout();
 QVBoxLayout *LayoutMain  = new QVBoxLayout();
 //添加控件
 LayoutUsername->addWidget(new QLabel("用户名"));
 layoutPassword->addWidget(new QLabel("密码"));

  //创建文本框
  QLineEdit *lineEditUserName = new QLineEdit();
  QLineEdit *lineEditPassWord = new QLineEdit();
  lineEditPassWord->setEchoMode(QLineEdit::Password);
  LayoutUsername->addWidget(lineEditUserName);
  layoutPassword->addWidget(lineEditPassWord);

         //子layout 加到主layout 中
         LayoutMain->addLayout(LayoutUsername);
         LayoutMain->addLayout(layoutPassword);

         QPushButton *btn = new QPushButton("登录");
         LayoutMain->addWidget(btn);
 //主界面使用layout
 QWidget *widgetMain = new QWidget();
 widgetMain->setLayout(LayoutMain);
 widgetMain->resize(600,400);
 widgetMain->show();



 //数据库
 //加载驱动
 QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");


 //数据库
 db.setHostName("localhost");
 db.setDatabaseName("medical_monitor1");
 db.setUserName("doctor3");
 db.setPassword("123456");


 //用open打开与数据库的来凝结
 //打开成功open会返回true
 bool openOK = db.open();

 if (openOK)
     qDebug()<<"建立连接成功";
               else
     {
     qDebug()<<"建立连接失败";
}

 //查询一条信息
 if (openOK)
 {
     //负责执行sql语句，db指定使用那个连接来执行这个语句的
    QSqlQuery query(db);
   //执行sql语句
    //法1
 //  query.exec("select * from mysql where uid = doctor1");//老师是doctor

    //方法2
/*
    QString userid = "doctor1";
    QString sql = "select * from mysql where uid = ' ";
    sql += userid;
    sql += "'";
    qDebug()<<sql;
    query.exec(sql);
*/
    //法3

    qDebug()<<"方法3";
    QString userid = "doctor1";
    query.prepare("select name from mysql where uid = :id");
    query.bindValue(":id",userid);//用变量替换uid

    query.exec();

    // 打印返回结果
            qDebug()<<query.size();
            while(query.next())//遍历返回的数据表
            {
                qDebug()<<query.value("name")<<query.value("mobile");
                QString name = query.value("name").toString(); // 获取名字字段
                qlonglong mobile = query.value("mobile").toULongLong();
                qDebug()<<name<<mobile; //获取手机号码字段
            }

            if (query.size() < 0)
            {
                qDebug()<<query.lastError();
            }

            bool queryOk;
            // 工作站从数据库读取数据
            query.prepare("SELECT * FROM sample WHERE time > :start and time < :end");
            query.bindValue(":start", "2020-07-22 11:00:00");
            query.bindValue(":end", "2020-07-22 12:00:00");

            queryOk = query.exec();
            if(queryOk)
            {
    //            while(query.next())
    //            {
    //                QByteArray waveData = query.value("value").toByteArray();
    //                // todo, 画波形
    //                qDebug()<<waveData;
    //            }
                qDebug("得到波形数据");
            }else
            {
                qDebug()<<"读波形错误："<<query.lastError();
            }

            /*
             * 以上代码运行与工作站
             ***********************************************************************************************
             * 以下代码应运行于设备端
             * */
                    // 获取当前设备是否已在设备表中
                    query.prepare("SELECT * from device WHERE serial = :serial");
                    query.bindValue(":serial", "DEV-007");

                    int dev_id = -1;
                    if(query.exec())
                    {
                        qDebug()<<"size"<<query.size();
                        if(query.size() > 0)
                        {
                            query.next();
                            qDebug()<<"设备已存在";
                            dev_id = query.value("dev_id").toInt();
                            qDebug()<<"当前设备编号："<<dev_id;
                        }
                        else
                        {
                            query.prepare("INSERT INTO device (serial)"
                                          "VALUES (:serial)");
                            query.bindValue(":serial", "DEV-007");
                            if (!query.exec())
                            {
                                qDebug("设备注册失败！");
                                qDebug()<<query.lastError();
                            }
                            else
                            {
                                qDebug("设备注册成功！");
                            }
                        }
                    }else
                    {
                        qDebug()<<"查看设备错误";
                        qDebug()<<query.lastError();
                    }

                    // 模拟终端设备，上传数据波形
                    // 方法2 bindValue
                    query.prepare("INSERT INTO sample (value, time, dev_id) VALUES (:array, :time, :dev_id)");
                    // 与数据库中数据类型一致的十六进制数组
                    short samples[3] = {2000,2001,2002};
                    QByteArray waves2((char*)samples, sizeof(samples));

                    query.bindValue(":array", waves2);
                    // 绑定当前时间
                    query.bindValue(":time", QDateTime::currentDateTime());
                    // 绑定设备ID
                    query.bindValue(":dev_id", dev_id);
                    // 执行sql语句
                    queryOk = query.exec();
                    if (!queryOk)
                    {
                        qDebug()<<"id="<<dev_id;
                        qDebug()<<"写波形错误："<<query.lastError();
                    }else{
                        qDebug()<<"写波形成功";
                    }

                    // 每15秒更新一次refresh字段，判断离线条件为refresh中时间与当前时间差值超过20秒
                    query.prepare("UPDATE `medical_monitor1`.`device` SET refresh = NOW() WHERE dev_id = :dev_id");
                    query.bindValue(":dev_id", dev_id);
                    queryOk = query.exec();
                    if(!queryOk)
                        qDebug()<<"更新设备在线状态错误";
                }

            /*
             * 下面代码运行在工作站
             */
            //原来有 注释了
            // QWidget *mainWin = new QWidget();

                // 显示设备列表
                // 创建表格对象
                QTableView *view = new QTableView();

                // 创建模型对象
                QSqlQueryModel model;
                model.setQuery("select *from device");
                //model.setQuery("select dev_id, seial, now()-refresh<20 AS online from device");


            //    view->move(0,100);
                view->setModel(&model);
                view->show();


                //显示病人信息

                QTableView *patientView = new QTableView();

                // 创建模型对象
                PatientModel patientModel;
           //     patientModel.setQuery("select *from patient");
                //model.setQuery("select dev_id, seial, now()-refresh<20 AS online from device");

              //  patientView->move(0,800);
                patientView->setModel(&patientModel);
                patientView->show();

  /*
//device_patient

                   QTableView *devPatientview = new QTableView();

                   // 创建模型对象
                   QSqlQueryModel devPatientModel;
               //    model.setQuery("select *from device");
                   //model.setQuery("select dev_id, seial, now()-refresh<20 AS online from device");
                  devPatientModel.setQuery("select * from patient "
                                           "left join device_patient "
                                           "on patient.id = device_patient.patient_id "
                                           "left join device "
                                           "on device.dev_id = device_patient.dev_id");

               //    view->move(0,100);
                   devPatientview->setModel(&model);
                   devPatientview->show();
             */

                //多线程
                MainWindow w;
                w.show();

    return a.exec();
}

void shujuku()
{

    //加载驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");


    //数据库
    db.setHostName("localhost");
    db.setDatabaseName("medical_monitor1");
    db.setUserName("doctor3");
    db.setPassword("123456");


    //用open打开与数据库的来凝结
    //打开成功open会返回true
    bool openOK = db.open();

    if (openOK)
        qDebug()<<"建立连接成功";
                  else
        {
        qDebug()<<"建立连接失败";
}

    //查询一条信息
    if (openOK)
    {
        //负责执行sql语句，db指定使用那个连接来执行这个语句的
       QSqlQuery query(db);
      //执行sql语句
       //法1
    //  query.exec("select * from mysql where uid = doctor1");//老师是doctor

       //方法2
/*
       QString userid = "doctor1";
       QString sql = "select * from mysql where uid = ' ";
       sql += userid;
       sql += "'";
       qDebug()<<sql;
       query.exec(sql);
*/
       //法3

       qDebug()<<"方法3";
       QString userid = "doctor1";
       query.prepare("select name from mysql where uid = :id");
       query.bindValue(":id",userid);//用变量替换uid

       query.exec();

       // 打印返回结果
               qDebug()<<query.size();
               while(query.next())//遍历返回的数据表
               {
                   qDebug()<<query.value("name")<<query.value("mobile");
                   QString name = query.value("name").toString(); // 获取名字字段
                   qlonglong mobile = query.value("mobile").toULongLong();
                   qDebug()<<name<<mobile; //获取手机号码字段
               }

               if (query.size() < 0)
               {
                   qDebug()<<query.lastError();
               }

               bool queryOk;
               // 工作站从数据库读取数据
               query.prepare("SELECT * FROM sample WHERE time > :start and time < :end");
               query.bindValue(":start", "2020-07-22 11:00:00");
               query.bindValue(":end", "2020-07-22 12:00:00");

               queryOk = query.exec();
               if(queryOk)
               {
       //            while(query.next())
       //            {
       //                QByteArray waveData = query.value("value").toByteArray();
       //                // todo, 画波形
       //                qDebug()<<waveData;
       //            }
                   qDebug("得到波形数据");
               }else
               {
                   qDebug()<<"读波形错误："<<query.lastError();
               }

               /*
                * 以上代码运行与工作站
                ***********************************************************************************************
                * 以下代码应运行于设备端
                * */
                       // 获取当前设备是否已在设备表中
                       query.prepare("SELECT * from device WHERE serial = :serial");
                       query.bindValue(":serial", "DEV-007");

                       int dev_id = -1;
                       if(query.exec())
                       {
                           qDebug()<<"size"<<query.size();
                           if(query.size() > 0)
                           {
                               query.next();
                               qDebug()<<"设备已存在";
                               dev_id = query.value("dev_id").toInt();
                               qDebug()<<"当前设备编号："<<dev_id;
                           }
                           else
                           {
                               query.prepare("INSERT INTO device (serial)"
                                             "VALUES (:serial)");
                               query.bindValue(":serial", "DEV-007");
                               if (!query.exec())
                               {
                                   qDebug("设备注册失败！");
                                   qDebug()<<query.lastError();
                               }
                               else
                               {
                                   qDebug("设备注册成功！");
                               }
                           }
                       }else
                       {
                           qDebug()<<"查看设备错误";
                           qDebug()<<query.lastError();
                       }

                       // 模拟终端设备，上传数据波形
                       // 方法2 bindValue
                       query.prepare("INSERT INTO sample (value, time, dev_id) VALUES (:array, :time, :dev_id)");
                       // 与数据库中数据类型一致的十六进制数组
                       short samples[3] = {2000,2001,2002};
                       QByteArray waves2((char*)samples, sizeof(samples));

                       query.bindValue(":array", waves2);
                       // 绑定当前时间
                       query.bindValue(":time", QDateTime::currentDateTime());
                       // 绑定设备ID
                       query.bindValue(":dev_id", dev_id);
                       // 执行sql语句
                       queryOk = query.exec();
                       if (!queryOk)
                       {
                           qDebug()<<"id="<<dev_id;
                           qDebug()<<"写波形错误："<<query.lastError();
                       }else{
                           qDebug()<<"写波形成功";
                       }

                       // 每15秒更新一次refresh字段，判断离线条件为refresh中时间与当前时间差值超过20秒
                       query.prepare("UPDATE `medical_monitor1`.`device` SET refresh = NOW() WHERE dev_id = :dev_id");
                       query.bindValue(":dev_id", dev_id);
                       queryOk = query.exec();
                       if(!queryOk)
                           qDebug()<<"更新设备在线状态错误";
                   }

               /*
                * 下面代码运行在工作站
                */
                QWidget *mainWin = new QWidget();
                   // 显示设备列表
                   // 创建表格对象
                   QTableView *view = new QTableView();

                   // 创建模型对象
                   QSqlQueryModel model;
                   model.setQuery("select *from device");
                   //model.setQuery("select dev_id, seial, now()-refresh<20 AS online from device");


               //    view->move(0,100);
                   view->setModel(&model);
                   view->show();


                   //显示病人信息

                   QTableView *patientView = new QTableView();

                   // 创建模型对象
                   PatientModel patientModel;
              //     patientModel.setQuery("select *from patient");
                   //model.setQuery("select dev_id, seial, now()-refresh<20 AS online from device");

                 //  patientView->move(0,800);
                   patientView->setModel(&patientModel);
                   patientView->show();

     /*
   //device_patient

                      QTableView *devPatientview = new QTableView();

                      // 创建模型对象
                      QSqlQueryModel devPatientModel;
                  //    model.setQuery("select *from device");
                      //model.setQuery("select dev_id, seial, now()-refresh<20 AS online from device");
                     devPatientModel.setQuery("select * from patient "
                                              "left join device_patient "
                                              "on patient.id = device_patient.patient_id "
                                              "left join device "
                                              "on device.dev_id = device_patient.dev_id");

                  //    view->move(0,100);
                      devPatientview->setModel(&model);
                      devPatientview->show();
                */

}

#if 0
int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    QWidget *mainWin = new QWidget();
    QWidgetSerialTx *serialTx = new QWidgetSerialTx(mainWin);
    QWidgetSerialRx *serialRx = new QWidgetSerialRx(mainWin);

    mainWin->resize(300,300);
    mainWin->show();

    return a.exec();
}

#endif

/*登录
int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    //创建layout
    QHBoxLayout *LayoutUsername  = new QHBoxLayout();
     QHBoxLayout *layoutPassword  = new QHBoxLayout();
     QVBoxLayout *LayoutMain  = new QVBoxLayout();






     //添加控件
     LayoutUsername->addWidget(new QLabel("用户名"));
     layoutPassword->addWidget(new QLabel("密码"));

      //创建文本框
      QLineEdit *lineEditUserName = new QLineEdit();
      QLineEdit *lineEditPassWord = new QLineEdit();
      lineEditPassWord->setEchoMode(QLineEdit::Password);
      LayoutUsername->addWidget(lineEditUserName);
      layoutPassword->addWidget(lineEditPassWord);

             //子layout 加到主layout 中
             LayoutMain->addLayout(LayoutUsername);
             LayoutMain->addLayout(layoutPassword);

             QPushButton *btn = new QPushButton("登录");
             LayoutMain->addWidget(btn);


     //主界面使用layout
     QWidget *widgetMain = new QWidget();
     widgetMain->setLayout(LayoutMain);
     widgetMain->resize(600,400);
     widgetMain->show();



    return a.exec();
}
*/


#if 0
int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    //创建波形控件
    QWidgetDraw *drawWidgetEcgI = new QWidgetDraw();
    QWidgetDraw *drawWidgetEcgII = new QWidgetDraw();
    QWidgetDraw *drawWidgetEcgIII = new QWidgetDraw();

    //配置波形控件的策略
    drawWidgetEcgI->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    drawWidgetEcgII->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    drawWidgetEcgIII->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);


    //设置标签内容
    drawWidgetEcgI->setLabelText("ECG  I");
    drawWidgetEcgII->setLabelText("ECG  II");
    drawWidgetEcgIII->setLabelText("ECG  III");
   // drawWidgetEcgI->setStyleSheet("color:white");
   // drawWidgetEcgII->setStyleSheet("color:white");
  //  drawWidgetEcgIII->setStyleSheet("color:white");

    QVBoxLayout *layoutWave = new QVBoxLayout();
    //把创建的波形添加到布局器
    layoutWave->addWidget(drawWidgetEcgI);
    layoutWave->addWidget(drawWidgetEcgII);
    layoutWave->addWidget(drawWidgetEcgIII);


    //添加按钮
    QLabel *widgetHr = new QLabel();
     QLabel *widgetNibp = new QLabel();

    widgetHr->setText("心电波形1");
    widgetNibp->setText("心电波形2");

    QPushButton *btnup = new QPushButton("UP");
    QPushButton *btnDown = new QPushButton("Dowm");


    //修改按钮拉伸策略
    btnup->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    btnDown->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);

    //创建布局其
     QVBoxLayout *layoutLabelAndBtnn = new QVBoxLayout();

     //把控件添加到布局其
     layoutLabelAndBtnn->addWidget(widgetHr);
     layoutLabelAndBtnn->addWidget(widgetNibp);
     layoutLabelAndBtnn->addWidget(btnup);
     layoutLabelAndBtnn->addWidget(btnDown);


     //创建布局其

     QHBoxLayout *layoutMain = new QHBoxLayout();
     layoutMain->addLayout(layoutWave);
     layoutMain->addLayout(layoutLabelAndBtnn);

     //配置拉伸因子
     layoutMain->setStretchFactor(layoutWave,2);
     layoutMain->setStretchFactor(layoutLabelAndBtnn,2);




   //创建主界面并添加布局器
    QWidget *mainWin = new QWidget();
    mainWin->setWindowTitle("火箭团队 1600 x 600");
    mainWin->setLayout(layoutMain);
    mainWin->resize(1600, 600);

    mainWin->show();

    return a.exec();
}

#endif
