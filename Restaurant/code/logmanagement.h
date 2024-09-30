#ifndef LOGMANAGEMENT_H
#define LOGMANAGEMENT_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QVariant>

#include "qdateconvertor.h"
#include "globals.h"


#include <winsock.h> //critical
//#include "UCBioAPI_Type.h"

class LogManagement : public QObject
{
    Q_OBJECT
public:
    explicit LogManagement(QObject *parent = nullptr);
//    QNetworkAccessManager* manager;
//    QNetworkRequest* request;
    int time;

private:
    void ConfigThread();


    QPrinter *printer;

    QTimer *timerOnline;

    QTimer *testTimer;

    QString sdb_Access;
    QString sdb_Rest;

    
    QSqlDatabase *db_mysql;
    QString sDbConnectionNameMysql;
    QString sDbHostMysql;
    QString sDBNameMysql;
    QString sDbUserMysql;
    QString sDbPassMysql;
    int iDbPortMysql;
    bool bDbopened_MySql;

    QSqlDatabase *db_sql;
    QString sDbConnectionNameSql;
    QString sDbHostSql;
    QString sDBNameSql;
    QString sDbUserSql;
    QString sDbPassSql;
    int iDbPortSql;
    bool bDbopened_sql;

    int DeviceId;
    int RestaurantId;

    int iTimeout;

    QString swebLogURL;

    QTimer *tCheckDb;

    QList<quint32> FirstTerminalList;

    QString rfid_auto;
    QString rfid_get;



    QString LoadQuery(QString sFilename);


    void PrintReceipt(QString PersonalID, QString Explaned, QString foodName, QString Kind, QString Name);

    bool func_log_checkPermistion(QString PersonnelCode, quint64 PersonnelId);

    bool net;
    bool virdi;

    bool netCable;

    void func_log_openprinter();

    void func_log_GetMasterFood(quint32 quiTerminalId, quint32 length, QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    QList<QString> func_log_GetTodayFood();

    //int RestaurantId;

    void func_log_logtoDatabase(QString PersonnelName, int FoodId, QString FoodName, int reservationId, int foodStatus, bool bCardFinger, quint32 qui_AuthRes, QString CardNumber);


    //int foo(int p);

signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();
    void sig_DB_Open(bool open);
    void sig_log_insertAccess(quint32 quiTerminalId,quint32 length,QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void sig_log_onlineTerminal(bool status);
    void sig_log_UserLog(int foodStatus,bool user,quint32 PersonnelId,int foodNumber,QString foodName,QString Name,QString PersonelCode);
    void sig_log_SendFoodCount(int foodType);

private slots:
    void slot_Start_Log_Thread();
    void slot_Stop_Log_Thread();
    void slot_check_database();
    void slot_frommain_RealTimeLog(quint32 quiTerminalId, quint32 qui_RFID_length, BYTE *RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void slot_frommain_TerminalStatus(quint32 quiTerminalId);
    void slot_fromlog_insertAccess(quint32 quiTerminalId,quint32 length,QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void setTime();
    void slot_log_chechkNet(bool status);
    void slot_log_chechkVirdi(bool status);

    void slot_log_netCable(bool status);

    void slot_log_testTimerTimeout();


};

#endif // LOGMANAGEMENT_H
