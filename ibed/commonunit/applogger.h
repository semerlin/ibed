#ifndef APPLOGGER_H
#define APPLOGGER_H

#include "commonunit_global.h"
#include "log4qt/logger.h"

/**
 * @brief application common log
 */
class COMMONUNITSHARED_EXPORT AppLogger 
{
public:
    static AppLogger &instance(void);

    /**
     * @brief initialize application log environment
     * @return
     */
    bool initialize(void);

    /**
     * @brief get application log handler
     * @return
     */
    Log4Qt::Logger *log();

private:
    AppLogger();
};

#endif // APPLOGGER_H
