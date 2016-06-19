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

private:
    QString m_logConfig;
private:
    AppSetting();
    void setDefault();
};

#endif // APPSETTING_H
