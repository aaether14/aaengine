#version 430 core



layout(std430, binding = 0) buffer per_object
{
  mat4 model_matrix[];
};





layout (location = 0) in vec4 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in uint drawid;





uniform mat4 VP;




out vec3 M_space_normal;
out vec2 interpolated_uv;





void main( void )
{


    M_space_normal = normalize(vec3(model_matrix[drawid] * vec4(normal, 0.0)));


    interpolated_uv = uv;


    gl_Position = VP * model_matrix[drawid] * vertex;



}
