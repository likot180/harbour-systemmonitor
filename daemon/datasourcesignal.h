#ifndef DATASOURCESIGNAL_H
#define DATASOURCESIGNAL_H

#include <QtDBus>
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
    void getNetworkStatus(QDBusMessage reply);

private:
    int m_signal;
};

#endif // DATASOURCESIGNAL_H
