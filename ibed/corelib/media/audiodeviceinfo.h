#ifndef AUDIODEVICEINFO_H
#define AUDIODEVICEINFO_H

#include "media_global.h"
#include "audioformat.h"
#include "audio.h"
#include <QList>


class MEDIASHARED_EXPORT AudioDeviceInfo
{
public:
    AudioDeviceInfo();
    AudioDeviceInfo(const AudioDeviceInfo &other);
    ~AudioDeviceInfo();

public:
    QString	deviceName()const;
    bool isFormatSupported(const AudioFormat &settings) const;
    bool	isNull() const;
    QList<AudioFormat::Endian> supportedByteOrders() const;
    QList<int> supportedChannelCounts() const;
    QList<int> supportedSampleRates() const;
    QList<AudioFormat::SampleBit> supportedSampleBits() const;
    AudioDeviceInfo &operator= (const AudioDeviceInfo &other);

public:
    static QList<AudioDeviceInfo> availableDevices(Audio::Mode mode);
    static AudioDeviceInfo defaultInputDevice();
    static AudioDeviceInfo defaultOutputDevice();

private:
    static QList<AudioDeviceInfo> availableOutputDevices(void);
    static QList<AudioDeviceInfo> availableInputDevices(void);

private:
    QString m_name;
};



#endif // AUDIODEVICEINFO_H
