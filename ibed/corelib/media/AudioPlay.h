#ifndef AUDIOPLAY_H
#define AUDIOPLAY_H

#include "media_global.h"
#include <alsa/asoundlib.h>
#include <QtGui>

class MEDIASHARED_EXPORT CAudioPlay : public QThread
{
public:
    CAudioPlay();
    ~CAudioPlay();

public:
    int AudioInit(const QString &name);
    int GetAudioType(const QString &name);
    void StopPlay(void);
    void StartPlay(void);
    void PausePlay(void);
    void ResumePlay(void);
    void WriteData(char *buffer, int size);
    void StartPlayNet(QByteArray datagram);
    void StartPlayLocal(void);
    bool isPlaying(void) const;

private:
    snd_pcm_t* handle; //PCI设备句柄
    snd_pcm_hw_params_t* params;//硬件信息和PCM流配置
    snd_pcm_uframes_t frames;
    //QSemaphore m_semaphore;
    int m_nDataBlock;
    char *m_buffer;
    int BUF_SIZE;
    QString m_name;
    bool m_bLocal;
    int m_alsa_can_pause;
    snd_mixer_t * mixer;
    snd_mixer_elem_t *pcm_element;
    bool m_isPlaying;

protected:
    void run();
};

#endif // AUDIOPLAY_H
