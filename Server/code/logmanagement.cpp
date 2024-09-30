#include "logmanagement.h"
#include <QApplication>

LogManagement::LogManagement(QObject *parent) : QObject(parent)
{

}

//functions

void LogManagement::ConfigThread()
{
    manager = new QNetworkAccessManager(this);
    request = new QNetworkRequest;

    tCheckDb = new QTimer(this);
    tCheckDb->setSingleShot(false);
    connect(tCheckDb,SIGNAL(timeout()),this,SLOT(slot_check_database()),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_log_insertAccess(quint32,quint32,QString,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            this,SLOT(slot_fromlog_insertAccess(quint32,quint32,QString,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_log_sendtocoket(quint32,quint32,QString,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool,bool)),
            this,SLOT(slot_fromlog_sendtosocket(quint32,quint32,QString,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool,bool)),Qt::QueuedConnection);
    FirstTerminalList.clear();

    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");

    FirstTerminalList.clear();

    sDbConnectionName = setting.value("Database/db_connection_log","log").toString();
    sDbHost = setting.value("Database/db_host","192.168.1.14").toString();
    iDbPort = setting.value("Database/db_port",8080).toInt();
    sDBName = setting.value("Database/db_name","saipa").toString();
    sDbUser = setting.value("Database/db_user","sa").toString();
    sDbPass = setting.value("Database/db_pass","123456").toString();

    iTimeout = setting.value("Database/db_timeout",5).toInt();

    swebLogURL = setting.value("WebLog/url","").toString();

    //
}


//slots

//sig_Start_Thread
void LogManagement::slot_Start_Log_Thread()
{
    qDebug() << "LG:start log thread worker";
    ConfigThread();



    db = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionName));
    QString sName = QString("DRIVER={SQL Server};SERVER=%1;Database=%2").arg(sDbHost).arg(sDBName);
    db->setDatabaseName(sName);
    db->setUserName(sDbUser);
    db->setPassword(sDbPass);
    db->setPort(iDbPort);


    if(db->open()){
        bDbopened = true;
        qDebug() << "LG: can Open DataBase";
    }
    else{
        bDbopened = false;
        qDebug() << "LG:" << db->lastError();
        QApplication::quit();
    }

    tCheckDb->start(iTimeout * 1000);
    emit this->sig_DB_Open(bDbopened);
}

//sig_Stop_Thread
void LogManagement::slot_Stop_Log_Thread()
{
    if(db->isOpen())
        db->close();
    this->deleteLater();
}

//void LogManagement::slot_frommain_firstconnections(quint32 uiterminalId)
//{
//    //qDebug() << "first connection of terminal id: " << uiterminalId;
//    for (int i=0; i<FirstTerminalList.count(); i++){
//        if(FirstTerminalList.at(i) == uiterminalId)
//            return;
//    }
//    FirstTerminalList.append(uiterminalId);

//}

void LogManagement::slot_check_database()
{
    //slot_fromlog_insertAccess(6,"'12345678'",4536 , 1, 1, 2019, 5, 5, 24, 0, 0, 1,0);
    //slot_frommain_TerminalStatus(6,0,0,0,0,0);
    if(db->isOpen()){
        bDbopened = true;
    }
    else{
        if(db->open()){
            bDbopened = true;
            qDebug() << "LG: can Open DataBase";
        }
        else{
            bDbopened = false;
            QApplication::quit();
        }
    }
    emit this->sig_DB_Open(bDbopened);
}

