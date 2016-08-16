#ifndef EDUCATIONWIDGET_H
#define EDUCATIONWIDGET_H

#include <QWidget>
#include <QHash>

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

signals:
    void play(const QString &name);
    void pause(const QString &name);
    void stop(const QString &name);

private slots:
    void onItemClicked(MusicPlayListItem *item);
    void onCurrentItemChanged(MusicPlayListItem *current, MusicPlayListItem *previous);
    void onIconClicked(MusicPlayListItem *item, int index);
    void updateEducation(void);

private:
    Ui::EducationWidget *ui;
    int m_height;
    QHash<QString, QString> m_eduFiles; //name and path
    QFont m_font;
    QFont m_largeFont;
};

#endif // EDUCATIONWIDGET_H
