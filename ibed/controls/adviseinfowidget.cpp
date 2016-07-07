#include "adviseinfowidget.h"
#include <QAbstractTableModel>
#include <QModelIndex>

class AdviseInfoPrivate : public QAbstractTableModel
{
public:
    AdviseInfoPrivate(QObject *parent = 0);
    AdviseInfoPrivate(const QList<QStringList> &info, QObject *parent = 0);

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
    QTableView(parent),
    d(new AdviseInfoPrivate)
{
    d->clearData();

    setModel(d);
}

void AdviseInfoWidget::clearData()
{
    d->clearData();
}

void AdviseInfoWidget::appendData(const QStringList &data)
{
    d->appendData(data);
}



AdviseInfoPrivate::AdviseInfoPrivate(QObject *parent) :
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

AdviseInfoPrivate::AdviseInfoPrivate(const QList<QStringList> &info, QObject *parent) :
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

void AdviseInfoPrivate::clearData()
{
    m_adviseInfo.clear();
}

void AdviseInfoPrivate::appendData(const QStringList &info)
{
    m_adviseInfo.append(info);
}

int AdviseInfoPrivate::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_adviseInfo.count();
}

int AdviseInfoPrivate::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_header.count();
}

QVariant AdviseInfoPrivate::data(const QModelIndex &index, int role) const
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

QVariant AdviseInfoPrivate::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)

    if(role != Qt::DisplayRole)
        return QVariant();

    return m_header.at(section);
}
