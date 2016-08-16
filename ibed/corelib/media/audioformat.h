#ifndef AUDIOFORMAT_H
#define AUDIOFORMAT_H

#include "media_global.h"
#include <QString>

class AudioFormat
{
public:
    typedef enum
    {
        BigEndian,
        LittleEndian,
    }Endian;

    typedef enum
    {
        Bit_8 = 8,
        Bit_16 = 16,
        Bit_24 = 24,
    }SampleBit;

public:
    AudioFormat();
    AudioFormat(const AudioFormat &format);
    ~AudioFormat();

public:
    QString codec(void) const;
    AudioFormat::Endian byteOrder(void) const;
    int channelCount(void) const;
    int sampleRate(void) const;
    AudioFormat::SampleBit sampleBit(void) const;
    int sampleSize(void) const;
    void	 setByteOrder (AudioFormat::Endian byteOrder);
    void	 setChannelCount (int channels);
    void	 setCodec(const QString &codec);
    void	 setSampleRate(int rate);
    void	 setSampleSize(int size);
    bool	 operator != (const AudioFormat &format) const;
    AudioFormat &operator = (const AudioFormat &format);
    bool	 operator == (const AudioFormat &format) const;

private:
    QString m_codec;
    AudioFormat::Endian m_byteOrder;
    int m_channels;
    int m_rate;
    AudioFormat::SampleBit m_bit;
    int m_size;
};



#endif // AUDIOFORMAT_H
