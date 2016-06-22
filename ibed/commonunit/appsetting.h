#ifndef APPSETTING_H
#define APPSETTING_H

#include "commonunit_global.h"
#include <QObject>

class COMMONUNITSHARED_EXPORT AppSetting : public QObject
{
    Q_OBJECT
public:
    static AppSetting &instance(void);
    bool initialize(void);
    QString logConfig(void) const;
    QString uiConfig(void) const;

private:
    QString m_logConfig;
    QString m_uiConfig;

private:
    AppSetting();
    void setDefault();
};

#endif // APPSETTING_H
