#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>

class PCF8574;

class Keyboard
{
public:
    explicit Keyboard(const QString &port, quint8 address);
    ~Keyboard();

public:
    quint8 value(void) const;
    QList<quint8> pressedKeys(void) const;
    QList<quint8> releasedKeys(void) const;
private:
    PCF8574 *m_pcf;
    quint8 m_address;
};

#endif // KEYBOARD_H
