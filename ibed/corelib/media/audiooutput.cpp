#include "audiooutput.h"
#include <alsa/asoundlib.h>
#include <QThread>

/* wav文件头结构体 */
struct WAV_HEADER
{
    char riff[4]; //"RIFF"标志
    int dataSize; //从下个地址到文件尾的总字节数
    char wave[4]; //"WAVE"
    char fmt[4]; //"fmt"
    int transition; //过渡字节
    short type; //编码格式(10H: 线性pcm)
    short channels; //声道数
    int sampleRate ; //采样频率
    int bytesPerSec; //每秒采样的字节数
    short adjustment; //数据快调整数(按字节算),通道数＊每样本数据位/8
    short bitsPerSample; //每次采样位数
    char data[4]; //”data“
    int audioSize; //音频数据的大小
};

using namespace Audio;

#define MIN_NOTIFY_INTERVAL (100)


AudioOutput::AudioOutput(QObject *parent) :
    QObject(parent),
    m_format(AudioFormat()),
    m_error(NoError),
    m_state(IdleState),
    m_notifyInterval(MIN_NOTIFY_INTERVAL),
    m_pcm(NULL),
    m_pcmParams(NULL),
    m_frames(32),
    m_device(NULL),
    m_thread(new QThread),
    m_canPause(false),
    m_private(new AudioOutputPrivate(this))
{
    m_private->moveToThread(m_thread);
    connect(this, SIGNAL(started()), m_private, SLOT(start()));
}

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
    m_private(new AudioOutputPrivate(this))
{
    m_private->moveToThread(m_thread);
    connect(this, SIGNAL(started()), m_private, SLOT(start()));
}

AudioOutput::~AudioOutput()
{

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

Audio::State AudioOutput::state() const
{
    return m_state;
}

void AudioOutput::setAudioFormat(const AudioFormat &format)
{
    m_format = format;
}


void AudioOutput::start(QIODevice *device)
{
    if(m_state != IdleState)
        return ;

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

    //采样位数
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
        if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S16_LE) < 0)
        {
            m_error = OpenError;
            return ;
        }
        break;
    case AudioFormat::Bit_24:
        if(snd_pcm_hw_params_set_format(m_pcm, m_pcmParams, SND_PCM_FORMAT_S24_LE) < 0)
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
    snd_pcm_uframes_t periodsize = m_frames * m_format.channelCount();
    if(snd_pcm_hw_params_set_buffer_size_near(m_pcm, m_pcmParams, &periodsize) < 0)
    {
        m_error = OpenError;
        return ;
    }

    periodsize /= 2;

    if(snd_pcm_hw_params_set_period_size_near(m_pcm, m_pcmParams, &periodsize, 0) < 0)
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

    m_device = device;

    m_thread->start();

    emit started();
}

void AudioOutput::setNotifyInterval(int ms)
{

}

void AudioOutput::resume()
{
//    if(snd_pcm_state(m_pcm) == SND_PCM_STATE_SUSPENDED)
//    {
//        while(snd_pcm_resume(m_pcm) == -EAGAIN)
//            sleep(1);
//    }

    if(m_canPause)
    {
        snd_pcm_pause(m_pcm, 0);
    }
    else
    {
        snd_pcm_prepare(m_pcm);
    }
}

void AudioOutput::stop()
{
    snd_pcm_drop(m_pcm);
}

void AudioOutput::suspend()
{
    if(m_canPause)
    {
        snd_pcm_pause(m_pcm, 1);
    }
    else
    {
        snd_pcm_drop(m_pcm);
    }
}


//#include "audiooutput.moc"





void AudioOutputPrivate::start()
{

    while(1)
    {
        QByteArray data = m_audio->m_device->read(512);
        snd_pcm_writei(m_audio->m_pcm, data.data(), 512);
    }
//    while(m_audio->m_device->read(512))
//    while((fread(buffer, 1, size, fp) != 0) && (m_bLocal == true))
//    {
//        if(snd_pcm_state(handle) != SND_PCM_STATE_DISCONNECTED)
//        {
//            int ret;

//            while((ret = snd_pcm_writei(handle, buffer, size)) < 0)
//            {
//                if(ret == -EPIPE)
//                {
//                    /* EPIPE means underrun */
//                    //fprintf(stderr, "underrun occurred\n");
//                    //完成硬件参数设置，使设备准备好
//                    snd_pcm_prepare(handle);
//                }
//                else
//                {
//                    fprintf(stderr, "error from writei: %s\n", snd_strerror(ret));
//                }
//            }
//        }
//        msleep(1);
//    }
//    fclose(fp);
}
