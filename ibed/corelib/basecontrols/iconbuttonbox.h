#ifndef ICONBUTTONBOX_H
#define ICONBUTTONBOX_H

#include "basecontrols_global.h"
#include "basebuttonbox.h"

#include <QIcon>
#include <QHash>

class BASECONTROLSSHARED_EXPORT IconButtonBox : public BaseButtonBox
{
    Q_OBJECT

public:
    explicit IconButtonBox(QWidget *parent = 0);
    explicit IconButtonBox(Qt::Orientation orientation, QWidget *parent = 0);
    ~IconButtonBox();

public slots:
    void setButtonIcon(const QString &name, const QStringList &icons);
    void setButtonIcon(int id, const QStringList &icons);
    void changeToIcon(const QString &name, int num);
    void changeToIcon(int id, int num);
    void changeToIcon(const QString &name, const QIcon &icon);
    void changeToIcon(int id, const QIcon &icon);

private:
    QHash<QAbstractButton *, QStringList> m_icons;
};

#endif // ICONBUTTONBOX_H
