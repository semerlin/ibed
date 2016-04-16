#ifndef APPLANCHER_H
#define APPLANCHER_H


class AppLancher
{
public:
    static AppLancher &instance(void);

public:
    int run(int argc, char **argv);

private:
    AppLancher();
};

#endif // APPLANCHER_H
