#ifndef ICONPUSHBUTTON_H
#define ICONPUSHBUTTON_H

#include "basecontrols_global.h"
#include <QPushButton>

class IconPushButtonPrivate;

class BASECONTROLSSHARED_EXPORT IconPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconPushButton(QWidget *parent = 0);
    virtual ~IconPushButton();

public slots:
    /**
     * @brief add icon to pushbutton
     */
    void addIcon(const QIcon &icon);
    void addIcon(const QString &icon);

    /**
     * @brief set pushbutton icons
     */
    void setIcons(const QList<QIcon> &icons);
    void setIcons(const QStringList &icons);

    /**
     * @brief change button icon
     * @param id - icon position
     */
    void changeToIcon(int id);

    /**
     * @brief remove button icon
     * @param id - icon position
     */
    void removeIcon(int id);

    /**
     * @brief clear pushbutton icons
     */
    void clearIcons(void);

private:
    IconPushButtonPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(IconPushButton)
};

#endif // ICONPUSHBUTTON_H