void LogManagement::slot_frommain_RealTimeLog(quint32 quiTerminalId,quint32 qui_RFID_length,BYTE* RFID_data,quint32 qui_UserID,quint8 qui_AuthMode,quint8 qui_AuthType,
                                              quint16 qui_Year,quint8 qui_Month,quint8 qui_Day,quint8 qui_Hour,quint8 qui_Min,quint8 qui_Sec,quint32 qui_AuthRes,bool bRes)
{

    QString rfid;
    rfid.clear();
    for(int i=0; i<static_cast<int>(qui_RFID_length); i++){
       rfid.append(RFID_data[i]);
    }
//    qDebug() << "rfid: " << rfid;
//    qDebug() << "qUserID: " << qui_UserID;
//    qDebug() << "AuthMode: " << qui_AuthMode;
//    qDebug() << "AuthType: " << qui_AuthType;
//    qDebug() << "DateTime:" << qui_Year << "/" << qui_Month << "/" << qui_Day << "_" << qui_Hour << ":" << qui_Min << ":" << qui_Sec;
//    qDebug() << "AuthRes: " << qui_AuthRes;
//    qDebug() << "is Auth: " << bRes;

    qDebug() << "LG:log management thread: auto log from terminal id: " << quiTerminalId;

    rfid_auto.clear();
    rfid_auto = rfid;

    emit this->sig_log_insertAccess(quiTerminalId,qui_RFID_length,rfid_auto,qui_UserID,qui_AuthMode,qui_AuthType,qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes);
    emit this->sig_log_sendtocoket(quiTerminalId,qui_RFID_length,rfid_auto,qui_UserID,qui_AuthMode,qui_AuthType,qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes,true);
    return;
}

void LogManagement::slot_frommain_GetLog(quint32 quiTerminalId,quint32 qui_RFID_length,BYTE* RFID_data,quint32 qui_UserID,quint8 qui_AuthMode,quint8 qui_AuthType,
                                         quint16 qui_Year,quint8 qui_Month,quint8 qui_Day,quint8 qui_Hour,quint8 qui_Min,quint8 qui_Sec,quint32 qui_AuthRes,bool bRes)
{
    QString rfid;
    rfid.clear();
    for(int i=0; i<static_cast<int>(qui_RFID_length); i++){
       rfid.append(RFID_data[i]);
    }

//    qDebug() << "rfid: " << rfid;
//    qDebug() << "qUserID: " << qui_UserID;
//    qDebug() << "AuthMode: " << qui_AuthMode;
//    qDebug() << "AuthType: " << qui_AuthType;
//    qDebug() << "DateTime:" << qui_Year << "/" << qui_Month << "/" << qui_Day << "_" << qui_Hour << ":" << qui_Min << ":" << qui_Sec;
//    qDebug() << "AuthRes: " << qui_AuthRes;
//    qDebug() << "is Auth: " << bRes;

    qDebug() << "LG:log management thread: get log from terminal id: " << quiTerminalId;

    rfid_get.clear();
    rfid_get = rfid;

    emit this->sig_log_insertAccess(quiTerminalId,qui_RFID_length,rfid_get,qui_UserID,qui_AuthMode,qui_AuthType,qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes);
    emit this->sig_log_sendtocoket(quiTerminalId,qui_RFID_length,rfid_get,qui_UserID,qui_AuthMode,qui_AuthType,qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes,false);
    return;

}

//main sig_main_getTerminalStatus
void LogManagement::slot_frommain_TerminalStatus(quint32 quiTerminalId,quint32 Door,quint32 Lock,quint32 Open,quint32 Cover,quint32 Terminal)
{
    qDebug() << "LG:log management thread: terminal Status update from terminal id: " << quiTerminalId;
    //qDebug() << foo(0);
    QDir dir;

    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertStatus.dll");
    squery = squery.arg(QString::number(quiTerminalId));
    squery = squery.arg(QString::number(Terminal));
    squery = squery.arg(QString::number(Door));
    squery = squery.arg(QString::number(Cover));
    squery = squery.arg(QString::number(Lock));
    squery = squery.arg(QString::number(Open));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "LG:query error terminal status: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "LG: can Open DataBase";
        }
    }
    return;
}

