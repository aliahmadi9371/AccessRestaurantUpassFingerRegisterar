#include "terminalmanagement.h"
#include <QApplication>

TerminalManagement::TerminalManagement(QObject *parent) : QObject(parent)
{

}

//functions

void TerminalManagement::ConfigThread()
{
    tCheckDb = new QTimer(this);
    tCheckDb->setSingleShot(false);
    connect(tCheckDb,SIGNAL(timeout()),this,SLOT(slot_check_database()),Qt::QueuedConnection);
    
    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    
    sCMD_AddTimezone = setting.value("WebSocket/websocket_cmd_addtimezone","CMD:AddTimezones:").toString();
    iCMD_timezoneCount = setting.value("WebSocket/websocket_cmd_addtimezone_count",0).toInt();
    sCMD_AddHol = setting.value("WebSocket/websocket_cmd_addhol","CMD:AddHolidays:").toString();
    iCMD_holidayCount = setting.value("WebSocket/websocket_cmd_addholiday_count",0).toInt();
    sCMD_AddAccess = setting.value("WebSocket/websocket_cmd_addaccess","CMD:AddAccessTimes:").toString();
    iCMD_accessCount = setting.value("WebSocket/websocket_cmd_addaccess_count",0).toInt();
    sCMD_AddGroup = setting.value("WebSocket/websocket_cmd_addgroup","CMD:AddAccessGroups:").toString();
    iCMD_groupCount = setting.value("WebSocket/websocket_cmd_addgroup_count",0).toInt();
    
    sDbConnectionName = setting.value("Database/db_connection_terminal","terminal").toString();
    sDbHost = setting.value("Database/db_host","192.168.1.14").toString();
    iDbPort = setting.value("Database/db_port",8080).toInt();
    sDBName = setting.value("Database/db_name","saipa").toString();
    sDbUser = setting.value("Database/db_user","sa").toString();
    sDbPass = setting.value("Database/db_pass","123456").toString();

    iTimeout = setting.value("Database/db_timeout",5).toInt();
}


//slots

//sig_Start_Thread
void TerminalManagement::slot_Start_Terminal_Thread()
{
    qDebug() << "TR_THREAD:start terminal thread worker";
    ConfigThread();
    
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionName));
    QString sName = QString("DRIVER={SQL Server};SERVER=%1;Database=%2").arg(sDbHost).arg(sDBName);
    db->setDatabaseName(sName);
    db->setUserName(sDbUser);
    db->setPassword(sDbPass);
    db->setPort(iDbPort);

    connect(this,SIGNAL(sig_terminal_TimeZoneResDb(bool,int,quint32)),
            this,SLOT(slot_fromterminal_TimeZoneResDb(bool,int,quint32)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_terminal_HolidayResDb(bool,int,quint32)),
            this,SLOT(slot_fromterminal_HolidayResDb(bool,int,quint32)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_terminal_AccessResDb(bool,int,quint32)),
            this,SLOT(slot_fromterminal_AccessResDb(bool,int,quint32)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_terminal_GroupResDb(bool,int,quint32)),
            this,SLOT(slot_fromterminal_GroupResDb(bool,int,quint32)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_terminal_saveCMD(int,bool,int,quint32)),
            this,SLOT(slot_fromterminal_savecmd(int,bool,int,quint32)),Qt::QueuedConnection);
    
    tCheckDb->start(iTimeout * 1000);

    if(db->open())
        bDbopened = true;
    else{
        bDbopened = false;
        qDebug() << "TR_THREAD:" << db->lastError();
        QApplication::quit();
    }
    tCheckDb->start(iTimeout * 1000);
    emit this->sig_DB_Open(bDbopened);
}

//sig_Stop_Thread
void TerminalManagement::slot_Stop_Terminal_Thread()
{
    if(db->isOpen())
        db->close();
    this->deleteLater();
}

void TerminalManagement::slot_check_database()
{
    if(db->isOpen()){
        bDbopened = true;
    }
    else{
        if(db->open()){
            bDbopened = true;
            qDebug() << "TR_THREAD: can Open DataBase";
        }
        else{
            bDbopened = false;
            qDebug() << "TR_THREAD: " << db->lastError().text();
            QApplication::quit();
        }
    }
    emit this->sig_DB_Open(bDbopened);    
}





