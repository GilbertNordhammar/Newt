#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D JB_uDepthTexture; // slot 7

void main()
{
    vec3 color = texture(JB_uDepthTexture, TexCoords).rgb;
    color.r = pow(color.r, 4.0); // Make depth more visible
    FragColor = vec4(vec3(color.r), 1.0);
} 