#version 430 core



layout(std430, binding = 0) buffer per_object
{
    mat4 model_matrix[];
};





layout (location = 0) in vec4 vertex;
layout (location = 1) in uint drawid;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;
layout (location = 4) in vec4 tangent;





/**
*View Projection matrix
*/
uniform mat4 VP;



/**
*Information to be sent to the fragment shader
*/
out vec3 M_space_normal;
out vec4 M_space_tangent;
out vec2 interpolated_uv;





void main(void)
{


    /**
    *Model matrix without translation component
    */
    mat3 normal_matrix = mat3(model_matrix[drawid]);


    /**
    *Transform normal to model space
    */
    M_space_normal = normalize(normal_matrix * normal);


    /**
    *Transform tangent to model space
    */
    M_space_tangent.xyz = normalize(normal_matrix * tangent.xyz);
    M_space_tangent.w = tangent.w;


    /**
    *Pass uv to fragment shader
    */
    interpolated_uv = uv;


    /**
    *Pass vertex information
    */
    gl_Position = VP * model_matrix[drawid] * vertex;



}
