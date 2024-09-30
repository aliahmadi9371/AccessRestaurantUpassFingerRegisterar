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

#include "globals.h"

class UserManagement : public QObject
{
    Q_OBJECT
public:
    explicit UserManagement(QObject *parent = nullptr);

private:
    void ConfigThread();
    QString LoadQuery(QString sFilename);
    

    
    QSqlDatabase *db_sql;
    QString sDbConnectionNameSql;
    QString sDbHostSql;
    QString sDBNameSql;
    QString sDbUserSql;
    QString sDbPassSql;
    int iDbPortSql;
    bool bDbopened_Sql;

    QSqlDatabase *db_mysql;
    QString sDbConnectionNameMysql;
    QString sDbHostMysql;
    QString sDBNameMysql;
    QString sDbUserMysql;
    QString sDbPassMysql;
    int iDbPortMysql;

    bool bDbopened_MySql;

    QTimer *tCheckDb;
    int iTimeout;

    QString sCMD_DeleteALL;
    int iCMD_deleteAllCount;
    QString sCMD_AddUser;
    int iCMD_addCount;
    QString sCMD_DelUser;
    int iCMD_delCount;
    

    int currentUserId;
    int currentUserIdMaster;
    QString sdb_Access;
    QString sdb_Rest;

    int DeviceId;


    bool netCable;

signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();

    void sig_tomain_cmd_delall(quint32 TerminalID);
    void sig_tomain_cmd_del(quint32 TerminalID,quint32 UserId);
    void sig_tomain_cmd_add(quint32 TerminalID,quint32 UserId, QString PersonnelCode,QString TextFir,QString CardCSN,bool isAdmin,
                            int isYear,int isMonth,int isDay,
                            int ieYear,int ieMonth,int ieDay);

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

    void slot_fromsocket_cmd_add_master(QString message);
    void slot_fromsocket_cmd_del_master(QString message);

    void slot_frommain_resp_deleteall(bool ok, int error, quint32 UCS_terminalID);
    void slot_frommain_resp_delete(quint32 UserId, bool ok, int error, quint32 UCS_terminalID);
    void slot_frommain_resp_add(quint32 UserID, bool ok, int error, quint32 UCS_terminalID);

    void slot_fromuser_savecmd(int type,bool ok,int error,quint32 UCS_terminalID,int userId);
    void slot_user_acctionadd(int result,int terminalId,int userId);
    void slot_user_acctiondel(int result,int terminalId,int userId);

    void slot_user_acctionadd_master(int result,int terminalId,int userId);
    void slot_user_acctiondel_master(int result,int terminalId,int userId);

    void slot_user_netCable(bool status);


};

#endif // USERMANAGEMENT_H
