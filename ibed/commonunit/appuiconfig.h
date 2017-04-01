#ifndef APPUICONFIG_H
#define APPUICONFIG_H

#include "commonunit_global.h"
#include <QString>
#include <QHash>

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
    void setDefault(void);
    void loadValue(const QString &name);
    QString getFontFamily(int id);
    QHash<QString, QVariant> m_params;
    QHash<AppFont, QString> m_fontFamily;
};

#endif // APPUICONFIG_H
