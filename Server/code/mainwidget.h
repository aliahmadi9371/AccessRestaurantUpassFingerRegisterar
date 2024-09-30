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

#include <winsock.h> //critical
//UCS SDK
#include "UCSAPI.h"
#include "UCSAPI_Basic.h"
#include "UCSAPI_Error.h"
#include "UCSAPI_Type.h"

//UCBio SDK
#include "UCBioAPI.h"
#include "UCBioAPI_Basic.h"
#include "UCBioAPI_Error.h"
#include "UCBioAPI_Export.h"
#include "UCBioAPI_ExportType.h"
#include "UCBioAPI_FastSearch.h"
#include "UCBioAPI_FastSearchType.h"
#include "UCBioAPI_SmartCard.h"
#include "UCBioAPI_SmartCardType.h"
#include "UCBioAPI_Type.h"


#include "websocket.h"
#include "usermanagement.h"
#include "terminalmanagement.h"
#include "logmanagement.h"

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

    QTimer StartTimer;

private:
    Ui::MainWidget *ui;
    bool bQuit;
    bool bInProc;
    int iCMDTimeout;
    QTimer tCMD;
    bool bTimeout;


    QThread *thp_WebSocket;
    WebSocket* wop_Websocket;

    QThread *thp_User;
    UserManagement* wop_User;

    QThread *thp_Terminal;
    TerminalManagement* wop_Terminal;
    
    
    QThread *thp_Log;
    LogManagement* wop_Log;



    QList<quint32> FirstTerminalList;

    UCSAPI_UINT32 retUserID;


    //quint32 main_TerminalId;


    void ConfigMain();
    void StartMainThread();
    void StartWebsocketThread();
    void StartUserThread();
    void StartTerminalThread();
    void StartLogThread();
    void ManageConnection();
    void StopApp();

    QSystemTrayIcon SysTray;
    QIcon icon;
    

    bool UCS_Start(UCSAPI_UINT32 UCS_maxTerminal, UCSAPI_UINT32 UCS_portNumber);
    bool BSP_Start(UCBioAPI_HANDLE_PTR pHandle);
    bool UCS_Stop();
    bool BSP_Stop(UCBioAPI_HANDLE Handle);
    UCBioAPI_HANDLE BSP_Handle;
    bool UCS_bStarted;
    bool BSP_bStarted;
    UCSAPI_UINT32 UCS_ClientId;
    UCSAPI_UINT32 UCS_MaxTerminal;
    UCSAPI_UINT32 UCS_PortNumber;

    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_AutoLogCallback0;
    UCSAPI_CALLBACK_PARAM_1_PTR UCS_p_AutoLogCallback1;

    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_LogCallback0;
    UCSAPI_CALLBACK_PARAM_1_PTR UCS_p_LogCallback1;

    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_DeleteUserCallback0;

    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_DeleteAllUserCallback0;

    UCSAPI_CALLBACK_PARAM_0_PTR UCS_p_AddUserCallback0;

    UCSAPI_TERMINAL_STATUS_PTR UCS_p_StatusTerminal;

    UCSAPI_CALLBACK_PARAM_0_PTR  UCS_p_TimezoneCallback0;
    UCSAPI_CALLBACK_PARAM_0_PTR  UCS_p_HolidayCallback0;
    UCSAPI_CALLBACK_PARAM_0_PTR  UCS_p_AccessCallback0;
    UCSAPI_CALLBACK_PARAM_0_PTR  UCS_p_GroupCallback0;



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
    UCSAPI_CHAR UserPersonellCode[20];
    UCSAPI_CHAR CardData[20];

    void CreateNullFaceInfo();
    void CreateNullCardInfo();
    void CreateValidCard(QString CardCSN);
    void CreateNullFormat();
    //user
    //user
    //#####################################################################################################################


    //#####################################################################################################################
    //TimeZones
    //TimeZones

    int callbackFlag;
    //functions
    int SendACDTimeZonesToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId);
    void CreateTimeZones(UCSAPI_UINT32 UCS_timezoneNum, UCSAPI_ACCESS_TIMEZONE UCS_timezones[]);
    void AddTimeZoneToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_TIMEZONE UCS_zone0, int index,
                                        UCSAPI_CHAR UCS_code1, UCSAPI_TIMEZONE UCS_zone1,
                                        UCSAPI_CHAR UCS_code2, UCSAPI_TIMEZONE UCS_zone2,
                                        UCSAPI_CHAR UCS_code3, UCSAPI_TIMEZONE UCS_zone3,
                                                               UCSAPI_TIMEZONE UCS_zone4,
                                                               UCSAPI_TIMEZONE UCS_zone5,
                                                               UCSAPI_TIMEZONE UCS_zone6,
                                                               UCSAPI_TIMEZONE UCS_zone7,
                                                               UCSAPI_TIMEZONE UCS_zone8,
                                                               UCSAPI_TIMEZONE UCS_zone9,
                                                               UCSAPI_TIMEZONE UCS_zone10,
                                                               UCSAPI_TIMEZONE UCS_zone11);
    void CreateZone(int indexZone,UCSAPI_UINT8 UCS_startHour,UCSAPI_UINT8 UCS_startMinute,UCSAPI_UINT8 UCS_stopHour,UCSAPI_UINT8 UCS_stopMinute);

    //params
    UCSAPI_ACCESS_CONTROL_DATA UCS_AccessControlDataTimezones;
        //UCSAPI_ACCESS_CONTROL_DATA
        UCSAPI_ACCESS_TIMEZONE_DATA UCS_AccessTimezonesData;
            //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_TIMEZONE_DATA
            UCSAPI_ACCESS_TIMEZONE UCS_Timezones[UCSAPI_ACCESS_TIMEZONE_MAX];
                //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_TIMEZONE_DATA.UCSAPI_TIMEZONE
                UCSAPI_TIMEZONE UCS_Zone[12];
            int iTimeZonesIndex;

            void clearTimezones();
            void createTimezones(int TimezoneCodeCount,QList<int>* codes, QList<int>* startHour, QList<int>* startMin, QList<int>* stopHour, QList<int>* stopMin);
    //TimeZones
    //TimeZones


    //Holidays
    //Holidays

    //functions
    int SendACDHolidaysToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId);
    void CreateHoliday(UCSAPI_UINT32 UCS_holidayNum, UCSAPI_ACCESS_HOLIDAY UCS_holidays[]);
    void AddHolidayToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_DATE_MM_DD UCS_date0, int index,
                            UCSAPI_CHAR UCS_code1, UCSAPI_DATE_MM_DD UCS_date1,  UCSAPI_DATE_MM_DD UCS_date11, UCSAPI_DATE_MM_DD UCS_date21, UCSAPI_DATE_MM_DD UCS_date31,
                            UCSAPI_CHAR UCS_code2, UCSAPI_DATE_MM_DD UCS_date2,  UCSAPI_DATE_MM_DD UCS_date12, UCSAPI_DATE_MM_DD UCS_date22,
                            UCSAPI_CHAR UCS_code3, UCSAPI_DATE_MM_DD UCS_date3,  UCSAPI_DATE_MM_DD UCS_date13, UCSAPI_DATE_MM_DD UCS_date23,
                                                   UCSAPI_DATE_MM_DD UCS_date4,  UCSAPI_DATE_MM_DD UCS_date14, UCSAPI_DATE_MM_DD UCS_date24,
                                                   UCSAPI_DATE_MM_DD UCS_date5,  UCSAPI_DATE_MM_DD UCS_date15, UCSAPI_DATE_MM_DD UCS_date25,
                                                   UCSAPI_DATE_MM_DD UCS_date6,  UCSAPI_DATE_MM_DD UCS_date16, UCSAPI_DATE_MM_DD UCS_date26,
                                                   UCSAPI_DATE_MM_DD UCS_date7,  UCSAPI_DATE_MM_DD UCS_date17, UCSAPI_DATE_MM_DD UCS_date27,
                                                   UCSAPI_DATE_MM_DD UCS_date8,  UCSAPI_DATE_MM_DD UCS_date18, UCSAPI_DATE_MM_DD UCS_date28,
                                                   UCSAPI_DATE_MM_DD UCS_date9,  UCSAPI_DATE_MM_DD UCS_date19, UCSAPI_DATE_MM_DD UCS_date29,
                                                   UCSAPI_DATE_MM_DD UCS_date10, UCSAPI_DATE_MM_DD UCS_date20, UCSAPI_DATE_MM_DD UCS_date30);
    void CreateHolidayDate(int index,UCSAPI_UINT16 UCS_month,UCSAPI_UINT16 UCS_day);

    //params
    UCSAPI_ACCESS_CONTROL_DATA UCS_AccessControlDataHolidays;
        //UCSAPI_ACCESS_CONTROL_DATA
        UCSAPI_ACCESS_HOLIDAY_DATA UCS_HolidaysData;
            //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_HOLIDAY_DATA
            UCSAPI_ACCESS_HOLIDAY UCS_Holidays[UCSAPI_ACCESS_HOLIDAY_MAX];
                //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_HOLIDAY_DATA.UCSAPI_ACCESS_HOLIDAY
                UCSAPI_ACCESS_HOLIDAY UCS_HolidaysDates[32];
                    //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_HOLIDAY_DATA.UCSAPI_ACCESS_HOLIDAY.UCSAPI_DATE_MM_DD
                    UCSAPI_DATE_MM_DD UCS_Date[32];
            int iHolidayIndex;

            void clearHolidays();
            void createHolidays(int HolidayCodeCount,QList<int>* codes,QList<int>* datesM,QList<int>* datesD);

    //Holidays
    //Holidays


    //access
    //access

    //functions
    int SendACDAccessToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId);
    void CreateAccess(UCSAPI_UINT32 UCS_accessTimeNum, UCSAPI_ACCESS_TIME UCS_accesses[]);
    void AddAccessToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_CHAR UCS_hcode0,int index, UCSAPI_ACCESS_TIMEZONE_CODE UCS_timeWeek,
                           UCSAPI_CHAR UCS_code1, UCSAPI_CHAR UCS_hcode1,
                           UCSAPI_CHAR UCS_code2, UCSAPI_CHAR UCS_hcode2,
                           UCSAPI_CHAR UCS_code3, UCSAPI_CHAR UCS_hcode3);
    void CreateAccess(UCSAPI_CHAR UCS_monCode0, UCSAPI_CHAR UCS_tueCode0, UCSAPI_CHAR UCS_wedCode0, UCSAPI_CHAR UCS_theCode0, UCSAPI_CHAR UCS_friCode0, UCSAPI_CHAR UCS_satCode0, UCSAPI_CHAR UCS_sunCode0, UCSAPI_CHAR UCS_holCode0,
                      UCSAPI_CHAR UCS_monCode1, UCSAPI_CHAR UCS_tueCode1, UCSAPI_CHAR UCS_wedCode1, UCSAPI_CHAR UCS_theCode1, UCSAPI_CHAR UCS_friCode1, UCSAPI_CHAR UCS_satCode1, UCSAPI_CHAR UCS_sunCode1, UCSAPI_CHAR UCS_holCode1,
                      UCSAPI_CHAR UCS_monCode2, UCSAPI_CHAR UCS_tueCode2, UCSAPI_CHAR UCS_wedCode2, UCSAPI_CHAR UCS_theCode2, UCSAPI_CHAR UCS_friCode2, UCSAPI_CHAR UCS_satCode2, UCSAPI_CHAR UCS_sunCode2, UCSAPI_CHAR UCS_holCode2,
                      UCSAPI_CHAR UCS_monCode3, UCSAPI_CHAR UCS_tueCode3, UCSAPI_CHAR UCS_wedCode3, UCSAPI_CHAR UCS_theCode3, UCSAPI_CHAR UCS_friCode3, UCSAPI_CHAR UCS_satCode3, UCSAPI_CHAR UCS_sunCode3, UCSAPI_CHAR UCS_holCode3);

    //params
    UCSAPI_ACCESS_CONTROL_DATA UCS_AccessControlDataAccess;
        //UCSAPI_ACCESS_CONTROL_DATA
        UCSAPI_ACCESS_TIME_DATA UCS_AccessTimeData;
            //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_TIME_DATA
            UCSAPI_ACCESS_TIME UCS_Accesses[UCSAPI_ACCESS_TIME_MAX];
                //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_TIME_DATA.UCSAPI_ACCESS_TIMEZONE_CODE
                UCSAPI_ACCESS_TIMEZONE_CODE UCS_AccessWeek;
            int iAccessIndex;

            void clearAcesses();
            void createAccesses(int AccessCodesCount,QList<int>* codes,int * holCoes,QList<int>* dayNum,QList<int>* dayCode);

    //access
    //access

    //group
    //group

    //functions
    int SendACDGroupToTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId);

    void CreateGroup(UCSAPI_UINT32 UCS_accessGroupNum, UCSAPI_ACCESS_GROUP UCS_groups[]);
    void AddGroupToStruct(UCSAPI_CHAR UCS_code0, UCSAPI_CHAR UCS_a1code0, UCSAPI_CHAR UCS_a2code0, UCSAPI_CHAR UCS_a3code0, UCSAPI_CHAR UCS_a4code0, int index,
                           UCSAPI_CHAR UCS_code1, UCSAPI_CHAR UCS_a1code1, UCSAPI_CHAR UCS_a2code1, UCSAPI_CHAR UCS_a3code1, UCSAPI_CHAR UCS_a4code1,
                           UCSAPI_CHAR UCS_code2, UCSAPI_CHAR UCS_a1code2, UCSAPI_CHAR UCS_a2code2, UCSAPI_CHAR UCS_a3code2, UCSAPI_CHAR UCS_a4code2,
                           UCSAPI_CHAR UCS_code3, UCSAPI_CHAR UCS_a1code3, UCSAPI_CHAR UCS_a2code3, UCSAPI_CHAR UCS_a3code3, UCSAPI_CHAR UCS_a4code3);
    void CreateGroup(UCSAPI_CHAR UCS_monCode0, UCSAPI_CHAR UCS_tueCode0, UCSAPI_CHAR UCS_wedCode0, UCSAPI_CHAR UCS_theCode0, UCSAPI_CHAR UCS_friCode0, UCSAPI_CHAR UCS_satCode0, UCSAPI_CHAR UCS_sunCode0, UCSAPI_CHAR UCS_holCode0,
                      UCSAPI_CHAR UCS_monCode1, UCSAPI_CHAR UCS_tueCode1, UCSAPI_CHAR UCS_wedCode1, UCSAPI_CHAR UCS_theCode1, UCSAPI_CHAR UCS_friCode1, UCSAPI_CHAR UCS_satCode1, UCSAPI_CHAR UCS_sunCode1, UCSAPI_CHAR UCS_holCode1,
                      UCSAPI_CHAR UCS_monCode2, UCSAPI_CHAR UCS_tueCode2, UCSAPI_CHAR UCS_wedCode2, UCSAPI_CHAR UCS_theCode2, UCSAPI_CHAR UCS_friCode2, UCSAPI_CHAR UCS_satCode2, UCSAPI_CHAR UCS_sunCode2, UCSAPI_CHAR UCS_holCode2,
                      UCSAPI_CHAR UCS_monCode3, UCSAPI_CHAR UCS_tueCode3, UCSAPI_CHAR UCS_wedCode3, UCSAPI_CHAR UCS_theCode3, UCSAPI_CHAR UCS_friCode3, UCSAPI_CHAR UCS_satCode3, UCSAPI_CHAR UCS_sunCode3, UCSAPI_CHAR UCS_holCode3);

    //params
    UCSAPI_ACCESS_CONTROL_DATA UCS_AccessControlDataGroup;
        //UCSAPI_ACCESS_CONTROL_DATA
        UCSAPI_ACCESS_GROUP_DATA UCS_AccessGroupData;
            //UCSAPI_ACCESS_CONTROL_DATA.UCSAPI_ACCESS_GROUP_DATA
            UCSAPI_ACCESS_GROUP UCS_Groups[UCSAPI_ACCESS_GROUP_MAX];
            int iGroupIndex;
            void clearGroups();
            void createGroups(int AccessCodesCount,QList<int>* codes,QList<int>* accCoes);

    //group
    //group
    //#####################################################################################################################

    //#####################################################################################################################
    //log
    //log

    //functions
    bool GetAccessLogFromTerminal(UCSAPI_UINT32 UCS_clientId, UCSAPI_UINT32 UCS_terminalId, UCSAPI_GET_LOG_TYPE UCS_logType);

    //params
    quint32 qui_TerminalId;
    quint32 qui_RFID_length;
    BYTE RFID_data[100];

    quint32 qui_UserID;

    quint8 qui_AuthMode;
    quint8 qui_AuthType;

    quint16 qui_Year;
    quint8 qui_Month;
    quint8 qui_Day;
    quint8 qui_Hour;
    quint8 qui_Min;
    quint8 qui_Sec;

    quint32 qui_AuthRes;
    bool bRes;


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

    quint32 qui_TerminaId_Status;
    quint32 qui_Door_Status;
    quint32 qui_Lock_Status;
    quint32 qui_Open_Status;
    quint32 qui_Cover_Status;
    quint32 qui_Terminal_Status;

    //log
    //log
    //#####################################################################################################################

    quint32 minimum_Terminals;
    bool bstart;


    void CreateAllAndSendUser(quint32 TerminalId, quint32 UserId, QString PersonnelCode, QString TextFir, QString CardCSN, int isYear, int isMonth, int isDay, int ieYear, int ieMonth, int ieDay, QString groupCode, bool isAdmin, int add_inactive);
    int addinactive;

    bool start;

