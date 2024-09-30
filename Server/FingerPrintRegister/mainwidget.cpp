#include "mainwidget.h"
#include "ui_mainwidget.h"


//ucbio enroll finger (send text fir to web socket)
//ucbio card serial number (send text csn as hex(2 digits)
//re init bio
//cansel enroll

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    qDebug() << "###################################################################################################";
    qDebug() << "App Start";



    sVersion = "V1.3";

    InitParams();
    bInitBio = BioInit();
    if(!bInitBio){
        qDebug() << "can not init bio";
        QApplication::quit();
    }
    ShowSDKInfo();
    GoToSysTray();
}

void MainWidget::InitParams()
{
    qDebug() << "**************************************************";
    qDebug() << "Init Params";

    bInitBio = false;
    bOpenDev = false;

    bCuurentSocket = false;
    bEnrolling = false;
    bCanselEnrollment = false;
    bSC = false;

    QSettings setting("config.dll",QSettings::IniFormat);
    WSport = quint16(setting.value("websocket/port",8080).toInt());
    qDebug() << "web soket port: " << WSport;

    strSocketClientName = setting.value("websocket/name","Test").toString();
    qDebug() << "socket name: " << strSocketClientName;

    bSC = setting.value("config/SC",false).toBool();
    qDebug() << "SC Card: " << bSC;

    soketthread = new QThread;
    socketworker = new socketWorker;
    socketworker->moveToThread(soketthread);
    soketthread->start();
    connect(socketworker, SIGNAL(start_worker(QString,quint16,int)), socketworker, SLOT(on_start_worker(QString,quint16,int)),Qt::QueuedConnection);
    emit socketworker->start_worker(strSocketClientName,WSport,1);
    connect(socketworker, SIGNAL(send_text(QString)), this, SLOT(processTextMessage(QString)),Qt::QueuedConnection);
    connect(this, SIGNAL(send_resp_tothread(QString,bool)), socketworker, SLOT(receive_resp(QString,bool)),Qt::QueuedConnection);

    memset(&initInfo0, 0, sizeof(UCBioAPI_INIT_INFO_0));
    qDebug() << "**************************************************";
}

bool MainWidget::BioInit()
{
        //qDebug() << "**************************************************";
        qDebug() << "Init BSP SDK";
        UCBioAPI_RETURN err = UCBioAPI_Init(&hUCBioAPI);
        if (err == UCBioAPIERROR_NONE){
            qDebug() << "Can Bio SDK Init: UCBioAPIERROR_NONE";

            //qDebug() << "**************************************************";
            return true;
        }
        else if(err == UCBioAPIERROR_INVALID_POINTER){
            qDebug() << "Can Not Bio SDK Init: UCBioAPIERROR_NONE";
            //qDebug() << "**************************************************";
            return false;
        }
        else if(err == UCBioAPIERROR_VALIDITY_FAIL){
            qDebug() << "Can Not Bio SDK Init: UCBioAPIERROR_VALIDITY_FAIL";
            //qDebug() << "**************************************************";
            return false;
        }
        else if(err == UCBioAPIERROR_EXPIRED_VERSION){
            qDebug() << "Can Not Bio SDK Init: UCBioAPIERROR_EXPIRED_VERSION";
            //qDebug() << "**************************************************";
            return false;
        }
        else{
            qDebug() << "Can Not Bio SDK Init: UCBioAPIERROR_UNKNOWN";
            //qDebug() << "**************************************************";
            return false;
        }
}