//socket sig_toterminal_timezone
void TerminalManagement::slot_fromsocket_timezone(QString message)
{
    qDebug() << "TR_THREAD:add timezone data to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddTimezone.count());
    if(sMessage == sCMD_AddTimezone && message.count() == iCMD_timezoneCount){
        QStringRef sTerminalId(&message , sCMD_AddTimezone.count() , 4);
        int tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);



        QSqlQuery query(*db);
        QString squery;
        QDir dir;
        squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-TimeZoneData.dll");
        squery = squery.arg(QString::number(quiTerminalId));


        clearTimezoneLists();
        query.exec(squery);

        query.next();
        int listIndex = 0;
        int queycount = 0;
        if(query.value("timezoneCode").isNull()){
            //qDebug() << "query is null";
            //qDebug() <<  query.lastError().text();
            slot_fromterminal_TimeZoneResDb(true,0,quiTerminalId);
            return;
        }
        TimezoneCodes.append(query.value("timezoneCode").toInt());
        queycount++;
        while(query.next()){
            queycount++;
            if(TimezoneCodes.at(listIndex) != query.value("timezoneCode").toInt()){
                listIndex++;
                TimezoneCodes.append(query.value("timezoneCode").toInt());
            }
        }
        listIndex = TimezoneCodes.count();
        //qDebug() << "time zone code count = " << TimezoneCodes.count();
        //qDebug() << "query count = " << queycount;


        int index = 0;
        query.first();
        for(int i=0; i<queycount; i++){
            if(TimezoneCodes.at(index) == query.value("timezoneCode").toInt()){
                StartHour[index].append(query.value("startHour").toInt());
                StartMin[index].append(query.value("startMinute").toInt());
                StopHour[index].append(query.value("endHour").toInt());
                StopMin[index].append(query.value("endMinute").toInt());
                query.next();
            }
            else{
                index++;
                StartHour[index].append(query.value("startHour").toInt());
                StartMin[index].append(query.value("startMinute").toInt());
                StopHour[index].append(query.value("endHour").toInt());
                StopMin[index].append(query.value("endMinute").toInt());
                query.next();
            }
        }

        emit this->sig_tomain_timezone(quiTerminalId,listIndex,&TimezoneCodes,StartHour,StartMin,StopHour,StopMin);
        return;
    }
    else{
        qDebug() << "TR_THREAD:message: " << message;
        qDebug() << "TR_THREAD:message.count: " << message.count();
        qDebug() << "TR_THREAD:iCMD_timezoneCount: " << iCMD_timezoneCount;
        qDebug() << "TR_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_terminal_finishedCMD();
    }
}

//socket sig_toterminal_holiday
void TerminalManagement::slot_fromsocket_holiday(QString message)
{
    qDebug() << "TR_THREAD:add holiday data to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddHol.count());
    if(sMessage == sCMD_AddHol && message.count() == iCMD_holidayCount){
        QStringRef sTerminalId(&message , sCMD_AddHol.count() , 4);
        int tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);

        QSqlQuery query(*db);
        QString squery;
        QDir dir;
        squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-HolidayData.dll");
        squery = squery.arg(QString::number(quiTerminalId));

        clearHolidayLists();
        query.exec(squery);

        query.next();
        int listIndex = 0;
        int queycount = 0;
        if(query.value("holidayCode").isNull()){
            //qDebug() << "query is null";
            //qDebug() <<  query.lastError().text();
            slot_fromterminal_AccessResDb(true,0,quiTerminalId);
            return;
        }
        HolidayCodes.append(query.value("holidayCode").toInt());
        queycount++;
        while(query.next()){
            queycount++;
            if(HolidayCodes.at(listIndex) != query.value("holidayCode").toInt()){
                listIndex++;
                HolidayCodes.append(query.value("holidayCode").toInt());
            }
        }
        listIndex = HolidayCodes.count();
        //qDebug() << "holiday code count = " << HolidayCodes.count();
        //qDebug() << "query count = " << queycount;


        int index = 0;
        query.first();
        for(int i=0; i<queycount; i++){
            if(HolidayCodes.at(index) == query.value("holidayCode").toInt()){
                Month[index].append(query.value("dateMonth").toInt());
                Day[index].append(query.value("dateDay").toInt());
                query.next();
            }
            else{
                index++;
                Month[index].append(query.value("dateMonth").toInt());
                Day[index].append(query.value("dateDay").toInt());
                query.next();
            }
        }

//        qDebug() << Month[0].count();
//        for(int i=0 ; i<listIndex; i++){
//            qDebug() << "HolidayCodes.at(" << i << ") = " << HolidayCodes.at(i);
//            for(int j=0; j<Month[i].count();j++){
//                qDebug() << "-----> Month[" << i << "].at(" << j << ") = " << Month[i].at(j);
//                qDebug() << "-----> Day[" << i << "].at(" << j << ") = " << Day[i].at(j);
//            }
//        }
        emit this->sig_tomain_hol(quiTerminalId,listIndex,&HolidayCodes,Month,Day);
        return;
    }
    else{
        qDebug() << "TR_THREAD:message: " << message;
        qDebug() << "TR_THREAD:message.count: " << message.count();
        qDebug() << "TR_THREAD:iCMD_holidayCount: " << iCMD_holidayCount;
        qDebug() << "TR_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_terminal_finishedCMD();
    }
}

