#include "crc32.h"


CRC32 &CRC32::instance()
{
    static CRC32 m_crc32;
    return m_crc32;
}
