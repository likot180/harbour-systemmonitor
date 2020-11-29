#include "datasourcesignal.h"
#include <contextproperty.h>

namespace {
bool first_val = true;
}
DataSourceSignal::DataSourceSignal(SystemSnapshot *parent) :
    DataSource(parent) {
    static ContextProperty *prop =
        new ContextProperty("Cellular.SignalStrength");
    connect(prop, &ContextProperty::valueChanged, [this]() {
        if (first_val) {
            first_val = false;
            return;
        }
        m_signal = prop->value().toInt();
    });
    connect(parent, SIGNAL(processSystemSnapshot()), SLOT(processSystemSnapshot()));
}

void DataSourceSignal::processSystemSnapshot() {
    emit systemDataGathered(DataSource::SignalPerc, m_signal);
}
