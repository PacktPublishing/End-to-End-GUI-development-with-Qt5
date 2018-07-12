// ComicPanel.qml
import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: panel
    signal cameraClicked()
    signal existingClicked()
    property alias displayText: textItem.text
    property alias imageSource: image.source
    width: 100
    height: 100
    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        onSourceChanged: print(source)
    }
    Rectangle {
        anchors.fill: parent
        border.color: "#000"
        border.width: 2
        opacity: 0.5
    }
    Text {
        id: textItem
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Button {
        id: cameraButton
        anchors.centerIn: parent
        text: "take picture"
        onClicked: panel.cameraClicked()
    }
    Button {
        id: existingButton
        anchors.top: cameraButton.bottom
        anchors.margins: 16
        anchors.horizontalCenter: cameraButton.horizontalCenter
        text: "load existing image"
        onClicked: panel.existingClicked()
    }
}
