#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

private slots:
    void onPushButtonPress();
    void onPushButtonReleased();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
