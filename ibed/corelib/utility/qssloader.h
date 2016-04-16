/*************************************************
 * Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
 * File name:      // 文件名
 * Author:
 * Version:
 * Date: // 作者、版本及完成日期
 * Description:
 * // 用于详细说明此程序文件完成的主要功能，与其他模块
 * // 或函数的接口，输出值、取值范围、含义及参数间的控
 * // 制、顺序、独立或依赖等关系
 * Others:         // 其它内容的说明
 * Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
 * 1. ....
 * History:
 * // 修改历史记录列表，每条修改记录应包括修改日期、修改
 * // 者及修改内容简述
 * 1. Date:
 * Author:
 * Modification:
 *
 * 2. ...
*************************************************/
#ifndef QSSLOADER_H
#define QSSLOADER_H

#include "utility_global.h"
#include <QObject>

class QStringList;

/**
 * @brief load qss file,  加载qss文件，实现换肤功能
 */
class UTILITYSHARED_EXPORT QssLoader : public QObject
{
    Q_OBJECT

public:
    explicit QssLoader();

public:
    /**
     * @brief find all qss files under the certen path
     * @param path: The path that may contain qss files
     * @return
     */
    QStringList findAllQss(const QString &path);

    /**
     * @brief load the assigned qss file
     * @param name: qss file name
     * @return
     */
    bool loadQss(const QString &name);

    /**
     * @brief current active qss style
     * @return
     */
    inline QString activeQss(void) const
    {
        return m_curQss;
    }

signals:
    void qssChanged(const QString &name);

private:
    QString m_curQss;

};

#endif // QSSLOADER_H
