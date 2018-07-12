import QtQuick 2.0
import cutecomics.gui 1.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Scene3D 2.0

Window {
    visible: true
    width: 800
    height: 600

    QtObject {
        id: elements
        property int counter: 0
        property string selectedElement
        property var list: []
        readonly property Component factory: Component {
            Element {}
        }
        function onSelected(objectName) {
            selectedElement = objectName;
            list.forEach(function(element) {
                if (element.objectName !== selectedElement) {
                    element.selected = false;
                }
            });
        }
        function onDeselected(objectName) {
            selectedElement = "";
        }
    }

    QtObject {
        id: usecases

        function addElementToComposition(shape) {
            var element = elements.factory.createObject(
                        composition.elements,
                        {
                            shape: shape,
                            objectName: "element"+elements.counter,
                            translation: Qt.vector3d(
                                             Math.random()*3, 0.0, Math.random()*3)
                        });
            element.wasSelected.connect(elements.onSelected);
            element.wasDeselected.connect(elements.onDeselected);
            elements.list.push(element);
            elements.counter += 1;
        }

        function removeElementFromComposition() {
            for (var i=0; i < elements.list.length; ++i) {
                if (elements.list[i].objectName === elements.selectedElement) {
                    elements.list[i].destroy();
                    elements.selectedElement = "";
                    break;
                }
            }
        }

        function saveCompositionToImage() {
            fileDialog.open();
        }
    }

    Scene3D {
        id: scene
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: menu.left
        aspects: ['logic','input']
        Composition {
            id: composition
            moveCamera: elements.selectedElement === ""
            backgroundColor: backgroundSelector.backgroundColor
        }
    }
    Rectangle {
        id: menu
        width: 180
        color: "#999"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Column {
            anchors.margins: 16
            anchors.fill: parent
            spacing: 8

            GroupBox {
                id: shapeSelector
                title: "Element shape:"
                width: parent.width
                readonly property string shape:
                    shapeGroup.checkedButton.objectName
                ButtonGroup {
                    id: shapeGroup
                    buttons: shapeButtons.children
                }
                Column {
                    id: shapeButtons
                    RadioButton {
                        id: verticalButton
                        objectName: "vertical"
                        text: "vertical"
                        checked: true
                    }
                    RadioButton {
                        id: horizontalButton
                        objectName: "horizontal"
                        text: "horizontal"
                    }
                    RadioButton {
                        id: cubeButton
                        objectName: "cube"
                        text: "cube"
                    }
                }
            }
            Button {
                text: "add element"
                width: parent.width
                onClicked: {
                    usecases.addElementToComposition(shapeSelector.shape);
                }
            }
            Button {
                text: "remove element"
                enabled: elements.selectedElement !== ""
                width: parent.width
                onClicked: {
                    usecases.removeElementFromComposition();
                }
            }
            GroupBox {
                id: backgroundSelector
                title: "Background color:"
                width: parent.width
                readonly property string backgroundColor:
                    backgroundGroup.checkedButton.objectName
                ButtonGroup {
                    id: backgroundGroup
                    buttons: backgroundButtons.children
                }
                Column {
                    id: backgroundButtons
                    RadioButton {
                        id: blackButton
                        objectName: "black"
                        text: "black"
                    }
                    RadioButton {
                        id: greyButton
                        objectName: "grey"
                        text: "grey"
                        checked: true
                    }
                    RadioButton {
                        id: whiteButton
                        objectName: "white"
                        text: "white"
                    }
                }
            }
            Button {
                text: "grab image"
                width: parent.width
                onClicked: {
                    usecases.saveCompositionToImage();
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        fileMode : FileDialog.SaveFile
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            scene.grabToImage(function(image) {
                var saved = image.saveToFile((fileDialog.file+"")
                                             .replace('file://', ''));
                snackbarText.text = saved ? "image saved" : "something went wrong :(";
                snackbar.visible = true;
                snackbarTimer.start();
            });
        }
    }

    Rectangle {
        id: snackbar
        visible: false
        width: 180
        height: 40
        color: "#333"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        Text {
            id: snackbarText
            color: "white"
            anchors.centerIn: parent
        }
        Timer {
            id: snackbarTimer
            interval: 2000
            onTriggered: parent.visible = false
        }
    }
}