//socket sig_toterminal_accesstime
void TerminalManagement::slot_fromsocket_accesstime(QString message)
{
    qDebug() << "TR_THREAD:add access data to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddAccess.count());
    if(sMessage == sCMD_AddAccess && message.count() == iCMD_accessCount){
        QStringRef sTerminalId(&message , sCMD_AddAccess.count() , 4);
        int tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);

        QSqlQuery query(*db);
        QString squery;
        QDir dir;
        squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-AccessTimeData.dll");
        squery = squery.arg(QString::number(quiTerminalId));


        clearAccessLists();
        query.exec(squery);

        query.next();
        int listIndex = 0;
        int queycount = 0;
        if(query.value("accessTimeCode").isNull()){
            //qDebug() << "query is null";
            //qDebug() <<  query.lastError().text();
            slot_fromterminal_HolidayResDb(true,0,quiTerminalId);
            return;
        }
        AccessCodes.append(query.value("accessTimeCode").toInt());
        queycount++;
        while(query.next()){
            queycount++;
            if(AccessCodes.at(listIndex) != query.value("accessTimeCode").toInt()){
                listIndex++;
                AccessCodes.append(query.value("accessTimeCode").toInt());
            }
        }
        listIndex = AccessCodes.count();
        //qDebug() << "access code count = " << AccessCodes.count();
        //qDebug() << "query count = " << queycount;


        int index = 0;
        query.first();
        for(int i=0; i<queycount; i++){
            if(AccessCodes.at(index) == query.value("accessTimeCode").toInt()){

                AccessHolidayCode[index] = query.value("holidayCode").toInt();
                AccessDayList[index].append(query.value("dayNum").toInt());
                AccessDayCodes[index].append(query.value("dayCode").toInt());
                query.next();
            }
            else{
                index++;
                AccessHolidayCode[index] = query.value("holidayCode").toInt();
                AccessDayList[index].append(query.value("dayNum").toInt());
                AccessDayCodes[index].append(query.value("dayCode").toInt());
                query.next();
            }
        }

//        for(int i=0 ; i<listIndex; i++){
//            qDebug() << "AccessCodes.at(" << i << ") = " << AccessCodes.at(i);
//            qDebug() << "AccessHolidayCode[" << i << "] = " << AccessHolidayCode[i];
//            for(int j=0; j<AccessDayList[i].count();j++){
//                qDebug() << "-----> AccessDayList[" << i << "].at(" << j << ") = " << AccessDayList[i].at(j);
//                qDebug() << "-----> AccessDayCodes[" << i << "].at(" << j << ") = " << AccessDayCodes[i].at(j);
//            }
//        }
        emit this->sig_tomain_access(quiTerminalId,listIndex,&AccessCodes,AccessHolidayCode,AccessDayList,AccessDayCodes);
        return;
    }
    else{
        qDebug() << "TR_THREAD:message: " << message;
        qDebug() << "TR_THREAD:message.count: " << message.count();
        qDebug() << "TR_THREAD:iCMD_accessCount: " << iCMD_accessCount;
        qDebug() << "TR_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_terminal_finishedCMD();
    }
}