void MainWidget::ShowSDKInfo()
{
    qDebug() << "**************************************************";
    qDebug() << "Show SDK Info";
    UCBioAPI_GetInitInfo(hUCBioAPI, 0, &initInfo0);

    qDebug() << "initInfo0.DefaultTimeout: " << initInfo0.DefaultTimeout;
    qDebug() << "initInfo0.StructureType: " << initInfo0.StructureType;
    qDebug() << "initInfo0.MaxFingersForEnroll: " << initInfo0.MaxFingersForEnroll;
    qDebug() << "initInfo0.NecessaryEnrollNum: " << initInfo0.NecessaryEnrollNum;
    qDebug() << "initInfo0.SamplesPerFinger: "<< initInfo0.SamplesPerFinger;
    qDebug() << "initInfo0.SecurityLevelForEnroll: " << initInfo0.SecurityLevelForEnroll;
    qDebug() << "initInfo0.SecurityLevelForVerify: " << initInfo0.SecurityLevelForVerify;
    qDebug() << "initInfo0.SecurityLevelForIdentify: " << initInfo0.SecurityLevelForIdentify;


//    initInfo0.DefaultTimeout = 10000;
//    initInfo0.StructureType = 0;
//    initInfo0.MaxFingersForEnroll = 2;
//    initInfo0.NecessaryEnrollNum = 1;
//    initInfo0.SamplesPerFinger = 2;
//    initInfo0.SecurityLevelForEnroll = 4;
//    initInfo0.SecurityLevelForVerify = 4;
//    initInfo0.SecurityLevelForIdentify = 4;

//    UCBioAPI_SetInitInfo(hUCBioAPI, 0, &initInfo0);


//    UCBioAPI_GetInitInfo(hUCBioAPI, 0, &initInfo0);

//    qDebug() << initInfo0.DefaultTimeout;
//    qDebug() << initInfo0.StructureType;
//    qDebug() << initInfo0.MaxFingersForEnroll;
//    qDebug() << initInfo0.NecessaryEnrollNum;
//    qDebug() << initInfo0.SamplesPerFinger;
//    qDebug() << initInfo0.SecurityLevelForEnroll;
//    qDebug() << initInfo0.SecurityLevelForVerify;
//    qDebug() << initInfo0.SecurityLevelForIdentify;

    UCBioAPI_VERSION ver;
    memset(&ver, 0, sizeof(UCBioAPI_VERSION));
    UCBioAPI_GetVersion(hUCBioAPI, &ver);


    sVer = QString::number(ver.Major1) +
            "." +
            QString::number(ver.Major2) +
            "." +
            QString::number(ver.Minor1) +
            "." +
            QString::number(ver.Minor2);

    sSDKVer = "UCBio SDK version:" +
            QString::number(ver.Major1) +
            "." +
            QString::number(ver.Major2) +
            "." +
            QString::number(ver.Minor1) +
            "." +
            QString::number(ver.Minor2);
    qDebug() << sSDKVer;

    qDebug() << "**************************************************";
}

void MainWidget::GoToSysTray()
{
    qDebug() << "**************************************************";
    qDebug() << "Show App on Sys Tray";
    icon.addFile("app.ico");

    SysTray.setIcon(icon);
    SysTray.setVisible(true);
    SysTray.setToolTip("FingerManager Client(" + sVersion +  ") " + "-Active(SDK version:" + sVer + ")");
    SysTray.show();
    qDebug() << "**************************************************";
}



bool MainWidget::OpenDevice()
{
    //qDebug() << "**************************************************";
    UCBioAPI_RETURN err = UCBioAPI_OpenDevice(hUCBioAPI, UCBioAPI_DEVICE_ID_AUTO);
    if (err == UCBioAPIERROR_NONE) {
        qDebug() << "Can Open Finger Print Reader Device: UCBioAPIERROR_NONE";
        //qDebug() << "**************************************************";
        return true;
    }
    else if(err == UCBioAPIERROR_DEVICE_ALREADY_OPENED){
         qDebug() << "Can Open Finger Print Reader Device: UCBioAPIERROR_DEVICE_ALREADY_OPENED";
         //qDebug() << "**************************************************";
         return true;
    }
    else if(err == UCBioAPIERROR_INVALID_HANDLE){
         qDebug() << "Can Not Open Finger Print Reader Device: UCBioAPIERROR_INVALID_HANDLE";
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_INVALID_DEVICE_ID){
         qDebug() << "Can Not Open Finger Print Reader Device: UCBioAPIERROR_INVALID_DEVICE_ID";
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_DEVICE_OPEN_FAIL){
         qDebug() << "Can Not Open Finger Print Reader Device: UCBioAPIERROR_INVALID_DEVICE_ID";
         //qDebug() << "**************************************************";
         return false;
    }
    else{
        qDebug() << "Can not Open Finger Print Reader Device: UCBioAPIERROR_UNKNOWN" ;
        //qDebug() << "**************************************************";
        return false;
    }
}



