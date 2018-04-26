#include "datasourcewlan.h"
#include <QDebug>
#include <QFile>

DataSourceWlan::DataSourceWlan(SystemSnapshot *parent) :
    DataSource(parent)
{
    m_sourceRx = registerSystemSource("/sys/class/net/wlan0/statistics/rx_bytes");
    m_sourceTx = registerSystemSource("/sys/class/net/wlan0/statistics/tx_bytes");

    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

// /sys/class/net/wlan0/statistics = rx_bytes | tx_bytes

void DataSourceWlan::processSystemSnapshot()
{
    qDebug() << "Network WLAN data";

    long long deltaRx = 0;
    long long deltaTx = 0;

    QVector<unsigned long long> bytesRx;
    QVector<unsigned long long> bytesTx;
    bool rxOk, txOk;

    bytesRx.append(QString(getSystemData(m_sourceRx)).toULongLong(&rxOk));
    bytesTx.append(QString(getSystemData(m_sourceTx)).toULongLong(&txOk));

    if (m_prevBytesRx.size() == bytesRx.size()) {
        for (int i=0;i<bytesRx.size();i++) {
            if (rxOk) {
                //Network was reseted
                if (bytesRx[i] < m_prevBytesRx[i]) {
                    deltaRx += bytesRx[i];
                } else {
                    deltaRx += (bytesRx[i] - m_prevBytesRx[i]);
                }
            }
        }
    }

    if (m_prevBytesTx.size() == bytesTx.size()) {
        for (int i=0;i<bytesTx.size();i++) {
            if (txOk) {
                //Network was reseted
                if (bytesTx[i] < m_prevBytesTx[i]) {
                    deltaTx += bytesTx[i];
                } else {
                    deltaTx += (bytesTx[i] - m_prevBytesTx[i]);
                }
            }
        }
    }

    // calculating rates
    double rateRx = 0;
    double rateTx = 0;

    if ( deltaRx > 0 ) rateRx = deltaRx / (double)m_prevTime.secsTo(getSnapshotTime());
    if ( deltaTx > 0 ) rateTx = deltaTx / (double)m_prevTime.secsTo(getSnapshotTime());

    // storing old data
    m_prevBytesRx = bytesRx;
    m_prevBytesTx = bytesTx;
    m_prevTime = getSnapshotTime();


    emit systemDataGathered(DataSource::NetworkWlanRx, rateRx);
    emit systemDataGathered(DataSource::NetworkWlanTx, rateTx);
}
