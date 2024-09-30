#include "databaseclass2.h"

//97 invalid query
//98 is not user

DatabaseClass2::DatabaseClass2(QObject *parent) : QObject(parent)
{

}

void DatabaseClass2::slot_db_StartThread()
{
    qDebug() << "DatabaseClass2-->start database thread";
    func_db_configClass();

    nam_db_NetworkManager = new QNetworkAccessManager(this);



    t_db_WebTimeout = new QTimer(this);
    t_db_WebTimeout->setSingleShot(true);
    connect(t_db_WebTimeout,SIGNAL(timeout()),
            this,SLOT(slot_db_WebTimeout()),
            Qt::QueuedConnection);

    connect(nam_db_NetworkManager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(slot_db_WebReply(QNetworkReply*)),
            Qt::QueuedConnection);


    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL",str_db_ConnectionName));
    db->setDatabaseName(str_db_DatabaseName);
    db->setHostName(str_db_HostName);
    db->setUserName(str_db_UserName);
    db->setPassword(str_db_PassWord);
    db->setPort(3306);


    tm_db_checkDb = new QTimer(this);
    tm_db_checkDb->setSingleShot(false);
    connect(tm_db_checkDb,SIGNAL(timeout()),
            this,SLOT(slot_db_CheckDatabase()),
            Qt::QueuedConnection);
    tm_db_checkDb->start(i_db_checkTimeSec*1000);

    b_db_WebResp = false;
    b_db_WebSuccess = false;

    func_db_OpenDb();
    emit this->signal_db_databaseConnection2(b_db_isOpen);

}

void DatabaseClass2::func_db_OpenDb()
{
    if(!db->open()){
        qDebug() << "DatabaseClass2-->database connection error - Exit App - " << db->lastError().text();
        QCoreApplication::exit();

    }
    else{
        qDebug() << "DatabaseClass2-->database  open";
        b_db_isOpen = true;
    }
}

void DatabaseClass2::slot_db_StopThread()
{
    qDebug() << "DatabaseClass2-->Stop";
    if(db->isOpen())
        db->close();
    delete db;
    return;
}

