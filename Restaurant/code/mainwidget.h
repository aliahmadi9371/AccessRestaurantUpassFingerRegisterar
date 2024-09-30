#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QDebug>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QSettings>
#include <QFile>
#include <stdio.h>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QPixmap>
#include <QNetworkInterface>

#include <winsock.h> //critical
//UCS SDK
#include "Inc/UCSAPI.h"
#include "Inc/UCSAPI_Basic.h"
#include "Inc/UCSAPI_Error.h"
#include "Inc/UCSAPI_Type.h"

//UCBio SDK
#include "Inc/UCBioAPI.h"
#include "Inc/UCBioAPI_Basic.h"
#include "Inc/UCBioAPI_Error.h"
#include "Inc/UCBioAPI_Export.h"
#include "Inc/UCBioAPI_ExportType.h"
#include "Inc/UCBioAPI_Type.h"


#include "websocket.h"
#include "usermanagement.h"
#include "logmanagement.h"
#include "globals.h"

#define SERVER_UNKNOWN -20
#define SERVER_LIMITATION -10
#define SERVER_BUSY -9
#define SERVER_INVALID_DATA_LENGTH -8
#define SERVER_INVALID_DATA -7
#define SERVER_TIMEOUT -6


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    //this

    int i_foodFontSize;
    QString s_foodFontName;

    int i_dateFontSize;
    QString s_dateFontName;

    int i_timeFontSize;
    QString s_timeFontName;


    QString sIniDate;
    QDate countDate;

    int iFoodCount1;
    int iFoodCount2;
    int iFoodCount3;
    int iFoodCount4;
    int iFoodCount;


    QLabel *lblFoodCount1;
    QLabel *lblFoodCount2;
    QLabel *lblFoodCount3;
    QLabel *lblFoodCount4;
    QLabel *lblFoodCount;


    //params
    QTimer timerTime; //check time on ui
    QTimer timerChangeUiForLog; //timer for show result of user on ui
    QString check_url; //url to check connectivity to net
    QTimer tNetCheck; //timer to check connectivity to net
    QString VirdiIp;
    bool tcpConnectionServer;
    bool tcpConnectionVirdi;
        //ui labels
    QTimer tcheckLCD;//timer to check foods for lcd
    QLabel *lblshowRes;
    QLabel *lbladdIp1;
    QLabel *lbladdIp2;
    QLabel *lblTime;
    QLabel *lblDate;
    QLabel *lblVirdi;
    QLabel *lblNet;
    QLabel *lblFood1;
    QLabel *lblFood2;
    QLabel *lblFood3;
    QLabel *lblFood4;
    bool net; //if net connectivity
    bool virdi; //if terminal connectivity
    int DeviceId; //restaurant Id (device id)
    int RestaurantId;
    QSqlDatabase *db_mysql;
    QString sDbConnectionNameMysql;
    QString sDbHostMysql;
    QString sDBNameMysql;
    QString sDbUserMysql;
    QString sDbPassMysql;
    int iDbPortMysql;

