#ifndef BEDDATAPROCESS_H
#define BEDDATAPROCESS_H

#include "sensor_global.h"
#include <QObject>
#include <QList>

class BedControl;
class QMutex;
class IDataHandler;

class SENSORSHARED_EXPORT BedDataProcess : public QObject
{
    Q_OBJECT
public:
    explicit BedDataProcess(quint8 address);

public slots:
    void setContentLen(quint8 len);
    void setRegAddress(quint16 address);
    void onProcessData(const QByteArray &data);

public:
    void addDataHandler(IDataHandler *handler);

signals:
    void infuCountChanged(int);
    void infuSpeedChanged(int);
    void infuMountChanged(int);
    void weightChanged(double);


private:
    QMutex *m_mutex;
    QByteArray m_data;
    quint8 m_contentLen;
    quint8 m_address;
    quint16 m_regAddress;
    QList<IDataHandler *> m_handlers;
};

#endif // BEDDATAPROCESS_H
