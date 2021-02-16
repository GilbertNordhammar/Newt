#begin vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 mat_VP;
uniform mat4 mat_model;

void main()
{
    gl_Position = mat_VP * mat_model * vec4(aPos, 1.0);
}
#end vertex

#begin fragment
#version 330 core

out vec4 FragColor;

uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0f);
//    FragColor = vec4(1,0,0,1);
} 
#end fragment