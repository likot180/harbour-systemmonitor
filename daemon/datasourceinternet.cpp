#include "datasourceinternet.h"

#include <QDBusConnection>
#include <QDBusMessage>

DataSourceInternet::DataSourceInternet(SystemSnapshot *parent)
    : DataSource(parent) {
    connect(parent, SIGNAL(processSystemSnapshot()),
            SLOT(processSystemSnapshot()));
}

void DataSourceInternet::processSystemSnapshot() {
    QDBusMessage m = QDBusMessage::createMethodCall(
        "net.connman", "/", "net.connman.Manager", "GetServices");
    QDBusMessage reply = QDBusConnection::systemBus().call(m);
    getWifiStrength(reply);
    emit systemDataGathered(DataSource::InternetPerc, m_strength);
}

void DataSourceInternet::getWifiStrength(QDBusMessage reply) {
    const QDBusArgument &a = reply.arguments().at(0).value<QDBusArgument>();

    m_strength = 0;

    if (a.currentType() == QDBusArgument::ArrayType) {
        a.beginArray();

        while (!a.atEnd()) {
            QMap<QString, QVariant> params;
            const QDBusArgument &wifi = a.asVariant().value<QDBusArgument>();

            if (wifi.currentType() == QDBusArgument::StructureType) {
                wifi.beginStructure();
                wifi >> m_wifiPath;
                wifi.beginMap();
                while (!wifi.atEnd()) {
                    wifi.beginMapEntry();

                    QString t;
                    QVariant v;
                    wifi >> t >> v;
                    params.insert(t, v);
                    wifi.endMapEntry();
                }

                wifi.endMap();
                wifi.endStructure();
            }
            if (params["State"].toString() == "online" &&
                params["Type"].toString() == "wifi") {
                // qDebug() << "found wifi path at " << m_wifiPath.path();
                m_strength = params["Strength"].toInt();
            }
        }
        a.endArray();
    }
}
