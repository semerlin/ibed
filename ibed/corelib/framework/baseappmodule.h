#ifndef BASEAPPMODULE_H
#define BASEAPPMODULE_H

#include "framework_global.h"
#include "iappmodule.h"
#include <QObject>

class FRAMEWORKSHARED_EXPORT BaseAppModule : public QObject, public IAppModule
{
    Q_OBJECT
public:
    explicit BaseAppModule(const QString &name = "empty");
    virtual ~BaseAppModule(){}

public:
    virtual bool load(const QVariant &extraVal = QVariant(QVariant::Invalid)) = 0;
    virtual bool isLoaded() const;
    virtual void unload() = 0;
    virtual bool reload();
    void setName(const QString &name);
    QString name() const;
    QString error() const;

signals:
    void message(const QString &msg);

protected:
    bool m_isLoaded;
    QString m_error;

private:
    QString m_name;
    QVariant m_val;
};

#endif // BASEAPPMODULE_H
