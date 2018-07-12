import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item1
    property alias addItemButton: addItemButton
    property alias addItemField: addItemField
    property alias groceriesListView: groceriesListView

    ListView {
        id: groceriesListView

        signal itemRemoved(string itemName)

        anchors.fill: parent
        model: ListModel {
            ListElement {
                name: "Bananas"
            }
            ListElement {
                name: "Orange Juice"
            }
            ListElement {
                name: "Grapes"
            }
            ListElement {
                name: "Eggs"
            }
        }
        delegate: ItemDelegate {
            width: groceriesListView.width
            text: modelData.name || model.name
            font.bold: true
            Button {
                id: removeItemButton
                width: height
                height: parent.height
                text: "X"
                anchors.right: parent.right
                Connections {
                    target: removeItemButton
                    onClicked: groceriesListView.itemRemoved(modelData.name
                                                    || model.name)
                }
            }
        }
    }

    Row {
        id: row
        height: 64
        spacing: 16
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 16
        anchors.rightMargin: 16

        TextField {
            id: addItemField
            placeholderText: "enter item name"
        }

        Button {
            id: addItemButton
            text: qsTr("Add item")
        }
    }
}
