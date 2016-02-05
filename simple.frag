#version 330

layout(location = 0, index = 0) out vec4 fragColor;



in vec3 M_space_normal;
in vec2 interpolated_uv;
uniform sampler2D material_texture;



void main( void )
{



 float light_factor = max(0.0, dot(vec3(0, 1, 0), M_space_normal)) * 2.5 + 0.25;
 fragColor = texture2D(material_texture, interpolated_uv) * light_factor;


}
