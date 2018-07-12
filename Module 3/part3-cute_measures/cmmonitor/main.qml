// cmmonitor/main.qml
import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebEngine 1.5

Window {
    visible: true
    width: 600
    height: 960
    title: qsTr("CM Monitor")

    ReadingsChart {
        id: readingsChart
        width: parent.width
        height: parent.height / 2
        Connections {
            target: receiverChannel
            onReadingsProcessed: {
                readingsChart.plot(readings);
            }
        }
    }

    WebEngineView {
        id: readingsChartJS
        anchors.top: readingsChart.bottom
        width: parent.width
        height: parent.height / 2
        url: "qrc:///ReadingsChartJS.html"
        webChannel: defaultWebChannel
    }
}
