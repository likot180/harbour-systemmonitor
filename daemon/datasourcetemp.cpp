#include "datasourcetemp.h"
#include <QString>

DataSourceTemp::DataSourceTemp(SystemSnapshot *parent) :
    DataSource(parent)
{
    m_temp = registerSystemSource("/sys/class/thermal/thermal_zone0/temp");
    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceTemp::processSystemSnapshot()
{
    const QByteArray &tempVal = getSystemData(m_temp);
    int temperature = QString(tempVal).left(2).toInt();

    emit systemDataGathered(DataSource::TemperatureDeg, temperature);
}
