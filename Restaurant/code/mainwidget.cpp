#include "mainwidget.h"
#include "ui_mainwidget.h"

static MainWidget* Main = nullptr;


static UCSAPI_CALLBACK_EVENT_HANDLER __attribute__((stdcall)) CallbackStartServer(UCSAPI_UINT32 TerminalID,UCSAPI_UINT32 EventType,UCSAPI_UINT32 wParam,UCSAPI_UINT32 lParam)
{
    if(Main)
        emit Main->CallBackSignal(TerminalID,EventType,wParam,lParam);
    return nullptr;
}

void MainWidget::CallBackSlot(UCSAPI_UINT32 TerminalID,
                            UCSAPI_UINT32 EventType,
                            UCSAPI_UINT32 wParam,
                            UCSAPI_UINT32 lParam)
{
    if( EventType == UCSAPI_CALLBACK_EVENT_CONNECTED){
        UCSAPI_CALLBACK_PARAM_0_PTR pCallBack0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam); //(UCSAPI_CALLBACK_PARAM_0*)wParam;
        UCS_ClientId = pCallBack0->ClientID;
        emit this->sig_main_firstConnect(TerminalID,UCS_ClientId);
        delete pCallBack0;
        delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam);
        return;
    }

    else if(EventType == UCSAPI_CALLBACK_EVENT_TERMINAL_STATUS){
        UCSAPI_TERMINAL_STATUS_PTR pStatus = reinterpret_cast<UCSAPI_TERMINAL_STATUS_PTR>(lParam);
        qDebug() << "MAIN-->:received status from terminal: " << TerminalID;
        qui_TerminaId_Status = TerminalID;
        emit this->sig_main_getTerminalStatus(qui_TerminaId_Status);
        delete pStatus;
        delete reinterpret_cast<UCSAPI_TERMINAL_STATUS_PTR>(lParam);
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_REALTIME_ACCESS_LOG){
        if(!virdi)
            return;
        UCSAPI_CALLBACK_PARAM_1_PTR  pCallback1 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_1_PTR>(lParam);
        UCSAPI_CALLBACK_PARAM_0_PTR  pCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam);
        if(pCallback1 && pCallback0){
            if(pCallback1->DataType == UCSAPI_CALLBACK_DATA_TYPE_ACCESS_LOG){

            qui_TerminalId_auto = TerminalID;
            qui_RFID_length_auto = pCallback1->Data.AccessLog->RFID->Length;
            memcpy(RFID_data_auto,pCallback1->Data.AccessLog->RFID->Data,8);
            qDebug() << "qui_RFID_length_auto = " << pCallback1->Data.AccessLog->RFID->Length;;

            //for(int i=0; i<8; i++)
                //qDebug() << RFID_data_auto[i];
            //qDebug() << "qui_RFID_length_auto = " << RFID_data_auto;
            qui_UserID_auto = pCallback1->Data.AccessLog->UserID;

            qui_AuthMode_auto = pCallback1->Data.AccessLog->AuthMode;
            qui_AuthType_auto = pCallback1->Data.AccessLog->AuthType;

            qui_Year_auto =  pCallback1->Data.AccessLog->DateTime.Year;
            qui_Month_auto = pCallback1->Data.AccessLog->DateTime.Month;
            qui_Day_auto = pCallback1->Data.AccessLog->DateTime.Day;
            qui_Hour_auto = pCallback1->Data.AccessLog->DateTime.Hour;
            qui_Min_auto = pCallback1->Data.AccessLog->DateTime.Min;
            qui_Sec_auto = pCallback1->Data.AccessLog->DateTime.Sec;

            qui_AuthRes_auto = pCallback1->Data.AccessLog->AuthResult;
            //qDebug() << "qui_AuthRes_auto = " << qui_AuthRes_auto;
            bRes_auto = pCallback1->Data.AccessLog->IsAuthorized;
            //qDebug() << "auth res in callback : " << bRes;
            emit this->sig_main_realTimeAccessLog(qui_TerminalId_auto,qui_RFID_length_auto,RFID_data_auto,qui_UserID_auto,qui_AuthMode_auto,qui_AuthType_auto,
                                                  qui_Year_auto,qui_Month_auto,qui_Day_auto,qui_Hour_auto,qui_Min_auto,qui_Sec_auto,qui_AuthRes_auto,bRes_auto);
            }
            delete pCallback1;
            delete pCallback0;
            delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_1_PTR>(lParam);
            delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam);
        }
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_DELETE_ALL_USER){
        if(bTimeout)
            return;
        emit this->sig_main_deleteAllUser(wParam,TerminalID);
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_ADD_USER){
        if(bTimeout)
            return;
        retUserID = lParam;
        emit this->sig_main_addUser(retUserID,wParam,TerminalID);
        return;

    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_DELETE_USER){
        if(bTimeout)
            return;
        retUserID = lParam;
        emit this->sig_main_deleteUser(retUserID,wParam,TerminalID);
        return;

    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_DISCONNECTED){
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_ACCESS_LOG){
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_SET_ACCESS_CONTROL_DATA){
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_ACCESS_LOG_COUNT){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_TERMINAL_TIME){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_USER_COUNT){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_USER_INFO_LIST){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_USER_DATA){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_VERIFY_USER_AUTH_INFO){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_VERIFY_FINGER_1_TO_1){ 
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_VERIFY_FINGER_1_TO_N){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_VERIFY_CARD){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_VERIFY_PASSWORD){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_TERMINAL_OPTION){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_SET_TERMINAL_OPTION){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_FW_UPGRADING){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_FW_UPGRADED){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_FW_VERSION){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_OPEN_DOOR){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_TERMINAL_CONTROL){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_PICTURE_LOG){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_ANTIPASSBACK){
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_VERIFY_USER_AUTH_INFO){
        return;
    }
    else {
        qDebug() << "MAIN-->:Invalid call back type";
        return;
    }
}


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    Main = this;
    qDebug() << "MAIN-->:Start";
    connect(this,SIGNAL(sig_main_start()),
            this,SLOT(slot_Main_start()),
            Qt::QueuedConnection);
    emit this->sig_main_start();
}



MainWidget::~MainWidget()
{
    StopApp();
    delete ui;
}

void MainWidget::slot_Main_start()
{
    ConfigMain();
    //slot_main_onNetCheck();
    StartMainThread();
    StartWebsocketThread();
    StartUserThread();
    //StartTerminalThread();
    StartLogThread();
    ManageConnection();  
    slot_checkLCD();
    //thread()->msleep(4000);
}

