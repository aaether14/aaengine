#include <fbx_manager/mesh.hpp>







void Mesh::LoadBufferObjects(FbxNode *root)
{





    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glGenBuffers(1, &ssbo);
    f->glGenBuffers(1, &indirect_buffer);
    f->glGenBuffers(1, &per_object_buffer);





    QVector<unsigned int> master_indices;
    QVector<float> master_vertices;
    QVector<float> master_normals;
    QVector<float> master_uvs;
    QVector<float> master_tangents;




    RecursiveLoad(root,
                  master_indices,
                  master_vertices,
                  master_normals,
                  master_uvs,
                  master_tangents);




    //creating vertex array object




    f->glGenVertexArrays(1, &vao);
    f->glBindVertexArray(vao);



    //loading indices



    f->glGenBuffers(1, &master_ibo);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, master_ibo);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * master_indices.size(), &master_indices[0], GL_STATIC_DRAW);




    f->glGenBuffers(1, &master_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, master_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_vertices.size(), &master_vertices[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);



    f->glGenBuffers(1, &master_normals_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, master_normals_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_normals.size(), &master_normals[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);




    f->glGenBuffers(1, &master_uvs_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, master_uvs_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_uvs.size(), &master_uvs[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);




    f->glGenBuffers(1, &master_tangents_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, master_tangents_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * master_tangents.size(), &master_tangents[0], GL_STATIC_DRAW);
    f->glEnableVertexAttribArray(3);
    f->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);





    f->glBindVertexArray(0);



    master_indices.clear();
    master_vertices.clear();
    master_normals.clear();
    master_uvs.clear();
    master_tangents.clear();




    //Handling cached drawing data loading



    QVector<DrawElementsCommand> cached_commands;
    QVector<unsigned int> cached_per_object_index;



    foreach(auto it, materials.keys())
    {



        QVector<DrawElementsCommand> commands;
        QVector<unsigned int> per_object_index;


        CacheDrawCommands(mesh_entries,
                          commands,
                          per_object_index,
                          it);



        indirect_buffer_stride_cache[it] = cached_commands.size();
        indirect_buffer_size_cache[it] = commands.size();
        per_object_buffer_stride_cache[it] = cached_per_object_index.size();



        cached_commands << commands;
        cached_per_object_index << per_object_index;





    }



    f->glGenBuffers(1, &cached_indirect_buffer);
    f->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, cached_indirect_buffer);
    f->glBufferData( GL_DRAW_INDIRECT_BUFFER,
                     sizeof(DrawElementsCommand) * cached_commands.size(),
                     &cached_commands[0],
            GL_STATIC_DRAW );


    f->glGenBuffers(1, &cached_per_object_buffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, cached_per_object_buffer);
    f->glBufferData(GL_ARRAY_BUFFER,
                    sizeof(unsigned int) * cached_per_object_index.size(),
                    &cached_per_object_index[0],
            GL_STATIC_DRAW);




    cached_commands.clear();
    cached_per_object_index.clear();






}


