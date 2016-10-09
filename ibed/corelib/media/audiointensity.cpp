#include <QTimer>
#include <QMutex>
#include <QVector>
#include "audiointensitycalc.h"
#include "coveragecircularqueue.h"
#include "audiointensity.h"
#include "log4qt/logger.h"

LOG4QT_DECLARE_STATIC_LOGGER(log, Audio)


AudioIntensity::AudioIntensity() :
    m_intensity(0),
    m_isMonitoring(false),
    m_handle(NULL),
    m_params(NULL),
    m_mutex(new QMutex),
    m_intensityCalc(new AudioIntensityCalc),
    m_enableMonitor(false)
{
    m_frames = 128;
    /* 2 bytes/sample, 2 channels */
    m_tmpData = (char *)malloc(m_frames * 4);

    connect(m_intensityCalc, SIGNAL(intensityChanged(int)), this, SLOT(onIntensityChanged(int)), Qt::QueuedConnection);
}

AudioIntensity::~AudioIntensity()
{
    stopMonitor();
    free(m_tmpData);

    delete m_intensityCalc;
}

bool AudioIntensity::initMonitor()
{
    QMutexLocker locker(m_mutex);

    unsigned int val;
    int dir;

    /* Open PCM device for recording (capture). */
    if(snd_pcm_open(&m_handle, "default", SND_PCM_STREAM_CAPTURE, 0) < 0)
    {
        log()->info("open pcm failed!");
        return false;
    }

    /* Allocate a hardware parameters object. */
    if(snd_pcm_hw_params_malloc(&m_params) < 0)
    {
        log()->info("alloc param failed!");
        return false;
    }

    /* Fill it in with default values. */
    if(snd_pcm_hw_params_any(m_handle, m_params) < 0)
    {
        log()->info("clear param data failed!");
        return false;
    }

    /* Set the desired hardware parameters. */
    /* Interleaved mode */
    if(snd_pcm_hw_params_set_access(m_handle, m_params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
    {
        log()->info("set pcm access to interleaved failed!");
        return false;
    }
    /* Signed 16-bit little-endian format */
    if(snd_pcm_hw_params_set_format(m_handle, m_params, SND_PCM_FORMAT_S16_LE) < 0)
    {
        log()->info("set pcm fotmat to s16_le failed!");
        return false;
    }

    /* Two channels (stereo) */
    if(snd_pcm_hw_params_set_channels(m_handle, m_params, 2) < 0)
    {
        log()->info("set record channel failed!");
        return false;
    }

    /* 8000 samples/second */
    val = 8000;
    if(snd_pcm_hw_params_set_rate_near(m_handle, m_params,  &val, &dir) < 0)
    {
        log()->info("set rate to 8000 failed!");
        return false;
    }

    /* Set period size to 128 frames. */
    if(snd_pcm_hw_params_set_period_size_near(m_handle,  m_params, &m_frames, &dir) < 0)
    {
        log()->info("set period size to 128 frames failed");
        return false;
    }

    /* Write the parameters to the driver */
    if(snd_pcm_hw_params(m_handle, m_params) < 0)
    {
        log()->info("write parameter to the driver failed!");
        return false;
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(m_params,  &m_frames, &dir);

    return true;
}


void AudioIntensity::startMonitor()
{
    if(!isRunning())
        start();

    m_enableMonitor = true;
    m_isMonitoring = true;
}


void AudioIntensity::stopMonitor()
{
    m_enableMonitor = false;
    m_mutex->lock();
    if(m_handle != NULL)
    {
        snd_pcm_drop(m_handle);
        snd_pcm_close(m_handle);
        m_handle = NULL;
    }
    m_mutex->unlock();
    m_isMonitoring = false;
}

bool AudioIntensity::isMonitoring() const
{
    return m_isMonitoring;
}

int AudioIntensity::intensity() const
{
    return m_intensity;
}

void AudioIntensity::run()
{
    while(1)
    {
        if(m_enableMonitor)
        {
            QByteArray data;
            m_mutex->lock();
            if(m_handle != NULL)
            {
                snd_pcm_drop(m_handle);
                snd_pcm_prepare(m_handle);
                for(int i = 0; i < 32; i++)
                {
                    if(!m_enableMonitor)
                        break;

                    long rc = snd_pcm_readi(m_handle, m_tmpData, m_frames);
                    if(rc == -EPIPE)
                    {
                        /* EPIPE means overrun */
                        snd_pcm_prepare(m_handle);
                    }
                    else if(rc == -EBADFD)
                    {

                    }
                    else if(rc == -ESTRPIPE)
                    {

                    }
                    else
                    {
                        for(int i = 0; i < rc; ++i)
                            data.append(m_tmpData[i]);
                    }
                }
            }

            m_mutex->unlock();

            m_intensityCalc->getIntensity(data);
        }

        ::usleep(2000000);
    }
}

void AudioIntensity::onIntensityChanged(int intensity)
{
    if(intensity != m_intensity)
    {
        m_intensity = intensity;
//        log()->debug(QString("audio intensity is: %1 dB").arg(m_intensity));
        emit intensityChanged(m_intensity);
    }
}

