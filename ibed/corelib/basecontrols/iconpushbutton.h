#ifndef ICONPUSHBUTTON_H
#define ICONPUSHBUTTON_H

#include <QPushButton>

class IconPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconPushButton(QWidget *parent = 0);
    virtual ~IconPushButton() {}

public slots:
    void addIcon(const QIcon &icon);
    void addIcon(const QString &icon);
    void setIcons(const QList<QIcon> &icons);
    void setIcons(const QStringList &icons);
    void changeToIcon(int id);
    void removeIcon(int id);
    void clearIcons(void);

private:
    QList<QIcon> m_icons;
};

#endif // ICONPUSHBUTTON_H
