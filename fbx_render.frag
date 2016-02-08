#version 430



layout(location = 0, index = 0) out vec4 fragColor;



in vec3 M_space_normal;
in vec2 interpolated_uv;
flat in int frag_material_index;




uniform sampler2D diffuse_texture;
uniform bool use_diffuse_texture;
uniform vec3 diffuse_color;





vec4 ComputeMaterialColor()
{


    float light_factor = max(0.0, dot(vec3(0, 1, 0), M_space_normal)) * 1.0 + 0.4;


    vec4 color;
    if (use_diffuse_texture)
        color = texture2D(diffuse_texture, interpolated_uv);
    else
        color = vec4(diffuse_color, 1.0);


    return color * light_factor;


}







void main( void )
{

    fragColor = ComputeMaterialColor();

}
