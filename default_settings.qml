pragma Singleton
import QtQuick 2.0



QtObject
{

    objectName : "Settings"
    property string project_name: "default.project"




    property var lights:
    [
                {
                    name:"Light1",
                    position: Qt.vector3d(0.0, 0.0, 0.0)
                }
    ]



}


