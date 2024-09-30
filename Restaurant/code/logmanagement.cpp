#include "logmanagement.h"


LogManagement::LogManagement(QObject *parent) : QObject(parent)
{

}

void LogManagement::func_log_openprinter()
{
    QPrinterInfo printerInfo;
    QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
    foreach (const QPrinterInfo &printerInfo, printers){
        if(printerInfo.description() == "POS-80C"){
            printer = new QPrinter(printerInfo,QPrinter::PrinterResolution);
            qDebug() << "LG:printer driver name: "<< printerInfo.description();
            //PrintReceipt("00000000","","جلو خورشت قرمه‌سبزی", "غذای نوع ۴", "علی احمدی");
            return;
        }
    }
    return;
}


void LogManagement::ConfigThread()
{
    qDebug() << "LG:config thread worker";
    timerOnline = new QTimer(this);
    timerOnline->setSingleShot(false);
    connect(timerOnline,SIGNAL(timeout()),
            this,SLOT(setTime()),
            Qt::QueuedConnection);

    time = 2;
    timerOnline->start(5000);


    testTimer = new QTimer(this);
    testTimer->setSingleShot(false);
    connect(testTimer,SIGNAL(timeout()),
            this,SLOT(slot_log_testTimerTimeout()),
            Qt::QueuedConnection);

    //testTimer->start(1000);


    func_log_openprinter();


    tCheckDb = new QTimer(this);
    tCheckDb->setSingleShot(false);


    connect(tCheckDb,SIGNAL(timeout()),this,SLOT(slot_check_database()),
            Qt::QueuedConnection);

    connect(this,SIGNAL(sig_log_insertAccess(quint32,quint32,QString,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            this,SLOT(slot_fromlog_insertAccess(quint32,quint32,QString,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            Qt::QueuedConnection);



    FirstTerminalList.clear();

    QSettings setting("config.dll",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");

    FirstTerminalList.clear();

    sdb_Access = setting.value("DbNames/access","saipa").toString();
    sdb_Rest = setting.value("DbNames/rest","restaurant").toString();

    sDbConnectionNameMysql = setting.value("MySql/db_connection_log","").toString();
    sDbHostMysql = setting.value("MySql/db_host","").toString();
    iDbPortMysql = setting.value("MySql/db_port",0).toInt();
    sDBNameMysql = setting.value("MySql/db_name","").toString();
    sDbUserMysql = setting.value("MySql/db_user","").toString();
    sDbPassMysql = setting.value("MySql/db_pass","").toString();

    sDbConnectionNameSql = setting.value("SqlServer/db_connection_log","").toString();
    sDbHostSql = setting.value("SqlServer/db_host","").toString();
    iDbPortSql = setting.value("SqlServer/db_port",0).toInt();
    sDBNameSql = setting.value("SqlServer/db_name","").toString();
    sDbUserSql = setting.value("SqlServer/db_user","").toString();
    sDbPassSql = setting.value("SqlServer/db_pass","").toString();

    iTimeout = setting.value("Main/db_timeout",5).toInt();
    DeviceId = 0;
    RestaurantId = 0;
    DeviceId = setting.value("Main/device_id",0).toInt();
    RestaurantId = setting.value("Main/restaurant_id",0).toInt();


    swebLogURL = setting.value("WebLog/url","").toString();
    net = false;
    virdi = false;
    netCable = false;
    bDbopened_sql = false;
    bDbopened_MySql = false;


    qDebug() << "LG----------->:config thread worker";
    return;

}


//slots

//sig_Start_Thread
void LogManagement::slot_Start_Log_Thread()
{
    qDebug() << "LG:start log thread worker";
    ConfigThread();

    qDebug() << "LG:create sql server";
    db_sql = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC",sDbConnectionNameSql));
    QString sName = QString(s_connection).arg(sDbHostSql).arg(sDBNameSql);
    db_sql->setDatabaseName(sName);
    db_sql->setUserName(sDbUserSql);
    db_sql->setPassword(sDbPassSql);
    db_sql->setPort(iDbPortSql);
    db_sql->setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=1,SQL_ATTR_LOGIN_TIMEOUT=1;");

    qDebug() << "LG:create and open mysql";
    db_mysql = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL",sDbConnectionNameMysql));
    db_mysql->setDatabaseName(sDBNameMysql);
    db_mysql->setUserName(sDbUserMysql);
    db_mysql->setPassword(sDbPassMysql);
    db_mysql->setPort(iDbPortMysql);
    db_mysql->setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");


    qDebug() << "LG:---------->sql connection option " << db_sql->connectOptions();
    qDebug() << "LG:---------->mysql connection option " << db_mysql->connectOptions();

    bDbopened_sql = false;
    bDbopened_MySql = false;
    db_mysql->setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");

//    if(netCable){
//        qDebug() << "LG: cable ok";
//        if(db_sql->open()){
//            qDebug() << "LG:cable ok---------->sql server connection open";
//            bDbopened_sql = true;
//        }
//        else{
//            bDbopened_sql = false;
//            qDebug() << "LG:cable ok---------->sql server connection error - " << db_sql->lastError().text();
//        }
//    }


    if(db_mysql->open()){
        bDbopened_MySql = true;
        qDebug() << "LG:---------->mysql connection open";
    }
    else{
        bDbopened_MySql = false;
        qDebug() << "LG:---------->mysql connection error - " << db_mysql->lastError().text();
    }

    tCheckDb->start(iTimeout * 1000);
//    emit this->sig_DB_Open(bDbopened_sql);
}

//sig_Stop_Thread
void LogManagement::slot_Stop_Log_Thread()
{
    if(db_mysql->isOpen())
        db_mysql->close();
    this->deleteLater();
}

void LogManagement::slot_check_database()
{
    qDebug() << "LG:---------->check db";
    if(bDbopened_sql == true){
        QString stestQuery("SELECT TOP 1 * FROM serv_restaurant_log");
        QSqlQuery query(*db_sql);
        if(!query.exec(stestQuery)){
            qDebug() << "LG:---------->sql server connection error - " << query.lastError().text();
            emit this->sig_DB_Open(false);
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
            emit this->sig_DB_Open(true);
        }
    }
    else{
        if(netCable){
            qDebug() << "LG: cable ok";
            if(db_sql->open()){
                bDbopened_sql = true;
                qDebug() << "LG:cable ok---------->sql server connection open";
            }
            else{
                bDbopened_sql = false;
                qDebug() << "LG:cable ok---------->sql server connection error - " << db_sql->lastError().text();
            }
        }
    }

    if(bDbopened_MySql == true){
        QString stestQuery("SELECT * FROM rest_userlogs LIMIT 1");
        QSqlQuery query(*db_mysql);
        if(!query.exec(stestQuery)){
            qDebug() <<  "LG:---------->mysql connection error - " << db_mysql->lastError().text();
        }
    }
    else{
        if(db_mysql->open()){
            bDbopened_MySql = true;
            qDebug() <<  "LG:---------->mysql connection open";
        }
        else{
            bDbopened_MySql = false;
            qDebug() <<  "LG:---------->mysql connection error - " << db_mysql->lastError().text();
            if(bDbopened_MySql){
                db_mysql->close();
                if(db_mysql->open()){
                    bDbopened_MySql = true;
                    qDebug() << "LG:---------->mysql connection open";
                }
                else{
                    bDbopened_MySql = false;
                    qDebug() << "LG:---------->mysql connection error - " << db_mysql->lastError().text();
                }
            }
        }
    }
}

void LogManagement::slot_frommain_RealTimeLog(quint32 quiTerminalId,quint32 qui_RFID_length,BYTE* RFID_data,quint32 qui_UserID,quint8 qui_AuthMode,quint8 qui_AuthType,
                                              quint16 qui_Year,quint8 qui_Month,quint8 qui_Day,quint8 qui_Hour,quint8 qui_Min,quint8 qui_Sec,quint32 qui_AuthRes,bool bRes)
{

    if(!virdi)
        return;
    qDebug() << "LG:user input from terminal id: " << quiTerminalId;
    QString rfid;
    rfid.clear();
    for(int i=0; i<static_cast<int>(qui_RFID_length); i++){
       rfid.append(RFID_data[i]);
    }

    //qDebug() << rfid;
    rfid_auto.clear();
    rfid_auto = rfid;

    slot_fromlog_insertAccess(quiTerminalId,qui_RFID_length,rfid_auto,qui_UserID,qui_AuthMode,qui_AuthType,qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes);
    return;
}



//main sig_main_getTerminalStatus
void LogManagement::slot_frommain_TerminalStatus(quint32 quiTerminalId)
{
    qDebug() << "LG:log management thread: terminal Status update from terminal id: " << quiTerminalId;
    if(time < 0){
        //qDebug() << "online after disconnection";
    }
    time = 5;
    emit this->sig_log_onlineTerminal(true);

    return;
}

//log sig_log_insertAccess

void LogManagement::func_log_GetMasterFood(quint32 quiTerminalId, quint32 length, QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes)
{
    QString Food1;
    Food1.clear();
    QString Food2;
    Food2.clear();
    QString Food3;
    Food3.clear();
    QString Food4;
    Food3.clear();

    int count=0;

    qDebug() << "get menu";
    QDir dirfood;
    QString squery = LoadQuery(dirfood.currentPath() + "/SqlQuery/log-getFoodTypesMaster.dll");
    squery = squery.arg(QString::number(RestaurantId));
    QSqlQuery query(*db_mysql);
    if(!query.exec(squery)){
        if(query.lastError().isValid()){
            qDebug() << "LG:My Sql query error get food : " << query.lastError().text();
            db_mysql->close();
            db_mysql->open();
            return;
        }
    }
    bool bFood1 = false;
    bool bFood2 = false;
    bool bFood3 = false;
    bool bFood4 = false;
    while(query.next()){

        if(query.value("FoodType").toInt() == 1){
            Food1 = query.value("FoodName").toString().toUtf8();
            bFood1 = true;
        }
        else if(query.value("FoodType").toInt() == 2){
            Food2 = query.value("FoodName").toString().toUtf8();
            bFood2 = true;
        }
        else if(query.value("FoodType").toInt() == 3){
            Food3 = query.value("FoodName").toString().toUtf8();
            bFood3 = true;
        }
        else if(query.value("FoodType").toInt() == 4){
            Food4 = query.value("FoodName").toString().toUtf8();
            bFood4 = true;
        }
        count++;
        if(count >= 4)
            break;
    }

    if(bFood1 == false && bFood2 == false && bFood3 == false && bFood4 == false ){

        qDebug() << "no food today";
        emit this->sig_log_UserLog(4,true,qui_UserID,0,"","","");

        if(RFID_data.count() != 0 )
            func_log_logtoDatabase("",0,Food3,0,1,1,3,RFID_data);
        else
            func_log_logtoDatabase("",0,Food3,0,1,0,3,"");
        return;
    }


    qDebug() << "get master food";
    QDir dirfoodMaster;
    QString squeryMaster = LoadQuery(dirfoodMaster.currentPath() + "/SqlQuery/log-GetMasterFood.dll");
    squeryMaster = squeryMaster.arg(QString::number(qui_UserID));
    squeryMaster = squeryMaster.arg(QString::number(DeviceId));

    // qDebug() << "";
    // qDebug() << "";

    // qDebug() << squeryMaster;

    // qDebug() << "";
     //qDebug() << "";

    QSqlQuery queryMaster(*db_mysql);
    if(!queryMaster.exec(squeryMaster)){
        if(queryMaster.lastError().isValid()){
            qDebug() << "LG:My Sql query error get food : " << queryMaster.lastError().text();
            db_mysql->close();
            db_mysql->open();
            return;
        }
    }
    queryMaster.next();
    QString Name;

    //qDebug() << "&&&&&&&&&&&&&&&&&&&&";
    if(queryMaster.value("FoodType").toInt() == 1){
        qDebug() << "LG:show result on lcd";
        if(bFood1){
            Name = queryMaster.value("Name").toString().toUtf8();
            emit this->sig_log_SendFoodCount(1);
            PrintReceipt(Name.toUtf8(),
                         QString::fromUtf8("شرکت بازرگانی سایپا یدک"),
                         Food1.toUtf8(),
                         QString::fromUtf8("غذای نوع %1").arg(1),
                         Name.toUtf8());
    
            emit this->sig_log_UserLog(1,true,qui_UserID,1,Food1.toUtf8(),Name,Name);
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase(Name,0,Food1,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase(Name,0,Food1,0,1,0,3,"");
            return;
        }
        else{
            qDebug() << "no food today";
            emit this->sig_log_UserLog(4,true,qui_UserID,0,"","","");
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase("",0,Food3,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase("",0,Food3,0,1,0,3,"");
            return;
        }
        
    }
    else if(queryMaster.value("FoodType").toInt() == 2){
        qDebug() << "LG:show result on lcd";
        if(bFood2){
            Name = queryMaster.value("Name").toString().toUtf8();
            emit this->sig_log_SendFoodCount(2);
            PrintReceipt(Name.toUtf8(),
                         QString::fromUtf8("شرکت بازرگانی سایپا یدک"),
                         Food2.toUtf8(),
                         QString::fromUtf8("غذای نوع %1").arg(2),
                         Name.toUtf8());
    
            emit this->sig_log_UserLog(1,true,qui_UserID,1,Food2.toUtf8(),Name,Name);
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase(Name,0,Food2,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase(Name,0,Food2,0,1,0,3,"");
            return;
        }
        else{
            qDebug() << "no food today";
            emit this->sig_log_UserLog(4,true,qui_UserID,0,"","","");
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase("",0,Food3,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase("",0,Food3,0,1,0,3,"");
            return;
        }
        
    }
    else if(queryMaster.value("FoodType").toInt() == 3){
        qDebug() << "LG:show result on lcd";
        
        if(bFood3){
            Name = queryMaster.value("Name").toString().toUtf8();
            emit this->sig_log_SendFoodCount(3);
            PrintReceipt(Name.toUtf8(),
                         QString::fromUtf8("شرکت بازرگانی سایپا یدک"),
                         Food3.toUtf8(),
                         QString::fromUtf8("غذای نوع %1").arg(3),
                         Name.toUtf8());
    
            emit this->sig_log_UserLog(1,true,qui_UserID,1,Food3.toUtf8(),Name,Name);
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase(Name,0,Food3,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase(Name,0,Food3,0,1,0,3,"");
            return;
        }
        else{
            qDebug() << "no food today";
            emit this->sig_log_UserLog(4,true,qui_UserID,0,"","","");

            if(RFID_data.count() != 0 )
                func_log_logtoDatabase("",0,Food3,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase("",0,Food3,0,1,0,3,"");
            return;
        }
    }
    else if(queryMaster.value("FoodType").toInt() == 4){
        qDebug() << "LG:show result on lcd";
        
        if(bFood4){
            Name = queryMaster.value("Name").toString().toUtf8();
            emit this->sig_log_SendFoodCount(4);
            PrintReceipt(Name.toUtf8(),
                         QString::fromUtf8("شرکت بازرگانی سایپا یدک"),
                         Food4.toUtf8(),
                         QString::fromUtf8("غذای نوع %1").arg(4),
                         Name.toUtf8());
    
            emit this->sig_log_UserLog(1,true,qui_UserID,1,Food4.toUtf8(),Name,Name);
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase(Name,0,Food4,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase(Name,0,Food4,0,1,0,3,"");
            return;
        }
        else{
            qDebug() << "no food today";
            emit this->sig_log_UserLog(4,true,qui_UserID,0,"","","");
    
            if(RFID_data.count() != 0 )
                func_log_logtoDatabase("",0,Food3,0,1,1,3,RFID_data);
            else
                func_log_logtoDatabase("",0,Food3,0,1,0,3,"");
            return;
        }
    }
    else return;

}


void LogManagement::func_log_logtoDatabase(QString PersonnelName, int FoodId, QString FoodName, int reservationId, int foodStatus, bool bCardFinger, quint32 qui_AuthRes, QString CardNumber)
{
    QString stestQuery1("SELECT TOP 1 * FROM serv_restaurant_log");
    QSqlQuery query1(*db_sql);

    QString stestQuery2("SELECT * FROM rest_userlogs LIMIT 1");
    QSqlQuery query2(*db_mysql);


    if(query1.exec(stestQuery1)){
        qDebug() << "LG:server log";

        QDir dir;
        QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcessServer.dll");
        squery = squery.arg(sdb_Rest);
        //personnel id
            squery = squery.arg("NULL");

        //personnel name
        if(PersonnelName.count() == 0)
            squery = squery.arg("NULL");
        else{
            squery = squery.arg(QString("'" + QString("%1").arg(PersonnelName) + "'"));
        }

        //food id
        if(FoodId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(FoodId));

        //food name
        if(FoodName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(FoodName) + "'");

        //reservation id
        if(reservationId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(reservationId));

        //food status
        squery = squery.arg(QString::number(foodStatus));

        //card finger
        if(bCardFinger){
            squery = squery.arg(QString::number(1));
            squery = squery.arg("NULL");
        }
        else{
            squery = squery.arg(QString::number(2));
            squery = squery.arg("'" + CardNumber + "'");
        }

        //delivery id
            squery = squery.arg("NULL");

        //delivery name
        if(PersonnelName.count() == 0)
            squery = squery.arg("NULL");
        else{
            squery = squery.arg(QString("'" + QString("%1").arg(PersonnelName) + "'"));
        }

        //device id
        squery = squery.arg(QString::number(DeviceId));
        QSqlQuery query(*db_sql);
        if(!query.exec(squery)){
            qDebug() << "LG:sql server error: " << query.lastError().text();
            //local insert
            qDebug() << "LG:local log";
            QDir dir;
            QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcess.dll");
            //personnel id
                squery = squery.arg("NULL");
            //personnel code
            if(PersonnelName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + PersonnelName + "'");

            //personnel name
            if(PersonnelName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + QString("%1").arg(PersonnelName) + "'");

            //food id
            if(FoodId == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg(QString::number(FoodId));

            //food name
            if(FoodName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + QString("%1").arg(FoodName) + "'");

            //reservation id
            if(reservationId == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg(QString::number(reservationId));

            //food status
            squery = squery.arg(QString::number(foodStatus));

            //card finger
            if(bCardFinger){
                squery = squery.arg(QString::number(1));
                squery = squery.arg("NULL");
            }
            else{
                squery = squery.arg(QString::number(2));
                squery = squery.arg("'" + CardNumber + "'");
            }

            //delivery id
                squery = squery.arg("NULL");

            //delivery name
            if(PersonnelName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + QString("%1").arg(PersonnelName) + "'");

            //device id
            squery = squery.arg(QString::number(DeviceId));
            QSqlQuery query(*db_mysql);
            query.exec(squery);
            if(!query.isValid()){
                qDebug() << "LG:mysql error: " << query.lastError().text();
            }
        }
    }

    //local insert
    else if(query2.exec(stestQuery2)){
        qDebug() << "LG:local log";
        QDir dir;
        QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcess.dll");
        //personnel id
            squery = squery.arg("NULL");

        //personnel code
        if(PersonnelName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + PersonnelName + "'");

        //personnel name
        if(PersonnelName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(PersonnelName) + "'");

        //food id
        if(FoodId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(FoodId));

        //food name
        if(FoodName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(FoodName) + "'");

        //reservation id
        if(reservationId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(reservationId));

        //food status
        squery = squery.arg(QString::number(foodStatus));

        //card finger
        if(bCardFinger){
            squery = squery.arg(QString::number(1));
            squery = squery.arg("NULL");
        }
        else{
            squery = squery.arg(QString::number(2));
            squery = squery.arg("'" + CardNumber + "'");
        }

        //delivery id
            squery = squery.arg("NULL");

        //delivery name
        if(PersonnelName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(PersonnelName) + "'");

        //device id
        squery = squery.arg(QString::number(DeviceId));
        QSqlQuery query(*db_mysql);
        query.exec(squery);
        if(!query.isValid()){
            qDebug() << "LG:mysql error: " << query.lastError().text();
        }
    }
    else{
        qDebug() << "LG:-->>>>>>>>>No Db is open";
        return;
    }
}

void LogManagement::slot_fromlog_insertAccess(quint32 quiTerminalId, quint32 length, QString RFID_data, quint32 qui_UserID, quint8 qui_AuthMode, quint8 qui_AuthType, quint16 qui_Year, quint8 qui_Month, quint8 qui_Day, quint8 qui_Hour, quint8 qui_Min, quint8 qui_Sec, quint32 qui_AuthRes, bool bRes)
{

    qDebug() << "LG:1- check user and food on terminal " << quiTerminalId << "on DateTime " <<  qui_Year << "/" << qui_Month << "/" << qui_Day << " - " << qui_Hour << ":" << qui_Min << ":" << qui_Sec;
    qDebug() << "AuthMode: " << qui_AuthMode << " , AuthType: " << qui_AuthType;
    quint64 personalId = 0;
    QString PersonnelCode;
    PersonnelCode.clear();
    QString personalName;
    personalName.clear();
    int foodId = 0;
    QString foodName;
    int foodKind = 0;
    foodName.clear();
    int reservationId = 0;
    int foodStatus = -1;
    bool bCardFinger = false;
    QString CardNumber;
    CardNumber.clear();
    //bool ifPermission = false;
    
    if(length != 0){
        CardNumber = RFID_data;
        qDebug() << "LG:2- user auth with card";
        bCardFinger = false;
    }
    else{
        qDebug() << "LG:2- user auth with finger";
        bCardFinger = true;
    }
    bool get = false;
    bool user = false;

    int ffoodStatus = -1;

    // -2 virdi user ok system user nk
    // -1 not user
    // 0 food nk
    // 1 food ok log ok permission ok
    // 2 food ok log nk
    // 3 food ok log ok permission nk

    if(bRes){

        if(qui_UserID >= 99999990){
            func_log_GetMasterFood(quiTerminalId,length,RFID_data,qui_UserID,qui_AuthMode,qui_AuthType,qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes);
            return;
        }
        qDebug() << "LG:3- is user of this device";

        //check user on local
        QDir diruser;
        QString squeryuser = LoadQuery(diruser.currentPath() + "/SqlQuery/log-getUser.dll");
        squeryuser = squeryuser.arg(QString::number(qui_UserID));
        squeryuser = squeryuser.arg(QString::number(RestaurantId));
        QSqlQuery queryuser(*db_mysql);
        queryuser.exec(squeryuser);
        qDebug() << "LG:mysql error: " << queryuser.lastError().text();
        if(!queryuser.next()){
            user = false;
            ffoodStatus = -2;
            foodStatus = -2;
        }
        else{
            PersonnelCode = queryuser.value("PersonnelCode").toString();
            personalName = queryuser.value("PersonnelName").toString();
            qDebug() << "LG:4- user auth with PersonnelId " << qui_UserID;
            qDebug() << "LG:4- user auth with PersonnelCode " << PersonnelCode;
            user = true;
        }

        if(user){
            ffoodStatus = 0;
            foodStatus = 0;

            //check food on local
            personalId = qui_UserID;
            QDir dirfood;
            QString squeryfood = LoadQuery(dirfood.currentPath() + "/SqlQuery/log-getFood.dll");
            squeryfood = squeryfood.arg(QString::number(personalId));
            squeryfood = squeryfood.arg(QString::number(RestaurantId));
            qDebug() << "LG:5- check food for Personnel Id " << personalId;
            QSqlQuery queryfood(*db_mysql);
            queryfood.exec(squeryfood);
            qDebug() << "LG:mysql error: " << queryuser.lastError().text();
            if(queryfood.next()){
                qDebug() << "LG:6- food ok";
                ffoodStatus = 1;
                foodStatus = 1;

                //food
                PersonnelCode = queryfood.value("PersonnelCode").toString();
                personalName = queryfood.value("PersonnelName").toString();
                reservationId = queryfood.value("ReservationId").toInt();
                foodName = queryfood.value("FoodName").toString();
                foodKind = queryfood.value("FoodType").toInt();
                foodId = queryfood.value("FoodId").toInt();
                qDebug() << "LG:------------> Reservation Id = " << reservationId;

                //server log check
                QString stestQuery1("SELECT TOP 1 * FROM serv_restaurant_log");
                QSqlQuery query1(*db_sql);

                QString stestQuery2("SELECT * FROM rest_userlogs LIMIT 1");
                QSqlQuery query2(*db_mysql);

                if(query1.exec(stestQuery1)){
                    qDebug() << "LG:7- server check log";
                    QDir dircheckfood;
                    QString squerycheckfood = LoadQuery(dircheckfood.currentPath() + "/SqlQuery/log-checkFoodLogServer.dll");
                    squerycheckfood = squerycheckfood.arg(sdb_Rest);
                    squerycheckfood = squerycheckfood.arg(QString::number(personalId));
                    squerycheckfood = squerycheckfood.arg(QString::number(DeviceId));
                    squerycheckfood = squerycheckfood.arg(QString::number(reservationId));
                    QSqlQuery querycheckfood(*db_sql);
                    querycheckfood.exec(squerycheckfood);
                    qDebug() << "LG:sql server error: " << querycheckfood.lastError().text();
                    if(!querycheckfood.next()){
                        qDebug() << "LG:8- food ok and log ok";
                        get = true;
                        foodStatus = 1;
                        ffoodStatus = 1;


                        if(!func_log_checkPermistion(PersonnelCode,personalId)){
                            ffoodStatus = 3;
                            foodStatus = 3;
                            get = false;
                        }

                    }
                    else{
                        qDebug() << "LG:8- food ok and log nk";
                        get = false;
                        ffoodStatus = 2;
                        foodStatus = 2;
                    }
                }
                //local check log
                else if(query2.exec(stestQuery2)){
                    qDebug() << "LG:7- local check log";

                    QDir dircheckfood;
                    QString squerycheckfood = LoadQuery(dircheckfood.currentPath() + "/SqlQuery/log-checkFoodLog.dll");
                    squerycheckfood = squerycheckfood.arg(QString::number(personalId));
                    squerycheckfood = squerycheckfood.arg(QString::number(reservationId));
                    squerycheckfood = squerycheckfood.arg(QString::number(DeviceId));
                    QSqlQuery querycheckfood(*db_mysql);
                    querycheckfood.exec(squerycheckfood);
                    qDebug() << "LG:mysql error: " << querycheckfood.lastError().text();
                    if(!querycheckfood.next()){
                        qDebug() << "LG:8- food ok and log ok";
                        get = true;
                        foodStatus = 1;
                        ffoodStatus = 1;

                        if(!func_log_checkPermistion(PersonnelCode,personalId)){
                            ffoodStatus = 3;
                            foodStatus = 3;
                            get = false;
                        }
                    }
                    else{
                        qDebug() << "LG:8- food ok and log nk";
                        get = false;
                        ffoodStatus = 2;
                        foodStatus = 2;
                    }
                }
                else{
                    qDebug() << "LG:-------------------->********No Db is open";
                    return;
                }
            }
            else{
                qDebug() << "LG:6- food nk";
                ffoodStatus = 0;
                foodStatus = 0;
            }
            if(get){
                qDebug() << "LG:9- print receipt";
                emit this->sig_log_SendFoodCount(foodKind);
                PrintReceipt(QString("%1").arg(PersonnelCode),
                             QString::fromUtf8("شرکت بازرگانی سایپا یدک"),
                             (foodName),
                             QString::fromUtf8("غذای نوع %1").arg(foodKind),
                             personalName);
            }
        }
    }
    else if(qui_AuthRes == 3){
        //if(qui_UserID >= 99999990){
            //return;
        //}
        qDebug() << "LG:3- is user of this device without permission with user id " << qui_UserID ;
        personalId = qui_UserID;
        user = true;
    }
    else{
        qDebug() << "LG:4- is not user of this device";
        user = false;
    }

    qDebug() << "LG:show result on lcd";
    emit this->sig_log_UserLog(ffoodStatus,user,qui_UserID,foodKind,foodName,personalName,PersonnelCode);
    QString stestQuery1("SELECT TOP 1 * FROM serv_restaurant_log");
    QSqlQuery query1(*db_sql);

    QString stestQuery2("SELECT * FROM rest_userlogs LIMIT 1");
    QSqlQuery query2(*db_mysql);


    if(query1.exec(stestQuery1)){
        qDebug() << "LG:server log";

        QDir dir;
        QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcessServer.dll");
        squery = squery.arg(sdb_Rest);
        //personnel id
        if(bRes || (qui_AuthRes == 3))
            squery = squery.arg(QString::number(qui_UserID));
        else
            squery = squery.arg("NULL");

        //personnel name
        if(personalName.count() == 0)
            squery = squery.arg("NULL");
        else{
            squery = squery.arg(QString("'" + QString("%1").arg(personalName) + "'"));
        }

        //food id
        if(foodId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(foodId));

        //food name
        if(foodName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(foodName) + "'");

        //reservation id
        if(reservationId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(reservationId));

        //food status

        squery = squery.arg(QString::number(foodStatus));

        //card finger
        if(bCardFinger){
            squery = squery.arg(QString::number(1));
            squery = squery.arg("NULL");
        }
        else{
            squery = squery.arg(QString::number(2));
            squery = squery.arg("'" + CardNumber + "'");
        }

        //delivery id
        if(bRes || (qui_AuthRes == 3))
            squery = squery.arg(QString::number(qui_UserID));
        else
            squery = squery.arg("NULL");

        //delivery name
        if(personalName.count() == 0)
            squery = squery.arg("NULL");
        else{
            squery = squery.arg(QString("'" + QString("%1").arg(personalName) + "'"));
        }

        //device id
        squery = squery.arg(QString::number(DeviceId));
        QSqlQuery query(*db_sql);
        if(!query.exec(squery)){
            qDebug() << "LG:sql server error: " << query.lastError().text();
            //local insert
            qDebug() << "LG:local log";
            QDir dir;
            QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcess.dll");
            //personnel id
            if(bRes || (qui_AuthRes == 3))
                squery = squery.arg(QString::number(qui_UserID));
            else
                squery = squery.arg("NULL");
            //personnel code
            if(PersonnelCode.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + PersonnelCode + "'");

            //personnel name
            if(personalName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + QString("%1").arg(personalName) + "'");

            //food id
            if(foodId == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg(QString::number(foodId));

            //food name
            if(foodName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + QString("%1").arg(foodName) + "'");

            //reservation id
            if(reservationId == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg(QString::number(reservationId));

            //food status
            squery = squery.arg(QString::number(foodStatus));

            //card finger
            if(bCardFinger){
                squery = squery.arg(QString::number(1));
                squery = squery.arg("NULL");
            }
            else{
                squery = squery.arg(QString::number(2));
                squery = squery.arg("'" + CardNumber + "'");
            }

            //delivery id
            if(bRes || (qui_AuthRes == 3))
                squery = squery.arg(QString::number(qui_UserID));
            else
                squery = squery.arg("NULL");

            //delivery name
            if(personalName.count() == 0)
                squery = squery.arg("NULL");
            else
                squery = squery.arg("'" + QString("%1").arg(personalName) + "'");

            //device id
            squery = squery.arg(QString::number(DeviceId));
            QSqlQuery query(*db_mysql);
            query.exec(squery);
            if(!query.isValid()){
                qDebug() << "LG:mysql error: " << query.lastError().text();
            }
        }
    }

    //local insert
    else if(query2.exec(stestQuery2)){
        qDebug() << "LG:local log";
        QDir dir;
        QString squery = LoadQuery(dir.currentPath() + "/SqlQuery/log-InsertAcess.dll");
        //personnel id
        if(bRes || (qui_AuthRes == 3))
            squery = squery.arg(QString::number(qui_UserID));
        else
            squery = squery.arg("NULL");
        //personnel code
        if(PersonnelCode.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + PersonnelCode + "'");

        //personnel name
        if(personalName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(personalName) + "'");

        //food id
        if(foodId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(foodId));

        //food name
        if(foodName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(foodName) + "'");

        //reservation id
        if(reservationId == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg(QString::number(reservationId));

        //food status
        squery = squery.arg(QString::number(foodStatus));

        //card finger
        if(bCardFinger){
            squery = squery.arg(QString::number(1));
            squery = squery.arg("NULL");
        }
        else{
            squery = squery.arg(QString::number(2));
            squery = squery.arg("'" + CardNumber + "'");
        }

        //delivery id
        if(bRes || (qui_AuthRes == 3))
            squery = squery.arg(QString::number(qui_UserID));
        else
            squery = squery.arg("NULL");

        //delivery name
        if(personalName.count() == 0)
            squery = squery.arg("NULL");
        else
            squery = squery.arg("'" + QString("%1").arg(personalName) + "'");

        //device id
        squery = squery.arg(QString::number(DeviceId));
        QSqlQuery query(*db_mysql);
        query.exec(squery);
        if(!query.isValid()){
            qDebug() << "LG:mysql error: " << query.lastError().text();
        }
    }
    else{
        qDebug() << "LG:-->>>>>>>>>No Db is open";
        return;
    }
    return;
}



bool LogManagement::func_log_checkPermistion(QString PersonnelCode, quint64 PersonnelId)
{
    qDebug() << "LG:9- check access local";
    //check permission local and then server
    QDir dirchechpermission;
    QString squerycheckpermission = LoadQuery(dirchechpermission.currentPath() + "/SqlQuery/log-checkPermission.dll");
    squerycheckpermission = squerycheckpermission.arg(QString::number(PersonnelId));
    QSqlQuery querycheckpermission(*db_mysql);
    if(querycheckpermission.exec(squerycheckpermission)){
        if(querycheckpermission.next()){
            qDebug() << "LG:local check access " << querycheckpermission.value("failure_to_Present").toInt();
            if(querycheckpermission.value("failure_to_Present").toInt() == 0){
                qDebug() << "LG:local check access failure";
                QDir dirchechpermissionserver;
                QString squerycheckpermissionserver = LoadQuery(dirchechpermissionserver.currentPath() + "/SqlQuery/log-checkPermissionServer.dll");
                squerycheckpermissionserver = squerycheckpermissionserver.arg(sdb_Access);
                squerycheckpermissionserver = squerycheckpermissionserver.arg("'" + PersonnelCode + "'");
                qDebug() << "LG:server check access";
                QSqlQuery querycheckpermissionserver(*db_sql);
                if(querycheckpermissionserver.exec(squerycheckpermissionserver)){
                    if(querycheckpermissionserver.next())
                        qDebug() << "LG:server check access " << querycheckpermissionserver.value("isPresent").toInt();
                        if(querycheckpermissionserver.value("isPresent").toInt() == 0)
                                return false;
                }
                else{
                    qDebug() << "LG:server check access error " << querycheckpermissionserver.lastError().text();
                }
            }
            else{
                qDebug() << "LG:check access ok";
            }
        }
    }
    else{
        qDebug() << "LG:local check access error " << querycheckpermission.lastError().text();
    }
    return true;
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

void LogManagement::PrintReceipt(QString PersonalID,QString Explaned,QString foodName,QString Kind,QString Name)
{
    QPainter painter;
    printer->setPageMargins(0,0,0,0,QPrinter::Millimeter);

    painter.begin(printer);
    painter.setPen(QPen(Qt::black,3));

    painter.drawRect(0,0,550,120);
    //painter.drawRect(0,90,550,20);
    //painter.drawLine(0,70,500,70);
    //painter.drawLine(0,71,500,71);
    //painter.drawLine(0,72,500,72);

    //painter.drawLine(0,278,500,278);
    //painter.drawLine(0,279,500,279);
    //painter.drawLine(0,280,500,280);

    //painter.drawLine(0,70,0,280);
    //painter.drawLine(1,70,1,280);
    //painter.drawLine(2,70,2,280);

    //painter.drawLine(498,70,498,280);
    //painter.drawLine(499,70,499,280);
    //painter.drawLine(500,70,500,280);

    //painter.drawLine(0,210,500,210);
    //painter.drawLine(0,210+1,500,210+1);
    //painter.drawLine(0,210+1+1,500,210+1+1);

    QFont font("B Nazanin",10,QFont::Bold);
    QFont fontSmall("B Nazanin",9);
    //QFont fontBold("B Nazanin",15,QFont::Bold);

    QDateConvertor mdate;
    QStringList today = mdate.Today();
    QString month = today[1];
    QString day = today[2];
    QString year = today[0];
    QString date = year + " / " + month + " / " + day;
    QString Time = QDateTime::currentDateTime().toString("hh:mm");

    //QRect rect1(0,0,500,70);
    //painter.setFont(fontBold);
    //painter.drawText(rect1,Qt::AlignCenter | Qt::TextWordWrap,Explaned);

    //painter.drawLine(0,70,500,70);
    //painter.drawLine(0,70+1,500,70+1);
    //painter.drawLine(0,70+1+1,500,70+1+1);

    painter.setFont(font);
    QRect rect2(0,0,548,40);
    painter.drawText(rect2,Qt::AlignRight | Qt::TextWordWrap,
                     QString("%1 %2 %3").arg(QString::fromUtf8("نام")).arg(" - ").arg(Name));
    QRect rect3(1,40,548,40);
    painter.drawText(rect3,Qt::AlignRight | Qt::TextWordWrap,
                     QString("%1 %2 %3").arg(" - ").arg(QString::fromUtf8("شماره پرسنلی")).arg(PersonalID));
    QRect rect4(1,80,548,40);
    painter.drawText(rect4,Qt::AlignRight | Qt::TextWordWrap,QString("%1 %2 %3").arg(Kind).arg(foodName).arg(" - "));

    painter.setFont(fontSmall);
    QRect rect5(0,0,548,25);
    painter.drawText(rect5,Qt::AlignLeft | Qt::TextWordWrap,
                     date +
                     "   " +
                     Time);
    painter.end();
}

void LogManagement::setTime()
{
  time = time - 1 ;
  if(time < 0){
      qDebug() << "offline terminal";
      emit this->sig_log_onlineTerminal(false);
  }
}

void LogManagement::slot_log_chechkNet(bool status)
{
    net = status;
}

void LogManagement::slot_log_chechkVirdi(bool status)
{
    virdi = status;
}

void LogManagement::slot_log_netCable(bool status)
{
    netCable = status;
}

void LogManagement::slot_log_testTimerTimeout()
{
    //emit this->sig_log_SendFoodCount(1);
    //emit this->sig_log_SendFoodCount(2);
    //emit this->sig_log_SendFoodCount(3);
    //emit this->sig_log_SendFoodCount(4);
}
