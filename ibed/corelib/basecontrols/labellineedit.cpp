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
**  @file     labellineedit.cpp
**  @brief    label line edit class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "labellineedit.h"
#include "ui_labellineedit.h"

LabelLineEdit::LabelLineEdit(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::LabelLineEdit)
{
    ui->setupUi(this);
}

LabelLineEdit::LabelLineEdit(const QString &name, const QString &text,
                             const QString &extraName, QWidget *parent) :
    BaseWidget(parent)
{
    ui->labelName->setText(name);
    ui->lineEdit->setText(text);
    ui->labelExtraName->setText(extraName);
}

LabelLineEdit::~LabelLineEdit()
{
    delete ui;
}

QString LabelLineEdit::text() const
{
    return ui->lineEdit->text();
}

void LabelLineEdit::setName(const QString &name)
{
    ui->labelName->setText(name);
}

void LabelLineEdit::setText(const QString &text)
{
    ui->lineEdit->setText(text);
}

void LabelLineEdit::setExtraName(const QString &name)
{
    ui->labelExtraName->setText(name);
}

void LabelLineEdit::setReadOnly(bool flag)
{
    ui->lineEdit->setReadOnly(true);
}

void LabelLineEdit::setNameVisible(bool flag)
{
    ui->labelName->setVisible(flag);
}

void LabelLineEdit::setExtraNameVisible(bool flag)
{
    ui->labelExtraName->setVisible(flag);
}

void LabelLineEdit::setLayoutStrech(int name, int text, int extra)
{
    ui->horizontalLayout->setStretch(0, name);
    ui->horizontalLayout->setStretch(1, text);
    ui->horizontalLayout->setStretch(2, extra);
}

void LabelLineEdit::setSpacing(int spacing)
{
    ui->horizontalLayout->setSpacing(spacing);
}
