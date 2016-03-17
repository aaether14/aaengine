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
    *We first check the mapping mode of the normals
    */


        if(vertex_uv->GetMappingMode() == FbxGeometryElement::eByControlPoint)
        {




            switch(vertex_uv->GetReferenceMode())
            {





            case FbxGeometryElement::eDirect:
            {



                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {


                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[0]);
                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(i).mData[1]);


                }




            }break;





            case FbxGeometryElement::eIndexToDirect:
            {




                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {


                    int index = vertex_uv->GetIndexArray().GetAt(i);
                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(index).mData[0]);
                    master_uvs << (float)(vertex_uv->GetDirectArray().GetAt(index).mData[1]);


                }



            }break;





            }





        }
        else
            should_fill_with_0 = true;
    }


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
