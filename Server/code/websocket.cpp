#include "websocket.h"
#include <QApplication>

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

    tCheckSys->start(10 * 1000);

    b_ws_inproc = false;

    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    
    sSocketServerURL = setting.value("WebSocket/websocket_url","ws://127.0.0.1:8080").toString();
    
    sCMD_AddUser = setting.value("WebSocket/websocket_cmd_adduser","CMD:AddUserId:").toString();
    sCMD_DelUser = setting.value("WebSocket/websocket_cmd_deluser","CMD:DelUserId:").toString();
    sCMD_DeleteALL = setting.value("WebSocket/websocket_cmd_deletall","CMD:DeleteAllUsers:").toString();
    sCMD_AddTimezone = setting.value("WebSocket/websocket_cmd_addtimezone","CMD:AddTimezoneData:").toString();
    sCMD_AddHol = setting.value("WebSocket/websocket_cmd_addhol","CMD:AddHolidayData:").toString();
    sCMD_AddAccess = setting.value("WebSocket/websocket_cmd_addaccess","CMD:AddAccessTimesData:").toString();
    sCMD_AddGroup = setting.value("WebSocket/websocket_cmd_addgroup","CMD:AddAccessGroupData:").toString();

    sDbConnectionName = setting.value("Database/db_connection_socket","socket").toString();
    sDbHost = setting.value("Database/db_host","192.168.1.14").toString();
    iDbPort = setting.value("Database/db_port",8080).toInt();
    sDBName = setting.value("Database/db_name","saipa").toString();
    sDbUser = setting.value("Database/db_user","sa").toString();
    sDbPass = setting.value("Database/db_pass","123456").toString();

    iTimeout = setting.value("Database/db_timeout",5).toInt();

    connect(this,SIGNAL(textMessageReceived(QString)),
            this, SLOT(cmd_processTextMessage(QString)),
            Qt::QueuedConnection);

}

//slots

//socket sig_Start_Thread
void WebSocket::slot_Start_WS_Thread()
{
    qDebug() << "WS_THREAD:start socket thread worker";
    ConfigThread();

    blog_ws = false;
    bcmd_ws = false;

    db = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionName));
    QString sName = QString("DRIVER={SQL Server};SERVER=%1;Database=%2").arg(sDbHost).arg(sDBName);
    db->setDatabaseName(sName);
    db->setUserName(sDbUser);
    db->setPassword(sDbPass);
    db->setPort(iDbPort);

    db_try = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionName+"try"));
    QString sName_try = QString("DRIVER={SQL Server};SERVER=%1;Database=%2").arg(sDbHost).arg(sDBName);
    db_try->setDatabaseName(sName_try);
    db_try->setUserName(sDbUser);
    db_try->setPassword(sDbPass);
    db_try->setPort(iDbPort);

    if(db->open() && db_try->open()){
        bDbopened = true;
        qDebug() << "WS_THREAD: can Open DataBase";
    }
    else{
        bDbopened = false;
        qDebug() << "WS_THREAD:" << db->lastError();
        qDebug() << "WS_THREAD:" << db_try->lastError();
        QApplication::quit();
    }
    tCheckDb->start(iTimeout * 1000);

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
    if(db->isOpen())
        db->close();
    this->deleteLater();
}

