#include "netprotocol.h"
#include <QMetaType>

NetProtocol::NetProtocol()
{
    m_package.head = 0xee;
    m_package.version = 0x01;
    m_package.device = 5;
    m_package.tail = 0xff;

    m_minLength = 14;

    qRegisterMetaType<NetProtocol::ContentList>("NetProtocol::ContentList");
}

void NetProtocol::setDeviceNum(quint16 num)
{
    m_package.device = num;
}


QByteArray NetProtocol::tryUnpackage(QByteArray &data)
{
    QByteArray validData;

    //do not reach minimum length
    if(data.count() < m_minLength)
        return validData;

    int headPos = -1, tailPos = -1;
    //search head
    for(int i = 0; i < data.count(); ++i)
    {
        if(quint8(data.at(i)) == m_package.head)
        {
            headPos = 0;
            data.remove(0, i);
            break;
        }
    }

    //no head, throw invalid data and return
    if(headPos < 0)
    {
        data.clear();
        return validData;
    }

    //length too short
    quint16 length = (quint8(data.at(2)) << 8) + quint8(data.at(3));
    if(length > data.count())
        return validData;

    //get tail
    if(quint8(data.at(length - 1)) == m_package.tail)
    {
        tailPos = length - 1;
    }

    //no tail, return and wait for new data
    if(tailPos < 0)
    {
        //remove invalid data
        data.remove(headPos, length);
        return validData;
    }

    validData = data.left(tailPos + 1);
    data.remove(0, tailPos + 1);

    return validData;
}

QByteArray NetProtocol::package(quint8 id, const NetProtocol::ContentList &contents)
{
    //package data to send to server
    int length = 0;
    QByteArray data;
    data.append(m_package.head);
    data.append(m_package.version);
    data.append(char(0));
    data.append(char(0));
    data.append(char(0));
    data.append(id);
    data.append((m_package.device >> 8));
    data.append((m_package.device & 0xff));
    data.append(char(0));
    data.append(char(0));
    data.append(char(0));

    length += 11;

    //append content
    foreach(const NetProtocol::Content &content, contents)
    {
        data += (content.id >> 8);
        data += (content.id & 0xff);
        data += (content.length >> 8);
        data += (content.length & 0xff);
        data += content.data;
        length += (content.data.count() + 4);
    }

    data.append(char(0));
    data.append(char(0));
    data.append(0xff);

    length += 3;

    data[2] = (length >> 8);
    data[3] = (length & 0xff);

    return data;
}

NetProtocol::ContentList NetProtocol::unpackage(const QByteArray &data, quint8 &id)
{
    ContentList list;

    if(data.count() < m_minLength)
        return list;

    //unpackage data from server

    //check head
    if(quint8(data.at(0)) == m_package.head)
    {
        //check tail
        int length = (quint8(data.at(2)) << 8) + quint8(data.at(3));
        if(length > data.count())
            return list;

        if(quint8(data.at(length - 1)) == m_package.tail)
        {
            //check version
            if(quint8(data.at(1)) == m_package.version)
            {
                //check transfer
                if(quint8(data.at(4)) == 0x01)
                {
                    //get id
                    id = quint8(data.at(5));
                    //unpackage content
                    for(int i = 11; i < (length - 3);)
                    {
                        NetProtocol::Content content;
                        content.id = (quint8(data.at(i)) << 8) + quint8(data.at(i + 1));
                        content.length = (quint8(data.at(i + 2)) << 8) + quint8(data.at(i + 3));
                        content.data = data.mid(i + 4, content.length);
                        list.append(content);
                        i += (4 + content.length);
                    }
                }
            }
        }
    }

    return list;
}

