#ifndef SERIALDEF_H
#define SERIALDEF_H

namespace SerialPort
{
    enum BaudrateType
    {
        BAUD50,
        BAUD75,
        BAUD110,
        BAUD134,
        BAUD150,
        BAUD200,
        BAUD300,
        BAUD600,
        BAUD1200,
        BAUD1800,
        BAUD2400,
        BAUD4800,
        BAUD9600,
    #ifdef Q_OS_WIN32
        BAUD14400,             //WINDOWS ONLY
    #endif
        BAUD19200,
        BAUD38400,
    #ifdef Q_OS_WIN32
        BAUD56000,             //WINDOWS ONLY
    #endif
        BAUD57600,
        BAUD115200,
    #ifdef Q_OS_WIN32
        BAUD128000,            //WINDOWS ONLY
        BAUD256000,            //WINDOWS ONLY
    #endif
    };

    enum DataBitsType
    {
        DATA_5,
        DATA_6,
        DATA_7,
        DATA_8
    };

    enum ParityType
    {
        PAR_NONE,
        PAR_ODD,
        PAR_EVEN,
    #ifdef Q_OS_WIN32
        PAR_MARK,               //WINDOWS ONLY
    #endif
        PAR_SPACE
    };

    enum StopBitsType
    {
        STOP_1,
    #ifdef Q_OS_WIN32
        STOP_1_5,               //WINDOWS ONLY
    #endif
        STOP_2
    };

    enum FlowType
    {
        FLOW_OFF,
        FLOW_HARDWARE,
        FLOW_XONXOFF
    };

    struct PortSettings
    {
        BaudrateType baudrate;
        DataBitsType dataBits;
        ParityType parity;
        StopBitsType stopBits;
        FlowType flowControl;
        long timeout;
    };


    enum LineStatus
    {
        LS_CTS,
        LS_DSR,
        LS_DCD,
        LS_RI,
        LS_RTS,
        LS_DTR,
        LS_ST,
        LS_SR,
    };

    enum SerialPort_Error
    {
        E_NO_ERROR,
        E_INVALID_FD,
        E_NO_MEMORY,
        E_CAUGHT_NON_BLOCKED_SIGNAL,
        E_PORT_TIMEOUT,
        E_INVALID_DEVICE,
        E_BREAK_CONDITION,
        E_FRAMING_ERROR,
        E_IO_ERROR,
        E_BUFFER_OVERRUN,
        E_RECEIVE_OVERFLOW,
        E_RECEIVE_PARITY_ERROR,
        E_TRANSMIT_OVERFLOW,
        E_READ_FAILED,
        E_WRITE_FAILED,
        E_PERMISSION_DENIED,
    };

}

#endif // SERIALDEF_H
