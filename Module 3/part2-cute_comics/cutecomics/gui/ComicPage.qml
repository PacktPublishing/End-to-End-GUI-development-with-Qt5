// ComicPage.qml
import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

Item {
    id: page

    property alias panelsRepeater: panelsRepeater
    property alias panelAdder: panelAdder
    property alias panelRemover: panelRemover

    width: 480
    height: width
    anchors.centerIn: parent

    Rectangle {
        id: pageFace
        anchors.fill: parent
    }
    DropShadow {
        source:pageFace
        anchors.fill: source
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        color: "#80000000"
    }

    Item {
        id: drawingSurface
        anchors.fill: parent
        anchors.margins: 32
        GridLayout {
            id: panelsGrid
            anchors.fill: parent
            rows: 1
            columns: panelsRepeater.count
            Repeater {
                id: panelsRepeater
                model: 0
            }
        }
    }

    PanelButton {
        id: panelAdder
        anchors.right: parent.right
        text: "+"
    }
    PanelButton {
        id: panelRemover
        anchors.top: panelAdder.bottom
        anchors.right: parent.right
        text: "-"
    }
}