void DatabaseClass2::func_db_configClass()
{
    QSettings setting("Upass.ini",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    str_db_ConnectionName = setting.value("Database/connection_name","").toString();
    str_db_ConnectionName = str_db_ConnectionName + "2";
    str_db_DatabaseName = setting.value("Database/database_name","").toString();
    str_db_HostName = setting.value("Database/hostname","").toString();
    str_db_UserName = setting.value("Database/username","").toString();
    str_db_PassWord = setting.value("Database/password","").toString();
    i_db_Port = setting.value("Database/port",0).toInt();
    i_db_checkTimeSec = setting.value("Database/checktime",5).toInt();

    i_db_TerminalId_2 = setting.value("SerialTerminalId/RS232_2",0).toInt();

    str_db_LogUrl = setting.value("Web/logurl",0).toString();
    i_db_WebTimeout = setting.value("Web/timeout",100).toInt();

    qDebug() << "DatabaseClass2-->connection name: " << str_db_ConnectionName;
    qDebug() << "DatabaseClass2-->database name: " << str_db_DatabaseName;
    qDebug() << "DatabaseClass2-->host name: " << str_db_HostName;
    qDebug() << "DatabaseClass2-->user name: " << str_db_UserName;
    qDebug() << "DatabaseClass2-->pass word name: " << str_db_PassWord;
    qDebug() << "DatabaseClass2-->port: " << i_db_Port;
    qDebug() << "DatabaseClass2-->database check time: " << i_db_checkTimeSec;
    qDebug() << "DatabaseClass2-->rs232_2 id: " << i_db_TerminalId_2;
    qDebug() << "DatabaseClass2-->log url: " << str_db_LogUrl;
    qDebug() << "DatabaseClass2-->web timeout: " << i_db_WebTimeout;

    b_db_isOpen = false;
}

void DatabaseClass2::slot_db_CheckDatabase()
{
    QSqlQuery query(*db);
    QString squery = "SELECT * FROM AsaController.tags LIMIT 1";
    if(b_db_isOpen == true && db->isOpen()){
        if(!query.exec(squery)){
            qDebug() << "DatabaseClass2-->database connection error - " << query.lastError().text();

            emit this->signal_db_databaseConnection2(false);
            if(db->isOpen()){
                db->close();
                qDebug() << "DatabaseClass2-->database connection error - Exit App - " << db->lastError().text();
                QCoreApplication::exit();
            }
        }
        else{
            emit this->signal_db_databaseConnection2(true);
            squery = func_db_LoadQuery("UpassUpdateStatus.sql");
            squery = squery.arg(QString::number(i_db_TerminalId_2));
            if(!query.exec(squery) || query.lastError().isValid())
            qDebug() << "DatabaseClass2-->update status terminal " << i_db_TerminalId_2 << " error - " << query.lastError().text();}
    }
    else{
        if(db->open()){
            b_db_isOpen = true;
            qDebug() << "DatabaseClass2-->database is open again - " << db->lastError().text();
        }
        else{
            qDebug() << "DatabaseClass2-->database connection error - Exit App";
            QCoreApplication::exit();
        }
        emit this->signal_db_databaseConnection2(b_db_isOpen);
    }
}

void DatabaseClass2::slot_db_GetNew_EPC_Data_port2(QString epcData)
{
    qDebug() << "DatabaseClass2-->port2 epc data : "  << epcData;
    if(epcData.count() < 4){
        qDebug() << "DatabaseClass2-->port2 invalid data";
        emit this->signal_db_changeProgStatus2(false);
        return;
    }
    QString crc;
    crc.clear();
    crc.append(epcData.at(0));
    crc.append(epcData.at(1));
    bool status = false;
    quint8 epc_length = crc.toUInt(&status,16);
    quint8 length_wd = 0;
    length_wd = epc_length & 0b11111000;
    length_wd = length_wd >> 3;
    qDebug() << "DatabaseClass2-->port2 epc length: " << length_wd * 2 * 2;
    if(epcData.count() != 2 + 2 + length_wd * 2 * 2){
        qDebug() << "DatabaseClass2-->port2 invalid data";
        emit this->signal_db_changeProgStatus2(false);
        return;
    }
    qDebug() << "DatabaseClass2-->port2 epc number: " << epcData.mid(4,length_wd * 2 * 2);
    func_db_checkTag2(epcData.mid(4,length_wd * 2 * 2));
    return;

}

void DatabaseClass2::func_db_checkTag2(QString tagnumber)
{
    //1- check if user
    int userId = func_db_CheckifUser(tagnumber);

    if(userId < 0){
        qDebug() << "DatabaseClass2-->invalid query";
        if(!func_db_SendLogWeb(tagnumber.count(),tagnumber,false,userId,99)){
            func_db_InsertAccess(tagnumber,userId,99);
        }
        emit this->signal_db_changeProgStatus2(false);
        return;

    }
    else if(userId == 0){
        qDebug() << "DatabaseClass2-->invalid user";
        //invalid user = 2
        if(!func_db_SendLogWeb(tagnumber.count(),tagnumber,false,userId,2)){
            func_db_InsertAccess(tagnumber,userId,2);
        }
        emit this->signal_db_changeProgStatus2(false);
        return;
    }
    else{
        qDebug() << "DatabaseClass2-->valid user = " << userId << " and permission check?";
        if(func_db_CheckifPermission(tagnumber)){
            qDebug() << "DatabaseClass2-->permission ok";
            //auth = 0
            emit this->signal_db_success2();
            if(!func_db_SendLogWeb(tagnumber.count(),tagnumber,true,userId,0)){
                func_db_InsertAccess(tagnumber,userId,0);
                return;
            }
        }
        else{
            qDebug() << "DatabaseClass2-->permission nk";
            // authpermission  = 3
            if(!func_db_SendLogWeb(tagnumber.count(),tagnumber,true,userId,3)){
                func_db_InsertAccess(tagnumber,userId,3);
            }
            emit this->signal_db_changeProgStatus2(false);
            return;
        }
    }
}

int DatabaseClass2::func_db_CheckifUser(QString TagNumber)
{
    QString string_query;
    string_query = func_db_LoadQuery("UpassGetUser.sql");
    QSqlQuery query(*db);
    string_query = string_query.arg(QString::number(i_db_TerminalId_2)).arg("'" + TagNumber + "'");
    if(query.exec(string_query)){
        if(query.next()){
            return query.value("UserId").toInt();
        }
        else
            return 0;
    }
    else
        return -1;

    //-1 query exception
    //0 not user
    //other user id
}

bool DatabaseClass2::func_db_CheckifPermission(QString TagNumber)
{
    QString string_query;
    string_query = func_db_LoadQuery("UpassGetAccess.sql");
    string_query = string_query.arg("'" + TagNumber + "'").arg(QString::number(i_db_TerminalId_2));
    QSqlQuery query(*db);
    if(!query.exec(string_query)){
        qDebug() << "DatabaseClass2-->permission query error - " << query.lastError().text();
        return false;
    }
    if(query.next())
        return true;
    else
        return false;
}

QString DatabaseClass2::func_db_LoadQuery(QString sFilePath)
{
    QString squery;
    QFile scriptFile(sFilePath);
    if(scriptFile.open(QIODevice::ReadOnly)){
        squery = QString(scriptFile.readAll());
        scriptFile.close();
        return squery;
    }
    else
        return "";
}

bool DatabaseClass2::func_db_SendLogWeb(int TagCount, QString TagNumber, bool isUser, int UserId , int error)
{
    QString log = func_db_SetLogString(TagCount,TagNumber, isUser,UserId ,error);
    b_db_WebResp = false;
    b_db_WebSuccess = false;
    t_db_WebTimeout->start(i_db_WebTimeout);
    nr_db_NetworkReply = nam_db_NetworkManager->get(QNetworkRequest(QUrl(str_db_LogUrl+log)));
    while(!b_db_WebResp){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    qDebug() << "DatabaseClass2--> after call Web log: b_db_WebSuccess = " << b_db_WebSuccess;
    return b_db_WebSuccess;
}

QString DatabaseClass2::func_db_SetLogString(int TagCount,QString TagNumber, bool isUser,int UserId ,int error)
{
    //error = 0 success
    //error = 1 unsuccess and is user
    //error = 3 unsuccess and is not user
    QString slog_socket;
    slog_socket.clear();
    slog_socket = "LOG:";
    slog_socket.append(QString("%1").arg(i_db_TerminalId_2, 4, 10, QChar('0')));
    slog_socket.append(":");
    slog_socket.append(QString("%1").arg(TagCount, 2, 10, QChar('0')));
    slog_socket.append(":");
        if(TagCount != 0)
            slog_socket.append(TagNumber);
        slog_socket.append(":");
        if(isUser){
            slog_socket.append(QString("%1").arg(UserId, 8, 10, QChar('0')));
        }
        else{
            slog_socket.append(QString("%1").arg(0, 8, 10, QChar('0')));
        }
        slog_socket.append(":");
        slog_socket.append(QString("%1").arg(3, 2, 10, QChar('0')));
        slog_socket.append(":");
        slog_socket.append(QString("%1").arg(7, 2, 10, QChar('0')));
        slog_socket.append(":");
        slog_socket.append(QString("%1").arg(QDateTime::currentDateTime().toString("yyyy")));
        slog_socket.append(QString("%1").arg(QDateTime::currentDateTime().toString("MM")));
        slog_socket.append(QString("%1").arg(QDateTime::currentDateTime().toString("dd")));
        slog_socket.append(QString("%1").arg(QDateTime::currentDateTime().toString("hh")));
        slog_socket.append(QString("%1").arg(QDateTime::currentDateTime().toString("mm")));
        slog_socket.append(QString("%1").arg(QDateTime::currentDateTime().toString("ss")));
        slog_socket.append(":");
        slog_socket.append(QString("%1").arg(error, 2, 10, QChar('0')));
        slog_socket.append(":");
        if(error == 0){
            slog_socket.append("1");
            slog_socket.append(":1");
            slog_socket.append(":END");
        }
        else{
            slog_socket.append("0");
            slog_socket.append(":1");
            slog_socket.append(":END");
        }
        qDebug() << "DatabaseClass2-->access log: " << slog_socket;
        return slog_socket;
}

void DatabaseClass2::func_db_InsertAccess(QString TagNumber,int UserId ,int error)
{
    QString string_query;
    string_query = func_db_LoadQuery("UpassInsertAccess.sql");
    QSqlQuery query(*db);
    qDebug() << "DatabaseClass2-->User id = " << UserId;

    if(error == 0){
        string_query = string_query.arg(QString::number(UserId)).arg(QString::number(i_db_TerminalId_2))
                                   .arg("'" + TagNumber + "'").arg(QString::number(3)).arg(QString::number(7))
                                   .arg(QDateTime::currentDateTime().toString("yyyy")).arg(QDateTime::currentDateTime().toString("MM"))
                                   .arg(QDateTime::currentDateTime().toString("dd")).arg(QDateTime::currentDateTime().toString("hh")).arg(QDateTime::currentDateTime().toString("mm"))
                                   .arg(QDateTime::currentDateTime().toString("ss")).arg(QString::number(error)).arg(QString("true"));
    }
    else if(UserId>0){
        string_query = string_query.arg(QString::number(UserId)).arg(QString::number(i_db_TerminalId_2))
                                   .arg("'" + TagNumber + "'").arg(QString::number(3)).arg(QString::number(7))
                                   .arg(QDateTime::currentDateTime().toString("yyyy")).arg(QDateTime::currentDateTime().toString("MM"))
                                   .arg(QDateTime::currentDateTime().toString("dd")).arg(QDateTime::currentDateTime().toString("hh")).arg(QDateTime::currentDateTime().toString("mm"))
                                   .arg(QDateTime::currentDateTime().toString("ss")).arg(QString::number(error)).arg(QString("false"));
    }
    else{
        string_query = string_query.arg("NULL").arg(QString::number(i_db_TerminalId_2))
                                   .arg("'" + TagNumber + "'").arg(QString::number(3)).arg(QString::number(7))
                                   .arg(QDateTime::currentDateTime().toString("yyyy")).arg(QDateTime::currentDateTime().toString("MM"))
                                   .arg(QDateTime::currentDateTime().toString("dd")).arg(QDateTime::currentDateTime().toString("hh")).arg(QDateTime::currentDateTime().toString("mm"))
                                   .arg(QDateTime::currentDateTime().toString("ss")).arg(QString::number(error)).arg(QString("false"));
    }
    qDebug() << "DatabaseClass2-->query insert access result - " << query.exec(string_query);
    qDebug() << "DatabaseClass2-->query insert access error - " << query.lastError().text();
}

void DatabaseClass2::testSlot()
{

//    b_db_WebResp = false;
//    b_db_WebSuccess = false;
//    t_db_WebTimeout->start(2500);
//    nr_db_NetworkReply = nam_db_NetworkManager->get(QNetworkRequest(QUrl("http://192.168.1.245:8001/web-service/srv-access-log?username=asarad&password=asa_1qaz@2wsx&command=LOG:0003:24:E2001066660C0172256012A2:00000000:99:99:20191023202452:02:0:END")));
//    while(!b_db_WebResp){
//        QCoreApplication::processEvents(QEventLoop::AllEvents);
//    }
//    qDebug() << "DatabaseClass2-->after call Web log: b_db_WebSuccess = " << b_db_WebSuccess;
    //return b_db_WebSuccess;

//    QString SQ;
//    SQ = func_db_LoadQuery("/var/miladtower/Upass/Query/UpassGetUser.sql");
//    QSqlQuery Q(*db);
//    SQ = SQ.arg(QString::number(3)).arg("'" + QString("8555") + "'");
//    if(Q.exec(SQ))
//        if(Q.next()){
//            qDebug() << Q.value("UserId").toInt();
//        }
}

void DatabaseClass2::slot_db_WebReply(QNetworkReply *reply)
{
    b_db_WebResp = true;
    nr_db_NetworkReply = reply;
    t_db_WebTimeout->stop();
    QByteArray response_data = nr_db_NetworkReply->readAll();
    qDebug() << "DatabaseClass2-->response_data = " << response_data;
    if (response_data.count() <= 0){
        qDebug() << "DatabaseClass2-->reply web log is null";
        b_db_WebSuccess = false;
    }
    else{
        if (response_data.contains("false") && response_data.contains("success")){
            b_db_WebSuccess = true;
        }
        else{
            b_db_WebSuccess = false;
        }
    }

    reply->deleteLater();
    nr_db_NetworkReply->deleteLater();
}

void DatabaseClass2::slot_db_WebTimeout()
{
    qDebug() << "DatabaseClass2-->web access log time out";
    b_db_WebSuccess = false;
    nr_db_NetworkReply->abort();
}


