#ifndef KBDBACKLIGHT_H
#define KBDBACKLIGHT_H


class KbdBacklight
{
public:
    static KbdBacklight &instance(void);

public:
    void turnOnBKL(void);
    void turnOffBKL(void);

private:
    KbdBacklight();
    ~KbdBacklight();

private:
    int m_fd;
};

#endif // KBDBACKLIGHT_H
