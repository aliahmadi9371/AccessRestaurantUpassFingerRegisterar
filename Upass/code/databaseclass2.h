#ifndef DATABASECLASS2_H
#define DATABASECLASS2_H


#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QSettings>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

class DatabaseClass2 : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseClass2(QObject *parent = 0);
    bool    b_db_isOpen;
    void func_db_OpenDb();
private:
    //params
    QSqlDatabase *db;
    QString str_db_ConnectionName;
    QString str_db_DatabaseName;
    QString str_db_HostName;
    QString str_db_UserName;
    QString str_db_PassWord;
    int     i_db_Port;

    QTimer  *tm_db_checkDb;
    int     i_db_checkTimeSec;

    int i_db_TerminalId_2;

    QNetworkAccessManager *nam_db_NetworkManager;
    QNetworkReply *nr_db_NetworkReply;
    QTimer *t_db_WebTimeout;
    int i_db_WebTimeout;
    QString str_db_LogUrl;
    bool b_db_WebResp;
    bool b_db_WebSuccess;


    //functions
    void func_db_configClass();
    void func_db_checkTag2(QString tagnumber);
    bool func_db_SendLogWeb(int TagCount,QString TagNumber, bool isUser,int UserId ,int error);
    QString func_db_SetLogString(int TagCount,QString TagNumber, bool isUser,int UserId ,int error);
    void func_db_InsertAccess(QString TagNumber,int UserId ,int error);
    int func_db_CheckifUser(QString TagNumber);
    bool func_db_CheckifPermission(QString TagNumber);
    QString func_db_LoadQuery(QString sFilePath);



signals:
    void signal_db_StartThread();

    void signal_db_StopThread();

    void signal_db_changeProgStatus2(bool proc);

    void signal_db_success2();

    void signal_db_databaseConnection2(bool status);


public slots:
private slots:
    void slot_db_StartThread();

    void slot_db_StopThread();

    void slot_db_CheckDatabase();

    void slot_db_GetNew_EPC_Data_port2(QString epcData);

    void slot_db_WebReply(QNetworkReply *reply);
    void slot_db_WebTimeout();

    void testSlot();
};

#endif // DATABASECLASS2_H
