#ifndef HELPCLASS_H
#define HELPCLASS_H

/**
* @brief: 帮助类
* @author: Fu_Lin
* @date:2018年8月21日
* @description: 主要用于一些读写文件，加密解密，等一些可公共调用的方法
*/

#include <QObject>
#include <QByteArray>
#include <QPoint>
#include <QLabel>

#define DefaultKEY "1ed中.@"  //加密會用到
#define AgencyFileName "agency.dat"

class QJsonObject;
class QJsonDocument;

typedef QMap<QString ,QString>  QMapString;

class HelpClass : public QObject
{
    Q_OBJECT

public:
    explicit HelpClass(QObject *parent = nullptr);

    /**
     * @brief GetEncrypt 获取加密后的密文
     * @param plaintextStr 加密前的明文 QByteArray类型
     * @param key 加密需要的钥匙，解密也要用到，建议不填写，使用默认自带钥匙
     * @return 已加密成功的密文
     */
    static QByteArray GetEncrypt(const QByteArray plaintextStr, QByteArray key ="");

    /**
      * @brief GetEncrypt 获取加密后的密文--重载函数
      * @param plaintextStr 加密前的明文 QString类型
      * @param key  加密需要的钥匙，解密也要用到，建议不填写，使用默认自带钥匙
      * @return 已加密成功的密文
      */
    static QByteArray GetEncrypt(const QString plaintextStr, QByteArray key ="");

    /**
     * @brief GetDecrypt 获取解密后的明文
     * @param ciphertext 解密前的密文， 必须为QByteArray类型
     * @param key 加密需要的钥匙，解密也要用到，建议不填写，使用默认自带钥匙
     * @return 已解密的明文
     */
    static QByteArray GetDecrypt(const QByteArray ciphertext, QByteArray key ="");

    /**
     * @brief isDirExist 判断文件夹是否存在,不存在则创建
     * @param fullPath 需要判断并创建的路径，支持多级子路径创建
     * @return 成功返回true, 失败返回false
     */
    static bool isDirExist(QString fullPath);

    /**
     * @brief bytesToKB  字节 转换为B KB MB GB
     * @param bytes 需要转换的字节数
     * @return 转换成功的对应KB, 大小，默认保留两位小数
     */
    static QString bytesToKB(qint64 size);

    /**
     * @brief writeDataToFile 将数据写入到文件，数据格式采用QList<QMap>类型
     * @param mapList 数据的map类型，直接将map数据写入文件，取出来的时候也是对应的时候也是对应map类型
     * @param Path 写入文件的路径名称，建议为空，使用默认参数
     * @return true 写入成功，false 写入失败
     */
    static bool writeDataToFile(QList<QMap<QString , QStringList> > mapList, QString Path = "");

    /**
     * @brief ReadDataFromFile 读取文件
     * @return  返回List<Map>类型
     */
    static QList<QMap<QString , QStringList> > ReadDataFromFile(QString Path = "");

    /**
     * @brief removeFile 删除传入的文件
     * @param filePath 文件的绝对路径
     * @return
     */
    static bool removeFile(QString filePath="");

    /**
     * @brief getTimestamp 获取当前时间戳
     * @return  QString类型时间戳
     */
    static QString getTimestamp();

    /**
     * @brief md5Encrypt 进行md5加密
     * @param plaintextStr 需要加密的明文
     * @return
     */
    static QString md5Encrypt(QString plaintextStr);

    /**
     * @brief getCurrentTime 获取当前时间
     * @return
     */
    static QString getCurrentTime(const QString &format = "");

    /**
     * @brief getCurrentDateTime 获取当前的年月日
     * @param format 转换格式
     * @return
     */
    static QString getCurrentDateTime(const QString &format = "");

    /**
     * @brief msecsTo 转换毫秒数，获取从传送过来的时间到当前时间之差
     * @param timeStr 传送过来的时间
     * @return 时间差，毫秒级时间戳
     */
    static QString msecsTo(const QString &timeStr);

    /**
     * @brief jsonCreate jsonObject 对象的生成
     * @param key  需要生成的key
     * @param value 需要生成的 value
     * @param isClean 是否生成前先清空jsonObject
     */
    static void jsonCreate(const QString &key, const QJsonValue &value, bool isClean=false);

    /**
    * @brief getJsonObject 调用此方法之前，需要先调用jsonCreate，来生成jsonObject
    * @return
    */
   static QJsonObject getJsonObject();

   /**
    * @brief tojsonArray 将json数组转换为字符串格式
    * @return
    */
   static QString tojsonArray(QJsonArray);

   /**
    * @brief generalJsonParse 通用的json解析方法 ,只能支持一级json解析，数组型的暂不支持
    * @param jsonDocument   需要解析的QJsonDocument,由外面调用传入
    * @param jsonkeyMap       需要解析的json中的Key值，首次传入，value应该为空，调用完成后，再根据key取出对应的value
    * @param headKey            json需要解析的头字段key，默认为code，如果code值不对，直接返回false，Map不做操作，code值请参考headValue
    * @param headValue          json需要解析的头字段key匹配的正确json返回值， 默认正确为0
    * @param flage                  跳过json headKey和value的对比，直接截取对应需要的字段
    * @return true 解析成功，false 解析失败
    */
   static bool generalJsonParse(QJsonDocument, QMap<QString ,QString> &jsonkeyMap, QString headKey = "code", int headValue = 0, bool flage = false);