bool MainWidget::EnrollFP()
{
    //qDebug() << "   **************************************************";
    //Open Device
    if(!OpenDevice()){
        emit this->send_resp_tothread("Finger Print Device is Not Connected",true);
        //clCurrentSocket->sendTextMessage("Finger Print Device is Not Connected");
        //clCurrentSocket->flush();
        return false;
    }


    UCBioAPI_RETURN err = UCBioAPI_Enroll(hUCBioAPI,
                                          nullptr,
                                          &hEnrolledFIR,
                                          nullptr,
                                          5000,
                                          nullptr,
                                          nullptr);


    //UCBioAPI_USE_DEFAULT_TIMEOUT

    if(bCanselEnrollment == true){
        UCBioAPI_FreeFIRHandle(hEnrolledFIR);
        qDebug() << "Can Not Enroll: Cansel process from socket client";
        CloseDevice();
        //qDebug() << "**************************************************";
        return false;
    }
    if (err == UCBioAPIERROR_NONE) {
        qDebug() << "Can Enroll: UCBioAPIERROR_NONE";
        CloseDevice();
        //qDebug() << "**************************************************";
        return true;
    }
    else if(err == UCBioAPIERROR_INVALID_HANDLE){
         qDebug() << "Can Not Enroll: UCBioAPIERROR_INVALID_HANDLE";
         CloseDevice();
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_INVALID_POINTER){
         qDebug() << "Can Not Enroll: UCBioAPIERROR_INVALID_POINTER";
         CloseDevice();
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_FUNCTION_FAIL){
         qDebug() << "Can Not Enroll: UCBioAPIERROR_FUNCTION_FAIL";
         CloseDevice();
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_DEVICE_NOT_OPENED){
         qDebug() << "Can Not Enroll: UCBioAPIERROR_DEVICE_NOT_OPENED";
         CloseDevice();
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_USER_CANCEL){
         qDebug() << "Can Not Enroll: UCBioAPIERROR_USER_CANCEL";
         bCanselEnrollment = true;
         CloseDevice();
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_USER_BACK){
         qDebug() << "Can Not Enroll: UCBioAPIERROR_USER_BACK";
         CloseDevice();
         //qDebug() << "**************************************************";
         return false;
    }
    else{
        qDebug() << "Can Not Enroll: UCBioAPIERROR_UNKNOWN" ;
        CloseDevice();
        //qDebug() << "**************************************************";
        return false;
    }
}

bool MainWidget::GetTextFIDFromHandle()
{
   UCBioAPI_RETURN err = UCBioAPI_GetTextFIRFromHandle(hEnrolledFIR,&TextFir,UCBioAPI_FALSE);
   if(err == UCBioAPIERROR_NONE){
       qDebug() << "Can FIR Handle to TextFIR: UCBioAPIERROR_NONE";
       //qDebug() << "   **************************************************";
       inputFIR.Form = UCBioAPI_FIR_FORM_TEXTENCODE;
       inputFIR.InputFIR.TextFIR = &TextFir;
       return true;
   }
   else if(err == UCBioAPIERROR_INVALID_HANDLE){
       qDebug() << "Can Not FIR Handle to TextFIR: UCBioAPIERROR_INVALID_HANDLE";
       //qDebug() << "   **************************************************";
       return false;
   }
   else if(err == UCBioAPIERROR_INVALID_POINTER){
       qDebug() << "Can Not FIR Handle to TextFIR: UCBioAPIERROR_INVALID_POINTER";
       //qDebug() << "   **************************************************";
       return false;
   }
   else{
       qDebug() << "Can Not FIR Handle to TextFIR: UCBioAPIERROR_UNKNOWN";
       //qDebug() << "   **************************************************";
       return false;
   }
}

//bool MainWidget::FIR_to_Template()
//{
//    //Export FIR to Input FIR
//    inputFIR.Form = UCBioAPI_FIR_FORM_HANDLE;
//    inputFIR.InputFIR.FIRinBSP = &hEnrolledFIR;

//    qDebug() << "   **************************************************";
//    UCBioAPI_RETURN err = UCBioAPI_FIRToTemplate(hUCBioAPI,
//                                                 &inputFIR,
//                                                 &ExData,
//                                                 UCBioAPI_TEMPLATE_TYPE_SIZE400);


