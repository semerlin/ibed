#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainTopWidget;
class MainBottomWidget;
class BaseInfoWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onTopWidgetButtonClick(int id);
    void onBottomWidgetButtonClick(int id);

private:
    Ui::MainWidget *ui;
    MainTopWidget *m_topWidget;
    MainBottomWidget *m_bottomWidget;
    BaseInfoWidget *m_baseInfoWidget;
};

#endif // MAINWIDGET_H
