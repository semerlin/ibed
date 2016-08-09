#ifndef APPSETTING_H
#define APPSETTING_H

#include "commonunit_global.h"
#include <QObject>
#include <QHash>
#include <QVariant>

class COMMONUNITSHARED_EXPORT AppSetting : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        LogConfig,
        UiConfig,
        ServerConfig,
        NetConfig,


        Param_Count,
    }Parameter;
public:
    static AppSetting &instance(void);
    bool initialize(void);
    QVariant value(Parameter param) const;
    void setValue(Parameter param, const QVariant &val);

private:
    AppSetting();
    void setDefault();
    QHash<QString, QVariant> m_params;
};

#endif // APPSETTING_H
