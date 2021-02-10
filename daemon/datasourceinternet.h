#ifndef DATASOURCEINTERNET_H
#define DATASOURCEINTERNET_H

#include <QtDBus>
#include "datasource.h"
#include "systemsnapshot.h"

class DataSourceInternet : public DataSource
{
    Q_OBJECT

public:
    explicit DataSourceInternet(SystemSnapshot *parent = 0);

signals:

public slots:
    void processSystemSnapshot();
    void getWifiStrength(QDBusMessage reply);

private:
    int m_strength;
    QDBusObjectPath m_wifiPath;
};

#endif // DATASOURCEINTERNET_H
