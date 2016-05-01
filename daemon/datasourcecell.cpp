#include "datasourcecell.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>

DataSourceCell::DataSourceCell(SystemSnapshot *parent) :
    DataSource(parent)
{
    for (int i=0;i<=7;i++) {
        m_sourcesRx.append(registerSystemSource(QString("/sys/class/net/rmnet%1/statistics/rx_bytes").arg(i)));
        m_sourcesRx.append(registerSystemSource(QString("/sys/class/net/rmnet_usb%1/statistics/rx_bytes").arg(i)));
        m_sourcesTx.append(registerSystemSource(QString("/sys/class/net/rmnet%1/statistics/tx_bytes").arg(i)));
        m_sourcesTx.append(registerSystemSource(QString("/sys/class/net/rmnet_usb%1/statistics/tx_bytes").arg(i)));
    }


    // Solution below does not work on boot: rmnet_usb* dirs are not available on boot and come out
    // after sysmon daemon start in Nexus 4

//    QDir rmnet("/sys/class/net");
//    QStringList filters;
//    filters << "rmnet_usb*" << "rmnet?";
//    rmnet.setNameFilters(filters);

//    const QStringList files = rmnet.entryList();
//    QStringListIterator iterator(files);
//    QString fileName;
//    while ( iterator.hasNext() ) {
//        fileName = rmnet.absoluteFilePath(iterator.next());
//        m_sourcesRx.append(registerSystemSource(fileName + "/statistics/rx_bytes"));
//        m_sourcesTx.append(registerSystemSource(fileName + "/statistics/tx_bytes"));

//        qDebug() << "Network cell data init: recording from " << fileName;
//    }

    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

// /sys/class/net/rmnet[0-7]/statistics = rx_bytes | tx_bytes
void DataSourceCell::processSystemSnapshot()
{
    //qDebug() << "Network CELL data";
    long long deltaRx = 0;
    long long deltaTx = 0;

    QVector<unsigned long long> bytesRx;
    QVector<unsigned long long> bytesTx;
    foreach(int sourceRx, m_sourcesRx) {
        bytesRx.append(QString(getSystemData(sourceRx)).toULongLong());
    }

    foreach(int sourceTx, m_sourcesTx) {
        bytesTx.append(QString(getSystemData(sourceTx)).toULongLong());
    }

    if (m_prevBytesRx.size() == bytesRx.size()) {
        for (int i=0;i<bytesRx.size();i++) {
            //Network was reseted
            if (bytesRx[i] < m_prevBytesRx[i]) {
                deltaRx += bytesRx[i];
            } else {
                deltaRx += (bytesRx[i] - m_prevBytesRx[i]);
            }
        }
    }

    if (m_prevBytesTx.size() == bytesTx.size()) {
        for (int i=0;i<bytesTx.size();i++) {
            if (bytesTx[i] < m_prevBytesTx[i]) {
                deltaTx += bytesTx[i];
            } else {
                deltaTx += (bytesTx[i] - m_prevBytesTx[i]);
            }
        }
    }

    // calculating rates
    double rateRx = 0;
    double rateTx = 0;

    if ( deltaRx > 0 ) rateRx = deltaRx / (double)m_prevTime.secsTo(getSnapshotTime());
    if ( deltaTx > 0 ) rateTx = deltaTx / (double)m_prevTime.secsTo(getSnapshotTime());

    //qDebug() << "Network CELL rates: " << rateRx << " " << rateTx << " [" << deltaRx << ", " << deltaTx << "]";

    // storing old data
    m_prevBytesRx = bytesRx;
    m_prevBytesTx = bytesTx;
    m_prevTime = getSnapshotTime();

    emit systemDataGathered(DataSource::NetworkCellRx, rateRx);
    emit systemDataGathered(DataSource::NetworkCellTx, rateTx);
}
