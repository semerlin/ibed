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
**  @file     callbtn.cpp
**  @brief    call button hardware use class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include <QTimer>
#include "callbtn.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "applogger.h"
#include "log4qt/logger.h"
#include "callbtn_p.h"


CallBtn::CallBtn() :
    d_ptr(new CallBtnPrivate(this))
{
}

CallBtn::~CallBtn()
{
    delete d_ptr;
}

bool CallBtn::init()
{
    Q_D(CallBtn);
    d->m_fd = ::open("/dev/callbtn", O_RDONLY);
    if(d->m_fd < 0)
    {
        AppLogger::instance().log()->error("open call button failed");
        return false;
    }
    AppLogger::instance().log()->info("open call button success");

    d->m_timer->start();

    return true;
}



CallBtnPrivate::CallBtnPrivate(CallBtn *parent) :
    m_fd(-1),
    m_timer(new QTimer(this)),
    q_ptr(parent)
{
    m_timer->setInterval(500);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onMonitorKeys()));
}

CallBtnPrivate::~CallBtnPrivate()
{
    ::close(m_fd);
}

void CallBtnPrivate::onMonitorKeys()
{
    if(m_fd > 0)
    {
        Q_Q(CallBtn);
        char val = 0;
        if(::read(m_fd, &val, 1) != -1)
        {
            if(val == 1)
            {
                emit q->callPressed();
            }
            else if(val == 2)
            {
                emit q->cancelPressed();
            }
        }
    }

}
