#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "controls_global.h"
#include <QWidget>
#include <QMap>

namespace Ui {
class MainWidget;
}

class MainTopWidget;
class MainBottomWidget;
class BaseInfoWidget;
class AdviseWidget;
class InOutWidget;
class EducationWidget;
class SettingWidget;

class CONTROLSSHARED_EXPORT MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onTopWidgetButtonClick(int id);
    void onBottomWidgetButtonClick(int id);

private:
    void connectBtnAndWidget(void);

private:
    Ui::MainWidget *ui;
    QWidget *m_lastWidget;
    MainTopWidget *m_topWidget;
    MainBottomWidget *m_bottomWidget;
    BaseInfoWidget *m_baseInfoWidget;
    AdviseWidget *m_adviseWidget;
    InOutWidget *m_inOutWidget;
    EducationWidget *m_educationWidget;
    SettingWidget *m_settingWidget;

private:
    QMap<int, QWidget *> m_btnWidgets;
};

#endif // MAINWIDGET_H
