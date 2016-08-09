#ifndef NETPROTOCOL_H
#define NETPROTOCOL_H

#include "network_global.h"
#include <QList>
#include <QByteArray>

class NETWORKSHARED_EXPORT NetProtocol
{
public:
    typedef struct
    {
        quint16 id;
        quint16 length;
        QByteArray data;
    }Content;

    typedef QList<Content> ContentList;

    typedef enum
    {
        HeartBeat = 1,
        Register = 2,
        CalTime = 3,
        TermiInfo = 8,
        TermiControl = 9,
        SysTime = 11,

        BaseInfo = 80,

        AdviseInfo = 101,

        InOutInfo = 102,

    }MsgId;

public:
    NetProtocol();

public:
    void setDeviceNum(quint16 num);
    QByteArray tryUnpackage(QByteArray &data);
    QByteArray package(quint8 id, const ContentList &contents = ContentList());
    ContentList unpackage(const QByteArray &data, quint8 &id);

private:
    typedef struct
    {
        quint8 head;
        quint8 version;
        quint16 length;
        quint8 transfer;
        quint8 msgId;
        quint16 device;
        quint8 state;
        quint8 character;
        quint8 reserved;
        ContentList contents;
        quint16 crc;
        quint8 tail;
    }Package;

    Package m_package;
    int m_minLength;
};

#endif // NETPROTOCOL_H