//    QString sDbHostSql;
//    int iDbPortSql;

    int iTimeout;
    QTimer tCheckDb;
    bool bDbopened_MySql;
    bool bInProc; //UCS functions in proc
    QTimer tCMD; //UCS function timer for proc
    int iCMDTimeout; //time out for CMD
    bool bTimeout; //if cmd time out
    UCBioAPI_HANDLE BSP_Handle; //BSP sdk handler
    bool UCS_bStarted; // if UCS start
    bool BSP_bStarted; // if BSP start
    UCSAPI_UINT32 UCS_ClientId; //program id
    UCSAPI_UINT32 UCS_MaxTerminal; //max terminal can connect
    UCSAPI_UINT32 UCS_PortNumber; // UCS PORT
    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_AutoLogCallback0;
    UCSAPI_CALLBACK_PARAM_1_PTR UCS_p_AutoLogCallback1;
    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_DeleteUserCallback0;
    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_DeleteAllUserCallback0;
    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_AddUserCallback0;
    UCSAPI_TERMINAL_STATUS_PTR UCS_p_StatusTerminal;
    quint32 qui_TerminaId_Status;

    //functions
    void StartMainThread();
    void ConfigMain();
    void ManageConnection();
    void StopApp();
    QList<QString> getcurrenyIP(); //get current ips to show on ui
    void prepareLCD(); //prepare lcd on init
    QString LoadQuery(QString sFilename); //load query from files
    bool UCS_Start(UCSAPI_UINT32 UCS_maxTerminal, UCSAPI_UINT32 UCS_portNumber);
    bool BSP_Start(UCBioAPI_HANDLE_PTR pHandle);
    bool UCS_Stop();
    bool BSP_Stop(UCBioAPI_HANDLE Handle);

    //web socket thread
    //params
    QThread *thp_WebSocket;
    WebSocket* wop_Websocket;

    //functions
    void StartWebsocketThread();

    //user action thread
    //params
    QThread *thp_User;
    UserManagement* wop_User;

    //functions
    void StartUserThread();

    //log
    //params
    QThread *thp_Log;
    LogManagement* wop_Log;



    //functions
    void StartLogThread();

    //#####################################################################################################################
    //user
    //user

    //functions
    int DeleteAllUserFromTerminals(UCSAPI_UINT32 UCS_clientId,UCSAPI_UINT32 UCS_terminalId);
    int DeleteUserFromTerminals(UCSAPI_UINT32 UCS_clientId,UCSAPI_UINT32 UCS_terminalId, UCSAPI_UINT32 UCS_userId);
    int UCS_SendUserToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId, UCSAPI_BOOL UCS_isOverwrite, UCSAPI_USER_DATA_PTR UCS_p_userData);
    void UCS_CreateUserData(UCSAPI_AUTH_DATA_PTR UCS_p_authData,UCSAPI_USER_INFO UCS_userInfo,UCSAPI_PICTURE_DATA_PTR UCS_p_pictureData);
    void UCS_CreateAuthData(UCSAPI_CARD_DATA_PTR UCS_p_cardData,UCSAPI_FACE_DATA_PTR UCS_p_faceData,UCSAPI_FINGER_DATA_PTR UCS_p_fingerData,UCSAPI_DATA_PTR UCS_p_passwordData);
    void UCS_CreateUserinfoData(UCSAPI_UINT32 UCS_userID,
                                UCSAPI_UINT8 UCS_authType,
                                UCSAPI_USER_PROPERTY UCS_userProperty,
                                UCSAPI_DATA_PTR UCS_p_uniqueID,
                                UCSAPI_DATA_PTR UCS_p_userName,
                                UCSAPI_ACCESS_AUTHORITY_PTR UCS_p_accessAuthority);
    void UCS_CreatePictureData(UCSAPI_UINT32 UCS_length,UCSAPI_UINT8 UCS_format[4],UCSAPI_UINT8* UCS_p_data);
    void UCS_CreateCardData(UCSAPI_UINT32 UCS_cardNum,UCSAPI_DATA_PTR UCS_p_cardData0,
                            UCSAPI_DATA_PTR UCS_p_cardData1,
                            UCSAPI_DATA_PTR UCS_p_cardData2,
                            UCSAPI_DATA_PTR UCS_p_cardData3,
                            UCSAPI_DATA_PTR UCS_p_cardData4);
    void UCS_CreateFaceData(long UCS_faceNum,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo0,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo1,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo2,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo3,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo4,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo5,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo6,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo7,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo8,
                            UCSAPI_FACE_INFO_PTR UCS_p_faceInfo9);
    void CreateFingerData(UCSAPI_UINT8 UCS_templateFormat,UCSAPI_UINT8 UCS_securityLevel,UCSAPI_BOOL UCS_isCheckSimilarFinger,UCBioAPI_EXPORT_DATA_PTR BSP_p_exportData);
    void UCS_CreatePasswordData(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data);
    void UCS_CreateUserProperty(UCSAPI_UINT8 UCS_finger,UCSAPI_UINT8 UCS_fPCard,UCSAPI_UINT8 UCS_password,UCSAPI_UINT8 UCS_card,UCSAPI_UINT8 UCS_cardID,UCSAPI_UINT8 UCS_operation ,UCSAPI_UINT8 UCS_identify,UCSAPI_UINT8 UCS_admin);
    void UCS_CreateUniqueID(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data);
    void UCS_CreateUserName(UCSAPI_UINT32 UCS_length,UCSAPI_VOID_PTR UCS_data);
    void UCS_CreateAccessAuth(UCSAPI_ACCESS_DATE_TYPE UCS_accessDateType,UCSAPI_ACCESS_DATE_PTR UCS_p_accessDate,UCSAPI_DATA_PTR UCS_p_accessGroup);
    bool UCS_CreateExportData(QString sTextFIR);
    void CreateAccessDate(UCSAPI_UINT16 UCS_startYear,UCSAPI_UINT8 UCS_startMonth,UCSAPI_UINT8 UCS_startDay,UCSAPI_UINT16 UCS_stopYear,UCSAPI_UINT8 UCS_stopMonth,UCSAPI_UINT8 UCS_stopDay);
    void CreateNullFaceInfo();
    void CreateNullCardInfo();
    void CreateValidCard(QString CardCSN);
    void CreateNullFormat();
    void CreateAllAndSendUser(quint32 TerminalId, quint32 UserId, QString PersonnelCode, QString TextFir, QString CardCSN, bool isAdmin, int isYear, int isMonth, int isDay, int ieYear, int ieMonth, int ieDay);

    //params
    UCSAPI_USER_DATA UCS_UserData;
    UCSAPI_AUTH_DATA UCS_AuthData;
    UCSAPI_USER_INFO UCS_UserInfo;
    UCSAPI_PICTURE_DATA UCS_PictureData;
    UCSAPI_CARD_DATA UCS_CardData;
    UCSAPI_FACE_DATA UCS_FaceData;
    UCSAPI_FINGER_DATA UCS_FingerData;
    UCSAPI_DATA UCS_PasswordData;
    UCSAPI_USER_PROPERTY UCS_UserProperty;
    UCSAPI_DATA UCS_UniqueID;
    UCSAPI_DATA UCS_UserName;
    UCSAPI_ACCESS_AUTHORITY UCS_AccessAuthority;
    QByteArray arTextFIRData;
    UCBioAPI_FIR_TEXTENCODE BSP_TextFir;
    UCBioAPI_INPUT_FIR BSP_InputFIR;
    UCBioAPI_EXPORT_DATA BSP_ExportedData;
    UCSAPI_ACCESS_DATE UCS_AccessDate;
    UCSAPI_DATA UCS_AccessGroup;
    UCSAPI_FACE_INFO UCS_FaceInfo;
    UCSAPI_DATA UCS_ValidCard;
    UCSAPI_CHAR Cardvalue[UCSAPI_DATA_SIZE_RFID];
    UCSAPI_DATA UCS_NullCard;
    QByteArray arCardCSN;
    UCSAPI_UINT8 UCS_Format[4];
    UCSAPI_CHAR UserGroupCode[4];
    UCSAPI_CHAR UserPersonelCode[20];
    UCSAPI_CHAR UserCSN[20];
    UCSAPI_CHAR UserCSNNull[20];
    UCSAPI_CHAR UserName[20];
    UCSAPI_UINT32 retUserID;
 //#####################################################################################################################

 //#####################################################################################################################
    //log
    //log

    //params
    quint32 qui_TerminalId_auto;
    quint32 qui_RFID_length_auto;
    BYTE RFID_data_auto[100];
    quint32 qui_UserID_auto;
    quint8 qui_AuthMode_auto;
    quint8 qui_AuthType_auto;
    quint16 qui_Year_auto;
    quint8 qui_Month_auto;
    quint8 qui_Day_auto;
    quint8 qui_Hour_auto;
    quint8 qui_Min_auto;
    quint8 qui_Sec_auto;
    quint32 qui_AuthRes_auto;
    bool bRes_auto;
    //log
    //log
