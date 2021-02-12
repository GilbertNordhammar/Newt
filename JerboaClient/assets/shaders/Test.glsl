#begin vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aNormal;

out vec2 vTexCoord;

uniform mat4 mat_VP;
uniform mat4 mat_model;
uniform mat4 mat_view;
uniform mat4 mat_projection;

void main()
{
    vTexCoord = aTexCoord;
    gl_Position = mat_VP * mat_model * vec4(aPos, 1.0);
}
#end vertex

#begin fragment
#version 330 core

//#include ../shaders/Jerboa/TestInclude.glsl
//#include Jerboa/TestInclude.glsl
#include <TestInclude.glsl>

//including TestInclude2.glsl here and in TestInclude.glsl to test include guard
#include <TestInclude2.glsl> 

out vec4 FragColor;

in vec2 vTexCoord;

void main()
{
    vec4 col_diffuse = texture(tex_diffuse0, vTexCoord);
    FragColor = vec4(col_diffuse.rgb, 1.0f);
} 
#end fragment