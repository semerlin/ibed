#include "fileaudioout.h"
#include <QFile>
#include <QDebug>
#include "audioutil.h"


FileAudioOut::FileAudioOut(const QString &fileName) :
    m_name(fileName),
    m_file(new QFile(fileName))
{
    connect(this, SIGNAL(stateChanged(Audio::State,Audio::State)),
            this, SLOT(onStateChanged(Audio::State,Audio::State)));
}

FileAudioOut::~FileAudioOut()
{
    delete m_file;
}

void FileAudioOut::setName(const QString &name)
{
    m_name = name;
    if(m_file->isOpen())
    {
        m_file->close();
    }

    m_file->setFileName(name);
}


AudioFormat FileAudioOut::format() const
{
    return AudioUtil::format(m_name);
}


int FileAudioOut::time() const
{
    return AudioUtil::time(m_name);
}

void FileAudioOut::play()
{
    AudioFormat audioFmt = AudioUtil::format(m_name);
    if(audioFmt.codec() == "pcm")
    {
        setAudioFormat(audioFmt);
        if(m_file->isOpen())
            m_file->close();
        m_file->open(QIODevice::ReadOnly);
        m_file->seek(44);
        start(m_file);
    }
}

void FileAudioOut::onStateChanged(Audio::State prev, Audio::State cur)
{
    Q_UNUSED(prev)
    switch(cur)
    {
    case Audio::ActiveState:
        qDebug() << "state: active";
        break;
    case Audio::SuspendedState:
        qDebug() << "state: suspend";
        break;
    case Audio::IdleState:
        qDebug() << "state: idle";
        break;
    default:
        break;
    }


}

