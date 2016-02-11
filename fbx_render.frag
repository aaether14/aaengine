#version 430 core



layout(location = 0, index = 0) out vec4 fragColor;



in vec3 M_space_normal;
in vec2 interpolated_uv;




uniform sampler2DArray textures;
uniform bool use_diffuse_texture;
uniform vec3 diffuse_color;





vec4 ComputeMaterialColor()
{


    float light_factor = max(0.0, dot(vec3(0, 1, 0), M_space_normal)) * 1.0 + 0.4;


    vec4 color;
    if (use_diffuse_texture)
        color = texture(textures, vec3(interpolated_uv, 0));
    else
        color = vec4(1.0);


    return color * light_factor;


}







void main( void )
{

    fragColor = ComputeMaterialColor();

}
