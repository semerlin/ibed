#ifndef BASEAPPMODULE_H
#define BASEAPPMODULE_H

#include "framework_global.h"
#include "iappmodule.h"

class FRAMEWORKSHARED_EXPORT BaseAppModule : public IAppModule
{
public:
    explicit BaseAppModule(const QString &name = "NullModule");
    virtual ~BaseAppModule();

public:
    virtual bool load(const QVariant &extraVal = QVariant(QVariant::Invalid));
    virtual bool isLoaded() const;
    virtual void unload();
    virtual void reload();
    void setName(const QString &name);
    QString name() const;
    QString error() const;

private:
    QString m_name;
    QString m_error;
    bool m_isLoaded;
    QVariant m_val;
};

#endif // BASEAPPMODULE_H
