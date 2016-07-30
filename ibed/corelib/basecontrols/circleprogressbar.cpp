#include "circleprogressbar.h"
#include <QPainter>
#include <QPainterPath>

CircleProgressBar::CircleProgressBar(QWidget *parent) :
    BaseWidget(parent),
    m_min(0),
    m_max(100),
    m_value(24),
    m_circleHeight(20),
    m_intervalAngle(3),
    m_startAngle(30),
    m_dashWidth(2),
    m_background(Qt::darkGray),
    m_active(Qt::gray),
    m_style(CircleProgressBar::Solid),
    m_fontSize(9),
    m_innerRadius(60),
    m_inner(Qt::gray),
    m_color(Qt::white),
    m_text(""),
    m_fontFamily(""),
    m_startColor(QColor(0, 0, 0)),
    m_stopColor(QColor(0, 0, 0)),
    m_useGradientColor(false)
{

}

void CircleProgressBar::setMaximum(int value)
{
    if(value <= m_min)
        return;

    setRange(value, m_max);
}

void CircleProgressBar::setMinimum(int value)
{
    if(value >= m_max)
        return;

    setRange(m_min, value);
}

void CircleProgressBar::setRange(int min, int max)
{
    int minimum, maximum;
    if(min >= max)
    {
        minimum = max;
        maximum = min;
    }
    else
    {
        minimum = min;
        maximum = max;
    }

    if((m_min != minimum) && (m_max != maximum))
    {
        m_min = minimum;
        m_max = maximum;
        update();
    }
}


void CircleProgressBar::setCircleStyle(CircleProgressBar::CircleStyle style)
{
    if(style != m_style)
    {
        m_style = style;
        update();
    }
}

void CircleProgressBar::setText(const QString &text)
{
    if(m_text != text)
    {
        m_text = text;
        update();
    }
}

void CircleProgressBar::setBackground(const QColor &color)
{
    if(m_background != color)
    {
        m_background = color;
        update();
    }
}


void CircleProgressBar::setActive(const QColor &color)
{
    if(m_active != color)
    {
        m_active = color;
        update();
    }
}

void CircleProgressBar::setIntervalAngle(int angle)
{
    if(m_intervalAngle != angle)
    {
        m_intervalAngle = angle;
        update();
    }
}

void CircleProgressBar::setStartAngle(int angle)
{
    if(m_startAngle != angle)
    {
        m_startAngle = angle;
        update();
    }
}

void CircleProgressBar::setCircleHeight(int height)
{
    if(m_circleHeight != height)
    {
        m_circleHeight = height;
        update();
    }
}

void CircleProgressBar::setDashWidth(int width)
{
    if(m_dashWidth != width)
    {
        m_dashWidth = width;
        update();
    }
}

void CircleProgressBar::setFontSize(int size)
{
    if(m_fontSize != size)
    {
        m_fontSize = size;
        update();
    }
}

void CircleProgressBar::setInnerRadius(int radius)
{
    if(m_innerRadius != radius)
    {
        m_innerRadius = radius;
        update();
    }
}

void CircleProgressBar::setInner(const QColor &color)
{
    if(m_inner != color)
    {
        m_inner = color;
        update();
    }
}

void CircleProgressBar::setColor(const QColor &color)
{
    m_useGradientColor = false;
    if(m_color != color)
    {
        m_color = color;
        update();
    }
}

void CircleProgressBar::setFontFamily(const QString &family)
{
    if(m_fontFamily != family)
    {
        m_fontFamily = family;
        update();
    }
}

void CircleProgressBar::setStartColor(const QColor &color)
{
    m_useGradientColor = true;
    if(m_startColor != color)
    {
        m_startColor = color;
        update();
    }
}

void CircleProgressBar::setStopColor(const QColor &color)
{
    m_useGradientColor = true;
    if(m_stopColor != color)
    {
        m_stopColor = color;
        update();
    }
}


int CircleProgressBar::maximum() const
{
    return m_max;
}

int CircleProgressBar::minimum() const
{
    return m_min;
}

int CircleProgressBar::value() const
{
    return m_value;
}

QColor CircleProgressBar::background() const
{
    return m_background;
}


QColor CircleProgressBar::active() const
{
    return m_active;
}

int CircleProgressBar::intervalAngle() const
{
    return m_intervalAngle;
}

int CircleProgressBar::startAngle() const
{
    return m_startAngle;
}

int CircleProgressBar::circleHeight() const
{
    return m_circleHeight;
}

int CircleProgressBar::dashWidth() const
{
    return m_dashWidth;
}

int CircleProgressBar::fontSize() const
{
    return m_fontSize;
}

int CircleProgressBar::innerRadius() const
{
    return m_innerRadius;
}

QColor CircleProgressBar::inner() const
{
    return m_inner;
}

QColor CircleProgressBar::color() const
{
    return m_color;
}

