#include "datasourcesignal.h"
#include <QString>

DataSourceSignal::DataSourceSignal(SystemSnapshot *parent) :
    DataSource(parent)
{
    m_signal = registerSystemSource("/run/state/namespaces/Cellular/SignalStrength");
    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceSignal::processSystemSnapshot()
{
    const QByteArray &signalval = getSystemData(m_signal);
    int signal = QString(signalval).toInt();

    emit systemDataGathered(DataSource::SignalPerc, signal);
}
