/*****************************************************************************
**
**  Copyright (C) 2016-2017 HuangYang
**
**  This file is part of IBED
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as
**  published by the Free Software Foundation.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     circleprogress.cpp
**  @brief    circle progress bar class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "circleprogressbar.h"
#include <QPainter>
#include <QPainterPath>


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


CircleProgressBar::CircleProgressBar(QWidget *parent) :
    BaseWidget(parent),
    d_ptr(new CircleProgressBarPrivate(this))
{

}

CircleProgressBar::~CircleProgressBar()
{
    delete d_ptr;
}

void CircleProgressBar::setMaximum(int value)
{
    Q_D(CircleProgressBar);
    if(value <= d->m_min)
        return;

    setRange(value, d->m_max);
}

void CircleProgressBar::setMinimum(int value)
{
    Q_D(CircleProgressBar);
    if(value >= d->m_max)
        return;

    setRange(d->m_min, value);
}

void CircleProgressBar::setRange(int min, int max)
{
    Q_D(CircleProgressBar);
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

    if((d->m_min != minimum) && (d->m_max != maximum))
    {
        d->m_min = minimum;
        d->m_max = maximum;
        update();
    }
}


void CircleProgressBar::setCircleStyle(CircleProgressBar::CircleStyle style)
{
    Q_ASSERT(style < CircleProgressBar::Count);
    Q_D(CircleProgressBar);
    if(style != d->m_style)
    {
        d->m_style = style;
        update();
    }
}

void CircleProgressBar::setText(const QString &text)
{
    Q_D(CircleProgressBar);
    if(d->m_text != text)
    {
        d->m_text = text;
        update();
    }
}

void CircleProgressBar::setBackground(const QColor &color)
{
    Q_D(CircleProgressBar);
    if(d->m_background != color)
    {
        d->m_background = color;
        update();
    }
}


void CircleProgressBar::setActive(const QColor &color)
{
    Q_D(CircleProgressBar);
    if(d->m_active != color)
    {
        d->m_active = color;
        update();
    }
}

void CircleProgressBar::setIntervalAngle(int angle)
{
    Q_D(CircleProgressBar);
    if(d->m_intervalAngle != angle)
    {
        d->m_intervalAngle = angle;
        update();
    }
}

void CircleProgressBar::setStartAngle(int angle)
{
    Q_D(CircleProgressBar);
    if(d->m_startAngle != angle)
    {
        d->m_startAngle = angle;
        update();
    }
}

void CircleProgressBar::setCircleHeight(int height)
{
    Q_D(CircleProgressBar);
    if(d->m_circleHeight != height)
    {
        d->m_circleHeight = height;
        update();
    }
}

void CircleProgressBar::setDashWidth(int width)
{
    Q_D(CircleProgressBar);
    if(d->m_dashWidth != width)
    {
        d->m_dashWidth = width;
        update();
    }
}

void CircleProgressBar::setFontSize(int size)
{
    Q_D(CircleProgressBar);
    if(d->m_fontSize != size)
    {
        d->m_fontSize = size;
        update();
    }
}

void CircleProgressBar::setInnerRadius(int radius)
{
    Q_D(CircleProgressBar);
    if(d->m_innerRadius != radius)
    {
        d->m_innerRadius = radius;
        update();
    }
}

void CircleProgressBar::setInner(const QColor &color)
{
    Q_D(CircleProgressBar);
    if(d->m_inner != color)
    {
        d->m_inner = color;
        update();
    }
}

void CircleProgressBar::setColor(const QColor &color)
{
    Q_D(CircleProgressBar);
    d->m_useGradientColor = false;
    if(d->m_color != color)
    {
        d->m_color = color;
        update();
    }
}

void CircleProgressBar::setFontFamily(const QString &family)
{
    Q_D(CircleProgressBar);
    if(d->m_fontFamily != family)
    {
        d->m_fontFamily = family;
        update();
    }
}

void CircleProgressBar::setStartColor(const QColor &color)
{
    Q_D(CircleProgressBar);
    d->m_useGradientColor = true;
    if(d->m_startColor != color)
    {
        d->m_startColor = color;
        update();
    }
}

void CircleProgressBar::setStopColor(const QColor &color)
{
    Q_D(CircleProgressBar);
    d->m_useGradientColor = true;
    if(d->m_stopColor != color)
    {
        d->m_stopColor = color;
        update();
    }
}


int CircleProgressBar::maximum() const
{
    return d_ptr->m_max;
}

int CircleProgressBar::minimum() const
{
    return d_ptr->m_min;
}

int CircleProgressBar::value() const
{
    return d_ptr->m_value;
}

QColor CircleProgressBar::background() const
{
    return d_ptr->m_background;
}


QColor CircleProgressBar::active() const
{
    return d_ptr->m_active;
}

int CircleProgressBar::intervalAngle() const
{
    return d_ptr->m_intervalAngle;
}

int CircleProgressBar::startAngle() const
{
    return d_ptr->m_startAngle;
}

int CircleProgressBar::circleHeight() const
{
    return d_ptr->m_circleHeight;
}

int CircleProgressBar::dashWidth() const
{
    return d_ptr->m_dashWidth;
}

int CircleProgressBar::fontSize() const
{
    return d_ptr->m_fontSize;
}

int CircleProgressBar::innerRadius() const
{
    return d_ptr->m_innerRadius;
}

QColor CircleProgressBar::inner() const
{
    return d_ptr->m_inner;
}

QColor CircleProgressBar::color() const
{
    return d_ptr->m_color;
}

void CircleProgressBar::setValue(int value)
{
    Q_D(CircleProgressBar);
    if((value >= d->m_min) && (value <= d->m_max))
    {
        d->m_value = value;
        update();
    }
}

CircleProgressBar::CircleStyle CircleProgressBar::circleStyle() const
{
    return d_ptr->m_style;
}

QString CircleProgressBar::text() const
{
   return d_ptr->m_text;
}

QString CircleProgressBar::fontFamily() const
{
    return d_ptr->m_fontFamily;
}

QColor CircleProgressBar::startColor() const
{
    return d_ptr->m_startColor;
}

QColor CircleProgressBar::stopColor() const
{
    return d_ptr->m_stopColor;
}

void CircleProgressBar::paintEvent(QPaintEvent *event)
{
    Q_D(CircleProgressBar);
    BaseWidget::paintEvent(event);
    switch(d->m_style)
    {
    case CircleProgressBar::Solid:
        d->drawSolidCircle();
        break;
    case CircleProgressBar::Dash:
        d->drawDashCircle();
        break;
    default:
        d->drawSolidCircle();
        break;
    }
}


CircleProgressBarPrivate::CircleProgressBarPrivate(CircleProgressBar *parent) :
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
    m_useGradientColor(false),
    q_ptr(parent)
{

}


void CircleProgressBarPrivate::drawSolidCircle()
{
    Q_Q(CircleProgressBar);
    QPainter painter(q);

    int radius = qMin(q->width() / 2, q->height() / 2) - 5;
    //translate coordinate to middle
    painter.translate(q->rect().center().x(), q->rect().center().y());

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


void CircleProgressBarPrivate::drawDashCircle()
{
    Q_Q(CircleProgressBar);
    QPainter painter(q);

    int radius = qMin(q->width() / 2, q->height() / 2) - 5;
    //translate coordinate to middle
    painter.translate(q->rect().center().x(), q->rect().center().y());

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