private slots:
    void slot_Main_start();
    void CallBackSlot(UCSAPI_UINT32 TerminalID,UCSAPI_UINT32 EventType,UCSAPI_UINT32 wParam,UCSAPI_UINT32 lParam);
    void slot_cmd_timeout();
    void slot_start();
    

    //void slot_update_TerminalList(quint32 UCS_p_status, quint32 UCS_terminalID);
    void slot_frommain_firstconnections(quint32 quiterminalId, quint32 quiClientId);

    //user
        //from user
    void slot_fromuser_cmd_add(quint32 TerminalId, quint32 UserID, QString PersonnelCode, QString TextFir, QString CardCSN, int isYear, int isMonth, int isDay, int ieYear, int ieMonth, int ieDay, QString groupCode, bool isAdmin, int add_inactive);
    void slot_fromuser_cmd_del(quint32 TerminalId, quint32 UserID);
    void slot_fromuser_cmd_delall(quint32 TerminalId);
//    void slot_fromuser_cmd_inactive(quint32 TerminalId, quint32 UserID, QString PersonnelCode, QString TextFir, QString CardCSN, int isYear, int isMonth, int isDay, int ieYear, int ieMonth, int ieDay, QString groupCode,bool isAdmin);

        //callback
    void slot_frommain_AddUserCallBackRes(quint32 UserId, quint32 UCS_p_callback0, quint32 UCS_terminalID);
    void slot_frommain_DelUserCallBackRes(quint32 UserId, quint32 UCS_p_callback0, quint32 UCS_terminalID);
    void slot_frommain_DelAllUsersCallBackRes(quint32 UCS_p_callback0,quint32 UCS_terminalID);
    //user


    //terminal
        //from terminal
        void slot_fromterminal_timezone(quint32 TerminalId, int TimezoneCodeCount, QList<int> *codes, QList<int>* startHour, QList<int>* startMin, QList<int>* stopHour, QList<int>* stopMin);
        void slot_fromterminal_hol(quint32 TerminalId, int HolidayCodeCount, QList<int> *codes, QList<int> *datesM, QList<int> *datesD);
        void slot_fromterminal_access(quint32 TerminalId,int AccessCodesCount,QList<int>* codes,int * holCoes,QList<int>* dayNum,QList<int>* dayCode);
        void slot_fromterminal_group(quint32 TerminalId,int GroupCodesCount,QList<int>* codes,QList<int>* accCoes);

        //from main to main
        void slot_frommain_TimezoneCallbackResp(quint32 error,quint32 UCS_terminalID);
        void slot_frommain_HolidayCallbackResp(quint32 error,quint32 UCS_terminalID);
        void slot_frommain_AccessCallbackResp(quint32 error,quint32 UCS_terminalID);
        void slot_frommain_GroupCallbackResp(quint32 error,quint32 UCS_terminalID);



    void slot_frommain_getStatus(quint32 TerminalId);

