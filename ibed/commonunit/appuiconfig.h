#ifndef APPUICONFIG_H
#define APPUICONFIG_H

#include "commonunit_global.h"
#include <QString>
#include <QHash>

class QVariant;

class COMMONUNITSHARED_EXPORT AppUiConfig
{
public:
    typedef enum
    {
        Font_en,
        Font_zh,
        QssPath,
        LaunchQss,
        DefaultQss,

        Param_count,
    }Parameter;
public:
    static AppUiConfig &instance();
    bool initialize(void);
    QVariant value(Parameter param) const;
    void setValue(Parameter param, const QVariant &val);
    void save();

private:
    AppUiConfig();
    void setDefault(void);
    void loadValue(const QString &name);
    QHash<QString, QVariant> m_params;
};

#endif // APPUICONFIG_H
