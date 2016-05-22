#ifndef BASEAPPMODULE_H
#define BASEAPPMODULE_H

#include "framework_global.h"
#include "iappmodule.h"

class FRAMEWORKSHARED_EXPORT BaseAppModule : IAppModule
{
public:
    BaseAppModule();
    virtual ~BaseAppModule();

public:
    virtual bool load(const QVariant &extraVal = QVariant(QVariant::Invalid));
    virtual bool isLoaded() const;
    virtual void unload();
    virtual void reload();
    virtual QString name() const;
    virtual QString error() const;

private:
    QString m_name;
    QString m_error;
    bool m_isLoaded;
    QVariant m_val;
};

#endif // BASEAPPMODULE_H
