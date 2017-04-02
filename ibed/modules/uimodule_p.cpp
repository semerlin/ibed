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
**  @file     uimodule_p.cpp
**  @brief    ui module private class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "uimodule_p.h"
#include <QResource>
#include <QTimer>
#include "mainwidget.h"
#include "standbywidget.h"
#include "callwidget.h"
#include "progressdialog.h"
#include "numipmethod.h"
#include "uimodule.h"
#include <QResource>
#include <QApplication>
#include "uimodule.h"


UiModulePrivate::UiModulePrivate(UiModule *parent) :
    m_mainWidget(NULL),
    m_standbyWidget(NULL),
    m_callWidget(NULL),
    m_progressDialog(NULL),
    #ifdef TARGET_IMX
    m_method(NULL),
    #endif
    m_standByCount(0),
    q_ptr(parent)
{
}

void UiModulePrivate::init()
{
    Q_Q(UiModule);
    m_standByTimer = new QTimer(this);
    m_standByCount = 0;
    m_standByTimer->setInterval(1000);
    connect(m_standByTimer, SIGNAL(timeout()), this, SLOT(onStandbyTimeout()));

    //register resource
    QResource::registerResource("./resource/ui/res.rcc");


    m_mainWidget =new MainWidget;
    m_standbyWidget =new StandbyWidget;
    m_callWidget = new CallWidget(m_mainWidget);
    m_callWidget->hide();
    m_progressDialog =new ProgressDialog;

    //register input method
#ifdef TARGET_IMX
    m_method = new NumIPMethod(m_mainWidget);
    m_method->setGeometry(0, 420, 800, 60);
    QWSServer::setCurrentInputMethod(m_method);
#endif

    //connect signals
    connect(m_mainWidget, SIGNAL(reconnect(QString,quint16,quint16,QString,QString,QString)),
            q, SIGNAL(reconnect(QString,quint16,quint16,QString,QString,QString)));
    connect(m_mainWidget, SIGNAL(updateAdvise()), q, SIGNAL(updateAdvise()));
    connect(m_mainWidget, SIGNAL(uploadInOut(QStringList)), q, SIGNAL(uploadInOut(QStringList)));
    connect(m_mainWidget, SIGNAL(brightnessChanged(int)), q, SIGNAL(brightnessChanged(int)));
    connect(m_mainWidget, SIGNAL(turnOffTimeChanged(int)), q, SIGNAL(turnOffTimeChanged(int)));
    connect(m_mainWidget, SIGNAL(play(QString)), q, SIGNAL(play(QString)));
    connect(m_mainWidget, SIGNAL(pause(QString)), q, SIGNAL(pause(QString)));
    connect(m_mainWidget, SIGNAL(stop(QString)), q, SIGNAL(stop(QString)));
    connect(m_mainWidget, SIGNAL(bedCtrlPressed(int)), q, SIGNAL(bedCtrlPressed(int)));
    connect(m_mainWidget, SIGNAL(bedCtrlPressed(int)), this, SLOT(onBedCtrlPressed()));
    connect(m_mainWidget, SIGNAL(bedCtrlReleased(int)), q, SIGNAL(bedCtrlReleased(int)));
    connect(m_mainWidget, SIGNAL(bedCtrlReleased(int)), this, SLOT(onBedCtrlReleased()));
    connect(m_mainWidget, SIGNAL(infuStart()), q, SIGNAL(infuStart()));
    connect(m_mainWidget, SIGNAL(infuStop()), q, SIGNAL(infuStop()));
    connect(m_mainWidget, SIGNAL(callOutRequest()), q, SIGNAL(callOutRequest()));

    connect(m_callWidget, SIGNAL(reject()), q, SIGNAL(callTerminate()));
}

void UiModulePrivate::deinit()
{
    Q_Q(UiModule);
    //register resource
    QResource::unregisterResource("./resource/ui/res.rcc");

    //disconnect signals
    disconnect(m_standByTimer, SIGNAL(timeout()), this, SLOT(onStandbyTimeout()));
    disconnect(m_mainWidget, SIGNAL(reconnect(QString,quint16,quint16,QString,QString,QString)),
            q, SIGNAL(reconnect(QString,quint16,quint16,QString,QString,QString)));
    disconnect(m_mainWidget, SIGNAL(updateAdvise()), q, SIGNAL(updateAdvise()));
    disconnect(m_mainWidget, SIGNAL(uploadInOut(QStringList)), q, SIGNAL(uploadInOut(QStringList)));
    disconnect(m_mainWidget, SIGNAL(brightnessChanged(int)), q, SIGNAL(brightnessChanged(int)));
    disconnect(m_mainWidget, SIGNAL(turnOffTimeChanged(int)), q, SIGNAL(turnOffTimeChanged(int)));
    disconnect(m_mainWidget, SIGNAL(play(QString)), q, SIGNAL(play(QString)));
    disconnect(m_mainWidget, SIGNAL(pause(QString)), q, SIGNAL(pause(QString)));
    disconnect(m_mainWidget, SIGNAL(stop(QString)), q, SIGNAL(stop(QString)));
    disconnect(m_mainWidget, SIGNAL(bedCtrlPressed(int)), q, SIGNAL(bedCtrlPressed(int)));
    disconnect(m_mainWidget, SIGNAL(bedCtrlPressed(int)), this, SLOT(onBedCtrlPressed()));
    disconnect(m_mainWidget, SIGNAL(bedCtrlReleased(int)), q, SIGNAL(bedCtrlReleased(int)));
    disconnect(m_mainWidget, SIGNAL(bedCtrlReleased(int)), this, SLOT(onBedCtrlReleased()));
    disconnect(m_mainWidget, SIGNAL(infuStart()), q, SIGNAL(infuStart()));
    disconnect(m_mainWidget, SIGNAL(infuStop()), q, SIGNAL(infuStop()));
    disconnect(m_mainWidget, SIGNAL(callOutRequest()), q, SIGNAL(callOutRequest()));

    disconnect(m_callWidget, SIGNAL(reject()), q, SIGNAL(callTerminate()));

    delete m_standByTimer;
    delete m_progressDialog;
    delete m_callWidget;
    delete m_standbyWidget;
    delete m_mainWidget;
}

void UiModulePrivate::onStandbyTimeout()
{
    if(m_standByCount++ > 6)
    {
        if(m_standbyWidget->isHidden())
            m_standbyWidget->show();
    }
}

void UiModulePrivate::onBedCtrlPressed()
{
    m_standByTimer->stop();
}

void UiModulePrivate::onBedCtrlReleased()
{
    m_standByTimer->start();
}

