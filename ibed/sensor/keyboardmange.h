#ifndef KEYBOARDMANGE_H
#define KEYBOARDMANGE_H

#include <QObject>
#include <QHash>
#include <QList>

class Keyboard;
class QTimer;

class KeyboardMange : public QObject
{
    Q_OBJECT

public:
    KeyboardMange();
    ~KeyboardMange();

public:
    int init(void);

signals:
    void keyPressed(int id);
    void keyReleased(int id);

private:
    void addKeyboard(Keyboard *keyboard);

private slots:
    void onMonitorKeys(void);

private:
    int m_fd;
    QTimer *m_monitor;
    QList<Keyboard *> m_keyboards;
    QList<quint8> m_allKeyId;
};

#endif // KEYBOARD_H
