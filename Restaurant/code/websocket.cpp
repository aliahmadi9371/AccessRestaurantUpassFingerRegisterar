#include "websocket.h"

WebSocket::WebSocket(QObject *parent) : QObject(parent)
{

}

void WebSocket::ConfigThread()
{
    tCheckDb = new QTimer(this);
    tCheckDb->setSingleShot(false);
    connect(tCheckDb,SIGNAL(timeout()),
            this,SLOT(slot_check_database()),
            Qt::QueuedConnection);


    tCheckSys = new QTimer(this);
    tCheckSys->setSingleShot(true);
    connect(tCheckSys,SIGNAL(timeout()),
            this,SLOT(slot_checksys_SendAll_oneByone()),
            Qt::QueuedConnection);

    //chech users each 2 minutes


    tCheckSys->start(2 * 60 * 1000);


    //tCheckSys->start(20 * 1000);

    b_ws_inproc = false;

    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    
    sSocketServerURL = setting.value("WebSocket/websocket_url","ws://127.0.0.1:8080").toString();
    
    sCMD_AddUser = setting.value("WebSocket/websocket_cmd_adduser","CMD:AddUserId:").toString();
    sCMD_DelUser = setting.value("WebSocket/websocket_cmd_deluser","CMD:DelUserId:").toString();
    sCMD_DeleteALL = setting.value("WebSocket/websocket_cmd_deletall","CMD:DeleteAllUsers:").toString();
    i_DeviceId = setting.value("Main/device_id",0).toInt();

    //sCMD_AddTimezone = setting.value("WebSocket/websocket_cmd_addtimezone","CMD:AddTimezoneData:").toString();
    //sCMD_AddHol = setting.value("WebSocket/websocket_cmd_addhol","CMD:AddHolidayData:").toString();
    //sCMD_AddAccess = setting.value("WebSocket/websocket_cmd_addaccess","CMD:AddAccessTimesData:").toString();
    //sCMD_AddGroup = setting.value("WebSocket/websocket_cmd_addgroup","CMD:AddAccessGroupData:").toString();

    sDbConnectionNameMysql = setting.value("MySql/db_connection_socket","").toString();
    sDbHostMysql = setting.value("MySql/db_host","").toString();
    iDbPortMysql = setting.value("MySql/db_port",0).toInt();
    sDBNameMysql = setting.value("MySql/db_name","").toString();
    sDbUserMysql = setting.value("MySql/db_user","").toString();
    sDbPassMysql = setting.value("MySql/db_pass","").toString();

    sdb_Access = setting.value("DbNames/access","saipa").toString();
    sdb_Rest = setting.value("DbNames/rest","restaurant").toString();

    sDbConnectionNameSql = setting.value("SqlServer/db_connection_socket","").toString();
    sDbHostSql = setting.value("SqlServer/db_host","").toString();
    iDbPortSql = setting.value("SqlServer/db_port",0).toInt();
    sDBNameSql = setting.value("SqlServer/db_name","").toString();
    sDbUserSql = setting.value("SqlServer/db_user","").toString();
    sDbPassSql = setting.value("SqlServer/db_pass","").toString();

    iTimeout = setting.value("Main/db_timeout",5).toInt();

    DeviceId = 0;
    DeviceId = setting.value("Main/device_id",0).toInt();

    connect(this,SIGNAL(textMessageReceived(QString)),
            this, SLOT(cmd_processTextMessage(QString)),
            Qt::QueuedConnection);

    connect(this,SIGNAL(textMessageReceivedMaster(QString)),
            this, SLOT(cmd_processTextMessageMaster(QString)),
            Qt::QueuedConnection);

    net = false;
    virdi = false;

}

//slots

