#ifndef CRC32_H
#define CRC32_H

#include "commonunit_global.h"

class COMMONUNITSHARED_EXPORT CRC32
{
public:
    static CRC32& instance(void);


private:
    CRC32();
};

#endif // CRC32

