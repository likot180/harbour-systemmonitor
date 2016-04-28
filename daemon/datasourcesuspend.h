#ifndef DATASOURCESUSPEND_H
#define DATASOURCESUSPEND_H

#include <QObject>
#include <QMap>
#include "datasource.h"
#include "systemsnapshot.h"

class DataSourceSuspend:
        public DataSource
{
    Q_OBJECT

public:
    DataSourceSuspend(SystemSnapshot *parent = 0);

public slots:
    void processSystemSnapshot();

private:
    int m_suspendStat;
    QMap< QString, DataSource::Type > m_streams;
    QMap< QString, unsigned long > m_prev;
    QDateTime m_prevTime;
};

#endif // DATASOURCESUSPEND_H
