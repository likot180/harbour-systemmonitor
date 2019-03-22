#ifndef DATASOURCEINTERNET_H
#define DATASOURCEINTERNET_H

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

private:
    int m_strength;
};

#endif // DATASOURCEINTERNET_H
