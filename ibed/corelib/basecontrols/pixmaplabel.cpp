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
**  @file     pixmaplabel.cpp
**  @brief    pixmap label class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "pixmaplabel.h"
#include "ui_pixmaplabel.h"

PixmapLabel::PixmapLabel(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::PixmapLabel)
{
    ui->setupUi(this);
}

PixmapLabel::~PixmapLabel()
{
    delete ui;
}

void PixmapLabel::setPixmap(const QPixmap &pixmap)
{
    ui->labelPic->setPixmap(pixmap);
}

void PixmapLabel::setText(const QString &text)
{
    ui->labelText->setText(text);
}

void PixmapLabel::setSpacing(int spacing)
{
    ui->verticalLayout->setSpacing(spacing);
}

void PixmapLabel::setContentsMargins(int left, int top, int right, int bottom)
{
    ui->verticalLayout->setContentsMargins(left, top, right, bottom);
}
