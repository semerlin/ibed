#ifndef LAUNCHWIDGET_P
#define LAUNCHWIDGET_P

#include "mainmodule_global.h"

class MAINMODULESHARED_EXPORT LaunchWidgetPrivate
{
public:
    LaunchWidgetPrivate() :
        m_currentStep(0),
        m_totalStep(0)
    {
    }

public:
    int m_currentStep;
    int m_totalStep;
};

#endif // LAUNCHWIDGET_P

