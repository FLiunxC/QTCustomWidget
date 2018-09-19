#include "HelpClass.h"
#include <QDateTime>
#include <QCryptographicHash>
#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QDebug>
#include <QSettings>

QJsonObject HelpClass::m_jsonObject;

HelpClass::HelpClass(QObject *parent) : QObject(parent)
{

}

QByteArray HelpClass::GetEncrypt(const QByteArray plaintextStr, QByteArray key)
{
    QByteArray encryptText = encryption(plaintextStr);
    if(key.isEmpty())
    {
        key = DefaultKEY;
    }
    return getXorEncryptDecrypt(encryptText, key);
}

QByteArray HelpClass::GetEncrypt(const QString plaintextStr, QByteArray key)
{
    QByteArray encryptText = encryption(plaintextStr);
    if(key.isEmpty())
    {
        key = DefaultKEY;
    }
    return getXorEncryptDecrypt(encryptText, key);
}

QByteArray HelpClass::GetDecrypt(const QByteArray ciphertext, QByteArray key)
{
    if(key.isEmpty())
    {
        key = DefaultKEY;
    }

    QByteArray plaintextByte = getXorEncryptDecrypt(ciphertext, key);

    return Deciphering(plaintextByte);
}

bool HelpClass::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
        return true;
    }
    else
    {
        bool ok = dir.mkpath(fullPath);//创建多级目录
        return ok;
    }
}

bool HelpClass::removeFile(QString filePath)
{
    if(filePath.isEmpty())
    {
        filePath = getCurrentTempDataDir()+"/"+AgencyFileName;
    }
    QFile * file = new QFile(filePath);
    if(file->exists())
    {
        if(file->remove())
        {
            delete file;
            return true;
        }
        else
        {
            delete file;
            return false;
        }
    }
    else
    {
         qCritical("File '%s' does not exist!", qUtf8Printable(filePath));
    }
    delete file;
    return false;
}

QString HelpClass::getTimestamp()
{
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t(); //获取时间戳

    return QString::number(timeT);
}

QString HelpClass::md5Encrypt(QString plaintextStr)
{
     if(plaintextStr.isEmpty())
     {
         return "";
     }
     QByteArray plaintextByArray = plaintextStr.toLocal8Bit();
     QByteArray byteMd5 = QCryptographicHash::hash(plaintextByArray, QCryptographicHash::Md5);

     QString strPwdMd5 = byteMd5.toHex();

     return strPwdMd5;
}

QString HelpClass::getCurrentTime(const QString &format)
{
    QTime  currenttime = QTime::currentTime();
    if(format.isEmpty())
    {
        return currenttime.toString();
    }

    return currenttime.toString(format);
}

QString HelpClass::getCurrentDateTime(const QString &format)
{
    QDateTime date =  QDateTime::currentDateTime();

    if(format.isEmpty())
    {
        return date.toString();
    }

    return date.toString(format);
}

QString HelpClass::msecsTo(const QString &timeStr)
{
    QTime time = QTime::fromString(timeStr);
    int mesecs = time.msecsTo(QTime::currentTime());

    return QString::number(mesecs);
}

void HelpClass::jsonCreate(const QString &key, const QJsonValue &value, bool isClean)
{
    if(isClean)
    {
        QStringList keyList = m_jsonObject.keys();
        for(QString key : keyList)
        {
            m_jsonObject.remove(key);
        }
    }
    if(key.isEmpty())
    {
        return;
    }
    m_jsonObject.insert(key, value);
}

QJsonObject HelpClass::getJsonObject()
{
    return m_jsonObject;
}

QString HelpClass::tojsonArray(QJsonArray jsonArray)
{
    QJsonDocument document;
    document.setArray(jsonArray);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    return strJson;
}

QString HelpClass::getUuid()
{
    return  QUuid::createUuid().toString();
}

QString HelpClass::getCurrentTempDataDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

