#include "datasourcecpusleep.h"

#include <time.h>
#include <QDebug>

DataSourceCpuSleep::DataSourceCpuSleep(SystemSnapshot *parent) :
    DataSource(parent)
{
    m_boot.tv_sec = 0;
    m_boot.tv_nsec = 0;
    m_mono.tv_sec = 0;
    m_mono.tv_nsec = 0;

    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceCpuSleep::processSystemSnapshot()
{
    timespec b, m;
    if ( clock_gettime(CLOCK_BOOTTIME, &b ) < 0 ||
         clock_gettime(CLOCK_MONOTONIC, &m ) < 0)
    {
        qDebug() << "Data sleep: error getting one of the times";
        return;
    }

    double db = b.tv_sec - m_boot.tv_sec + 1e-9 * (b.tv_nsec - m_boot.tv_nsec);
    double dm = m.tv_sec - m_mono.tv_sec + 1e-9 * (m.tv_nsec - m_mono.tv_nsec);
    double sleep = (db-dm) / db * 100;
    //qDebug() << "Sleep: " << dm << " / " << db << ": " << sleep;

    m_boot = b;
    m_mono = m;

    emit systemDataGathered(DataSource::CpuSleep, sleep);
}
