#ifndef BEDDATASEND_H
#define BEDDATASEND_H

#include <QThread>
#include <QQueue>
#include "modbus.h"

class BedControl;
class QMutex;
class QWaitCondition;

class BedDataSend : public QThread
{
    Q_OBJECT
public:
    class ModbusData
    {
    public:
        ModbusData(Modbus::FunctionCode code, quint16 address, const QByteArray &data) :
            m_code(code),
            m_address(address),
            m_data(data)
        {

        }
    public:
        Modbus::FunctionCode m_code;
        quint16 m_address;
        QByteArray m_data;
    };

public:
    BedDataSend(BedControl *parent);
    ~BedDataSend();

public:
    void appendSendData(ModbusData *data);

protected:
    void run();

private:
    QQueue<ModbusData *> m_dataQueue;

    BedControl *m_control;
    QMutex *m_waitMutex;
    QMutex *m_mutex;
    QWaitCondition *m_waitCondition;

};

#endif // BEDDATASEND_H
