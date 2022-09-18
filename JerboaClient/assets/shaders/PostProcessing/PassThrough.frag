#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D JB_uColorTexture0;

void main()
{
    vec3 color = texture(JB_uColorTexture0, TexCoords).rgb;
    FragColor = vec4(color, 1.0);
} 