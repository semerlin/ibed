#ifndef FORMULA_H
#define FORMULA_H

#include "utility_global.h"
#include <QObject>

class QRect;

class UTILITYSHARED_EXPORT Formula
{
public:
    Formula();

public:
    static QRect rectInRectPosition(const QRect &src, const QRect &dest, Qt::AlignmentFlag flag);
};

#endif // FORMULA_H
