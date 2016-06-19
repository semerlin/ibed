#ifndef QSSMODULE_H
#define QSSMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"
#include <QHash>

class QssLoader;

class MODULESSHARED_EXPORT QssModule : public BaseAppModule
{
public:
    static QssModule &instance(void);

public:
    bool load(const QVariant &val);
    void unload();
    bool canRunInThread() const;
    QStringList skins(void);


private:
    QssModule(const QString &name);
    ~QssModule();

private:
    QssLoader *m_loader;
    QHash<QString, QString> m_skins;  //shortcut name first
};

#endif // QSSMODULE_H
