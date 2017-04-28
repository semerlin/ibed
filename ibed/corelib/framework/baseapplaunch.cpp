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
**  @file     baseapplaunch.cpp
**  @brief    base application launch class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "iapplaunchwidget.h"
#include "modulemanager.h"
#include "baseapplaunch.h"
#include <QApplication>
#include <QStringList>
#include <QTimer>


class BaseAppLaunchPrivate : public QObject
{
    Q_OBJECT
public:
    explicit BaseAppLaunchPrivate(BaseAppLaunch *parent, IAppLaunchWidget *widget, ModuleManager *manager);
    ~BaseAppLaunchPrivate();

public slots:
    void onModuleChanged(IAppModule *module, ModuleManager::MODULE_STATUS status);
    void onStartLaunch();

signals:
    void launchStarted(const QVariant &val);

private:
    IAppLaunchWidget *m_widget;
    ModuleManager *m_moduleManger;
    QVariant m_extVal;
    BaseAppLaunch *const q_ptr;
    Q_DECLARE_PUBLIC(BaseAppLaunch)

};

BaseAppLaunch::BaseAppLaunch(IAppLaunchWidget *widget, ModuleManager *manager) :
    d_ptr(new BaseAppLaunchPrivate(this, widget, manager))
{
}

BaseAppLaunch::~BaseAppLaunch()
{
    delete d_ptr;
}

int BaseAppLaunch::run(int argc, char **argv)
{
    Q_D(BaseAppLaunch);
    d->m_widget->show();

    QStringList val;
    for(int i = 0; i < argc; ++i)
    {
        val << argv[i];
    }

    d->m_extVal = val;
    //wait a little minute to let m_widget shown
    QTimer::singleShot(100, d_ptr, SLOT(onStartLaunch()));
    return 0;
}


BaseAppLaunchPrivate::BaseAppLaunchPrivate(BaseAppLaunch *parent, IAppLaunchWidget *widget, ModuleManager *manager) :
    m_widget(widget),
    m_moduleManger(manager),
    m_extVal(QVariant(QVariant::Invalid)),
    q_ptr(parent)
{
    connect(this, SIGNAL(launchStarted(QVariant)),
            m_moduleManger, SLOT(onLoadModules(const QVariant&)));

    connect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManager::MODULE_STATUS)),
            this, SLOT(onModuleChanged(IAppModule*,ModuleManager::MODULE_STATUS)));

    foreach(IAppModule *module, m_moduleManger->modules())
    {
        connect(module, SIGNAL(message(const QString&)),
                m_widget, SLOT(printMsg(const QString&)));
    }

}

BaseAppLaunchPrivate::~BaseAppLaunchPrivate()
{
    if(m_moduleManger != NULL)
    {
        disconnect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManager::MODULE_STATUS)),
                   this, SLOT(onModuleChanged(IAppModule*,ModuleManager::MODULE_STATUS)));
    }
}

void BaseAppLaunchPrivate::onModuleChanged(IAppModule *module, ModuleManager::MODULE_STATUS status)
{
    if(status == ModuleManager::MODULE_LOADING)
    {
        m_widget->printMsg(tr("loading module '%1' ").arg(module->name()));
    }
    else if(status == ModuleManager::MODULE_LOADED)
    {
        m_widget->increaseStep();
        m_widget->printMsg(tr("load module '%1' success").arg(module->name()));
    }
    else if(status == ModuleManager::MODULE_LOAD_FAILED)
    {
        m_widget->printMsg(tr("load module '%1 failed, error = \"%2\"").arg(module->name())
                           .arg(module->error()));
    }
    else if(status == ModuleManager::MODULE_LOAD_FINISHED)
    {
        emit q_ptr->launchFinished();
    }
}

void BaseAppLaunchPrivate::onStartLaunch()
{
    emit launchStarted(m_extVal);
}

#include "baseapplaunch.moc"
