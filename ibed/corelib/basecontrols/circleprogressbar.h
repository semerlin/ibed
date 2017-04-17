#ifndef CIRCLEPROGRESSBAR_H
#define CIRCLEPROGRESSBAR_H

#include "basecontrols_global.h"
#include "basewidget.h"

class CircleProgressBarPrivate;

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
        Count,
    }CircleStyle;

public:
    explicit CircleProgressBar(QWidget *parent = 0);
    virtual ~CircleProgressBar();

public slots:
    /**
     * @brief set circle max value
     * @param value - max value
     */
    void setMaximum(int value);

    /**
     * @brief set circle min value
     * @param value - circle minimum value
     */
    void setMinimum(int value);

    /**
     * @brief set circle value range
     * @param min - minimum value
     * @param max - maximum value
     */
    void setRange(int min, int max);

    /**
     * @brief set current value
     * @param value - current value
     */
    void setValue(int value);

    /**
     * @brief set circle style
     * @param style
     */
    void setCircleStyle(CircleProgressBar::CircleStyle style);

    /**
     * @brief set text display in circle
     * @param text - text
     */
    void setText(const QString &text);

    /**
     * @brief set circle background color
     * @param color - background color
     */
    void setBackground(const QColor &color);

    /**
     * @brief set active range color
     * @param color - active range color
     */
    void setActive(const QColor &color);

    /**
     * @brief set interval angle
     * @param angle - interval angle
     */
    void setIntervalAngle(int angle);

    /**
     * @brief set circle start angle
     * @param angle - start angle
     */
    void setStartAngle(int angle);

    /**
     * @brief set circle height
     * @param height - circle height
     */
    void setCircleHeight(int height);

    /**
     * @brief set dash line width
     * @param width - dash line width
     */
    void setDashWidth(int width);

    /**
     * @brief set font size
     * @param size - font size
     */
    void setFontSize(int size);

    /**
     * @brief set circle inner radius
     * @param radius - inner radius
     */
    void setInnerRadius(int radius);

    /**
     * @brief set inner color
     * @param color - inner color
     */
    void setInner(const QColor &color);

    /**
     * @brief set circle color
     * @param color - circle color
     */
    void setColor(const QColor &color);

    /**
     * @brief set circle text font family
     * @param family - text font family
     */
    void setFontFamily(const QString &family);

    /**
     * @brief set gradient start color
     * @param color - start color
     */
    void setStartColor(const QColor &color);

    /**
     * @brief set gradient stop color
     * @param color - stop color
     */
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
    CircleProgressBarPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(CircleProgressBar)
};

#endif // CIRCLEPROGRESSBAR_H
