#ifndef CIRCLEPROGRESSBAR_H
#define CIRCLEPROGRESSBAR_H

#include "basecontrols_global.h"
#include "basewidget.h"

class BASECONTROLSSHARED_EXPORT CircleProgressBar : public BaseWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor active READ active WRITE setActive)
    Q_PROPERTY(int circleHeight READ circleHeight WRITE setCircleHeight)
    Q_PROPERTY(int intervalAngle READ intervalAngle WRITE setIntervalAngle)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int dashWidth READ dashWidth WRITE setDashWidth)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily)
    Q_PROPERTY(int innerRadius READ innerRadius WRITE setInnerRadius)
    Q_PROPERTY(QColor inner READ inner WRITE setInner)
    Q_PROPERTY(QColor startColor READ startColor WRITE setStartColor)
    Q_PROPERTY(QColor stopColor READ stopColor WRITE setStopColor)

public:
    typedef enum
    {
        Solid,
        Dash,
    }CircleStyle;

public:
    explicit CircleProgressBar(QWidget *parent = 0);

public slots:
    void setMaximum(int value);
    void setMinimum(int value);
    void setRange(int min, int max);
    void setValue(int value);
    void setCircleStyle(CircleProgressBar::CircleStyle style);
    void setText(const QString &text);

    void setBackground(const QColor &color);
    void setActive(const QColor &color);
    void setIntervalAngle(int angle);
    void setStartAngle(int angle);
    void setCircleHeight(int height);
    void setDashWidth(int width);
    void setFontSize(int size);
    void setInnerRadius(int radius);
    void setInner(const QColor &color);
    void setColor(const QColor &color);
    void setFontFamily(const QString &family);
    void setStartColor(const QColor &color);
    void setStopColor(const QColor &color);

public:
    int maximum(void) const;
    int minimum(void) const;
    int value(void) const;
    QColor background(void) const;
    QColor active(void) const;
    int intervalAngle(void) const;
    int startAngle(void) const;
    int circleHeight(void) const;
    int dashWidth(void) const;
    int fontSize(void) const;
    int innerRadius(void) const;
    QColor inner(void) const;
    QColor color(void) const;
    CircleProgressBar::CircleStyle circleStyle(void) const;
    QString text(void) const;
    QString fontFamily(void) const;
    QColor startColor(void) const;
    QColor stopColor(void) const;

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    void drawSolidCircle(void);
    void drawDashCircle(void);

private:
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
};

#endif // CIRCLEPROGRESSBAR_H
