#version 330 core
out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D tex_diffuse0;

void main()
{
    vec4 col_diffuse = texture(tex_diffuse0, vTexCoords);
    FragColor = vec4(col_diffuse.rgb, 1.0f);
} 