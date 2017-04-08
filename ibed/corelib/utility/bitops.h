#ifndef BITOPS_H
#define BITOPS_H

#include "utility_global.h"

class UTILITYSHARED_EXPORT Bitops
{
public:
    /**
     * @brief find first signed position, from lower positon to higher position
     * @param x - value need to find
     * @return position
     */
    static int generic_ffs(int x);

     /**
     * @brief find last signed position, from lower positon to higher position
     * @param x - value need to find
     * @return position
     */
    static int generic_fls(int x);

    /**
     * @brief calculate 32 bits hamming weight
     * @param w - value need to calculate
     * @return singed bits in w
     */
    static quint32 generic_hweight32(quint32 w);

    /**
     * @brief calculate 16 bits hamming weight
     * @param w - value need to calculate
     * @return singed bits in w
     */
    static quint32 generic_hweight16(quint16 w);

    /**
     * @brief calculate 8 bits hamming weight
     * @param w - value need to calculate
     * @return singed bits in w
     */
    static quint32 generic_hweight8(quint8 w);
};

#endif // BITOPS_H




