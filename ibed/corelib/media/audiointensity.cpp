#include <QTimer>
#include <QMutex>
#include <QVector>
#include "coveragecircularqueue.h"
#include "audiointensity.h"
#include "qmath.h"
#include "math.h"
#include "log4qt/logger.h"

LOG4QT_DECLARE_STATIC_LOGGER(log, Audio)

static int BitReverse(int j, int nu)
{
    int j2;
    int j1 = j;
    int k = 0;
    for (int i = 1; i <= nu; i++)
    {
        j2 = j1 / 2;
        k = 2 * k + j1 - 2 * j2;
        j1 = j2;
    }

    return k;
}

static QVector<double> FFTDb(const QVector<double> &source)
{
    int sourceLen = source.size();
    int nu = (int)(qLn(sourceLen) / qLn(2));
    int halfSourceLen = sourceLen / 2;
    int nu1 = nu - 1;
    QVector<double> xre;
    QVector<double> xim;
    QVector<double> decibel;
    xre.resize(sourceLen);
    xim.resize(sourceLen);
    decibel.resize(halfSourceLen);
    double tr, ti, p, arg, c, s;
    for (int i = 0; i < sourceLen; i++)
    {
        xre[i] = source[i];
        xim[i] = 0.0f;
    }
    int k = 0;
    for (int l = 1; l <= nu; l++)
    {
        while (k < sourceLen)
        {
            for (int i = 1; i <= halfSourceLen; i++)
            {
                p = BitReverse(k >> nu1, nu);
                arg = 2 * (double)M_PI * p / sourceLen;
                c = (double)qCos(arg);
                s = (double)qSin(arg);
                tr = xre[k + halfSourceLen] * c + xim[k + halfSourceLen] * s;
                ti = xim[k + halfSourceLen] * c - xre[k + halfSourceLen] * s;
                xre[k + halfSourceLen] = xre[k] - tr;
                xim[k + halfSourceLen] = xim[k] - ti;
                xre[k] += tr;
                xim[k] += ti;
                k++;
            }
            k += halfSourceLen;
        }
        k = 0;
        nu1--;
        halfSourceLen = halfSourceLen / 2;
    }
    k = 0;
    int r;
    while (k < sourceLen)
    {
        r = BitReverse(k, nu);
        if (r > k)
        {
            tr = xre[k];
            ti = xim[k];
            xre[k] = xre[r];
            xim[k] = xim[r];
            xre[r] = tr;
            xim[r] = ti;
        }
        k++;
    }
    for (int i = 0; i < sourceLen / 2; i++)
    {
        decibel[i] = 10.0 * log10((float)(qSqrt((xre[i] * xre[i]) + (xim[i] * xim[i]))));
    }

    return decibel;
}


AudioIntensity::AudioIntensity() :
    m_intensity(0),
    m_isMonitoring(false),
    m_handle(NULL),
    m_params(NULL),
    m_calcTimer(new QTimer(this)),
    m_queue(new CoverageCircularQueue<char>(4096))
{
    m_frames = 128;
    /* 2 bytes/sample, 2 channels */
    m_tmpData = (char *)malloc(m_frames * 4);
    m_calcTimer->setInterval(500);
    connect(m_calcTimer, SIGNAL(timeout()), this, SLOT(onCalcIntensity()));
}

AudioIntensity::~AudioIntensity()
{
    stopMonitor();
    free(m_tmpData);
}


bool AudioIntensity::startMonitor()
{
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

    start();
    m_calcTimer->start();

    m_isMonitoring = true;

    return true;
}

void AudioIntensity::stopMonitor()
{
    quit();
    m_calcTimer->stop();
    snd_pcm_close(m_handle);

    m_isMonitoring = false;
}

bool AudioIntensity::isMonitoring() const
{
    return m_isMonitoring;
}

int AudioIntensity::intensity() const
{
    return calcIntensity();
}

void AudioIntensity::run()
{
    while(1)
    {
        int rc = snd_pcm_readi(m_handle, m_tmpData, m_frames);
        if (rc == -EPIPE)
        {
            /* EPIPE means overrun */
            snd_pcm_prepare(m_handle);
        }

        for(int i = 0; i < rc; ++i)
            m_queue->enqueue(m_tmpData[i]);
    }
}

void AudioIntensity::onCalcIntensity()
{
    for(int i = 0; i < m_queue->size(); ++i)
        m_recData[i] = m_queue->dequeue();

    int temp = calcIntensity();
    if(temp != m_intensity)
    {
        m_intensity = temp;
//        log()->debug(QString("audio intensity is: %1 dB").arg(m_intensity));
        emit intensityChanged(m_intensity);
    }
}

int AudioIntensity::calcIntensity() const
{
    QVector<double> wave;
    wave.resize(m_recData.size() / 2);
    int h = 0;
    qint16 tempVal = 0;
    for (int i = 0; i < wave.size(); i += 2)
    {
        tempVal = (m_recData.at(i + 1) & 0xff);
        tempVal <<= 8;
        tempVal += (m_recData[i] & 0xff);
        wave[h] = (double)(tempVal); //采样位数为16bit
        ++h;
    }

    double sum = 0.0;
    QVector<double> sound = FFTDb(wave);
    foreach(const double &data, sound)
    {
        sum += data;
    }

    int val = sum / sound.size();

    return val;
}

