import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import com.dieseleeasy.backend 1.0
import "frontend.js" as Frontend

Window {
    id: window
    x: (Screen.desktopAvailableWidth - width)/2
    y: (Screen.desktopAvailableHeight - height - 10)/2
    visible: true
    width: 500
    height: 480
    title: qsTr("BitRepresentation")
    color: "#252323"
    onAfterRendering: if(!Frontend.rendered) {
                        backend.number = 0;
                        Frontend.rendered = true;
                      }
    BackEnd {
        id: backend
    }

    FileDialog {
        id: fileDialog
        title: "Choose a file"
        nameFilters: ["Text files (*.txt)", "All files(*)"]
        selectedNameFilter: "Text files (*.txt)"
        width: 600
        height: 500
        onAccepted: {
            backend.openFile(fileUrls)
        }
    }

    Label {
        id: label_1
        text: qsTr(Frontend.displayNumber())
        x: tf_1.x
        y: 70
        font.family: "Helvetica"
        font.pointSize: 14
        color: "#04934e"
    }

    TextField {
        id: tf_1
        placeholderText: qsTr("Insert a number")
        x: (window.width - width - tf_2.width - 10)/2
        y: 100
        width: 200
        height: 40
        color: "#252323"
        background: Rectangle {
            color: "#04934e"
        }
        onTextChanged: backend.number = text
    }

    TextField {
        id: tf_2
        placeholderText: qsTr("Insert a hex number")
        x: tf_1.x + tf_1.width + 10
        y: 100
        width: 200
        height: 40
        color: "#252323"
        background: Rectangle {
            color: "#04934e"
        }
        onTextChanged: {
            backend.hexNumber = text
        }
    }

    Button {
        id: invBut
        text: qsTr("Invert bits")
        width: 110
        x: tf_1.x + tf_1.width - width
        y: 210
        height: 30
        /*contentItem: Text{
            text: invBut.text
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#252323"
        }*/

        MouseArea {
            id: mouse
            anchors.fill: parent
            cursorShape: "PointingHandCursor"
            onClicked: {
                backend.invertBits()
            }
        }

        background: Rectangle {
            id: butBackRec
            radius: 6
            color: !mouse.pressed ? "#04934e" : "#70798c"
        }
        //onHoveredChanged:  butBackRec.color = hovered ? "#70798c" : "#04934e"
    }

    Button {
        id: addBut
        text: qsTr("Add from file")
        x: tf_2.x
        y: 210
        width: 110
        height: 30
        /*contentItem: Text{
            text: addBut.text
            color: "#252323"
        }*/

        MouseArea {
            id: mouseAdd
            anchors.fill: parent
            cursorShape: "PointingHandCursor"
            onClicked: {
                fileDialog.visible = true
                //fileDialog.open()
            }
        }

        background: Rectangle {
            id: addBackRec
            radius: 6
            color: !mouseAdd.pressed ? "#04934e" : "#70798c"
        }
        //onHoveredChanged:  addBackRec.color = hovered ? "#70798c" : "#04934e"
    }

   Component.onCompleted: {
        const SPACING = 14; // расстояние между кнопками
        const BUT_WIDTH = 39; // ширина кнопки
        const WIDTH = 7 * SPACING + 8 * BUT_WIDTH; // полная ширина кнопок
        for(let i = 0; i < 8; i++){
            Qt.createQmlObject('import QtQuick 2.12; import QtQuick.Controls 2.5; import "frontend.js" as Frontend;
                Button {
                    id: anotherBut' + i +';
                    width: '+ BUT_WIDTH + ';
                    height: '+ BUT_WIDTH + ';
                    x: (window.width - ' + WIDTH + ')/2 + ' + (i*SPACING + i*BUT_WIDTH) + ';
                    y: 155;

                    MouseArea {
                        id: mouse' + i + '
                        anchors.fill: parent
                        cursorShape: "PointingHandCursor"
                        onClicked: {
                            /*Frontend.clicked = (Frontend.clicked || label_1.text == "0") ? false : true;
                            butBackRec'+ i +'.color = !Frontend.clicked ? "#04934e" : "#70798c";*/
                            backend.toggleBit(' + i + ');
                        }
                    }

                    background: Rectangle {
                        id: butBackRec' + i + '
                        objectName: "butBackRec' + i +'"
                        radius: 6
                        color: "#04934e"
                    }


                }', window, "dynamicSnippet1");
            }
    }
}
