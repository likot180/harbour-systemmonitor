#include "datasourcesignal.h"

#include <QDBusConnection>
#include <QDBusMessage>

DataSourceSignal::DataSourceSignal(SystemSnapshot *parent)
    : DataSource(parent) {
    connect(parent, SIGNAL(processSystemSnapshot()),
            SLOT(processSystemSnapshot()));
}

void DataSourceSignal::processSystemSnapshot() {
    QDBusMessage m = QDBusMessage::createMethodCall(
        "org.ofono", "/ril_0", "org.ofono.NetworkRegistration",
        "GetProperties");
    QDBusMessage reply = QDBusConnection::systemBus().call(m);
    getNetworkStatus(reply);
    emit systemDataGathered(DataSource::SignalPerc, m_signal);
}

void DataSourceSignal::getNetworkStatus(QDBusMessage reply) {
    const QDBusArgument &a = reply.arguments().at(0).value<QDBusArgument>();

    m_signal = 0;

    if (a.currentType() == QDBusArgument::MapType) {
        a.beginMap();

        while (!a.atEnd()) {
            a.beginMapEntry();
            QString t;
            QVariant v;
            a >> t >> v;

            if (t == "Strength") {
                m_signal = v.toInt();
                // qDebug() << "Strength " << m_signal;
            }

            a.endMapEntry();
        }
        a.endMap();
    }
}
