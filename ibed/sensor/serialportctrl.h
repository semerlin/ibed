#ifndef SERIALPORTCTRL_H
#define SERIALPORTCTRL_H

#include <qglobal.h>
#include "serialdef.h"
#include "posix_serialport.h"



#ifdef Q_OS_LINUX
#define SerialPortBase Posix_SerialPort
#else
#endif


class SENSORSHARED_EXPORT SerialPortCtrl : public SerialPortBase
{

};

#endif // SERIALPORT_H
