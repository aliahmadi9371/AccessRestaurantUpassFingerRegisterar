#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QCoreApplication>
#include "globals.h"

class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(QObject *parent = nullptr);
    QTimer* tCheckSys;


private:
    void ConfigThread();
    QString LoadQuery(QString sFilename);

    void check_Timezone();
    void check_Holiday();
    void check_Acess();
    void check_Groupe();

    void check_User();
    void check_Master();

    QString sSocketServerURL;
    int iWebSocketPort;
    
    QString sCMD_DeleteALL;
    QString sCMD_AddUser;
    QString sCMD_DelUser;
    int i_DeviceId;

    QString sCMD_AddTimezone;
    QString sCMD_AddHol;
    QString sCMD_AddAccess;
    QString sCMD_AddGroup;


    bool b_ws_inproc;
    bool bconnected;


    bool blog_ws;
    bool bcmd_ws;

    QString sdb_Access;
    QString sdb_Rest;

    QString sDbConnectionNameSql;
    QString sDbHostSql;
    QString sDBNameSql;
    QString sDbUserSql;
    QString sDbPassSql;
    int iDbPortSql;

    int DeviceId;

    int iTimeout;
    bool net;
    bool virdi;

    QString sDbConnectionNameMysql;
    QString sDbHostMysql;
    QString sDBNameMysql;
    QString sDbUserMysql;
    QString sDbPassMysql;
    int iDbPortMysql;
    int iTimeoutMysql;


    QTimer* tCheckDb;


    QSqlDatabase *db_sql;
    QSqlDatabase *db_mysql;

    bool bDbopened_sql;
    bool bDbopened_mysql;
    bool netCable;

signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();

    void sig_isConnected(bool connected);
    
    void sig_touser_cmd_add(QString message);
    void sig_touser_cmd_del(QString message);

    void sig_touser_cmd_add_master(QString message);
    void sig_touser_cmd_del_master(QString message);

    void sig_touser_cmd_delall(QString message);

    void sig_toterminal_timezone(QString message);
    void sig_toterminal_holiday(QString message);
    void sig_toterminal_accesstime(QString message);
    void sig_toterminal_accessgroup(QString message);

    void textMessageReceived(QString message);
    void textMessageReceivedMaster(QString message);


    

public slots:

private slots:
    void slot_Start_WS_Thread();
    void slot_Stop_WS_Thread();

    void slot_check_database();


    void cmd_processTextMessage(QString message);
    void cmd_processTextMessageMaster(QString message);

    void slot_fromuser_invalid();
    void sig_user_finishedCMD();


    void slot_checksys_SendAll_oneByone();
    void slot_socket_chechkNet(bool status);
    void slot_socket_chechkVirdi(bool status);

    void slot_socket_netCable(bool status);

};

#endif // WEBSOCKET_H
