#include "infusionwidget.h"
#include "ui_infusionwidget.h"
#include "circleprogressbar.h"

InfusionWidget::InfusionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfusionWidget),
    m_infuMount(200)
{
    ui->setupUi(this);

    ui->progressBarLeft->setText("55");
    ui->progressBarLeft->setValue(55);

    ui->progressBarSpeed->setCircleStyle(CircleProgressBar::Dash);
    ui->progressBarSpeed->setText("90");
    ui->progressBarSpeed->setValue(90);

    ui->labelLeft->setText(tr("输液剩余%1").arg("55%"));
    ui->labelSpeed->setText(tr("滴速%1滴/秒").arg(90));

    ui->pushButtonStart->setText(tr("开 始"));
    ui->pushButtonStop->setText(tr("停 止"));
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonReset->setText(tr("清 零"));
    ui->pushButtonReset->setEnabled(false);
    ui->pushButtonReset->hide();

    ui->comboBoxMount->insertItem(0, "50", 50);
    ui->comboBoxMount->insertItem(1, "100", 100);
    ui->comboBoxMount->insertItem(2, "250", 250);
    ui->comboBoxMount->insertItem(3, "500", 500);

}

InfusionWidget::~InfusionWidget()
{
    delete ui;
}

int InfusionWidget::infuMount() const
{
    return m_infuMount;
}

void InfusionWidget::setLeft(int left)
{
    ui->progressBarLeft->setValue(left);
    ui->progressBarLeft->setText(QString::number(left));
    ui->labelLeft->setText(tr("输液剩余%1%").arg(left));
}

void InfusionWidget::setSpeed(int speed)
{
    ui->labelSpeed->setText(tr("滴速%1滴/分").arg(speed));
    if(speed >= 100)
        ui->progressBarSpeed->setText("E");
    else
        ui->progressBarSpeed->setText(QString::number(speed));
    ui->progressBarSpeed->setValue(speed);
}

void InfusionWidget::on_pushButtonStart_clicked()
{
    ui->progressBarLeft->setValue(100);
    ui->progressBarLeft->setText("0");
    ui->labelLeft->setText(tr("输液剩余%1").arg("0%"));
    ui->labelSpeed->setText(tr("滴速%1滴/秒").arg(0));
    ui->progressBarSpeed->setText("0");
    ui->progressBarSpeed->setValue(0);
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonStart->setEnabled(false);
    m_infuMount = ui->comboBoxMount->itemData(ui->comboBoxMount->currentIndex()).toInt();
    ui->comboBoxMount->setEnabled(false);
    emit infuStart();
}

void InfusionWidget::on_pushButtonStop_clicked()
{
    ui->progressBarLeft->setValue(100);
    ui->progressBarLeft->setText("0");
    ui->labelLeft->setText(tr("输液剩余%1").arg("0%"));
    ui->labelSpeed->setText(tr("滴速%1滴/秒").arg(0));
    ui->progressBarSpeed->setText("0");
    ui->progressBarSpeed->setValue(0);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonStart->setEnabled(true);
    ui->comboBoxMount->setEnabled(true);
    emit infuStop();
}

void InfusionWidget::on_pushButtonReset_clicked()
{
//    ui->progressBarLeft->setValue(100);
//    ui->progressBarLeft->setText(0);
//    ui->labelLeft->setText(tr("输液剩余%1").arg("0%"));
}
