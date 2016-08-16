#include "audioformat.h"

AudioFormat::AudioFormat() :
    m_codec("pcm"),
    m_byteOrder(AudioFormat::LittleEndian),
    m_channels(2),
    m_rate(8000),
    m_bit(AudioFormat::Bit_8),
    m_size(0)

{

}

AudioFormat::AudioFormat(const AudioFormat &format) :
    m_codec(format.m_codec),
    m_byteOrder(format.m_byteOrder),
    m_channels(format.m_channels),
    m_rate(format.m_rate),
    m_bit(format.m_bit),
    m_size(format.m_size)
{

}

AudioFormat::~AudioFormat()
{

}

QString AudioFormat::codec() const
{
    return m_codec;
}

AudioFormat::Endian AudioFormat::byteOrder() const
{
    return m_byteOrder;
}

int AudioFormat::channelCount() const
{
    return m_channels;
}

int AudioFormat::sampleRate() const
{
    return m_rate;
}

AudioFormat::SampleBit AudioFormat::sampleBit() const
{
    return m_bit;
}

int AudioFormat::sampleSize() const
{
    return m_size;
}

void AudioFormat::setByteOrder(AudioFormat::Endian byteOrder)
{
    m_byteOrder = byteOrder;
}

void AudioFormat::setChannelCount(int channels)
{
    m_channels = channels;
}

void AudioFormat::setCodec(const QString &codec)
{
    m_codec = codec;
}

void AudioFormat::setSampleRate(int rate)
{
    m_rate = rate;
}

void AudioFormat::setSampleSize(int size)
{
    m_size = size;
}

bool AudioFormat::operator !=(const AudioFormat &format) const
{
    return ((m_codec != format.m_codec) ||
            (m_byteOrder != format.m_byteOrder) ||
            (m_channels != format.m_channels) ||
            (m_rate != format.m_rate) ||
            (m_bit != format.m_bit) ||
            (m_size != format.m_size));
}

AudioFormat &AudioFormat::operator =(const AudioFormat &format)
{
    if(this == &format)
        return *this;

    m_codec = format.m_codec;
    m_byteOrder = format.m_byteOrder;
    m_channels = format.m_channels;
    m_rate = format.m_rate;
    m_bit = format.m_bit;
    m_size = format.m_size;

    return *this;
}

bool AudioFormat::operator ==(const AudioFormat &format) const
{
    return ((m_codec == format.m_codec) &&
            (m_byteOrder == format.m_byteOrder) &&
            (m_channels == format.m_channels) &&
            (m_rate == format.m_rate) &&
            (m_bit == format.m_bit) &&
            (m_size == format.m_size));
}

