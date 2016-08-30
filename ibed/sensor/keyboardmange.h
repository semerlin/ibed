#ifndef KEYBOARDMANGE_H
#define KEYBOARDMANGE_H

#include <QObject>
#include <QSet>
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
    void start(void);
    void stop(void);
    QList<quint8> pressedKeys(int index);
    QList<quint8> releasedKeys(int index);

signals:
//    void keyPressed(int id);
//    void keyReleased(int id);
    void keyStatusChanged(void);

private:
    void addKeyboard(Keyboard *keyboard);

private slots:
    void onMonitorKeys(void);

private:
    int m_fd;
    QTimer *m_monitor;
    QList<Keyboard *> m_keyboards;
//    QList<quint8> m_allKeyId;
};

#endif // KEYBOARD_H
