#include "socketworker.h"

socketWorker::socketWorker(QObject *parent) : QObject(parent)
{

}

void socketWorker::on_start_worker(QString server_name, quint16 port, int maxPending)
{
    p_qwsClientServer = new QWebSocketServer(server_name,QWebSocketServer::NonSecureMode,this);
    p_qwsClientServer->listen(QHostAddress::LocalHost,quint16(port));
    p_qwsClientServer->setMaxPendingConnections(maxPending);
    connect(p_qwsClientServer,SIGNAL(newConnection()),this, SLOT(on_NewWebSocketConnection()),Qt::QueuedConnection);
    qDebug() << "socket Name: " << p_qwsClientServer->serverName();
    qDebug() << "socket URL: " << p_qwsClientServer->serverUrl();
    qDebug() << "socket HostAdress: " << p_qwsClientServer->serverAddress();
    bBusy = false;
    FP_SC = 0;

}

void socketWorker::on_NewWebSocketConnection()
{
    //qDebug() << "**************************************************";
    if(lst_WS_clients.count() > 0)
        qobject_cast<QWebSocket *>(sender())->deleteLater();


    QWebSocket *pSocket = p_qwsClientServer->nextPendingConnection();


    qDebug() << "A client socket with address: " << pSocket << " is connect to Test Server";
    connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(processTextMessage(QString)),Qt::QueuedConnection);
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(on_SocketDisconnected()),Qt::QueuedConnection);
    lst_WS_clients << pSocket;
    qDebug() << "client list count: " << lst_WS_clients.count();
    //qDebug() << "**************************************************";
}
void socketWorker::on_SocketDisconnected()
{
    //qDebug() << "**************************************************";
    qDebug() << "Socket Disconnect";
    lst_WS_clients.removeOne(qobject_cast<QWebSocket *>(sender()));
    //qDebug() << "**************************************************";

}

void socketWorker::receive_resp(QString text,bool end)
{
    clCurrentSocket->sendTextMessage(text);
    clCurrentSocket->flush();
    if(end){
        bBusy = false;
        FP_SC = 0;
    }
    return;
}

void socketWorker::processTextMessage(QString text)
{
    //qDebug() << "**************************************************";
    //qDebug() << "text message";
    clCurrentSocket = qobject_cast<QWebSocket *>(sender());
    qDebug() << "client socket with address: " << clCurrentSocket << " Sent a Text message";
    if(text == "CMD:CANSELENROLL"){
        if(bBusy && FP_SC == 1){
            emit this->send_text(text);
            return;
        }
        if(bBusy){
            clCurrentSocket->sendTextMessage("Invalid Command");
            clCurrentSocket->flush();
            return;
        }
    }
    if(bBusy && (text == "CMD_NK:REINITBIO" || text == "CMD:FINGER_ENROLL" || text == "CMD:GETCSN")){
        clCurrentSocket->sendTextMessage("Client Busy");
        clCurrentSocket->flush();
        return;
    }
    else{
        if(text == "CMD_NK:REINITBIO" || text == "CMD:FINGER_ENROLL" || text == "CMD:GETCSN"){
            if(text == "CMD:FINGER_ENROLL")
                FP_SC = 1;
            if(text == "CMD:GETCSN")
                FP_SC = 2;
            bBusy = true;
            emit this->send_text(text);
            return;
        }
        else{
            clCurrentSocket->sendTextMessage("Invalid Command");
            clCurrentSocket->flush();
            return;
        }
    }
}
