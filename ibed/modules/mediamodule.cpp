#include "fileaudioout.h"
#include "audiointensity.h"
#include "mediamodule.h"
#include <QFileInfo>
#include <QTimer>

MediaModule::MediaModule(const QString &name) :
    BaseAppModule(name)

{

}

MediaModule::~MediaModule()
{
    delete m_player;
    delete m_intensity;
}

bool MediaModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    m_player = new FileAudioOut;
    m_intensity = new AudioIntensity;
    m_curPlay = "";

    connect(m_intensity, SIGNAL(intensityChanged(int)), this, SIGNAL(intensityChanged(int)));

    return true;
}

void MediaModule::unload()
{

}

void MediaModule::init()
{
    m_intensity->initMonitor();
    m_intensity->startMonitor();
}

void MediaModule::startMonitor()
{
    m_intensity->initMonitor();
    m_intensity->startMonitor();
}

void MediaModule::stopMonitor()
{
    m_intensity->stopMonitor();
}

void MediaModule::onPlay(const QString &name)
{
    if(m_curPlay == name)
    {
        if(m_player->state() == Audio::SuspendedState)
            m_player->resume();
        else if(m_player->state() == Audio::IdleState)
            m_player->play();
    }
    else
    {
        if(m_player->state() != Audio::IdleState)
            m_player->stop();

        m_player->setName(name);
        m_curPlay = name;
        QTimer::singleShot(200, this, SLOT(playTimeOut()));
    }
}

void MediaModule::onPause(const QString &name)
{
    Q_UNUSED(name)

    m_player->suspend();
}

void MediaModule::onStop(const QString &name)
{
    Q_UNUSED(name)
    if(m_player->state() != Audio::IdleState)
        m_player->stop();
}

void MediaModule::playTimeOut()
{
    m_player->play();
}


