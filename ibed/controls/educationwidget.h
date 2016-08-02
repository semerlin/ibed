#ifndef EDUCATIONWIDGET_H
#define EDUCATIONWIDGET_H

#include <QWidget>

namespace Ui {
class EducationWidget;
}

class MusicPlayListItem;

class EducationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWidget(QWidget *parent = 0);
    ~EducationWidget();

private slots:
    void onItemClicked(MusicPlayListItem *item);
    void onCurrentItemChanged(MusicPlayListItem *current, MusicPlayListItem *previous);
    void onIconClicked(MusicPlayListItem *item, int index);

private:
    Ui::EducationWidget *ui;
    int m_height;
};

#endif // EDUCATIONWIDGET_H
