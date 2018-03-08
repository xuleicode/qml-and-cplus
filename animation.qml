import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
Window
{
    id:root
    width: 360
    height: 360
    title:"Gearslogy"
    Column
    {
        Row
        {
            id:tools
            Button
            {
                id:button_01
                text:"Reset1"
                onClicked:
                {
                    display.fillMode = Image.Stretch
                    display.width = display.sourceSize.width
                    display.height = display.sourceSize.height
                    display.anchors.centerIn = viewPort
                    display.clip = false
                    console.log("Reset button");
                }
            }
            Button
            {
                id:button_02
                text:"fit to window"
                onClicked:
                {
                    display.fillMode = Image.Stretch
                    display.width = root.width
                    display.height = root.height
                    console.log("Reset button");
                }
            }
        }
        Rectangle
        {
            id:viewPort
            width: root.width
            height: root.height
            AnimatedImage
            {
                id:display
                anchors.centerIn: viewPort
                source: "qrc:/image/timg.gif"
            }
        }

    }
}
