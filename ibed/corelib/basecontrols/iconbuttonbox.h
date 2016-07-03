#ifndef ICONBUTTONBOX_H
#define ICONBUTTONBOX_H

#include "basecontrols_global.h"
#include "basebuttonbox.h"

#include <QIcon>
#include <QHash>
#include <QList>

class BASECONTROLSSHARED_EXPORT IconButtonBox : public BaseButtonBox
{
    Q_OBJECT

public:
    explicit IconButtonBox(QWidget *parent = 0);
    explicit IconButtonBox(Qt::Orientation orientation, QWidget *parent = 0);
    ~IconButtonBox();

public:
    bool addButtonIcon(const QString &name, const QIcon &icon);
    bool setButtonIcons(const QString &name, const QStringList &icons);
    bool setButtonIcons(int id, const QStringList &icons);
    bool setButtonIcons(const QString &name, const QList<QIcon> &icons);
    bool setButtonIcons(int id, const QList<QIcon> &icons);

public slots:
    void changeToIcon(const QString &name, int num);
    void changeToIcon(int id, int num);
    void changeToIcon(const QString &name, const QIcon &icon);
    void changeToIcon(int id, const QIcon &icon);
    void removeIcon(int id, int num);
    void removeIcon(const QString &name, int num);
    void clearIcons(void);

private:
    QHash<QAbstractButton *, QList<QIcon> > m_icons;
};

#endif // ICONBUTTONBOX_H
