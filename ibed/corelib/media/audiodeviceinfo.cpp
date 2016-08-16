#include "audiodeviceinfo.h"
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <alsa/asoundlib.h>
#include <assert.h>
#include <termios.h>
#include <signal.h>
#include <sys/poll.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <endian.h>

AudioDeviceInfo::AudioDeviceInfo()
{

}

AudioDeviceInfo::AudioDeviceInfo(const AudioDeviceInfo &other)
{

}

AudioDeviceInfo::~AudioDeviceInfo()
{

}

QString AudioDeviceInfo::deviceName() const
{

}

bool AudioDeviceInfo::isFormatSupported(const AudioFormat &settings) const
{

}

bool AudioDeviceInfo::isNull() const
{

}

QList<AudioFormat::Endian> AudioDeviceInfo::supportedByteOrders() const
{

}

QList<int> AudioDeviceInfo::supportedChannelCounts() const
{

}

QList<int> AudioDeviceInfo::supportedSampleRates() const
{

}

QList<AudioFormat::SampleBit> AudioDeviceInfo::supportedSampleBits() const
{

}

AudioDeviceInfo &AudioDeviceInfo::operator=(const AudioDeviceInfo &other)
{

}

QList<AudioDeviceInfo> AudioDeviceInfo::availableDevices(Audio::Mode mode)
{
//    snd_ctl_t *handle;
//    int card, err, dev, idx;
//    snd_ctl_card_info_t *info;
//    snd_pcm_info_t *pcminfo;
//    snd_ctl_card_info_alloca(&info);
//    snd_pcm_info_alloca(&pcminfo);

//    card = -1;
//    if (snd_card_next(&card) < 0 || card < 0) {
//        error(_("no soundcards found..."));
//        return;
//    }
//    printf(_("**** List of %s Hardware Devices ****\n"),
//           snd_pcm_stream_name(stream));
//    while (card >= 0) {
//        char name[32];
//        sprintf(name, "hw:%d", card);
//        if ((err = snd_ctl_open(&handle, name, 0)) < 0) {
//            error("control open (%i): %s", card, snd_strerror(err));
//            goto next_card;
//        }
//        if ((err = snd_ctl_card_info(handle, info)) < 0) {
//            error("control hardware info (%i): %s", card, snd_strerror(err));
//            snd_ctl_close(handle);
//            goto next_card;
//        }
//        dev = -1;
//        while (1) {
//            unsigned int count;
//            if (snd_ctl_pcm_next_device(handle, &dev)<0)
//                error("snd_ctl_pcm_next_device");
//            if (dev < 0)
//                break;
//            snd_pcm_info_set_device(pcminfo, dev);
//            snd_pcm_info_set_subdevice(pcminfo, 0);
//            snd_pcm_info_set_stream(pcminfo, stream);
//            if ((err = snd_ctl_pcm_info(handle, pcminfo)) < 0) {
//                if (err != -ENOENT)
//                    error("control digital audio info (%i): %s", card, snd_strerror(err));
//                continue;
//            }
//            printf(_("card %i: %s [%s], device %i: %s [%s]\n"),
//                card, snd_ctl_card_info_get_id(info), snd_ctl_card_info_get_name(info),
//                dev,
//                snd_pcm_info_get_id(pcminfo),
//                snd_pcm_info_get_name(pcminfo));
//            count = snd_pcm_info_get_subdevices_count(pcminfo);
//            printf( _("  Subdevices: %i/%i\n"),
//                snd_pcm_info_get_subdevices_avail(pcminfo), count);
//            for (idx = 0; idx < (int)count; idx++) {
//                snd_pcm_info_set_subdevice(pcminfo, idx);
//                if ((err = snd_ctl_pcm_info(handle, pcminfo)) < 0) {
//                    error("control digital audio playback info (%i): %s", card, snd_strerror(err));
//                } else {
//                    printf(_("  Subdevice #%i: %s\n"),
//                        idx, snd_pcm_info_get_subdevice_name(pcminfo));
//                }
//            }
//        }
//        snd_ctl_close(handle);
//    next_card:
//        if (snd_card_next(&card) < 0) {
//            error("snd_card_next");
//            break;
//        }
//    }
}

AudioDeviceInfo AudioDeviceInfo::defaultInputDevice()
{

}

AudioDeviceInfo AudioDeviceInfo::defaultOutputDevice()
{

}

QList<AudioDeviceInfo> AudioDeviceInfo::availableOutputDevices()
{

}

QList<AudioDeviceInfo> AudioDeviceInfo::availableInputDevices()
{

}

