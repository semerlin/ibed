#include "baseinfowidget.h"
#include "ui_baseinfowidget.h"

BaseInfoWidget::BaseInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseInfoWidget)
{
    ui->setupUi(this);

    ui->labelName->setText(QT_TRANSLATE_NOOP("BaseInfo", "未知"));
    ui->labelSex->setText(QT_TRANSLATE_NOOP("BaseInfo", "未知"));
    ui->labelAge->setText(QT_TRANSLATE_NOOP("BaseInfo", "未知"));

    ui->widgetBedNum->setSpacing(10);
    ui->widgetBedNum->setContentsMargin(5, 0, 30, 0);
    ui->widgetBedNum->setPixmap(QPixmap(":/res/images/bed.png"));
    ui->widgetBedNum->setText(QT_TRANSLATE_NOOP("BaseInfo", "病床号"));

    ui->labelLevel->setText(tr("XX"));

    ui->widgetTime->setContentsMargins(5, 0, 5, 5);
    ui->widgetTime->setPixmap(QPixmap(":/res/images/checkin.png"));
    ui->widgetTime->setInfo(QT_TRANSLATE_NOOP("BaseInfo", "入院时间"));
    ui->widgetTime->setData(QT_TRANSLATE_NOOP("BaseInfo", "未知"));

    ui->widgetDoctor->setContentsMargins(5, 0, 5, 5);
    ui->widgetDoctor->setPixmap(QPixmap(":/res/images/doctor.png"));
    ui->widgetDoctor->setInfo(QT_TRANSLATE_NOOP("BaseInfo", "责任医生"));
    ui->widgetDoctor->setData(QT_TRANSLATE_NOOP("BaseInfo", "未知"));

    ui->widgetEat->setContentsMargins(5, 0, 5, 5);
    ui->widgetEat->setPixmap(QPixmap(":/res/images/eat.png"));
    ui->widgetEat->setInfo(QT_TRANSLATE_NOOP("BaseInfo", "饮食类别"));
    ui->widgetEat->setData(QT_TRANSLATE_NOOP("BaseInfo", "未知"));

    ui->widgetNurse->setContentsMargins(5, 0, 5, 5);
    ui->widgetNurse->setPixmap(QPixmap(":/res/images/nurse.png"));
    ui->widgetNurse->setInfo(QT_TRANSLATE_NOOP("BaseInfo", "责任护士"));
    ui->widgetNurse->setData(QT_TRANSLATE_NOOP("BaseInfo", "未知"));

    ui->widgetAdvise->setInfo(QT_TRANSLATE_NOOP("BaseInfo", "医生建议"));
    ui->widgetAdvise->setPixmap(QPixmap(":/res/images/advise.png"));
    ui->widgetAdvise->setData(QT_TRANSLATE_NOOP("BaseInfo", "无"));
    ui->widgetAdvise->setDataReadOnly(true);

    ui->widgetAllergy->setInfo(QT_TRANSLATE_NOOP("BaseInfo", "药物过敏史"));
    ui->widgetAllergy->setPixmap(QPixmap(":/res/images/medicine.png"));
    ui->widgetAllergy->setData(QT_TRANSLATE_NOOP("BaseInfo", "无"));
    ui->widgetAllergy->setDataReadOnly(true);
}

BaseInfoWidget::~BaseInfoWidget()
{
    delete ui;
}

void BaseInfoWidget::setName(const QString &name)
{
    ui->labelName->setText(name);
}

void BaseInfoWidget::setSex(const QString &sex)
{
    ui->labelSex->setText(sex);
}

void BaseInfoWidget::setAge(const QString &age)
{
    ui->labelAge->setText(age);
}

void BaseInfoWidget::setBed(const QString &bed)
{
    ui->widgetBedNum->setBedNum(bed.toInt());
}

void BaseInfoWidget::setLevel(const QString &level)
{
    ui->labelLevel->setText(level);
}

void BaseInfoWidget::setTime(const QString &time)
{
    ui->widgetTime->setData(time);
}

void BaseInfoWidget::setDoctor(const QString &doctor)
{
    ui->widgetDoctor->setData(doctor);
}

void BaseInfoWidget::setEat(const QString &eat)
{
    ui->widgetEat->setData(eat);
}

void BaseInfoWidget::setNurse(const QString &nurse)
{
    ui->widgetNurse->setData(nurse);
}

void BaseInfoWidget::setAdvise(const QString &advise)
{
    ui->widgetAdvise->setData(advise);
}

void BaseInfoWidget::setAllergy(const QString &allergy)
{
    ui->widgetAllergy->setData(allergy);
}