void WebSocket::slot_checksys_SendAll_oneByone()
{
    qDebug() << "WS_THREAD:-------------> check sys";
    check_Timezone();
    check_Holiday();
    check_Acess();
    check_Groupe();

    check_User();

    tCheckSys->start(1 * 60 * 1000);
    return;
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
        QSqlQuery query(*db);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "CS_THREAD: query error check timezones: " << query.lastError().text();
            db->close();
            if(!db->open())
                QApplication::quit();
            else {
                qDebug() << "WS_THREAD: can Open DataBase";
            }
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
        QSqlQuery query(*db);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check holiday: " << query.lastError().text();
            db->close();
            if(!db->open())
                QApplication::quit();
            else {
                qDebug() << "WS_THREAD: can Open DataBase";
            }
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
        QSqlQuery query(*db);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check access: " << query.lastError().text();
            db->close();
            if(!db->open())
                QApplication::quit();
            else {
                qDebug() << "WS_THREAD: can Open DataBase";
            }
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
        QSqlQuery query(*db);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check access: " << query.lastError().text();
            db->close();
            if(!db->open())
                QApplication::quit();
            else {
                qDebug() << "WS_THREAD: can Open DataBase";
            }
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

void WebSocket::check_User()
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/ws-UserActionData.dll");
    if(squery == ""){
        qDebug() << "WS_THREAD: Can not find Terminal_User_query";
        return;
    }
    else{
        QSqlQuery query(*db);
        query.exec(squery);
        if(query.lastError().isValid()){
            qDebug() << "WS_THREAD: query error check user: " << query.lastError().text();
            db->close();
            if(!db->open())
                QApplication::quit();
            else {
                qDebug() << "WS_THREAD: can Open DataBase";
            }
            return;
        }
        int terminaID = 0;
        int userId = 0;
        while(query.next()){ 
            QCoreApplication::processEvents(QEventLoop::AllEvents);


            if(query.value("terminalId").isNull() || query.value("real_user_fr").isNull())
                continue;
            if( query.value("action").toInt() == 11 || query.value("action").toInt() == 31 || query.value("action").toInt() == 41){
                int tmp = query.value("action").toInt();
                if(tmp == 11 || tmp == 31)
                    tmp = 1;
                else if(tmp == 41)
                    tmp = 2;
                else
                    tmp = 0;
                terminaID = query.value("terminalId").toInt();
                userId = query.value("real_user_fr").toInt();

//                query.value("count_resend")

                //update try count
                int id = query.value("id").toInt();
                qDebug() << "WS_THREAD: add table id = " << id;
                qDebug() << "WS_THREAD: add UPDATE Try Count - userId = " << userId  << " and Try Count = " << query.value("count_resend").toInt();
                QSqlQuery add_Tyrq(*db_try);
                QString add_Trys = LoadQuery(dir.currentPath() + "/SqlQuery/ws-UpdateTryCount.dll");
                add_Trys = add_Trys.arg(QString::number(id));
                if(add_Tyrq.exec(add_Trys))
                    qDebug() << "WS_THREAD: add try count update successful";
                else
                    qDebug() << "WS_THREAD: add try count update error" << add_Tyrq.lastError().text();
                add_Tyrq.finish();
                add_Tyrq.clear();
                //update try count

                b_ws_inproc = true;
                qDebug() << "WS_THREAD:" << sCMD_AddUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":END";
                emit this->textMessageReceived(sCMD_AddUser+QString("%1").arg(userId, 8, 10, QChar('0')) + ":" + QString("%1").arg(terminaID, 4, 10, QChar('0')) + ":" + QString::number(tmp) + ":END");
            }
            else if( query.value("action").toInt() == 21){
                terminaID = query.value("terminalId").toInt();
                userId = query.value("real_user_fr").toInt();

                //update try count
                int id = query.value("id").toInt();
                qDebug() << "WS_THREAD: delete table id = " << id;
                qDebug() << "WS_THREAD: delete UPDATE Try Count - userId = " << userId  << " and Try Count = " << query.value("count_resend").toInt();
                QSqlQuery delete_Tyrq(*db_try);
                QString delete_Trs = LoadQuery(dir.currentPath() + "/SqlQuery/ws-UpdateTryCount.dll");
                delete_Tyrq.finish();
                delete_Trs = delete_Trs.arg(QString::number(id));
                if(delete_Tyrq.exec(delete_Trs))
                    qDebug() << "WS_THREAD: delete try count update successful";
                else
                    qDebug() << "WS_THREAD: delete try count update error" << delete_Tyrq.lastError().text();
                delete_Tyrq.finish();
                delete_Tyrq.clear();
                //update try count


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
    return;
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

//tCheckDb->timeout
void WebSocket::slot_check_database()
{
    if(db->isOpen() && db_try->isOpen()){
        bDbopened = true;
    }
    else{
        if(db->open() && db_try->open()){
            bDbopened = true;
            qDebug() << "WS_THREAD: can Open DataBase";

        }
        else{
            bDbopened = false;
            qDebug() << "WS_THREAD:" << db->lastError();
            qDebug() << "WS_THREAD:" << db_try->lastError();
            QApplication::quit();
        }
    }
}



