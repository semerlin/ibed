#ifndef APPSETTING_H
#define APPSETTING_H

#include "commonunit_global.h"
#include <QVariant>

class AppSettingPrivate;

/**
 * @brief application global settings
 */
class COMMONUNITSHARED_EXPORT AppSetting
{
public:
    typedef enum
    {
        DeviceNum,

        LogConfig,
        UiConfig,
        ServerConfig,
        NetConfig,
        EduAudioPath,
        DriverConfig,

        Brightness,
        Sound,
        TurnOffTime,

        ModbusPort,


        Param_Count,
    }Parameter;

public:
    static AppSetting &instance(void);

    /**
     * @brief initialize application settings
     * @return
     */
    bool initialize(void);

    /**
     * @brief get parameter value
     * @param param - parameter enum name
     * @return parameter value
     */
    QVariant value(Parameter param) const;

    /**
     * @brief set parameter value
     * @param param - parameter enum name
     * @param val - parameter value
     */
    void setValue(Parameter param, const QVariant &val);

    /**
     * @brief save application settings to ini file
     */
    void save(void);

private:
    AppSetting();
    ~AppSetting();
    AppSettingPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(AppSetting)
};

#endif // APPSETTING_H
