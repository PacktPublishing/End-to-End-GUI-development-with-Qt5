import QtQuick 2.0
import QtQuick.Controls 2.2

GroupBox {
    property alias group: group
    title: "Background color:"
    ButtonGroup {
        id: group
        buttons: buttons.children
    }
    Column {
        id: buttons
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
