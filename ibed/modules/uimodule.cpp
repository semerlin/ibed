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
**  @file     uimodule.cpp
**  @brief    application ui display control
**  @details  control ui display, message update, actions
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include <QTimer>
#include "mainwidget.h"
#include "standbywidget.h"
#include "callwidget.h"
#include "progressdialog.h"
#include "numipmethod.h"
#include "uimodule.h"
#include <QResource>
#include <QApplication>
#include "uimodule_p.h"

UiModule::UiModule(const QString &name) :
    BaseAppModule(name),
    d_ptr(new UiModulePrivate(this))
{

}

UiModule::~UiModule()
{
    delete d_ptr;
}

bool UiModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    Q_D(UiModule);

    d->init();

    //register resource
    QResource::registerResource("./resource/ui/res.rcc");

    return true;
}

void UiModule::unload()
{
    Q_D(UiModule);
    d->deinit();
}

void UiModule::showMainWidget()
{
    Q_D(UiModule);
    d->m_mainWidget->show();
    d->m_standByTimer->start();
}

int UiModule::infuMount() const
{
    return d_ptr->m_mainWidget->infuMount();
}


void UiModule::onRegistered()
{
    Q_D(UiModule);
    d->m_mainWidget->setNetworkStatus(QT_TRANSLATE_NOOP("Server", "连接成功!"));
}

void UiModule::onRegisterTimeout()
{
    Q_D(UiModule);
    d->m_mainWidget->setNetworkStatus(QT_TRANSLATE_NOOP("Server", "连接失败!"));
}

void UiModule::onDisconnect()
{
    Q_D(UiModule);
    d->m_mainWidget->setNetworkStatus(QT_TRANSLATE_NOOP("Server", "连接失败!"));
}

void UiModule::onNameChanged(const QString &name)
{
    Q_D(UiModule);
    d->m_mainWidget->setName(name);
    d->m_standbyWidget->setName(name);
}

void UiModule::onSexChanged(const QString &sex)
{
    Q_D(UiModule);
    d->m_mainWidget->setSex(sex);
}

void UiModule::onAgeChanged(const QString &age)
{
    Q_D(UiModule);
    d->m_mainWidget->setAge(age);
    d->m_standbyWidget->setAge(age.toInt());
}

void UiModule::onBedChanged(const QString &bed)
{
    Q_D(UiModule);
    d->m_mainWidget->setBed(bed);
    d->m_standbyWidget->setBedNum(bed.toInt());
}

void UiModule::onLevelChanged(const QString &level)
{
    Q_D(UiModule);
    QString display;
    switch(level.toInt())
    {
    case 0:
        display = "特级护理";
        d->m_mainWidget->setLevelColor(Qt::white, Qt::red);
        break;
    case 1:
        display = "一级护理";
        d->m_mainWidget->setLevelColor(Qt::white, QColor(255, 0, 255));
        break;
    case 2:
        display = "二级护理";
        d->m_mainWidget->setLevelColor(Qt::white, Qt::blue);
        break;
    case 3:
        display = "三级护理";
        d->m_mainWidget->setLevelColor(Qt::gray, Qt::white);
        break;
    default:
        display = "三级护理";
        d->m_mainWidget->setLevelColor(Qt::gray, Qt::white);
        break;
    }

    d->m_mainWidget->setLevel(display);
    d->m_standbyWidget->setNursery(level.toInt());
}

void UiModule::onTimeChanged(const QString &time)
{
    Q_D(UiModule);
    int index = time.indexOf("/");
    d->m_mainWidget->setTime(time.left(index) + "\n" + time.right(time.count() - index - 1));
}

void UiModule::onDoctorChanged(const QString &doctor)
{
    Q_D(UiModule);
    d->m_mainWidget->setDoctor(doctor);
}

void UiModule::onEatChanged(const QString &eat)
{
    Q_D(UiModule);
    d->m_mainWidget->setEat(eat);
}

void UiModule::onNurseChanged(const QString &nurse)
{
    Q_D(UiModule);
    d->m_mainWidget->setNurse(nurse);
}

void UiModule::onAdviseChanged(const QString &advise)
{
    Q_D(UiModule);
    d->m_mainWidget->setAdvise(advise);
}

void UiModule::onAllergyChanged(const QString &allergy)
{
    Q_D(UiModule);
    d->m_mainWidget->setAllergy(allergy);
}

void UiModule::onAdviseUpdate(const QString &data)
{
    Q_D(UiModule);
    d->m_mainWidget->addAdvise(data);
}

void UiModule::onLightIntensityChanged(int intensity)
{
    Q_D(UiModule);
    d->m_standbyWidget->setLightIntensity(QString::number(intensity));
}

void UiModule::onTemperatureChanged(int temper)
{
    Q_D(UiModule);
    d->m_standbyWidget->setTemperature(QString::number(temper)+"℃");
}

void UiModule::onHumidityChanged(int humidity)
{
    Q_D(UiModule);
    d->m_standbyWidget->setHumidity(QString::number(humidity) + "%");
}

void UiModule::onAudioIntensityChanged(int intensity)
{
    Q_D(UiModule);
    d->m_standbyWidget->setAudioIntensity(QString::number(intensity));
}

void UiModule::onClicked()
{
    Q_D(UiModule);
    d->m_standByCount = 0;
    if(!d->m_standbyWidget->isHidden())
        d->m_standbyWidget->hide();
}

void UiModule::onWeightChanged(double weight)
{
    Q_D(UiModule);
    int temp = static_cast<int>(weight);
    d->m_standbyWidget->setWeight(QString::number(temp)+"Kg");
    d->m_mainWidget->setWeight(weight);
}

void UiModule::onInfuInputChanged(int mount)
{
    Q_D(UiModule);
    if(d->m_mainWidget->infuMount() > 0)
    {
        int left = (d->m_mainWidget->infuMount() - mount) * 100 / d->m_mainWidget->infuMount();
        d->m_mainWidget->setLeft(left);
    }
}


void UiModule::onInfuSpeedChanged(int speed)
{
    Q_D(UiModule);
    d->m_mainWidget->setSpeed(speed);
}

void UiModule::onCallOutConnecting()
{
    Q_D(UiModule);
    d->m_callWidget->show();
    d->m_callWidget->setGeometry(321, 88, 158, 304);
}

void UiModule::onCallInConnecting()
{
    Q_D(UiModule);
    d->m_callWidget->show();
    d->m_callWidget->setGeometry(321, 88, 158, 304);
}

void UiModule::onCallConnected()
{
    Q_D(UiModule);
    d->m_callWidget->beginTimer();
}

void UiModule::onCallTerminate()
{
    Q_D(UiModule);
    d->m_callWidget->endTimer();
    d->m_callWidget->hide();
}



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

UiModulePrivate::~UiModulePrivate()
{
    delete m_standByTimer;
    delete m_progressDialog;
    delete m_callWidget;
    delete m_standbyWidget;
    delete m_mainWidget;
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

