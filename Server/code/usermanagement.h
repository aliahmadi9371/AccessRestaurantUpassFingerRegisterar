#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QFile>
#include <QDir>

//#include <winsock.h> //critical
// //UCS SDK
//#include "UCSAPI.h"
//#include "UCSAPI_Basic.h"
//#include "UCSAPI_Error.h"
//#include "UCSAPI_Type.h"

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

class UserManagement : public QObject
{
    Q_OBJECT
public:
    explicit UserManagement(QObject *parent = nullptr);
    bool bDbopened;

private:
    void ConfigThread();
    QString LoadQuery(QString sFilename);
    

    
    QSqlDatabase *db;
    QString sDbConnectionName;
    QString sDbHost;
    QString sDBName;
    QString sDbUser;
    QString sDbPass;
    int iDbPort;
    int iTimeout;

    QString sCMD_DeleteALL;
    int iCMD_deleteAllCount;
    QString sCMD_AddUser;
    int iCMD_addCount;
    QString sCMD_DelUser;
    int iCMD_delCount;
    

    int currentUserId;

    QTimer *tCheckDb;

signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();
    void sig_DB_Open(bool open);

    void sig_tomain_cmd_delall(quint32 TerminalID);
    void sig_tomain_cmd_del(quint32 TerminalID,quint32 UserId);
    void sig_tomain_cmd_add(quint32 TerminalID,quint32 UserId,QString PersonnelCode,QString TextFir,QString CardCSN,int isYear,int isMonth, int isDay, int ieYear, int ieMonth, int ieDay, QString groupCode,bool isAdmin, int add_inactive);

    void invaid_cmd();
    void sig_user_finishedCMD();

    void sig_user_savecmd(int type,bool ok,int error,quint32 UCS_terminalID,int userId);
    void sig_user_acctionadd(int result,int terminalId,int userId);
    void sig_user_acctiondel(int result,int terminalId,int userId);
     
public slots:
    
private slots:
    void slot_Start_User_Thread();
    void slot_Stop_User_Thread();
    
    void slot_check_database();

    void slot_fromsocket_cmd_add(QString message);
    void slot_fromsocket_cmd_del(QString message);
    void slot_fromsocket_cmd_delall(QString message);

    void slot_frommain_resp_deleteall(bool ok, int error, quint32 UCS_terminalID);
    void slot_frommain_resp_delete(quint32 UserId, bool ok, int error, quint32 UCS_terminalID);
    void slot_frommain_resp_add(quint32 UserID, bool ok, int error, quint32 UCS_terminalID, int addinactive);

    void slot_fromuser_savecmd(int type,bool ok,int error,quint32 UCS_terminalID,int userId);
    void slot_user_acctionadd(int result,int terminalId,int userId);
    void slot_user_acctiondel(int result,int terminalId,int userId);

};

#endif // USERMANAGEMENT_H
