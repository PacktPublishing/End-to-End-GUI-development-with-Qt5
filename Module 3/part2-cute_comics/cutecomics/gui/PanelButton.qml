// PanelButton.qml
import QtQuick 2.0

Item {
    signal clicked()
    property alias text: textItem.text
    width: 40
    height: width
    opacity: 0.5
    Text {
        id: textItem
        text: "+"
        anchors.centerIn: parent
        font.pixelSize: 40
    }
    MouseArea {
        onClicked: parent.clicked()
        anchors.fill: parent
    }
}
