#include "baseinfowidget.h"
#include "ui_baseinfowidget.h"

BaseInfoWidget::BaseInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseInfoWidget)
{
    ui->setupUi(this);

    ui->labelName->setText(tr("XX"));
    ui->labelSex->setText(tr("XX"));
    ui->labelAge->setText(tr("XX"));

    ui->widgetBedNum->setSpacing(10);
    ui->widgetBedNum->setContentsMargin(5, 0, 30, 0);
    ui->widgetBedNum->setPixmap(QPixmap(":/res/images/bed.png"));
    ui->widgetBedNum->setText(tr("Num"));

    ui->labelLevel->setText(tr("XX"));

    ui->widgetTime->setContentsMargins(5, 0, 5, 5);
    ui->widgetTime->setPixmap(QPixmap(":/res/images/checkin.png"));
    ui->widgetTime->setInfo(tr("Time"));
    ui->widgetTime->setData(tr("XX"));

    ui->widgetDoctor->setContentsMargins(5, 0, 5, 5);
    ui->widgetDoctor->setPixmap(QPixmap(":/res/images/doctor.png"));
    ui->widgetDoctor->setInfo(tr("Doctor"));
    ui->widgetDoctor->setData(tr("XX"));

    ui->widgetEat->setContentsMargins(5, 0, 5, 5);
    ui->widgetEat->setPixmap(QPixmap(":/res/images/eat.png"));
    ui->widgetEat->setInfo(tr("Eat"));
    ui->widgetEat->setData(tr("XX"));

    ui->widgetNurse->setContentsMargins(5, 0, 5, 5);
    ui->widgetNurse->setPixmap(QPixmap(":/res/images/nurse.png"));
    ui->widgetNurse->setInfo(tr("Nurse"));
    ui->widgetNurse->setData(tr("XX"));

    ui->widgetAdvise->setInfo(tr("Advise"));
    ui->widgetAdvise->setPixmap(QPixmap(":/res/images/advise.png"));
    ui->widgetAdvise->setData(tr("No advise"));
    ui->widgetAdvise->setDataReadOnly(true);

    ui->widgetAllergy->setInfo(tr("Allergy"));
    ui->widgetAllergy->setPixmap(QPixmap(":/res/images/medicine.png"));
    ui->widgetAllergy->setData(tr("No allergy"));
    ui->widgetAllergy->setDataReadOnly(true);
}

BaseInfoWidget::~BaseInfoWidget()
{
    delete ui;
}
