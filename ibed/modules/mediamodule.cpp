#include "AudioPlay.h"
#include "audiointensity.h"
#include "mediamodule.h"
#include <QFileInfo>

MediaModule::MediaModule(const QString &name) :
    BaseAppModule(name),
    m_intensity(new AudioIntensity)
{
    m_player = new CAudioPlay;

    connect(m_intensity, SIGNAL(intensityChanged(int)), this, SIGNAL(intensityChanged(int)));
}

MediaModule::~MediaModule()
{
    delete m_player;
    delete m_intensity;
}

bool MediaModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    return true;
}

void MediaModule::unload()
{

}

void MediaModule::init()
{
    m_intensity->startMonitor();
}

void MediaModule::onPlay(const QString &name)
{
    if(!m_player->isPlaying())
        m_player->AudioInit(name.toLatin1().constData());
    m_player->StartPlayLocal();
}

void MediaModule::onPause(const QString &name)
{
    Q_UNUSED(name)
    m_player->PausePlay();
}

void MediaModule::onStop(const QString &name)
{
    Q_UNUSED(name)
    m_player->StopPlay();
}
