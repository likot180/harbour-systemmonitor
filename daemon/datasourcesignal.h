#ifndef DATASOURCESIGNAL_H
#define DATASOURCESIGNAL_H

#include "datasource.h"
#include "systemsnapshot.h"

class DataSourceSignal : public DataSource
{
    Q_OBJECT

public:
    explicit DataSourceSignal(SystemSnapshot *parent = 0);

signals:

public slots:
    void processSystemSnapshot();

private:
    int m_signal;
};

#endif // DATASOURCESIGNAL_H