void MainWidget::ConfigMain()
{
    qDebug() << "MAIN-->:Config Class";



    timerTime.setSingleShot(false);
    timerTime.start(700);

    timerChangeUiForLog.setSingleShot(true);

    bInProc = false;
    UCS_bStarted = false;
    BSP_bStarted = false;
    iCMDTimeout = 0;
    bTimeout = false;


    UCS_ClientId = 0;
    UCS_MaxTerminal = 0;
    UCS_PortNumber = 0;

    QSettings setting("config.dll",QSettings::IniFormat);
    UCS_MaxTerminal = static_cast<UCSAPI_UINT32>(setting.value("UCS/max_reader",1).toInt());
    UCS_PortNumber = static_cast<UCSAPI_UINT32>(setting.value("UCS/ucs_port",9870).toInt());
    iCMDTimeout = setting.value("Main/cmd_timeout",500).toInt();
    check_url = setting.value("Main/ping_url","").toString();
    VirdiIp = setting.value("UCS/virdi_ip","").toString();
    tcpConnectionServer = false;
    tcpConnectionVirdi = false;


    sIniDate = setting.value("Counter/date","").toString();
    if(countDate.currentDate().toString() == sIniDate){
        iFoodCount1 = setting.value("Counter/count1",0).toInt();
        iFoodCount2 = setting.value("Counter/count2",0).toInt();
        iFoodCount3 = setting.value("Counter/count3",0).toInt();
        iFoodCount4 = setting.value("Counter/count4",0).toInt();
        iFoodCount = 0;
    }
    else{
        iFoodCount1 = 0;
        iFoodCount2 = 0;
        iFoodCount3 = 0;
        iFoodCount4 = 0;
        iFoodCount = 0;
        setting.setValue("Counter/count1",0);
        setting.setValue("Counter/count2",0);
        setting.setValue("Counter/count3",0);
        setting.setValue("Counter/count4",0);
        setting.setValue("Counter/date",countDate.currentDate().toString());
    }


    tCMD.setSingleShot(true);
    connect(&tCMD,SIGNAL(timeout()),
            this,SLOT(slot_cmd_timeout()),
            Qt::QueuedConnection);

    tNetCheck.setSingleShot(false);
    tNetCheck.start(5000);


    tcheckLCD.setSingleShot(false);
    tcheckLCD.start(60000);
    connect(&tcheckLCD,SIGNAL(timeout()),
            this,SLOT(slot_checkLCD()),
            Qt::QueuedConnection);


    net = false;
    virdi = false;

    tCheckDb.setSingleShot(false);
    connect(&tCheckDb,SIGNAL(timeout()),this,SLOT(slot_check_database()),Qt::QueuedConnection);


    sDbConnectionNameMysql = setting.value("MySql/db_connection_main","").toString();
    sDbHostMysql = setting.value("MySql/db_host","").toString();
    iDbPortMysql = setting.value("MySql/db_port",0).toInt();
    sDBNameMysql = setting.value("MySql/db_name","").toString();
    sDbUserMysql = setting.value("MySql/db_user","").toString();
    sDbPassMysql = setting.value("MySql/db_pass","").toString();

//    sDbHostSql = setting.value("SqlServer/db_host","").toString();
//    iDbPortSql = setting.value("SqlServer/db_port",0).toInt();


    iTimeout = setting.value("Main/db_timeout",5).toInt();

    i_foodFontSize = setting.value("Main/foodfontsize",20).toInt();
    s_foodFontName = setting.value("Main/foodfontname","").toString();

    i_dateFontSize = setting.value("Main/datefontsize",20).toInt();
    s_dateFontName = setting.value("Main/datefontname","").toString();

    i_timeFontSize = setting.value("Main/timefontsize",20).toInt();
    s_timeFontName = setting.value("Main/timefontname","").toString();

    db_mysql = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL",sDbConnectionNameMysql));
    db_mysql->setDatabaseName(sDBNameMysql);
    db_mysql->setUserName(sDbUserMysql);
    db_mysql->setPassword(sDbPassMysql);
    db_mysql->setPort(iDbPortMysql);
    bDbopened_MySql = false;
    db_mysql->setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1");

    DeviceId = 0;
    RestaurantId = 0;
    DeviceId = setting.value("Main/device_id",0).toInt();
    RestaurantId = setting.value("Main/restaurant_id",0).toInt();

    if(db_mysql->open()){
        bDbopened_MySql = true;
        qDebug() << "MAIN-->:---------->mysql connection open";
    }
    else{
        bDbopened_MySql = false;
        qDebug() << "MAIN-->:---------->mysql connection error -  " << db_mysql->lastError().text();
    }


    connect(this,SIGNAL(CallBackSignal(UCSAPI_UINT32,UCSAPI_UINT32,UCSAPI_UINT32,UCSAPI_UINT32)),
            this,SLOT(CallBackSlot(UCSAPI_UINT32,UCSAPI_UINT32,UCSAPI_UINT32,UCSAPI_UINT32 )),
            Qt::DirectConnection);

    prepareLCD();
    return;
}

