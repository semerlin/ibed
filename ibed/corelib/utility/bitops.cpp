#include "bitops.h"

int Bitops::generic_ffs(int x)
{
    int32_t r = 1;

    if(!x)
        return 0;

    if(!(x & 0xffff))
    {
        x >>= 16;
        r += 16;
    }

    if(!(x & 0xff))
    {
        x >>= 8;
        r += 8;
    }

    if(!(x & 0x0f))
    {
        x >>= 4;
        r += 4;
    }

    if(!(x & 0x03))
    {
        x >>= 2;
        r += 2;
    }

    if(!(x & 0x01))
    {
        x >>= 1;
        r += 1;
    }

    return r;
}

int Bitops::generic_fls(int x)
{
    int32_t r = 32;

    if(!x)
        return 0;

    if(!(x & 0xffff0000u))
    {
        x <<= 16;
        r -= 16;
    }

    if(!(x & 0xff000000u))
    {
        x <<= 8;
        r -= 8;
    }

    if(!(x & 0xf0000000u))
    {
        x <<= 4;
        r -= 4;
    }

    if(!(x & 0xc0000000u))
    {
        x <<= 2;
        r -= 2;
    }

    if(!(x & 0x80000000u))
    {
        x <<= 1;
        r -= 1;
    }

    return r;
}

quint32 Bitops::generic_hweight32(quint32 w)
{
    quint32 res = (w & 0x55555555) + ((w >> 1) & 0x55555555);
    res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
    res = (res & 0x0f0f0f0f) + ((res >> 4) & 0x0f0f0f0f);
    res = (res & 0x00ff00ff) + ((res >> 8) & 0x00ff00ff);
    return (res & 0x0000ffff) + ((res >> 16) & 0x0000ffff);
}

quint32 Bitops::generic_hweight16(quint16 w)
{
    quint16 res = (w & 0x5555) + ((w >> 1) & 0x5555);
    res = (res & 0x3333) + ((res >> 2) & 0x3333);
    res = (res & 0x0f0f) + ((res >> 4) & 0x0f0f);
    return (res & 0x00ff) + ((res >> 8) & 0x00ff);
}


quint32 Bitops::generic_hweight8(quint8 w)
{
    quint8 res = (w & 0x55) + ((w >> 1) & 0x55);
    res = (res & 0x33) + ((res >> 2) & 0x33);
    return (res & 0x0f) + ((res >> 4) & 0x0f);
}

