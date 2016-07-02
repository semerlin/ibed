#ifndef APPSETTING_H
#define APPSETTING_H

#include "commonunit_global.h"
#include <QObject>

class COMMONUNITSHARED_EXPORT AppSetting : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        LogConfig,
        UiConfig,

        Param_Count,
    }Parameter;
public:
    static AppSetting &instance(void);
    bool initialize(void);
    QVariant value(Parameter param) const;
    void setValue(Parameter param, const QVariant &val);
    QString logConfig(void) const;
    QString uiConfig(void) const;

private:
    QString m_logConfig;
    QString m_uiConfig;

private:
    AppSetting();
    void setDefault();
    void loadParam(const QString &name);
};

#endif // APPSETTING_H
