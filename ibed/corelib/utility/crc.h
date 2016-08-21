#ifndef CRC_H
#define CRC_H


class CRC
{
public:
    CRC();

public:
    static unsigned short mbCRC16(unsigned char* pucFrame, unsigned char usLen);
};

#endif // CRC_H
