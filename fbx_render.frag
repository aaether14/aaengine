#version 430 core




layout(location = 0, index = 0) out vec4 fragColor;




in vec3 M_space_normal;
in vec2 interpolated_uv;




uniform vec3 diffuse_color;
uniform sampler2D diffuse_texture;
uniform bool use_diffuse_texture;





vec4 ComputeLightColor()
{


    vec4 color = vec4(1.0);


    float light_factor = max(0.0, dot(vec3(0, 1, 0), M_space_normal)) * 1.0 + 0.4;


    return color * light_factor;


}





vec4 ComputeMaterialColor()
{



    vec4 color;


    if (use_diffuse_texture)
    {
        color = texture2D(diffuse_texture, interpolated_uv);
        if (color.a < 0.5)
            discard;
    }
    else
    {
        color = vec4(diffuse_color, 1.0);
    }


    return color;


}







void main( void )
{

    fragColor = ComputeLightColor() * ComputeMaterialColor();

}
