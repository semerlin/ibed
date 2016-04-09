#ifndef QSSLOADER_H
#define QSSLOADER_H

#include "utility_global.h"
#include <QObject>

class QStringList;

/**
 * @brief 加载qss文件，实现换肤功能
 */
class UTILITYSHARED_EXPORT QssLoader : public QObject
{
    Q_OBJECT

public:
    explicit qssloader();

public:
    /**
     * @brief 枚举指定路径下面所有的qss文件
     * @param path 需要寻找的路径
     * @return
     */
    QStringList findAllQss(const QString &path);

    /**
     * @brief 加载制定的qss文件
     * @param name qss文件名
     * @return
     */
    bool loadQss(const QString &name);

signals:
    void qssChanged(const QString &name);

};

#endif // QSSLOADER_H
