#include <fbx_manager/mesh/mesh.hpp>









void Mesh::NormalizeScene(FbxScene *scene, FbxManager *fbx_manager,
                          bool convert_axis,
                          bool convert_scale,
                          bool split_points,
                          bool generate_tangents)
{


    /**
     *if the mesh is not in the OpenGL axis system format, convert it
     */


    if (convert_axis)
    {


        FbxAxisSystem SceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
        if (SceneAxisSystem != FbxAxisSystem::OpenGL)
        {
            FbxAxisSystem::OpenGL.ConvertScene(scene);
        }



    }


    /**
     *if the mesh is not in a resonable scale system, convert it
     */


    if (convert_scale)
    {


        FbxSystemUnit SceneSystemUnit = scene->GetGlobalSettings().GetSystemUnit();
        if( SceneSystemUnit.GetScaleFactor() != 1.0 )
        {
            FbxSystemUnit::cm.ConvertScene(scene);
        }





    }






    /**
     *Triangulate the scene in odrer to correctly send vertex data to shader
     */

    FbxGeometryConverter geometry_converter(fbx_manager);
    geometry_converter.Triangulate(scene, true);






    /**
    *Generate tangent data for all meshes in the scene
    */

    if (generate_tangents)

    {


        for (int i = 0; i < scene->GetGeometryCount(); i++)
        {


            FbxMesh * current_mesh = FbxCast<FbxMesh>(scene->GetGeometry(i));
            if (!current_mesh)
                continue;


            current_mesh->GenerateTangentsDataForAllUVSets(true);

        }



    }





    if (split_points)
    {


        for (int i = 0; i < scene->GetGeometryCount(); i++)
        {


            FbxMesh * current_mesh = FbxCast<FbxMesh>(scene->GetGeometry(i));
            if (!current_mesh)
                continue;


            current_mesh->SplitPoints();

        }




    }



    /**
    *Mark that the mesh should be saved after loading the file
    */
    should_save_scene_after_load = true;



}