//sig_toterminal_accessgroup
void TerminalManagement::slot_fromsocket_accessgroup(QString message)
{
    qDebug() << "TR_THREAD:add group data to terminal";
    QStringRef sMessage(&message , 0 , sCMD_AddGroup.count());
    if(sMessage == sCMD_AddGroup && message.count() == iCMD_groupCount){
        QStringRef sTerminalId(&message , sCMD_AddGroup.count() , 4);
        int tmp = sTerminalId.toInt();
        quint32 quiTerminalId = static_cast<quint32>(tmp);

        qDebug() << "terminal id: " << quiTerminalId;

        QSqlQuery query(*db);
        QString squery;
        QDir dir;
        squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-AccessGroupData.dll");
        squery = squery.arg(QString::number(quiTerminalId));
        clearGroupLists();
        query.exec(squery);

        query.next();
        int listIndex = 0;
        int queycount = 0;
        if(query.value("accessGroupCode").isNull()){
            //qDebug() << "query is null";
            //qDebug() <<  query.lastError().text();
            slot_fromterminal_GroupResDb(true,0,quiTerminalId);
            return;
        }
        groupCode.append(query.value("accessGroupCode").toInt());
        queycount++;
        while(query.next()){
            queycount++;
            if(groupCode.at(listIndex) != query.value("accessGroupCode").toInt()){
                listIndex++;
                groupCode.append(query.value("accessGroupCode").toInt());
            }
        }
        listIndex = groupCode.count();
        //qDebug() << "groupCode code count = " << groupCode.count();
        //qDebug() << "query count = " << queycount;


        int index = 0;
        query.first();
        for(int i=0; i<queycount; i++){
            if(groupCode.at(index) == query.value("accessGroupCode").toInt()){
                HaccessCodes[index].append(query.value("accessTimeCode").toInt());
                query.next();
            }
            else{
                index++;
                HaccessCodes[index].append(query.value("accessTimeCode").toInt());
                query.next();
            }
        }

//        for(int i=0 ; i<listIndex; i++){
//            qDebug() << "groupCode.at(" << i << ") = " << groupCode.at(i);
//            for(int j=0; j<HaccessCodes[i].count();j++){
//                qDebug() << "-----> HaccessCodes[" << i << "].at(" << j << ") = " << HaccessCodes[i].at(j);
//            }
//        }
        emit this->sig_tomain_group(quiTerminalId,listIndex,&groupCode,HaccessCodes);
        return;
    }
    else{
        qDebug() << "TR_THREAD:message: " << message;
        qDebug() << "TR_THREAD:message.count: " << message.count();
        qDebug() << "TR_THREAD:iCMD_groupCount: " << iCMD_groupCount;
        qDebug() << "TR_THREAD:sMessage: " << sMessage;
        emit this->invaid_cmd();
        emit this->sig_terminal_finishedCMD();
    }
}


void TerminalManagement::slot_frommain_timezoneResp(bool ok,int error,quint32 UCS_terminalID)
{
    if(ok)
        qDebug() << "TR_THREAD:OK end of add timezone to terminal " << UCS_terminalID << " with error code " << error;
    else
        qDebug() << "TR_THREAD:NK end of of add timezone to terminal " << UCS_terminalID << " with error code " << error;
    slot_fromterminal_savecmd(3,ok,error,UCS_terminalID);
    slot_fromterminal_TimeZoneResDb(ok,error,UCS_terminalID);
    emit this->sig_terminal_finishedCMD();
}

void TerminalManagement::slot_frommain_holidayResp(bool ok,int error,quint32 UCS_terminalID)
{
    if(ok)
        qDebug() << "TR_THREAD:OK end of add holiday to terminal " << UCS_terminalID << " with error code " << error;
    else
        qDebug() << "TR_THREAD:NK end of add holiday to terminal " << UCS_terminalID << " with error code " << error;
    slot_fromterminal_savecmd(4,ok,error,UCS_terminalID);
    slot_fromterminal_HolidayResDb(ok,error,UCS_terminalID);
    emit this->sig_terminal_finishedCMD();
}

void TerminalManagement::slot_frommain_accesstimeResp(bool ok,int error,quint32 UCS_terminalID)
{
    if(ok)
        qDebug() << "TR_THREAD:OK end of add access to terminal " << UCS_terminalID << " with error code " << error;
    else
        qDebug() << "TR_THREAD:NK end of add access to from terminal " << UCS_terminalID << " with error code " << error;
    slot_fromterminal_savecmd(5,ok,error,UCS_terminalID);
    slot_fromterminal_AccessResDb(ok,error,UCS_terminalID);
    emit this->sig_terminal_finishedCMD();
}

