#include "callwidget.h"
#include "ui_callwidget.h"
#include <QTimer>
#include <QTime>

CallWidget::CallWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CallWidget),
    m_timer(new QTimer(this)),
    m_timeCnt(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->labelStep->setText(QT_TRANSLATE_NOOP("Call", "护士站"));
    ui->labelTime->setText("00:00:00");

    ui->pushButtonAnswer->hide();

    connect(m_timer,SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_timer->setInterval(1000);
}

CallWidget::~CallWidget()
{
    delete m_timer;
    delete ui;
}

void CallWidget::beginTimer()
{
    m_timeCnt = 0;
    ui->labelTime->setText("00:00:00");
    m_timer->start();
}

void CallWidget::endTimer()
{
    m_timer->stop();
}

void CallWidget::on_pushButtonCancel_clicked()
{
    emit reject();
}

void CallWidget::onTimeout()
{
    ++m_timeCnt;

    QTime time(0, 0);
    time.addSecs(m_timeCnt);

    ui->labelTime->setText(time.toString());
}
