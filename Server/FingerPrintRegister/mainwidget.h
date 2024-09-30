#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDebug>
//#include <QWebSocket>
//#include <QWebSocketServer>
#include <QSettings>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QThread>

#include <winsock.h> //critical for SDK
//#include <unistd.h>

//UCBio SDK
#include "UCBioAPI.h"
#include "UCBioAPI_Error.h"
#include "UCBioAPI_Export.h"
#include "UCBioAPI_ExportType.h"
#include "UCBioAPI_FastSearch.h"
#include "UCBioAPI_FastSearchType.h"
#include "UCBioAPI_SmartCard.h"
#include "UCBioAPI_SmartCardType.h"
#include "UCBioAPI_Type.h"
#include "UCBioAPI_Basic.h"

#include "socketworker.h"


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    QString sVersion;
    QIcon icon;
    QSystemTrayIcon SysTray;
    QString sSDKVer;
    QString sVer;





private:
    Ui::MainWidget *ui;

    QThread *soketthread;
    socketWorker *socketworker;

    UCBioAPI_INIT_INFO_0 initInfo0;

    void InitParams();

    //UCBio Realated Funcs
    bool BioInit();
    bool BioTerminate();
    bool OpenDevice();
    bool CloseDevice();
    bool EnrollFP();
    //bool FIR_to_Template();
    bool GetFringerPrint();
    bool GetTextFIDFromHandle();
    bool GetCSN();
    bool SendCSN();

    //UCBio Realated Parameters
    UCBioAPI_HANDLE hUCBioAPI;
    bool bInitBio;
    bool bOpenDev;
    UCBioAPI_FIR_HANDLE hEnrolledFIR;
    UCBioAPI_INPUT_FIR inputFIR;
    UCBioAPI_EXPORT_DATA ExData;
    UCBioAPI_FINGER_BLOCK_PTR blockptr;
    UCBioAPI_FIR_TEXTENCODE TextFir;

    BYTE pBuf[32];
    WORD nLen;
    QString sCSN;
    //UCBioAPI_UINT16 wLed;


    //socket params
    quint16 WSport;
    bool bCuurentSocket;
    bool bSC;
    //QList<QWebSocket *> lst_WS_clients;
    //QWebSocket* clCurrentSocket;
    //QWebSocket* stmpSocket;
    //QWebSocketServer *p_qwsClientServer;
    QString strSocketClientName;
    bool bCanselEnrollment;
    bool bEnrolling;

    void ShowSDKInfo();
    void GoToSysTray();

signals:
    void send_resp_tothread(QString text,bool end);

private slots:
    //void onNewWebSocketConnection();
    //void onSocketDisconnected();
    void processTextMessage(QString text);
};

#endif // MAINWIDGET_H
