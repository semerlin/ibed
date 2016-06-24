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
    QString qssPath(void) const;
    QString launchQss(void) const;
    QString defaultQss(void) const;

private:
    QString m_cnFont;
    QString m_enFont;
    QString m_defaultQss;
    QString m_launchQss;
    QString m_qssPath;

private:
    AppUiConfig();
    void setDefault(void);
};

#endif // APPUICONFIG_H
