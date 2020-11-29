#include "datasourceinternet.h"
#include <contextproperty.h>

namespace {
bool first_val = true;
}
DataSourceInternet::DataSourceInternet(SystemSnapshot *parent) :
    DataSource(parent) {
    static ContextProperty *prop =
        new ContextProperty("Internet.SignalStrength");
    connect(prop, &ContextProperty::valueChanged, [this]() {
        if (first_val) {
            first_val = false;
            return;
        }
        m_strength = prop->value().toInt();
    });
    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceInternet::processSystemSnapshot() {
    emit systemDataGathered(DataSource::InternetPerc, m_strength);
}
