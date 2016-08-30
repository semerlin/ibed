#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <QObject>
#include <alsa/asoundlib.h>
#include "audioformat.h"
#include "audio.h"

class QThread;

class AudioOutputPrivate;



class AudioOutput : public QObject
{
    Q_OBJECT
public:
    AudioOutput(QObject *parent = 0);
    AudioOutput(const AudioFormat &format = AudioFormat(), QObject *parent = 0);
    ~AudioOutput();

public:
    Audio::Error	error() const;
    AudioFormat format() const;
    int	notifyInterval() const;
    qint64 processedUSecs() const;
    Audio::State	state() const;
    void setAudioFormat(const AudioFormat &format);

public slots:
    void	 setNotifyInterval(int ms);
    void	 start(QIODevice * device);
    void	 resume();
    void	 stop();
    void	 suspend();

signals:
    void notify();
    void stateChanged(Audio::State state);
    void started(void);

private:
    AudioFormat m_format;
    Audio::Error m_error;
    Audio::State m_state;
    int m_notifyInterval;
    snd_pcm_t* m_pcm;
    snd_pcm_hw_params_t* m_pcmParams;
    snd_pcm_uframes_t m_frames;
    QIODevice *m_device;
    QThread *m_thread;
    int m_canPause;

private:
    friend class AudioOutputPrivate;
    AudioOutputPrivate *m_private;

};

class AudioOutputPrivate : public QObject
{
    Q_OBJECT

public:
    AudioOutputPrivate(AudioOutput *audio) :
        m_audio(audio)
    {
    }

public slots:
    void start();

private:
    AudioOutput *m_audio;
};


#endif // AUDIOPLAY_H
