#version 430 core



layout(location = 0, index = 0) out vec4 fragColor;



in vec3 M_space_normal;
in vec2 interpolated_uv;





vec4 ComputeMaterialColor()
{


    float light_factor = max(0.0, dot(vec3(0, 1, 0), M_space_normal)) * 1.0 + 0.4;
    return vec4(1.0) * light_factor;


}







void main( void )
{

    fragColor = ComputeMaterialColor();

}
