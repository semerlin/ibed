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
**  @file     appentry.cpp
**  @brief    application entry
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/


#include <QApplication>
#include "launchwidget.h"
#include "modulemanager.h"
#include "baseapplaunch.h"
#include "appsetting.h"
#include "applogger.h"
#include "appuiconfig.h"
#include "qssloader.h"
#include "mainmodule.h"
#include <QDir>
#include <QTextCodec>
#include "appentry.h"
#include <QResource>
#include "mainwidget.h"
#include "baseapplication.h"
#include "audioformat.h"
#include "audiooutput.h"
#include <QFile>
#include <QTimer>



AppEntry &AppEntry::instance()
{
    static AppEntry m_appEntry;
    return m_appEntry;
}

int AppEntry::run(int argc, char **argv)
{
    BaseApplication app(argc, argv);

    QResource::registerResource("./resource/ui/launch.rcc");

    //support chinese
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    m_widget = new LaunchWidget;

    //load base configure
    AppSetting::instance().initialize();
    AppLogger::instance().initialize();
    AppUiConfig::instance().initialize();

    AppLogger::instance().log()->info(tr("application startup"));

    //init main module
    m_mainModule = new MainModule;

    //launch widget qss need load first
    AppLogger::instance().log()->info("initialize launch widget ui");
    QssLoader qssLoader;
    qssLoader.loadQss(m_widget, AppUiConfig::instance().value(AppUiConfig::SkinPath).toString() +
                      QDir::separator() +
                      AppUiConfig::instance().value(AppUiConfig::LaunchQss).toString());


    //start lanch
    m_widget->setSteps( m_mainModule->manger()->unloadedModules().count());

    BaseAppLaunch launcher(m_widget, m_mainModule->manger());
    connect(&launcher, SIGNAL(launchFinished()), this, SLOT(onLaunchFinished()));

    AppLogger::instance().log()->info("start launch app modules");
    launcher.run(argc, argv);

    return app.exec();
}

void AppEntry::onLaunchFinished()
{
    AppLogger::instance().log()->info(QT_TRANSLATE_NOOP("Launch", "Launch Finished!"));

    //init main module
    m_mainModule->initialize();

//    AudioFormat format;
//    format.setByteOrder(AudioFormat::LittleEndian);
//    format.setChannelCount(1);
//    format.setSampleRate(44100);
//    format.setSampleBit(AudioFormat::Bit_8);

//    AudioOutput *output = new AudioOutput(format);
//    QFile *file = new QFile;

//    file->setFileName("./resource/callout.wav");
//    bool flag = file->open( QIODevice::WriteOnly | QIODevice::Truncate );
//    file->seek(44);

//    output->start(file);
//	destroy launch widget
    QTimer::singleShot(2000, this, SLOT(onMainWidgetShown()));
}

void AppEntry::onMainWidgetShown()
{
    m_widget->hide();
    delete m_widget;
    m_widget = NULL;

}

AppEntry::AppEntry() :
    m_widget(NULL),
    m_mainModule(NULL)
{

}

AppEntry::~AppEntry()
{
    delete m_widget;
    delete m_mainModule;
}
