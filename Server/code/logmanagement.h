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


#include <winsock.h> //critical
// //UCS SDK
//#include "UCSAPI.h"
//#include "UCSAPI_Basic.h"
//#include "UCSAPI_Error.h"
#include "UCSAPI_Type.h"

// //UCBio SDK
//#include "UCBioAPI.h"
//#include "UCBioAPI_Basic.h"
//#include "UCBioAPI_DeviceEx.h"
//#include "UCBioAPI_Error.h"
//#include "UCBioAPI_Export.h"
//#include "UCBioAPI_ExportType.h"
//#include "UCBioAPI_Extension.h"
//#include "UCBioAPI_FastSearch.h"
//#include "UCBioAPI_FastSearchType.h"
//#include "UCBioAPI_SmartCard.h"
//#include "UCBioAPI_SmartCardType.h"
//#include "UCBioAPI_Type.h"

class LogManagement : public QObject
{
    Q_OBJECT
public:
    explicit LogManagement(QObject *parent = nullptr);
    QNetworkAccessManager* manager;
    QNetworkRequest* request;
    bool bDbopened;

private:
    void ConfigThread();



    
    QSqlDatabase *db;
    QString sDbConnectionName;
    QString sDbHost;
    QString sDBName;
    QString sDbUser;
    QString sDbPass;
    int iDbPort;
    int iTimeout;

    QString swebLogURL;

    QTimer *tCheckDb;

    QList<quint32> FirstTerminalList;

    QString rfid_auto;
    QString rfid_get;



    QString LoadQuery(QString sFilename);






    //int foo(int p);

signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();
    void sig_DB_Open(bool open);
    void sig_log_insertAccess(quint32 quiTerminalId,quint32 length,QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void sig_log_sendtocoket(quint32 quiTerminalId,quint32 length,QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes,bool isOnline);

private slots:
    void slot_Start_Log_Thread();
    void slot_Stop_Log_Thread();
    void slot_check_database();

    //void slot_frommain_firstconnections(quint32 UCS_terminalId);
    void slot_frommain_RealTimeLog(quint32 quiTerminalId, quint32 qui_RFID_length, BYTE *RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void slot_frommain_GetLog(quint32 quiTerminalId, quint32 qui_RFID_length, BYTE *RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void slot_frommain_TerminalStatus(quint32 quiTerminalId, quint32 Door, quint32 Lock, quint32 Open, quint32 Cover, quint32 Terminal);

    void slot_fromlog_insertAccess(quint32 quiTerminalId,quint32 length,QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes);
    void slot_fromlog_sendtosocket(quint32 quiTerminalId, quint32 length, QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes, bool isOnline);
};

#endif // LOGMANAGEMENT_H