void MainWidget::slot_check_database()
{
    qDebug() << "MAIN-->:---------->check db";
    if(bDbopened_MySql == true){
        QString stestQuery("SELECT * FROM rest_userlogs LIMIT 1");
        QSqlQuery query(*db_mysql);
        if(!query.exec(stestQuery)){
            qDebug() << "MAIN-->:---------->mysql connection error - "  << query.lastError().text();
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
    else{
        if(db_mysql->open()){
            bDbopened_MySql = true;
            qDebug() << "MAIN-->:---------->mysql connection open";
        }
        else{
            bDbopened_MySql = false;
            qDebug() << "MAIN-->:---------->mysql connection error - " << db_mysql->lastError().text();

        }
    }
    tCheckDb.start(iTimeout * 1000);
}

void MainWidget::slot_cmd_timeout()
{
    qDebug() << "MAIN-->:cmd timeout";
    tCMD.stop();
    bTimeout = true;
    bInProc = false;
    return;
}

void MainWidget::StartMainThread()
{
    UCS_bStarted = UCS_Start(UCS_MaxTerminal,UCS_PortNumber);
    if(!UCS_bStarted){
        QApplication::quit();
    }
    BSP_bStarted = BSP_Start(&BSP_Handle);
    return;
}

void MainWidget::StartWebsocketThread()
{
    thp_WebSocket = new QThread;
    wop_Websocket = new WebSocket;
    connect(wop_Websocket,SIGNAL(sig_Start_Thread()),wop_Websocket,SLOT(slot_Start_WS_Thread()),
            Qt::QueuedConnection);
    connect(wop_Websocket,SIGNAL(sig_Stop_Thread()),wop_Websocket,SLOT(slot_Stop_WS_Thread()),
            Qt::QueuedConnection);

    wop_Websocket->moveToThread(thp_WebSocket);
    thp_WebSocket->start();
    emit wop_Websocket->sig_Start_Thread();


}

void MainWidget::StartUserThread()
{
    thp_User = new QThread;
    wop_User = new UserManagement;
    connect(wop_User,SIGNAL(sig_Start_Thread()),wop_User,SLOT(slot_Start_User_Thread()),Qt::QueuedConnection);
    connect(wop_User,SIGNAL(sig_Stop_Thread()),wop_User,SLOT(slot_Stop_User_Thread()),Qt::QueuedConnection);
    wop_User->moveToThread(thp_User);
    thp_User->start();
    emit wop_User->sig_Start_Thread();
}

void MainWidget::StartLogThread()
{
    thp_Log = new QThread;
    wop_Log = new LogManagement;
    connect(wop_Log,SIGNAL(sig_Start_Thread()),wop_Log,SLOT(slot_Start_Log_Thread()),
            Qt::QueuedConnection);

    connect(wop_Log,SIGNAL(sig_Stop_Thread()),wop_Log,SLOT(slot_Stop_Log_Thread()),
            Qt::QueuedConnection);

    wop_Log->moveToThread(thp_Log);
    thp_Log->start();
    emit wop_Log->sig_Start_Thread();
}

void MainWidget::ManageConnection()
{
    //connect(this,SIGNAL(sig_main_inproc(bool)),wop_Websocket,SLOT(slot_frommain_proc(bool)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_main_firstConnect(quint32,quint32)),
            this,SLOT(slot_frommain_firstconnections(quint32,quint32)),
            Qt::QueuedConnection);

    connect(this,SIGNAL(sig_main_realTimeAccessLog(quint32,quint32,BYTE*,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            wop_Log,SLOT(slot_frommain_RealTimeLog(quint32,quint32,BYTE*,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            Qt::QueuedConnection);

    connect(this,SIGNAL(sig_main_getTerminalStatus(quint32)),
            wop_Log,SLOT(slot_frommain_TerminalStatus(quint32)),
            Qt::QueuedConnection);

    connect(&timerTime,SIGNAL(timeout()),
            this,SLOT(setTime()),
            Qt::QueuedConnection);

    connect(&timerChangeUiForLog,SIGNAL(timeout()),
            this,SLOT(reset_LCD_user()),
            Qt::QueuedConnection);


    connect(&tNetCheck,SIGNAL(timeout()),
            this,SLOT(slot_main_onNetCheck()),
            Qt::QueuedConnection);

    connect(wop_Log,SIGNAL(sig_log_onlineTerminal(bool)),
            this,SLOT(slot_main_TerminalStaus(bool)),
            Qt::QueuedConnection);

    connect(wop_Log,SIGNAL(sig_DB_Open(bool)),
            this,SLOT(slot_check_dbConnection(bool)),
            Qt::QueuedConnection);

    connect(wop_Log,SIGNAL(sig_log_UserLog(int,bool,quint32,int,QString,QString,QString)),
            this,SLOT(slot_main_userLog(int,bool,quint32,int,QString,QString,QString)),
            Qt::QueuedConnection);

    connect(wop_Log,SIGNAL(sig_log_SendFoodCount(int)),
            this,SLOT(slot_main_GetFoodCount(int)),
            Qt::QueuedConnection);


    //user
    connect(wop_User,SIGNAL(invaid_cmd()),
            wop_Websocket,SLOT(slot_fromuser_invalid()),
            Qt::QueuedConnection);

        //from socket to user (cmd)
        connect(wop_Websocket,SIGNAL(sig_touser_cmd_add(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_add(QString)),
                Qt::QueuedConnection);

        connect(wop_Websocket,SIGNAL(sig_touser_cmd_del(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_del(QString)),
                Qt::QueuedConnection);

        connect(wop_Websocket,SIGNAL(sig_touser_cmd_delall(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_delall(QString)),
                Qt::QueuedConnection);


        connect(wop_Websocket,SIGNAL(sig_touser_cmd_add_master(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_add_master(QString)),
                Qt::QueuedConnection);

        connect(wop_Websocket,SIGNAL(sig_touser_cmd_del_master(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_del_master(QString)),
                Qt::QueuedConnection);

        //from user to main (functions)
        connect(wop_User,SIGNAL(sig_tomain_cmd_add(quint32,quint32,QString,QString,QString,bool,int,int,int,int,int,int)),
                this,SLOT(slot_fromuser_cmd_add(quint32,quint32,QString,QString,QString,bool,int,int,int,int,int,int)),
                Qt::QueuedConnection);

        connect(wop_User,SIGNAL(sig_tomain_cmd_del(quint32,quint32)),
                this,SLOT(slot_fromuser_cmd_del(quint32,quint32)),
                Qt::QueuedConnection);

        connect(wop_User,SIGNAL(sig_tomain_cmd_delall(quint32)),
                this,SLOT(slot_fromuser_cmd_delall(quint32)),
                Qt::QueuedConnection);

        //from main to main (callback)
        connect(this,SIGNAL(sig_main_addUser(quint32,quint32, quint32)),
                this,SLOT(slot_frommain_AddUserCallBackRes(quint32,quint32,quint32)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_deleteUser(quint32,quint32,quint32)),
                this,SLOT(slot_frommain_DelUserCallBackRes(quint32,quint32,quint32)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_deleteAllUser(quint32, quint32)),
                this,SLOT(slot_frommain_DelAllUsersCallBackRes(quint32,quint32)),
                Qt::QueuedConnection);

        //from main to user (resp)
        connect(this,SIGNAL(sig_main_resp_deleteall(bool,int,quint32)),
                wop_User,SLOT(slot_frommain_resp_deleteall(bool,int,quint32)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_resp_delete(quint32,bool,int,quint32)),
                wop_User,SLOT(slot_frommain_resp_delete(quint32,bool,int,quint32)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_resp_add(quint32,bool,int,quint32)),
                wop_User,SLOT(slot_frommain_resp_add(quint32,bool,int,quint32)),
                Qt::QueuedConnection);

        //from user to socket
        connect(wop_User,SIGNAL(sig_user_finishedCMD()),
                wop_Websocket,SLOT(sig_user_finishedCMD()),
                Qt::QueuedConnection);


        //check connection to db
        connect(this,SIGNAL(sig_main_netStatus(bool)),
                wop_Websocket,SLOT(slot_socket_chechkNet(bool)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_netStatus(bool)),
                wop_Log,SLOT(slot_log_chechkNet(bool)),
                Qt::QueuedConnection);

        //check connection to terminal
        connect(this,SIGNAL(sig_main_virdiStatus(bool)),
                wop_Websocket,SLOT(slot_socket_chechkVirdi(bool)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_virdiStatus(bool)),
                wop_Log,SLOT(slot_log_chechkVirdi(bool)),
                Qt::QueuedConnection);


        connect(this,SIGNAL(sig_main_netCable(bool)),
                wop_Websocket,SLOT(slot_socket_netCable(bool)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_netCable(bool)),
                wop_User,SLOT(slot_user_netCable(bool)),
                Qt::QueuedConnection);

        connect(this,SIGNAL(sig_main_netCable(bool)),
                wop_Log,SLOT(slot_log_netCable(bool)),
                Qt::QueuedConnection);





}

void MainWidget::StopApp()
{
    UCS_Stop();
    BSP_Stop(BSP_Handle);

    emit wop_Websocket->sig_Stop_Thread();
    thp_WebSocket->deleteLater();

    emit wop_User->sig_Stop_Thread();
    thp_User->deleteLater();

    emit wop_Log->sig_Stop_Thread();
    thp_Log->deleteLater();

    qDebug() << "MAIN-->:END";
}

//SDK Start Stop
//SDK Start Stop
bool MainWidget::UCS_Start(UCSAPI_UINT32 UCS_maxTerminal, UCSAPI_UINT32 UCS_portNumber)
{
    UCSAPI_RETURN ret = UCSAPI_ServerStart(UCS_maxTerminal,UCS_portNumber,0,reinterpret_cast<UCSAPI_CALLBACK_EVENT_HANDLER>(CallbackStartServer));
    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can UCS SDK Start: UCSAPIERR_NONE";
        return true;
    }
    else if(ret == UCSAPIERR_FUNCTION_FAIL){
        qDebug() << "MAIN-->:Can Not Server Start: UCSAPIERR_FUNCTION_FAIL";
        return false;
    }
    else{
        qDebug() << "MAIN-->:Can Not Server Start: UCSAPIError_UNKNOWN";
        return false;
    }
}

bool MainWidget::BSP_Start(UCBioAPI_HANDLE_PTR pHandle)
{
     UCBioAPI_RETURN ret = UCBioAPI_Init(pHandle);
     if(ret == UCBioAPIERROR_NONE){
         qDebug() << "MAIN-->:Can BSP SDK Start: UCBioAPIERROR_NONE";
         return true;
     }
     else if(ret == UCBioAPIERROR_INVALID_POINTER){
         qDebug() << "MAIN-->:Can Not BSP SDK Start: UCBioAPIERROR_INVALID_POINTER";
         return false;
     }
      else if(ret == UCBioAPIERROR_VALIDITY_FAIL){
          qDebug() << "MAIN-->:Can Not BSP SDK Start: UCBioAPIERROR_VALIDITY_FAIL";
          return false;
      }
      else if(ret == UCBioAPIERROR_EXPIRED_VERSION){
          qDebug() << "MAIN-->:Can Not BSP SDK Start: UCBioAPIERROR_EXPIRED_VERSION";
          return false;
      }
     else{
         qDebug() << "MAIN-->:Can Not BSP SDK Start: UCBioAPIError_UNKNOWN";
         return false;
     }
}

bool MainWidget::UCS_Stop()
{
    UCSAPI_RETURN ret = UCSAPI_ServerStop();
    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can UCS SDK Stop: UCSAPIERR_NONE";
        return true;
    }
    else{
        qDebug() << "MAIN-->:Can Not UCS SDK Stop: UCSAPIError_UNKNOWN";
        return false;
    }
}

bool MainWidget::BSP_Stop(UCBioAPI_HANDLE Handle)
{
    UCBioAPI_RETURN ret = UCBioAPI_Terminate(Handle);
    if(ret == UCBioAPIERROR_NONE){
        qDebug() << "MAIN-->:Can BSP SDK Stop: UCBioAPIERROR_NONE";
        return true;
    }
    else if(ret == UCBioAPIERROR_INVALID_HANDLE){
        qDebug() << "MAIN-->:Can Not BSP SDK Stop: UCBioAPIERROR_NONE";
        return false;
    }
    else{
        qDebug() << "MAIN-->:Can Not Server Stop: UCBioAPIError_UNKNOWN";
        return false;
    }
}
//SDK Start Stop
//SDK Start Stop

//Add User
//Add User

void MainWidget::CreateNullFaceInfo()
{
    UCS_FaceInfo.Length = 0;
    UCS_FaceInfo.Data = nullptr;
}

void MainWidget::CreateNullCardInfo()
{
    UCS_NullCard.Length = 0;
    UCS_NullCard.Data = nullptr;
}

void MainWidget::CreateValidCard(QString CardCSN)
{
    UCS_ValidCard.Length = static_cast<UCSAPI_UINT32>(CardCSN.count());


    qDebug() << "MAIN-->:UCS_ValidCard.Length = " << UCS_ValidCard.Length;
    //UCS_ValidCard.Data = new UCSAPI_CHAR[UCS_ValidCard.Length];
    //for(int i=0 ; i<CardCSN.count() ; i++)
        //qDebug() << CardCSN.toLocal8Bit()[i];
    memcpy(UCS_ValidCard.Data,CardCSN.toLocal8Bit(),UCS_ValidCard.Length);
    return;
}

void MainWidget::CreateNullFormat()
{
    UCS_Format[0] = 0;
    UCS_Format[1] = 0;
    UCS_Format[2] = 0;
    UCS_Format[3] = 0;
}

void MainWidget::CreateAllAndSendUser(quint32 TerminalId, quint32 UserId, QString PersonnelCode,QString TextFir, QString CardCSN,bool isAdmin,
                                      int isYear,int isMonth,int isDay,
                                      int ieYear,int ieMonth,int ieDay)
{

    bool textfir = false;
    qDebug() << "MAIN-->:User Text Fir lenght = " << TextFir.count();
    qDebug() << "MAIN-->:User Card CSN = " << CardCSN;
    //qDebug() << "MAIN-->:User isAdmin = " << isAdmin;

    quint8 iisAdmin = 0;
    if(isAdmin == true)
        iisAdmin = 1;

    qDebug() << "MAIN-->:User isAdmin = " << isAdmin;

    if(TextFir.count() != 0){
        if(!UCS_CreateExportData(TextFir)){
            tCMD.stop();
            emit this->sig_main_resp_add(UserId,false,SERVER_UNKNOWN,TerminalId);
            return;
        }
        textfir = true;
        CreateFingerData(UCBioAPI_TEMPLATE_FORMAT_UNION400,UCBioAPI_FIR_SECURITY_LEVEL_NORMAL,UCSAPI_TRUE,&BSP_ExportedData);
    }
    else{
        CreateFingerData(UCBioAPI_TEMPLATE_FORMAT_UNION400,UCBioAPI_FIR_SECURITY_LEVEL_NORMAL,UCSAPI_TRUE,nullptr);
    }

    //user name
    for(int i=0; i<20; i++)
        UserName[i] = 0;
    UCS_UserName.Length = 0;
    UCS_UserName.Data = UserName ;

    //access group
    for(int i=0; i<4; i++)
        UserGroupCode[i] = 0;
    UCS_AccessGroup.Length = 0;
    UCS_AccessGroup.Data = UserGroupCode;

    //personnel code
    for(int i=0; i<20; i++)
        UserPersonelCode[i] = 0;
    UCS_UniqueID.Length = static_cast<UCSAPI_UINT32>(PersonnelCode.count());
    for(int i=0; i<PersonnelCode.count(); i++)
        UserPersonelCode[i] = PersonnelCode.at(i).toLatin1();
    UCS_UniqueID.Data = UserPersonelCode;

    //csn null
    for(int i=0; i<20; i++)
        UserCSNNull[i] = 0;
    UCS_NullCard.Length = 0;
    UCS_NullCard.Data = UserCSNNull;

    //csn null
    for(int i=0; i<20; i++)
        UserCSN[i] = 0;
    UCS_ValidCard.Length = static_cast<UCSAPI_UINT32>(CardCSN.count());
    for(int i=0; i<CardCSN.count(); i++)
        UserCSN[i] = CardCSN.at(i).toLatin1();
    UCS_ValidCard.Data = UserCSN;
    
    UCS_AccessDate.StartDate.Year = static_cast<UCSAPI_UINT16>(isYear);
    UCS_AccessDate.StartDate.Month = static_cast<UCSAPI_UINT8>(isMonth);
    UCS_AccessDate.StartDate.Day = static_cast<UCSAPI_UINT8>(isDay);
    UCS_AccessDate.EndDate.Year = static_cast<UCSAPI_UINT16>(ieYear);
    UCS_AccessDate.EndDate.Month = static_cast<UCSAPI_UINT8>(ieMonth);
    UCS_AccessDate.EndDate.Day = static_cast<UCSAPI_UINT8>(ieDay);

    if(isYear != 0 && isMonth != 0 && isDay != 0 && ieYear != 0 && ieMonth != 0 && ieDay != 0)
        UCS_CreateAccessAuth(UCSAPI_DATE_TYPE_ALLOWED,&UCS_AccessDate,&UCS_AccessGroup);
    else
        UCS_CreateAccessAuth(UCSAPI_DATE_TYPE_NOT_USE,&UCS_AccessDate,&UCS_AccessGroup);


    //user data --> user info --> user property
    //user data --> auth data --> card data
    if(CardCSN.count() != 0 && TextFir.count() != 0){
        qDebug() << "MAIN-->:User both card and finger";
        UCS_CreateUserProperty(1,0,0,1,0,0,1,iisAdmin);
        UCS_CreateCardData(1,&UCS_ValidCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard);
    }
    else if(CardCSN.count() == 0 && TextFir.count() != 0){
       qDebug() << "MAIN-->:User just finger";
        UCS_CreateUserProperty(1,0,0,0,0,0,1,iisAdmin);
        UCS_CreateCardData(0,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard);
    }
    else if(CardCSN.count() == 0 && TextFir.count() == 0){
        qDebug() << "MAIN-->:User nothing";
        UCS_CreateUserProperty(0,0,0,0,0,0,1,iisAdmin);
        UCS_CreateCardData(0,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard);
    }
    else if(CardCSN.count() != 0 && TextFir.count() == 0){
        qDebug() << "MAIN-->:User just card";
        UCS_CreateUserProperty(0,0,0,1,0,0,1,iisAdmin);
        UCS_CreateCardData(1,&UCS_ValidCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard,&UCS_NullCard);
    }

    //user data --> auth data --> password data
    UCS_CreatePasswordData(0,nullptr);



    //user data --> auth data --> face data
    CreateNullFaceInfo();
    UCS_CreateFaceData(0,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo,&UCS_FaceInfo);

    //user data --> picture data
    UCS_CreatePictureData(0,UCS_Format,nullptr);

    //user data --> user info
    UCS_CreateUserinfoData(quint32(UserId),05,UCS_UserProperty,&UCS_UniqueID,&UCS_UserName,&UCS_AccessAuthority);

    //user data --> auth data
    UCS_CreateAuthData(&UCS_CardData,&UCS_FaceData,&UCS_FingerData,&UCS_PasswordData);

    //user data
    UCS_CreateUserData(&UCS_AuthData,UCS_UserInfo,&UCS_PictureData);


    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    int functionsRes = static_cast<int>(UCS_SendUserToTerminal(UCS_ClientId,TerminalId,UCSAPI_TRUE,&UCS_UserData));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_add(UserId,false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    //qDebug() << "MAIN-->:finish add user before callback";
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back add user";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_add(UserId,false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;
}

void MainWidget::slot_fromuser_cmd_add(quint32 TerminalId, quint32 UserID, QString PersonnelCode, QString TextFir, QString CardCSN,bool isAdmin,
                                       int isYear,int isMonth,int isDay,
                                       int ieYear,int ieMonth,int ieDay)
{
    if(TextFir.count()==0 && CardCSN.count()==0){
        emit this->sig_main_resp_add(UserID,false,SERVER_INVALID_DATA,TerminalId);
        return;
    }
    CreateAllAndSendUser(TerminalId,UserID,PersonnelCode,TextFir,CardCSN,isAdmin,
                         isYear,isMonth,isDay,
                         ieYear,ieMonth,ieDay);
    return;
}

int MainWidget::UCS_SendUserToTerminal(UCSAPI_UINT32 UCS_clientId,UCSAPI_UINT32 UCS_terminalId,UCSAPI_BOOL UCS_isOverwrite,UCSAPI_USER_DATA_PTR UCS_p_userData)
{
    qDebug() << "MAIN-->:Add User id " << UCS_p_userData->UserInfo.UserID <<  " to Terminal " << UCS_terminalId;

    UCSAPI_RETURN ret =  UCSAPI_AddUserToTerminal(quint16(UCS_clientId),UCS_terminalId,UCS_isOverwrite,UCS_p_userData);

    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_NONE";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_NOT_SERVER_ACTIVE";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else if(ret == UCSAPIERR_INVALID_POINTER){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_POINTER";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_POINTER;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_TERMINAL";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_TERMINAL;
    }
    else if(ret == UCSAPIERR_USER_NAME_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_USER_NAME_SIZE";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_USER_NAME_SIZE;
    }
    else if(ret == UCSAPIERR_UNIQUE_ID_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_UNIQUE_ID_SIZE";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_UNIQUE_ID_SIZE;
    }
    else if(ret == UCSAPIERR_INVALID_SECURITY_LEVEL){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_SECURITY_LEVEL";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_SECURITY_LEVEL;
    }
    else if(ret == UCSAPIERR_INVALID_PARAMETER){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_PARAMETER";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_PARAMETER;
    }
    else if(ret == UCSAPIERR_CODE_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_CODE_SIZE";
       //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_CODE_SIZE;
    }
    else if(ret == UCSAPIERR_PASSWORD_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_PASSWORD_SIZE";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_PASSWORD_SIZE;
    }
    else if(ret == UCSAPIERR_MAX_CARD_NUMBER){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_MAX_CARD_NUMBER";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_MAX_CARD_NUMBER;
    }
    else if(ret == UCSAPIERR_MAX_FINGER_NUMBER){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_MAX_FINGER_NUMBER";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_MAX_FINGER_NUMBER;
    }
    else if(ret == UCSAPIERR_PICTURE_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_PICTURE_SIZE";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_PICTURE_SIZE;
    }
    else{
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :SERVER_UNKNOWN";
        //UCBioAPI_FreeExportData(&BSP_ExportedData);
        return SERVER_UNKNOWN;
    }

}

void MainWidget::slot_frommain_AddUserCallBackRes(quint32 UserId,quint32 UCS_p_callback0,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:add user callback";

    UCS_p_AddUserCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_AddUserCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(UCS_p_callback0);

    int errorCode = static_cast<int>(UCS_p_AddUserCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;
    tCMD.stop();
    bInProc = false;
    emit this->sig_main_resp_add(UserId,success,errorCode,UCS_terminalID);
    delete UCS_p_AddUserCallback0;
    delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(UCS_p_callback0);

    return;
}

void MainWidget::UCS_CreateUserData(UCSAPI_AUTH_DATA_PTR UCS_p_authData,UCSAPI_USER_INFO UCS_userInfo,UCSAPI_PICTURE_DATA_PTR UCS_p_pictureData)
{
    
    //UserData.PictureData
    UCS_UserData.AuthData = UCS_p_authData;

    //UserData.UserInfo
    UCS_UserData.UserInfo = UCS_userInfo;

    //UserData.PictureData

    UCS_UserData.PictureData = UCS_p_pictureData;

}

//UCS_AuthData
void MainWidget::UCS_CreateAuthData(UCSAPI_CARD_DATA_PTR UCS_p_cardData,UCSAPI_FACE_DATA_PTR UCS_p_faceData,UCSAPI_FINGER_DATA_PTR UCS_p_fingerData,UCSAPI_DATA_PTR UCS_p_passwordData)
{
    //UCS_AuthData.Card
    UCS_AuthData.Card = UCS_p_cardData;

    //UCS_AuthData.Face
    UCS_AuthData.Face = UCS_p_faceData;

    //UCS_AuthData.finger
    UCS_AuthData.Finger = UCS_p_fingerData;

    //UCS_AuthData.Password
    UCS_AuthData.Password = UCS_p_passwordData;
}

//UCS_UserInfo
void MainWidget::UCS_CreateUserinfoData(UCSAPI_UINT32 UCS_userID,
                                        UCSAPI_UINT8 UCS_authType,
                                        UCSAPI_USER_PROPERTY UCS_userProperty,
                                        UCSAPI_DATA_PTR UCS_p_uniqueID,
                                        UCSAPI_DATA_PTR UCS_p_userName,
                                        UCSAPI_ACCESS_AUTHORITY_PTR UCS_p_accessAuthority)
{
    //UserInfo.UserID
    UCS_UserInfo.UserID = UCS_userID;

    //UserInfo.AuthType //UCSAPI_AUTH_TYPE_FINGER_1_TO_N   //0=not use
    UCS_UserInfo.AuthType = UCS_authType;

    //Userinfo.Property
    UCS_UserInfo.Property = UCS_userProperty;

    //UserInfo.UniqueID
    UCS_UserInfo.UniqueID = UCS_p_uniqueID;

    //UserInfo.UserName
    UCS_UserInfo.UserName = UCS_p_userName;

    //UserInfo.AcessFlag
    UCS_UserInfo.AcessFlag.Face1toN = 0;
    UCS_UserInfo.AcessFlag.reserved = 0;
    UCS_UserInfo.AcessFlag.blacklist = 0;
    UCS_UserInfo.AcessFlag.exceptpassback = 0;

    //UserInfo.AccessAuthority
    UCS_UserInfo.AccessAuthority = UCS_p_accessAuthority;
}

//UCS_PictureData
void MainWidget::UCS_CreatePictureData(UCSAPI_UINT32 UCS_length,UCSAPI_UINT8 UCS_format[4],UCSAPI_UINT8* UCS_p_data)
{
    //UserData.PictureData.Header
    UCS_PictureData.Header.Length = UCS_length;
    UCS_PictureData.Header.Format[0] = UCS_format[0];
    UCS_PictureData.Header.Format[1] = UCS_format[1];
    UCS_PictureData.Header.Format[2] = UCS_format[2];
    UCS_PictureData.Header.Format[3] = UCS_format[3];


    //UserData.PictureData.Data
    UCS_PictureData.Data = UCS_p_data;
}

//UCS_CardData
void MainWidget::UCS_CreateCardData(UCSAPI_UINT32 UCS_cardNum,UCSAPI_DATA_PTR UCS_p_cardData0,
                                                              UCSAPI_DATA_PTR UCS_p_cardData1,
                                                              UCSAPI_DATA_PTR UCS_p_cardData2,
                                                              UCSAPI_DATA_PTR UCS_p_cardData3,
                                                              UCSAPI_DATA_PTR UCS_p_cardData4)
{
    //UCS_CardData
    UCS_CardData.CardNum = UCS_cardNum;

    UCS_CardData.RFID[0] = UCS_p_cardData0;
    UCS_CardData.RFID[1] = UCS_p_cardData1;
    UCS_CardData.RFID[2] = UCS_p_cardData2;
    UCS_CardData.RFID[3] = UCS_p_cardData3;
    UCS_CardData.RFID[4] = UCS_p_cardData4;
}

//UCS_FaceData
void MainWidget::UCS_CreateFaceData(long UCS_faceNum,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo0,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo1,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo2,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo3,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo4,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo5,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo6,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo7,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo8,
                                    UCSAPI_FACE_INFO_PTR UCS_p_faceInfo9)

{
    //UCS_FaceData
    UCS_FaceData.FaceNumber = UCS_faceNum;

    UCS_FaceData.FaceInfo[0] = UCS_p_faceInfo0;
    UCS_FaceData.FaceInfo[1] = UCS_p_faceInfo1;
    UCS_FaceData.FaceInfo[2] = UCS_p_faceInfo2;
    UCS_FaceData.FaceInfo[3] = UCS_p_faceInfo3;
    UCS_FaceData.FaceInfo[4] = UCS_p_faceInfo4;
    UCS_FaceData.FaceInfo[5] = UCS_p_faceInfo5;
    UCS_FaceData.FaceInfo[6] = UCS_p_faceInfo6;
    UCS_FaceData.FaceInfo[7] = UCS_p_faceInfo7;
    UCS_FaceData.FaceInfo[8] = UCS_p_faceInfo8;
    UCS_FaceData.FaceInfo[9] = UCS_p_faceInfo9;
}

//UCS_fingerData
void MainWidget::CreateFingerData(UCSAPI_UINT8 UCS_templateFormat,UCSAPI_UINT8 UCS_securityLevel,UCSAPI_BOOL UCS_isCheckSimilarFinger,UCBioAPI_EXPORT_DATA_PTR BSP_p_exportData)
{
    //UCS_fingerData.DuressFinger
    for(int i = 0; i < 10; i++ )
        UCS_FingerData.DuressFinger[i] = 0;

    //UCS_fingerData.TemplateFormat //UCBioAPI_TEMPLATE_FORMAT_UNION400
    UCS_FingerData.TemplateFormat = UCS_templateFormat;

    //UCS_fingerData.SecurityLevel //UCBioAPI_FIR_SECURITY_LEVEL_NORMAL
    UCS_FingerData.SecurityLevel = UCS_securityLevel;

    //UCS_fingerData.IsCheckSimilarFinger
    UCS_FingerData.IsCheckSimilarFinger = UCS_isCheckSimilarFinger;

    //UCS_fingerData.ExportData
    UCS_FingerData.ExportData = BSP_p_exportData;
}

//UCS_PasswordData
void MainWidget::UCS_CreatePasswordData(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data)
{
    //UCS_PasswordData
    UCS_PasswordData.Length = UCS_length;
    UCS_PasswordData.Data = UCS_data;
}

//UCS_UserProperty
void MainWidget::UCS_CreateUserProperty(UCSAPI_UINT8 UCS_finger,UCSAPI_UINT8 UCS_fPCard,UCSAPI_UINT8 UCS_password,UCSAPI_UINT8 UCS_card,UCSAPI_UINT8 UCS_cardID,UCSAPI_UINT8 UCS_operation ,UCSAPI_UINT8 UCS_identify,UCSAPI_UINT8 UCS_admin)
{
    //UCS_UserProperty
    UCS_UserProperty.Card = UCS_card;
    UCS_UserProperty.Admin = UCS_admin;
    UCS_UserProperty.CardID = UCS_cardID;
    UCS_UserProperty.FPCard = UCS_fPCard;
    UCS_UserProperty.Finger = UCS_finger;
    UCS_UserProperty.Identify = UCS_identify;
    UCS_UserProperty.Password = UCS_password;
    UCS_UserProperty.Operation = UCS_operation;
}

//UCS_UniqueID
void MainWidget::UCS_CreateUniqueID(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data)
{
    //UCS_UniqueID
    UCS_UniqueID.Length = UCS_length;
    UCS_UniqueID.Data = UCS_data;
}

//UCS_UniqueID
void MainWidget::UCS_CreateUserName(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data)
{
    //UCS_UniqueID
    UCS_UserName.Length = UCS_length;
    UCS_UserName.Data = UCS_data;
}

//UCS_AccessAuthority;
void MainWidget::UCS_CreateAccessAuth(UCSAPI_ACCESS_DATE_TYPE UCS_accessDateType,UCSAPI_ACCESS_DATE_PTR UCS_p_accessDate,UCSAPI_DATA_PTR UCS_p_accessGroup)
{
    //UCS_AccessAuthority
    UCS_AccessAuthority.AccessDateType = 0;
    UCS_AccessAuthority.AccessDateType = UCS_accessDateType;
    /*typedef UCSAPI_UINT32	UCSAPI_ACCESS_DATE_TYPE;
    UCSAPI_DATE_TYPE_NOT_USE						0
    UCSAPI_DATE_TYPE_ALLOWED						1
    UCSAPI_DATE_TYPE_RESTRICTION					2
    */

    //UCS_AccessAuthority.AccessDate
    UCS_AccessAuthority.AccessDate = UCS_p_accessDate;

    //UCS_AccessAuthority.AccessGroup
    UCS_AccessAuthority.AccessGroup = UCS_p_accessGroup;
}

//BSP_ExportedData
bool MainWidget::UCS_CreateExportData(QString sTextFIR)
{
    arTextFIRData.clear();
    arTextFIRData = sTextFIR.toLocal8Bit();
    BSP_TextFir.TextFIR = arTextFIRData.data();
    BSP_TextFir.IsWideChar = UCBioAPI_FALSE;

    BSP_InputFIR.Form = UCBioAPI_FIR_FORM_TEXTENCODE;
    BSP_InputFIR.InputFIR.TextFIR = &BSP_TextFir;

    UCBioAPI_RETURN ret = UCBioAPI_FIRToTemplate(BSP_Handle,&BSP_InputFIR,&BSP_ExportedData,UCBioAPI_TEMPLATE_TYPE_SIZE400);

    if(ret == UCBioAPIERROR_NONE){
        qDebug() << "MAIN-->:Can Create Exported Data: UCBioAPIERROR_NONE";
        qDebug() << "MAIN-->:BSP_ExportedData.TemplateType = " << BSP_ExportedData.TemplateType;
        qDebug() << "MAIN-->:BSP_ExportedData.FingerNum= " << BSP_ExportedData.FingerNum;
        for(int i=0; i<BSP_ExportedData.FingerNum; i++)
            qDebug() << "MAIN-->:BSP_ExportedData.FingerInfo[" << i << "].FingerID= " << BSP_ExportedData.FingerInfo[i].FingerID;
        return true;
    }
    else if(ret == UCBioAPIERROR_INVALID_HANDLE){
        qDebug() << "MAIN-->:Can Not Create Exported Data: UCBioAPIERROR_INVALID_HANDLE";
        return true;
    }
    else if(ret == UCBioAPIERROR_INVALID_POINTER){
        qDebug() << "MAIN-->:Can Not Create Exported Data: UCBioAPIERROR_INVALID_POINTER";
        return false;
    }
    else if(ret == UCBioAPIERROR_MUST_BE_PROCESSED_DATA){
        qDebug() << "MAIN-->:Can Not Create Exported Data: UCBioAPIERROR_MUST_BE_PROCESSED_DATA";
        return false;
    }
    else if(ret == UCBioAPIERROR_FUNCTION_FAIL){
        qDebug() << "MAIN-->:Can Not Create Exported Data: UCBioAPIERROR_FUNCTION_FAIL";
        return false;
    }
    else{
        qDebug() << "Can Not Create Exported Data: UCBioAPIERROR_UNKNOWN";
        return false;
    }
}

//UCS_AccessDate
void MainWidget::CreateAccessDate(UCSAPI_UINT16 UCS_startYear,UCSAPI_UINT8 UCS_startMonth,UCSAPI_UINT8 UCS_startDay,UCSAPI_UINT16 UCS_stopYear,UCSAPI_UINT8 UCS_stopMonth,UCSAPI_UINT8 UCS_stopDay)
{
    UCS_AccessDate.StartDate.Year = 0;
    UCS_AccessDate.StartDate.Month = 0;
    UCS_AccessDate.StartDate.Day = 0;
    UCS_AccessDate.EndDate.Year = 0;
    UCS_AccessDate.EndDate.Month = 0;
    UCS_AccessDate.EndDate.Day = 0;

    if(UCS_startYear !=0 && UCS_startMonth != 0  && UCS_startDay != 0  && UCS_stopYear != 0  && UCS_stopMonth != 0  && UCS_stopDay != 0){
        UCS_AccessDate.StartDate.Year = UCS_startYear;
        UCS_AccessDate.StartDate.Month = UCS_startMonth;
        UCS_AccessDate.StartDate.Day = UCS_startDay;
        UCS_AccessDate.EndDate.Year = UCS_stopYear;
        UCS_AccessDate.EndDate.Month = UCS_stopMonth;
        UCS_AccessDate.EndDate.Day = UCS_stopDay;
    }
    return;
}
//Add User
//Add User

//Delete User
//Delete User

void MainWidget::slot_fromuser_cmd_del(quint32 TerminalId, quint32 UserID)
{
//    if(!bstart){
//        emit this->sig_main_resp_delete(false,-11,TerminalId);
//        return;
//    }
    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    int functionsRes = static_cast<int>(DeleteUserFromTerminals(UCS_ClientId,TerminalId,UserID));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_delete(UserID,false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back del user";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_delete(UserID,false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;
}

int MainWidget::DeleteUserFromTerminals(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId, UCSAPI_UINT32 UCS_userId)
{
    UCSAPI_RETURN ret = UCSAPI_DeleteUserFromTerminal(quint16(UCS_clientId),UCS_terminalId,UCS_userId);

    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can Delete user from terminal id " << UCS_terminalId << " :UCSAPIERR_NONE";
        return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not Delet user from terminal id " << UCS_terminalId << " :UCSAPIERR_NOT_SERVER_ACTIVE";
        return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else  if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not Delete user from terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_TERMINAL";
        return UCSAPIERR_INVALID_TERMINAL;
    }
    else{
        qDebug() << "MAIN-->:Can Not Delete user from terminal id " << UCS_terminalId << " :SERVER_UNKNOWN";
        return SERVER_UNKNOWN;
    }
}

void MainWidget::slot_frommain_DelUserCallBackRes(quint32 UserId,quint32 UCS_p_callback0,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:delete user callback";
    UCS_p_DeleteUserCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_DeleteUserCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(UCS_p_callback0);

    int errorCode = static_cast<int>(UCS_p_DeleteUserCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;

    tCMD.stop();
    bInProc =false;
    emit this->sig_main_resp_delete(UserId,success,errorCode,UCS_terminalID);
    delete UCS_p_DeleteUserCallback0;
    delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(UCS_p_callback0);
    //return;
}


//Delete User
//Delete User


//Delete AllUser
//Delete AllUser
void MainWidget::slot_fromuser_cmd_delall(quint32 TerminalId)
{
//    if(!bstart){
//        emit this->sig_main_resp_deleteall(false,-11,TerminalId);
//        return;
//    }
    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    int functionsRes = static_cast<int>(DeleteAllUserFromTerminals(UCS_ClientId,TerminalId));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_deleteall(false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back del user";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_deleteall(false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;
}

int MainWidget::DeleteAllUserFromTerminals(UCSAPI_UINT32 UCS_clientId,UCSAPI_UINT32 UCS_terminalId)
{
     UCSAPI_RETURN ret = UCSAPI_DeleteAllUserFromTerminal(quint16(UCS_clientId),UCS_terminalId);
     if(ret == UCSAPIERR_NONE){
         qDebug() << "MAIN-->:Can Delete All users from terminal id " << UCS_terminalId << " :UCSAPIERR_NONE";
         return UCSAPIERR_NONE;
     }
     else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
         qDebug() << "MAIN-->:Can Not Delete users from terminal id " << UCS_terminalId << " :UCSAPIERR_NOT_SERVER_ACTIVE";
         return UCSAPIERR_NOT_SERVER_ACTIVE;
     }
     else if(ret == UCSAPIERR_INVALID_TERMINAL){
         qDebug() << "MAIN-->:Can Not Delete All users from terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_TERMINAL";
         return UCSAPIERR_INVALID_TERMINAL;
     }
     else{
         qDebug() << "MAIN-->:Can Not Delete All users from terminal id " << UCS_terminalId << " :SERVER_UNKNOWN";
         return SERVER_UNKNOWN;
     }
}

void MainWidget::slot_frommain_DelAllUsersCallBackRes(quint32 UCS_p_callback0,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:delete all user calback";
    UCS_p_DeleteAllUserCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_DeleteAllUserCallback0 = UCSAPI_CALLBACK_PARAM_0_PTR(UCS_p_callback0);

    int errorCode = static_cast<int>(UCS_p_DeleteAllUserCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;

    tCMD.stop();
    bInProc =false;
    emit this->sig_main_resp_deleteall(success,errorCode,UCS_terminalID);
    delete UCS_p_DeleteAllUserCallback0;
    delete UCSAPI_CALLBACK_PARAM_0_PTR(UCS_p_callback0);

    return;
}
//Delete AllUser
//Delete AllUser



void MainWidget::slot_frommain_firstconnections(quint32 quiterminalId, quint32 quiClientId)
{
    qDebug() << "MAIN-->:terminal id: " << quiterminalId << " first connection with client id: " << quiClientId;
}

void MainWidget::setTime()
{
    //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss");
    lblTime->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    QDateConvertor mdate;
    QStringList today = mdate.Today();
    QString month = today[1];
    QString day = today[2];
    QString year = today[0];
    QString date = day + " / " + month + " / " + year;

    lblDate->setText(today[4] + " " + date);
    QCoreApplication::processEvents(QEventLoop::AllEvents);
}

void MainWidget::slot_main_userLog(int foodStatus , bool user, quint32 PersonnelId, int FoodNumber, QString FoodName,QString Name,QString PersonnelCode)
{
    bool uuser = user;
    uuser = user;
    PersonnelId = 0;
    //-1 not user
    // 0 food nk
    //1 food ok log ok
    //2 food ok log nk

    timerChangeUiForLog.start(3000);
//    if(foodStatus == -3){
//        lblshowRes->setHidden(false);
//        lblshowRes->setStyleSheet("QLabel { background-color : white; color : red; border: 15px solid black;}");
//        lblshowRes->setAlignment(Qt::AlignCenter);
//        lblshowRes->setText("شما غذای حذف کرده‌اید");
//    }
    if(foodStatus == -1 || foodStatus == -2){
        lblshowRes->setHidden(false);
        lblshowRes->setStyleSheet("QLabel { background-color : white; color : red; border: 15px solid black;}");
        lblshowRes->setAlignment(Qt::AlignCenter);
        lblshowRes->setText("شما کاربر این رستوران نمی باشید");
    }
    else if(foodStatus == 0){
        lblshowRes->setHidden(false);
        lblshowRes->setAlignment(Qt::AlignCenter);
        lblshowRes->setStyleSheet("QLabel { background-color : white; color : red; border: 15px solid black;}");
        lblshowRes->setText("شما غذا رزرو نکرده اید");
    }
    else if(foodStatus == 1){
        lblshowRes->setHidden(false);
        lblshowRes->setAlignment(Qt::AlignCenter);
        lblshowRes->setStyleSheet("QLabel { background-color : white; color : green; border: 15px solid black;}");
        lblshowRes->setText(QString("لطفا رسید غذای خود را بردارید") + "\n" + Name  + " - " + PersonnelCode + + "\n" + (" غذای نوع " + QString("%1").arg(QString::number(FoodNumber))) + " - " + QString("%1").arg(FoodName));
    }
    else if(foodStatus == 2){
        lblshowRes->setHidden(false);
        lblshowRes->setAlignment(Qt::AlignCenter);
        lblshowRes->setStyleSheet("QLabel { background-color : white; color : red; border: 15px solid black;}");
        lblshowRes->setText("شما غذای خود را قبلا تحویل گرفته اید");
    }
    else if(foodStatus == 3){
        lblshowRes->setHidden(false);
        lblshowRes->setAlignment(Qt::AlignCenter);
        lblshowRes->setStyleSheet("QLabel { background-color : white; color : red; border: 15px solid black;}");
        lblshowRes->setText("شما مجاز به دریافت غذای خود نمی‌باشید");
    }
    else if(foodStatus == 4){
        lblshowRes->setHidden(false);
        lblshowRes->setAlignment(Qt::AlignCenter);
        lblshowRes->setStyleSheet("QLabel { background-color : white; color : red; border: 15px solid black;}");
        lblshowRes->setText("اپراتور گرامی امروز غذا حاضر نیست");
    }


    //check ui
}

void MainWidget::slot_main_TerminalStaus(bool status)
{
    QDir dir;
    qDebug() << "MAIN-->status virdi = " << status;
    if(tcpConnectionVirdi && status){
        virdi = true;
        QPixmap virdiOk;
        virdiOk.load(dir.currentPath() + "/pics/virdiOk.png","PNG");
        lblVirdi->setPixmap(virdiOk);
    }
    else{
        virdi = false;
        QPixmap virdiNk;
        virdiNk.load(dir.currentPath() + "/pics/virdiNk.png","PNG");
        lblVirdi->setPixmap(virdiNk);
    }
    emit this->sig_main_virdiStatus(virdi);
    return;
}

void MainWidget::slot_check_dbConnection(bool status)
{
    //net = status;
    QDir dir;
    //qDebug() << "MAIN-->status db = " << status;
    if(tcpConnectionServer && status){
        qDebug() << "MAIN-->:net ok";
        net = true;
        QPixmap netOk;
        netOk.load(dir.currentPath() + "/pics/netOk.png","PNG");
        lblNet->setPixmap(netOk);
    }
    else{
        qDebug() << "MAIN-->:net nk";
        net = false;
        QPixmap netNk;
        netNk.load(dir.currentPath() + "/pics/netNk.png","PNG");
        lblNet->setPixmap(netNk);
    }
    emit this->sig_main_netStatus(net);
}

QList<QString> MainWidget::getcurrenyIP()
{
    QList<QString> list;
    list.clear();
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol  && address != QHostAddress(QHostAddress::LocalHost))
            list.append(address.toString().replace(".","A"));
    }
    return list;
}

void MainWidget::slot_main_onNetCheck()
{
    tcpConnectionServer = false;
    tcpConnectionVirdi = false;
    lbladdIp1->setText("");
    lbladdIp2->setText("");
    lbladdIp1->setText(QString("deviceidA%1").arg(QString::number(DeviceId)));
    QList<QString> ip = getcurrenyIP();
    if(ip.count() == 0){
        qDebug() << "MAIN-->:0 IPs";
    }
    else if(ip.count() == 1){
        qDebug() << "MAIN-->:1 IPs";
        if(ip.at(0) == VirdiIp){
            tcpConnectionVirdi = true;
        }
        else{
            tcpConnectionServer = true;
            lbladdIp2->setText(ip.at(0));
        }
    }
    else if(ip.count() == 2){
        qDebug() << "MAIN-->:2 IPs";
        if(ip.at(0) == VirdiIp){
            tcpConnectionServer = true;
            tcpConnectionVirdi = true;
            lbladdIp2->setText(ip.at(1));
        }
        else if(ip.at(1) == VirdiIp){
            tcpConnectionServer = true;
            tcpConnectionVirdi = true;
            lbladdIp2->setText(ip.at(0));
        }
    }

    emit this->sig_main_netCable(tcpConnectionServer);
    return;


}

void MainWidget::slot_checkLCD()
{
    lblFood1->setText("");
    lblFood2->setText("");
    lblFood3->setText("");
    lblFood4->setText("");

    QDir dirfood;
    QString squery = LoadQuery(dirfood.currentPath() + "/SqlQuery/main-getLCD.dll");
    squery = squery.arg(QString::number(RestaurantId));
    QSqlQuery query(*db_mysql);
    if(!query.exec(squery)){
        if(query.lastError().isValid()){
            qDebug() << "LG:My Sql query error get food : " << query.lastError().text();
            db_mysql->close();
            db_mysql->open();
        }
    }
    QList<QString> names;
    names.clear();
    QList<int> kinds;
    kinds.clear();
    int count = 0;
    while(query.next()){

        if(query.value("FoodType").toInt() == 1){
            kinds.append(1);
            names.append(query.value("FoodName").toString().toUtf8());
        }
        else if(query.value("FoodType").toInt() == 2){
            kinds.append(2);
            names.append(query.value("FoodName").toString().toUtf8());
        }
        else if(query.value("FoodType").toInt() == 3){
            kinds.append(3);
            names.append(query.value("FoodName").toString().toUtf8());
        }
        else if(query.value("FoodType").toInt() == 4){
            kinds.append(4);
            names.append(query.value("FoodName").toString());
        }
        count++;
        if(count >= 4)
            break;
    }
    for(int i=0; i<names.count(); i++){
        if(i+1 == 1){
            //qDebug() << "1 - " << kinds.at(i) << names.at(i);
            lblFood1->setText(" غذای نوع " + QString("%1").arg(kinds.at(i)) + " - " + QString("%1").arg(names.at(i)));
        }
        else if(i+1 == 2){
            //qDebug() << "2 - " << kinds.at(i) << names.at(i);
            lblFood2->setText(" غذای نوع " + QString("%1").arg(kinds.at(i)) + " - " + QString("%1").arg(names.at(i)));
        }
        else if(i+1 == 3){
            //qDebug() << "3 - " << kinds.at(i) << names.at(i);
            lblFood3->setText(" غذای نوع " + QString("%1").arg(kinds.at(i)) + " - " + QString("%1").arg(names.at(i)));
        }
        else if(i+1 == 4){
            //qDebug() << "4 - " << kinds.at(i) << names.at(i);
            lblFood4->setText(" غذای نوع " + QString("%1").arg(kinds.at(i)) + " - " + QString("%1").arg(names.at(i)));
        }
    }
    lblFoodCount1->setText(QString::number(iFoodCount1));
    lblFoodCount2->setText(QString::number(iFoodCount2));
    lblFoodCount3->setText(QString::number(iFoodCount3));
    lblFoodCount4->setText(QString::number(iFoodCount4));
    iFoodCount = iFoodCount1 + iFoodCount2 + iFoodCount3 + iFoodCount4;
    lblFoodCount->setText(QString::number(iFoodCount));
}

void MainWidget::prepareLCD()
{
    ui->label->setGeometry(this->geometry());
    QPixmap pm;
    QDir dir;
    pm.load(dir.currentPath() + "/pics/bk.png","PNG");
    ui->label->setPixmap(pm);

    lblshowRes = new QLabel();
    lbladdIp1 = new QLabel(this);
    lbladdIp2 = new QLabel(this);
    lbladdIp1->setGeometry(this->geometry().right()-100,
                           this->geometry().bottom()-40,
                           100,20);
    lbladdIp2->setGeometry(this->geometry().right()-100,
                           this->geometry().bottom()-40 + 20,
                           100,20);
    lbladdIp1->setHidden(false);
    lbladdIp2->setHidden(false);
    lbladdIp1->setAlignment(Qt::AlignLeft);
    lbladdIp2->setAlignment(Qt::AlignLeft);
    QFont f("B Yekan",40);
    lblshowRes->setWindowFlag(Qt::FramelessWindowHint);
    lblshowRes->setFont(f);
    lblshowRes->setGeometry(0,256,1024,256);
    lblshowRes->setHidden(true);


    QFont fTime(s_timeFontName,i_timeFontSize);
    lblTime = new QLabel(this);
    lblTime->setHidden(false);
    lblTime->setGeometry(200,42,150,40);
    lblTime->setFont(fTime);
    lblTime->setAlignment(Qt::AlignRight);
    lblTime->setStyleSheet("QLabel { color : white; }");


    QFont fDate(s_dateFontName,i_dateFontSize);
    lblDate = new QLabel(this);
    lblDate->setHidden(false);
    lblDate->setGeometry(350,42,350,40);
    lblDate->setFont(fDate);
    lblDate->setWordWrap(true);
    lblDate->setAlignment(Qt::AlignLeft);
    lblDate->setStyleSheet("QLabel { color : white; }");


    lblVirdi = new QLabel(this);
    lblVirdi->setHidden(false);
    lblVirdi->setGeometry(350,590,106,106);
    QPixmap virdiNk;
    virdiNk.load(dir.currentPath() + "/pics/virdiNk.png","PNG");
    lblVirdi->setPixmap(virdiNk);


    lblNet = new QLabel(this);
    lblNet->setHidden(false);
    lblNet->setGeometry(556,590,106,106);
    QPixmap netNk;
    netNk.load(dir.currentPath() + "/pics/netNk.png","PNG");
    lblNet->setPixmap(netNk);


    lblFood1 = new QLabel(this);
    lblFood2 = new QLabel(this);
    lblFood3 = new QLabel(this);
    lblFood4 = new QLabel(this);

    lblFoodCount1 = new QLabel(this);
    lblFoodCount2 = new QLabel(this);
    lblFoodCount3 = new QLabel(this);
    lblFoodCount4 = new QLabel(this);
    lblFoodCount = new QLabel(this);

    lblFood1->setHidden(false);
    lblFood2->setHidden(false);
    lblFood3->setHidden(false);
    lblFood4->setHidden(false);

    lblFoodCount1->setHidden(false);
    lblFoodCount2->setHidden(false);
    lblFoodCount3->setHidden(false);
    lblFoodCount4->setHidden(false);
    lblFoodCount->setHidden(false);

    lblFood1->setGeometry(257,170,507,78);
    lblFood2->setGeometry(257,170 + 78 + 25,507,78);
    lblFood3->setGeometry(257,170 + 78 + 78 + 25 + 25,507,78);
    lblFood4->setGeometry(257,170 + 78 + 78 + 78 + 25 + 25 + 25,507,78);

    lblFoodCount1->setGeometry(149,170,98,78);
    lblFoodCount2->setGeometry(149,170 + 78 + 25,98,78);
    lblFoodCount3->setGeometry(149,170 + 78 + 78 + 25 + 25,98,78);
    lblFoodCount4->setGeometry(149,170 + 78 + 78 + 78 + 25 + 25 + 25,98,78);
    lblFoodCount->setGeometry(149,170 + 78 + 78 + 78 + 78 + 25 + 25 + 25 + 25,98,78);

    lblFood1->setStyleSheet("QLabel { color : black; }");
    lblFood2->setStyleSheet("QLabel { color : black; }");
    lblFood3->setStyleSheet("QLabel { color : black; }");
    lblFood4->setStyleSheet("QLabel { color : black; }");

    lblFoodCount1->setStyleSheet("QLabel { color : black; }");
    lblFoodCount2->setStyleSheet("QLabel { color : black; }");
    lblFoodCount3->setStyleSheet("QLabel { color : black; }");
    lblFoodCount4->setStyleSheet("QLabel { color : black; }");
    lblFoodCount->setStyleSheet("QLabel { color : black; }");

    QFont fFood(s_foodFontName,i_foodFontSize);
    lblFood1->setFont(fFood);
    lblFood2->setFont(fFood);
    lblFood3->setFont(fFood);
    lblFood4->setFont(fFood);

    lblFoodCount1->setFont(fFood);
    lblFoodCount2->setFont(fFood);
    lblFoodCount3->setFont(fFood);
    lblFoodCount4->setFont(fFood);
    lblFoodCount->setFont(fFood);

    lblFood1->setAlignment(Qt::AlignLeft);
    lblFood2->setAlignment(Qt::AlignLeft);
    lblFood3->setAlignment(Qt::AlignLeft);
    lblFood4->setAlignment(Qt::AlignLeft);

    lblFoodCount1->setAlignment(Qt::AlignCenter);
    lblFoodCount2->setAlignment(Qt::AlignCenter);
    lblFoodCount3->setAlignment(Qt::AlignCenter);
    lblFoodCount4->setAlignment(Qt::AlignCenter);
    lblFoodCount->setAlignment(Qt::AlignCenter);
}

void MainWidget::reset_LCD_user()
{
    lblshowRes->setHidden(true);
}

QString MainWidget::LoadQuery(QString sFilename)
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

void MainWidget::slot_main_GetFoodCount(int foodType)
{
    QSettings setting("config.dll",QSettings::IniFormat);


    sIniDate = setting.value("Counter/date","").toString();
    if(!(countDate.currentDate().toString() == sIniDate)){
        iFoodCount1 = 0;
        iFoodCount2 = 0;
        iFoodCount3 = 0;
        iFoodCount4 = 0;
        iFoodCount = 0;
        setting.setValue("Counter/count1",0);
        setting.setValue("Counter/count2",0);
        setting.setValue("Counter/count3",0);
        setting.setValue("Counter/count4",0);
        setting.setValue("Counter/date",countDate.currentDate().toString());
    }

    if(foodType == 1){
        iFoodCount1++;
        lblFoodCount1->setText(QString::number(iFoodCount1));
    }
    else if(foodType == 2){
        iFoodCount2++;
        lblFoodCount2->setText(QString::number(iFoodCount2));
    }
    else if(foodType == 3){
        iFoodCount3++;
        lblFoodCount3->setText(QString::number(iFoodCount3));
    }
    else if(foodType == 4){
        iFoodCount4++;
        lblFoodCount4->setText(QString::number(iFoodCount4));
    }

    iFoodCount = iFoodCount1 + iFoodCount2 + iFoodCount3 + iFoodCount4;
    lblFoodCount->setText(QString::number(iFoodCount));

    setting.setValue("Counter/count1",iFoodCount1);
    setting.setValue("Counter/count2",iFoodCount2);
    setting.setValue("Counter/count3",iFoodCount3);
    setting.setValue("Counter/count4",iFoodCount4);
}
