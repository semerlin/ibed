#ifndef APPLOGGER_H
#define APPLOGGER_H

#include "commonunit_global.h"
#include "log4qt/logger.h"

class COMMONUNITSHARED_EXPORT AppLogger 
{
public:
    static AppLogger &instance(void);
    void initialize(void);
    Log4Qt::Logger *log();

private:
    AppLogger();
};

#endif // APPLOGGER_H
