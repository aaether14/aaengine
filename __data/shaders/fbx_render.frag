#version 430 core




layout(location = 0, index = 0) out vec4 fragColor;




in vec3 M_space_normal;
in vec2 interpolated_uv;




uniform vec3 diffuse_color;
uniform sampler2D diffuse_texture;
uniform bool use_diffuse_texture;




struct light
{
    vec4 ambient_color;
    vec4 diffuse_color;
    vec4 position;
    vec4 type_data;
};




layout(std430, binding = 1) buffer scene
{
    light lights[];
};




vec4 ComputeLightColor()
{


    vec4 color;
    for (int i = 0; i < lights.length(); i++)
    {
        if (lights[i].type_data.x == 0)
        {
            //Directional light
            color += (lights[i].diffuse_color * max(0.0, dot(vec3(lights[i].position), M_space_normal)) +
                      lights[i].ambient_color);
        }
    }
    return color;


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
