// CCPanels.qml
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtMultimedia 5.9
import QtQuick.Dialogs 1.2

TableSurface {
    ListModel {
        id: panelsEntity
        property int currentIndex: -1
    }

    ComicPage {
        id: page
        anchors.centerIn: parent
        panelsRepeater.delegate: ComicPanel {
            displayText: pid || 0
            imageSource: pictureSource || ""
            Layout.fillWidth: true
            Layout.fillHeight: true
            onCameraClicked: {
                panelsEntity.currentIndex = index;
                camera.imageCapture.capture();
            }
            onExistingClicked: {
                panelsEntity.currentIndex = index;
                fileDialog.open();
            }
        }
        panelsRepeater.model: panelsEntity
        panelAdder.onClicked: panelsEntity.append({"pid":panelsEntity.count,"pictureSource":""})
        panelRemover.onClicked: if (panelsEntity.count > 0) {
                                    panelsEntity.remove(panelsEntity.count-1);
                                }
    }

    Camera {
        id: camera
        imageCapture {
            onImageCaptured: panelsEntity.get(panelsEntity.currentIndex).pictureSource = preview
        }
    }

    VideoOutput {
        source: camera
        width: 120
        height: 75
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 16
    }

    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)"]
        onAccepted: panelsEntity.get(panelsEntity.currentIndex).pictureSource = Qt.resolvedUrl(fileUrl)
    }
}
