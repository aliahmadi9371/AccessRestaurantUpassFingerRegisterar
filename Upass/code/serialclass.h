#ifndef SERIALCLASS_H
#define SERIALCLASS_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSettings>
#include <QDataStream>

class SerialClass : public QObject
{
    Q_OBJECT
public:
    explicit SerialClass(QObject *parent = 0);

private:
    QSerialPort* serialPort_1;
    QString serialPort_1_path;
    bool bOpen1;
    QByteArray buffer1;
    bool bInSerial1;
    QTimer *timerSerial1;

    QSerialPort* serialPort_2;
    QString serialPort_2_path;
    bool bOpen2;
    QByteArray buffer2;
    bool bInSerial2;
    QTimer *timerSerial2;

    bool bInproc1;
    bool bInproc2;

    bool dbStatusConnection1;
    bool dbStatusConnection2;

    bool func_serial_openSerial(QSerialPort* serialPort,
                                QString portName, QSerialPort::BaudRate baudRate, QSerialPort::Direction directionPort,
                                QSerialPort::DataBits dataLength, QSerialPort::Parity parityBit, QSerialPort::StopBits stopBits,
                                QSerialPort::FlowControl flowControl, QIODevice::OpenModeFlag openMode);
    void func_serial_configClass(QString iniPath);
    void resetSerialPort1();
    void resetSerialPort2();

signals:
    void signal_serial_StartThread();
    void signal_serial_StopThread();

    void signal_serial_GetNew_EPC_Data_port1(QString epcdata);
    void signal_serial_GetNew_EPC_Data_port2(QString epcdata);

public slots:

private slots:
    void slot_serial_StartThread();
    void slot_serial_StopThread();

    void slot_serial_ReadPort1();
    void slot_serial_ReadPort2();

    void slot_serial_timeout1();
    void slot_serial_timeout2();

    void slot_serial_changeProcMode1(bool proc);
    void slot_serial_changeProcMode2(bool proc);

    void slot_serial_dbConnectionStatus1(bool status);
    void slot_serial_dbConnectionStatus2(bool status);
};

#endif // SERIALCLASS_H
