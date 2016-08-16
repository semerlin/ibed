#ifndef AUDIORECORD_H
#define AUDIORECORD_H

#include "media_global.h"
#include <QtGui>
#include <alsa/asoundlib.h>

class MEDIASHARED_EXPORT CAudioRecord : public QThread
{
    Q_OBJECT
public:
    CAudioRecord();
    ~CAudioRecord();

public:
    int InitAudioRecord(void);
    void StopRecord(void);
    void StartRecord(void);
    void PauseRecord(void);
    void ResumeRecord(void);
    void ReadData(char *buffer, int size);
    void StartRecordNet(char *buffer, int size);

protected:
    void run();

private:
    snd_pcm_t* handle; //PCI设备句柄
    snd_pcm_hw_params_t* params;//硬件信息和PCM流配置
    snd_pcm_uframes_t frames;
    int m_alsa_can_pause;

signals:

public slots:

};

#endif // AUDIORECORD_H
