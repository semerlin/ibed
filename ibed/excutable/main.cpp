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
**  @file     main.cpp
**  @brief    application entry
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @date     2016-04-09
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "appentry.h"

int main(int argc, char *argv[])
{
    return AppEntry::instance().run(argc, argv);
}
