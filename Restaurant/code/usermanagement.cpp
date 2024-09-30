#include "usermanagement.h"

UserManagement::UserManagement(QObject *parent) : QObject(parent)
{

}

//functions

void UserManagement::ConfigThread()
{
    tCheckDb = new QTimer(this);
    tCheckDb->setSingleShot(false);
    connect(tCheckDb,SIGNAL(timeout()),this,SLOT(slot_check_database()),Qt::QueuedConnection);

    netCable = false;
    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    sCMD_AddUser = setting.value("WebSocket/websocket_cmd_adduser","CMD:AddUserId:").toString();
    iCMD_addCount = setting.value("WebSocket/websocket_cmd_adduser_count",0).toInt();
    sCMD_DelUser = setting.value("WebSocket/websocket_cmd_deluser","CMD:DelUserId:").toString();
    iCMD_delCount = setting.value("WebSocket/websocket_cmd_deluser_count",0).toInt();
    sCMD_DeleteALL = setting.value("WebSocket/websocket_cmd_deletall","CMD:DeleteAllUsers:").toString();
    iCMD_deleteAllCount = setting.value("WebSocket/websocket_cmd_deleteall_count",0).toInt();

    sdb_Access = setting.value("DbNames/access","saipa").toString();
    sdb_Rest = setting.value("DbNames/rest","restaurant").toString();

    sDbConnectionNameMysql = setting.value("MySql/db_connection_user","").toString();
    sDbHostMysql = setting.value("MySql/db_host","").toString();
    iDbPortMysql = setting.value("MySql/db_port",0).toInt();
    sDBNameMysql = setting.value("MySql/db_name","").toString();
    sDbUserMysql = setting.value("MySql/db_user","").toString();
    sDbPassMysql = setting.value("MySql/db_pass","").toString();

    sDbConnectionNameSql = setting.value("SqlServer/db_connection_user","").toString();
    sDbHostSql = setting.value("SqlServer/db_host","").toString();
    iDbPortSql = setting.value("SqlServer/db_port",0).toInt();
    sDBNameSql = setting.value("SqlServer/db_name","").toString();
    sDbUserSql = setting.value("SqlServer/db_user","").toString();
    sDbPassSql = setting.value("SqlServer/db_pass","").toString();

    iTimeout = setting.value("Man/db_timeout",5).toInt();

    DeviceId = 0;
    DeviceId = setting.value("Main/device_id",0).toInt();


}


//slots