//socket sig_Start_Thread
void WebSocket::slot_Start_WS_Thread()
{
    qDebug() << "WS_THREAD:start socket thread worker";
    ConfigThread();

    blog_ws = false;
    bcmd_ws = false;

    netCable = false;
    bDbopened_sql = false;
    bDbopened_mysql = false;

    db_sql = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionNameSql));
    QString sName = QString(s_connection).arg(sDbHostSql).arg(sDBNameSql);
    db_sql->setDatabaseName(sName);
    db_sql->setUserName(sDbUserSql);
    db_sql->setPassword(sDbPassSql);
    db_sql->setPort(iDbPortSql);
    db_sql->setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=1,SQL_ATTR_LOGIN_TIMEOUT=1;");


    db_mysql = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL",sDbConnectionNameMysql));
    db_mysql->setDatabaseName(sDBNameMysql);
    db_mysql->setUserName(sDbUserMysql);
    db_mysql->setPassword(sDbPassMysql);
    db_mysql->setPort(iDbPortMysql);
    db_mysql->setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");



//    if(netCable){
//        qDebug() << "WS_THREAD: cable ok";
//        if(db_sql->open()){
//            bDbopened_sql = true;
//            qDebug() << "WS_THREAD:cable ok---------->sql server connection open";
//        }
//        else{
//            bDbopened_sql = false;
//            qDebug() << "WS_THREAD:cable ok---------->sql server connection error - " << db_sql->lastError().text();
//        }
//    }

    tCheckDb->start(iTimeout * 1000);

}

//tCheckDb_sql->timeout
void WebSocket::slot_check_database()
{
    qDebug() << "WS_THREAD:check db";
    if(bDbopened_sql == true){
        QString stestQuery("SELECT TOP 1 * FROM serv_restaurant_log");
        QSqlQuery query(*db_sql);
        if(!query.exec(stestQuery) && bDbopened_sql){
            qDebug() << "WS_THREAD:---------->sql server connection error - " << query.lastError().text();
            db_sql->close();
            if(db_sql->open()){
                bDbopened_sql = true;
                qDebug() << "WS_THREAD:cable ok---------->sql server connection open";
            }
            else{
                bDbopened_sql = false;
                qDebug() << "WS_THREAD:cable ok---------->sql server connection error - " << db_sql->lastError().text();
            }
        }
    }
    else{
        if(netCable){
            qDebug() << "WS_THREAD: cable ok";
            if(db_sql->open()){
                bDbopened_sql = true;
                qDebug() << "WS_THREAD:cable ok---------->sql server connection open";
            }
            else{
                bDbopened_sql = false;
                qDebug() << "WS_THREAD:cable ok---------->sql server connection error - " << db_sql->lastError().text();
            }
        }
    }


    if(bDbopened_mysql == true){
        QString stestQuery("SELECT * FROM rest_userlogs LIMIT 1");
        QSqlQuery query(*db_mysql);
        if(!query.exec(stestQuery)){
            qDebug() << "WS_THREAD:---------->mysql connection error - " << db_mysql->lastError().text();
        }
    }
    else{
        if(db_mysql->open()){
            bDbopened_mysql = true;
            qDebug() << "WS_THREAD:---------->mysql connection open";
        }
        else{
            bDbopened_mysql = false;
            qDebug() << "WS_THREAD:---------->mysql connection error" << db_mysql->lastError().text();
        }
    }

}

//ws_cmd textMessageReceived
void WebSocket::cmd_processTextMessage(QString message)
{
    qDebug() << "WS_THREAD:received cmd:------------->" << message;
    if(message.contains(sCMD_AddUser)){
        emit this->sig_touser_cmd_add(message);
    }
    else if(message.contains(sCMD_DelUser)){
        emit this->sig_touser_cmd_del(message);
    }
    else if(message.contains(sCMD_DeleteALL)){
        emit this->sig_touser_cmd_delall(message);
    }
    else if(message.contains(sCMD_AddTimezone)){
        emit this->sig_toterminal_timezone(message);
    }
    else if(message.contains(sCMD_AddHol)){
        emit this->sig_toterminal_holiday(message);
    }
    else if(message.contains(sCMD_AddAccess)){
        emit this->sig_toterminal_accesstime(message);
    }
    else if(message.contains(sCMD_AddGroup)){
        emit this->sig_toterminal_accessgroup(message);
    }
}

