#include "basedatahandler.h"

BaseDataHandler::BaseDataHandler(quint8 code, quint16 address) :
    IDataHandler(),
    m_fucCode(code),
    m_regAddress(address)
{

}

quint8 BaseDataHandler::fucCode() const
{
    return m_fucCode;
}

quint16 BaseDataHandler::regAddress() const
{
    return m_regAddress;
}

void BaseDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
{
    Q_UNUSED(code)
    Q_UNUSED(address)
    Q_UNUSED(data)
}
