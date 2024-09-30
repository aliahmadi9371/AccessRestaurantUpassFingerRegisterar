#include "usermanagement.h"
#include <QApplication>

UserManagement::UserManagement(QObject *parent) : QObject(parent)
{

}

//functions

void UserManagement::ConfigThread()
{
    tCheckDb = new QTimer(this);
    tCheckDb->setSingleShot(false);
    connect(tCheckDb,SIGNAL(timeout()),this,SLOT(slot_check_database()),Qt::QueuedConnection);

    
    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    sCMD_AddUser = setting.value("WebSocket/websocket_cmd_adduser","CMD:AddUserId:").toString();
    iCMD_addCount = setting.value("WebSocket/websocket_cmd_adduser_count",0).toInt();
    sCMD_DelUser = setting.value("WebSocket/websocket_cmd_deluser","CMD:DelUserId:").toString();
    iCMD_delCount = setting.value("WebSocket/websocket_cmd_deluser_count",0).toInt();
    sCMD_DeleteALL = setting.value("WebSocket/websocket_cmd_deletall","CMD:DeleteAllUsers:").toString();
    iCMD_deleteAllCount = setting.value("WebSocket/websocket_cmd_deleteall_count",0).toInt();


    sDbConnectionName = setting.value("Database/db_connection_user","0").toString();
    sDbHost = setting.value("Database/db_host","192.168.1.14").toString();
    iDbPort = setting.value("Database/db_port",8080).toInt();
    sDBName = setting.value("Database/db_name","saipa").toString();
    sDbUser = setting.value("Database/db_user","sa").toString();
    sDbPass = setting.value("Database/db_pass","123456").toString();

    iTimeout = setting.value("Database/db_timeout",5).toInt();

}


//slots

//sig_Start_Thread
void UserManagement::slot_Start_User_Thread()
{
    qDebug() << "US_THREAD:start user thread worker";
    ConfigThread();


    db = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionName));
    QString sName = QString("DRIVER={SQL Server};SERVER=%1;Database=%2").arg(sDbHost).arg(sDBName);
    db->setDatabaseName(sName);
    db->setUserName(sDbUser);
    db->setPassword(sDbPass);
    db->setPort(iDbPort);

    connect(this,SIGNAL(sig_user_acctionadd(int,int,int)),
            this,SLOT(slot_user_acctionadd(int,int,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_user_acctiondel(int,int,int)),
            this,SLOT(slot_user_acctiondel(int,int,int)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_user_savecmd(int,bool,int,quint32,int)),
            this,SLOT(slot_fromuser_savecmd(int,bool,int,quint32,int)),Qt::QueuedConnection);


    if(db->open()){
        bDbopened = true;
        qDebug() << "US_THREAD: can Open DataBase";
    }
    else{
        bDbopened = false;
        qDebug() << "US_THREAD:" << db->lastError();
        QApplication::quit();
    }
    tCheckDb->start(iTimeout * 1000);
}

//sig_Stop_Thread
void UserManagement::slot_Stop_User_Thread()
{
    if(db->isOpen())
        db->close();
    this->deleteLater();
}