void WebSocket::cmd_processTextMessageMaster(QString message)
{
    qDebug() << "WS_THREAD:received Master cmd:------------->" << message;
    if(message.contains(sCMD_AddUser)){
        emit this->sig_touser_cmd_add_master(message);
    }
    else if(message.contains(sCMD_DelUser)){
        emit this->sig_touser_cmd_del_master(message);
    }
}

//user sig_user_finishedCMD
//terminal sig_user_finishedCMD
void WebSocket::sig_user_finishedCMD()
{
    b_ws_inproc = false;
}

//this invaid_cmd
void WebSocket::slot_fromuser_invalid()
{
    qDebug() << "WS_THREAD:invalid message!";
    return;
}

//socket sig_Stop_Thread
void WebSocket::slot_Stop_WS_Thread()
{ 
    qDebug() << "WS_THREAD:stop socket thread worker";
    if(db_sql->isOpen())
        db_sql->close();
    this->deleteLater();
}

void WebSocket::slot_checksys_SendAll_oneByone()
{
    qDebug() << "WS_THREAD:-------------> check sys";
    if(net && virdi){
        check_User();

        check_Master();
        //emit this->textMessageReceived(sCMD_AddUser+QString("%1").arg(2, 8, 10, QChar('0')) + ":" + QString("%1").arg(1, 4, 10, QChar('0')) + ":END");
    }
    else{
        qDebug() << "WS_THREAD:net or virdi problem can not check sys";
    }
    tCheckSys->start(1 * 60 * 1000);

    //tCheckSys->start(5 * 1000);
    return;
}



void WebSocket::check_User()
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-UserActionData.dll");
    //qDebug() << "WS_THREAD: query: " << squery;
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Terminal_User_query";
        return;
    }
    else{
        squery = squery.arg(sdb_Rest);
        squery = squery.arg(QString::number(i_DeviceId));
        //qDebug() << "******************* " << squery;
        QSqlQuery query(*db_sql);
        if(!query.exec(squery)){
            qDebug() << "WS_THREAD: query error check user: " << query.lastError().text();
            return;
        }
        else{
            int terminaID = 0;
            int userId = 0;
            while(query.next()){
                QCoreApplication::processEvents(QEventLoop::AllEvents);
                if(query.value("UserId").isNull())
                    continue;
                if( query.value("action").toInt() == 11 || query.value("action").toInt() == 31){
                    terminaID = 1;
                    userId = query.value("UserId").toInt();
                    b_ws_inproc = true;
                    qDebug() << sCMD_AddUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
                    emit this->textMessageReceived(sCMD_AddUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
                }
                else if( query.value("action").toInt() == 21){
                    terminaID = 1;
                    userId = query.value("UserId").toInt();
                    b_ws_inproc = true;
                    qDebug() << sCMD_DelUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
                    emit this->textMessageReceived(sCMD_DelUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
                }
                else
                    continue;
                while(b_ws_inproc){
                    QCoreApplication::processEvents(QEventLoop::AllEvents);
                }
            }
        }

    }
    return;
}

void WebSocket::check_Master()
{

    qDebug() << "WS_THREAD: check masters";
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-GetMaster.dll");
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Master_User_query";
        return;
    }
    else{
        squery = squery.arg(QString::number(i_DeviceId));

        qDebug() << "";
        qDebug() << "";

        qDebug() << squery;

        qDebug() << "";
        qDebug() << "";
        QSqlQuery query(*db_mysql);
        if(!query.exec(squery)){
            qDebug() << "WS_THREAD: query error check master users: " << query.lastError().text();
            return;
        }
        else{
            int terminaID = 0;
            int userId = 0;
            QString CSN;
            QString FingerPrint;
            QString Name;
            while(query.next()){

                qDebug() << " mysql master query";
                QCoreApplication::processEvents(QEventLoop::AllEvents);
                if(query.value("UserId").isNull())
                    continue;
                if( query.value("UserAction").toInt() == 31){
                    terminaID = 1;
                    userId = query.value("UserId").toInt();
                    b_ws_inproc = true;
                    qDebug() << sCMD_AddUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
                    emit this->textMessageReceivedMaster(sCMD_AddUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
                }
                else if( query.value("UserAction").toInt() == 21){
                    terminaID = 1;
                    userId = query.value("UserId").toInt();
                    b_ws_inproc = true;
                    qDebug() << sCMD_DelUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
                    emit this->textMessageReceivedMaster(sCMD_DelUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
                }
                else
                    continue;
                while(b_ws_inproc){
                    QCoreApplication::processEvents(QEventLoop::AllEvents);
                }
            }
        }
    }
}

QString WebSocket::LoadQuery(QString sFilename)
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

void WebSocket::check_Timezone()
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-terminalStatus_timeZone.dll");
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Terminal_Timezone_query";
        return;
    }
    else{
        QSqlQuery query(*db_sql);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "CS_THREAD: query error check timezones: " << query.lastError().text();
            db_sql->close();
            db_sql->open();
            return;
        }
        int terminaID;
        while(query.next()){
            QCoreApplication::processEvents(QEventLoop::AllEvents);
            if(query.value("terminalId").isNull())
                continue;
            terminaID = query.value("terminalId").toInt();
            b_ws_inproc = true;
            qDebug() << sCMD_AddTimezone+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
            emit this->textMessageReceived(sCMD_AddTimezone+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
            while(b_ws_inproc){
                QCoreApplication::processEvents(QEventLoop::AllEvents);
            }
        }
    }
    return;
}