//#####################################################################################################################


private slots:
    void slot_Main_start();
    void CallBackSlot(UCSAPI_UINT32 TerminalID,UCSAPI_UINT32 EventType,UCSAPI_UINT32 wParam,UCSAPI_UINT32 lParam);
    void slot_cmd_timeout();
    void slot_check_database(); // &tCheckDb(timeout) -- (iTimeout)
    void slot_checkLCD();
    void reset_LCD_user(); // &timerChangeUiForLog(time out) -- 3 sec
    void slot_main_onNetCheck(); //&tNetCheck(time out) -- 5 sec
    void slot_main_userLog(int foodStatus, bool user , quint32 PersonnelId, int FoodNumber, QString FoodName, QString Name, QString PersonnelCode);
    

    //void slot_update_TerminalList(quint32 UCS_p_status, quint32 UCS_terminalID);
    void slot_frommain_firstconnections(quint32 quiterminalId, quint32 quiClientId);

    //user
        //from user
    void slot_fromuser_cmd_add(quint32 TerminalId, quint32 UserID, QString PersonnelCode, QString TextFir, QString CardCSN, bool isAdmin,
                               int isYear, int isMonth, int isDay,
                               int ieYear, int ieMonth, int ieDay);
    void slot_fromuser_cmd_del(quint32 TerminalId, quint32 UserID);
    void slot_fromuser_cmd_delall(quint32 TerminalId);

        //callback
    void slot_frommain_AddUserCallBackRes(quint32 UserId, quint32 UCS_p_callback0, quint32 UCS_terminalID);
    void slot_frommain_DelUserCallBackRes(quint32 UserId, quint32 UCS_p_callback0, quint32 UCS_terminalID);
    void slot_frommain_DelAllUsersCallBackRes(quint32 UCS_p_callback0,quint32 UCS_terminalID);
    //user

    void setTime();
    void slot_main_TerminalStaus(bool status);
    void slot_check_dbConnection(bool status);


    void slot_main_GetFoodCount(int foodType);
