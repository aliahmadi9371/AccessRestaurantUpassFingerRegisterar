#include "serialclass.h"

SerialClass::SerialClass(QObject *parent) : QObject(parent)
{

}


void SerialClass::slot_serial_StartThread()
{
    qDebug() << "SerialClass----->start serial thread";
    func_serial_configClass("Upass.ini");


    bInproc1 = false;
    bInproc2 = false;

    timerSerial1 = new QTimer();
    timerSerial2 = new QTimer();

    timerSerial1->setSingleShot(true);
    timerSerial2->setSingleShot(true);

    connect(timerSerial1,SIGNAL(timeout()),
            this,SLOT(slot_serial_timeout1()),
            Qt::QueuedConnection);

    connect(timerSerial2,SIGNAL(timeout()),
            this,SLOT(slot_serial_timeout2()),
            Qt::QueuedConnection);

    serialPort_1 = new QSerialPort(this);
    serialPort_2 = new QSerialPort(this);

    bOpen1 = func_serial_openSerial(serialPort_1,serialPort_1_path,
                                    QSerialPort::Baud9600,QSerialPort::AllDirections,
                                    QSerialPort::Data8,QSerialPort::NoParity,
                                    QSerialPort::OneStop,QSerialPort::NoFlowControl,QIODevice::ReadWrite);
    connect(serialPort_1,SIGNAL(readyRead()),this,SLOT(slot_serial_ReadPort1()),Qt::QueuedConnection);
    bInSerial1 = false;

    bOpen2 = func_serial_openSerial(serialPort_2,serialPort_2_path,
                                    QSerialPort::Baud9600,QSerialPort::AllDirections,
                                    QSerialPort::Data8,QSerialPort::NoParity,
                                    QSerialPort::OneStop,QSerialPort::NoFlowControl,QIODevice::ReadWrite);
    connect(serialPort_2,SIGNAL(readyRead()),this,SLOT(slot_serial_ReadPort2()),Qt::QueuedConnection);
    bInSerial2 = false;


    dbStatusConnection1 = false;
    dbStatusConnection2 = false;
}

void SerialClass::func_serial_configClass(QString iniPath)
{
    QSettings setting(iniPath,QSettings::IniFormat);
    setting.setIniCodec("UTF-8");

    serialPort_1_path = setting.value("Serial/RS232_1","ttyS3").toString(); //ttyS3 (RS232_1)
    serialPort_2_path = setting.value("Serial/RS232_2","ttyS1").toString(); //ttyS1 (RS232_2)

}

void SerialClass::slot_serial_StopThread()
{
    qDebug() << "SerialClass----->Stop";
    serialPort_1->close();
    serialPort_2->close();
    return;
}

bool SerialClass::func_serial_openSerial(QSerialPort* serialPort,
                                         QString portName,
                                         QSerialPort::BaudRate baudRate,
                                         QSerialPort::Direction directionPort,
                                         QSerialPort::DataBits dataLength,
                                         QSerialPort::Parity parityBit,
                                         QSerialPort::StopBits stopBits,
                                         QSerialPort::FlowControl flowControl,
                                         QIODevice::OpenModeFlag openMode)
{
    if(serialPort->isOpen())
        serialPort->close();

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate,directionPort);
    serialPort->setDataBits(dataLength);
    serialPort->setParity(parityBit);
    serialPort->setStopBits(stopBits);
    serialPort->setFlowControl(flowControl);

    if(serialPort->open(openMode)){
        qDebug() << "SerialClass----->serial port " << portName << " can open";
        return true;
    }
    else{
        qDebug() << "SerialClass----->serial port " << portName << " can  not open";
        qDebug() << "SerialClass----->serial Port error: " <<  serialPort->errorString();
        return false;
    }
}

void SerialClass::slot_serial_ReadPort1()
{
    if(!dbStatusConnection1)
        return;
    qDebug() << "SerialClass----->RS232_1";
    if(bInproc1){
        qDebug() << "SerialClass----->RS232_1 in proc";
        resetSerialPort1();
        return;
    }
    QByteArray buffer = serialPort_1->readAll();
    if(buffer.count() < 4 && (!bInSerial1)){
        resetSerialPort1();
        return;
    }
    buffer1.append(buffer);
    if((!bInSerial1) && (buffer1.count() >= 4) && (buffer1.at(0) == '4' && buffer1.at(1) == '0' && buffer1.at(2) == '0' && buffer1.at(3) == '1')){
       qDebug() << "SerialClass----->start identification message in RS232_1 (ttyS3)";
       bInSerial1 = true;
       timerSerial1->start(1000);
    }
    else if((buffer1.count() >= 4) && (buffer1.at(0) != '4' || buffer1.at(1) != '0' || buffer1.at(2) != '0' || buffer1.at(3) != '1')){
        qDebug() << "SerialClass----->invalid header in RS232_1";
        resetSerialPort1();
        return;
    }
    if(buffer1.count() < 16){
        return;
    }
    else if(buffer1.count() >= 16){
        QString length;
        length.clear();
        length.append(buffer1.at(14));
        length.append(buffer1.at(15));
        bool status = false;
        int epc_length = length.toUInt(&status,16);
        if(buffer1.count() < 16 + epc_length*2 + 2)
            return;
        if(buffer1.count() > 16 + epc_length*2 + 2){
            resetSerialPort1();
            return;
        }
        QByteArray epcData;
        epcData.clear();
        for(int i=0; i< buffer1.count() - 16; i++){
            epcData.append(buffer1.at(i + 16));
        }
        epcData = epcData.mid(0,epc_length * 2 + 2);
        if(epcData.count() == epc_length * 2 + 2){
            if(epcData.at(epc_length * 2) != 0x0D || epcData.at(epc_length * 2 + 1) != 0x0A){
                qDebug() << "SerialClass----->invalid data in RS232_1 ";
                resetSerialPort1();
                return;
            }
            QString epc = epcData.mid(0,epc_length*2);
            qDebug() << "SerialClass----->reset RS232_1 proc = true";
            emit this->signal_serial_GetNew_EPC_Data_port1(epc);
            bInproc1 = true;
            resetSerialPort1();
        }
        else
            return;
    }
}

