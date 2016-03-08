#ifndef CRYPTOGRAM_H
#define CRYPTOGRAM_H

#include "commonunit_global.h"

#include <QString>

class COMMONUNITSHARED_EXPORT Cryptogram
{
public:
    static Cryptogram &instance(void);

public:
    QString encrypt(const QString &str, quint64 key);
    QString decrypt(const QString &str, quint64 key);

private:
    explicit Cryptogram();
};

#endif // CRYPTOGRAM_H
