#include "util.h"
#include <QString>

Util &Util::instance()
{
    static Util m_util;
    return m_util;
}

QString Util::fileName(const QString &name)
{
    int dot = name.lastIndexOf('.');
    if(dot != -1)
        return name.left(dot);
    else
        return name;
}

QString Util::fileSuffix(const QString &name)
{
    int dot = name.lastIndexOf('.');
    if(dot != -1)
        return name.right(dot);
    else
        return QString("");
}

Util::Util()
{
}

