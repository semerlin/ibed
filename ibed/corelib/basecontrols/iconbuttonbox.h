#ifndef ICONBUTTONBOX_H
#define ICONBUTTONBOX_H

#include "basecontrols_global.h"
#include "basebuttonbox.h"

#include <QIcon>
#include <QList>

class IconButtonBoxPrivate;

class BASECONTROLSSHARED_EXPORT IconButtonBox : public BaseButtonBox
{
    Q_OBJECT

public:
    explicit IconButtonBox(QWidget *parent = 0);
    explicit IconButtonBox(Qt::Orientation orientation, QWidget *parent = 0);
    ~IconButtonBox();

public:
    /**
     * @brief add icon to button
     * @param name - button name
     * @param icon - icon
     * @return trur or false
     */
    bool addButtonIcon(const QString &name, const QIcon &icon);

    /**
     * @brief set button icons
     * @param name - button name
     * @param icons - icon paths
     * @return true or false
     */
    bool setButtonIcons(const QString &name, const QStringList &icons);

    /**
     * @brief set button icons
     * @param id - button position
     * @param icons - icon paths
     * @return true or false
     */
    bool setButtonIcons(int id, const QStringList &icons);

    /**
     * @brief set button icons
     * @param name - button name
     * @param icons - icons
     * @return true or false
     */
    bool setButtonIcons(const QString &name, const QList<QIcon> &icons);

    /**
     * @brief set button icons
     * @param id - button position
     * @param icons - icons
     * @return true or false
     */
    bool setButtonIcons(int id, const QList<QIcon> &icons);

public slots:
    /**
     * @brief change button icon
     */
    void changeToIcon(const QString &name, int num);
    void changeToIcon(int id, int num);
    void changeToIcon(const QString &name, const QIcon &icon);
    void changeToIcon(int id, const QIcon &icon);

    /**
     * @brief remove button icon
     */
    void removeIcon(int id, int num);
    void removeIcon(const QString &name, int num);

    /**
     * @brief clear all button icons
     */
    void clearIcons(void);

private:
    IconButtonBoxPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(IconButtonBox)
};

#endif // ICONBUTTONBOX_H
