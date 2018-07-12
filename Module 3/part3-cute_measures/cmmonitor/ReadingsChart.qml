// ReadingsChart.qml
import QtQuick 2.9
import QtCharts 2.2

ChartView {
    id: chartView
    width: 640
    height: 480

    function plot(readings) {
        if (readings[0]) {
            readingsChart.axisTimer.stop();
            readingsChart.emptyText.visible = false;
            readingsChart.valueAxisX.min = new Date(readings[0].timestamp - 15000);
            readingsChart.valueAxisX.max = new Date(readings[0].timestamp);
            readingsChart.lineSeries.append(new Date(readings[0].timestamp), readings[0].value);
        }
    }

    DateTimeAxis {
        id: valueAxisX
        format: "H:mm:ss"
        min: new Date(Date.now() - 15000) // 15 secs
        max: new Date(Date.now())
    }
    ValueAxis{
        id: valueAxisY
        max: 1
        min: -1
    }
    LineSeries {
        id: lineSeries
        name: "mockSensor1"
        axisX: valueAxisX
        axisY: valueAxisY
        color: "orange"
    }
    Text {
        id: emptyText
        anchors.centerIn: parent
        text: "waiting for data..."
    }
    Timer {
        id: axisTimer
        running: true
        repeat: true
        interval: 1000
        onTriggered: {
            valueAxisX.min = new Date(Date.now() - 15000);
            valueAxisX.max = new Date(Date.now());
        }
    }
}
