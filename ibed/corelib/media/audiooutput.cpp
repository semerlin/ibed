#include "audiooutput.h"
#include <alsa/asoundlib.h>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#define ALSA_PCM_NEW_HW_PARAMS_API


using namespace Audio;

#define MIN_NOTIFY_INTERVAL (100)



AudioOutput::AudioOutput(const AudioFormat &format, QObject *parent) :
    QObject(parent),
    m_format(format),
    m_error(NoError),
    m_state(IdleState),
    m_notifyInterval(MIN_NOTIFY_INTERVAL),
    m_pcm(NULL),
    m_pcmParams(NULL),
    m_frames(32),
    m_device(NULL),
    m_thread(new QThread),
    m_canPause(false),
    m_mutex(new QMutex),
    m_private(new AudioOutputPrivate(this))
{
    qRegisterMetaType<Audio::Error>("Audio::Error");
    qRegisterMetaType<Audio::State>("Audio::State");
    qRegisterMetaType<Audio::Mode>("Audio::Mode");

    m_private->moveToThread(m_thread);
    connect(this, SIGNAL(started()), m_private, SLOT(start()), Qt::QueuedConnection);
    connect(m_private, SIGNAL(finished(Audio::Error)),
            this, SLOT(onFinished(Audio::Error)), Qt::QueuedConnection);

}

AudioOutput::~AudioOutput()
{
    stop();
    delete m_thread;
    delete m_private;
}

Audio::Error AudioOutput::error() const
{
    return m_error;
}

AudioFormat AudioOutput::format() const
{
    return m_format;
}

int AudioOutput::notifyInterval() const
{
    return m_notifyInterval;
}

qint64 AudioOutput::processedUSecs() const
{
    return 0;
}

Audio::State AudioOutput::state() const
{
    return m_state;
}

void AudioOutput::setAudioFormat(const AudioFormat &format)
{
    m_format = format;
}

void AudioOutput::init()
{
    QMutexLocker locker(m_mutex);

    if(snd_pcm_open(&m_pcm, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
    {
        m_error = OpenError;
        return ;
    }

    if(snd_pcm_hw_params_malloc(&m_pcmParams) < 0)
    {
        m_error = OpenError;
        return ;
    }

    if(snd_pcm_hw_params_any(m_pcm, m_pcmParams) < 0)
    {
        m_error = OpenError;
        return ;
    }

    if(snd_pcm_hw_params_set_access(m_pcm, m_pcmParams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
    {
        m_error = OpenError;
        return ;
    }


    //閲囨牱浣嶆暟
    switch(m_format.sampleBit())
    {
    case AudioFormat::Bit_8:
        if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_U8) < 0)
        {
            m_error = OpenError;
            return ;
        }
        break;
    case AudioFormat::Bit_16:
        switch(m_format.byteOrder())
        {
        case AudioFormat::LittleEndian:
            if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S16_LE) < 0)
            {
                m_error = OpenError;
                return ;
            }
            break;
        case AudioFormat::BigEndian:
            if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S16_BE) < 0)
            {
                m_error = OpenError;
                return ;
            }
            break;
        default:
            if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S16_LE) < 0)
            {
                m_error = OpenError;
                return ;
            }
            break;
        }

        break;
    case AudioFormat::Bit_24:
        switch(m_format.byteOrder())
        {
        case AudioFormat::LittleEndian:
            if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S24_LE) < 0)
            {
                m_error = OpenError;
                return ;
            }
            break;
        case AudioFormat::BigEndian:
            if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S24_BE) < 0)
            {
                m_error = OpenError;
                return ;
            }
            break;
        default:
            if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S24_LE) < 0)
            {
                m_error = OpenError;
                return ;
            }
            break;
        }
        break;
    default:
        if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S16_LE) < 0)
        {
            m_error = OpenError;
            return ;
        }
        break;
    }

    if(snd_pcm_hw_params_set_channels(m_pcm, m_pcmParams, m_format.channelCount()) < 0)
    {
        m_error = OpenError;
        return ;
    }


    int dir;
    unsigned int val = m_format.sampleRate();
    if(snd_pcm_hw_params_set_rate_near(m_pcm, m_pcmParams, &val, &dir) < 0)
    {
        m_error = OpenError;
        return ;
    }

    /* Set period size to 32 frames. */
    m_frames = 32;
    if(snd_pcm_hw_params_set_period_size_near(m_pcm, m_pcmParams, &m_frames, 0) < 0)
    {
        m_error = OpenError;
        return ;
    }


    if(snd_pcm_hw_params(m_pcm, m_pcmParams) < 0)
    {
        m_error = OpenError;
        return ;
    }

    m_canPause = snd_pcm_hw_params_can_pause(m_pcmParams);
}