void SerialClass::slot_serial_ReadPort2()
{
    if(!dbStatusConnection2)
        return;
    qDebug() << "SerialClass----->RS232_2";
    if(bInproc2){
        qDebug() << "SerialClass----->RS232_2 in proc";
        resetSerialPort2();
        return;
    }
    QByteArray buffer = serialPort_2->readAll();
    if(buffer.count() < 4 && (!bInSerial2)){
        resetSerialPort2();
        return;
    }
    buffer2.append(buffer);
    if((!bInSerial2) && (buffer2.count() >= 4) && (buffer2.at(0) == '4' && buffer2.at(1) == '0' && buffer2.at(2) == '0' && buffer2.at(3) == '1')){
       qDebug() << "SerialClass----->start identification message in RS232_2 (ttyS1)";
       bInSerial2 = true;
       timerSerial2->start(1000);
    }
    else if((buffer2.count() >= 4) && (buffer2.at(0) != '4' || buffer2.at(1) != '0' || buffer2.at(2) != '0' || buffer2.at(3) != '1')){
        qDebug() << "SerialClass----->invalid header in RS232_2";
        resetSerialPort2();
        return;
    }
    if(buffer2.count() < 16){
        return;
    }
    else if(buffer2.count() >= 16){
        QString length;
        length.clear();
        length.append(buffer2.at(14));
        length.append(buffer2.at(15));
        bool status = false;
        int epc_length = length.toUInt(&status,16);
        if(buffer2.count() < 16 + epc_length*2 + 2)
            return;
        if(buffer2.count() > 16 + epc_length*2 + 2){
            resetSerialPort2();
            return;
        }
        QByteArray epcData;
        epcData.clear();
        for(int i=0; i< buffer2.count() - 16; i++){
            epcData.append(buffer2.at(i + 16));
        }
        epcData = epcData.mid(0,epc_length * 2 + 2);
        if(epcData.count() == epc_length * 2 + 2){
            if(epcData.at(epc_length * 2) != 0x0D || epcData.at(epc_length * 2 + 1) != 0x0A){
                qDebug() << "SerialClass----->invalid data in RS232_2";
                resetSerialPort2();
                return;
            }
            QString epc = epcData.mid(0,epc_length*2);
            emit this->signal_serial_GetNew_EPC_Data_port2(epc);
            qDebug() << "SerialClass----->reset RS232_2 proc = true";
            bInproc2 = true;
            resetSerialPort2();
        }
        else
            return;
    }
}

void SerialClass::slot_serial_timeout1()
{
    qDebug() << "SerialClass----->timeout serial RS232_1";
    resetSerialPort1();
}

void SerialClass::slot_serial_timeout2()
{
    qDebug() << "SerialClass----->timeout serial RS232_2";
    resetSerialPort2();
}

void SerialClass::resetSerialPort1()
{
    qDebug() << "SerialClass----->reset RS232_1";
    buffer1.clear();
    timerSerial1->stop();
    bInSerial1 = false;
    serialPort_1->flush();
    serialPort_1->clear();
}

void SerialClass::resetSerialPort2()
{
    qDebug() << "SerialClass----->reset RS232_2";
    buffer2.clear();
    timerSerial2->stop();
    bInSerial2 = false;
    serialPort_2->flush();
    serialPort_2->clear();
}

void SerialClass::slot_serial_changeProcMode1(bool proc)
{
    qDebug() << "SerialClass----->reset RS232_1 proc = " << proc;
    bInproc1 = proc;
}

void SerialClass::slot_serial_changeProcMode2(bool proc)
{
    qDebug() << "SerialClass----->reset RS232_2 proc = " << proc;
    bInproc2 = proc;
}

void SerialClass::slot_serial_dbConnectionStatus1(bool status)
{
    dbStatusConnection1 = status;
}

void SerialClass::slot_serial_dbConnectionStatus2(bool status)
{
    dbStatusConnection2 = status;
}