//    if(err == UCBioAPIERROR_NONE){
//        qDebug() << "Can FIR to TEMPLATE: UCBioAPIERROR_NONE";
//        qDebug() << "   **************************************************";
//        return true;
//    }
//    else if(err == UCBioAPIERROR_INVALID_HANDLE){
//        qDebug() << "Can Not FIR to Template: UCBioAPIERROR_INVALID_HANDLE";
//        qDebug() << "   **************************************************";
//        return false;
//    }
//    else if(err == UCBioAPIERROR_INVALID_POINTER){
//        qDebug() << "Can Not FIR to Template: UCBioAPIERROR_INVALID_POINTER";
//        qDebug() << "   **************************************************";
//        return false;
//    }
//    else if(err == UCBioAPIERROR_MUST_BE_PROCESSED_DATA){
//        qDebug() << "Can Not FIR to Template: UCBioAPIERROR_MUST_BE_PROCESSED_DATA";
//        qDebug() << "   **************************************************";
//        return false;
//    }
//    else if(err == UCBioAPIERROR_FUNCTION_FAIL){
//        qDebug() << "Can Not FIR to Template: UCBioAPIERROR_FUNCTION_FAIL";
//        qDebug() << "   **************************************************";
//        return false;
//    }
//    else{
//        qDebug() << "Can Not FIR to Template: UCBioAPIERROR_UNKNOWN";
//        qDebug() << "   **************************************************";
//        return false;
//    }
//}



bool MainWidget::GetFringerPrint()
{
    //qDebug() << "**************************************************";
    if(!EnrollFP()){
        if(bCanselEnrollment == true){
            emit this->send_resp_tothread("CMD_NK:ENROLL_CANSEL",true);
            bCanselEnrollment = false;
            bEnrolling = false;
            return false;
        }
        emit this->send_resp_tothread("CMD_NK:ENROLL",true);
        bEnrolling = false;
        return false;
    }
    if(!GetTextFIDFromHandle()){
        emit this->send_resp_tothread("CMD_NK:ENROLL",true);
        bEnrolling = false;
        return false;
    }
    char* TextFirData = inputFIR.InputFIR.TextFIR->TextFIR;
    QString TEXTFIR;
    TEXTFIR.clear();
    int i = 0;
    while(*TextFirData != NULL){
        TEXTFIR.append(*TextFirData);
        TextFirData++;
        i++;
    }
    qDebug() << "text FIR count= " << i;
    QString tmp = QString("CMD_OK:TEXTFIR:%1").arg(i,8,10,QChar('0')) + ":";
    tmp = tmp + TEXTFIR;
    emit this->send_resp_tothread(tmp,true);
    UCBioAPI_FreeFIRHandle(hEnrolledFIR);
    UCBioAPI_FreeTextFIR(&TextFir);
    //qDebug() << "**************************************************";
    bEnrolling = false;
    return true;
}

bool MainWidget::SendCSN()
{
    if(!GetCSN()){
        emit this->send_resp_tothread("CMD_NK:CSN_NK",true);
        bEnrolling = false;
        return false;
    }
    else{
        sCSN.clear();
        for(int i=0; i<nLen; i++){
            sCSN.append(QString("%1").arg(pBuf[i],2,16,QLatin1Char('0')));
        }
        sCSN = sCSN.toUpper();
        emit this->send_resp_tothread("CMD_OK:CSN_" + QString("%1").arg(nLen,2,10,QLatin1Char('0'))+ "_" + sCSN,true);
        bEnrolling = false;
        return true;
    }
}

