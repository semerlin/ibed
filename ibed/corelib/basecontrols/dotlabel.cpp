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
**  @file     dotlabel.cpp
**  @brief    dot label class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "dotlabel.h"
#include "ui_dotlabel.h"
#include <QPalette>

DotLabel::DotLabel(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::DotLabel),
    m_color(Qt::white),
    m_text("")
{
    ui->setupUi(this);
    ui->labelDot->setAutoFillBackground(true);
}

DotLabel::~DotLabel()
{
    delete ui;
}

void DotLabel::setDotColor(const QColor &color)
{
    if(m_color != color)
    {
        m_color = color;
        ui->labelDot->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                    .arg(color.red())
                                    .arg(color.green())
                                    .arg(color.blue()));
    }
}

void DotLabel::setText(const QString &text)
{
    ui->labelValue->setText(text);
}

void DotLabel::setSpacing(int spacing)
{
   ui->horizontalLayout->setSpacing(spacing);
}

QColor DotLabel::dotColor() const
{
    return m_color;
}

QString DotLabel::text() const
{
    return m_text;
}
