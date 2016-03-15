#include <fbx_manager/entry/meshentry.hpp>







void MeshEntry::LoadNormals(FbxMesh * mesh,
                            QVector<float> &master_normals)
{






    /**
     *should_fill_with_0 will be true if we've met an invalid data scenario and
     *we have to fill the vbos with 0's
     */

    bool should_fill_with_0 = false;



    /**
    *If the mesh has no normal information we should attempt to fill with 0's
    */

    if (mesh->GetElementNormalCount() < 1)
        should_fill_with_0 = true;



    if (!should_fill_with_0)
    {


        /**
     * First we get the vertex normal information for the mesh
     */

        FbxGeometryElementNormal* vertex_normal = mesh->GetElementNormal(0);


        /**
    *We first check the mapping mode of the normals
    */


        switch(vertex_normal->GetMappingMode())
        {


        /**
    *Easy scenario, normal is set by control point
    */

        case FbxGeometryElement::eByControlPoint:
            switch(vertex_normal->GetReferenceMode())
            {



            case FbxGeometryElement::eDirect:
            {



                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {


                    master_normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[0]);
                    master_normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[1]);
                    master_normals << (float)(vertex_normal->GetDirectArray().GetAt(i).mData[2]);


                }




            }
                break;

            case FbxGeometryElement::eIndexToDirect:
            {




                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {

                    int index = vertex_normal->GetIndexArray().GetAt(i);
                    master_normals << (float)(vertex_normal->GetDirectArray().GetAt(index).mData[0]);
                    master_normals << (float)(vertex_normal->GetDirectArray().GetAt(index).mData[1]);
                    master_normals << (float)(vertex_normal->GetDirectArray().GetAt(index).mData[2]);


                }



            }
                break;

            default:
                should_fill_with_0 = true;



            }
            break;




            /**
    *This is the worse scenario where the normals are set by polygon vertex and
    *not by control point, so we have to loop through each polygon vertex and
    *add it's contribution to the control point normal we will output
    */

        case FbxGeometryElement::eByPolygonVertex:


            switch(vertex_normal->GetReferenceMode())
            {



            case FbxGeometryElement::eDirect:
            {



                QVector<float> temp_normals;
                temp_normals.resize(mesh->GetControlPointsCount() * 3);



                for (int i = 0; i < mesh->GetPolygonCount(); i++)
                    for (int j = 0; j < 3; j++)
                    {

                        int current_polygon_vertex = mesh->GetPolygonVertex(i, j);

                        temp_normals[current_polygon_vertex * 3 + 0] = vertex_normal->GetDirectArray().GetAt(i).mData[0];
                        temp_normals[current_polygon_vertex * 3 + 1] = vertex_normal->GetDirectArray().GetAt(i).mData[1];
                        temp_normals[current_polygon_vertex * 3 + 2] = vertex_normal->GetDirectArray().GetAt(i).mData[2];
                    }




                master_normals << temp_normals;
                temp_normals.clear();




            }
                break;



            case FbxGeometryElement::eIndexToDirect:
            {



                QVector<float> temp_normals;
                temp_normals.resize(mesh->GetControlPointsCount() * 3);



                for (int i = 0; i < mesh->GetPolygonCount(); i++)
                    for (int j = 0; j < 3; j++)
                    {

                        int current_polygon_vertex = mesh->GetPolygonVertex(i, j);
                        int index = vertex_normal->GetIndexArray().GetAt(i);

                        temp_normals[current_polygon_vertex * 3 + 0] = vertex_normal->GetDirectArray().GetAt(index).mData[0];
                        temp_normals[current_polygon_vertex * 3 + 1] = vertex_normal->GetDirectArray().GetAt(index).mData[1];
                        temp_normals[current_polygon_vertex * 3 + 2] = vertex_normal->GetDirectArray().GetAt(index).mData[2];


                    }




                master_normals << temp_normals;
                temp_normals.clear();




            }
                break;

            default:
                should_fill_with_0 = true;



            }
            break;



        }





    }
    else


        /**
    *If we came across abnormal information we should output an error then go
    *ahead and fill with 0's
    */

        if (should_fill_with_0)
        {


            qDebug() << mesh->GetNode()->GetName() << "had abnormal normal information and we had to fill 0's!";


            for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                master_normals << 0.0 << 0.0 << 0.0;


        }






}
