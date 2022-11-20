#version 330 core

#include <VertexInput2D>

out vec2 TexCoords;

void main()
{
    TexCoords = JB_VertexIn_TexCoord1;
    gl_Position = vec4(JB_VertexIn_Position2D.x, JB_VertexIn_Position2D.y, 0.0, 1.0); 
} 