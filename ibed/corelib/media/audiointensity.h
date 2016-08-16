#ifndef AUDIOINTENSITY_H
#define AUDIOINTENSITY_H

#include "media_global.h"
#include <QObject>
#include <alsa/asoundlib.h>
#include <QThread>
#include "coveragecircularqueue.h"

class QTimer;
class QMutex;

class MEDIASHARED_EXPORT AudioIntensity : public QThread
{
    Q_OBJECT

public:
    AudioIntensity();
    ~AudioIntensity();

public:
    bool startMonitor(void);
    void stopMonitor(void);
    bool isMonitoring(void) const;
    int intensity(void) const;

protected:
    void run();

signals:
    void intensityChanged(int intensity);

private slots:
    void onCalcIntensity(void);

private:
    int calcIntensity(void) const;

private:
    int m_intensity;
    bool m_isMonitoring;
    snd_pcm_t* m_handle; //PCI设备句柄
    snd_pcm_hw_params_t* m_params;//硬件信息和PCM流配置
    snd_pcm_uframes_t m_frames;
    QByteArray m_recData;
    QTimer *m_calcTimer;
    char *m_tmpData;
    CoverageCircularQueue<char> *m_queue;
};

#endif // AUDIOINTENSITY_H
