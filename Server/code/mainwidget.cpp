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
//        qDebug() << "clientId = " << UCS_ClientId;
        emit this->sig_main_firstConnect(TerminalID,UCS_ClientId);
        delete pCallBack0;
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_DISCONNECTED){
        //UCSAPI_CALLBACK_PARAM_0_PTR pCallBack0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam);
        //UCSAPI_CALLBACK_PARAM_1_PTR pCallBack1 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_1_PTR>(wParam);
        emit this->sig_main_disConnect(TerminalID);
        //delete pCallBack0;
        //delete pCallBack1;
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_TERMINAL_STATUS){
        UCSAPI_TERMINAL_STATUS_PTR pStatus = reinterpret_cast<UCSAPI_TERMINAL_STATUS_PTR>(lParam);
        qDebug() << "MAIN-->:received status from terminal: " << TerminalID;
        qui_TerminaId_Status = TerminalID;
        qui_Door_Status = pStatus->Door;
        qui_Lock_Status = pStatus->Lock;
        qui_Open_Status = pStatus->Open;
        qui_Cover_Status = pStatus->Cover;
        qui_Terminal_Status = pStatus->Terminal;


        emit this->sig_main_getTerminalStatus(qui_TerminaId_Status,qui_Door_Status,qui_Lock_Status,qui_Open_Status,qui_Cover_Status,qui_Terminal_Status);
        emit this->sig_main_GetLog(TerminalID);
        delete pStatus;
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_REALTIME_ACCESS_LOG){
        UCSAPI_CALLBACK_PARAM_1_PTR  pCallback1 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_1_PTR>(lParam);
        UCSAPI_CALLBACK_PARAM_0_PTR  pCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam);
        if(pCallback1 && pCallback0){
            if(pCallback1->DataType == UCSAPI_CALLBACK_DATA_TYPE_ACCESS_LOG){

            qui_TerminalId_auto = TerminalID;
            qui_RFID_length_auto = pCallback1->Data.AccessLog->RFID->Length;
            memcpy(RFID_data_auto,pCallback1->Data.AccessLog->RFID->Data,qui_RFID_length_auto);
            //qDebug() << "qui_RFID_length_auto = " << qui_RFID_length_auto;
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
        }
        return;
    }
    else if(EventType == UCSAPI_CALLBACK_EVENT_GET_ACCESS_LOG){
        UCSAPI_CALLBACK_PARAM_1_PTR  pCallback1 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_1_PTR>(lParam);
        UCSAPI_CALLBACK_PARAM_0_PTR  pCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(wParam);
        if(pCallback1 && pCallback0){
            //qDebug() << pCallback1->DataType;
            if(pCallback1->DataType == UCSAPI_CALLBACK_DATA_TYPE_ACCESS_LOG){
                qui_TerminalId = TerminalID;
                qui_RFID_length = pCallback1->Data.AccessLog->RFID->Length;
                //qDebug() << "qui_RFID_length = " << qui_RFID_length;
                memcpy(RFID_data,pCallback1->Data.AccessLog->RFID->Data,qui_RFID_length);
                qui_UserID = pCallback1->Data.AccessLog->UserID;
                qui_AuthMode = pCallback1->Data.AccessLog->AuthMode;
                qui_AuthType = pCallback1->Data.AccessLog->AuthType;
                qui_Year = pCallback1->Data.AccessLog->DateTime.Year;
                qui_Month = pCallback1->Data.AccessLog->DateTime.Month;
                qui_Day = pCallback1->Data.AccessLog->DateTime.Day;
                qui_Hour = pCallback1->Data.AccessLog->DateTime.Hour;
                qui_Min = pCallback1->Data.AccessLog->DateTime.Min;
                qui_Sec = pCallback1->Data.AccessLog->DateTime.Sec;
                qui_AuthRes = pCallback1->Data.AccessLog->AuthResult;
                //qDebug() << "qui_AuthRes = " << qui_AuthRes;
                bRes = pCallback1->Data.AccessLog->IsAuthorized;

                //qDebug() << "auth res in callback : " << bRes;
                emit this->sig_main_getAccessLog(qui_TerminalId,qui_RFID_length,RFID_data,qui_UserID,qui_AuthMode,qui_AuthType,
                                                 qui_Year,qui_Month,qui_Day,qui_Hour,qui_Min,qui_Sec,qui_AuthRes,bRes);
            }
        }
        delete pCallback1;
        delete pCallback0;
        //((UCSAPI_CALLBACK_PARAM_1_PTR)lParam)->DataType = UCSAPI_CALLBACK_DATA_TYPE_ACCESS_LOG;
        //qDebug() << "TotalNumber : " <<((UCSAPI_CALLBACK_PARAM_0*)wParam)->Progress.TotalNumber;
        //qDebug() << "CurrentIndex : " <<((UCSAPI_CALLBACK_PARAM_0*)wParam)->Progress.CurrentIndex;

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
    else if(EventType == UCSAPI_CALLBACK_EVENT_SET_ACCESS_CONTROL_DATA){
        if(bTimeout)
            return;
        if(callbackFlag == 1)
            emit this->sig_main_TimeZoneCallBackResp(wParam,TerminalID);
        else if(callbackFlag == 2)
            emit this->sig_main_HolidayCallBackResp(wParam,TerminalID);
        else if(callbackFlag == 3)
            emit this->sig_main_AccessCallBackResp(wParam,TerminalID);
        else if(callbackFlag == 4)
            emit this->sig_main_GroupCallBackResp(wParam,TerminalID);
        return;
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

//    icon.addFile("app.ico");
//    SysTray.setIcon(icon);
//    SysTray.setVisible(true);
//    SysTray.setToolTip("Virdi ServerV1.3 - Active");
//    SysTray.show();
//    qDebug() << "MAIN-->:run";

    qDebug() << "MAIN-->:Start";

    connect(this,SIGNAL(sig_main_start()),this,SLOT(slot_Main_start()),Qt::QueuedConnection);
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
    StartWebsocketThread();
    StartUserThread();
    StartTerminalThread();
    StartLogThread();
    ManageConnection();

    StartMainThread();
}

void MainWidget::ConfigMain()
{
    qDebug() << "MAIN-->:Config Class";

    bInProc = false;
    UCS_bStarted = false;
    BSP_bStarted = false;
    iCMDTimeout = 0;
    bTimeout = false;

    UCS_ClientId = 0;
    UCS_MaxTerminal = 0;
    UCS_PortNumber = 0;
    start = false;

    FirstTerminalList.clear();

    QSettings setting("config.dll",QSettings::IniFormat);
    UCS_MaxTerminal = static_cast<UCSAPI_UINT32>(setting.value("UCS/max_reader",1).toInt());
    UCS_PortNumber = static_cast<UCSAPI_UINT32>(setting.value("UCS/ucs_port",9870).toInt());
    iCMDTimeout = setting.value("Main/cmd_timeout",500).toInt();

    minimum_Terminals = static_cast<quint32>(setting.value("Main/minimum_terminals",1).toInt());
    bstart = false;

    tCMD.setSingleShot(true);
    connect(&tCMD,SIGNAL(timeout()),this,SLOT(slot_cmd_timeout()),Qt::QueuedConnection);


    connect(this,SIGNAL(CallBackSignal(UCSAPI_UINT32 ,
                                       UCSAPI_UINT32 ,
                                       UCSAPI_UINT32 ,
                                       UCSAPI_UINT32)),this,SLOT(CallBackSlot(UCSAPI_UINT32 ,
                                                                 UCSAPI_UINT32 ,
                                                                 UCSAPI_UINT32 ,
                                                                 UCSAPI_UINT32 )),Qt::DirectConnection);

    StartTimer.setSingleShot(false);
    StartTimer.stop();
    connect(&StartTimer,SIGNAL(timeout()),this,SLOT(slot_start()),Qt::DirectConnection);



    return;
}

void MainWidget::slot_cmd_timeout()
{
    qDebug() << "MAIN-->:cmd timeout";
    tCMD.stop();
    bTimeout = true;
    bInProc = false;
    callbackFlag = 0;
    return;
}

void MainWidget::StartMainThread()
{
    if(!start){
        start = true;
        StartTimer.start(5000);
    }
    if(wop_Websocket->bDbopened && wop_User->bDbopened && wop_Terminal->bDbopened && wop_Log->bDbopened){
        StartTimer.stop();
        UCS_bStarted = UCS_Start(UCS_MaxTerminal,UCS_PortNumber);
        if(!UCS_bStarted){
            QApplication::quit();
        }
        BSP_bStarted = BSP_Start(&BSP_Handle);
    }
    return;
}

void MainWidget::slot_start()
{
    StartMainThread();
}

void MainWidget::StartWebsocketThread()
{
    thp_WebSocket = new QThread;
    wop_Websocket = new WebSocket;
    connect(wop_Websocket,SIGNAL(sig_Start_Thread()),wop_Websocket,SLOT(slot_Start_WS_Thread()),Qt::QueuedConnection);
    connect(wop_Websocket,SIGNAL(sig_Stop_Thread()),wop_Websocket,SLOT(slot_Stop_WS_Thread()),Qt::QueuedConnection);
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

void MainWidget::StartTerminalThread()
{
    thp_Terminal = new QThread;
    wop_Terminal = new TerminalManagement;
    connect(wop_Terminal,SIGNAL(sig_Start_Thread()),wop_Terminal,SLOT(slot_Start_Terminal_Thread()),Qt::QueuedConnection);
    connect(wop_Terminal,SIGNAL(sig_Stop_Thread()),wop_Terminal,SLOT(slot_Stop_Terminal_Thread()),Qt::QueuedConnection);
    wop_Terminal->moveToThread(thp_User);
    thp_Terminal->start();
    emit wop_Terminal->sig_Start_Thread();
}

void MainWidget::StartLogThread()
{
    thp_Log = new QThread;
    wop_Log = new LogManagement;
    connect(wop_Log,SIGNAL(sig_Start_Thread()),wop_Log,SLOT(slot_Start_Log_Thread()),Qt::QueuedConnection);
    connect(wop_Log,SIGNAL(sig_Stop_Thread()),wop_Log,SLOT(slot_Stop_Log_Thread()),Qt::QueuedConnection);
    wop_Log->moveToThread(thp_Log);
    thp_Log->start();
    emit wop_Log->sig_Start_Thread();
}

void MainWidget::ManageConnection()
{


    //connect(this,SIGNAL(sig_main_inproc(bool)),wop_Websocket,SLOT(slot_frommain_proc(bool)),Qt::QueuedConnection);
    connect(this,SIGNAL(sig_main_firstConnect(quint32,quint32)),
            this,SLOT(slot_frommain_firstconnections(quint32,quint32)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_main_realTimeAccessLog(quint32,quint32,BYTE*,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            wop_Log,SLOT(slot_frommain_RealTimeLog(quint32,quint32,BYTE*,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_main_getAccessLog(quint32,quint32,BYTE*,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),
            wop_Log,SLOT(slot_frommain_GetLog(quint32,quint32,BYTE*,quint32,quint8,quint8,quint16,quint8,quint8,quint8,quint8,quint8,quint32,bool)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_main_getTerminalStatus(quint32,quint32,quint32,quint32,quint32,quint32)),
            wop_Log,SLOT(slot_frommain_TerminalStatus(quint32,quint32,quint32,quint32,quint32,quint32)),Qt::QueuedConnection);

    connect(this,SIGNAL(sig_main_GetLog(quint32)),
            this,SLOT(slot_frommain_getStatus(quint32)),Qt::QueuedConnection);




    //user
    connect(wop_User,SIGNAL(invaid_cmd()),wop_Websocket,SLOT(slot_fromuser_invalid()),Qt::QueuedConnection);
        //from socket to user (cmd)
        connect(wop_Websocket,SIGNAL(sig_touser_cmd_add(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_add(QString)),Qt::QueuedConnection);
        connect(wop_Websocket,SIGNAL(sig_touser_cmd_del(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_del(QString)),Qt::QueuedConnection);
        connect(wop_Websocket,SIGNAL(sig_touser_cmd_delall(QString)),
                wop_User,SLOT(slot_fromsocket_cmd_delall(QString)),Qt::QueuedConnection);

        //from user to main (functions)

        connect(wop_User,SIGNAL(sig_tomain_cmd_add(quint32,quint32,QString,QString,QString,int,int,int,int,int,int,QString,bool,int)),
                this,SLOT(slot_fromuser_cmd_add(quint32,quint32,QString,QString,QString,int,int,int,int,int,int,QString,bool,int)),Qt::QueuedConnection);

        connect(wop_User,SIGNAL(sig_tomain_cmd_del(quint32,quint32)),
                this,SLOT(slot_fromuser_cmd_del(quint32,quint32)),Qt::QueuedConnection);
        connect(wop_User,SIGNAL(sig_tomain_cmd_delall(quint32)),
                this,SLOT(slot_fromuser_cmd_delall(quint32)),Qt::QueuedConnection);

        //from main to main (callback)
        connect(this,SIGNAL(sig_main_addUser(quint32,quint32, quint32)),
                this,SLOT(slot_frommain_AddUserCallBackRes(quint32,quint32,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_deleteUser(quint32,quint32,quint32)),
                this,SLOT(slot_frommain_DelUserCallBackRes(quint32,quint32,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_deleteAllUser(quint32, quint32)),
                this,SLOT(slot_frommain_DelAllUsersCallBackRes(quint32,quint32)),Qt::QueuedConnection);

        //from main to user (resp)
        connect(this,SIGNAL(sig_main_resp_deleteall(bool,int,quint32)),
                wop_User,SLOT(slot_frommain_resp_deleteall(bool,int,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_resp_delete(quint32,bool,int,quint32)),
                wop_User,SLOT(slot_frommain_resp_delete(quint32,bool,int,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_resp_add(quint32,bool,int,quint32,int)),
                wop_User,SLOT(slot_frommain_resp_add(quint32,bool,int,quint32,int)),Qt::QueuedConnection);

        //from user to socket
        connect(wop_User,SIGNAL(sig_user_finishedCMD()),
                wop_Websocket,SLOT(sig_user_finishedCMD()),Qt::QueuedConnection);
    //user



    //terminal
    connect(wop_Terminal,SIGNAL(invaid_cmd()),
            wop_Websocket,SLOT(slot_fromuser_invalid()),Qt::QueuedConnection);
        //from socket to terminal
        connect(wop_Websocket,SIGNAL(sig_toterminal_timezone(QString)),
                wop_Terminal,SLOT(slot_fromsocket_timezone(QString)),Qt::QueuedConnection);
        connect(wop_Websocket,SIGNAL(sig_toterminal_holiday(QString)),
                wop_Terminal,SLOT(slot_fromsocket_holiday(QString)),Qt::QueuedConnection);
        connect(wop_Websocket,SIGNAL(sig_toterminal_accesstime(QString)),
                wop_Terminal,SLOT(slot_fromsocket_accesstime(QString)),Qt::QueuedConnection);
        connect(wop_Websocket,SIGNAL(sig_toterminal_accessgroup(QString)),
                wop_Terminal,SLOT(slot_fromsocket_accessgroup(QString)),Qt::QueuedConnection);

        //from terminal to main
        connect(wop_Terminal,SIGNAL(sig_tomain_timezone(quint32,int,QList<int>*,QList<int>*,QList<int>*,QList<int>*,QList<int>*)),
                this,SLOT(slot_fromterminal_timezone(quint32,int,QList<int>*,QList<int>*,QList<int>*,QList<int>*,QList<int>*)),Qt::QueuedConnection);
        connect(wop_Terminal,SIGNAL(sig_tomain_hol(quint32,int,QList<int>*,QList<int>*,QList<int>*)),
                this,SLOT(slot_fromterminal_hol(quint32,int,QList<int>*,QList<int>*,QList<int>*)),Qt::QueuedConnection);
        connect(wop_Terminal,SIGNAL(sig_tomain_access(quint32,int,QList<int>*,int*,QList<int>*,QList<int>*)),
                this,SLOT(slot_fromterminal_access(quint32,int,QList<int>*,int*,QList<int>*,QList<int>*)),Qt::QueuedConnection);
        connect(wop_Terminal,SIGNAL(sig_tomain_group(quint32,int,QList<int>*,QList<int>*)),
                this,SLOT(slot_fromterminal_group(quint32,int,QList<int>*,QList<int>*)),Qt::QueuedConnection);


        //from main to main
        connect(this,SIGNAL(sig_main_TimeZoneCallBackResp(quint32,quint32)),
                this,SLOT(slot_frommain_TimezoneCallbackResp(quint32,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_HolidayCallBackResp(quint32,quint32)),
                this,SLOT(slot_frommain_HolidayCallbackResp(quint32,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_AccessCallBackResp(quint32,quint32)),
                this,SLOT(slot_frommain_AccessCallbackResp(quint32,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_GroupCallBackResp(quint32,quint32)),
                this,SLOT(slot_frommain_GroupCallbackResp(quint32,quint32)),Qt::QueuedConnection);

        //from main to terminal
        connect(this,SIGNAL(sig_main_resp_timezoneResp(bool,int,quint32)),
                wop_Terminal,SLOT(slot_frommain_timezoneResp(bool,int,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_resp_holResp(bool,int,quint32)),
                wop_Terminal,SLOT(slot_frommain_holidayResp(bool,int,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_resp_accessResp(bool,int,quint32)),
                wop_Terminal,SLOT(slot_frommain_accesstimeResp(bool,int,quint32)),Qt::QueuedConnection);
        connect(this,SIGNAL(sig_main_resp_groupResp(bool,int,quint32)),
                wop_Terminal,SLOT(slot_frommain_accessgroupResp(bool,int,quint32)),Qt::QueuedConnection);

        //from terminal to socket
        connect(wop_Terminal,SIGNAL(sig_terminal_finishedCMD()),
                wop_Websocket,SLOT(sig_user_finishedCMD()),Qt::QueuedConnection);

    //terminal
}

void MainWidget::StopApp()
{
    UCS_Stop();
    BSP_Stop(BSP_Handle);

    emit wop_Websocket->sig_Stop_Thread();
    thp_WebSocket->deleteLater();

    emit wop_User->sig_Stop_Thread();
    thp_User->deleteLater();

    emit wop_Terminal->sig_Stop_Thread();
    thp_Terminal->deleteLater();

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
    for(int i=0; i<20;i++)
        CardData[i] = 0;

    for(int i=0; i<CardCSN.count(); i++)
        CardData[i] = CardCSN.at(i).toLatin1();

    UCS_ValidCard.Length = static_cast<UCSAPI_UINT32>(CardCSN.count());
    UCS_ValidCard.Data = CardData;
    return;
}

void MainWidget::CreateNullFormat()
{
    UCS_Format[0] = 0;
    UCS_Format[1] = 0;
    UCS_Format[2] = 0;
    UCS_Format[3] = 0;
}

void MainWidget::CreateAllAndSendUser(quint32 TerminalId,quint32 UserId, QString PersonnelCode,QString TextFir, QString CardCSN, int isYear, int isMonth, int isDay, int ieYear, int ieMonth, int ieDay,QString groupCode,bool isAdmin, int add_inactive)
{
//    qDebug() << "fir count= " << TextFir.count();
//    qDebug() << "csn count= " << CardCSN.count();
//    qDebug() << "date start = " << isYear << "/" << isMonth << "/" << isDay;
//    qDebug() << "date stop = " << ieYear << "/" << ieMonth << "/" << ieDay;
//    qDebug() << "group code: " << groupCode;
    //qDebug() << "group code count: " << groupCode.count();


    //user data --> user info --> access authority
    //UCS_AccessGroup.Length = 0;
    //UCS_AccessGroup.Data = nullptr;

    qDebug() << "MAIN-->:User Text Fir lenght = " << TextFir.count();
    qDebug() << "MAIN-->:User Card CSN = " << CardCSN;
    qDebug() << "MAIN-->:User start date: " << isYear << "/" <<isMonth << "/" << isDay << "/ , " << ieYear << "/" << ieMonth << "/" << ieDay;

    quint8 iisAdmin = 0;
    if(isAdmin == true)
        iisAdmin = 1;

    if(TextFir.count() != 0){
        if(!UCS_CreateExportData(TextFir)){
            tCMD.stop();
            emit this->sig_main_resp_add(UserId,false,SERVER_UNKNOWN,TerminalId,addinactive);
            return;
        }
        CreateFingerData(UCBioAPI_TEMPLATE_FORMAT_UNION400,UCBioAPI_FIR_SECURITY_LEVEL_NORMAL,UCSAPI_TRUE,&BSP_ExportedData);
    }
    else{
        UCBioAPI_FreeExportData(&BSP_ExportedData);

    }

    if(add_inactive == 1)
        CreateAccessDate(static_cast<UINT16>(isYear),static_cast<UINT8>(isMonth),static_cast<UINT8>(isDay),static_cast<UINT16>(ieYear),static_cast<UINT8>(ieMonth),static_cast<UINT8>(ieDay));
    if(add_inactive == 2){
        isYear = QDate::currentDate().year();
        isMonth = QDate::currentDate().month();
        isDay = QDate::currentDate().day();

        ieYear = QDate::currentDate().year() + 10;
        ieMonth = QDate::currentDate().month();
        ieDay = QDate::currentDate().day();

        CreateAccessDate(static_cast<UINT16>(isYear),static_cast<UINT8>(isMonth),static_cast<UINT8>(isDay),static_cast<UINT16>(ieYear),static_cast<UINT8>(ieMonth),static_cast<UINT8>(ieDay));

    }

    //accass group
    for(int i=0; i<4; i++)
        UserGroupCode[i] = 0;
    for(int i=0; i<groupCode.count(); i++)
        UserGroupCode[i] = groupCode.at(i).toLatin1();
    qDebug() << "MAIN-->:groupCode = " << groupCode;
    UCS_AccessGroup.Length = static_cast<UCSAPI_UINT32>(groupCode.count());
    UCS_AccessGroup.Data = UserGroupCode;

    //personnel code
    for(int i=0; i<20; i++)
        UserPersonellCode[i] = 0;
    for(int i=0 ; i < PersonnelCode.count(); i++)
        UserPersonellCode[i] = PersonnelCode.at(i).toLatin1();
    qDebug() << "MAIN-->:PersonnelCode = " << PersonnelCode;
    UCS_UniqueID.Length = static_cast<UCSAPI_UINT32>(PersonnelCode.count());
    UCS_UniqueID.Data = UserPersonellCode;



    char tmp[4];
    memcpy(tmp,UCS_AccessGroup.Data,4);
    //memcpy(UCS_AccessGroup.Data,groupCode.data(),size_t(groupCode.count()));
    qDebug() << "MAIN-->:User Group Code " << tmp[0] << tmp[1] << tmp[2] << tmp[3] ;


    if(add_inactive == 1){
        if(isYear != 0 && isMonth != 0 && isDay != 0 && ieYear != 0 && ieMonth != 0 && ieDay != 0)
                UCS_CreateAccessAuth(UCSAPI_DATE_TYPE_ALLOWED,&UCS_AccessDate,&UCS_AccessGroup);
        else
            UCS_CreateAccessAuth(UCSAPI_DATE_TYPE_NOT_USE,&UCS_AccessDate,&UCS_AccessGroup);
    }
    else if(add_inactive == 2){
        UCS_CreateAccessAuth(UCSAPI_DATE_TYPE_RESTRICTION,&UCS_AccessDate,&UCS_AccessGroup);
    }


//UCSAPI_DATE_TYPE_ALLOWED




    UCS_CreateUserName(0,nullptr);

    CreateNullCardInfo();
    CreateValidCard(CardCSN);


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
        emit this->sig_main_resp_add(UserId,false,functionsRes,TerminalId,addinactive);
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
        emit this->sig_main_resp_add(UserId,false,SERVER_TIMEOUT,TerminalId,addinactive);
        return;
    }
    return;
}

void MainWidget::slot_fromuser_cmd_add(quint32 TerminalId, quint32 UserID, QString PersonnelCode, QString TextFir, QString CardCSN, int isYear, int isMonth, int isDay, int ieYear, int ieMonth, int ieDay, QString groupCode,bool isAdmin, int add_inactive)
{
//    if(!bstart){
//        emit this->sig_main_resp_add(false,-11,TerminalId);
//        return;
//    }
    addinactive = add_inactive;
    CreateAllAndSendUser(TerminalId,UserID,PersonnelCode,TextFir,CardCSN,isYear,isMonth,isDay,ieYear,ieMonth,ieDay,groupCode,isAdmin,addinactive);
    return;
}

int MainWidget::UCS_SendUserToTerminal(UCSAPI_UINT32 UCS_clientId,UCSAPI_UINT32 UCS_terminalId,UCSAPI_BOOL UCS_isOverwrite,UCSAPI_USER_DATA_PTR UCS_p_userData)
{
    qDebug() << "MAIN-->:Add User id " << UCS_p_userData->UserInfo.UserID <<  " to Terminal " << UCS_terminalId;

    UCSAPI_RETURN ret =  UCSAPI_AddUserToTerminal(quint16(UCS_clientId),UCS_terminalId,UCS_isOverwrite,UCS_p_userData);

    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_NONE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_NOT_SERVER_ACTIVE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else if(ret == UCSAPIERR_INVALID_POINTER){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_POINTER";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_POINTER;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_TERMINAL";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_TERMINAL;
    }
    else if(ret == UCSAPIERR_USER_NAME_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_USER_NAME_SIZE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_USER_NAME_SIZE;
    }
    else if(ret == UCSAPIERR_UNIQUE_ID_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send Use to terminal id " << UCS_terminalId << " :UCSAPIERR_UNIQUE_ID_SIZE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_UNIQUE_ID_SIZE;
    }
    else if(ret == UCSAPIERR_INVALID_SECURITY_LEVEL){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_SECURITY_LEVEL";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_SECURITY_LEVEL;
    }
    else if(ret == UCSAPIERR_INVALID_PARAMETER){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_PARAMETER";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_INVALID_PARAMETER;
    }
    else if(ret == UCSAPIERR_CODE_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_CODE_SIZE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_CODE_SIZE;
    }
    else if(ret == UCSAPIERR_PASSWORD_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_PASSWORD_SIZE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_PASSWORD_SIZE;
    }
    else if(ret == UCSAPIERR_MAX_CARD_NUMBER){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_MAX_CARD_NUMBER";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_MAX_CARD_NUMBER;
    }
    else if(ret == UCSAPIERR_MAX_FINGER_NUMBER){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_MAX_FINGER_NUMBER";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_MAX_FINGER_NUMBER;
    }
    else if(ret == UCSAPIERR_PICTURE_SIZE){
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :UCSAPIERR_PICTURE_SIZE";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
        return UCSAPIERR_PICTURE_SIZE;
    }
    else{
        qDebug() << "MAIN-->:Can Not UCS Send User to terminal id " << UCS_terminalId << " :SERVER_UNKNOWN";
        UCBioAPI_FreeExportData(&BSP_ExportedData);
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
    emit this->sig_main_resp_add(UserId,success,errorCode,UCS_terminalID,addinactive);
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

//UCS_UserName
void MainWidget::UCS_CreateUserName(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data)
{
    //UCS_UserName
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




//TimeZones
//TimeZonesa

void MainWidget::slot_fromterminal_timezone(quint32 TerminalId,int TimezoneCodeCount,QList<int>* codes, QList<int>* startHour, QList<int>* startMin, QList<int>* stopHour, QList<int>* stopMin)
{
//    if(!bstart){
//        emit this->sig_main_resp_timezoneResp(false,-11,TerminalId);
//        return;
//    }
//    qDebug() << TimezoneCodeCount;
//    for(int i=0 ; i<TimezoneCodeCount; i++ ){
//         qDebug() << "startHour[" << i << "].count() = " << startHour[i].count();
//    }
//    for(int i=0; i<TimezoneCodeCount; i++){
//        for(int j=0; j<startHour[i].count();j++){
//            qDebug() << "StartHour[" << i << "].at(" << j << ") = " << startHour[i].at(j);
//            qDebug() << "StartMin[" << i << "].at(" << j << ") = " << startMin[i].at(j);
//            qDebug() << "StopHour[" << i << "].at(" << j << ") = " << stopHour[i].at(j);
//            qDebug() << "StopMin[" << i << "].at(" << j << ") = " << stopMin[i].at(j);
//        }
//    }

    clearTimezones();
    createTimezones(TimezoneCodeCount,codes,startHour,startMin,stopHour,stopMin);
    CreateTimeZones(static_cast<UCSAPI_UINT32>(TimezoneCodeCount),UCS_Timezones);
    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    callbackFlag = 1;
    int functionsRes = static_cast<int>(SendACDTimeZonesToTerminal(UCS_ClientId,TerminalId));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc =false;
        emit this->sig_main_resp_timezoneResp(false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back timezone";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_timezoneResp(false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;
}

void MainWidget::clearTimezones()
{
    for(int i=0; i<UCSAPI_ACCESS_TIMEZONE_MAX; i++){
        UCS_Timezones[i].Code[0] = 0;
        UCS_Timezones[i].Code[1] = 0;
        UCS_Timezones[i].Code[2] = 0;
        UCS_Timezones[i].Code[3] = 0;
        for(int j=0; j<12; j++){
            UCS_Timezones[i].Zone[j].StartTime.Hour = 0;
            UCS_Timezones[i].Zone[j].StartTime.Minute = 0;
            UCS_Timezones[i].Zone[j].EndTime.Hour = 0;
            UCS_Timezones[i].Zone[j].EndTime.Minute = 0;
        }
    }
}

void MainWidget::createTimezones(int TimezoneCodeCount, QList<int> *codes, QList<int> *startHour, QList<int> *startMin, QList<int> *stopHour, QList<int> *stopMin)
{
    qDebug() << "MAIN-->: Timezones_count = " << TimezoneCodeCount;
    for(int i=0; i<TimezoneCodeCount; i++){
        QString code = QString("%1").arg(codes->at(i), 4, 10, QChar('0'));
        qDebug() << "Time zone codes " <<  code;

        UCS_Timezones[i].Code[0] = code.at(0).toLatin1();
        UCS_Timezones[i].Code[1] = code.at(1).toLatin1();
        UCS_Timezones[i].Code[2] = code.at(2).toLatin1();
        UCS_Timezones[i].Code[3] = code.at(3).toLatin1();

        qDebug() << "MAIN-->:Timezones_code : " << UCS_Timezones[i].Code[0] << UCS_Timezones[i].Code[1] << UCS_Timezones[i].Code[2] << UCS_Timezones[i].Code[3];
        for(int j=0; j<startHour[i].count();j++){

            UCS_Timezones[i].Zone[j].StartTime.Hour=static_cast<UCSAPI_UINT8>(startHour[i].at(j));
            UCS_Timezones[i].Zone[j].StartTime.Minute=static_cast<UCSAPI_UINT8>(startMin[i].at(j));
            UCS_Timezones[i].Zone[j].EndTime.Hour=static_cast<UCSAPI_UINT8>(stopHour[i].at(j));
            UCS_Timezones[i].Zone[j].EndTime.Minute=static_cast<UCSAPI_UINT8>(stopMin[i].at(j));

            qDebug() << "MAIN-->:-->StartTime: " << UCS_Timezones[i].Zone[j].StartTime.Hour << ":" << UCS_Timezones[i].Zone[j].StartTime.Minute << " EndTime: " << UCS_Timezones[i].Zone[j].EndTime.Hour << ":" <<  UCS_Timezones[i].Zone[j].EndTime.Minute;
        }
    }
}

int MainWidget::SendACDTimeZonesToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId)
{
    UCSAPI_RETURN ret = UCSAPI_SetAccessControlDataToTerminal(quint16(UCS_clientId),UCS_terminalId,&UCS_AccessControlDataTimezones);
    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can Send TimeZones To Terminal: UCSAPIERR_NONE";
        return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not Send TimeZones To Terminal id " << UCS_terminalId << ":UCSAPIERR_NOT_SERVER_ACTIVE";
        return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else if(ret == UCSAPIERR_INVALID_POINTER){
        qDebug() << "MAIN-->:Can Not Send TimeZones To Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_POINTER";
        return UCSAPIERR_INVALID_POINTER;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not Send TimeZones To Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_TERMINAL";
        return UCSAPIERR_INVALID_TERMINAL;
    }
    else{
        qDebug() << "MAIN-->:Can Not Send TimeZones To Terminal id " << UCS_terminalId << ":SERVER_UNKNOWN";
        return SERVER_UNKNOWN;
    }
}

void MainWidget::slot_frommain_TimezoneCallbackResp(quint32 error,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:add timezone call back";
    callbackFlag = 0;
    UCS_p_TimezoneCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_TimezoneCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);

    int errorCode = static_cast<int>(UCS_p_TimezoneCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;
    tCMD.stop();
    bInProc = false;
    emit this->sig_main_resp_timezoneResp(success,errorCode,UCS_terminalID);
    delete UCS_p_TimezoneCallback0;
    delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);


    return;
}

void MainWidget::CreateTimeZones(UCSAPI_UINT32 UCS_timezoneNum,UCSAPI_ACCESS_TIMEZONE UCS_timezones[UCSAPI_ACCESS_TIMEZONE_MAX])
{
    UCS_AccessControlDataTimezones.DataType = UCSAPI_ACCESS_CONTROL_DATA_TYPE_TIMEZONE;
    UCS_AccessTimezonesData.TimezoneNum = UCS_timezoneNum;
    for(int i=0; i<UCSAPI_ACCESS_TIMEZONE_MAX; i++)
        UCS_AccessTimezonesData.Timezone[i] = UCS_timezones[i];
    UCS_AccessControlDataTimezones.Data.Timezone = &UCS_AccessTimezonesData;

}

void MainWidget::AddTimeZoneToStruct(UCSAPI_CHAR UCS_code0,UCSAPI_TIMEZONE UCS_zone0,int index,
                                     UCSAPI_CHAR UCS_code1,UCSAPI_TIMEZONE UCS_zone1,
                                     UCSAPI_CHAR UCS_code2,UCSAPI_TIMEZONE UCS_zone2,
                                     UCSAPI_CHAR UCS_code3,UCSAPI_TIMEZONE UCS_zone3,
                                                           UCSAPI_TIMEZONE UCS_zone4,
                                                           UCSAPI_TIMEZONE UCS_zone5,
                                                           UCSAPI_TIMEZONE UCS_zone6,
                                                           UCSAPI_TIMEZONE UCS_zone7,
                                                           UCSAPI_TIMEZONE UCS_zone8,
                                                           UCSAPI_TIMEZONE UCS_zone9,
                                                           UCSAPI_TIMEZONE UCS_zone10,
                                                           UCSAPI_TIMEZONE UCS_zone11)
{
    UCS_Timezones[index].Code[0] = UCS_code0;
    UCS_Timezones[index].Code[1] = UCS_code1;
    UCS_Timezones[index].Code[2] = UCS_code2;
    UCS_Timezones[index].Code[3] = UCS_code3;

    UCS_Timezones[index].Zone[0] = UCS_zone0;
    UCS_Timezones[index].Zone[1] = UCS_zone1;
    UCS_Timezones[index].Zone[2] = UCS_zone2;
    UCS_Timezones[index].Zone[3] = UCS_zone3;
    UCS_Timezones[index].Zone[4] = UCS_zone4;
    UCS_Timezones[index].Zone[5] = UCS_zone5;
    UCS_Timezones[index].Zone[6] = UCS_zone6;
    UCS_Timezones[index].Zone[7] = UCS_zone7;
    UCS_Timezones[index].Zone[8] = UCS_zone8;
    UCS_Timezones[index].Zone[9] = UCS_zone9;
    UCS_Timezones[index].Zone[10] = UCS_zone10;
    UCS_Timezones[index].Zone[11] = UCS_zone11;

    for(int i=0; i<4; i++)
        UCS_Timezones[index].Reserved[i] = 0;
}

void MainWidget::CreateZone(int indexZone,UCSAPI_UINT8 UCS_startHour,UCSAPI_UINT8 UCS_startMinute,UCSAPI_UINT8 UCS_stopHour,UCSAPI_UINT8 UCS_stopMinute)
{
    UCS_Zone[indexZone].StartTime.Hour = UCS_startHour;
    UCS_Zone[indexZone].StartTime.Minute = UCS_startMinute;
    UCS_Zone[indexZone].EndTime.Hour = UCS_stopHour;
    UCS_Zone[indexZone].EndTime.Minute = UCS_stopMinute;
}

//TimeZones
//TimeZones


//holidays
//holidays

void MainWidget::slot_fromterminal_hol(quint32 TerminalId,int HolidayCodeCount,QList<int>* codes,QList<int>* datesM,QList<int>* datesD)
{
//    if(!bstart){
//        emit this->sig_main_resp_holResp(false,-11,TerminalId);
//        return;
//    }
//    qDebug() << HolidayCodeCount;
//    for(int i=0 ; i<HolidayCodeCount; i++ ){
//         qDebug() << "codes[" << i << "] = " << codes[i];
//         for(int j=0; j<datesM[i].count();j++){
//             qDebug() << "datesM[" << i << "].at(" << j << ") = " << datesM[i].at(j);
//             qDebug() << "datesD[" << i << "].at(" << j << ") = " << datesD[i].at(j);;
//         }
//    }
    clearHolidays();
    createHolidays(HolidayCodeCount,codes,datesM,datesD);
    CreateHoliday(static_cast<UCSAPI_UINT32>(HolidayCodeCount),UCS_Holidays);
    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    callbackFlag = 2;
    int functionsRes = static_cast<int>(SendACDHolidaysToTerminal(UCS_ClientId,TerminalId));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_holResp(false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back holiday";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_holResp(false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;

}

void MainWidget::clearHolidays()
{
    for(int i=0; i<UCSAPI_ACCESS_HOLIDAY_MAX; i++){
        UCS_Holidays[i].Code[0] = 0;
        UCS_Holidays[i].Code[1] = 0;
        UCS_Holidays[i].Code[2] = 0;
        UCS_Holidays[i].Code[3] = 0;
        for(int j=0 ; j<32; j++){
            UCS_Holidays[i].Date[j].Month = 0;
            UCS_Holidays[i].Date[j].Day = 0;
        }
    }
    return;
}

void MainWidget::createHolidays(int HolidayCodeCount,QList<int>* codes,QList<int>* datesM,QList<int>* datesD)
{
    qDebug() << "MAIN-->:Holiday_count =" << HolidayCodeCount;
    for(int i=0 ; i<HolidayCodeCount; i++ ){
        QString code = QString("%1").arg(codes->at(i), 4, 10, QChar('0'));
        //qDebug() << "MAIN-->:Holiday_codes[" << i << "] = " <<code;
        UCS_Holidays[i].Code[0] = code.at(0).toLatin1();
        UCS_Holidays[i].Code[1] = code.at(1).toLatin1();
        UCS_Holidays[i].Code[2] = code.at(2).toLatin1();
        UCS_Holidays[i].Code[3] = code.at(3).toLatin1();

        qDebug() << "MAIN-->:Holiday_codes: " << UCS_Holidays[i].Code[0] << UCS_Holidays[i].Code[1] << UCS_Holidays[i].Code[2] << UCS_Holidays[i].Code[3];
        for(int j=0; j<datesM[i].count();j++){
            UCS_Holidays[i].Date[j].Month = static_cast<UCSAPI_UINT16>(datesM[i].at(j));
            UCS_Holidays[i].Date[j].Day = static_cast<UCSAPI_UINT16>(datesD[i].at(j));
            qDebug() << "MAIN-->:Holiday_date: " << UCS_Holidays[i].Date[j].Month << "/" << UCS_Holidays[i].Date[j].Day;
        }
    }
}

int MainWidget::SendACDHolidaysToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId)
{
    UCSAPI_RETURN ret = UCSAPI_SetAccessControlDataToTerminal(quint16(UCS_clientId),UCS_terminalId,&UCS_AccessControlDataHolidays);
    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can Send Holiday To Terminal id " << UCS_terminalId << ":UCSAPIERR_NONE";
        return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not Send Holiday To Terminal id " << UCS_terminalId << ":UCSAPIERR_NOT_SERVER_ACTIVE";
        return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else if(ret == UCSAPIERR_INVALID_POINTER){
        qDebug() << "MAIN-->:Can Not Send Holiday To Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_POINTER";
        return UCSAPIERR_INVALID_POINTER;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not Send Holiday To Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_TERMINAL";
        return UCSAPIERR_INVALID_TERMINAL;
    }
    else{
        qDebug() << "MAIN-->:Can Not Send Holiday To Terminal id " << UCS_terminalId << ":SERVER_UNKNOWN";
        return SERVER_UNKNOWN;
    }
}

void MainWidget::slot_frommain_HolidayCallbackResp(quint32 error,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:add holiday callback";
    callbackFlag = 0;
    UCS_p_HolidayCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_HolidayCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);

    int errorCode = static_cast<int>(UCS_p_HolidayCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;
    tCMD.stop();
    bInProc = false;
    emit this->sig_main_resp_holResp(success,errorCode,UCS_terminalID);
    delete UCS_p_HolidayCallback0;
    delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);
    return;
}

void MainWidget::CreateHoliday(UCSAPI_UINT32 UCS_holidayNum, UCSAPI_ACCESS_HOLIDAY UCS_holidays[UCSAPI_ACCESS_HOLIDAY_MAX])
{
    UCS_AccessControlDataHolidays.DataType = UCSAPI_ACCESS_CONTROL_DATA_TYPE_HOLIDAY;
    UCS_HolidaysData.HolidayNum = UCS_holidayNum;
    for(int i=0; i<UCSAPI_ACCESS_HOLIDAY_MAX; i++)
        UCS_HolidaysData.Holiday[i] = UCS_holidays[i];
    UCS_AccessControlDataHolidays.Data.Holiday = &UCS_HolidaysData;
}

void MainWidget::AddHolidayToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_DATE_MM_DD UCS_date0, int index,
                                    UCSAPI_CHAR UCS_code1, UCSAPI_DATE_MM_DD UCS_date1,  UCSAPI_DATE_MM_DD UCS_date11, UCSAPI_DATE_MM_DD UCS_date21, UCSAPI_DATE_MM_DD UCS_date31,
                                    UCSAPI_CHAR UCS_code2, UCSAPI_DATE_MM_DD UCS_date2,  UCSAPI_DATE_MM_DD UCS_date12, UCSAPI_DATE_MM_DD UCS_date22,
                                    UCSAPI_CHAR UCS_code3, UCSAPI_DATE_MM_DD UCS_date3,  UCSAPI_DATE_MM_DD UCS_date13, UCSAPI_DATE_MM_DD UCS_date23,
                                                           UCSAPI_DATE_MM_DD UCS_date4,  UCSAPI_DATE_MM_DD UCS_date14, UCSAPI_DATE_MM_DD UCS_date24,
                                                           UCSAPI_DATE_MM_DD UCS_date5,  UCSAPI_DATE_MM_DD UCS_date15, UCSAPI_DATE_MM_DD UCS_date25,
                                                           UCSAPI_DATE_MM_DD UCS_date6,  UCSAPI_DATE_MM_DD UCS_date16, UCSAPI_DATE_MM_DD UCS_date26,
                                                           UCSAPI_DATE_MM_DD UCS_date7,  UCSAPI_DATE_MM_DD UCS_date17, UCSAPI_DATE_MM_DD UCS_date27,
                                                           UCSAPI_DATE_MM_DD UCS_date8,  UCSAPI_DATE_MM_DD UCS_date18, UCSAPI_DATE_MM_DD UCS_date28,
                                                           UCSAPI_DATE_MM_DD UCS_date9,  UCSAPI_DATE_MM_DD UCS_date19, UCSAPI_DATE_MM_DD UCS_date29,
                                                           UCSAPI_DATE_MM_DD UCS_date10, UCSAPI_DATE_MM_DD UCS_date20, UCSAPI_DATE_MM_DD UCS_date30)
{
    UCS_Holidays[index].Code[0] = UCS_code0;
    UCS_Holidays[index].Code[1] = UCS_code1;
    UCS_Holidays[index].Code[2] = UCS_code2;
    UCS_Holidays[index].Code[3] = UCS_code3;

    UCS_Holidays[index].Date[0] = UCS_date0;
    UCS_Holidays[index].Date[1] = UCS_date1;
    UCS_Holidays[index].Date[2] = UCS_date2;
    UCS_Holidays[index].Date[3] = UCS_date3;
    UCS_Holidays[index].Date[4] = UCS_date4;
    UCS_Holidays[index].Date[5] = UCS_date5;
    UCS_Holidays[index].Date[6] = UCS_date6;
    UCS_Holidays[index].Date[7] = UCS_date7;
    UCS_Holidays[index].Date[8] = UCS_date8;
    UCS_Holidays[index].Date[9] = UCS_date9;
    UCS_Holidays[index].Date[10] = UCS_date10;
    UCS_Holidays[index].Date[11] = UCS_date11;
    UCS_Holidays[index].Date[12] = UCS_date12;
    UCS_Holidays[index].Date[13] = UCS_date13;
    UCS_Holidays[index].Date[14] = UCS_date14;
    UCS_Holidays[index].Date[15] = UCS_date15;
    UCS_Holidays[index].Date[16] = UCS_date16;
    UCS_Holidays[index].Date[17] = UCS_date17;
    UCS_Holidays[index].Date[18] = UCS_date18;
    UCS_Holidays[index].Date[19] = UCS_date19;
    UCS_Holidays[index].Date[20] = UCS_date20;
    UCS_Holidays[index].Date[21] = UCS_date21;
    UCS_Holidays[index].Date[22] = UCS_date22;
    UCS_Holidays[index].Date[23] = UCS_date23;
    UCS_Holidays[index].Date[24] = UCS_date24;
    UCS_Holidays[index].Date[25] = UCS_date25;
    UCS_Holidays[index].Date[26] = UCS_date26;
    UCS_Holidays[index].Date[27] = UCS_date27;
    UCS_Holidays[index].Date[28] = UCS_date28;
    UCS_Holidays[index].Date[29] = UCS_date29;
    UCS_Holidays[index].Date[30] = UCS_date30;
    UCS_Holidays[index].Date[31] = UCS_date31;
}

void MainWidget::CreateHolidayDate(int index,UCSAPI_UINT16 UCS_month,UCSAPI_UINT16 UCS_day)
{
    UCS_Date[index].Month = UCS_month;
    UCS_Date[index].Day = UCS_day;
}

//holidays
//holidays

//access
//access

void MainWidget::slot_fromterminal_access(quint32 TerminalId,int AccessCodesCount,QList<int>* codes,int * holCoes,QList<int>* dayNum,QList<int>* dayCode)
{
//    if(!bstart){
//        emit this->sig_main_resp_accessResp(false,-11,TerminalId);
//        return;
//    }
//    qDebug() << AccessCodesCount;
//    for(int i=0 ; i<AccessCodesCount; i++ ){
//         qDebug() << "codes[" << i << "] = " << codes[i];
//         qDebug() << "holCoes[" << i << "] = " << holCoes[i];
//         for(int j=0; j<dayNum[i].count();j++){
//             qDebug() << "dayNum[" << i << "].at(" << j << ") = " << dayNum[i].at(j);
//             qDebug() << "dayCode[" << i << "].at(" << j << ") = " << dayCode[i].at(j);;
//         }
//    }
    clearAcesses();
    createAccesses(AccessCodesCount,codes,holCoes,dayNum,dayCode);
    CreateAccess(static_cast<UCSAPI_UINT32>(AccessCodesCount),UCS_Accesses);
    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    callbackFlag = 3;
    int functionsRes = static_cast<int>(SendACDAccessToTerminal(UCS_ClientId,TerminalId));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_accessResp(false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back access";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_accessResp(false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;

}

void MainWidget::clearAcesses()
{
    for(int i=0; i<UCSAPI_ACCESS_TIME_MAX; i++){
        UCS_Accesses[i].Code[0] = 0;
        UCS_Accesses[i].Code[1] = 0;
        UCS_Accesses[i].Code[2] = 0;
        UCS_Accesses[i].Code[3] = 0;

        UCS_Accesses[i].Holiday[0] = 0;
        UCS_Accesses[i].Holiday[1] = 0;
        UCS_Accesses[i].Holiday[2] = 0;
        UCS_Accesses[i].Holiday[3] = 0;

        UCS_Accesses[i].Timezone.Fri[0] = 0;
        UCS_Accesses[i].Timezone.Fri[1] = 0;
        UCS_Accesses[i].Timezone.Fri[2] = 0;
        UCS_Accesses[i].Timezone.Fri[3] = 0;

        UCS_Accesses[i].Timezone.Hol[0] = 0;
        UCS_Accesses[i].Timezone.Hol[1] = 0;
        UCS_Accesses[i].Timezone.Hol[2] = 0;
        UCS_Accesses[i].Timezone.Hol[3] = 0;

        UCS_Accesses[i].Timezone.Mon[0] = 0;
        UCS_Accesses[i].Timezone.Mon[1] = 0;
        UCS_Accesses[i].Timezone.Mon[2] = 0;
        UCS_Accesses[i].Timezone.Mon[3] = 0;

        UCS_Accesses[i].Timezone.Sat[0] = 0;
        UCS_Accesses[i].Timezone.Sat[1] = 0;
        UCS_Accesses[i].Timezone.Sat[2] = 0;
        UCS_Accesses[i].Timezone.Sat[3] = 0;

        UCS_Accesses[i].Timezone.Sun[0] = 0;
        UCS_Accesses[i].Timezone.Sun[1] = 0;
        UCS_Accesses[i].Timezone.Sun[2] = 0;
        UCS_Accesses[i].Timezone.Sun[3] = 0;

        UCS_Accesses[i].Timezone.Thu[0] = 0;
        UCS_Accesses[i].Timezone.Thu[1] = 0;
        UCS_Accesses[i].Timezone.Thu[2] = 0;
        UCS_Accesses[i].Timezone.Thu[3] = 0;

        UCS_Accesses[i].Timezone.Tue[0] = 0;
        UCS_Accesses[i].Timezone.Tue[1] = 0;
        UCS_Accesses[i].Timezone.Tue[2] = 0;
        UCS_Accesses[i].Timezone.Tue[3] = 0;

        UCS_Accesses[i].Timezone.Wed[0] = 0;
        UCS_Accesses[i].Timezone.Wed[1] = 0;
        UCS_Accesses[i].Timezone.Wed[2] = 0;
        UCS_Accesses[i].Timezone.Wed[3] = 0;
    }
    return;
}

void MainWidget::createAccesses(int AccessCodesCount,QList<int>* codes,int * holCoes,QList<int>* dayNum,QList<int>* dayCode)
{
    qDebug() << "MAIN-->:AccessTime_Count = " << AccessCodesCount;
    for(int i=0; i<AccessCodesCount; i++){
        QString code = QString("%1").arg(codes->at(i), 4, 10, QChar('0'));
        //qDebug() << "AccessTime_codes[" << i << "] = " << code;
        QString holcode = QString("%1").arg(holCoes[i], 4, 10, QChar('0'));
       //qDebug() << "AccessTime_holidaycode[" << i << "] = " <<holcode;
        UCS_Accesses[i].Code[0] = code.at(0).toLatin1();
        UCS_Accesses[i].Code[1] = code.at(1).toLatin1();
        UCS_Accesses[i].Code[2] = code.at(2).toLatin1();
        UCS_Accesses[i].Code[3] = code.at(3).toLatin1();

        UCS_Accesses[i].Holiday[0] = holcode.at(0).toLatin1();
        UCS_Accesses[i].Holiday[1] = holcode.at(1).toLatin1();
        UCS_Accesses[i].Holiday[2] = holcode.at(2).toLatin1();
        UCS_Accesses[i].Holiday[3] = holcode.at(3).toLatin1();
//        qDebug() << "dayNum[" << i << "].count() = " << dayNum[i].count();
//        for(int z=0; z < (dayNum[i].count()); z++){
//            qDebug() << "i = " << i << ", z = " << z;
//                qDebug() << "dayNum["<< i << "].at("<< z << ") = " << dayNum[i].at(z);

//        }

        qDebug() << "MAIN-->: AccessTimeCode: " << UCS_Accesses[i].Code[0] << UCS_Accesses[i].Code[1] << UCS_Accesses[i].Code[2] << UCS_Accesses[i].Code[3];
        qDebug() << "MAIN-->: AccessTimeHolidayCode: " << UCS_Accesses[i].Holiday[0] << UCS_Accesses[i].Holiday[1] << UCS_Accesses[i].Holiday[2] << UCS_Accesses[i].Holiday[3];

        for(int j=0; j<dayNum[i].count(); j++){
            //qDebug() << "MAIN-->: dayNum[" << i << "].at(" << j << ") = " << dayNum[i].at(j);
            if(dayNum[i].at(j) == 0){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Hol[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Hol[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Hol[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Hol[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_HolDayAccess: " << UCS_Accesses[i].Timezone.Hol[0] << UCS_Accesses[i].Timezone.Hol[1] << UCS_Accesses[i].Timezone.Hol[2] << UCS_Accesses[i].Timezone.Hol[3];
            }
            else if(dayNum[i].at(j) == 1){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Sat[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Sat[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Sat[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Sat[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Sat: " << UCS_Accesses[i].Timezone.Sat[0] << UCS_Accesses[i].Timezone.Sat[1] << UCS_Accesses[i].Timezone.Sat[2] << UCS_Accesses[i].Timezone.Sat[3];
            }
            else if(dayNum[i].at(j) == 2){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Sun[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Sun[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Sun[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Sun[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Sun: " << UCS_Accesses[i].Timezone.Sun[0] << UCS_Accesses[i].Timezone.Sun[1] << UCS_Accesses[i].Timezone.Sun[2] << UCS_Accesses[i].Timezone.Sun[3];
            }
            else if(dayNum[i].at(j) == 2){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Mon[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Mon[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Mon[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Mon[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Mon: " << UCS_Accesses[i].Timezone.Mon[0] << UCS_Accesses[i].Timezone.Mon[1] << UCS_Accesses[i].Timezone.Mon[2] << UCS_Accesses[i].Timezone.Mon[3];
            }
            else if(dayNum[i].at(j) == 4){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Tue[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Tue[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Tue[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Tue[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Tue: " << UCS_Accesses[i].Timezone.Tue[0] << UCS_Accesses[i].Timezone.Tue[1] << UCS_Accesses[i].Timezone.Tue[2] << UCS_Accesses[i].Timezone.Tue[3];
            }
            else if(dayNum[i].at(j) == 5){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Wed[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Wed[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Wed[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Wed[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Wed: " << UCS_Accesses[i].Timezone.Wed[0] << UCS_Accesses[i].Timezone.Wed[1] << UCS_Accesses[i].Timezone.Wed[2] << UCS_Accesses[i].Timezone.Wed[3];
            }
            else if(dayNum[i].at(j) == 6){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Thu[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Thu[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Thu[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Thu[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Thu: " << UCS_Accesses[i].Timezone.Thu[0] << UCS_Accesses[i].Timezone.Thu[1] << UCS_Accesses[i].Timezone.Thu[2] << UCS_Accesses[i].Timezone.Thu[3];
            }
            else if(dayNum[i].at(j) == 7){
                QString code = QString("%1").arg(dayCode[i].at(j), 4, 10, QChar('0'));
                UCS_Accesses[i].Timezone.Fri[0] = code.at(0).toLatin1();
                UCS_Accesses[i].Timezone.Fri[1] = code.at(1).toLatin1();
                UCS_Accesses[i].Timezone.Fri[2] = code.at(2).toLatin1();
                UCS_Accesses[i].Timezone.Fri[3] = code.at(3).toLatin1();

                qDebug() << "MAIN-->: AccessTime_Fri: " << UCS_Accesses[i].Timezone.Fri[0] << UCS_Accesses[i].Timezone.Fri[1] << UCS_Accesses[i].Timezone.Fri[2] << UCS_Accesses[i].Timezone.Fri[3];
            }
        }
    }
    return;
}

int MainWidget::SendACDAccessToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId)
{
    UCSAPI_RETURN ret = UCSAPI_SetAccessControlDataToTerminal(quint16(UCS_clientId),UCS_terminalId,&UCS_AccessControlDataAccess);
    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can Send Access To Terminal: UCSAPIERR_NONE";
        return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not Send Access To Terminal id " << UCS_terminalId << ":UCSAPIERR_NOT_SERVER_ACTIVE";
        return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else if(ret == UCSAPIERR_INVALID_POINTER){
        qDebug() << "MAIN-->:Can Not Send Access To Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_POINTER";
        return UCSAPIERR_INVALID_POINTER;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not Send Access To Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_TERMINAL";
        return UCSAPIERR_INVALID_TERMINAL;
    }
    else{
        qDebug() << "MAIN-->:Can Not Send Access To Terminal id " << UCS_terminalId << ":SERVER_UNKNOWN";
        return SERVER_UNKNOWN;
    }
}

void MainWidget::slot_frommain_AccessCallbackResp(quint32 error,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:add access callback";
    callbackFlag = 0;
    UCS_p_AccessCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_AccessCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);

    int errorCode = static_cast<int>(UCS_p_AccessCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;
    tCMD.stop();
    bInProc = false;
    emit this->sig_main_resp_accessResp(success,errorCode,UCS_terminalID);
    delete UCS_p_AccessCallback0;
    delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);

    return;
}

void MainWidget::CreateAccess(UCSAPI_UINT32 UCS_accessTimeNum, UCSAPI_ACCESS_TIME UCS_accesses[UCSAPI_ACCESS_TIME_MAX])
{
    UCS_AccessControlDataAccess.DataType = UCSAPI_ACCESS_CONTROL_DATA_TYPE_TIME;
    UCS_AccessTimeData.AccessTimeNum = UCS_accessTimeNum;
    for(int i=0; i<UCSAPI_ACCESS_TIME_MAX; i++)
        UCS_AccessTimeData.AccessTime[i] = UCS_accesses[i];
    UCS_AccessControlDataAccess.Data.AccessTime = &UCS_AccessTimeData;
}

void MainWidget::AddAccessToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_CHAR UCS_hcode0,int index, UCSAPI_ACCESS_TIMEZONE_CODE UCS_timeWeek,
                                   UCSAPI_CHAR UCS_code1, UCSAPI_CHAR UCS_hcode1,
                                   UCSAPI_CHAR UCS_code2, UCSAPI_CHAR UCS_hcode2,
                                   UCSAPI_CHAR UCS_code3, UCSAPI_CHAR UCS_hcode3)
{
    UCS_Accesses[index].Code[0] = UCS_code0;
    UCS_Accesses[index].Code[1] = UCS_code1;
    UCS_Accesses[index].Code[2] = UCS_code2;
    UCS_Accesses[index].Code[3] = UCS_code3;

    UCS_Accesses[index].Holiday[0] = UCS_hcode0;
    UCS_Accesses[index].Holiday[1] = UCS_hcode1;
    UCS_Accesses[index].Holiday[2] = UCS_hcode2;
    UCS_Accesses[index].Holiday[3] = UCS_hcode3;

    UCS_Accesses[index].Timezone = UCS_timeWeek;
}


void MainWidget::CreateAccess(UCSAPI_CHAR UCS_monCode0, UCSAPI_CHAR UCS_tueCode0, UCSAPI_CHAR UCS_wedCode0, UCSAPI_CHAR UCS_theCode0, UCSAPI_CHAR UCS_friCode0, UCSAPI_CHAR UCS_satCode0, UCSAPI_CHAR UCS_sunCode0, UCSAPI_CHAR UCS_holCode0,
                              UCSAPI_CHAR UCS_monCode1, UCSAPI_CHAR UCS_tueCode1, UCSAPI_CHAR UCS_wedCode1, UCSAPI_CHAR UCS_theCode1, UCSAPI_CHAR UCS_friCode1, UCSAPI_CHAR UCS_satCode1, UCSAPI_CHAR UCS_sunCode1, UCSAPI_CHAR UCS_holCode1,
                              UCSAPI_CHAR UCS_monCode2, UCSAPI_CHAR UCS_tueCode2, UCSAPI_CHAR UCS_wedCode2, UCSAPI_CHAR UCS_theCode2, UCSAPI_CHAR UCS_friCode2, UCSAPI_CHAR UCS_satCode2, UCSAPI_CHAR UCS_sunCode2, UCSAPI_CHAR UCS_holCode2,
                              UCSAPI_CHAR UCS_monCode3, UCSAPI_CHAR UCS_tueCode3, UCSAPI_CHAR UCS_wedCode3, UCSAPI_CHAR UCS_theCode3, UCSAPI_CHAR UCS_friCode3, UCSAPI_CHAR UCS_satCode3, UCSAPI_CHAR UCS_sunCode3, UCSAPI_CHAR UCS_holCode3)
{
    UCS_AccessWeek.Mon[0] = UCS_monCode0;
    UCS_AccessWeek.Mon[1] = UCS_monCode1;
    UCS_AccessWeek.Mon[2] = UCS_monCode2;
    UCS_AccessWeek.Mon[3] = UCS_monCode3;

    UCS_AccessWeek.Tue[0] = UCS_tueCode0;
    UCS_AccessWeek.Tue[1] = UCS_tueCode1;
    UCS_AccessWeek.Tue[2] = UCS_tueCode2;
    UCS_AccessWeek.Tue[3] = UCS_tueCode3;

    UCS_AccessWeek.Wed[0] = UCS_wedCode0;
    UCS_AccessWeek.Wed[1] = UCS_wedCode1;
    UCS_AccessWeek.Wed[2] = UCS_wedCode2;
    UCS_AccessWeek.Wed[3] = UCS_wedCode3;

    UCS_AccessWeek.Thu[0] = UCS_theCode0;
    UCS_AccessWeek.Thu[1] = UCS_theCode1;
    UCS_AccessWeek.Thu[2] = UCS_theCode2;
    UCS_AccessWeek.Thu[3] = UCS_theCode3;

    UCS_AccessWeek.Fri[0] = UCS_friCode0;
    UCS_AccessWeek.Fri[1] = UCS_friCode1;
    UCS_AccessWeek.Fri[2] = UCS_friCode2;
    UCS_AccessWeek.Fri[3] = UCS_friCode3;

    UCS_AccessWeek.Sat[0] = UCS_satCode0;
    UCS_AccessWeek.Sat[1] = UCS_satCode1;
    UCS_AccessWeek.Sat[2] = UCS_satCode2;
    UCS_AccessWeek.Sat[3] = UCS_satCode3;

    UCS_AccessWeek.Sun[0] = UCS_sunCode0;
    UCS_AccessWeek.Sun[1] = UCS_sunCode1;
    UCS_AccessWeek.Sun[2] = UCS_sunCode2;
    UCS_AccessWeek.Sun[3] = UCS_sunCode3;

    UCS_AccessWeek.Hol[0] = UCS_holCode0;
    UCS_AccessWeek.Hol[1] = UCS_holCode1;
    UCS_AccessWeek.Hol[2] = UCS_holCode2;
    UCS_AccessWeek.Hol[3] = UCS_holCode3;


}
//access
//access


//groups
//groups

void MainWidget::slot_fromterminal_group(quint32 TerminalId,int GroupCodesCount,QList<int>* codes,QList<int>* accCoes)
{
//    if(!bstart){
//        emit this->sig_main_resp_groupResp(false,-11,TerminalId);
//        return;
//    }
//    qDebug() << "GroupCodesCount: " << GroupCodesCount;
//    for(int i=0 ; i<GroupCodesCount; i++ ){
//         qDebug() << "codes[" << i << "] = " << codes[i];
//         for(int j=0; j<accCoes[i].count();j++){
//             qDebug() << "accCoes[" << i << "].at(" << j << ") = " << accCoes[i].at(j);
//         }
//    }


    clearGroups();

    createGroups(GroupCodesCount,codes,accCoes);
    CreateGroup(static_cast<UCSAPI_UINT32>(GroupCodesCount),UCS_Groups);
    bTimeout = false;
    tCMD.start(iCMDTimeout);
    bInProc = true;
    callbackFlag = 4;
    int functionsRes = static_cast<int>(SendACDGroupToTerminal(UCS_ClientId,TerminalId));
    if(functionsRes != 0){
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_groupResp(false,functionsRes,TerminalId);
        return;
    }
    while(bInProc){
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    if(bTimeout){
        qDebug() << "MAIN-->:time out in call back group";
        tCMD.stop();
        bInProc = false;
        emit this->sig_main_resp_groupResp(false,SERVER_TIMEOUT,TerminalId);
        return;
    }
    return;
}

void MainWidget::clearGroups()
{
    for(int i=0; i<UCSAPI_ACCESS_GROUP_MAX; i++){
        UCS_Groups[i].Code[0] = 0;
        UCS_Groups[i].Code[1] = 0;
        UCS_Groups[i].Code[2] = 0;
        UCS_Groups[i].Code[3] = 0;

        UCS_Groups[i].AccssTime1[0] = 0;
        UCS_Groups[i].AccssTime1[1] = 0;
        UCS_Groups[i].AccssTime1[2] = 0;
        UCS_Groups[i].AccssTime1[3] = 0;

        UCS_Groups[i].AccssTime2[0] = 0;
        UCS_Groups[i].AccssTime2[1] = 0;
        UCS_Groups[i].AccssTime2[2] = 0;
        UCS_Groups[i].AccssTime2[3] = 0;

        UCS_Groups[i].AccssTime3[0] = 0;
        UCS_Groups[i].AccssTime3[1] = 0;
        UCS_Groups[i].AccssTime3[2] = 0;
        UCS_Groups[i].AccssTime3[3] = 0;

        UCS_Groups[i].AccssTime4[0] = 0;
        UCS_Groups[i].AccssTime4[1] = 0;
        UCS_Groups[i].AccssTime4[2] = 0;
        UCS_Groups[i].AccssTime4[3] = 0;
    }

}

void MainWidget::createGroups(int AccessCodesCount,QList<int>* codes,QList<int>* accCoes)
{
    qDebug() << "MAIN-->:AccessGroup_Count = " << AccessCodesCount;
    for(int i=0; i<AccessCodesCount; i++){
        QString code = QString("%1").arg(codes->at(i), 4, 10, QChar('0'));
        UCS_Groups[i].Code[0] = code.at(0).toLatin1();
        UCS_Groups[i].Code[1] = code.at(1).toLatin1();
        UCS_Groups[i].Code[2] = code.at(2).toLatin1();
        UCS_Groups[i].Code[3] = code.at(3).toLatin1();

       // qDebug() << code;
        qDebug() << "MAIN-->:AccessGroup_code = " << UCS_Groups[i].Code[0] << UCS_Groups[i].Code[1] << UCS_Groups[i].Code[2] << UCS_Groups[i].Code[3];
        for(int j=0; j<accCoes[i].count(); j++){
            if(j == 0){
                QString acode = QString("%1").arg(accCoes[i].at(j), 4, 10, QChar('0'));
                UCS_Groups[i].AccssTime1[0] = acode.at(0).toLatin1();
                UCS_Groups[i].AccssTime1[1] = acode.at(1).toLatin1();
                UCS_Groups[i].AccssTime1[2] = acode.at(2).toLatin1();
                UCS_Groups[i].AccssTime1[3] = acode.at(3).toLatin1();

                qDebug() << "MAIN-->:AccessGroup_Access1Code = " << UCS_Groups[i].AccssTime1[0] << UCS_Groups[i].AccssTime1[1] << UCS_Groups[i].AccssTime1[2] << UCS_Groups[i].AccssTime1[3];
            }
            else if(j == 1){
                QString acode = QString("%1").arg(accCoes[i].at(j), 4, 10, QChar('0'));
                UCS_Groups[i].AccssTime2[0] = acode.at(0).toLatin1();
                UCS_Groups[i].AccssTime2[1] = acode.at(1).toLatin1();
                UCS_Groups[i].AccssTime2[2] = acode.at(2).toLatin1();
                UCS_Groups[i].AccssTime2[3] = acode.at(3).toLatin1();

                qDebug() << "MAIN-->:AccessGroup_Access2Code = " << UCS_Groups[i].AccssTime2[0] << UCS_Groups[i].AccssTime2[1] << UCS_Groups[i].AccssTime2[2] << UCS_Groups[i].AccssTime2[3];
            }
            else if(j == 2){
                QString acode = QString("%1").arg(accCoes[i].at(j), 4, 10, QChar('0'));
                UCS_Groups[i].AccssTime3[0] = acode.at(0).toLatin1();
                UCS_Groups[i].AccssTime3[1] = acode.at(1).toLatin1();
                UCS_Groups[i].AccssTime3[2] = acode.at(2).toLatin1();
                UCS_Groups[i].AccssTime3[3] = acode.at(3).toLatin1();

                qDebug() << "MAIN-->:AccessGroup_Access3Code = " << UCS_Groups[i].AccssTime3[0] << UCS_Groups[i].AccssTime3[1] << UCS_Groups[i].AccssTime3[2] << UCS_Groups[i].AccssTime3[3];
            }
            else if(j == 3){
                QString acode = QString("%1").arg(accCoes[i].at(j), 4, 10, QChar('0'));
                UCS_Groups[i].AccssTime4[0] = acode.at(0).toLatin1();
                UCS_Groups[i].AccssTime4[1] = acode.at(1).toLatin1();
                UCS_Groups[i].AccssTime4[2] = acode.at(2).toLatin1();
                UCS_Groups[i].AccssTime4[3] = acode.at(3).toLatin1();

                qDebug() << "MAIN-->:AccessGroup_Access4Code = " << UCS_Groups[i].AccssTime4[0] << UCS_Groups[i].AccssTime4[1] << UCS_Groups[i].AccssTime4[2] << UCS_Groups[i].AccssTime4[3];
            }
        }
    }
    return;
}

int MainWidget::SendACDGroupToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId)
{
    UCSAPI_RETURN ret = UCSAPI_SetAccessControlDataToTerminal(quint16(UCS_clientId),UCS_terminalId,&UCS_AccessControlDataGroup);
    if(ret == UCSAPIERR_NONE){
       qDebug() << "MAIN-->:Can Send Group To Terminal id" << UCS_terminalId << " :UCSAPIERR_NONE";
       return UCSAPIERR_NONE;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
       qDebug() << "MAIN-->:Can Not Send Group To Terminal id " << UCS_terminalId << " :UCSAPIERR_NOT_SERVER_ACTIVE";
       return UCSAPIERR_NOT_SERVER_ACTIVE;
    }
    else if(ret == UCSAPIERR_INVALID_POINTER){
       qDebug() << "MAIN-->:Can Not Send Group To Terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_POINTER";
       return UCSAPIERR_INVALID_POINTER;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
       qDebug() << "MAIN-->:Can Not Send Group To Terminal id " << UCS_terminalId << " :UCSAPIERR_INVALID_TERMINAL";
       return UCSAPIERR_INVALID_TERMINAL;
    }
    else{
       qDebug() << "MAIN-->:Can Not Send Group To Terminal id " << UCS_terminalId << " :SERVER_UNKNOWN";
       return false;
    }
}

void MainWidget::slot_frommain_GroupCallbackResp(quint32 error,quint32 UCS_terminalID)
{
    qDebug() << "MAIN-->:add group callback";
    callbackFlag = 0;
    UCS_p_GroupCallback0 = new UCSAPI_CALLBACK_PARAM_0;
    UCS_p_GroupCallback0 = reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);

    int errorCode = static_cast<int>(UCS_p_GroupCallback0->ErrorCode);
    bool success = false;
    if(errorCode == 0)
        success = true;
    tCMD.stop();
    bInProc = false;

    emit this->sig_main_resp_groupResp(success,errorCode,UCS_terminalID);

    delete UCS_p_GroupCallback0;
    delete reinterpret_cast<UCSAPI_CALLBACK_PARAM_0_PTR>(error);

    //return
}

void MainWidget::CreateGroup(UCSAPI_UINT32 UCS_accessGroupNum, UCSAPI_ACCESS_GROUP UCS_groups[UCSAPI_ACCESS_GROUP_MAX])
{
    UCS_AccessControlDataGroup.DataType = UCSAPI_ACCESS_CONTROL_DATA_TYPE_GROUP;
    UCS_AccessGroupData.AccessGroupNum = UCS_accessGroupNum;
    for(int i=0; i<UCSAPI_ACCESS_GROUP_MAX; i++)
       UCS_AccessGroupData.AccessGroup[i] = UCS_groups[i];
    UCS_AccessControlDataGroup.Data.AccessGroup = &UCS_AccessGroupData;
}

void MainWidget::AddGroupToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_CHAR UCS_a1code0, UCSAPI_CHAR UCS_a2code0, UCSAPI_CHAR UCS_a3code0, UCSAPI_CHAR UCS_a4code0,int index,
                                  UCSAPI_CHAR UCS_code1, UCSAPI_CHAR UCS_a1code1, UCSAPI_CHAR UCS_a2code1, UCSAPI_CHAR UCS_a3code1, UCSAPI_CHAR UCS_a4code1,
                                  UCSAPI_CHAR UCS_code2, UCSAPI_CHAR UCS_a1code2, UCSAPI_CHAR UCS_a2code2, UCSAPI_CHAR UCS_a3code2, UCSAPI_CHAR UCS_a4code2,
                                  UCSAPI_CHAR UCS_code3, UCSAPI_CHAR UCS_a1code3, UCSAPI_CHAR UCS_a2code3, UCSAPI_CHAR UCS_a3code3, UCSAPI_CHAR UCS_a4code3 )
{
    UCS_Groups[index].Code[0] = UCS_code0;
    UCS_Groups[index].Code[1] = UCS_code1;
    UCS_Groups[index].Code[2] = UCS_code2;
    UCS_Groups[index].Code[3] = UCS_code3;

    UCS_Groups[index].AccssTime1[0] = UCS_a1code0;
    UCS_Groups[index].AccssTime1[1] = UCS_a1code1;
    UCS_Groups[index].AccssTime1[2] = UCS_a1code2;
    UCS_Groups[index].AccssTime1[3] = UCS_a1code3;

    UCS_Groups[index].AccssTime2[0] = UCS_a2code0;
    UCS_Groups[index].AccssTime2[1] = UCS_a2code1;
    UCS_Groups[index].AccssTime2[2] = UCS_a2code2;
    UCS_Groups[index].AccssTime2[3] = UCS_a2code3;

    UCS_Groups[index].AccssTime3[0] = UCS_a3code0;
    UCS_Groups[index].AccssTime3[1] = UCS_a3code1;
    UCS_Groups[index].AccssTime3[2] = UCS_a3code2;
    UCS_Groups[index].AccssTime3[3] = UCS_a3code3;

    UCS_Groups[index].AccssTime4[0] = UCS_a4code0;
    UCS_Groups[index].AccssTime4[1] = UCS_a4code1;
    UCS_Groups[index].AccssTime4[2] = UCS_a4code2;
    UCS_Groups[index].AccssTime4[3] = UCS_a4code3;
}

//groups
//groups

void MainWidget::slot_frommain_getStatus(quint32 TerminalId)
{
    GetAccessLogFromTerminal(UCS_ClientId,TerminalId,UCSAPI_GET_LOG_TYPE_NEW);
    return;
}

bool MainWidget::GetAccessLogFromTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId, UCSAPI_GET_LOG_TYPE UCS_logType)
{
    UCSAPI_RETURN ret =  UCSAPI_GetAccessLogFromTerminal(quint16(UCS_clientId),UCS_terminalId,UCS_logType);
    if(ret == UCSAPIERR_NONE){
        qDebug() << "MAIN-->:Can Request Logs From Terminal id " << UCS_terminalId << ": UCSAPIERR_NONE";
        return true;
    }
    else if(ret == UCSAPIERR_NOT_SERVER_ACTIVE){
        qDebug() << "MAIN-->:Can Not Request Logs From Terminal id " << UCS_terminalId << ":UCSAPIERR_NOT_SERVER_ACTIVE";
        return false;
    }
    else if(ret == UCSAPIERR_INVALID_PARAMETER){
        qDebug() << "MAIN-->:Can Not Request Logs From Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_PARAMETER";
        return false;
    }
    else if(ret == UCSAPIERR_INVALID_TERMINAL){
        qDebug() << "MAIN-->:Can Not Request Logs From Terminal id " << UCS_terminalId << ":UCSAPIERR_INVALID_TERMINAL";
        return false;
    }
    else{
        qDebug() << "MAIN-->:Can Not Request Logs From Terminal id " << UCS_terminalId << ":UCSAPIERR_UNKNOWN";
        return false;
    }
}


void MainWidget::slot_frommain_firstconnections(quint32 quiterminalId, quint32 quiClientId)
{
    qDebug() << "MAIN-->:terminal id: " << quiterminalId << " first connection with client id: " << quiClientId;
    for (int i=0; i<FirstTerminalList.count(); i++){
        if(FirstTerminalList.at(i) == quiterminalId)
            return;
    }
    FirstTerminalList.append(quiterminalId);
    if(FirstTerminalList.count() >= static_cast<int>(minimum_Terminals))
        bstart = true;
}