void WebSocket::check_Holiday()
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-terminalStatus_holiday.dll");
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Terminal_Holiday_query";
        return;
    }
    else{
        QSqlQuery query(*db_sql);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check holiday: " << query.lastError().text();
            db_sql->close();
            db_sql->open();
            return;
        }
        int terminaID;
        while(query.next()){
            QCoreApplication::processEvents(QEventLoop::AllEvents);
            if(query.value("terminalId").isNull())
                continue;
            terminaID = query.value("terminalId").toInt();
            b_ws_inproc = true;
            qDebug() << sCMD_AddHol+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
            emit this->textMessageReceived(sCMD_AddHol+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
            while(b_ws_inproc){
                QCoreApplication::processEvents(QEventLoop::AllEvents);
            }
        }
    }
    return;
}

void WebSocket::check_Acess()
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-terminalStatus_accessTime.dll");
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Terminal_Access_query";
        return;
    }
    else{
        QSqlQuery query(*db_sql);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check access: " << query.lastError().text();
            db_sql->close();
            db_sql->open();
            return;
        }
        int terminaID;
        while(query.next()){
            QCoreApplication::processEvents(QEventLoop::AllEvents);
            if(query.value("terminalId").isNull())
                continue;
            terminaID = query.value("terminalId").toInt();
            b_ws_inproc = true;
            qDebug() << sCMD_AddAccess+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
            emit this->textMessageReceived(sCMD_AddAccess+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
            while(b_ws_inproc){
                QCoreApplication::processEvents(QEventLoop::AllEvents);
            }
        }
    }
    return;
}

void WebSocket::check_Groupe()
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-terminalStatus_accessGroup.dll");
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Terminal_Group_query";
        return;
    }
    else{
        QSqlQuery query(*db_sql);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check access: " << query.lastError().text();
            db_sql->close();
            db_sql->open();
            return;
        }
        int terminaID;
        while(query.next()){
            QCoreApplication::processEvents(QEventLoop::AllEvents);
            if(query.value("terminalId").isNull())
                continue;
            terminaID = query.value("terminalId").toInt();
            b_ws_inproc = true;
            qDebug() << sCMD_AddGroup+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
            emit this->textMessageReceived(sCMD_AddGroup+QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END");
            while(b_ws_inproc){
                QCoreApplication::processEvents(QEventLoop::AllEvents);
            }
        }
    }
    return;
}


void WebSocket::slot_socket_chechkNet(bool status)
{
    net = status;
}

void WebSocket::slot_socket_chechkVirdi(bool status)
{
    virdi = status;
}

void WebSocket::slot_socket_netCable(bool status)
{
    netCable = status;
}

