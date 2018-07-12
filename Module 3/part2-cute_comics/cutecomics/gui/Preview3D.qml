// Preview3D
import QtQuick.Scene3D 2.0
import QtQml 2.2

Scene3D {
    id: scene3d
    aspects: ['input','logic']
    Component {
        id: elementC
        Element {}
    }

    Composition {
        id: composition
    }
    Component.onCompleted: {
        elementC.createObject(composition.elements);
    }
}
