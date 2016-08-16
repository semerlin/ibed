#ifndef AUDIO_H
#define AUDIO_H

#include <QMetaType>

namespace Audio
{
    enum Error { NoError, OpenError, IOError, UnderrunError, FatalError };
    enum State { ActiveState, SuspendedState, StoppedState, IdleState };
    enum Mode { AudioInput, AudioOutput };
}


Q_DECLARE_METATYPE(Audio::Error)
Q_DECLARE_METATYPE(Audio::State)
Q_DECLARE_METATYPE(Audio::Mode)

#endif // AUDIO

