#version 430 core




layout(location = 0, index = 0) out vec4 fragColor;




/**
*Information from vertex shader
*/
in vec3 M_space_normal;
in vec4 M_space_tangent;
in vec2 interpolated_uv;




/**
*Material Information
*/
uniform vec3 diffuse_color;
uniform float diffuse_intensity;
uniform bool use_diffuse_texture;
uniform vec3 specular_color;
uniform float specular_intensity;
uniform float specular_hardness;




/**
*Texture samplers
*/
uniform sampler2D diffuse_texture;
uniform sampler2D normal_map;




/**
*True if the mesh will use normal mapping
*/
uniform bool is_using_tangents;




/**
*This is how light information is structured
*/
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





vec3 ComputeNormal()
{



    if (is_using_tangents)
    {



        vec3 normal = normalize(M_space_normal);
        vec3 tangent = normalize(M_space_tangent.xyz);
        tangent = normalize(tangent - dot(tangent, normal) * normal);
        vec3 binormal = cross(normal, tangent.xyz) * M_space_tangent.w;


        mat3 TBN = mat3(tangent, binormal, normal);
        vec3 bump_normal = texture2D(normal_map, interpolated_uv).xyz;
        bump_normal = 2.0 * bump_normal - 1.0;



        return normalize(TBN * bump_normal);



    }
    else
    {
        return normalize(M_space_normal);
    }



}





vec4 ComputeLightColor()
{



    vec3 normal = ComputeNormal();



    vec4 color;
    for (int i = 0; i < lights.length(); i++)
    {



        if (lights[i].type_data.x == 0)
        {

            /**
            *Directional ligtht
            */
            vec4 l_diffuse_color = lights[i].diffuse_color * max(0.0, dot(vec3(lights[i].position), normal));
            vec4 l_ambient_color = lights[i].ambient_color;
            color += (l_diffuse_color + l_ambient_color);



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
        color = vec4(diffuse_color * diffuse_intensity, 1.0);
    }


    return color;


}







void main( void )
{


    fragColor = ComputeLightColor() * ComputeMaterialColor();


}
