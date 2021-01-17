#begin vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 vTexCoords;

void main()
{
    vTexCoords = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

in vec2 vTexCoords;

void main()
{
    vec4 col_copy = col_test;
    vec4 col_diffuse = texture(tex_diffuse0, vTexCoords);
    FragColor = vec4(col_diffuse.rgb, 1.0f);
} 
#end fragment