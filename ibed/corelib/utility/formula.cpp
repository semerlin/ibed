#include <QRect>
#include "formula.h"

Formula::Formula()
{

}

QRect Formula::rectInRectPosition(const QRect &src, const QRect &dest, Qt::AlignmentFlag flag)
{
    if(src.contains(dest))
        return dest;

    int top, left;
    if(flag & Qt::AlignLeft)
        left = dest.left();

    if(flag & Qt::AlignTop)
        top = dest.top();

    if(flag & Qt::AlignRight)
        left = dest.right() - src.width();

    if(flag & Qt::AlignBottom)
        top = dest.bottom() - src.height();

    if(flag & Qt::AlignHCenter)
        left = dest.left() + (dest.width() - src.width()) / 2;

    if(flag & Qt::AlignVCenter)
        top = dest.top() + (dest.height() - src.height()) / 2;

    return QRect(left, top, src.width(), src.height());
}

