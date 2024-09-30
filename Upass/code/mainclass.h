#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QProcess>

#include <wiringPi.h>

#include "serialclass.h"
#include "databaseclass1.h"
#include "databaseclass2.h"

#include "/home/ali/CTPOZ/Library/lib8/CSJPOSLib.h"


#define OOUT1 31
#define OOUT2 33
#define IINP1 35
#define IINP2 37

namespace Ui {
class MainClass;
}

class MainClass : public QWidget
{
    Q_OBJECT

public:
    explicit MainClass(QWidget *parent = 0);
    ~MainClass();

private:
    Ui::MainClass *ui;

    SerialClass* serialWorker;
    QThread* serialThread;
    void start_serial();

    DatabaseClass1* dbWorker_1;
    QThread* dbThread_1;
    void start_db_1();

    DatabaseClass2* dbWorker_2;
    QThread* dbThread_2;
    void start_db_2();

    void setWiringOPI();
    void mangeConnections();

    QTimer timerSuccess1;
    QTimer timerSuccess2;

    bool bOepn1;
    bool bOepn2;

    QTimer test;

signals:
    void signal_main_StartThread();

    void InputDetected1();
    void InputDetected2();


public slots:

private slots:
    void slot_main_StartThread();

    void recieveInput1();
    void recieveInput2();

    void slot_main_success1();
    void slot_main_success2();
    void slot_main_successEnd1();
    void slot_main_successEnd2();
};

#endif // MAINCLASS_H
