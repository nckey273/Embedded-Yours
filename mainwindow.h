#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qcgaugewidget.h"
#include <QMainWindow>
#include <QPainter>
#include <QQuickWidget>
#include <QQuickItem>
#include <QQuickView>
#include <QVariant>
#include <QDateTime>






namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void ReadData();

private:
    Ui::MainWindow *ui;
    QcGaugeWidget *SpeedGauge;
    QcNeedleItem *SpeedNeedle;
    QcGaugeWidget *SpeedGauge1;
    QcNeedleItem *SpeedNeedle1;
    QcGaugeWidget *SpeedGauge2;
    QcNeedleItem *SpeedNeedle2;
    QcGaugeWidget *SpeedGauge3;
    QcNeedleItem *SpeedNeedle3;

};

#endif // MAINWINDOW_H
