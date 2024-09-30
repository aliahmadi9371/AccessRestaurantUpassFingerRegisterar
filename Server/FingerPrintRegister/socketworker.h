#ifndef SOCKETWORKER_H
#define SOCKETWORKER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>

class socketWorker : public QObject
{
    Q_OBJECT
public:
    explicit socketWorker(QObject *parent = nullptr);

private:
    QList<QWebSocket *> lst_WS_clients;
    QWebSocket* clCurrentSocket;
    QWebSocket* stmpSocket;
    QWebSocketServer *p_qwsClientServer;

    bool bBusy;
    int FP_SC;

signals:
    void start_worker(QString server_name, quint16 port, int maxPending);
    void send_text(QString text);
    void newconnection();

public slots:

    void on_start_worker(QString server_name, quint16 port, int maxPending);
    //void stop();
    void on_NewWebSocketConnection();
    void on_SocketDisconnected();
    void processTextMessage(QString text);
    void receive_resp(QString text, bool end);
};

#endif // SOCKETWORKER_H
