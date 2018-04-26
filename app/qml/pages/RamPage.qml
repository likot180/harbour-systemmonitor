import QtQuick 2.0
import Sailfish.Silica 1.0
import net.thecust.sysmon 1.0

Page {
    id: page

    property int deepView: 12
    onDeepViewChanged: {
        for (var i=0;i<depthModel.count;i++) {
            if (depthModel.get(i).interval == deepView) {
                comboBoxDepthView.currentIndex = i;
                break;
            }
        }
    }

    function updateGraph() {
        ramUsed.updateGraph();
        swapUsed.updateGraph();
    }

    Connections {
        target: sysmon
        onDataUpdated: {
            updateGraph();
        }
    }

    Component.onCompleted: {
        updateGraph();
    }

    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height

        VerticalScrollDecorator { flickable: flickable }

        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("RAM usage")
            }

            ComboBox {
                id: comboBoxDepthView
                label: qsTr("Show data for")
                currentIndex: 2
                menu: ContextMenu {
                    Repeater {
                        model: depthModel
                        delegate: MenuItem {
                            text: model.label
                            onClicked: {
                                page.deepView = model.interval
                            }
                        }
                    }
                }
            }

            SysMonGraph {
                id: ramUsed
                graphTitle: qsTr("RAM")
                graphHeight: Screen.width >= 1080 ? 350 : 200
                dataType: [DataSource.RAMUsed]
                dataAvg: true
                dataDepth: deepView
                scale: true
                axisY.units: " MiB"
                valueConverter: function(value) {
                    return (value/1024).toFixed(0);
                }

                clickEnabled: false
            }

            SysMonGraph {
                id: swapUsed
                graphTitle: qsTr("Swap")
                graphHeight: Screen.width >= 1080 ? 350 : 200
                dataType: [DataSource.SwapUsed]
                dataAvg: true
                dataDepth: deepView
                scale: true
                axisY.units: " MiB"
                valueConverter: function(value) {
                    return (value/1024).toFixed(0);
                }

                clickEnabled: false
            }
        }
    }
}
