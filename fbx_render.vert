#version 430


in vec4 vertex;
in vec3 normal;
in vec2 uv;
in int material_index;



uniform mat4 VP;
uniform mat4 M;



out vec3 M_space_normal;
out vec2 interpolated_uv;
flat out int frag_material_index;



void main( void )
{


    M_space_normal = normalize(vec3(M * vec4(normal, 0.0)));
    interpolated_uv = uv;
    frag_material_index = material_index;


    gl_Position = VP * M * vertex;



}
