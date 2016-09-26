#ifndef BEDDATASEND_H
#define BEDDATASEND_H

#include <QThread>
#include <QQueue>
#include "modbus.h"

class BedControl;
class QMutex;
class QWaitCondition;

class ModbusData
{
public:
    ModbusData(Modbus::FunctionCode code, quint16 address, const QByteArray &data) :
        m_code(code),
        m_address(address),
        m_data(data)
    {

    }

    ModbusData &operator = (const ModbusData &data)
    {
        if(this == &data)
            return *this;

        m_code = data.m_code;
        m_address = data.m_address;
        m_data = data.m_data;

        return *this;
    }

public:
    Modbus::FunctionCode m_code;
    quint16 m_address;
    QByteArray m_data;
};


class BedDataSend : public QThread
{
    Q_OBJECT
public:
    BedDataSend(BedControl *parent);
    ~BedDataSend();

public:
    void appendSendData(const ModbusData &data);

protected:
    void run();

private:
    QQueue<ModbusData> m_dataQueue;

    BedControl *m_control;
    QMutex *m_mutex;
};

#endif // BEDDATASEND_H
