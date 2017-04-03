#ifndef APPUICONFIG_P_H
#define APPUICONFIG_P_H

#include "commonunit_global.h"
#include <QHash>
#include <QFontDatabase>
#include <QStringList>

class COMMONUNITSHARED_EXPORT AppUiConfigPrivate
{
public:
    void setDefault(void);
    void loadValue(const QString &name);

    inline QString getFontFamily(int id)
    {
        QStringList list = QFontDatabase::applicationFontFamilies(id);
        return list.at(0);
    }

public:
    QHash<QString, QVariant> m_params;
    QHash<QString, QString> m_fontFamily;
};

#endif // APPUICONFIG_P

