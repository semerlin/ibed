#ifndef APPUICONFIG_H
#define APPUICONFIG_H

#include "commonunit_global.h"
#include <QString>

class COMMONUNITSHARED_EXPORT AppUiConfig
{
public:
    static AppUiConfig &instance();
    bool initialize(void);
    QString font(void) const;

private:
    QString m_font;

private:
    AppUiConfig();
    void setDefault(void);
};

#endif // APPUICONFIG_H