//socket sig_touser_add
void UserManagement::slot_fromsocket_cmd_add(QString message)
{
    qDebug() << "US_THREAD:add user id to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddUser.count());
    if(sMessage == sCMD_AddUser && message.count() == iCMD_addCount && (message.contains("1:END") || message.contains("2:END") ) ){

        int tmpp = 0;
        if(message.contains("1:END"))
            tmpp = 1;
        else
            tmpp = 2;

        QStringRef sUserID(&message , sCMD_AddUser.count() , 8);
        QStringRef sTerminalId(&message , sCMD_AddUser.count() + 8 + 1 , 4);
        int tmp = sUserID.toInt();
        currentUserId = tmp;
        quint32 quiUserId = static_cast<quint32>(tmp);
        tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);

        QSqlQuery query(*db);
        QString squery;
        QDir dir;
        squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserData.dll");
        //qDebug() << dir.currentPath() + "/SqlQuery/usr-UserData.dll";
        squery = squery.arg(QString::number(quiUserId)).arg(QString::number(quiTerminalId));
        query.exec(squery);

        int isYear = 0;
        int isMonth = 0;
        int isDay = 0;
        int ieYear = 0;
        int ieMonth = 0;
        int ieDay = 0;
        QString groupCode;
        bool isAdmin = false;
        groupCode.clear();

        QString PersonnelCode;
        PersonnelCode.clear();


        //personnelCode

        QString sTextFir;
        sTextFir.clear();
        QString sCardValue;
        sTextFir.clear();
        while(query.next()){
                groupCode = QString("%1").arg(query.value("accessGroupCode").toInt(), 4, 10, QChar('0'));
                PersonnelCode = query.value("personnelCode").toString();

            if((!query.value("isAdmin").isNull()) && (query.value("isAdmin").toBool() == true))
                isAdmin = true;
            if(!query.value("fingerValue").isNull())
                sTextFir = query.value("fingerValue").toString();

            if(!query.value("cardValue").isNull())
                sCardValue = query.value("cardValue").toString();

            //qDebug() << "sCardValue = " << sCardValue;
            if(!query.value("startYear").isNull())
                isYear = query.value("startYear").toInt();
            if(!query.value("startMonth").isNull())
                isMonth = query.value("startMonth").toInt();
            if(!query.value("startDay").isNull())
                isDay = query.value("startDay").toInt();
            if(!query.value("endYear").isNull())
                ieYear = query.value("endYear").toInt();
             if(!query.value("endMonth").isNull())
                ieMonth = query.value("endMonth").toInt();
            if(!query.value("endDay").isNull())
                ieDay = query.value("endDay").toInt();
        }

        qDebug() << "US_THREAD:User Id = " << quiUserId;
        qDebug() << "US_THREAD:User PersonnelCode = " << PersonnelCode;
        qDebug() << "US_THREAD:User TerminalId = " << quiTerminalId;
        qDebug() << "US_THREAD:isAdmin : " << isAdmin;
        qDebug() << "US_THREAD:User Text Fir lenght = " << sTextFir.count();
        qDebug() << "US_THREAD:User Card CSN = " << sCardValue;
        qDebug() << "US_THREAD:User start date: " << isYear << "/" <<isMonth << "/" << isDay << "/ , " << ieYear << "/" << ieMonth << "/" << ieDay;

        emit this->sig_tomain_cmd_add(quiTerminalId,quiUserId,PersonnelCode,sTextFir,sCardValue,isYear,isMonth,isDay,ieYear,ieMonth,ieDay,groupCode,isAdmin,tmpp);
        return;
    }
    else{
        qDebug() << "US_THREAD:message: " << message;
        qDebug() << "US_THREAD:message.count: " << message.count();
        qDebug() << "US_THREAD:iCMD_addCount: " << iCMD_addCount;
        qDebug() << "US_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_user_finishedCMD();
    }
}

//socket sig_touser_del
void UserManagement::slot_fromsocket_cmd_del(QString message)
{
    qDebug() << "US_THREAD:delete user id from terminal";
    QStringRef sMessage(&message , 0 , sCMD_DelUser.count());
    if(sMessage == sCMD_DelUser && message.count() == iCMD_delCount){
        QStringRef sUserID(&message , sCMD_DelUser.count() , 8);
        QStringRef sTerminalId(&message , sCMD_DelUser.count() + 8 + 1 , 4);
        int tmp = sUserID.toInt();
        currentUserId = tmp;
        quint32 quiUserId = static_cast<quint32>(tmp);
        tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);
        emit this->sig_tomain_cmd_del(quiTerminalId,quiUserId);
        return;
    }
    else{
        qDebug() << "US_THREAD:message: " << message;
        qDebug() << "US_THREAD:message.count: " << message.count();
        qDebug() << "US_THREAD:iCMD_delCount: " << iCMD_delCount;
        qDebug() << "US_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_user_finishedCMD();
    }

}

//socket sig_touser_deleteall
void UserManagement::slot_fromsocket_cmd_delall(QString message)
{
    qDebug() << "US_THREAD:delete all users from terminal";
    QStringRef sMessage(&message , 0 , sCMD_DeleteALL.count());
    if(sMessage == sCMD_DeleteALL && message.count() == iCMD_deleteAllCount){
        QStringRef sTerminalId(&message , sCMD_DelUser.count() , 4);
        int tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);
        emit this->sig_tomain_cmd_delall(quiTerminalId);
        return;
    }
    else{
        qDebug() << "US_THREAD:message: " << message;
        qDebug() << "US_THREAD:message.count: " << message.count();
        qDebug() << "US_THREAD:iCMD_deleteAllCount: " << iCMD_deleteAllCount;
        qDebug() << "US_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_user_finishedCMD();
    }
}

