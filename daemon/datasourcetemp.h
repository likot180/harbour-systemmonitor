#ifndef DATASOURCETEMP_H
#define DATASOURCETEMP_H

#include "datasource.h"
#include "systemsnapshot.h"

class DataSourceTemp : public DataSource
{
    Q_OBJECT

public:
    explicit DataSourceTemp(SystemSnapshot *parent = 0);

signals:

public slots:
    void processSystemSnapshot();

private:
    int m_temp;
};

#endif // DATASOURCETEMP_H
