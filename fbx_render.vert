#version 430 core



layout(std430, binding = 0) buffer per_object
{
  mat4 matrix[];
};





in vec4 vertex;
in vec3 normal;
in vec2 uv;



uniform mat4 VP;



out vec3 M_space_normal;
out vec2 interpolated_uv;




void main( void )
{


    M_space_normal = normalize(vec3(matrix[0] * vec4(normal, 0.0)));
    interpolated_uv = uv;
    gl_Position = VP * matrix[0] * vertex;



}
