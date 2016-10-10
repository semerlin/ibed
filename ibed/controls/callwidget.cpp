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
    if(!m_timer->isActive())
        m_timer->start();
}

void CallWidget::endTimer()
{
    m_timer->stop();
    m_timeCnt = 0;
    ui->labelTime->setText("00:00:00");
}

void CallWidget::on_pushButtonCancel_clicked()
{
    emit reject();
}

void CallWidget::onTimeout()
{
    ++m_timeCnt;

    int sec = m_timeCnt % 60;
    int minute = m_timeCnt / 60 % 60;
    int hour = m_timeCnt / 3600;

    QByteArray time;
    time.append(hour / 10 + 0x30);
    time.append(hour % 10 + 0x30);
    time.append(':');
    time.append(minute / 10 + 0x30);
    time.append(minute % 10 + 0x30);
    time.append(':');
    time.append(sec / 10 + 0x30);
    time.append(sec % 10 + 0x30);

    ui->labelTime->setText(time.data());
}
