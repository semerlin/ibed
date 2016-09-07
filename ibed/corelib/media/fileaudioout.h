#ifndef FILEAUDIOOUT_H
#define FILEAUDIOOUT_H

#include "media_global.h"
#include "audiooutput.h"

class QFile;

class MEDIASHARED_EXPORT FileAudioOut : public AudioOutput
{
    Q_OBJECT
public:
    FileAudioOut(const QString &fileName = QString());
    ~FileAudioOut();

public:
    void setName(const QString &name);
    AudioFormat format(void) const;
    int time(void) const;
    void play(void);

//private slots:
//    void onStateChanged(Audio::State prev, Audio::State cur);

private:
    QString m_name;
    QFile *m_file;
};

#endif // FILEAUDIOOUT_H
