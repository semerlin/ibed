#include "cryptogram.h"

//常量
//随机选择
//TODO
#define KEY_C1 52845
#define KEY_C2 22719

//分解常量
//可显示ascii 33-126之间，差值93
#define R_C1 33
#define R_C2 92
//#define R_C2 26

/**
 * 简单的加密解密算法
 */

Cryptogram::Cryptogram()
{

}


Cryptogram &Cryptogram::instance(void)
{
    static Cryptogram m_cryptogram;
    return m_cryptogram;
}

/**
 * @brief 加密函数
 * @param str 明文
 * @param key 密钥
 * @return 密文
 */
QString Cryptogram::encrypt(const QString &str, quint64 key)
{
    QString result;
    QString ret;
    quint64 tempKey = key;

    //TODO 明文长度增加时加密时间增长的测试
    result.clear();
    for(int i = 0; i < str.size(); i++)
    {
        //按位加密
        QChar val = str.at(i);
        //^不会破坏明文
        uchar newVal = (static_cast<uchar>(val.toLatin1()) ^ static_cast<uchar>(key >> 8)); //加密值
        result += QChar(newVal);  //写入加密值
        //引入明文变量增加随机概率
        key = (static_cast<uchar>(val.toLatin1()) + key) * KEY_C1 + KEY_C2;  //产生新密钥
    }

    //对密文进行转换
    //将字符转换为两个可显示字符保存，方便密文显示
    //转换为两个的原因是加密字符范围大于可显示字符范围，两个才可唯一还原
    /**
     * TODO 会不会看出密文长度始终为明文长度两倍的规律?返回固定长度?
     * 返回定长度时第一个字节保存长度变量
     */
    ret.clear();
    uchar factor = static_cast<uchar>(tempKey & 0xff);
    for(int i = 0; i < result.size(); i++)
    {
        QChar val = result.at(i);
        QString str("00");
        //引入key增加强度
        str[0] = R_C1 + (static_cast<uchar>(val.toLatin1()) ^ factor) / R_C2;
        str[1] = R_C1 + (static_cast<uchar>(val.toLatin1()) ^ factor) % R_C2;
        ret += str;
    }

    return ret;
}

/**
 * @brief 解密函数
 * @param str 密文
 * @param key 密钥
 * @return 明文
 */
QString Cryptogram::decrypt(const QString &str, quint64 key)
{
    QString result;

    result.clear();
    uchar factor = static_cast<uchar>(key & 0xff);
    for(int i = 0; i < str.length() / 2; i++) // 将字符串两个字母一组进行处理
    {
        char val = (static_cast<uchar>(str[i * 2].toLatin1()) - R_C1) * R_C2;
        val += static_cast<uchar>(str[i * 2 + 1].toLatin1()) - R_C1;

        val ^= factor;

        result += QChar(val);
    }


    for(int i = 0; i < result.length(); i++) // 依次对字符串中各字符进行操作
    {
        //按位解密
        QChar val = result[i];
        uchar newVal = (static_cast<uchar>(val.toLatin1()) ^ static_cast<char>(key >> 8)); //加密值
        result[i] = QChar(newVal);  //写入解密值
        key = (newVal + key) * KEY_C1 + KEY_C2;  //产生新密钥
    }

    return result;
}
