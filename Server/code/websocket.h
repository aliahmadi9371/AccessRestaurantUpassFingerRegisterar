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


class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(QObject *parent = nullptr);
    QTimer* tCheckSys;

    bool bDbopened;


private:
    void ConfigThread();
    QString LoadQuery(QString sFilename);

    void check_Timezone();
    void check_Holiday();
    void check_Acess();
    void check_Groupe();

    void check_User();

    QString sSocketServerURL;
    int iWebSocketPort;
    
    QString sCMD_DeleteALL;
    QString sCMD_AddUser;
    QString sCMD_DelUser;
    QString sCMD_AddTimezone;
    QString sCMD_AddHol;
    QString sCMD_AddAccess;
    QString sCMD_AddGroup;


    bool b_ws_inproc;
    bool bconnected;


    bool blog_ws;
    bool bcmd_ws;


    QString sDbConnectionName;
    QString sDbHost;
    QString sDBName;
    QString sDbUser;
    QString sDbPass;
    int iDbPort;

    QTimer* tCheckDb;


    QSqlDatabase *db;
    QSqlDatabase *db_try;
    int iTimeout;


signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();

    void sig_isConnected(bool connected);
    
    void sig_touser_cmd_add(QString message);
    void sig_touser_cmd_del(QString message);
    void sig_touser_cmd_delall(QString message);

    void sig_toterminal_timezone(QString message);
    void sig_toterminal_holiday(QString message);
    void sig_toterminal_accesstime(QString message);
    void sig_toterminal_accessgroup(QString message);

    void textMessageReceived(QString);


    

public slots:

private slots:
    void slot_Start_WS_Thread();
    void slot_Stop_WS_Thread();

    void slot_check_database();


    void cmd_processTextMessage(QString message);

    void slot_fromuser_invalid();
    void sig_user_finishedCMD();


    void slot_checksys_SendAll_oneByone();

};

#endif // WEBSOCKET_H
