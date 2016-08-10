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

public slots:
    void setStatusText(const QString &text);

signals:
    void reconnect(const QString &ip, quint16 port);
    void brightnessChanged(int value);
    void turnOffTimeChanged(int value);

private slots:
    void onPushButtonPress();
    void onPushButtonReleased();


    void on_pushButtonSave_clicked();

private:
    Ui::SettingWidget *ui;
    void saveLocal(void);
    void saveServer(void);
    void saveScreen(void);
};

#endif // SETTINGWIDGET_H
