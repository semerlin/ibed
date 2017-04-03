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
**  @file     callmanage.cpp
**  @brief    manage all call status
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "callbtn.h"
#include "call.h"
#include "callmanage.h"
#include "sip.h"
#include "appsetting.h"
#include "servermanger.h"
#include "callmanage_p.h"

CallManage::CallManage() :
    d_ptr(new CallManagePrivate(this))
{
#ifdef TARGET_IMX
    Q_D(CallManage);
    connect(d->m_btn, SIGNAL(callPressed()), this, SLOT(onCallOutRequest()));
    connect(d->m_btn, SIGNAL(cancelPressed()), this, SLOT(onTerminate()));
#endif
}

CallManage::~CallManage()
{
    delete d_ptr;
}

bool CallManage::init()
{
    Q_D(CallManage);
#ifdef TARGET_IMX
    if(!d->m_btn->init())
        return false;
#endif

    d->initSip();

    return true;
}


void CallManage::regToServer()
{
    Q_D(CallManage);
    d->m_sip->reg(AppSetting::instance().value(AppSetting::DeviceNum).toString(),
                       "intellicare", ServerManger::instance().address(ServerManger::Sip));
}


void CallManage::onCallOutRequest()
{
    Q_D(CallManage);
    if(d->m_isIdle)
    {
        d->m_isIdle = false;

        d->m_sip->reg(AppSetting::instance().value(AppSetting::DeviceNum).toString(),
                           "intellicare", ServerManger::instance().address(ServerManger::Sip));
        d->m_sip->dial("0");
    }
}

void CallManage::onTerminate()
{
    Q_D(CallManage);
    d->m_sip->hangup();
    d->m_sip->reset();
    d->m_isIdle = true;
}


CallManagePrivate::CallManagePrivate(CallManage *parent) :
    m_sip(new Sip),
    m_isIdle(true),
    m_isInited(false),
    q_ptr(parent)
{
#ifdef TARGET_IMX
    m_btn = new CallBtn;
#endif

    connect(m_sip, SIGNAL(stateChanged(CallState,CallState)), this, SLOT(onStateChanged(CallState,CallState)));

}

CallManagePrivate::~CallManagePrivate()
{
    delete m_sip;
}

void CallManagePrivate::onStateChanged(CallState prev, CallState current)
{
    Q_UNUSED(prev)
    Q_Q(CallManage);

    switch(current)
    {
    case Calling:
    case Connecting:
    case Early:
        emit q->callOutConnecting();
        break;
    case Incoming:
        m_isIdle = false;
        m_sip->answer();
        emit q->callInConnecting();
        break;
    case Confirmed:
        emit q->callConnected();
        break;
    case Disconnected:
        m_sip->reset();
        m_isIdle = true;
        emit q->callTerminate();
        break;
    default:
        break;
    }

}

void CallManagePrivate::initSip()
{
    if(m_isInited)
    {
        m_sip->destroy();
        m_isInited = false;
    }

    m_sip->setPort(ServerManger::instance().port(ServerManger::Sip));

    if(!m_sip->init())
        return;

    if(!m_sip->reg(AppSetting::instance().value(AppSetting::DeviceNum).toString(),
                   "intellicare", ServerManger::instance().address(ServerManger::Sip)))
        return;

    m_isInited = true;
}
