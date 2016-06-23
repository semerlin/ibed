#ifndef APPUICONFIG_H
#define APPUICONFIG_H

#include "commonunit_global.h"
#include <QString>

class COMMONUNITSHARED_EXPORT AppUiConfig
{
public:
    static AppUiConfig &instance();
    bool initialize(void);
    QString enFont(void) const;
    QString cnFont(void) const;

private:
    QString m_cnFont;
    QString m_enFont;

private:
    AppUiConfig();
    void setDefault(void);
};

#endif // APPUICONFIG_H
