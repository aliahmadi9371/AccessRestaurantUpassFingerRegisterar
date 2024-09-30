#include "mainclass.h"
#include "ui_mainclass.h"

static MainClass* main = NULL;

void readiput1(){
    if(main)
        emit main->InputDetected1();
}

void MainClass::recieveInput1()
{
    qDebug() << "Main------------>received from input 1";
    if(bOepn1)
        slot_main_successEnd1();
}

void readiput2(){
    if(main)
        emit main->InputDetected2();
}

void MainClass::recieveInput2()
{
    qDebug() << "Main------------>received from input 2";
    if(bOepn2)
        slot_main_successEnd2();
}


MainClass::MainClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainClass)
{
    ui->setupUi(this);

    CSJPOSLib::ESCPOSPrinter *printer = new CSJPOSLib::ESCPOSPrinter();

    qDebug() << "Main------------>Start Program";
    connect(this,SIGNAL(signal_main_StartThread()),
            this,SLOT(slot_main_StartThread()),Qt::QueuedConnection);


    bOepn1 = false;
    bOepn2 = false;
}

MainClass::~MainClass()
{
    qDebug() << "Main------------>Stop Signals";
    emit dbWorker_1->signal_db_StopThread();
    dbWorker_1->deleteLater();
    dbThread_1->deleteLater();

    emit dbWorker_2->signal_db_StopThread();
    dbWorker_2->deleteLater();
    dbThread_2->deleteLater();

    emit serialWorker->signal_serial_StopThread();
    serialWorker->deleteLater();
    serialThread->deleteLater();
    qDebug() << "Main------------>Stop Application";
    delete ui;
}

