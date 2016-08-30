#ifndef MEDIAMODULE_H
#define MEDIAMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class CAudioPlay;
class AudioIntensity;

class MODULESSHARED_EXPORT MediaModule : public BaseAppModule
{
    Q_OBJECT

public:
    MediaModule(const QString &name);
    ~MediaModule();

public:
    bool load(const QVariant &val);
    void unload();
    void init(void);

signals:
    void intensityChanged(int intensity);

public slots:
    void onPlay(const QString &name);
    void onPause(const QString &name);
    void onStop(const QString &name);

private:
    CAudioPlay *m_player;
    AudioIntensity *m_intensity;
};

#endif // MEDIAMODULE_H
