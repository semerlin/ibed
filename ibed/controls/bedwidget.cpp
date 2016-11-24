#include "bedwidget.h"
#include "ui_bedwidget.h"
#include "boost/foreach.hpp"
#include <QTimer>
#include <QDateTime>
#include <QDebug>

BedWidget::BedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BedWidget),
    m_timer(new QTimer)
{
    ui->setupUi(this);

    ui->labelHuman->setPixmap(QString(":/res/images/leftup1.png"));
    ui->labelHuman1->setPixmap(QString(":/res/images/rightup1.png"));
    ui->labelWeightName->setText(tr("总重量"));
    ui->labelWeightPic->setPixmap(QString(":/res/images/weight.png"));
    ui->labelWeight->setText("0Kg");
    initButtons();

    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_pressIDs.clear();
    m_releasedIDs.clear();
    m_timer->start();
}

BedWidget::~BedWidget()
{
    delete ui;
    delete m_timer;
}

void BedWidget::setWeight(const QString &weight)
{
    ui->labelWeight->setText(weight);
}

void BedWidget::initButtons()
{
    QList<IconPushButton *> allPButtons = this->findChildren<IconPushButton *>();
    BOOST_FOREACH(IconPushButton *btn, allPButtons)
    {
        btn->setIconSize(QSize(72, 72));
        connect(btn, SIGNAL(pressed()), this, SLOT(onButtonPress()));
        connect(btn, SIGNAL(released()), this, SLOT(onButtonReleased()));
    }

    ui->pushButton1->setIcons(QStringList()
                             << ":/res/images/left1_l.png"
                             << ":/res/images/left1_h.png");

    ui->pushButton2->setIcons(QStringList()
                             << ":/res/images/left1_l.png"
                             << ":/res/images/left1_h.png");

    ui->pushButton3->setIcons(QStringList()
                             << ":/res/images/left2_l.png"
                             << ":/res/images/left2_h.png");

    ui->pushButton4->setIcons(QStringList()
                             << ":/res/images/left2_l.png"
                             << ":/res/images/left2_h.png");

    ui->pushButton5->setIcons(QStringList()
                             << ":/res/images/right1-2_l.png"
                             << ":/res/images/right1-2_h.png");

    ui->pushButton6->setIcons(QStringList()
                             << ":/res/images/right2_l.png"
                             << ":/res/images/right2_h.png");

    ui->pushButton7->setIcons(QStringList()
                             << ":/res/images/left1_l.png"
                             << ":/res/images/left1_h.png");

    ui->pushButton8->setIcons(QStringList()
                             << ":/res/images/right4_l.png"
                             << ":/res/images/right4_h.png");

    ui->pushButton9->setIcons(QStringList()
                             << ":/res/images/right5_l.png"
                             << ":/res/images/right5_h.png");

    ui->pushButton10->setIcons(QStringList()
                             << ":/res/images/right6_l.png"
                             << ":/res/images/right6_h.png");

    ui->pushButton11->setIcons(QStringList()
                             << ":/res/images/right7_l.png"
                             << ":/res/images/right7_h.png");

    ui->pushButton12->setIcons(QStringList()
                             << ":/res/images/left2_l.png"
                             << ":/res/images/left2_h.png");

    ui->pushButton13->setIcons(QStringList()
                             << ":/res/images/right8_l.png"
                             << ":/res/images/right8_h.png");

    ui->pushButton14->setIcons(QStringList()
                             << ":/res/images/right9_l.png"
                             << ":/res/images/right9_h.png");

    ui->pushButton15->setIcons(QStringList()
                             << ":/res/images/right10_l.png"
                             << ":/res/images/right10_h.png");

    ui->pushButton16->setIcons(QStringList()
                             << ":/res/images/right11_l.png"
                             << ":/res/images/right11_h.png");

    ui->pushButton17->setIcons(QStringList()
                             << ":/res/images/right12_l.png"
                             << ":/res/images/right12_h.png");

    ui->pushButton18->setIcons(QStringList()
                             << ":/res/images/right13_l.png"
                             << ":/res/images/right13_h.png");

    ui->pushButton19->setIcons(QStringList()
                             << ":/res/images/right14_l.png"
                               << ":/res/images/right14_h.png");
}

void BedWidget::onButtonPress()
{
    IconPushButton *btn = qobject_cast<IconPushButton *>(sender());
    btn->changeToIcon(1);
    QString name = btn->objectName();
    name.remove("pushButton");
    m_pressIDs.enqueue(qMakePair(qMakePair(name.toInt(), QDateTime::currentMSecsSinceEpoch()), false));
//    emit buttonPress(name.toInt());
}

void BedWidget::onButtonReleased()
{
    IconPushButton *btn = qobject_cast<IconPushButton *>(sender());
    btn->changeToIcon(0);
    QString name = btn->objectName();
    name.remove("pushButton");
    m_releasedIDs.enqueue(qMakePair(qMakePair(name.toInt(), QDateTime::currentMSecsSinceEpoch()), false));
//    emit buttonReleased(name.toInt());
}

void BedWidget::onTimeout()
{
    QPair<QPair<int, qint64>, bool> pressID;
    QPair<QPair<int, qint64>, bool> releasedID;
    quint64 ellipseTime = 0;

    //check released buttons first
    for(int i = 0; i < m_releasedIDs.count(); ++i)
    {
        pressID = m_pressIDs.dequeue();
        releasedID = m_releasedIDs.dequeue();
        if(pressID.first.first != releasedID.first.first)
            continue;
        else
        {
            ellipseTime = releasedID.first.second - pressID.first.second;
            if(ellipseTime >= 500)
            {
                //valid button release
                emit buttonReleased(releasedID.first.first);
            }

//            qDebug() << QString("key press %1 ms").arg(ellipseTime);
        }
    }

    //check pressed buttons
    for(int i = 0; i < m_pressIDs.count(); ++i)
    {
        pressID = m_pressIDs.at(i);
        ellipseTime = QDateTime::currentMSecsSinceEpoch() - pressID.first.second;
        if(ellipseTime >= 500)
        {
            //valid button press
            if(!pressID.second)
            {
                emit buttonPress(pressID.first.first);
                m_pressIDs[i].second = true;
            }
        }
    }
}