void MainClass::slot_main_StartThread()
{

    setWiringOPI();
    start_db_1();
    while(!dbWorker_1->b_db_isOpen){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    start_db_2();
    while(!dbWorker_2->b_db_isOpen){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    start_serial();
    mangeConnections();
    main = this;


    test.setSingleShot(false);
    //test.start(5000);
    connect(&test,SIGNAL(timeout()),
            dbWorker_1,SLOT(testSlot()),
            Qt::QueuedConnection);
    connect(&test,SIGNAL(timeout()),
            dbWorker_2,SLOT(testSlot()),
            Qt::QueuedConnection);

}

void MainClass::start_serial()
{
    serialThread = new QThread;
    serialWorker = new SerialClass;
    serialWorker->moveToThread(serialThread);
    connect(serialWorker,SIGNAL(signal_serial_StartThread()),
            serialWorker,SLOT(slot_serial_StartThread()),
            Qt::QueuedConnection);
    serialThread->start();
    emit serialWorker->signal_serial_StartThread();
}

void MainClass::start_db_1()
{
    dbThread_1 = new QThread;
    dbWorker_1 = new DatabaseClass1;
    dbWorker_1->moveToThread(dbThread_1);
    connect(dbWorker_1,SIGNAL(signal_db_StartThread()),
                dbWorker_1,SLOT(slot_db_StartThread()),
                Qt::QueuedConnection);
    dbThread_1->start();
    emit dbWorker_1->signal_db_StartThread();
}

void MainClass::start_db_2()
{
    dbThread_2 = new QThread;
    dbWorker_2 = new DatabaseClass2;
    dbWorker_2->moveToThread(dbThread_2);
    connect(dbWorker_2,SIGNAL(signal_db_StartThread()),
                dbWorker_2,SLOT(slot_db_StartThread()),
                Qt::QueuedConnection);
    dbThread_2->start();
    emit dbWorker_2->signal_db_StartThread();
}

void MainClass::setWiringOPI()
{
    wiringPiSetupPhys();
    pinMode(OOUT1,OUTPUT);
    pinMode(OOUT2,OUTPUT);

    pinMode(IINP1,INPUT);
    pinMode(IINP2,INPUT);

    pullUpDnControl(OOUT1, PUD_DOWN);
    pullUpDnControl(OOUT1, PUD_DOWN);

    pullUpDnControl(IINP1, PUD_UP);
    pullUpDnControl(IINP2, PUD_UP);

    wiringPiISR(IINP1, INT_EDGE_FALLING, &readiput1);
    wiringPiISR(IINP2, INT_EDGE_FALLING, &readiput2);

    connect(this,SIGNAL(InputDetected1()),
            this,SLOT(recieveInput1()),
            Qt::QueuedConnection);
    connect(this,SIGNAL(InputDetected2()),
            this,SLOT(recieveInput2()),
            Qt::QueuedConnection);
}

void MainClass::mangeConnections()
{
    connect(serialWorker,SIGNAL(signal_serial_GetNew_EPC_Data_port1(QString)),
            dbWorker_1,SLOT(slot_db_GetNew_EPC_Data_port1(QString)),
            Qt::QueuedConnection);

    connect(serialWorker,SIGNAL(signal_serial_GetNew_EPC_Data_port2(QString)),
            dbWorker_2,SLOT(slot_db_GetNew_EPC_Data_port2(QString)),
            Qt::QueuedConnection);

    connect(dbWorker_1,SIGNAL(signal_db_changeProgStatus1(bool)),
            serialWorker,SLOT(slot_serial_changeProcMode1(bool)),
            Qt::QueuedConnection);

    connect(dbWorker_2,SIGNAL(signal_db_changeProgStatus2(bool)),
            serialWorker,SLOT(slot_serial_changeProcMode2(bool)),
            Qt::QueuedConnection);

    connect(dbWorker_1,SIGNAL(signal_db_databaseConnection1(bool)),
            serialWorker,SLOT(slot_serial_dbConnectionStatus1(bool)),
            Qt::QueuedConnection);

    connect(dbWorker_2,SIGNAL(signal_db_databaseConnection2(bool)),
            serialWorker,SLOT(slot_serial_dbConnectionStatus2(bool)),
            Qt::QueuedConnection);

    connect(dbWorker_1,SIGNAL(signal_db_success1()),
            this,SLOT(slot_main_success1()),
            Qt::QueuedConnection);

    connect(dbWorker_2,SIGNAL(signal_db_success2()),
            this,SLOT(slot_main_success2()),
            Qt::QueuedConnection);

    timerSuccess1.setSingleShot(true);
    connect(&timerSuccess1,SIGNAL(timeout()),
            this,SLOT(slot_main_successEnd1()),
            Qt::QueuedConnection);

    timerSuccess2.setSingleShot(true);
    connect(&timerSuccess2,SIGNAL(timeout()),
            this,SLOT(slot_main_successEnd2()),
            Qt::QueuedConnection);

    connect(dbWorker_1,SIGNAL(signal_db_StopThread()),
            dbWorker_1,SLOT(slot_db_StopThread()),
            Qt::QueuedConnection);

    connect(dbWorker_2,SIGNAL(signal_db_StopThread()),
            dbWorker_2,SLOT(slot_db_StopThread()),
            Qt::QueuedConnection);

    connect(serialWorker,SIGNAL(signal_serial_StopThread()),
            serialWorker,SLOT(slot_serial_StopThread()),
            Qt::QueuedConnection);
}

void MainClass::slot_main_success1()
{
    digitalWrite(OOUT1,1);
    bOepn1 = true;
    timerSuccess1.start(1000);
}

void MainClass::slot_main_success2()
{
    digitalWrite(OOUT2,1);
    bOepn2 = true;
    timerSuccess2.start(1000);
}

void MainClass::slot_main_successEnd1()
{
    timerSuccess1.stop();
    digitalWrite(OOUT1,0);
    emit dbWorker_1->signal_db_changeProgStatus1(false);
    bOepn1 = false;
    return;
}

void MainClass::slot_main_successEnd2()
{
    timerSuccess2.stop();
    digitalWrite(OOUT2,0);
    emit dbWorker_2->signal_db_changeProgStatus2(false);
    bOepn2 = false;
    return;
}