//main sig_main_resp_deleteall
void UserManagement::slot_frommain_resp_deleteall(bool ok, int error, quint32 UCS_terminalID)
{
    if(ok)
        qDebug() << "US_THREAD:OK end of delete all users from terminal " << UCS_terminalID << " with error code " << error;
    else
        qDebug() << "US_THREAD:NK end of delete all users from terminal " << UCS_terminalID << " with error code " << error;
    emit this->sig_user_finishedCMD();
}

//main sig_main_resp_delete
void UserManagement::slot_frommain_resp_delete(quint32 UserId,bool ok, int error, quint32 UCS_terminalID)
{
    if(ok){
        qDebug() << "US_THREAD:OK end of delete user id " << UserId << "from terminal id " << " with error code " << error;
        slot_fromuser_savecmd(2,ok,error,UCS_terminalID,currentUserId);
        slot_user_acctiondel(20,static_cast<int>(UCS_terminalID),static_cast<int>(UserId));
    }
    else{
        qDebug() << "US_THREAD:NK end of delete user  id " << UserId << "from terminal id " << " with error code " << error;
        slot_fromuser_savecmd(2,ok,error,UCS_terminalID,static_cast<int>(UserId));
        slot_user_acctiondel(21,static_cast<int>(UCS_terminalID),static_cast<int>(UserId));
    }
    emit this->sig_user_finishedCMD();
}

//main sig_main_resp_add
void UserManagement::slot_frommain_resp_add(quint32 UserID,bool ok, int error, quint32 UCS_terminalID, int addinactive)
{
    if(ok){
        qDebug() << "US_THREAD:OK end of add user id " << UserID << "to terminal id " << UCS_terminalID << " with error code " << error;

        if(addinactive == 1){
            slot_fromuser_savecmd(1,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd(30,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
        else {
            slot_fromuser_savecmd(4,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd(40,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
    }
    else{
        qDebug() << "US_THREAD:NK end of add userid " << UserID << "to terminal id " << " with error code " << error;
        if(addinactive == 1){
            slot_fromuser_savecmd(1,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd(31,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
        else {
            slot_fromuser_savecmd(4,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd(41,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
    }

    emit this->sig_user_finishedCMD();
}

//tCheckDb->timeout
void UserManagement::slot_check_database()
{
    if(db->isOpen()){
        bDbopened = true;
    }
    else{
        if(db->open()){
            bDbopened = true;
            qDebug() << "US_THREAD:" << db->lastError();
            qDebug() << "US_THREAD: can Open DataBase";
        }
        else{
            bDbopened = false;
            QApplication::quit();
        }
    }
    emit this->sig_DB_Open(bDbopened);
}

QString UserManagement::LoadQuery(QString sFilename)
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

void UserManagement::slot_fromuser_savecmd(int type, bool ok, int error, quint32 UCS_terminalID, int userId)
{
    bool ook = ok;
    ook = false;
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/InsertCMD.dll");
    squery = squery.arg(QString::number(UCS_terminalID));
    squery = squery.arg(QString::number(type));
    squery = squery.arg(QString::number(error));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg("CURRENT_TIMESTAMP");
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:query error save user cmd: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "US_THREAD: can Open DataBase";
        }
    }
    return;
}

void UserManagement::slot_user_acctionadd(int result, int terminalId, int userId)
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserAction.dll");
    squery = squery.arg(QString::number(result));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(terminalId));
    if(result == 30 || result == 31)
        squery = squery.arg(QString::number(31));
    else
        squery = squery.arg(QString::number(41));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:query error action add: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "US_THREAD: can Open DataBase";
        }
    }
    return;
}

void UserManagement::slot_user_acctiondel(int result,int terminalId,int userId)
{
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserAction.dll");
    squery = squery.arg(QString::number(result));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(terminalId));
    squery = squery.arg(QString::number(21));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:query error action delete: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "US_THREAD: can Open DataBase";
        }
    }
    return;
}
