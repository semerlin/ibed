#ifndef MAINTOPWIDGET_H
#define MAINTOPWIDGET_H

#include <QWidget>


namespace Ui {
class MainTopWidget;
}

class QPushButton;

class MainTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTopWidget(QWidget *parent = 0);
    ~MainTopWidget();

public:
    QPushButton *button(int id) const;
    const QList<QPushButton *> buttons() const;
private:
    void lowlightButtons(void);

signals:
    void buttonClicked(int id);

private slots:
    void onButtonClicked(int id);

private:
    Ui::MainTopWidget *ui;
};

#endif // MAINTOPWIDGET_H
