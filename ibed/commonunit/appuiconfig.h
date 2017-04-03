#ifndef APPUICONFIG_H
#define APPUICONFIG_H

#include "commonunit_global.h"
#include <QString>
#include <QHash>

class AppUiConfigPrivate;

/**
 * @brief application global ui configure
 */
class COMMONUNITSHARED_EXPORT AppUiConfig
{
public:
    typedef enum
    {
        SkinPath,
        LaunchQss,
        ApplicationQss,
        InoutEditColor,
        MusicSelectBackground,

        Param_count,
    }Parameter;

    typedef enum
    {
       Font_En,
       Font_Zh
    }AppFont;

public:
    static AppUiConfig &instance();

    /**
     * @brief initialize application ui environment
     * @return true - initalize success
     *         false - initialize failed
     *         in this version, we always return true
     */
    bool initialize(void);

    /**
     * @brief get parameter value
     * @param param - parameter enum name
     * @return
     */
    QVariant value(Parameter param) const;

    /**
     * @brief set parameter value
     * @param param - parameter name
     * @param val - parameter value
     */
    void setValue(Parameter param, const QVariant &val);

    /**
     * @brief save ui environment to ini file
     */
    void save();

    /**
     * @brief get font family name
     * @param font - font enum name
     * @return font family name
     */
    QString fontFamily(AppFont font) const;

private:
    AppUiConfig();
    ~AppUiConfig();
    AppUiConfigPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(AppUiConfig)
};

#endif // APPUICONFIG_H