void AudioOutput::start(QIODevice *device)
{
    if(m_state != IdleState)
        return ;

    init();

    m_device = device;

    m_thread->start();

    m_state = ActiveState;

    emit stateChanged(IdleState, ActiveState);
    emit started();
}

void AudioOutput::setNotifyInterval(int ms)
{
    Q_UNUSED(ms)
}

void AudioOutput::resume()
{
    m_mutex->lock();
    if(m_pcm != NULL)
    {
        if(m_state == SuspendedState)
        {
            if(m_canPause)
            {
                snd_pcm_pause(m_pcm, 0);
            }
            else
            {
                snd_pcm_prepare(m_pcm);
            }
            m_mutex->unlock();
            m_state = ActiveState;
            emit stateChanged(SuspendedState, ActiveState);
        }
        else
            m_mutex->unlock();
    }
    else
        m_mutex->unlock();
}

void AudioOutput::stop()
{
    m_mutex->lock();
    if(m_pcm != NULL)
    {
        snd_pcm_drop(m_pcm);
        snd_pcm_close(m_pcm);
        m_pcm = NULL;

//        if(m_device->isOpen())
//            m_device->close();

        m_mutex->unlock();
        State prevState = m_state;
        m_state = IdleState;
        emit stateChanged(prevState, m_state);
    }
    else
        m_mutex->unlock();
}

void AudioOutput::suspend()
{
    m_mutex->lock();
    if(m_pcm != NULL)
    {
        if(m_state == ActiveState)
        {
            if(m_canPause)
            {
                snd_pcm_pause(m_pcm, 1);
            }
            else
            {
                snd_pcm_drop(m_pcm);
            }
            m_mutex->unlock();
            m_state = SuspendedState;
            emit stateChanged(ActiveState, SuspendedState);
        }
        else
            m_mutex->unlock();
    }
    else
        m_mutex->unlock();
}

void AudioOutput::onFinished(Audio::Error error)
{
    Q_UNUSED(error)

    m_error = error;

    m_mutex->lock();
    if(m_pcm != NULL)
    {
        snd_pcm_drop(m_pcm);
        snd_pcm_close(m_pcm);
        m_pcm = NULL;
    }
    m_mutex->unlock();

//    if(m_device->isOpen())
//        m_device->close();

    State prevState = m_state;
    m_state = IdleState;
    emit stateChanged(prevState, m_state);
}




//#include "audiooutput.moc"





void AudioOutputPrivate::start()
{
    int ret = 0;
    //calculate period size
    int periodsize = m_audio->m_frames * m_audio->m_format.channelCount() * m_audio->m_format.sampleBit() / 8;

    //check id device is opened
    if(!m_audio->m_device->isOpen())
    {
        //open device first
        if(!m_audio->m_device->open(QIODevice::ReadOnly))
        {
            emit finished(Audio::OpenError);
            return ;
        }
    }

    while(1)
    {
        QByteArray data = m_audio->m_device->read(periodsize);
        if(data.count() <= 0)
        {
            //error happend or reach file end
            //TODO catch error
//            error = m_audio->m_device->errorString();

            emit finished(Audio::NoError);
            break;
        }
        m_audio->m_mutex->lock();
        if(m_audio->m_pcm != NULL)
        {
            ret = snd_pcm_writei(m_audio->m_pcm, data.data(), m_audio->m_frames);
            if(ret < 0)
            {
                if(ret == -EPIPE)
                    ::snd_pcm_prepare(m_audio->m_pcm);
    //            else if(ret == -EBADFD)
    //            {
    //                //user stopped
    //                emit finished(Audio::IOError);
    //                break;
    //            }
                else
                {
                    m_audio->m_mutex->unlock();
                    break;
                }
            }
        }
        m_audio->m_mutex->unlock();
    }


}
