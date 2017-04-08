/*****************************************************************************
**
**  Copyright (C) 2016-2017 HuangYang
**
**  This file is part of IBED
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as
**  published by the Free Software Foundation.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     bitops.cpp
**  @brief    bits option from linux kernel
**  @details  none
**  @author   linux kernel
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

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
    //这个计算方式是用的算法中的"分治法"
    //开始的数据是32组,这一行把相邻的位相加，数据就变成16个组，每组2位，
    //完全可以表示相加之后是有0，1或2个1
    quint32 res = (w & 0x55555555) + ((w >> 1) & 0x55555555);
    //现在数据是16组,这一行把相邻的组相加，数据就变成8个组，每组4位，
    res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
    //现在数据是8组,这一行把相邻的组相加，数据就变成4个组，每组8位，
    res = (res & 0x0f0f0f0f) + ((res >> 4) & 0x0f0f0f0f);
    //现在数据是4组,这一行把相邻的组相加，数据就变成2个组，每组16位，
    res = (res & 0x00ff00ff) + ((res >> 8) & 0x00ff00ff);
    //现在数据是2组,这一行把相邻的组相加，就计算出hamming weight
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

