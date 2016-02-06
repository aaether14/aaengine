import QtQuick 2.5
import Qt3D 2.0





QtObject
{



    id:default_camera
    objectName: "Default_camera"
    property matrix4x4 out_viewProj



    property vector3d direction: Qt.vector3d(0, 0, -1)
    property real  vertical_angle: Math.PI / 24
    property real horizontal_angle: Math.PI




    property real movement_speed: 50.0
    property real rotation_speed: Math.PI



    property real mouse_speed: 0.04
    property vector2d last_mouse_position: Qt.vector2d(0, 0)





    property Camera camera: Camera{

        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 60
        aspectRatio: 1.33
        nearPlane : 0.01
        farPlane : 300.0

        position: Qt.vector3d(0.0, 0.0, 100)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)

    }







    Component.onCompleted: {
        updateVP();
    }




    function updateVP()
    {
        camera.viewCenter = camera.position.plus(direction);
        out_viewProj = camera.projectionMatrix.times(camera.matrix);
    }




    function updateDirection()
    {

        direction = Qt.vector3d(Math.cos(vertical_angle) * Math.sin(horizontal_angle),
                                Math.sin(vertical_angle),
                                Math.cos(vertical_angle) * Math.cos(horizontal_angle));



        var right = Qt.vector3d(Math.sin(horizontal_angle - Math.PI / 2.0),
                                0,
                                Math.cos(horizontal_angle - Math.PI / 2.0));


        camera.upVector = right.crossProduct(direction);


    }



    function processKeyInput()
    {




        if(gInput.getKey(Qt.Key_W))
            camera.position = camera.position.plus(direction.times(gFPS.delta() * movement_speed));
        if(gInput.getKey(Qt.Key_S))
            camera.position = camera.position.minus(direction.times(gFPS.delta() * movement_speed));



        if(gInput.getKey(Qt.Key_A))
            horizontal_angle = horizontal_angle + gFPS.delta() * rotation_speed;
        if(gInput.getKey(Qt.Key_D))
            horizontal_angle = horizontal_angle - gFPS.delta() * rotation_speed;



    }



    function processMouseInput()
    {

        if (gInput.getButton(Qt.RightButton))
        {


            var delta_mouse_position = (last_mouse_position.minus(gInput.getMousePosition())).times(mouse_speed * gFPS.delta());
            gInput.setMousePosition(last_mouse_position);


            horizontal_angle = horizontal_angle + delta_mouse_position.x;
            vertical_angle = vertical_angle + delta_mouse_position.y;

        }
        else
        {
            last_mouse_position = gInput.getMousePosition();
        }


    }



    function onUpdate()
    {

        updateDirection();
        processKeyInput();
        processMouseInput();
        updateVP();


    }








}