signals:
    void CallBackSignal(UCSAPI_UINT32 TerminalID,UCSAPI_UINT32 EventType,UCSAPI_UINT32 wParam, UCSAPI_UINT32 lParam);
    void CallBackResp(int iTerminalID,int err);

    void NewConnectionSignal();
    void sig_main_getTerminalStatus(quint32 UCS_terminalID,quint32 Door,quint32 Lock,quint32 Open,quint32 Cover,quint32 Terminal);
    void sig_main_realTimeAccessLog(quint32 qui_TerminalId,quint32 qui_RFID_length,BYTE* RFID_data,quint32 qui_UserID,quint8 qui_AuthMode,quint8 qui_AuthType,quint16 qui_Year,quint8 qui_Month,quint8 qui_Day,quint8 qui_Hour,quint8 qui_Min,quint8 qui_Sec,quint32 qui_AuthRes,bool bRes);
    void sig_main_getAccessLog(quint32 qui_TerminalId,quint32 qui_RFID_length,BYTE* RFID_data,quint32 qui_UserID,quint8 qui_AuthMode,quint8 qui_AuthType,quint16 qui_Year,quint8 qui_Month,quint8 qui_Day,quint8 qui_Hour,quint8 qui_Min,quint8 qui_Sec,quint32 qui_AuthRes,bool bRes);
    void sig_main_start();
    void sig_main_firstConnect(quint32 quiterminalId, quint32 quiClientId);
    void sig_main_disConnect(quint32 UCS_terminalID);
    void sig_main_GetLog(quint32 TerminalId);


    //user (for callback)
    void sig_main_deleteAllUser(quint32 UCS_p_callback0,quint32 UCS_terminalID);
    void sig_main_addUser(quint32 UserId,quint32 UCS_p_callback0,quint32 UCS_terminalID);
    void sig_main_deleteUser(quint32 UserId,quint32 UCS_p_callback0,quint32 UCS_terminalID);

    void sig_main_resp_deleteall(bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_delete(quint32 UserId,bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_add(quint32 UserId,bool ok,int error,quint32 UCS_terminalID, int addinactive);

    //terminal
    void sig_main_TimeZoneCallBackResp(quint32 error,quint32 UCS_terminalID);
    void sig_main_HolidayCallBackResp(quint32 error,quint32 UCS_terminalID);
    void sig_main_AccessCallBackResp(quint32 error,quint32 UCS_terminalID);
    void sig_main_GroupCallBackResp(quint32 error,quint32 UCS_terminalID);

    void sig_main_resp_timezoneResp(bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_holResp(bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_accessResp(bool ok,int error,quint32 UCS_terminalID);
    void sig_main_resp_groupResp(bool ok,int error,quint32 UCS_terminalID);


    void sig_main_inproc(bool proc);
};

#endif // MAINWIDGET_H
