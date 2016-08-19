#include "adviseinfowidget.h"
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QHeaderView>
#include <QTableWidget>
#include <QMouseEvent>
#include <QScrollBar>

class AdviseInfoModel : public QAbstractTableModel
{
public:
    AdviseInfoModel(QObject *parent = 0);
    AdviseInfoModel(const QList<QStringList> &info, QObject *parent = 0);

public:
    void clearData(void);
    void appendData(const QStringList &info);

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<QStringList> m_adviseInfo;
    QStringList m_header;
};

AdviseInfoWidget::AdviseInfoWidget(QWidget *parent) :
    LineTableView(Qt::Vertical, parent),
    m_model(new AdviseInfoModel)
{
    m_model->clearData();
    verticalHeader()->hide();

    setModel(m_model);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    horizontalHeader()->setStretchLastSection(true);
}

void AdviseInfoWidget::clearData()
{
    m_model->clearData();
}

void AdviseInfoWidget::appendData(const QStringList &data)
{
    m_model->appendData(data);
}

void AdviseInfoWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPoint = event->pos();
    LineTableView::mousePressEvent(event);
}

void AdviseInfoWidget::mouseMoveEvent(QMouseEvent *event)
{
    verticalScrollBar()->setValue(verticalScrollBar()->value() +
                                  m_lastPoint.y() - event->pos().y());
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() +
                                  m_lastPoint.x() - event->pos().x());

    m_lastPoint = event->pos();
}



AdviseInfoModel::AdviseInfoModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_header = QStringList()
            << QT_TRANSLATE_NOOP("AdviseInfo", "编号")
            << QT_TRANSLATE_NOOP("AdviseInfo", "类别")
            << QT_TRANSLATE_NOOP("AdviseInfo", "医生姓名")
            << QT_TRANSLATE_NOOP("AdviseInfo", "记录时间")
            << QT_TRANSLATE_NOOP("AdviseInfo", "医嘱编码")
            << QT_TRANSLATE_NOOP("AdviseInfo", "内容")
            << QT_TRANSLATE_NOOP("AdviseInfo", "状态")
            << QT_TRANSLATE_NOOP("AdviseInfo", "结束时间");
}

AdviseInfoModel::AdviseInfoModel(const QList<QStringList> &info, QObject *parent) :
    QAbstractTableModel(parent)
{
    m_adviseInfo = info;

    m_header = QStringList()
            << QT_TRANSLATE_NOOP("AdviseInfo", "编号")
            << QT_TRANSLATE_NOOP("AdviseInfo", "类别")
            << QT_TRANSLATE_NOOP("AdviseInfo", "医生姓名")
            << QT_TRANSLATE_NOOP("AdviseInfo", "记录时间")
            << QT_TRANSLATE_NOOP("AdviseInfo", "医嘱编码")
            << QT_TRANSLATE_NOOP("AdviseInfo", "内容")
            << QT_TRANSLATE_NOOP("AdviseInfo", "状态")
            << QT_TRANSLATE_NOOP("AdviseInfo", "结束时间");
}

void AdviseInfoModel::clearData()
{
    beginRemoveRows(QModelIndex(), 0, m_adviseInfo.count() - 1);
    endRemoveRows();
    m_adviseInfo.clear();
}

void AdviseInfoModel::appendData(const QStringList &info)
{
    beginInsertRows(QModelIndex(), m_adviseInfo.count(), m_adviseInfo.count());
    m_adviseInfo.append(info);
    endInsertRows();
}

int AdviseInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_adviseInfo.count();
}

int AdviseInfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_header.count();
}

QVariant AdviseInfoModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();

        if((row >= 0) && (column >= 0))
        {
            if(m_adviseInfo.count() > row)
            {
                if(m_adviseInfo.at(row).count() > column)
                {
                    return m_adviseInfo.at(row).at(column);
                }
            }
        }

        return QVariant();
    }
    else
        return QVariant();
}

QVariant AdviseInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)

    if(role != Qt::DisplayRole)
        return QVariant();

    return m_header.at(section);
}