   /**
    * @brief generalarrayJsonParse  通用的json数组解析方法 ,只能支持一级数组json解析，数组嵌套型的暂不支持
    * @param jsonArray 需要解析的QJsonArray,由外面调用传入
    * @param listJsonkepMap 需要解析的json中的Key值，首次传入，value应该为空，调用完成后，再根据key取出对应的value
    * @param arrayKey 需要解析判断的json中的key值，如果判断不是数组类型，直接返回false，
    * @param headKey  json需要解析的头字段key，默认为code，如果code值不对，直接返回false，Map不做操作，code值请参考headValue
    * @param headValue  json需要解析的头字段key匹配的正确json返回值， 默认正确为0
    * @return
    */
   static bool generalArrayJsonParse(QJsonDocument jsonDocument, QList<QMapString> & listJsonkepMap, QMapString jsonkey, QString arrayKey, QString headKey = "code", int headValue = 0);
   /**
    * @brief getUuid 获取Uuid唯一标识符 ，经测试不会重复出现
    * @return
    */
   static QString getUuid();

   /**
    * @brief getCurrentTempDataDir 获取临时目录路径
    * @return
    */
   static QString getCurrentTempDataDir();

   /**
    * @brief loaderQssFile 加载QSS样式表文件
    * @param qssFileName  根据传送过来的qss文件名称加载不同的路径文件（可以传全路径或者当前的文件名）
    * @return 返回已经读取成功的qqs文件数据，返回空代表打开文件失败
    */
   static QString loaderQSSFile(const QString &qssFileName);

   /**
    * @brief setGlobalStyleSheet 设置全局样式表格式
    * @param qssFileName 需要设置的样式表文件
    * @return 无
    */
   static void setGlobalStyleSheet(const QString &qssFileName);

   /**
    * @brief writeSettingFile 将相关数据写入配置文件
    * @param mapSettingData 需要写入的map数据
    * @param groupName  写入setting自定义的组名，读取的时候也要对应的组名
    * @param filePath 需要写入的文件路径（包含文件名称）
    * @param isEncrypt 写入时时候加密，缺省值为不加密
    */
   static void writeSettingFile(QMap<QString , QString> mapSettingData, QString groupName, QString filePath, bool isEncrypt = false);

   /**
    * @brief readSettingFile 读取相关配置数据信息
    * @param groupName 需要读取的setting自定义的组名，与写入时的对应
    * @param filePath 需要读取的文件路径(包含文件名称)
    * @param isDecrypt 读取时是否解密,与写入时时候加密对应
    * @return 返回对应的组名的map数据，根据自己定义的key来取值
    */
   static QMap<QString , QString> readSettingFile(QString groupName, QString filePath , bool isDecrypt = false);

   /**
    * @brief ToolTipmessage 消息提示框弹出，默认从最上中间弹出
    * @param parent  弹窗的父对象
    * @param message 弹出消息的显示文本
    * @param point 弹出消息的位置，默认不写，位置在最上中间动画弹出, 如果填写具体位置则无动画弹出
    */
   static void ToolTipmessage(QWidget * parent, QString message, QPoint point = QPoint(0, 0));

   /**
    * @brief getFontWidth 获取字体长度
    * @param text 字体文本
    * @return 字体长度
    */
   static int getFontWidth(QString text);

   /**
    * @brief showDialogText  首先子对象的提示性文本框，如：该数据获取为空等等提示性
    * @param parent 需要显示的父对象
    * @param showText 需要显示提示的文本内同
    * @param free 是否释放该控件文本
    */
   static void showDialogText(QWidget *parent, QString showText, bool free = false);

   /**
    * @brief setGraphicsEffect 设置文本阴影
    * @param parent 需要设置的父对象
    */
   static void setGraphicsEffect(QWidget * parent);

   /**
    * @brief CopyText  剪切板实现“复制”“粘贴”功能
    * @param text 需要复制的文本
    */
   static void copyText(QString text);

   //-----------------------------------------结束-------------------------------------------------------//
private:
    /**
     * @brief encryption base64加密中英文字符
     * @param plaintextStr 加密明文 QByteArray类型
     * @return
     */
    static QByteArray encryption(const QByteArray plaintextStr);
    /**
     * @brief encryption base64加密中英文字符重载函数
     * @param plaintextStr 加密明文，QString类型
     * @return
     */
    static QByteArray encryption(const QString plaintextStr);
    /**
     * @brief Deciphering 解密字符
     * @param ciphertext 需要解密的密文，必须为QByteArray
     * @return
     */
    static QByteArray Deciphering(const QByteArray ciphertext);
    /**
      * @brief getXorEncryptDecrypt 异或加解密方法
      * @param str 需要加密的明文或密文
      * @param key  需要加密的钥匙
      * @return
      */
    static QByteArray getXorEncryptDecrypt(const QByteArray &str, const QByteArray &key);

private:
    static QJsonObject m_jsonObject;
    static QLabel *m_label;
};

#endif // HELPCLASS_H