bool MainWidget::GetCSN()
{
    nLen = 32;
    memset(pBuf, 0x00, sizeof pBuf);
    if(!OpenDevice()){
        emit this->send_resp_tothread("SC Device is Not Connected",true);
        return false;
    }
    qDebug() << "Get CSN";
    UCBioAPI_RETURN ret = UCBioAPI_SC_ReadSerial(hUCBioAPI, pBuf, &nLen, UCBioAPI_SC_LED_TOGGLE);
    if(ret == UCBioAPIERROR_NONE){
        qDebug() << "Can Get CSN: UCBioAPIERROR_NONE";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return true;
    }
    else if(ret == UCBioAPIERROR_INVALID_HANDLE){
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_INVALID_HANDLE";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
    else if(ret == UCBioAPIERROR_FUNCTION_NOT_SUPPORTED){
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_FUNCTION_NOT_SUPPORTED";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
    else if(ret == UCBioAPIERROR_DEVICE_NOT_OPENED){
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_DEVICE_NOT_OPENED";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
    else if(ret == UCBioAPIERROR_SC_FUNCTION_FAILED){
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_SC_FUNCTION_FAILED";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
    else if(ret == UCBioAPIERROR_SC_NOT_SUPPORTED_DEVICE){
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_SC_NOT_SUPPORTED_DEVICE";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
    else if(ret == UCBioAPIERROR_SC_NOT_SUPPORTED_FIRMWARE){
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_SC_NOT_SUPPORTED_FIRMWARE";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
    else{
        qDebug() << "Can Not Get CSN: UCBioAPIERROR_UNKNOWN";
        //qDebug() << "   **************************************************";
        CloseDevice();
        return false;
    }
}

void MainWidget::processTextMessage(QString text)
{
    //qDebug() << "**************************************************";
    //qDebug() << "text message";

    if(text == "CMD:CANSELENROLL" && bEnrolling == true){
        //qDebug() << "**************************************************";
        qDebug() << "cansel Enroll";
        bCanselEnrollment = true;
        emit this->send_resp_tothread("Please Close Fingerprint Registration Wizard",false);
        //qDebug() << "**************************************************";
        return;
    }
    if(bEnrolling == false){
        if(text == "CMD:FINGER_ENROLL"){
            bEnrolling = true;
            qDebug() << "received Finger Enroll CMD from Socket";
            GetFringerPrint();
            //qDebug() << "**************************************************";

        }
        else if(text == "CMD:REINITBIO"){
            if(bOpenDev)
                CloseDevice();
            if(bInitBio)
                BioTerminate();
            bInitBio = BioInit();
            if(!bInitBio){
                emit this->send_resp_tothread("CMD_NK:REINITBIO",true);
            }
            else if(bInitBio){
                emit this->send_resp_tothread("CMD_OK:REINITBIO",true);
            }
            else{
                emit this->send_resp_tothread("CMD_NK:REINITBIO",true);
            }
        }
        else if(text == "CMD:GETCSN"){
            if(!bSC){
                emit this->send_resp_tothread("CMD_NK:CSN_NK_NOTSUPPORTED",true);
                return;
            }
            bEnrolling = true;
            qDebug() << "received get CSN CMD from Socket";
            SendCSN();
            //qDebug() << "**************************************************";
        }

    }
}
bool MainWidget::CloseDevice()
{
    //qDebug() << "**************************************************";
    UCBioAPI_RETURN err = UCBioAPI_CloseDevice(hUCBioAPI, UCBioAPI_DEVICE_ID_AUTO);
    if (err == UCBioAPIERROR_NONE) {
        qDebug() << "Can Close Finger Print Reader Device: UCBioAPIERROR_NONE";
        //qDebug() << "**************************************************";
        return true;
    }
    else if(err == UCBioAPIERROR_DEVICE_NOT_OPENED){
         qDebug() << "Can Close Finger Print Reader Device: UCBioAPIERROR_DEVICE_NOT_OPENED";
         //qDebug() << "**************************************************";
         return true;
    }
    else if(err == UCBioAPIERROR_INVALID_HANDLE){
         qDebug() << "Can Not Close Finger Print Reader Device: UCBioAPIERROR_INVALID_HANDLE";
         //qDebug() << "**************************************************";
         return false;
    }
    else if(err == UCBioAPIERROR_WRONG_DEVICE_ID){
         qDebug() << "Can Not Close Finger Print Reader Device: UCBioAPIERROR_WRONG_DEVICE_ID";
         //qDebug() << "**************************************************";
         return false;

    }
    else{
        qDebug() << "Can Not Close Finger Print Reader Device: UCBioAPIERROR_UNKNOWN" ;
        //qDebug() << "**************************************************";
        return false;

    }

}

bool MainWidget::BioTerminate()
{
  //qDebug() << "**************************************************";
    UCBioAPI_RETURN err = UCBioAPI_Terminate(hUCBioAPI);
   if (err == UCBioAPIERROR_NONE){
       qDebug() << "Can Bio SDK Terminate: UCBioAPIERROR_NONE" ;
       //qDebug() << "**************************************************";
       return true;
   }
   else if(err == UCBioAPIERROR_INVALID_HANDLE){
       qDebug() << "Can Not Bio SDK Terminate: UCBioAPIERROR_INVALID_HANDLE";
       //qDebug() << "**************************************************";
       return false;
   }
   else{
       qDebug() << "Can Not Bio SDK Terminate: UCBioAPIERROR_UNKNOWN" ;
       //qDebug() << "**************************************************";
       return false;
   }
}

MainWidget::~MainWidget()
{
    if(bOpenDev)
        CloseDevice();
    if(bInitBio)
        BioTerminate();

    socketworker->deleteLater();
    soketthread->deleteLater();
    qDebug() << "###################################################################################################";

    delete ui;
}


