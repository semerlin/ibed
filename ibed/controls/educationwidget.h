#ifndef EDUCATIONWIDGET_H
#define EDUCATIONWIDGET_H

#include <QWidget>

namespace Ui {
class EducationWidget;
}

class EducationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWidget(QWidget *parent = 0);
    ~EducationWidget();

private:
    Ui::EducationWidget *ui;
};

#endif // EDUCATIONWIDGET_H
