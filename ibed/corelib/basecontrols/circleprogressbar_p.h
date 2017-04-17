#ifndef CIRCLEPROGRESSBAR_P_H
#define CIRCLEPROGRESSBAR_P_H

#include "basecontrols_global.h"
#include <QColor>
#include "circleprogressbar.h"

class BASECONTROLSSHARED_EXPORT CircleProgressBarPrivate
{
public:
    explicit CircleProgressBarPrivate(CircleProgressBar *parent);

public:
    void drawSolidCircle(void);
    void drawDashCircle(void);

public:
    int m_min;
    int m_max;
    int m_value;
    int m_circleHeight;
    int m_intervalAngle;
    int m_startAngle;
    int m_dashWidth;
    QColor m_background;
    QColor m_active;
    CircleProgressBar::CircleStyle m_style;
    int m_fontSize;
    int m_innerRadius;
    QColor m_inner;
    QColor m_color;
    QString m_text;
    QString m_fontFamily;
    QColor m_startColor;
    QColor m_stopColor;
    bool m_useGradientColor;

private:
    CircleProgressBar *const q_ptr;
    Q_DECLARE_PUBLIC(CircleProgressBar)
};

#endif // CIRCLEPROGRESSBAR_P

