#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "QSerialPort"
#include "QWidget"
#include <QString>
#include <wiringPi.h>
#include <QMovie>





 QSerialPort *serial;
QString Dataa,tempdata;
QString pot1,pot2,pot3,pot4;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/************/
    SpeedGauge = new QcGaugeWidget;
    QcLabelItem *lab = SpeedGauge->addLabel(40);
    lab->setText("0");
    SpeedNeedle = SpeedGauge->addNeedle(60);
    SpeedNeedle->setLabel(lab);
    SpeedNeedle->setColor(Qt::red);
    SpeedNeedle->setValueRange(0,130);

/**********/
    SpeedGauge1 = new QcGaugeWidget;
    QcLabelItem *lab1 = SpeedGauge1->addLabel(40);
    lab1->setText("0");
    SpeedNeedle1 = SpeedGauge1->addNeedle(60);
    SpeedNeedle1->setLabel(lab1);
    SpeedNeedle1->setColor(Qt::red);
    SpeedNeedle1->setValueRange(0,130);
/**********/
    SpeedGauge2 = new QcGaugeWidget;
    QcLabelItem *lab2 = SpeedGauge2->addLabel(40);
    lab2->setText("0");
    SpeedNeedle2 = SpeedGauge2->addNeedle(60);
    SpeedNeedle2->setLabel(lab2);
    SpeedNeedle2->setColor(Qt::red);
    SpeedNeedle2->setValueRange(0,130);
 /***********/
        SpeedGauge3 = new QcGaugeWidget;
        QcLabelItem *lab3 = SpeedGauge3->addLabel(40);
        lab3->setText("0");
        SpeedNeedle3 = SpeedGauge3->addNeedle(60);
        SpeedNeedle3->setLabel(lab3);
        SpeedNeedle3->setColor(Qt::red);
        SpeedNeedle3->setValueRange(0,130);

    ui->verticalLayoutpot3->addWidget(SpeedGauge);
    ui->verticalLayoutpot1->addWidget(SpeedGauge1);
    ui->verticalLayoutpot2->addWidget(SpeedGauge2);
    ui->verticalLayoutpot4->addWidget(SpeedGauge3);

    /***** bkg image****/
QMovie *movie =new QMovie ("/home/pi/cp2/bgbg.gif");
ui->bkg->setMovie(movie);
movie->start();
    /*******/


/**************/
QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm");
ui->dateplace->setText(sDate);
/****/

    wiringPiSetup();
    pinMode(2,INPUT);
    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyS0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QSerialPort::ReadWrite);
    connect(serial,SIGNAL(readyRead()),this,SLOT(ReadData()));
    serial->clear();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    close();
}



void MainWindow::ReadData()

{       //QString pot1,pot2,pot3,pot4;
               //data0 data1 data2 data3

        pot1="";
        pot2="";
        pot3="";
        pot4="";
        tempdata="";
    if (serial->isOpen())
            {
        serial->waitForReadyRead(10);
        //Dataa=serial->;
        if(serial->bytesAvailable()>=5)
                    {  Dataa=serial->readLine();
                        Dataa.replace("\n","");Dataa.replace("\r","");
                        pot1.append(Dataa);
                        pot1.replace(1,pot1.length()-1,"");

                        tempdata.append(Dataa);
                        tempdata.replace(2,tempdata.length()-1,"");
                        pot2.append(tempdata.right(1));
                        tempdata="";
                        tempdata.append(Dataa);
                        tempdata.replace(3,tempdata.length()-1,"");
                        pot3.append(tempdata.right(1));
                        tempdata="";
                        tempdata.append(Dataa);
                        tempdata.replace(4,tempdata.length()-1,"");
                        pot4.append(tempdata.right(1));

                    if((pot1.length()>0)&&(pot2.length()>0)&&(pot3.length()>0)&&(pot4.length()>0))
                    {QChar valtmp=pot1.at(0);
                        int val1=valtmp.toLatin1();
                       ui->labelpot1->setText(QString::number(val1));
                       //qDebug() << "data=" << Dataa << " Pot 1 =" << val2 << " Pot2=" << val2 << " Pot3= " << val3 << " Pot4=" << val4 ;
SpeedNeedle1->setCurrentValue(val1);

                        valtmp=pot2.at(0);
                        int val2=valtmp.toLatin1();
SpeedNeedle2->setCurrentValue(val2);
                      ui->labelpot2->setText(QString::number(val2));


                      valtmp=pot3.at(0);
                      int val3=valtmp.toLatin1();
                     ui->labelpot3->setText(QString::number(val3));
SpeedNeedle->setCurrentValue(val3);

                      valtmp=pot4.at(0);
                     int val4=valtmp.toLatin1();
                    ui->labelpot4->setText(QString::number(val4));
SpeedNeedle3->setCurrentValue(val4);
                    qDebug() << "data=" << Dataa << " Pot 1 =" << val2 << " Pot2=" << val2 << " Pot3= " << val3 << " Pot4=" << val4 ;

}



                    }

        //serial->clear();

//                if(Dataa.length()>=4)
//                    {
//
//                //
//                //pot3.append(Dataa);
//                pot1.replace(1,pot1.length()-1,"");
//                //
//                //
//                //pot4.append(pot3.right(pot3.length()-2));
//                      qDebug() << pot1;
//                Dataa="";}
    }






}






