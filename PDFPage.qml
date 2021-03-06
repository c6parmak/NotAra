import QtQuick 2.0
import MyTypes 1.0

Rectangle {
    id: page;
    property PDFView pdfView;

    color: "transparent";
    transformOrigin: Item.Top;
    anchors.horizontalCenter: parent.horizontalCenter;
    width: pageSize.width * scale;
    height: pageSize.height * scale

    Component.onCompleted: {
        console.log("SCALE", scale, pdfScale)
        //pdfView.attachPage(this)
    }
    Component.onDestruction: {
        //pdfView.detachPage(this);
    }

    Image {
        id: image;
        anchors.horizontalCenter: page.horizontalCenter;
        //height: page.height;
        //fillMode: Image.PreserveAspectFit;
        asynchronous: true;
        source: "image://pdfImage/" + pageNumber;
        //sourceSize.width:  view.fitWidth ? parent.width
        //                                 : pageSize.width * parent.scale
        z: 1;


        // Text highlight rectangles
        Repeater {
            model: highlights
            Repeater {
                model: modelData
                Rectangle {
                    x: model.modelData.x
                    y: model.modelData.y
                    width: model.modelData.width
                    height: model.modelData.height
                    color: "#40FFD700"
                }
            }
        }

        // Crop Rect
        Repeater {
            model: clipRects
            Rectangle {
                x: model.modelData.x;
                y: model.modelData.y;
                width: model.modelData.width;
                height: model.modelData.height;
                color: "transparent";
                border.width: 1;
                border.color: "#FFD700";
            }
        }

        // Text selection rectangles
        Repeater {
            model: selection
            Rectangle {
                x: model.modelData.x
                y: model.modelData.y
                width: model.modelData.width
                height: model.modelData.height
                color: "#400070BB"
            }
        }

        // Selection Rect
        Rectangle {
            x: selectionRect.x;
            y: selectionRect.y;
            width: selectionRect.width;
            height: selectionRect.height;
            color: "transparent";
            border.width: 1;
            border.color: "#990070BB";
        }

    }
}
