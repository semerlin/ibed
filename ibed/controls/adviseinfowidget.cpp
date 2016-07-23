#include "adviseinfowidget.h"
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QHeaderView>

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
}

void AdviseInfoWidget::clearData()
{
    m_model->clearData();
}

void AdviseInfoWidget::appendData(const QStringList &data)
{
    m_model->appendData(data);
}



AdviseInfoModel::AdviseInfoModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_header = QStringList()
            << "Num"
            << "Type"
            << "Name"
            << "Record Time"
            << "Code"
            << "Detail"
            << "Status"
            << "End Time";
}

AdviseInfoModel::AdviseInfoModel(const QList<QStringList> &info, QObject *parent) :
    QAbstractTableModel(parent)
{
    m_adviseInfo = info;

    m_header = QStringList()
            << "Num"
            << "Type"
            << "Name"
            << "Record Time"
            << "Code"
            << "Detail"
            << "Status"
            << "End Time";
}

void AdviseInfoModel::clearData()
{
    m_adviseInfo.clear();
}

void AdviseInfoModel::appendData(const QStringList &info)
{
    m_adviseInfo.append(info);
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