#version 430 core


in vec4 vertex;
in vec3 normal;
in vec2 uv;



uniform mat4 VP;
uniform mat4 M;



out vec3 M_space_normal;
out vec2 interpolated_uv;



void main( void )
{


    M_space_normal = normalize(vec3(M * vec4(normal, 0.0)));
    interpolated_uv = uv;
    gl_Position = VP * M * vertex;



}
