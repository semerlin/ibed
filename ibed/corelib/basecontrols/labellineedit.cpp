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

void LabelLineEdit::setReadOnly()
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