//sig_Start_Thread
void UserManagement::slot_Start_User_Thread()
{
    qDebug() << "US_THREAD:start user thread worker";
    ConfigThread();


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


    connect(this,SIGNAL(sig_user_acctionadd(int,int,int)),
            this,SLOT(slot_user_acctionadd(int,int,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_user_acctiondel(int,int,int)),
            this,SLOT(slot_user_acctiondel(int,int,int)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_user_savecmd(int,bool,int,quint32,int)),
            this,SLOT(slot_fromuser_savecmd(int,bool,int,quint32,int)),Qt::QueuedConnection);

    bDbopened_Sql = false;
    bDbopened_MySql = false;

//    if(netCable){
//        qDebug() << "US_THREAD: cable ok";
//        if(db_sql->open()){
//            qDebug() << "US_THREAD:cable ok---------->sql server connection open";
//            bDbopened_Sql = true;
//        }
//        else{
//            bDbopened_Sql = false;
//            qDebug() << "US_THREAD:cable ok---------->sql server connection error - " << db_sql->lastError().text();
//        }
//    }

    if(db_mysql->open()){
        bDbopened_MySql = true;
        qDebug() << "US_THREAD:---------->MySql connection open";
    }
    else{
        bDbopened_MySql = false;
        qDebug() << "US_THREAD:---------->MySql connection error - " << db_mysql->lastError().text();
    }
    tCheckDb->start(iTimeout * 1000);
}

//tCheckDb->timeout
void UserManagement::slot_check_database()
{
    qDebug() << "US_THREAD:check db";
    if(bDbopened_Sql == true){
        QString stestQuery("SELECT TOP 1 * FROM serv_restaurant_log");
        QSqlQuery query(*db_sql);
        if(!query.exec(stestQuery) && bDbopened_Sql){
            qDebug() << "WS_THREAD:---------->sql server connection error - " << query.lastError().text();
            db_sql->close();
            if(db_sql->open()){
                bDbopened_Sql = true;
                qDebug() << "WS_THREAD:cable ok---------->sql server connection open";
            }
            else{
                bDbopened_Sql = false;
                qDebug() << "WS_THREAD:cable ok---------->sql server connection error - " << db_sql->lastError().text();
            }
        }
    }
    else{
        if(netCable){
            qDebug() << "US_THREAD: cable ok";
            if(db_sql->open()){
                bDbopened_Sql = true;
                qDebug() << "US_THREAD:cable ok---------->sql server connection open";
            }
            else{
                bDbopened_Sql = false;
                qDebug() << "US_THREAD:cable ok---------->sql server connection error - " << db_sql->lastError().text();
            }
        }
    }

    if(bDbopened_MySql == true){
        QString stestQuery("SELECT * FROM rest_userlogs LIMIT 1");
        QSqlQuery query(*db_mysql);
        if(!query.exec(stestQuery)){
            qDebug() << "US_THREAD:---------->mysql connection error - " << db_mysql->lastError().text();
        }
    }
    else{
        if(db_mysql->open()){
            bDbopened_MySql = true;
            qDebug() << "US_THREAD:---------->mysql connection open";
        }
        else{
            bDbopened_MySql = false;
            qDebug() << "US_THREAD:---------->mysql connection error" << db_mysql->lastError().text();
        }
    }


}

//sig_Stop_Thread
void UserManagement::slot_Stop_User_Thread()
{
    if(db_sql->isOpen())
        db_sql->close();
    if(db_mysql->isOpen())
        db_mysql->close();
    this->deleteLater();
}

//socket sig_touser_add
void UserManagement::slot_fromsocket_cmd_add(QString message)
{
    //emit this->sig_tomain_cmd_add(1,2,"","FCDF602D",0,2019,10,20,2019,12,25);
    //return;

    qDebug() << "US_THREAD:add user id to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddUser.count());
    if(sMessage == sCMD_AddUser && message.count() == iCMD_addCount){
        QStringRef sUserID(&message , sCMD_AddUser.count() , 8);
        QStringRef sTerminalId(&message , sCMD_AddUser.count() + 8 + 1 , 4);
        int tmp = sUserID.toInt();
        currentUserId = tmp;
        quint32 quiUserId = static_cast<quint32>(tmp);
        tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);

        QSqlQuery query(*db_sql);
        QString squery;
        QDir dir;
        squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserData.dll");
        //qDebug() << dir.currentPath() + "/SqlQuery/usr-UserData.dll";

        squery = squery.arg(sdb_Rest).arg(sdb_Access).arg(QString::number(DeviceId)).arg(QString::number(quiUserId));
        int isYear = 0;
        int isMonth = 0;
        int isDay = 0;
        int ieYear = 0;
        int ieMonth = 0;
        int ieDay = 0;
        bool isAdmin = false;

        QString sPersonnelCode;
        sPersonnelCode.clear();
        QString sTextFir;
        sTextFir.clear();
        QString sCardValue;
        sCardValue.clear();
        if(query.exec(squery)){
            while(query.next()){
                qDebug() << "US_THREAD:Valid Query";
                if(!query.value("fingerValue").isNull())
                    sTextFir = query.value("fingerValue").toString();
                if(!query.value("cardValue").isNull())
                    sCardValue = query.value("cardValue").toString();
                if(!query.value("personnelCode").isNull())
                    sPersonnelCode = query.value("personnelCode").toString();
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
            qDebug() << "US_THREAD:Personnel Id = " << quiUserId;
            qDebug() << "US_THREAD:Terminal Id = " << 1;
            qDebug() << "US_THREAD:Device Id = " << DeviceId;
            qDebug() << "US_THREAD:isAdmin : " << isAdmin;
            qDebug() << "US_THREAD:User Text Fir lenght = " << sTextFir.count();
            qDebug() << "US_THREAD:User Card CSN = " << sCardValue;
            qDebug() << "US_THREAD:User Personnel Code = " << sPersonnelCode;
            qDebug() << "US_THREAD:User start , stop date: " << isYear << "/" <<isMonth << "/" << isDay << "/ , " << ieYear << "/" << ieMonth << "/" << ieDay;
            emit this->sig_tomain_cmd_add(quiTerminalId,quiUserId,sPersonnelCode,sTextFir,sCardValue,isAdmin,isYear,isMonth,isDay,ieYear,ieMonth,ieDay);
            return;
        }
        qDebug() << "US_THREAD:inValid Query";
        qDebug() << "US_THREAD:message: " << message;
        qDebug() << "US_THREAD:message.count: " << message.count();
        qDebug() << "US_THREAD:iCMD_addCount: " << iCMD_addCount;
        qDebug() << "US_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_user_finishedCMD();
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


void UserManagement::slot_fromsocket_cmd_add_master(QString message)
{
    qDebug() << "US_THREAD:add master user id to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddUser.count());
    if(sMessage == sCMD_AddUser && message.count() == iCMD_addCount){
        QStringRef sUserID(&message , sCMD_AddUser.count() , 8);
        QStringRef sTerminalId(&message , sCMD_AddUser.count() + 8 + 1 , 4);
        int tmp = sUserID.toInt();
        currentUserIdMaster = tmp;
        quint32 quiUserId = static_cast<quint32>(tmp);
        tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);

        QSqlQuery query(*db_mysql);
        QString squery;
        QDir dir;

        squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-MasterUserData.dll");
        //qDebug() << dir.currentPath() + "/SqlQuery/usr-MasterUserData.dll";

        squery = squery.arg(QString::number(DeviceId)).arg(QString::number(quiUserId)).arg("31");
        int isYear = 0;
        int isMonth = 0;
        int isDay = 0;
        int ieYear = 0;
        int ieMonth = 0;
        int ieDay = 0;
        bool isAdmin = false;

        QString sPersonnelCode;
        sPersonnelCode.clear();
        QString sTextFir;
        sTextFir.clear();
        QString sCardValue;
        sCardValue.clear();

        if(query.exec(squery)){
            while(query.next()){
                qDebug() << "US_THREAD:Valid Master Query";
                if(!query.value("FingerPrint").isNull())
                    sTextFir = query.value("FingerPrint").toString();
                if(!query.value("CardSerialNumber").isNull())
                    sCardValue = query.value("CardSerialNumber").toString();
                if(!query.value("Name").isNull())
                    sPersonnelCode = query.value("Name").toString();
            }
            qDebug() << "US_THREAD:Personnel Id = " << quiUserId;
            qDebug() << "US_THREAD:Terminal Id = " << 1;
            qDebug() << "US_THREAD:Device Id = " << DeviceId;
            qDebug() << "US_THREAD:isAdmin : " << isAdmin;
            qDebug() << "US_THREAD:User Text Fir lenght = " << sTextFir.count();
            qDebug() << "US_THREAD:User Card CSN = " << sCardValue;
            qDebug() << "US_THREAD:User Personnel Code = " << sPersonnelCode;
            qDebug() << "US_THREAD:User start , stop date: " << isYear << "/" <<isMonth << "/" << isDay << "/ , " << ieYear << "/" << ieMonth << "/" << ieDay;
            emit this->sig_tomain_cmd_add(quiTerminalId,quiUserId,sPersonnelCode,sTextFir,sCardValue,isAdmin,isYear,isMonth,isDay,ieYear,ieMonth,ieDay);
            return;
        }
        qDebug() << "US_THREAD:inValid Query";
        qDebug() << "US_THREAD:message: " << message;
        qDebug() << "US_THREAD:message.count: " << message.count();
        qDebug() << "US_THREAD:iCMD_addCount: " << iCMD_addCount;
        qDebug() << "US_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_user_finishedCMD();
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

void UserManagement::slot_fromsocket_cmd_del_master(QString message)
{
    qDebug() << "US_THREAD:delete master user id from terminal";
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
        if(UserId >= 99999990){
            qDebug() << "US_THREAD:OK end of delete master user id " << UserId << "from terminal id 1" << " with error code " << error;
            slot_fromuser_savecmd(2,ok,error,UCS_terminalID,static_cast<int>(UserId));
            slot_user_acctiondel_master(20,static_cast<int>(UCS_terminalID),static_cast<int>(UserId));
        }
        else{
            qDebug() << "US_THREAD:OK end of delete user id " << UserId << "from terminal id " << " with error code " << error;
            slot_fromuser_savecmd(2,ok,error,UCS_terminalID,static_cast<int>(UserId));
            slot_user_acctiondel(20,static_cast<int>(UCS_terminalID),static_cast<int>(UserId));
        }
    }
    else{ 
        if(UserId >= 99999990){
            qDebug() << "US_THREAD:NK end of delete masrt user id " << UserId << "from terminal id " << " with error code " << error;
            slot_fromuser_savecmd(2,ok,error,UCS_terminalID,static_cast<int>(UserId));
            slot_user_acctiondel_master(21,static_cast<int>(UCS_terminalID),static_cast<int>(UserId));
        }
        else {
            qDebug() << "US_THREAD:NK end of delete user  id " << UserId << "from terminal id " << " with error code " << error;
            slot_fromuser_savecmd(2,ok,error,UCS_terminalID,static_cast<int>(UserId));
            slot_user_acctiondel(21,static_cast<int>(UCS_terminalID),static_cast<int>(UserId));
        }
    }
    emit this->sig_user_finishedCMD();
}

//main sig_main_resp_add
void UserManagement::slot_frommain_resp_add(quint32 UserID,bool ok, int error, quint32 UCS_terminalID)
{
    if(ok){
        if(UserID >= 99999990){
            qDebug() << "US_THREAD:OK end of add master user id " << UserID << "to terminal id " << UCS_terminalID << " with error code " << error;
            slot_fromuser_savecmd(1,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd_master(30,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
        else{
            qDebug() << "US_THREAD:OK end of add user id " << UserID << "to terminal id " << UCS_terminalID << " with error code " << error;
            slot_fromuser_savecmd(1,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd(30,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
    }
    else{

        if(UserID >= 99999990){
            qDebug() << "US_THREAD:NK end of add userid " << UserID << "to terminal id " << " with error code " << error;
            slot_fromuser_savecmd(1,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd_master(31,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
        else{
            qDebug() << "US_THREAD:NK end of add userid " << UserID << "to terminal id " << " with error code " << error;
            slot_fromuser_savecmd(1,ok,error,UCS_terminalID,static_cast<int>(UserID));
            slot_user_acctionadd(31,static_cast<int>(UCS_terminalID),static_cast<int>(UserID));
        }
    }
    emit this->sig_user_finishedCMD();
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

    qDebug() << "US_THREAD: saved cmd result on terminal id " << UCS_terminalID;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/InsertCMD.dll");
    squery = squery.arg(QString::number(type));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(error));
    squery = squery.arg(QString::number(DeviceId));
    QSqlQuery query(*db_mysql);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:MySql query error save user cmd: " << query.lastError().text();
        db_mysql->close();
        db_mysql->open();
    }
    return;
}

void UserManagement::slot_user_acctionadd(int result, int terminalId, int userId)
{
    QDir dir;
    terminalId = 1;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserAction.dll");
    squery = squery.arg(sdb_Rest);
    squery = squery.arg(QString::number(result));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(DeviceId));
    squery = squery.arg(QString::number(31));
    QSqlQuery query(*db_sql);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:Sql Server query error action add: " << query.lastError().text();
        db_sql->close();
        db_sql->open();
    }
    return;
}

void UserManagement::slot_user_acctionadd_master(int result, int terminalId, int userId)
{
    QDir dir;
    terminalId = 1;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserActionMaster.dll");
    squery = squery.arg(QString::number(result));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(DeviceId));
    squery = squery.arg(QString::number(31));
    QSqlQuery query(*db_mysql);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:mysql query error action add master: " << query.lastError().text();
        db_sql->close();
        db_sql->open();
    }
    return;
}

void UserManagement::slot_user_acctiondel(int result,int terminalId,int userId)
{
    QDir dir;
    terminalId = 1;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserAction.dll");
    squery = squery.arg(sdb_Rest);
    squery = squery.arg(QString::number(result));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(DeviceId));
    squery = squery.arg(QString::number(21));
    QSqlQuery query(*db_sql);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:Sql Server query error action delete: " << query.lastError().text();
        db_sql->close();
        db_sql->open();
    }
    return;
}

void UserManagement::slot_user_acctiondel_master(int result,int terminalId,int userId)
{
    QDir dir;
    terminalId = 1;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/usr-UserActionMaster.dll");
    squery = squery.arg(QString::number(result));
    squery = squery.arg(QString::number(userId));
    squery = squery.arg(QString::number(DeviceId));
    squery = squery.arg(QString::number(21));
    QSqlQuery query(*db_mysql);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "US_THREAD:mysql query error action delete master: " << query.lastError().text();
        db_sql->close();
        db_sql->open();
    }
    return;
}

void UserManagement::slot_user_netCable(bool status)
{
    netCable = status;
}