void TerminalManagement::slot_frommain_accessgroupResp(bool ok,int error,quint32 UCS_terminalID)
{
    if(ok)
        qDebug() << "TR_THREAD:OK end of add group to terminal " << UCS_terminalID << " with error code " << error;
    else
        qDebug() << "TR_THREAD:NK end of add group to terminal " << UCS_terminalID << " with error code " << error;
    slot_fromterminal_savecmd(6,ok,error,UCS_terminalID);
    slot_fromterminal_GroupResDb(ok,error,UCS_terminalID);
    emit this->sig_terminal_finishedCMD();
}

QString TerminalManagement::LoadQuery(QString sFilename)
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

void TerminalManagement::clearTimezoneLists()
{
    for(int i=0 ; i< 128; i++){
        TimezoneCodes.clear();
        StartHour[i].clear();
        StartMin[i].clear();
        StopHour[i].clear();
        StopMin[i].clear();
    }
}

void TerminalManagement::clearHolidayLists()
{
    HolidayCodes.clear();
    for(int i=0 ; i< 64; i++){
        Month[i].clear();
        Day[i].clear();
    }
}

void TerminalManagement::clearAccessLists()
{
    AccessCodes.clear();
    for(int i=0 ; i< 128; i++){
        AccessHolidayCode[i] = 0;
        AccessDayList[i].clear();
        AccessDayCodes[i].clear();
    }
}

void TerminalManagement::clearGroupLists()
{
    for(int i=0 ; i< 128; i++){
       groupCode.clear();
        HaccessCodes[i].clear();
    }
    return;
}


void TerminalManagement::slot_fromterminal_TimeZoneResDb(bool ok,int error,quint32 UCS_terminalID)
{
    if(!ok){
        qDebug() << "TR_THREAD:" << error;
        return;
    }
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-UpdateTimezone.dll");
    squery = squery.arg(QString::number(UCS_terminalID));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "TR_THREAD:query error update timezone status: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "TR_THREAD: can Open DataBase";
        }
    }
    return;
}

void TerminalManagement::slot_fromterminal_HolidayResDb(bool ok,int error,quint32 UCS_terminalID)
{
    if(!ok){
        qDebug() << "TR_THREAD:" << error;
        return;
    }
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-UpdateHoliday.dll");
    squery = squery.arg(QString::number(UCS_terminalID));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "TR_THREAD:query error update holiday status: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "TR_THREAD: can Open DataBase";
        }

    }
    return;
}

void TerminalManagement::slot_fromterminal_AccessResDb(bool ok,int error,quint32 UCS_terminalID)
{
    if(!ok){
        qDebug() << "TR_THREAD:" << error;
        return;
    }
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-UpdateAccess.dll");
    squery = squery.arg(QString::number(UCS_terminalID));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "TR_THREAD:query error update access status: " << query.lastError().text();
        db->close();
        if(!db->open()){
            QApplication::quit();
        }
        else {
            qDebug() << "TR_THREAD: can Open DataBase";
        }
    }
    return;
}

void TerminalManagement::slot_fromterminal_GroupResDb(bool ok,int error,quint32 UCS_terminalID)
{
    if(!ok){
        qDebug() << "TR_THREAD:" << error;
        return;
    }
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/tr-UpdateGroup.dll");
    squery = squery.arg(QString::number(UCS_terminalID));
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "TR_THREAD:query error update group status: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "TR_THREAD: can Open DataBase";
        }
    }
    return;
}

void TerminalManagement::slot_fromterminal_savecmd(int type,bool ok,int error,quint32 UCS_terminalID)
{
    if(ok)
        qDebug() << "TR_THREAD:" << ok;
    QDir dir;
    QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/InsertCMD.dll");
    squery = squery.arg(QString::number(UCS_terminalID));
    squery = squery.arg(QString::number(type));
    squery = squery.arg(QString::number(error));
    squery = squery.arg("NULL");
    squery = squery.arg("CURRENT_TIMESTAMP");
    QSqlQuery query(*db);
    query.exec(squery);
    if(query.lastError().isValid()){
        qDebug() << "TR_THREAD:query error terminal save cmd: " << query.lastError().text();
        db->close();
        if(!db->open())
            QApplication::quit();
        else {
            qDebug() << "TR_THREAD: can Open DataBase";
        }
    }
    return;
}
