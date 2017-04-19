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
**  @file     labelslider.cpp
**  @brief    label slider class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "labelslider.h"
#include "ui_labelslider.h"

LabelSlider::LabelSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelSlider)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

LabelSlider::~LabelSlider()
{
    delete ui;
}

int LabelSlider::value() const
{
    return ui->horizontalSlider->value();
}

void LabelSlider::setInfo(const QString &info)
{
    ui->labelInfo->setText(info);
}

void LabelSlider::setPercent(const QString &percent)
{
    ui->labelPercent->setText(percent);
}

void LabelSlider::setSpacing(int spacing)
{
    ui->horizontalLayout->setSpacing(spacing);
}

void LabelSlider::setContentsMargins(int left, int top, int right, int bottom)
{
    ui->horizontalLayout->setContentsMargins(left, top, right, bottom);
}

void LabelSlider::setRange(int min, int max)
{
    ui->horizontalSlider->setRange(min, max);
}

void LabelSlider::setValue(int val)
{
    ui->horizontalSlider->setValue(val);
}
