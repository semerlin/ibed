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
**  along with OST. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     launchwidget.cpp
**  @brief    launch widget
**  @details  show launch progress and display some messages
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/


#include "launchwidget.h"
#include "ui_launchwidget.h"
#include "launchwidget_p.h"

LaunchWidget::LaunchWidget(QWidget *parent) :
    IAppLaunchWidget(parent),
    ui(new Ui::LaunchWidget),
    d_ptr(new LaunchWidgetPrivate)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->progressBar_launch->setValue(0);
}

LaunchWidget::~LaunchWidget()
{
    delete ui;
    delete d_ptr;
}

void LaunchWidget::setSteps(int steps)
{
    Q_D(LaunchWidget);
    d->m_totalStep = steps;
    ui->progressBar_launch->setRange(0, steps);
}

void LaunchWidget::increaseStep()
{
    Q_D(LaunchWidget);
    d->m_currentStep ++;
    if(d->m_currentStep > d->m_totalStep)
        d->m_currentStep = d->m_totalStep;

    ui->progressBar_launch->setValue(d->m_currentStep);
}

void LaunchWidget::printMsg(const QString &msg)
{
    ui->label_message->setText(msg);
}