signals:
    void CallBackSignal(UCSAPI_UINT32 TerminalID,UCSAPI_UINT32 EventType,UCSAPI_UINT32 wParam, UCSAPI_UINT32 lParam);
    void CallBackResp(int iTerminalID,int err);

    void NewConnectionSignal();
    void sig_main_getTerminalStatus(quint32 UCS_terminalID);
    void sig_main_realTimeAccessLog(quint32 qui_TerminalId,quint32 qui_RFID_length,BYTE* RFID_data,quint32 qui_UserID,quint8 qui_AuthMode,quint8 qui_AuthType,quint16 qui_Year,quint8 qui_Month,quint8 qui_Day,quint8 qui_Hour,quint8 qui_Min,quint8 qui_Sec,quint32 qui_AuthRes,bool bRes);
    void sig_main_start();
    void sig_main_firstConnect(quint32 quiterminalId, quint32 quiClientId);
    void sig_main_disConnect(quint32 UCS_terminalID);

    //user (for callback)
    void sig_main_deleteAllUser(quint32 UCS_p_callback0,quint32 UCS_terminalID);
    void sig_main_addUser(quint32 UserId,quint32 UCS_p_callback0,quint32 UCS_terminalID);
    void sig_main_deleteUser(quint32 UserId,quint32 UCS_p_callback0,quint32 UCS_terminalID);

    void sig_main_resp_deleteall(bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_delete(quint32 UserId,bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_add(quint32 UserId,bool ok,int error,quint32 UCS_terminalID);
    void sig_main_inproc(bool proc);

    void sig_main_netStatus(bool status);
    void sig_main_virdiStatus(bool status);

    void sig_main_netCable(bool status);


};

#endif // MAINWIDGET_H
