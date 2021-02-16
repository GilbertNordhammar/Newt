#begin vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 v2f_texCoord;
out vec3 v2f_worldPos;
out vec3 v2f_normal;

uniform mat4 mat_VP;
uniform mat4 mat_model;
uniform mat4 mat_view;
uniform mat4 mat_projection;

void main()
{
    v2f_normal = mat3(transpose(inverse(mat_model))) * aNormal; // TODO: Move transpose calculation to CPU and pass via uniform
    v2f_normal = normalize(v2f_normal);
    v2f_texCoord = aTexCoord;
    v2f_worldPos = (mat_model * vec4(aPos, 1.0)).xyz;
    gl_Position = mat_VP * vec4(v2f_worldPos, 1.0);
}
#end vertex

#begin fragment
#version 330 core

in vec2 v2f_texCoord;
in vec3 v2f_worldPos;
in vec3 v2f_normal;

out vec4 FragColor;

uniform bool useGamma;
uniform vec3 cameraWorldPos;

uniform struct {
    sampler2D albedo;
    sampler2D normal;
    sampler2D metallic;
    sampler2D roughness;
    sampler2D ao;
} material;

struct PointLight {
    vec3 color;
    float power;
    vec3 position;
};

#define MAX_POINT_LIGHTS 32
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int nPointLights = 0;

const float PI = 3.14159265359;

void main()
{
    vec3 albedo = texture(material.albedo, v2f_texCoord).rgb;
    vec3 normal = texture(material.normal, v2f_texCoord).rgb; // TODO: convert with tangent space matrix
    vec3 metallic = texture(material.metallic, v2f_texCoord).rgb;
    vec3 roughness = texture(material.roughness, v2f_texCoord).rgb;
    vec3 ao = texture(material.ao, v2f_texCoord).rgb;

    //    vec3 normal = normalize(v2f_normal);
    vec3 viewDir = normalize(cameraWorldPos - v2f_worldPos);

    vec3 baseRefl = vec3(0.04);
    // baseRefl = mix(baseRefl, albedo, metallic); // TODO: Calculate 'metallic'
    
    // reflectance equation
    vec3 reflectance = vec3(0.0);
    for(int i = 0; i < nPointLights; i++) 
    {
        // per-light radiance
        vec3 lightDir = normalize(pointLights[i].position - v2f_worldPos);
        vec3 halfway = normalize(lightDir + viewDir);
        float distToLight = length(pointLights[i].position - v2f_worldPos);
        float attenuation = 1.0 / (distToLight * distToLight);
        vec3 radiance = pointLights[i].color * pointLights[i].power * attenuation;
        
        albedo += radiance;
    }

    if(useGamma)
        albedo = pow(albedo, vec3(1.0 / 2.2));

    FragColor = vec4(albedo, 1.0f);
} 
#end fragment