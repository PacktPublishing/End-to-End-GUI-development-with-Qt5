import QtQuick 2.0
import QtQuick.Controls 2.2

GroupBox {
    title: "Element shape:"
    property alias group: group
    ButtonGroup {
        id: group
        buttons: buttons.children
    }
    Column {
        id: buttons
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
