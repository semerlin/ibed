#ifndef QSSLOADER_H
#define QSSLOADER_H

#include "utility_global.h"
#include <QObject>

class QStringList;
class QWidget;

/**
 * @brief load qss file
 */
class UTILITYSHARED_EXPORT QssLoader
{
public:
    /**
     * @brief find all qss files under the certen path
     * @param path - The path that may contain qss files
     * @return qss file list
     */
    static QStringList findAllQss(const QString &path);

    /**
     * @brief load the assigned qss file
     * @param name - qss file name
     * @return load status
     */
    static bool loadQss(const QString &name);

    /**
     * @brief load the assigned qss file for a appoint widget
     * @param widget - widget need to change qss
     * @param name - qss file name
     * @return load status
     */
    static bool loadQss(QWidget *widget, const QString &name);
};

#endif // QSSLOADER_H