void CircleProgressBar::setValue(int value)
{
    if((value >= m_min) && (value <= m_max))
    {
        m_value = value;
        update();
    }
}

CircleProgressBar::CircleStyle CircleProgressBar::circleStyle() const
{
    return m_style;
}

QString CircleProgressBar::text() const
{
   return m_text;
}

QString CircleProgressBar::fontFamily() const
{
    return m_fontFamily;
}

QColor CircleProgressBar::startColor() const
{
    return m_startColor;
}

QColor CircleProgressBar::stopColor() const
{
    return m_stopColor;
}

void CircleProgressBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    switch(m_style)
    {
    case CircleProgressBar::Solid:
        drawSolidCircle();
        break;
    case CircleProgressBar::Dash:
        drawDashCircle();
        break;
    default:
        drawSolidCircle();
        break;
    }
}


void CircleProgressBar::drawSolidCircle(void)
{
    QPainter painter(this);

    int radius = qMin(width() / 2, height() / 2) - 5;
    //translate coordinate to middle
    painter.translate(rect().center().x(), rect().center().y());

    //set pen render
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.moveTo(0, 0);
    path.addEllipse(QPoint(0, 0), radius, radius);
    path.addEllipse(QPoint(0, 0), radius - m_circleHeight, radius - m_circleHeight);

    painter.fillPath(path, QBrush(m_background));

    //draw active
    if(m_max == m_min)
        return ;

    int angle = (m_value - m_min) * 360 / (m_max - m_min);
    if(angle >= 360)
        angle = 360;


    QPainterPath activePath;
    activePath.moveTo(0, 0);
    activePath.arcTo(QRect(-radius, -radius, radius * 2, radius * 2), 450 - (angle + m_startAngle), angle);
    activePath.closeSubpath();

    painter.fillPath(activePath.intersected(path), QBrush(m_active));

    //draw text
    if(m_innerRadius >= (radius - m_circleHeight))
        m_innerRadius = radius - m_circleHeight;
    painter.setBrush(QColor(m_inner));
    painter.setPen(QColor(m_inner));
    painter.drawEllipse(QPoint(0, 0), m_innerRadius, m_innerRadius);

    painter.setFont(QFont(m_fontFamily, m_fontSize));
    painter.setPen(QColor(m_color));
    painter.drawText(QRect(-m_innerRadius, -m_innerRadius, m_innerRadius * 2, m_innerRadius * 2),
                     Qt::AlignCenter, m_text);


}

void CircleProgressBar::drawDashCircle(void)
{
    QPainter painter(this);

    int radius = qMin(width() / 2, height() / 2) - 5;
    //translate coordinate to middle
    painter.translate(rect().center().x(), rect().center().y());

    //set pen render
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    //set start drawing angle
    int sum = 360 / m_intervalAngle;
    //draw inactive
    painter.setPen(QPen(m_background, m_dashWidth));
    for(int i = 0; i < sum; ++i)
    {
        painter.drawLine(0, radius - m_circleHeight, 0, radius);
        painter.rotate(m_intervalAngle);
    }

    //draw active
    QList<QColor> colors;
    if(m_useGradientColor)
    {
        for(qreal i = 0.0; i < sum; i += 1.0)
        {
            int r = (m_stopColor.red() - m_startColor.red()) * i / sum + m_startColor.red();
            int g = (m_stopColor.green() - m_startColor.green()) * i / sum + m_startColor.green();
            int b = (m_stopColor.blue() - m_startColor.blue()) * i / sum + m_startColor.blue();
            colors.append(QColor(r, g, b));
        }
    }


    if(m_max == m_min)
        return ;

    int num = (m_value - m_min) * sum / (m_max - m_min);
    if(num >= sum)
        num = sum;

    painter.save();
    painter.rotate(m_startAngle + 180);
    if(!m_useGradientColor)
        painter.setPen(QPen(m_active, m_dashWidth));

    for(int i = 0; i < num ; ++i)
    {

        if(m_useGradientColor)
            painter.setPen(QPen(colors.at(i), m_dashWidth));
        painter.drawLine(0, radius - m_circleHeight, 0, radius);
        painter.rotate(m_intervalAngle);
    }
    painter.restore();

    //draw text
    if(m_innerRadius >= (radius - m_circleHeight))
        m_innerRadius = radius - m_circleHeight;
    painter.setBrush(QColor(m_inner));
    painter.setPen(QColor(m_inner));
    painter.drawEllipse(QPoint(0, 0), m_innerRadius, m_innerRadius);

    painter.setFont(QFont(m_fontFamily, m_fontSize));
    painter.setPen(QColor(m_color));
    painter.drawText(QRect(-m_innerRadius, -m_innerRadius, m_innerRadius * 2, m_innerRadius * 2),
                     Qt::AlignCenter, m_text);

}
