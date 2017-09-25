import QtQuick 2.2
import QtQuick.Window 2.2
import FramelessWindowHelper 1.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
ApplicationWindow {
    id: rootWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("FramelessHelper")

    flags: Qt.FramelessWindowHint | Qt.Window

    FramelessWindowHelper {
        Component.onCompleted: {
            addTitleObject(button)
            setTitleHeight(30)
        }
    }



    Item {
        anchors.fill: parent
        anchors.margins: rootWindow.visibility === ApplicationWindow.Maximized ?
                             8 : 0
        Rectangle {
            anchors.fill: parent
            color: 'blue'
            border.width: 1
            border.color: 'red'
        }

        Rectangle {
            id: titleBar
            width: parent.width
            Button {
                id: button
                anchors.right: parent.right
                height: 30
                onClicked: Qt.quit()
            }
        }

    }
}
