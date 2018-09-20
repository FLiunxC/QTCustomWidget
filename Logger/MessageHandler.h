#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <stdio.h>
#include <stdlib.h>
#include <QFile>
#include <QDateTime>
#include <QMutex>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QTextCodec>
#include "HelpClass.h"
/**
* @By QtCreator Create: 2018年4月10日 11:29:36
* @Brief: 日志系统模块
* @Author: fu_lin
* @Description:可以贯穿qml和C++
*/

#define FILEName "logger.txt"
class MessageHandler: public QObject{

    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr)
    {
        Q_UNUSED(parent);
        //注册MessageHandler
        qInstallMessageHandler(MessageHandler::outputMessage);
    }
private:
    static void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        static QMutex mutex;
        mutex.lock();

        QString text;
        switch(type)
        {

        case QtDebugMsg:
            text = QString("Debug:");
            break;

        case QtWarningMsg:
            text = QString("Warning:");
            break;

        case QtCriticalMsg:
            text = QString("Critical:");
            break;

        case QtFatalMsg:
            text = QString("Fatal:");
            break;

        case QtInfoMsg:
            text = QString("Info:");
            break;
        }

        QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
        QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        QString current_date = QString("(%1)").arg(current_date_time);
        QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

        QString logPath ;
#if defined (Q_OS_ANDROID)

        QStringList stringList =  QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        //   qInfo()<<"当前获取到的stringList = "<<stringList;

        logPath =  stringList.at(stringList.length() - 1);

        int indexPosition = logPath.lastIndexOf("/");
        if(indexPosition != -1)
        {
            logPath = logPath.mid(0, indexPosition);

            if(!isDirExist(logPath+"/YYM"))
            {
                qInfo("Failed to create log directory.");
            }
            else
            {
                logPath = logPath+"/YYM";
            }
        }
#else
        logPath =  HelpClass::getCurrentTempDataDir()+"/Logger";

        HelpClass::isDirExist(logPath);
//        qInfo()<<"当前获取到的stringList = "<<logPath;
#endif
        QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");

        logPath = logPath +QString("/logger(%1).txt").arg(date);
    //    qInfo()<<"LogPath = "<<logPath;
        QFile file(logPath);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream text_stream(&file);
        text_stream.setCodec("UTF-8");
        text_stream << message << "\r\n";
        file.flush();
        file.close();

        mutex.unlock();
    }
};
#endif // MESSAGEHANDLER_H
