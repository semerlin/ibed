#ifndef CALLDEF_H
#define CALLDEF_H

namespace Call
{
    typedef enum
    {
        Connecting,
        Connected,
        LocalTerminate,
        RemoteTerminate,
    }CallStep;
}

#endif // CALLDEF

