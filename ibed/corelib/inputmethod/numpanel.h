#ifndef NUMPANEL_H
#define NUMPANEL_H

#include "inputmethod_global.h"
#include <QWidget>

#ifdef TARGET_IMX

namespace Ui {
class NumPanel;
}

class QSignalMapper;
class NumIPMethod;

class INPUTMETHODSHARED_EXPORT NumPanel : public QWidget
{
    Q_OBJECT

public:
    explicit NumPanel(NumIPMethod *method, QWidget *parent = 0);
    ~NumPanel();

signals:
    void keyPressed(int key);

protected:
    bool event(QEvent *e);

private slots:
    void onFocusChanged(QWidget *old, QWidget *now);

private:
    Ui::NumPanel *ui;
    QSignalMapper *m_mapper;
    NumIPMethod *m_method;
    QWidget *m_lastFocusWidget;
};
#endif

#endif // NUMPANEL_H
