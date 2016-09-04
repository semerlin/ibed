#include "audioutil.h"
#include <QFile>

/* wav文件头结构体 */
typedef struct
{
    char riff[4]; //"RIFF"标志
    int dataSize; //从下个地址到文件尾的总字节数
    char wave[4]; //"WAVE"
    char fmt[4]; //"fmt"
    int transition; //过渡字节
    short type; //编码格式(1: 线性pcm)
    short channels; //声道数
    int sampleRate ; //采样频率
    int bytesPerSec; //每秒采样的字节数
    short adjustment; //数据快调整数(按字节算),通道数＊每样本数据位/8
    short bitsPerSample; //每次采样位数
    char data[4]; //”data“
    int audioSize; //音频数据的大小
}WAV_HEADER;


AudioUtil::AudioUtil()
{

}

AudioFormat AudioUtil::format(const QString &name)
{
    AudioFormat format;
    if(name.isEmpty())
        return format;

    QFile file(name);
    if(!file.open(QIODevice::ReadOnly))
        return format;

    WAV_HEADER header;
    file.read((char *)&header, sizeof(WAV_HEADER) / sizeof(char));

    //check format
    QString wave = QString("%1%2%3%4").arg(header.wave[0]).arg(header.wave[1]).arg(header.wave[2]).arg(header.wave[3]);
    QString riff = QString("%1%2%3%4").arg(header.riff[0]).arg(header.riff[1]).arg(header.riff[2]).arg(header.riff[3]);
    QString fmt = QString("%1%2%3").arg(header.fmt[0]).arg(header.fmt[1]).arg(header.fmt[2]);

    if((wave == "WAVE") &&
       (riff == "RIFF") &&
       (fmt == "fmt"))
    {
        if(header.type == 1)
            format.setCodec("pcm");

        format.setChannelCount(header.channels);
        format.setSampleRate(header.sampleRate);
        format.setSampleBit((AudioFormat::SampleBit)(header.bitsPerSample));

        return format;
    }
    else
        return format;
}

int AudioUtil::time(const QString &name)
{
    if(name.isEmpty())
        return 0;

    QFile file(name);
    if(!file.open(QIODevice::ReadOnly))
        return 0;

    WAV_HEADER header;
    file.read((char *)&header, sizeof(WAV_HEADER) / sizeof(char));

    //check format
    QString wave = QString("%1%2%3%4").arg(header.wave[0]).arg(header.wave[1]).arg(header.wave[2]).arg(header.wave[3]);
    QString riff = QString("%1%2%3%4").arg(header.riff[0]).arg(header.riff[1]).arg(header.riff[2]).arg(header.riff[3]);
    QString fmt = QString("%1%2%3").arg(header.fmt[0]).arg(header.fmt[1]).arg(header.fmt[2]);

    if((wave == "WAVE") && (riff == "RIFF") && (fmt == "fmt"))
    {
        quint64 size = header.audioSize;
        int time = size / header.channels / (header.bitsPerSample / 8) / header.sampleRate;

        return time;
    }
    else
        return 0;
}

