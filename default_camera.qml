import QtQuick 2.5
import Qt3D 2.0


QtObject
{


    id:camera
    objectName: "Default_camera"
    property matrix4x4 vp



    property CameraLens lens : CameraLens {
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 60
        aspectRatio: 1.33
        nearPlane : 0.01
        farPlane : 300.0
    }



    property Transform transform : Transform {
        LookAt {
            position: Qt.vector3d(0.0, 0.0, -100.0)
            upVector: Qt.vector3d(0.0, 1.0, 0.0)
            viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
        }
    }





    function update()
    {
        vp = lens.projectionMatrix.times(transform.matrix);
    }




}

