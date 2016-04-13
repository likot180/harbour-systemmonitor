#ifndef DATASOURCECPUSLEEP_H
#define DATASOURCECPUSLEEP_H

#include <QObject>
#include <time.h>

#include "datasource.h"
#include "systemsnapshot.h"

class DataSourceCpuSleep : public DataSource
{
    Q_OBJECT

public:
    explicit DataSourceCpuSleep(SystemSnapshot *parent = 0);

public slots:
    void processSystemSnapshot();

private:
    timespec m_boot; ///< Previous reading of CLOCK_BOOTTIME
    timespec m_mono; ///< Previous reading of CLOCK_MONOTONIC
};

#endif // DATASOURCECPUSLEEP_H
