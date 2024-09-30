#include "mainwidget.h"
#include <QApplication>
#include <QDir>





#define LOGSIZE 1024 * 100000
#ifdef QT_DEBUG
   #define LOG_TO_FILE true
#else
  #define LOG_TO_FILE true
#endif

void myMessageOutput(QtMsgType type,
                     const QMessageLogContext &context,
                     const QString &msg)
{
   QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
   QByteArray localMsg = msg.toLocal8Bit();
   QDateTime time = QDateTime::currentDateTime();
   QString formattedTime = time.toString("MM-dd hh:mm:ss.zzz");
   QString fileName =  QString("log/Log_%1_.txt")
           .arg(QDate::currentDate().toString("yyyy_MM_dd"));
   QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
   QString logLevelName = msgLevelHash[type];
   QByteArray logLevelMsg = logLevelName.toLocal8Bit();
   QDir dir;
   if (!dir.exists("log"))
       dir.mkpath("log");
   QFile outFileCheck(fileName);
   QString NewFileName = fileName;
   int size = static_cast<int>(outFileCheck.size());
   int counter = 0 ;
   while ( size > LOGSIZE ){
       counter++;
       NewFileName = fileName+QString::number(counter);
       QFile outFileCheck(NewFileName);
       size = static_cast<int>(outFileCheck.size());
   }
   if (LOG_TO_FILE) {
       QString txt = QString("%1 %2: %3 (%4)").arg(formattedTime, logLevelName, msg,  context.file);
       QFile outFile(NewFileName);
       outFile.open(QIODevice::WriteOnly | QIODevice::Append);
       QTextStream ts(&outFile);
       ts << txt << endl;
       outFile.close();
   } else {
       fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
       fflush(stderr);
   }
   if (type == QtFatalMsg)
       abort();
}

int main(int argc, char *argv[])
{
    //sqlServer_connection = "DRIVER={SQL Server};SERVER=%1;Database=%2;Client_CSet=UTF-8";

    QSettings setting("config.dll",QSettings::IniFormat);
    bool bDebug = setting.value("Main/main_debug_log",false).toBool();
    qDebug() << "Debug to file: " << bDebug;

    if(bDebug)
        qInstallMessageHandler(myMessageOutput);
    qDebug() << "available drivers: " << QSqlDatabase::drivers();

    QApplication a(argc, argv);

    MainWidget w;
    w.setWindowTitle("FingerManager Restaurant");
    QIcon iicon;
    iicon.addFile("app.ico");
    w.setWindowIcon(iicon);
    w.setFixedHeight(768);
    w.setFixedWidth(1024);
    w.setHidden(false);
    w.setWindowFlag(Qt::FramelessWindowHint);
    w.showFullScreen();
    //w.show();


    return a.exec();
}