//log sig_log_insertAccess
void LogManagement::slot_fromlog_insertAccess(quint32 quiTerminalId, quint32 length, QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes)
{
//    qDebug() << "rfid: " << RFID_data;
//    qDebug() << "rfid length: " <<  length;
//    qDebug() << "qUserID: " << qui_UserID;
//    qDebug() << "AuthMode: " << qui_AuthMode;
//    qDebug() << "AuthType: " << qui_AuthType;
//    qDebug() << "DateTime:" << qui_Year << "/" << qui_Month << "/" << qui_Day << "_" << qui_Hour << ":" << qui_Min << ":" << qui_Sec;
//    qDebug() << "AuthRes: " << qui_AuthRes;
//    qDebug() << "is Auth: " << bRes;


    //qDebug() << "access result: " << bRes;
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcess.dll");
    if(bRes || (qui_AuthRes == UCSAPI_AUTH_PERMISSION))
        squery = squery.arg(QString::number(qui_UserID));
    else
        squery = squery.arg("NULL");
    squery = squery.arg(QString::number(quiTerminalId));
    if(length == 0)
        squery = squery.arg("NULL");
    else{
        squery = squery.arg("'" + RFID_data + "'");
    }
    squery = squery.arg(QString::number(qui_AuthMode));
    squery = squery.arg(QString::number(qui_AuthType));
    squery = squery.arg(QString::number(qui_Year));
    squery = squery.arg(QString::number(qui_Month));
    squery = squery.arg(QString::number(qui_Day));
    squery = squery.arg(QString::number(qui_Hour));
    squery = squery.arg(QString::number(qui_Min));
    squery = squery.arg(QString::number(qui_Sec));
    squery = squery.arg(QString::number(qui_AuthRes));
    if(bRes)
        squery = squery.arg("1");
    else
        squery = squery.arg("0");
    //qDebug() << squery;
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "LG:query error log access: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "LG: can Open DataBase";
        }
    }
    return;
}

void LogManagement::slot_fromlog_sendtosocket(quint32 quiTerminalId, quint32 length, QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes,bool isOnline)
{
    QString slog_socket;
    slog_socket.clear();
    //header
    slog_socket = "LOG";
    slog_socket.append(":");

    //terminal id
    slog_socket.append(QString("%1").arg(quiTerminalId, 4, 10, QChar('0')));
    slog_socket.append(":");

    //rfid or uhf length
    slog_socket.append(QString("%1").arg(length, 2, 10, QChar('0')));
    slog_socket.append(":");

    //rfid ot uhf tag
    if(length != 0)
        slog_socket.append(RFID_data);
    slog_socket.append(":");

    //user id
    if(bRes || (qui_AuthRes == UCSAPI_AUTH_PERMISSION)){
        //qDebug() << "valid user id";
        slog_socket.append(QString("%1").arg(qui_UserID, 8, 10, QChar('0')));
    }
    else{
        //qDebug() << "invalid user id";
        slog_socket.append(QString("%1").arg(0, 8, 10, QChar('0')));
    }
    slog_socket.append(":");

    //auth mode
    slog_socket.append(QString("%1").arg(qui_AuthMode, 2, 10, QChar('0')));
    slog_socket.append(":");

    //auth type
    slog_socket.append(QString("%1").arg(qui_AuthType, 2, 10, QChar('0')));
    slog_socket.append(":");

    //date time
    slog_socket.append(QString("%1").arg(qui_Year, 4, 10, QChar('0')));
    slog_socket.append(QString("%1").arg(qui_Month, 2, 10, QChar('0')));
    slog_socket.append(QString("%1").arg(qui_Day, 2, 10, QChar('0')));
    slog_socket.append(QString("%1").arg(qui_Hour, 2, 10, QChar('0')));
    slog_socket.append(QString("%1").arg(qui_Min, 2, 10, QChar('0')));
    slog_socket.append(QString("%1").arg(qui_Sec, 2, 10, QChar('0')));
    slog_socket.append(":");

    //auth error
    slog_socket.append(QString("%1").arg(qui_AuthRes, 2, 10, QChar('0')));
    slog_socket.append(":");

    //is auth
    if(bRes)
        slog_socket.append("1");
    else
        slog_socket.append("0");
    slog_socket.append(":");

    //is online
    if(isOnline)
        slog_socket.append("1");
    else
        slog_socket.append("0");
    slog_socket.append(":");


    slog_socket.append("END");
    qDebug() << "send log to socket";
    qDebug() << "LG:" << slog_socket;




    request->setUrl(QUrl(swebLogURL+slog_socket));
    qDebug() << swebLogURL+slog_socket;
    manager->get(*request);
    return;
}

QString LogManagement::LoadQuery(QString sFilename)
{
    QString squery;
    QFile scriptFile(sFilename);
    if (scriptFile.open(QIODevice::ReadOnly))
    {
        squery = QString(scriptFile.readAll());
        scriptFile.close();
        return squery;
    }
    else{
        return "";
    }
}

//int LogManagement::foo(int p) {
//    return foo(p)+foo(p);
//}


