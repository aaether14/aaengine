#include <fbx_manager/entry/meshentry.hpp>







void MeshEntry::LoadUVs(FbxMesh *mesh, QVector<float> &master_uvs)
{





    /**
     *should_fill_with_0 will be true if we've met an invalid data scenario and
     *we have to fill the vbos with 0's
     */

    bool should_fill_with_0 = false;



    /**
    *If the mesh has no uv information we should attempt to fill with 0's
    */

    if (mesh->GetElementUVCount() < 1)
        should_fill_with_0 = true;




    if (!should_fill_with_0)
    {


        /**
     * First we get the vertex uv information for the mesh
     */

        FbxGeometryElementUV* vertex_uv = mesh->GetElementUV(0);


        /**
    *We first check the mapping mode of the uvs
    */


        switch(vertex_uv->GetMappingMode())
        {


        /**
    *Best scenario, uv is set by control point
    */

        case FbxGeometryElement::eByControlPoint:
            switch(vertex_uv->GetReferenceMode())
            {



            case FbxGeometryElement::eDirect:
            {



                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {


                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[0]);
                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[1]);


                }




            }
                break;

            case FbxGeometryElement::eIndexToDirect:
            {




                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {

                    int index = vertex_uv->GetIndexArray().GetAt(i);
                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(index).mData[0]);
                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(index).mData[1]);


                }



            }
                break;

            default:
                should_fill_with_0 = true;



            }
            break;




            /**
    *This is the worse scenario where the uvs are set by polygon vertex and
    *not by control point, so we have to loop through each polygon vertex and
    *add it's contribution to the control point uv we will output
    */

        case FbxGeometryElement::eByPolygonVertex:


            switch(vertex_uv->GetReferenceMode())
            {



            case FbxGeometryElement::eDirect:
            {



                QVector<float> temp_uvs;
                temp_uvs.resize(mesh->GetControlPointsCount() * 2);



                for (int i = 0; i < mesh->GetPolygonCount(); i++)
                    for (int j = 0; j < 3; j++)
                    {

                        int current_polygon_vertex = mesh->GetPolygonVertex(i, j);

                        temp_uvs[current_polygon_vertex * 2 + 0] = vertex_uv->GetDirectArray().GetAt(i).mData[0];
                        temp_uvs[current_polygon_vertex * 2 + 1] = vertex_uv->GetDirectArray().GetAt(i).mData[1];
                    }




                master_uvs << temp_uvs;
                temp_uvs.clear();




            }
                break;



            case FbxGeometryElement::eIndexToDirect:
            {



                QVector<float> temp_uvs;
                temp_uvs.resize(mesh->GetControlPointsCount() * 2);



                for (int i = 0; i < mesh->GetPolygonCount(); i++)
                    for (int j = 0; j < 3; j++)
                    {


                        int current_polygon_vertex = mesh->GetPolygonVertex(i, j);
                        int index = vertex_uv->GetIndexArray().GetAt(i);

                        temp_uvs[current_polygon_vertex * 2 + 0] = vertex_uv->GetDirectArray().GetAt(index).mData[0];
                        temp_uvs[current_polygon_vertex * 2 + 1] = vertex_uv->GetDirectArray().GetAt(index).mData[1];


                    }




                master_uvs << temp_uvs;
                temp_uvs.clear();




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


            qDebug() << mesh->GetNode()->GetName() << "had abnormal uv information and we had to fill 0's!";


            for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                master_uvs << 0.0 << 0.0;


        }





}
