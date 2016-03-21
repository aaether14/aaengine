#include <fbx_manager/entry/meshentry.hpp>





void MeshEntry::LoadTangents(FbxMesh *mesh,
                             QVector<float> &master_tangents)
{





    /**
     *should_fill_with_0 will be true if we've met an invalid data scenario and
     *we have to fill the vbos with 0's
     */

    bool should_fill_with_0 = false;



    /**
    *If the mesh has no tangent information we should attempt to fill with 0's
    */

    if (mesh->GetElementTangentCount() < 1)
        should_fill_with_0 = true;



    if (!should_fill_with_0)
    {


        /**
     * First we get the vertex tangent information for the mesh
     */

        FbxGeometryElementTangent* vertex_tangent = mesh->GetElementTangent(0);


        /**
    *We first check the mapping mode of the tangents
    */


        if(vertex_tangent->GetMappingMode() == FbxGeometryElement::eByControlPoint)
        {




            switch(vertex_tangent->GetReferenceMode())
            {





            case FbxGeometryElement::eDirect:
            {



                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {


                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(i).mData[0]);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(i).mData[1]);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(i).mData[2]);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(i).mData[3]);


                }




            }break;





            case FbxGeometryElement::eIndexToDirect:
            {




                for (int i = 0; i < mesh->GetControlPointsCount(); i++)
                {


                    int index = vertex_tangent->GetIndexArray().GetAt(i);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(index).mData[0]);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(index).mData[1]);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(index).mData[2]);
                    master_tangents << (float)(vertex_tangent->GetDirectArray().GetAt(index).mData[3]);




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


        qDebug() << mesh->GetNode()->GetName() << "had abnormal tangent information and we had to fill 0's!";


        for (int i = 0; i < mesh->GetControlPointsCount(); i++)
            master_tangents << 0.0 << 0.0 << 0.0 << 0.0;


    }





}
