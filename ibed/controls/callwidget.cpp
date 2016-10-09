#include "callwidget.h"
#include "ui_callwidget.h"

CallWidget::CallWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CallWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->labelStep->setText(QT_TRANSLATE_NOOP("Call", "护士站"));
    ui->labelTime->setText("00:00:00");

    ui->pushButtonAnswer->hide();
}

CallWidget::~CallWidget()
{
    delete ui;
}

void CallWidget::on_pushButtonCancel_clicked()
{
    emit reject();
}