bool HelpClass::writeDataToFile(QList<QMap<QString, QStringList> > mapList, QString Path)
{
    if(Path.isEmpty())
    {
        Path = getCurrentTempDataDir()+"/Data";
    }

    if(!isDirExist(Path))
    {
        return false;
    }

    Path = Path +"/"+AgencyFileName;

    //保险起见先把原先的文件删除再重写
    removeFile(Path);

    QFile * file = new QFile(Path);

    //默认只写，不会追加前面已有的数据，而是覆盖前面的数据
    if(!file->open(QIODevice::WriteOnly)){
        qInfo()<<QString("%1 file WriteOnly open failed~").arg(Path);
        return false;
    }
    QDataStream  dataStream(file);
    dataStream.setVersion(QDataStream::Qt_5_9);
    QList<QMap<QString, QStringList> >::ConstIterator iter = mapList.constBegin();

    while(iter != mapList.constEnd())
    {
        dataStream<<(*iter);

        iter++;
    }

    file->close();

    delete file;
}

QList<QMap<QString, QStringList> > HelpClass::ReadDataFromFile(QString Path)
{
    if(Path.isEmpty())
    {
        Path = getCurrentTempDataDir()+"/Data/"+AgencyFileName;
    }
    QFile * file = new QFile(Path);
    QList<QMap<QString, QStringList> > mapList;
    //默认只写，不会追加前面已有的数据，而是覆盖前面的数据
    if(!file->open(QIODevice::ReadOnly)){
        qCritical()<<QString("%1 file ReadOnly open failed~").arg(Path);
        return mapList;
    }

    QDataStream  dataStream(file);
    dataStream.setVersion(QDataStream::Qt_5_9);

    while(!dataStream.atEnd())
    {
        QMap<QString, QStringList>  mapData;
        dataStream>>mapData;

        mapList.append(mapData);
    }
    file->close();

    delete file;

    return mapList;
}

QByteArray HelpClass::encryption(const QByteArray plaintextStr)
{
    QByteArray ciphertext = plaintextStr.toBase64();

    return ciphertext;
}

QByteArray HelpClass::encryption(const QString plaintextStr)
{
    QByteArray plaintextByte = plaintextStr.toLocal8Bit();

    return encryption(plaintextByte);
}

QByteArray HelpClass::Deciphering(const QByteArray ciphertext)
{
    QByteArray plaintext = QByteArray::fromBase64(ciphertext);
    return plaintext;
}

QByteArray HelpClass::getXorEncryptDecrypt(const QByteArray &str, const QByteArray &key)
{
    QByteArray bs = str;

    for(int i=0; i<bs.size(); i++){
        for(int j  = 0; j < key.size(); j++)
            bs[i] = bs[i] ^ key[j];
    }

    return bs;
}

void HelpClass::writeSettingFile(QMap<QString, QString> mapSettingData, QString groupName, QString filePath, bool isEncrypt)
{
    QSettings settings(filePath, QSettings::IniFormat);

    QStringList mapList = mapSettingData.keys();

     settings.beginGroup(groupName);
     for(QString key : mapList)
     {
         QString value = mapSettingData.value(key);
         if(isEncrypt)
         {
             QByteArray valueData = GetEncrypt(value);
             settings.setValue(key, valueData);
         }
         else
         {
             settings.setValue(key, value);
         }
     }

     settings.endGroup();
}

QMap<QString, QString> HelpClass::readSettingFile(QString groupName, QString filePath, bool isDecrypt)
{
        QMap<QString, QString> map;
        QSettings settings(filePath,QSettings::IniFormat);

        settings.beginGroup(groupName);
        QStringList keyList = settings.allKeys();

        for(QString key :keyList)
        {
                QString value;
                if(isDecrypt)
                {
                     QByteArray valueData = settings.value(key).toByteArray();
                     valueData = GetDecrypt(valueData);

                     value = QString(valueData);
                }
                else
                {
                     value = settings.value(key).toString();
                }
                map.insert(key, value);
        }
        return map;
}

//加载qss文件
QString HelpClass::loaderQSSFile(const QString & qssFileName)
{

    QFile file(QString(":/qss/%1.qss").arg(qssFileName));
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical("QSS File '%s' does not open!", qUtf8Printable(qssFileName));
        return "";
    }

    QString styleSheet = QLatin1String(file.readAll());
    file.close();

    return styleSheet;
}
