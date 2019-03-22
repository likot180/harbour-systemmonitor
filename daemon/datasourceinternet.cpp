#include "datasourceinternet.h"
#include <QString>

DataSourceInternet::DataSourceInternet(SystemSnapshot *parent) :
    DataSource(parent) {
    m_strength = registerSystemSource("/run/state/namespaces/Internet/SignalStrength");
    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceInternet::processSystemSnapshot() {
    const QByteArray &strengthval = getSystemData(m_strength);
    int strength = QString(strengthval).toInt();

    emit systemDataGathered(DataSource::InternetPerc, strength);
}
