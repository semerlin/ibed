#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H

#include "media_global.h"
#include "audioformat.h"

class MEDIASHARED_EXPORT AudioUtil
{
public:
    AudioUtil();

public:
    static AudioFormat format(const QString &name);
    static int time(const QString &name);
};

#endif // AUDIOUTIL_H
