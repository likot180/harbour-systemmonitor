#include "datasourcesuspend.h"
#include "storage.h"

#include <QTextStream>

DataSourceSuspend::DataSourceSuspend(SystemSnapshot *parent):
    DataSource(parent)
{
    m_suspendStat = registerSystemSource("/sys/kernel/debug/suspend_stats");

    m_streams["success:"] = DataSource::SuspendSuccess;
    m_streams["fail:"] = DataSource::SuspendFail;

    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceSuspend::processSystemSnapshot()
{
    //qDebug() << "Suspend DATA";

    QTextStream stat(getSystemData(m_suspendStat));

    QMap< QString, unsigned long > current;

    while ( !stat.atEnd() )
    {
        QString cline = stat.readLine();
        if (cline.length() == 0) continue; // skip empty line

        QStringList clist = cline.split(" ",QString::SkipEmptyParts);
        if (clist.length() != 2) continue; // skip this line, it's not in form "key value"

        if (m_streams.contains(clist[0])) current[ clist[0] ] = clist[1].toULong();
    }

    if ( m_prev.size() > 0 )
    {
        for ( QMap< QString, unsigned long >::const_iterator iter = current.constBegin();
              iter != current.end();
              ++iter )
        {
            unsigned long p = m_prev.value(iter.key());
            unsigned long c = iter.value();

            double rate = (c-p) / (double)m_prevTime.secsTo(getSnapshotTime());

            //qDebug() << "Suspend: " << iter.key() << " " << p << "->" << c << " : " << rate;

            if (m_streams.contains(iter.key()) ) // must be always true
                emit systemDataGathered( m_streams[iter.key()], rate);
            else
                qDebug() << "Internal error in DataSourceSuspend::processSystemSnapshot(): " << iter.key();
        }
    }

    m_prevTime = getSnapshotTime();
    m_prev = current;
}
