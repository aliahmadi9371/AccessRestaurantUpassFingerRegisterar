#ifndef TERMINALMANAGEMENT_H
#define TERMINALMANAGEMENT_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QFile>
#include <QDir>

//#include <winsock.h> //critical
// //UCS SDK
//#include "UCSAPI.h"
//#include "UCSAPI_Basic.h"
//#include "UCSAPI_Error.h"
//#include "UCSAPI_Type.h"

// //UCBio SDK
//#include "UCBioAPI.h"
//#include "UCBioAPI_Basic.h"
//#include "UCBioAPI_DeviceEx.h"
//#include "UCBioAPI_Error.h"
//#include "UCBioAPI_Export.h"
//#include "UCBioAPI_ExportType.h"
//#include "UCBioAPI_Extension.h"
//#include "UCBioAPI_FastSearch.h"
//#include "UCBioAPI_FastSearchType.h"
//#include "UCBioAPI_SmartCard.h"
//#include "UCBioAPI_SmartCardType.h"
//#include "UCBioAPI_Type.h"

class TerminalManagement : public QObject
{
    Q_OBJECT
public:
    explicit TerminalManagement(QObject *parent = nullptr);
    bool bDbopened;

private:
    void ConfigThread();

    QSqlDatabase *db;
    QString sDbConnectionName;
    QString sDbHost;
    QString sDBName;
    QString sDbUser;
    QString sDbPass;
    int iDbPort;
    int iTimeout;

    QTimer *tCheckDb;

    QString sCMD_AddTimezone;
    int iCMD_timezoneCount;
    QString sCMD_AddHol;
    int iCMD_holidayCount;
    QString sCMD_AddAccess;
    int iCMD_accessCount;
    QString sCMD_AddGroup;
    int iCMD_groupCount;



    QList<int> TimezoneCodes;
    QList<int> StartHour[128];
    QList<int> StartMin[128];
    QList<int> StopHour[128];
    QList<int> StopMin[128];

    QList<int> HolidayCodes;
    QList<int> Month[64];
    QList<int> Day[64];

    QList<int> AccessCodes;
    QList<int> AccessDayCodes[128];
    QList<int> AccessDayList[128];
    int AccessHolidayCode[128];


    QList<int> groupCode;
    QList<int> HaccessCodes[128];

    void clearTimezoneLists();
    void clearHolidayLists();
    void clearAccessLists();
    void clearGroupLists();




    QString LoadQuery(QString sFilename);

signals:
    void sig_Start_Thread();
    void sig_Stop_Thread();
    void sig_DB_Open(bool open);

    void sig_tomain_timezone(quint32 TerminalId,int TimezoneCodeCount,QList<int>* codes,QList<int>* startHours,QList<int>* startMin,QList<int>* stopHour,QList<int>* stopMin);
    void sig_tomain_hol(quint32 TerminalId,int HolidayCodeCount,QList<int>* codes,QList<int>* datesM,QList<int>* datesD);
    void sig_tomain_access(quint32 TerminalId,int AccessCodesCount,QList<int>* codes,int * holCoes,QList<int>* dayNum,QList<int>* dayCode);
    void sig_tomain_group(quint32 TerminalId,int GroupCodesCount,QList<int>* codes,QList<int>* accCoes);

    void sig_terminal_finishedCMD();
    void invaid_cmd();

    void sig_terminal_TimeZoneResDb(bool ok,int error,quint32 UCS_terminalID);
    void sig_terminal_HolidayResDb(bool ok,int error,quint32 UCS_terminalID);
    void sig_terminal_AccessResDb(bool ok,int error,quint32 UCS_terminalID);
    void sig_terminal_GroupResDb(bool ok,int error,quint32 UCS_terminalID);

    void sig_terminal_saveCMD(int type,bool ok,int error,quint32 UCS_terminalID);


public slots:

private slots:
    void slot_Start_Terminal_Thread();
    void slot_Stop_Terminal_Thread();

     void slot_check_database();



    void slot_fromsocket_timezone(QString message);
    void slot_fromsocket_holiday(QString message);
    void slot_fromsocket_accesstime(QString message);
    void slot_fromsocket_accessgroup(QString message);

    void slot_frommain_timezoneResp(bool ok,int error,quint32 UCS_terminalID);
    void slot_frommain_holidayResp(bool ok,int error,quint32 UCS_terminalID);
    void slot_frommain_accesstimeResp(bool ok,int error,quint32 UCS_terminalID);
    void slot_frommain_accessgroupResp(bool ok,int error,quint32 UCS_terminalID);

    void slot_fromterminal_TimeZoneResDb(bool ok,int error,quint32 UCS_terminalID);
    void slot_fromterminal_HolidayResDb(bool ok,int error,quint32 UCS_terminalID);
    void slot_fromterminal_AccessResDb(bool ok,int error,quint32 UCS_terminalID);
    void slot_fromterminal_GroupResDb(bool ok,int error,quint32 UCS_terminalID);

    void slot_fromterminal_savecmd(int type,bool ok,int error,quint32 UCS_terminalID);
};

#endif // TERMINALMANAGEMENT_H
