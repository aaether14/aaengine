#include <fbx_manager/mesh/mesh.hpp>









void Mesh::NormalizeScene(FbxScene *scene, FbxManager *fbx_manager,
                          bool convert_axis,
                          bool convert_scale,
                          bool split_points,
                          bool generate_tangents,
                          bool triangulate,
                          bool convert_textures)
{







    /**
     *Triangulate the scene in odrer to correctly send vertex data to shader
     */



    if (triangulate)
    {


        FbxGeometryConverter geometry_converter(fbx_manager);
        geometry_converter.Triangulate(scene, true);


    }






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
    *Splitting points will attempt to convert from PerPolygon normals and uvs to
    *PerControlPoint ones
    */

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
    *Generate tangent data for all meshes in the scene
    */

    if (generate_tangents)

    {


        for (int i = 0; i < scene->GetGeometryCount(); i++)
        {


            /**
             *Skip through invalid meshes
             */

            FbxMesh * current_mesh = FbxCast<FbxMesh>(scene->GetGeometry(i));
            if (!current_mesh)
                continue;


            /**
            *Remove existing tangent data
            */

            for (int i = 0; i < current_mesh->GetElementTangentCount(); i++)
                current_mesh->RemoveElementTangent(current_mesh->GetElementTangent(i));



            /**
            *Cant compute tangents without uvs and normals
            */


            if (current_mesh->GetElementUVCount() < 1 ||
                    current_mesh->GetElementNormalCount() < 1)
                continue;



            /**
            *We need per control point uvs and normals
            */

            if (current_mesh->GetElementUV(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint ||
                    current_mesh->GetElementNormal(0)->GetMappingMode() != FbxGeometryElement::eByControlPoint)
                continue;



            /**
             *If everything is ok extract vertex uv and normal
             */

            FbxGeometryElementUV * vertex_uv = current_mesh->GetElementUV(0);
            FbxGeometryElementNormal * vertex_normal = current_mesh->GetElementNormal(0);



            /**
             * Create the tangents array
             */


            FbxGeometryElementTangent * vertex_tangent = current_mesh->CreateElementTangent();
            vertex_tangent->SetMappingMode(FbxGeometryElement::eByControlPoint);
            vertex_tangent->SetReferenceMode(FbxGeometryElement::eDirect);




            QVector<QVector3D> tan1(current_mesh->GetControlPointsCount(), QVector3D(0.0, 0.0, 0.0));
            QVector<QVector3D> tan2(current_mesh->GetControlPointsCount(), QVector3D(0.0, 0.0, 0.0));



            for (int j = 0; j < current_mesh->GetPolygonCount(); j++)
            {


                /**
                 *First get the indices of the vertices in the triangle
                 */


                int i1 = current_mesh->GetPolygonVertex(j, 0);
                int i2 = current_mesh->GetPolygonVertex(j, 1);
                int i3 = current_mesh->GetPolygonVertex(j, 2);


                /**
                 * Get vertices of the triangle
                 */

                FbxVector4 v1 = current_mesh->GetControlPointAt(i1);
                FbxVector4 v2 = current_mesh->GetControlPointAt(i2);
                FbxVector4 v3 = current_mesh->GetControlPointAt(i3);




                /**
                 * Get uvs of the triangle
                 */


                FbxVector2 w1, w2, w3;
                if (vertex_uv->GetReferenceMode() == FbxGeometryElement::eDirect)
                {
                    w1 = vertex_uv->GetDirectArray().GetAt(i1);
                    w2 = vertex_uv->GetDirectArray().GetAt(i2);
                    w3 = vertex_uv->GetDirectArray().GetAt(i3);
                }
                else if(vertex_uv->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                {
                    w1 = vertex_uv->GetDirectArray().GetAt(vertex_uv->GetIndexArray().GetAt(i1));
                    w2 = vertex_uv->GetDirectArray().GetAt(vertex_uv->GetIndexArray().GetAt(i2));
                    w3 = vertex_uv->GetDirectArray().GetAt(vertex_uv->GetIndexArray().GetAt(i3));
                }



                /**
                 * Compute intermediate tangents
                 */


                float x1 = v2.mData[0] - v1.mData[0];
                float x2 = v3.mData[0] - v1.mData[0];
                float y1 = v2.mData[1] - v1.mData[1];
                float y2 = v3.mData[1] - v1.mData[1];
                float z1 = v2.mData[2] - v1.mData[2];
                float z2 = v3.mData[2] - v1.mData[2];



                float s1 = w2.mData[0] - w1.mData[0];
                float s2 = w3.mData[0] - w1.mData[0];
                float t1 = w2.mData[1] - w1.mData[1];
                float t2 = w3.mData[1] - w1.mData[1];



                float r = 1.0f / (s1 * t2 - s2 * t1);




                QVector3D sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                               (t2 * z1 - t1 * z2) * r);
                QVector3D tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                               (s1 * z2 - s2 * z1) * r);




                tan1[i1] += sdir;
                tan1[i2] += sdir;
                tan1[i3] += sdir;

                tan2[i1] += tdir;
                tan2[i2] += tdir;
                tan2[i3] += tdir;



            }



            /**
            *Compute actual tangents
            */


            for (int j = 0; j < current_mesh->GetControlPointsCount(); j++)
            {



                QVector3D n, t;



                if (vertex_normal->GetReferenceMode() == FbxGeometryElement::eDirect)
                {
                    n = aae::mesh_util::QVector3DFromFbxVector3D(vertex_normal->GetDirectArray().GetAt(j));
                }
                else if (vertex_normal->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                {
                    n = aae::mesh_util::QVector3DFromFbxVector3D(vertex_normal->GetDirectArray().GetAt(vertex_normal->GetIndexArray().GetAt(j)));
                }


                t = tan1[j];


                QVector3D tangent = (t - n * QVector3D::dotProduct(n, t)).normalized();
                float hardness = (QVector3D::dotProduct(QVector3D::crossProduct(n, t), tan2[j]) < 0.0f) ? -1.0f : 1.0f;


                vertex_tangent->GetDirectArray().Add(FbxVector4(tangent.x(), tangent.y(), tangent.z(), hardness));


            }




        }



    }







    /**
    *Texture conversion might be necesary because on some platforms some
    *texture formats are not supported
    */


    if (convert_textures)
    {

        for (int i = 0; i < scene->GetTextureCount(); i++)
        {



            FbxFileTexture * texture = FbxCast<FbxFileTexture>(scene->GetTexture(i));
            if (!texture)
                continue;



            QString suffix = QFileInfo(texture->GetFileName()).suffix();



            if (suffix == "tga")
                texture->SetFileName(QString(QFileInfo(texture->GetFileName()).baseName() + ".png").toStdString().c_str());



        }

    }





    /**
    *Mark that the mesh should be saved after loading the file
    */
    should_save_scene_after_load = true;



}






